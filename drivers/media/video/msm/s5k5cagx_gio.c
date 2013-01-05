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
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <media/msm_camera.h>
#include <mach/gpio.h>
#include "s5k5cagx_gio.h"
#include <mach/camera.h>
#include <mach/vreg.h>
#include <linux/io.h>
#define SENSOR_DEBUG 0
//#define CONFIG_LOAD_FILE
#define S5K5CAGX_BURST_WRITE_LIST(A) s5k5cagx_sensor_burst_write_list(A,(sizeof(A) / sizeof(A[0])),#A);
#define S5K5CAGX_WRITE_LIST(A) s5k5cagx_sensor_write_list(A,(sizeof(A) / sizeof(A[0])),#A);
#define CHECK_EFFECT 0x00000001
#define CHECK_BRIGHTNESS 0x00000002
#define CHECK_CONTRAST 0x00000004
#define CHECK_SATURATION 0x00000008
#define CHECK_SHARPNESS 0x00000010
#define CHECK_WB 0x00000020
#define CHECK_ISO 0x00000040
#define CHECK_AE 0x00000080
#define CHECK_SCENE 0x00000100
#define CHECK_AFMODE 0x00000200
#define CHECK_DTP 0x00000400
#define CHECK_SNAPSHOT_SIZE 0x00000800
#define CHECK_PREVIEW_SIZE 0x00001000
#define CHECK_ZOOM 0x00002000
#define CHECK_JPEGQUALITY 0x00004000
#define CHECK_AUTOCONTRAST 0x00008000
#define CHECK_FPS 0x00010000
#define CHECK_AE_AWB_LOCK 0x00020000
struct s5k5cagx_status_struct {
	char camera_initailized;//  1 is not init a sensor
	u32 need_configuration;
	char camera_mode;
	char effect;
	char brightness;
	char contrast;
	char saturation;
	char sharpness;
	char whiteBalance;
	char iso;
	char auto_exposure;
	char scene;
	char afmode;
	char afcanceled;
	char dtp;
	char snapshot_size;
	char preview_size;
	char lowcap_on;
	char nightcap_on;
	char power_on;
	char fps;
	char ae_lock;
	char awb_lock;
	char camera_status;
	int current_lux;
	unsigned short id;
};
static struct s5k5cagx_status_struct s5k5cagx_status;
struct s5k5cagx_work {
	struct work_struct work;
};
static struct  s5k5cagx_work *s5k5cagx_sensorw;
static struct  i2c_client *s5k5cagx_client;
struct s5k5cagx_ctrl {
	const struct msm_camera_sensor_info *sensordata;
};
static struct s5k5cagx_ctrl *s5k5cagx_ctrl;
static DECLARE_WAIT_QUEUE_HEAD(s5k5cagx_wait_queue);
DECLARE_MUTEX(s5k5cagx_sem);
/*=============================================================
	EXTERNAL DECLARATIONS
==============================================================*/
extern struct s5k5cagx_reg s5k5cagx_regs;
extern int cpufreq_direct_set_policy(unsigned int cpu, const char *buf);
extern void pcam_msm_i2c_pwr_mgmt(struct i2c_adapter *adap, int on);
extern int* get_i2c_clock_addr(struct i2c_adapter *adap);
/*=============================================================*/
static int cam_hw_init(void);
void sensor_DTP_control(char value);
#ifdef CONFIG_LOAD_FILE
	static int s5k5cagx_regs_table_write(char *name);
#endif
static int s5k5cagx_sensor_read(unsigned short subaddr, unsigned short *data)
{
	int ret;
	unsigned char buf[2];
	struct i2c_msg msg = { s5k5cagx_client->addr, 0, 2, buf };

	buf[0] = (subaddr >> 8);
	buf[1] = (subaddr & 0xFF);
	ret = i2c_transfer(s5k5cagx_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO)
		goto error;
	msg.flags = I2C_M_RD;

	ret = i2c_transfer(s5k5cagx_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
	if (ret == -EIO)
		goto error;
	*data = ((buf[0] << 8) | buf[1]);
error:
	return ret;
}
static int s5k5cagx_sensor_write(unsigned short subaddr, unsigned short val)
{
	unsigned char buf[4];
	struct i2c_msg msg = { s5k5cagx_client->addr, 0, 4, buf };
	buf[0] = (subaddr >> 8);
	buf[1] = (subaddr & 0xFF);
	buf[2] = (val >> 8);
	buf[3] = (val & 0xFF);
	return i2c_transfer(s5k5cagx_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
}
static int s5k5cagx_sensor_write_list(struct samsung_short_t *list,int size, char *name)
{
	int ret = 0;
	int i = 0;
#ifdef CONFIG_LOAD_FILE
	ret = s5k5cagx_regs_table_write(name);
#else
	printk("[S5K5CAGX] s5k5cagx_sensor_write_list : %s\n", name);
	for (i = 0; i < size; i++)
	{
	//printk("[PGH] %x      %x\n", list[i].subaddr, list[i].value);
		if(list[i].subaddr == 0xffff)
		{
			//printk("[S5K5CAGX] now SLEEP!!!!\n  %d", list[i].value);
			msleep(list[i].value);
		}
		else
		{
		    if(s5k5cagx_sensor_write(list[i].subaddr, list[i].value) < 0)
		    {
			    printk("[S5K5CAGX] sensor_write_list fail...-_-\n");
			    return -1;
		    }
		}
	}
#endif
	return ret;
}
#define BURST_MODE_BUFFER_MAX_SIZE 2700
unsigned char s5k5cagx_buf_for_burstmode[BURST_MODE_BUFFER_MAX_SIZE];
static int s5k5cagx_sensor_burst_write_list(struct samsung_short_t *list,int size, char *name)
{
	int err = -EINVAL;
	int i = 0;
	int idx = 0;
	unsigned short subaddr = 0, next_subaddr = 0;
	unsigned short value = 0;
	struct i2c_msg msg = {  s5k5cagx_client->addr, 0, 0, s5k5cagx_buf_for_burstmode};

	printk("[S5K5CAGX] s5k5cagx_sensor_burst_write_list : %s\n", name);

	for (i = 0; i < size; i++)
	{
		if(idx > (BURST_MODE_BUFFER_MAX_SIZE-10))
		{
			printk("[S5K5CAGX] BURST MODE buffer overflow!!!\n");
			 return err;
		}
		subaddr = list[i].subaddr;
		if(subaddr == 0x0F12)next_subaddr = list[i+1].subaddr;
		value = list[i].value;
		switch(subaddr)
		{
			case 0x0F12:
			{
				// make and fill buffer for burst mode write
				if(idx ==0)
				{
					s5k5cagx_buf_for_burstmode[idx++] = 0x0F;
					s5k5cagx_buf_for_burstmode[idx++] = 0x12;
				}
				s5k5cagx_buf_for_burstmode[idx++] = value>> 8;
				s5k5cagx_buf_for_burstmode[idx++] = value & 0xFF;

				//write in burstmode
				if(next_subaddr != 0x0F12)
				{
					msg.len = idx;
					err = i2c_transfer(s5k5cagx_client->adapter, &msg, 1) == 1 ? 0 : -EIO;
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
			    err = s5k5cagx_sensor_write(subaddr, value);
			}
			break;
		}
	}
	if (unlikely(err < 0))
	{
		printk("[S5K5CAGX]%s: register set failed\n",__func__);
		return err;
	}

	return 0;
}
void s5k5cagx_set_effect(char value)
{
	switch(value)
	{
		case EXT_CFG_EFFECT_NORMAL :
			S5K5CAGX_WRITE_LIST(s5k5cagx_effect_off);
		break;
		case EXT_CFG_EFFECT_NEGATIVE :
			S5K5CAGX_WRITE_LIST(s5k5cagx_effect_negative);
		break;

		case EXT_CFG_EFFECT_MONO :
			S5K5CAGX_WRITE_LIST(s5k5cagx_effect_mono);
		break;
		case EXT_CFG_EFFECT_SEPIA :
			S5K5CAGX_WRITE_LIST(s5k5cagx_effect_sepia);
		break;
		default :
			printk("[S5K5CAGX] Unexpected Effect mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_whitebalance(char value)
{
	switch(value)
	{
		case EXT_CFG_WB_AUTO :
			S5K5CAGX_WRITE_LIST(s5k5cagx_wb_auto);
		break;
		case EXT_CFG_WB_DAYLIGHT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_wb_daylight);
		break;
		case EXT_CFG_WB_CLOUDY :
			S5K5CAGX_WRITE_LIST(s5k5cagx_wb_cloudy);
		break;
		case EXT_CFG_WB_FLUORESCENT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_wb_fluorescent);
		break;

		case EXT_CFG_WB_INCANDESCENT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_wb_incandescent);
		break;
		default :
			printk("[S5K5CAGX] Unexpected WB mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_brightness(char value)
{
	switch(value)
	{
		case PCAM_BR_STEP_P_4 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_p_4);
		break;

		case PCAM_BR_STEP_P_3 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_p_3);
		break;
		case PCAM_BR_STEP_P_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_p_2);
		break;
		case PCAM_BR_STEP_P_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_p_1);
		break;
		case PCAM_BR_STEP_0 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_0);
		break;
		case PCAM_BR_STEP_M_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_m_1);
		break;
		case PCAM_BR_STEP_M_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_m_2);
		break;
		case PCAM_BR_STEP_M_3 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_m_3);
		break;
		case PCAM_BR_STEP_M_4 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_brightness_m_4);
		break;
		default :
			printk("[S5K5CAGX] Unexpected BR mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_iso(char value)
{
	switch(value)
	{
		case EXT_CFG_ISO_AUTO :
			S5K5CAGX_WRITE_LIST(s5k5cagx_iso_auto);
		break;
		case EXT_CFG_ISO_50 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_iso_50);
		break;
		case EXT_CFG_ISO_100 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_iso_100);
		break;
		case EXT_CFG_ISO_200 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_iso_200);
		break;
		case EXT_CFG_ISO_400 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_iso_400);
		break;
		default :
			printk("[S5K5CAGX] Unexpected ISO mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_metering(char value)
{
	switch(value)
	{
		case EXT_CFG_METERING_NORMAL :
			S5K5CAGX_WRITE_LIST(s5k5cagx_metering_normal);
		break;
		case EXT_CFG_METERING_SPOT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_metering_spot);
		break;
		case EXT_CFG_METERING_CENTER :
			S5K5CAGX_WRITE_LIST(s5k5cagx_metering_center);
		break;
		default :
			printk("[S5K5CAGX] Unexpected METERING mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_scene(char value)
{
	S5K5CAGX_WRITE_LIST(s5k5cagx_scene_off);
	switch(value)
	{
		//case PCAM_SCENE_OFF :
		case EXT_CFG_SCENE_PORTRAIT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_portrait);
		break;
		case EXT_CFG_SCENE_LANDSCAPE :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_landscape);
		break;
		case EXT_CFG_SCENE_SPORTS :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_sports);
		break;
		case EXT_CFG_SCENE_PARTY :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_party);
		break;
		case EXT_CFG_SCENE_BEACH :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_beach);
		break;
		case EXT_CFG_SCENE_SUNSET :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_sunset);
		break;
		case EXT_CFG_SCENE_DAWN :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_dawn);
		break;
		case EXT_CFG_SCENE_FALL :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_fall);
		break;
		case EXT_CFG_SCENE_NIGHTSHOT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_nightshot);
		break;
		case EXT_CFG_SCENE_BACKLIGHT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_backlight);
		break;
		case EXT_CFG_SCENE_FIREWORK :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_firework);
		break;
		case EXT_CFG_SCENE_TEXT :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_text);
		break;
		case EXT_CFG_SCENE_CANDLE :
			S5K5CAGX_WRITE_LIST(s5k5cagx_scene_candle);
		break;
		default :
			printk("[S5K5CAGX] Unexpected SCENE mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_contrast(char value)
{
	switch(value)
	{
		case PCAM_CR_STEP_M_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_contrast_m_2);
		break;
		case PCAM_CR_STEP_M_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_contrast_m_1);
		break;
		case PCAM_CR_STEP_0 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_contrast_0);
		break;
		case PCAM_CR_STEP_P_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_contrast_p_1);
		break;
		case PCAM_CR_STEP_P_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_contrast_p_2);
		break;
		default :
			printk("[S5K5CAGX] Unexpected PCAM_CR_CONTROL mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_saturation(char value)
{
	switch(value)
	{
		case PCAM_SA_STEP_M_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_saturation_m_2);
		break;
		case PCAM_SA_STEP_M_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_saturation_m_1);
		break;
		case PCAM_SA_STEP_0 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_saturation_0);
		break;
		case PCAM_SA_STEP_P_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_saturation_p_1);
		break;
		case PCAM_SA_STEP_P_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_saturation_p_2);
		break;
		default :
			printk("[S5K5CAGX] Unexpected PCAM_SA_CONTROL mode : %d\n",  value);
		break;
	}
}
void s5k5cagx_set_sharpness(char value)
{
	switch(value)
	{
		case PCAM_SP_STEP_M_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_sharpness_m_2);
		break;
		case PCAM_SP_STEP_M_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_sharpness_m_1);
		break;
		case PCAM_SP_STEP_0 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_sharpness_0);
		break;
		case PCAM_SP_STEP_P_1 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_sharpness_p_1);
		break;
		case PCAM_SP_STEP_P_2 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_sharpness_p_2);
		break;
		default :
			printk("[S5K5CAGX] Unexpected PCAM_SP_CONTROL mode : %d\n",  value);
		break;
	}
}
int s5k5cagx_set_af(char value)
{
	switch(value)
	{
		case PCAM_AF_CHECK_STATUS :{
			unsigned short af_status;
			s5k5cagx_sensor_write(0x002C, 0x7000);
			s5k5cagx_sensor_write(0x002E, 0x26FE);
			s5k5cagx_sensor_read(0x0F12, &af_status);
			S5K5CAGX_DEBUG("AF_CHECK_STATUS : %d\n",af_status);
			return af_status;
		}
		break;
		case PCAM_AF_OFF :
			S5K5CAGX_WRITE_LIST(s5k5cagx_af_off);
		break;
		case PCAM_AF_SET_NORMAL :
			S5K5CAGX_WRITE_LIST(s5k5cagx_af_normal_on);
		break;
		case PCAM_AF_SET_MACRO :
			S5K5CAGX_WRITE_LIST(s5k5cagx_af_macro_on);
		break;
		case PCAM_AF_DO :
			S5K5CAGX_WRITE_LIST(s5k5cagx_af_do);
		break;

		//case PCAM_AF_ABORT :
		//	S5K5CAGX_WRITE_LIST(s5k5cagx_af_abort);
		//break;
		default :
			printk("[S5K5CAGX] unexpected AF command : %d\n",value);
		break;
	}
	return 0;
}
void s5k5cagx_set_DTP(char value)
{
	switch(value)
	{
		case PCAM_DTP_OFF:
			S5K5CAGX_WRITE_LIST(s5k5cagx_dtp_off);
		break;
		case PCAM_DTP_ON:
			S5K5CAGX_WRITE_LIST(s5k5cagx_dtp_on);
		break;
		default:
			printk("[S5K5CAGX] unexpected DTP control on PCAM\n");
		break;
	}
}
void s5k5cagx_set_fps(char value)
{
	switch(value)
	{
		case PCAM_FRAME_AUTO :
			//S5K4ECGX_WRITE_LIST(s5k5cagx_FPS_15);
		break;
		case PCAM_FRAME_FIX_15 :
			S5K5CAGX_WRITE_LIST(s5k5cagx_fps_15fix);
		break;
		//case PCAM_FRAME_FIX_30 :
			//S5K4ECGX_WRITE_LIST(s5k5cagx_FPS_20);
		//break;
		default :
			printk("[S5K4ECGX]Unexpected PCAM_FRAME_CONTROL mode : %d\n", value);
		break;
	}
}
void sensor_rough_control(void __user *arg)
{
	ioctl_pcam_info_8bit ctrl_info;
	if(copy_from_user((void *)&ctrl_info, (const void *)arg, sizeof(ctrl_info)))
	{
		printk("[S5K5CAGX] %s fail copy_from_user!\n", __func__);
	}
	switch(ctrl_info.mode)
	{
		case PCAM_AUTO_TUNNING:
		break;
		case PCAM_SDCARD_DETECT:
		break;
		case PCAM_GET_INFO:{
			unsigned short lsb, msb, rough_iso;
			s5k5cagx_sensor_write(0xFCFC, 0xD000);
			s5k5cagx_sensor_write(0x002C, 0x7000);
			s5k5cagx_sensor_write(0x002E, 0x23E8);
			s5k5cagx_sensor_read(0x0F12, &lsb); 		//0x2A14
			s5k5cagx_sensor_read(0x0F12, &msb);		//0x2A16
			s5k5cagx_sensor_read(0x0F12, &rough_iso); //0x2A8
			ctrl_info.value_1 = lsb;
			ctrl_info.value_2 = msb;
			printk("[S5K5CAGX] exposure %x %x \n", lsb, msb);
			ctrl_info.value_3 = rough_iso;
			printk("[S5K5CAGX] rough_iso %x \n", rough_iso);
		}
		break;
		case PCAM_FRAME_CONTROL:
			s5k5cagx_status.fps = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_FPS;
			else
				s5k5cagx_set_fps(s5k5cagx_status.fps);
		break;
		case PCAM_AF_CONTROL:
			if(ctrl_info.value_1 ==  2|| ctrl_info.value_1 == 3)s5k5cagx_status.afmode= ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_AFMODE;
			else
				ctrl_info.value_3 = s5k5cagx_set_af(ctrl_info.value_1);
		break;
		case PCAM_EFFECT_CONTROL:
			s5k5cagx_status.effect = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_EFFECT;
			else
				s5k5cagx_set_effect(s5k5cagx_status.effect);
		break;
		case PCAM_WB_CONTROL:
			s5k5cagx_status.whiteBalance = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_WB;
			else
				s5k5cagx_set_whitebalance(s5k5cagx_status.whiteBalance);
		break;
		case PCAM_BR_CONTROL:
			s5k5cagx_status.brightness = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_BRIGHTNESS;
			else
				s5k5cagx_set_brightness(s5k5cagx_status.brightness);
		break;
		case PCAM_ISO_CONTROL:
			s5k5cagx_status.iso = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_ISO;
			else
				s5k5cagx_set_iso(s5k5cagx_status.iso);
		break;
		case PCAM_METERING_CONTROL:
			s5k5cagx_status.auto_exposure = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_AE;
			else
				s5k5cagx_set_metering(s5k5cagx_status.auto_exposure);
		break;
		case PCAM_SCENE_CONTROL:
			s5k5cagx_status.scene = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration|= CHECK_SCENE;
			else
				s5k5cagx_set_scene(s5k5cagx_status.scene);
		break;
		case PCAM_AWB_AE_CONTROL:     //110107 hm83.cho   add AE/AWB Lock
		{
			switch(ctrl_info.value_1)
			{
				case PCAM_AWB_AE_LOCK :{
					if(s5k5cagx_status.whiteBalance == EXT_CFG_WB_AUTO)
					{
						S5K5CAGX_WRITE_LIST(s5k5cagx_awb_ae_lock);
					}
				}
				break;
				case PCAM_AWB_AE_UNLOCK :{
					if(s5k5cagx_status.whiteBalance == EXT_CFG_WB_AUTO)
					{
						S5K5CAGX_WRITE_LIST(s5k5cagx_awb_ae_unlock);
					}
				}
				break;
				default :{
					printk("[S5K5CAGX] Unexpected AWB_AE mode : %d\n", ctrl_info.value_1);
				}
				break;
			}
		}
		break;
		case PCAM_CR_CONTROL:
			s5k5cagx_status.contrast = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration|= CHECK_CONTRAST;
			else
				s5k5cagx_set_contrast(s5k5cagx_status.contrast);
		break;
		case PCAM_SA_CONTROL:
			s5k5cagx_status.saturation = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_SATURATION;
			else
				s5k5cagx_set_saturation(s5k5cagx_status.saturation);
		break;
		case PCAM_SP_CONTROL:
			s5k5cagx_status.sharpness = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_SHARPNESS;
			else
				s5k5cagx_set_sharpness(s5k5cagx_status.sharpness);
		break;
		case PCAM_CPU_CONTROL:{
			switch(ctrl_info.value_1)
			{
				case PCAM_CPU_CONSERVATIVE:{
				S5K5CAGX_DEBUG("now conservative\n");
				cpufreq_direct_set_policy(0, "conservative");
				}
				break;
				case PCAM_CPU_ONDEMAND:{
				S5K5CAGX_DEBUG("now ondemand\n");
				/* cpufreq_direct_set_policy(0, "ondemand"); */
				}
				break;
				case PCAM_CPU_PERFORMANCE:{
				S5K5CAGX_DEBUG("now performance\n");
				cpufreq_direct_set_policy(0, "performance");
				}
				break;
				default:{
					printk("[S5K5CAGX] unexpected CPU control on PCAM\n");
				}
				break;
			}
		}
		break;
		case PCAM_DTP_CONTROL:
			s5k5cagx_status.dtp = ctrl_info.value_1;
			if(!s5k5cagx_status.camera_initailized)
				s5k5cagx_status.need_configuration |= CHECK_DTP;
			else
				s5k5cagx_set_DTP(s5k5cagx_status.dtp);
			if(ctrl_info.value_1 == 0)
					ctrl_info.value_3 = 2;
			else if(ctrl_info.value_1 == 1)
					ctrl_info.value_3 = 3;
		break;
/*
		case PCAM_SET_PREVIEW_SIZE:
			mMode = ctrl_info.value_1;
		break;
*/
		case PCAM_GET_MODULE_STATUS:
		{
			unsigned short	id = 0; //CAM FOR FW
			//ctrl_info.value_3 = gpio_get_value(0);
			s5k5cagx_sensor_write(0x002C, 0x0000);
			s5k5cagx_sensor_write(0x002E, 0x0040);
			s5k5cagx_sensor_read(0x0F12, &id);

			ctrl_info.value_3 = id;

			printk("[S5K5CAGX] check current module status : %x\n", ctrl_info.value_3);
			printk("[S5K5CAGX] PINON/OFF : %d\n", gpio_get_value(0));
		}
		break;
		default :
			printk("[S5K5CAGX] Unexpected mode on sensor_rough_control : %d\n", ctrl_info.mode);
		break;
	}
	if(copy_to_user((void *)arg, (const void *)&ctrl_info, sizeof(ctrl_info)))
	{
		printk("[S5K5CAGX] %s fail on copy_to_user!\n", __func__);
	}
}
void cam_pw(int status)
{
	struct vreg *vreg_cam_out8;
	struct vreg *vreg_cam_out9;
	struct vreg *vreg_cam_out10;
        //HW_REV_00 : ldo4, HW_REV_01 : ldo10
	vreg_cam_out10 = vreg_get(NULL, "ldo10"); // VCAM_AF_2.8V
	vreg_cam_out8 = vreg_get(NULL, "ldo8"); // VCAM_IO_2.6V
	vreg_cam_out9 = vreg_get(NULL, "ldo9"); // VCAMA_2.8V
	if(status == 1) //POWER ON
	{
		printk("[S5K5CAGX]Camera Sensor Power ON\n");
		//gpio_direction_output(3, 0);
		//mdelay(100);
		vreg_set_level(vreg_cam_out10, OUT3000mV);
		vreg_set_level(vreg_cam_out9,  OUT2800mV);
		vreg_set_level(vreg_cam_out8,  OUT2800mV);
		gpio_set_value(3,1); //VDDD
		mdelay(1);
		vreg_enable(vreg_cam_out9);//VDDS
		mdelay(1);
		vreg_enable(vreg_cam_out8);// VDDIO
		mdelay(1);
		vreg_enable(vreg_cam_out10);//AF
	}
	else //POWER OFF
	{
		printk("[S5K5CAGX]Camera Sensor Power OFF\n");
		vreg_disable(vreg_cam_out8);// VDDS
		udelay(1);
		vreg_disable(vreg_cam_out9); //VDDIO
		udelay(1);
		gpio_set_value(3,0); //VDDD
		udelay(1);
		vreg_disable(vreg_cam_out10); //AF
		/* cpufreq_direct_set_policy(0, "ondemand"); */
	}
}
static int cam_hw_init()
{
	int rc = 0;
	unsigned short	id = 0; //CAM FOR FW
//	unsigned int	before_time, after_time, i;//I2C SPEED TEST
	S5K5CAGX_DEBUG("next cam_hw_init\n");
	/* Input MCLK = 24MHz */
	msm_camio_clk_rate_set(24000000);
	msm_camio_camif_pad_reg_reset();
	mdelay(1);

	//BENNET NOT USE gpio_set_value(1, 1); //STBY UP
	gpio_set_value(0, 1); //RESET UP
	mdelay(15);
#if 0//PGH I2C SPEED TEST
        before_time = get_jiffies_64();
    for (i = 0; i < 3000; i++)
        {
		s5k5cagx_sensor_write(0x002E, 0x0040);
        }

        after_time = get_jiffies_64();
        printk("[S5K5CAGX] Total Time 3000: %d\n",  jiffies_to_msecs(after_time-before_time));
#endif//PGH I2C SPEED TEST
	s5k5cagx_sensor_write(0x002C, 0x0000);
	s5k5cagx_sensor_write(0x002E, 0x0040);
	s5k5cagx_sensor_read(0x0F12, &id);
	printk("[S5K5CAGX] [GT-S5660V] CURRENT SENSOR FW ID : 0x%x \n", id);
	return rc;
}
static long s5k5cagx_config_effect(int mode, int effect)
{
	return 0;
#ifdef NOT_USE
	long rc = 0;
	switch (mode) {
	case SENSOR_PREVIEW_MODE:
		S5K5CAGX_DEBUG("SENSOR_PREVIEW_MODE\n");
		break;
	case SENSOR_SNAPSHOT_MODE:
		S5K5CAGX_DEBUG("SENSOR_SNAPSHOT_MODE");
		break;
	default:
		printk("[PGH] %s default\n", __func__);
		break;
	}
	switch (effect) {
	case CAMERA_EFFECT_OFF: {
	S5K5CAGX_DEBUG("CAMERA_EFFECT_OFF");
	}
		break;
	case CAMERA_EFFECT_MONO: {
	S5K5CAGX_DEBUG("CAMERA_EFFECT_MONO");
	}
		break;
	case CAMERA_EFFECT_NEGATIVE: {
	S5K5CAGX_DEBUG("CAMERA_EFFECT_NEGATIVE");
	}
		break;
	case CAMERA_EFFECT_SOLARIZE: {
	S5K5CAGX_DEBUG("CAMERA_EFFECT_SOLARIZE");
	}
		break;
	case CAMERA_EFFECT_SEPIA: {
	S5K5CAGX_DEBUG("CAMERA_EFFECT_SEPIA");
	}
		break;
	default: {
	printk("[S5K5CAGX] unexpeceted effect  %s/%d\n", __func__, __LINE__);
		return -EINVAL;
	}

	}
	return rc;
#endif
}
void s5k5cagx_check_REG_TC_GP_EnablePreviewChanged(void)
{
	int cnt = 0;
	int REG_TC_GP_EnableCaptureChanged = 0;
	while(cnt < 150)
	{
		s5k5cagx_sensor_write(0x002C, 0x7000);
		s5k5cagx_sensor_write(0x002E, 0x0222);
		s5k5cagx_sensor_read(0x0F12, (unsigned short*)&REG_TC_GP_EnableCaptureChanged);
		if(!REG_TC_GP_EnableCaptureChanged)break;
		mdelay(10);
		cnt++;
	}
	if(cnt)printk("[S5K4ECGX] wait time for preview frame : %dms\n",cnt*10);
	if(REG_TC_GP_EnableCaptureChanged)printk("[S5K4ECGX] start preview failed.\n");
}
void s5k5cagx_check_REG_TC_GP_EnableCaptureChanged(void)
{
	int cnt = 0;
	int REG_TC_GP_EnableCaptureChanged = 0;
	while(cnt < 150)
	{
		s5k5cagx_sensor_write(0x002C, 0x7000);
		s5k5cagx_sensor_write(0x002E, 0x0226);
		s5k5cagx_sensor_read(0x0F12, (unsigned short*)&REG_TC_GP_EnableCaptureChanged);
		if(!REG_TC_GP_EnableCaptureChanged)break;
		mdelay(10);
		cnt++;
	}
	if(cnt)printk("[S5K4ECGX] wait time for capture frame : %dms\n",cnt*10);
	if(REG_TC_GP_EnableCaptureChanged)printk("[S5K4ECGX] take picture failed.\n");
}
static void s5k5cagx_set_preview(void)
{
	unsigned int before_time, after_time, time_gab;
	int *i2c_clk_addr;
	//i2c_clk_addr = 0xd500c004;
	i2c_clk_addr = get_i2c_clock_addr(s5k5cagx_client->adapter);

	printk("[S5K4ECGX]s5k5cagx_set_preview start\n");
	if(s5k5cagx_status.camera_initailized == false)
	{
		before_time = get_jiffies_64();
#if defined(CONFIG_LOAD_FILE)
		S5K5CAGX_WRITE_LIST(s5k5cagx_init0);
#else
		S5K5CAGX_BURST_WRITE_LIST(s5k5cagx_init0);
#endif
		after_time = get_jiffies_64();
		time_gab = jiffies_to_msecs(after_time-before_time);
		if(time_gab > 600)
		{
			printk("[S5K5CAGX] i2c speed is going down : %dmsec\n", time_gab);
			pcam_msm_i2c_pwr_mgmt(s5k5cagx_client->adapter, 1);
			//this funcion have to call after clk_enable by PCAM, do not use it without pcam's allowance
			printk("[S5K5CAGX] i2c clk set forcely 0x316\n");
			writel(0x316, i2c_clk_addr);
			printk("[S5K5CAGX] re-check i2c clk :%x\n", readl(i2c_clk_addr));
		   }
		else
		{
			printk("[S5K5CAGX] init speed is fine : %dmsec\n", time_gab);
		}
#define DATA_LINE_CHECK
#ifdef DATA_LINE_CHECK
		if(s5k5cagx_status.need_configuration & CHECK_DTP&& s5k5cagx_status.dtp != PCAM_DTP_OFF)s5k5cagx_set_DTP(s5k5cagx_status.dtp);
#endif
	}
	else if(s5k5cagx_status.camera_initailized == true)
	{
		S5K5CAGX_WRITE_LIST(s5k5cagx_preview);
	}

	s5k5cagx_check_REG_TC_GP_EnablePreviewChanged();

	if(s5k5cagx_status.scene == EXT_CFG_SCENE_OFF)
	{
		if(s5k5cagx_status.need_configuration & CHECK_EFFECT && s5k5cagx_status.effect != EXT_CFG_EFFECT_NORMAL)s5k5cagx_set_effect(s5k5cagx_status.effect);
		if(s5k5cagx_status.need_configuration & CHECK_BRIGHTNESS && s5k5cagx_status.brightness != PCAM_BR_STEP_0)s5k5cagx_set_brightness(s5k5cagx_status.brightness);
		if(s5k5cagx_status.need_configuration & CHECK_AE && s5k5cagx_status.auto_exposure != EXT_CFG_METERING_CENTER)s5k5cagx_set_metering(s5k5cagx_status.auto_exposure);
//           temp block PCAM_ISO_AUTO ? no enum value in update GB
//		if(s5k5cagx_status.need_configuration & CHECK_ISO && s5k5cagx_status.iso != PCAM_ISO_AUTO)s5k5cagx_set_iso(s5k5cagx_status.iso);
		if(s5k5cagx_status.need_configuration & CHECK_CONTRAST && s5k5cagx_status.contrast != PCAM_CR_STEP_0 )s5k5cagx_set_contrast(s5k5cagx_status.contrast);
		if(s5k5cagx_status.need_configuration & CHECK_SATURATION && s5k5cagx_status.saturation != PCAM_SA_STEP_0)s5k5cagx_set_saturation(s5k5cagx_status.saturation);
		if(s5k5cagx_status.need_configuration & CHECK_SHARPNESS && s5k5cagx_status.sharpness != PCAM_SP_STEP_0)s5k5cagx_set_sharpness(s5k5cagx_status.sharpness);
		if(s5k5cagx_status.need_configuration & CHECK_WB && s5k5cagx_status.whiteBalance != EXT_CFG_WB_AUTO)s5k5cagx_set_whitebalance(s5k5cagx_status.whiteBalance);
		if(s5k5cagx_status.need_configuration & CHECK_AFMODE && s5k5cagx_status.camera_initailized == false)s5k5cagx_set_af(s5k5cagx_status.afmode);
	}
	else
	{
		s5k5cagx_set_scene(s5k5cagx_status.scene);
	}

	if(s5k5cagx_status.need_configuration & CHECK_FPS)s5k5cagx_set_fps(s5k5cagx_status.fps);
	/* reset status*/
	s5k5cagx_status.preview_size = PCAM_PREVIEW_SIZE_640x480_VGA;
	s5k5cagx_status.camera_initailized = true;
	s5k5cagx_status.lowcap_on= false;
	s5k5cagx_status.nightcap_on= false;
	s5k5cagx_status.afcanceled = false;
	s5k5cagx_status.camera_status = PREVIEW;
}
static void s5k5cagx_set_capture(void)
{
	char vsync_value, cnt;
	int base_high, base_low, cur_lux;
	unsigned short	msb, lsb;

	msb = lsb = 0;
	cur_lux = 0;
	s5k5cagx_status.camera_status = SNAPSHOT;
	/* check a current lux value */
	//s5k5cagx_sensor_write(0x002C, 0x7000);
	//s5k5cagx_sensor_write(0x002E, 0x032E);
	////s5k5cagx_sensor_read(0x0F12, &lsb);
	//s5k5cagx_sensor_read(0x0F12, &msb);
	//base_high = (msb<<16) | lsb;
	//s5k5cagx_sensor_read(0x0F12, &lsb);
	//s5k5cagx_sensor_read(0x0F12, &msb);
	//base_low = (msb<<16) | lsb;                    // 110107 hm83.cho  change lux sequence
	s5k5cagx_sensor_write(0x002C, 0x7000);
	s5k5cagx_sensor_write(0x002E, 0x2448);
	s5k5cagx_sensor_read(0x0F12, &lsb);
	s5k5cagx_sensor_read(0x0F12, &msb);
	cur_lux = (msb<<16) | lsb;

	S5K5CAGX_DEBUG("cur_lux : 0x%08x \n", cur_lux);
	/* check a state of vsync */
	for(cnt=0; cnt<700; cnt++)
	{
		vsync_value = gpio_get_value(14);
		if(vsync_value)
			break;
		else
		{
			S5K5CAGX_DEBUG(" on snapshot,  wait cnt:%d vsync_value:%d\n", cnt, vsync_value);
			msleep(3);
		}
	}
	/* start capture */
	if(cur_lux > 0xFFFE)
	{
		S5K5CAGX_WRITE_LIST(s5k5cagx_high_snapshot);
	}
	else if(cur_lux < 0x0020)
	{
		if((s5k5cagx_status.scene == EXT_CFG_SCENE_NIGHTSHOT) ||(s5k5cagx_status.scene == EXT_CFG_SCENE_FIREWORK) )
		{
			S5K5CAGX_WRITE_LIST(s5k5cagx_night_snapshot);
		}
		else
		{
			S5K5CAGX_WRITE_LIST(s5k5cagx_lowlight_snapshot);
		}
	}
	else
	{
		S5K5CAGX_WRITE_LIST(s5k5cagx_snapshot);
	}
	s5k5cagx_check_REG_TC_GP_EnableCaptureChanged();
}
static long s5k5cagx_set_sensor_mode(int mode)
{
	switch (mode)
	{
		case SENSOR_PREVIEW_MODE:
			s5k5cagx_set_preview();
		break;
		case SENSOR_SNAPSHOT_MODE:
			s5k5cagx_set_capture();
		break;
		case SENSOR_RAW_SNAPSHOT_MODE:
			S5K5CAGX_DEBUG("RAW_SNAPSHOT NOT SUPPORT!!");
		break;
		default:
			return -EINVAL;
	}
	return 0;
}
static int s5k5cagx_sensor_init_probe(const struct msm_camera_sensor_info *data)
{
	int rc = 0;
#ifndef CONFIG_LOAD_FILE
	rc = S5K5CAGX_WRITE_LIST(s5k5cagx_pre_init0);
#endif
	mdelay(10);
	return rc;
}
#ifdef CONFIG_LOAD_FILE
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
static char *s5k5cagx_regs_table = NULL;
static int s5k5cagx_regs_table_size;
void s5k5cagx_regs_table_init(void)
{
	struct file *filp;
	char *dp;
	long l;
	loff_t pos;
	//int i;
	int ret;
	mm_segment_t fs = get_fs();
	printk("%s %d\n", __func__, __LINE__);
	set_fs(get_ds());
#if 0
	filp = filp_open("/data/camera/s5k5cagx.h", O_RDONLY, 0);
#else
	filp = filp_open("/mnt/sdcard/s5k5cagx.h", O_RDONLY, 0);
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
	s5k5cagx_regs_table = dp;
	s5k5cagx_regs_table_size = l;
	*((s5k5cagx_regs_table + s5k5cagx_regs_table_size) - 1) = '\0';
//	printk("s5k5cagx_regs_table 0x%x, %ld\n", dp, l);
}
void s5k5cagx_regs_table_exit(void)
{
	printk("%s %d\n", __func__, __LINE__);
	if (s5k5cagx_regs_table) {
		kfree(s5k5cagx_regs_table);
		s5k5cagx_regs_table = NULL;
	}
}
static int s5k5cagx_regs_table_write(char *name)
{
	char *start, *end, *reg;//, *data;
	unsigned short addr, value;
	char reg_buf[7], data_buf[7];
	addr = value = 0;
	*(reg_buf + 6) = '\0';
	*(data_buf + 6) = '\0';
	start = strstr(s5k5cagx_regs_table, name);
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
			//printk("addr 0x%04x, value 0x%04x\n", addr, value);
			if (addr == 0xffff)
			{
				msleep(value);
				printk("delay 0x%04x, value 0x%04x\n", addr, value);
			}
			else
			{
				if( s5k5cagx_sensor_write(addr, value) < 0 )
				{
					printk("[S5K5CAGX] %s fail on sensor_write\n", __func__);
				}
			}
		}
		else
			printk("[S5K5CAGX] EXCEPTION! reg value : %c  addr : 0x%x,  value : 0x%x\n", *reg, addr, value);
	}
	return 0;
}
#endif
int s5k5cagx_sensor_init(const struct msm_camera_sensor_info *data)
{
	int rc = 0;
	cam_pw(1);
	s5k5cagx_ctrl = kzalloc(sizeof(struct s5k5cagx_ctrl), GFP_KERNEL);
	if (!s5k5cagx_ctrl) {
		CDBG("s5k5cagx_init failed!\n");
		rc = -ENOMEM;
		goto init_done;
	}
	if (data)
		s5k5cagx_ctrl->sensordata = data;
	rc = cam_hw_init();
	if(rc < 0)
	{
		printk("[S5K5CAGX] cam_fw_init failed!\n");
		goto init_fail;
	}
#ifdef CONFIG_LOAD_FILE
	s5k5cagx_regs_table_init();
#endif
	rc = s5k5cagx_sensor_init_probe(data);
	if (rc < 0) {
		CDBG("s5k5cagx_sensor_init failed!\n");
		goto init_fail;
	}
init_done:
	return rc;
init_fail:
	cam_pw(0);
	kfree(s5k5cagx_ctrl);
	return rc;
}
static int s5k5cagx_init_client(struct i2c_client *client)
{
	/* Initialize the MSM_CAMI2C Chip */
	init_waitqueue_head(&s5k5cagx_wait_queue);
	return 0;
}
int s5k5cagx_sensor_config(void __user *argp)
{
	struct sensor_cfg_data cfg_data;
	long   rc = 0;
	if (copy_from_user(&cfg_data,
			(void *)argp,
			sizeof(struct sensor_cfg_data)))
		return -EFAULT;
	/* down(&s5k5cagx_sem); */
	CDBG("s5k5cagx_ioctl, cfgtype = %d, mode = %d\n",
		cfg_data.cfgtype, cfg_data.mode);
		switch (cfg_data.cfgtype) {
		case CFG_SET_MODE:
			rc = s5k5cagx_set_sensor_mode(
						cfg_data.mode);
			break;
		case CFG_SET_EFFECT:
			rc = s5k5cagx_config_effect(cfg_data.mode,
						cfg_data.cfg.effect);
			break;
		case CFG_GET_AF_MAX_STEPS:
		default:
			rc = -EINVAL;
			break;
		}
	/* up(&s5k5cagx_sem); */
	return rc;
}
int s5k5cagx_sensor_release(void)
{
	int rc = 0;
	s5k5cagx_status.camera_initailized = false;
	s5k5cagx_status.need_configuration = 0;
	s5k5cagx_status.effect = 0;
	s5k5cagx_status.brightness = 0;
	s5k5cagx_status.contrast = 0;
	s5k5cagx_status.saturation = 0;
	s5k5cagx_status.sharpness = 0;
	s5k5cagx_status.whiteBalance = 0;
	s5k5cagx_status.iso = 0;
	s5k5cagx_status.auto_exposure = 0;
	s5k5cagx_status.scene = 0;
	s5k5cagx_status.afmode = EXT_CFG_AF_SET_NORMAL;
	s5k5cagx_status.afcanceled = true;
	s5k5cagx_status.dtp = 0;
	cam_pw(0);
	/* cpufreq_direct_set_policy(0, "ondemand"); */
	kfree(s5k5cagx_ctrl);
	/* up(&s5k5cagx_sem); */
#ifdef CONFIG_LOAD_FILE
	s5k5cagx_regs_table_exit();
#endif
	return rc;
}
static int s5k5cagx_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int rc = 0;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		rc = -ENOTSUPP;
		goto probe_failure;
	}
	s5k5cagx_sensorw =
		kzalloc(sizeof(struct s5k5cagx_work), GFP_KERNEL);
	if (!s5k5cagx_sensorw) {
		rc = -ENOMEM;
		goto probe_failure;
	}
	i2c_set_clientdata(client, s5k5cagx_sensorw);
	s5k5cagx_init_client(client);
	s5k5cagx_client = client;

	printk("s5k5cagx_probe succeeded!\n");
	return 0;
probe_failure:
	kfree(s5k5cagx_sensorw);
	s5k5cagx_sensorw = NULL;
	CDBG("s5k5cagx_probe failed!\n");
	return rc;
}
static const struct i2c_device_id s5k5cagx_i2c_id[] = {
	{ "s5k5cagx", 0},
	{ },
};
static struct i2c_driver s5k5cagx_i2c_driver = {
	.id_table = s5k5cagx_i2c_id,
	.probe  = s5k5cagx_i2c_probe,
	.remove = __exit_p(s5k5cagx_i2c_remove),
	.driver = {
		.name = "s5k5cagx",
	},
};
static int s5k5cagx_sensor_probe(const struct msm_camera_sensor_info *info,struct msm_sensor_ctrl *s)
{
	int rc = i2c_add_driver(&s5k5cagx_i2c_driver);
	printk("[S5K5CAGX]s5k5cagx_sensor_probe start\n");
	if (rc < 0 || s5k5cagx_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_done;
	}

	if (rc < 0){// || s5k4ecgx_client == NULL) {
		printk("[S5K5CAGX]s5k4ecgx_sensor_probe fail\n");
		rc = -ENOTSUPP;
		goto probe_done;
	}
	/*initailize states*/
	s5k5cagx_status.camera_initailized = false;
	s5k5cagx_status.need_configuration = 0;
	s5k5cagx_status.camera_mode = 0;
	s5k5cagx_status.effect = EXT_CFG_EFFECT_NORMAL;
	s5k5cagx_status.brightness = PCAM_BR_STEP_0;
	s5k5cagx_status.contrast = PCAM_CR_STEP_0;
	s5k5cagx_status.saturation = PCAM_SA_STEP_0;
	s5k5cagx_status.sharpness = PCAM_SP_STEP_0;
	s5k5cagx_status.whiteBalance = EXT_CFG_WB_AUTO;
	s5k5cagx_status.iso = PCAM_ISO_AUTO;
	s5k5cagx_status.auto_exposure = EXT_CFG_METERING_NORMAL;
	s5k5cagx_status.scene = EXT_CFG_SCENE_OFF;
	s5k5cagx_status.afmode  = EXT_CFG_AF_SET_NORMAL;
	s5k5cagx_status.afcanceled = true;
	s5k5cagx_status.dtp = PCAM_DTP_OFF;
	s5k5cagx_status.snapshot_size = PCAM_SNAPSHOT_SIZE_2560x1920_5M;
	s5k5cagx_status.preview_size = PCAM_PREVIEW_SIZE_640x480_VGA;
	s5k5cagx_status.current_lux = 0;
	/*sensor on/off for vfe initailization */
	cam_pw(1);
        /* Input MCLK = 24MHz */
        msm_camio_clk_rate_set(24000000);
        mdelay(5);
	gpio_set_value(0, 1);//RESET
        mdelay(15);
	rc = s5k5cagx_sensor_init_probe(info);

	if (rc < 0)
		goto probe_done;
	gpio_set_value(0, 0);//RESET
	s->s_init = s5k5cagx_sensor_init;
	s->s_release = s5k5cagx_sensor_release;
	s->s_config  = s5k5cagx_sensor_config;
	s->s_mount_angle = 90; // for CTS
	cam_pw(0);
probe_done:
	printk("%s %s:%d\n", __FILE__, __func__, __LINE__);
	return rc;
}
static int __s5k5cagx_probe(struct platform_device *pdev)
{
	return msm_camera_drv_start(pdev, s5k5cagx_sensor_probe);
}
static struct platform_driver msm_camera_driver = {
	.probe = __s5k5cagx_probe,
	.driver = {
		.name = "msm_camera_s5k5cagx",
		.owner = THIS_MODULE,
	},
};
static int __init s5k5cagx_init(void)
{
	return platform_driver_register(&msm_camera_driver);
}
module_init(s5k5cagx_init);
