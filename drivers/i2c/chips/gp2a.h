#ifndef __GP2A_H__
#define __GP2A_H__


/* i2c */
#define I2C_M_WR 0 /* for i2c */
#define I2c_M_RD 1 /* for i2c */

/* sensor gpio */
#define GPIO_SENSE_OUT	124


//ADDSEL is LOW
#define GP2A_ADDR	0x88 /* slave addr for i2c */

#define REGS_PROX 	0x0 // Read  Only
#define REGS_GAIN    	0x1 // Write Only
#define REGS_HYS	0x2 // Write Only
#define REGS_CYCLE	0x3 // Write Only
#define REGS_OPMOD	0x4 // Write Only
#define REGS_CON	0x6 // Write Only

/* sensor type */
#define LIGHT           0
#define PROXIMITY	1
#define ALL		2

/* power control */
#define ON              1
#define OFF		0

/* IOCTL for proximity sensor */
#define SHARP_GP2AP_IOC_MAGIC   'C'                                 
#define SHARP_GP2AP_OPEN    _IO(SHARP_GP2AP_IOC_MAGIC,1)            
#define SHARP_GP2AP_CLOSE   _IO(SHARP_GP2AP_IOC_MAGIC,2)      

/* input device for proximity sensor */
#define USE_INPUT_DEVICE 	0  /* 0 : No Use  ,  1: Use  */

#define USE_INTERRUPT		1
#define INT_CLEAR    1 /* 0 = by polling operation, 1 = by interrupt operation */


/* initial value for sensor register */
/*static u8 gp2a_original_image[8] =
{
	0x00,  
	0x08,  
	0xC2,  
	0x04,
	0x00,
};
*/
static u8 gp2a_original_image[8] =
{
	0x00,  	// REGS_PROX
	0x08,  	// REGS_GAIN
	0x40,  	// REGS_HYS
	0x04,  	// REGS_CYCLE
	0x03,   // REGS_OPMOD
};



/* driver data */
struct gp2a_data {
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct work_struct work_prox;  /* for proximity sensor */
	int             irq;
	struct hrtimer timer;
	struct timer_list light_init_timer;

};
struct gp2a_data *gp2a_global;


struct workqueue_struct *gp2a_wq;

/* prototype */
extern short gp2a_get_proximity_value(void);
static int proximity_open(struct inode *ip, struct file *fp);
static int proximity_release(struct inode *ip, struct file *fp);
static long proximity_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);


#endif
