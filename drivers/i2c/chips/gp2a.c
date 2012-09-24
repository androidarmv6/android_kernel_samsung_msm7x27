/* 
 *  Title : Optical Sensor(proximity sensor) driver for GP2AP002S00F   
 *  Date  : 2009.02.27
 *  Name  : ms17.kim
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
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
#include <linux/wakelock.h>
#include <mach/vreg.h>

#include "gp2a.h"

/*********** for debug **********************************************************/
#if 1 
#define gprintk(fmt, x... ) printk( "%s(%d): " fmt, __FUNCTION__ ,__LINE__, ## x)
#else
#define gprintk(x...) do { } while (0)
#endif
/*******************************************************************************/


#define GP2A_DEBUG


extern int board_hw_revision;
#define	VIR_LED_EN 	58

/* global var */
static struct i2c_client *opt_i2c_client = NULL;

struct class *proxsensor_class;

struct device *switch_cmd_dev;

static bool proximity_enable = OFF;

static short proximity_value = 0;

static struct wake_lock prx_wake_lock;

static struct vreg *vreg_proximity;

static ktime_t timeA,timeB;
#if USE_INTERRUPT
static ktime_t timeSub;
#endif

/*************************************************************************/
/*		GP2A I2C_API	  				         */
/*************************************************************************/
/*  i2c read routine for gp2a  */
#if USE_INTERRUPT
static int opt_i2c_read(u8 reg, u8 *val, unsigned int len )
{

	int err;
	u8 buf[3];
	//u8 rbuf[3];

	//memset(buf, 0, sizeof(buf));
	
	struct i2c_msg msg[2];


	buf[0] = reg; 

	msg[0].addr = opt_i2c_client->addr;
	msg[0].flags = 1;
	
	msg[0].len = 2;
	msg[0].buf = buf;
	err = i2c_transfer(opt_i2c_client->adapter, msg, 1);
	
	*val = buf[0] << 8 | buf[1];
	
    if (err >= 0) return 0;

    printk("%s %d i2c transfer error\n", __func__, __LINE__);
    return err;
}
#endif

/*  i2c write routine for gp2a */
static int opt_i2c_write( u8 reg, u8 *val )
{
    int err;
    struct i2c_msg msg[1];
    unsigned char data[2];

    if( opt_i2c_client == NULL )
        return -ENODEV;

    data[0] = reg;
    data[1] = *val;

    msg->addr = opt_i2c_client->addr;
    msg->flags = I2C_M_WR;
    msg->len = 2;
    msg->buf = data;

    err = i2c_transfer(opt_i2c_client->adapter, msg, 1);

    if (err >= 0) return 0;

    printk("%s %d i2c transfer error\n", __func__, __LINE__);
    return err;
}


/*************************************************************************/
/*		GP2A sysfs	  				         */
/*************************************************************************/

short gp2a_get_proximity_value()
{
	return ((proximity_value==1)? 0:1);
}

EXPORT_SYMBOL(gp2a_get_proximity_value);


static ssize_t proxsensor_file_state_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
	unsigned int detect = 0;

	gprintk("called %s \n",__func__);

	detect = gpio_get_value(GPIO_SENSE_OUT);	

//	return sprintf(buf,"%u\n",detect);
	return detect;
}

static DEVICE_ATTR(proxsensor_file_state, S_IRUGO, proxsensor_file_state_show, NULL);



/*****************************************************************************************
 *  
 *  function    : gp2a_work_func_prox 
 *  description : This function is for proximity sensor (using B-1 Mode ). 
 *                when INT signal is occured , it gets value from VO register.   
 *
 *                 
 */
#if USE_INTERRUPT
static void gp2a_work_func_prox(struct work_struct *work)
{
	struct gp2a_data *gp2a = container_of(work, struct gp2a_data, work_prox);
	
	unsigned char value;
	unsigned char int_val=REGS_PROX;
	unsigned char vout=0;

	/* Read VO & INT Clear */
	
	gprintk("[PROXIMITY] %s : \n",__func__);

	if(INT_CLEAR)
	{
		//int_val = REGS_PROX | (1 <<7);
	}
	opt_i2c_read((u8)(int_val),&value,1);
	vout = value & 0x01;
	printk(KERN_INFO "[PROXIMITY] value = %d \n",vout);



	/* Report proximity information */
	proximity_value = vout;

	
	if(proximity_value ==0)
	{
		timeB = ktime_get();
		
		timeSub = ktime_sub(timeB,timeA);
		printk(KERN_INFO "[PROXIMITY] timeSub sec = %d, timeSub nsec = %d \n",timeSub.tv.sec,timeSub.tv.nsec);
		
		if (timeSub.tv.sec>=3 )
		{
		    wake_lock_timeout(&prx_wake_lock,HZ/2);
			printk(KERN_INFO "[PROXIMITY] wake_lock_timeout : HZ/2 \n");
		}
		else
			printk(KERN_INFO "[PROXIMITY] wake_lock is already set \n");

	}

	if(USE_INPUT_DEVICE)
	{
		input_report_abs(gp2a->input_dev,ABS_DISTANCE,(int)vout);
		input_sync(gp2a->input_dev);
		mdelay(1);
	}

	/* Write HYS Register */

	if(!vout)
	{
		value = 0x40;


	}
	else
	{
		value = 0x20;

	}
	
	opt_i2c_write((u8)(REGS_HYS),&value);

	/* Forcing vout terminal to go high */

	value = 0x18;
	opt_i2c_write((u8)(REGS_CON),&value);


	/* enable INT */

	enable_irq(gp2a->irq);

	/* enabling VOUT terminal in nomal operation */

	value = 0x00;

	opt_i2c_write((u8)(REGS_CON),&value);

}


static irqreturn_t gp2a_irq_handler(int irq, void *dev_id)
{
	struct gp2a_data *gp2a = dev_id;

	printk("[HSIL] %s\n", __func__);

	if(gp2a->irq !=-1)
	{
		disable_irq_nosync(gp2a->irq);
		gprintk("[PROXIMITY] disable_irq \n");

		queue_work(gp2a_wq, &gp2a->work_prox);

	}
	
	printk("[PROXIMITY] IRQ_HANDLED \n");

	return IRQ_HANDLED;
}

#endif



void gp2a_chip_init(void)
{
	/* set INT 	*/
//	s3c_gpio_cfgpin(GPIO_PS_VOUT, S3C_GPIO_SFN(GPIO_PS_VOUT_AF));
//	s3c_gpio_setpull(GPIO_PS_VOUT, S3C_GPIO_PULL_NONE);

//	set_irq_type(IRQ_GP2A_INT, IRQ_TYPE_EDGE_FALLING);
		
	
}



/*****************************************************************************************
 *  
 *  function    : gp2a_on 
 *  description : This function is power-on function for optical sensor.
 *
 *  int type    : Sensor type. Two values is available (PROXIMITY,LIGHT).
 *                it support power-on function separately.
 *                
 *                 
 */

void gp2a_on(struct gp2a_data *gp2a, int type)
{
	u8 value;
	int err = 0;
	
	gprintk("gp2a_on(%d)\n",type);
	gprintk("gp2a power on voltage up \n");

	if( board_hw_revision < 3 )
	{
		vreg_enable(vreg_proximity); // voltage 
	}
	else
	{
		gpio_set_value(VIR_LED_EN, 1);
	}

	//register irq to wakeup source
	printk("[GP2A] register irq = %d\n",gp2a ->irq);
	err = set_irq_wake(gp2a ->irq, 1);  // enable : 1, disable : 0
	printk("[GP2A] register wakeup source = %d\n",err);
	if (err) 
		printk("[GP2A] register wakeup source failed\n");
	

	// ASD : Select switch for analog sleep function ( 0:ineffective, 1:effective )
	// OCON[1:0] : Select switches for enabling/disabling VOUT terminal 
	//             ( 00:enable, 11:force to go High, 10:forcr to go Low )
	value = 0x18;	// 11:force to go High
	opt_i2c_write((u8)(REGS_CON),&value);

	value = 0x40;	// HYSD enable
	opt_i2c_write((u8)(REGS_HYS),&value);

	// VCON : VOUT terminal output method control ( 0:normal mode, 1:interrupt mode )
	// SSD : Software shutdown function ( 0:shutdown mode, 1:opteration mode )
	value = 0x03;	// VCON enable, SSD enable
	opt_i2c_write((u8)(REGS_OPMOD),&value);

	if(type == PROXIMITY)
	{
		gprintk("enable irq for proximity\n");
		enable_irq(gp2a ->irq);
	}

	// OCON[1:0] : Select switches for enabling/disabling VOUT terminal 
	//             ( 00:enable, 11:force to go High, 10:forcr to go Low )
	value = 0x00;	// 00:enable
	opt_i2c_write((u8)(REGS_CON),&value);
}

/*****************************************************************************************
 *  
 *  function    : gp2a_off 
 *  description : This function is power-off function for optical sensor.
 *
 *  int type    : Sensor type. Three values is available (PROXIMITY,LIGHT,ALL).
 *                it support power-on function separately.
 *                
 *                 
 */

void gp2a_off(struct gp2a_data *gp2a, int type)
{
	u8 value;
	int err = 0;
	
	if( board_hw_revision < 3 )
	{
		vreg_disable(vreg_proximity); // voltage 
	}
	else
	{
		gpio_set_value(VIR_LED_EN, 0);
	}

	gprintk("gp2a_off voltage down(%d)\n",type);

	//delete irq from wakeup source
	printk("[GP2A] unregister irq = %d\n",gp2a ->irq);
	err = set_irq_wake(gp2a ->irq, 0); // enable : 1, disable : 0
	printk("[GP2A] register wakeup source = %d\n",err);
	if (err) 
		printk("[GP2A] register wakeup source failed\n");
	
	
	gprintk("gp2a power off \n");
	if(type == PROXIMITY || type==ALL)
	{
		gprintk("disable irq for proximity \n");
		disable_irq_nosync(gp2a ->irq);
	}
	// SSD : Software shutdown function ( 0:shutdown mode, 1:opteration mode )
	value = 0x02;	// VCON enable, SSD disable
	opt_i2c_write((u8)(REGS_OPMOD),&value);

}


/*************************************************************************/
/*		GP2A file operations  				         */
/*************************************************************************/
static int proximity_open(struct inode *ip, struct file *fp)
{
	return 0;

}

static int proximity_release(struct inode *ip, struct file *fp)
{
	return 0;

}

static long proximity_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	struct gp2a_data *gp2a = dev_get_drvdata(switch_cmd_dev);
	int ret=0;
	switch(cmd) {

		case SHARP_GP2AP_OPEN:
			{
				printk(KERN_INFO "[PROXIMITY] %s : case OPEN\n", __FUNCTION__);
				gp2a_on(gp2a,PROXIMITY);
				proximity_enable =1;
				
			}
			break;

		case SHARP_GP2AP_CLOSE:
			{
				printk(KERN_INFO "[PROXIMITY] %s : case CLOSE\n", __FUNCTION__);
				gp2a_off(gp2a,PROXIMITY);
				proximity_enable=0;
			}
			break;

		default:
			printk(KERN_INFO "[PROXIMITY] unknown ioctl %d\n", cmd);
			ret = -1;
			break;
	}
	return ret;
}



static struct file_operations proximity_fops = {
	.owner  = THIS_MODULE,
	.open   = proximity_open,
    	.release = proximity_release,
    	.unlocked_ioctl = proximity_ioctl,
};
                 
static struct miscdevice proximity_device = {
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = "proximity",
    .fops   = &proximity_fops,
};



//------------------------------------------------------------------------------------

static int gp2a_opt_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int err = 0;
	int i;
#if USE_INTERRUPT
	int irq;
#endif
	int config;

	struct gp2a_data *gp2a;
#ifdef STM_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
#endif

	if( board_hw_revision < 3 )
	{
		vreg_proximity = vreg_get(0, "ldo19");
		if (IS_ERR(vreg_proximity))
		{	
			printk("===== [PROXIMITY] proximity IS_ERR TEST =====\n");
			return PTR_ERR(vreg_proximity);
		}
	
	vreg_set_level(vreg_proximity, 12); // set to 3.0V voltage 
		vreg_enable(vreg_proximity); // voltage 
	}
	else
	{
		gpio_set_value(VIR_LED_EN, 1);
	}
	
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
	{
		printk(KERN_INFO "[GP2A] i2c_check_functionality error\n");
		err = -ENODEV;
		goto exit;
	}
	if ( !i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_BYTE_DATA) ) {
		printk(KERN_INFO "[GP2A] byte op is not permited.\n");
		goto exit;
	}

	/* OK. For now, we presume we have a valid client. We now create the
	client structure, even though we cannot fill it completely yet. */
	if (!(gp2a = kzalloc(sizeof(struct gp2a_data), GFP_KERNEL)))
	{
		err = -ENOMEM;
		goto exit;
	}
	memset(gp2a, 0, sizeof(struct gp2a_data));
	gp2a->client = client;
	i2c_set_clientdata(client, gp2a);

	opt_i2c_client = client;

	if (i2c_smbus_read_byte(client) < 0)
	{
		printk(KERN_ERR "[GP2A] i2c_smbus_read_byte error!!\n");
		goto exit_kfree;
	}
	else
	{
		printk("GP2A Device detected!\n");
	}

	printk("[%s] slave addr = %x\n", __func__, client->addr);
	
	/* Input device Settings */
	if(USE_INPUT_DEVICE)
	{
		gp2a->input_dev = input_allocate_device();
		if (gp2a->input_dev == NULL) 
		{
			pr_err("Failed to allocate input device\n");
			return -ENOMEM;
		}
		gp2a->input_dev->name = "proximity";
	
		set_bit(EV_SYN,gp2a->input_dev->evbit);
		set_bit(EV_ABS,gp2a->input_dev->evbit);
		
 	       input_set_abs_params(gp2a->input_dev, ABS_DISTANCE, 0, 1, 0, 0);
		
	
		err = input_register_device(gp2a->input_dev);
		if (err) 
		{
			pr_err("Unable to register %s input device\n", gp2a->input_dev->name);
			input_free_device(gp2a->input_dev);
			kfree(gp2a);
			return -1;
		}

	}

#if USE_INTERRUPT
	/* WORK QUEUE Settings */
	gp2a_wq = create_singlethread_workqueue("gp2a_wq");
	if (!gp2a_wq)
		return -ENOMEM;
	INIT_WORK(&gp2a->work_prox, gp2a_work_func_prox);
	gprintk("Workqueue Settings complete\n");
#endif

	/* misc device Settings */
	err = misc_register(&proximity_device);
	if(err) {
		pr_err(KERN_ERR "misc_register failed - prox \n");
	}

	/* wake lock init */
	wake_lock_init(&prx_wake_lock, WAKE_LOCK_SUSPEND, "prx_wake_lock");

	/* set sysfs for light sensor */
	proxsensor_class = class_create(THIS_MODULE, "proxsensor");
	if (IS_ERR(proxsensor_class))
		pr_err("Failed to create class(proxsensor)!\n");

	switch_cmd_dev = device_create(proxsensor_class, NULL, 0, NULL, "switch_cmd");	
	if (device_create_file(switch_cmd_dev, &dev_attr_proxsensor_file_state) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_proxsensor_file_state.attr.name);
	
	dev_set_drvdata(switch_cmd_dev,gp2a);
	
	/* ktime init */

	timeA = ktime_set(0,0);
	timeB = ktime_set(0,0);
	
	/* gpio config */
	config = GPIO_CFG(GPIO_SENSE_OUT, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA);
	err = gpio_tlmm_config(config, GPIO_CFG_ENABLE);
	if (err) 
		printk(KERN_ERR "%s: gpio_tlmm_config(%#x)=%d\n", __func__, GPIO_SENSE_OUT, err);

	/* GP2A Regs INIT SETTINGS */
	for(i=1;i<5;i++)
	{
		opt_i2c_write((u8)(i),&gp2a_original_image[i]);
	}

	mdelay(2);
#if USE_INTERRUPT
	/* INT Settings */	
	irq = gpio_to_irq(GPIO_SENSE_OUT);
	gp2a->irq = -1;
	set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);

	err = request_irq(irq, gp2a_irq_handler, IRQF_DISABLED, "gp2a_int", gp2a);
	if (err)
	{
		printk("[GP2A] request_irq failed for gp2a\n");
		goto exit_kfree;
	}

	printk("[GP2A] register irq = %d\n",irq);
	err = set_irq_wake(irq, 1);
	printk("[GP2A] register wakeup source = %d\n",err);
	if (err) 
		printk("[GP2A] register wakeup source failed\n");
	
	gp2a->irq = irq;
	gprintk("INT Settings complete\n");
#endif
	
	// maintain power-down mode before using sensor
	gp2a_off(gp2a,ALL);
	
//++	// test for sensor 

/*
	printk("[GP2A] curr prox value = %d\n", gpio_get_value(GPIO_SENSE_OUT));
	gp2a_on(gp2a,PROXIMITY);
	printk("[GP2A] curr prox value = %d\n", gpio_get_value(GPIO_SENSE_OUT));
	
//--

	// maintain power-down mode before using sensor
	//ESD test sleep
	gp2a_off(gp2a,ALL);
*/

	printk("gp2a_opt_probe is OK!!\n");
	return 0;
	
exit_kfree:
	kfree(gp2a);
exit:
	return err;
}


static int gp2a_opt_remove(struct i2c_client *client)
{
	struct gp2a_data *gp2a = i2c_get_clientdata(client);
#ifdef GP2A_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
#endif	
	if (gp2a_wq)
		destroy_workqueue(gp2a_wq);

	if(USE_INPUT_DEVICE)
		input_unregister_device(gp2a->input_dev);
	kfree(gp2a);

	misc_deregister(&proximity_device);

	return 0;
}

#ifdef CONFIG_PM
static int gp2a_opt_suspend(struct i2c_client *client, pm_message_t mesg)
{
	int config = 0;
	int err = 0;
	
	printk("[HSIL] %s\n", __func__);
	if(!proximity_enable)
	{
		config = GPIO_CFG(VIR_LED_EN, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA);
		err = gpio_tlmm_config(config, GPIO_CFG_ENABLE);
		if (err) 
			printk(KERN_ERR "%s: gpio_tlmm_config(%#x)=%d\n", __func__, VIR_LED_EN, err);
		
		config = GPIO_CFG(GPIO_SENSE_OUT, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA);
		err = gpio_tlmm_config(config, GPIO_CFG_ENABLE);
		if (err) 
			printk(KERN_ERR "%s: gpio_tlmm_config(%#x)=%d\n", __func__, GPIO_SENSE_OUT, err);
	}
	return 0;
}

static int gp2a_opt_resume(struct i2c_client *client)
{
	int config = 0;
	int err = 0;

	printk("[HSIL] %s\n", __func__);
	if(!proximity_enable)
	{
		config = GPIO_CFG(VIR_LED_EN, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA);
		err = gpio_tlmm_config(config, GPIO_CFG_ENABLE);
		if (err) 
			printk(KERN_ERR "%s: gpio_tlmm_config(%#x)=%d\n", __func__, VIR_LED_EN, err);
		
		config = GPIO_CFG(GPIO_SENSE_OUT, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA);
		err = gpio_tlmm_config(config, GPIO_CFG_ENABLE);
		if (err) 
			printk(KERN_ERR "%s: gpio_tlmm_config(%#x)=%d\n", __func__, GPIO_SENSE_OUT, err);
		
		gpio_set_value(VIR_LED_EN, 1);
	}
#if 0
	/* wake_up source handler */
	if(proximity_enable)
	{
		value = 0x18;
		opt_i2c_write((u8)(REGS_CON),&value);

		value = 0x40;
		opt_i2c_write((u8)(REGS_HYS),&value);
		
		
		value = 0x03;
		opt_i2c_write((u8)(REGS_OPMOD),&value);

		enable_irq(gp2a->irq);
		
		value = 0x00;
		opt_i2c_write((u8)(REGS_CON),&value);

	       wake_lock_timeout(&prx_wake_lock,3 * HZ);
		timeA = ktime_get();
		printk("[%s] : wake_lock_timeout 3 Sec \n",__func__);

		/*
		if(!gpio_get_value(GPIO_PS_VOUT))
		{
			gp2a_irq_handler(gp2a->irq,gp2a);
			

		}
		*/
	}
#endif
	return 0;
}
#else
#define gp2a_opt_suspend NULL
#define gp2a_opt_resume NULL
#endif

static unsigned short normal_i2c[] = { I2C_CLIENT_END};
I2C_CLIENT_INSMOD_1(gp2a);

static const struct i2c_device_id gp2a_id[] = {
	{ "gp2a", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, gp2a_id);

static struct i2c_driver gp2a_opt_driver = {	
	.driver = {
		.owner	= THIS_MODULE,	
		.name	= "gp2a",
	},
//	.class		= I2C_CLASS_HWMON,
	.id_table	= gp2a_id,
//	.address_data	= &addr_data,//kerner version 3.2
	.probe		= gp2a_opt_probe,
	.remove		= gp2a_opt_remove,
	.suspend	= gp2a_opt_suspend,
	.resume		= gp2a_opt_resume,
};

static int __init gp2a_opt_init(void)
{

#ifdef GP2A_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
#endif
	return i2c_add_driver(&gp2a_opt_driver);
}

static void __exit gp2a_opt_exit(void)
{
	i2c_del_driver(&gp2a_opt_driver);
#ifdef GP2A_DEBUG
	printk(KERN_INFO "%s\n",__FUNCTION__);
#endif
}

module_init( gp2a_opt_init );
module_exit( gp2a_opt_exit );

MODULE_AUTHOR("SAMSUNG");
MODULE_DESCRIPTION("Optical Sensor driver for gp2ap002s00f");
MODULE_LICENSE("GPL");
