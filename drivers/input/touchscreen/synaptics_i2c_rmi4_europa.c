/* drivers/input/keyboard/synaptics_i2c_rmi.c
 *
 * Copyright (C) 2007 Google, Inc.
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

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/earlysuspend.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <mach/gpio.h>
#include <mach/vreg.h>
#include <linux/synaptics_i2c_rmi.h>
#include <linux/device.h>
#include <linux/i2c/europa_tsp_gpio.h>

//#define DEBUG_INPUT_REPORT

#define MAX_X  240 
#define MAX_Y 320 

static uint16_t dualx = 120;
static uint16_t dualy = 160;
static int dtouchs = 0;
static int dt_ativar = 0;
static int gm_ativar = 0;
static int send_msg = 1;

static struct workqueue_struct *synaptics_wq;

struct synaptics_ts_data {
	uint16_t addr;
	struct i2c_client *client;
	struct input_dev *input_dev;
	int use_irq;
	//	struct hrtimer timer;
	struct work_struct  work;
	//	struct work_struct  work_timer;
	struct early_suspend early_suspend;
};

struct synaptics_ts_data *ts_global;
int tsp_i2c_read(u8 reg, unsigned char *rbuf, int buf_size);

/* sys fs */
static int fakedt = 0;
static ssize_t fakedt_show(struct device *dev, struct device_attribute *attr, char *buf);
static ssize_t fakedt_store( struct device *dev, struct device_attribute *attr, const char *buf, size_t size);
static DEVICE_ATTR(fakedt	, S_IRUGO | S_IWUSR | S_IWOTH | S_IXOTH, fakedt_show, fakedt_store);

struct class *touch_class;
EXPORT_SYMBOL(touch_class);
struct device *synaptics_dev;
EXPORT_SYMBOL(synaptics_dev);

#ifdef CONFIG_HAS_EARLYSUSPEND
static void synaptics_ts_early_suspend(struct early_suspend *h);
static void synaptics_ts_late_resume(struct early_suspend *h);
#endif

int tsp_reset( void )
{
	int ret=1;
#if 0	
	uint8_t i2c_addr = 0x07;
	uint8_t buf[1];
#endif
	struct vreg *vreg_touch;
	printk("[TSP] %s+\n", __func__ );

	vreg_touch = vreg_get(NULL, "ldo6");

	if (ts_global->use_irq)
	{
		disable_irq(ts_global->client->irq);
	}

	ret = vreg_disable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		ret=-EIO;
		goto tsp_reset_out;
	}

#if 0
	gpio_configure( TSP_SCL, GPIO_CFG_OUTPUT );
	gpio_configure( TSP_SDA, GPIO_CFG_OUTPUT );
	gpio_configure( TSP_INT, GPIO_CFG_INPUT );
#endif
	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);

	gpio_set_value( TSP_SCL , 0 ); 
	gpio_set_value( TSP_SDA , 0 ); 
	gpio_set_value( TSP_INT , 0 ); 

	msleep( 5 );

	gpio_set_value( TSP_SCL , 1 ); 
	gpio_set_value( TSP_SDA , 1 ); 
	gpio_set_value( TSP_INT , 1 ); 

	ret = vreg_enable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		ret=-EIO;
		goto tsp_reset_out;
	}

	msleep(10);
#if 0
	while (ts_global->use_irq)
	{
		msleep(10);

		ret = tsp_i2c_read( i2c_addr, buf, sizeof(buf));
		if (ret <= 0) {
			printk("[TSP] %d : i2c_transfer failed\n", __LINE__);
		}
		else
		{
			printk("[TSP] %s:%d, ver SW=%x\n", __func__,__LINE__, buf[0] );
			ret=1;
			break;
		}
	}
#endif

tsp_reset_out:
	if (ts_global->use_irq)
	{
		enable_irq(ts_global->client->irq);
	}
	printk("[TSP] %s-\n", __func__ );

	return ret;
}

static void synaptics_ts_work_func(struct work_struct *work)
{
	int ret=0;
	uint8_t buf[3];
	uint8_t i2c_addr = 0x02;
	uint16_t x=0;
	uint16_t y=0;
	uint16_t z=1;
	int finger = 0;
	
#ifdef DEBUG_INPUT_REPORT
	static int prev_finger = 0;
#endif
	struct synaptics_ts_data *ts = container_of(work, struct synaptics_ts_data, work);

	ret = tsp_i2c_read( i2c_addr, buf, sizeof(buf));
	
	if (ret <= 0) {
		printk("[TSP] i2c failed : ret=%d, ln=%d\n",ret, __LINE__);
		goto work_func_out;
	}

	x = buf[0];

	y = buf[1] & 0x0F;
	y = (y << 8) | (buf[2] );
	finger = (buf[1] >> 7);
	
	if (dtouchs<2){
	if (finger==1 && fakedt) {   // DT mode
		if (dt_ativar==0) {
			if (x>120 && y<160){
				dt_ativar=1;
			}
		}
		if (dt_ativar==1) {
			if (x>=120 && y<160){
				dt_ativar=1;
			}
			else if (x<120 && y<160){
				dt_ativar=2;
			}
			else {
				dt_ativar=0;
			}
		}
		if (dt_ativar==2) {
			if (x<120 && y<160){
				dt_ativar=2;
			}
			else if (x<120 && y>=160){
				dt_ativar=3;
			}
			else {
				dt_ativar=0;
			}
		}
		if (dt_ativar==3) {
			if (x<120 && y>=160){
				dt_ativar=3;
			}
			else if (x>=120 && y>=160){
				dt_ativar=4;
			}
			else {
				dt_ativar=0;
			}
		}
		if (dt_ativar==4) {
			if (x>=120 && y>=160){
				dt_ativar=4;
			}
			else if (x>=120 && y<160){
				dt_ativar=5;
				dtouchs=2;
				dualx=120;
				dualy=160;
			}
			else {
				dt_ativar=0;
			}
		}
	}
	if (finger==1 && fakedt) {  //GM mode
		if (gm_ativar==0) {
			if (x>120 && y<160){
				gm_ativar=1;
			}
		}
		if (gm_ativar==1) {
			if (x>=120 && y<160){
				gm_ativar=1;
			}
			else if (x>=120 && y>=160){
				gm_ativar=2;
			}
			else {
				gm_ativar=0;
			}
		}
		if (gm_ativar==2) {
			if (x>=120 && y>=160){
				gm_ativar=2;
			}
			else if (x<120 && y>=160){
				gm_ativar=3;
			}
			else {
				gm_ativar=0;
			}
		}
		if (gm_ativar==3) {
			if (x<120 && y>=160){
				gm_ativar=3;
			}
			else if (x<120 && y<160){
				gm_ativar=4;
			}
			else {
				gm_ativar=0;
			}
		}
		if (gm_ativar==4) {
			if (x<120 && y<160){
				gm_ativar=4;
			}
			else if (x>=120 && y<160){
				gm_ativar=5;
				dtouchs=1;
				send_msg=1;
			}
			else {
				gm_ativar=0;
			}
		}
	}}
	
	if (send_msg==1) {
	if (dtouchs<2) {
	  input_report_abs(ts->input_dev, ABS_MT_POSITION_X, x);
	  input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, y);
	  input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, finger);
	  input_report_abs(ts->input_dev, ABS_MT_WIDTH_MAJOR, z*10);
	  input_mt_sync(ts->input_dev);
	  }
	else if (dtouchs==2) {
	  input_report_abs(ts->input_dev, ABS_MT_POSITION_X, dualx);
	  input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, dualy);
	  input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, finger);
	  input_report_abs(ts->input_dev, ABS_MT_WIDTH_MAJOR, 10);
	  input_mt_sync(ts->input_dev);
	  input_report_abs(ts->input_dev, ABS_MT_POSITION_X, x);
	  input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, y);
	  input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, finger);
	  input_report_abs(ts->input_dev, ABS_MT_WIDTH_MAJOR, z*10);
	  input_mt_sync(ts->input_dev);
	}  
	if (finger==0) {
		if (gm_ativar==5){
			dualx=x;
			dualy=y;
			gm_ativar=0;
			dtouchs=2;
		}
		else {
			dtouchs=0;
			dt_ativar=0;
			gm_ativar=0;
		}
		send_msg=1;
		
	}
	input_sync(ts->input_dev);
	}
	

#ifdef DEBUG_INPUT_REPORT
	if ( finger ^ prev_finger )
	{
		printk("[TSP] x=%d, y=%d\n", x, y );
		prev_finger = finger;
	}
#endif

work_func_out:
	if (ts->use_irq)
	{
		enable_irq(ts->client->irq);
	}
}

int tsp_i2c_read(u8 reg, unsigned char *rbuf, int buf_size)
{
	int ret=-1;
	struct i2c_msg rmsg;
	uint8_t start_reg;

	rmsg.addr = ts_global->client->addr;
	rmsg.flags = 0;//I2C_M_WR;
	rmsg.len = 1;
	rmsg.buf = &start_reg;
	start_reg = reg;
	ret = i2c_transfer(ts_global->client->adapter, &rmsg, 1);

	if(ret>=0) {
		rmsg.flags = I2C_M_RD;
		rmsg.len = buf_size;
		rmsg.buf = rbuf;
		ret = i2c_transfer(ts_global->client->adapter, &rmsg, 1 );
	}

	if( ret < 0 )
	{
		printk("[TSP] Error code : %d\n", __LINE__ );
		printk("[TSP] reset ret=%d\n", tsp_reset( ) );
	}

	return ret;
}

static irqreturn_t synaptics_ts_irq_handler(int irq, void *dev_id)
{
	struct synaptics_ts_data *ts = dev_id;

	disable_irq_nosync(ts->client->irq);
	queue_work(synaptics_wq, &ts->work);
	return IRQ_HANDLED;
}

static int synaptics_ts_probe(
		struct i2c_client *client, const struct i2c_device_id *id)
{
	struct synaptics_ts_data *ts;
	int ret = 0;
	struct vreg *vreg_touch;
	uint8_t i2c_addr = 0x05;
	uint8_t buf[3];

	printk("[TSP] %s, %d\n", __func__, __LINE__ );

	vreg_touch = vreg_get(NULL, "ldo6");
	ret = vreg_set_level(vreg_touch, OUT2600mV);
	if (ret) {
		printk(KERN_ERR "%s: vreg set level failed (%d)\n",
				__func__, ret);
		return -EIO;
	}

	ret = vreg_enable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		return -EIO;
	}

	msleep(100);

	ts = kzalloc(sizeof(*ts), GFP_KERNEL);
	if (ts == NULL) {
		ret = -ENOMEM;
		goto err_alloc_data_failed;
	}
	INIT_WORK(&ts->work, synaptics_ts_work_func);
	//	INIT_WORK(&ts->work_timer, report_touch );
	ts->client = client;
	i2c_set_clientdata(client, ts);

	ts_global = ts;

	/* Check point - i2c check - start */
	ret = tsp_i2c_read( i2c_addr, buf, sizeof(buf));

	if (ret <= 0) {
		printk(KERN_ERR "i2c_transfer failed\n");
		ret = tsp_i2c_read( i2c_addr, buf, sizeof(buf));

		if (ret <= 0) 
		{
			printk("[TSP] %s, ln:%d, Failed to register TSP!!!\n\tcheck the i2c line!!!, ret=%d\n", __func__,__LINE__, ret);
			goto err_check_functionality_failed;
		}
	}
	/* Check point - i2c check - end */

	ts->input_dev = input_allocate_device();
	if (ts->input_dev == NULL) {
		ret = -ENOMEM;
		printk(KERN_ERR "synaptics_ts_probe: Failed to allocate input device\n");
		goto err_input_dev_alloc_failed;
	}
	ts->input_dev->name = "sec_touchscreen";
	set_bit(EV_ABS, ts->input_dev->evbit);

	printk(KERN_INFO "synaptics_ts_probe: max_x: 240, max_y: 320\n");
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_X, -1, MAX_X+1, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_Y, -1, MAX_Y+1, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);

	/* ts->input_dev->name = ts->keypad_info->name; */
	ret = input_register_device(ts->input_dev);
	if (ret) {
		printk(KERN_ERR "synaptics_ts_probe: Unable to register %s input device\n", ts->input_dev->name);
		goto err_input_register_device_failed;
	}
	printk("[TSP] %s, irq=%d\n", __func__, client->irq );
	if (client->irq) {
		ret = request_irq(client->irq, synaptics_ts_irq_handler,/* IRQF_TRIGGER_RISING |*/ IRQF_TRIGGER_FALLING , client->name, ts);
		if (ret == 0) 
			ts->use_irq = 1;
		else
			dev_err(&client->dev, "request_irq failed\n");
	}

	//	hrtimer_init(&ts->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	//	ts->timer.function = synaptics_ts_timer_func;

#ifdef CONFIG_HAS_EARLYSUSPEND
	ts->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	ts->early_suspend.suspend = synaptics_ts_early_suspend;
	ts->early_suspend.resume = synaptics_ts_late_resume;
	register_early_suspend(&ts->early_suspend);
#endif

	printk(KERN_INFO "synaptics_ts_probe: Start touchscreen %s in %s mode\n", ts->input_dev->name, ts->use_irq ? "interrupt" : "polling");

	/* sys fs */
	touch_class = class_create(THIS_MODULE, "touch");
	if (IS_ERR(touch_class)) pr_err("Failed to create class(touch)!\n");
	synaptics_dev = device_create(touch_class, NULL, 0, NULL, "synaptics");
	if (device_create_file(synaptics_dev, &dev_attr_fakedt) < 0) pr_err("Failed to create device file(%s)!\n", dev_attr_fakedt.attr.name);
	
	/* Check point - Firmware */
	printk("[TSP] %s, ver CY=%x\n", __func__ , buf[0] );
	printk("[TSP] %s, ver HW=%x\n", __func__ , buf[1] );
	printk("[TSP] %s, ver SW=%x\n", __func__ , buf[2] );
	/* Check point - Firmware */

	return 0;

err_input_register_device_failed:
	input_free_device(ts->input_dev);

err_input_dev_alloc_failed:
	kfree(ts);
err_alloc_data_failed:
err_check_functionality_failed:
	return ret;
}

static int synaptics_ts_remove(struct i2c_client *client)
{
	struct synaptics_ts_data *ts = i2c_get_clientdata(client);
	unregister_early_suspend(&ts->early_suspend);
	if (ts->use_irq)
		free_irq(client->irq, ts);
	//	else
	//		hrtimer_cancel(&ts->timer);
	input_unregister_device(ts->input_dev);
	kfree(ts);
	return 0;
}

static int synaptics_ts_suspend(struct i2c_client *client, pm_message_t mesg)
{
	int ret;
	struct synaptics_ts_data *ts = i2c_get_clientdata(client);
	struct vreg *vreg_touch;
	printk("[TSP] %s+\n", __func__ );

	vreg_touch = vreg_get(NULL, "ldo6");

	if (ts->use_irq)
	{
		disable_irq(client->irq);
	}
#if 0
	gpio_configure( TSP_SCL, GPIO_CFG_OUTPUT );
	gpio_configure( TSP_SDA, GPIO_CFG_OUTPUT );
	gpio_configure( TSP_INT, GPIO_CFG_INPUT );
#endif
	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);

	gpio_set_value( TSP_SCL , 0 ); 
	gpio_set_value( TSP_SDA , 0 ); 
	gpio_set_value( TSP_INT , 0 ); 

	ret = cancel_work_sync(&ts->work);
	if (ret && ts->use_irq) /* if work was pending disable-count is now 2 */
	{
		enable_irq(client->irq);
	}

	msleep(20);

	ret = vreg_disable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		return -EIO;
	}

	printk("[TSP] %s-\n", __func__ );
	return 0;
}

static int synaptics_ts_resume(struct i2c_client *client)
{
	int ret;
	struct vreg *vreg_touch;
	struct synaptics_ts_data *ts = i2c_get_clientdata(client);
	uint8_t i2c_addr = 0x07;
	uint8_t buf[1];

	printk("[TSP] %s+\n", __func__ );

	gpio_set_value( TSP_SCL , 1 ); 
	gpio_set_value( TSP_SDA , 1 ); 
	gpio_set_value( TSP_INT , 1 ); 

	vreg_touch = vreg_get(NULL, "ldo6");

	ret = vreg_enable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		return -EIO;
	}

	msleep(100);

	while (ts->use_irq)
	{
		msleep(10);

		ret = tsp_i2c_read( i2c_addr, buf, sizeof(buf));
		if (ret <= 0) {
			printk("[TSP] %d : i2c_transfer failed\n", __LINE__);
		}
		else if	( buf[0] == 0 )
		{
			printk("[TSP] %s:%d, ver SW=%x\n", __func__,__LINE__, buf[0] );
		}
		else
		{
			printk("[TSP] %s:%d, ver SW=%x\n", __func__,__LINE__, buf[0] );
			enable_irq(client->irq);
			break;
		}
	}

	printk("[TSP] %s-\n", __func__ );
	return 0;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void synaptics_ts_early_suspend(struct early_suspend *h)
{
	struct synaptics_ts_data *ts;
	ts = container_of(h, struct synaptics_ts_data, early_suspend);
	synaptics_ts_suspend(ts->client, PMSG_SUSPEND);
}

static void synaptics_ts_late_resume(struct early_suspend *h)
{
	struct synaptics_ts_data *ts;
	ts = container_of(h, struct synaptics_ts_data, early_suspend);
	synaptics_ts_resume(ts->client);
}
#endif

static const struct i2c_device_id synaptics_ts_id[] = {
	{ "synaptics-rmi-ts", 1 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, synaptics_ts_id);

static struct i2c_driver synaptics_ts_driver = {
	.probe		= synaptics_ts_probe,
	.remove		= synaptics_ts_remove,
#ifndef CONFIG_HAS_EARLYSUSPEND
	.suspend	= synaptics_ts_suspend,
	.resume		= synaptics_ts_resume,
#endif
	.id_table	= synaptics_ts_id,
	.driver = {
		.name	= "synaptics-rmi-ts",
	},
};

// this funtion is garbage funtion for battery driver
int set_tsp_for_ta_detect(int state)
{
	return 1;
}
EXPORT_SYMBOL(set_tsp_for_ta_detect);

static int __devinit synaptics_ts_init(void)
{
	
	struct i2c_driver * otherDriver;
	struct device_driver * other;
	
	other = driver_find(SYNAPTICS_I2C_RMI_NAME, &i2c_bus_type);
	
	if (other)
	{
//		printk(KERN_ERR "Previous driver found: %s\n", other->name);
		put_driver(other);
		otherDriver = to_i2c_driver(other);
		printk(KERN_ERR "Previous driver found: %s, addr 0x%x, owner %x\n", other->name, (int)otherDriver, (int)other->owner);
		//driver_unregister(other);
		i2c_del_driver(otherDriver);
		if (synaptics_wq)
			destroy_workqueue(synaptics_wq);
		printk(KERN_ERR "Prev driver removed\n");
	}
	
	printk("[TSP] %s\n", __func__ );
	synaptics_wq = create_singlethread_workqueue("synaptics_wq");
	if (!synaptics_wq)
		return -ENOMEM;
	return i2c_add_driver(&synaptics_ts_driver);
}

static void __exit synaptics_ts_exit(void)
{
	i2c_del_driver(&synaptics_ts_driver);
	if (synaptics_wq)
		destroy_workqueue(synaptics_wq);
}

static ssize_t fakedt_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int n;
	n=sprintf(buf, "%d", fakedt);
        return n + 1;
}

static ssize_t fakedt_store(
		struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	char *after;
	unsigned long value = simple_strtoul(buf, &after, 10);
	if (value) fakedt = 1;
	else fakedt = 0;
	return size;
}

module_init(synaptics_ts_init);
module_exit(synaptics_ts_exit);

MODULE_DESCRIPTION("Synaptics Touchscreen Driver");
MODULE_LICENSE("GPL");
