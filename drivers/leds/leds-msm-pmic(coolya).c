/*
 * leds-msm-pmic.c - MSM PMIC LEDs driver.
 *
 * Copyright (c) 2009, Code Aurora Forum. All rights reserved.
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

//#define MAX_KEYPAD_BL_LEVEL	16

extern int board_hw_revision;
#if defined(CONFIG_MACH_CALLISTO)
static unsigned char n_GPIO_KEY_LED_EN = 78;
#else
static unsigned char n_GPIO_KEY_LED_EN = 97;
#endif
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) || defined(CONFIG_MACH_TASSDT)
static struct vreg *vreg_keyled;
static int state;
#endif

static void set_led(int value)
{
	if (value > 0)
			{
				vreg_enable(vreg_keyled);
				printk("[KeyLED] %s: vreg_enable\n", __func__);
			}
			else
			{
				vreg_disable(vreg_keyled);
				printk("[KeyLED] %s: vreg_disable\n", __func__);
			}
}

static void msm_keypad_bl_led_set(struct led_classdev *led_cdev,
	enum led_brightness value)
{
//	int ret;

	// hsil
	printk("[KeyLED] %s: value=%d\n", __func__, value);

#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if (value > 1) value = 1;

	if(value != state)
	{
		if ( board_hw_revision >= 0x3 )
		{
			set_led(value);
		}
		else
			{
			if (value > 0)
			{
				gpio_set_value(n_GPIO_KEY_LED_EN, 1);
				printk("[KeyLED] %s: gpio_set_value(1)\n", __func__);
			}
			else
			{
				gpio_set_value(n_GPIO_KEY_LED_EN, 0);
				printk("[KeyLED] %s: gpio_set_value(0)\n", __func__);
			}
		}
		state = value;
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

//	ret = pmic_set_led_intensity(LED_KEYPAD, value / MAX_KEYPAD_BL_LEVEL);
//	if (ret)
//		dev_err(led_cdev->dev, "can't set keypad backlight\n");
}

static struct led_classdev msm_kp_bl_led = {
	.name			= "button-backlight",
	.brightness_set		= msm_keypad_bl_led_set,
	.brightness		= LED_OFF,
};

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
	msm_keypad_bl_led_set(&msm_kp_bl_led, LED_FULL);
	return rc;
}

static int __devexit msm_pmic_led_remove(struct platform_device *pdev)
{
	state = -1;
	led_classdev_unregister(&msm_kp_bl_led);

	return 0;
}

#ifdef CONFIG_PM
static int msm_pmic_led_suspend(struct platform_device *dev,
		pm_message_t state)
{
	msm_keypad_bl_led_set(&msm_kp_bl_led, LED_OFF);
	led_classdev_suspend(&msm_kp_bl_led);

	return 0;
}

static int msm_pmic_led_resume(struct platform_device *dev)
{
	led_classdev_resume(&msm_kp_bl_led);
	msm_keypad_bl_led_set(&msm_kp_bl_led, LED_FULL);
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
