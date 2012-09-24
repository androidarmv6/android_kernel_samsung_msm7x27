/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.
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
 *
 */

//PCAM 1/5" s5k5ccff

#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <media/msm_camera.h>
#include <mach/gpio.h>


#include "s5k5ccff.h"
#include <mach/camera.h>
#include <mach/vreg.h>
#include <linux/io.h>


#define SENSOR_DEBUG 0


//#define CONFIG_LOAD_FILE


#define S5K5CCFF_BURST_WRITE_LIST(A)	s5k5ccff_sensor_burst_write_list(A,(sizeof(A) / sizeof(A[0])),#A);
#define S5K5CCFF_WRITE_LIST(A)			s5k5ccff_sensor_write_list(A,(sizeof(A) / sizeof(A[0])),#A);



static char first_start_camera = 1;//  1 is not init a sensor

static char mEffect = 0;
static char mBrightness = 0;
static char mContrast = 0;
static char mSaturation = 0;
static char mSharpness = 0;
static char mWhiteBalance = 0;
static char mISO = 0;
static char mAutoExposure = 0;
static char mScene = 0;
static char mAfMode = 0;
static char mDTP = 0;
static char mInit = 0;
static char mMode = 0;


struct s5k5ccff_work {
	struct work_struct work;
};

static struct  s5k5ccff_work *s5k5ccff_sensorw;
static struct  i2c_client *s5k5ccff_client;

struct s5k5ccff_ctrl {
	const struct msm_camera_sensor_info *sensordata;
};


static struct s5k5ccff_ctrl *s5k5ccff_ctrl;

static DECLARE_WAIT_QUEUE_HEAD(s5k5ccff_wait_queue);
DECLARE_MUTEX(s5k5ccff_sem);
static int16_t s5k5ccff_effect = CAMERA_EFFECT_OFF;

/*=============================================================
	EXTERNAL DECLARATIONS
==============================================================*/
extern struct s5k5ccff_reg s5k5ccff_regs;
extern int cpufreq_direct_set_policy(unsigned int cpu, const char *buf);
extern void pcam_msm_i2c_pwr_mgmt(struct i2c_adapter *adap, int on);
/*=============================================================*/

static int cam_hw_init(void);

void sensor_DTP_control(char value);

#ifdef CONFIG_LOAD_FILE
	static int s5k5ccff_regs_table_write(char *name);
#endif





static int s5k5ccff_sensor_read(unsigned short subaddr, unsigned short *data)
{
	int ret;
	unsigned char buf[2];
	struct i2c_msg msg = { s5k5ccff_client->addr, 0, 2, buf };
	
	buf[0] = (subaddr >> 8);
	buf[1] = (subaddr & 0xFF);

	ret = i2c_transfer(s5k5ccff_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) 
		goto error;

	msg.flags = I2C_M_RD;
	
	ret = i2c_transfer(s5k5ccff_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) 
		goto error;

	*data = ((buf[0] << 8) | buf[1]);

error:
	return ret;
}

static int s5k5ccff_sensor_write(unsigned short subaddr, unsigned short val)
{
	unsigned char buf[4];
	struct i2c_msg msg = { s5k5ccff_client->addr, 0, 4, buf };

//	printk("[PGH] on write func s5k5ccff_client->addr : %x\n", s5k5ccff_client->addr);
//	printk("[PGH] on write func  s5k5ccff_client->adapter->nr : %d\n", s5k5ccff_client->adapter->nr);


	buf[0] = (subaddr >> 8);
	buf[1] = (subaddr & 0xFF);
	buf[2] = (val >> 8);
	buf[3] = (val & 0xFF);

	return i2c_transfer(s5k5ccff_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
}



static int s5k5ccff_sensor_write_list(struct samsung_short_t *list,int size, char *name)	
{
	int ret = 0;

#ifdef CONFIG_LOAD_FILE	
	ret = s5k5ccff_regs_table_write(name);
#else
	int i = 0;

	printk("<=PCAM=> s5k5ccff_sensor_write_list : %s\n", name);


	for (i = 0; i < size; i++)
	{
	//	printk("[PGH] %x      %x\n", list[i].subaddr, list[i].value);

		if(list[i].subaddr == 0xffff)
		{
//			printk("<=PCAM=> now SLEEP!!!!\n  %d", list[i].value);
			msleep(list[i].value);
		}
		else
		{
		    if(s5k5ccff_sensor_write(list[i].subaddr, list[i].value) < 0)
		    {
			    printk("<=PCAM=> sensor_write_list fail...-_-\n");
			    return -1;
		    }
		}
	}


#endif
	return ret;
}


#define BURST_MODE_BUFFER_MAX_SIZE 2700
unsigned char s5k5ccff_buf_for_burstmode[BURST_MODE_BUFFER_MAX_SIZE];
static int s5k5ccff_sensor_burst_write_list(struct samsung_short_t *list,int size, char *name)	
{
	int err = -EINVAL;
	int i = 0;
	int idx = 0;

	unsigned short subaddr = 0, next_subaddr = 0;
	unsigned short value = 0;

	struct i2c_msg msg = {  s5k5ccff_client->addr, 0, 0, s5k5ccff_buf_for_burstmode};
	


	for (i = 0; i < size; i++)
	{

		if(idx > (BURST_MODE_BUFFER_MAX_SIZE-10))
		{
			printk("<=PCAM=> BURST MODE buffer overflow!!!\n");
			 return err;
		}



		subaddr = list[i].subaddr;

		if(subaddr == 0x0F12)
			next_subaddr = list[i+1].subaddr;

		value = list[i].value;
		

		switch(subaddr)
		{

			case 0x0F12:
			{
				// make and fill buffer for burst mode write
				if(idx ==0) 
				{
					s5k5ccff_buf_for_burstmode[idx++] = 0x0F;
					s5k5ccff_buf_for_burstmode[idx++] = 0x12;
				}
				s5k5ccff_buf_for_burstmode[idx++] = value>> 8;
				s5k5ccff_buf_for_burstmode[idx++] = value & 0xFF;

			
			 	//write in burstmode	
				if(next_subaddr != 0x0F12)
				{
					msg.len = idx;
					err = i2c_transfer(s5k5ccff_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
					//printk("s5k4ecgx_sensor_burst_write, idx = %d\n",idx);
					idx=0;
				}
				
			}
			break;

			case 0xFFFF:
			{
				msleep(value);
			}
			break;
		
			default:
			{
			    idx = 0;
			    err = s5k5ccff_sensor_write(subaddr, value);
			}
			break;
			
		}

		
	}

	if (unlikely(err < 0))
	{
		printk("<=PCAM=>%s: register set failed\n",__func__);
		return err;
	}
	return 0;

}






void sensor_effect_control(char value)
{

	//int *i2c_clk_addr; //TEMP Dirty Code, Do not use it!
	//i2c_clk_addr = 0xd500c004;

	switch(value)
	{
		case PCAM_EFFECT_NORMAL :{
		PCAM_DEBUG("PCAM_EFFECT_NORMAL");
		S5K5CCFF_WRITE_LIST(s5k5ccff_effect_off);
		}
		break;		

		case PCAM_EFFECT_NEGATIVE :{
		PCAM_DEBUG("PCAM_EFFECT_NEGATIVE");
		S5K5CCFF_WRITE_LIST(s5k5ccff_effect_negative);
		}
		break;	
		
		case PCAM_EFFECT_MONO :{
		PCAM_DEBUG("PCAM_EFFECT_MONO");
		S5K5CCFF_WRITE_LIST(s5k5ccff_effect_mono);
		}
		break;	

		case PCAM_EFFECT_SEPIA :{
		PCAM_DEBUG("PCAM_EFFECT_SEPIA");
		S5K5CCFF_WRITE_LIST(s5k5ccff_effect_sepia);
		}
		break;	

		default :{
			printk("<=PCAM=> Unexpected Effect mode : %d\n",  value);
		}
		break;
				
	}

}


void sensor_whitebalance_control(char value)
{
	switch(value)
	{
		case PCAM_WB_AUTO :{
		PCAM_DEBUG("PCAM_WB_AUTO");
		S5K5CCFF_WRITE_LIST(s5k5ccff_wb_auto);
		}
		break;	

		case PCAM_WB_DAYLIGHT :{
		PCAM_DEBUG("PCAM_WB_DAYLIGHT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_wb_daylight);
		}
		break;	

		case PCAM_WB_CLOUDY :{
		PCAM_DEBUG("PCAM_WB_CLOUDY");
		S5K5CCFF_WRITE_LIST(s5k5ccff_wb_cloudy);
		}
		break;	

		case PCAM_WB_FLUORESCENT :{
		PCAM_DEBUG("PCAM_WB_FLUORESCENT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_wb_fluorescent);
		}
		break;	
		
		case PCAM_WB_INCANDESCENT :{
		PCAM_DEBUG("PCAM_WB_INCANDESCENT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_wb_incandescent);
		}
		break;	

		default :{
			printk("<=PCAM=> Unexpected WB mode : %d\n",  value);
		}
		break;
		
	}// end of switch

}


void sensor_brightness_control(char value)
{
	switch(value)
	{
		case PCAM_BR_STEP_P_4 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_4");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_p_4);
		}
		break;
		
		case PCAM_BR_STEP_P_3 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_3");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_p_3);
		}
		break;

		case PCAM_BR_STEP_P_2 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_p_2);
		}
		break;

		case PCAM_BR_STEP_P_1 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_p_1);
		}
		break;

		case PCAM_BR_STEP_0 :{
		PCAM_DEBUG("PCAM_BR_STEP_0");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_0);
		}
		break;

		case PCAM_BR_STEP_M_1 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_m_1);
		}
		break;

		case PCAM_BR_STEP_M_2 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_m_2);
		}
		break;

		case PCAM_BR_STEP_M_3 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_3");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_m_3);
		}
		break;

		case PCAM_BR_STEP_M_4 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_4");
		S5K5CCFF_WRITE_LIST(s5k5ccff_brightness_m_4);
		}
		break;


		default :{
			printk("<=PCAM=> Unexpected BR mode : %d\n",  value);
		}
		break;

	}
	
}


void sensor_iso_control(char value)
{
	switch(value)
	{
		case PCAM_ISO_AUTO :{
		PCAM_DEBUG("PCAM_ISO_AUTO");
		S5K5CCFF_WRITE_LIST(s5k5ccff_iso_auto);
		}
		break;

		case PCAM_ISO_50 :{
		PCAM_DEBUG("PCAM_ISO_50");
		S5K5CCFF_WRITE_LIST(s5k5ccff_iso_50);
		}
		break;

		case PCAM_ISO_100 :{
		PCAM_DEBUG("PCAM_ISO_100");
		S5K5CCFF_WRITE_LIST(s5k5ccff_iso_100);
		}
		break;

		case PCAM_ISO_200 :{
		PCAM_DEBUG("PCAM_ISO_200");
		S5K5CCFF_WRITE_LIST(s5k5ccff_iso_200);
		}
		break;

		case PCAM_ISO_400 :{
		PCAM_DEBUG("PCAM_ISO_400");
		S5K5CCFF_WRITE_LIST(s5k5ccff_iso_400);
		}
		break;

		default :{
			printk("<=PCAM=> Unexpected ISO mode : %d\n",  value);
		}
		break;
		
	}

}


void sensor_metering_control(char value)
{
	switch(value)
	{
		case PCAM_METERING_NORMAL :{
		PCAM_DEBUG("PCAM_METERING_NORMAL");
		S5K5CCFF_WRITE_LIST(s5k5ccff_metering_normal);
		}
		break;
		
		case PCAM_METERING_SPOT :{
		PCAM_DEBUG("PCAM_METERING_SPOT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_metering_spot);
		}
		break;

		case PCAM_METERING_CENTER :{
		PCAM_DEBUG("PCAM_METERING_CENTER");
		S5K5CCFF_WRITE_LIST(s5k5ccff_metering_center);
		}
		break;

		default :{
			printk("<=PCAM=> Unexpected METERING mode : %d\n",  value);
		}
		break;
	}

}


void sensor_scene_control(char value)
{
	switch(value)
	{
		case PCAM_SCENE_OFF :{
		PCAM_DEBUG("PCAM_SCENE_OFF");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);
		}
		break;

		case PCAM_SCENE_PORTRAIT :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);
		PCAM_DEBUG("PCAM_SCENE_PORTRAIT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_portrait);
		}
		break;

		case PCAM_SCENE_LANDSCAPE :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);
		PCAM_DEBUG("PCAM_SCENE_LANDSCAPE");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_landscape);
		}
		break;

		case PCAM_SCENE_SPORTS :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);
		PCAM_DEBUG("PCAM_SCENE_SPORTS");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_sports);
		}
		break;

		case PCAM_SCENE_PARTY :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);		
		PCAM_DEBUG("PCAM_SCENE_PARTY");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_party);			
		}
		break;

		case PCAM_SCENE_BEACH :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);		
		PCAM_DEBUG("PCAM_SCENE_BEACH");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_beach);
		}
		break;

		case PCAM_SCENE_SUNSET :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);	
		PCAM_DEBUG("PCAM_SCENE_SUNSET");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_sunset);
		}
		break;
		
		case PCAM_SCENE_DAWN :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);			
		PCAM_DEBUG("PCAM_SCENE_DAWN");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_dawn);	
		}
		break;

		case PCAM_SCENE_FALL :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);						
		PCAM_DEBUG("PCAM_SCENE_FALL");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_fall);		
		}
		break;

		case PCAM_SCENE_NIGHTSHOT :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);
		PCAM_DEBUG("PCAM_SCENE_NIGHTSHOT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_nightshot);			
		}
		break;

		case PCAM_SCENE_BACKLIGHT :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);	
		PCAM_DEBUG("PCAM_SCENE_BACKLIGHT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_backlight);
		}
		break;

		case PCAM_SCENE_FIREWORK :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);		
		PCAM_DEBUG("PCAM_SCENE_FIREWORK");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_firework);				
		}
		break;

		case PCAM_SCENE_TEXT :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);					
		PCAM_DEBUG("PCAM_SCENE_TEXT");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_text);
		}
		break;

		case PCAM_SCENE_CANDLE :{
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_off);							
		PCAM_DEBUG("PCAM_SCENE_CANDLE");
		S5K5CCFF_WRITE_LIST(s5k5ccff_scene_candle);	
		}
		break;

		default :{
			printk("<=PCAM=> Unexpected SCENE mode : %d\n",  value);
		}
		break;				
	}
}


void sensor_contrast_control(char value)
{
	switch(value)
	{
		case PCAM_CR_STEP_M_2 :{
		PCAM_DEBUG("PCAM_CR_STEP_M_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_contrast_m_2);
		}
		break;

		case PCAM_CR_STEP_M_1 :{
		PCAM_DEBUG("PCAM_CR_STEP_M_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_contrast_m_1);	
		}
		break;

		case PCAM_CR_STEP_0 :{
		PCAM_DEBUG("PCAM_CR_STEP_0");
		S5K5CCFF_WRITE_LIST(s5k5ccff_contrast_0);
		}
		break;

		case PCAM_CR_STEP_P_1 :{
		PCAM_DEBUG("PCAM_CR_STEP_P_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_contrast_p_1);
		}
		break;

		case PCAM_CR_STEP_P_2 :{
		PCAM_DEBUG("PCAM_CR_STEP_P_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_contrast_p_2);
		}
		break;

		default :{
			printk("<=PCAM=> Unexpected PCAM_CR_CONTROL mode : %d\n",  value);
		}
		break;												
	}
}


void sensor_saturation_control(char value)
{
	switch(value)
	{
		case PCAM_SA_STEP_M_2 :{
		PCAM_DEBUG("PCAM_SA_STEP_M_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_saturation_m_2);
		}
		break;

		case PCAM_SA_STEP_M_1 :{
		PCAM_DEBUG("PCAM_SA_STEP_M_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_saturation_m_1);		
		}
		break;

		case PCAM_SA_STEP_0 :{
		PCAM_DEBUG("PCAM_SA_STEP_0");
		S5K5CCFF_WRITE_LIST(s5k5ccff_saturation_0);
		}
		break;

		case PCAM_SA_STEP_P_1 :{
		PCAM_DEBUG("PCAM_SA_STEP_P_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_saturation_p_1);
		}
		break;

		case PCAM_SA_STEP_P_2 :{
		PCAM_DEBUG("PCAM_SA_STEP_P_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_saturation_p_2);
		}
		break;

		default :{
			printk("<=PCAM=> Unexpected PCAM_SA_CONTROL mode : %d\n",  value);
		}
		break;					
	}

}


void sensor_sharpness_control(char value)
{
	switch(value)
	{
		case PCAM_SP_STEP_M_2 :{
		PCAM_DEBUG("PCAM_SP_STEP_M_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_sharpness_m_2);
		}
		break;

		case PCAM_SP_STEP_M_1 :{
		PCAM_DEBUG("PCAM_SP_STEP_M_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_sharpness_m_1);		
		}
		break;

		case PCAM_SP_STEP_0 :{
		PCAM_DEBUG("PCAM_SP_STEP_0");
		S5K5CCFF_WRITE_LIST(s5k5ccff_sharpness_0);	
		}
		break;

		case PCAM_SP_STEP_P_1 :{
		PCAM_DEBUG("PCAM_SP_STEP_P_1");
		S5K5CCFF_WRITE_LIST(s5k5ccff_sharpness_p_1);			
		}
		break;

		case PCAM_SP_STEP_P_2 :{
		PCAM_DEBUG("PCAM_SP_STEP_P_2");
		S5K5CCFF_WRITE_LIST(s5k5ccff_sharpness_p_2);			
		}
		break;

		default :{
			printk("<=PCAM=> Unexpected PCAM_SP_CONTROL mode : %d\n",  value);
		}
		break;					
	}
}


int sensor_af_control(char value)
{
	switch(value)
	{

		case PCAM_AF_CHECK_STATUS :{
		}
		break;
		
		case PCAM_AF_OFF :{
		}
		break;

		case PCAM_AF_SET_NORMAL :{
		}
		break;

		case PCAM_AF_SET_MACRO :{
		}
		break;

		case PCAM_AF_DO :{
		}
		break;


		default :{
			printk("<=PCAM=> unexpected AF command : %d\n",value);
		}		
		break;
		
	}	
	return;

}



void sensor_DTP_control(char value)
{
	switch(value)
	{
		case PCAM_DTP_OFF:{
		PCAM_DEBUG("DTP OFF");
		S5K5CCFF_WRITE_LIST(s5k5ccff_dtp_off);
		}
		break;

		case PCAM_DTP_ON:{
		PCAM_DEBUG("DTP ON");
		S5K5CCFF_WRITE_LIST(s5k5ccff_dtp_on);
		}
		break;

		default:{
		printk("<=PCAM=> unexpected DTP control on PCAM\n");
		}
		break;
	}
}





void sensor_rough_control(void __user *arg)
{

	ioctl_pcam_info_8bit		ctrl_info;


	PCAM_DEBUG("START");


	if(copy_from_user((void *)&ctrl_info, (const void *)arg, sizeof(ctrl_info)))
	{
		printk("<=PCAM=> %s fail copy_from_user!\n", __func__);
	}

/*
	printk("<=PCAM=> TEST %d %d %d %d %d \n", ctrl_info.mode, ctrl_info.address,\
	 ctrl_info.value_1, ctrl_info.value_2, ctrl_info.value_3);
*/

	switch(ctrl_info.mode)
	{
		case PCAM_AUTO_TUNNING:
		break;

		
		case PCAM_SDCARD_DETECT:
		break;

		case PCAM_GET_INFO:{
			unsigned short lsb, msb, rough_iso;					
			s5k5ccff_sensor_write(0xFCFC, 0xD000);					
			s5k5ccff_sensor_write(0x002C, 0x7000);
			s5k5ccff_sensor_write(0x002E, 0x2A14);
			s5k5ccff_sensor_read(0x0F12, &lsb); 		//0x2A14
			s5k5ccff_sensor_read(0x0F12, &msb);		//0x2A16
			s5k5ccff_sensor_read(0x0F12, &rough_iso); //0x2A8
													
			ctrl_info.value_1 = lsb;					
			ctrl_info.value_2 = msb;	
			//printk("<=PCAM=> exposure %x %x \n", lsb, msb);
			ctrl_info.value_3 = rough_iso;	
			//printk("<=PCAM=> rough_iso %x \n", rough_iso);			
		}
		break;

		case PCAM_FRAME_CONTROL:
		{
			switch(ctrl_info.value_1)
			{

				case PCAM_FRAME_AUTO :{
				PCAM_DEBUG("PCAM_FRAME_AUTO");		
				}					
				break;
				
				case PCAM_FRAME_FIX_15 :{
				PCAM_DEBUG("PCAM_FRAME_FIX_15");
				S5K5CCFF_WRITE_LIST(s5k5ccff_fps_15fix);		
				}
				break;

				case PCAM_FRAME_FIX_30 :{
				printk("PCAM_FRAME_FIX_30");
				PCAM_DEBUG("PCAM_FRAME_FIX_30");
				S5K5CCFF_WRITE_LIST(s5k5ccff_fps_30fix);	
				}
				break;


				default :{
					printk("<=PCAM=> Unexpected PCAM_FRAME_CONTROL mode : %d\n", ctrl_info.value_1);
				}
				break;				
			
			}
		}
		break;


		case PCAM_AF_CONTROL:
		{
			mAfMode= ctrl_info.value_1;
			ctrl_info.value_3 = sensor_af_control(mAfMode);
		}
		break;

		
		case PCAM_EFFECT_CONTROL:
		{
			mEffect = ctrl_info.value_1;
			sensor_effect_control(mEffect);
				
			
		}// end of PCAM_EFFECT_CONTROL
		break;


		case PCAM_WB_CONTROL:
		{
			mWhiteBalance = ctrl_info.value_1;
			sensor_whitebalance_control(mWhiteBalance);
			

		}//end of PCAM_WB_CONTROL
		break;


		case PCAM_BR_CONTROL:
		{
			mBrightness = ctrl_info.value_1;
			if(mInit)
				sensor_brightness_control(mBrightness);
			
		}//end of PCAM_BR_CONTROL
		break;

		case PCAM_ISO_CONTROL:
		{
			mISO = ctrl_info.value_1;
			sensor_iso_control(mISO);
	
		}
		break;


		case PCAM_METERING_CONTROL:
		{
			mAutoExposure = ctrl_info.value_1;
			sensor_metering_control(mAutoExposure);
			
		}//end of case
		break;


		case PCAM_SCENE_CONTROL:
		{
			mScene = ctrl_info.value_1;
			sensor_scene_control(mScene);

		}
		break;


		case PCAM_AWB_AE_CONTROL:
		{
			printk("<=PCAM=> PCAM_AWB_AE_CONTROL skip~~~\n");
			/*
			switch(ctrl_info.value_1)
			{
				case PCAM_AWB_AE_LOCK :{
				PCAM_DEBUG("PCAM_AWB_AE_LOCK");
				s5k5ccff_sensor_write_list(s5k5ccff_awb_ae_lock , S5K5CCFF_AWB_AE_LOCK_REGS, \
				"s5k5ccff_awb_ae_lock"); 					
				}
				break;

				case PCAM_AWB_AE_UNLOCK :{
				PCAM_DEBUG("PCAM_AWB_AE_UNLOCK");
				s5k5ccff_sensor_write_list(s5k5ccff_awb_ae_unlock , S5K5CCFF_AWB_AE_UNLOCK_REGS, \
				"s5k5ccff_awb_ae_unlock"); 
					
				}
				break;

				default :{
					printk("<=PCAM=> Unexpected AWB_AE mode : %d\n", ctrl_info.value_1);
				}
				break;						
				
			}
			*/
		}
		break;
			
		case PCAM_CR_CONTROL:
		{
			mContrast = ctrl_info.value_1;
			if(mInit)
				sensor_contrast_control(mContrast);

		}
		break;
			

		case PCAM_SA_CONTROL:
		{
			mSaturation = ctrl_info.value_1;
			if(mInit)
				sensor_saturation_control(mSaturation);
			
		}
		break;

		

		case PCAM_SP_CONTROL:
		{
			mSharpness = ctrl_info.value_1;
			if(mInit)
				sensor_sharpness_control(mSharpness);
			
		}
		break;

		case PCAM_CPU_CONTROL:
		{

			switch(ctrl_info.value_1)
			{
				case PCAM_CPU_CONSERVATIVE:{
				PCAM_DEBUG("now conservative");
				cpufreq_direct_set_policy(0, "conservative");
				}
				break;

				case PCAM_CPU_ONDEMAND:{
				PCAM_DEBUG("now ondemand");
				cpufreq_direct_set_policy(0, "ondemand");
				}
				break;	

				case PCAM_CPU_PERFORMANCE:{
				PCAM_DEBUG("now performance");
				cpufreq_direct_set_policy(0, "performance");
				}
				break;
				
				default:{
					printk("<=PCAM=> unexpected CPU control on PCAM\n");
				}
				break;
			}
		}
		break;

		case PCAM_DTP_CONTROL:
		{
			if(mInit == 0)
			{
				if(ctrl_info.value_1 == 0)
					ctrl_info.value_3 = 2;

				else if(ctrl_info.value_1 == 1)
					ctrl_info.value_3 = 3;

				mDTP = 1;
			}

			else
			{
				sensor_DTP_control(ctrl_info.value_1);

				if(ctrl_info.value_1 == 0)
					ctrl_info.value_3 = 2;

				else if(ctrl_info.value_1 == 1)
					ctrl_info.value_3 = 3;
			
				mDTP = 0;
			}

		}
		break;

		case PCAM_SET_PREVIEW_SIZE:
		{
			mMode = ctrl_info.value_1;
		}
		break;


		default :{
			printk("<=PCAM=> Unexpected mode on sensor_rough_control : %d\n", ctrl_info.mode);
		}
		break;
	}



	if(copy_to_user((void *)arg, (const void *)&ctrl_info, sizeof(ctrl_info)))
	{
		printk("<=PCAM=> %s fail on copy_to_user!\n", __func__);
	}
	
}










void cam_pw(int status)
{
        struct vreg *vreg_cam_out8_vddio;
        struct vreg *vreg_cam_out9_vdda;
        struct vreg *vreg_cam_out10_vddreg;
        //struct vreg *vreg_cam_out4; //AF

        vreg_cam_out8_vddio		= vreg_get(NULL, "ldo8");
        vreg_cam_out9_vdda		= vreg_get(NULL, "ldo9");
        vreg_cam_out10_vddreg	= vreg_get(NULL, "ldo10");
        //vreg_cam_out4 = vreg_get(NULL, "ldo4");




	if(status == 1) //POWER ON
	{
		PCAM_DEBUG("POWER ON");
		//vreg_set_level(vreg_cam_out4,  OUT2800mV);
		vreg_set_level(vreg_cam_out9_vdda,  OUT2800mV);		// VDDA 2.8V
		vreg_set_level(vreg_cam_out10_vddreg, OUT1200mV);	// VDD_REG 1.2V		
		vreg_set_level(vreg_cam_out8_vddio,  OUT2800mV);		// VDDIO 2.8V		

		vreg_enable(vreg_cam_out9_vdda);
		udelay(1);
		vreg_enable(vreg_cam_out10_vddreg);
		udelay(1);
		vreg_enable(vreg_cam_out8_vddio);				

	   // vreg_enable(vreg_cam_out4);
	}
	else //POWER OFF
	{
		PCAM_DEBUG("POWER OFF");
		vreg_disable(vreg_cam_out8_vddio);
		udelay(1);
		vreg_disable(vreg_cam_out10_vddreg);
		udelay(1);
		vreg_disable(vreg_cam_out9_vdda);
		//vreg_disable(vreg_cam_out4); //AF 2800
	}
	
}



static int cam_hw_init()
{

	int rc = 0;
	unsigned short	id = 0; //CAM FOR FW
//	unsigned int	before_time, after_time, i;//I2C SPEED TEST

	PCAM_DEBUG("next cam_hw_init");


	/* Input MCLK = 24MHz */
	msm_camio_clk_rate_set(24000000);
	msm_camio_camif_pad_reg_reset();
	udelay(1);
	
	//TASS NOT USE gpio_set_value(1, 1); //STBY UP   
	gpio_set_value(0, 1); //RESET UP   


#if 0//PGH I2C SPEED TEST
        before_time = get_jiffies_64();
    for (i = 0; i < 3000; i++) 
        {
		s5k5ccff_sensor_write(0x002E, 0x0040);
        }       
 
        after_time = get_jiffies_64();
        printk("<=PCAM=> Total Time 3000: %d\n",  jiffies_to_msecs(after_time-before_time));
#endif//PGH I2C SPEED TEST



	s5k5ccff_sensor_write(0x002C, 0x0000);
	s5k5ccff_sensor_write(0x002E, 0x0040);
	s5k5ccff_sensor_read(0x0F12, &id);


	if(id != 0x05CC)
	{
		printk("<=PCAM=> [TASS] WRONG SENSOR FW => id 0x%x \n", id);
		//rc = -1;
	}
	else
		printk("<=PCAM=> [TASS] CURRENT SENSOR FW => id 0x%x \n", id);

	return rc;
}







static long s5k5ccff_set_effect(int mode, int effect)
{
	long rc = 0;

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
	    	PCAM_DEBUG("SENSOR_PREVIEW_MODE");
		break;

	case SENSOR_SNAPSHOT_MODE:
		PCAM_DEBUG("SENSOR_SNAPSHOT_MODE");
		break;

	default:
		printk("[PGH] %s default\n", __func__);
		break;
	}

	switch (effect) {
	case CAMERA_EFFECT_OFF: {
	PCAM_DEBUG("CAMERA_EFFECT_OFF");
	}
			break;

	case CAMERA_EFFECT_MONO: {
	PCAM_DEBUG("CAMERA_EFFECT_MONO");
	}
		break;

	case CAMERA_EFFECT_NEGATIVE: {
	PCAM_DEBUG("CAMERA_EFFECT_NEGATIVE");
	}
		break;

	case CAMERA_EFFECT_SOLARIZE: {
	PCAM_DEBUG("CAMERA_EFFECT_SOLARIZE");
	}
		break;

	case CAMERA_EFFECT_SEPIA: {
	PCAM_DEBUG("CAMERA_EFFECT_SEPIA");
	}
		break;

	default: {
	printk("<=PCAM=> unexpeceted effect  %s/%d\n", __func__, __LINE__);
		return -EINVAL;
	}
	
	}
	s5k5ccff_effect = effect;
	
	return rc;
}

static long s5k5ccff_set_sensor_mode(int mode)
{
	//long rc = 0;
	unsigned short	msb, lsb;
	int base_high, base_low, cur_lux;
	char vsync_value, cnt;

	unsigned int	before_time, after_time, i, time_gab;//I2C SPEED TEST

	int *i2c_clk_addr; //TEMP Dirty Code, Do not use it!

	PCAM_DEBUG("START");
	i2c_clk_addr = 0xd500c004;

	if(first_start_camera)
	{
		printk("<=PCAM=> camera init for TASS ver0.1");

		//i2c_clk_addr = 0xd500c004;
		//printk("<=PCAM=> i2c clk :%x\n", readl(i2c_clk_addr));

		before_time = get_jiffies_64();


		#if defined(CONFIG_LOAD_FILE)
		S5K5CCFF_WRITE_LIST(s5k5ccff_init0);
		#else
		S5K5CCFF_BURST_WRITE_LIST(s5k5ccff_init0);
		#endif


		after_time = get_jiffies_64();
		time_gab = jiffies_to_msecs(after_time-before_time);

		if(time_gab > 280)
		{
			printk("<=PCAM=> i2c speed is going down : %dmsec\n", time_gab);

			pcam_msm_i2c_pwr_mgmt(s5k5ccff_client->adapter, 1);
			//this funcion have to call after clk_enable by PCAM, do not use it without pcam's allowance
			pcam_msm_i2c_pwr_mgmt(s5k5ccff_client->adapter, 1);
			
			//this funcion have to call after clk_enable by PCAM, do not use it without pcam's allowance
			printk("<=PCAM=> i2c clk set forcely 0x316\n");
			writel(0x316, i2c_clk_addr);
			printk("<=PCAM=> re-check i2c clk :%x\n", readl(i2c_clk_addr));

		    }
		else
		{
			printk("<=PCAM=> init speed is fine : %dmsec\n", time_gab);
		}

		first_start_camera = 0;
		mInit = 1;
	} 



	switch (mode) {
	case SENSOR_PREVIEW_MODE:
	{
		PCAM_DEBUG("PREVIEW~~~");

		/*
		if(mMode)
		{
			printk("<=PCAM=> now CAMCORDER MODE~~~~~~~~~\n");	
			S5K5CCFF_WRITE_LIST(s5k5ccff_camcorder_set);	
			S5K5CCFF_WRITE_LIST(s5k5ccff_fps_30fix);	
		}
		else
		{
			printk("<=PCAM=> now CAMERA MODE~~~~~~~~~\n");
		}
		*/


		if((mScene == PCAM_SCENE_NIGHTSHOT) ||(mScene == PCAM_SCENE_FIREWORK) )
		{
			for(cnt=0; cnt<1200; cnt++)
			{
				vsync_value = gpio_get_value(14);

				if(vsync_value)
					break;
				else
				{
					PCAM_DEBUG(" wait cnt:%d vsync_value:%d\n", cnt, vsync_value);
					msleep(1);
				}
		
			}

	
		}

		if(mDTP == 1)
		{
			S5K5CCFF_WRITE_LIST(s5k5ccff_dtp_on);		
		}
		else
		{
			S5K5CCFF_WRITE_LIST(s5k5ccff_preview);	
		}


		if(mScene == PCAM_SCENE_OFF)
			sensor_effect_control(mEffect);

		sensor_scene_control(mScene);

		//if(mScene != PCAM_SCENE_SPORTS && mScene != PCAM_SCENE_NIGHTSHOT)
		//	sensor_iso_control(mISO);			

		if(mScene == PCAM_SCENE_OFF)
		{
		    sensor_brightness_control(mBrightness);
		    sensor_metering_control(mAutoExposure);
		    sensor_contrast_control(mContrast);
		    sensor_saturation_control(mSaturation);
		    sensor_sharpness_control(mSharpness);
		    sensor_whitebalance_control(mWhiteBalance);
		    //sensor_af_control(mAfMode);
		}

		
	}
		break;
		
	case SENSOR_SNAPSHOT_MODE:
	{
		PCAM_DEBUG("SNAPSHOT~~~");

		msb = lsb = 0;
		cur_lux = 0;

		s5k5ccff_sensor_write(0xFCFC, 0xD000);
		s5k5ccff_sensor_write(0x002C, 0x7000);
		s5k5ccff_sensor_write(0x002E, 0x2A3C);
		s5k5ccff_sensor_read(0x0F12, &lsb);
		s5k5ccff_sensor_read(0x0F12, &msb);

		cur_lux = (msb<<16) | lsb;
		printk("cur_lux : 0x%08x \n", cur_lux);


		for(cnt=0; cnt<700; cnt++)
		{
			vsync_value = gpio_get_value(14);

			if(vsync_value)
				break;
			else
			{
				printk(" on snapshot,  wait cnt:%d vsync_value:%d\n", cnt, vsync_value);			
				PCAM_DEBUG(" on snapshot,  wait cnt:%d vsync_value:%d\n", cnt, vsync_value);
				msleep(3);
			}
	
		}


		if(cur_lux > 0xFFFE)
		{
			PCAM_DEBUG("HighLight Snapshot!\n");
			printk("HighLight Snapshot!\n");			
			S5K5CCFF_WRITE_LIST(s5k5ccff_high_snapshot);				
		}
		else if(cur_lux < 0x0020)
		{
			if((mScene == PCAM_SCENE_NIGHTSHOT) ||(mScene == PCAM_SCENE_FIREWORK) )
			{
				PCAM_DEBUG("Night Snapshot!\n");
				printk("Night Snapshot!\n");			
				S5K5CCFF_WRITE_LIST(s5k5ccff_night_snapshot);								
			}
			else
			{
				PCAM_DEBUG("LowLight Snapshot delay ~~~~!\n");
				printk("LowLight Snapshot 500...sec!\n");
				S5K5CCFF_WRITE_LIST(s5k5ccff_lowlight_snapshot);
			}
		}
		else
		{
			PCAM_DEBUG("Normal Snapshot!\n");
			printk("Normal Snapshot!\n");		
			S5K5CCFF_WRITE_LIST(s5k5ccff_snapshot);
		}
		
		
	}
	break;

	case SENSOR_RAW_SNAPSHOT_MODE:
		PCAM_DEBUG("RAW_SNAPSHOT NOT SUPPORT!!");
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int s5k5ccff_sensor_init_probe(const struct msm_camera_sensor_info *data)
{
	int rc = 0;

	return rc;
}

#ifdef CONFIG_LOAD_FILE

#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>

#include <asm/uaccess.h>

static char *s5k5ccff_regs_table = NULL;

static int s5k5ccff_regs_table_size;

void s5k5ccff_regs_table_init(void)
{
	struct file *filp;
	char *dp;
	long l;
	loff_t pos;
//	int i;
	int ret;
	mm_segment_t fs = get_fs();

	printk("%s %d\n", __func__, __LINE__);

	set_fs(get_ds());
#if 0
	filp = filp_open("/data/camera/s5k5ccff.h", O_RDONLY, 0);
#else
	filp = filp_open("/mnt/sdcard/s5k5ccff.h", O_RDONLY, 0);
#endif
	if (IS_ERR(filp)) {
		printk("file open error\n");
		return;
	}
	l = filp->f_path.dentry->d_inode->i_size;	
	printk("l = %ld\n", l);
	dp = kmalloc(l, GFP_KERNEL);
	if (dp == NULL) {
		printk("Out of Memory\n");
		filp_close(filp, current->files);
	}
	pos = 0;
	memset(dp, 0, l);
	ret = vfs_read(filp, (char __user *)dp, l, &pos);
	if (ret != l) {
		printk("Failed to read file ret = %d\n", ret);
		kfree(dp);
		filp_close(filp, current->files);
		return;
	}

	filp_close(filp, current->files);
	
	set_fs(fs);

	s5k5ccff_regs_table = dp;
	
	s5k5ccff_regs_table_size = l;

	*((s5k5ccff_regs_table + s5k5ccff_regs_table_size) - 1) = '\0';

//	printk("s5k5ccff_regs_table 0x%x, %ld\n", dp, l);
}

void s5k5ccff_regs_table_exit(void)
{
	printk("%s %d\n", __func__, __LINE__);
	if (s5k5ccff_regs_table) {
		kfree(s5k5ccff_regs_table);
		s5k5ccff_regs_table = NULL;
	}	
}

static int s5k5ccff_regs_table_write(char *name)
{
	char *start, *end, *reg;//, *data;	
	unsigned short addr, value;
	char reg_buf[7], data_buf[7];

	addr = value = 0;

	*(reg_buf + 6) = '\0';
	*(data_buf + 6) = '\0';

	start = strstr(s5k5ccff_regs_table, name);
	
	end = strstr(start, "};");

	while (1) {	
		/* Find Address */	
		reg = strstr(start,"{0x");		
		if (reg)
			start = (reg + 16);
		if ((reg == NULL) || (reg > end))
			break;
		/* Write Value to Address */	
		if (reg != NULL) {
			memcpy(reg_buf, (reg + 1), 6);	
			memcpy(data_buf, (reg + 9), 6);	
			addr = (unsigned short)simple_strtoul(reg_buf, NULL, 16); 
			value = (unsigned short)simple_strtoul(data_buf, NULL, 16); 
//			printk("addr 0x%04x, value 0x%04x\n", addr, value);
			if (addr == 0xffff)
			{
				msleep(value);
				printk("delay 0x%04x, value 0x%04x\n", addr, value);
			}	
			else
			{
				if( s5k5ccff_sensor_write(addr, value) < 0 )
				{
					printk("<=PCAM=> %s fail on sensor_write\n", __func__);
				}
			}
		}
		else
			printk("<=PCAM=> EXCEPTION! reg value : %c  addr : 0x%x,  value : 0x%x\n", *reg, addr, value);
	}

	return 0;
}
#endif



int s5k5ccff_sensor_init(const struct msm_camera_sensor_info *data)
{
	int rc = 0;

	s5k5ccff_ctrl = kzalloc(sizeof(struct s5k5ccff_ctrl), GFP_KERNEL);
	if (!s5k5ccff_ctrl) {
		CDBG("s5k5ccff_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	if (data)
		s5k5ccff_ctrl->sensordata = data;

	rc = cam_hw_init();
	if(rc < 0)
	{
		printk("<=PCAM=> cam_fw_init failed!\n");
		goto init_fail;
	}

#ifdef CONFIG_LOAD_FILE
	s5k5ccff_regs_table_init();
#endif	

	rc = s5k5ccff_sensor_init_probe(data);
	if (rc < 0) {
		CDBG("s5k5ccff_sensor_init failed!\n");
		goto init_fail;
	}

init_done:
	return rc;

init_fail:
	kfree(s5k5ccff_ctrl);
	return rc;
}

static int s5k5ccff_init_client(struct i2c_client *client)
{
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&s5k5ccff_wait_queue);
	return 0;
}

int s5k5ccff_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cfg_data;
	long   rc = 0;

	if (copy_from_user(&cfg_data,
			(void *)argp,
			sizeof(struct sensor_cfg_data)))
		return -EFAULT;

	/* down(&s5k5ccff_sem); */

	CDBG("s5k5ccff_ioctl, cfgtype = %d, mode = %d\n",
		cfg_data.cfgtype, cfg_data.mode);

		switch (cfg_data.cfgtype) {
		case CFG_SET_MODE:
			rc = s5k5ccff_set_sensor_mode(
						cfg_data.mode);
			break;

		case CFG_SET_EFFECT:
			rc = s5k5ccff_set_effect(cfg_data.mode,
						cfg_data.cfg.effect);
			break;

		case CFG_GET_AF_MAX_STEPS:
		default:
			rc = -EINVAL;
			break;
		}

	/* up(&s5k5ccff_sem); */

	return rc;
}

int s5k5ccff_sensor_release(void)
{
	int rc = 0;
        //int *switch_i2c_addr; //TEMP Dirty Code, Do not use it!


	first_start_camera = 1;

	//If did not init below that, it can keep the previous status. it depend on concept by PCAM
	mEffect = 0;
	mBrightness = 0;
	mContrast = 0;
	mSaturation = 0;
	mSharpness = 0;
	mWhiteBalance = 0;
	mISO = 0;
	mAutoExposure = 0;
	mScene = 0;
	//mAfMode = 0;
	mDTP = 0;
	mInit = 0;


	//TEMP Dirty Code, Do not use it! PCAM...
        //switch_i2c_addr = 0xd500c010;
        //writel(1, switch_i2c_addr);

	printk("<=PCAM=> s5k5ccff_sensor_release\n");

	kfree(s5k5ccff_ctrl);
	/* up(&s5k5ccff_sem); */

#ifdef CONFIG_LOAD_FILE
	s5k5ccff_regs_table_exit();
#endif

	return rc;
}

static int s5k5ccff_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;


	
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		rc = -ENOTSUPP;
		goto probe_failure;
	}

	s5k5ccff_sensorw =
		kzalloc(sizeof(struct s5k5ccff_work), GFP_KERNEL);

	if (!s5k5ccff_sensorw) {
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, s5k5ccff_sensorw);
	s5k5ccff_init_client(client);
	s5k5ccff_client = client;


	CDBG("s5k5ccff_probe succeeded!\n");

	return 0;

probe_failure:
	kfree(s5k5ccff_sensorw);
	s5k5ccff_sensorw = NULL;
	CDBG("s5k5ccff_probe failed!\n");
	return rc;
}

static const struct i2c_device_id s5k5ccff_i2c_id[] = {
	{ "s5k5ccff", 0},
	{ },
};

static struct i2c_driver s5k5ccff_i2c_driver = {
	.id_table = s5k5ccff_i2c_id,
	.probe  = s5k5ccff_i2c_probe,
	.remove = __exit_p(s5k5ccff_i2c_remove),
	.driver = {
		.name = "s5k5ccff",
	},
};

static int s5k5ccff_sensor_probe(const struct msm_camera_sensor_info *info,
				struct msm_sensor_ctrl *s)
{

	int rc = i2c_add_driver(&s5k5ccff_i2c_driver);
	if (rc < 0 || s5k5ccff_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_done;
	}


#if 0//PCAM
	rc = s5k5ccff_sensor_init_probe(info);
	if (rc < 0)
		goto probe_done;
#endif
	gpio_set_value(0, 0);//RESET
	gpio_set_value(1, 0);//STBY
	cam_pw(0);


	s->s_init = s5k5ccff_sensor_init;
	s->s_release = s5k5ccff_sensor_release;
	s->s_config  = s5k5ccff_sensor_config;

probe_done:
	CDBG("%s %s:%d\n", __FILE__, __func__, __LINE__);
	return rc;
}

static int __s5k5ccff_probe(struct platform_device *pdev)
{
	return msm_camera_drv_start(pdev, s5k5ccff_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
	.probe = __s5k5ccff_probe,
	.driver = {
		.name = "msm_camera_s5k5ccff",
		.owner = THIS_MODULE,
	},
};

static int __init s5k5ccff_init(void)
{
	return platform_driver_register(&msm_camera_driver);
}

module_init(s5k5ccff_init);
