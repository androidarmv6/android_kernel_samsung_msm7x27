/*
 * leds-msm-pmic.c - MSM PMIC LEDs driver.
 *
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <mach/vreg.h>

#include <mach/pmic.h>
#include <linux/gpio.h>
#include <linux/delay.h>

//#define MAX_KEYPAD_BL_LEVEL	16

extern int board_hw_revision;
#if defined(CONFIG_MACH_CALLISTO)
static unsigned char n_GPIO_KEY_LED_EN = 78;
#else
static unsigned char n_GPIO_KEY_LED_EN = 97;
#endif
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) || defined(CONFIG_MACH_TASSDT)
static struct vreg *vreg_keyled;
#endif

#ifdef CONFIG_KEYPAD_TOUCH_BLN
#include <linux/miscdevice.h>
#define BACKLIGHTNOTIFICATION_VERSION 8

bool bln_enabled = false; // indicates if BLN function is enabled/allowed (default: false, app enables it on boot)
bool bln_notification_ongoing= false; // indicates ongoing LED Notification
bool bln_blink_enabled = false;	// indicates blink is set
#endif

static int state = 0;


static void msm_keypad_bl_led_set(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	// printk("[KeyLED] %s: value=%d\n", __func__, value);
	if (value != state)
	{
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
		if ( board_hw_revision >= 0x3 )
		{
		if (value)
			vreg_enable(vreg_keyled);
		else
			vreg_disable(vreg_keyled);
		}
		else
		{
			if (value)
				gpio_set_value(n_GPIO_KEY_LED_EN, 1);
			else
				gpio_set_value(n_GPIO_KEY_LED_EN, 0);
		}
#endif

#if defined(CONFIG_MACH_LUCAS) || defined(CONFIG_MACH_CALLISTO)
	if (value)
		gpio_set_value(n_GPIO_KEY_LED_EN, 1);
	else
		gpio_set_value(n_GPIO_KEY_LED_EN, 0);
#endif

#if defined(CONFIG_MACH_TASSDT)
	if (value)
		vreg_enable(vreg_keyled);
	else
		vreg_disable(vreg_keyled);
#endif

	 state = value;
	}
}

static struct led_classdev msm_kp_bl_led = {
	.name			= "button-backlight",
	.brightness_set		= msm_keypad_bl_led_set,
	.brightness		= 0,
	.max_brightness		= 1,
};

#ifdef CONFIG_KEYPAD_TOUCH_BLN
/* bln start */
static void enable_touchkey_backlights(void){
	msm_keypad_bl_led_set(&msm_kp_bl_led, 1);
}

static void disable_touchkey_backlights(void){
	msm_keypad_bl_led_set(&msm_kp_bl_led, 0);
}

static void enable_led_notification(void){
	if (bln_enabled){
		/* signal ongoing led notification */
		bln_notification_ongoing = true;
		enable_touchkey_backlights();
		printk("%s: notification led enabled\n", __FUNCTION__);
	}
}

static void disable_led_notification(void){
	printk("%s: notification led disabled\n", __FUNCTION__);
	/* disable the blink state */
	bln_blink_enabled = false;
	disable_touchkey_backlights();
	/* signal led notification is disabled */
	bln_notification_ongoing = false;
}

static ssize_t backlightnotification_status_read(struct device *dev, struct device_attribute *attr, char *buf) {
    return sprintf(buf,"%u\n",(bln_enabled ? 1 : 0));
}

static ssize_t backlightnotification_status_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int data;
	if(sscanf(buf, "%u\n", &data) == 1) {
		pr_devel("%s: %u \n", __FUNCTION__, data);
		if(data == 0 || data == 1){

			if(data == 1){
				printk("%s: backlightnotification function enabled\n", __FUNCTION__);
				bln_enabled = true;
			}

			if(data == 0){
				printk("%s: backlightnotification function disabled\n", __FUNCTION__);
				bln_enabled = false;
				if (bln_notification_ongoing)
					disable_led_notification();
			}
		}
		else
			printk("%s: invalid input range %u\n", __FUNCTION__, data);
	}
	else
		printk("%s: invalid input\n", __FUNCTION__);

	return size;
}

static ssize_t notification_led_status_read(struct device *dev, struct device_attribute *attr, char *buf) {
	return sprintf(buf,"%u\n", (bln_notification_ongoing ? 1 : 0));
}

static ssize_t notification_led_status_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int data;

	if(sscanf(buf, "%u\n", &data) == 1) {
		if(data == 0 || data == 1){
			pr_devel("%s: %u \n", __FUNCTION__, data);
			if (data == 1)
				enable_led_notification();

			if(data == 0)
				disable_led_notification();

		} else
			printk("%s: wrong input %u\n", __FUNCTION__, data);
	} else
		printk("%s: input error\n", __FUNCTION__);

	return size;
}

static ssize_t blink_control_read(struct device *dev, struct device_attribute *attr, char *buf) {
	return sprintf(buf,"%u\n", (bln_blink_enabled ? 1 : 0));
}

static ssize_t blink_control_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int data;

	if(sscanf(buf, "%u\n", &data) == 1) {
		if(data == 0 || data == 1){
			if (bln_notification_ongoing){
				pr_devel("%s: %u \n", __FUNCTION__, data);
				if (data == 1){
					bln_blink_enabled = true;
					disable_touchkey_backlights();
				}

				if(data == 0){
					bln_blink_enabled = false;
					enable_touchkey_backlights();
				}
			}

		} else
			printk("%s: wrong input %u\n", __FUNCTION__, data);
	} else
		printk("%s: input error\n", __FUNCTION__);

	return size;
}

static ssize_t backlightnotification_version(struct device *dev, struct device_attribute *attr, char *buf) {
	return sprintf(buf, "%u\n", BACKLIGHTNOTIFICATION_VERSION);
}

static DEVICE_ATTR(blink_control, S_IRUGO | S_IWUGO , blink_control_read, blink_control_write);
static DEVICE_ATTR(enabled, S_IRUGO | S_IWUGO , backlightnotification_status_read, backlightnotification_status_write);
static DEVICE_ATTR(notification_led, S_IRUGO | S_IWUGO , notification_led_status_read, notification_led_status_write);
static DEVICE_ATTR(version, S_IRUGO , backlightnotification_version, NULL);

static struct attribute *bln_interface_attributes[] = {
		&dev_attr_blink_control.attr,
		&dev_attr_enabled.attr,
		&dev_attr_notification_led.attr,
		&dev_attr_version.attr,
		NULL
};

static struct attribute_group bln_interface_attributes_group = {
		.attrs  = bln_interface_attributes,
};

static struct miscdevice backlightnotification_device = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = "backlightnotification",
};
/* bln end */
#endif


static int msm_pmic_led_probe(struct platform_device *pdev)
{
	int rc, ret = 0;
#if !defined(CONFIG_MACH_COOPER) && !defined(CONFIG_MACH_GIO) && !defined(CONFIG_MACH_TASSDT)
	struct vreg *vreg_keyled;
#endif

#if defined(CONFIG_MACH_COOPER)
	if ( board_hw_revision >= 0x3 )
	{
	vreg_keyled = vreg_get(NULL, "ldo17");
	ret = vreg_set_level(vreg_keyled, OUT3300mV);
	}
	else
	{
		vreg_keyled = vreg_get(NULL, "ldo4");
		ret = vreg_set_level(vreg_keyled, OUT3000mV);
	}
#endif

#if defined(CONFIG_MACH_GIO)
	vreg_keyled = vreg_get(NULL, "ldo17");
	ret = vreg_set_level(vreg_keyled, OUT2800mV);
#endif
#if defined(CONFIG_MACH_TASSDT)
	vreg_keyled = vreg_get(NULL, "ldo4");
	ret = vreg_set_level(vreg_keyled, OUT3000mV);
#endif

	rc = led_classdev_register(&pdev->dev, &msm_kp_bl_led);
	if (rc) {
		dev_err(&pdev->dev, "unable to register led class driver\n");
		return rc;
	}
#ifdef CONFIG_KEYPAD_TOUCH_BLN
	printk("%s misc_register(%s)\n", __FUNCTION__, backlightnotification_device.name);
	rc = misc_register(&backlightnotification_device);
	if (rc) {
		printk("%s misc_register(%s) fail\n", __FUNCTION__, backlightnotification_device.name);
	} else {
		/* add the backlightnotification attributes */
		if (sysfs_create_group(&backlightnotification_device.this_device->kobj, &bln_interface_attributes_group) < 0)
		{
			printk("%s sysfs_create_group fail\n", __FUNCTION__);
			printk("Failed to create sysfs group for device (%s)!\n", backlightnotification_device.name);
		}
	}
#endif
	msm_keypad_bl_led_set(&msm_kp_bl_led, 0);
	return rc;
}

static int __devexit msm_pmic_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&msm_kp_bl_led);
#ifdef CONFIG_KEYPAD_TOUCH_BLN
	misc_deregister(&backlightnotification_device);
#endif

	return 0;
}

#ifdef CONFIG_PM
static int msm_pmic_led_suspend(struct platform_device *dev,
		pm_message_t pm_state)
{
#ifdef CONFIG_KEYPAD_TOUCH_BLN
	/*
	 * Disallow powering off the touchkey controller
	 * while a led notification is ongoing
	 */
	if(!bln_notification_ongoing)
#endif
	{
		msm_keypad_bl_led_set(&msm_kp_bl_led, 0);
		led_classdev_suspend(&msm_kp_bl_led);
	}
#ifdef CONFIG_KEYPAD_TOUCH_BLN
	else
		enable_led_notification();
#endif

	return 0;
}

static int msm_pmic_led_resume(struct platform_device *dev)
{
	led_classdev_resume(&msm_kp_bl_led);

	return 0;
}
#else
#define msm_pmic_led_suspend NULL
#define msm_pmic_led_resume NULL
#endif

static struct platform_driver msm_pmic_led_driver = {
	.probe		= msm_pmic_led_probe,
	.remove		= __devexit_p(msm_pmic_led_remove),
	.suspend	= msm_pmic_led_suspend,
	.resume		= msm_pmic_led_resume,
	.driver		= {
		.name	= "pmic-leds",
		.owner	= THIS_MODULE,
	},
};

static int __init msm_pmic_led_init(void)
{
#if defined(CONFIG_MACH_LUCAS)
	n_GPIO_KEY_LED_EN = 58;
#elif defined(CONFIG_MACH_CALLISTO)
	if( board_hw_revision < 3 )
		n_GPIO_KEY_LED_EN = 77;
#endif
	return platform_driver_register(&msm_pmic_led_driver);
}
module_init(msm_pmic_led_init);

static void __exit msm_pmic_led_exit(void)
{
	platform_driver_unregister(&msm_pmic_led_driver);
}
module_exit(msm_pmic_led_exit);

MODULE_DESCRIPTION("MSM PMIC LEDs driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pmic-leds");
