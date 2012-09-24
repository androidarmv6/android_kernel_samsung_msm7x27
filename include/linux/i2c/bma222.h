#ifndef __BMA222_H__
#define __BMA222_H__
/*  $Date: 2010/03/31
 *  $Revision: 1.0 $
 *
 */

/*
 * This software program is licensed subject to the GNU General Public License
 * (GPL).Version 2,June 1991, available at http://www.fsf.org/copyleft/gpl.html

 * (C) Copyright 2010 Bosch Sensortec GmbH
 * All Rights Reserved
 */


/*************************************************************************************************/
/*! \file bma222.h
    \brief BMA222 Sensor Driver Support Header File */
/* user defined code to be added here ... */

//Example....
//#define YOUR_H_DEFINE  /**< <Doxy Comment for YOUR_H_DEFINE> */
/** Define the calling convention of YOUR bus communication routine.
        \note This includes types of parameters. This example shows the configuration for an SPI bus link.

    If your communication function looks like this:

    write_my_bus_xy(unsigned char device_addr, unsigned char register_addr, unsigned char * data, unsigned char length);

    The BMA222_WR_FUNC_PTR would equal:

    #define     BMA222_WR_FUNC_PTR char (* bus_write)(unsigned char, unsigned char, unsigned char *, unsigned char)

    Parameters can be mixed as needed refer to the \ref BMA222_BUS_WRITE_FUNC  macro.


*/

// [HSS] move from bma222_driver.h to bma222.h
/*! \file bma150_driver.h
    \brief This file contains all ioctl() commands define for the BMA222 in linux
    
    Details.
*/
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#include <linux/timer.h>
#include <linux/mutex.h>
#include <linux/hrtimer.h>
#include <linux/input.h>

#define BMA222_IOC_MAGIC 'B'

#define BMA222_SOFT_RESET				_IO(BMA222_IOC_MAGIC,0)
#define BMA222_SET_RANGE				_IOWR(BMA222_IOC_MAGIC,4, unsigned char)
#define BMA222_GET_RANGE				_IOWR(BMA222_IOC_MAGIC,5, unsigned char)
#define BMA222_SET_MODE					_IOWR(BMA222_IOC_MAGIC,6, unsigned char)
#define BMA222_GET_MODE					_IOWR(BMA222_IOC_MAGIC,7, unsigned char)
#define BMA222_SET_BANDWIDTH			_IOWR(BMA222_IOC_MAGIC,8, unsigned char)
#define BMA222_GET_BANDWIDTH			_IOWR(BMA222_IOC_MAGIC,9, unsigned char)

#define BMA222_RESET_INTERRUPT			_IO(BMA222_IOC_MAGIC,30)
#define BMA222_READ_ACCEL_X				_IOWR(BMA222_IOC_MAGIC,31,signed char)
#define BMA222_READ_ACCEL_Y				_IOWR(BMA222_IOC_MAGIC,32,signed char)
#define BMA222_READ_ACCEL_Z				_IOWR(BMA222_IOC_MAGIC,33,signed char)
#define BMA222_GET_INTERRUPT_STATUS		_IOWR(BMA222_IOC_MAGIC,34,unsigned char)

#define BMA222_READ_ACCEL_XYZ			_IOWR(BMA222_IOC_MAGIC,46,signed char)

#define BMA222_SET_INT_MODE             _IOWR(BMA222_IOC_MAGIC,50,unsigned char)
#define BMA222_SET_INT_Enable           _IOWR(BMA222_IOC_MAGIC,51,unsigned char)
#define BMA222_IOC_MAXNR				53
#define BMA222_GET_SENSOR_TYPE			_IOR(BMA222_IOC_MAGIC,52,signed char)
#define BMA222_GET_HWREV				_IOR(BMA222_IOC_MAGIC,53,int)
#define BMA222_CALIBRATION				_IOWR(BMA222_IOC_MAGIC,48,short)

#define BMA222_OFFSET_FILT_X_REG                0x38
#define BMA222_OFFSET_FILT_Y_REG                0x39
#define BMA222_OFFSET_FILT_Z_REG                0x3A

#define BMA222_WR_FUNC_PTR char (* bus_write)(unsigned char, unsigned char *, unsigned char)



/** link makro between API function calls and bus write function
        \note The bus write function can change since this is a system dependant issue.

    If the bus_write parameter calling order is like: reg_addr, reg_data, wr_len it would be as it is here.

    If the parameters are differently ordered or your communication function like I2C need to know the device address,
    you can change this macro accordingly.


    define BMA222_BUS_WRITE_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
    bus_write(dev_addr, reg_addr, reg_data, wr_len)

    This macro lets all API functions call YOUR communication routine in a way that equals your definition in the
    \ref BMA222_WR_FUNC_PTR definition.



*/
#define BMA222_BUS_WRITE_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
           bus_write(reg_addr, reg_data, wr_len)


/** Define the calling convention of YOUR bus communication routine.
        \note This includes types of parameters. This example shows the configuration for an SPI bus link.

    If your communication function looks like this:

    read_my_bus_xy(unsigned char device_addr, unsigned char register_addr, unsigned char * data, unsigned char length);

    The BMA222_RD_FUNC_PTR would equal:

    #define     BMA222_RD_FUNC_PTR char (* bus_read)(unsigned char, unsigned char, unsigned char *, unsigned char)

        Parameters can be mixed as needed refer to the \ref BMA222_BUS_READ_FUNC  macro.


*/

#define BMA222_SPI_RD_MASK 0x80   /* for spi read transactions on SPI the MSB has to be set */
#define BMA222_RD_FUNC_PTR char (* bus_read)( unsigned char, unsigned char *, unsigned char)


/** link makro between API function calls and bus read function
        \note The bus write function can change since this is a system dependant issue.

    If the bus_read parameter calling order is like: reg_addr, reg_data, wr_len it would be as it is here.

    If the parameters are differently ordered or your communication function like I2C need to know the device address,
    you can change this macro accordingly.


        define BMA222_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
           bus_read(dev_addr, reg_addr, reg_data, wr_len)

    This macro lets all API functions call YOUR communication routine in a way that equals your definition in the
    \ref BMA222_WR_FUNC_PTR definition.

        \note: this macro also includes the "MSB='1'" for reading BMA222 addresses.

*/
/*
#define BMA222_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, r_len)\
           bus_read(reg_addr | BMA222_SPI_RD_MASK, reg_data, r_len)

*/


#define BMA222_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, r_len)\
           bus_read(reg_addr, reg_data, r_len)

/** bma222 I2C Address
*/
//#define BMA222_I2C_ADDR                  0x18   // For engineering sample, should use 0x18 i2c address
#define BMA222_I2C_ADDR                  0x08
// [HSS] Support both address ( 0X18(old) and 0X08(new) ) (2010.09.29)
#define BMA222_I2C_ADDR_ENG                  0x18


/*
#define BMA222_I2C_ADDR1                0x40
#define BMA222_I2C_ADDR                 BMA222_I2C_ADDR1
#define BMA222_I2C_ADDR2                0x41
*/
/*
        SMB380 API error codes
*/

#define E_SMB_NULL_PTR          (char)-127
#define E_COMM_RES              (char)-1
#define E_OUT_OF_RANGE          (char)-2
#define E_EEPROM_BUSY           (char)-3

/*
 *
 *      register definitions
 *
 */


#define BMA222_EEP_OFFSET                       0x16
#define BMA222_IMAGE_BASE                       0x38
#define BMA222_IMAGE_LEN                        22


#define BMA222_CHIP_ID_REG                      0x00
#define BMA222_VERSION_REG                      0x01
#define BMA222_X_AXIS_LSB_REG                   0x02
#define BMA222_X_AXIS_MSB_REG                   0x03
#define BMA222_Y_AXIS_LSB_REG                   0x04
#define BMA222_Y_AXIS_MSB_REG                   0x05
#define BMA222_Z_AXIS_LSB_REG                   0x06
#define BMA222_Z_AXIS_MSB_REG                   0x07
#define BMA222_TEMP_RD_REG                      0x08
#define BMA222_STATUS1_REG                      0x09
#define BMA222_STATUS2_REG                      0x0A
#define BMA222_STATUS_TAP_SLOPE_REG             0x0B
#define BMA222_STATUS_ORIENT_HIGH_REG           0x0C
#define BMA222_RANGE_SEL_REG                    0x0F
#define BMA222_BW_SEL_REG                       0x10
#define BMA222_MODE_CTRL_REG                    0x11
#define BMA222_LOW_NOISE_CTRL_REG               0x12
#define BMA222_DATA_CTRL_REG                    0x13
#define BMA222_RESET_REG                        0x14
#define BMA222_INT_ENABLE1_REG                  0x16
#define BMA222_INT_ENABLE2_REG                  0x17
#define BMA222_INT1_PAD_SEL_REG                 0x19
#define BMA222_INT_DATA_SEL_REG                 0x1A
#define BMA222_INT2_PAD_SEL_REG                 0x1B
#define BMA222_INT_SRC_REG                      0x1E
#define BMA222_INT_SET_REG                      0x20
#define BMA222_INT_CTRL_REG                     0x21
#define BMA222_LOW_DURN_REG                     0x22
#define BMA222_LOW_THRES_REG                    0x23
#define BMA222_LOW_HIGH_HYST_REG                0x24
#define BMA222_HIGH_DURN_REG                    0x25
#define BMA222_HIGH_THRES_REG                   0x26
#define BMA222_SLOPE_DURN_REG                   0x27
#define BMA222_SLOPE_THRES_REG                  0x28
#define BMA222_TAP_PARAM_REG                    0x2A
#define BMA222_TAP_THRES_REG                    0x2B
#define BMA222_ORIENT_PARAM_REG                 0x2C
#define BMA222_THETA_BLOCK_REG                  0x2D
#define BMA222_THETA_FLAT_REG                   0x2E
#define BMA222_FLAT_HOLD_TIME_REG               0x2F
#define BMA222_SELF_TEST_REG                    0x32
#define BMA222_EEPROM_CTRL_REG                  0x33
#define BMA222_SERIAL_CTRL_REG                  0x34
#define BMA222_EXTMODE_CTRL_REG                 0x35
#define BMA222_OFFSET_CTRL_REG                  0x36
#define BMA222_OFFSET_PARAMS_REG                0x37
#define BMA222_OFFSET_X_AXIS_REG                0x38
#define BMA222_OFFSET_Y_AXIS_REG                0x39
#define BMA222_OFFSET_Z_AXIS_REG                0x3A
#define BMA222_TRIM_ADC_REG                     0x46


// [HSS] from define.h

typedef char                            S8;
typedef unsigned char                   U8;
typedef short                           S16;
typedef unsigned short                  U16;
typedef int                             S32;
typedef unsigned int                    U32;
typedef long long                       S64;
typedef unsigned long long              U64;
typedef unsigned char                   BIT;
typedef unsigned int                    BOOL;
typedef double                          F32;

#define ON                      1                                               /**< Define for "ON" */
#define OFF                     0                                               /**< Define for "OFF" */
#define TRUE            1                                               /**< Define for "TRUE" */
#define FALSE           0                                               /**< Define for "FALSE" */
#define ENABLE  1                                               /**< Define for "ENABLE" */
#define DISABLE 0                                               /**< Define for "DISABLE" */
#define LOW                     0                                               /**< Define for "Low" */
#define HIGH            1                                               /**< Define for "High" */
#define INPUT           0                                               /**< Define for "Input" */
#define OUTPUT  1                                               /**< Define for "Output" */



#define         C_Null_U8X                              (U8)0
#define         C_Zero_U8X                              (U8)0
#define         C_One_U8X                               (U8)1
#define         C_Two_U8X                               (U8)2
#define         C_Three_U8X                             (U8)3
#define         C_Four_U8X                              (U8)4
#define         C_Five_U8X                              (U8)5
#define         C_Six_U8X                               (U8)6
#define         C_Seven_U8X                             (U8)7
#define         C_Eight_U8X                             (U8)8
#define         C_Nine_U8X                              (U8)9
#define         C_Ten_U8X                               (U8)10
#define         C_Eleven_U8X                            (U8)11
#define         C_Twelve_U8X                            (U8)12
#define         C_Sixteen_U8X                           (U8)16
#define         C_TwentyFour_U8X                        (U8)24
#define         C_ThirtyTwo_U8X                         (U8)32
#define         C_Hundred_U8X                           (U8)100
#define         C_OneTwentySeven_U8X                    (U8)127
#define         C_TwoFiftyFive_U8X                      (U8)255
#define         C_TwoFiftySix_U16X                      (U16)256
/* Return type is True */
#define C_Successful_S8X                        (S8)0
/* return type is False */
#define C_Unsuccessful_S8X                      (S8)-1

typedef enum
{
        E_False,
        E_True
} te_Boolean;

// [HSS] from define.h end


/* register write and read delays */

#define BMA222_MDELAY_DATA_TYPE                 unsigned int
#define BMA222_EE_W_DELAY                       28                    /* delay after EEP write is 28 msec */
/** bma222 acceleration data
        \brief Structure containing acceleration values for x,y and z-axis in signed short

*/

typedef struct
{
   short x, /**< holds x-axis acceleration data sign extended. Range -512 to 511. */
         y, /**< holds y-axis acceleration data sign extended. Range -512 to 511. */
         z; /**< holds z-axis acceleration data sign extended. Range -512 to 511. */
} bma222acc_t;
/** bma222 image registers data structure
        \brief Register type that contains all bma222 image registers from address 0x38 to 0x4D
        This structure can hold the complete image data of bma222

*/
typedef struct
{
   unsigned char
   offset_filt_x ,                 /**<  image address 0x38:  */
   offset_filt_y ,                 /**<  image address 0x39:  */
   offset_filt_z ,                 /**<  image address 0x3A:  */
   offset_unfilt_x ,               /**<  image address 0x3B:  */
   offset_unfilt_y ,               /**<  image address 0x3C:  */
   offset_unfilt_z ,               /**<  image address 0x3D:  */
   spare_0 ,                       /**<  image address 0x3E:  */
   spare_1 ,                       /**<  image address 0x3F:  */
   crc ,                           /**<  image address 0x40:  */
   i2c_addr ,                      /**<  image address 0x41:  */
   dev_config ,                    /**<  image address 0x42:  */
   trim_offset_t ,                 /**<  image address 0x43:  */
   gain_x ,                        /**<  image address 0x44:  */
   offset_x ,                      /**<  image address 0x45:  */
   gain_y ,                        /**<  image address 0x46:  */
   offset_y ,                      /**<  image address 0x47:  */
   gain_z ,                        /**<  image address 0x48:  */
   offset_z ,                      /**<  image address 0x49:  */
   trim1 ,                         /**<  image address 0x4A:  */
   trim2 ,                         /**<  image address 0x4B:  */
   trim3 ,                         /**<  image address 0x4C:  */
   trim4 ;                          /**<  image address 0x4D:  */
} bma222regs_t;
/** bma222 typedef structure
        \brief This structure holds all relevant information about bma222 and links communication to the
*/

typedef struct
{
	bma222regs_t * image;   /**< pointer to bma222regs_t structure not mandatory */
   	unsigned char mode;     /**< save current bma222 operation mode */
   	unsigned char chip_id,  /**< save bma222's chip id which has to be 0x02 after calling bma222_init() */
                             ml_version, /**< holds the bma222 ML_version number */
                             al_version; /**< holds the bma222 AL_version number */
   	unsigned char dev_addr;   /**< initializes bma222's I2C device address 0x38 */
   	unsigned char int_mask;   /**< stores the current bma222 API generated interrupt mask */
   	BMA222_WR_FUNC_PTR;               /**< function pointer to the SPI/I2C write function */
   	BMA222_RD_FUNC_PTR;               /**< function pointer to the SPI/I2C read function */
   	void (*delay_msec)( BMA222_MDELAY_DATA_TYPE ); /**< function pointer to a pause in mili seconds function */

   	struct work_struct work_acc;
	struct hrtimer timer;
	ktime_t acc_poll_delay;
	u8 state;
	struct mutex power_lock;
	struct workqueue_struct *wq;
	struct input_dev *acc_input_dev;
} bma222_t;

#define BMA222_CHIP_ID__POS             0
#define BMA222_CHIP_ID__MSK             0xFF
#define BMA222_CHIP_ID__LEN             8
#define BMA222_CHIP_ID__REG             BMA222_CHIP_ID_REG

#define BMA222_ML_VERSION__POS          0
#define BMA222_ML_VERSION__LEN          4
#define BMA222_ML_VERSION__MSK          0x0F
#define BMA222_ML_VERSION__REG          BMA222_VERSION_REG

#define BMA222_AL_VERSION__POS          4
#define BMA222_AL_VERSION__LEN          4
#define BMA222_AL_VERSION__MSK          0xF0
#define BMA222_AL_VERSION__REG          BMA222_VERSION_REG
/* DATA REGISTERS */

#define BMA222_NEW_DATA_X__POS          0
#define BMA222_NEW_DATA_X__LEN          1
#define BMA222_NEW_DATA_X__MSK          0x01
#define BMA222_NEW_DATA_X__REG          BMA222_X_AXIS_LSB_REG

#define BMA222_ACC_X14_LSB__POS           2
#define BMA222_ACC_X14_LSB__LEN           6
#define BMA222_ACC_X14_LSB__MSK           0xFC
#define BMA222_ACC_X14_LSB__REG           BMA222_X_AXIS_LSB_REG

#define BMA222_ACC_X12_LSB__POS           4
#define BMA222_ACC_X12_LSB__LEN           4
#define BMA222_ACC_X12_LSB__MSK           0xF0
#define BMA222_ACC_X12_LSB__REG           BMA222_X_AXIS_LSB_REG

#define BMA222_ACC_X10_LSB__POS           6
#define BMA222_ACC_X10_LSB__LEN           2
#define BMA222_ACC_X10_LSB__MSK           0xC0
#define BMA222_ACC_X10_LSB__REG           BMA222_X_AXIS_LSB_REG

#define BMA222_ACC_X8_LSB__POS           0
#define BMA222_ACC_X8_LSB__LEN           0
#define BMA222_ACC_X8_LSB__MSK           0x00
#define BMA222_ACC_X8_LSB__REG           BMA222_X_AXIS_LSB_REG

#define BMA222_ACC_X_MSB__POS           0
#define BMA222_ACC_X_MSB__LEN           8
#define BMA222_ACC_X_MSB__MSK           0xFF
#define BMA222_ACC_X_MSB__REG           BMA222_X_AXIS_MSB_REG

#define BMA222_NEW_DATA_Y__POS          0
#define BMA222_NEW_DATA_Y__LEN          1
#define BMA222_NEW_DATA_Y__MSK          0x01
#define BMA222_NEW_DATA_Y__REG          BMA222_Y_AXIS_LSB_REG

#define BMA222_ACC_Y14_LSB__POS           2
#define BMA222_ACC_Y14_LSB__LEN           6
#define BMA222_ACC_Y14_LSB__MSK           0xFC
#define BMA222_ACC_Y14_LSB__REG           BMA222_Y_AXIS_LSB_REG

#define BMA222_ACC_Y12_LSB__POS           4
#define BMA222_ACC_Y12_LSB__LEN           4
#define BMA222_ACC_Y12_LSB__MSK           0xF0
#define BMA222_ACC_Y12_LSB__REG           BMA222_Y_AXIS_LSB_REG

#define BMA222_ACC_Y10_LSB__POS           6
#define BMA222_ACC_Y10_LSB__LEN           2
#define BMA222_ACC_Y10_LSB__MSK           0xC0
#define BMA222_ACC_Y10_LSB__REG           BMA222_Y_AXIS_LSB_REG

#define BMA222_ACC_Y8_LSB__POS           0
#define BMA222_ACC_Y8_LSB__LEN           0
#define BMA222_ACC_Y8_LSB__MSK           0x00
#define BMA222_ACC_Y8_LSB__REG           BMA222_Y_AXIS_LSB_REG

#define BMA222_ACC_Y_MSB__POS           0
#define BMA222_ACC_Y_MSB__LEN           8
#define BMA222_ACC_Y_MSB__MSK           0xFF
#define BMA222_ACC_Y_MSB__REG           BMA222_Y_AXIS_MSB_REG

#define BMA222_NEW_DATA_Z__POS          0
#define BMA222_NEW_DATA_Z__LEN          1
#define BMA222_NEW_DATA_Z__MSK          0x01
#define BMA222_NEW_DATA_Z__REG          BMA222_Z_AXIS_LSB_REG

#define BMA222_ACC_Z14_LSB__POS           2
#define BMA222_ACC_Z14_LSB__LEN           6
#define BMA222_ACC_Z14_LSB__MSK           0xFC
#define BMA222_ACC_Z14_LSB__REG           BMA222_Z_AXIS_LSB_REG

#define BMA222_ACC_Z12_LSB__POS           4
#define BMA222_ACC_Z12_LSB__LEN           4
#define BMA222_ACC_Z12_LSB__MSK           0xF0
#define BMA222_ACC_Z12_LSB__REG           BMA222_Z_AXIS_LSB_REG

#define BMA222_ACC_Z10_LSB__POS           6
#define BMA222_ACC_Z10_LSB__LEN           2
#define BMA222_ACC_Z10_LSB__MSK           0xC0
#define BMA222_ACC_Z10_LSB__REG           BMA222_Z_AXIS_LSB_REG

#define BMA222_ACC_Z8_LSB__POS           0
#define BMA222_ACC_Z8_LSB__LEN           0
#define BMA222_ACC_Z8_LSB__MSK           0x00
#define BMA222_ACC_Z8_LSB__REG           BMA222_Z_AXIS_LSB_REG

#define BMA222_ACC_Z_MSB__POS           0
#define BMA222_ACC_Z_MSB__LEN           8
#define BMA222_ACC_Z_MSB__MSK           0xFF
#define BMA222_ACC_Z_MSB__REG           BMA222_Z_AXIS_MSB_REG
#define BMA222_TEMPERATURE__POS         0
#define BMA222_TEMPERATURE__LEN         8
#define BMA222_TEMPERATURE__MSK         0xFF
#define BMA222_TEMPERATURE__REG         BMA222_TEMP_RD_REG
/*  INTERRUPT STATUS BITS  */

#define BMA222_LOWG_INT_S__POS          0
#define BMA222_LOWG_INT_S__LEN          1
#define BMA222_LOWG_INT_S__MSK          0x01
#define BMA222_LOWG_INT_S__REG          BMA222_STATUS1_REG

#define BMA222_HIGHG_INT_S__POS          1
#define BMA222_HIGHG_INT_S__LEN          1
#define BMA222_HIGHG_INT_S__MSK          0x02
#define BMA222_HIGHG_INT_S__REG          BMA222_STATUS1_REG

#define BMA222_SLOPE_INT_S__POS          2
#define BMA222_SLOPE_INT_S__LEN          1
#define BMA222_SLOPE_INT_S__MSK          0x04
#define BMA222_SLOPE_INT_S__REG          BMA222_STATUS1_REG

#define BMA222_SLOW_INT_S__POS          3
#define BMA222_SLOW_INT_S__LEN          1
#define BMA222_SLOW_INT_S__MSK          0x08
#define BMA222_SLOW_INT_S__REG          BMA222_STATUS1_REG

#define BMA222_DOUBLE_TAP_INT_S__POS     4
#define BMA222_DOUBLE_TAP_INT_S__LEN     1
#define BMA222_DOUBLE_TAP_INT_S__MSK     0x10
#define BMA222_DOUBLE_TAP_INT_S__REG     BMA222_STATUS1_REG

#define BMA222_SINGLE_TAP_INT_S__POS     5
#define BMA222_SINGLE_TAP_INT_S__LEN     1
#define BMA222_SINGLE_TAP_INT_S__MSK     0x20
#define BMA222_SINGLE_TAP_INT_S__REG     BMA222_STATUS1_REG

#define BMA222_ORIENT_INT_S__POS         6
#define BMA222_ORIENT_INT_S__LEN         1
#define BMA222_ORIENT_INT_S__MSK         0x40
#define BMA222_ORIENT_INT_S__REG         BMA222_STATUS1_REG

#define BMA222_FLAT_INT_S__POS           7
#define BMA222_FLAT_INT_S__LEN           1
#define BMA222_FLAT_INT_S__MSK           0x80
#define BMA222_FLAT_INT_S__REG           BMA222_STATUS1_REG

#define BMA222_DATA_INT_S__POS           7
#define BMA222_DATA_INT_S__LEN           1
#define BMA222_DATA_INT_S__MSK           0x80
#define BMA222_DATA_INT_S__REG           BMA222_STATUS2_REG
#define BMA222_SLOPE_FIRST_X__POS        0
#define BMA222_SLOPE_FIRST_X__LEN        1
#define BMA222_SLOPE_FIRST_X__MSK        0x01
#define BMA222_SLOPE_FIRST_X__REG        BMA222_STATUS_TAP_SLOPE_REG

#define BMA222_SLOPE_FIRST_Y__POS        1
#define BMA222_SLOPE_FIRST_Y__LEN        1
#define BMA222_SLOPE_FIRST_Y__MSK        0x02
#define BMA222_SLOPE_FIRST_Y__REG        BMA222_STATUS_TAP_SLOPE_REG

#define BMA222_SLOPE_FIRST_Z__POS        2
#define BMA222_SLOPE_FIRST_Z__LEN        1
#define BMA222_SLOPE_FIRST_Z__MSK        0x04
#define BMA222_SLOPE_FIRST_Z__REG        BMA222_STATUS_TAP_SLOPE_REG

#define BMA222_SLOPE_SIGN_S__POS         3
#define BMA222_SLOPE_SIGN_S__LEN         1
#define BMA222_SLOPE_SIGN_S__MSK         0x08
#define BMA222_SLOPE_SIGN_S__REG         BMA222_STATUS_TAP_SLOPE_REG
#define BMA222_TAP_FIRST_X__POS        4
#define BMA222_TAP_FIRST_X__LEN        1
#define BMA222_TAP_FIRST_X__MSK        0x10
#define BMA222_TAP_FIRST_X__REG        BMA222_STATUS_TAP_SLOPE_REG

#define BMA222_TAP_FIRST_Y__POS        5
#define BMA222_TAP_FIRST_Y__LEN        1
#define BMA222_TAP_FIRST_Y__MSK        0x20
#define BMA222_TAP_FIRST_Y__REG        BMA222_STATUS_TAP_SLOPE_REG

#define BMA222_TAP_FIRST_Z__POS        6
#define BMA222_TAP_FIRST_Z__LEN        1
#define BMA222_TAP_FIRST_Z__MSK        0x40
#define BMA222_TAP_FIRST_Z__REG        BMA222_STATUS_TAP_SLOPE_REG

#define BMA222_TAP_SIGN_S__POS         7
#define BMA222_TAP_SIGN_S__LEN         1
#define BMA222_TAP_SIGN_S__MSK         0x80
#define BMA222_TAP_SIGN_S__REG         BMA222_STATUS_TAP_SLOPE_REG
#define BMA222_HIGHG_FIRST_X__POS        0
#define BMA222_HIGHG_FIRST_X__LEN        1
#define BMA222_HIGHG_FIRST_X__MSK        0x01
#define BMA222_HIGHG_FIRST_X__REG        BMA222_STATUS_ORIENT_HIGH_REG

#define BMA222_HIGHG_FIRST_Y__POS        1
#define BMA222_HIGHG_FIRST_Y__LEN        1
#define BMA222_HIGHG_FIRST_Y__MSK        0x02
#define BMA222_HIGHG_FIRST_Y__REG        BMA222_STATUS_ORIENT_HIGH_REG

#define BMA222_HIGHG_FIRST_Z__POS        2
#define BMA222_HIGHG_FIRST_Z__LEN        1
#define BMA222_HIGHG_FIRST_Z__MSK        0x04
#define BMA222_HIGHG_FIRST_Z__REG        BMA222_STATUS_ORIENT_HIGH_REG

#define BMA222_HIGHG_SIGN_S__POS         3
#define BMA222_HIGHG_SIGN_S__LEN         1
#define BMA222_HIGHG_SIGN_S__MSK         0x08
#define BMA222_HIGHG_SIGN_S__REG         BMA222_STATUS_ORIENT_HIGH_REG
#define BMA222_ORIENT_S__POS             4
#define BMA222_ORIENT_S__LEN             3
#define BMA222_ORIENT_S__MSK             0x70
#define BMA222_ORIENT_S__REG             BMA222_STATUS_ORIENT_HIGH_REG

#define BMA222_FLAT_S__POS               7
#define BMA222_FLAT_S__LEN               1
#define BMA222_FLAT_S__MSK               0x80
#define BMA222_FLAT_S__REG               BMA222_STATUS_ORIENT_HIGH_REG
#define BMA222_RANGE_SEL__POS             0
#define BMA222_RANGE_SEL__LEN             4
#define BMA222_RANGE_SEL__MSK             0x0F
#define BMA222_RANGE_SEL__REG             BMA222_RANGE_SEL_REG
#define BMA222_BANDWIDTH__POS             0
#define BMA222_BANDWIDTH__LEN             5
#define BMA222_BANDWIDTH__MSK             0x1F
#define BMA222_BANDWIDTH__REG             BMA222_BW_SEL_REG
#define BMA222_SLEEP_DUR__POS             1
#define BMA222_SLEEP_DUR__LEN             4
#define BMA222_SLEEP_DUR__MSK             0x1E
#define BMA222_SLEEP_DUR__REG             BMA222_MODE_CTRL_REG
#define BMA222_EN_LOW_POWER__POS          6
#define BMA222_EN_LOW_POWER__LEN          1
#define BMA222_EN_LOW_POWER__MSK          0x40
#define BMA222_EN_LOW_POWER__REG          BMA222_MODE_CTRL_REG
#define BMA222_EN_SUSPEND__POS            7
#define BMA222_EN_SUSPEND__LEN            1
#define BMA222_EN_SUSPEND__MSK            0x80
#define BMA222_EN_SUSPEND__REG            BMA222_MODE_CTRL_REG
#define BMA222_EN_LOW_NOISE__POS          7
#define BMA222_EN_LOW_NOISE__LEN          1
#define BMA222_EN_LOW_NOISE__MSK          0x80
#define BMA222_EN_LOW_NOISE__REG          BMA222_LOW_NOISE_CTRL_REG
/**     DISABLE MSB SHADOWING PROCEDURE          **/

#define BMA222_DIS_SHADOW_PROC__POS       6
#define BMA222_DIS_SHADOW_PROC__LEN       1
#define BMA222_DIS_SHADOW_PROC__MSK       0x40
#define BMA222_DIS_SHADOW_PROC__REG       BMA222_DATA_CTRL_REG

/**     FILTERED OR UNFILTERED ACCELERATION DATA  **/

#define BMA222_EN_DATA_HIGH_BW__POS         7
#define BMA222_EN_DATA_HIGH_BW__LEN         1
#define BMA222_EN_DATA_HIGH_BW__MSK         0x80
#define BMA222_EN_DATA_HIGH_BW__REG         BMA222_DATA_CTRL_REG
/**     RESET REGISTERS                         **/

#define BMA222_EN_SOFT_RESET__POS         0
#define BMA222_EN_SOFT_RESET__LEN         8
#define BMA222_EN_SOFT_RESET__MSK         0xFF
#define BMA222_EN_SOFT_RESET__REG         BMA222_RESET_REG

#define BMA222_EN_SOFT_RESET_VALUE        0xB6
/**     INTERRUPT ENABLE REGISTER              **/


#define BMA222_EN_SLOPE_X_INT__POS         0
#define BMA222_EN_SLOPE_X_INT__LEN         1
#define BMA222_EN_SLOPE_X_INT__MSK         0x01
#define BMA222_EN_SLOPE_X_INT__REG         BMA222_INT_ENABLE1_REG

#define BMA222_EN_SLOPE_Y_INT__POS         1
#define BMA222_EN_SLOPE_Y_INT__LEN         1
#define BMA222_EN_SLOPE_Y_INT__MSK         0x02
#define BMA222_EN_SLOPE_Y_INT__REG         BMA222_INT_ENABLE1_REG

#define BMA222_EN_SLOPE_Z_INT__POS         2
#define BMA222_EN_SLOPE_Z_INT__LEN         1
#define BMA222_EN_SLOPE_Z_INT__MSK         0x04
#define BMA222_EN_SLOPE_Z_INT__REG         BMA222_INT_ENABLE1_REG

#define BMA222_EN_SLOW_INT__POS            3
#define BMA222_EN_SLOW_INT__LEN            1
#define BMA222_EN_SLOW_INT__MSK            0x08
#define BMA222_EN_SLOW_INT__REG            BMA222_INT_ENABLE1_REG

#define BMA222_EN_DOUBLE_TAP_INT__POS      4
#define BMA222_EN_DOUBLE_TAP_INT__LEN      1
#define BMA222_EN_DOUBLE_TAP_INT__MSK      0x10
#define BMA222_EN_DOUBLE_TAP_INT__REG      BMA222_INT_ENABLE1_REG

#define BMA222_EN_SINGLE_TAP_INT__POS      5
#define BMA222_EN_SINGLE_TAP_INT__LEN      1
#define BMA222_EN_SINGLE_TAP_INT__MSK      0x20
#define BMA222_EN_SINGLE_TAP_INT__REG      BMA222_INT_ENABLE1_REG

#define BMA222_EN_ORIENT_INT__POS          6
#define BMA222_EN_ORIENT_INT__LEN          1
#define BMA222_EN_ORIENT_INT__MSK          0x40
#define BMA222_EN_ORIENT_INT__REG          BMA222_INT_ENABLE1_REG

#define BMA222_EN_FLAT_INT__POS            7
#define BMA222_EN_FLAT_INT__LEN            1
#define BMA222_EN_FLAT_INT__MSK            0x80
#define BMA222_EN_FLAT_INT__REG            BMA222_INT_ENABLE1_REG
/**     INTERRUPT ENABLE REGISTER              **/

#define BMA222_EN_HIGHG_X_INT__POS         0
#define BMA222_EN_HIGHG_X_INT__LEN         1
#define BMA222_EN_HIGHG_X_INT__MSK         0x01
#define BMA222_EN_HIGHG_X_INT__REG         BMA222_INT_ENABLE2_REG

#define BMA222_EN_HIGHG_Y_INT__POS         1
#define BMA222_EN_HIGHG_Y_INT__LEN         1
#define BMA222_EN_HIGHG_Y_INT__MSK         0x02
#define BMA222_EN_HIGHG_Y_INT__REG         BMA222_INT_ENABLE2_REG

#define BMA222_EN_HIGHG_Z_INT__POS         2
#define BMA222_EN_HIGHG_Z_INT__LEN         1
#define BMA222_EN_HIGHG_Z_INT__MSK         0x04
#define BMA222_EN_HIGHG_Z_INT__REG         BMA222_INT_ENABLE2_REG

#define BMA222_EN_LOWG_INT__POS            3
#define BMA222_EN_LOWG_INT__LEN            1
#define BMA222_EN_LOWG_INT__MSK            0x08
#define BMA222_EN_LOWG_INT__REG            BMA222_INT_ENABLE2_REG

#define BMA222_EN_NEW_DATA_INT__POS        4
#define BMA222_EN_NEW_DATA_INT__LEN        1
#define BMA222_EN_NEW_DATA_INT__MSK        0x10
#define BMA222_EN_NEW_DATA_INT__REG        BMA222_INT_ENABLE2_REG
#define BMA222_EN_INT1_PAD_LOWG__POS        0
#define BMA222_EN_INT1_PAD_LOWG__LEN        1
#define BMA222_EN_INT1_PAD_LOWG__MSK        0x01
#define BMA222_EN_INT1_PAD_LOWG__REG        BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_HIGHG__POS       1
#define BMA222_EN_INT1_PAD_HIGHG__LEN       1
#define BMA222_EN_INT1_PAD_HIGHG__MSK       0x02
#define BMA222_EN_INT1_PAD_HIGHG__REG       BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_SLOPE__POS       2
#define BMA222_EN_INT1_PAD_SLOPE__LEN       1
#define BMA222_EN_INT1_PAD_SLOPE__MSK       0x04
#define BMA222_EN_INT1_PAD_SLOPE__REG       BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_SLOW__POS        3
#define BMA222_EN_INT1_PAD_SLOW__LEN        1
#define BMA222_EN_INT1_PAD_SLOW__MSK        0x08
#define BMA222_EN_INT1_PAD_SLOW__REG        BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_DB_TAP__POS      4
#define BMA222_EN_INT1_PAD_DB_TAP__LEN      1
#define BMA222_EN_INT1_PAD_DB_TAP__MSK      0x10
#define BMA222_EN_INT1_PAD_DB_TAP__REG      BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_SNG_TAP__POS     5
#define BMA222_EN_INT1_PAD_SNG_TAP__LEN     1
#define BMA222_EN_INT1_PAD_SNG_TAP__MSK     0x20
#define BMA222_EN_INT1_PAD_SNG_TAP__REG     BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_ORIENT__POS      6
#define BMA222_EN_INT1_PAD_ORIENT__LEN      1
#define BMA222_EN_INT1_PAD_ORIENT__MSK      0x40
#define BMA222_EN_INT1_PAD_ORIENT__REG      BMA222_INT1_PAD_SEL_REG

#define BMA222_EN_INT1_PAD_FLAT__POS        7
#define BMA222_EN_INT1_PAD_FLAT__LEN        1
#define BMA222_EN_INT1_PAD_FLAT__MSK        0x80
#define BMA222_EN_INT1_PAD_FLAT__REG        BMA222_INT1_PAD_SEL_REG
#define BMA222_EN_INT2_PAD_LOWG__POS        0
#define BMA222_EN_INT2_PAD_LOWG__LEN        1
#define BMA222_EN_INT2_PAD_LOWG__MSK        0x01
#define BMA222_EN_INT2_PAD_LOWG__REG        BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_HIGHG__POS       1
#define BMA222_EN_INT2_PAD_HIGHG__LEN       1
#define BMA222_EN_INT2_PAD_HIGHG__MSK       0x02
#define BMA222_EN_INT2_PAD_HIGHG__REG       BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_SLOPE__POS       2
#define BMA222_EN_INT2_PAD_SLOPE__LEN       1
#define BMA222_EN_INT2_PAD_SLOPE__MSK       0x04
#define BMA222_EN_INT2_PAD_SLOPE__REG       BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_SLOW__POS        3
#define BMA222_EN_INT2_PAD_SLOW__LEN        1
#define BMA222_EN_INT2_PAD_SLOW__MSK        0x08
#define BMA222_EN_INT2_PAD_SLOW__REG        BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_DB_TAP__POS      4
#define BMA222_EN_INT2_PAD_DB_TAP__LEN      1
#define BMA222_EN_INT2_PAD_DB_TAP__MSK      0x10
#define BMA222_EN_INT2_PAD_DB_TAP__REG      BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_SNG_TAP__POS     5
#define BMA222_EN_INT2_PAD_SNG_TAP__LEN     1
#define BMA222_EN_INT2_PAD_SNG_TAP__MSK     0x20
#define BMA222_EN_INT2_PAD_SNG_TAP__REG     BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_ORIENT__POS      6
#define BMA222_EN_INT2_PAD_ORIENT__LEN      1
#define BMA222_EN_INT2_PAD_ORIENT__MSK      0x40
#define BMA222_EN_INT2_PAD_ORIENT__REG      BMA222_INT2_PAD_SEL_REG

#define BMA222_EN_INT2_PAD_FLAT__POS        7
#define BMA222_EN_INT2_PAD_FLAT__LEN        1
#define BMA222_EN_INT2_PAD_FLAT__MSK        0x80
#define BMA222_EN_INT2_PAD_FLAT__REG        BMA222_INT2_PAD_SEL_REG
#define BMA222_EN_INT1_PAD_NEWDATA__POS     0
#define BMA222_EN_INT1_PAD_NEWDATA__LEN     1
#define BMA222_EN_INT1_PAD_NEWDATA__MSK     0x01
#define BMA222_EN_INT1_PAD_NEWDATA__REG     BMA222_INT_DATA_SEL_REG

#define BMA222_EN_INT2_PAD_NEWDATA__POS     7
#define BMA222_EN_INT2_PAD_NEWDATA__LEN     1
#define BMA222_EN_INT2_PAD_NEWDATA__MSK     0x80
#define BMA222_EN_INT2_PAD_NEWDATA__REG     BMA222_INT_DATA_SEL_REG
/*****          INTERRUPT SOURCE SELECTION                      *****/

#define BMA222_UNFILT_INT_SRC_LOWG__POS        0
#define BMA222_UNFILT_INT_SRC_LOWG__LEN        1
#define BMA222_UNFILT_INT_SRC_LOWG__MSK        0x01
#define BMA222_UNFILT_INT_SRC_LOWG__REG        BMA222_INT_SRC_REG

#define BMA222_UNFILT_INT_SRC_HIGHG__POS       1
#define BMA222_UNFILT_INT_SRC_HIGHG__LEN       1
#define BMA222_UNFILT_INT_SRC_HIGHG__MSK       0x02
#define BMA222_UNFILT_INT_SRC_HIGHG__REG       BMA222_INT_SRC_REG

#define BMA222_UNFILT_INT_SRC_SLOPE__POS       2
#define BMA222_UNFILT_INT_SRC_SLOPE__LEN       1
#define BMA222_UNFILT_INT_SRC_SLOPE__MSK       0x04
#define BMA222_UNFILT_INT_SRC_SLOPE__REG       BMA222_INT_SRC_REG

#define BMA222_UNFILT_INT_SRC_SLOW__POS        3
#define BMA222_UNFILT_INT_SRC_SLOW__LEN        1
#define BMA222_UNFILT_INT_SRC_SLOW__MSK        0x08
#define BMA222_UNFILT_INT_SRC_SLOW__REG        BMA222_INT_SRC_REG

#define BMA222_UNFILT_INT_SRC_TAP__POS         4
#define BMA222_UNFILT_INT_SRC_TAP__LEN         1
#define BMA222_UNFILT_INT_SRC_TAP__MSK         0x10
#define BMA222_UNFILT_INT_SRC_TAP__REG         BMA222_INT_SRC_REG

#define BMA222_UNFILT_INT_SRC_DATA__POS        5
#define BMA222_UNFILT_INT_SRC_DATA__LEN        1
#define BMA222_UNFILT_INT_SRC_DATA__MSK        0x20
#define BMA222_UNFILT_INT_SRC_DATA__REG        BMA222_INT_SRC_REG
/*****  INTERRUPT PAD ACTIVE LEVEL AND OUTPUT TYPE       *****/

#define BMA222_INT1_PAD_ACTIVE_LEVEL__POS       0
#define BMA222_INT1_PAD_ACTIVE_LEVEL__LEN       1
#define BMA222_INT1_PAD_ACTIVE_LEVEL__MSK       0x01
#define BMA222_INT1_PAD_ACTIVE_LEVEL__REG       BMA222_INT_SET_REG

#define BMA222_INT2_PAD_ACTIVE_LEVEL__POS       2
#define BMA222_INT2_PAD_ACTIVE_LEVEL__LEN       1
#define BMA222_INT2_PAD_ACTIVE_LEVEL__MSK       0x04
#define BMA222_INT2_PAD_ACTIVE_LEVEL__REG       BMA222_INT_SET_REG


/*****  OUTPUT TYPE IF SET TO 1 IS : OPEN DRIVE , IF NOT SET
        IT IS PUSH-PULL                                  *****/


#define BMA222_INT1_PAD_OUTPUT_TYPE__POS        1
#define BMA222_INT1_PAD_OUTPUT_TYPE__LEN        1
#define BMA222_INT1_PAD_OUTPUT_TYPE__MSK        0x02
#define BMA222_INT1_PAD_OUTPUT_TYPE__REG        BMA222_INT_SET_REG

#define BMA222_INT2_PAD_OUTPUT_TYPE__POS        3
#define BMA222_INT2_PAD_OUTPUT_TYPE__LEN        1
#define BMA222_INT2_PAD_OUTPUT_TYPE__MSK        0x08
#define BMA222_INT2_PAD_OUTPUT_TYPE__REG        BMA222_INT_SET_REG
/*****               INTERRUPT MODE SELECTION              ******/

#define BMA222_INT_MODE_SEL__POS                0
#define BMA222_INT_MODE_SEL__LEN                4
#define BMA222_INT_MODE_SEL__MSK                0x0F
#define BMA222_INT_MODE_SEL__REG                BMA222_INT_CTRL_REG

/*****               LATCHED INTERRUPT RESET               ******/

#define BMA222_INT_RESET_LATCHED__POS           7
#define BMA222_INT_RESET_LATCHED__LEN           1
#define BMA222_INT_RESET_LATCHED__MSK           0x80
#define BMA222_INT_RESET_LATCHED__REG           BMA222_INT_CTRL_REG
/*****               LOW-G DURATION                        ******/

#define BMA222_LOWG_DUR__POS                    0
#define BMA222_LOWG_DUR__LEN                    8
#define BMA222_LOWG_DUR__MSK                    0xFF
#define BMA222_LOWG_DUR__REG                    BMA222_LOW_DURN_REG

/*****               LOW-G THRESHOLD                       ******/

#define BMA222_LOWG_THRES__POS                  0
#define BMA222_LOWG_THRES__LEN                  8
#define BMA222_LOWG_THRES__MSK                  0xFF
#define BMA222_LOWG_THRES__REG                  BMA222_LOW_THRES_REG

/*****               LOW-G HYSTERESIS                       ******/

#define BMA222_LOWG_HYST__POS                   0
#define BMA222_LOWG_HYST__LEN                   2
#define BMA222_LOWG_HYST__MSK                   0x03
#define BMA222_LOWG_HYST__REG                   BMA222_LOW_HIGH_HYST_REG

/*****               LOW-G INTERRUPT MODE                   ******/
/*****       IF 1 -- SUM MODE , 0 -- SINGLE MODE            ******/
#define BMA222_LOWG_INT_MODE__POS               2
#define BMA222_LOWG_INT_MODE__LEN               1
#define BMA222_LOWG_INT_MODE__MSK               0x04
#define BMA222_LOWG_INT_MODE__REG               BMA222_LOW_HIGH_HYST_REG
/*****               HIGH-G DURATION                        ******/

#define BMA222_HIGHG_DUR__POS                    0
#define BMA222_HIGHG_DUR__LEN                    8
#define BMA222_HIGHG_DUR__MSK                    0xFF
#define BMA222_HIGHG_DUR__REG                    BMA222_HIGH_DURN_REG

/*****               HIGH-G THRESHOLD                       ******/

#define BMA222_HIGHG_THRES__POS                  0
#define BMA222_HIGHG_THRES__LEN                  8
#define BMA222_HIGHG_THRES__MSK                  0xFF
#define BMA222_HIGHG_THRES__REG                  BMA222_HIGH_THRES_REG


/*****               HIGH-G HYSTERESIS                       ******/

#define BMA222_HIGHG_HYST__POS                  6
#define BMA222_HIGHG_HYST__LEN                  2
#define BMA222_HIGHG_HYST__MSK                  0xC0
#define BMA222_HIGHG_HYST__REG                  BMA222_LOW_HIGH_HYST_REG
/*****               SLOPE DURATION                        ******/

#define BMA222_SLOPE_DUR__POS                    0
#define BMA222_SLOPE_DUR__LEN                    2
#define BMA222_SLOPE_DUR__MSK                    0x03
#define BMA222_SLOPE_DUR__REG                    BMA222_SLOPE_DURN_REG
/*****               SLOPE THRESHOLD                       ******/

#define BMA222_SLOPE_THRES__POS                  0
#define BMA222_SLOPE_THRES__LEN                  8
#define BMA222_SLOPE_THRES__MSK                  0xFF
#define BMA222_SLOPE_THRES__REG                  BMA222_SLOPE_THRES_REG
/*****               SLOW THRESHOLD                       ******/

#define BMA222_SLOW_THRES__POS                  0
#define BMA222_SLOW_THRES__LEN                  6
#define BMA222_SLOW_THRES__MSK                  0x3F
#define BMA222_SLOW_THRES__REG                  BMA222_SLOW_THRES_REG
/*****               SLOW DURATION                       ******/

#define BMA222_SLOW_DUR__POS                  6
#define BMA222_SLOW_DUR__LEN                  2
#define BMA222_SLOW_DUR__MSK                  0xC0
#define BMA222_SLOW_DUR__REG                  BMA222_SLOW_THRES_REG
/*****               TAP DURATION                        ******/

#define BMA222_TAP_DUR__POS                    0
#define BMA222_TAP_DUR__LEN                    3
#define BMA222_TAP_DUR__MSK                    0x07
#define BMA222_TAP_DUR__REG                    BMA222_TAP_PARAM_REG

/*****               TAP SHOCK DURATION                 ******/

#define BMA222_TAP_SHOCK_DURN__POS             6
#define BMA222_TAP_SHOCK_DURN__LEN             1
#define BMA222_TAP_SHOCK_DURN__MSK             0x40
#define BMA222_TAP_SHOCK_DURN__REG             BMA222_TAP_PARAM_REG

/*****               ADV TAP INT                        ******/

#define BMA222_ADV_TAP_INT__POS                5
#define BMA222_ADV_TAP_INT__LEN                1
#define BMA222_ADV_TAP_INT__MSK                0x20
#define BMA222_ADV_TAP_INT__REG                BMA222_TAP_PARAM_REG

/*****               TAP QUIET DURATION                 ******/

#define BMA222_TAP_QUIET_DURN__POS             7
#define BMA222_TAP_QUIET_DURN__LEN             1
#define BMA222_TAP_QUIET_DURN__MSK             0x80
#define BMA222_TAP_QUIET_DURN__REG             BMA222_TAP_PARAM_REG
/*****               TAP THRESHOLD                       ******/

#define BMA222_TAP_THRES__POS                  0
#define BMA222_TAP_THRES__LEN                  5
#define BMA222_TAP_THRES__MSK                  0x1F
#define BMA222_TAP_THRES__REG                  BMA222_TAP_THRES_REG

/*****               TAP SAMPLES                         ******/

#define BMA222_TAP_SAMPLES__POS                6
#define BMA222_TAP_SAMPLES__LEN                2
#define BMA222_TAP_SAMPLES__MSK                0xC0
#define BMA222_TAP_SAMPLES__REG                BMA222_TAP_THRES_REG
/*****       ORIENTATION MODE                        ******/

#define BMA222_ORIENT_MODE__POS                  0
#define BMA222_ORIENT_MODE__LEN                  2
#define BMA222_ORIENT_MODE__MSK                  0x03
#define BMA222_ORIENT_MODE__REG                  BMA222_ORIENT_PARAM_REG

/*****       ORIENTATION BLOCKING                    ******/

#define BMA222_ORIENT_BLOCK__POS                 2
#define BMA222_ORIENT_BLOCK__LEN                 2
#define BMA222_ORIENT_BLOCK__MSK                 0x0C
#define BMA222_ORIENT_BLOCK__REG                 BMA222_ORIENT_PARAM_REG

/*****       ORIENTATION HYSTERESIS                  ******/

#define BMA222_ORIENT_HYST__POS                  4
#define BMA222_ORIENT_HYST__LEN                  3
#define BMA222_ORIENT_HYST__MSK                  0x70
#define BMA222_ORIENT_HYST__REG                  BMA222_ORIENT_PARAM_REG
/*****       ORIENTATION AXIS SELECTION              ******/
/***** IF SET TO 1 -- X AND Z ARE SWAPPED , Y IS INVERTED */

#define BMA222_ORIENT_AXIS__POS                  7
#define BMA222_ORIENT_AXIS__LEN                  1
#define BMA222_ORIENT_AXIS__MSK                  0x80
#define BMA222_ORIENT_AXIS__REG                  BMA222_THETA_BLOCK_REG

/*****       THETA BLOCKING                    ******/

#define BMA222_THETA_BLOCK__POS                  0
#define BMA222_THETA_BLOCK__LEN                  6
#define BMA222_THETA_BLOCK__MSK                  0x3F
#define BMA222_THETA_BLOCK__REG                  BMA222_THETA_BLOCK_REG
/*****       THETA FLAT                        ******/

#define BMA222_THETA_FLAT__POS                  0
#define BMA222_THETA_FLAT__LEN                  6
#define BMA222_THETA_FLAT__MSK                  0x3F
#define BMA222_THETA_FLAT__REG                  BMA222_THETA_FLAT_REG
/*****      FLAT HOLD TIME                     ******/

#define BMA222_FLAT_HOLD_TIME__POS              4
#define BMA222_FLAT_HOLD_TIME__LEN              2
#define BMA222_FLAT_HOLD_TIME__MSK              0x30
#define BMA222_FLAT_HOLD_TIME__REG              BMA222_FLAT_HOLD_TIME_REG
/*****      FLAT HYS                           ******/

#define BMA222_FLAT_HYS__POS                   0
#define BMA222_FLAT_HYS__LEN                   3
#define BMA222_FLAT_HYS__MSK                   0x07
#define BMA222_FLAT_HYS__REG                   BMA222_FLAT_HOLD_TIME_REG
/*****      LOW POWER MODE -STATUS             ******/

#define BMA222_LOW_POWER_MODE_S__POS            0
#define BMA222_LOW_POWER_MODE_S__LEN            1
#define BMA222_LOW_POWER_MODE_S__MSK            0x01
#define BMA222_LOW_POWER_MODE_S__REG            BMA222_STATUS_LOW_POWER_REG
/*****      ACTIVATE SELF TEST                 ******/

#define BMA222_EN_SELF_TEST__POS                0
#define BMA222_EN_SELF_TEST__LEN                2
#define BMA222_EN_SELF_TEST__MSK                0x03
#define BMA222_EN_SELF_TEST__REG                BMA222_SELF_TEST_REG

/*****     SELF TEST -- NEGATIVE               ******/

#define BMA222_NEG_SELF_TEST__POS               2
#define BMA222_NEG_SELF_TEST__LEN               1
#define BMA222_NEG_SELF_TEST__MSK               0x04
#define BMA222_NEG_SELF_TEST__REG               BMA222_SELF_TEST_REG

/*****     SELF TEST AMPLITUDE                 ******/

#define BMA222_SELF_TEST_AMP__POS               4
#define BMA222_SELF_TEST_AMP__LEN               3
#define BMA222_SELF_TEST_AMP__MSK               0x70
#define BMA222_SELF_TEST_AMP__REG               BMA222_SELF_TEST_REG
/*****     EEPROM CONTROL                      ******/

/* SETTING THIS BIT  UNLOCK'S WRITING SETTING REGISTERS TO EEPROM */

#define BMA222_UNLOCK_EE_PROG_MODE__POS     0
#define BMA222_UNLOCK_EE_PROG_MODE__LEN     1
#define BMA222_UNLOCK_EE_PROG_MODE__MSK     0x01
#define BMA222_UNLOCK_EE_PROG_MODE__REG     BMA222_EEPROM_CTRL_REG


/* SETTING THIS BIT STARTS WRITING SETTING REGISTERS TO EEPROM */

#define BMA222_START_EE_PROG_TRIG__POS      1
#define BMA222_START_EE_PROG_TRIG__LEN      1
#define BMA222_START_EE_PROG_TRIG__MSK      0x02
#define BMA222_START_EE_PROG_TRIG__REG      BMA222_EEPROM_CTRL_REG


/* STATUS OF WRITING TO EEPROM */

#define BMA222_EE_PROG_READY__POS          2
#define BMA222_EE_PROG_READY__LEN          1
#define BMA222_EE_PROG_READY__MSK          0x04
#define BMA222_EE_PROG_READY__REG          BMA222_EEPROM_CTRL_REG


/* UPDATE IMAGE REGISTERS WRITING TO EEPROM */

#define BMA222_UPDATE_IMAGE__POS                3
#define BMA222_UPDATE_IMAGE__LEN                1
#define BMA222_UPDATE_IMAGE__MSK                0x08
#define BMA222_UPDATE_IMAGE__REG                BMA222_EEPROM_CTRL_REG
/* SPI INTERFACE MODE SELECTION */

#define BMA222_EN_SPI_MODE_3__POS              0
#define BMA222_EN_SPI_MODE_3__LEN              1
#define BMA222_EN_SPI_MODE_3__MSK              0x01
#define BMA222_EN_SPI_MODE_3__REG              BMA222_SERIAL_CTRL_REG

/* I2C WATCHDOG PERIOD SELECTION */

#define BMA222_I2C_WATCHDOG_PERIOD__POS        1
#define BMA222_I2C_WATCHDOG_PERIOD__LEN        1
#define BMA222_I2C_WATCHDOG_PERIOD__MSK        0x02
#define BMA222_I2C_WATCHDOG_PERIOD__REG        BMA222_SERIAL_CTRL_REG

/* I2C WATCHDOG SELECTION */

#define BMA222_EN_I2C_WATCHDOG__POS            2
#define BMA222_EN_I2C_WATCHDOG__LEN            1
#define BMA222_EN_I2C_WATCHDOG__MSK            0x04
#define BMA222_EN_I2C_WATCHDOG__REG            BMA222_SERIAL_CTRL_REG
/* SETTING THIS BIT  UNLOCK'S WRITING TRIMMING REGISTERS TO EEPROM */

#define BMA222_UNLOCK_EE_WRITE_TRIM__POS        4
#define BMA222_UNLOCK_EE_WRITE_TRIM__LEN        4
#define BMA222_UNLOCK_EE_WRITE_TRIM__MSK        0xF0
#define BMA222_UNLOCK_EE_WRITE_TRIM__REG        BMA222_CTRL_UNLOCK_REG
/**    OFFSET  COMPENSATION     **/

/**    SLOW COMPENSATION FOR X,Y,Z AXIS      **/

#define BMA222_EN_SLOW_COMP_X__POS              0
#define BMA222_EN_SLOW_COMP_X__LEN              1
#define BMA222_EN_SLOW_COMP_X__MSK              0x01
#define BMA222_EN_SLOW_COMP_X__REG              BMA222_OFFSET_CTRL_REG

#define BMA222_EN_SLOW_COMP_Y__POS              1
#define BMA222_EN_SLOW_COMP_Y__LEN              1
#define BMA222_EN_SLOW_COMP_Y__MSK              0x02
#define BMA222_EN_SLOW_COMP_Y__REG              BMA222_OFFSET_CTRL_REG

#define BMA222_EN_SLOW_COMP_Z__POS              2
#define BMA222_EN_SLOW_COMP_Z__LEN              1
#define BMA222_EN_SLOW_COMP_Z__MSK              0x04
#define BMA222_EN_SLOW_COMP_Z__REG              BMA222_OFFSET_CTRL_REG

/**    FAST COMPENSATION READY FLAG          **/

#define BMA222_FAST_COMP_RDY_S__POS             4
#define BMA222_FAST_COMP_RDY_S__LEN             1
#define BMA222_FAST_COMP_RDY_S__MSK             0x10
#define BMA222_FAST_COMP_RDY_S__REG             BMA222_OFFSET_CTRL_REG

/**    FAST COMPENSATION FOR X,Y,Z AXIS      **/

#define BMA222_EN_FAST_COMP__POS                5
#define BMA222_EN_FAST_COMP__LEN                2
#define BMA222_EN_FAST_COMP__MSK                0x60
#define BMA222_EN_FAST_COMP__REG                BMA222_OFFSET_CTRL_REG

/**    RESET OFFSET REGISTERS                **/

#define BMA222_RESET_OFFSET_REGS__POS           7
#define BMA222_RESET_OFFSET_REGS__LEN           1
#define BMA222_RESET_OFFSET_REGS__MSK           0x80
#define BMA222_RESET_OFFSET_REGS__REG           BMA222_OFFSET_CTRL_REG
/**     SLOW COMPENSATION  CUTOFF               **/

#define BMA222_COMP_CUTOFF__POS                 0
#define BMA222_COMP_CUTOFF__LEN                 1
#define BMA222_COMP_CUTOFF__MSK                 0x01
#define BMA222_COMP_CUTOFF__REG                 BMA222_OFFSET_PARAMS_REG

/**     COMPENSATION TARGET                  **/

#define BMA222_COMP_TARGET_OFFSET_X__POS        1
#define BMA222_COMP_TARGET_OFFSET_X__LEN        2
#define BMA222_COMP_TARGET_OFFSET_X__MSK        0x06
#define BMA222_COMP_TARGET_OFFSET_X__REG        BMA222_OFFSET_PARAMS_REG

#define BMA222_COMP_TARGET_OFFSET_Y__POS        3
#define BMA222_COMP_TARGET_OFFSET_Y__LEN        2
#define BMA222_COMP_TARGET_OFFSET_Y__MSK        0x18
#define BMA222_COMP_TARGET_OFFSET_Y__REG        BMA222_OFFSET_PARAMS_REG

#define BMA222_COMP_TARGET_OFFSET_Z__POS        5
#define BMA222_COMP_TARGET_OFFSET_Z__LEN        2
#define BMA222_COMP_TARGET_OFFSET_Z__MSK        0x60
#define BMA222_COMP_TARGET_OFFSET_Z__REG        BMA222_OFFSET_PARAMS_REG

#define BMA222_TRIM_ADC_BITWIDTH__POS       6
#define BMA222_TRIM_ADC_BITWIDTH__LEN       2
#define BMA222_TRIM_ADC_BITWIDTH__MSK       0xC0
#define BMA222_TRIM_ADC_BITWIDTH__REG       BMA222_TRIM_ADC_REG
#define BMA222_GET_BITSLICE(regvar, bitname)\
                        (regvar & bitname##__MSK) >> bitname##__POS


#define BMA222_SET_BITSLICE(regvar, bitname, val)\
                  (regvar & ~bitname##__MSK) | ((val<<bitname##__POS)&bitname##__MSK)


/** \endcond */

/* SETTING THIS BIT  UNLOCK'S WRITING SETTING REGISTERS TO EEPROM */

#define BMA222_UNLOCK_EE_WRITE_SETTING__POS     0
#define BMA222_UNLOCK_EE_WRITE_SETTING__LEN     1
#define BMA222_UNLOCK_EE_WRITE_SETTING__MSK     0x01
#define BMA222_UNLOCK_EE_WRITE_SETTING__REG     BMA222_EEPROM_CTRL_REG


/* SETTING THIS BIT STARTS WRITING SETTING REGISTERS TO EEPROM */

#define BMA222_START_EE_WRITE_SETTING__POS      1
#define BMA222_START_EE_WRITE_SETTING__LEN      1
#define BMA222_START_EE_WRITE_SETTING__MSK      0x02
#define BMA222_START_EE_WRITE_SETTING__REG      BMA222_EEPROM_CTRL_REG

/* STATUS OF WRITING TO EEPROM */

#define BMA222_EE_WRITE_SETTING_S__POS          2
#define BMA222_EE_WRITE_SETTING_S__LEN          1
#define BMA222_EE_WRITE_SETTING_S__MSK          0x04
#define BMA222_EE_WRITE_SETTING_S__REG          BMA222_EEPROM_CTRL_REG

/* CONSTANTS */


/* range and bandwidth */

#define BMA222_RANGE_2G                 0 /**< sets range to +/- 2G mode \see BMA222_set_range() */
#define BMA222_RANGE_4G                 1 /**< sets range to +/- 4G mode \see BMA222_set_range() */
#define BMA222_RANGE_8G                 2 /**< sets range to +/- 8G mode \see BMA222_set_range() */
#define BMA222_RANGE_16G                3 /**< sets range to +/- 16G mode \see BMA222_set_range() */


#define BMA222_BW_7_81HZ        0x08       /**< sets bandwidth to LowPass 7.81  HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_15_63HZ       0x09       /**< sets bandwidth to LowPass 15.63 HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_31_25HZ       0x0A       /**< sets bandwidth to LowPass 31.25 HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_62_50HZ       0x0B       /**< sets bandwidth to LowPass 62.50 HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_125HZ         0x0C       /**< sets bandwidth to LowPass 125HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_250HZ         0x0D       /**< sets bandwidth to LowPass 250HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_500HZ         0x0E       /**< sets bandwidth to LowPass 500HZ \see BMA222_set_bandwidth() */
#define BMA222_BW_1000HZ        0x0F       /**< sets bandwidth to LowPass 1000HZ \see BMA222_set_bandwidth() */

/* mode settings */

#define BMA222_MODE_NORMAL      0
#define BMA222_MODE_LOWPOWER    1
#define BMA222_MODE_SUSPEND     2

/* wake up */

#define BMA222_WAKE_UP_DUR_20MS         0
#define BMA222_WAKE_UP_DUR_80MS         1
#define BMA222_WAKE_UP_DUR_320MS                2
#define BMA222_WAKE_UP_DUR_2560MS               3


/* LG/HG thresholds are in LSB and depend on RANGE setting */
/* no range check on threshold calculation */

#define BMA222_SELF_TEST0_ON            1
#define BMA222_SELF_TEST1_ON            2

#define BMA222_EE_W_OFF                 0
#define BMA222_EE_W_ON                  1
/** Macro to convert floating point low-g-thresholds in G to 8-bit register values.<br>
  * Example: BMA222_LOW_TH_IN_G( 0.3, 2.0) generates the register value for 0.3G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA222_LOW_TH_IN_G( gthres, range)                      ((256 * gthres ) / range)

/** Macro to convert floating point high-g-thresholds in G to 8-bit register values.<br>
  * Example: BMA222_HIGH_TH_IN_G( 1.4, 2.0) generates the register value for 1.4G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA222_HIGH_TH_IN_G(gthres, range)                              ((256 * gthres ) / range)

/** Macro to convert floating point low-g-hysteresis in G to 8-bit register values.<br>
  * Example: BMA222_LOW_HY_IN_G( 0.2, 2.0) generates the register value for 0.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA222_LOW_HY_IN_G( ghyst, range )                              ((32 * ghyst) / range)

/** Macro to convert floating point high-g-hysteresis in G to 8-bit register values.<br>
  * Example: BMA222_HIGH_HY_IN_G( 0.2, 2.0) generates the register value for 0.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA222_HIGH_HY_IN_G( ghyst, range )                             ((32 * ghyst) / range)


/** Macro to convert floating point G-thresholds to 8-bit register values<br>
  * Example: BMA222_SLOPE_TH_IN_G( 1.2, 2.0) generates the register value for 1.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */

#define BMA222_SLOPE_TH_IN_G( gthres, range)    ((128 * gthres ) / range)
/*user defined Enums*/
//Example..
//enum {
//E_YOURDATA1, /**< <DOXY Comment for E_YOURDATA1> */
//E_YOURDATA2  /**< <DOXY Comment for E_YOURDATA2> */
//};
//Example...
//struct DUMMY_STRUCT {
//data1, /**< <DOXY Comment for data1> */
//data2  /**< <DOXY Comment for data1> */
//};
int bma222_soft_reset(void);
int bma222_init(bma222_t *bma222, int bma222_i2c_slave_addr) ; // [HSS] Support both address ( 0X18(old) and 0X08(new) ) (2010.09.29)
int bma222_set_MEMS(unsigned char CMB381 , unsigned char Noise_level );
int bma222_set_LowNoise (unsigned char Noise_Mode)         ;
int bma222_set_package_sel(unsigned char stacked_assy )  ;
unsigned char bma222_set_mode(unsigned char Mode);
int bma222_get_mode(unsigned char * Mode );
int bma222_set_range(unsigned char Range);
int bma222_get_range(unsigned char * Range );
int bma222_set_bandwidth(unsigned char bw);
int bma222_get_bandwidth(unsigned char * bw);
int bma222_write_reg(unsigned char addr, unsigned char *data, unsigned char len);
int bma222_read_reg(unsigned char addr, unsigned char *data, unsigned char len);
int bma222_reset_interrupt(void);
int bma222_read_accel_xyz(bma222acc_t * acc);
int bma222_read_accel_x(short *a_x);
int bma222_read_accel_y(short *a_y);
int bma222_read_accel_z(short *a_z);
int bma222_soft_reset(void) ;
int bma222_get_interrupt_status(unsigned char * status);
int bma222_set_Int_Mode(unsigned char mode );
int bma222_update_image(void);
int bma222_get_image(bma222regs_t *bma222Image);
int bma222_set_image(bma222regs_t *bma222Image);
int bma222_set_Int_Enable( unsigned char InterruptType , unsigned char value );
int bma222_get_nvmprog_ready(unsigned char *ready);
int bma222_set_nvmprog_mode(unsigned char prgmode);
int bma222_set_nvprog_trig(unsigned char trig);
int bma222_set_EnterExtMode(void);
int bma222_set_EnterExtMode(void);
int bma222_set_ExitExtMode(void);
int bma222_set_resolution(unsigned char bitresolution);
int bma222_set_resolution(unsigned char bitresolution);
int bma222_get_resolution(unsigned char *bitresolution );
int bma222_set_offset_target_x(unsigned char offsettarget);
/* EasyCASE ) */
/* EasyCASE ( 1175
   bma222_get_offset_target_x */
int bma222_get_offset_target_x(unsigned char *offsettarget );
/* EasyCASE ) */
/* EasyCASE ( 1179
   bma222_set_offset_target_y */
int bma222_set_offset_target_y(unsigned char offsettarget);
/* EasyCASE ) */
/* EasyCASE ( 1183
   bma222_get_offset_target_y */
int bma222_get_offset_target_y(unsigned char *offsettarget );
/* EasyCASE ) */
/* EasyCASE ( 1185
   bma222_set_offset_target_z */
int bma222_set_offset_target_z(unsigned char offsettarget);
/* EasyCASE ) */
/* EasyCASE ( 1187
   bma222_get_offset_target_z */
int bma222_get_offset_target_z(unsigned char *offsettarget );
/* EasyCASE ) */
/* EasyCASE ( 1189
   bma222_set_offset_filt_x */
int bma222_set_offset_filt_x(unsigned char offsetfilt);
/* EasyCASE ) */
/* EasyCASE ( 1191
   bma222_get_offset_filt_x */
int bma222_get_offset_filt_x(unsigned char *offsetfilt );
/* EasyCASE ) */
/* EasyCASE ( 1195
   bma222_set_offset_filt_y */
int bma222_set_offset_filt_y(unsigned char offsetfilt);
/* EasyCASE ) */
/* EasyCASE ( 1197
   bma222_get_offset_filt_y */
int bma222_get_offset_filt_y(unsigned char *offsetfilt );
/* EasyCASE ) */
/* EasyCASE ( 1199
   bma222_set_offset_filt_z */
int bma222_set_offset_filt_z(unsigned char offsetfilt);
/* EasyCASE ) */
/* EasyCASE ( 1201
   bma222_get_offset_filt_z */
int bma222_get_offset_filt_z(unsigned char *offsetfilt );
int bma222_set_ee_w(unsigned char eew);
int bma222_set_ee_prog_trig(void);
int bma222_get_eeprom_writing_status(unsigned char *eewrite );
int bma222_get_cal_ready(unsigned char *calrdy );
int bma222_set_cal_trigger(unsigned char caltrigger);
#endif
