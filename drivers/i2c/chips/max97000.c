/*
 * Copyright (C) 2007-2008 SAMSUNG Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/i2c.h>
#include <linux/slab.h>
#include <mach/gpio.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/input.h>
//#include <mach/rpc_pm.h>
#include <mach/vreg.h>
#include <asm/io.h>
//#include <asm/mach-types.h>

#include <linux/i2c/max97000.h> /* define ioctls */
#include <linux/uaccess.h>

#define ALLOW_USPACE_RW		1

static struct i2c_client *pclient;

static int opened;
static int pclk_set;

#define MAX97000_INPUTGAIN 0x00
#define MAX97000_HPH_MIXER 0x01
#define MAX97000_SPK_MIXER 0x02
#define MAX97000_HPH_LEFT_CTRL 0x03
#define MAX97000_HPH_RIGHT_CTRL 0x04
#define MAX97000_SPK_CTRL 0x05
#define MAX97000_LIMITER 0x07
#define MAX97000_PWR_MANAGEMENT 0x08
#define MAX97000_CHARGE_PUMP 0x09
#define MAX97000_REV_ID 0xFF

// khsuh_imst
#define MAX97000_INPUTMODE_CTRL 0x00
#define MAX97000_SPKVOL_CTRL 0x01
#define MAX97000_LEFT_HPHVOL_CTRL 0x02
#define MAX97000_RIGHT_HPHVOL_CTRL 0x03
#define MAX97000_OUTPUTMODE_CTRL 0x04


// khsuh_imsi #if defined(CONFIG_SAMSUNG_TARGET)
#define PATH_MIC_SEL		26
#define AMP_SHDC 23 // active low : 0(Disable) 1(Enable)
// #endif

static struct workqueue_struct *headset_on_work_queue;
static void headset_on_work(struct work_struct *work);
static DECLARE_WORK(g_headset_on_work, headset_on_work);
unsigned char is_incall;
static int is_incallMode = 0;


#ifdef CONFIG_ANDROID_POWER
#include <linux/android_power.h>

static android_suspend_lock_t max97000_suspend_lock = {
	.name = "max97000"
};
static inline void init_suspend(void)
{
	android_init_suspend_lock(&max97000_suspend_lock);
}

static inline void deinit_suspend(void)
{
	android_uninit_suspend_lock(&max97000_suspend_lock);
}

static inline void prevent_suspend(void)
{
	android_lock_idle(&max97000_suspend_lock);
}

static inline void allow_suspend(void)
{
	android_unlock_suspend(&max97000_suspend_lock);
}
#else
static inline void init_suspend(void) {}
static inline void deinit_suspend(void) {}
static inline void prevent_suspend(void) {}
static inline void allow_suspend(void) {}
#endif

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
static void max97000_early_suspend(struct early_suspend *h);
static void max97000_late_resume(struct early_suspend *h);
#endif

DECLARE_MUTEX(audio_sem);

struct max97000_data {
	struct work_struct work;
#ifdef CONFIG_HAS_EARLYSUSPEND
	struct early_suspend early_suspend;
#endif
};

static DECLARE_WAIT_QUEUE_HEAD(g_data_ready_wait_queue);

int max97000_i2c_sensor_init(void);
int max97000_i2c_hph_gain(uint8_t gain);
int max97000_i2c_spk_gain(uint8_t gain);
int max97000_i2c_speaker_onoff(int nOnOff);		// no-in-call
int max97000_i2c_receiver_onoff(int nOnOff);
int max97000_i2c_headset_onoff(int nOnOff);		// in-call
int max97000_i2c_speaker_headset_onoff(int nOnOff);
static int max97000_i2c_write(unsigned char u_addr, unsigned char u_data);
static int max97000_i2c_read(unsigned char u_addr, unsigned char *pu_data);

unsigned char spk_vol, hpl_vol, hpr_vol;
unsigned char spk_vol_mute, hpl_vol_mute, hpr_vol_mute;
static int mic_status = 1;		// 1 sub_mic
static int rec_status = 0;

#define I2C_WRITE(reg,data) max97000_i2c_write(reg, data) /*if (!max97000_i2c_write(reg, data) < 0) return -EIO*/
#define I2C_READ(reg,data) max97000_i2c_read(reg,data) /*if (max97000_i2c_read(reg,data) < 0 ) return -EIO*/

char max97000_outmod_reg;
extern int audio_enabled;

static void headset_on_work(struct work_struct *work)
{
	unsigned char reg_value;

	I2C_READ(MAX97000_PWR_MANAGEMENT,&reg_value);

	if(reg_value & 0x80)
	{
		reg_value &= 0x7F;
        I2C_WRITE(MAX97000_SPK_CTRL,0x0); // MAX 0x1F : 0dB
		I2C_WRITE(MAX97000_HPH_LEFT_CTRL,0x0); // MAX 0x1F : 0dB
		I2C_WRITE(MAX97000_HPH_RIGHT_CTRL,0x0); // MAX 0x1F : 0dB

	}

#if 0
	if(is_incall == 0)
	{
		msleep(6000);
	} else {
		msleep(300);
	}
#else
	msleep(600);
#endif
	max97000_i2c_headset_onoff(true);
}

int audio_i2c_tx_data(char* txData, int length)
{
	int rc; 

	struct i2c_msg msg[] = {
		{
			.addr = pclient->addr,
			.flags = 0,
			.len = length,
			.buf = txData,		
		},
	};
    
	rc = i2c_transfer(pclient->adapter, msg, 1);
	if (rc < 0) {
		printk(KERN_ERR "max97000: audio_i2c_tx_data error %d\n", rc);
		return rc;
	}

#if 0
	else {
		int i;
		/* printk(KERN_INFO "mt_i2c_lens_tx_data: af i2c client addr = %x,"
		   " register addr = 0x%02x%02x:\n", slave_addr, txData[0], txData[1]); 
		   */
		for (i = 0; i < length; i++)
			printk("\tdata[%d]: 0x%02x\n", i, txData[i]);
	}
#endif
	return 0;
}


static int max97000_i2c_write(unsigned char u_addr, unsigned char u_data)
{
	int rc;
	unsigned char buf[2];

	buf[0] = u_addr;
	buf[1] = u_data;
    
	rc = audio_i2c_tx_data(buf, 2);
	if(rc < 0)
		printk(KERN_ERR "max97000: txdata error %d add:0x%02x data:0x%02x\n",
			rc, u_addr, u_data);

	return rc;	
}

static int audio_i2c_rx_data(char* rxData, int length)
{
	int rc;

	struct i2c_msg msgs[] = {
		{
			.addr = pclient->addr,
			.flags = 0,      
			.len = 1,
			.buf = rxData,
		},
		{
			.addr = pclient->addr,
			.flags = I2C_M_RD|I2C_M_NO_RD_ACK,
			.len = length,
			.buf = rxData,
		},
	};

	rc = i2c_transfer(pclient->adapter, msgs, 2);
      
	if (rc < 0) {
		printk(KERN_ERR "max97000: audio_i2c_rx_data error %d\n", rc);
		return rc;
	}
      
#if 0
	else {
		int i;
		for (i = 0; i < length; i++)
			printk(KERN_INFO "\tdata[%d]: 0x%02x\n", i, rxData[i]);
	}
#endif

	return 0;
}

static int max97000_i2c_read(unsigned char u_addr, unsigned char *pu_data)
{
	int rc;
	unsigned char buf;

	buf = u_addr;
	rc = audio_i2c_rx_data(&buf, 1);
	if (!rc)
		*pu_data = buf;
	else printk(KERN_ERR "max97000: i2c read failed\n");
	return rc;	
}


static void max97000_chip_init(void)
{
	printk(KERN_INFO "max97000: init\n");
	if (!pclient) 
		return;

    /* max97000 init sequence */
	printk(KERN_INFO "max97000: max97000 SHDC set High to enable chip \n");
	gpio_set_value(AMP_SHDC,1); // khsuh_imsi SDHC High
      
	/* delay 2 ms */
	msleep(2);
	printk(KERN_INFO "max97000: max97000 sensor init sequence done\n");
}

static int max97000_open(struct inode *ip, struct file *fp)
{
	int rc = -EBUSY;
	down(&audio_sem);
	printk(KERN_INFO "max97000: open\n");
	if (!opened) {
		printk(KERN_INFO "max97000: prevent collapscd e on idle\n");

#ifndef CONFIG_ANDROID_POWER
		prevent_suspend();
#endif
//		opened = 1;
		rc = 0;
	}
	up(&audio_sem);
	return rc;
}

static int max97000_release(struct inode *ip, struct file *fp)
{
	int rc = -EBADF;
	printk(KERN_INFO "max97000: release\n");
	down(&audio_sem);
	if (opened) {
		printk(KERN_INFO "max97000: release clocks\n");
             // PWR_DOWN Ã³¸® max97000_i2c_power_down();
		printk(KERN_INFO "max97000: allow collapse on idle\n");
#ifndef CONFIG_ANDROID_POWER            
		allow_suspend();
#endif
		
		rc = pclk_set = opened = 0;
	}
	up(&audio_sem);
	return rc;
}

#if ALLOW_USPACE_RW
#define COPY_FROM_USER(size) ({                                         \
        if (copy_from_user(rwbuf, argp, size)) rc = -EFAULT;            \
        !rc; })
#endif

static long max97000_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
#if ALLOW_USPACE_RW
	void __user *argp = (void __user *)arg;
#endif
	int rc = 0;
	unsigned char reg_value;

#if ALLOW_USPACE_RW
	unsigned char addr = 0;
	unsigned char data = 0;
    unsigned char temp_buf;
	char rwbuf[2];
#endif

	down(&audio_sem);

	spk_vol_mute = hpl_vol_mute = hpr_vol_mute = 0;

	switch(cmd) {
#if ALLOW_USPACE_RW
	case MAX97000_I2C_IOCTL_W:
		if (COPY_FROM_USER(2)) {
			addr = *((unsigned char *)rwbuf);
			data = *((unsigned char *)(rwbuf+1));
			rc = max97000_i2c_write(addr, data);

			switch(addr)
			{
				case 0x01:
					spk_vol = data;
					break;
				case 0x02:
					hpl_vol = data;
					break;
				case 0x03:
					hpr_vol = data;
					break;
				default:
					break;
			}

		}
		else printk("max97000: write: err %d\n", rc);
		break;

	case MAX97000_I2C_IOCTL_R:
		if (COPY_FROM_USER(2)) {
			addr = *((unsigned char*) rwbuf);
			rc = max97000_i2c_read(addr, (unsigned char *)(rwbuf+1));
			if (!rc) {
				if (copy_to_user(argp, rwbuf, 2)) {
					printk("max97000: read: err writeback -EFAULT\n");
					rc = -EFAULT;
				}
			}
		}
		else printk("max97000: read: err %d\n", rc);
		break;

        case MAX97000_HPH_VOL_SET:
        {
            if (COPY_FROM_USER(2)) {
                temp_buf = *((unsigned char *)rwbuf);
                max97000_i2c_hph_gain(temp_buf);
            }
        }
        break;

    case MAX97000_SPK_VOL_SET:
        {
            if (COPY_FROM_USER(2)) {
                temp_buf = *((unsigned char *)rwbuf);
                max97000_i2c_spk_gain(temp_buf);
            }
        }
        break;
#endif /* ALLOW_USPACE_RW */

    case MAX97000_I2C_IOCTL_SWITCH_DEVICE:
        {
        
        }
        break;

    case MAX97000_SPEAKER_ON:
             {
                printk("max97000 : speaker on\n");
                max97000_i2c_speaker_onoff(true);
             }
		break;    

    case MAX97000_SPEAKER_OFF:
             {
                printk("max97000 : speaker off\n");
                max97000_i2c_speaker_onoff(false);
             }
		break;        

    case MAX97000_HEADSET_ON:
            {
                printk("max97000 : headset on\n");
#if 1
				if (COPY_FROM_USER(2)) {
					is_incall = *((unsigned char *)rwbuf);
				}

				queue_work(headset_on_work_queue, &g_headset_on_work);
#else
                max97000_i2c_headset_onoff(true);
#endif
            }
		break;   

    case MAX97000_HEADSET_OFF:
            {
                printk("max97000 : headset off\n");
                max97000_i2c_headset_onoff(false);
            }
		break;       

    case MAX97000_SPK_EAR_ON: 
                printk("max97000 : speaker headset on\n");
		max97000_i2c_speaker_headset_onoff(true);
		break;    

    case MAX97000_RCV_ON:
            {
                printk("max97000 : receiver on\n");
                max97000_i2c_receiver_onoff(true);
            }
            break;     

    case MAX97000_RCV_OFF:
            {
                printk("max97000 : receiver off\n");
                max97000_i2c_receiver_onoff(false);
            }
            break;

    case MAX97000_I2C_IOCTL_INIT: 
        {
             printk("max97000 : i2c init \n");
		rc = max97000_i2c_sensor_init();
        }
        break;    
       
	case MAX97000_AMP_SUSPEND:
		{
			if(audio_enabled)
			{
				printk("max97000 : AMP suspend\n");
				rc = max97000_i2c_read(MAX97000_PWR_MANAGEMENT,&reg_value);
				if (rc < 0 )
				{
					printk(KERN_ERR "max97000_suspend: max97000_i2c_read failed\n");
					return -EIO;
				}

				max97000_i2c_write(MAX97000_SPK_CTRL,spk_vol_mute);
				max97000_i2c_write(MAX97000_HPH_LEFT_CTRL,hpl_vol_mute);
				max97000_i2c_write(MAX97000_HPH_RIGHT_CTRL,hpr_vol_mute);

				reg_value = reg_value & 0x7f; // SHDN = 0 max97000 shut down

				rc = max97000_i2c_write(MAX97000_PWR_MANAGEMENT, reg_value);
				if (rc < 0 )
				{
					printk(KERN_ERR "max97000_suspend: max97000_i2c_write failed\n");
					return -EIO;
				}

//				msleep(10); // 10m startup time delay
			}
		}
		break;

	case MAX97000_AMP_RESUME:
		{
			if(audio_enabled)
			{
				printk("max97000 : AMP resume\n");
				rc = max97000_i2c_read(MAX97000_PWR_MANAGEMENT,&reg_value);
				if (rc < 0 )
				{
					printk(KERN_ERR "max97000_resume: max97000_i2c_read failed\n");
					return -EIO;
				}

				reg_value = reg_value | 0x80; // SHDN = 1 max97000 wakeup

				rc = max97000_i2c_write(MAX97000_PWR_MANAGEMENT, reg_value);
				if (rc < 0 )
				{
					printk(KERN_ERR "max97000_resume: max97000_i2c_write failed\n");
					return -EIO;
				}

				msleep(10); // 10m startup time delay
//				printk("max97000 : 0x%x, 0x%x, 0x%x.\n", spk_vol, hpl_vol, hpr_vol);

				max97000_i2c_write(MAX97000_SPK_CTRL,spk_vol);
				max97000_i2c_write(MAX97000_HPH_LEFT_CTRL,hpl_vol);
				max97000_i2c_write(MAX97000_HPH_RIGHT_CTRL,hpr_vol);
			}
		}
		break;

	case MAX97000_AMP_RECORDING_MAIN_MIC:
		if(gpio_direction_output(PATH_MIC_SEL, 0))		// main mic
		{
			printk("%s:%d set MIC_SEL fail\n", __func__, __LINE__);
		}
		rec_status = 1;
		printk("%s- MIC_SEL=%d.\n", __func__, gpio_get_value(PATH_MIC_SEL));
		break;

	case MAX97000_AMP_RECORDING_SUB_MIC:
		if(gpio_direction_output(PATH_MIC_SEL, 1))		// sub mic
		{
			printk("%s:%d set MIC_SEL fail\n", __func__, __LINE__);
		}
		rec_status = 0;
		printk("%s- MIC_SEL=%d.\n", __func__, gpio_get_value(PATH_MIC_SEL));
		break;

    default:
        printk(KERN_INFO "max97000: unknown ioctl %d\n", cmd);
        break;
	}

	up(&audio_sem);

	return rc;
}

int max97000_gpio_recording_start(int state)		// for recording
{
		if(gpio_direction_output(PATH_MIC_SEL, state ? 0 : mic_status))		// main mic
		{
			printk("%s:%d set MIC_SEL fail\n", __func__, __LINE__);
			return -1;
		}
		rec_status = state;
		printk("%s- MIC_SEL=%d.\n", __func__, gpio_get_value(PATH_MIC_SEL));
		return 0;
}

int max97000_i2c_sensor_init(void)
{
		// digital setting
        I2C_WRITE(MAX97000_INPUTGAIN,0x52); // INA = Single-End, INB = Differential, pre-gain 0dB

		spk_vol = 0x29; // 6dB
		hpl_vol = hpr_vol = 0x1F; //6dB

		// volume setting 
        I2C_WRITE(MAX97000_SPK_CTRL,spk_vol); // Speaker Unmute, MAX 0x29 : 6dB

        I2C_WRITE(MAX97000_HPH_LEFT_CTRL,hpl_vol); // ZCD Enable, SLEW Enable, HPL Unmute Max 0x1F : 6dB

        I2C_WRITE(MAX97000_HPH_RIGHT_CTRL,hpr_vol); // HPR Unmute MAX 0x1F : 6dB

		// mixer setting
		I2C_WRITE(MAX97000_SPK_MIXER,0x08); // INB2(mono) -> SPKMIX

		I2C_WRITE(MAX97000_HPH_MIXER,0x11); // INA1(Stereo) -> HPHMIX

		// power management
		I2C_WRITE(MAX97000_PWR_MANAGEMENT,0x96); // SHDN = 1 (Enable), SPKEN Enable, HPLEN Enable, HPREN Enable

		printk("MAX97000 : %s is done.\n", __func__);

	return 0;
}

int max97000_i2c_hph_gain(uint8_t gain)
{
	static const uint8_t max_legal_gain  = 0x1F;
	
	if (gain > max_legal_gain) gain = max_legal_gain;

	hpl_vol = hpr_vol = gain;

	I2C_WRITE(MAX97000_HPH_LEFT_CTRL, gain);
	I2C_WRITE(MAX97000_HPH_RIGHT_CTRL, gain);
	return 0;
}

int max97000_i2c_spk_gain(uint8_t gain)
{
	static const uint8_t max_legal_gain  = 0x1F;
	
	if (gain > max_legal_gain) gain = max_legal_gain;

	spk_vol = gain;

	I2C_WRITE(MAX97000_SPK_CTRL, gain);
	return 0;
}

int max97000_i2c_speaker_headset_onoff(int nOnOff)
{
//        unsigned char reg_value;

//		printk("%s(%d) - MIC_SEL=%d.\n", __func__, nOnOff, gpio_get_value(PATH_MIC_SEL));
//		is_incallMode = 0;
        I2C_WRITE(MAX97000_INPUTGAIN,0x52); // dINA = 0(stereo), dINB = 1(mono)
        if( nOnOff )
        {
//            I2C_READ(MAX97000_SPK_MIXER,&reg_value);

//			reg_value &= 0xB0;
//			reg_value |= 0x09;
			I2C_WRITE(MAX97000_HPH_MIXER, 0x88); // INA1 (stereo) -> HPHMIX

            I2C_WRITE(MAX97000_SPK_MIXER, 0x01); // INB2 (mono) -> SPKMIX

        }
        else
        {
#if 1		// return to isr last value
            I2C_WRITE(MAX97000_OUTPUTMODE_CTRL, max97000_outmod_reg); 
#endif
        }

	return 0;
}

int max97000_i2c_speaker_onoff(int nOnOff)
{
        unsigned char reg_value;

#if 0	// defined(CONFIG_SAMSUNG_TARGET)
		if(gpio_direction_output(PATH_MIC_SEL, rec_status ? 0 :nOnOff))
		{
			printk("%s:%d set MIC_SEL fail\n", __func__, __LINE__);
		}
//		printk("%s(%d) - MIC_SEL=%d.\n", __func__, nOnOff, gpio_get_value(PATH_MIC_SEL));
		mic_status = nOnOff;
#endif
		is_incallMode = 0;
        I2C_WRITE(MAX97000_INPUTGAIN,0x52); // dINA = 0(stereo), dINB = 1(mono)

		spk_vol = hpl_vol = hpr_vol = 0x1F;
        if( nOnOff )
        {
            I2C_READ(MAX97000_OUTPUTMODE_CTRL,&reg_value);

			if(audio_enabled)
			{
				reg_value &= 0xB0;
				reg_value |= 0x80;
			}
			else
			{
				reg_value &= 0x30;
			}

			reg_value |= 0x04;		// 07

            I2C_WRITE(MAX97000_OUTPUTMODE_CTRL, reg_value);

        }
        else
        {
            I2C_READ(MAX97000_OUTPUTMODE_CTRL,&reg_value);

			if(audio_enabled)
			{
				reg_value &= 0xB0;
				reg_value |= 0x80;
			}
			else
			{
				reg_value &= 0x30;
			}

			reg_value |= 0x02;		// 08

            I2C_WRITE(MAX97000_OUTPUTMODE_CTRL,reg_value); 
        }
		max97000_outmod_reg = reg_value;
	return 0;
}

int max97000_i2c_receiver_onoff(int nOnOff)
{
        unsigned char reg_value;

#if defined(CONFIG_SAMSUNG_TARGET)
		if(gpio_direction_output(PATH_MIC_SEL, rec_status ? 0 : !nOnOff))
		{
			printk("%s:%d set MIC_SEL fail\n", __func__, __LINE__);
		}
//		printk("%s(%d) - MIC_SEL=%d.\n", __func__, nOnOff, gpio_get_value(PATH_MIC_SEL));
		mic_status = nOnOff ? 0 : 1;	// reverse
#endif
        if( nOnOff )
        {
            I2C_READ(MAX97000_PWR_MANAGEMENT,&reg_value); 

            reg_value &= 0x7F; // SHDN Clear
            
            I2C_WRITE(MAX97000_PWR_MANAGEMENT,reg_value);
        }
        else
        {
            I2C_READ(MAX97000_PWR_MANAGEMENT,&reg_value);

            reg_value |= 0x80; // SHDN Enable

            I2C_WRITE(MAX97000_PWR_MANAGEMENT,reg_value); 
        }
		max97000_outmod_reg = reg_value;

	return 0;
}

int max97000_i2c_headset_onoff(int nOnOff)
{
 //       unsigned char reg_value;

#if defined(CONFIG_SAMSUNG_TARGET)
		if(gpio_direction_output(PATH_MIC_SEL, rec_status ? 0 : !nOnOff))
		{
			printk("%s:%d set MIC_SEL fail\n", __func__, __LINE__);
		}
//		printk("%s(%d) - MIC_SEL=%d.\n", __func__, nOnOff, gpio_get_value(PATH_MIC_SEL));
		mic_status = nOnOff ? 0 : 1;	// reverse
#endif
#if 0
        spk_vol = 0x0A;
		hpl_vol = hpr_vol = 0x15; // 0x17(-9dB) -> 0x1C(-3dB) -> 0x1F(0dB) -> 0x15(-13dB)
#endif
		if(is_incallMode)
		{
			if(audio_enabled)
			{
				I2C_WRITE(MAX97000_INPUTGAIN,0x52); // dINA = 0(stereo), dINB = 1(mono)
			} else {
				I2C_WRITE(MAX97000_INPUTGAIN,0xD2); // dINA = 1(mono), dINB = 1(mono)
			}
		} else {
			I2C_WRITE(MAX97000_INPUTGAIN,0xD2); // dINA = 1(mono), dINB = 1(mono)
			is_incallMode = 1;
		}

        if( nOnOff )
        {
			//I2C_READ(MAX97000_OUTPUTMODE_CTRL,&reg_value);

			//reg_value &= 0xB0;
			//reg_value |= 0x82;		// 08
	
			I2C_WRITE(MAX97000_HPH_MIXER,0x88); // INA1(stereo) -> HPHMIX
		}
		else
		{
			//I2C_READ(MAX97000_OUTPUTMODE_CTRL,&reg_value);

			//reg_value &= 0xB0;
			//reg_value |= 0x84;		// 07

			I2C_WRITE(MAX97000_SPK_MIXER, 0x01); // INB2(mono) -> SPKMIX
		} 
//		max97000_outmod_reg = reg_value;

	return 0;
}



//#undef I2C_WRITE
//#undef I2C_READ

static int max97000_init_client(struct i2c_client *client)
{
	/* Initialize the max97000 Chip */
	init_waitqueue_head(&g_data_ready_wait_queue);
	return 0;
}

static struct file_operations max97000_fops = {
        .owner 	= THIS_MODULE,
        .open 	= max97000_open,
        .release = max97000_release,
        .unlocked_ioctl = max97000_ioctl,
};

static struct miscdevice max97000_device = {
        .minor 	= MISC_DYNAMIC_MINOR,
        .name 	= "max97000",
        .fops 	= &max97000_fops,
};


static int max97000_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct max97000_data *mt;
	int err = 0;
	printk(KERN_INFO "max97000: probe\n");
	if(!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		goto exit_check_functionality_failed;		
	
	if(!(mt = kzalloc( sizeof(struct max97000_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit_alloc_data_failed;
	}

	i2c_set_clientdata(client, mt);
	max97000_init_client(client);
	pclient = client;
	
	max97000_chip_init();
	
	/* Register a misc device */
	err = misc_register(&max97000_device);
	if(err) {
		printk(KERN_ERR "max97000_probe: misc_register failed \n");
		goto exit_misc_device_register_failed;
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
	mt->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN;
	mt->early_suspend.suspend = max97000_early_suspend;
	mt->early_suspend.resume = max97000_late_resume;
	register_early_suspend(&mt->early_suspend);
	printk("register_early_suspend(max97000) \n");
#elif defined (CONFIG_ANDROID_POWER)
	init_suspend();
#endif    

	headset_on_work_queue = create_workqueue("headset_on");
	if (headset_on_work_queue == NULL) {
		goto exit_check_functionality_failed;
	}

	max97000_i2c_sensor_init();
	return 0;
	
exit_misc_device_register_failed:
exit_alloc_data_failed:
exit_check_functionality_failed:
	
	return err;
}

	
static int max97000_remove(struct i2c_client *client)
{
	struct max97000_data *mt = i2c_get_clientdata(client);
	free_irq(client->irq, mt);

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&mt->early_suspend);
#elif defined (CONFIG_ANDROID_POWER)
	deinit_suspend();
#endif

	//khsuh_imsi i2c_detach_client(client);
	pclient = NULL;
	misc_deregister(&max97000_device);
	kfree(mt);
	destroy_workqueue(headset_on_work_queue);
	return 0;
}

void max97000_shutdown(struct i2c_client *client)
{
	int ret;
	
	I2C_WRITE(MAX97000_SPK_CTRL,spk_vol_mute);
	I2C_WRITE(MAX97000_HPH_LEFT_CTRL,hpl_vol_mute);
	I2C_WRITE(MAX97000_HPH_RIGHT_CTRL,hpr_vol_mute);

	ret = I2C_WRITE(MAX97000_PWR_MANAGEMENT, 0x00);
	if (ret < 0 )
	{
		printk(KERN_ERR "max97000_suspend: max97000_i2c_write failed\n");
	}

	printk(KERN_EMERG "max97000_shutdown: success\n");
}

int max97000_suspend(void)
{
    int ret; 
    unsigned char reg_value;
  	
	trace_in();
	spk_vol_mute = hpl_vol_mute = hpr_vol_mute = 0;
	if(!audio_enabled && !is_incallMode) {
		max97000_i2c_write(MAX97000_SPK_CTRL,spk_vol_mute);
		max97000_i2c_write(MAX97000_HPH_LEFT_CTRL,hpl_vol_mute);
		max97000_i2c_write(MAX97000_HPH_RIGHT_CTRL,hpr_vol_mute);
	
		ret = max97000_i2c_read(MAX97000_PWR_MANAGEMENT,&reg_value);
		if (ret < 0 )
		{
			printk(KERN_ERR "max97000_suspend: max97000_i2c_read failed\n");
			//return -EIO;
		}

		reg_value = reg_value & 0x7f; // SHDN = 0 max97000 shut down

		ret = max97000_i2c_write(MAX97000_PWR_MANAGEMENT, reg_value);
		if (ret < 0 )
		{
			printk(KERN_ERR "max97000_suspend: max97000_i2c_write failed\n");
			//return -EIO;
		}
		debug("PWR OFF");
	}
	trace_out();
    return 0;
}

int max97000_resume(void)
{
    int ret; 
    unsigned char reg_value;

	trace_in();
#if 0
	ret = max97000_i2c_read(MAX97000_PWR_MANAGEMENT,&reg_value);
	if (ret < 0 )
	{
		printk(KERN_ERR "max97000_resume: max97000_i2c_read failed\n");
		//return -EIO;
	}
	if(audio_enabled && !(reg_value & 0x80))
	{
		reg_value = reg_value | 0x80; // SHDN = 1 max97000 wakeup

		ret = max97000_i2c_write(MAX97000_PWR_MANAGEMENT, reg_value);
		if (ret < 0 )
		{
			printk(KERN_ERR "max97000_resume: max97000_i2c_write failed\n");
			//return -EIO;
		}
		printk("MAX97000_SHDN wakeup\n");

		msleep(10); // 10m startup time delay

	}
	max97000_i2c_write(MAX97000_SPK_CTRL,spk_vol);
	max97000_i2c_write(MAX97000_HPH_LEFT_CTRL,hpl_vol);
	max97000_i2c_write(MAX97000_HPH_RIGHT_CTRL,hpr_vol);
#else
	ret = max97000_i2c_read(MAX97000_PWR_MANAGEMENT,&reg_value);
	if (ret < 0 )
	{
		printk(KERN_ERR "max97000_resume: max97000_i2c_read failed\n");
		//return -EIO;
	}
	if (!(reg_value & 0x80))
	{
		reg_value = reg_value | 0x80; // SHDN = 1 max97000 wakeup

		ret = max97000_i2c_write(MAX97000_PWR_MANAGEMENT, reg_value);
		if (ret < 0 )
		{
			printk(KERN_ERR "max97000_resume: max97000_i2c_write failed\n");
			//return -EIO;
		}
		debug("PWR_ON");

		msleep(10); // 10m startup time delay
		max97000_i2c_write(MAX97000_SPK_CTRL,spk_vol);
		max97000_i2c_write(MAX97000_HPH_LEFT_CTRL,hpl_vol);
		max97000_i2c_write(MAX97000_HPH_RIGHT_CTRL,hpr_vol);
	}
#endif
	
	trace_out();
    return 0;
}


#ifdef CONFIG_HAS_EARLYSUSPEND
static void max97000_early_suspend(struct early_suspend *h)
{
	struct max97000_data *mt;
	mt = container_of(h, struct max97000_data, early_suspend);
	trace_in();	
	max97000_suspend();
	trace_out();
}

static void max97000_late_resume(struct early_suspend *h)
{
	struct max97000_data *mt;
	mt = container_of(h, struct max97000_data, early_suspend);
	trace_in();	
	max97000_resume();
	trace_out();
}
#endif

#if 0
int max97000_i2c_resume(struct i2c_client *client)
{
	max97000_resume();
	return 0;
}
int max97000_i2c_suspend(struct i2c_client *client, pm_message_t state)
{
	max97000_suspend();
	return 0;
}
#endif

static const struct i2c_device_id max97000_id[] = {
	{ "max97000", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, max97000_id);


static struct i2c_driver max97000_driver = {
	.probe 		= max97000_probe,
	.remove 	= max97000_remove,
	.id_table	= max97000_id,
//	.shutdown 	= max97000_shutdown,
//	.suspend	= max97000_i2c_suspend,
//	.resume		= max97000_i2c_resume,
	.driver = {		
		.name   = "max97000",
	},
};

static int __init max97000_init(void)
{
	return i2c_add_driver(&max97000_driver);
}

static void __exit max97000_exit(void)
{
	i2c_del_driver(&max97000_driver);
}

EXPORT_SYMBOL(max97000_i2c_speaker_onoff);
EXPORT_SYMBOL(max97000_i2c_receiver_onoff);
EXPORT_SYMBOL(max97000_i2c_headset_onoff);
EXPORT_SYMBOL(max97000_i2c_speaker_headset_onoff);
EXPORT_SYMBOL(max97000_suspend);
EXPORT_SYMBOL(max97000_resume);
EXPORT_SYMBOL(max97000_gpio_recording_start);

module_init(max97000_init);
module_exit(max97000_exit);

MODULE_AUTHOR("");
MODULE_DESCRIPTION("MAX97000 Driver");
MODULE_LICENSE("GPL");
