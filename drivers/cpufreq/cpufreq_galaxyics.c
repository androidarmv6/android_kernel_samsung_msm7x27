/*
 * drivers/cpufreq/cpufreq_galaxyics.c
 *
 * Copyright (C) 2013 MaclawStudio
 * Copyright (C) 2010 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Author: Mike Chan (mike@android.com)
 * Modified by: Marcin Chojnacki (marcinch7@gmail.com)
 */

#include <linux/cpu.h>
#include <linux/cpumask.h>
#include <linux/cpufreq.h>
#include <linux/sched.h>
#include <linux/tick.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/moduleparam.h>
#include <asm/cputime.h>
#include <linux/earlysuspend.h>

static unsigned int awake_ideal_freq;
static unsigned int sleep_ideal_freq;
static unsigned int ramp_up_step;
static unsigned int ramp_down_step;
static unsigned long max_cpu_load;
static unsigned long min_cpu_load;
static unsigned long up_rate_us;
static unsigned long down_rate_us;
static unsigned int sample_rate_jiffies;

static void (*pm_idle_old)(void);
static atomic_t active_count = ATOMIC_INIT(0);

struct galaxyics_info_s {
	struct cpufreq_policy *cur_policy;
	struct cpufreq_frequency_table *freq_table;
	struct timer_list timer;
	u64 time_in_idle;
	u64 idle_exit_time;
	u64 freq_change_time;
	u64 freq_change_time_in_idle;
	int cur_cpu_load;
	int old_freq;
	int ramp_dir;
	unsigned int enable;
	int ideal_speed;
};
static DEFINE_PER_CPU(struct galaxyics_info_s, galaxyics_info);

static struct workqueue_struct *up_wq;
static struct workqueue_struct *down_wq;
static struct work_struct freq_scale_work;

static cpumask_t work_cpumask;
static spinlock_t cpumask_lock;
static unsigned int suspended;

static int cpufreq_governor_galaxyics(struct cpufreq_policy *policy,
		unsigned int event);

#ifndef CONFIG_CPU_FREQ_DEFAULT_GOV_GALAXYICS
static
#endif
struct cpufreq_governor cpufreq_gov_galaxyics = {
	.name = "galaxyics",
	.governor = cpufreq_governor_galaxyics,
	.max_transition_latency = 9000000,
	.owner = THIS_MODULE,
};

inline static void galaxyics_update_min_max(struct galaxyics_info_s *this_galaxyics, struct cpufreq_policy *policy, int suspend) {
	if (suspend) {
		this_galaxyics->ideal_speed =
			policy->max > sleep_ideal_freq ?
			(sleep_ideal_freq > policy->min ? sleep_ideal_freq : policy->min) : policy->max;
	} else {
		this_galaxyics->ideal_speed =
			policy->min < awake_ideal_freq ?
			(awake_ideal_freq < policy->max ? awake_ideal_freq : policy->max) : policy->min;
	}
}

inline static void galaxyics_update_min_max_allcpus(void) {
	unsigned int i;
	for_each_online_cpu(i) {
		struct galaxyics_info_s *this_galaxyics = &per_cpu(galaxyics_info, i);
		if (this_galaxyics->enable)
			galaxyics_update_min_max(this_galaxyics,this_galaxyics->cur_policy,suspended);
	}
}

inline static unsigned int validate_freq(struct cpufreq_policy *policy, int freq) {
	if (freq > (int)policy->max)
		return policy->max;
	if (freq < (int)policy->min)
		return policy->min;
	return freq;
}

inline static void reset_timer(unsigned long cpu, struct galaxyics_info_s *this_galaxyics) {
	this_galaxyics->time_in_idle = get_cpu_idle_time_us(cpu, &this_galaxyics->idle_exit_time);
	mod_timer(&this_galaxyics->timer, jiffies + sample_rate_jiffies);
}

inline static void work_cpumask_set(unsigned long cpu) {
	unsigned long flags;
	spin_lock_irqsave(&cpumask_lock, flags);
	cpumask_set_cpu(cpu, &work_cpumask);
	spin_unlock_irqrestore(&cpumask_lock, flags);
}

inline static int work_cpumask_test_and_clear(unsigned long cpu) {
	unsigned long flags;
	int res = 0;
	spin_lock_irqsave(&cpumask_lock, flags);
	res = cpumask_test_and_clear_cpu(cpu, &work_cpumask);
	spin_unlock_irqrestore(&cpumask_lock, flags);
	return res;
}

inline static int target_freq(struct cpufreq_policy *policy, struct galaxyics_info_s *this_galaxyics,
			      int new_freq, int old_freq, int prefered_relation) {
	int index, target;
	struct cpufreq_frequency_table *table = this_galaxyics->freq_table;

	if (new_freq == old_freq)
		return 0;
	new_freq = validate_freq(policy,new_freq);
	if (new_freq == old_freq)
		return 0;

	if (table &&
	    !cpufreq_frequency_table_target(policy,table,new_freq,prefered_relation,&index))
	{
		target = table[index].frequency;
		if (target == old_freq) {
			if (new_freq > old_freq && prefered_relation==CPUFREQ_RELATION_H
			    && !cpufreq_frequency_table_target(policy,table,new_freq,
							       CPUFREQ_RELATION_L,&index))
				target = table[index].frequency;
			else if (new_freq < old_freq && prefered_relation==CPUFREQ_RELATION_L
				&& !cpufreq_frequency_table_target(policy,table,new_freq,
								   CPUFREQ_RELATION_H,&index))
				target = table[index].frequency;
		}

		if (target == old_freq)
			return 0;
	}
	else target = new_freq;

	__cpufreq_driver_target(policy, target, prefered_relation);

	return target;
}

static void cpufreq_galaxyics_timer(unsigned long cpu)
{
	u64 delta_idle;
	u64 delta_time;
	int cpu_load;
	int old_freq;
	u64 update_time;
	u64 now_idle;
	int queued_work = 0;
	struct galaxyics_info_s *this_galaxyics = &per_cpu(galaxyics_info, cpu);
	struct cpufreq_policy *policy = this_galaxyics->cur_policy;

	now_idle = get_cpu_idle_time_us(cpu, &update_time);
	old_freq = policy->cur;

	if (this_galaxyics->idle_exit_time == 0 || update_time == this_galaxyics->idle_exit_time)
		return;

	delta_idle = cputime64_sub(now_idle, this_galaxyics->time_in_idle);
	delta_time = cputime64_sub(update_time, this_galaxyics->idle_exit_time);

	if (delta_time < 1000) {
		if (!timer_pending(&this_galaxyics->timer))
			reset_timer(cpu,this_galaxyics);
		return;
	}

	if (delta_idle > delta_time)
		cpu_load = 0;
	else
		cpu_load = 100 * (unsigned int)(delta_time - delta_idle) / (unsigned int)delta_time;

	this_galaxyics->cur_cpu_load = cpu_load;
	this_galaxyics->old_freq = old_freq;

	if (cpu_load > max_cpu_load || delta_idle == 0)
	{
		if (old_freq < policy->max &&
			 (old_freq < this_galaxyics->ideal_speed || delta_idle == 0 ||
			  cputime64_sub(update_time, this_galaxyics->freq_change_time) >= up_rate_us))
		{
			this_galaxyics->ramp_dir = 1;
			work_cpumask_set(cpu);
			queue_work(up_wq, &freq_scale_work);
			queued_work = 1;
		}
		else this_galaxyics->ramp_dir = 0;
	}
	else if (cpu_load < min_cpu_load && old_freq > policy->min &&
		 (old_freq > this_galaxyics->ideal_speed ||
		  cputime64_sub(update_time, this_galaxyics->freq_change_time) >= down_rate_us))
	{
		this_galaxyics->ramp_dir = -1;
		work_cpumask_set(cpu);
		queue_work(down_wq, &freq_scale_work);
		queued_work = 1;
	}
	else this_galaxyics->ramp_dir = 0;

	if (!queued_work && old_freq < policy->max)
		reset_timer(cpu,this_galaxyics);
}

static void cpufreq_idle(void)
{
	struct galaxyics_info_s *this_galaxyics = &per_cpu(galaxyics_info, smp_processor_id());
	struct cpufreq_policy *policy = this_galaxyics->cur_policy;

	if (!this_galaxyics->enable) {
		pm_idle_old();
		return;
	}

	if (policy->cur == policy->min && timer_pending(&this_galaxyics->timer))
		del_timer(&this_galaxyics->timer);

	pm_idle_old();

	if (!timer_pending(&this_galaxyics->timer))
		reset_timer(smp_processor_id(), this_galaxyics);
}

static void cpufreq_galaxyics_freq_change_time_work(struct work_struct *work)
{
	unsigned int cpu;
	int new_freq;
	int old_freq;
	int ramp_dir;
	struct galaxyics_info_s *this_galaxyics;
	struct cpufreq_policy *policy;
	unsigned int relation = CPUFREQ_RELATION_L;
	for_each_possible_cpu(cpu) {
		this_galaxyics = &per_cpu(galaxyics_info, cpu);
		if (!work_cpumask_test_and_clear(cpu))
			continue;

		ramp_dir = this_galaxyics->ramp_dir;
		this_galaxyics->ramp_dir = 0;

		old_freq = this_galaxyics->old_freq;
		policy = this_galaxyics->cur_policy;

		if (old_freq != policy->cur)
			new_freq = old_freq;
		else if (ramp_dir > 0 && nr_running() > 1) {
			if (old_freq < this_galaxyics->ideal_speed)
				new_freq = this_galaxyics->ideal_speed;
			else if (ramp_up_step) {
				new_freq = old_freq + ramp_up_step;
				relation = CPUFREQ_RELATION_H;
			}
			else {
				new_freq = policy->max;
				relation = CPUFREQ_RELATION_H;
			}
		}
		else if (ramp_dir < 0) {
			if (old_freq > this_galaxyics->ideal_speed) {
				new_freq = this_galaxyics->ideal_speed;
				relation = CPUFREQ_RELATION_H;
			}
			else if (ramp_down_step)
				new_freq = old_freq - ramp_down_step;
			else {
				new_freq = old_freq * this_galaxyics->cur_cpu_load / max_cpu_load;
				if (new_freq > old_freq)
					new_freq = old_freq -1;
			}
		}
		else 
			new_freq = old_freq;

		new_freq = target_freq(policy,this_galaxyics,new_freq,old_freq,relation);
		if (new_freq)
			this_galaxyics->freq_change_time_in_idle =
				get_cpu_idle_time_us(cpu,&this_galaxyics->freq_change_time);

		if (new_freq < policy->max)
			reset_timer(cpu,this_galaxyics);
		else if (timer_pending(&this_galaxyics->timer))
			del_timer(&this_galaxyics->timer);
	}
}

static int cpufreq_governor_galaxyics(struct cpufreq_policy *new_policy,
		unsigned int event)
{
	unsigned int cpu = new_policy->cpu;
	struct galaxyics_info_s *this_galaxyics = &per_cpu(galaxyics_info, cpu);

	switch (event) {
	case CPUFREQ_GOV_START:
		if ((!cpu_online(cpu)) || (!new_policy->cur))
			return -EINVAL;

		this_galaxyics->cur_policy = new_policy;

		this_galaxyics->enable = 1;

		galaxyics_update_min_max(this_galaxyics,new_policy,suspended);

		this_galaxyics->freq_table = cpufreq_frequency_get_table(cpu);

		smp_wmb();

		if (atomic_inc_return(&active_count) <= 1) {
			pm_idle_old = pm_idle;
			pm_idle = cpufreq_idle;
		}

		if (this_galaxyics->cur_policy->cur < new_policy->max && !timer_pending(&this_galaxyics->timer))
			reset_timer(cpu,this_galaxyics);

		break;

	case CPUFREQ_GOV_LIMITS:
		galaxyics_update_min_max(this_galaxyics,new_policy,suspended);

		if (this_galaxyics->cur_policy->cur > new_policy->max)
			__cpufreq_driver_target(this_galaxyics->cur_policy,
						new_policy->max, CPUFREQ_RELATION_H);
		else if (this_galaxyics->cur_policy->cur < new_policy->min)
			__cpufreq_driver_target(this_galaxyics->cur_policy,
						new_policy->min, CPUFREQ_RELATION_L);

		if (this_galaxyics->cur_policy->cur < new_policy->max && !timer_pending(&this_galaxyics->timer))
			reset_timer(cpu,this_galaxyics);

		break;

	case CPUFREQ_GOV_STOP:
		this_galaxyics->enable = 0;
		smp_wmb();
		del_timer(&this_galaxyics->timer);
		flush_work(&freq_scale_work);
		this_galaxyics->idle_exit_time = 0;

		if (atomic_dec_return(&active_count) <= 1)
			pm_idle = pm_idle_old;

		break;
	}

	return 0;
}

static void galaxyics_suspend(int cpu, int suspend)
{
	struct galaxyics_info_s *this_galaxyics = &per_cpu(galaxyics_info, smp_processor_id());
	struct cpufreq_policy *policy = this_galaxyics->cur_policy;
	unsigned int new_freq;

	if (!this_galaxyics->enable)
		return;

	galaxyics_update_min_max(this_galaxyics,policy,suspend);
	if (!suspend) {
		new_freq = validate_freq(policy,awake_ideal_freq);
		__cpufreq_driver_target(policy, new_freq,
					CPUFREQ_RELATION_L);
	} else {
		this_galaxyics->freq_change_time_in_idle =
			get_cpu_idle_time_us(cpu,&this_galaxyics->freq_change_time);
	}

	reset_timer(smp_processor_id(),this_galaxyics);
}

static void galaxyics_early_suspend(struct early_suspend *handler) {
	int i;
	if (suspended || sleep_ideal_freq==0)
		return;
	suspended = 1;
	for_each_online_cpu(i)
		galaxyics_suspend(i,1);
}

static void galaxyics_late_resume(struct early_suspend *handler) {
	int i;
	if (!suspended)
		return;
	suspended = 0;
	for_each_online_cpu(i)
		galaxyics_suspend(i,0);
}

static struct early_suspend galaxyics_power_suspend = {
	.suspend = galaxyics_early_suspend,
	.resume = galaxyics_late_resume,
};

static int __init cpufreq_galaxyics_init(void)
{
	unsigned int i;
	struct galaxyics_info_s *this_galaxyics;

	awake_ideal_freq = 800000;
	sleep_ideal_freq = 122880;
	ramp_up_step = 128000;
	ramp_down_step = 256000;
	max_cpu_load = 50;
	min_cpu_load = 25;
	up_rate_us = 48000;
	down_rate_us = 99000;
	sample_rate_jiffies = 2;

	spin_lock_init(&cpumask_lock);
	suspended = 0;

	for_each_possible_cpu(i) {
		this_galaxyics = &per_cpu(galaxyics_info, i);
		this_galaxyics->enable = 0;
		this_galaxyics->cur_policy = 0;
		this_galaxyics->ramp_dir = 0;
		this_galaxyics->time_in_idle = 0;
		this_galaxyics->idle_exit_time = 0;
		this_galaxyics->freq_change_time = 0;
		this_galaxyics->freq_change_time_in_idle = 0;
		this_galaxyics->cur_cpu_load = 0;
		init_timer_deferrable(&this_galaxyics->timer);
		this_galaxyics->timer.function = cpufreq_galaxyics_timer;
		this_galaxyics->timer.data = i;
		work_cpumask_test_and_clear(i);
	}

	up_wq = create_rt_workqueue("kgalaxyics_up");
	down_wq = create_workqueue("kgalaxyics_down");
	if (!up_wq || !down_wq)
		return -ENOMEM;

	INIT_WORK(&freq_scale_work, cpufreq_galaxyics_freq_change_time_work);

	register_early_suspend(&galaxyics_power_suspend);

	return cpufreq_register_governor(&cpufreq_gov_galaxyics);
}

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_GALAXYICS
fs_initcall(cpufreq_galaxyics_init);
#else
module_init(cpufreq_galaxyics_init);
#endif

static void __exit cpufreq_galaxyics_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_galaxyics);
	destroy_workqueue(up_wq);
	destroy_workqueue(down_wq);
}

module_exit(cpufreq_galaxyics_exit);

MODULE_AUTHOR("Marcin Chojnacki <marcinch7@gmail.com>");
MODULE_DESCRIPTION("'cpufreq_galaxyics' - A cpufreq governor optimized for GalaxyICS devices");
MODULE_LICENSE("GPL");
