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

//PGH TEST

#include <linux/delay.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <media/msm_camera.h>
#include <mach/gpio.h>
#include "sr200pc10.h"

#include <mach/camera.h>
#include <mach/vreg.h>

#define SENSOR_DEBUG 0


#if 1//PCAM ROUGH CODE
//#define CONFIG_LOAD_FILE 0


#define PCAM_AUTO_TUNNING		0
#define PCAM_SDCARD_DETECT		1
#define PCAM_EXPOSURE_TIME		2
#define PCAM_ISO_SPEED			3
#define PCAM_FIXED_FRAME		4
#define PCAM_AUTO_FRAME			5
#define PCAM_NIGHT_SHOT			6


#endif


#define	MAX_RETRY_COUNT	3


struct sr200pc10_work {
	struct work_struct work;
};

static struct  sr200pc10_work *sr200pc10_sensorw;
static struct  i2c_client *sr200pc10_client;

struct sr200pc10_ctrl {
	const struct msm_camera_sensor_info *sensordata;
};


static struct sr200pc10_ctrl *sr200pc10_ctrl;

static DECLARE_WAIT_QUEUE_HEAD(sr200pc10_wait_queue);
DECLARE_MUTEX(sr200pc10_sem);
static int16_t sr200pc10_effect = CAMERA_EFFECT_OFF;

/*=============================================================
	EXTERNAL DECLARATIONS
==============================================================*/
extern struct sr200pc10_reg sr200pc10_regs;


/*=============================================================*/


static int cam_hw_init(void);

#ifdef CONFIG_LOAD_FILE
//static int sr200pc10_regs_table_write(char *name);
int sr200pc10_regs_table_write(char *name);
#endif


static int sr200pc10_sensor_read(unsigned short subaddr, unsigned short *data)
{
	int ret;
	unsigned char buf[1] = {0};
	struct i2c_msg msg = { sr200pc10_client->addr, 0, 1, buf };
	
	buf[0] = subaddr;
//	buf[1] = 0x0;

	ret = i2c_transfer(sr200pc10_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) 
		goto error;

	msg.flags = I2C_M_RD;
	
	ret = i2c_transfer(sr200pc10_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO) 
		goto error;

//	*data = ((buf[0] << 8) | buf[1]);
	*data = buf[0];

error:
	return ret;
}

static int sr200pc10_sensor_write(unsigned short subaddr, unsigned short val)
{
	unsigned char buf[2] = {0};
	struct i2c_msg msg = { sr200pc10_client->addr, 0, 2, buf };


	buf[0] = subaddr;
	buf[1] = val;

	return i2c_transfer(sr200pc10_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
}


#ifdef CONFIG_LOAD_FILE

#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>


static char *sr200pc10_regs_table = NULL;

static int sr200pc10_regs_table_size;

void sr200pc10_regs_table_init(void)
{
	struct file	*filp;
	char		*dp;
	long		l;
	loff_t		pos;
//	int		i;
	int		ret;

	mm_segment_t fs	= get_fs();

	set_fs(get_ds());

	filp = filp_open("/sdcard/sr200pc10.h", O_RDONLY, 0);

	if(IS_ERR(filp))
	{
		printk("<=PCAM=> file open error\n");
		return;
	}

	l = filp->f_path.dentry->d_inode->i_size;
	printk("<=PCAM=> l = %ld\n", l);

	dp = kmalloc(l, GFP_KERNEL);
	if(dp == NULL)
	{
		printk("<=PCAM=> Out of Memory\n");
		filp_close(filp, current->files);
	}
	pos = 0;
	memset(dp, 0, l);
	ret = vfs_read(filp, (char __user *)dp, l, &pos);

	if(ret != l)
	{
		printk("<=PCAM=> Failed to read file ret = %d\n", ret);
		kfree(dp);
		filp_close(filp, current->files);
		return;
	}

	filp_close(filp, current->files);

	set_fs(fs);

	sr200pc10_regs_table		= dp;
	sr200pc10_regs_table_size	= l;

	*((sr200pc10_regs_table + sr200pc10_regs_table_size) - 1) = '\0';

//	printk("<=PCAM=> sr200pc10_regs_table 0x%x, %ld\n", (unsigned int)dp, l);

}

void sr200pc10_regs_table_exit(void)
{
	PCAM_DEBUG("START");

	if(sr200pc10_regs_table)
	{
		kfree(sr200pc10_regs_table);
		sr200pc10_regs_table = NULL;
	}

}


//static int sr200pc10_regs_table_write(char *name)
int sr200pc10_regs_table_write(char *name)
{
	char *start, *end, *reg;// *data;
	unsigned short addr = 0;
	unsigned short value = 0;
	char reg_buf[5], data_buf[5];

	*(reg_buf + 4) = '\0';
	*(data_buf + 4) = '\0';

	start = strstr(sr200pc10_regs_table, name);

	end = strstr(start, "};");

	while(1)
	{
		/* Find Address */
		reg = strstr(start, "{0x");
		if(reg)
			start = (reg + 12);
		if((reg == NULL) || (reg > end))
			break;

		/* Write Value to Address */
		if(reg != NULL)
		{
			memcpy(reg_buf, (reg + 1), 4);
			memcpy(data_buf, (reg + 7), 4);
			
//			PCAM_DEBUG("reg_buf : %s,  data_buf : %s\n", reg_buf, data_buf);


			addr = (unsigned short)simple_strtoul(reg_buf, NULL, 16);
			value = (unsigned short)simple_strtoul(data_buf, NULL, 16);
			
//			PCAM_DEBUG("addr : 0x%x,  value : 0x%x\n", addr, value);


			//Can Added Special Handle
				/* now NONE */


			if(addr = 0xff)
			{
				msleep(value*8);
			}
			else
			{

			    if( sr200pc10_sensor_write(addr, value) < 0)
			    {
				    printk("<=PCAM=> %s fail on sensor_write\n", __func__);
				    return -1;
			    }
			}
			


		}
		else
			printk("<=PCAM=> EXCEPTION! reg value : %c  addr : 0x%x,  value : 0x%x\n", *reg, addr, value);


	}


	return 0;

}

#endif //CONFIG_LOAD_FILE



static int sr200pc10_sensor_write_list(struct samsung_short_t *list,int size, char *name)
{

	int ret = 0;
#ifdef CONFIG_LOAD_FILE
	ret = sr200pc10_regs_table_write(name);
#else
	int i;

	for (i = 0; i < size; i++)
	{
	//	printk("[PGH] %x      %x\n", list[i].subaddr, list[i].value);

		if(list[i].subaddr == 0xff)
		{
//			printk("<=PCAM=> now SLEEP!!!!\n");
			msleep(list[i].value*8);
		}
		else
		{
		    if(sr200pc10_sensor_write(list[i].subaddr, list[i].value) < 0)
		    {
			    printk("<=PCAM=> sensor_write_list fail...-_-\n");
			    return -1;
		    }
		}
	}
#endif
	return ret;
}



#if 1//PCAM REMOVE OR FIX ME ROUGH CODE

void static night_shot_control(int flag)
{
	int Exptime;
	int Expmax;
	unsigned short read_1, read_2, read_3;	

	PCAM_DEBUG("night_shot_control start\n");
	
	if(flag == 1) //ON
	{

	    PCAM_DEBUG("PCAM_NIGHT_SHOT ON");

	    sr200pc10_sensor_write(0x03, 0x20);
	    sr200pc10_sensor_write(0x10, 0x1C); //AE off for 50Hz

	    sr200pc10_sensor_read(0x80, &read_1);
	    sr200pc10_sensor_read(0x81, &read_2);
	    sr200pc10_sensor_read(0x82, &read_3);


	    Exptime = ((read_1 << 16) | (read_2 << 8) | (read_3));
	    PCAM_DEBUG(" read first : %d %d %d\n", read_1, read_2, read_3);


	    sr200pc10_sensor_read(0x88, &read_1);
	    sr200pc10_sensor_read(0x89, &read_2);
	    sr200pc10_sensor_read(0x8A, &read_3);

	    Expmax = ((read_1 << 16) | (read_2 << 8) | (read_3));
	    PCAM_DEBUG(" read second : %d %d %d\n", read_1, read_2, read_3);

	    PCAM_DEBUG("Night Shot, Exptime : %d, Expmax : %d \n", Exptime, Expmax);


	    if(Exptime < Expmax)
	    {
//		printk("<=PCAM=> night 1 set\n");

		sr200pc10_sensor_write_list(sr200pc_cfg_scene_night1, sizeof(sr200pc_cfg_scene_night1)/\
		sizeof(sr200pc_cfg_scene_night1[0]), "sr200pc_cfg_scene_night1");		

	    }
	    else
	    {
//		printk("<=PCAM=> night 2 set\n");

		sr200pc10_sensor_write_list(sr200pc_cfg_scene_night2, sizeof(sr200pc_cfg_scene_night2)/\
		sizeof(sr200pc_cfg_scene_night2[0]), "sr200pc_cfg_scene_night2");		


	    }
	}

	else
	{
		PCAM_DEBUG("PCAM_NIGHT_SHOT OFF");


		sr200pc10_sensor_write_list(sr200pc_cfg_scene_normal, sizeof(sr200pc_cfg_scene_normal)/\
		sizeof(sr200pc_cfg_scene_normal[0]), "sr200pc_cfg_scene_normal"); 


		sr200pc10_sensor_write_list(sr200pc10_preview_table, sizeof(sr200pc10_preview_table)/\
		sizeof(sr200pc10_preview_table[0]), "sr200pc10_preview_table"); // preview start

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
//	printk("<=PCAM=> TEST %d %d %d %d %d \n", ctrl_info.mode, ctrl_info.address, ctrl_info.value_1, ctrl_info.value_2, ctrl_info.value_3);


	switch(ctrl_info.mode)
	{
		case PCAM_AUTO_TUNNING:
			break;

		
		case PCAM_SDCARD_DETECT:
			break;

		case PCAM_EXPOSURE_TIME:
		{
			sr200pc10_sensor_write(0x03, 0x20);
			sr200pc10_sensor_read(0x80, &ctrl_info.value_1);
			sr200pc10_sensor_read(0x81, &ctrl_info.value_2);
			sr200pc10_sensor_read(0x82, &ctrl_info.value_3);			
		}
			break;

		case PCAM_ISO_SPEED:
		{
			sr200pc10_sensor_write(0x03, 0x02);
			sr200pc10_sensor_read(0x1A, &ctrl_info.value_1);
			sr200pc10_sensor_write(0x03, 0x20);			
			sr200pc10_sensor_read(0xB0, &ctrl_info.value_2);
		}
			break;


		case PCAM_FIXED_FRAME:
		{
			PCAM_DEBUG("PCAM_FIXED_FRAME");
			PCAM_DEBUG("Now Camcorder previewing(FIXED FRAME)~\n");
		    	sr200pc10_sensor_write_list(sr200pc10_cfg_fps_15, sizeof(sr200pc10_cfg_fps_15)/\
		    	sizeof(sr200pc10_cfg_fps_15[0]), "sr200pc10_cfg_fps_15");

			ctrl_info.value_3 = 1;
		}
			break;

		case PCAM_AUTO_FRAME:
		{
			PCAM_DEBUG("PCAM_AUTO_FRAME");
			ctrl_info.value_3 = 1;
		}
			break;

		case PCAM_NIGHT_SHOT:
		{
			if(ctrl_info.value_1 == 1)
			{
				PCAM_DEBUG("PCAM_NIGHT_SHOT ON!");
				night_shot_control(1);
			}
			else
			{
				PCAM_DEBUG("PCAM_NIGHT_SHOT OFF!");
				night_shot_control(0);
			}
		}
			break;




		default :
			printk("<=PCAM=> Unexpected mode on sensor_rough_control!!!\n");
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


	printk("<=PCAM=> cam_pw start\n");


        vreg_cam_out8 = vreg_get(NULL, "ldo8");
        vreg_cam_out9 = vreg_get(NULL, "ldo9");
        vreg_cam_out10 = vreg_get(NULL, "ldo10");


	if(status == 1)
	{

	    PCAM_DEBUG("POWER ON");
	    vreg_set_level(vreg_cam_out8,  OUT2600mV);//2600
	    vreg_set_level(vreg_cam_out9,  OUT2800mV);//2800
	    vreg_set_level(vreg_cam_out10, OUT1800mV);//1800

	    vreg_enable(vreg_cam_out8);
	    vreg_enable(vreg_cam_out9);
	    vreg_enable(vreg_cam_out10);

	}
	else
	{
	    PCAM_DEBUG("POWER OFF");
	    vreg_disable(vreg_cam_out8);
	    vreg_disable(vreg_cam_out9);
	    vreg_disable(vreg_cam_out10);
	}

}


static int cam_hw_init()
{

	int rc = 0;
	unsigned short	id = 0; //PGH FOR TEST
	int retry = 0;

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

	mdelay(10);

	gpio_set_value(0, 1); //RESET UP
	

	mdelay(1);

	do
	{
		sr200pc10_sensor_read(0x04, &id);		
	} while((++retry < MAX_RETRY_COUNT) && (id == 0));

	if(id == 0x84)
		printk("<=PCAM=> RIGHT SENSOR FW => id 0x%x \n", id);
	else
	{
		printk("<=PCAM=> WRONG SENSOR FW => id 0x%x \n", id);
		rc = -1;
	}



	return rc;
}





static long sr200pc10_set_effect(int mode, int effect)
{
	long rc = 0;


	PCAM_DEBUG("mode : %d,   effect : %d", mode, effect);
	

	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		PCAM_DEBUG("SENSOR_PREVIEW_MODE");
		break;

	case SENSOR_SNAPSHOT_MODE:
		PCAM_DEBUG("SENSOR_SNAPSHOT_MODE");
		break;

	default:
		printk("<=PCAM=> %s default\n", __func__);
		break;
	}

	switch (effect) {
	case CAMERA_EFFECT_OFF: {
	PCAM_DEBUG("CAMERA_EFFECT_OFF");
	sr200pc10_sensor_write_list(sr200pc10_effect_normal, sizeof(sr200pc10_effect_normal)/\
		sizeof(sr200pc10_effect_normal[0]), "sr200pc10_effect_normal"); 

	}
			break;

	case CAMERA_EFFECT_MONO: {

	PCAM_DEBUG("CAMERA_EFFECT_MONO");
	sr200pc10_sensor_write_list(sr200pc10_effect_mono, sizeof(sr200pc10_effect_mono)/\
		sizeof(sr200pc10_effect_mono[0]), "sr200pc10_effect_mono"); 

	}
		break;

	case CAMERA_EFFECT_NEGATIVE: {

	PCAM_DEBUG("CAMERA_EFFECT_NEGATIVE");
	sr200pc10_sensor_write_list(sr200pc10_effect_negative, sizeof(sr200pc10_effect_negative)/\
		sizeof(sr200pc10_effect_negative[0]), "sr200pc10_effect_negative"); 

	}
		break;

	case CAMERA_EFFECT_SOLARIZE: {

	printk("<=PCAM=> CAMERA_EFFECT_SOLARIZE NOT SUPPORT\n");

	}
		break;

	case CAMERA_EFFECT_SEPIA: {
	PCAM_DEBUG("CAMERA_EFFECT_SEPIA");
	sr200pc10_sensor_write_list(sr200pc10_effect_sepia, sizeof(sr200pc10_effect_sepia)/\
		sizeof(sr200pc10_effect_sepia[0]), "sr200pc10_effect_sepia"); 

	}
		break;

	default: {

	printk("<=PCAM=> unexpeceted effect  %s/%d\n", __func__, __LINE__);

		return -EINVAL;
	}
	}

	sr200pc10_effect = effect;

	return rc;
}

static long sr200pc10_set_brightness(int mode, int brightness)
{
	long rc = 0;

	PCAM_DEBUG("mode : %d,   brightness : %d", mode, brightness);
#if 0
	switch (mode) {
		case SENSOR_PREVIEW_MODE:
			printk("<=PCAM=> %s SENSOR_PREVIEW_MODE\n", __func__);
	 		break;

		case SENSOR_SNAPSHOT_MODE:
			printk("<=PCAM=> 222222 %s SENSOR_SNAPSHOT_MODE\n", __func__);
	  		break;

		default:
			printk("<=PCAM=> %s default\n", __func__);
			break;
	}
#endif
	switch (brightness) {
		case CAMERA_BRIGTHNESS_0:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_0");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_0, sizeof(sr200pc10_cfg_brightness_0)/\
			sizeof(sr200pc10_cfg_brightness_0[0]), "sr200pc10_cfg_brightness_0");
			break;

		case CAMERA_BRIGTHNESS_1:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_1");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_1, sizeof(sr200pc10_cfg_brightness_1)/\
			sizeof(sr200pc10_cfg_brightness_1[0]), "sr200pc10_cfg_brightness_1");
			break;

		case CAMERA_BRIGTHNESS_2:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_2");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_2, sizeof(sr200pc10_cfg_brightness_2)/\
			sizeof(sr200pc10_cfg_brightness_2[0]), "sr200pc10_cfg_brightness_2");
			break;

		case CAMERA_BRIGTHNESS_3:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_3");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_3, sizeof(sr200pc10_cfg_brightness_3)/\
			sizeof(sr200pc10_cfg_brightness_3[0]), "sr200pc10_cfg_brightness_3");
			break;

		case CAMERA_BRIGTHNESS_4:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_4");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_4, sizeof(sr200pc10_cfg_brightness_4)/\
			sizeof(sr200pc10_cfg_brightness_4[0]), "sr200pc10_cfg_brightness_4");
			break;

		case CAMERA_BRIGTHNESS_5:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_5");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_5, sizeof(sr200pc10_cfg_brightness_5)/\
			sizeof(sr200pc10_cfg_brightness_5[0]), "sr200pc10_cfg_brightness_5");
 			break;

		case CAMERA_BRIGTHNESS_6:
			PCAM_DEBUG("CAMERA_BRIGTHNESS_6");
			sr200pc10_sensor_write_list(sr200pc10_cfg_brightness_6, sizeof(sr200pc10_cfg_brightness_6)/\
			sizeof(sr200pc10_cfg_brightness_6[0]), "sr200pc10_cfg_brightness_6");
 			break;

		default:
			printk("<=PCAM=> unexpected brightness %s/%d\n", __func__, __LINE__);
			return -EINVAL;
 	}
	return rc;
}

static long sr200pc10_set_whitebalance(int mode, int wb)
{
	long rc = 0;

	PCAM_DEBUG("mode : %d,   whitebalance : %d", mode, wb);
#if 0
	switch (mode) {
		case SENSOR_PREVIEW_MODE:
			printk("<=PCAM=> %s SENSOR_PREVIEW_MODE\n", __func__);
	 		break;

		case SENSOR_SNAPSHOT_MODE:
			printk("<=PCAM=> 222222 %s SENSOR_SNAPSHOT_MODE\n", __func__);
	  		break;

		default:
			printk("<=PCAM=> %s default\n", __func__);
			break;
	}
#endif
	switch (wb) {
		case CAMERA_WB_AUTO:
			PCAM_DEBUG("CAMERA_WB_AUTO");
			sr200pc10_sensor_write_list(sr200pc10_cfg_wb_auto, sizeof(sr200pc10_cfg_wb_auto)/\
			sizeof(sr200pc10_cfg_wb_auto[0]), "sr200pc10_cfg_wb_auto");
			break;

		case CAMERA_WB_INCANDESCENT:
			PCAM_DEBUG("CAMERA_WB_INCANDESCENT");
			sr200pc10_sensor_write_list(sr200pc10_cfg_wb_incandescent, sizeof(sr200pc10_cfg_wb_incandescent)/\
			sizeof(sr200pc10_cfg_wb_incandescent[0]), "sr200pc10_cfg_wb_incandescent");
			break;

		case CAMERA_WB_FLUORESCENT:
			PCAM_DEBUG("CAMERA_WB_FLUORESCENT");
			sr200pc10_sensor_write_list(sr200pc10_cfg_wb_fluorescent, sizeof(sr200pc10_cfg_wb_fluorescent)/\
			sizeof(sr200pc10_cfg_wb_fluorescent[0]), "sr200pc10_cfg_wb_fluorescent");
			break;

		case CAMERA_WB_DAYLIGHT:
			PCAM_DEBUG("<=PCAM=> CAMERA_WB_DAYLIGHT");
			sr200pc10_sensor_write_list(sr200pc10_cfg_wb_daylight, sizeof(sr200pc10_cfg_wb_daylight)/\
			sizeof(sr200pc10_cfg_wb_daylight[0]), "sr200pc10_cfg_wb_daylight");
			break;

		case CAMERA_WB_CLOUDY_DAYLIGHT:
			PCAM_DEBUG("<=PCAM=> CAMERA_WB_CLOUDY_DAYLIGHT");
			sr200pc10_sensor_write_list(sr200pc10_cfg_wb_cloudy, sizeof(sr200pc10_cfg_wb_cloudy)/\
			sizeof(sr200pc10_cfg_wb_cloudy[0]), "sr200pc10_cfg_wb_cloudy");
			break;

		default:
			printk("<=PCAM=> unexpected WB mode %s/%d\n", __func__, __LINE__);
			return -EINVAL;
 	}
	return rc;
}

static long sr200pc10_set_metering(int mode, int metering)
{
	long rc = 0;

	PCAM_DEBUG("mode : %d,   metering : %d", mode, metering);
#if 0
	switch (mode) {
		case SENSOR_PREVIEW_MODE:
			printk("<=PCAM=> %s SENSOR_PREVIEW_MODE\n", __func__);
	 		break;

		case SENSOR_SNAPSHOT_MODE:
			printk("<=PCAM=> 222222 %s SENSOR_SNAPSHOT_MODE\n", __func__);
	  		break;

		default:
			printk("<=PCAM=> %s default\n", __func__);
			break;
	}
#endif
	switch (metering) {

		case CAMERA_AEC_CENTER_WEIGHTED:
			PCAM_DEBUG("CAMERA_AEC_CENTER_WEIGHTED");
			sr200pc10_sensor_write_list(sr200pc10_exposure_centerweighted, sizeof(sr200pc10_exposure_centerweighted)/\
			sizeof(sr200pc10_exposure_centerweighted[0]), "sr200pc10_exposure_centerweighted");
			break;

		case CAMERA_AEC_SPOT_METERING:
			PCAM_DEBUG("CAMERA_AEC_SPOT_METERING");
			sr200pc10_sensor_write_list(sr200pc10_exposure_spot, sizeof(sr200pc10_exposure_spot)/\
			sizeof(sr200pc10_exposure_spot[0]), "sr200pc10_exposure_spot");
			break;

		case CAMERA_AEC_FRAME_AVERAGE:
			PCAM_DEBUG("CAMERA_AEC_FRAME_AVERAGE");
			sr200pc10_sensor_write_list(sr200pc10_exposure_matrix, sizeof(sr200pc10_exposure_matrix)/\
			sizeof(sr200pc10_exposure_matrix[0]), "sr200pc10_exposure_matrix");
			break;

		default:
			printk("<=PCAM=> unexpected metering %s/%d\n", __func__, __LINE__);
			return -EINVAL;
 	}
	return rc;
}


static long sr200pc10_set_ISO(int mode, int iso)
{
	long rc = 0;

	PCAM_DEBUG("mode : %d,   ISO : %d", mode, iso);
#if 0
	switch (mode) {
		case SENSOR_PREVIEW_MODE:
			printk("<=PCAM=> %s SENSOR_PREVIEW_MODE\n", __func__);
	 		break;

		case SENSOR_SNAPSHOT_MODE:
			printk("<=PCAM=> 222222 %s SENSOR_SNAPSHOT_MODE\n", __func__);
	  		break;

		default:
			printk("<=PCAM=> %s default\n", __func__);
			break;
	}
#endif
	switch (iso) {
		case CAMERA_ISOValue_AUTO:
			PCAM_DEBUG("CAMERA_ISO_AUTO");
			sr200pc10_sensor_write_list(sr200pc10_cfg_iso_auto, sizeof(sr200pc10_cfg_iso_auto)/\
			sizeof(sr200pc10_cfg_iso_auto[0]), "sr200pc10_cfg_iso_auto");			
			break;

		case CAMERA_ISOValue_100:
			PCAM_DEBUG("CAMERA_ISO_100");
			sr200pc10_sensor_write_list(sr200pc10_cfg_iso_100, sizeof(sr200pc10_cfg_iso_100)/\
			sizeof(sr200pc10_cfg_iso_100[0]), "sr200pc10_cfg_iso_100");						
			break;

		case CAMERA_ISOValue_200:
			PCAM_DEBUG("CAMERA_ISO_200");
			sr200pc10_sensor_write_list(sr200pc10_cfg_iso_200, sizeof(sr200pc10_cfg_iso_200)/\
			sizeof(sr200pc10_cfg_iso_200[0]), "sr200pc10_cfg_iso_200");									
			break;

		case CAMERA_ISOValue_400:
			PCAM_DEBUG("CAMERA_ISO_400");
			sr200pc10_sensor_write_list(sr200pc10_cfg_iso_400, sizeof(sr200pc10_cfg_iso_400)/\
			sizeof(sr200pc10_cfg_iso_400[0]), "sr200pc10_cfg_iso_400");												
			break;

		default:
			printk("<=PCAM=> unexpected ISO value %s/%d\n", __func__, __LINE__);
			return -EINVAL;
 	}
	return rc;
}

static long sr200pc10_set_sensor_mode(int mode)
{

//	PCAM_DEBUG("Sensor Mode  mode : %d", mode);
	switch (mode) {
	case SENSOR_PREVIEW_MODE:
	{
		PCAM_DEBUG("Preview");
/*
		sr200pc10_sensor_write_list(sr200pc_cfg_scene_normal, sizeof(sr200pc_cfg_scene_normal)/\
		sizeof(sr200pc_cfg_scene_normal[0]), "sr200pc_cfg_scene_normal"); 
*/	
		sr200pc10_sensor_write_list(sr200pc10_preview_table, sizeof(sr200pc10_preview_table)/\
		sizeof(sr200pc10_preview_table[0]), "sr200pc10_preview_table"); // preview start


	}
		break;

	case SENSOR_SNAPSHOT_MODE:
	{
		PCAM_DEBUG("Capture");				
		sr200pc10_sensor_write_list(sr200pc10_capture_table, sizeof(sr200pc10_capture_table)/\
		sizeof(sr200pc10_capture_table[0]), "sr200pc10_capture_table");
	}
		break;

	case SENSOR_RAW_SNAPSHOT_MODE:
		printk("<=PCAM=> ??? Capture RAW \n");		
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int sr200pc10_sensor_init_probe(const struct msm_camera_sensor_info *data)
{
	int rc = 0;


	mdelay(10);
	sr200pc10_sensor_write_list(sr200pc10_init0,sizeof(sr200pc10_init0)/sizeof(sr200pc10_init0[0]), "sr200pc10_init0");

	msleep(100);	

	return rc;

}

int sr200pc10_sensor_init(const struct msm_camera_sensor_info *data)
{
	int rc = 0;



	sr200pc10_ctrl = kzalloc(sizeof(struct sr200pc10_ctrl), GFP_KERNEL);
	if (!sr200pc10_ctrl) {
		CDBG("sr200pc10_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}

	if (data)
		sr200pc10_ctrl->sensordata = data;


	rc = cam_hw_init();
	if (rc < 0) 
	{
		printk("<=PCAM=> cam_hw_init failed!\n");
		goto init_fail;
	}


#ifdef CONFIG_LOAD_FILE
	sr200pc10_regs_table_init();
#endif


	rc = sr200pc10_sensor_init_probe(data);
	if (rc < 0) {
		CDBG("sr200pc10_sensor_init failed!\n");
		goto init_fail;
	}


init_done:
	return rc;

init_fail:
	kfree(sr200pc10_ctrl);
	return rc;
}

static int sr200pc10_init_client(struct i2c_client *client)
{
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&sr200pc10_wait_queue);
	return 0;
}

int sr200pc10_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cfg_data;
	long   rc = 0;

	if (copy_from_user(&cfg_data,
			(void *)argp,
			sizeof(struct sensor_cfg_data)))
		return -EFAULT;

	/* down(&sr200pc10_sem); */

	CDBG("sr200pc10_ioctl, cfgtype = %d, mode = %d\n",
		cfg_data.cfgtype, cfg_data.mode);

		switch (cfg_data.cfgtype) {
		case CFG_SET_MODE:
			rc = sr200pc10_set_sensor_mode(
						cfg_data.mode);
			break;

		case CFG_SET_EFFECT:
			rc = sr200pc10_set_effect(cfg_data.mode,
						cfg_data.cfg.effect);
			break;

		case CFG_SET_BRIGHTNESS:
#if 0
			rc = sr200pc10_set_brightness(cfg_data.mode,
						cfg_data.cfg.brightness);
#endif
			break;

		case CFG_SET_WB:
#if 0
			rc = sr200pc10_set_whitebalance(cfg_data.mode,
						cfg_data.cfg.whitebalance);
#endif
			break;

		case CFG_SEND_WB_INFO:
#if 0
			rc = sr200pc10_set_ISO(cfg_data.mode,
						cfg_data.cfg.iso);
#endif
			break;

		case CFG_SET_EXPOSURE_MODE:
#if 0
			rc = sr200pc10_set_metering(cfg_data.mode,
						cfg_data.cfg.metering);
#endif
			break;

		case CFG_GET_AF_MAX_STEPS:
		default:
			rc = -EINVAL;
			break;
		}

	/* up(&sr200pc10_sem); */

	return rc;
}

int sr200pc10_sensor_release(void)
{
	int rc = 0;

	/* down(&sr200pc10_sem); */


	PCAM_DEBUG("sensor release");	


	sr200pc10_sensor_write_list(sr200pc_sleep_command, sizeof(sr200pc_sleep_command)/\
		sizeof(sr200pc_sleep_command[0]), "sr200pc_sleep_command"); 


	kfree(sr200pc10_ctrl);
	/* up(&sr200pc10_sem); */

#ifdef CONFIG_LOAD_FILE
	sr200pc10_regs_table_exit();
#endif


	return rc;
}

static int sr200pc10_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		rc = -ENOTSUPP;
		goto probe_failure;
	}

	sr200pc10_sensorw =
		kzalloc(sizeof(struct sr200pc10_work), GFP_KERNEL);

	if (!sr200pc10_sensorw) {
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, sr200pc10_sensorw);
	sr200pc10_init_client(client);
	sr200pc10_client = client;


	CDBG("sr200pc10_probe succeeded!\n");

	return 0;

probe_failure:
	kfree(sr200pc10_sensorw);
	sr200pc10_sensorw = NULL;
	CDBG("sr200pc10_probe failed!\n");
	return rc;
}

static const struct i2c_device_id sr200pc10_i2c_id[] = {
	{ "sr200pc10", 0},
	{ },
};

static struct i2c_driver sr200pc10_i2c_driver = {
	.id_table = sr200pc10_i2c_id,
	.probe  = sr200pc10_i2c_probe,
	.remove = __exit_p(sr200pc10_i2c_remove),
	.driver = {
		.name = "sr200pc10",
	},
};


static int sr200pc10_sensor_probe(const struct msm_camera_sensor_info *info,
				struct msm_sensor_ctrl *s)
{

	int rc = i2c_add_driver(&sr200pc10_i2c_driver);
	if (rc < 0 || sr200pc10_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_done;
	}


	/* Input MCLK = 24MHz */
	msm_camio_clk_rate_set(24000000);
	mdelay(5);


#if 0//bestiq
	rc = sr200pc10_sensor_init_probe(info);
	if (rc < 0)
		goto probe_done;
#endif


	cam_pw(0); //TEMP

	s->s_init = sr200pc10_sensor_init;
	s->s_release = sr200pc10_sensor_release;
	s->s_config  = sr200pc10_sensor_config;



probe_done:
	CDBG("%s %s:%d\n", __FILE__, __func__, __LINE__);
	return rc;
}

static int __sr200pc10_probe(struct platform_device *pdev)
{
	return msm_camera_drv_start(pdev, sr200pc10_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
	.probe = __sr200pc10_probe,
	.driver = {
		.name = "msm_camera_sr200pc10",
		.owner = THIS_MODULE,
	},
};

static int __init sr200pc10_init(void)
{
	return platform_driver_register(&msm_camera_driver);
}

module_init(sr200pc10_init);
