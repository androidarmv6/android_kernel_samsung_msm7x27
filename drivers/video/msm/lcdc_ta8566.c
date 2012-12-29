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
#include "msm_fb.h"

#include <linux/module.h>

#define LCDC_DEBUG

#ifdef LCDC_DEBUG
#define DPRINT(x...)	printk("ta8566 " x)
#else
#define DPRINT(x...)	
#endif

#define __LCD_CONTROL_BY_FILE__

#define GPIO_BL_CTRL	26
#define GPIO_LCD_DET	94

/*
 * Serial Interface
 */
#define LCD_CSX_HIGH	gpio_set_value(spi_cs, 1);
#define LCD_CSX_LOW		gpio_set_value(spi_cs, 0);

#define LCD_SCL_HIGH	gpio_set_value(spi_sclk, 1);
#define LCD_SCL_LOW		gpio_set_value(spi_sclk, 0);

#define LCD_SDI_HIGH	gpio_set_value(spi_sdi, 1);
#define LCD_SDI_LOW		gpio_set_value(spi_sdi, 0);

#define DEFAULT_USLEEP	1	

// #define LCD_DET_ENABLE   // minhyodebug

#ifdef LCD_DET_ENABLE
#include <linux/irq.h>

struct ta8566_lcd_det_data {
	int             irq;
	struct work_struct work_lcd_det;  /* for lcd_det */
};

struct ta8566_lcd_det_data 	lcd_det_data;
struct workqueue_struct 	*lcd_det_wq;
struct platform_device 		*plcdc_ta8566_panel_device;
#endif

extern int board_hw_revision;

int lcd_on_state_for_debug;
EXPORT_SYMBOL(lcd_on_state_for_debug);

struct setting_table {
	unsigned char command;	
	unsigned char parameters;
	unsigned char parameter[31]; // CALLISTO-REV00A, minhyo [15];
	long wait;
};

/* from Rev04 */
static struct setting_table power_on_setting_table[] = {
// DOTCLK 9.388MHz, 
	// power setting sequence
	{	 0xBA,	2, { 0x85, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xB6,	3, { 0x26, 0x05, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xB7,	3, { 0x7F, 0x44, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xB8,	4, { 0x68, 0x60, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Display  Control Setting
	{	 0xB0,	4, { 0x03 /* data read with falling-edge of DOTCLK , DATA-EN : active high, VSYNC : active low, HSYNC : active low */, 0x90/*0x80 internal clock */, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	  0 },
	{	 0xB1,	2, { 0x01, 0x90/* 240 x 400 */, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xB2,	9, { 0x42, 0x3E, 0x0F, 0x11, 0x40, 0x1C, 0x55, 0x0E, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xB3,	4, { 0xB6, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Gamma Setting
	{	 0xC0, 31, { 0x00, 0x31, 0x1E, 0x1E, 0x1E, 0x21, 0x27, 0x25, 0x14, 0x13, 0x0B, 0x0C, 0x04, 0x04, 0x04, 0x0E, 0x3F, 0x3B, 0x3B, 0x3B, 0x2D, 0x22, 0x1C, 0x0D, 0x10, 0x18, 0x1E, 0x21, 0x21, 0x21, 0x00 },	0 },	
	{	 0xC1, 31, { 0x00, 0x26, 0x2B, 0x2B, 0x2B, 0x2E, 0x34, 0x32, 0x21, 0x1F, 0x18, 0x19, 0x14, 0x14, 0x14, 0x19, 0x3F, 0x2B, 0x2B, 0x2B, 0x20, 0x15, 0x10, 0x01, 0x04, 0x0A, 0x11, 0x14, 0x14, 0x14, 0x00 },	0 },	
	{	 0xC2, 31, { 0x21, 0x2E, 0x1B, 0x1B, 0x1B, 0x1C, 0x24, 0x21, 0x14, 0x17, 0x13, 0x1A, 0x12, 0x12, 0x12, 0x31, 0x21, 0x2D, 0x2D, 0x2D, 0x20, 0x1A, 0x18, 0x0D, 0x14, 0x1C, 0x23, 0x24, 0x24, 0x24, 0x00 },	0 },	
	// Extend Enable Reg	
	{	 0xBA,	2, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Sleep out
	{	 0x11,	0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  120 },
	// Set Display mode
	{	 0x2A,	4, { 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0x2B,	4, { 0x00, 0x00, 0x01, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },		
	{	 0x36,	1, { 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0x3A,	1, { 0x70 /* 16M Color */, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	20 },
	// Display on
	{	 0x29,	0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   40 },
	// Memory Write
	{	 0x2C,	0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
};

/* for Rev00 ~ Rev03 */
static struct setting_table power_on_setting_table_old[] = {
// DOTCLK 9.388MHz, 
	// power setting sequence
	{	 0xBA,	2, { 0x85, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xC3,	1, { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xF7,	3, { 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xC3,	1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xB6,	3, { 0x26, 0x05, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xB7,	3, { 0x7F, 0x44, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xB8,	4, { 0x68, 0x62, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Display  Control Setting
	{	 0xB0,	4, { 0x03 /* data read with falling-edge of DOTCLK , DATA-EN : active high, VSYNC : active low, HSYNC : active low */, 0x90/*0x80 internal clock */, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	  0 },
	{	 0xB1,	2, { 0x01, 0x90/* 240 x 400 */, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0xB2,	9, { 0x42, 0x3E, 0x0F, 0x11, 0x40, 0x1C, 0x55, 0x0E, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0xB3,	4, { 0xB6, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Gamma Setting
	{	 0xC0, 31, { 0x00, 0x31, 0x1E, 0x1E, 0x1E, 0x21, 0x27, 0x25, 0x14, 0x13, 0x0B, 0x0C, 0x04, 0x04, 0x04, 0x0E, 0x3F, 0x3B, 0x3B, 0x3B, 0x2D, 0x22, 0x1C, 0x0D, 0x10, 0x18, 0x1E, 0x21, 0x21, 0x21, 0x00 },	0 },	
	{	 0xC1, 31, { 0x00, 0x26, 0x2B, 0x2B, 0x2B, 0x2E, 0x34, 0x32, 0x21, 0x1F, 0x18, 0x19, 0x14, 0x14, 0x14, 0x19, 0x3F, 0x2B, 0x2B, 0x2B, 0x20, 0x15, 0x10, 0x01, 0x04, 0x0A, 0x11, 0x14, 0x14, 0x14, 0x00 },	0 },	
	{	 0xC2, 31, { 0x21, 0x2E, 0x1B, 0x1B, 0x1B, 0x1C, 0x24, 0x21, 0x14, 0x17, 0x13, 0x1A, 0x12, 0x12, 0x12, 0x31, 0x21, 0x2D, 0x2D, 0x2D, 0x20, 0x1A, 0x18, 0x0D, 0x14, 0x1C, 0x23, 0x24, 0x24, 0x24, 0x00 },	0 },	
	// Extend Enable Reg	
	{	 0xBA,	2, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Sleep out
	{	 0x11,	0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  120 },
	// Set Display mode
	{	 0x2A,	4, { 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{	 0x2B,	4, { 0x00, 0x00, 0x01, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },		
	{	 0x36,	1, { 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{	 0x3A,	1, { 0x70 /* 16M Color */, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	20 },
	// Display on
	{	 0x29,	0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   40 },
	// Memory Write
	{	 0x2C,	0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
};

static struct setting_table power_off_setting_table[] = {
	{  0x28,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  40 },
	{  0x10,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};

#define POWER_ON_SETTINGS	(int)(sizeof(power_on_setting_table)/sizeof(struct setting_table))
#define POWER_ON_SETTINGS_OLD	(int)(sizeof(power_on_setting_table_old)/sizeof(struct setting_table))
#define POWER_OFF_SETTINGS	(int)(sizeof(power_off_setting_table)/sizeof(struct setting_table))

static int lcdc_ta8566_panel_off(struct platform_device *pdev);

static int lcd_brightness = -1;

static int spi_cs;
static int spi_sclk;
static int spi_sdi;
static int lcd_en;
static int lcd_reset;

#if 0
static unsigned char bit_shift[8] = { (1 << 7),	/* MSB */
	(1 << 6),
	(1 << 5),
	(1 << 4),
	(1 << 3),
	(1 << 2),
	(1 << 1),
	(1 << 0)		               /* LSB */
};
#endif

static int delayed_backlight_value = -1;
static void lcdc_ta8566_set_brightness_in_blu(int level);

struct ta8566_state_type{
	boolean disp_initialized;
	boolean display_on;
	boolean disp_powered_up;
};

#if 0 // minhyodebug
static struct ta8566_state_type ta8566_state = { 1,1,1 };
#else
static struct ta8566_state_type ta8566_state = { 0 };
#endif
static struct msm_panel_common_pdata *lcdc_ta8566_pdata;

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

static void spi_init(void)
{
	/* Setting the Default GPIO's */
	spi_sclk = *(lcdc_ta8566_pdata->gpio_num);
	spi_cs   = *(lcdc_ta8566_pdata->gpio_num + 1);
	spi_sdi  = *(lcdc_ta8566_pdata->gpio_num + 2);
	lcd_en   = *(lcdc_ta8566_pdata->gpio_num + 3);
	lcd_reset= *(lcdc_ta8566_pdata->gpio_num + 4);
//	spi_sdo  = *(lcdc_ta8566_pdata->gpio_num + 3);

	/* Set the output so that we dont disturb the slave device */
	gpio_set_value(spi_sclk, 0);
	gpio_set_value(spi_sdi, 0);

	/* Set the Chip Select De-asserted */
	gpio_set_value(spi_cs, 0);

}

static void ta8566_disp_powerup(void)
{
	DPRINT("start %s\n", __func__);	

	if (!ta8566_state.disp_powered_up && !ta8566_state.display_on) {
		/* Reset the hardware first */
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);

		//LCD_EN_HI
		//gpio_set_value(lcd_en, 1);
		//TODO: turn on ldo
		udelay(100);
		
		//LCD_RESET_N_LO
		gpio_set_value(lcd_reset, 0);
		udelay(15); // minhyodebug msleep(1);	
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);
		usleep(20); // minhyodebug msleep(10);

		
		/* Include DAC power up implementation here */
		
	    ta8566_state.disp_powered_up = TRUE;
	}
}

static void ta8566_disp_powerdown(void)
{
	DPRINT("start %s\n", __func__);	

		/* Reset Assert */
		gpio_set_value(lcd_reset, 0);		

		/* turn off LDO */
		//TODO: turn off LDO
		//gpio_set_value(lcd_en, 0);

	    ta8566_state.disp_powered_up = FALSE;
}

static void ta8566_init(void)
{
	msleep(1);
}

static void ta8566_disp_on(void)
{
	int i;

	DPRINT("start %s\n", __func__);	

	if (ta8566_state.disp_powered_up && !ta8566_state.display_on) {
		ta8566_init();
		msleep(10);

		if(board_hw_revision >= 4)
		{
			for (i = 0; i < POWER_ON_SETTINGS; i++)
				setting_table_write(&power_on_setting_table[i]);		
		}
		else
		{
			for (i = 0; i < POWER_ON_SETTINGS_OLD; i++)
				setting_table_write(&power_on_setting_table_old[i]);
		}

		msleep(1);
		ta8566_state.display_on = TRUE;
		lcd_on_state_for_debug = TRUE;
	}
}


// 20100915
int lcdc_ta8566_panel_poweron(void)
{
	DPRINT("[%s]\n", __func__); 

	if (!ta8566_state.disp_initialized) {
		/* Configure reset GPIO that drives DAC */
		lcdc_ta8566_pdata->panel_config_gpio(1);
		ta8566_disp_powerup();
		spi_init();	/* LCD needs SPI */
		ta8566_disp_on();
		ta8566_state.disp_initialized = TRUE;
	}

#ifdef LCD_DET_ENABLE
	/* enable INT */
	enable_irq(lcd_det_data.irq);	
#endif
	
	// TEMP CODE for BLU
	//gpio_set_value(GPIO_BL_CTRL, 1);
	//gpio_set_value(91, 1); 
	
	return 0;
}

static int lcdc_ta8566_panel_on(struct platform_device *pdev)
{
	lcdc_ta8566_panel_poweron();
	
	return 0;
}

void lcdc_ta8566_panel_poweroff(void)
{
	int i;

	DPRINT("[%s]\n", __func__); 

#ifdef LCD_DET_ENABLE
	disable_irq(lcd_det_data.irq);
#endif

	if (ta8566_state.disp_powered_up && ta8566_state.display_on) {
		
		for (i = 0; i < POWER_OFF_SETTINGS; i++)
			setting_table_write(&power_off_setting_table[i]);	
		
		lcdc_ta8566_pdata->panel_config_gpio(0);
		ta8566_state.display_on = FALSE;
		lcd_on_state_for_debug = FALSE;
		ta8566_state.disp_initialized = FALSE;
		ta8566_disp_powerdown();
	}
}


static int lcdc_ta8566_panel_off(struct platform_device *pdev)
{
	lcdc_ta8566_panel_poweroff();
	return 0;
}

#if 1 // 20100915
extern void lcdc_ta8566_config_gpios(int enable);
extern int gpio_array_num[];

void early_spi_init(void)
{
	printk("[%s]================SPI_INIT \n", __func__); // minhyodebug

	/* Setting the Default GPIO's */
	spi_sclk = *(gpio_array_num);
	spi_cs   = *(gpio_array_num + 1);
	spi_sdi  = *(gpio_array_num + 2);
	lcd_en   = *(gpio_array_num + 3);
	lcd_reset= *(gpio_array_num + 4);
//	spi_sdo  = *(gpio_array_num + 3);

	/* Set the output so that we dont disturb the slave device */
	gpio_set_value(spi_sclk, 0);
	gpio_set_value(spi_sdi, 0);

	/* Set the Chip Select De-asserted */
	gpio_set_value(spi_cs, 0);

}

void spi_gpio_init(void)
{
	#if 1 
	 lcdc_ta8566_config_gpios(1); 
	#else
		GPIO_CFG(GPIO_OUT_132, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),
		GPIO_CFG(GPIO_OUT_131, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),
		GPIO_CFG(GPIO_OUT_103, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),
	//	GPIO_CFG(GPIO_OUT_122, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),
		GPIO_CFG(GPIO_OUT_101,	0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),

	/* gpio config */
	config = GPIO_CFG(GPIO_OUT_132, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA);
	err = gpio_tlmm_config(config, GPIO_ENABLE);
	if (err) 
		printk(KERN_ERR "%s: gpio_tlmm_config(%d)=%d\n", __func__, (int)GPIO_LCD_DET, err);

	config = GPIO_CFG(GPIO_OUT_131, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA);
	err = gpio_tlmm_config(config, GPIO_ENABLE);
	if (err) 
		printk(KERN_ERR "%s: gpio_tlmm_config(%d)=%d\n", __func__, (int)GPIO_LCD_DET, err);

	config = GPIO_CFG(GPIO_OUT_103, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA);
	err = gpio_tlmm_config(config, GPIO_ENABLE);
	if (err) 
		printk(KERN_ERR "%s: gpio_tlmm_config(%d)=%d\n", __func__, (int)GPIO_LCD_DET, err);

	config = GPIO_CFG(GPIO_OUT_101, 0, GPIO_INPUT, GPIO_NO_PULL, GPIO_2MA);
	err = gpio_tlmm_config(config, GPIO_ENABLE);
	if (err) 
		printk(KERN_ERR "%s: gpio_tlmm_config(%d)=%d\n", __func__, (int)GPIO_LCD_DET, err);
	#endif
}

int lcdc_ta8566_ldi_off(void)
{
	int i;

	DPRINT("start %s\n", __func__);	

	spi_gpio_init();
	early_spi_init();
	msleep(2);
	for (i = 0; i < POWER_OFF_SETTINGS; i++)
		setting_table_write(&power_off_setting_table[i]);	
	return 0;
}
#endif


#if 1

// brightness tuning
#define MAX_BRIGHTNESS_LEVEL 		255
#define DFT_BRIGHTNESS_LEVEL 		137 // 140  // When we are booting, Application set brightness-leverl 140, Brightness-level 140 is mapped Backlight-level 34. 
#define LOW_BRIGHTNESS_LEVEL 		30

#define MAX_BACKLIGHT_VALUE2 		61
#define MAX_BACKLIGHT_VALUE 		58
#define LOW_BACKLIGHT_VALUE 		12 
#define DIM_BACKLIGHT_VALUE 		7 
#define DFT_BACKLIGHT_VALUE			( (DFT_BRIGHTNESS_LEVEL - LOW_BRIGHTNESS_LEVEL) * (MAX_BACKLIGHT_VALUE-LOW_BACKLIGHT_VALUE) / (MAX_BRIGHTNESS_LEVEL-LOW_BRIGHTNESS_LEVEL) + LOW_BACKLIGHT_VALUE )
#define MAX_BRIGHTNESS_IN_BLU		64 // backlight-IC MAX VALUE

static DEFINE_SPINLOCK(bl_ctrl_lock);
static DEFINE_SPINLOCK(bl_ctrl_irq_lock);


static void lcdc_ta8566_set_brightness_in_blu(int level)
{
	unsigned long irqflags;
	int tune_level = level;
	int pulse;

//	printk("================minhyodebug: lcdc_ta8566_set_brightness_in_blu level=%d\n",level);
	// LCD should be turned on prior to backlight
	if(ta8566_state.disp_initialized == FALSE && tune_level > 0)
	{
		//DPRINT("skip bl:%d\n", tune_level);	
		delayed_backlight_value = tune_level;
//		printk("================minhyodebug: lcdc_ta8566_set_brightness_in_blu A\n");
		return;
	}
	else
	{
		//DPRINT("set bl:%d\n", tune_level);	
		delayed_backlight_value = -1;
	}

	//sm.kim: 20100331
	// when LCD is absent, don't turn on BLU
	// over current may distroy inductor element
#if 0//1
	if(gpio_get_value(GPIO_LCD_DET) == 1 && tune_level > 0)
		{
		DPRINT("LCD may be absent. skip bl.\n");
		return;
		}
#endif

	//TODO: lock
	spin_lock(&bl_ctrl_lock);

	if (tune_level <= 0) 
	{
		/* keep back light OFF */
		gpio_set_value(GPIO_BL_CTRL, 0);
		mdelay(3);		//guaranteed shutdown
		lcd_brightness = tune_level;
	} 
	else 
	{
		/* keep back light ON */
		if(unlikely(lcd_brightness < 0))
		{
			// first time
			int val = gpio_get_value(GPIO_BL_CTRL);
			//printk("================minhyodebug: lcdc_ta8566_set_brightness_in_blu val=%d\n", val);
			if(val)
			{
				lcd_brightness = 0;
				gpio_set_value(GPIO_BL_CTRL, 0);
				mdelay(4); // minhyodebug0811 3);		//guaranteed shutdown
			}
		}

		if(!lcd_brightness)
		{
			//printk("================minhyodebug: lcdc_ta8566_set_brightness_in_blu B\n");
			gpio_set_value(GPIO_BL_CTRL, 1);
			udelay(3); 
			lcd_brightness = MAX_BRIGHTNESS_IN_BLU;
		}
			
		pulse = (lcd_brightness - tune_level + MAX_BRIGHTNESS_IN_BLU) % MAX_BRIGHTNESS_IN_BLU;

		spin_lock_irqsave(&bl_ctrl_irq_lock, irqflags);

		for(; pulse>0; pulse--)
		{
		//	printk("pulse # %d\n", pulse);
			gpio_set_value(GPIO_BL_CTRL, 0);
			udelay(3);
			gpio_set_value(GPIO_BL_CTRL, 1);
			udelay(3);
		}
				
		spin_unlock_irqrestore(&bl_ctrl_irq_lock, irqflags);
		lcd_brightness = tune_level;
	
		}

//	printk("================minhyodebug: lcdc_ta8566_set_brightness_in_blu Z\n");
	
	//TODO: unlock
	spin_unlock(&bl_ctrl_lock);

}

extern int tsp_off;
extern void tsp_recover(void);
 
int tsp_recover_flg = 0;
EXPORT_SYMBOL(tsp_recover_flg);

static void lcdc_ta8566_set_backlight(struct msm_fb_data_type *mfd)
{	
	int bl_level = mfd->bl_level;
	int tune_level;


	// brightness tuning
	if(bl_level > DFT_BRIGHTNESS_LEVEL)
	{
		tune_level = (bl_level - LOW_BRIGHTNESS_LEVEL) * (MAX_BACKLIGHT_VALUE2-LOW_BACKLIGHT_VALUE) / (MAX_BRIGHTNESS_LEVEL-LOW_BRIGHTNESS_LEVEL) + LOW_BACKLIGHT_VALUE;
		if(tune_level < DFT_BACKLIGHT_VALUE)
			tune_level = DFT_BACKLIGHT_VALUE;
	}
	else if(bl_level >= LOW_BRIGHTNESS_LEVEL)
		tune_level = (bl_level - LOW_BRIGHTNESS_LEVEL) * (MAX_BACKLIGHT_VALUE-LOW_BACKLIGHT_VALUE) / (MAX_BRIGHTNESS_LEVEL-LOW_BRIGHTNESS_LEVEL) + LOW_BACKLIGHT_VALUE;
	else if(bl_level > 0)
		tune_level = DIM_BACKLIGHT_VALUE;
	else
		tune_level = bl_level;

	DPRINT("%s:%d,%d\n", __func__, bl_level, tune_level);	

	if (tune_level && tsp_off)
	{
		printk("[HSIL] tsp will be recover\n");
		tsp_off = 0;
		tsp_recover();
		tsp_recover_flg = 1;
	}
	// turn on lcd if needed
#ifdef __LCD_ON_EARLY__
	if(tune_level > 0)
		{
		if(!ta8566_state.disp_powered_up)
			ta8566_disp_powerup();
		if(!ta8566_state.display_on)
			ta8566_disp_on();
		}
#endif

	lcdc_ta8566_set_brightness_in_blu(tune_level);
}
#endif


#ifdef __LCD_CONTROL_BY_FILE__
static int s3cfb_sysfs_show_lcd_power(struct device *dev, struct device_attribute *attr, char *buf)
{
        return snprintf(buf, PAGE_SIZE, "%d\n", ta8566_state.disp_initialized);
}

static int s3cfb_sysfs_store_lcd_power(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct platform_device* pdev;
	
    if (len < 1)
        return -EINVAL;

	pdev = container_of(dev, struct platform_device, dev);

    if (strnicmp(buf, "on", 2) == 0 || strnicmp(buf, "1", 1) == 0)
    	{
		lcdc_ta8566_panel_on(pdev);
    	lcdc_ta8566_set_brightness_in_blu(15);
    	}
    else if (strnicmp(buf, "off", 3) == 0 || strnicmp(buf, "0", 1) == 0)
    	{
    	lcdc_ta8566_set_brightness_in_blu(0);
		lcdc_ta8566_panel_off(pdev);
    	}
    else
            return -EINVAL;

    return len;
}

static DEVICE_ATTR(lcd_power, 0660,						//sm.kim: give write permission for application
                        s3cfb_sysfs_show_lcd_power,
                        s3cfb_sysfs_store_lcd_power);
#endif

#ifdef LCD_DET_ENABLE // minhyo0614

static irqreturn_t lcd_det_irq_handler(int irq, void *dev_id)
{
	struct ta8566_lcd_det_data *lcd_det = dev_id;

	printk("[LCD] lcd_det->irq = %d\n",lcd_det->irq);

	if(lcd_det->irq !=-1)
	{
		disable_irq(lcd_det->irq);
		printk("[LCD] disable_irq \n");

		queue_work(lcd_det_wq, &lcd_det->work_lcd_det);

	}
	
	printk("[LCD] IRQ_HANDLED \n");

	return IRQ_HANDLED;
}

static void lcd_det_work_func(struct work_struct *work)
{
	/* LCD init */
	lcdc_ta8566_panel_off(plcdc_ta8566_panel_device);
	msleep(2);
	lcdc_ta8566_panel_on(plcdc_ta8566_panel_device);

	/* enable INT */
//	enable_irq(lcd_det->irq);
}

#endif

static int __init ta8566_probe(struct platform_device *pdev)
{
	int ret;
	
	printk("++++++%s\n", __func__);
	printk("++++++pdev->id=%d\n", pdev->id);


#ifdef __LCD_CONTROL_BY_FILE__
    ret = device_create_file(&(pdev->dev), &dev_attr_lcd_power);
    if (ret < 0)
            printk(KERN_WARNING "ta8566: failed to add entries\n");
#endif

	if (pdev->id == 0)
	{
		lcdc_ta8566_pdata = pdev->dev.platform_data;    // lcdc_ta8566_panel_data in board-msm7x27.c

		#ifdef LCD_DET_ENABLE
		{ 
			int config, irq, err;

			plcdc_ta8566_panel_device = pdev;

			/* work queue setting */
			lcd_det_wq= create_singlethread_workqueue("lcd_det_wq");
			if (!lcd_det_wq)
				return -ENOMEM;
			INIT_WORK(&lcd_det_data.work_lcd_det, lcd_det_work_func);
			printk("Workqueue Settings complete\n");

			/* gpio config */
			config = GPIO_CFG(GPIO_LCD_DET, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA);
			err = gpio_tlmm_config(config, GPIO_CFG_ENABLE);
			if (err) 
				printk(KERN_ERR "%s: gpio_tlmm_config(%d)=%d\n", __func__, (int)GPIO_LCD_DET, err);
			
			/* INT setting */
			irq = gpio_to_irq(GPIO_LCD_DET);
			lcd_det_data.irq = -1;
			set_irq_type(irq, IRQ_TYPE_EDGE_RISING);
			err = request_irq(irq, lcd_det_irq_handler, IRQF_DISABLED, "lcd_det_int", &lcd_det_data);
			if (err)
			{
				printk("%s: request_irq failed for lcd_det\n", __func__);
				return 0;
			}
			lcd_det_data.irq = irq;
			printk("INT Settings complete\n");
		}
		#endif
		
		return 0;
	}

	printk("------%s\n", __func__);

	
	msm_fb_add_device(pdev);

	return 0;
}

static void ta8566_shutdown(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

   	lcdc_ta8566_set_brightness_in_blu(0);
	lcdc_ta8566_panel_off(pdev);
}

static struct platform_driver this_driver = {
	.probe  = ta8566_probe,
	.shutdown	= ta8566_shutdown,
	.driver = {
		.name   = "lcdc_ta8566_wqvga",
	},
};

static struct msm_fb_panel_data ta8566_panel_data = {
//	.on = NULL, // 20100915 lcdc_ta8566_panel_on,
//	.off = NULL, // 20100915 lcdc_ta8566_panel_off,
	.on = lcdc_ta8566_panel_on,
	.off = lcdc_ta8566_panel_off,
	.set_backlight = lcdc_ta8566_set_backlight,
};

static struct platform_device this_device = {
	.name   = "lcdc_panel",
	.id	= 1,
	.dev	= {
		.platform_data = &ta8566_panel_data,
	}
};

//
//if you change screen resolution, you should modify same information in hardware/msm7k/libgralloc-qsd8k/framebuffer.cpp
//

#define LCDC_FB_XRES	240
#define LCDC_FB_YRES	400
#if 1 // 9.388Mhz
#define LCDC_HBP		12 
#define LCDC_HPW		4 
#define LCDC_HFP		12 
#define LCDC_VBP		4 
#define LCDC_VPW		4 
#define LCDC_VFP		4 
#else // 8.19Mhz
#define LCDC_HBP		2 // minhyo0519 24
#define LCDC_HPW		2 // minhyo0519 12
#define LCDC_HFP		2 // minhyo0519 8
#define LCDC_VBP		2 // minhyo0519 8 // 20 // minhyo 8
#define LCDC_VPW		1 // minhyo0519 2 // 16 // minhyo 2
#define LCDC_VFP		3 // minhyo0519 8 // 24 // minhyo 8
#endif

static int __init lcdc_ta8566_panel_init(void)
{
	int ret;
	struct msm_panel_info *pinfo;

	printk("++++++%s\n", __func__);

#ifdef CONFIG_FB_MSM_TRY_MDDI_CATCH_LCDC_PRISM
	if (msm_fb_detect_client("lcdc_ta8566_wqvga"))
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

	pinfo = &ta8566_panel_data.panel_info;
	pinfo->xres = LCDC_FB_XRES;
	pinfo->yres = LCDC_FB_YRES;
	pinfo->height = 70; // minhyo-rgb888
	pinfo->width = 42;  // minhyo-rgb888
	pinfo->type = LCDC_PANEL;
	pinfo->pdest = DISPLAY_1;
	pinfo->wait_cycle = 0;
	pinfo->bpp = 24;
	pinfo->fb_num = 2;
	pinfo->clk_rate = (9388 * 1000); // minhyo0609 8192000;
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

module_init(lcdc_ta8566_panel_init);
