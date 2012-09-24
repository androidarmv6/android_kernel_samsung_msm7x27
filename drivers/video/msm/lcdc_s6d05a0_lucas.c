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
#define DPRINT(x...)	printk("s6d05a0 " x)
#else
#define DPRINT(x...)	
#endif

#define __LCD_CONTROL_BY_FILE__ /* for Wifi test mode */
#define GPIO_LCD_DET	94

/* Panel Type */
#define PANEL_SHARP_VA		0x511810
#define PANEL_GP_TN			0x61ad10

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
	unsigned char parameter[20];
	long wait;
};

extern int board_hw_revision;	// 20101005 hongkuk.son for LCD 180 degree rotate
unsigned int lcd_panel_type = 0;

// bennett
static struct setting_table power_on_setting_table_va[] = {
	{	 0xF1,	4,  /* PASSWD2 */ 
			{ 0x01, 0x5a, 0x01, 0x5a, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xEF,	1,  /* DCON */
			{ 0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xF2, 11,  /* DISCTL */
			{ 0x14, 0x14, 0x0f, 0x11, 0x0f, 
			  0x11, 0x0f, 0x10, 0x00, 0x18, 
			  0x18, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xF6,	3,  /* IFCTL */
			{ 0x80, 0x30, 0x09, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xFD,	3,  /* GATECTL */
			{ 0x33, 0x1D, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0x2A,	4,  /* CASET */
			{ 0x00, 0x00, 0x01, 0x3f, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0x2B,	4,  /* PASET */ 
			{ 0x00, 0x00, 0x00, 0xef, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0x36,	1,  /* MADCTL */
			{ 0x48, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0x3A,  1,  /* COLMOD */
			{0x77, 0x00, 0x00, 0x00, 0x00, 
			 0x00, 0x00, 0x00, 0x00, 0x00, 
			 0x00, 0x00, 0x00, 0x00, 0x00 },    0 }, 
	/* GAMMA Control */
	{	 0xF7, 15,  /* RGAMCTL */
			{ 0x92, 0x00, 0x00, 0x26, 0x34, 
			  0x2a, 0x28, 0x2d, 0x0b, 0x04, 
			  0x01, 0x07, 0x00, 0x14, 0x14 },	0 },	
	{	 0xF8, 15,  /* RNGAMCTL */
			{ 0x40, 0x12, 0x00, 0x04, 0x0d, 
			  0x15, 0x16, 0x16, 0x28, 0x2d, 
			  0x37, 0x35, 0x03, 0x14, 0x14 },	0 },	
	{	 0xF9, 15,  /* GNGAMCTL */
			{ 0x92, 0x00, 0x00, 0x2b, 0x36, 
			  0x30, 0x2e, 0x2f, 0x0b, 0x09, 
			  0x04, 0x09, 0x00, 0x14, 0x14 },	0 },
	{	 0xFA, 15,  /* GNGAMCTL */
			{ 0x40, 0x12, 0x01 ,0x02, 0x0d, 
			  0x18, 0x1b, 0x1d, 0x21, 0x25, 
			  0x31, 0x32, 0x00, 0x14, 0x14 },	0 },	
	{	 0xFB, 15,  /* BGAMCTL */
			{ 0xaa, 0x16, 0x00, 0x08, 0x1a, 
			  0x20, 0x22, 0x24, 0x14, 0x0b, 
			  0x02, 0x07, 0x01, 0x14, 0x14 },	0 },	
	{	 0xFC, 15,  /* BNGAMCTL */
			{ 0x56, 0x2a, 0x00, 0x00, 0x06, 
	    	  0x07, 0x0b, 0x10, 0x29, 0x29, 
			  0x24, 0x1a, 0x00, 0x14, 0x14 },	0 },	
	{	 0xF3,  9,  /* PWRCTL */
			{ 0x01, 0x00, 0x26, 0x26, 0x08, 
			  0x33, 0x6d, 0x6d, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xF4,  5,  /* VCMCTL */
			{ 0x4d, 0x4d, 0x5e, 0x5e, 0x77, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 }, 	0 },	
	{	 0xF5,  6,  /* SRCCTL */
			{ 0x13, 0x11, 0x0b, 0x00, 0x00, 
			  0x1f, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 }, 	0 },	
	// sleep out
	{	 0x11,	0, 
			{ 0x00, 0x00, 0x00, 0x00, 0x00, 
	          0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },  120 },	
	// Display on
	{	 0x29,	0, 
			{ 0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00, 
			  0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
};

static struct setting_table power_off_setting_table_va[] = {
	{  0x28,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  40 },
	{  0x10,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};

#define POWER_ON_SETTINGS_VA	(int)(sizeof(power_on_setting_table_va)/sizeof(struct setting_table))
#define POWER_OFF_SETTINGS_VA	(int)(sizeof(power_off_setting_table_va)/sizeof(struct setting_table))

/* TN Panel 
 * 2011.01.19 apply new init sequence from LCD Group*/

static struct setting_table power_on_setting_table_tn[] = {

		// Level2 command access
	{	0xF0,	2,	{	0x5A, 0x5A, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{   0xF1,   2,  {   0x5A, 0x5A, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00    },  0 },

	{	0xF7,	2,	{	0x02, 0x19, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },

	// Power Setting Sequence
	{	0xF4,	11,	{	0x0B, 0x00, 0x00, 0x00, 0x22, 
						0x67, 0x04, 0x02, 0x2A, 0x50, 
						0x05, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF5,	6,	{	0x00, 0x72, 0x52, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF6,	9,	{	0x01, 0x01, 0x03, 0x00, 0x04, 
						0x0C, 0x02, 0x00, 0x07, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00 	},	0 },

	// Initializing Sequence
	{	0x35,	1,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0x36,	1,	{	0x48, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0x3A,	1,	{	0x66, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	


	{	0xF7,	4,	{	0x03, 0x19, 0x30, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	/*  Display Control */
	{	0xF2,	12,	{	0x1E, 0x97, 0x03, 0x08, 0x06, 
						0x10, 0x00, 0x19, 0x48, 0x00, 
						0x07, 0x01, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },


	// Gamma Setting Sequence
	// 2011.02.10 setting is changed for revision 3 panel.
	// 2011.02.14 vice president choice value.(GAMMA 2.8)
	// RED
	{	0xF9,	1,	{	0x04, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xFA,	16,	{	0x00, 0x0A, 0x0C, 0x0F, 0x19, 
						0x33, 0x31, 0x16, 0x19, 0x16, 
						0x1D, 0x00, 0x00, 0x00, 0x00,	
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	16,	{	0x0A, 0x00, 0x10, 0x14, 0x13, 
						0x13, 0x0A, 0x3F, 0x37, 0x21, 
						0x0A, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	// GREEN
	{	0xF9,	1,	{	0x02, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xFA,	16,	{	0x00, 0x0A, 0x0C, 0x11, 0x21, 
						0x33, 0x31, 0x16, 0x19, 0x16, 
						0x1D, 0x00, 0x00, 0x00, 0x00,	
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	16,	{	0x0A, 0x00, 0x0F, 0x17, 0x16, 
						0x18, 0x0A, 0x3F, 0x37, 0x21, 
						0x0A, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	// BLUE
	{	0xF9,	1,	{	0x01, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xFA,	16,	{	0x00, 0x0A, 0x0C, 0x10, 0x19, 
						0x33, 0x31, 0x16, 0x1A, 0x16, 
						0x1D, 0x00, 0x00, 0x00, 0x00,	
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	16,	{	0x0A, 0x00, 0x10, 0x14, 0x13, 
						0x13, 0x0A, 0x3F, 0x37, 0x21, 
						0x0A, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	


	// Level2 command blocking
	{	0xF0,	2,	{	0xA5, 0xA5, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
		/*  Sleep OUT */
	{   0x11,   0,  {   0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00    },  120 },

	{	0x29,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	40 },	
};

static struct setting_table power_off_setting_table_tn[] = {

	/*  Sleep IN */


	{ 0x10, 0,  { 0x00, 0x00, 0x00, 0x00, 0x00, 
				  0x00, 0x00, 0x00, 0x00, 0x00, 
				  0x00, 0x00, 0x00, 0x00, 0x00, 
				  0x00, 0x00, 0x00, 0x00, 0x00 }, 0 },

	{ 0x28, 0,  { 0x01, 0x00, 0x00, 0x00, 0x00, 
				  0x00, 0x00, 0x00, 0x00, 0x00, 
				  0x00, 0x00, 0x00, 0x00, 0x00, 
				  0x00, 0x00, 0x00, 0x00, 0x00 }, 40 },

};


#define POWER_ON_SETTINGS_TN   (int)(sizeof(power_on_setting_table_tn)/sizeof(struct setting_table))
#define POWER_OFF_SETTINGS_TN	(int)(sizeof(power_off_setting_table_tn)/sizeof(struct setting_table))

static int lcdc_s6d05a0_panel_off(struct platform_device *pdev);

static int spi_cs 	= 0;
static int spi_sclk = 0;
static int spi_sdi 	= 0;
static int lcd_en   = 0;
static int lcd_reset= 0;

struct s6d05a0_state_type{
	boolean disp_initialized;
	boolean display_on;
	boolean disp_powered_up;
};

#if 1// minhyodebug
static struct s6d05a0_state_type s6d05a0_state = { 1,1,1 };
#else
static struct s6d05a0_state_type s6d05a0_state = { 0 };
#endif
static struct msm_panel_common_pdata *lcdc_s6d05a0_pdata;

static void setting_table_write(struct setting_table *table)
{
	long i, j;

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
		msleep(table->wait);
}

static void spi_read_byte( char addr, unsigned int *data,int count)
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

static void spi_init(void)
{

	/* Set the output so that we dont disturb the slave device */
	gpio_set_value(spi_sclk, 0);
	gpio_set_value(spi_sdi,  0);

	/* Set the Chip Select De-asserted */
	gpio_set_value(spi_cs, 0);

}

static unsigned int determine_lcd_type(void)
{
	unsigned int data = 0;
	
	spi_read_byte(0x04, &data, 3);

	printk("%s, LCD Type :%x \n",__func__,data);
	return data;
}

static void s6d05a0_disp_powerup(void)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d05a0_state.disp_powered_up && !s6d05a0_state.display_on) {

		gpio_set_value(lcd_reset, 1);
		msleep(50);
		gpio_set_value(lcd_reset, 0);
		udelay(10); 
		gpio_set_value(lcd_reset, 1);
		msleep(10); 

	    s6d05a0_state.disp_powered_up = TRUE;
	}
}

static void s6d05a0_disp_powerdown(void)
{
	DPRINT("start %s\n", __func__);	

		/* Reset Assert */
		gpio_set_value(lcd_reset, 0);		

		/* turn off LDO */
		//TODO: turn off LDO
		//gpio_set_value(lcd_en, 0);

	    s6d05a0_state.disp_powered_up = FALSE;
}

static void s6d05a0_init(void)
{
	msleep(1);
}

static void s6d05a0_disp_on(void)
{
	int i;

	DPRINT("start %s\n", __func__);	

	if(!lcd_panel_type) {
	   	lcd_panel_type = determine_lcd_type();
	}

	if (s6d05a0_state.disp_powered_up && !s6d05a0_state.display_on) {
		s6d05a0_init();

		if(lcd_panel_type == PANEL_SHARP_VA) {
			for (i = 0; i < POWER_ON_SETTINGS_VA; i++)
				setting_table_write(&power_on_setting_table_va[i]);		

		} else if(lcd_panel_type == PANEL_GP_TN) {
			for (i = 0; i < POWER_ON_SETTINGS_TN; i++)
				setting_table_write(&power_on_setting_table_tn[i]);		
		}

		s6d05a0_state.display_on = TRUE;
		lcd_on_state_for_debug = TRUE;
	}
}

static int lcdc_s6d05a0_panel_on(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d05a0_state.disp_initialized) {
		/* Configure reset GPIO that drives DAC */
		lcdc_s6d05a0_pdata->panel_config_gpio(1);
		s6d05a0_disp_powerup();
		spi_init();
		s6d05a0_disp_on();
		s6d05a0_state.disp_initialized = TRUE;
	}

	
	return 0;
}

static int lcdc_s6d05a0_panel_off(struct platform_device *pdev)
{
	int i;

	DPRINT("start %s\n", __func__);	


	if (s6d05a0_state.disp_powered_up && s6d05a0_state.display_on) {
		if(lcd_panel_type == PANEL_SHARP_VA) {
			for (i = 0; i < POWER_OFF_SETTINGS_VA; i++)
				setting_table_write(&power_off_setting_table_va[i]);		

		} else if(lcd_panel_type == PANEL_GP_TN) {
			for (i = 0; i < POWER_OFF_SETTINGS_TN; i++)
				setting_table_write(&power_off_setting_table_tn[i]);	
			msleep(120);	
		}
	
		lcdc_s6d05a0_pdata->panel_config_gpio(0);
		s6d05a0_state.display_on = FALSE;
		lcd_on_state_for_debug = FALSE;
		s6d05a0_state.disp_initialized = FALSE;

		s6d05a0_disp_powerdown();
	}
	return 0;
}



static void lcdc_s6d05a0_set_backlight(struct msm_fb_data_type *mfd)
{	
	int bl_value = mfd->bl_level;

	printk("[BACLKIGHT] : %d\n",bl_value);
	if(board_hw_revision == 0) {
		lcdc_s6d_set_brightness_by_aat1401(bl_value);
	} else if(board_hw_revision >= 1) {
		lcdc_s6d_set_brightness_by_ktd259(bl_value);
	} else {
		printk("Unknown HW Rev!!!!\n");
		lcdc_s6d_set_brightness_by_aat1401(bl_value);
	}

}

#ifdef __LCD_CONTROL_BY_FILE__
static int s6d05a0_show_lcd_power(struct device *dev, struct device_attribute *attr, char *buf)
{
        return snprintf(buf, PAGE_SIZE, "%d\n",s6d05a0_state.disp_initialized);
}

static int s6d05a0_store_lcd_power(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
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

		if(s6d05a0_state.disp_powered_up || s6d05a0_state.display_on) {
			printk("LCD is alredy turn ON\n");
			return 0;
		}
		clk_enable(pclk);
		clk_enable(pad_pclk);

		lcdc_s6d05a0_panel_on(pdev);

		if(board_hw_revision == 0) {
			lcdc_s6d_set_brightness_by_aat1401(141);
		} else if(board_hw_revision >= 1) {
			lcdc_s6d_set_brightness_by_ktd259(141);
		} else {
			printk("Unknown HW Rev!!!!\n");
			lcdc_s6d_set_brightness_by_aat1401(141);
		}
	} else if (strnicmp(buf, "off", 3) == 0 || strnicmp(buf, "0", 1) == 0) 
	{
		if(!s6d05a0_state.disp_powered_up || !s6d05a0_state.display_on) {
			printk("LCD is already turn OFF\n");
			return 0;
		}

		if(board_hw_revision == 0) {
			lcdc_s6d_set_brightness_by_aat1401(0);
		} else if(board_hw_revision >= 1) {
			lcdc_s6d_set_brightness_by_ktd259(0);
		} else {
			printk("Unknown HW Rev!!!!\n");
			lcdc_s6d_set_brightness_by_aat1401(0);
		}

		lcdc_s6d05a0_panel_off(pdev);
		clk_disable(pclk);
		clk_disable(pad_pclk);


    }
    else 
		return -EINVAL;

    return len;
}

static DEVICE_ATTR(lcd_power, 0660,						//sm.kim: give write permission for application
                        s6d05a0_show_lcd_power,
                        s6d05a0_store_lcd_power);
#endif


static int __init s6d05a0_probe(struct platform_device *pdev)
{

	int ret = 0;

	printk("++++++%s\n", __func__);
	printk("++++++pdev->id=%d\n", pdev->id);

#ifdef __LCD_CONTROL_BY_FILE__
    ret = device_create_file(&(pdev->dev), &dev_attr_lcd_power);
    if (ret < 0)
            printk(KERN_WARNING "s6d05a0: failed to add entries\n");
#endif

	if (pdev->id == 0)
	{
		lcdc_s6d05a0_pdata = pdev->dev.platform_data;    // lcdc_s6d05a0_panel_data in board-msm7x27.c

		return 0;
	}

	/* Setting the Default GPIO's */
	spi_sclk = *(lcdc_s6d05a0_pdata->gpio_num);
	spi_cs   = *(lcdc_s6d05a0_pdata->gpio_num + 1);
	spi_sdi  = *(lcdc_s6d05a0_pdata->gpio_num + 2);
	lcd_en   = *(lcdc_s6d05a0_pdata->gpio_num + 3);
	lcd_reset= *(lcdc_s6d05a0_pdata->gpio_num + 4);

	if(!spi_sclk || !spi_cs || !spi_sdi || !lcd_en || !lcd_reset) {
			printk("[LCD] SPI Init Error. %d,%d,%d,%d,%d\n",spi_sclk,spi_cs,spi_sdi,lcd_en,lcd_reset);

			spi_cs = 131;
			spi_sclk = 132;
			spi_sdi = 103;
			lcd_en = 122;
			lcd_reset = 101;

			printk("[LCD] apply GrandTF MSM7227's spi value\n");
	
	}

	printk("------%s\n", __func__);

	
	msm_fb_add_device(pdev);

	return 0;
}

static void s6d05a0_shutdown(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

	if(board_hw_revision == 0) {
		lcdc_s6d_set_brightness_by_aat1401(0);
	} else if(board_hw_revision >= 1) {
		lcdc_s6d_set_brightness_by_ktd259(0);
	} else {
		printk("Unknown HW Rev!!!!\n");
		lcdc_s6d_set_brightness_by_aat1401(0);
	}

	lcdc_s6d05a0_panel_off(pdev);
}

static struct platform_driver this_driver = {
	.probe  = s6d05a0_probe,
	.shutdown	= s6d05a0_shutdown,
	.driver = {
		.name   = "lcdc_s6d05a0_wqvga",
	},
};

static struct msm_fb_panel_data s6d05a0_panel_data = {
	.on = lcdc_s6d05a0_panel_on,
	.off = lcdc_s6d05a0_panel_off,
	.set_backlight = lcdc_s6d05a0_set_backlight,
};

static struct platform_device this_device = {
	.name   = "lcdc_panel",
	.id	= 1,
	.dev	= {
		.platform_data = &s6d05a0_panel_data,
	}
};

//
//if you change screen resolution, you should modify same information in hardware/msm7k/libgralloc-qsd8k/framebuffer.cpp
//

// Bennett
#define LCDC_FB_XRES	320
#define LCDC_FB_YRES 	240
/*  VA Panel Porch Value */
#define LCDC_HBP		8	// 16 
#define LCDC_HPW		12	// 24 
#define LCDC_HFP		8	// 16 
#define LCDC_VBP		8	// 16 
#define LCDC_VPW		12	// 24 
#define LCDC_VFP		8	// 16

/*  TN Panel Porch Value */
/*  respec dot clock is 83177550 */
#define LCDC_TN_HPW		10	/* Hsync Pulse Width */ 
#define LCDC_TN_HBP		13	/* Hsync Back  Porch */
#define LCDC_TN_HFP		13	/* Hsync Front Porch */
#define LCDC_TN_VPW		4	/* Vsync Pulse Width */
#define LCDC_TN_VBP		4	/* Vsync Back  Porch */
#define LCDC_TN_VFP		6	/* Vsync Front Porch */

static int __init lcdc_s6d05a0_panel_init(void)
{
	int ret;
	struct msm_panel_info *pinfo;

	printk("++++++%s\n", __func__);

#ifdef CONFIG_FB_MSM_TRY_MDDI_CATCH_LCDC_PRISM
	if (msm_fb_detect_client("lcdc_s6d05a0_wqvga"))
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
	if(!lcd_panel_type) {
		spi_cs = 131;
		spi_sclk = 132;
		spi_sdi = 103;
		lcd_en = 122;
		lcd_reset = 101;

		spi_init();
	   	lcd_panel_type = determine_lcd_type();
	}

	pinfo = &s6d05a0_panel_data.panel_info;
	pinfo->xres = LCDC_FB_XRES;
	pinfo->yres = LCDC_FB_YRES;
	pinfo->height = 70; // minhyo-rgb888
 	pinfo->width = 42;  // minhyo-rgb888
	pinfo->type = LCDC_PANEL;
	pinfo->pdest = DISPLAY_1;
	pinfo->wait_cycle = 0;
	pinfo->fb_num = 2;
	pinfo->bl_max = 255;
	pinfo->bl_min = 1;

	if(lcd_panel_type == PANEL_GP_TN) {
		printk("LCD Type. type:%x\n",lcd_panel_type); 
		pinfo->bpp = 18;
		pinfo->lcdc.h_back_porch = LCDC_TN_HBP;
		pinfo->lcdc.h_front_porch = LCDC_TN_HFP;
		pinfo->lcdc.h_pulse_width = LCDC_TN_HPW;
		pinfo->lcdc.v_back_porch = LCDC_TN_VBP;
		pinfo->lcdc.v_front_porch = LCDC_TN_VFP;
		pinfo->lcdc.v_pulse_width = LCDC_TN_VPW;
		pinfo->clk_rate = (8190 * 1000); 

		printk("###################################\n");
		printk("# PORCH Tunning (TN Panel)        #\n");
		printk("###################################\n");
		printk("Hsync Back  Portch : %d\n",pinfo->lcdc.h_back_porch);
		printk("Hsync Front Portch : %d\n",pinfo->lcdc.h_front_porch);
		printk("Hsync Pulse Width  : %d\n",pinfo->lcdc.h_pulse_width);
		printk("Vsync Back  Portch : %d\n",pinfo->lcdc.v_back_porch);
		printk("Vsync Front Portch : %d\n",pinfo->lcdc.v_front_porch);
		printk("Vsync Pulse Width  : %d\n",pinfo->lcdc.v_pulse_width);
		printk("Bit per PIXEL      : %d\n",pinfo->bpp);


	} else if(lcd_panel_type == PANEL_SHARP_VA) {
		printk("LCD Type. type:%x\n",lcd_panel_type); 
		pinfo->bpp = 24;
		pinfo->lcdc.h_back_porch = LCDC_HBP;
		pinfo->lcdc.h_front_porch = LCDC_HFP;
		pinfo->lcdc.h_pulse_width = LCDC_HPW;
		pinfo->lcdc.v_back_porch = LCDC_VBP;
		pinfo->lcdc.v_front_porch = LCDC_VFP;
		pinfo->lcdc.v_pulse_width = LCDC_VPW;
		pinfo->clk_rate = (9388 * 1000); // minhyo0609 8192000;

	} else  {
		printk("Cannot determine LCD Type. type:%x\n",lcd_panel_type); 
		printk("Defualt is VA\n");
		pinfo->bpp = 24;
		pinfo->lcdc.h_back_porch = LCDC_HBP;
		pinfo->lcdc.h_front_porch = LCDC_HFP;
		pinfo->lcdc.h_pulse_width = LCDC_HPW;
		pinfo->lcdc.v_back_porch = LCDC_VBP;
		pinfo->lcdc.v_front_porch = LCDC_VFP;
		pinfo->lcdc.v_pulse_width = LCDC_VPW;
		pinfo->clk_rate = (9388 * 1000); // minhyo0609 8192000;
		lcd_panel_type = PANEL_SHARP_VA;
	}
#if 0
	pinfo->lcdc.h_back_porch = LCDC_HBP;
	pinfo->lcdc.h_front_porch = LCDC_HFP;
	pinfo->lcdc.h_pulse_width = LCDC_HPW;
	pinfo->lcdc.v_back_porch = LCDC_VBP;
	pinfo->lcdc.v_front_porch = LCDC_VFP;
	pinfo->lcdc.v_pulse_width = LCDC_VPW;
#endif
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

module_init(lcdc_s6d05a0_panel_init);
