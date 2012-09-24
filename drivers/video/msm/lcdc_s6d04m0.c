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
#include <linux/clk.h>
#include <mach/gpio.h>
#include "msm_fb.h"

#define LCDC_DEBUG

#ifdef LCDC_DEBUG
#define DPRINT(x...)	printk("s6d04m0 " x)
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

#define LCD_SDI_DATA	gpio_get_value(spi_sdi)

#define LCD_SDI_SWITCH_INPUT		gpio_direction_input(spi_sdi);
#define LCD_SDI_SWITCH_OUTPUT_LOW	gpio_direction_output(spi_sdi, 0);
#define LCD_SDI_SWITCH_OUTPUT_HIGH	gpio_direction_output(spi_sdi, 1);

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
#define RDDIDIF			0x04		// 4 parameters
#define	RDID1			0xDA		// 2 parameters
#define	RDID2			0xDB		// 2 parameters
#define	RDID3			0xDC		// 2 parameters

struct setting_table {
	unsigned char command;	
	unsigned char parameters;
	unsigned char parameter[15];
	long wait;
};


#if 0
static struct setting_table power_on_setting_table[] = {
	{    0xF0,  2, { 0x5a, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{    0xF3,  1, { 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{    0xFF,  4, { 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   0 },
	{    0x11,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  20 },
	// power setting sequence
	{    0xF3,  8, { 0x01, 0x26, 0x26, 0x0b, 0x22, 0x66, 0x60, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{    0xF4,  5, { 0x5d, 0x60, 0x6d, 0x6d, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	{    0xF5,  6, { 0x02, 0x11, 0x0a, 0xf0, 0x33, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   40 },	
	{    0xF3,  1, { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   20 },	
	{    0xFF,  4, { 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   20 },	
	{    0xF3,  1, { 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    0xFF,  4, { 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   40 },	
	{    0xF3,  1, { 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    0xFF,  4, { 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   40 },	
	{    0xF3,  1, { 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   40 },	
	{    0xF3,  1, { 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   60 },	
	{    0xFF,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF2, 11, { 0x16, 0x16, 0x01, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    0xFD,  1, { 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },
	// initializing sequence
	{    0x3A,  1, { 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    0x36,  1, { 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	{    0xF6,  4, { 0x00, 0x01, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// gamma setting sequence
	{    0xF7, 15, { 0x93, 0x15, 0x2b, 0x2c, 0x30, 0x29, 0x26, 0x27, 0x20, 0x24, 0x2b, 0x25, 0x0a, 0x11, 0x11 },	0 },	
	{    0xF8, 15, { 0x80, 0x04, 0x17, 0x1a, 0x1d, 0x1e, 0x23, 0x2e, 0x14, 0x17, 0x24, 0x20, 0x06, 0x11, 0x11 },	0 },	
	{    0xF9, 15, { 0x8f, 0x15, 0x2b, 0x2c, 0x30, 0x29, 0x26, 0x27, 0x1e, 0x22, 0x29, 0x23, 0x08, 0x11, 0x11 },	0 },	
	{    0xFA, 15, { 0x80, 0x00, 0x17, 0x1a, 0x1d, 0x1e, 0x23, 0x2e, 0x12, 0x15, 0x22, 0x1e, 0x04, 0x11, 0x11 },	0 },	
	{    0xFB, 15, { 0x8f, 0x15, 0x2b, 0x2c, 0x30, 0x29, 0x26, 0x27, 0x1e, 0x22, 0x29, 0x23, 0x08, 0x11, 0x11 },	0 },	
	{    0xFC, 15, { 0x80, 0x00, 0x17, 0x1a, 0x1d, 0x1e, 0x23, 0x2e, 0x12, 0x15, 0x22, 0x1e, 0x04, 0x11, 0x11 },	0 },	
	// B/L(CABC) setting sequence
	{    0x51,  1, { 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x55,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x5E,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xCA,  3, { 0x80, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xCC,  1, { 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF3,  1, { 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },	0 },	
	// Display on
	{    0x29,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	// B/L(CABC) On
	{    0xCB,  1, { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xCD,  2, { 0x7f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x55,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x51,  1, { 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x53,  1, { 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
};
#else
//20100302 LMS280GS17
static struct setting_table power_on_setting_table_smd[] = {
	{    0xF0,  2, { 0x5a, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },
	{    0xF3,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   20 },
	// power setting sequence
	{    0xF3,  8, { 0x81, 0x26, 0x26, 0x07, 0x33, 0x66, 0x66, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF4,  5, { 0x5d, 0x60, 0x6d, 0x6d, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF5,  6, { 0x12, 0x11, 0x03, 0xf0, 0x33, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xFD,  1, { 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	// sleep out
	{    0x11,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  120 },	
	// initializing sequence
	{    0x3A,  1, { 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x35,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x36,  1, { 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF2, 11, { 0x16, 0x16, 0x01, 0x08, 0x08, 0x08, 0x08, 0x1f, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF6,  4, { 0x00, 0x01, 0xf0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	// gamma setting sequence
	{    0xF7, 15, { 0x98, 0x17, 0x00, 0x20, 0x32, 0x30, 0x28, 0x26, 0x1e, 0x2b, 0x3b, 0x2b, 0x08, 0x11, 0x11 },	0 },	
	{    0xF8, 15, { 0x80, 0x00, 0x00, 0x00, 0x17, 0x16, 0x1e, 0x26, 0x1d, 0x1e, 0x35, 0x2b, 0x0c, 0x11, 0x11 },	0 },	
	{    0xF9, 15, { 0x90, 0x17, 0x00, 0x00, 0x28, 0x27, 0x27, 0x28, 0x18, 0x1d, 0x24, 0x27, 0x09, 0x11, 0x11 },	0 },	
	{    0xFA, 15, { 0x80, 0x00, 0x00, 0x00, 0x1d, 0x1e, 0x22, 0x2d, 0x14, 0x14, 0x22, 0x1e, 0x04, 0x11, 0x11 },	0 },	
	{    0xFB, 15, { 0x8e, 0x17, 0x00, 0x00, 0x20, 0x29, 0x25, 0x28, 0x1e, 0x25, 0x32, 0x28, 0x11, 0x11, 0x11 },	0 },	
	{    0xFC, 15, { 0x80, 0x00, 0x00, 0x00, 0x1d, 0x1f, 0x23, 0x2e, 0x14, 0x11, 0x1c, 0x14, 0x04, 0x11, 0x11 },	0 },	
	// Display on
	{    0x29,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
};

#endif

//Sharp
static struct setting_table power_on_setting_table_sharp[] = {
	// level2 command access
	{    0xF0,  2, { 0x5a, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },
	{    0xD9,  2, { 0x00, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },
	// power setting sequence
	{    0xFF,  4, { 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF4,  5, { 0x77, 0x77, 0x77, 0x77, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF3,  8, { 0x80, 0x26, 0x26, 0x09, 0x33, 0x72, 0x72, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	// initializing sequence
	{    0x35,  1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x36,  1, { 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0x3A,  1, { 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF2, 11, { 0x15, 0x15, 0x01, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF6,  4, { 0x00, 0x07, 0xf0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	// gamma setting sequence
	{    0xF5,  6, { 0x12, 0x11, 0x03, 0xf0, 0x30, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
	{    0xF7, 15, { 0xa2, 0x1c, 0x06, 0x0e, 0x13, 0x1f, 0x27, 0x2f, 0x15, 0x11, 0x13, 0x0e, 0x08, 0x02, 0x22 },	0 },	
	{    0xF8, 15, { 0x8d, 0x1f, 0x06, 0x0e, 0x1a, 0x24, 0x27, 0x2f, 0x15, 0x14, 0x13, 0x0e, 0x08, 0x02, 0x22 },	0 },	
	{    0xF9, 15, { 0x8c, 0x13, 0x06, 0x02, 0x17, 0x1e, 0x24, 0x2b, 0x16, 0x14, 0x1e, 0x19, 0x10, 0x02, 0x22 },	0 },	
	{    0xFA, 15, { 0x84, 0x0a, 0x06, 0x02, 0x1d, 0x23, 0x23, 0x2b, 0x14, 0x18, 0x1e, 0x19, 0x10, 0x02, 0x22 },	0 },	
	{    0xFB, 15, { 0x83, 0x0f, 0x06, 0x0c, 0x1b, 0x1e, 0x25, 0x2b, 0x16, 0x0c, 0x13, 0x0c, 0x07, 0x02, 0x22 },	0 },	
	{    0xFC, 15, { 0x80, 0x00, 0x06, 0x0c, 0x21, 0x23, 0x25, 0x2b, 0x16, 0x18, 0x13, 0x0c, 0x07, 0x02, 0x22 },	0 },	
	// sleep out
	{    0x11,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  120 },	
	// Display on
	{    0x29,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },    0 },	
};


//#define POWER_ON_SETTINGS	(int)(sizeof(power_on_setting_table)/sizeof(struct setting_table))

#if 0
static struct setting_table power_off_setting_table[] = {
	{    SLPIN,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};
#else
//20100302 LMS280GS17
static struct setting_table power_off_setting_table[] = {
	{     0xF3,  1, { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  10 },
	{     0x10,  0, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 120 },
};
#endif


#define POWER_OFF_SETTINGS	(int)(sizeof(power_off_setting_table)/sizeof(struct setting_table))

static int lcdc_s6d04m0_panel_off(struct platform_device *pdev);
static void spi_init(void);

static int lcd_brightness = -1;
static int lcd_type = 0;
enum {
	LcdTypeNone = -1,
	LcdTypeSMD = 1,
	LcdTypeSharp = 2,
};

static u8 mtp_value_smd[3] = { 0x51, 0x88, 0x11 };
static u8 mtp_value_sharp[3] = { 0x51, 0x1C, 0x11 };

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
static void lcdc_s6d04m0_set_brightness_in_blu(int level);

struct s6d04m0_state_type{
	boolean disp_initialized;
	boolean display_on;
	boolean disp_powered_up;
};

static struct s6d04m0_state_type s6d04m0_state = { 
	.disp_initialized = TRUE,
	.display_on = TRUE,
	.disp_powered_up = TRUE,
};

static struct msm_panel_common_pdata *lcdc_s6d04m0_pdata;

static void read_ldi_register(u8 addr, u8 *buf, int count)
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

	if(count>1)
		{
		//dummy clock cycle
		LCD_SCL_LOW
		udelay(DEFAULT_USLEEP); 	
		LCD_SCL_HIGH
		udelay(DEFAULT_USLEEP);	
		}

	/* Read Parameter */
	if (count > 0) {
	for (j = 0; j < count; j++) {

		for (i = 7; i >= 0; i--) { 
			LCD_SCL_LOW
			udelay(DEFAULT_USLEEP);	
			// read bit
			if(LCD_SDI_DATA)
				buf[j] |= (0x1<<i);
			else
				buf[j] &= ~(0x1<<i);
			LCD_SCL_HIGH
			udelay(DEFAULT_USLEEP);	
		}

	}
	}

	LCD_CSX_HIGH
	udelay(DEFAULT_USLEEP);	

	//switch output
	LCD_SDI_SWITCH_OUTPUT_LOW
	
//	msleep(table->wait);
}

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
	else
		udelay(10);
}

static void determine_lcd_type(void)
{
	u8 data[4]={0,0,0,0};

	spi_init();

	// read MTP from LDI
	read_ldi_register(RDDIDIF, &data[0], 3);
	printk("ldi mtpdata: %x %x %x\n", data[0], data[1], data[2]);
//	read_ldi_register(RDID1, &data[0], 1);
//	read_ldi_register(RDID2, &data[1], 1);
//	read_ldi_register(RDID3, &data[2], 1);
//	printk("ldi mtpdata: %x %x %x\n", data[0], data[1], data[2]);

	if(data[0]==mtp_value_smd[0] && data[1]==mtp_value_smd[1] && data[2]==mtp_value_smd[2])
		{
		printk(KERN_NOTICE "lcd type is smd\n");
		lcd_type = LcdTypeSMD;
		}
	else if(data[0]==mtp_value_sharp[0] && data[1]==mtp_value_sharp[1] && data[2]==mtp_value_sharp[2])
		{
		printk(KERN_NOTICE "lcd type is sharp\n");
		lcd_type = LcdTypeSharp;
		}
	else if(data[0] == 0xff)
		{
		printk(KERN_WARNING "lcd type is none(lcd may be absent)\n");
		lcd_type = LcdTypeNone;
		}
	else
		{
		printk(KERN_NOTICE "default lcd type is smd\n");
		lcd_type = LcdTypeSMD;
		}

}

static void spi_init(void)
{
	/* Setting the Default GPIO's */
	spi_sclk = *(lcdc_s6d04m0_pdata->gpio_num);
	spi_cs   = *(lcdc_s6d04m0_pdata->gpio_num + 1);
	spi_sdi  = *(lcdc_s6d04m0_pdata->gpio_num + 2);
	lcd_en   = *(lcdc_s6d04m0_pdata->gpio_num + 3);
	lcd_reset= *(lcdc_s6d04m0_pdata->gpio_num + 4);
//	spi_sdo  = *(lcdc_s6d04m0_pdata->gpio_num + 3);

	/* Set the output so that we dont disturb the slave device */
	gpio_set_value(spi_sclk, 0);
	gpio_set_value(spi_sdi, 0);

	/* Set the Chip Select De-asserted */
	gpio_set_value(spi_cs, 0);

}

static void s6d04m0_disp_powerup(void)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d04m0_state.disp_powered_up && !s6d04m0_state.display_on) {
		/* Reset the hardware first */

		//LCD_EN_HI
		//gpio_set_value(lcd_en, 1);
		//TODO: turn on ldo

		//msleep(50);
		
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);
		//msleep(10);
		udelay(100);
		//LCD_RESET_N_LO
		gpio_set_value(lcd_reset, 0);
		//msleep(1);	
		udelay(15);
		//LCD_RESET_N_HI
		gpio_set_value(lcd_reset, 1);
//		msleep(20);
		msleep(10);

		
		/* Include DAC power up implementation here */
		
	    s6d04m0_state.disp_powered_up = TRUE;
	}
}

static void s6d04m0_disp_powerdown(void)
{
	DPRINT("start %s\n", __func__);	

		/* Reset Assert */
		gpio_set_value(lcd_reset, 0);		

		/* turn off LDO */
		//TODO: turn off LDO
		//gpio_set_value(lcd_en, 0);

	    s6d04m0_state.disp_powered_up = FALSE;
}

static void s6d04m0_init(void)
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

static void s6d04m0_disp_on(void)
{
	int i;

	//u8 data[4];

	DPRINT("start %s\n", __func__);	

	if (s6d04m0_state.disp_powered_up && !s6d04m0_state.display_on) {
		s6d04m0_init();
		//mdelay(20);

		// read MTP from LDI
		determine_lcd_type();

		/* s6d04m0 setting */
		if(lcd_type==LcdTypeSharp)
			{
			for (i = 0; i < ARRAY_SIZE(power_on_setting_table_sharp); i++)
				setting_table_write(&power_on_setting_table_sharp[i]);			
			}
		else
			{
			for (i = 0; i < ARRAY_SIZE(power_on_setting_table_smd); i++)
				setting_table_write(&power_on_setting_table_smd[i]);			
			}

		//mdelay(1);
		s6d04m0_state.display_on = TRUE;
	}
}

static int lcdc_s6d04m0_panel_on(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

	if (!s6d04m0_state.disp_initialized) {
		/* Configure reset GPIO that drives DAC */
		lcdc_s6d04m0_pdata->panel_config_gpio(1);
		//spi_dac = *(lcdc_s6d04m0_pdata->gpio_num + 4);
		//gpio_set_value(spi_dac, 0);
		//udelay(15);
		//gpio_set_value(spi_dac, 1);
		spi_init();	/* LCD needs SPI */
		s6d04m0_disp_powerup();
		s6d04m0_disp_on();

		//msleep(200);
		msleep(50);
		s6d04m0_state.disp_initialized = TRUE;

	}

	// TEMP CODE for BLU
	//gpio_set_value(GPIO_BL_CTRL, 1);
	//gpio_set_value(91, 1); 
	
	return 0;
}

static int lcdc_s6d04m0_panel_off(struct platform_device *pdev)
{
	int i;

	DPRINT("start %s\n", __func__);	

	// TEMP CODE for BLU
	//gpio_set_value(GPIO_BL_CTRL, 0);
	//gpio_set_value(91, 0); 

	if (s6d04m0_state.disp_powered_up && s6d04m0_state.display_on) {
		
		for (i = 0; i < POWER_OFF_SETTINGS; i++)
			setting_table_write(&power_off_setting_table[i]);	
		
		lcdc_s6d04m0_pdata->panel_config_gpio(0);
		s6d04m0_state.display_on = FALSE;
		s6d04m0_state.disp_initialized = FALSE;
		s6d04m0_disp_powerdown();
	}
	return 0;
}

#if 1

// brightness tuning
#define MAX_BRIGHTNESS_LEVEL 255
#define LOW_BRIGHTNESS_LEVEL 30
#define MAX_BACKLIGHT_VALUE 30
#define LOW_BACKLIGHT_VALUE 7 // 3 // 7
#define DIM_BACKLIGHT_VALUE 4 // 1 // 4

static DEFINE_SPINLOCK(bl_ctrl_lock);
static DEFINE_SPINLOCK(bl_ctrl_irq_lock);

// brightness setting for KTD259 (Backlight IC)
#define MAX_BRIGHTNESS_IN_BLU	32

static void lcdc_s6d04m0_set_brightness_in_blu(int level)
{
	unsigned long irqflags;
	int tune_level = level;
	int pulse;

	// LCD should be turned on prior to backlight
	if(s6d04m0_state.disp_initialized == FALSE && tune_level > 0)
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

	// when LCD is absent, don't turn on BLU
	// over current may distroy inductor element
	if( lcd_type == 0 ) determine_lcd_type();
	if( lcd_type < 0 && tune_level > 0)
		{
		printk("LCD may be absent. skip bl.\n");
		return;
		}
	
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

static void lcdc_s6d04m0_set_backlight(struct msm_fb_data_type *mfd)
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
		if(!s6d04m0_state.disp_powered_up)
			s6d04m0_disp_powerup();
		if(!s6d04m0_state.display_on)
			s6d04m0_disp_on();
		}
#endif

	lcdc_s6d04m0_set_brightness_in_blu(tune_level);
}
#endif


#ifdef __LCD_CONTROL_BY_FILE__
static int lcdc_s6d04m0_pixclock_on(struct platform_device *pdev)
{
	static struct clk *mdp_lcdc_pclk_clk;
	static struct clk *mdp_lcdc_pad_pclk_clk;

	DPRINT("start %s\n", __func__);	

	mdp_lcdc_pclk_clk = clk_get(NULL, "mdp_lcdc_pclk_clk");
	if (IS_ERR(mdp_lcdc_pclk_clk)) {
		printk(KERN_ERR "error: can't get mdp_lcdc_pclk_clk!\n");
		return IS_ERR(mdp_lcdc_pclk_clk);
	}
	
	mdp_lcdc_pad_pclk_clk = clk_get(NULL, "mdp_lcdc_pad_pclk_clk");
	if (IS_ERR(mdp_lcdc_pad_pclk_clk)) {
		printk(KERN_ERR "error: can't get mdp_lcdc_pad_pclk_clk!\n");
		return IS_ERR(mdp_lcdc_pad_pclk_clk);
	}
	
	clk_enable(mdp_lcdc_pclk_clk);
	clk_enable(mdp_lcdc_pad_pclk_clk);

	return 0;
}

static int lcdc_s6d04m0_pixclock_off(struct platform_device *pdev)
{
	static struct clk *mdp_lcdc_pclk_clk;
	static struct clk *mdp_lcdc_pad_pclk_clk;

	DPRINT("start %s\n", __func__);	

	mdp_lcdc_pclk_clk = clk_get(NULL, "mdp_lcdc_pclk_clk");
	if (IS_ERR(mdp_lcdc_pclk_clk)) {
		printk(KERN_ERR "error: can't get mdp_lcdc_pclk_clk!\n");
		return IS_ERR(mdp_lcdc_pclk_clk);
	}
	
	mdp_lcdc_pad_pclk_clk = clk_get(NULL, "mdp_lcdc_pad_pclk_clk");
	if (IS_ERR(mdp_lcdc_pad_pclk_clk)) {
		printk(KERN_ERR "error: can't get mdp_lcdc_pad_pclk_clk!\n");
		return IS_ERR(mdp_lcdc_pad_pclk_clk);
	}
	
	clk_disable(mdp_lcdc_pclk_clk);
	clk_disable(mdp_lcdc_pad_pclk_clk);

	return 0;
}
#endif


#ifdef __LCD_CONTROL_BY_FILE__
static int s3cfb_sysfs_show_lcd_power(struct device *dev, struct device_attribute *attr, char *buf)
{
        return snprintf(buf, PAGE_SIZE, "%d\n", s6d04m0_state.disp_initialized);
}

static int s3cfb_sysfs_store_lcd_power(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct platform_device* pdev;
	
    if (len < 1)
        return -EINVAL;

	pdev = container_of(dev, struct platform_device, dev);

    if (strnicmp(buf, "on", 2) == 0 || strnicmp(buf, "1", 1) == 0)
    	{
		lcdc_s6d04m0_panel_on(pdev);
    	lcdc_s6d04m0_set_brightness_in_blu(15);
    	}
    else if (strnicmp(buf, "off", 3) == 0 || strnicmp(buf, "0", 1) == 0)
    	{
    	lcdc_s6d04m0_set_brightness_in_blu(0);
		lcdc_s6d04m0_panel_off(pdev);
    	}
    else
            return -EINVAL;

    return len;
}

static DEVICE_ATTR(lcd_power, 0666,						//sm.kim: give write permission for application
                        s3cfb_sysfs_show_lcd_power,
                        s3cfb_sysfs_store_lcd_power);
#endif


#ifdef __LCD_CONTROL_BY_FILE__
static int s3cfb_sysfs_show_lcd_power_clock(struct device *dev, struct device_attribute *attr, char *buf)
{
        return snprintf(buf, PAGE_SIZE, "%d\n", s6d04m0_state.disp_initialized);
}

static int s3cfb_sysfs_store_lcd_power_clock(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct platform_device* pdev;
	
    if (len < 1)
        return -EINVAL;

	pdev = container_of(dev, struct platform_device, dev);

    if (strnicmp(buf, "on", 2) == 0 || strnicmp(buf, "1", 1) == 0)
    	{
		lcdc_s6d04m0_pixclock_on(pdev);
		lcdc_s6d04m0_panel_on(pdev);
    	lcdc_s6d04m0_set_brightness_in_blu(15);
    	}
    else if (strnicmp(buf, "off", 3) == 0 || strnicmp(buf, "0", 1) == 0)
    	{
    	lcdc_s6d04m0_set_brightness_in_blu(0);
		lcdc_s6d04m0_panel_off(pdev);
		lcdc_s6d04m0_pixclock_off(pdev);
    	}
    else
            return -EINVAL;

    return len;
}

static DEVICE_ATTR(lcd_power_clock, 0666,						//sm.kim: give write permission for application
                        s3cfb_sysfs_show_lcd_power_clock,
                        s3cfb_sysfs_store_lcd_power_clock);
#endif


static int __init s6d04m0_probe(struct platform_device *pdev)
{
	int ret;
	DPRINT("start %s\n", __func__);	

#ifdef __LCD_CONTROL_BY_FILE__
    ret = device_create_file(&(pdev->dev), &dev_attr_lcd_power);
    if (ret < 0)
            printk(KERN_WARNING "s6d04m0: failed to add entries\n");

    ret = device_create_file(&(pdev->dev), &dev_attr_lcd_power_clock);
    if (ret < 0)
            printk(KERN_WARNING "s6d04m0: failed to add entries\n");
#endif

	if (pdev->id == 0) {
		lcdc_s6d04m0_pdata = pdev->dev.platform_data;
		return 0;
	}
	msm_fb_add_device(pdev);

	return 0;
}

static void s6d04m0_shutdown(struct platform_device *pdev)
{
	DPRINT("start %s\n", __func__);	

   	lcdc_s6d04m0_set_brightness_in_blu(0);
	lcdc_s6d04m0_panel_off(pdev);
}

static struct platform_driver this_driver = {
	.probe  = s6d04m0_probe,
	.shutdown	= s6d04m0_shutdown,
	.driver = {
		.name   = "lcdc_s6d04m0_qvga",
	},
};

static struct msm_fb_panel_data s6d04m0_panel_data = {
	.on = lcdc_s6d04m0_panel_on,
	.off = lcdc_s6d04m0_panel_off,
	.set_backlight = lcdc_s6d04m0_set_backlight,
};

static struct platform_device this_device = {
	.name   = "lcdc_panel",
	.id	= 1,
	.dev	= {
		.platform_data = &s6d04m0_panel_data,
	}
};

//
//if you change screen resolution, you should modify same information in hardware/msm7k/libgralloc-qsd8k/framebuffer.cpp
//
#if defined(CONFIG_MACH_LUCAS)
#define LCDC_FB_XRES	320
#define LCDC_FB_YRES 	240
#define LCDC_HBP		16 // minhyo0519 24
#define LCDC_HPW		24 // minhyo0519 12
#define LCDC_HFP		16 // minhyo0519 8
#define LCDC_VBP		16 // minhyo0519 8 // 20 // minhyo 8
#define LCDC_VPW		24 // minhyo0519 2 // 16 // minhyo 2
#define LCDC_VFP		16 // minhyo0519 8 // 24 // minhyo 8
#define LCDC_PCLK		(LCDC_FB_XRES+LCDC_HBP+LCDC_HPW+LCDC_HFP)*(LCDC_FB_YRES+LCDC_VBP+LCDC_VPW+LCDC_VFP)*2 // *3
#else
#define LCDC_FB_XRES	240
#define LCDC_FB_YRES	320
#define LCDC_HBP		8
#define LCDC_HPW		12
#define LCDC_HFP		8
#define LCDC_VBP		8
#define LCDC_VPW		12
#define LCDC_VFP		8
#endif

static int __init lcdc_s6d04m0_panel_init(void)
{
	int ret;
	struct msm_panel_info *pinfo;

#ifdef CONFIG_FB_MSM_TRY_MDDI_CATCH_LCDC_PRISM
	if (msm_fb_detect_client("lcdc_s6d04m0_qvga"))
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

	pinfo = &s6d04m0_panel_data.panel_info;
	pinfo->xres = LCDC_FB_XRES;
	pinfo->yres = LCDC_FB_YRES;
#if defined(CONFIG_MACH_LUCAS)
	pinfo->height = 42;
	pinfo->width = 57;
#else
	pinfo->height = 57;
	pinfo->width = 42;
#endif
	pinfo->type = LCDC_PANEL;
	pinfo->pdest = DISPLAY_1;
	pinfo->wait_cycle = 0;
	pinfo->bpp = 24;
	pinfo->fb_num = 2;
#if defined(CONFIG_MACH_LUCAS)
	pinfo->clk_rate = (9388 * 1000); // 8192000;
#else	
	pinfo->clk_rate = 8192000;
#endif
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

module_init(lcdc_s6d04m0_panel_init);
