/*
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2008-2009, Code Aurora Forum. All rights reserved.
 * Author: Brian Swetland <swetland@google.com>
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

#include <linux/platform_device.h>
#include <linux/gpio_event.h>

#include <asm/mach-types.h>

/* don't turn this on without updating the ffa support */
#define SCAN_FUNCTION_KEYS 0

/* FFA:
 36: KEYSENSE_N(0)
 37: KEYSENSE_N(1)
 38: KEYSENSE_N(2)
 39: KEYSENSE_N(3)
 40: KEYSENSE_N(4)

 31: KYPD_17
 32: KYPD_15
 33: KYPD_13
 34: KYPD_11
 35: KYPD_9
 41: KYPD_MEMO
*/

static unsigned int keypad_row_gpios_00[] = { 42, 41 }; /* GPIO_NUM for KBC(0) ~ KBC(7) */
static unsigned int keypad_col_gpios_00[] = { 35, 34 };          /* GPIO_NUM for KBR(0) ~ KBR(5) */

// Gio H/W REV 03 Keypad
static unsigned int keypad_row_gpios_03[] = { 42, 41,40 };
static unsigned int keypad_col_gpios_03[] = { 35 };

static unsigned int keypad_row_gpios_8k_ffa[] = {31, 32, 33, 34, 35, 36};
static unsigned int keypad_col_gpios_8k_ffa[] = {38, 39, 40, 41, 42};

#define KEYMAP_INDEX_00(col, row) ((col)*ARRAY_SIZE(keypad_col_gpios_00) + (row))

// Gio H/W REV 03 Keypad
#define KEYMAP_INDEX_03(col, row) ((col)*ARRAY_SIZE(keypad_col_gpios_03) + (row))


#define FFA_8K_KEYMAP_INDEX(row, col) ((row)* \
				ARRAY_SIZE(keypad_col_gpios_8k_ffa) + (col))

static unsigned short keypad_keymap_surf_00[ARRAY_SIZE(keypad_row_gpios_00) *
					  ARRAY_SIZE(keypad_col_gpios_00)] = {

	[KEYMAP_INDEX_00(0, 0)] = KEY_HOME,
	[KEYMAP_INDEX_00(1, 0)] = KEY_RESERVED,
	
	[KEYMAP_INDEX_00(0, 1)] = KEY_VOLUMEDOWN,
	[KEYMAP_INDEX_00(1, 1)] = KEY_VOLUMEUP,
	
#if SCAN_FUNCTION_KEYS
	[KEYMAP_INDEX_00(6, 0)] = KEY_F5,
	[KEYMAP_INDEX_00(6, 1)] = KEY_F4,
	[KEYMAP_INDEX_00(6, 2)] = KEY_F3,
	[KEYMAP_INDEX_00(6, 3)] = KEY_F2,
	[KEYMAP_INDEX_00(6, 4)] = KEY_F1
#endif
};

// Gio H/W REV 03 Keypad
static unsigned short keypad_keymap_surf_03[ARRAY_SIZE(keypad_row_gpios_03) *
					  ARRAY_SIZE(keypad_col_gpios_03)] = {

	[KEYMAP_INDEX_03(0, 0)] = KEY_VOLUMEUP,
	[KEYMAP_INDEX_03(1, 0)] = KEY_VOLUMEDOWN,
	[KEYMAP_INDEX_03(2, 0)] = KEY_HOME,
#if SCAN_FUNCTION_KEYS
	[KEYMAP_INDEX_03(6, 0)] = KEY_F5,
	[KEYMAP_INDEX_03(6, 1)] = KEY_F4,
	[KEYMAP_INDEX_03(6, 2)] = KEY_F3,
	[KEYMAP_INDEX_03(6, 3)] = KEY_F2,
	[KEYMAP_INDEX_03(6, 4)] = KEY_F1
#endif
};

static unsigned short keypad_keymap_ffa[ARRAY_SIZE(keypad_col_gpios_00) *
					      ARRAY_SIZE(keypad_row_gpios_00)] = {
};

#define QSD8x50_FFA_KEYMAP_SIZE (ARRAY_SIZE(keypad_col_gpios_8k_ffa) * \
			ARRAY_SIZE(keypad_row_gpios_8k_ffa))

static unsigned short keypad_keymap_8k_ffa[QSD8x50_FFA_KEYMAP_SIZE] = {
	[FFA_8K_KEYMAP_INDEX(0, 0)] = KEY_VOLUMEDOWN,
	/*[KEYMAP_INDEX(0, 1)] = ,*/
	[FFA_8K_KEYMAP_INDEX(0, 2)] = KEY_DOWN,
	[FFA_8K_KEYMAP_INDEX(0, 3)] = KEY_8,
	[FFA_8K_KEYMAP_INDEX(0, 4)] = KEY_5,

	[FFA_8K_KEYMAP_INDEX(1, 0)] = KEY_UP,
	[FFA_8K_KEYMAP_INDEX(1, 1)] = KEY_CLEAR,
	[FFA_8K_KEYMAP_INDEX(1, 2)] = KEY_4,
	/*[KEYMAP_INDEX(1, 3)] = ,*/
	[FFA_8K_KEYMAP_INDEX(1, 4)] = KEY_2,

	[FFA_8K_KEYMAP_INDEX(2, 0)] = KEY_HOME,      /* A */
	[FFA_8K_KEYMAP_INDEX(2, 1)] = KEY_BACK,      /* B */
	[FFA_8K_KEYMAP_INDEX(2, 2)] = KEY_0,
	[FFA_8K_KEYMAP_INDEX(2, 3)] = 228,           /* KEY_SHARP */
	[FFA_8K_KEYMAP_INDEX(2, 4)] = KEY_9,

	[FFA_8K_KEYMAP_INDEX(3, 0)] = KEY_3,
	[FFA_8K_KEYMAP_INDEX(3, 1)] = KEY_RIGHT,
	[FFA_8K_KEYMAP_INDEX(3, 2)] = KEY_VOLUMEUP,
	/*[KEYMAP_INDEX(3, 3)] = ,*/
	[FFA_8K_KEYMAP_INDEX(3, 4)] = KEY_6,

	[FFA_8K_KEYMAP_INDEX(4, 0)] = 232,		/* OK */
	[FFA_8K_KEYMAP_INDEX(4, 1)] = KEY_SOUND,
	[FFA_8K_KEYMAP_INDEX(4, 2)] = KEY_1,
	[FFA_8K_KEYMAP_INDEX(4, 3)] = KEY_SEND,
	[FFA_8K_KEYMAP_INDEX(4, 4)] = KEY_LEFT,

	/*[KEYMAP_INDEX(5, 0)] = ,*/
	[FFA_8K_KEYMAP_INDEX(5, 1)] = 227,           /* KEY_STAR */
	[FFA_8K_KEYMAP_INDEX(5, 2)] = 230, /*SOFT2*/ /* 2 */
	[FFA_8K_KEYMAP_INDEX(5, 3)] = KEY_MENU,      /* 1 */
	[FFA_8K_KEYMAP_INDEX(5, 4)] = KEY_7,

};

/* SURF keypad platform device information */
static struct gpio_event_matrix_info surf_keypad_matrix_info_00 = {
	.info.func	= gpio_event_matrix_func,
	.keymap		= keypad_keymap_surf_00,
	.output_gpios	= keypad_col_gpios_00,
	.input_gpios	= keypad_row_gpios_00,
	.noutputs	= ARRAY_SIZE(keypad_col_gpios_00),
	.ninputs	= ARRAY_SIZE(keypad_row_gpios_00),
	.settle_time.tv.nsec = 40 * NSEC_PER_USEC,
	.poll_time.tv.nsec = 20 * NSEC_PER_MSEC,
	.flags		= GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_DRIVE_INACTIVE |
			  GPIOKPF_PRINT_UNMAPPED_KEYS
};

// Gio H/W REV 03 Keypad
static struct gpio_event_matrix_info surf_keypad_matrix_info_03 = {
	.info.func	= gpio_event_matrix_func,
	.keymap		= keypad_keymap_surf_03,
	.output_gpios	= keypad_col_gpios_03,
	.input_gpios	= keypad_row_gpios_03,
	.noutputs	= ARRAY_SIZE(keypad_col_gpios_03),
	.ninputs	= ARRAY_SIZE(keypad_row_gpios_03),
	.settle_time.tv.nsec = 40 * NSEC_PER_USEC,
	.poll_time.tv.nsec = 20 * NSEC_PER_MSEC,
	.flags		= GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_DRIVE_INACTIVE |
			  GPIOKPF_PRINT_UNMAPPED_KEYS
};

static struct gpio_event_info *surf_keypad_info_00[] = {
	&surf_keypad_matrix_info_00.info
};

// Gio H/W REV 03 Keypad
static struct gpio_event_info *surf_keypad_info_03[] = {
	&surf_keypad_matrix_info_03.info
};

static struct gpio_event_platform_data surf_keypad_data_00 = {
	.name		= "sec_key",
	.info			= surf_keypad_info_00,
	.info_count	= ARRAY_SIZE(surf_keypad_info_00)
};

// Gio H/W REV 03 Keypad
static struct gpio_event_platform_data surf_keypad_data_03 = {
	.name		= "sec_key",
	.info			= surf_keypad_info_03,
	.info_count	= ARRAY_SIZE(surf_keypad_info_03)
};

struct platform_device keypad_device_surf_00 = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &surf_keypad_data_00,
	},
};

// Gio H/W REV 03 Keypad
struct platform_device keypad_device_surf_03 = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &surf_keypad_data_03,
	},
};


/* 8k FFA keypad platform device information */
static struct gpio_event_matrix_info keypad_matrix_info_8k_ffa = {
	.info.func	= gpio_event_matrix_func,
	.keymap		= keypad_keymap_8k_ffa,
	.output_gpios	= keypad_row_gpios_8k_ffa,
	.input_gpios	= keypad_col_gpios_8k_ffa,
	.noutputs	= ARRAY_SIZE(keypad_row_gpios_8k_ffa),
	.ninputs	= ARRAY_SIZE(keypad_col_gpios_8k_ffa),
	.settle_time.tv.nsec = 40 * NSEC_PER_USEC,
	.poll_time.tv.nsec = 20 * NSEC_PER_MSEC,
	.flags		= GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_DRIVE_INACTIVE |
			  GPIOKPF_PRINT_UNMAPPED_KEYS
};

static struct gpio_event_info *keypad_info_8k_ffa[] = {
	&keypad_matrix_info_8k_ffa.info
};

static struct gpio_event_platform_data keypad_data_8k_ffa = {
	.name		= "8k_ffa_keypad",
	.info		= keypad_info_8k_ffa,
	.info_count	= ARRAY_SIZE(keypad_info_8k_ffa)
};

struct platform_device keypad_device_8k_ffa = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &keypad_data_8k_ffa,
	},
};

/* 7k FFA keypad platform device information */
static struct gpio_event_matrix_info keypad_matrix_info_7k_ffa = {
	.info.func	= gpio_event_matrix_func,
	.keymap		= keypad_keymap_ffa,
	.output_gpios	= keypad_row_gpios_00,
	.input_gpios	= keypad_col_gpios_00,
	.noutputs	= ARRAY_SIZE(keypad_row_gpios_00),
	.ninputs	= ARRAY_SIZE(keypad_col_gpios_00),
	.settle_time.tv.nsec = 40 * NSEC_PER_USEC,
	.poll_time.tv.nsec = 20 * NSEC_PER_MSEC,
	.flags		= GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_DRIVE_INACTIVE |
			  GPIOKPF_PRINT_UNMAPPED_KEYS
};

static struct gpio_event_info *keypad_info_7k_ffa[] = {
	&keypad_matrix_info_7k_ffa.info
};

static struct gpio_event_platform_data keypad_data_7k_ffa = {
	.name		= "7k_ffa_keypad",
	.info		= keypad_info_7k_ffa,
	.info_count	= ARRAY_SIZE(keypad_info_7k_ffa)
};

struct platform_device keypad_device_7k_ffa = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &keypad_data_7k_ffa,
	},
};


