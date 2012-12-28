/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Code Aurora Forum nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * Alternatively, provided that this notice is retained in full, this software
 * may be relicensed by the recipient under the terms of the GNU General Public
 * License version 2 ("GPL") and only version 2, in which case the provisions of
 * the GPL apply INSTEAD OF those given above.  If the recipient relicenses the
 * software under the GPL, then the identification text in the MODULE_LICENSE
 * macro must be changed to reflect "GPLv2" instead of "Dual BSD/GPL".  Once a
 * recipient changes the license terms to the GPL, subsequent recipients shall
 * not relicense under alternate licensing terms, including the BSD or dual
 * BSD/GPL terms.  In addition, the following license statement immediately
 * below and between the words START and END shall also then apply when this
 * software is relicensed under the GPL:
 *
 * START
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 and only version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * END
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <linux/delay.h>
#include <mach/gpio.h>
#include <linux/clk.h>
#include "msm_fb.h"
#include "lcdc_s6d_backlight.h"

#include <linux/module.h>


#define LCDC_DEBUG

#ifdef LCDC_DEBUG
#define DPRINT(x...)	printk("s6d04h0a_TASS " x)
#else
#define DPRINT(x...)	
#endif

#define LCD_DET_ENABLE
#define __LCD_CONTROL_BY_FILE__ /* for Wifi test mode */
#ifdef LCD_DET_ENABLE
#define GPIO_LCD_DET	94
#include <linux/irq.h>

struct s6d04h0a_lcd_det_data {
	int    		irq;
	struct 		work_struct work_lcd_det;  
	/* for lcd_det */
};

struct s6d04h0a_lcd_det_data lcd_det_data;
struct workqueue_struct *lcd_det_wq;
#endif

/* Panel Type */
#define PANEL_BOE           0x61bc11
#define PANEL_GP
#define PANEL_TIANMA

/*
 * Serial Interface
 */
#define LCD_CSX_HIGH	gpio_set_value(spi_cs, 1);
#define LCD_CSX_LOW		gpio_set_value(spi_cs, 0);

#define LCD_SCL_HIGH	gpio_set_value(spi_sclk, 1);
#define LCD_SCL_LOW		gpio_set_value(spi_sclk, 0);

#define LCD_SDI_HIGH	gpio_set_value(spi_sdi, 1);
#define LCD_SDI_LOW		gpio_set_value(spi_sdi, 0);

#define LCD_SDI_SWITCH_INPUT gpio_direction_input(spi_sdi);
#define LCD_SDI_SWITCH_OUTPUT gpio_direction_output(spi_sdi, 0);

#define DEFAULT_USLEEP	1	

int lcd_on_state_for_debug;
EXPORT_SYMBOL(lcd_on_state_for_debug);


/*  added for TN LCD Backlight */
static DECLARE_MUTEX(backlight_sem);

struct setting_table {
	unsigned char command;	
	unsigned char parameters;
	unsigned char parameter[31]; // 31 > 90 > 45
	long wait;
};


extern int board_hw_revision;	// 20101005 hongkuk.son for LCD 180 degree rotate
static unsigned int lcd_panel_type = 0;

static struct setting_table power_on_setting_table_bgr[] = {
		// Non Para
	{	0x01,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	// Level2 command access
	{	0xF0,	2,	{	0x5A, 0x5A, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	// Power Setting Sequence
	{	0xF4,	14,	{	0x01, 0x00, 0x00, 0x00, 0x21, 
						0x47, 0x01, 0x02, 0x2A, 0x2A, 
						0x03, 0x2A, 0x00, 0x02, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF5,	6,	{	0x00, 0x17, 0x6C, 0x00, 0x00, 
						0x0B, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF6,	9,	{	0x01, 0x01, 0x07, 0x00, 0x01, 
						0x0C, 0x01, 0x0C, 0x07, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00 	},	0 },

	// Initializing Sequence
	{	0x35,	1,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0x36,	1,	{	0x08, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0x3A,	1,	{	0x66, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF7,	4,	{	0x02, 0x01, 0x70, 0x80, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00 	},	0 },

	{	0xF2,	12,	{	0x28, 0x65, 0x03, 0x08, 0x08, 
						0x00, 0x00, 0x19, 0x48, 0x04, 
						0x03, 0x01, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },

	/* Gamma */
	
	{	0xF9,	1,	{	0x07, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xFA,	11,	{	0x00, 0x00, 0x00, 0x02, 0x0C, 
						0x0E, 0x0C, 0x3F, 0x3F, 0x3F, 
						0x1B, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	10,	{	0x00, 0x00, 0x26, 0x2F, 0x33, 
						0x3C, 0x2B, 0x2D, 0x19, 0x09, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	


	// Level2 command blocking
	{	0xF0,	2,	{	0xA5, 0xA5, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	// Sleep out
	{	0x11,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	160 },	

	{	0x29,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	


};

/*  Initialize sequence update
 *  11.30 modified ?�문기술그룹 ?�청 ?�항 반영
 *  11.30 ?�규???�임 ?�청 ?�항 반영
 *  12.01 ?�병�??�임 ?�복 ?�청 ?�항 반영
 *  12.03 H/W그룹 ?�질개선 감마 ?�팅 반영
 *  12.10 H/W그룹 ?�질개선 ?�항 ?�복
 *  12.10 ?�문기술그룹 ?�청 ?�항 반영
 *  12.22 ?�문기술그룹 ?�청 ?�항 반영
 *  */
static struct setting_table power_on_setting_table_rgb[] = {
	// Level2 command access
	{	0xF0,	2,	{	0x5A, 0x5A, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF7,	2,	{	0x02, 0x01, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	


	// Power Setting Sequence
	{	0xF4,	14,	{	0x09, 0x00, 0x00, 0x00, 0x77, 
						0x77, 0x07, 0x02, 0x2E, 0x47, 
						0x05, 0x2A, 0x00, 0x02, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF5,	10,	{	0x00, 0x23, 0x5D, 0x00, 0x00, 
						0x0A, 0x00, 0x00, 0x01, 0x0D, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF6,	9,	{	0x00, 0x01, 0x07, 0x00, 0x01, 
						0x0C, 0x01, 0x0C, 0x03, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00 	},	0 },

	// Initializing Sequence
	{	0x35,	1,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0x36,	1,	{	0x98, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0x3A,	1,	{	0x66, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF7,	4,	{	0x00, 0x01, 0x70, 0x80, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00 	},	0 },

	{	0xF8,	2,	{	0x22, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF2,	17,	{	0x28, 0x67, 0x03, 0x08, 0x08, 
						0x00, 0x00, 0x15, 0x48, 0x00, 
						0x00, 0x01, 0x00, 0x00, 0x59, 
						0x08, 0x08, 0x00, 0x00, 0x00	},	0 },
	// Gamma Setting Sequence
	{	0xF9,	1,	{	0x07, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
#if 1 // original
	{	0xFA,	16,	{	0x00, 0x00, 0x10, 0x17, 0x25, 
						0x31, 0x21, 0x31, 0x2B, 0x28, 
						0x2B, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	16,	{	0x00, 0x00, 0x30, 0x32, 0x33, 
						0x33, 0x23, 0x29, 0x22, 0x1B, 
						0x12, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
#else // for H/W ?�질 개선
	{	0xFA,	16,	{	0x00, 0x00, 0x19, 0x17, 0x25, 
						0x31, 0x21, 0x31, 0x2B, 0x28, 
						0x2b, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	16,	{	0x00, 0x00, 0x2b, 0x2f, 0x32, 
						0x35, 0x22, 0x28, 0x19, 0x0f, 
						0x08, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

#endif

	// Level2 command blocking
	{	0xF0,	2,	{	0xA5, 0xA5, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	// Sleep out
	{	0x11,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	160 },	

	{	0x29,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	


};

static struct setting_table power_off_setting_table[] = {
//	Sleep In
	{ 0x10, 0,  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};

#if 0
static struct setting_table sleep_in_setting_table[] = {
//	Sleep In
	{ 0x10, 0,  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};

static struct setting_table sleep_out_setting_table[] = {
//	Sleep In
	{ 0x11, 0,  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};
#endif
/***/

#define POWER_ON_SETTINGS_REV00	(int)(sizeof(power_on_setting_table_bgr)/sizeof(struct setting_table))
#define POWER_ON_SETTINGS_REV01 (int)(sizeof(power_on_setting_table_rgb)/sizeof(struct setting_table))
#define POWER_ON_SETTINGS_HW2	(int)(sizeof(power_on_setting_table_hw2)/sizeof(struct setting_table))
#define POWER_OFF_SETTINGS	(int)(sizeof(power_off_setting_table)/sizeof(struct setting_table))
#define SLEEP_IN_SETTING	(int)(sizeof(sleep_in_setting_table)/sizeof(struct setting_table))
#define SLEEP_OUT_SETTING	(int)(sizeof(sleep_out_setting_table)/sizeof(struct setting_table))

static int lcdc_s6d04h0a_panel_off(struct platform_device *pdev);


static int spi_cs = 0;
static int spi_sclk = 0;
static int spi_sdi = 0;
static int lcd_en = 0;
static int lcd_reset = 0;

struct s6d04h0a_state_type{
	boolean disp_initialized;
	boolean display_on;
	boolean disp_powered_up;
};

static struct s6d04h0a_state_type s6d04h0a_state = { 
	.disp_initialized = TRUE,
	.display_on = TRUE,
	.disp_powered_up = TRUE,
};

static struct msm_panel_common_pdata *lcdc_s6d04h0a_pdata;

static void setting_table_write(struct setting_table *table)
{
	long i, j;
#if 0
	LCD_CSX_HIGH
	udelay(DEFAULT_USLEEP);
	LCD_SCL_HIGH 
	udelay(DEFAULT_USLEEP);

	/* Write Command */
	LCD_CSX_LOW
	udelay(DEFAULT_USLEEP);
	LCD_SCL_LOW 
	udelay(DEFAULT_USLEEP);		
	LCD_SDI_LOW 
	udelay(DEFAULT_USLEEP);
	
	LCD_SCL_HIGH 
	udelay(DEFAULT_USLEEP); 

   	for (i = 7; i >= 0; i--) { 
		LCD_SCL_LOW
		udelay(DEFAULT_USLEEP);
		if ((table->command >> i) & 0x1)
			LCD_SDI_HIGH
		else
			LCD_SDI_LOW
		udelay(DEFAULT_USLEEP);	
		LCD_SCL_HIGH
		udelay(DEFAULT_USLEEP);	
	}

	LCD_CSX_HIGH
	udelay(DEFAULT_USLEEP);	

	/* Write Parameter */
	if ((table->parameters) > 0) {
	for (j = 0; j < table->parameters; j++) {
		LCD_CSX_LOW 
		udelay(DEFAULT_USLEEP); 	
		
		LCD_SCL_LOW 
		udelay(DEFAULT_USLEEP); 	
		LCD_SDI_HIGH 
		udelay(DEFAULT_USLEEP);
		LCD_SCL_HIGH 
		udelay(DEFAULT_USLEEP); 	

		for (i = 7; i >= 0; i--) { 
			LCD_SCL_LOW
			udelay(DEFAULT_USLEEP);	
			if ((table->parameter[j] >> i) & 0x1)
				LCD_SDI_HIGH
			else
				LCD_SDI_LOW
			udelay(DEFAULT_USLEEP);	
			LCD_SCL_HIGH
			udelay(DEFAULT_USLEEP);					
		}

			LCD_CSX_HIGH
			udelay(DEFAULT_USLEEP);	
	}
	}
	if(table->wait)
		mdelay(table->wait);
#else
	LCD_CSX_HIGH
	LCD_SCL_HIGH 

	/* Write Command */
	LCD_CSX_LOW
	LCD_SCL_LOW 
	LCD_SDI_LOW 
	
	LCD_SCL_HIGH 

   	for (i = 7; i >= 0; i--) { 
		LCD_SCL_LOW
		if ((table->command >> i) & 0x1)
			LCD_SDI_HIGH
		else
			LCD_SDI_LOW
		LCD_SCL_HIGH
	}

	LCD_CSX_HIGH

	/* Write Parameter */
	if ((table->parameters) > 0) {
	for (j = 0; j < table->parameters; j++) {
		LCD_CSX_LOW 
		
		LCD_SCL_LOW 
		LCD_SDI_HIGH 
		LCD_SCL_HIGH 

		for (i = 7; i >= 0; i--) { 
			LCD_SCL_LOW
			if ((table->parameter[j] >> i) & 0x1)
				LCD_SDI_HIGH
			else
				LCD_SDI_LOW
			LCD_SCL_HIGH
		}

			LCD_CSX_HIGH
	}
	}
	if(table->wait) {
		msleep(table->wait);
	}

#endif
}

static void spi_read_byte( char addr, uint32 *data,int count)
{
	long i;
	int bnum;
	uint32 bits, dbit;

	LCD_CSX_HIGH
	udelay(DEFAULT_USLEEP);
	LCD_SCL_HIGH 
	udelay(DEFAULT_USLEEP);

	/* Write Command */
	LCD_CSX_LOW
	udelay(DEFAULT_USLEEP);
	LCD_SCL_LOW 
	udelay(DEFAULT_USLEEP);		
	LCD_SDI_LOW 
	udelay(DEFAULT_USLEEP);
	
	LCD_SCL_HIGH 
	udelay(DEFAULT_USLEEP); 

   	for (i = 7; i >= 0; i--) { 
		LCD_SCL_LOW
		udelay(DEFAULT_USLEEP);
		if ((addr >> i) & 0x1)
			LCD_SDI_HIGH
		else
			LCD_SDI_LOW
		udelay(DEFAULT_USLEEP);	
		LCD_SCL_HIGH
		udelay(DEFAULT_USLEEP);	
	}

	//swith input
	LCD_SDI_SWITCH_INPUT
	/* Read Parameter */
	if (count > 1) {
		LCD_SCL_LOW
		udelay(DEFAULT_USLEEP);
		dbit = gpio_get_value(spi_sdi);
		udelay(DEFAULT_USLEEP);
		LCD_SCL_HIGH

	}

	bnum = count * 8;
	bits = 0;
	while(bnum) {
		bits <<= 1;
		LCD_SCL_LOW
		udelay(DEFAULT_USLEEP);
		dbit = gpio_get_value(spi_sdi);		
		LCD_SCL_HIGH
		udelay(DEFAULT_USLEEP);	
		bits |= dbit;
		bnum--;

	}
	*data = bits;
	
	LCD_CSX_LOW
	udelay(DEFAULT_USLEEP);	
	LCD_SDI_SWITCH_OUTPUT



}

static unsigned int determine_lcd_type(void)
{
	unsigned int data = 0;
	
	spi_read_byte(0x04, &data, 3);

	printk("%s, LCD Type :%x \n",__func__,data);
	return data;
}
static void spi_init(void)
{

	/* Set the output so that we dont disturb the slave device */
	gpio_set_value(spi_sclk, 0);
	gpio_set_value(spi_sdi, 0);

	/* Set the Chip Select De-asserted */
	gpio_set_value(spi_cs, 0);

}

static void s6d04h0a_disp_powerup(void)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d04h0a_state.disp_powered_up && !s6d04h0a_state.display_on) {
		/* Reset the hardware first */
		
		gpio_set_value(lcd_reset, 1);
		udelay(100);
		gpio_set_value(lcd_reset, 0);
		udelay(15);
		gpio_set_value(lcd_reset, 1);
		udelay(20);

		
		/* Include DAC power up implementation here */
		
	    s6d04h0a_state.disp_powered_up = TRUE;
	}
}

static void s6d04h0a_disp_powerdown(void)
{
	DPRINT("start %s\n", __func__);	

		/* Reset Assert */
		gpio_set_value(lcd_reset, 0);		
	
	    s6d04h0a_state.disp_powered_up = FALSE;
}

static void s6d04h0a_disp_on(void)
{
	int i;

	DPRINT("start %s\n", __func__);	


	if(!lcd_panel_type) {
	   	lcd_panel_type = determine_lcd_type();
	}
	
	printk("TASS HW rev is %d, apply %d's init sequence\n",board_hw_revision,board_hw_revision);
	if(lcd_panel_type == PANEL_BOE) {
		for (i = 0; i < POWER_ON_SETTINGS_REV01; i++) {
			setting_table_write(&power_on_setting_table_rgb[i]);		
		}

	} else {
		for (i = 0; i < POWER_ON_SETTINGS_REV00; i++)
			setting_table_write(&power_on_setting_table_bgr[i]);		
	}

		s6d04h0a_state.display_on = TRUE;
		lcd_on_state_for_debug = TRUE;
}

static int lcdc_s6d04h0a_panel_on(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	
	if (!s6d04h0a_state.disp_initialized) {

		lcdc_s6d04h0a_pdata->panel_config_gpio(1);
		spi_init();	/* LCD needs SPI */
		s6d04h0a_disp_powerup();
		s6d04h0a_disp_on();
		msleep(50);
		s6d04h0a_state.disp_initialized = TRUE;
		
	}
	return 0;
}

static int lcdc_s6d04h0a_panel_off(struct platform_device *pdev)
{
	int i;
	if(s6d04h0a_state.disp_powered_up && s6d04h0a_state.display_on) {

		for (i = 0; i < POWER_OFF_SETTINGS; i++)
			setting_table_write(&power_off_setting_table[i]);	
		
			lcdc_s6d04h0a_pdata->panel_config_gpio(0);
			s6d04h0a_state.display_on = FALSE;
			lcd_on_state_for_debug = FALSE;
			s6d04h0a_state.disp_initialized = FALSE;

			s6d04h0a_disp_powerdown();
	}
	if(lcd_det_data.irq > 0)
		enable_irq(lcd_det_data.irq); 
	return 0;
}




static void lcdc_s6d04h0a_set_backlight(struct msm_fb_data_type *mfd)
{	
	int bl_value = mfd->bl_level;
	static int lockup_count = 0;
	printk("[BACLKIGHT] : %d\n",bl_value);
	if(board_hw_revision == 1 || board_hw_revision == 0) {
		lcdc_s6d_set_brightness_by_aat1401(bl_value);
	} else if(board_hw_revision == 2 || board_hw_revision == 3) {
		printk("[LCD] BACKLIGHT SET\n");
		lcdc_s6d_set_brightness_by_ktd259(bl_value);
	} else{
		printk("Unknown HW Rev!!!!\n");
		lcdc_s6d_set_brightness_by_ktd259(bl_value);
	}
}
#ifdef __LCD_CONTROL_BY_FILE__
static int s6d04h0a_show_lcd_power(struct device *dev, struct device_attribute *attr, char *buf)
{
        return snprintf(buf, PAGE_SIZE, "%d\n", s6d04h0a_state.disp_initialized);
}

static int s6d04h0a_store_lcd_power(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct platform_device* pdev;
	static struct clk *pclk=NULL;
	static struct clk *pad_pclk=NULL;
	
    if (len < 1)
        return -EINVAL;

	pdev = container_of(dev, struct platform_device, dev);

	if(!pclk || !pad_pclk) {
		pclk = clk_get(NULL,"mdp_lcdc_pclk_clk");
		pad_pclk = clk_get(NULL,"mdp_lcdc_pad_pclk_clk");
		if(IS_ERR(pclk) || IS_ERR(pad_pclk)) {
				printk(KERN_ERR "LCD Error : Clock get failed\n");
				return IS_ERR(pclk);
		}
	}

    if (strnicmp(buf, "on", 2) == 0 || strnicmp(buf, "1", 1) == 0)
    {
		if(s6d04h0a_state.disp_powered_up || s6d04h0a_state.display_on) {
			printk("LCD is alredy turn ON\n");
			return 0;
		}
		clk_enable(pclk);
		clk_enable(pad_pclk);

		lcdc_s6d04h0a_panel_on(pdev);
		if(board_hw_revision == 1 || board_hw_revision == 0) {
			lcdc_s6d_set_brightness_by_aat1401(141);
		} else if(board_hw_revision == 2 || board_hw_revision == 3) {
			lcdc_s6d_set_brightness_by_ktd259(141);
		} else{
			printk("Unknown HW Rev!!!!\n");
			lcdc_s6d_set_brightness_by_ktd259(141);
		}

    }
    else if (strnicmp(buf, "off", 3) == 0 || strnicmp(buf, "0", 1) == 0)
    {
		if(!s6d04h0a_state.disp_powered_up || !s6d04h0a_state.display_on) {
			printk("LCD is already turn OFF\n");
			return 0;
		}

		if(board_hw_revision == 1 || board_hw_revision == 0) {
			lcdc_s6d_set_brightness_by_aat1401(0);
		} else if(board_hw_revision == 2 || board_hw_revision == 3) {
			lcdc_s6d_set_brightness_by_ktd259(0);
		} else{
			printk("Unknown HW Rev!!!!\n");
			lcdc_s6d_set_brightness_by_ktd259(0);
		}

		lcdc_s6d04h0a_panel_off(pdev);
		clk_disable(pclk);
		clk_disable(pad_pclk);
    }
    else
            return -EINVAL;

    return len;
}

static DEVICE_ATTR(lcd_power, 0660,						//sm.kim: give write permission for application
                        s6d04h0a_show_lcd_power,
                        s6d04h0a_store_lcd_power);
#endif
#ifdef LCD_DET_ENABLE // minhyo0614

static irqreturn_t lcd_det_irq_handler(int irq, void *dev_id)
{
	struct s6d04h0a_lcd_det_data *lcd_det = dev_id;

	disable_irq_nosync(lcd_det->irq);
	printk("[LCD] lcd_det->irq  %d\n",lcd_det->irq);

	if(	s6d04h0a_state.display_on == TRUE  &&
		s6d04h0a_state.disp_initialized == TRUE && 
		s6d04h0a_state.disp_powered_up) {
	
		if(lcd_det->irq !=-1)
		{
			queue_work(lcd_det_wq, &lcd_det->work_lcd_det);
		}

		printk("[LCD] IRQ_HANDLED \n");

		return IRQ_HANDLED;
	} else {
		printk("[LCD] LCD Power down OK. \n");
		enable_irq(lcd_det->irq);
		return IRQ_HANDLED;
	}

}

static void lcd_det_work_func(struct work_struct *work)
{
	int i;
	/*  LCD re-initialize. cause of ESD */
	printk("LCD re-initializei workqueue. cause of ESD\n");

	/*  Panel power off  */
	for (i = 0; i < POWER_OFF_SETTINGS; i++)
		setting_table_write(&power_off_setting_table[i]);	

	lcdc_s6d04h0a_pdata->panel_config_gpio(0);
	printk("panel gpio set to OFF\n");
	/* Reset Assert */
	gpio_set_value(lcd_reset, 0);
	printk("lcd reset pin to LOW\n");	
	
	s6d04h0a_state.display_on = FALSE; 
	lcd_on_state_for_debug = FALSE;
	s6d04h0a_state.disp_initialized = FALSE;  
	s6d04h0a_state.disp_powered_up = FALSE;

	mdelay(10);

	/* Panel power on */
	lcdc_s6d04h0a_pdata->panel_config_gpio(1);
	printk("panel gpios set to ON\n");
	spi_init();	/* LCD needs SPI */
	s6d04h0a_disp_powerup();
	printk("disp_powerup ok\n");
	s6d04h0a_disp_on();
	printk("disp_on ok\n");
	mdelay(50);
	s6d04h0a_state.disp_initialized = TRUE;  

	enable_irq(lcd_det_data.irq);
}

#endif

static int __init s6d04h0a_probe(struct platform_device *pdev)
{
	int ret = 0;
	printk("++++++pdev->id=%d\n", pdev->id);

#ifdef __LCD_CONTROL_BY_FILE__
    ret = device_create_file(&(pdev->dev), &dev_attr_lcd_power);
    if (ret < 0)
            printk(KERN_WARNING "s6d04h0a: failed to add entries\n");
#endif

	if (pdev->id == 0)
	{
		lcdc_s6d04h0a_pdata = pdev->dev.platform_data;    // lcdc_s6d04h0a_panel_data in board-msm7x27.c
		#ifdef LCD_DET_ENABLE
		{ 
			int irq, err;

			/* work queue setting */
			lcd_det_wq= create_singlethread_workqueue("lcd_det_wq");
			if (!lcd_det_wq)
				return -ENOMEM;
			INIT_WORK(&lcd_det_data.work_lcd_det, lcd_det_work_func);
			printk("Workqueue Settings complete\n");

			/* gpio config */
//			err = gpio_tlmm_config(GPIO_CFG(GPIO_LCD_DET, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
//			if (err) 
//				printk(KERN_ERR "%s: gpio_tlmm_config(%d)=%d\n", __func__, (int)GPIO_LCD_DET, err);
			
			/* INT setting */
			irq = MSM_GPIO_TO_INT(GPIO_LCD_DET);
			lcd_det_data.irq = -1;
			set_irq_type(irq, IRQ_TYPE_EDGE_RISING);
			err = request_irq(irq, lcd_det_irq_handler, IRQF_DISABLED, "lcd_det_int", &lcd_det_data);
			if (err)
			{
				printk("%s: request_irq failed for lcd_det\n", __func__);
				return 0;
			}
			lcd_det_data.irq = irq;
			disable_irq(lcd_det_data.irq);
			printk("INT Settings complete\n");
		}
		#endif

		/* Setting the Default SPI GPIO's */
		spi_sclk = *(lcdc_s6d04h0a_pdata->gpio_num);
		spi_cs   = *(lcdc_s6d04h0a_pdata->gpio_num + 1);
		spi_sdi  = *(lcdc_s6d04h0a_pdata->gpio_num + 2);
		lcd_en   = *(lcdc_s6d04h0a_pdata->gpio_num + 3);
		lcd_reset= *(lcdc_s6d04h0a_pdata->gpio_num + 4);

		if(!spi_sclk || !spi_cs || !spi_sdi || !lcd_en || !lcd_reset) {
			printk("[LCD] SPI Init Error. %d,%d,%d,%d,%d\n",spi_sclk,spi_cs,spi_sdi,lcd_en,lcd_reset);

			spi_cs = 131;
			spi_sclk = 132;
			spi_sdi = 103;
			lcd_en = 122;
			lcd_reset = 101;

			printk("[LCD] apply GrandTF MSM7227's spi value\n");
	
		}

	}


	

	return 0;
}

static void s6d04h0a_shutdown(struct platform_device *pdev)
{
	
	if(board_hw_revision == 1 || board_hw_revision == 0) {
		lcdc_s6d_set_brightness_by_aat1401(0);
	} else if(board_hw_revision == 2 || board_hw_revision == 3) {
		lcdc_s6d_set_brightness_by_ktd259(0);
	} else {
		printk("Unknown HW Rev!!!!\n");
		lcdc_s6d_set_brightness_by_aat1401(0);
	}

	if(lcd_det_data.irq > 0) {
		free_irq(lcd_det_data.irq,pdev->id);
		lcd_det_data.irq = -1;
	}
	lcdc_s6d04h0a_panel_off(pdev);
}

static struct platform_driver this_driver = {
	.probe  = s6d04h0a_probe,
	.shutdown	= s6d04h0a_shutdown,
	.driver = {
		.name   = "lcdc_s6d04h0a_qvga",
	},
};

static struct msm_fb_panel_data s6d04h0a_panel_data = {
	.on = lcdc_s6d04h0a_panel_on,
	.off = lcdc_s6d04h0a_panel_off,
	.set_backlight = lcdc_s6d04h0a_set_backlight,
};

static struct platform_device this_device = {
	.name   = "lcdc_panel",
	.id	= 1,
	.dev	= {
		.platform_data = &s6d04h0a_panel_data,
	}
};

/* 
 * CHECK POINT
 * if you change screen resolution, you should modify same information in hardware/msm7k/libgralloc-qsd8k/framebuffer.cpp
*/

#define LCDC_FB_XRES	240
#define LCDC_FB_YRES	320

#define LCDC_HPW		10
#define LCDC_HBP		13
#define LCDC_HFP		13
#define LCDC_VPW		2
#define LCDC_VBP		8
#define LCDC_VFP		8


#define LCDC_PCLK		(LCDC_FB_XRES + LCDC_HBP + LCDC_HPW + LCDC_HFP) * (LCDC_FB_YRES + LCDC_VBP + LCDC_VPW + LCDC_VFP) * 2

static int __init lcdc_s6d04h0a_panel_init(void)
{
	int ret;
	struct msm_panel_info *pinfo;

	printk("++++++%s\n", __func__);

#ifdef CONFIG_FB_MSM_TRY_MDDI_CATCH_LCDC_PRISM
	if (msm_fb_detect_client("lcdc_s6d04h0a_qvga"))
		{
		printk(KERN_ERR "%s: msm_fb_detect_client failed!\n", __func__); 
		return 0;
		}
#endif
	
	ret = platform_driver_register(&this_driver);
	if (ret)
		{
		printk(KERN_ERR "%s: platform_driver_register failed! ret=%d\n", __func__, ret); 
		return ret;
		}

	pinfo = &s6d04h0a_panel_data.panel_info;
	pinfo->xres = LCDC_FB_XRES;
	pinfo->yres = LCDC_FB_YRES;
	pinfo->height = 70; // minhyo-rgb888
	pinfo->width = 42;  // minhyo-rgb888
	pinfo->type = LCDC_PANEL;
	pinfo->pdest = DISPLAY_1;
	pinfo->wait_cycle = 0;
	pinfo->bpp = 18;
	pinfo->fb_num = 2;
	pinfo->clk_rate = (8760 * 1000);//(8384 * 1000);
	pinfo->bl_max = 255;
	pinfo->bl_min = 1;

	pinfo->lcdc.h_back_porch = LCDC_HBP;
	pinfo->lcdc.h_front_porch = LCDC_HFP;
	pinfo->lcdc.h_pulse_width = LCDC_HPW;
	pinfo->lcdc.v_back_porch = LCDC_VBP;
	pinfo->lcdc.v_front_porch = LCDC_VFP;
	pinfo->lcdc.v_pulse_width = LCDC_VPW;
	pinfo->lcdc.border_clr = 0;     /* blk */
	pinfo->lcdc.underflow_clr = 0xff;       /* blue */
	pinfo->lcdc.hsync_skew = 0;

	ret = platform_device_register(&this_device);
	if (ret)
		{
		printk(KERN_ERR "%s: platform_device_register failed! ret=%d\n", __func__, ret); 
		platform_driver_unregister(&this_driver);
		}

	printk("--%s\n", __func__);

	return ret;
}

module_init(lcdc_s6d04h0a_panel_init);
