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
#include <linux/delay.h>
#include <linux/input.h>

#include <mach/vreg.h>
#include <asm/io.h>

#include <linux/uaccess.h>

static struct i2c_client *pclient;

struct fsa9280_data {
	struct work_struct work;
};

static DECLARE_WAIT_QUEUE_HEAD(g_data_ready_wait_queue);

int fsa9280_i2c_write(unsigned char u_addr, unsigned char u_data);
int fsa9280_i2c_read(unsigned char u_addr, unsigned char *pu_data);

int fsa9280_i2c_tx_data(char* txData, int length)
{
	int i;
	
	struct i2c_msg msg[] = {
		{
			.addr = pclient->addr,
			.flags = 0,
			.len = length,
			.buf = txData,		
		},
	};

	for( i = 0; i < 10; i++)
	{
		if(i2c_transfer(pclient->adapter, msg, 1) >= 0) break;
		printk(KERN_ERR "[FSA9280]: tx error.. retry %d !!\n", i);
		mdelay(10);
	}
	if (i == 10) 
	{
		printk(KERN_ERR "[FSA9280]: fsa9280_i2c_tx_data error %d\n", i);
		return -EIO;
	}

	return 0;
}


int fsa9280_i2c_write(unsigned char u_addr, unsigned char u_data)
{
	int rc;
	unsigned char buf[2];

	buf[0] = u_addr;
	buf[1] = u_data;
    
	rc = fsa9280_i2c_tx_data(buf, 2);
	if(rc < 0)
		printk(KERN_ERR "[FSA9280]: txdata error %d add:0x%02x data:0x%02x\n",
			rc, u_addr, u_data);

	return rc;	
}

static int fsa9280_i2c_rx_data(char* rxData, int length)
{
	int i;
	
	struct i2c_msg msgs[] = {
		{
			.addr = pclient->addr,
			.flags = 0,      
			.len = 1,
			.buf = rxData,
		},
		{
			.addr = pclient->addr,
			.flags = I2C_M_RD,
			.len = length,
			.buf = rxData,
		},
	};


	for( i = 0; i < 10; i++)
	{
		if(i2c_transfer(pclient->adapter, msgs, 2) >= 0) break;
		printk(KERN_ERR "[FSA9280]: tx error.. retry %d !!\n", i);
		mdelay(10);
	}
	if (i == 10) 
	{
		printk(KERN_ERR "[FSA9280]: fsa9280_i2c_rx_data error %d\n", i);
		return -EIO;
	}
      
	return 0;
}

int fsa9280_i2c_read(unsigned char u_addr, unsigned char *pu_data)
{
	int rc;
	unsigned char buf;

	buf = u_addr;
	rc = fsa9280_i2c_rx_data(&buf, 1);
	if (!rc)
		*pu_data = buf;
	else 
		printk(KERN_ERR "[FSA9280]: i2c read failed\n");
	return rc;	
}

static void fsa9280_chip_init(void)
{
	unsigned char cont_reg = 0;
	
	printk(KERN_INFO "[FSA9280]: init\n");
	if (!pclient) 
		return;

    /* fsa9280 init sequence */
	fsa9280_i2c_write(0x02, 0x1E); // FSA9480 initilaization
	fsa9280_i2c_read(0x02, &cont_reg); // FSA9480 initilaization check
	printk("[FSA9280]: Initial control reg 0x02 : 0x%x\n", cont_reg);
	
	/* delay 2 ms */
	msleep(2);
	printk(KERN_INFO "[FSA9280]: fsa9280 sensor init sequence done\n");
}


static int fsa9280_client(struct i2c_client *client)
{
	/* Initialize the fsa9280 Chip */
	init_waitqueue_head(&g_data_ready_wait_queue);
	return 0;
}

extern int battery_restart(void);
extern int batt_init_done;	// hsil

//static int init_skip = 0;

static irqreturn_t fsa9280_interrupt_handler(int irq, void *data)
{
	disable_irq_nosync(irq);
	
	printk(KERN_INFO "[FSA9280]: irq active\n");	
//	if(!init_skip) //move.. msm_batt_check_event
//		init_skip = 1;
//	else 
		
	if (!batt_init_done)	// hsil : in case battery driver is not initilized
		printk("%s : This interrupt will be dropped\n", __func__);
	else
		battery_restart();

	printk(KERN_INFO "[FSA9280]: irq release\n");	
	enable_irq(irq);
	return IRQ_HANDLED;
}

static int fsa9280_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct fsa9280_data *mt;
	int err = -1;
	printk(KERN_INFO "[FSA9280]: probe\n");
	if(!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		goto exit_check_functionality_failed;		
	
	if(!(mt = kzalloc( sizeof(struct fsa9280_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit_alloc_data_failed;
	}

	i2c_set_clientdata(client, mt);
	fsa9280_client(client);
	pclient = client;
	
	fsa9280_chip_init();

	if(request_irq(MSM_GPIO_TO_INT(18), fsa9280_interrupt_handler, IRQF_TRIGGER_FALLING, "MICROUSB", NULL)) {
		free_irq(MSM_GPIO_TO_INT(18), NULL);
		printk("[FSA9280] fsa9280_interrupt_handler can't register the handler! and passing....\n");
	}
	
	printk(KERN_INFO "[FSA9280]: probe complete\n");
	return 0;
	
exit_alloc_data_failed:
exit_check_functionality_failed:
	
	return err;
}

	
static int fsa9280_remove(struct i2c_client *client)
{
	struct fsa9280_data *mt = i2c_get_clientdata(client);
	free_irq(client->irq, mt);

	//khsuh_imsi i2c_detach_client(client);
	pclient = NULL;

	kfree(mt);
	return 0;
}


static const struct i2c_device_id fsa9280_id[] = {
	{ "fsa9280", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, fsa9280_id);


static struct i2c_driver fsa9280_driver = {
	.probe 		= fsa9280_probe,
	.remove 	= fsa9280_remove,
	.id_table	= fsa9280_id,
	.driver = {		
		.name   = "fsa9280",
	},
};

static int __init fsa9280_init(void)
{
	return i2c_add_driver(&fsa9280_driver);
}

static void __exit fsa9280_exit(void)
{
	i2c_del_driver(&fsa9280_driver);
}


EXPORT_SYMBOL(fsa9280_i2c_read);
EXPORT_SYMBOL(fsa9280_i2c_write);

module_init(fsa9280_init);
module_exit(fsa9280_exit);

MODULE_AUTHOR("");
MODULE_DESCRIPTION("fsa9280 Driver");
MODULE_LICENSE("GPL");

