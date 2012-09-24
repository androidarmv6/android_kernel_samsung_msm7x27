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

//PCAM 1/5" s5k5ca

#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <media/msm_camera.h>
#include <mach/gpio.h>


#include "s5k5ca.h"
#include <mach/camera.h>
#include <mach/vreg.h>
#include <linux/io.h>


#define SENSOR_DEBUG 0


//#define CONFIG_LOAD_FILE

#define S5K5CA_BURST_WRITE_LIST(A)	s5k5ca_sensor_burst_write_list(A,ARRAY_SIZE(A),#A);


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


struct s5k5ca_work {
	struct work_struct work;
};

static struct  s5k5ca_work *s5k5ca_sensorw;
static struct  i2c_client *s5k5ca_client;

struct s5k5ca_ctrl {
	const struct msm_camera_sensor_info *sensordata;
};


static struct s5k5ca_ctrl *s5k5ca_ctrl;

static DECLARE_WAIT_QUEUE_HEAD(s5k5ca_wait_queue);
DECLARE_MUTEX(s5k5ca_sem);
static int16_t s5k5ca_effect = CAMERA_EFFECT_OFF;

/*=============================================================
	EXTERNAL DECLARATIONS
==============================================================*/
extern struct s5k5ca_reg s5k5ca_regs;
extern int cpufreq_direct_set_policy(unsigned int cpu, const char *buf);
extern void pcam_msm_i2c_pwr_mgmt(struct i2c_adapter *adap, int on);
extern int* get_i2c_clock_addr(struct i2c_adapter *adap);
/*=============================================================*/

static int cam_hw_init(void);

#ifdef CONFIG_LOAD_FILE
	static int s5k5ca_regs_table_write(char *name);
#endif




#if 0//ORG
static int s5k5ca_reset(const struct msm_camera_sensor_info *dev)
{
	int rc = 0;

	rc = gpio_request(dev->sensor_reset, "s5k5ca");

	if (!rc) {
		rc = gpio_direction_output(dev->sensor_reset, 0);
		mdelay(20);
		rc = gpio_direction_output(dev->sensor_reset, 1);
	}

	gpio_free(dev->sensor_reset);
	return rc;
}


static int32_t s5k5ca_i2c_txdata(unsigned short saddr,
	unsigned char *txdata, int length)
{
	struct i2c_msg msg[] = {
		{
			.addr = saddr,
			.flags = 0,
			.len = length,
			.buf = txdata,
		},
	};

#if SENSOR_DEBUG
	if (length == 2)
		CDBG("msm_io_i2c_w: 0x%04x 0x%04x\n",
			*(u16 *) txdata, *(u16 *) (txdata + 2));
	else if (length == 4)
		CDBG("msm_io_i2c_w: 0x%04x\n", *(u16 *) txdata);
	else
		CDBG("msm_io_i2c_w: length = %d\n", length);
#endif
	if (i2c_transfer(s5k5ca_client->adapter, msg, 1) < 0) {
		CDBG("s5k5ca_i2c_txdata failed\n");
		return -EIO;
	}

	return 0;
}

static int32_t s5k5ca_i2c_write(unsigned short saddr,
	unsigned short waddr, unsigned short wdata, enum s5k5ca_width width)
{
	int32_t rc = -EIO;
	unsigned char buf[4];

	memset(buf, 0, sizeof(buf));
	switch (width) {
	case WORD_LEN: {
		buf[0] = (waddr & 0xFF00)>>8;
		buf[1] = (waddr & 0x00FF);
		buf[2] = (wdata & 0xFF00)>>8;
		buf[3] = (wdata & 0x00FF);

		rc = s5k5ca_i2c_txdata(saddr, buf, 4);
	}
		break;

	case BYTE_LEN: {
		buf[0] = waddr;
		buf[1] = wdata;
		rc = s5k5ca_i2c_txdata(saddr, buf, 2);
	}
		break;

	default:
		break;
	}

	if (rc < 0)
		CDBG(
		"i2c_write failed, addr = 0x%x, val = 0x%x!\n",
		waddr, wdata);

	return rc;
}

static int32_t s5k5ca_i2c_write_table(
	struct s5k5ca_i2c_reg_conf const *reg_conf_tbl,
	int num_of_items_in_table)
{
	int i;
	int32_t rc = -EIO;

	for (i = 0; i < num_of_items_in_table; i++) {
		rc = s5k5ca_i2c_write(s5k5ca_client->addr,
			reg_conf_tbl->waddr, reg_conf_tbl->wdata,
			reg_conf_tbl->width);
		if (rc < 0)
			break;
		if (reg_conf_tbl->mdelay_time != 0)
			mdelay(reg_conf_tbl->mdelay_time);
		reg_conf_tbl++;
	}

	return rc;
}

static int s5k5ca_i2c_rxdata(unsigned short saddr,
	unsigned char *rxdata, int length)
{
	struct i2c_msg msgs[] = {
	{
		.addr   = saddr,
		.flags = 0,
		.len   = 2,
		.buf   = rxdata,
	},
	{
		.addr   = saddr,
		.flags = I2C_M_RD,
		.len   = length,
		.buf   = rxdata,
	},
	};

#if SENSOR_DEBUG
	if (length == 2)
		CDBG("msm_io_i2c_r: 0x%04x 0x%04x\n",
			*(u16 *) rxdata, *(u16 *) (rxdata + 2));
	else if (length == 4)
		CDBG("msm_io_i2c_r: 0x%04x\n", *(u16 *) rxdata);
	else
		CDBG("msm_io_i2c_r: length = %d\n", length);
#endif

	if (i2c_transfer(s5k5ca_client->adapter, msgs, 2) < 0) {
		CDBG("s5k5ca_i2c_rxdata failed!\n");
		return -EIO;
	}

	return 0;
}

static int32_t s5k5ca_i2c_read(unsigned short   saddr,
	unsigned short raddr, unsigned short *rdata, enum s5k5ca_width width)
{
	int32_t rc = 0;
	unsigned char buf[4];

	if (!rdata)
		return -EIO;

	memset(buf, 0, sizeof(buf));

	switch (width) {
	case WORD_LEN: {
		buf[0] = (raddr & 0xFF00)>>8;
		buf[1] = (raddr & 0x00FF);

		rc = s5k5ca_i2c_rxdata(saddr, buf, 2);
		if (rc < 0)
			return rc;

		*rdata = buf[0] << 8 | buf[1];
	}
		break;

	default:
		break;
	}

	if (rc < 0)
		CDBG("s5k5ca_i2c_read failed!\n");

	return rc;
}
#endif

#if 1//PGH
static int s5k5ca_sensor_read(unsigned short subaddr, unsigned short *data)
{
	int ret;
	unsigned char buf[2];
	struct i2c_msg msg = { s5k5ca_client->addr, 0, 2, buf };
	
	buf[0] = (subaddr >> 8);
	buf[1] = (subaddr & 0xFF);

	ret = i2c_transfer(s5k5ca_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) 
		goto error;

	msg.flags = I2C_M_RD;
	
	ret = i2c_transfer(s5k5ca_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) 
		goto error;

	*data = ((buf[0] << 8) | buf[1]);

error:
	return ret;
}
#endif//PGH

static int s5k5ca_sensor_write(unsigned short subaddr, unsigned short val)
{
	unsigned char buf[4];
	struct i2c_msg msg = { s5k5ca_client->addr, 0, 4, buf };

//	printk("[PGH] on write func s5k5ca_client->addr : %x\n", s5k5ca_client->addr);
//	printk("[PGH] on write func  s5k5ca_client->adapter->nr : %d\n", s5k5ca_client->adapter->nr);


	buf[0] = (subaddr >> 8);
	buf[1] = (subaddr & 0xFF);
	buf[2] = (val >> 8);
	buf[3] = (val & 0xFF);

	return i2c_transfer(s5k5ca_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
}

static int s5k5ca_sensor_write_list(struct samsung_short_t *list,int size, char *name)	
{
	int ret = 0;

#ifdef CONFIG_LOAD_FILE	
	ret = s5k5ca_regs_table_write(name);
#else
	int i = 0;

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
		    if(s5k5ca_sensor_write(list[i].subaddr, list[i].value) < 0)
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
unsigned char s5k5ca_buf_for_burstmode[BURST_MODE_BUFFER_MAX_SIZE];
static int s5k5ca_sensor_burst_write_list(struct samsung_short_t *list,int size, char *name)	
{
	int err = -EINVAL;
	int i = 0;
	int idx = 0;

	unsigned short subaddr = 0, next_subaddr = 0;
	unsigned short value = 0;

	struct i2c_msg msg = {  s5k5ca_client->addr, 0, 0, s5k5ca_buf_for_burstmode};
	


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
					s5k5ca_buf_for_burstmode[idx++] = 0x0F;
					s5k5ca_buf_for_burstmode[idx++] = 0x12;
				}
				s5k5ca_buf_for_burstmode[idx++] = value>> 8;
				s5k5ca_buf_for_burstmode[idx++] = value & 0xFF;

			
			 	//write in burstmode	
				if(next_subaddr != 0x0F12)
				{
					msg.len = idx;
					err = i2c_transfer(s5k5ca_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
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
			    err = s5k5ca_sensor_write(subaddr, value);
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





#if 1//PCAM
void sensor_effect_control(char value)
{
	switch(value)
	{
		case PCAM_EFFECT_NORMAL :{
		PCAM_DEBUG("PCAM_EFFECT_NORMAL");
		s5k5ca_sensor_write_list(s5k5ca_effect_off, S5K5CA_EFFECT_OFF_REGS,\
		 "s5k5ca_effect_off"); 
		}
		break;		

		case PCAM_EFFECT_NEGATIVE :{
		PCAM_DEBUG("PCAM_EFFECT_NEGATIVE");
		s5k5ca_sensor_write_list(s5k5ca_effect_negative, S5K5CA_EFFECT_NEGATIVE_REGS,\
		 "s5k5ca_effect_negative"); 
		}
		break;	
		
		case PCAM_EFFECT_MONO :{
		PCAM_DEBUG("PCAM_EFFECT_MONO");
		s5k5ca_sensor_write_list(s5k5ca_effect_mono, S5K5CA_EFFECT_MONO_REGS,\
		 "s5k5ca_effect_mono"); 
		}
		break;	

		case PCAM_EFFECT_SEPIA :{
		PCAM_DEBUG("PCAM_EFFECT_SEPIA");
		s5k5ca_sensor_write_list(s5k5ca_effect_sepia, S5K5CA_EFFECT_SEPIA_REGS,\
		 "s5k5ca_effect_sepia"); 
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
		s5k5ca_sensor_write_list(s5k5ca_wb_auto, S5K5CA_WB_AUTO_REGS,\
		 "s5k5ca_wb_auto"); 
		}
		break;	

		case PCAM_WB_DAYLIGHT :{
		PCAM_DEBUG("PCAM_WB_DAYLIGHT");
		s5k5ca_sensor_write_list(s5k5ca_wb_daylight, S5K5CA_WB_DAYLIGHT_REGS,\
		 "s5k5ca_wb_daylight"); 
		}
		break;	

		case PCAM_WB_CLOUDY :{
		PCAM_DEBUG("PCAM_WB_CLOUDY");
		s5k5ca_sensor_write_list(s5k5ca_wb_cloudy, S5K5CA_WB_CLOUDY_REGS,\
		 "s5k5ca_wb_cloudy"); 
		}
		break;	

		case PCAM_WB_FLUORESCENT :{
		PCAM_DEBUG("PCAM_WB_FLUORESCENT");
		s5k5ca_sensor_write_list(s5k5ca_wb_fluorescent, S5K5CA_WB_FLUORESCENT_REGS,\
		 "s5k5ca_wb_fluorescent"); 
		}
		break;	
		
		case PCAM_WB_INCANDESCENT :{
		PCAM_DEBUG("PCAM_WB_INCANDESCENT");
		s5k5ca_sensor_write_list(s5k5ca_wb_incandescent, S5K5CA_WB_INCANDESCENT_REGS,\
		 "s5k5ca_wb_incandescent"); 
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
		s5k5ca_sensor_write_list(s5k5ca_brightness_p_4, S5K5CA_BRIGHTNESS_P_4_REGS,\
		 "s5k5ca_brightness_p_4"); 
		}
		break;
		
		case PCAM_BR_STEP_P_3 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_3");
		s5k5ca_sensor_write_list(s5k5ca_brightness_p_3, S5K5CA_BRIGHTNESS_P_3_REGS,\
		 "s5k5ca_brightness_p_3"); 
		}
		break;

		case PCAM_BR_STEP_P_2 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_brightness_p_2, S5K5CA_BRIGHTNESS_P_2_REGS,\
		 "s5k5ca_brightness_p_2"); 
		}
		break;

		case PCAM_BR_STEP_P_1 :{
		PCAM_DEBUG("PCAM_BR_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_brightness_p_1, S5K5CA_BRIGHTNESS_P_1_REGS,\
		 "s5k5ca_brightness_p_1"); 
		}
		break;

		case PCAM_BR_STEP_0 :{
		PCAM_DEBUG("PCAM_BR_STEP_0");
		s5k5ca_sensor_write_list(s5k5ca_brightness_0, S5K5CA_BRIGHTNESS_0_REGS, \
		"s5k5ca_brightness_0"); 
		}
		break;

		case PCAM_BR_STEP_M_1 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_1");
		s5k5ca_sensor_write_list(s5k5ca_brightness_m_1, S5K5CA_BRIGHTNESS_M_1_REGS, \
		"s5k5ca_brightness_m_1"); 
		}
		break;

		case PCAM_BR_STEP_M_2 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_2");
		s5k5ca_sensor_write_list(s5k5ca_brightness_m_2, S5K5CA_BRIGHTNESS_M_2_REGS, \
		"s5k5ca_brightness_m_2"); 
		}
		break;

		case PCAM_BR_STEP_M_3 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_3");
		s5k5ca_sensor_write_list(s5k5ca_brightness_m_3, S5K5CA_BRIGHTNESS_M_3_REGS, \
		"s5k5ca_brightness_m_3"); 
		}
		break;

		case PCAM_BR_STEP_M_4 :{
		PCAM_DEBUG("PCAM_BR_STEP_M_4");
		s5k5ca_sensor_write_list(s5k5ca_brightness_m_4, S5K5CA_BRIGHTNESS_M_4_REGS, \
		"s5k5ca_brightness_m_4"); 
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
		s5k5ca_sensor_write_list(s5k5ca_iso_auto, S5K5CA_ISO_AUTO_REGS, \
		"s5k5ca_iso_auto"); 
		}
		break;

		case PCAM_ISO_50 :{
		PCAM_DEBUG("PCAM_ISO_50");
		s5k5ca_sensor_write_list(s5k5ca_iso_50, S5K5CA_ISO_50_REGS, \
		"s5k5ca_iso_50"); 
		}
		break;

		case PCAM_ISO_100 :{
		PCAM_DEBUG("PCAM_ISO_100");
		s5k5ca_sensor_write_list(s5k5ca_iso_100, S5K5CA_ISO_100_REGS, \
		"s5k5ca_iso_100"); 
		}
		break;

		case PCAM_ISO_200 :{
		PCAM_DEBUG("PCAM_ISO_200");
		s5k5ca_sensor_write_list(s5k5ca_iso_200, S5K5CA_ISO_200_REGS, \
		"s5k5ca_iso_200"); 
		}
		break;

		case PCAM_ISO_400 :{
		PCAM_DEBUG("PCAM_ISO_400");
		s5k5ca_sensor_write_list(s5k5ca_iso_400, S5K5CA_ISO_400_REGS, \
		"s5k5ca_iso_400"); 
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
		s5k5ca_sensor_write_list(s5k5ca_metering_normal, S5K5CA_METERING_NORMAL_REGS, \
		"s5k5ca_metering_normal"); 
		}
		break;
		
		case PCAM_METERING_SPOT :{
		PCAM_DEBUG("PCAM_METERING_SPOT");
		s5k5ca_sensor_write_list(s5k5ca_metering_spot, S5K5CA_METERING_SPOT_REGS, \
		"s5k5ca_metering_spot"); 
		}
		break;

		case PCAM_METERING_CENTER :{
		PCAM_DEBUG("PCAM_METERING_CENTER");
		s5k5ca_sensor_write_list(s5k5ca_metering_center, S5K5CA_METERING_CENTER_REGS, \
		"s5k5ca_metering_center"); 
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
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
		}
		break;

		case PCAM_SCENE_PORTRAIT :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_PORTRAIT");
		s5k5ca_sensor_write_list(s5k5ca_scene_portrait , S5K5CA_SCENE_PORTRAIT_REGS, \
		"s5k5ca_scene_portrait"); 
		}
		break;

		case PCAM_SCENE_LANDSCAPE :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_LANDSCAPE");
		s5k5ca_sensor_write_list(s5k5ca_scene_landscape , S5K5CA_SCENE_LANDSCAPE_REGS, \
		"s5k5ca_scene_landscape"); 
		}
		break;

		case PCAM_SCENE_SPORTS :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_SPORTS");
		s5k5ca_sensor_write_list(s5k5ca_scene_sports , S5K5CA_SCENE_SPORTS_REGS, \
		"s5k5ca_scene_sports"); 
		}
		break;

		case PCAM_SCENE_PARTY :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_PARTY");
		s5k5ca_sensor_write_list(s5k5ca_scene_party , S5K5CA_SCENE_PARTY_REGS, \
		"s5k5ca_scene_party"); 
		
		}
		break;

		case PCAM_SCENE_BEACH :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_BEACH");
		s5k5ca_sensor_write_list(s5k5ca_scene_beach , S5K5CA_SCENE_BEACH_REGS, \
		"s5k5ca_scene_beach"); 
		}
		break;

		case PCAM_SCENE_SUNSET :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_SUNSET");
		s5k5ca_sensor_write_list(s5k5ca_scene_sunset , S5K5CA_SCENE_SUNSET_REGS, \
		"s5k5ca_scene_sunset"); 
		}
		break;
		
		case PCAM_SCENE_DAWN :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_DAWN");
		s5k5ca_sensor_write_list(s5k5ca_scene_dawn , S5K5CA_SCENE_DAWN_REGS, \
		"s5k5ca_scene_dawn"); 
		}
		break;

		case PCAM_SCENE_FALL :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_FALL");
		s5k5ca_sensor_write_list(s5k5ca_scene_fall , S5K5CA_SCENE_FALL_REGS, \
		"s5k5ca_scene_fall"); 
		}
		break;

		case PCAM_SCENE_NIGHTSHOT :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_NIGHTSHOT");
		s5k5ca_sensor_write_list(s5k5ca_scene_nightshot , S5K5CA_SCENE_NIGHTSHOT_REGS, \
		"s5k5ca_scene_nightshot"); 
		}
		break;

		case PCAM_SCENE_BACKLIGHT :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_BACKLIGHT");
		s5k5ca_sensor_write_list(s5k5ca_scene_backlight , S5K5CA_SCENE_BACKLIGHT_REGS, \
		"s5k5ca_scene_backlight"); 
		}
		break;

		case PCAM_SCENE_FIREWORK :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_FIREWORK");
		s5k5ca_sensor_write_list(s5k5ca_scene_firework , S5K5CA_SCENE_FIREWORK_REGS, \
		"s5k5ca_scene_firework"); 
		}
		break;

		case PCAM_SCENE_TEXT :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_TEXT");
		s5k5ca_sensor_write_list(s5k5ca_scene_text , S5K5CA_SCENE_TEXT_REGS, \
		"s5k5ca_scene_text"); 
		}
		break;

		case PCAM_SCENE_CANDLE :{
		s5k5ca_sensor_write_list(s5k5ca_scene_off , S5K5CA_SCENE_OFF_REGS, \
		"s5k5ca_scene_off"); 
			
		PCAM_DEBUG("PCAM_SCENE_CANDLE");
		s5k5ca_sensor_write_list(s5k5ca_scene_candle , S5K5CA_SCENE_CANDLE_REGS, \
		"s5k5ca_scene_candle"); 
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
		PCAM_DEBUG("PCAM_CR_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_contrast_m_2 , S5K5CA_CONTRAST_M_2_REGS, \
		"s5k5ca_contrast_m_2"); 					
		}
		break;

		case PCAM_CR_STEP_M_1 :{
		PCAM_DEBUG("PCAM_CR_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_contrast_m_1 , S5K5CA_CONTRAST_M_1_REGS, \
		"s5k5ca_contrast_m_1"); 					
		}
		break;

		case PCAM_CR_STEP_0 :{
		PCAM_DEBUG("PCAM_CR_STEP_0");
		s5k5ca_sensor_write_list(s5k5ca_contrast_0 , S5K5CA_CONTRAST_0_REGS, \
		"s5k5ca_contrast_0"); 					
		}
		break;

		case PCAM_CR_STEP_P_1 :{
		PCAM_DEBUG("PCAM_CR_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_contrast_p_1 , S5K5CA_CONTRAST_P_1_REGS, \
		"s5k5ca_contrast_p_1"); 					
		}
		break;

		case PCAM_CR_STEP_P_2 :{
		PCAM_DEBUG("PCAM_CR_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_contrast_p_2 , S5K5CA_CONTRAST_P_2_REGS, \
		"s5k5ca_contrast_p_2"); 					
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
		PCAM_DEBUG("PCAM_SA_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_saturation_m_2 , S5K5CA_SATURATION_M_2_REGS, \
		"s5k5ca_saturation_m_2"); 					
		}
		break;

		case PCAM_SA_STEP_M_1 :{
		PCAM_DEBUG("PCAM_SA_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_saturation_m_1 , S5K5CA_SATURATION_M_1_REGS, \
		"s5k5ca_saturation_m_1"); 					
		}
		break;

		case PCAM_SA_STEP_0 :{
		PCAM_DEBUG("PCAM_SA_STEP_0");
		s5k5ca_sensor_write_list(s5k5ca_saturation_0 , S5K5CA_SATURATION_0_REGS, \
		"s5k5ca_saturation_0"); 					
		}
		break;

		case PCAM_SA_STEP_P_1 :{
		PCAM_DEBUG("PCAM_SA_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_saturation_p_1 , S5K5CA_SATURATION_P_1_REGS, \
		"s5k5ca_saturation_p_1"); 					
		}
		break;

		case PCAM_SA_STEP_P_2 :{
		PCAM_DEBUG("PCAM_SA_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_saturation_p_2 , S5K5CA_SATURATION_P_2_REGS, \
		"s5k5ca_saturation_p_2"); 					
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
		PCAM_DEBUG("PCAM_SP_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_sharpness_m_2 , S5K5CA_SHARPNESS_M_2_REGS, \
		"s5k5ca_sharpness_m_2"); 					
		}
		break;

		case PCAM_SP_STEP_M_1 :{
		PCAM_DEBUG("PCAM_SP_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_sharpness_m_1 , S5K5CA_SHARPNESS_M_1_REGS, \
		"s5k5ca_sharpness_m_1"); 					
		}
		break;

		case PCAM_SP_STEP_0 :{
		PCAM_DEBUG("PCAM_SP_STEP_0");
		s5k5ca_sensor_write_list(s5k5ca_sharpness_0 , S5K5CA_SHARPNESS_0_REGS, \
		"s5k5ca_sharpness_0"); 					
		}
		break;

		case PCAM_SP_STEP_P_1 :{
		PCAM_DEBUG("PCAM_SP_STEP_P_1");
		s5k5ca_sensor_write_list(s5k5ca_sharpness_p_1 , S5K5CA_SHARPNESS_P_1_REGS, \
		"s5k5ca_sharpness_p_1"); 					
		}
		break;

		case PCAM_SP_STEP_P_2 :{
		PCAM_DEBUG("PCAM_SP_STEP_P_2");
		s5k5ca_sensor_write_list(s5k5ca_sharpness_p_2 , S5K5CA_SHARPNESS_P_2_REGS, \
		"s5k5ca_sharpness_p_2"); 					
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
		unsigned short af_status;
	//				unsigned short i;
			
		//PCAM_DEBUG("PCAM_AF_CHECK_STATUS");


	//				msleep(133); //after 2 frame for AF

		s5k5ca_sensor_write(0x002C, 0x7000);
		s5k5ca_sensor_write(0x002E, 0x26FE);
		s5k5ca_sensor_read(0x0F12, &af_status);
		PCAM_DEBUG("PCAM_AF_CHECK_STATUS : return %d",af_status);
		return af_status;


#if 0//PCAM // Below that is moving to Hal
			for(i=0; i<100; i++)
			{
				if(( af_status == PCAM_AF_SUCCESS) || (af_status==PCAM_AF_LOWCONF)|| (af_status==PCAM_AF_CANCELED))
				{
					PCAM_DEBUG("<=PCAM=> DONE! af_status : %x ", af_status);
					ctrl_info.value_3 = af_status;
					break;
				}
				else
				{
					PCAM_DEBUG("<=PCAM=> NOT YET! af_status :%x", af_status);
					msleep(50);
					s5k5ca_sensor_read(0x0F12, &af_status);
					
				}

			}
			
			if(i == 100)
			{
				printk("<=PCAM=> PCAM_AF_CHECK_STATUS TIME OUT!\n");
				ctrl_info.value_3 = PCAM_AF_TIMEOUT;
				
			}
#endif//PCAM
			
		}//end of case
		break;


		
		case PCAM_AF_OFF :{
		PCAM_DEBUG("PCAM_AF_OFF");
		s5k5ca_sensor_write_list(s5k5ca_af_off, S5K5CA_AF_OFF_REGS, "s5k5ca_af_off"); 
		}
		break;
		
		case PCAM_AF_SET_NORMAL :{
		PCAM_DEBUG("PCAM_AF_SET_NORMAL");
		s5k5ca_sensor_write_list(s5k5ca_af_normal_on, S5K5CA_AF_NORMAL_ON_REGS,\
		 "s5k5ca_af_normal_on"); 					
		}
		break;

		case PCAM_AF_SET_MACRO :{
		PCAM_DEBUG("PCAM_AF_SET_MACRO");
		s5k5ca_sensor_write_list(s5k5ca_af_macro_on, S5K5CA_AF_MACRO_ON_REGS,\
		 "s5k5ca_af_macro_on"); 									
		}
			break;

		case PCAM_AF_DO :{
		PCAM_DEBUG("PCAM_AF_DO");
		s5k5ca_sensor_write_list(s5k5ca_af_do, S5K5CA_AF_DO_REGS,\
		 "s5k5ca_af_do"); 														
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
		s5k5ca_sensor_write_list(s5k5ca_dtp_off, S5K5CA_DTP_OFF_REGS, \
							"s5k5ca_dtp_off"); // dtp off
		}
		break;

		case PCAM_DTP_ON:{
		PCAM_DEBUG("DTP ON");
		s5k5ca_sensor_write_list(s5k5ca_dtp_on, S5K5CA_DTP_ON_REGS, \
							"s5k5ca_dtp_on"); // dtp on
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
			s5k5ca_sensor_write(0xFCFC, 0xD000);					
			s5k5ca_sensor_write(0x002C, 0x7000);
			s5k5ca_sensor_write(0x002E, 0x23E8);
			s5k5ca_sensor_read(0x0F12, &lsb); //0x23E8
			s5k5ca_sensor_read(0x0F12, &msb); //0x23EA
			s5k5ca_sensor_read(0x0F12, &rough_iso); //0x23EC
													
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
				s5k5ca_sensor_write_list(s5k5ca_fps_15fix, S5K5CA_FPS_15FIX_REGS,\
				 "s5k5ca_fps_15fix"); 	
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
			switch(ctrl_info.value_1)
			{
				case PCAM_AWB_AE_LOCK :{
				PCAM_DEBUG("PCAM_AWB_AE_LOCK");
				s5k5ca_sensor_write_list(s5k5ca_awb_ae_lock , S5K5CA_AWB_AE_LOCK_REGS, \
				"s5k5ca_awb_ae_lock"); 					
				}
				break;

				case PCAM_AWB_AE_UNLOCK :{
				PCAM_DEBUG("PCAM_AWB_AE_UNLOCK");
				s5k5ca_sensor_write_list(s5k5ca_awb_ae_unlock , S5K5CA_AWB_AE_UNLOCK_REGS, \
				"s5k5ca_awb_ae_unlock"); 
					
				}
				break;

				default :{
					printk("<=PCAM=> Unexpected AWB_AE mode : %d\n", ctrl_info.value_1);
				}
				break;						
				
			}
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
#endif//PCAM









void cam_pw(int status)
{
        struct vreg *vreg_cam_out8;
        struct vreg *vreg_cam_out9;
        struct vreg *vreg_cam_out10;
        struct vreg *vreg_cam_out4; //AF



        vreg_cam_out8 = vreg_get(NULL, "ldo8");
        vreg_cam_out9 = vreg_get(NULL, "ldo9");
        vreg_cam_out10 = vreg_get(NULL, "ldo10");
        vreg_cam_out4 = vreg_get(NULL, "ldo4");




	if(status == 1) //POWER ON
	{
	    PCAM_DEBUG("POWER ON for Callisto");
	    vreg_set_level(vreg_cam_out10, OUT1800mV);//1800
	    vreg_set_level(vreg_cam_out9,  OUT2800mV);//2800
	    vreg_set_level(vreg_cam_out8,  OUT2600mV);//2600
	    vreg_set_level(vreg_cam_out4,  OUT2800mV);//2800

	    vreg_enable(vreg_cam_out10);//1.8V VDDD
	    msleep(1); // by new document 2010-5-14		
	    vreg_enable(vreg_cam_out9);//2.8V  VDDA
	    vreg_enable(vreg_cam_out8);//2.6V VDDIO
	    vreg_enable(vreg_cam_out4);//2.8V AF

	    //after power on, below function will be called.
	    pcam_msm_i2c_pwr_mgmt(s5k5ca_client->adapter, 1);

		
	}
	else //POWER OFF
	{
	    PCAM_DEBUG("POWER OFF");

	    //before power on, below function will be called.
	    pcam_msm_i2c_pwr_mgmt(s5k5ca_client->adapter, 0);		
		
	    vreg_disable(vreg_cam_out8); //VDDIO 2600
	    udelay(30);
	    vreg_disable(vreg_cam_out10); //VDDD 1800
	    vreg_disable(vreg_cam_out9); //VDDA 2800
	    vreg_disable(vreg_cam_out4); //AF 2800
	}
	
}



static int cam_hw_init()
{

	int rc = 0;
	unsigned short	id = 0; //CAM FOR FW
//	unsigned int	before_time, after_time, i;//I2C SPEED TEST

	PCAM_DEBUG("next cam_hw_init");
	

#if 0//BLOCK FOR PRE INIT
	PCAM_DEBUG("++++++++++++++++++++++++++test driver++++++++++++++++++++++++++++++++++++");
 
	gpio_set_value(0, 0);//RESET	
	gpio_set_value(1, 0);//STBY 

	cam_pw(1);

	gpio_set_value(1, 1); //STBY -> UP
#endif	


	/* Input MCLK = 24MHz */
	msm_camio_clk_rate_set(24000000);
	msm_camio_camif_pad_reg_reset();
	msleep(1);

	
	gpio_set_value(1, 1); //STBY UP   
	msleep(1);
	gpio_set_value(0, 1); //RESET UP   
	msleep(15);	



#if 0//PGH I2C SPEED TEST
        before_time = get_jiffies_64();
    for (i = 0; i < 3000; i++) 
        {
		s5k5ca_sensor_write(0x002E, 0x0040);
        }       
 
        after_time = get_jiffies_64();
        printk("<=PCAM=> Total Time 3000: %d\n",  jiffies_to_msecs(after_time-before_time));
#endif//PGH I2C SPEED TEST



	s5k5ca_sensor_write(0x002C, 0x0000);
	s5k5ca_sensor_write(0x002E, 0x0040);
	s5k5ca_sensor_read(0x0F12, &id);


	if(id != 0x05CA)
	{
		printk("<=PCAM=> WRONG SENSOR FW => id 0x%x \n", id);
		rc = -1;
	}
	else
		printk("<=PCAM=> CURRENT SENSOR FW => id 0x%x \n", id);
	return rc;
}





#if 0//PGH
static int32_t s5k5ca_set_lens_roll_off(void)
{
	int32_t rc = 0;
	rc = s5k5ca_i2c_write_table(&s5k5ca_regs.rftbl[0],
								 s5k5ca_regs.rftbl_size);
	return rc;
}
#endif//PGH

#if 0//PGH
static long s5k5ca_reg_init(void)
{
	int32_t array_length;
	int32_t i;
	long rc;

	/* PLL Setup Start */
	rc = s5k5ca_i2c_write_table(&s5k5ca_regs.plltbl[0],
					s5k5ca_regs.plltbl_size);

	if (rc < 0)
		return rc;
	/* PLL Setup End   */

	array_length = s5k5ca_regs.prev_snap_reg_settings_size;

	/* Configure sensor for Preview mode and Snapshot mode */
	for (i = 0; i < array_length; i++) {
		rc = s5k5ca_i2c_write(s5k5ca_client->addr,
		  s5k5ca_regs.prev_snap_reg_settings[i].register_address,
		  s5k5ca_regs.prev_snap_reg_settings[i].register_value,
		  WORD_LEN);

		if (rc < 0)
			return rc;
	}

	/* Configure for Noise Reduction, Saturation and Aperture Correction */
	array_length = s5k5ca_regs.noise_reduction_reg_settings_size;

	for (i = 0; i < array_length; i++) {
		rc = s5k5ca_i2c_write(s5k5ca_client->addr,
			s5k5ca_regs.noise_reduction_reg_settings[i].register_address,
			s5k5ca_regs.noise_reduction_reg_settings[i].register_value,
			WORD_LEN);

		if (rc < 0)
			return rc;
	}

	/* Set Color Kill Saturation point to optimum value */
	rc =
	s5k5ca_i2c_write(s5k5ca_client->addr,
	0x35A4,
	0x0593,
	WORD_LEN);
	if (rc < 0)
		return rc;

	rc = s5k5ca_i2c_write_table(&s5k5ca_regs.stbl[0],
					s5k5ca_regs.stbl_size);
	if (rc < 0)
		return rc;

	rc = s5k5ca_set_lens_roll_off();
	if (rc < 0)
		return rc;

	return 0;
}
#endif//PGH

static long s5k5ca_set_effect(int mode, int effect)
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
	s5k5ca_effect = effect;
	
	return rc;
}

static long s5k5ca_set_sensor_mode(int mode)
{
	//long rc = 0;
	unsigned short	msb, lsb;
	int base_high, base_low, cur_lux;
	char vsync_value, cnt;

	unsigned int	before_time, after_time, i, time_gab;//I2C SPEED TEST
	//unsigned short	dummy_read = 0; //CAM FOR FW
	int *i2c_clk_addr; //TEMP Dirty Code, Do not use it!

	PCAM_DEBUG("START");
	//i2c_clk_addr = 0xd500c004;	// Froyo version (-Jeonhk 20110310)
	i2c_clk_addr = get_i2c_clock_addr(s5k5ca_client->adapter);

	printk("[S5K5CA]s5k5ca_set_preview start\n");

	if(first_start_camera)
	{
	    printk("<=PCAM=> camera init ver02~=== \n");

	    //i2c_clk_addr = 0xd500c004;
	    //printk("<=PCAM=> i2c clk :%x\n", readl(i2c_clk_addr));

	    before_time = get_jiffies_64();
 
	    //s5k5ca_sensor_write_list(s5k5ca_init0, S5K5CA_INIT_REGS, "s5k5ca_init0");
	    S5K5CA_BURST_WRITE_LIST(s5k5ca_init0);

	    after_time = get_jiffies_64();

	    time_gab = jiffies_to_msecs(after_time-before_time);


	    if(time_gab > 900)
	    {
		printk("<=PCAM=> i2c speed is going down : %dmsec\n", time_gab);

		pcam_msm_i2c_pwr_mgmt(s5k5ca_client->adapter, 1);
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
			s5k5ca_sensor_write_list(s5k5ca_dtp_on, S5K5CA_DTP_ON_REGS, \
								"s5k5ca_dtp_on"); // dtp on
		}
		else
		{
			s5k5ca_sensor_write_list(s5k5ca_preview, S5K5CA_PREVIEW_REGS, \
								"s5k5ca_preview"); // preview start
		}


		sensor_effect_control(mEffect);
		sensor_scene_control(mScene);
		if(mScene != PCAM_SCENE_SPORTS && mScene != PCAM_SCENE_NIGHTSHOT)
			sensor_iso_control(mISO);			
		sensor_brightness_control(mBrightness);
		sensor_metering_control(mAutoExposure);
		sensor_contrast_control(mContrast);
		sensor_saturation_control(mSaturation);
		sensor_sharpness_control(mSharpness);
		sensor_whitebalance_control(mWhiteBalance);
		sensor_af_control(mAfMode);
		
	}
		break;
		
	case SENSOR_SNAPSHOT_MODE:
	{
		PCAM_DEBUG("SNAPSHOT~~~");

		
		msb = lsb = 0;
		base_high = base_low = cur_lux = 0;


		s5k5ca_sensor_write(0x002C, 0x7000);
		s5k5ca_sensor_write(0x002E, 0x032E);
		s5k5ca_sensor_read(0x0F12, &lsb);
		s5k5ca_sensor_read(0x0F12, &msb);

		base_high = (msb<<16) | lsb;
		PCAM_DEBUG("base_high : 0x%08x \n", base_high);

		s5k5ca_sensor_read(0x0F12, &lsb);
		s5k5ca_sensor_read(0x0F12, &msb);

		base_low = (msb<<16) | lsb;
		PCAM_DEBUG("base_low : 0x%08x \n", base_low);


		s5k5ca_sensor_write(0x002C, 0x7000);
		s5k5ca_sensor_write(0x002E, 0x2448);
		s5k5ca_sensor_read(0x0F12, &lsb);
		s5k5ca_sensor_read(0x0F12, &msb);

		cur_lux = (msb<<16) | lsb;
		PCAM_DEBUG("cur_lux : 0x%08x \n", cur_lux);




		for(cnt=0; cnt<700; cnt++)
		{
			vsync_value = gpio_get_value(14);

			if(vsync_value)
				break;
			else
			{
				PCAM_DEBUG(" on snapshot,  wait cnt:%d vsync_value:%d\n", cnt, vsync_value);
				msleep(3);
			}
	
		}
			



		if(cur_lux > base_high)
		{
			PCAM_DEBUG("HighLight Snapshot!\n");
			s5k5ca_sensor_write_list(s5k5ca_high_snapshot, S5K5CA_HIGH_SNAPSHOT_REGS, "s5k5ca_high_snapshot"); 		
		}
		else if(cur_lux < base_low)
		{
			if((mScene == PCAM_SCENE_NIGHTSHOT) ||(mScene == PCAM_SCENE_FIREWORK) )
			{
				PCAM_DEBUG("Night Snapshot!\n");
				s5k5ca_sensor_write_list(s5k5ca_night_snapshot, S5K5CA_NIGHT_SNAPSHOT_REGS, "s5k5ca_night_snapshot"); 			
			}
			else
			{
				PCAM_DEBUG("LowLight Snapshot!\n");
				s5k5ca_sensor_write_list(s5k5ca_lowlight_snapshot, S5K5CA_LOWLIGHT_SNAPSHOT_REGS, "s5k5ca_lowlight_snapshot"); 			
			}
		}
		else
		{
			PCAM_DEBUG("Normal Snapshot!\n");
			s5k5ca_sensor_write_list(s5k5ca_snapshot, S5K5CA_SNAPSHOT_REGS, "s5k5ca_snapshot"); 						
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

static int s5k5ca_sensor_init_probe(const struct msm_camera_sensor_info *data)
{
	int rc = 0;
	printk("[S5K5CA]sensor_init_probe()\n");

	#ifndef CONFIG_LOAD_FILE
	s5k5ca_sensor_write_list(s5k5ca_pre_init0, S5K5CA_PRE_INIT_REGS,"s5k5ca_pre_init0");
	msleep(10);	
	#endif

	return rc;

}

#ifdef CONFIG_LOAD_FILE

#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>

#include <asm/uaccess.h>

static char *s5k5ca_regs_table = NULL;

static int s5k5ca_regs_table_size;

void s5k5ca_regs_table_init(void)
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
	filp = filp_open("/data/camera/s5k5ca.h", O_RDONLY, 0);
#else
	filp = filp_open("/mnt/sdcard/s5k5ca.h", O_RDONLY, 0);
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

	s5k5ca_regs_table = dp;
	
	s5k5ca_regs_table_size = l;

	*((s5k5ca_regs_table + s5k5ca_regs_table_size) - 1) = '\0';

//	printk("s5k5ca_regs_table 0x%x, %ld\n", dp, l);
}

void s5k5ca_regs_table_exit(void)
{
	printk("%s %d\n", __func__, __LINE__);
	if (s5k5ca_regs_table) {
		kfree(s5k5ca_regs_table);
		s5k5ca_regs_table = NULL;
	}	
}

static int s5k5ca_regs_table_write(char *name)
{
	char *start, *end, *reg;//, *data;	
	unsigned short addr, value;
	char reg_buf[7], data_buf[7];

	addr = value = 0;

	*(reg_buf + 6) = '\0';
	*(data_buf + 6) = '\0';

	start = strstr(s5k5ca_regs_table, name);
	
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
				if( s5k5ca_sensor_write(addr, value) < 0 )
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



int s5k5ca_sensor_init(const struct msm_camera_sensor_info *data)
{
	int rc = 0;

	s5k5ca_ctrl = kzalloc(sizeof(struct s5k5ca_ctrl), GFP_KERNEL);
	if (!s5k5ca_ctrl) {
		CDBG("s5k5ca_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	if (data)
		s5k5ca_ctrl->sensordata = data;

	printk("new s5k5ca_sensor_init !!\n");
	gpio_set_value(0, 0);//RESET	
	gpio_set_value(1, 0);//STBY 
	
	cam_pw(1);
	
	rc = cam_hw_init();
	if(rc < 0)
	{
		printk("<=PCAM=> cam_fw_init failed!\n");
		goto init_fail;
	}

#ifdef CONFIG_LOAD_FILE
	s5k5ca_regs_table_init();
#endif	

	rc = s5k5ca_sensor_init_probe(data);
	if (rc < 0) {
		CDBG("s5k5ca_sensor_init failed!\n");		
		goto init_fail;
	}

init_done:
	return rc;

init_fail:
	kfree(s5k5ca_ctrl);
	return rc;
}

static int s5k5ca_init_client(struct i2c_client *client)
{
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&s5k5ca_wait_queue);
	return 0;
}

int s5k5ca_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cfg_data;
	long   rc = 0;

	if (copy_from_user(&cfg_data,
			(void *)argp,
			sizeof(struct sensor_cfg_data)))
		return -EFAULT;

	/* down(&s5k5ca_sem); */

	CDBG("s5k5ca_ioctl, cfgtype = %d, mode = %d\n",
		cfg_data.cfgtype, cfg_data.mode);

		switch (cfg_data.cfgtype) {
		case CFG_SET_MODE:
			rc = s5k5ca_set_sensor_mode(
						cfg_data.mode);
			break;

		case CFG_SET_EFFECT:
			rc = s5k5ca_set_effect(cfg_data.mode,
						cfg_data.cfg.effect);
			break;

		case CFG_GET_AF_MAX_STEPS:
		default:
			rc = -EINVAL;
			break;
		}

	/* up(&s5k5ca_sem); */

	return rc;
}

int s5k5ca_sensor_release(void)
{
	int rc = 0;
        int *switch_i2c_addr; //TEMP Dirty Code, Do not use it!

	/* down(&s5k5ca_sem); */
/*
	printk("<=PCAM=> lens moving to Base before CAM OFF\n");
	s5k5ca_sensor_write(0x0028, 0x7000);
	s5k5ca_sensor_write(0x002A, 0x0254);
	s5k5ca_sensor_write(0x0F12, 0x0030); //Lens Pistion (0x00 ~ 0xfF) normally (0x30 ~ 0x80)
	*/


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

	printk("<=PCAM=> s5k5ca_sensor_release\n");

	kfree(s5k5ca_ctrl);
	/* up(&s5k5ca_sem); */

#ifdef CONFIG_LOAD_FILE
	s5k5ca_regs_table_exit();
#endif

	cam_pw(0);
	return rc;
}

static int s5k5ca_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;


	
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		rc = -ENOTSUPP;
		goto probe_failure;
	}

	s5k5ca_sensorw =
		kzalloc(sizeof(struct s5k5ca_work), GFP_KERNEL);

	if (!s5k5ca_sensorw) {
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, s5k5ca_sensorw);
	s5k5ca_init_client(client);
	s5k5ca_client = client;


	CDBG("s5k5ca_probe succeeded!\n");

	return 0;

probe_failure:
	kfree(s5k5ca_sensorw);
	s5k5ca_sensorw = NULL;
	CDBG("s5k5ca_probe failed!\n");
	return rc;
}

static const struct i2c_device_id s5k5ca_i2c_id[] = {
	{ "s5k5ca", 0},
	{ },
};

static struct i2c_driver s5k5ca_i2c_driver = {
	.id_table = s5k5ca_i2c_id,
	.probe  = s5k5ca_i2c_probe,
	.remove = __exit_p(s5k5ca_i2c_remove),
	.driver = {
		.name = "s5k5ca",
	},
};

static int s5k5ca_sensor_probe(const struct msm_camera_sensor_info *info,
				struct msm_sensor_ctrl *s)
{

	int rc = i2c_add_driver(&s5k5ca_i2c_driver);
	if (rc < 0 || s5k5ca_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_done;
	}

	cam_pw(1);

#if 1//PCAM
	rc = s5k5ca_sensor_init_probe(info);
	if (rc < 0)
		goto probe_done;
#endif
	gpio_set_value(0, 0);//RESET
	gpio_set_value(1, 0);//STBY
	cam_pw(0);


	s->s_init = s5k5ca_sensor_init;
	s->s_release = s5k5ca_sensor_release;
	s->s_config  = s5k5ca_sensor_config;	
	s->s_camera_type = BACK_CAMERA_2D;
	s->s_mount_angle = 0;

probe_done:
	CDBG("%s %s:%d\n", __FILE__, __func__, __LINE__);
	return rc;
}

static int __s5k5ca_probe(struct platform_device *pdev)
{
	printk("_s5k5ca_probe\n");

	return msm_camera_drv_start(pdev, s5k5ca_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
	.probe = __s5k5ca_probe,
	.driver = {
		.name = "msm_camera_s5k5ca",
		.owner = THIS_MODULE,
	},
};

static int __init s5k5ca_init(void)
{
	printk("s5k5ca_init\n");

	return platform_driver_register(&msm_camera_driver);
}

module_init(s5k5ca_init);
