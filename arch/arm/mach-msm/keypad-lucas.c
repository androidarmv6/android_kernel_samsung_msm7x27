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

static unsigned int keypad_row_gpios[] = { 35, 34, 33, 32, 31, 123, 122, 110 }; /* GPIO_NUM for KBC(0) ~ KBC(7) */
static unsigned int keypad_col_gpios[] = { 42, 41, 40, 39, 38, 2, 3 };          /* GPIO_NUM for KBR(0) ~ KBR(6) */

#define KEYMAP_INDEX(row, col) ((row)*ARRAY_SIZE(keypad_col_gpios) + (col))

static unsigned short keypad_keymap_bennett_00[ARRAY_SIZE(keypad_col_gpios) *
					  ARRAY_SIZE(keypad_row_gpios)] = {
        [KEYMAP_INDEX(0, 0)] = KEY_Q,
        [KEYMAP_INDEX(0, 1)] = KEY_A,
        [KEYMAP_INDEX(0, 2)] = KEY_Z,
        [KEYMAP_INDEX(0, 3)] = KEY_CANCEL,	// KEY SYM
        [KEYMAP_INDEX(0, 4)] = KEY_O,
        [KEYMAP_INDEX(0, 5)] = KEY_LEFTSHIFT,
//        [KEYMAP_INDEX(0, 6)] = KEY_END,
 
        [KEYMAP_INDEX(1, 0)] = KEY_W,
        [KEYMAP_INDEX(1, 1)] = KEY_S,
        [KEYMAP_INDEX(1, 2)] = KEY_X,
        [KEYMAP_INDEX(1, 3)] = KEY_MAIL,
        [KEYMAP_INDEX(1, 4)] = KEY_P,
        [KEYMAP_INDEX(1, 5)] = KEY_RIGHTALT,
        [KEYMAP_INDEX(1, 6)] = KEY_VOLUMEUP,

        [KEYMAP_INDEX(2, 0)] = KEY_E,
        [KEYMAP_INDEX(2, 1)] = KEY_D,
        [KEYMAP_INDEX(2, 2)] = KEY_C,
        [KEYMAP_INDEX(2, 3)] = KEY_QUESTION,
        [KEYMAP_INDEX(2, 4)] = KEY_L,
        [KEYMAP_INDEX(2, 6)] = KEY_VOLUMEDOWN,
 
        [KEYMAP_INDEX(3, 0)] = KEY_R,
        [KEYMAP_INDEX(3, 1)] = KEY_F,
        [KEYMAP_INDEX(3, 2)] = KEY_V,
        [KEYMAP_INDEX(3, 3)] = KEY_SPACE,
        [KEYMAP_INDEX(3, 4)] = KEY_BACKSPACE,
        [KEYMAP_INDEX(3, 5)] = KEY_SEND,        
        [KEYMAP_INDEX(3, 6)] = KEY_CAMERA,                
 
        [KEYMAP_INDEX(4, 0)] = KEY_T,
        [KEYMAP_INDEX(4, 1)] = KEY_G,
        [KEYMAP_INDEX(4, 2)] = KEY_B,
        [KEYMAP_INDEX(4, 3)] = KEY_DOT,
	 [KEYMAP_INDEX(4, 4)] = KEY_UP,
        [KEYMAP_INDEX(4, 5)] = KEY_DOWN,

        [KEYMAP_INDEX(5, 0)] = KEY_Y,
        [KEYMAP_INDEX(5, 1)] = KEY_H,
        [KEYMAP_INDEX(5, 2)] = KEY_N,
        [KEYMAP_INDEX(5, 3)] = KEY_LEFT,
        [KEYMAP_INDEX(5, 4)] = KEY_ENTER,
	 [KEYMAP_INDEX(5, 5)] = KEY_RIGHT,
 
        [KEYMAP_INDEX(6, 0)] = KEY_U,
        [KEYMAP_INDEX(6, 1)] = KEY_J,
        [KEYMAP_INDEX(6, 2)] = KEY_M,
        [KEYMAP_INDEX(6, 3)] = KEY_MENU,
        [KEYMAP_INDEX(6, 4)] = KEY_BACK,
 
        [KEYMAP_INDEX(7, 0)] = KEY_I,
        [KEYMAP_INDEX(7, 1)] = KEY_K,
        [KEYMAP_INDEX(7, 3)] = KEY_HOME,
        [KEYMAP_INDEX(7, 4)] = KEY_SEARCH, 
};

/* SURF keypad platform device information */
static struct gpio_event_matrix_info bennett_00_keypad_matrix_info = {
	.info.func	= gpio_event_matrix_func,
	.keymap		= keypad_keymap_bennett_00,
	.output_gpios	= keypad_row_gpios,
	.input_gpios	= keypad_col_gpios,
	.noutputs	= ARRAY_SIZE(keypad_row_gpios),
	.ninputs	= ARRAY_SIZE(keypad_col_gpios),
	.settle_time.tv.nsec = 40 * NSEC_PER_USEC,
	.poll_time.tv.nsec = 20 * NSEC_PER_MSEC,
	.flags		= GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_DRIVE_INACTIVE |
			  GPIOKPF_PRINT_UNMAPPED_KEYS
};

static struct gpio_event_info *bennett_00_keypad_info[] = {
	&bennett_00_keypad_matrix_info.info
};

static struct gpio_event_platform_data bennett_00_keypad_data = {
	.name		= "sec_keypad0",
	.info		= bennett_00_keypad_info,
	.info_count	= ARRAY_SIZE(bennett_00_keypad_info)
};
struct platform_device keypad_device_bennett_00 = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &bennett_00_keypad_data,
	},
};

// hsil
static unsigned short keypad_keymap_bennett_03[ARRAY_SIZE(keypad_col_gpios) *
					  ARRAY_SIZE(keypad_row_gpios)] = {
        [KEYMAP_INDEX(0, 0)] = KEY_Q,
        [KEYMAP_INDEX(0, 1)] = KEY_T,
        [KEYMAP_INDEX(0, 2)] = KEY_Z,
        [KEYMAP_INDEX(0, 3)] = KEY_B,
        [KEYMAP_INDEX(0, 4)] = KEY_LEFTSHIFT,
        [KEYMAP_INDEX(0, 5)] = KEY_MENU,
 
        [KEYMAP_INDEX(1, 0)] = KEY_W,
        [KEYMAP_INDEX(1, 1)] = KEY_Y,
        [KEYMAP_INDEX(1, 2)] = KEY_X,
        [KEYMAP_INDEX(1, 3)] = KEY_N,
        [KEYMAP_INDEX(1, 4)] = KEY_RIGHTALT,
        [KEYMAP_INDEX(1, 5)] = KEY_HOME,
        [KEYMAP_INDEX(1, 6)] = KEY_VOLUMEUP,

        [KEYMAP_INDEX(2, 0)] = KEY_E,
        [KEYMAP_INDEX(2, 1)] = KEY_U,
        [KEYMAP_INDEX(2, 2)] = KEY_C,
        [KEYMAP_INDEX(2, 3)] = KEY_M,
        [KEYMAP_INDEX(2, 5)] = KEY_BACK,
        [KEYMAP_INDEX(2, 6)] = KEY_VOLUMEDOWN,
 
        [KEYMAP_INDEX(3, 0)] = KEY_R,
        [KEYMAP_INDEX(3, 1)] = KEY_I,
        [KEYMAP_INDEX(3, 2)] = KEY_V,
        [KEYMAP_INDEX(3, 3)] = KEY_ENTER,
        [KEYMAP_INDEX(3, 5)] = KEY_SEARCH,
 
        [KEYMAP_INDEX(4, 0)] = KEY_A,
        [KEYMAP_INDEX(4, 1)] = KEY_G,
        [KEYMAP_INDEX(4, 2)] = KEY_O,
        [KEYMAP_INDEX(4, 3)] = KEY_CANCEL,	// SYM
        [KEYMAP_INDEX(4, 5)] = KEY_QUESTION,

        [KEYMAP_INDEX(5, 0)] = KEY_S,
        [KEYMAP_INDEX(5, 1)] = KEY_H,
        [KEYMAP_INDEX(5, 2)] = KEY_P,
        [KEYMAP_INDEX(5, 3)] = KEY_0,
        [KEYMAP_INDEX(5, 4)] = KEY_SEND,        
        [KEYMAP_INDEX(5, 5)] = KEY_CAMERA,              
 
        [KEYMAP_INDEX(6, 0)] = KEY_D,
        [KEYMAP_INDEX(6, 1)] = KEY_J,
        [KEYMAP_INDEX(6, 2)] = KEY_L,
        [KEYMAP_INDEX(6, 3)] = KEY_UP,
        [KEYMAP_INDEX(6, 4)] = KEY_DOWN,
        [KEYMAP_INDEX(6, 5)] = KEY_SPACE,
 
        [KEYMAP_INDEX(7, 0)] = KEY_F,
        [KEYMAP_INDEX(7, 1)] = KEY_K,
        [KEYMAP_INDEX(7, 2)] = KEY_BACKSPACE,
        [KEYMAP_INDEX(7, 3)] = KEY_LEFT,
        [KEYMAP_INDEX(7, 4)] = KEY_RIGHT, 
        [KEYMAP_INDEX(7, 5)] = KEY_DOT, 
};

static struct gpio_event_matrix_info bennett_03_keypad_matrix_info = {
	.info.func	= gpio_event_matrix_func,
	.keymap		= keypad_keymap_bennett_03,
	.output_gpios	= keypad_row_gpios,
	.input_gpios	= keypad_col_gpios,
	.noutputs	= ARRAY_SIZE(keypad_row_gpios),
	.ninputs	= ARRAY_SIZE(keypad_col_gpios),
	.settle_time.tv.nsec = 40 * NSEC_PER_USEC,
	.poll_time.tv.nsec = 20 * NSEC_PER_MSEC,
	.flags		= GPIOKPF_LEVEL_TRIGGERED_IRQ | GPIOKPF_DRIVE_INACTIVE |
			  GPIOKPF_PRINT_UNMAPPED_KEYS
};

static struct gpio_event_info *bennett_03_keypad_info[] = {
	&bennett_03_keypad_matrix_info.info
};

static struct gpio_event_platform_data bennett_03_keypad_data = {
	.name		= "sec_keypad",	
	.info		= bennett_03_keypad_info,
	.info_count	= ARRAY_SIZE(bennett_03_keypad_info)
};
struct platform_device keypad_device_bennett_03 = {
	.name	= GPIO_EVENT_DEV_NAME,
	.id	= -1,
	.dev	= {
		.platform_data	= &bennett_03_keypad_data,
	},
};


