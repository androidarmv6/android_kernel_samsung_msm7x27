#ifndef __DEV_IOCTL_TS_MELFAS_H__
#define __DEV_IOCTL_TS_MELFAS_H__
#ifndef _ASM_GENERIC_IOCTL_H
#define _ASM_GENERIC_IOCTL_H

/* ioctl command encoding: 32 bits total, command in lower 16 bits,
 * size of the parameter structure in the lower 14 bits of the
 * upper 16 bits.
 * Encoding the size of the parameter structure in the ioctl request
 * is useful for catching programs compiled with old versions
 * and to avoid overwriting user space outside the user buffer area.
 * The highest 2 bits are reserved for indicating the ``access mode''.
 * NOTE: This limits the max parameter size to 16kB -1 !
 */

/*
 * The following is for compatibility across the various Linux
 * platforms.  The generic ioctl numbering scheme doesn't really enforce
 * a type field.  De facto, however, the top 8 bits of the lower 16
 * bits are indeed used as a type field, so we might just as well make
 * this explicit here.  Please be sure to use the decoding macros
 * below from now on.
 */
#define _IOC_NRBITS	8
#define _IOC_TYPEBITS	8

/*
 * Let any architecture override either of the following before
 * including this file.
 */

#ifndef _IOC_SIZEBITS
# define _IOC_SIZEBITS	14
#endif

#ifndef _IOC_DIRBITS
# define _IOC_DIRBITS	2
#endif

#define _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIRMASK	((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT	0
#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

/*
 * Direction bits, which any architecture can choose to override
 * before including this file.
 */

#ifndef _IOC_NONE
#define _IOC_NONE	0U
#endif

#ifndef _IOC_WRITE
#define _IOC_WRITE	1U
#endif

#ifndef _IOC_READ
#define _IOC_READ	2U
#endif

#define _IOC(dir,type,nr,size) \
	(((dir)  << _IOC_DIRSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr)   << _IOC_NRSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))

#ifdef __KERNEL__
/* provoke compile error for invalid uses of size argument */
extern unsigned int __invalid_size_argument_for_IOC;
#define _IOC_TYPECHECK(t) \
	((sizeof(t) == sizeof(t[1]) && \
	  sizeof(t) < (1 << _IOC_SIZEBITS)) ? \
	  sizeof(t) : __invalid_size_argument_for_IOC)
#else
#define _IOC_TYPECHECK(t) (sizeof(t))
#endif

/* used to create numbers */
#define _IO(type,nr)		_IOC(_IOC_NONE,(type),(nr),0)
#define _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOWR(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOR_BAD(type,nr,size)	_IOC(_IOC_READ,(type),(nr),sizeof(size))
#define _IOW_BAD(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),sizeof(size))
#define _IOWR_BAD(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))

/* used to decode ioctl numbers.. */
#define _IOC_DIR(nr)		(((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#define _IOC_TYPE(nr)		(((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NR(nr)		(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

/* ...and for the drivers/sound files... */

#define IOC_IN		(_IOC_WRITE << _IOC_DIRSHIFT)
#define IOC_OUT		(_IOC_READ << _IOC_DIRSHIFT)
#define IOC_INOUT	((_IOC_WRITE|_IOC_READ) << _IOC_DIRSHIFT)
#define IOCSIZE_MASK	(_IOC_SIZEMASK << _IOC_SIZESHIFT)
#define IOCSIZE_SHIFT	(_IOC_SIZESHIFT)

#endif /* _ASM_GENERIC_IOCTL_H */

#ifndef NULL
#define NULL				0
#endif

typedef struct {
	int count;
	unsigned char addr;
	unsigned char pData[256];
}__attribute__((packed)) TsI2CData;

#define DEV_IOCTL_TS_MAGIC	'X'

#define CMD_SET_DATA_STRONG		0		
#define CMD_SET_DATA_READ			1
#define CMD_SET_DATA_HIGH			2
#define CMD_SET_DATA_LOW			3
#define CMD_SET_PWR_ON			4
#define CMD_SET_PWR_OFF			5
#define CMD_SET_PWR_STRONG		6
#define CMD_SET_CLK_STRONG		7
#define CMD_SET_CLK_READ			8
#define CMD_SET_CLK_HIGH			9
#define CMD_SET_CLK_LOW			10
#define CMD_CHECK_DATA_BIT		11
#define CMD_CHECK_CLK_BIT			12
#define CMD_I2C_SEND				13
#define CMD_SET_INT_EN				14
#define CMD_SET_INT_DIS			15
#define CMD_TEST_UP				16
#define CMD_TEST_DOWN				17
#define CMD_RST_UP					18
#define CMD_RST_DOWN				19
#define CMD_RST_READ				20
#define CMD_RST_STRONG				21
#define CMD_ISSP_SET				22
#define CMD_ISSP_CLR				23

#define DEV_CTRL_TOUCH_DAT_OUT		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_DATA_STRONG)
#define DEV_CTRL_TOUCH_DAT_IN		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_DATA_READ)
#define DEV_CTRL_TOUCH_DAT_HIGH	_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_DATA_HIGH)
#define DEV_CTRL_TOUCH_DAT_LOW	_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_DATA_LOW)
#define DEV_CTRL_TOUCH_PWR_ON		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_PWR_ON)
#define DEV_CTRL_TOUCH_PWR_OFF		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_PWR_OFF)
#define DEV_CTRL_TOUCH_PWR_OUT		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_PWR_STRONG)
#define DEV_CTRL_TOUCH_CLK_OUT		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_CLK_STRONG)
#define DEV_CTRL_TOUCH_CLK_IN		_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_CLK_READ)
#define DEV_CTRL_TOUCH_CLK_HIGH	_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_CLK_HIGH)
#define DEV_CTRL_TOUCH_CLK_LOW	_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_CLK_LOW)
#define DEV_CTRL_TOUCH_I2C_WRITE	_IOWR(DEV_IOCTL_TS_MAGIC, CMD_I2C_SEND, TsI2CData)
#define DEV_CTRL_TOUCH_DAT_CHK	_IO(DEV_IOCTL_TS_MAGIC, CMD_CHECK_DATA_BIT)
#define DEV_CTRL_TOUCH_CLK_CHK	_IO(DEV_IOCTL_TS_MAGIC, CMD_CHECK_CLK_BIT)
#define DEV_CTRL_TOUCH_INT_ENABLE	_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_INT_EN) 
#define DEV_CTRL_TOUCH_INT_DISABLE	_IO(DEV_IOCTL_TS_MAGIC, CMD_SET_INT_DIS) 
#define DEV_CTRL_TOUCH_TEST_UP	_IO(DEV_IOCTL_TS_MAGIC, CMD_TEST_UP) 
#define DEV_CTRL_TOUCH_TEST_DOWN	_IO(DEV_IOCTL_TS_MAGIC, CMD_TEST_DOWN) 
#define DEV_CTRL_TOUCH_RST_HIGH	_IO(DEV_IOCTL_TS_MAGIC, CMD_RST_UP) 
#define DEV_CTRL_TOUCH_RST_LOW	_IO(DEV_IOCTL_TS_MAGIC, CMD_RST_DOWN) 
#define DEV_CTRL_TOUCH_RST_IN	_IO(DEV_IOCTL_TS_MAGIC, CMD_RST_READ) 
#define DEV_CTRL_TOUCH_RST_OUT	_IO(DEV_IOCTL_TS_MAGIC, CMD_RST_STRONG) 
#define DEV_CTRL_TOUCH_SET_FLAG		_IO(DEV_IOCTL_TS_MAGIC, CMD_ISSP_SET) 
#define DEV_CTRL_TOUCH_CLR_FLAG		_IO(DEV_IOCTL_TS_MAGIC, CMD_ISSP_CLR) 
#define DEV_CTRL_TOUCH_MAX_NR		24

#if 1
typedef struct {
	unsigned char gid;
	unsigned char gcnt;
	unsigned char	sx;
	unsigned char sy;
	unsigned char cx;
	unsigned char cy;
	unsigned char ver;
}__attribute__((packed)) TsRawData;
#endif

#if 0
typedef struct {
	unsigned short x;
	unsigned short y;
	unsigned short z;
	unsigned short width;
	unsigned char pointType;
}__attribute__((packed)) TsRawData;
#endif

#endif /* __DEV_IOCTL_TS_MELFAS_H__ */
