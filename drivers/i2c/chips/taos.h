#ifndef __TAOS_H__
#define __TAOS_H__


/* i2c */
#define I2C_M_WR 0 /* for i2c */
#define I2c_M_RD 1 /* for i2c */

/* sensor gpio */
#define GPIO_SENSE_OUT	27

/* sensor type */
#define LIGHT           0
#define PROXIMITY	1
#define ALL		2

/* IOCTL for proximity sensor */
#define TAOS_PROX_IOC_MAGIC   'C'                                 
#define TAOS_PROX_OPEN    _IO(TAOS_PROX_IOC_MAGIC,1)            
#define TAOS_PROX_CLOSE   _IO(TAOS_PROX_IOC_MAGIC,2)      

/* input device for proximity sensor */
#define USE_INPUT_DEVICE 	0  /* 0 : No Use  ,  1: Use  */

#define USE_INTERRUPT		1

/* driver data */
struct taos_data {
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct work_struct work_prox;  /* for proximity sensor */
	int             irq;
	struct hrtimer timer;
	struct timer_list light_init_timer;

};
struct taos_data *taos_global;


struct workqueue_struct *taos_wq;

/* prototype */
extern short taos_get_proximity_value(void);
static int proximity_open(struct inode *ip, struct file *fp);
static int proximity_release(struct inode *ip, struct file *fp);
static long proximity_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);


#endif
