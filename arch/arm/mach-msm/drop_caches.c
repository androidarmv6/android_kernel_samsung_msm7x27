
#include <linux/kthread.h>
#include <linux/timer.h>
#include <asm/uaccess.h>
#include <asm/param.h>
#include <linux/fs.h>
#include "proc_comm.h"

#define INIT_CHECK_INTERVAL ( 45 * HZ ) // 45 sec
#define CHECK_INTERVAL ( 1200 * HZ ) // every 20 min

void drop_caches_check_event(struct work_struct *work);
void drop_caches_registertimer(struct timer_list* ptimer, unsigned long timeover );
void drop_caches_timeout(unsigned long arg);

struct timer_list drop_caches_timer;
struct workqueue_struct *drop_caches_wq;
static DECLARE_WORK(drop_caches_work, drop_caches_check_event);
//extern void do_sync(unsigned long wait);
extern void do_sync(void);

void drop_caches_check_event(struct work_struct *work)
{
	int id = 0;

	mm_segment_t old_fs;
	struct file *filp;
	char buff[1] = {'1'};

	printk("[DP] do drop_caches\n");

	msm_proc_comm(PCOM_CUSTOMER_CMD3, &id, 0);

//	do_sync(1);
	do_sync();

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	filp = filp_open("/proc/sys/vm/drop_caches", O_WRONLY, 0666);
	if(!filp)
		printk("Can't open /proc/sys/vm/drop_caches file\n");
	else
		filp->f_op->write(filp, (void *)buff, 1, &filp->f_pos);
		
	set_fs(old_fs);
}

void drop_caches_registertimer(struct timer_list* ptimer, unsigned long timeover )
{
	init_timer(ptimer);
	ptimer->expires = get_jiffies_64() + timeover;
	ptimer->data = (long) NULL;
	ptimer->function = drop_caches_timeout;
	add_timer(ptimer);
}

void drop_caches_timeout(unsigned long arg)
{
	queue_work(drop_caches_wq, &drop_caches_work);
	//drop_caches_registertimer(&drop_caches_timer, CHECK_INTERVAL);
}

static void drop_caches_thread(void)
{
	drop_caches_wq = create_singlethread_workqueue("drop_caches");
	if (!drop_caches_wq) {
		printk(KERN_ERR "%s: create workque failed \n", __func__);
		return;
	}

	drop_caches_registertimer(&drop_caches_timer, INIT_CHECK_INTERVAL);
	printk("[DP] drop_caches_registerd\n");
}
 
static int __init drop_caches_init(void)
{
	drop_caches_thread();
	return 0;
}
 
module_init(drop_caches_init);
