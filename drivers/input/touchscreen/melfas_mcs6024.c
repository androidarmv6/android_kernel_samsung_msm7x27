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

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/earlysuspend.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <mach/gpio.h>
#include <mach/vreg.h>
#include <linux/synaptics_i2c_rmi.h>
#include <linux/device.h>
#include <linux/i2c/tsp_gpio.h>
#include <linux/jiffies.h>

#define DEBUG_INPUT_REPORT

/* firmware - update */
#include <linux/firmware.h>
/* firmware - update */

#include "melfas_download.h"
#include "melfas_firmware.h"

#define MAX_X  320	//240 
#define MAX_Y  240	//320 

#define I2C_RETRY 3

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
static unsigned int sleep_timestamp=0;

/* firmware - update */
static int firmware_ret_val = -1;
static int tsp_ready = -1;
static int HW_ver = -1;
static int SW_ver = -1;

int firm_update( void );
extern int board_hw_revision;
//CHJ extern int cypress_update( int );
/* firmware - update */

/* sys fs */
struct class *touch_class;
EXPORT_SYMBOL(touch_class);
struct device *firmware_dev;
EXPORT_SYMBOL(firmware_dev);

int read_ver(void);
static ssize_t firmware_show(struct device *dev, struct device_attribute *attr, char *buf);
static ssize_t firmware_store( struct device *dev, struct device_attribute *attr, const char *buf, size_t size);
static ssize_t firmware_ret_show(struct device *dev, struct device_attribute *attr, char *buf);
static ssize_t firmware_ret_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size);
static DEVICE_ATTR(firmware	, 0660, firmware_show, firmware_store);
static DEVICE_ATTR(firmware_ret	, 0660, firmware_ret_show, firmware_ret_store);
/* sys fs */

#ifdef CONFIG_HAS_EARLYSUSPEND
static void synaptics_ts_early_suspend(struct early_suspend *h);
static void synaptics_ts_late_resume(struct early_suspend *h);
#endif

void mcsdl_vdd_on(void)
{ 
	struct vreg *vreg_touch;
	vreg_touch = vreg_get(NULL, "ldo6");
	vreg_set_level(vreg_touch, OUT2800mV);
	vreg_enable(vreg_touch);
	mdelay(25); //MUST wait for 25ms after vreg_enable() 
}

void mcsdl_vdd_off(void)
{
	struct vreg *vreg_touch;
	vreg_touch = vreg_get(NULL, "ldo6");
	vreg_disable(vreg_touch);
	mdelay(100); //MUST wait for 100ms before vreg_enable() 
}

int tsp_reset( void )
{
	int ret=0;
	struct vreg *vreg_touch;
	printk("[TSP] %s+\n", __func__ );

	vreg_touch = vreg_get(NULL, "ldo6");

	if (ts_global->use_irq)
	{
		disable_irq(ts_global->client->irq);
	}

	ret = vreg_disable(vreg_touch);

	msleep(10);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		ret=-EIO;
		goto tsp_reset_out;
	}

	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_set_value( VTOUCH_EN , 0 );	//I2C Pullup

	msleep(10);

	gpio_set_value( TSP_SCL , 0 ); 
	gpio_set_value( TSP_SDA , 0 ); 
	gpio_set_value( TSP_INT , 0 ); 

	msleep(200);

	gpio_set_value( TSP_SCL , 1 ); 
	gpio_set_value( TSP_SDA , 1 ); 
	gpio_set_value( TSP_INT , 1 ); 
	gpio_set_value( VTOUCH_EN , 1 );	//I2C Pullup

	ret = vreg_enable(vreg_touch);

	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		ret=-EIO;
		goto tsp_reset_out;
	}

	msleep(200);

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
	int ret;
	uint8_t start_reg = 0x10;
	uint8_t buf1[6];

	int x=0;
	int y=0;
	int finger=0;
	int width=0;

#ifdef CONFIG_KERNEL_DEBUG_SEC
	static int finger_old=0;
#endif
	struct synaptics_ts_data *ts = container_of(work, struct synaptics_ts_data, work);

	ret = tsp_i2c_read( start_reg, buf1, sizeof(buf1));

	if (ret <= 0) {
		printk("[TSP] i2c failed : ret=%d, ln=%d\n",ret, __LINE__);
		goto work_func_out;
	}

	if( !tsp_ready ){
		tsp_ready++;
		goto work_func_out;
	}

	x = buf1[2] | (uint16_t)(buf1[1] & 0x03) << 8;
	y = buf1[4] | (uint16_t)(buf1[3] & 0x0f) << 8;
	width = buf1[5]/4;
	finger = buf1[0] & 0x01;

	input_report_abs(ts->input_dev, ABS_MT_POSITION_X, x);
	input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, y);	
	input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, finger);
	input_report_abs(ts->input_dev, ABS_MT_WIDTH_MAJOR, width);

	input_mt_sync(ts->input_dev);
	input_sync(ts->input_dev);

#ifdef CONFIG_KERNEL_DEBUG_SEC
	if(finger != finger_old)
		//printk("[TSP] x:%3d, y:%3d, width:%3d, finger=%d\n", x, y, width, finger );

	finger_old = finger;
#endif

work_func_out:
	enable_irq(ts->client->irq); 
}

int tsp_i2c_read(u8 reg, unsigned char *rbuf, int buf_size)
{
	int ret=-1;
	int cnt=0;
	struct i2c_msg rmsg;
	uint8_t start_reg;

	rmsg.addr = ts_global->client->addr;
	rmsg.flags = 0;
	rmsg.len = 1;
	rmsg.buf = &start_reg;
	start_reg = reg;

	for(cnt==0;cnt<I2C_RETRY;cnt++){
		ret = i2c_transfer(ts_global->client->adapter, &rmsg, 1);
		if(ret == 1){
			rmsg.flags = I2C_M_RD;
			rmsg.len = buf_size;
			rmsg.buf = rbuf;
			ret = i2c_transfer(ts_global->client->adapter, &rmsg, 1);

			if(ret == 1)
				break;	
			else
				printk("[TSP] Error ln=%d, ret=%d\n",__LINE__, ret);

		} else {
			printk("[TSP] Error ln=%d, ret=%d\n",__LINE__, ret);
		}
	}

	if (cnt==I2C_RETRY)
		tsp_reset();

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

	printk("[TSP] %s, %d\n", __func__, __LINE__ );

	tsp_ready=0;

	vreg_touch = vreg_get(NULL, "ldo6");
	ret = vreg_set_level(vreg_touch, OUT2800mV);
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

	gpio_tlmm_config(GPIO_CFG( VTOUCH_EN, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);	//I2C Pullup 2.6V 
	gpio_set_value( VTOUCH_EN, 1 );

	msleep(100);

	ts = kzalloc(sizeof(*ts), GFP_KERNEL);
	if (ts == NULL) {
		ret = -ENOMEM;
		goto err_alloc_data_failed;
	}
	INIT_WORK(&ts->work, synaptics_ts_work_func);
	ts->client = client;
	i2c_set_clientdata(client, ts);

	ts_global = ts;

	ts->input_dev = input_allocate_device();
	if (ts->input_dev == NULL) {
		ret = -ENOMEM;
		printk(KERN_ERR "synaptics_ts_probe: Failed to allocate input device\n");
		goto err_input_dev_alloc_failed;
	}
	ts->input_dev->name = "sec_touchscreen";
	set_bit(EV_SYN, ts->input_dev->evbit);
	set_bit(EV_KEY, ts->input_dev->evbit);
	set_bit(BTN_TOUCH, ts->input_dev->keybit);
	set_bit(EV_ABS, ts->input_dev->evbit);

	printk(KERN_INFO "synaptics_ts_probe: max_x: %d, max_y: %d\n", MAX_X, MAX_Y);

	input_set_abs_params(ts->input_dev, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_X, 0, MAX_X, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_Y, 0, MAX_Y, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);

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

#ifdef CONFIG_HAS_EARLYSUSPEND
	ts->early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
//CHJ origin	ts->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	ts->early_suspend.suspend = synaptics_ts_early_suspend;
	ts->early_suspend.resume = synaptics_ts_late_resume;
	register_early_suspend(&ts->early_suspend);
#endif

	printk(KERN_INFO "synaptics_ts_probe: Start touchscreen %s in %s mode\n", ts->input_dev->name, ts->use_irq ? "interrupt" : "polling");

	/* sys fs */
	touch_class = class_create(THIS_MODULE, "touch");
	if (IS_ERR(touch_class))
		pr_err("Failed to create class(touch)!\n");

	firmware_dev = device_create(touch_class, NULL, 0, NULL, "firmware");
	if (IS_ERR(firmware_dev))
		pr_err("Failed to create device(firmware)!\n");

	if (device_create_file(firmware_dev, &dev_attr_firmware) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_firmware.attr.name);
	if (device_create_file(firmware_dev, &dev_attr_firmware_ret) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_firmware_ret.attr.name);
	/* sys fs */

	/* Check point - i2c check - start */
	ret = read_ver();

	if (ret <= 0) {
		printk("[TSP] %s, ln=%d, Error\n", __func__, __LINE__ );
		ret = read_ver();

		if (ret <= 0) 
		{
			printk("[TSP] %s, ln:%d, Failed to register TSP!!!\n\tcheck the i2c line!!!, ret=%d\n", __func__,__LINE__, ret);
			goto err_check_functionality_failed;
		}
	}
	/* Check point - i2c check - end */

#if 0//CHJ
	/* Check point - firmware ver check - start */
	if(board_hw_revision == 0x02){
		if( (HW_ver==0x08)&&(SW_ver<0x11) ){
			printk(KERN_INFO "[TSP] board_rev=%d, TSP HW_ver=%2x, SW_ver=%2x\n", board_hw_revision, HW_ver, SW_ver);
			firm_update();
		}
	}

	if(board_hw_revision == 0x03){
		if( (HW_ver==HEX_HW_VER)&&(SW_ver<HEX_SW_VER) ){
			printk(KERN_INFO "[TSP] board_rev=%d, TSP HW_ver=%2x, SW_ver=%2x\n", board_hw_revision, HW_ver, SW_ver);
			firm_update();
		}
	}
	/* Check point - firmware ver check - end */
#endif

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


	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);

	gpio_set_value( TSP_SCL , 0 ); 
	gpio_set_value( TSP_SDA , 0 ); 
	gpio_set_value( TSP_INT , 0 ); 

	gpio_set_value( VTOUCH_EN , 0 );	//I2C Pullup

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

	sleep_timestamp = jiffies_to_msecs(jiffies);
	printk("[TSP] %s-\n", __func__ );
	return 0;
}

static int synaptics_ts_resume(struct i2c_client *client)
{
	int ret=0;
	struct vreg *vreg_touch;

	printk("[TSP] %s+\n", __func__ );

	while( jiffies_to_msecs(jiffies)-sleep_timestamp < 200 ) {
		printk("[TSP] %d, cnt=%d\n", jiffies_to_msecs(jiffies)-sleep_timestamp, ret );
		msleep(10);	
		ret++;
	}
	
	tsp_ready=0;

	gpio_set_value( TSP_SCL , 1 ); 
	gpio_set_value( TSP_SDA , 1 ); 
	gpio_set_value( TSP_INT , 1 ); 

	gpio_set_value( VTOUCH_EN , 1 );	//I2C Pullup

	vreg_touch = vreg_get(NULL, "ldo6");

	ret = vreg_enable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		return -EIO;
	}

	msleep(30);	
	
	enable_irq(client->irq);
	printk("[TSP] %s-\n", __func__);
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

static int __devinit synaptics_ts_init(void)
{
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

int read_ver(void)
{
	int ret = 0;
	uint8_t i2c_addr = 0x1E;
	uint8_t buf_tmp[3]={0};

	HW_ver = 0;
	SW_ver = 0;

	ret = tsp_i2c_read( i2c_addr, buf_tmp, sizeof(buf_tmp));

	if (ret <= 0) {
		printk("[TSP] %s, ln:%d, Failed to i2c, ret=%d\n", __func__,__LINE__, ret);

		goto read_ver_out;
	}

	HW_ver = buf_tmp[0];
	SW_ver = buf_tmp[2];
	printk("[TSP] %s, ver HW=0x%02x, SW=0x%02x\n", __func__ , HW_ver, SW_ver );

read_ver_out:
	return ret;

}

static ssize_t firmware_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int phone_ver = 0;
	int cnt = 0;

	printk("[TSP] %s ln=%d\n",__func__, __LINE__);

	read_ver();

	while ( cnt < 10 ) {
		if ( HW_ver == firmware_ver[cnt][0] ){
			phone_ver = firmware_ver[cnt][1];
			printk("[TSP] phone_ver=%02x\n", phone_ver );
			break;
		}
	 	cnt++;
	}

	sprintf(buf, "%02X%02X%02X\n", HW_ver, phone_ver, SW_ver );

	return sprintf(buf, "%s", buf );
}

/* firmware - update */
static ssize_t firmware_store(
		struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	char *after;

	unsigned long value = simple_strtoul(buf, &after, 10);	
	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
	firmware_ret_val = -1;

	if ( value == 1 )
	{
		printk("[TSP] Firmware update start!!\n" );

		firm_update( );
	}

	return size;
}

static ssize_t firmware_ret_show(struct device *dev, struct device_attribute *attr, char *buf)
{	
	printk("[TSP] %s!\n", __func__);

	return sprintf(buf, "%d", firmware_ret_val );
}

static ssize_t firmware_ret_store(
		struct device *dev, struct device_attribute *attr,
		const char *buf, size_t size)
{
	printk("[TSP] %s, operate nothing!\n", __func__);

	return size;
}


int firm_update( void )
{
	int ret = 0;
	int cnt = 0;
	struct vreg *vreg_touch;

	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);

	printk("[TSP] disable_irq : %d\n", __LINE__ );

	firmware_ret_val = -1;

	vreg_touch = vreg_get(NULL, "ldo6");

	if (ts_global->use_irq)
	{
		printk("[TSP] disable_irq : %d\n", __LINE__ );
		disable_irq(ts_global->client->irq);
	}

	ret = vreg_disable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
		ret=-EIO;
	}

	printk("[F/W D/L] Entry gpio_tlmm_config\n");

	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);

	gpio_set_value( TSP_SCL , 0 ); 
	gpio_set_value( TSP_SDA , 0 ); 
	gpio_set_value( TSP_INT , 0 ); 

	gpio_set_value( VTOUCH_EN , 0 );	//I2C Pullup

	for (cnt=0; cnt <5 ; cnt++){
		mdelay(200);	
		printk("[F/W D/L] Entry mcsdl_download_binary_data, try=%d\n", cnt );

		ret = mcsdl_download_binary_data( HW_ver );
		mdelay(200);	

		if(ret > 0)
		{
			ret = read_ver();
			if ( ret> 0) {
				firmware_ret_val = 1;
				printk("[TSP] Firmware update success! HW rev 0x%02x., SW rev 0x%02x.]\n", HW_ver, SW_ver);
				break;	
			}
		} else {
			printk("[TSP] Firmware update failed.. RESET!, try=%d\n", cnt);
			mcsdl_vdd_off();
			mdelay(500);
			mcsdl_vdd_on();
			mdelay(200);

			if ( cnt >= 4 ) {
				printk("[TSP] Firmware update failed.. RESET!, try=%d\n", cnt);
				printk("[TSP] check i2c lines.\n");
				firmware_ret_val = 0;
				break;	
			}
		}
	}

	gpio_set_value( TSP_SCL , 1 ); 
	gpio_set_value( TSP_SDA , 1 ); 
	gpio_set_value( TSP_INT , 1 ); 
	gpio_set_value( VTOUCH_EN , 1 );	//I2C Pullup
	
	ret = vreg_enable(vreg_touch);
	if (ret) {
		printk(KERN_ERR "%s: vreg enable failed (%d)\n",
				__func__, ret);
	}

	msleep(10);

	if (ts_global->use_irq)
	{
		enable_irq(ts_global->client->irq);
	}

	return 0;
}
/* firmware - update */

module_init(synaptics_ts_init);
module_exit(synaptics_ts_exit);

MODULE_DESCRIPTION("Synaptics Touchscreen Driver");
MODULE_LICENSE("GPL");
