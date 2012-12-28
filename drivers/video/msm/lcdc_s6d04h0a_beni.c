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
#include "lcdc_s6d_backlight.h"

#include <linux/module.h>


#define LCDC_DEBUG

#ifdef LCDC_DEBUG
#define DPRINT(x...)	printk("s6d04h0a " x)
#else
#define DPRINT(x...)	
#endif

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

int lcd_on_state_for_debug;
EXPORT_SYMBOL(lcd_on_state_for_debug);


/*  added for TN LCD Backlight  */
static DECLARE_MUTEX(backlight_sem);

struct setting_table {
	unsigned char command;	
	unsigned char parameters;
	unsigned char parameter[31]; // 31 > 90 > 45
	long wait;
};


extern int board_hw_revision;

static struct setting_table power_on_setting_table[] = {
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
	{	0xF4,	11,	{	0x0B, 0x00, 0x00, 0x00, 0x22, 
						0x67, 0x04, 0x02, 0x2A, 0x75, 
						0x05, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF5,	6,	{	0x00, 0x6B, 0x5A, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xF6,	9,	{	0x01, 0x01, 0x07, 0x00, 0x02, 
						0x0C, 0x02, 0x08, 0x07, 0x00, 
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

	{	0xF2,	12,	{	0x28, 0x66, 0x03, 0x08, 0x08, 
						0x00, 0x00, 0x1D, 0x48, 0x04, 
						0x03, 0x01, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },

	// Gamma Setting Sequence
	{	0xF9,	1,	{	0x07, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	

	{	0xFA,	16,	{	0x02, 0x00, 0x00, 0x2F, 0x30, 
						0x3F, 0x30, 0x27, 0x1F, 0x20, 
						0x1C, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	0 },	
	
	{	0xFB,	16,	{	0x02, 0x00, 0x1F, 0x1D, 0x1E, 
						0x1B, 0x0F, 0x3C, 0x33, 0x2E, 
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
						0x00, 0x00, 0x00, 0x00, 0x00	},	120 },	

	{	0x29,	0,	{	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00	},	40 },	

};

static struct setting_table power_off_setting_table[] = {
//	Sleep In
	{ 	0x10, 	0,  { 	0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00	}, 120 },
};

#define POWER_ON_SETTINGS	(int)(sizeof(power_on_setting_table)/sizeof(struct setting_table))
#define POWER_OFF_SETTINGS	(int)(sizeof(power_off_setting_table)/sizeof(struct setting_table))

static int lcdc_s6d04h0a_panel_off(struct platform_device *pdev);

static int spi_cs;
static int spi_sclk;
//static int spi_sdo;
static int spi_sdi;
//static int spi_dac;
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
	if(table->wait)
		msleep(table->wait);

#endif
}

static void spi_init(void)
{
	/* Setting the Default GPIO's */
	spi_sclk = *(lcdc_s6d04h0a_pdata->gpio_num);
	spi_cs   = *(lcdc_s6d04h0a_pdata->gpio_num + 1);
	spi_sdi  = *(lcdc_s6d04h0a_pdata->gpio_num + 2);
	lcd_en   = *(lcdc_s6d04h0a_pdata->gpio_num + 3);
	lcd_reset= *(lcdc_s6d04h0a_pdata->gpio_num + 4);
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
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);

		//LCD_EN_HI
		//gpio_set_value(lcd_en, 1);
		//TODO: turn on ldo
		udelay(50);
		
		//LCD_RESET_N_LO
		gpio_set_value(lcd_reset, 0);
		udelay(15);
		//LCD_RESET_N_HI
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

		/* turn off LDO */
		//TODO: turn off LDO
		//gpio_set_value(lcd_en, 0);

	    s6d04h0a_state.disp_powered_up = FALSE;
}

#if 0
static void s6d04h0a_init(void)
{
}
#endif

static void s6d04h0a_disp_on(void)
{
	int i;

	DPRINT("start %s\n", __func__);	

	if (s6d04h0a_state.disp_powered_up && !s6d04h0a_state.display_on) {
		
		for (i = 0; i < POWER_ON_SETTINGS; i++)
			setting_table_write(&power_on_setting_table[i]);		

		s6d04h0a_state.display_on = TRUE;
		lcd_on_state_for_debug = TRUE;
	}
}

static int lcdc_s6d04h0a_panel_on(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d04h0a_state.disp_initialized) {
		/* Configure reset GPIO that drives DAC */
		lcdc_s6d04h0a_pdata->panel_config_gpio(1);
		s6d04h0a_disp_powerup();
		spi_init();	/* LCD needs SPI */
		s6d04h0a_disp_on();
		s6d04h0a_state.disp_initialized = TRUE;
	}
	
	return 0;
}

static int lcdc_s6d04h0a_panel_off(struct platform_device *pdev)
{
	int i;

	DPRINT("start %s\n", __func__);	

	if (s6d04h0a_state.disp_powered_up && s6d04h0a_state.display_on) {
		for (i = 0; i < POWER_OFF_SETTINGS; i++)
			setting_table_write(&power_off_setting_table[i]);	
		
		lcdc_s6d04h0a_pdata->panel_config_gpio(0);
		s6d04h0a_state.display_on = FALSE;
		lcd_on_state_for_debug = FALSE;
		s6d04h0a_state.disp_initialized = FALSE;
		s6d04h0a_disp_powerdown();
	}
	return 0;
}

static void lcdc_s6d04h0a_set_backlight(struct msm_fb_data_type *mfd)
{	
	int bl_value = mfd->bl_level;

	printk("[BACLKIGHT] : %d\n",bl_value);

	if(board_hw_revision == 1 || board_hw_revision == 0) {
		lcdc_s6d_set_brightness_by_aat1401(bl_value);
	} else if(board_hw_revision == 2 || board_hw_revision == 3 ) {
		lcdc_s6d_set_brightness_by_ktd259(bl_value);
	} else {
		printk("Unknown HW Rev!!!!\n");
		lcdc_s6d_set_brightness_by_ktd259(bl_value);
	}
}


static int __init s6d04h0a_probe(struct platform_device *pdev)
{
	printk("++++++pdev->id=%d\n", pdev->id);

	if (pdev->id == 0)
	{
		lcdc_s6d04h0a_pdata = pdev->dev.platform_data;    // lcdc_s6d04h0a_panel_data in board-msm7x27.c
		
		return 0;
	}

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

	msm_fb_add_device(pdev);
	lcdc_s6d04h0a_panel_on(pdev);

	return 0;
}

static void s6d04h0a_shutdown(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

	if(board_hw_revision == 1 || board_hw_revision == 0) {
		lcdc_s6d_set_brightness_by_aat1401(0);
	} else if(board_hw_revision == 2 || board_hw_revision == 3) {
		lcdc_s6d_set_brightness_by_ktd259(0);
	} else {
		printk("Unknown HW Rev!!!!\n");
		lcdc_s6d_set_brightness_by_ktd259(0);
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

//
//if you change screen resolution, you should modify same information in hardware/msm7k/libgralloc-qsd8k/framebuffer.cpp
//

#define LCDC_FB_XRES	240
#define LCDC_FB_YRES	320

#define LCDC_HBP		16
#define LCDC_HPW		5
#define LCDC_HFP		16
#define LCDC_VBP		8
#define LCDC_VPW		2
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
	pinfo->type = LCDC_PANEL;
	pinfo->pdest = DISPLAY_1;
	pinfo->wait_cycle = 0;
//	pinfo->bpp = 24;
	pinfo->bpp = 18;
	pinfo->fb_num = 2;
//	pinfo->clk_rate = (9388 * 1000); //(8384 * 1000); vsync clk change ( 87Hz -> 97.7Hz )
//	pinfo->clk_rate = (8500 * 1000); //vsync clk change ( 94Hz )
	pinfo->clk_rate = (8192 * 1000);
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
