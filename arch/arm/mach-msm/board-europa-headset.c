/*
 *  H2W device detection driver.
 *
 * Copyright (C) 2008 SAMSUNG Corporation.
 * Copyright (C) 2008 Google, Inc.
 *
 * Authors: 
 *  Laurence Chen <Laurence_Chen@htc.com>
 *  Nick Pelly <npelly@google.com>
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
 */

/*  For detecting SAMSUNG 2 Wire devices, such as wired headset.

    Logically, the H2W driver is always present, and H2W state (hi->state)
    indicates what is currently plugged into the H2W interface.

    When the headset is plugged in, CABLE_IN1 is pulled low. When the headset
    button is pressed, CABLE_IN2 is pulled low. These two lines are shared with
    the TX and RX (respectively) of UART3 - used for serial debugging.

    This headset driver keeps the CPLD configured as UART3 for as long as
    possible, so that we can do serial FIQ debugging even when the kernel is
    locked and this driver no longer runs. So it only configures the CPLD to
    GPIO while the headset is plugged in, and for 10ms during detection work.

    Unfortunately we can't leave the CPLD as UART3 while a headset is plugged
    in, UART3 is pullup on TX but the headset is pull-down, causing a 55 mA
    drain on bigfoot.

    The headset detection work involves setting CPLD to GPIO, and then pulling
    CABLE_IN1 high with a stronger pullup than usual. A H2W headset will still
    pull this line low, whereas other attachments such as a serial console
    would get pulled up by this stronger pullup.

    Headset insertion/removal causes UEvent's to be sent, and
    /sys/class/switch/h2w/state to be updated.

    Button presses are interpreted as input event (KEY_MEDIA). Button presses
    are ignored if the headset is plugged in, so the buttons on 11 pin -> 3.5mm
    jack adapters do not work until a headset is plugged into the adapter. This
    is to avoid serial RX traffic causing spurious button press events.

    We tend to check the status of CABLE_IN1 a few more times than strictly
    necessary during headset detection, to avoid spurious headset insertion
    events caused by serial debugger TX traffic.
*/

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/sysdev.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/irq.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/hrtimer.h>
#include <linux/switch.h>
#include <linux/input.h>
#include <linux/debugfs.h>
#include <asm/gpio.h>
#include <asm/atomic.h>
#include <mach/board.h>
#include <mach/vreg.h>
#include <mach/pmic.h>

#include <linux/wakelock.h>

#include <mach/hardware.h>

#define FEATURE_SENDEND_ENABLE

#if defined(CONFIG_MACH_CALLISTO) || defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_LUCAS)
#define JACK_ACTIVE_LOW

#define GPIO_JACK_S_35 	28
#define GPIO_SEND_END 	29

#elif defined(CONFIG_MACH_EUROPA)

#if (CONFIG_BOARD_REVISION == 1)

#define GPIO_JACK_S_35 	92
#define GPIO_SEND_END 	16		// for volrans rev0.3, SEND_END isn't GPIO. it should be modified

#else	/* CONFIG_BOARD_REVOSION > 1 */

#define GPIO_JACK_S_35 	28
#define GPIO_SEND_END 	29

#endif	/* CONDIG_BOARD_REVISION */
#endif /* CONFIG_MACH_EUROPA */

/*******************  define FEATURES ***************************/
#define FEATURE_SND_RPC
#define FEATURE_SND_RPC_TEMP
#define FEATURE_3PI_ADC
/****************************************************************/

#ifdef FEATURE_SND_RPC
#include <mach/msm_rpcrouter.h>
#define SND_RPC_PROG 			0x30000002
#define SND_RPC_VERS 			0x00020001
#define SND_MUTE_UNMUTED		0
#define SND_MUTE_MUTED			1
#define	SND_DEVICE_HEADSET		3
#define SND_DEVICE_FORCE_SPEAKER	26
#define SND_SET_DEVICE_PROC		2
#define SND_SET_EXTAMP_PROC		100
int flag_boot = 1;
int suspend_state = 0;
int resume_state = 0;
int suspend_count = 0;
#endif

#ifdef FEATURE_3PI_ADC
#include "proc_comm.h"
#define SMEM_PROC_COMM_GET_ADC			PCOM_OEM_SAMSUNG_GET_ADC
#define SMEM_PROC_COMM_MICBIAS_ONOFF	PCOM_OEM_MICBIAS_ONOFF
// SMEM_PROC_COMM_GET_ADC data 1
enum {
	SMEM_PROC_COMM_GET_ADC_BATTERY = 0x0,
	SMEM_PROC_COMM_GET_ADC_TEMP,
	SMEM_PROC_COMM_GET_ADC_VF,
	SMEM_PROC_COMM_GET_ADC_ALL, // data1 : VF(MSB 2 bytes) vbatt_adc(LSB 2bytes), data2 : temp_adc
	SMEM_PROC_COMM_GET_ADC_EAR_ADC,		// 3PI_ADC
	SMEM_PROC_COMM_GET_ADC_MAX,
};

enum {
	SMEM_PROC_COMM_MICBIAS_CONTROL_OFF = 0x0,
	SMEM_PROC_COMM_MICBIAS_CONTROL_ON,
	SMEM_PROC_COMM_MICBIAS_CONTROL_MAX
};

static int checking_adc = 0;

int get_3pi_adc(void)
{
	int res = 0;
	int data1 = SMEM_PROC_COMM_GET_ADC_EAR_ADC;
	int data2 = 0;

	res = msm_proc_comm(SMEM_PROC_COMM_GET_ADC, &data1, &data2);
	if(res < 0)
	{
		printk(KERN_ERR "[H2W] %s :%d fail %d\n", __func__, data1, res);
		return res;
	}

	return data1;
}
#endif

//#define CVT_FROM_MS(val) 			(val*1000000)
//#define BTN_PRESS_DEBOUNCE_TIME	 	CVT_FROM_MS(150)

#define CONFIG_DEBUG_H2W

#ifdef CONFIG_DEBUG_H2W
#define H2W_DBG(fmt, arg...) printk(KERN_INFO "[H2W] %s " fmt "\r\n", __func__, ## arg)
#else
#define H2W_DBG(fmt, arg...) do {} while (0)
#endif

static struct wake_lock headset_delayed_work_wake_lock;
extern unsigned int on_call;

static struct workqueue_struct *g_detection_work_queue;
static void detection_work(struct work_struct *work);
static DECLARE_WORK(g_detection_work, detection_work);

#if 1	// for DFMS test
static struct workqueue_struct *g_earbutton_work_queue;
static void earbutton_work(struct work_struct *work);
static DECLARE_WORK(g_earbutton_work, earbutton_work);
static unsigned int earbutton_pressed = 0;
#endif

#define BIT_HEADSET		(1 << 0)
#define BIT_HEADSET_NO_MIC	(1 << 1)

static void earbutton_func_work(struct work_struct *work);
static DECLARE_WORK(g_earbutton_func_work, earbutton_func_work);


enum {
	H2W_NO_DEVICE	= 0,
	H2W_SEC_HEADSET	= 1,
	H2W_NORMAL_HEADSET = 2, 
};

struct h2w_info {
	struct switch_dev sdev;
	struct switch_dev button_sdev;	// for DFMS test

	struct input_dev *input;
	struct mutex mutex_lock;

	atomic_t btn_state;
	int ignore_btn;

	unsigned int irq;
	unsigned int irq_btn;
	int btn_11pin_35mm_flag;

	struct hrtimer timer;
	ktime_t debounce_time;
	int headset_state;

	struct hrtimer btn_timer;
	ktime_t btn_debounce_time;
	int button_state;
	
	unsigned int use_irq : 1;
};
static struct h2w_info *hi;

static int h2w_suspend(struct platform_device * device, pm_message_t state)
{
	++suspend_count;
	suspend_state = gpio_get_value(GPIO_JACK_S_35);
	H2W_DBG("suspend_state = %s", suspend_state?"connected":"disconnected");
	return 0;
}
static int h2w_resume(struct platform_device * device)
{
	--suspend_count;
	resume_state = gpio_get_value(GPIO_JACK_S_35);
	H2W_DBG("resume_state = %s", resume_state?"connected":"disconnected");
	return 0;
}

static ssize_t h2w_print_name(struct switch_dev *sdev, char *buf)
{
	switch (switch_get_state(&hi->sdev)) {
	case H2W_NO_DEVICE:
		return sprintf(buf, "No Device\n");
	case H2W_SEC_HEADSET:
		return sprintf(buf, "H2W_SEC_HEADSET\n");
	case H2W_NORMAL_HEADSET:
		return sprintf(buf, "H2W_NORMAL_HEADSET\n");
	}
	return -EINVAL;
}
static ssize_t h2w_set_state(struct switch_dev *sdev, char *buf)
{
	int state = *buf - 48;
	switch(state){
	case H2W_NO_DEVICE:
		switch_set_state(&hi->sdev, H2W_NO_DEVICE);
		return 0;
	case H2W_SEC_HEADSET:
		switch_set_state(&hi->sdev, H2W_SEC_HEADSET);
		return 0;
	case H2W_NORMAL_HEADSET:
		switch_set_state(&hi->sdev, H2W_NORMAL_HEADSET);
		return 0;
	default:
		break;
	}

	return -EINVAL;
}


#if 1	// for DFMS test
static ssize_t button_print_name(struct switch_dev *sdev, char *buf)
{
	switch (switch_get_state(&hi->button_sdev)) {
	case 0:
		return sprintf(buf, "No Input\n");
	case 1:
		return sprintf(buf, "Button Pressed\n");
	}
	return -EINVAL;
}
#endif

static void button_pressed(void)
{

	mdelay(50);
#ifdef JACK_ACTIVE_LOW	
	if(gpio_get_value(GPIO_JACK_S_35))
#else
	if(!gpio_get_value(GPIO_JACK_S_35))
#endif
	{
		H2W_DBG("ignored cuz headset was removed");
		return;
	}

	H2W_DBG("@@@@ press adc = [%d] \n", checking_adc);
	if ( checking_adc >= 7  && checking_adc < 10 )
	{
		atomic_set(&hi->btn_state, 1);
		input_report_key(hi->input, KEY_MEDIA, 1);
		input_sync(hi->input);

		earbutton_pressed = 1;
		// for DFMS test
		queue_work(g_earbutton_work_queue, &g_earbutton_work);
	}
}

static void button_released(void)
{
	atomic_set(&hi->btn_state, 0);
	input_report_key(hi->input, KEY_MEDIA, 0);
	input_sync(hi->input);

	earbutton_pressed = 0;
	// for DFMS test
	queue_work(g_earbutton_work_queue, &g_earbutton_work);
}

#ifdef FEATURE_SENDEND_ENABLE
static void remove_headset(void)
{
	int res;
	int data1;
	int data2;

	unsigned long irq_flags;

	mutex_lock(&hi->mutex_lock);
	switch_set_state(&hi->sdev, switch_get_state(&hi->sdev) &
			~(BIT_HEADSET | BIT_HEADSET_NO_MIC));
	mutex_unlock(&hi->mutex_lock);
	// for headset detection sound
	wake_lock_timeout(&headset_delayed_work_wake_lock, 5*HZ);

#ifndef FEATURE_SENDEND_ENABLE
	set_irq_wake(hi->irq_btn, 0);
	/* Disable button */
	local_irq_save(irq_flags);
	disable_irq(hi->irq_btn);
	local_irq_restore(irq_flags);
	//	mic_en(0);

	if (atomic_read(&hi->btn_state))
		button_released();
#else
	if (hi->btn_11pin_35mm_flag) {
		set_irq_wake(hi->irq_btn, 0);
		local_irq_save(irq_flags);
		disable_irq(hi->irq_btn);
		local_irq_restore(irq_flags);
		// imsi turn_mic_bias_on(0);
		//pmic_mic_en(0);
		hi->btn_11pin_35mm_flag = 0;
		if (atomic_read(&hi->btn_state))
			button_released();
	}
#endif

	res = 0;
	data1 = SMEM_PROC_COMM_MICBIAS_CONTROL_OFF;
	data2 = 0;

	res = msm_proc_comm(SMEM_PROC_COMM_MICBIAS_ONOFF, &data1, &data2);
	if(res < 0)
	{
		printk(KERN_ERR "[H2W] %s :%d fail %d\n", __func__, data1, res);
	}

	hi->debounce_time = ktime_set(0, 20000000);  /* 20 ms */
}
#else
static void remove_headset(void)

{
	unsigned long irq_flags;

	H2W_DBG("");

	switch_set_state(&hi->sdev, H2W_NO_DEVICE);
#if 0
	/* Disable button */
	local_irq_save(irq_flags);
	disable_irq(hi->irq_btn);
	local_irq_restore(irq_flags);
#endif
	if (atomic_read(&hi->btn_state))
		button_released();

	hi->debounce_time = ktime_set(0, 20000000);  /* 20 ms */
}

#endif

#ifdef FEATURE_SND_RPC 
static int mic_bias_on(void)
{
	int rc;
	struct msm_rpc_endpoint *ep = NULL;	
	uint32_t device = SND_DEVICE_HEADSET;
	uint32_t ear_mute = SND_MUTE_UNMUTED;
	uint32_t mic_mute = SND_MUTE_UNMUTED;
	struct rpc_snd_set_device_args {
		uint32_t device;
		uint32_t ear_mute;
		uint32_t mic_mute;
		uint32_t cb_func;
		uint32_t client_data;
	};
	struct snd_set_device_msg {
		struct rpc_request_hdr hdr;
		struct rpc_snd_set_device_args args;
	};
	struct snd_set_device_msg dmsg;

	struct rpc_snd_set_extamp_args {
		uint32_t device;
		uint32_t speaker_volume;
		uint32_t headset_volume;

		uint32_t cb_func;
		uint32_t client_data;
	};
	struct snd_set_extamp_msg {
		struct rpc_request_hdr hdr;
		struct rpc_snd_set_extamp_args args;
	};
	struct snd_set_extamp_msg emsg;
	  /* int data1 = 0; 
	 * int data2 = 0;	 */

	ep = msm_rpc_connect_compatible(SND_RPC_PROG, SND_RPC_VERS, 0);
	if(ep == NULL)
	{
		printk("snd_rpc_prog endpoint is NULL\n");
		return -ENODEV;
	}
	else if (IS_ERR(ep))
	{
		rc = PTR_ERR(ep);
		printk("%s: rpc connect failed for SND_RPC_PROG. rc = %d\n", __func__, rc);
		ep = NULL;
		return rc;
	}

	emsg.args.device = cpu_to_be32(device);
	emsg.args.speaker_volume = cpu_to_be32(ear_mute);
	emsg.args.headset_volume = cpu_to_be32(mic_mute);
	emsg.args.cb_func = -1;
	emsg.args.client_data = 0;
	rc = msm_rpc_call(ep, SND_SET_EXTAMP_PROC, &emsg, sizeof(emsg), 5 * HZ);
	if (rc < 0) {
		printk(KERN_ERR
				"%s: msm_rpc_call_reply failed! proc = %d rc = %d\n",
				__func__, SND_SET_DEVICE_PROC, rc);
		return rc;
	}

	msleep(10);
	
	H2W_DBG("%d %d %d", device, ear_mute, mic_mute);
	dmsg.args.device = cpu_to_be32(device);
	dmsg.args.ear_mute = cpu_to_be32(ear_mute);
	dmsg.args.mic_mute = cpu_to_be32(mic_mute);
	dmsg.args.cb_func = -1;
	dmsg.args.client_data = 0;
	rc = msm_rpc_call(ep, SND_SET_DEVICE_PROC, &dmsg, sizeof(dmsg), 5 * HZ);
	if (rc < 0) {
		printk(KERN_ERR
				"%s: msm_rpc_call_reply failed! proc = %d rc = %d\n",
				__func__, SND_SET_DEVICE_PROC, rc);
		return rc;
	}

	msleep(10);
	
	ear_mute = SND_MUTE_MUTED;
	mic_mute = SND_MUTE_MUTED;
	H2W_DBG("%d %d %d", device, ear_mute, mic_mute);
	dmsg.args.ear_mute = cpu_to_be32(ear_mute);
	dmsg.args.mic_mute = cpu_to_be32(mic_mute);
	rc = msm_rpc_call(ep, SND_SET_DEVICE_PROC, &dmsg, sizeof(dmsg), 5 * HZ);
	if (rc < 0) {
		printk(KERN_ERR
				"%s: msm_rpc_call_reply failed! proc = %d rc = %d\n",
				__func__, SND_SET_DEVICE_PROC, rc);
		return rc;
	}
	return 0;
}
static int mic_bias_on_forcely(void)
{
	int rc;
	struct msm_rpc_endpoint *ep = NULL;	
	struct rpc_snd_set_device_args {
		uint32_t device;
		uint32_t ear_mute;
		uint32_t mic_mute;
		uint32_t cb_func;
		uint32_t client_data;
	};
	struct snd_set_device_msg {
		struct rpc_request_hdr hdr;
		struct rpc_snd_set_device_args args;
	};
	struct snd_set_device_msg dmsg;

	struct rpc_snd_set_extamp_args {
		uint32_t device;
		uint32_t speaker_volume;
		uint32_t headset_volume;

		uint32_t cb_func;
		uint32_t client_data;
	};
	struct snd_set_extamp_msg {
		struct rpc_request_hdr hdr;
		struct rpc_snd_set_extamp_args args;
	};
	struct snd_set_extamp_msg emsg;
	  /* int data1 = 0; 
	 * int data2 = 0;	 */
	uint32_t device = SND_DEVICE_FORCE_SPEAKER;
	uint32_t ear_mute = SND_MUTE_UNMUTED;
	uint32_t mic_mute = SND_MUTE_UNMUTED;

	ep = msm_rpc_connect_compatible(SND_RPC_PROG, SND_RPC_VERS, 0);
	if(ep == NULL)
	{
		printk("snd_rpc_prog endpoint is NULL\n");
		return -ENODEV;
	}
	else if (IS_ERR(ep))
	{
		rc = PTR_ERR(ep);
		printk("%s: rpc connect failed for SND_RPC_PROG. rc = %d\n", __func__, rc);
		ep = NULL;
		return rc;
	}

	emsg.args.device = cpu_to_be32(device);
	emsg.args.speaker_volume = cpu_to_be32(ear_mute);
	emsg.args.headset_volume = cpu_to_be32(mic_mute);
	emsg.args.cb_func = -1;
	emsg.args.client_data = 0;
	/* rc = msm_rpc_call(ep, SND_SET_EXTAMP_PROC, &emsg, sizeof(emsg), 5 * HZ);
	 * if (rc < 0) {
		 * printk(KERN_ERR
				 * "%s: msm_rpc_call_reply failed! proc = %d rc = %d\n",
				 * __func__, SND_SET_DEVICE_PROC, rc);
		 * return rc;
	 * }

	 * msleep(10); */
	
	H2W_DBG("suspend_count = %d", suspend_count);
	//H2W_DBG("%d %d %d", device, ear_mute, mic_mute);
	dmsg.args.device = cpu_to_be32(device);
	dmsg.args.ear_mute = cpu_to_be32(ear_mute);
	dmsg.args.mic_mute = cpu_to_be32(mic_mute);
	dmsg.args.cb_func = -1;
	dmsg.args.client_data = 0;
	rc = msm_rpc_call(ep, SND_SET_DEVICE_PROC, &dmsg, sizeof(dmsg), 5 * HZ);
	if (rc < 0) {
		printk(KERN_ERR
				"%s: msm_rpc_call_reply failed! proc = %d rc = %d\n",
				__func__, SND_SET_DEVICE_PROC, rc);
		return rc;
	}

	msleep(10);
	
	/* ear_mute = SND_MUTE_MUTED;
	 * mic_mute = SND_MUTE_MUTED;
	 * H2W_DBG("%d %d %d", device, ear_mute, mic_mute);
	 * dmsg.args.ear_mute = cpu_to_be32(ear_mute);
	 * dmsg.args.mic_mute = cpu_to_be32(mic_mute);
	 * rc = msm_rpc_call(ep, SND_SET_DEVICE_PROC, &dmsg, sizeof(dmsg), 5 * HZ);
	 * if (rc < 0) {
		 * printk(KERN_ERR
				 * "%s: msm_rpc_call_reply failed! proc = %d rc = %d\n",
				 * __func__, SND_SET_DEVICE_PROC, rc);
		 * return rc;
	 * } */
	return 0;
}
#endif


#ifdef FEATURE_SENDEND_ENABLE
static void insert_headset(void)
{
	unsigned long irq_flags;
	int state;

	int res;
	int data1;
	int data2;
					
	//int mic_test;
#ifdef FEATURE_3PI_ADC
	int adc_3pi = 0;
#endif

	wake_lock_timeout(&headset_delayed_work_wake_lock, 5*HZ);
	if(!on_call)
	{
		if(suspend_count)
		{
			mic_bias_on_forcely();
		}
		else if((!suspend_state)&&(resume_state))
		{
			mic_bias_on_forcely();
		}
	}
#if 0
	/* set 4 pole headset */	
	state = BIT_HEADSET;
	printk("[H2W] 1) switch_set_state : %d\n", state);
	mutex_lock(&hi->mutex_lock);
	switch_set_state(&hi->sdev, state);
	mutex_unlock(&hi->mutex_lock);

	//state = BIT_HEADSET | BIT_HEADSET_NO_MIC;

	state = switch_get_state(&hi->sdev);
#else
	res = 0;
	data1 = SMEM_PROC_COMM_MICBIAS_CONTROL_ON;
	data2 = 0;

	res = msm_proc_comm(SMEM_PROC_COMM_MICBIAS_ONOFF, &data1, &data2);
	if(res < 0)
	{
		printk(KERN_ERR "[H2W] %s :%d fail %d\n", __func__, data1, res);
	}
#endif
	state &= ~(BIT_HEADSET_NO_MIC | BIT_HEADSET);

	//if (hi->headset_mic_35mm) {
	/* support 3.5mm earphone with mic */
	//printk(KERN_INFO "11pin_3.5mm_headset plug in\n");
	/* Turn On Mic Bias */
	// imsi turn_mic_bias_on(1);
	//pmic_mic_en(1);
	/* mic_test = pmic_mic_set_volt(MIC_VOLT_2_00V);
	 * if(0 > mic_test)
		 * {
			 * printk("%s : mic_set_volt return error(%d)\n\n", __func__, mic_test);
		 * } */
		/* Wait pin be stable */
		msleep(300);
		/* Detect headset with or without microphone */
#if 0
		if (!gpio_get_value(GPIO_SEND_END)) { // active low
			/* without microphone */
			// imsi turn_mic_bias_on(0);
			mic_en(0);
			state |= BIT_HEADSET_NO_MIC;
			printk(KERN_INFO
			       "11pin_3.5mm without microphone\n");
		} else { /* with microphone */
#endif
#ifdef FEATURE_3PI_ADC
	adc_3pi = get_3pi_adc();
	printk("+++++ get_3pi_adc = %d +++++++\n", adc_3pi);
	if(adc_3pi >= 0 && adc_3pi <= 3)
	{
		printk("[h2w] 1) 11pin_3.5mm without microphone\n");
		msleep(200);
		// recheck 3pi_adc
		adc_3pi = get_3pi_adc();
		printk("+++++ get_3pi_adc = %d +++++++\n", adc_3pi);
		if(adc_3pi >= 0 && adc_3pi <= 3)
		{
			state |= BIT_HEADSET_NO_MIC;
			printk("[h2w] 2) 11pin_3.5mm without microphone\n");
		}
		else
		{
			state |= BIT_HEADSET;
			/* Enable button irq */
			if (!hi->btn_11pin_35mm_flag) {
				set_irq_type(hi->irq_btn,IRQF_TRIGGER_LOW);		// detect high

				set_irq_wake(hi->irq_btn, 1);

				local_irq_save(irq_flags);
				enable_irq(hi->irq_btn);
				local_irq_restore(irq_flags);

				hi->btn_11pin_35mm_flag = 1;
			}
			printk("[h2w] 2) 11pin_3.5mm with microphone\n");
		}	
	}
	else
	{
		state |= BIT_HEADSET;
		/* Enable button irq */
		if (!hi->btn_11pin_35mm_flag) {
			set_irq_type(hi->irq_btn,IRQF_TRIGGER_LOW);		// detect high

			set_irq_wake(hi->irq_btn, 1);

			local_irq_save(irq_flags);
			enable_irq(hi->irq_btn);
			local_irq_restore(irq_flags);

			hi->btn_11pin_35mm_flag = 1;
		}
		printk("[h2w] 1) 11pin_3.5mm with microphone\n");
	}
#else
			state |= BIT_HEADSET;
			/* Enable button irq */
			if (!hi->btn_11pin_35mm_flag) {
				set_irq_type(hi->irq_btn,IRQF_TRIGGER_LOW);		// detect high

				set_irq_wake(hi->irq_btn, 1);

				local_irq_save(irq_flags);
				enable_irq(hi->irq_btn);
				local_irq_restore(irq_flags);

				hi->btn_11pin_35mm_flag = 1;
			}
			printk(KERN_INFO
			       "11pin_3.5mm with microphone\n");
#endif
//		}
	//} else /* not support 3.5mm earphone with mic */
	//	state |= BIT_HEADSET_NO_MIC;
	hi->debounce_time = ktime_set(0, 20000000);  /* 500 -> 20 ms */

	/* in case 3 pole headset */
	if (!hi->btn_11pin_35mm_flag) { 
		printk("[H2W] 2) switch_set_state : %d\n", state);
		mutex_lock(&hi->mutex_lock);
		switch_set_state(&hi->sdev, state);
		mutex_unlock(&hi->mutex_lock);
	}
	else {
		/* set 4 pole headset */	
		state = BIT_HEADSET;
		printk("[H2W] 1) switch_set_state : %d\n", state);
		mutex_lock(&hi->mutex_lock);
		switch_set_state(&hi->sdev, state);
		mutex_unlock(&hi->mutex_lock);		
	}

	/* On some non-standard headset adapters (usually those without a
	 * button) the btn line is pulled down at the same time as the detect
	 * line. We can check here by sampling the button line, if it is
	 * low then it is probably a bad adapter so ignore the button.
	 * If the button is released then we stop ignoring the button, so that
	 * the user can recover from the situation where a headset is plugged
	 * in with button held down.
	 */
//#ifdef FEATURE_SENDEND_ENABLE
//	hi->ignore_btn = !gpio_get_value(GPIO_SEND_END );
//#else
//        hi->ignore_btn = 1;
//#endif

//#ifdef FEATURE_SENDEND_ENABLE
//	/* Enable button irq */
//	local_irq_save(irq_flags);
//	enable_irq(hi->irq_btn);
//	local_irq_restore(irq_flags);
//#endif
//	hi->debounce_time = ktime_set(0, 20000000);  /* 20 ms */
}
#else
static void insert_headset(void)
{
    unsigned long irq_flags;

    H2W_DBG("");

    switch_set_state(&hi->sdev, H2W_SEC_HEADSET);

    /* On some non-standard headset adapters (usually those without a
     * button) the btn line is pulled down at the same time as the detect
     * line. We can check here by sampling the button line, if it is
     * low then it is probably a bad adapter so ignore the button.
     * If the button is released then we stop ignoring the button, so that
     * the user can recover from the situation where a headset is plugged
     * in with button held down.
     */
    hi->ignore_btn = 1; // !gpio_get_value(BIGFOOT_GPIO_CABLE_IN2);
#if 0
    /* Enable button irq */
    local_irq_save(irq_flags);
    enable_irq(hi->irq_btn);
    local_irq_restore(irq_flags);
#endif
    hi->debounce_time = ktime_set(0, 20000000);  /* 20 ms */
}


#endif

#ifdef FEATURE_SENDEND_ENABLE
static int is_accessary_pluged_in(void)
{
	int type = 0;
	int jack_state = 0;
	int sendend_state = 0;
	/* int mic_test = 0;

	 * mic_test = pmic_mic_set_volt(MIC_VOLT_2_00V);
	 * if(0 > mic_test)
	 * {
		 * printk("%s : mic_set_volt return error(%d)\n\n", __func__, mic_test);
	 * }
	 * pmic_mic_en(1); */
	/* Step 1: set both GPIO_CABLE_IN1 and GPIO_CABLE_IN2 as input */
	jack_state = gpio_get_value(GPIO_JACK_S_35);
	sendend_state = gpio_get_value(GPIO_SEND_END);

	printk("[H2W] jack_state = %d, sendend_state = %d\n",jack_state,sendend_state);

#if 0
	if ((jack_state == 1) && (sendend_state == 1) )
	{
		type = H2W_SEC_HEADSET;
	}
	else if ((jack_state == 1) && (sendend_state == 0))
	{
		type = H2W_NORMAL_HEADSET;
	}
#else
#ifdef JACK_ACTIVE_LOW
	if ((jack_state == 0))
#else
	if ((jack_state == 1))
#endif		
	{
		type = H2W_SEC_HEADSET;
	}
#endif
#ifdef JACK_ACTIVE_LOW
	else if ( jack_state == 1 )
#else
	else if ( jack_state == 0 )
#endif		
	{
		type = H2W_NO_DEVICE;
	}
	// khsuh_imsi mic_en(0);
	//pmic_mic_en(0);

	return type;
}
#endif

void headset_button_event(int is_press)
{
	if (!is_press) 	//release
	{
		if (hi->ignore_btn)
			hi->ignore_btn = 0;
		else if (atomic_read(&hi->btn_state))
			button_released();
	} 
	else 			//press
	{
		if (!hi->ignore_btn && !atomic_read(&hi->btn_state))
			button_pressed();
	}
}

static void earbutton_func_work(struct work_struct *work)
{
	int headset_state;
	int count = 8;
	
  	headset_state = gpio_get_value(GPIO_JACK_S_35);

	while(count-- && !earbutton_pressed)
	{
#ifdef JACK_ACTIVE_LOW	
		if(hi->button_state != (gpio_get_value(GPIO_SEND_END)) || headset_state)
#else
		if(hi->button_state != (gpio_get_value(GPIO_SEND_END)) || !headset_state)
#endif			
		{
			H2W_DBG("SEND_END key is ignored. State is unstable.");
			return;
		}
		msleep(5);
	}

	//H2W_DBG("count = %d button_state is %s", count+1, hi->button_state?"pressed":"released");
	if (hi->button_state) {
		headset_button_event(1);
	} else {
		headset_button_event(0);
	}
}

#if 1	// for DFMS test
static void earbutton_work(struct work_struct *work)
{
	mutex_lock(&hi->mutex_lock);
	switch_set_state(&hi->button_sdev, earbutton_pressed);
	mutex_unlock(&hi->mutex_lock);
}
#endif

static void detection_work(struct work_struct *work)
{
	unsigned long irq_flags;
	int jack_state;
	int type;

	H2W_DBG("");
#ifdef JACK_ACTIVE_LOW
	if (gpio_get_value(GPIO_JACK_S_35) != 0) 
#else
	if (gpio_get_value(GPIO_JACK_S_35) != 1)
#endif        
	{
		/* Headset not plugged in */
		if (switch_get_state(&hi->sdev) != H2W_NO_DEVICE)
			remove_headset();
		return;
	}

	/* Something plugged in, lets make sure its a headset */

	/* Disable headset interrupt while detecting.*/
	local_irq_save(irq_flags);
	disable_irq(hi->irq);
	local_irq_restore(irq_flags);
#ifdef FEATURE_SENDEND_ENABLE
	/* Something plugged in, lets make sure its a headset */
	type = is_accessary_pluged_in();
#endif

	/* Restore IRQs */
	local_irq_save(irq_flags);
	enable_irq(hi->irq);
	local_irq_restore(irq_flags);

	jack_state = gpio_get_value(GPIO_JACK_S_35);
//	msleep(1);
#ifdef JACK_ACTIVE_LOW
    if ( gpio_get_value(GPIO_JACK_S_35) == 0 )
#else
	if ( gpio_get_value(GPIO_JACK_S_35) == 1 )
#endif
	{
		if (switch_get_state(&hi->sdev) == H2W_NO_DEVICE)
		{
			insert_headset();
		}
		else
		{
			printk("GPIO_JACK_S_35 = 1, but not insert_headset\n\n");
		}
	} 
	else {
		printk("JACK_S_35 was low, but not a headset "
				"(recent jack_state = %d)", jack_state);
	}
}

#if 0
static enum hrtimer_restart button_event_timer_func(struct hrtimer *data)
{
	H2W_DBG("");
#ifdef FEATURE_SENDEND_ENABLE
	// check again
	if(hi->button_state != gpio_get_value(GPIO_SEND_END))
	{
		printk("ERROR - button value : %d -> %d\n", hi->button_state, gpio_get_value(GPIO_SEND_END));
		return HRTIMER_NORESTART;
	}

    // butten active high	
        if (gpio_get_value(GPIO_SEND_END)) {
		headset_button_event(1);
		/* 10 ms */
		//hi->btn_debounce_time = ktime_set(0, 10000000);
	} else {
		headset_button_event(0);
		/* 100 ms */
		//hi->btn_debounce_time = on_call ? ktime_set(0, 400000000):ktime_set(0, BTN_PRESS_DEBOUNCE_TIME);
	}
//	printk("%s - SEND_END=%d.\n", __func__, gpio_get_value(GPIO_SEND_END));
#else
	if (switch_get_state(&hi->sdev) == H2W_SEC_HEADSET) {
		if (0){ // gpio_get_value(GPIO_SEND_END )) {
			if (hi->ignore_btn)
				hi->ignore_btn = 0;
			else if (atomic_read(&hi->btn_state))
				button_released();
		} else {
			if (!hi->ignore_btn && !atomic_read(&hi->btn_state))
				button_pressed();
		}
	}
#endif
	return HRTIMER_NORESTART;
}
#endif

static enum hrtimer_restart detect_event_timer_func(struct hrtimer *data)
{
	H2W_DBG("");

	queue_work(g_detection_work_queue, &g_detection_work);
	return HRTIMER_NORESTART;
}

static irqreturn_t detect_irq_handler(int irq, void *dev_id)
{
	int value1, value2;
	int retry_limit = 10;

	set_irq_type(hi->irq_btn, IRQF_TRIGGER_HIGH);		// detect high

	H2W_DBG("");
	do {
		value1 = gpio_get_value(GPIO_JACK_S_35);
		set_irq_type(hi->irq, value1 ?
				IRQF_TRIGGER_FALLING : IRQF_TRIGGER_RISING);
		value2 = gpio_get_value(GPIO_JACK_S_35);
	} while (value1 != value2 && retry_limit-- > 0);

//	printk("headset value2 = %d (%d retries)\n", value2, (10-retry_limit));

#ifdef JACK_ACTIVE_LOW
//	if ((switch_get_state(&hi->sdev) == H2W_NO_DEVICE) ^ value2) 
#else
//	if ((switch_get_state(&hi->sdev) == H2W_NO_DEVICE) ^ !value2)
#endif	
	{ 
		hi->headset_state = value1;
		H2W_DBG("GPIO_JACK_S_35 is %s",value1?"HIGH":"LOW");
		if (switch_get_state(&hi->sdev) != H2W_NO_DEVICE)
			hi->ignore_btn = 1;
		/* Do the rest of the work in timer context */
		hrtimer_start(&hi->timer, hi->debounce_time, HRTIMER_MODE_REL);
	}

	return IRQ_HANDLED;
}

static irqreturn_t button_irq_handler(int irq, void *dev_id)
{
	int adc = 0;
	int value1, value2;
	int retry_limit = 10;
	int headset_state; 

	adc = get_3pi_adc();
	H2W_DBG("#### irq  adc = [%d] ", adc);

//	H2W_DBG("");
	do {
#ifdef FEATURE_SENDEND_ENABLE
		value1 = gpio_get_value(GPIO_SEND_END );
		set_irq_type(hi->irq_btn, value1 ?
				IRQF_TRIGGER_LOW : IRQF_TRIGGER_HIGH);
		value2 = gpio_get_value(GPIO_SEND_END );
#else
		value1 = 0;
		set_irq_type(hi->irq_btn, value1 ?
				IRQF_TRIGGER_LOW : IRQF_TRIGGER_HIGH);
		value2 = 0;
#endif
	} while (value1 != value2 && retry_limit-- > 0);

	headset_state = gpio_get_value(GPIO_JACK_S_35);

#ifdef JACK_ACTIVE_LOW	
	if(headset_state)
#else
	if(!headset_state)
#endif
	{
		H2W_DBG("ignored cuz headset was removed");
		return IRQ_HANDLED;
	}

	/* if (!gpio_get_value(GPIO_SEND_END)) 
	 * {
		 * hi->btn_debounce_time = ktime_set(0, 10000000);
	 * } 
	 * else 
	 * {
		 * //H2W_DBG("on_call = %d",on_call);
		 * hi->btn_debounce_time = on_call ? ktime_set(0, 600000000):ktime_set(0, BTN_PRESS_DEBOUNCE_TIME);
	 * } */

	if(value1 == value2 && retry_limit > 0)
	{
		hi->button_state = value1;
		if(value1 == 1)
		{
			checking_adc = adc;
			H2W_DBG(" SUCCESS !\n");
		}
		else
		{
			H2W_DBG(" FAIL !\n");
		}
		H2W_DBG("GPIO_SEND_END is %s (%d retries)", hi->button_state?"HIGH":"LOW", (10 - retry_limit));
		//hrtimer_start(&hi->btn_timer, hi->btn_debounce_time, HRTIMER_MODE_REL);
		schedule_work(&g_earbutton_func_work);
	}

	return IRQ_HANDLED;
}

#if defined(CONFIG_DEBUG_FS)
static int h2w_debug_set(void *data, u64 val)
{
	mutex_lock(&hi->mutex_lock);
	switch_set_state(&hi->sdev, (int)val);
	mutex_unlock(&hi->mutex_lock);
	return 0;
}

static int h2w_debug_get(void *data, u64 *val)
{
	return 0;
}


DEFINE_SIMPLE_ATTRIBUTE(h2w_debug_fops, h2w_debug_get, h2w_debug_set, "%llu\n");
static int __init h2w_debug_init(void)
{
	struct dentry *dent;

	dent = debugfs_create_dir("h2w", 0);
	if (IS_ERR(dent))
		return PTR_ERR(dent);

	debugfs_create_file("state", 0644, dent, NULL, &h2w_debug_fops);

	return 0;
}

device_initcall(h2w_debug_init);
#endif

static int h2w_probe(struct platform_device *pdev)
{
	int ret;
	//unsigned long irq_flags;
   
	printk(KERN_INFO "[H2W] Registering H2W (headset) driver\n");
	hi = kzalloc(sizeof(struct h2w_info), GFP_KERNEL);
	if (!hi)
		return -ENOMEM;

	atomic_set(&hi->btn_state, 0);
	hi->ignore_btn = 0;
	hi->headset_state = 0;
	hi->button_state = 0;

	hi->debounce_time = ktime_set(0, 20000000);  /* 100 ms -> 20 ms */
	//hi->btn_debounce_time = ktime_set(0, 50000000); /* 50 ms */
        
	hi->btn_11pin_35mm_flag = 0;

	mutex_init(&hi->mutex_lock);

	hi->sdev.name = "h2w";
	hi->sdev.print_name = h2w_print_name;
	hi->sdev.set_state = h2w_set_state;

	ret = switch_dev_register(&hi->sdev);
	if (ret < 0)
		goto err_switch_dev_register;

#if 1	// for DFMS test
	hi->button_sdev.name = "sec_earbutton";
	hi->button_sdev.print_name = button_print_name;

	ret = switch_dev_register(&hi->button_sdev);
	if (ret < 0)
		goto err_switch_dev_register;
	switch_set_state(&hi->button_sdev, 0);
	
	g_earbutton_work_queue = create_workqueue("earbutton");
	if (g_earbutton_work_queue == NULL) {
		ret = -ENOMEM;
		goto err_create_work_queue;
	}
#endif

	g_detection_work_queue = create_workqueue("detection");
	if (g_detection_work_queue == NULL) {
		ret = -ENOMEM;
		goto err_create_work_queue;
	}

//    printk("%s:%d GPIO_SEND_END=%d.\n",__func__, __LINE__, GPIO_SEND_END);

/*****************************************************************/
// JACK_S_35 GPIO setting     
/*****************************************************************/    
	
	ret = gpio_request(GPIO_JACK_S_35, "h2w_detect");
	if (ret < 0)
		goto err_request_detect_gpio;

	ret = gpio_direction_input(GPIO_JACK_S_35);
	if (ret < 0)
		goto err_set_detect_gpio;

	hi->irq = gpio_to_irq(GPIO_JACK_S_35);
	if (hi->irq < 0) {
		ret = hi->irq;
		goto err_get_h2w_detect_irq_num_failed;
	}

	hrtimer_init(&hi->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hi->timer.function = detect_event_timer_func;

/*****************************************************************/
// SEND_END GPIO setting     
/*****************************************************************/

	ret = gpio_request(GPIO_SEND_END , "h2w_button");
	if (ret < 0)
		goto err_request_button_gpio;

	ret = gpio_direction_input(GPIO_SEND_END );
	if (ret < 0)
		goto err_set_button_gpio;

	hi->irq_btn = gpio_to_irq(GPIO_SEND_END );
	if (hi->irq_btn < 0) {
		ret = hi->irq_btn;
		goto err_get_button_irq_num_failed;
	}

	/* hrtimer_init(&hi->btn_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	 * hi->btn_timer.function = button_event_timer_func; */



/*****************************************************************/
// JACK_S_35 irq setting     
/*****************************************************************/       
//	local_irq_save(irq_flags);
//    printk("%s:%d JACK_value=%d.\n",__func__, __LINE__, gpio_get_value(GPIO_JACK_S_35));

#ifdef JACK_ACTIVE_LOW
	ret = request_irq(hi->irq, detect_irq_handler,
			  IRQF_TRIGGER_FALLING, "h2w_detect", NULL);
#else
	ret = request_irq(hi->irq, detect_irq_handler,
			  IRQF_TRIGGER_RISING, "h2w_detect", NULL);
#endif        
	if (ret < 0)
		goto err_request_detect_irq;

      hi->use_irq = ret == 0;

     printk(KERN_INFO "Headset Driver: Start gpio inputs for %s in %s mode\n", hi->sdev.name, hi->use_irq ? "interrupt" : "polling");

	ret = set_irq_wake(hi->irq, 1);
	if (ret < 0)
		goto err_request_input_dev;

//	local_irq_restore(irq_flags);


/*****************************************************************/
// SEND_END irq setting     
/*****************************************************************/

//    local_irq_save(irq_flags);
    /* Disable button until plugged in */
    set_irq_flags(hi->irq_btn, IRQF_VALID | IRQF_NOAUTOEN);
    ret = request_irq(hi->irq_btn, button_irq_handler,
              IRQF_TRIGGER_HIGH, "h2w_button", NULL);       // detect high
    if (ret < 0)
        goto err_request_button_irq;

 //   local_irq_restore(irq_flags);

	hi->input = input_allocate_device();
	if (!hi->input) {
		ret = -ENOMEM;
		goto err_request_input_dev;
	}
#if defined(CONFIG_MACH_CALLISTO)
	hi->input->name = "callisto_headset";
#elif defined(CONFIG_MACH_COOPER)
	hi->input->name = "cooper_headset";	
#elif defined(CONFIG_MACH_BENI)
	hi->input->name = "beni_headset";	
#elif defined(CONFIG_MACH_TASS)
	hi->input->name = "tass_headset";		
#elif defined(CONFIG_MACH_LUCAS)
	hi->input->name = "lucas_headset";	
#elif defined(CONFIG_MACH_EUROPA)
	hi->input->name = "europa_headset";	
#endif
	set_bit(EV_KEY, hi->input->evbit);
	set_bit(KEY_MEDIA, hi->input->keybit);

	ret = input_register_device(hi->input);
	if (ret < 0)
		goto err_register_input_dev;

#ifdef FEATURE_SND_RPC 
	if(flag_boot)
	{
		mic_bias_on();
		flag_boot = 0;
	}
#endif

	return 0;

err_register_input_dev:
	input_free_device(hi->input);
err_request_input_dev:
#ifdef FEATURE_SENDEND_ENABLE
	free_irq(hi->irq, 0);
#endif
	free_irq(hi->irq_btn, 0);
err_get_button_irq_num_failed:
err_get_h2w_detect_irq_num_failed:
err_set_button_gpio:
err_set_detect_gpio:
err_request_detect_irq:    
       gpio_free(GPIO_JACK_S_35);
err_request_button_gpio:
err_request_button_irq: 
#if 1 // def FEATURE_SENDEND_ENABLE
	gpio_free(GPIO_SEND_END );
#endif
err_request_detect_gpio:
	destroy_workqueue(g_detection_work_queue);
	destroy_workqueue(g_earbutton_work_queue);
err_create_work_queue:
	switch_dev_unregister(&hi->sdev);
err_switch_dev_register:
	printk(KERN_ERR "H2W: Failed to register driver\n");

	return ret;
}

static int h2w_remove(struct platform_device *pdev)
{
	H2W_DBG("");
	if (switch_get_state(&hi->sdev))
		remove_headset();
	input_unregister_device(hi->input);
#ifdef FEATURE_SENDEND_ENABLE
	gpio_free(GPIO_SEND_END );
#endif
	gpio_free(GPIO_JACK_S_35);
#ifdef FEATURE_SENDEND_ENABLE    
	free_irq(hi->irq_btn, 0);
#endif
	free_irq(hi->irq, 0);
	destroy_workqueue(g_detection_work_queue);
	destroy_workqueue(g_earbutton_work_queue);
	switch_dev_unregister(&hi->sdev);

	return 0;
}


static struct platform_device h2w_device = {
#if defined(CONFIG_MACH_CALLISTO)
	.name		= "callisto-headset",
#elif defined(CONFIG_MACH_COOPER)
	.name		= "cooper-headset",
#elif defined(CONFIG_MACH_BENI)
	.name		= "beni-headset",
#elif defined(CONFIG_MACH_TASS)
	.name		= "tass-headset",
#elif defined(CONFIG_MACH_LUCAS)
	.name		= "lucas-headset",	
#elif defined(CONFIG_MACH_EUROPA)
	.name		= "europa-headset",
#endif
};


static struct platform_driver h2w_driver = {
	.probe		= h2w_probe,
	.remove		= h2w_remove,
	.suspend 	= h2w_suspend,
	.resume		= h2w_resume,
	.driver		= {
#if defined(CONFIG_MACH_CALLISTO)
		.name		= "callisto-headset",
#elif defined(CONFIG_MACH_COOPER)
		.name		= "cooper-headset",
#elif defined(CONFIG_MACH_BENI)
		.name		= "beni-headset",
#elif defined(CONFIG_MACH_TASS)
		.name		= "tass-headset",
#elif defined(CONFIG_MACH_LUCAS)
		.name		= "lucas-headset",				
#elif defined(CONFIG_MACH_EUROPA)
		.name		= "europa-headset",
#endif
		.owner		= THIS_MODULE,
	},
};

 int __init h2w_init(void)
{
	int ret;
	H2W_DBG("JACK_S_35(%d), SEND_END(%d)", GPIO_JACK_S_35, GPIO_SEND_END);
	wake_lock_init(&headset_delayed_work_wake_lock, WAKE_LOCK_SUSPEND, "headset_delayed_work");
	ret = platform_driver_register(&h2w_driver);
	if (ret)
		return ret;
	return platform_device_register(&h2w_device);
}

static void __exit h2w_exit(void)
{
	wake_lock_destroy(&headset_delayed_work_wake_lock);
	platform_device_unregister(&h2w_device);

	platform_driver_unregister(&h2w_driver);
}

module_init(h2w_init);
module_exit(h2w_exit);

MODULE_AUTHOR("anonymous <anonymous@samsung.com>");
MODULE_DESCRIPTION("SAMSUNG Headset driver");
MODULE_LICENSE("GPL");
