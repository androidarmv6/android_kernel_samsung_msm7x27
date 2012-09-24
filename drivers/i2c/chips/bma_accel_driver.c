/*  $Date: 2009/11/10 17:37:35 $
 *  $Revision: 1.0 $ 
 */

/*
 * This software program is licensed subject to the GNU General Public License
 * (GPL).Version 2,June 1991, available at http://www.fsf.org/copyleft/gpl.html

 * (C) Copyright 2010 Bosch Sensortec GmbH
 * All Rights Reserved
 */



/*! \file BMA023_driver.c
    \brief This file contains all function implementations for the BMA023 in linux
    
    Details.
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/earlysuspend.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <asm/uaccess.h>
#include <linux/unistd.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/irq.h>
#include <mach/gpio.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/i2c-algo-bit.h>
#include <linux/wakelock.h>
#include <linux/input.h>

#include <linux/i2c/bma222.h>
#include <linux/i2c/bma023_dev.h>
#include <mach/vreg.h>

//#define DEBUG 1
#define CAL 1

//#define BMA_DEBUG

#define ACC_DEV_MAJOR 241
#define BMA222_RETRY_COUNT	3

extern int board_hw_revision;
bma222_t * g_bma222;

enum BMA_SENSORS  
{
	BMA222 = 0,
	BMA023,
};


#define	ACC_ENABLED 1


/* globe variant */
static struct i2c_client *bma_client = NULL;
static char			sensor_type = -1;		
struct class *acc_class;
static int 			calibration = 0 ;
struct bma_data {
	struct work_struct work_acc;
	struct hrtimer timer;
	ktime_t acc_poll_delay;
	u8 state;
	struct mutex power_lock;
	struct workqueue_struct *wq;
	struct early_suspend early_suspend;
	
	union{
		bma222_t			bma222;
		bma023_t			bma023;
	};
};

#ifdef CONFIG_HAS_EARLYSUSPEND
static void bma_early_suspend(struct early_suspend *h);
static void bma_late_resume(struct early_suspend *h);
#endif

static int bma222_fast_calibration(signed char *data);
// this proc file system's path is "/proc/driver/bma020"
// usage :	(at the path) type "cat bma020" , it will show short information for current accelation
// 			use it for simple working test only

//#define BMA222_PROC_FS

#ifdef BMA222_PROC_FS

#include <linux/proc_fs.h>

#define DRIVER_PROC_ENTRY		"driver/bma222"
static void bma_acc_enable(void);

static int bma222_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	char *p = page;
	int len = 0;
	
	mutex_lock(&g_bma222->power_lock);
	printk("bma222_proc_read\n");

	g_bma222->state |= ACC_ENABLED;
	bma_acc_enable();

	mutex_unlock(&g_bma222->power_lock);

	len = (p - page) - off;
	if (len < 0) {
		len = 0;
	}

	printk("bma_proc_read: success full\n");

	*eof = (len <= count) ? 1 : 0;
	*start = page + off;
	return len;
}
#endif	//BMA222_PROC_FS

/*************************************************************************/
/*						BMA220 I2C_API						   */
/*************************************************************************/
/*	i2c delay routine for eeprom	*/
static inline void bma222_i2c_delay(unsigned int msec)
{
	mdelay(msec);
}


/*	i2c write routine for bma	*/
static inline char bma222_i2c_write(unsigned char reg_addr, unsigned char *data, unsigned char len)
{
	uint8_t i;
	unsigned char tmp[2];
	tmp[0] = reg_addr;
	tmp[1] = *data;
	
	struct i2c_msg msg[] = {
		{
			.addr	= bma_client->addr,
			.flags	= 0,
			.len	= 2,
			.buf	= tmp,
		}
	};
	
	for (i = 0; i < BMA222_RETRY_COUNT; i++) {
		if (i2c_transfer(bma_client->adapter, msg, 1) >= 0) {
			break;
		}
		mdelay(10);
	}

	if (i >= BMA222_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, BMA222_RETRY_COUNT);
		return -EIO;
	}
	return 0;
}

/*	i2c read routine for bma220	*/
static inline char bma222_i2c_read(unsigned char reg_addr, unsigned char *data, unsigned char len) 
{
	uint8_t i;

	struct i2c_msg msgs[] = {
		{
			.addr	= bma_client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= &reg_addr,
		},
		{
			.addr	= bma_client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= data,
		}
	};
	
	for (i = 0; i < BMA222_RETRY_COUNT; i++) {
		if (i2c_transfer(bma_client->adapter, msgs, 2) >= 0) {
			break;
		}
		mdelay(10);
	}

	if (i >= BMA222_RETRY_COUNT) {
		pr_err("%s: retry over %d\n", __FUNCTION__, BMA222_RETRY_COUNT);
		return -EIO;
	}
	return 0;	
}


static char i2c_acc_bma023_read(u8 reg, u8 *val, unsigned int len )
{
#if 0
	int 	 err;
	struct 	 i2c_msg msg[1];
	
	unsigned char data[1];
	trace_in() ;
	if( (bma_client == NULL) || (!bma_client->adapter) )
	{
		printk( "ERROR 1\n" ) ;
		return -ENODEV;
	}
	
	msg->addr 	= bma_client->addr;
	msg->flags 	= I2C_M_WR;
	msg->len 	= 1;
	msg->buf 	= data;
	*data       = reg;

	err = i2c_transfer(bma_client->adapter, msg, 1);
	debug( "MGS 2, err= %d\n", err ) ;

	if (err >= 0) 
	{
		msg->flags = I2C_M_RD;
		msg->len   = len;
		msg->buf   = val;
		err = i2c_transfer(bma_client->adapter, msg, 1);
    	debug( "MSG 3, err= %d\n", err ) ;
	}

	if (err >= 0) 
	{
    	debug( "ERROR 4, err= %d\n", err ) ;
		trace_out() ;
		return 0;
	}
	printk("%s %d i2c transfer error\n", __func__, __LINE__);/* add by inter.park */

	trace_out(); 
	return err;
#else
	int dummy=0;
	int i=0;
	if( bma_client == NULL )	/*	No global client pointer?	*/
		return -1;
	while(i<len)
	{		
		dummy = i2c_smbus_read_word_data(bma_client, reg);
		val[i] = dummy & 0x00ff;
		i++;
		reg++;
		dummy = len;
	}
	return 0;
#endif
}

static char i2c_acc_bma023_write( u8 reg, u8 *val )
{
#if 0
	int err;
	struct i2c_msg msg[1];
	unsigned char data[2];
	trace_in() ;


	if( (bma_client == NULL) || (!bma_client->adapter) ){
	    trace_out(); 
	    return -ENODEV;
	}

	data[0] = reg;
	data[1] = *val;

	msg->addr = bma_client->addr;
	msg->flags = I2C_M_WR;
	msg->len = 2;
	msg->buf = data;

	err = i2c_transfer(bma_client->adapter, msg, 1);

	if (err >= 0) trace_out(); 
	return 0;

	printk("%s %d i2c transfer error\n", __func__, __LINE__);/* add by inter.park */
	trace_out(); 
	return err;
#else
	int dummy;
	int i=0;
	unsigned char len = 1;
	if( bma_client == NULL )	/*	No global client pointer?	*/
		return -1;	
	dummy = i2c_smbus_write_byte_data(bma_client, reg, val[0]);

	while(i<len)
	{
		dummy = i2c_smbus_write_byte_data(bma_client, reg, val[0]);
		reg++;
		val++;
		i++;		
		if(dummy<0)
			return -1;	
	}

	return 0;
#endif
}

/*************************************************************************/
/*						BMA023 Sysfs						   */
/*************************************************************************/
//TEST
static ssize_t bma_fs_read(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	bma222acc_t acc;
	bma222_read_accel_xyz(&acc);

       // printk("x: %d,y: %d,z: %d\n", acc.x, acc.y, acc.z);
	count = sprintf(buf,"%d,%d,%d\n", acc.x, acc.y, acc.z );

	return count;
}

static ssize_t bma_fs_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	//buf[size]=0;
	printk("input data --> %s\n", buf);

	return size;
}

static DEVICE_ATTR(acc_file, S_IRUGO | S_IWUSR | S_IWGRP, bma_fs_read, bma_fs_write);

static ssize_t bma_fs_cal(struct device *dev, struct device_attribute *attr, char *buf)
{
	int err, count =0;
	bma222acc_t acc;
	char data[3];
	
#if (defined (CONFIG_MACH_TASS)) || (defined (CONFIG_MACH_TASSDT))
		data[0] = 0; //x
		data[1] = 0; //y
		data[2] = 2; //z ("2" means "-1"-> 0 0 -64)
#else
		data[0] = 0; //x
		data[1] = 0; //y
		data[2] = 1; //z ("1" means "1" -> 0 0 64)
#endif

	bma222_read_accel_xyz(&acc);
	printk("[BMA222] + IOCTL BMA222_CALIBRATION X: %d Y: %d Z: %d \n",acc.x, acc.y, acc.z);
	
	printk("[BMA222] IOCTL BMA222_CALIBRATION data0: %d data1: %d data2: %d \n",data[0], data[1], data[2]);
#if CAL
	err = bma222_fast_calibration(data);
#endif					
	bma222_read_accel_xyz(&acc);
			
	printk("[BMA222] - IOCTL BMA222_CALIBRATION X: %d Y: %d Z: %d \n",acc.x, acc.y, acc.z);

	count = sprintf(buf,"%d\n", err);

	return count;
}
static DEVICE_ATTR(calibrate, S_IRUGO | S_IWUSR | S_IWOTH, bma_fs_cal, NULL);


/*	read command for BMA device file	*/
static ssize_t bma_read(struct file *file, char __user *buf, size_t count, 
loff_t *offset)
{	
	bma222acc_t acc;	
	int ret;
	if( bma_client == NULL )
	{
#ifdef BMA_DEBUG
		printk(KERN_INFO "I2C driver not install\n");
#endif
		return -1;
	}

	bma222_read_accel_xyz(&acc);
//#ifdef BMA_DEBUG
	printk(KERN_INFO "BMA Accel: X/Y/Z axis: %-8d %-8d %-8d\n" ,
		(int)acc.x, (int)acc.y, (int)acc.z);  
//#endif

	if( count != sizeof(acc) )
	{
		return -1;
	}
	ret = copy_to_user(buf,&acc, sizeof(acc));
	if( ret != 0 )
	{
#ifdef BMA_DEBUG
	printk(KERN_INFO "BMA Accel: copy_to_user result: %d\n", ret);
#endif
	}
	return sizeof(acc);
}

/*	write command for BMA Accel device file	*/
static ssize_t bma_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	if( bma_client == NULL )
		return -1;
#ifdef BMA_DEBUG
	printk(KERN_INFO "BMA Accel should be accessed with ioctl command\n");
#endif
	return 0;
}

/*	open command for BMA accel device file	*/
static int bma_open(struct inode *inode, struct file *file)
{
#ifdef BMA_DEBUG
		printk(KERN_INFO "%s\n",__FUNCTION__); 
#endif

	if( bma_client == NULL)
	{
#ifdef BMA_DEBUG
		printk(KERN_INFO "I2C driver not install\n"); 
#endif
		return -1;
	}

#ifdef BMA_DEBUG
	printk(KERN_INFO "BMA Accel has been opened\n");
#endif
	return 0;
}

/*	release command for BMA accel device file	*/
static int bma_close(struct inode *inode, struct file *file)
{
#ifdef BMA_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);	
#endif
	return 0;
}


#if CAL
//static int bma222_fast_calibration(signed char *data);	
/******************************************************************************
*
 * Description: *//**\brief  This API start the fast inline calibration and 
store
 *              offset value into EEPROM
 *
 *
 *  \param       signed char data[0]  --> x axis target offset  
 *                           data[1]  --> y axis target offset
 *                           data[2]  --> z axis target offset
 *                  00b ------ 0g
 *                  01b ------ 1g
 *                  10b ------ -1g
 *                  11b ------ 0g
 * 
******************************************************************************/
static int bma222_fast_calibration(signed char *data)
{
    signed char tmp;
#ifdef DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
    printk(KERN_INFO "data are %d,%d,%d\n",data[0],data[1],data[2]);
    printk(KERN_INFO "start x axis fast calibration\n");
#endif
    bma222_set_offset_target_x(data[0]);
    //bma222_get_offset_target_x(&tmp);
    //printk(KERN_INFO "x offset is %d\n",tmp);
    //bma222_get_offset_filt_x(&tmp);
    //printk(KERN_INFO "x offset filt is %d\n",tmp);
    tmp=1;//selet x axis in cal_trigger
    bma222_set_cal_trigger(tmp);
    do
    {
        mdelay(2);
        bma222_get_cal_ready(&tmp);
#ifdef DEBUG
        printk(KERN_INFO "wait 2ms and got cal ready flag is %d\n",tmp);
#endif  
    }while(tmp==0);
	
#ifdef DEBUG
    bma222_get_offset_filt_x(&tmp);
    printk(KERN_INFO "x offset filt is %d\n",tmp);
    printk(KERN_INFO "x axis fast calibration finished\n");
    printk(KERN_INFO "start y axis fast calibration\n");
#endif

    bma222_set_offset_target_y(data[1]);
    //bma222_get_offset_target_y(&tmp);
    //printk(KERN_INFO "y offset is %d\n",tmp);
    //bma222_get_offset_filt_y(&tmp);
    //printk(KERN_INFO "y offset filt is %d\n",tmp);
    tmp=2;//selet y axis in cal_trigger
    bma222_set_cal_trigger(tmp);
    do
    {
        mdelay(2); 
        bma222_get_cal_ready(&tmp);
#ifdef DEBUG
        printk(KERN_INFO "wait 2ms and got cal ready flag is %d\n",tmp);
#endif  
    }while(tmp==0);
	
#ifdef DEBUG
    bma222_get_offset_filt_y(&tmp);
    printk(KERN_INFO "y offset filt is %d\n",tmp);
    printk(KERN_INFO "y axis fast calibration finished\n");
    printk(KERN_INFO "start z axis fast calibration\n");
#endif
    bma222_set_offset_target_z(data[2]);

    //bma222_get_offset_target_z(&tmp);
    //printk(KERN_INFO "z offset is %d\n",tmp);
    //bma222_get_offset_filt_z(&tmp);
    //printk(KERN_INFO "z offset filt is %d\n",tmp);
    tmp=3;//selet z axis in cal_trigger
    bma222_set_cal_trigger(tmp);
    do
    {
        mdelay(2); 
        bma222_get_cal_ready(&tmp);
#ifdef DEBUG
        printk(KERN_INFO "wait 2ms and got cal ready flag is %d\n",tmp);
#endif  
    }while(tmp==0);
	
#ifdef DEBUG
    bma222_get_offset_filt_z(&tmp);
    printk(KERN_INFO "z offset filt is %d\n",tmp);
    printk(KERN_INFO "z axis fast calibration finished\n");
    printk(KERN_INFO "store xyz offset to eeprom\n");
#endif
    tmp=1;//unlock eeprom
    bma222_set_ee_w(tmp);
    bma222_set_ee_prog_trig();//update eeprom
    do
    {
        mdelay(2); 
        bma222_get_eeprom_writing_status(&tmp);
#ifdef DEBUG
        printk(KERN_INFO "wait 2ms and got eeprom writing status is %d\n",tmp);
#endif  
    }while(tmp==0);
	
    tmp=0;//lock eemprom
    bma222_set_ee_w(tmp);
#ifdef DEBUG
    printk(KERN_INFO "eeprom writing is finished\n");
#endif  
    return 0;
}
#endif


/*	ioctl command for BMA accel device file	*/
static int bma_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	unsigned char data[6];
	unsigned char data_cal[3];
	bma222acc_t acc;

	/* check cmd */
	if(_IOC_TYPE(cmd) != BMA222_IOC_MAGIC)	
	{
#ifdef BMA_DEBUG
		printk("cmd magic type error\n");
#endif
		return -ENOTTY;
	}
	if(_IOC_NR(cmd) > BMA222_IOC_MAXNR)
	{
#ifdef BMA_DEBUG
		printk("cmd number error\n");
#endif
		return -ENOTTY;
	}

	if(_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE,(void __user*)arg, _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void __user*)arg, _IOC_SIZE(cmd));
	
	if(err)
	{
#ifdef BMA_DEBUG
		printk("cmd access_ok error\n");
#endif
		return -EFAULT;
	}
	/* check bam120_client */
	if( bma_client == NULL)
	{
#ifdef BMA_DEBUG
		printk("I2C driver not install\n"); 
#endif
		return -EFAULT;
	}
	
	/* cmd mapping */

	switch(cmd)
	{
	case BMA222_SOFT_RESET:
		err = bma222_soft_reset();
		return err;


	case BMA222_SET_RANGE:
		if(copy_from_user(data,(unsigned char*)arg,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_from_user error\n");
#endif
			return -EFAULT;
		}
		err = bma222_set_range(*data);
		return err;

	case BMA222_GET_RANGE:
		err = bma222_get_range(data);
		if(copy_to_user((unsigned char*)arg,data,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;

	case BMA222_SET_MODE:  // for suspend
		if(copy_from_user(data,(unsigned char*)arg,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_from_user error\n");
#endif
			return -EFAULT;
		}
		err = bma222_set_mode(*data);
		return err;

	case BMA222_GET_MODE:
		err = bma222_get_mode(data);
		if(copy_to_user((unsigned char*)arg,data,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;

	case BMA222_SET_BANDWIDTH:
		if(copy_from_user(data,(unsigned char*)arg,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_from_user error\n");
#endif
			return -EFAULT;
		}
		err = bma222_set_bandwidth(*data);
		return err;

	case BMA222_GET_BANDWIDTH:
		err = bma222_get_bandwidth(data);
		if(copy_to_user((unsigned char*)arg,data,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;

	case BMA222_RESET_INTERRUPT:
		err = bma222_reset_interrupt();
		return err;

	case BMA222_READ_ACCEL_X:
		err = bma222_read_accel_x((short*)data);
		if(copy_to_user((signed char*)arg,(short*)data,1*sizeof(short))!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;

	case BMA222_READ_ACCEL_Y:
		err = bma222_read_accel_y((short*)data);
		if(copy_to_user((signed char*)arg,(short*)data,1*sizeof(short))!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;

	case BMA222_READ_ACCEL_Z:
		err = bma222_read_accel_z((short*)data);
		if(copy_to_user((signed char*)arg,(short*)data,1*sizeof(short))!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;
	case BMA222_READ_ACCEL_XYZ:
		if(sensor_type == BMA222)
		{
			err = bma222_read_accel_xyz((bma222acc_t*)data);
			if(copy_to_user((bma222acc_t*)arg,(bma222acc_t*)data,3*sizeof(short))!=0)
			{
#ifdef BMA_DEBUG
				printk("copy_to error\n");
#endif
				return -EFAULT;
			}
		}else if(sensor_type == BMA023)
		{
			err = bma023_read_accel_xyz((bma023acc_t*)data);
			//printk("[%s] read accel x = %d, y = %d, z = %d\n", __func__, ((bma023acc_t*)data)->x, ((bma023acc_t*)data)->y, ((bma023acc_t*)data)->z);
			if(copy_to_user((bma023acc_t*)arg,(bma023acc_t*)data,3*sizeof(short))!=0)
			{
#ifdef BMA_DEBUG
				printk("copy_to error\n");
#endif
				return -EFAULT;
			}
		}
		
		return err;

	case BMA222_GET_SENSOR_TYPE:		
		printk("[%s] Get Sensor Type = %d\n", __func__, sensor_type);
		if(copy_to_user((char*)arg,&sensor_type,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;

      case BMA222_GET_HWREV:
  		// printk("[%s] Get HW REV = %d\n", __func__, board_hw_revision);
		if(copy_to_user((int*)arg,&board_hw_revision,1)!=0)
		{
#ifdef BMA_DEBUG
			printk("copy_to_user error\n");
#endif
			return -EFAULT;
		}
		return err;         
			
	case BMA222_CALIBRATION:		
		bma222_read_accel_xyz(&acc);
		printk("[BMA222] + IOCTL BMA222_CALIBRATION X: %d Y: %d Z: %d \n",acc.x, acc.y, acc.z);

		if(copy_from_user(data_cal,(unsigned char*)arg,3)!=0)
		{
#ifdef DEBUG
			printk(KERN_INFO "copy_from_user error\n");
#endif			
			return -EFAULT;		
		}	
		printk("[BMA222] IOCTL BMA222_CALIBRATION data0: %d data1: %d data2: %d \n",data_cal[0], data_cal[1], data_cal[2]);
#if CAL
		err = bma222_fast_calibration(data_cal);
#endif					
		bma222_read_accel_xyz(&acc);
			
		printk("[BMA222] - IOCTL BMA222_CALIBRATION X: %d Y: %d Z: %d \n",acc.x, acc.y, acc.z);
		return err;

	default:
		return 0;
	}
}

static const struct file_operations bma_fops = {
	.owner = THIS_MODULE,
	.read = bma_read,
	.write = bma_write,
	.open = bma_open,
	.release = bma_close,
	.ioctl = bma_ioctl,
};

static struct miscdevice bma_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "bma_accel",
	.fops = &bma_fops,
};

static int bma_detect(struct i2c_client *client, int kind,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
#ifdef BMA_DEBUG
	printk(KERN_INFO "%s\n", __FUNCTION__);
#endif
	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		return -ENODEV;

	strlcpy(info->type, "bma", I2C_NAME_SIZE);

	return 0;
}



static void I2c_udelaySet(void)
{
	struct i2c_algo_bit_data *adap = bma_client->adapter->algo_data;
	adap->udelay = 1;
}

static void bma_acc_enable(void)
{
	printk("starting poll timer, delay %lldns\n", ktime_to_ns(g_bma222->acc_poll_delay));
	hrtimer_start(&g_bma222->timer, g_bma222->acc_poll_delay, HRTIMER_MODE_REL);
}

static void bma_acc_disable(void)
{
	printk("cancelling poll timer\n");
	hrtimer_cancel(&g_bma222->timer);
	cancel_work_sync(&g_bma222->work_acc);
}

/////////////////////////////////////////////////////////////////////////////////////

static ssize_t poll_delay_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%lld\n", ktime_to_ns(g_bma222->acc_poll_delay));
}


static ssize_t poll_delay_store(struct device *dev,struct device_attribute *attr, const char *buf, size_t size)
{
	int64_t new_delay;
	int err;

	err = strict_strtoll(buf, 10, &new_delay);
	if (err < 0) return err;
	if (new_delay < 10000000 ) new_delay = 10000000;

	printk("new delay = %lldns, old delay = %lldns\n",
		    new_delay, ktime_to_ns(g_bma222->acc_poll_delay));
	mutex_lock(&g_bma222->power_lock);
	if (new_delay != ktime_to_ns(g_bma222->acc_poll_delay)) {
		bma_acc_disable();
		g_bma222->acc_poll_delay = ns_to_ktime(new_delay);
		if (g_bma222->state & ACC_ENABLED) {
			bma_acc_enable();
		}
	}
	mutex_unlock(&g_bma222->power_lock);

	return size;
}

static ssize_t acc_enable_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", (g_bma222->state & ACC_ENABLED) ? 1 : 0);
}


static ssize_t acc_enable_store(struct device *dev,struct device_attribute *attr, const char *buf, size_t size)
{
	bool new_value;

	if (sysfs_streq(buf, "1"))
		new_value = true;
	else if (sysfs_streq(buf, "0"))
		new_value = false;
	else {
		pr_err("%s: invalid value %d\n", __func__, *buf);
		return -EINVAL;
	}

	mutex_lock(&g_bma222->power_lock);
	printk("new_value = %d, old state = %d\n", new_value, (g_bma222->state & ACC_ENABLED) ? 1 : 0);
	if (new_value && !(g_bma222->state & ACC_ENABLED)) {
		g_bma222->state |= ACC_ENABLED;
		bma_acc_enable();
	} else if (!new_value && (g_bma222->state & ACC_ENABLED)) {
		bma_acc_disable();
		g_bma222->state = 0;
	}
	mutex_unlock(&g_bma222->power_lock);
	return size;
}

static DEVICE_ATTR(poll_delay, S_IRUGO | S_IWUSR | S_IWGRP,
		   poll_delay_show, poll_delay_store);

static struct device_attribute dev_attr_acc_enable =
	__ATTR(enable, S_IRUGO | S_IWUSR | S_IWGRP,
	       acc_enable_show, acc_enable_store);

static struct attribute *acc_sysfs_attrs[] = {
	&dev_attr_acc_enable.attr,
	&dev_attr_poll_delay.attr,
	NULL
};

static struct attribute_group acc_attribute_group = {
	.attrs = acc_sysfs_attrs,
};
///////////////////////////////////////////////////////////////////////////////////

static void bma_work_func_acc(struct work_struct *work)
{
	bma222acc_t acc;
	int err;
		
	err = bma222_read_accel_xyz(&acc);
	
//	printk("##### %d,  %d,  %d\n", acc.x, acc.y, acc.z );

	input_report_rel(g_bma222->acc_input_dev, REL_X, acc.x);
	input_report_rel(g_bma222->acc_input_dev, REL_Y, acc.y);
	input_report_rel(g_bma222->acc_input_dev, REL_Z, acc.z);
	input_sync(g_bma222->acc_input_dev);
}

/* This function is for light sensor.  It operates every a few seconds.
 * It asks for work to be done on a thread because i2c needs a thread
 * context (slow and blocking) and then reschedules the timer to run again.
 */
static enum hrtimer_restart bma_timer_func(struct hrtimer *timer)
{
	queue_work(g_bma222->wq, &g_bma222->work_acc);
	hrtimer_forward_now(&g_bma222->timer, g_bma222->acc_poll_delay);
	return HRTIMER_RESTART;
}

static int bma_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int err = 0;
	int tempvalue;
	struct input_dev *input_dev;
	struct bma_data *data;
      int bma222_i2c_slave_addr = client->addr; // [HSS] Support both address ( 0X18(old) and 0X08(new) ) (2010.09.29)
#ifdef BMA_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
#endif

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
	{
		printk(KERN_INFO "i2c_check_functionality error\n");
		goto exit;
	}
	data = kzalloc(sizeof(struct bma_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}		

	printk("[%s] slave addr = %x\n", __func__, client->addr);
	
	/* read chip id */
	tempvalue = 0;			
#if 1//BMA220_SMBUS
	tempvalue = i2c_smbus_read_word_data(client, 0x00);
	// [HSS] Support both address ( 0X18(old) and 0X08(new) ) (2010.09.29)
      if( tempvalue <0)
      {
         if(bma222_i2c_slave_addr == BMA222_I2C_ADDR)
         {
            client->addr =  bma222_i2c_slave_addr = BMA222_I2C_ADDR_ENG;
            printk(KERN_INFO "[HSS][%s] Slave Address is not matched, so, it will retry i2c transfer with changed slave address!\n", __func__);
		    tempvalue = i2c_smbus_read_word_data(client, 0x00);
         }
      }
#else
	i2c_master_send(client, (char*)&tempvalue, 1);
	i2c_master_recv(client, (char*)&tempvalue, 1);
#endif
	if((tempvalue&0x0007) == 0x0002)
	{
		printk(KERN_INFO "Bosch Sensortec Device detected!\nBMA023 registered I2C driver!\n");
		bma_client = client;
		sensor_type = BMA023;
	}
	else
	{
	// [HSS] Support both address ( 0X18(old) and 0X08(new) ) (2010.09.29)
		//client->addr = BMA222_I2C_ADDR;
		client->addr = bma222_i2c_slave_addr;
		tempvalue = 0;

		tempvalue = i2c_smbus_read_word_data(client, 0x00);
		if((tempvalue&0x00FF) == 0x0003) // BMA220 : 0xdd, BMA222 : 0x03
		{
			printk(KERN_INFO "Bosch Sensortec Device detected!\nBMA220 registered I2C driver!\n");			
			bma_client = client;
			I2c_udelaySet();
			sensor_type= BMA222;
		}
		else
		{		
			printk(KERN_ERR "Bosch Sensortec Device not found, i2c error %d \n", tempvalue);
	//		i2c_detach_client(client);				
			bma_client = NULL;
			err = -1;
			goto kfree_exit;
		}
	}
	
	i2c_set_clientdata(bma_client, data);
	err = misc_register(&bma_device);
	if (err) {
		printk(KERN_ERR "bma accel device register failed\n");
		goto kfree_exit;
	}
	printk(KERN_INFO "bma accel device create ok\n");

	g_bma222 = &data->bma222;
//////////////////////////////////////////////////////////////////////////////
	mutex_init(&g_bma222->power_lock);

	/* hrtimer settings.  we poll for light values using a timer. */
	hrtimer_init(&g_bma222->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	g_bma222->acc_poll_delay = ns_to_ktime(50 * NSEC_PER_MSEC);
	g_bma222->timer.function = bma_timer_func;

	/* the timer just fires off a work queue request.  we need a thread
	   to read the i2c (can be slow and blocking). */
	g_bma222->wq = create_singlethread_workqueue("bma_wq");
	if (!g_bma222->wq) {
		err = -ENOMEM;
		printk("%s: could not create workqueue\n", __func__);
		goto err_create_workqueue;
	}
	/* this is the thread function we run on the work queue */
	INIT_WORK(&g_bma222->work_acc, bma_work_func_acc);

///////////////////////////////////////////////////////////////////////////////////
	/* allocate lightsensor-level input_device */
	input_dev = input_allocate_device();
	if (!input_dev) {
		printk("%s: could not allocate input device\n", __func__);
		err = -ENOMEM;
		goto err_input_allocate_device_light;
	}
	input_set_drvdata(input_dev, g_bma222);
	input_dev->name = "accelerometer_sensor";


	set_bit(EV_REL, input_dev->evbit);	
	/* 32768 == 1g, range -4g ~ +4g */
	/* acceleration x-axis */
	input_set_capability(input_dev, EV_REL, REL_X);
	input_set_abs_params(input_dev, REL_X, -256, 256, 0, 0);
	/* acceleration y-axis */
	input_set_capability(input_dev, EV_REL, REL_Y);
	input_set_abs_params(input_dev, REL_Y, -256, 256, 0, 0);
	/* acceleration z-axis */
	input_set_capability(input_dev, EV_REL, REL_Z);
	input_set_abs_params(input_dev, REL_Z, -256, 256, 0, 0);

	printk("registering lightsensor-level input device\n");
	err = input_register_device(input_dev);
	if (err < 0) {
		printk("%s: could not register input device\n", __func__);
		input_free_device(input_dev);
		goto err_input_register_device_light;
	}
	g_bma222->acc_input_dev = input_dev;


	err = sysfs_create_group(&input_dev->dev.kobj,&acc_attribute_group);
	if (err) {
		printk("Creating bh1721 attribute group failed");
		goto error_device;
	}
//////////////////////////////////////////////////////////////////////////////

	if(sensor_type == BMA222)
	{
		/* bma220 sensor initial */
		data->bma222.bus_write = bma222_i2c_write;
		data->bma222.bus_read = bma222_i2c_read;
		data->bma222.delay_msec = bma222_i2c_delay;	

	// [HSS] Support both address ( 0X18(old) and 0X08(new) ) (2010.09.29)
		bma222_init(&(data->bma222), bma222_i2c_slave_addr);
		bma222_set_bandwidth(4); //bandwidth 250Hz => lowest to reduce noise
		bma222_set_range(0);	//range +/- 2G


	}
	else if(sensor_type == BMA023)
	{
		data->bma023.bma023_bus_write = i2c_acc_bma023_write;
		data->bma023.bma023_bus_read  = i2c_acc_bma023_read;

		/*call init function to set read write functions, read registers */
		bma023_init( &(data->bma023) );

		/* from this point everything is prepared for sensor communication */


		/* set range to 2G mode, other constants: 
		 * 	   			4G: bma023_RANGE_4G, 
		 * 	    		8G: bma023_RANGE_8G */

		bma023_set_range(bma023_RANGE_2G); 

		/* set bandwidth to 25 HZ */
		bma023_set_bandwidth(bma023_BW_25HZ);
	}

#ifdef BMA222_PROC_FS
	create_proc_read_entry(DRIVER_PROC_ENTRY, 0, 0, bma222_proc_read, NULL);
#endif	//BMA222_PROC_FS

#ifdef CONFIG_HAS_EARLYSUSPEND
	data->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	data->early_suspend.suspend = bma_early_suspend;
	data->early_suspend.resume  = bma_late_resume;
	register_early_suspend(&data->early_suspend);
#endif
	return 0;

//	misc_deregister(&bma_device);

error_device:
	sysfs_remove_group(&client->dev.kobj, &acc_attribute_group);
err_input_register_device_light:
	input_unregister_device(g_bma222->acc_input_dev);
err_input_allocate_device_light:	

err_create_workqueue:
	destroy_workqueue(g_bma222->wq);
	mutex_destroy(&data->power_lock);
kfree_exit:
	kfree(data);
exit:
	return err;
}


static int bma_remove(struct i2c_client *client)
{
	struct bma_data *data = i2c_get_clientdata(client);

	if (g_bma222->state & ACC_ENABLED)
	{
		g_bma222->state = 0;
		bma_acc_disable();
	}
	sysfs_remove_group(&g_bma222->acc_input_dev->dev.kobj, &acc_attribute_group);
	input_unregister_device(g_bma222->acc_input_dev);

	destroy_workqueue(g_bma222->wq);
	mutex_destroy(&g_bma222->power_lock);
	
#ifdef BMA_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
#endif	
	misc_deregister(&bma_device);

	//i2c_detach_client(client);
	kfree(data);
	g_bma222 = NULL;
	return 0;
}

static int bma_suspend(struct i2c_client *client, pm_message_t mesg)
{
	int ret = 0;;

	if(sensor_type == BMA222)
	{
		if((ret = bma222_set_mode(2)) != 0)	// 2: suspend mode
			printk(KERN_ERR "[%s] Change to Suspend Mode is failed\n",__FUNCTION__);
		
	}
	else if(sensor_type == BMA023)
	{
		bma023_set_operation_mode( ACCEL, STANDBY, calibration ) ;
	}
	if (g_bma222->state & ACC_ENABLED) 
		bma_acc_disable();

#ifdef BMA_DEBUG
	printk(KERN_INFO "[%s] bma220 !!suspend mode!!\n",__FUNCTION__);
#endif

	return 0;
}

static int bma_resume(struct i2c_client *client)
{
	int ret = 0;

	if(sensor_type == BMA222)
	{
		if((ret = bma222_set_mode(0)) != 0)	// Normal mode
			printk(KERN_ERR "[%s] Change to Normal Mode is failed\n",__FUNCTION__);
	}
	else if(sensor_type == BMA023)
	{
		bma023_set_operation_mode( ACCEL, ONLYACCEL, calibration ) ;
	}

	if (g_bma222->state & ACC_ENABLED)
		bma_acc_enable();

#ifdef BMA_DEBUG
	printk(KERN_INFO "[%s] bma220 !!resume mode!!\n",__FUNCTION__);
#endif

	return 0;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void bma_early_suspend(struct early_suspend *h)
{
	struct bma_data *data;
	data = container_of(h, struct bma_data, early_suspend);
	bma_suspend(&bma_client,PMSG_SUSPEND);
}

static void bma_late_resume(struct early_suspend *h)
{
	struct bma_data *data;
	data = container_of(h, struct bma_data, early_suspend);
	bma_resume(&bma_client);
}
#endif

static unsigned short normal_i2c[] = { I2C_CLIENT_END};
I2C_CLIENT_INSMOD_1(bma_accel);

static const struct i2c_device_id bma_id[] = {
	{ "bma_accel", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, bma_id);

static struct i2c_driver bma_accel_driver = {	
	.driver = {
		.owner	= THIS_MODULE,	
		.name	= "bma_accel",
	},
	//.class		= I2C_CLASS_HWMON,
	.id_table		= bma_id,
	//.address_data	= &addr_data, //3.2 kernel
	.probe		= bma_probe,
	.remove		= bma_remove,
	.detect		= bma_detect,
#ifndef CONFIG_HAS_EARLYSUSPEND
	.suspend	= bma_suspend,
	.resume		= bma_resume,
#endif
};

static int __init BMA_init(void)
{
	struct device *dev_t;

#ifdef BMA_DEBUG
	printk(KERN_ERR "%s\n",__FUNCTION__);
#endif
	acc_class = class_create(THIS_MODULE, "accelerometer");

	if (IS_ERR(acc_class)) 
		return PTR_ERR( acc_class );

	dev_t = device_create( acc_class, NULL, MKDEV(ACC_DEV_MAJOR, 0), "%s", "accelerometer");

	if (device_create_file(dev_t, &dev_attr_acc_file) < 0)
		printk("Failed to create device file(%s)!\n", dev_attr_acc_file.attr.name);
	if (device_create_file(dev_t, &dev_attr_calibrate) < 0)
		printk("Failed to create device file(%s)!\n", dev_attr_calibrate.attr.name);

	if (IS_ERR(dev_t)) 
	{
		return PTR_ERR(dev_t);
	}

	return i2c_add_driver(&bma_accel_driver);
}

static void __exit BMA_exit(void)
{
	i2c_del_driver(&bma_accel_driver);
	printk(KERN_ERR "BMA_ACCEL exit\n");

	class_destroy( acc_class );
}

module_init(BMA_init);
module_exit(BMA_exit);




