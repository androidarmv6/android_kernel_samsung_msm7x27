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

#define LCDC_DEBUG

#ifdef LCDC_DEBUG
#define DPRINT(x...)	printk("s6d04d1 " x)
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

#define WRPWD			0xF0
#define POWCTL			0xF3
#define EDSTEST			0xFF
#define VCMCTL			0xF4
#define SRCCTL			0xF5
#define SLPOUT			0x11
#define MADCTL			0x36
#define COLMOD			0x3A
#define DISCTL			0xF2
#define IFCTL			0xF6
#define GATECTL			0xFD
#define WRDISBV			0x51
#define WRCABCMB		0x5E
#define MIECTL1			0xCA
#define BCMODE			0xCB
#define MIECTL2			0xCC
#define MIDCTL3			0xCD
#define RPGAMCTL		0xF7
#define RNGAMCTL		0xF8
#define GPGAMCTL		0xF9
#define GNGAMCTL		0xFA
#define BPGAMCTL		0xFB
#define BNGAMCTL		0xFC
#define CASET			0x2A
#define PASET			0x2B
#define RAMWR           0x2C
#define WRCTRLD			0x53
#define WRCABC			0x55
#define DISPON			0x29
#define DISPOFF			0x28
#define SLPIN			0x10

struct setting_table {
	unsigned char command;	
	unsigned char parameters;
	unsigned char parameter[15];
	long wait;
};

static struct setting_table power_on_setting_table[] = {
/* Power Setting */
	{   POWCTL,  7, { 0x80, 0x00, 0x00, 0x0B, 0x33, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{   VCMCTL,  5, { 0x6e, 0x6e, 0x7f, 0x7f, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{   SRCCTL,  5, { 0x12, 0x00, 0x03, 0xF0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{   SLPOUT,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
/* Display Control */
	{   MADCTL,  1, { 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },	
	{   COLMOD,  1, { 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  30 },	
	{	DISCTL, 11, { 0x14, 0x14, 0x03, 0x03, 0x04, 0x03, 0x04, 0x10, 0x04, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00 },	0 },
	{    IFCTL,  4, { 0x00, 0x81, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },	
	{  GATECTL,  2, { 0x22, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },	
//	{  WRDISBV,  1, { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 }, //BRIGHTNESS	
	{ WRCABCMB,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },	
	{  MIECTL1,  3, { 0x80, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{   BCMODE,  1, { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{  MIECTL2,  3, { 0x20, 0x01, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
//	{  MIDCTL3,  2, { 0x7C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
//	{  MIECTL3,  2, { 0x2C, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
/* Gamma Table Set */
	{ RPGAMCTL, 15, { 0x00, 0x23, 0x15, 0x15, 0x1C, 0x19, 0x18, 0x1E, 0x24, 0x25, 0x25, 0x20, 0x10, 0x22, 0x21 },   0 },	
	{ RNGAMCTL, 15, { 0x19, 0x00, 0x15, 0x15, 0x1C, 0x1F, 0x1E, 0x24, 0x1E, 0x1F, 0x25, 0x20, 0x10, 0x22, 0x21 },   0 },	
	{ GPGAMCTL, 15, { 0x06, 0x23, 0x14, 0x14, 0x1D, 0x1A, 0x19, 0x1F, 0x24, 0x26, 0x30, 0x1E, 0x1E, 0x22, 0x21 },   0 },	
	{ GNGAMCTL, 15, { 0x19, 0x06, 0x14, 0x14, 0x1D, 0x20, 0x1F, 0x25, 0x1E, 0x20, 0x30, 0x1E, 0x1E, 0x22, 0x21 },   0 },	
	{ BPGAMCTL, 15, { 0x2C, 0x23, 0x20, 0x20, 0x23, 0x2F, 0x30, 0x39, 0x09, 0x09, 0x18, 0x13, 0x13, 0x22, 0x21 },   0 },	
	{ BNGAMCTL, 15, { 0x19, 0x2C, 0x20, 0x20, 0x23, 0x35, 0x36, 0x3F, 0x03, 0x03, 0x18, 0x13, 0x13, 0x22, 0x21 },   0 },	
/* RAM Address Set */
	{    CASET,  4, { 0x00, 0x00, 0x00, 0xEF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    PASET,  4, { 0x00, 0x00, 0x01, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    RAMWR,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
/* Display On */
//	{  WRCTRLD,  1, { 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
//	{   WRCABC,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{   DISPON,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  50 },	
};

static struct setting_table power_off_setting_table[] = {
//	{  WRCTRLD,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{  DISPOFF,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  40 },
	{    SLPIN,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};

#define POWER_ON_SETTINGS	(int)(sizeof(power_on_setting_table)/sizeof(struct setting_table))
#define POWER_OFF_SETTINGS	(int)(sizeof(power_off_setting_table)/sizeof(struct setting_table))

static int lcdc_s6d04d1_panel_off(struct platform_device *pdev);

static int lcd_brightness = -1;

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

static int delayed_backlight_value = -1;
static void lcdc_s6d04d1_set_brightness_in_blu(int level);

struct s6d04d1_state_type{
	boolean disp_initialized;
	boolean display_on;
	boolean disp_powered_up;
};

static struct s6d04d1_state_type s6d04d1_state = { 0 };
static struct msm_panel_common_pdata *lcdc_s6d04d1_pdata;

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

	mdelay(table->wait);
}

static void spi_init(void)
{
	/* Setting the Default GPIO's */
	spi_sclk = *(lcdc_s6d04d1_pdata->gpio_num);
	spi_cs   = *(lcdc_s6d04d1_pdata->gpio_num + 1);
	spi_sdi  = *(lcdc_s6d04d1_pdata->gpio_num + 2);
	lcd_en   = *(lcdc_s6d04d1_pdata->gpio_num + 3);
	lcd_reset= *(lcdc_s6d04d1_pdata->gpio_num + 4);
//	spi_sdo  = *(lcdc_s6d04d1_pdata->gpio_num + 3);

	/* Set the output so that we dont disturb the slave device */
	gpio_set_value(spi_sclk, 0);
	gpio_set_value(spi_sdi, 0);

	/* Set the Chip Select De-asserted */
	gpio_set_value(spi_cs, 0);

}

static void s6d04d1_disp_powerup(void)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d04d1_state.disp_powered_up && !s6d04d1_state.display_on) {
		/* Reset the hardware first */
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);

		//LCD_EN_HI
		//gpio_set_value(lcd_en, 1);
		//TODO: turn on ldo
		mdelay(50);
		
		//LCD_RESET_N_LO
		gpio_set_value(lcd_reset, 0);
		mdelay(1);	
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);
		mdelay(10);

		
		/* Include DAC power up implementation here */
		
	    s6d04d1_state.disp_powered_up = TRUE;
	}
}

static void s6d04d1_disp_powerdown(void)
{
	DPRINT("start %s\n", __func__);	

		/* Reset Assert */
		gpio_set_value(lcd_reset, 0);		

		/* turn off LDO */
		//TODO: turn off LDO
		//gpio_set_value(lcd_en, 0);

	    s6d04d1_state.disp_powered_up = FALSE;
}

static void s6d04d1_init(void)
{
#if 0
	/* Image interface settings */
	serigo(GORDON_REG_IMGCTL2, 0x00);
	serigo(GORDON_REG_IMGSET1, 0x00);

	/* Exchange the RGB signal for J510(Softbank mobile) */
	serigo(GORDON_REG_IMGSET2, 0x12);
	serigo(GORDON_REG_LCDIFSET1, 0x00);

	/* Pre-charge settings */
	serigo(GORDON_REG_PCCTL, 0x09);
	serigo(GORDON_REG_LCDIFCTL2, 0x7B);
#endif
	mdelay(1);
}

static void s6d04d1_disp_on(void)
{
	int i;

	DPRINT("start %s\n", __func__);	

	if (s6d04d1_state.disp_powered_up && !s6d04d1_state.display_on) {
		s6d04d1_init();
		mdelay(20);

		/* s6d04d1 setting */
		for (i = 0; i < POWER_ON_SETTINGS; i++)
			setting_table_write(&power_on_setting_table[i]);			// new lcd

		mdelay(1);
		s6d04d1_state.display_on = TRUE;
	}
}

static int lcdc_s6d04d1_panel_on(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d04d1_state.disp_initialized) {
		/* Configure reset GPIO that drives DAC */
		lcdc_s6d04d1_pdata->panel_config_gpio(1);
		//spi_dac = *(lcdc_s6d04d1_pdata->gpio_num + 4);
		//gpio_set_value(spi_dac, 0);
		//udelay(15);
		//gpio_set_value(spi_dac, 1);
		spi_init();	/* LCD needs SPI */
		s6d04d1_disp_powerup();
		s6d04d1_disp_on();
		s6d04d1_state.disp_initialized = TRUE;
	}

	// TEMP CODE for BLU
	//gpio_set_value(GPIO_BL_CTRL, 1);
	//gpio_set_value(91, 1); 
	
	return 0;
}

static int lcdc_s6d04d1_panel_off(struct platform_device *pdev)
{
	int i;

	DPRINT("start %s\n", __func__);	

	// TEMP CODE for BLU
	//gpio_set_value(GPIO_BL_CTRL, 0);
	//gpio_set_value(91, 0); 

	if (s6d04d1_state.disp_powered_up && s6d04d1_state.display_on) {
		
		for (i = 0; i < POWER_OFF_SETTINGS; i++)
			setting_table_write(&power_off_setting_table[i]);	
		
		lcdc_s6d04d1_pdata->panel_config_gpio(0);
		s6d04d1_state.display_on = FALSE;
		s6d04d1_state.disp_initialized = FALSE;
		s6d04d1_disp_powerdown();
	}
	return 0;
}

#if 1

// brightness tuning
#define MAX_BRIGHTNESS_LEVEL 255
#define LOW_BRIGHTNESS_LEVEL 30
#define MAX_BACKLIGHT_VALUE 30
#define LOW_BACKLIGHT_VALUE 3 // 7
#define DIM_BACKLIGHT_VALUE 1 // 4

static DEFINE_SPINLOCK(bl_ctrl_lock);
static DEFINE_SPINLOCK(bl_ctrl_irq_lock);

// brightness setting for KTD259 (Backlight IC)
#define MAX_BRIGHTNESS_IN_BLU	32

static void lcdc_s6d04d1_set_brightness_in_blu(int level)
{
	unsigned long irqflags;
	int tune_level = level;
		int pulse;

	// LCD should be turned on prior to backlight
	if(s6d04d1_state.disp_initialized == FALSE && tune_level > 0)
		{
		//DPRINT("skip bl:%d\n", tune_level);	
		delayed_backlight_value = tune_level;
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

	if (tune_level <= 0) {
			/* keep back light OFF */
			gpio_set_value(GPIO_BL_CTRL, 0);
			mdelay(3);		//guaranteed shutdown
		lcd_brightness = tune_level;
		} else {
			/* keep back light ON */
			if(unlikely(lcd_brightness < 0))
				{
				// first time
				int val = gpio_get_value(GPIO_BL_CTRL);
				if(val)
					{
					lcd_brightness = 0;
					gpio_set_value(GPIO_BL_CTRL, 0);
					mdelay(3);		//guaranteed shutdown
					}
				}

			if(!lcd_brightness)
				{
				gpio_set_value(GPIO_BL_CTRL, 1);
				udelay(1);
				lcd_brightness = MAX_BRIGHTNESS_IN_BLU;
				}
			
		pulse = (lcd_brightness - tune_level + MAX_BRIGHTNESS_IN_BLU) % MAX_BRIGHTNESS_IN_BLU;

		spin_lock_irqsave(&bl_ctrl_irq_lock, irqflags);

			for(; pulse>0; pulse--)
				{
				gpio_set_value(GPIO_BL_CTRL, 0);
				udelay(1);
				gpio_set_value(GPIO_BL_CTRL, 1);
				udelay(1);
				}
				
		spin_unlock_irqrestore(&bl_ctrl_irq_lock, irqflags);

		lcd_brightness = tune_level;
	
		}
	
	//TODO: unlock
	spin_unlock(&bl_ctrl_lock);

}

static void lcdc_s6d04d1_set_backlight(struct msm_fb_data_type *mfd)
{	
	int bl_level = mfd->bl_level;
	int tune_level;

	// brightness tuning
	if(bl_level >= LOW_BRIGHTNESS_LEVEL)
		tune_level = (bl_level - LOW_BRIGHTNESS_LEVEL) * (MAX_BACKLIGHT_VALUE-LOW_BACKLIGHT_VALUE) / (MAX_BRIGHTNESS_LEVEL-LOW_BRIGHTNESS_LEVEL) + LOW_BACKLIGHT_VALUE;
	else if(bl_level > 0)
		tune_level = DIM_BACKLIGHT_VALUE;
	else
		tune_level = bl_level;

	//if(!bl_level || lcd_brightness <= 0)		// reduce log msg
		DPRINT("%s:%d,%d\n", __func__, bl_level, tune_level);	

	// turn on lcd if needed
#ifdef __LCD_ON_EARLY__
	if(tune_level > 0)
		{
		if(!s6d04d1_state.disp_powered_up)
			s6d04d1_disp_powerup();
		if(!s6d04d1_state.display_on)
			s6d04d1_disp_on();
		}
#endif

	lcdc_s6d04d1_set_brightness_in_blu(tune_level);
}
#endif


#ifdef __LCD_CONTROL_BY_FILE__
static int s3cfb_sysfs_show_lcd_power(struct device *dev, struct device_attribute *attr, char *buf)
{
        return snprintf(buf, PAGE_SIZE, "%d\n", s6d04d1_state.disp_initialized);
}

static int s3cfb_sysfs_store_lcd_power(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct platform_device* pdev;
	
    if (len < 1)
        return -EINVAL;

	pdev = container_of(dev, struct platform_device, dev);

    if (strnicmp(buf, "on", 2) == 0 || strnicmp(buf, "1", 1) == 0)
    	{
		lcdc_s6d04d1_panel_on(pdev);
    	lcdc_s6d04d1_set_brightness_in_blu(15);
    	}
    else if (strnicmp(buf, "off", 3) == 0 || strnicmp(buf, "0", 1) == 0)
    	{
    	lcdc_s6d04d1_set_brightness_in_blu(0);
		lcdc_s6d04d1_panel_off(pdev);
    	}
    else
            return -EINVAL;

    return len;
}

static DEVICE_ATTR(lcd_power, 0666,						//sm.kim: give write permission for application
                        s3cfb_sysfs_show_lcd_power,
                        s3cfb_sysfs_store_lcd_power);
#endif

static int __init s6d04d1_probe(struct platform_device *pdev)
{
	int ret;
	DPRINT("start %s\n", __func__);	

#ifdef __LCD_CONTROL_BY_FILE__
    ret = device_create_file(&(pdev->dev), &dev_attr_lcd_power);
    if (ret < 0)
            printk(KERN_WARNING "s6d04d1: failed to add entries\n");
#endif

	if (pdev->id == 0) {
		lcdc_s6d04d1_pdata = pdev->dev.platform_data;
		return 0;
	}
	msm_fb_add_device(pdev);

	return 0;
}

static void s6d04d1_shutdown(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

   	lcdc_s6d04d1_set_brightness_in_blu(0);
	lcdc_s6d04d1_panel_off(pdev);
}

static struct platform_driver this_driver = {
	.probe  = s6d04d1_probe,
	.shutdown	= s6d04d1_shutdown,
	.driver = {
		.name   = "lcdc_s6d04d1_wqvga",
	},
};

static struct msm_fb_panel_data s6d04d1_panel_data = {
	.on = lcdc_s6d04d1_panel_on,
	.off = lcdc_s6d04d1_panel_off,
	.set_backlight = lcdc_s6d04d1_set_backlight,
};

static struct platform_device this_device = {
	.name   = "lcdc_panel",
	.id	= 1,
	.dev	= {
		.platform_data = &s6d04d1_panel_data,
	}
};

//
//if you change screen resolution, you should modify same information in hardware/msm7k/libgralloc-qsd8k/framebuffer.cpp
//

#define LCDC_FB_XRES	240
#define LCDC_FB_YRES	400
#define LCDC_HBP		24
#define LCDC_HPW		12
#define LCDC_HFP		8
#define LCDC_VBP		8
#define LCDC_VPW		2
#define LCDC_VFP		8
#define LCDC_PCLK		(LCDC_FB_XRES+LCDC_HBP+LCDC_HPW+LCDC_HFP)*(LCDC_FB_YRES+LCDC_VBP+LCDC_VPW+LCDC_VFP)*3

static int __init lcdc_s6d04d1_panel_init(void)
{
	int ret;
	struct msm_panel_info *pinfo;

#ifdef CONFIG_FB_MSM_TRY_MDDI_CATCH_LCDC_PRISM
	if (msm_fb_detect_client("lcdc_s6d04d1_wqvga"))
		{
		printk(KERN_ERR "%s: msm_fb_detect_client failed!\n", __func__); 
		return 0;
		}
#endif
	DPRINT("start %s\n", __func__);	
	
	ret = platform_driver_register(&this_driver);
	if (ret)
		{
		printk(KERN_ERR "%s: platform_driver_register failed! ret=%d\n", __func__, ret); 
		return ret;
		}

	pinfo = &s6d04d1_panel_data.panel_info;
	pinfo->xres = LCDC_FB_XRES;
	pinfo->yres = LCDC_FB_YRES;
	pinfo->type = LCDC_PANEL;
	pinfo->pdest = DISPLAY_1;
	pinfo->wait_cycle = 0;
	pinfo->bpp = 24;
	pinfo->fb_num = 2;
	pinfo->clk_rate = 8192000;
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

	printk("%s\n", __func__);

	ret = platform_device_register(&this_device);
	if (ret)
		{
		printk(KERN_ERR "%s: platform_device_register failed! ret=%d\n", __func__, ret); 
		platform_driver_unregister(&this_driver);
		}

	return ret;
}

module_init(lcdc_s6d04d1_panel_init);
