/*
 * Copyright (C) 2010 MEMSIC, Inc.
 *
 * Initial Code:
 *	Robbie Cao
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/mm.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sysctl.h>
#include <asm/uaccess.h>
#include <mach/vreg.h>

#include <linux/i2c/mmc31xx.h>

#define DEBUG					0
#define MAX_FAILURE_COUNT		3

#define MMC31XX_DELAY_TM		10	/* ms */
#define MMC31XX_DELAY_SET		10	/* ms */
#define MMC31XX_DELAY_RST		10	/* ms */

/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#define READMD			1
#define MMC32XX_DELAY_TM		10	/* ms */
#define MMC32XX_DELAY_RM	      10 /* ms */

#define MMC31XX_DELAY_STDN	1	/* ms */

#define MMC31XX_RETRY_COUNT	3
#define MMC31XX_RESET_INTV	10

#define MMC31XX_DEV_NAME	"mmc31xx"
// HW_REV_00 : ldo3 HW_REV_01 : ldo4
#if defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS)
#define LDO_LCD				"ldo4"
#else
#define LDO_LCD				"ldo3"
#endif

static u32 read_idx = 0;
struct class *mag_class;

static struct i2c_client *this_client;

/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
extern int board_hw_revision;

static int mmc31xx_i2c_rx_data(char *buf, int len)
{
	uint8_t i;
	struct i2c_msg msgs[] = {
		{
			.addr	= this_client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= buf,
		},
		{
			.addr	= this_client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= buf,
		}
	};

	for (i = 0; i < MMC31XX_RETRY_COUNT; i++) {
		if (i2c_transfer(this_client->adapter, msgs, 2) >= 0) {
			break;
		}
		mdelay(10);
	}

	if (i >= MMC31XX_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, MMC31XX_RETRY_COUNT);
		return -EIO;
	}

	return 0;
}

static int mmc31xx_i2c_tx_data(char *buf, int len)
{
	uint8_t i;
	struct i2c_msg msg[] = {
		{
			.addr	= this_client->addr,
			.flags	= 0,
			.len	= len,
			.buf	= buf,
		}
	};
	
	for (i = 0; i < MMC31XX_RETRY_COUNT; i++) {
		if (i2c_transfer(this_client->adapter, msg, 1) >= 0) {
			break;
		}
		mdelay(10);
	}

	if (i >= MMC31XX_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, MMC31XX_RETRY_COUNT);
		return -EIO;
	}
	
	return 0;
}

/*************************************************************************/
/*						BMA023 Sysfs						   */
/*************************************************************************/
static ssize_t mmc31xx_fs_read(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned char data[16] = {0};
	int vec[3] = {0};
	int count;
	int res = 0;

	// Write 0x00000010 to 0x00000000

	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
		data[0] = MMC32XX_REG_CTRL;      
		data[1] = MMC32XX_CTRL_RM | MMC32XX_CTRL_NOBOOST;
	}
	else
	{	
		data[0] = MMC31XX_REG_CTRL;      
		data[1] = MMC31XX_CTRL_SET;
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
   	data[0] = MMC32XX_REG_CTRL;      
		data[1] = MMC32XX_CTRL_RM | MMC32XX_CTRL_NOBOOST;
#else	// EUROPA, CALLISTO
		data[0] = MMC31XX_REG_CTRL;      
		data[1] = MMC31XX_CTRL_SET;
#endif		

	if (mmc31xx_i2c_tx_data(data, 2) < 0) {
		return 0;
	}
	/* wait external capacitor charging done for next SET/RESET */
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 )
	{
		msleep(MMC32XX_DELAY_RM);	
	}
	else
	{
		msleep(MMC31XX_DELAY_SET);	
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		msleep(MMC32XX_DELAY_RM);	
#else	// EUROPA, CALLISTO
		msleep(MMC31XX_DELAY_SET);	
#endif		

	/* [HSS] Charge pump reset before TM command (MMC3280) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
		data[0] = MMC32XX_REG_CTRL;        
		data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
		mmc31xx_i2c_tx_data(data, 2);
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
	data[0] = MMC32XX_REG_CTRL;        
	data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
	mmc31xx_i2c_tx_data(data, 2);
#endif
	// Write 0x00000001 to 0x00000000
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{	
      	data[0] = MMC32XX_REG_CTRL;      
       	data[1] = MMC31XX_CTRL_TM | MMC32XX_CTRL_NOBOOST;
	}
	else
	{   
       	data[0] = MMC31XX_REG_CTRL;
       	data[1] = MMC31XX_CTRL_TM;
  }
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
      	data[0] = MMC32XX_REG_CTRL;
       	data[1] = MMC31XX_CTRL_TM | MMC32XX_CTRL_NOBOOST;      
#else	// EUROPA, CALLISTO
       	data[0] = MMC31XX_REG_CTRL;
       	data[1] = MMC31XX_CTRL_TM;
#endif		
	res = mmc31xx_i2c_tx_data(data, 2);

	/* wait TM done for coming data read */

	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
		msleep(MMC32XX_DELAY_TM);	   
       	data[0] = MMC32XX_REG_DATA;      
	}
	else
	{  
		msleep(MMC31XX_DELAY_TM);	
		data[0] = MMC31XX_REG_DATA;
   	}           
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		msleep(MMC32XX_DELAY_TM);	   
   	data[0] = MMC32XX_REG_DATA;      
#else	// EUROPA, CALLISTO
		msleep(MMC31XX_DELAY_TM);	
    data[0] = MMC31XX_REG_DATA;
#endif		
	if (mmc31xx_i2c_rx_data(data, 6) < 0) {
		return 0;
	}
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 	
	{
		vec[0] = data[1] << 8 | data[0];
		vec[1] = data[3] << 8 | data[2];
		vec[2] = data[5] << 8 | data[4];
	}
	else
	{
		vec[0] = data[0] << 8 | data[1];
		vec[1] = data[2] << 8 | data[3];
		vec[2] = data[4] << 8 | data[5];
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		vec[0] = data[1] << 8 | data[0];
		vec[1] = data[3] << 8 | data[2];
		vec[2] = data[5] << 8 | data[4];
#else	// EUROPA, CALLISTO
		vec[0] = data[0] << 8 | data[1];
		vec[1] = data[2] << 8 | data[3];
		vec[2] = data[4] << 8 | data[5];
#endif		
#if DEBUG
	printk("[X - %04x] [Y - %04x] [Z - %04x]\n", 
		vec[0], vec[1], vec[2]);
#endif

    printk("x: %d,y: %d,z: %d\n", vec[0], vec[1], vec[2]);
	count = sprintf(buf,"%d,%d,%d\n", vec[0], vec[1], vec[2]);

	return count;
}

static ssize_t mmc31xx_fs_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	//buf[size]=0;
	printk("input data --> %s\n", buf);

	return size;
}

static ssize_t mmc31xx_power_on(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned char data[16] = {0};	
	int count;
	int res = 0;

	/* [HSS] Charge pump reset before TM command (MMC3280) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
		data[0] = MMC32XX_REG_CTRL;        
		data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
		mmc31xx_i2c_tx_data(data, 2);
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
	data[0] = MMC32XX_REG_CTRL;        
	data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
	mmc31xx_i2c_tx_data(data, 2);
#endif

	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{	
       	data[0] = MMC32XX_REG_CTRL;      
		data[1] = MMC31XX_CTRL_TM | MMC32XX_CTRL_NOBOOST;
	}
	else
	{   
       	data[0] = MMC31XX_REG_CTRL;
		data[1] = MMC31XX_CTRL_TM;
  }
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
 	data[0] = MMC32XX_REG_CTRL;  
	data[1] = MMC31XX_CTRL_TM | MMC32XX_CTRL_NOBOOST;    
#else	// EUROPA, CALLISTO
	data[0] = MMC31XX_REG_CTRL;
	data[1] = MMC31XX_CTRL_TM;
#endif		

	res = mmc31xx_i2c_tx_data(data, 2);

	/* wait TM done for coming data read */
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 	
	{	
		msleep(MMC32XX_DELAY_TM);
	}
	else
	{
		msleep(MMC31XX_DELAY_TM);
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		msleep(MMC32XX_DELAY_TM);
#else	// EUROPA, CALLISTO
		msleep(MMC31XX_DELAY_TM);
#endif		

#if DEBUG
	printk("[%s] result of i2c writing: %d\n", __func__, !(res < 0));
#endif
	count = sprintf(buf,"%d\n", !(res < 0));

	return count;
}
static DEVICE_ATTR(read_mag, S_IRUGO | S_IWUSR | S_IWGRP, mmc31xx_fs_read, mmc31xx_fs_write);
static DEVICE_ATTR(power_on, S_IRUGO, mmc31xx_power_on, NULL);

static int mmc31xx_open(struct inode *inode, struct file *file)
{
	return nonseekable_open(inode, file);
}

static int mmc31xx_release(struct inode *inode, struct file *file)
{
	return 0;
}

static int mmc31xx_ioctl(struct inode *inode, struct file *file, 
	unsigned int cmd, unsigned long arg)
{
	void __user *pa = (void __user *)arg;
	unsigned char data[16] = {0};
	int vec[3] = {0};

	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
   	int MD_times = 0;
    static int RM_Cnt =0;
	switch (cmd) {
	case MMC31XX_IOC_TM:
	/* [HSS] Charge pump reset before TM command (MMC3280) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
		data[0] = MMC32XX_REG_CTRL;        
		data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
		mmc31xx_i2c_tx_data(data, 2);
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
	data[0] = MMC32XX_REG_CTRL;        
	data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
	mmc31xx_i2c_tx_data(data, 2);
#endif	
       	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
       	if ( board_hw_revision >= 2 ) 
       	{	
          	data[0] = MMC32XX_REG_CTRL;      
			data[1] = MMC31XX_CTRL_TM | MMC32XX_CTRL_NOBOOST;
       	}
       	else
       	{   
          	data[0] = MMC31XX_REG_CTRL;
			data[1] = MMC31XX_CTRL_TM;
       	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
  	data[0] = MMC32XX_REG_CTRL;    
	data[1] = MMC31XX_CTRL_TM | MMC32XX_CTRL_NOBOOST;	  
#else	// EUROPA, CALLISTO
  	data[0] = MMC31XX_REG_CTRL;
	data[1] = MMC31XX_CTRL_TM;	
#endif		
		if (mmc31xx_i2c_tx_data(data, 2) < 0) {
			return -EFAULT;
		}
		/* wait TM done for coming data read */
		/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
		if ( board_hw_revision >= 2 ) 	
		{
			msleep(MMC32XX_DELAY_TM);
		}
		else
		{		
			msleep(MMC31XX_DELAY_TM);
		}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		msleep(MMC32XX_DELAY_TM);
#else	// EUROPA, CALLISTO
		msleep(MMC31XX_DELAY_TM);
#endif		
		break;
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
	case MMC31XX_IOC_SET: /* [HSS] MMC3140 only */
		data[0] = MMC31XX_REG_CTRL;
		data[1] = MMC31XX_CTRL_SET;
		if (mmc31xx_i2c_tx_data(data, 2) < 0) {
			return -EFAULT;
		}
		/* wait external capacitor charging done for next SET/RESET */
		msleep(MMC31XX_DELAY_SET);
		break;
	case MMC31XX_IOC_RESET:  /* [HSS] MMC3140 only */
		data[0] = MMC31XX_REG_CTRL;
		data[1] = MMC31XX_CTRL_RST;
		if (mmc31xx_i2c_tx_data(data, 2) < 0) {
			return -EFAULT;
		}
		/* wait external capacitor charging done for next SET/RESET */
		msleep(MMC31XX_DELAY_RST);
		break;
	case MMC31XX_IOC_RM:  /* [HSS] MMC3280 only */
		data[0] = MMC32XX_REG_CTRL;
		data[1] = MMC32XX_CTRL_RM | MMC32XX_CTRL_NOBOOST;
		if (mmc31xx_i2c_tx_data(data, 2) < 0) {
			return -EFAULT;
		}
		/* wait external capacitor charging done for next SET/RESET */
		msleep(MMC32XX_DELAY_RM);
		break;		
	case MMC31XX_IOC_READ:
     	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
      	if ( board_hw_revision >= 2 ) 
      	{   
          	data[0] = MMC32XX_REG_DATA;      
      	}
      	else
      	{  
           	data[0] = MMC31XX_REG_DATA;
      	}       
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
    	data[0] = MMC32XX_REG_DATA;      
#else	// EUROPA, CALLISTO
     	data[0] = MMC31XX_REG_DATA;
#endif		
		if (mmc31xx_i2c_rx_data(data, 6) < 0) {
			return -EFAULT;
		}
		/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
		if ( board_hw_revision >= 2 ) 	
		{		
				vec[0] = data[1] << 8 | data[0];
				vec[1] = data[3] << 8 | data[2];
				vec[2] = data[5] << 8 | data[4];
		}		
		else
		{		
				vec[0] = data[0] << 8 | data[1];
				vec[1] = data[2] << 8 | data[3];
				vec[2] = data[4] << 8 | data[5];
		}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
				vec[0] = data[1] << 8 | data[0];
				vec[1] = data[3] << 8 | data[2];
				vec[2] = data[5] << 8 | data[4];
#else	// EUROPA, CALLISTO
				vec[0] = data[0] << 8 | data[1];
				vec[1] = data[2] << 8 | data[3];
				vec[2] = data[4] << 8 | data[5];
#endif		
	#if DEBUG
		printk("[X - %04x] [Y - %04x] [Z - %04x]\n", 
			vec[0], vec[1], vec[2]);
	#endif
		if (copy_to_user(pa, vec, sizeof(vec))) {
			return -EFAULT;
		}
		break;
	case MMC31XX_IOC_READXYZ:
		/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if (defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
		if ( board_hw_revision >= 2 ) /* [HSS] H/W REV >= 2 (REV0.1) :  MMC3280 */ 	
		{
#endif	// CONFIG_MACH_COOPER
			/* do RM every MMC328X_RESET_INTV times read */
	//		if (!(read_idx % MMC31XX_RESET_INTV)) {
			if ( (RM_Cnt%20) == 0) {
				/* RM */
				data[0] = MMC32XX_REG_CTRL;
				data[1] = MMC32XX_CTRL_RM | MMC32XX_CTRL_NOBOOST;
				/* not check return value here, assume it always OK */
				mmc31xx_i2c_tx_data(data, 2);
				/* wait external capacitor charging done for next RM */
				msleep(MMC32XX_DELAY_RM);
				RM_Cnt = 0;
			}
	               RM_Cnt++;
			/* [HSS] Charge pump reset before TM command (MMC3280) */
			data[0] = MMC32XX_REG_CTRL;        
			data[1] = MMC32XX_CTRL_CHARGERST | MMC32XX_CTRL_NOBOOST;
			mmc31xx_i2c_tx_data(data, 2);
      
			/* send TM cmd before read */
			data[0] = MMC32XX_REG_CTRL;
			data[1] = MMC31XX_CTRL_TM;
			/* not check return value here, assume it always OK */
			mmc31xx_i2c_tx_data(data, 2);
			/* wait TM done for coming data read */
			msleep(MMC32XX_DELAY_TM);
#if READMD
			/* Read MD */
			data[0] = MMC32XX_REG_DS;
			if (mmc31xx_i2c_rx_data(data, 1) < 0) {
				return -EFAULT;
			}
			while (!(data[0] & 0x01)) {
				msleep(1);
				/* Read MD again*/
				data[0] = MMC32XX_REG_DS;
				if (mmc31xx_i2c_rx_data(data, 1) < 0) {
					return -EFAULT;
				}
				if (data[0] & 0x01) break;
				MD_times++;
				if (MD_times > 2) {
			#if DEBUG
					printk("TM not work!!");
			#endif
					return -EFAULT;
				}
			}
#endif		
			/* read xyz raw data */
			read_idx++;
			data[0] = MMC32XX_REG_DATA;
			if (mmc31xx_i2c_rx_data(data, 6) < 0) {
				return -EFAULT;
			}
			vec[0] = data[1] << 8 | data[0];
			vec[1] = data[3] << 8 | data[2];
			vec[2] = data[5] << 8 | data[4];
		#if DEBUG
			printk("[X - %04x] [Y - %04x] [Z - %04x]\n", 
				vec[0], vec[1], vec[2]);
		#endif
			if (copy_to_user(pa, vec, sizeof(vec))) {
				return -EFAULT;
			}
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
		}
		else     /* [HSS] H/W REV < 2 (REV0.1) :  MMC3140 */
#endif	// CONFIG_MACH_COOPER
#else
		{	
			/* do RESET/SET every MMC31XX_RESET_INTV times read */
			if ((read_idx >= MMC31XX_RESET_INTV)) {
				/* RESET */
				data[0] = MMC31XX_REG_CTRL;
				data[1] = MMC31XX_CTRL_RST;
				/* not check return value here, assume it always OK */
				mmc31xx_i2c_tx_data(data, 2);
#if DEBUG
				printk(KERN_ERR "RESET\n");
#endif
				/* wait external capacitor charging done for next SET/RESET */
				msleep(MMC31XX_DELAY_SET);
				/* SET */
				data[0] = MMC31XX_REG_CTRL;
				data[1] = MMC31XX_CTRL_SET;
				/* not check return value here, assume it always OK */
				mmc31xx_i2c_tx_data(data, 2);
#if DEBUG
				printk(KERN_ERR "SET\n");	
#endif
				msleep(MMC31XX_DELAY_STDN);
				read_idx = 0;
			}

			/* send TM cmd before read */
			data[0] = MMC31XX_REG_CTRL;
			data[1] = MMC31XX_CTRL_TM;
			/* not check return value here, assume it always OK */
			if(mmc31xx_i2c_tx_data(data, 2) < 0){
				printk(KERN_ERR "[mmc31xx] i2c write is failed\n");
				return -EFAULT;
			}
#if 0
			printk(KERN_ERR "[mmc31xx] i2c read ctl reg before delay\n");
			data[0] = MMC31XX_REG_CTRL;
			if (mmc31xx_i2c_rx_data(data, 2) < 0) {
				printk(KERN_ERR "[mmc31xx] i2c read is failed\n");
				return -EFAULT;
			}
			printk("[mmc31xx] before data[0] = %x\n", data[0]);
			/* wait TM done for coming data read */
#endif
			msleep(MMC31XX_DELAY_TM);		
#if 0
			printk(KERN_ERR "[mmc31xx] i2c read ctl reg after delay\n");
			data[0] = MMC31XX_REG_CTRL;
			if (mmc31xx_i2c_rx_data(data, 2) < 0) {
				printk(KERN_ERR "[mmc31xx] i2c read is failed\n");
				return -EFAULT;
			}
			printk("[mmc31xx] after data[0] = %x\n", data[0]);
#endif
			/* read xyz raw data */
			read_idx++;
			data[0] = MMC31XX_REG_DATA;
			if (mmc31xx_i2c_rx_data(data, 6) < 0) {
				printk(KERN_ERR "[mmc31xx] i2c read is failed\n");
				return -EFAULT;
			}
			vec[0] = data[0] << 8 | data[1];
			vec[1] = data[2] << 8 | data[3];
			vec[2] = data[4] << 8 | data[5];
#if DEBUG
			printk("[X - %04x] [Y - %04x] [Z - %04x]\n", 
				vec[0], vec[1], vec[2]);
#endif
			if (copy_to_user(pa, vec, sizeof(vec))) {
				return -EFAULT;
			}
		}
#endif	// (defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		break;
	default:
		break;
	}

	return 0;
}

static ssize_t mmc31xx_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	ssize_t ret = 0;

	sprintf(buf, "MMC31XX");
	ret = strlen(buf) + 1;

	return ret;
}

static DEVICE_ATTR(mmc31xx, S_IRUGO, mmc31xx_show, NULL);

static struct file_operations mmc31xx_fops = {
	.owner	= THIS_MODULE,
	.open	= mmc31xx_open,
	.release	= mmc31xx_release,
	.ioctl		= mmc31xx_ioctl,
};

static struct miscdevice mmc31xx_device = {
	.minor 	= MISC_DYNAMIC_MINOR,
	.name 	= MMC31XX_DEV_NAME,
	.fops 	= &mmc31xx_fops,
};

int mmc31xx_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct vreg *mmc31xx_vreg;
	unsigned char data[16] = {0};
	int res = 0;

	printk(KERN_ERR "[mmc31xx_probe] +\n");
	
/* [HSS] PMIC LDO depends on each model's H/W. */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
  	/* [HSS] [Cooper] PMIC LDO Change - VLCD_3.0V : ldo3 => ldo4 (REV0.2) */
	if(board_hw_revision < 5)
	{
		if(board_hw_revision >= 3)
			mmc31xx_vreg = vreg_get(0, "ldo4");
		else
			mmc31xx_vreg = vreg_get(0, "ldo3");
	}
#elif defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
    // HW_REV_00 : ldo3 HW_REV_01 : ldo4
	if(board_hw_revision < 2)
		mmc31xx_vreg = vreg_get(0, "ldo4");
#elif defined(CONFIG_MACH_LUCAS)
        // HW_REV_00 : ldo3 HW_REV_01 : ldo4
	mmc31xx_vreg = vreg_get(0, "ldo4");
#else
	mmc31xx_vreg = vreg_get(0, "ldo3");
#endif		
		
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("%s: functionality check failed\n", __FUNCTION__);
		res = -ENODEV;
		goto out;
	}
	this_client = client;

	res = misc_register(&mmc31xx_device);
	if (res) {
		pr_err("%s: mmc31xx_device register failed\n", __FUNCTION__);
		goto out;
	}
	res = device_create_file(&client->dev, &dev_attr_mmc31xx);
	if (res) {
		pr_err("%s: device_create_file failed\n", __FUNCTION__);
		goto out_deregister;
	}
	
	// Power On	
#if defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
	if(board_hw_revision < 2){
		if(vreg_enable(mmc31xx_vreg))
			printk(KERN_ERR "vreg_enable: VLCD_3.0V vreg operation failed\n");
	}
#elif defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if(board_hw_revision < 5) {
		if(vreg_enable(mmc31xx_vreg))
			printk(KERN_ERR "vreg_enable: VLCD_3.0V operation failed\n");
	}
#else
	if(vreg_enable(mmc31xx_vreg))
		printk(KERN_ERR "vreg_enable: VLCD_3.0V operation failed\n");
#endif

	/* send ST cmd to mag sensor first of all */
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
      	data[0] = MMC32XX_REG_CTRL;      
		data[1] = MMC32XX_CTRL_RM | MMC32XX_CTRL_NOBOOST;
	}
	else
	{	
       	data[0] = MMC31XX_REG_CTRL;      
		data[1] = MMC31XX_CTRL_SET;
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
   	data[0] = MMC32XX_REG_CTRL;      
		data[1] = MMC32XX_CTRL_RM | MMC32XX_CTRL_NOBOOST;
#else	// EUROPA, CALLISTO
		data[0] = MMC31XX_REG_CTRL;      
		data[1] = MMC31XX_CTRL_SET;
#endif		
	
	if (mmc31xx_i2c_tx_data(data, 2) < 0) {
		/* assume SET always success */
		printk(KERN_ERR "[mmc31xx] mmc31xx set is failed\n");		
	}
	/* wait external capacitor charging done for next SET/RESET */
	/* [HSS][Cooper] Magnetic sensor change : MMC3140 -> MMC3280 (since REV0.1) */	
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if ( board_hw_revision >= 2 ) 
	{
		msleep(MMC32XX_DELAY_RM);
	}
	else
	{	
		msleep(MMC31XX_DELAY_SET);
	}
#elif (defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) || defined(CONFIG_MACH_LUCAS))
		msleep(MMC32XX_DELAY_RM);
#else	// EUROPA, CALLISTO
		msleep(MMC31XX_DELAY_SET);
#endif		

	printk(KERN_ERR "[mmc31xx_probe] -\n");

	return 0;

out_deregister:
	misc_deregister(&mmc31xx_device);
out:
	return res;
}

static int mmc31xx_remove(struct i2c_client *client)
{
	device_remove_file(&client->dev, &dev_attr_mmc31xx);
	misc_deregister(&mmc31xx_device);

	return 0;
}

#ifdef CONFIG_PM
static int mmc31xx_suspend(struct i2c_client *client, pm_message_t mesg)
{
	struct vreg *mmc31xx_vreg;
  
/* [HSS] PMIC LDO depends on each model's H/W. */  
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
  	/* [HSS] [Cooper] PMIC LDO Change - VLCD_3.0V : ldo3 => ldo4 (REV0.2) */
	if(board_hw_revision < 5) {
		if(board_hw_revision >= 3)
			mmc31xx_vreg = vreg_get(0, "ldo4");
		else
			mmc31xx_vreg = vreg_get(0, "ldo3");
	}
#elif defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
    // HW_REV_00 : ldo3 HW_REV_01 : ldo4
	if(board_hw_revision < 2)
		mmc31xx_vreg = vreg_get(0, "ldo4");
#elif defined(CONFIG_MACH_LUCAS)
        // HW_REV_00 : ldo3 HW_REV_01 : ldo4
	mmc31xx_vreg = vreg_get(0, "ldo4");		
#else
	mmc31xx_vreg = vreg_get(0, "ldo3");
#endif	

#if defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
	if(board_hw_revision < 2) {
		if(vreg_disable(mmc31xx_vreg))
			printk(KERN_ERR "vreg_disable: VLCD_3.0V vreg operation failed\n");
	}
#elif defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if(board_hw_revision < 5) {
		if(vreg_disable(mmc31xx_vreg))
			printk(KERN_ERR "vreg_disable: VLCD_3.0V vreg operation failed\n");
	}
#else
	if(vreg_disable(mmc31xx_vreg))
		printk(KERN_ERR "vreg_disable: VLCD_3.0V vreg operation failed\n");
#endif	
	
#if DEBUG
	printk(KERN_INFO "[%s]\n",__FUNCTION__);
#endif

	return 0;
}

static int mmc31xx_resume(struct i2c_client *client)
{
	struct vreg *mmc31xx_vreg;

/* [HSS] PMIC LDO depends on each model's H/W. */
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)	
  	/* [HSS] [Cooper] PMIC LDO Change - VLCD_3.0V : ldo3 => ldo4 (REV0.2) */
	if(board_hw_revision < 5) {
		if(board_hw_revision >= 3)
			mmc31xx_vreg = vreg_get(0, "ldo4");
		else
			mmc31xx_vreg = vreg_get(0, "ldo3");
	}
#elif defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
    // HW_REV_00 : ldo3 HW_REV_01 : ldo4
	if(board_hw_revision < 2)
		mmc31xx_vreg = vreg_get(0, "ldo4");
#elif defined(CONFIG_MACH_LUCAS)
        // HW_REV_00 : ldo3 HW_REV_01 : ldo4
	mmc31xx_vreg = vreg_get(0, "ldo4");		
#else
	mmc31xx_vreg = vreg_get(0, "ldo3");
#endif	

#if defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT)
	if(board_hw_revision < 2) {	
		if(vreg_enable(mmc31xx_vreg))
			printk(KERN_ERR "vreg_enable: VLCD_3.0V vreg operation failed\n");			
	}
#elif defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
	if(board_hw_revision < 5) {
		if(vreg_enable(mmc31xx_vreg))
			printk(KERN_ERR "vreg_enable: VLCD_3.0V vreg operation failed\n");			
	}
#else
	if(vreg_enable(mmc31xx_vreg))
		printk(KERN_ERR "vreg_enable: VLCD_3.0V vreg operation failed\n");			
#endif
		
#if DEBUG
	printk(KERN_INFO "[%s]\n",__FUNCTION__);
#endif

	return 0;
}
#else
#define mmc31xx_suspend NULL
#define mmc31xx_resume NULL
#endif
static const struct i2c_device_id mmc31xx_id[] = {
	{ MMC31XX_I2C_NAME, 0 },
	{ }
};

static struct i2c_driver mmc31xx_driver = {
	.probe 		= mmc31xx_probe,
	.remove 	= mmc31xx_remove,
	.suspend	= mmc31xx_suspend,
	.resume		= mmc31xx_resume,
	.id_table	= mmc31xx_id,
	.driver 	= {
		.owner	= THIS_MODULE,
		.name	= MMC31XX_I2C_NAME,
	},
};


static int __init mmc31xx_init(void)
{
	struct device *dev_t;
	pr_info("mmc31xx driver: init\n");
	mag_class = class_create(THIS_MODULE, "magnetic");

	if (IS_ERR(mag_class)) 
		return PTR_ERR( mag_class );

	dev_t = device_create( mag_class, NULL, 0, "%s", "magnetic");

	if (device_create_file(dev_t, &dev_attr_read_mag) < 0)
		printk("Failed to create device file(%s)!\n", dev_attr_read_mag.attr.name);

	if (device_create_file(dev_t, &dev_attr_power_on) < 0)
		printk("Failed to create device file(%s)!\n", dev_attr_power_on.attr.name);

	if (IS_ERR(dev_t)) 
	{
		return PTR_ERR(dev_t);
	}
	return i2c_add_driver(&mmc31xx_driver);
}

static void __exit mmc31xx_exit(void)
{
	pr_info("mmc31xx driver: exit\n");
	i2c_del_driver(&mmc31xx_driver);
}

module_init(mmc31xx_init);
module_exit(mmc31xx_exit);

MODULE_AUTHOR("Robbie Cao<hjcao@memsic.com>");
MODULE_DESCRIPTION("MEMSIC MMC31XX Magnetic Sensor Driver");
MODULE_LICENSE("GPL");

