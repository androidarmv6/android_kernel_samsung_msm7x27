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
#include <linux/i2c/tsp_gpio.h>

#define FIRM_TEST 0
#define DEBUG_INPUT_REPORT

/* firmware - update */
#if FIRM_TEST
#include "./CYPRESS_I2C_ISSP/issp_define.h"
#endif

#include <linux/firmware.h>
/* firmware - update */

//++ for dedicated key object on TSP
// Key codes
#define	TOUCH_MENU	KEY_MENU
#define	TOUCH_HOME	KEY_HOME
#define	TOUCH_BACK	KEY_BACK
#define	TOUCH_SEARCH	KEY_SEARCH

#define MAX_KEYS	4

static const int touchkey_keycodes[] = {
			TOUCH_MENU,
			TOUCH_HOME,
			TOUCH_BACK,
			TOUCH_SEARCH,
		};

static int touchkey_size = 4;
//-- for dedicated key object on TSP

#define MAX_X  320	//240 
#define MAX_Y  240	//320 

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

/* firmware - update */
static int firmware_ret_val = -1;
static int HW_ver = -1;
#if FIRM_TEST
unsigned char g_pTouchFirmware[TSP_TOTAL_LINES*TSP_LINE_LENGTH];
unsigned int g_FirmwareImageSize = 0;

static void issp_request_firmware(char* update_file_name);
#endif

int firm_update( void );
extern int cypress_update( int );

#if FIRM_TEST
unsigned char pSocData[]= {
	"fdjkjklijk"
		//#include "./CYPRESS_I2C_ISSP/Europa_ver02_100218" 	
};
#endif
/* firmware - update */

/* sys fs */
struct class *touch_class;
EXPORT_SYMBOL(touch_class);
struct device *firmware_dev;
EXPORT_SYMBOL(firmware_dev);

static ssize_t firmware_show(struct device *dev, struct device_attribute *attr, char *buf);
static ssize_t firmware_store( struct device *dev, struct device_attribute *attr, const char *buf, size_t size);
static ssize_t firmware_ret_show(struct device *dev, struct device_attribute *attr, char *buf);
static ssize_t firmware_ret_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size);
static DEVICE_ATTR(firmware	, S_IRUGO | S_IWUSR | S_IWOTH | S_IXOTH, firmware_show, firmware_store);
static DEVICE_ATTR(firmware_ret	, S_IRUGO | S_IWUSR | S_IWOTH | S_IXOTH, firmware_ret_show, firmware_ret_store);
/* sys fs */

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
	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
#endif

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
//	uint8_t buf[3];
	uint8_t buf[5];
	uint8_t temp;
	
	uint8_t i2c_addr = 0x02;
	uint16_t x=0;
	uint16_t y=0;
	uint16_t z=1;
	int finger = 0;
	static int prev_key = 0;
	static int curr_key = 0;
	static int key_report = 0;
	
#ifdef DEBUG_INPUT_REPORT
	static int prev_finger = 0;
#endif
	struct synaptics_ts_data *ts = container_of(work, struct synaptics_ts_data, work);

	ret = tsp_i2c_read( i2c_addr, buf, sizeof(buf));

	if (ret <= 0) {
		printk("[TSP] i2c failed : ret=%d, ln=%d\n",ret, __LINE__);
		goto work_func_out;
	}

//	x = buf[0];
//	y = buf[1] & 0x0F;
//	y = (y << 8) | (buf[2] );
//	finger = (buf[1] >> 7);

	x = buf[1];	//buf[0];
	y = buf[2];	//buf[0];
	if( buf[0] & 0x40 )
		x += 256;

	finger = buf[0] & 0x01;

	input_report_abs(ts->input_dev, ABS_X, x);
	input_report_abs(ts->input_dev, ABS_Y, y);		
	input_report_abs(ts->input_dev, ABS_PRESSURE, z);
	input_report_key(ts->input_dev, BTN_TOUCH, finger);
	input_sync(ts->input_dev);
	
//	printk("[TSP] buf[0]=%X, buf[1]=%X, buf[2]=%X, buf[3]=%X, buf[4]=%X\n",
//			 buf[0], buf[1], buf[2], buf[3], buf[4] );
//	printk("[TSP] temp=%X, key_report=%X, prev_key=%X\n", temp, key_report, prev_key );

	// Processing Key Btn 
	// 3 : MENU, 5 : HOME, 9 : PREV, 11 : SEARCH
	temp = buf[4];
	if(	temp )
	{
		if( !key_report )
		{
			key_report = 1;
			switch( temp )
			{
				case 0x03 : //MENU
					prev_key = 1;
#ifdef DEBUG_INPUT_REPORT
					printk("[TSP] MENU BTN Clicked!! \n" );
#endif
					input_report_key(ts->input_dev, touchkey_keycodes[prev_key-1], 1);
					break;
				case 0x05 : //HOME
					prev_key = 2;
#ifdef DEBUG_INPUT_REPORT
					printk("[TSP] HOME BTN Clicked!! \n" );
#endif
					input_report_key(ts->input_dev, touchkey_keycodes[prev_key-1], 1);
					break;
				case 0x09 : //PREV
					prev_key = 3;
#ifdef DEBUG_INPUT_REPORT
					printk("[TSP] PREV BTN Clicked!! \n" );
#endif
					input_report_key(ts->input_dev, touchkey_keycodes[prev_key-1], 1);
					break;
				case 0x11 : //SEARCH
					prev_key = 4;
#ifdef DEBUG_INPUT_REPORT
					printk("[TSP] SEARCH BTN Clicked!! \n" );
#endif
					input_report_key(ts->input_dev, touchkey_keycodes[prev_key-1], 1);
					break;
			}
		}
	}
	else if( prev_key )
	{
#ifdef DEBUG_INPUT_REPORT
		switch( prev_key )
		{
			case 1 : //MENU
				printk("[TSP] MENU BTN Released!! \n" );
				break;
			case 2 : //HOME
				printk("[TSP] HOME BTN Released!! \n" );
				break;
			case 3 : //PREV
				printk("[TSP] PREV BTN Released!! \n" );
				break;
			case 4 : //SEARCH
				printk("[TSP] SEARCH BTN Released!! \n" );
				break;
		}
#endif
		input_report_key(ts->input_dev, touchkey_keycodes[prev_key-1], 0);
		prev_key =0;
		key_report = 0;
	}
/*	
	// TSP 칩에서 터치키 눌러질때 터치이벤트도 동시에 올라가서 불필요한 처리가 되게 됨.
	// TSP 펌웨어에서 추가적으로 처리될때까지 임시 루틴을 사용하여 불필요한 터치 이벤트를 올리지 않도록 할 필요가 있음.
//	if( !key_report && !prev_key )
	{
		key_report = 0;
		input_report_abs(ts->input_dev, ABS_X, x);
		input_report_abs(ts->input_dev, ABS_Y, y);		
		input_report_abs(ts->input_dev, ABS_PRESSURE, z);
		input_report_key(ts->input_dev, BTN_TOUCH, finger);
		input_sync(ts->input_dev);
	}
*/

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
	uint8_t i2c_addr = 0x07;
	uint8_t buf[3];
	int key=0;

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
	ts->input_dev->name = "synaptics-rmi-touchscreen";
	set_bit(EV_SYN, ts->input_dev->evbit);
	set_bit(EV_KEY, ts->input_dev->evbit);
	set_bit(BTN_TOUCH, ts->input_dev->keybit);
	set_bit(EV_ABS, ts->input_dev->evbit);

	printk(KERN_INFO "synaptics_ts_probe: max_x: %d, max_y: %d\n", MAX_X, MAX_Y);
	input_set_abs_params(ts->input_dev, ABS_X, 0, MAX_X, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_Y, 0, MAX_Y, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_PRESSURE, 0, 255, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_TOOL_WIDTH, 0, 15, 0, 0);

	// for touch key
	for(key = 0; key < touchkey_size; key++)
		input_set_capability(ts->input_dev, EV_KEY, touchkey_keycodes[key]);

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

	/* Check point - Firmware */
	printk("[TSP] %s, ver CY=%x\n", __func__ , buf[0] );
	printk("[TSP] %s, ver HW=%x\n", __func__ , buf[1] );
	printk("[TSP] %s, ver SW=%x\n", __func__ , buf[2] );

	HW_ver = buf[1];
	printk(KERN_INFO "synaptics_ts_probe: Manufacturer ID: %x, HW ver=%d\n", buf[0], HW_ver);
#if 0
	if ( ( 0x00 < buf[2]) && (buf[2] < 0x04) )
	{
		printk("[TSP] %s, ver SW=%x\n", __func__ , buf[2] );
		printk("[TSP] %s, firm_update was blocked!!\n", __func__ );
		//firm_update( );
	}
#endif	
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
	gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_tlmm_config(GPIO_CFG( TSP_INT, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP,GPIO_CFG_2MA), GPIO_CFG_ENABLE);
#endif

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

static ssize_t firmware_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	uint8_t i2c_addr = 0x06;
	uint8_t buf_tmp[2] = {0};
	int phone_ver = 0;

	printk("[TSP] %s\n",__func__);


	if ( HW_ver == 1 )
	{
		/* for glass */
		phone_ver = 1;  /* SW Ver.4 - change this value if New firmware be released */ 	
	}
	else if( HW_ver == 2 )
	{
		/* for acryl */
		phone_ver = 1;  /* SW Ver.4 - change this value if New firmware be released */ 	
	}
	else
	{
		printk("[TSP] %s:%d,HW_ver is wrong!!\n", __func__,__LINE__ );
	}

	tsp_i2c_read( i2c_addr, buf_tmp, sizeof(buf_tmp));
	printk("[TSP] %s:%d, phone_ver=%d, ver SW=%x, HW=%x\n", __func__,__LINE__, phone_ver, buf_tmp[1], buf_tmp[0] );

	/* below protocol is defined with App. ( juhwan.jeong@samsung.com )
	   The TSP Driver report like XY as decimal.
	   The X is the Firmware version what phone has.
	   The Y is the Firmware version what TSP has. */

	sprintf(buf, "%d,%d\n", phone_ver, buf_tmp[1] );

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
#if FIRM_TEST
		printk("[TSP] start update cypress touch firmware !!\n");
		g_FirmwareImageSize = CYPRESS_FIRMWARE_IMAGE_SIZE;

		if(g_pTouchFirmware == NULL)
		{
			printk("[TSP][ERROR] %s() kmalloc fail !! \n", __FUNCTION__);
			return -1;
		}


		/* ready for firmware code */
		size = issp_request_firmware("touch.hex");

		/* firmware update */
		//	issp_upgrade();

		g_FirmwareImageSize = 0;

		// step.1 power off/on

		// step.2 enable irq


#endif
		return size;
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
	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);

	printk("[TSP] disable_irq : %d\n", __LINE__ );
	disable_irq(ts_global->client->irq);

	// TEST
	//gpio_configure( TSP_SCL, GPIOF_DRIVE_OUTPUT );

	if( HW_ver==1 || HW_ver==2 )
		firmware_ret_val = cypress_update( HW_ver );
	else	
	{
		printk(KERN_INFO "[TSP] %s, %d cypress_update blocked, HW ver=%d\n", __func__, __LINE__, HW_ver);
		firmware_ret_val = 0; // Fail
	}

	if( firmware_ret_val )
		printk(KERN_INFO "[TSP] %s success, %d\n", __func__, __LINE__);
	else	
		printk(KERN_INFO "[TSP] %s fail, %d\n", __func__, __LINE__);

	//gpio_configure( TSP_SCL, GPIOF_DRIVE_OUTPUT );

	printk("[TSP] enable_irq : %d\n", __LINE__ );
	enable_irq(ts_global->client->irq);

	return 0;
} 

#if FIRM_TEST
static void issp_request_firmware(char* update_file_name)
{
	int idx_src = 0;
	int idx_dst = 0;
	int line_no = 0;
	int dummy_no = 0;
	char buf[2];
	int ret = 0;

	struct device *dev = &ts_global->input_dev->dev;	
	const struct firmware * fw_entry;

	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
	printk("[TSP] firmware file name : %s\n", update_file_name);

	ret = request_firmware(&fw_entry, update_file_name, dev);
	if ( ret )
	{
		printk("[TSP] request_firmware fail, ln=%d\n", ret );
		return ;
	}
	else
	{
		printk("[TSP] request_firmware success, ln=%d\n", ret );
		printk("[TSP][DEBUG] ret=%d, firmware size=%d\n", ret, fw_entry->size);
		printk("[TSP] %c %c %c %c %c\n", fw_entry->data[0], fw_entry->data[1], fw_entry->data[2], fw_entry->data[3], fw_entry->data[4]);
	}

	do {
		if(fw_entry->data[idx_src] == ':') // remove prefix
		{
			idx_src+=9;
			dummy_no++;

			if(dummy_no != line_no+1)
			{
				printk("[ERROR] Can not skip semicolon !! line_no(%d), dummy_no(%d)\n", line_no, dummy_no);
			}
		}
		else if(fw_entry->data[idx_src] == '\r') // return code
		{
			idx_src+=2; idx_dst--; line_no++;

			if( idx_dst > TSP_LINE_LENGTH*line_no)
			{
				printk("[ERROR] length buffer over error !! line_no(%d), idx_dst(%d)\n", line_no, idx_dst);
			}
		}
		else if(fw_entry->data[idx_src] == 0x0a) // return code
		{
			idx_src+=1; idx_dst--; line_no++;

			if( idx_dst > TSP_LINE_LENGTH*line_no)
			{
				printk("[ERROR] length buffer over error !! line_no(%d), idx_dst(%d)\n", line_no, idx_dst);
			}
		}
		else
		{
			sprintf(buf, "%c%c", fw_entry->data[idx_src], fw_entry->data[idx_src+1]);
			if(idx_dst > TSP_TOTAL_LINES*TSP_LINE_LENGTH)
			{
				printk("[ERROR] buffer over error !!  line_no(%d), idx_dst(%d)\n", line_no, idx_dst);
			}
			g_pTouchFirmware[idx_dst] = simple_strtol(buf, NULL, 16);
			idx_src+=2; idx_dst++;
		}
	} while ( line_no < TSP_TOTAL_LINES );

	release_firmware(fw_entry);
}
#endif

/* firmware - update */

module_init(synaptics_ts_init);
module_exit(synaptics_ts_exit);

MODULE_DESCRIPTION("Synaptics Touchscreen Driver");
MODULE_LICENSE("GPL");
