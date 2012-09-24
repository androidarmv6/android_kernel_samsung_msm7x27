/* drivers/input/misc/gpio_matrix.c
 *
 * Copyright (C) 2007 Google, Inc.
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

#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/gpio_event.h>
#include <linux/hrtimer.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/wakelock.h>
#include <mach/gpio.h>
#include <linux/irq.h>	//hsil

#include <linux/module.h>

//#define AUTO_POWER_ON_OFF_FLAG 1

#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_GIO)
unsigned int Volume_Up_irq = 0;
unsigned int Volume_Down_irq = 0;
#endif

extern int board_hw_revision;
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_GIO)
extern void TSP_forced_release_forkey(void);
#endif

// for COOPER
#define GPIO_POWERKEY 83

#ifdef CONFIG_MACH_LUCAS
#define GPIO_KBR6 3	 
#endif

#if defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
#define GPIO_KBC0 35
#endif

#if defined(CONFIG_MACH_CALLISTO)
// hsil
#define GPIO_SLIDE	36
#define GPIO_KBR5	37
#define GPIO_KBR6	27
#define GPIO_VOL_UP	76
#endif

#if AUTO_POWER_ON_OFF_FLAG
static struct timer_list poweroff_keypad_timer;
#endif

#if defined(CONFIG_MACH_EUROPA)
int wlan_debug_step;
EXPORT_SYMBOL(wlan_debug_step);
#endif

#if defined(CONFIG_MACH_EUROPA) || defined(CONFIG_MACH_CALLISTO) || defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS)
int key_pressed;
extern int power_off_done;
extern int lcd_on_state_for_debug;
#ifdef ATH_CLAIM_RELEASE_WAR
extern void ath_debug_sdio_claimer(void);
#endif
#endif

#if defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_CALLISTO)
int alt_key_pressed = 0;
#endif

#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_GIO)
#if defined(CONFIG_KERNEL_SEC_MMICHECK)
int mmi_keycode[] = {
			KEY_BACK, KEY_HOME, KEY_MENU, KEY_POWER, KEY_VOLUMEUP, KEY_VOLUMEDOWN,
			KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_A,
			KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_M, KEY_Z, KEY_X,
			KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_OK, KEY_BACKSPACE, KEY_COMMA, KEY_LEFTSHIFT, 214,
			KEY_ENTER, KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_LEFTALT, 223, KEY_MAIL, KEY_SEARCH,
			KEY_COMMA, KEY_SPACE, 231, 228
	};
#endif
#endif

struct gpio_kp {
	struct gpio_event_input_devs *input_devs;
	struct gpio_event_matrix_info *keypad_info;
	struct hrtimer timer;
	struct wake_lock wake_lock;
	int current_output;
	unsigned int use_irq:1;
	unsigned int key_state_changed:1;
	unsigned int last_key_state_changed:1;
	unsigned int some_keys_pressed:2;
	unsigned int disabled_irq:1;
	unsigned long keys_pressed[0];
};

// hsil
int enter_suspend;
EXPORT_SYMBOL(enter_suspend);

#if AUTO_POWER_ON_OFF_FLAG
static void poweroff_keypad_timer_handler(unsigned long data)
{
	struct gpio_kp *kp = (struct gpio_kp *)data;
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	unsigned short keyentry = mi->keymap[0];
	unsigned short dev = keyentry >> MATRIX_CODE_BITS;

	printk("force to power off + \n");
	input_report_key(kp->input_devs->dev[dev], KEY_END, 1);
	printk("force to power off - \n");
}
#endif

static void clear_phantom_key(struct gpio_kp *kp, int out, int in)
{
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	int key_index = out * mi->ninputs + in;
	unsigned short keyentry = mi->keymap[key_index];
	unsigned short keycode = keyentry & MATRIX_KEY_MASK;
	unsigned short dev = keyentry >> MATRIX_CODE_BITS;

	if (!test_bit(keycode, kp->input_devs->dev[dev]->key)) {
		if (mi->flags & GPIOKPF_PRINT_PHANTOM_KEYS)
			pr_info("gpiomatrix: phantom key %x, %d-%d (%d-%d) "
				"cleared\n", keycode, out, in,
				mi->output_gpios[out], mi->input_gpios[in]);
		__clear_bit(key_index, kp->keys_pressed);
	} else {
		if (mi->flags & GPIOKPF_PRINT_PHANTOM_KEYS)
			pr_info("gpiomatrix: phantom key %x, %d-%d (%d-%d) "
				"not cleared\n", keycode, out, in,
				mi->output_gpios[out], mi->input_gpios[in]);
	}
}

static int restore_keys_for_input(struct gpio_kp *kp, int out, int in)
{
	int rv = 0;
	int key_index;

	key_index = out * kp->keypad_info->ninputs + in;
	while (out < kp->keypad_info->noutputs) {
		if (test_bit(key_index, kp->keys_pressed)) {
			rv = 1;
			clear_phantom_key(kp, out, in);
		}
		key_index += kp->keypad_info->ninputs;
		out++;
	}
	return rv;
}

static void remove_phantom_keys(struct gpio_kp *kp)
{
	int out, in, inp;
	int key_index;

	if (kp->some_keys_pressed < 3)
		return;

	for (out = 0; out < kp->keypad_info->noutputs; out++) {
		inp = -1;
		key_index = out * kp->keypad_info->ninputs;
		for (in = 0; in < kp->keypad_info->ninputs; in++, key_index++) {
			if (test_bit(key_index, kp->keys_pressed)) {
				if (inp == -1) {
					inp = in;
					continue;
				}
				if (inp >= 0) {
					if (!restore_keys_for_input(kp, out + 1,
									inp))
						break;
					clear_phantom_key(kp, out, inp);
					inp = -2;
				}
				restore_keys_for_input(kp, out, in);
			}
		}
	}
}
// hsil
int volup_cnt = 0;
static void report_key(struct gpio_kp *kp, int key_index, int out, int in)
{
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	int pressed = test_bit(key_index, kp->keys_pressed);
	unsigned short keyentry = mi->keymap[key_index];
	unsigned short keycode = keyentry & MATRIX_KEY_MASK;
	unsigned short dev = keyentry >> MATRIX_CODE_BITS;

	if (pressed != test_bit(keycode, kp->input_devs->dev[dev]->key)) {
		if (keycode == KEY_RESERVED) {
#ifdef CONFIG_KERNEL_DEBUG_SEC
#if defined(CONFIG_MACH_EUROPA)
			if ((mi->flags & GPIOKPF_PRINT_UNMAPPED_KEYS) && (board_hw_revision < 4))
#elif defined(CONFIG_MACH_CALLISTO)
			if ((mi->flags & GPIOKPF_PRINT_UNMAPPED_KEYS) && (board_hw_revision < 3))
#else
			if (mi->flags & GPIOKPF_PRINT_UNMAPPED_KEYS)
#endif			
				pr_info("gpiomatrix: unmapped key, %d-%d "
					"(%d-%d) changed to %d\n",
					out, in, mi->output_gpios[out],
					mi->input_gpios[in], pressed);
#endif			
		} else {
#ifdef CONFIG_KERNEL_DEBUG_SEC
			if (mi->flags & GPIOKPF_PRINT_MAPPED_KEYS)
				pr_info("gpiomatrix: key %x, %d-%d (%d-%d) "
					"changed to %d\n", keycode,
					out, in, mi->output_gpios[out],
					mi->input_gpios[in], pressed);
#endif			

#if defined(CONFIG_MACH_EUROPA) || defined(CONFIG_MACH_CALLISTO)  || defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_GIO)
			if(!power_off_done) {

#if defined(CONFIG_MACH_CALLISTO)
				if ((keycode == KEY_LEFTALT) && pressed)
					alt_key_pressed = 1;
				if ((keycode == KEY_LEFTALT) && !pressed)
					alt_key_pressed = 0;

				if ((alt_key_pressed) && (keycode == KEY_LEFT))
					printk("key (Alt + Down) pressed\n");
				else if ((alt_key_pressed) && (keycode == KEY_RIGHT))
					printk("key (Alt + Up) pressed\n");
				else
				{	
#endif
			input_report_key(kp->input_devs->dev[dev], keycode, pressed);
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_GIO)
				if(keycode == KEY_HOME && pressed == 1)
					TSP_forced_release_forkey();
#endif
#if defined(CONFIG_MACH_CALLISTO)  || defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_GIO)
//#ifdef CONFIG_KERNEL_DEBUG_SEC
//				printk("key event (keycode:%d, pressed:%d), w=%d\n", 
//						keycode, pressed, lcd_on_state_for_debug);	// sec: sm.kim
//#endif

#ifdef ATH_CLAIM_RELEASE_WAR
				if(!lcd_on_state_for_debug) 
				    ath_debug_sdio_claimer();
#endif
#else
				printk("key event (keycode:%d, pressed:%d), wlan_debug_step=%d\n", 
						keycode, pressed, wlan_debug_step);	// sec: sm.kim
#endif
#if defined(CONFIG_MACH_CALLISTO)
				}
#endif
				key_pressed = pressed;
			} else {
				printk("power_off_done : %d\n", power_off_done);
			}
#else
			input_report_key(kp->input_devs->dev[dev], keycode, pressed);
//			printk("key event (keycode:%d, pressed:%d), wlan_debug_step=%d\n", 
//					keycode, pressed, wlan_debug_step);	// sec: sm.kim
#ifdef CONFIG_KERNEL_DEBUG_SEC
			printk("key event (keycode:%d, pressed:%d)\n", keycode, pressed);	//sec: sm.kim
#endif
#endif
		}
	}
}

static enum hrtimer_restart gpio_keypad_timer_func(struct hrtimer *timer)
{
	int out, in;
	int pout;	// multikey
	int key_index;
	int gpio;
	struct gpio_kp *kp = container_of(timer, struct gpio_kp, timer);
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	unsigned gpio_keypad_flags = mi->flags;
	unsigned polarity = !!(gpio_keypad_flags & GPIOKPF_ACTIVE_HIGH);

	out = kp->current_output;
	if (out == mi->noutputs) {
		out = 0;
		kp->last_key_state_changed = kp->key_state_changed;
		kp->key_state_changed = 0;
		kp->some_keys_pressed = 0;
	} else {
		key_index = out * mi->ninputs;
		for (in = 0; in < mi->ninputs; in++, key_index++) {
			gpio = mi->input_gpios[in];
			if (gpio_get_value(gpio) ^ !polarity) {
				if (kp->some_keys_pressed < 3)
					kp->some_keys_pressed++;
				kp->key_state_changed |= !__test_and_set_bit(
						key_index, kp->keys_pressed);
			} else
				kp->key_state_changed |= __test_and_clear_bit(
						key_index, kp->keys_pressed);
		}
		gpio = mi->output_gpios[out];
		// multikey
		for( pout = 0; pout < mi->noutputs; pout++ )
		{
                       if( out != pout )
                               gpio_direction_output(mi->output_gpios[pout], !polarity);
		}

		if (gpio_keypad_flags & GPIOKPF_DRIVE_INACTIVE)
			gpio_set_value(gpio, !polarity);
		else
			gpio_direction_input(gpio);
		out++;
	}
	kp->current_output = out;
	if (out < mi->noutputs) {
		gpio = mi->output_gpios[out];
		// multikey
		for( pout = 0; pout < mi->noutputs; pout++ )
                       if( out != pout )
                               gpio_direction_input(mi->output_gpios[pout]);

			
		if (gpio_keypad_flags & GPIOKPF_DRIVE_INACTIVE)
			gpio_set_value(gpio, polarity);
		else
			gpio_direction_output(gpio, polarity);
		hrtimer_start(timer, mi->settle_time, HRTIMER_MODE_REL);
		return HRTIMER_NORESTART;
	}
	if (gpio_keypad_flags & GPIOKPF_DEBOUNCE) {
		if (kp->key_state_changed) {
			hrtimer_start(&kp->timer, mi->debounce_delay,
				      HRTIMER_MODE_REL);
			return HRTIMER_NORESTART;
		}
		kp->key_state_changed = kp->last_key_state_changed;
	}
	if (kp->key_state_changed) {
		if (gpio_keypad_flags & GPIOKPF_REMOVE_SOME_PHANTOM_KEYS)
			remove_phantom_keys(kp);
		key_index = 0;
		for (out = 0; out < mi->noutputs; out++)
			for (in = 0; in < mi->ninputs; in++, key_index++)
				report_key(kp, key_index, out, in);
	}
	if (!kp->use_irq || kp->some_keys_pressed) {
		hrtimer_start(timer, mi->poll_time, HRTIMER_MODE_REL);
		return HRTIMER_NORESTART;
	}

	/* No keys are pressed, reenable interrupt */
	for (out = 0; out < mi->noutputs; out++) {
		if (gpio_keypad_flags & GPIOKPF_DRIVE_INACTIVE)
			gpio_set_value(mi->output_gpios[out], polarity);
		else
			gpio_direction_output(mi->output_gpios[out], polarity);
	}
	for (in = 0; in < mi->ninputs; in++)
		enable_irq(gpio_to_irq(mi->input_gpios[in]));
	wake_unlock(&kp->wake_lock);
	return HRTIMER_NORESTART;
}


// for COOPER
static irqreturn_t gpiokey_irq_handler(int irq_in, void *dev_id)
{
	unsigned int key_status;
	struct gpio_kp *kp = dev_id;
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	unsigned short keyentry = mi->keymap[0];
	unsigned short dev = keyentry >> MATRIX_CODE_BITS;

	key_status = gpio_get_value(GPIO_POWERKEY);

	if(!power_off_done) {
		if(key_status == 0) // 0 : press
		{
			input_report_key(kp->input_devs->dev[dev], KEY_END, 1);
#ifdef CONFIG_KERNEL_DEBUG_SEC
//			printk("key event (keycode:%d, pressed:%d)\n", KEY_END, 1);	//sec: sm.kim
#endif			
			key_pressed = 1;
		}
		else if (key_status == 1) // 1 : release
		{
			input_report_key(kp->input_devs->dev[dev], KEY_END, 0);
#ifdef CONFIG_KERNEL_DEBUG_SEC
//			printk("key event (keycode:%d, pressed:%d)\n", KEY_END, 0); //sec: sm.kim
#endif
			key_pressed = 0;
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_GIO)
			TSP_forced_release_forkey();
#endif
		}
	}
	else
		printk("power_off_done : %d\n", power_off_done);

	return IRQ_HANDLED;

}

static irqreturn_t gpio_keypad_irq_handler(int irq_in, void *dev_id)
{
	int i;
	struct gpio_kp *kp = dev_id;
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	unsigned gpio_keypad_flags = mi->flags;

	if (!kp->use_irq) {
		/* ignore interrupt while registering the handler */
		kp->disabled_irq = 1;
		disable_irq_nosync(irq_in);
		return IRQ_HANDLED;
	}

	for (i = 0; i < mi->ninputs; i++)
		disable_irq_nosync(gpio_to_irq(mi->input_gpios[i]));
	for (i = 0; i < mi->noutputs; i++) {
		if (gpio_keypad_flags & GPIOKPF_DRIVE_INACTIVE)
			gpio_set_value(mi->output_gpios[i],
				!(gpio_keypad_flags & GPIOKPF_ACTIVE_HIGH));
		else
			gpio_direction_input(mi->output_gpios[i]);
	}
	wake_lock(&kp->wake_lock);
	hrtimer_start(&kp->timer, ktime_set(0, 0), HRTIMER_MODE_REL);
	return IRQ_HANDLED;
}

#if defined(CONFIG_MACH_CALLISTO)
// hsil
static irqreturn_t slide_int_handler(int irq, void *dev_id)
{
	struct gpio_kp *kp = dev_id;
	int state;
	struct gpio_event_matrix_info *mi = kp->keypad_info;
	unsigned short keyentry = mi->keymap[0];
	unsigned short dev = keyentry >> MATRIX_CODE_BITS;
			 
	state = gpio_get_value(GPIO_SLIDE) ^ 1;
//	printk("[SLIDE] changed Slide state (%d)\n", state);

	input_report_switch(kp->input_devs->dev[dev], SW_LID, state);
	input_sync(kp->input_devs->dev[dev]);
	
	return IRQ_HANDLED;
}
#endif

static int gpio_keypad_request_irqs(struct gpio_kp *kp)
{
	int i;
	int err;
	unsigned int irq;
	unsigned long request_flags;
	struct gpio_event_matrix_info *mi = kp->keypad_info;

	switch (mi->flags & (GPIOKPF_ACTIVE_HIGH|GPIOKPF_LEVEL_TRIGGERED_IRQ)) {
	default:
		request_flags = IRQF_TRIGGER_FALLING;
		break;
	case GPIOKPF_ACTIVE_HIGH:
		request_flags = IRQF_TRIGGER_RISING;
		break;
	case GPIOKPF_LEVEL_TRIGGERED_IRQ:
		request_flags = IRQF_TRIGGER_LOW;
		break;
	case GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_ACTIVE_HIGH:
		request_flags = IRQF_TRIGGER_HIGH;
		break;
	}

	for (i = 0; i < mi->ninputs; i++) {
		err = irq = gpio_to_irq(mi->input_gpios[i]);
		if (err < 0)
			goto err_gpio_get_irq_num_failed;

#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_GIO)
		switch(mi->input_gpios[i])
		{
			case 41:
				Volume_Up_irq = irq;
				break;
				
			case 42:
				Volume_Down_irq = irq;
				break;
		}
#endif		
#if defined(CONFIG_MACH_LUCAS)
		switch(mi->input_gpios[i])
		{
			case 3:
				Volume_Up_irq = irq;
				Volume_Down_irq = irq;
				break;
		}
#endif		
		err = request_irq(irq, gpio_keypad_irq_handler, request_flags,
				  "gpio_kp", kp);
		if (err) {
			pr_err("gpiomatrix: request_irq failed for input %d, "
				"irq %d\n", mi->input_gpios[i], irq);
			goto err_request_irq_failed;
		}
#if !defined(CONFIG_MACH_LUCAS) || !defined(CONFIG_MACH_CALLISTO)/*&& !defined(CONFIG_MACH_TASS) */
//#ifndef CONFIG_MACH_LUCAS
		err = set_irq_wake(irq, 1);
		if (err) {
			pr_err("gpiomatrix: set_irq_wake failed for input %d, "
				"irq %d\n", mi->input_gpios[i], irq);
		}
#endif		
		disable_irq(irq);
		if (kp->disabled_irq) {
			kp->disabled_irq = 0;
			enable_irq(irq);
		}
	}
/*
#if defined(CONFIG_MACH_TASS) 
	err = set_irq_wake(gpio_to_irq(GPIO_KBC0), 1);
	if (err) 
	{
		pr_err("gpiomatrix: set_irq_wake failed for input %d, "	"irq %d\n", GPIO_KBC0, irq);
	}
#endif
*/
#if defined (CONFIG_MACH_LUCAS)
	err = set_irq_wake(gpio_to_irq(GPIO_KBR6), 1);
	if (err) 
	{
		pr_err("gpiomatrix: set_irq_wake failed for input %d, "	"irq %d\n", mi->input_gpios[i], irq);
	}
#elif defined (CONFIG_MACH_CALLISTO)
	err = set_irq_wake(gpio_to_irq(GPIO_KBR5), 1);	// hsil
	err = set_irq_wake(gpio_to_irq(GPIO_KBR6), 1);	// hsil
	err = set_irq_wake(gpio_to_irq(GPIO_VOL_UP), 1);	// hsil
#endif
	
//#ifndef CONFIG_MACH_LUCAS
#if defined (CONFIG_MACH_CALLISTO)
	// hsil
	set_irq_type(gpio_to_irq(GPIO_SLIDE), IRQ_TYPE_EDGE_BOTH);
	err = request_irq(gpio_to_irq(GPIO_SLIDE), slide_int_handler, IRQF_DISABLED, "slide_kp", kp);
	if (err)
	{
		printk("[SLIDE] request_irq failed for slide\n");
		goto err_request_irq_failed;
	}
	
	err = set_irq_wake(gpio_to_irq(GPIO_SLIDE), 1);
	if (err) 
		printk("[SLIDE] register wakeup source failed\n");
#else
	// for COOPER
	err = irq = gpio_to_irq(GPIO_POWERKEY);
	if (err < 0)
		goto err_gpio_get_irq_num_failed;
	set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
	err = request_irq(irq, gpiokey_irq_handler, IRQF_DISABLED, "gpio_key", kp);
	if (err)
	{
		printk("[PWRKEY] request_irq failed for slide\n");
		goto err_request_irq_failed;
	}
	
	err = set_irq_wake(irq, 1);
	if (err) 
		printk("[PWRKEY] register wakeup source failed\n");

#if AUTO_POWER_ON_OFF_FLAG
	init_timer(&poweroff_keypad_timer);
	poweroff_keypad_timer.function = poweroff_keypad_timer_handler;
	poweroff_keypad_timer.data = (unsigned long)kp;
	poweroff_keypad_timer.expires = jiffies + 60*HZ;

	add_timer(&poweroff_keypad_timer);
#endif
#endif
	return 0;

	for (i = mi->noutputs - 1; i >= 0; i--) {
		free_irq(gpio_to_irq(mi->input_gpios[i]), kp);
err_request_irq_failed:
err_gpio_get_irq_num_failed:
		;
	}
	return err;
}

int gpio_event_matrix_func(struct gpio_event_input_devs *input_devs,
	struct gpio_event_info *info, void **data, int func)
{
	int i;
	int err;
	int key_count;
	struct gpio_kp *kp;
	struct gpio_event_matrix_info *mi;

	mi = container_of(info, struct gpio_event_matrix_info, info);
	if (func == GPIO_EVENT_FUNC_SUSPEND || func == GPIO_EVENT_FUNC_RESUME) {
		/* TODO: disable scanning */
		return 0;
	}

	if (func == GPIO_EVENT_FUNC_INIT) {
		if (mi->keymap == NULL ||
		   mi->input_gpios == NULL ||
		   mi->output_gpios == NULL) {
			err = -ENODEV;
			pr_err("gpiomatrix: Incomplete pdata\n");
			goto err_invalid_platform_data;
		}
		printk("[%s:%d] hw rev = %d\n", __func__, __LINE__, board_hw_revision);

#if defined(CONFIG_MACH_EUROPA)
		if(board_hw_revision >= 3)
		{
			mi->keymap[(0)*mi->ninputs + (1)] = KEY_RESERVED;
			mi->keymap[(3)*mi->ninputs + (1)] = KEY_VOLUMEDOWN;
			mi->keymap[(3)*mi->ninputs + (4)] = KEY_VOLUMEUP;

			if(board_hw_revision >= 4)
			{
				mi->input_gpios[4] = 76;
			}
		}
#endif
#if defined(CONFIG_MACH_CALLISTO)
		// hsil
		input_set_capability(input_devs->dev[0], EV_SW, SW_LID);
#endif
		key_count = mi->ninputs * mi->noutputs;

		*data = kp = kzalloc(sizeof(*kp) + sizeof(kp->keys_pressed[0]) *
				     BITS_TO_LONGS(key_count), GFP_KERNEL);
		if (kp == NULL) {
			err = -ENOMEM;
			pr_err("gpiomatrix: Failed to allocate private data\n");
			goto err_kp_alloc_failed;
		}
		kp->input_devs = input_devs;
		kp->keypad_info = mi;
		for (i = 0; i < key_count; i++) {
			unsigned short keyentry = mi->keymap[i];
			unsigned short keycode = keyentry & MATRIX_KEY_MASK;
			unsigned short dev = keyentry >> MATRIX_CODE_BITS;
			if (dev >= input_devs->count) {
				pr_err("gpiomatrix: bad device index %d >= "
					"%d for key code %d\n",
					dev, input_devs->count, keycode);
				err = -EINVAL;
				goto err_bad_keymap;
			}
			if (keycode && keycode <= KEY_MAX)
				input_set_capability(input_devs->dev[dev],
							EV_KEY, keycode);
		}
		input_set_capability(input_devs->dev[0],EV_KEY, KEY_END); // for COOPER

#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_GIO)
#if defined(CONFIG_KERNEL_SEC_MMICHECK)
		for(i = 0 ; i < ARRAY_SIZE(mmi_keycode) ; i++)
			input_set_capability(input_devs->dev[0],EV_KEY, mmi_keycode[i]); // for COOPER			
#endif
#endif
		for (i = 0; i < mi->noutputs; i++) {
			if (gpio_cansleep(mi->output_gpios[i])) {
				pr_err("gpiomatrix: unsupported output gpio %d,"
					" can sleep\n", mi->output_gpios[i]);
				err = -EINVAL;
				goto err_request_output_gpio_failed;
			}
			err = gpio_request(mi->output_gpios[i], "gpio_kp_out");
			if (err) {
				pr_err("gpiomatrix: gpio_request failed for "
					"output %d\n", mi->output_gpios[i]);
				goto err_request_output_gpio_failed;
			}
			if (mi->flags & GPIOKPF_DRIVE_INACTIVE)
				err = gpio_direction_output(mi->output_gpios[i],
					!(mi->flags & GPIOKPF_ACTIVE_HIGH));
			else
				err = gpio_direction_input(mi->output_gpios[i]);
			if (err) {
				pr_err("gpiomatrix: gpio_configure failed for "
					"output %d\n", mi->output_gpios[i]);
				goto err_output_gpio_configure_failed;
			}
		}
		for (i = 0; i < mi->ninputs; i++) {
			err = gpio_request(mi->input_gpios[i], "gpio_kp_in");
			if (err) {
				pr_err("gpiomatrix: gpio_request failed for "
					"input %d\n", mi->input_gpios[i]);
				goto err_request_input_gpio_failed;
			}
			err = gpio_direction_input(mi->input_gpios[i]);
			if (err) {
				pr_err("gpiomatrix: gpio_direction_input failed"
					" for input %d\n", mi->input_gpios[i]);
				goto err_gpio_direction_input_failed;
			}
		}
		
		// for COOPER
		err = gpio_request(GPIO_POWERKEY, "gpio_powerkey");
		if (err) {
			pr_err("gpiomatrix: gpio_request failed for "
				"input GPIO_POWERKEY %d\n", GPIO_POWERKEY);
			goto err_request_input_gpio_failed;
		}
		err = gpio_direction_input(GPIO_POWERKEY);
		if (err) {
			pr_err("gpiomatrix: gpio_direction_input failed"
				" for input GPIO_POWERKEY %d\n", GPIO_POWERKEY);
			goto err_gpio_direction_input_failed;
		}

		kp->current_output = mi->noutputs;
		kp->key_state_changed = 1;

		hrtimer_init(&kp->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		kp->timer.function = gpio_keypad_timer_func;
		wake_lock_init(&kp->wake_lock, WAKE_LOCK_SUSPEND, "gpio_kp");
		err = gpio_keypad_request_irqs(kp);
		kp->use_irq = err == 0;

		pr_info("GPIO Matrix Keypad Driver: Start keypad matrix for "
			"%s%s in %s mode\n", input_devs->dev[0]->name,
			(input_devs->count > 1) ? "..." : "",
			kp->use_irq ? "interrupt" : "polling");

		if (kp->use_irq)
			wake_lock(&kp->wake_lock);
		hrtimer_start(&kp->timer, ktime_set(0, 0), HRTIMER_MODE_REL);

		return 0;
	}

	err = 0;
	kp = *data;

	if (kp->use_irq)
		for (i = mi->noutputs - 1; i >= 0; i--)
			free_irq(gpio_to_irq(mi->input_gpios[i]), kp);

	hrtimer_cancel(&kp->timer);
	wake_lock_destroy(&kp->wake_lock);
	for (i = mi->noutputs - 1; i >= 0; i--) {
err_gpio_direction_input_failed:
		gpio_free(mi->input_gpios[i]);
err_request_input_gpio_failed:
		;
	}
	for (i = mi->noutputs - 1; i >= 0; i--) {
err_output_gpio_configure_failed:
		gpio_free(mi->output_gpios[i]);
err_request_output_gpio_failed:
		;
	}
err_bad_keymap:
	kfree(kp);
err_kp_alloc_failed:
err_invalid_platform_data:
	return err;
}
