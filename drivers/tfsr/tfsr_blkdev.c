/*
 *---------------------------------------------------------------------------*
 *                                                                           *
 * Copyright (C) 2003-2010 Samsung Electronics                               *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License version 2 as         *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
*/
/**
 * @version	LinuStoreIII_1.2.0_b036-FSR_1.2.1p1_b139_RTM
 * @file        drivers/tfsr/tfsr_blkdev.c
 * @brief       This file is BML I/O part which supports linux kernel 2.6
 *              It provides (un)registering block device, request function
 *
*/

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
#include <linux/platform_device.h>
#else
#include <linux/device.h>
#endif

#include "tfsr_base.h"

#define DEVICE_NAME             "tfsr"
#define MAJOR_NR                BLK_DEVICE_TINY_FSR

/**
 * list to keep track of each created block devices
 */
static DECLARE_MUTEX(bml_list_mutex);
static LIST_HEAD(bml_list);

#ifdef CONFIG_PM
#include <linux/pm.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
int (*bml_module_suspend)(struct platform_device *pdev, pm_message_t state);
int (*bml_module_resume)(struct platform_device *pdev);
#else
int (*bml_module_suspend)(struct device *dev, u32 state, u32 level);
int (*bml_module_resume)(struct device *dev, u32 level);
#endif

EXPORT_SYMBOL(bml_module_suspend);
EXPORT_SYMBOL(bml_module_resume);

#endif /* end of CONFIG_PM */

/**
 * transger data from BML to buffer cache
 * @param volume        : device number
 * @param partno        : 0~15: partition, other: whole device
 * @param req           : request description
 * @return              1 on success, 0 on failure
 *
 * It will erase a block before it do write the data
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
static int bml_transfer(u32 volume, u32 partno, const struct request *req, u32 data_len)
#else
static int bml_transfer(u32 volume, u32 partno, const struct request *req)
#endif
{
	unsigned long sector, nsect;
	char *buf;
	FSRVolSpec *vs;
	FSRPartI *ps;
	u32 nPgsPerUnit = 0, n1stVpn = 0, spp_shift, spp_mask;
	int ret;
	
	DEBUG(DL3,"TINY[I]: volume(%d), partno(%d)\n", volume, partno);

	if (!blk_fs_request(req))
	{
		return 0;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	sector = blk_rq_pos(req);
	nsect = data_len >> 9;
#else
	sector = req->sector;
	nsect = req->current_nr_sectors;
#endif
	buf = req->buffer;
	
	vs = fsr_get_vol_spec(volume);
	ps = fsr_get_part_spec(volume);
	spp_shift = ffs(vs->nSctsPerPg) - 1;
	spp_mask = vs->nSctsPerPg - 1;
	
	if(!fsr_is_whole_dev(partno))
	{
		if (FSR_BML_GetVirUnitInfo(volume, 
			fsr_part_start(ps, partno), &n1stVpn, &nPgsPerUnit) 
				!= FSR_BML_SUCCESS)
		{
			ERRPRINTK("FSR_BML_GetVirUnitInfo FAIL\n");
			return -EIO;
		}
	}

	switch (rq_data_dir(req)) 
	{
		case READ:
			/*
			 * If sector and nsect are aligned with vs->nSctsPerPg,
			 * you have to use a FSR_BML_Read() function using page unit,
			 * If not, use a FSR_BML_ReadScts() function using sector unit.
			 */
			if ((!(sector & spp_mask) && !(nsect & spp_mask))) 
			{
				ret = FSR_BML_Read(volume, n1stVpn + (sector >> spp_shift),
						nsect >> spp_shift, buf, NULL, FSR_BML_FLAG_ECC_ON);
			} 
			else 
			{
				ret = FSR_BML_ReadScts(volume, n1stVpn + (sector >> spp_shift),
						sector & spp_mask, nsect, buf, NULL, FSR_BML_FLAG_ECC_ON);
			}
			break;
		default:
			ERRPRINTK("Unknown request 0x%x\n", (u32) rq_data_dir(req));
			return -EINVAL;
	}

	/* I/O error */
	if (ret != FSR_BML_SUCCESS) 
	{
		ERRPRINTK("TINY: transfer error = %X\n", ret);
		return -EIO;
	}
	
	DEBUG(DL3,"TINY[O]: volume(%d), partno(%d)\n", volume, partno);

	return 1;
}

/**
 * request function which is do read/write sector
 * @param rq    : request queue which is created by blk_init_queue()
 * @return              none
 */
static void bml_request(struct request_queue *rq)
{
	u32 minor, volume, partno, spp_mask;
	struct request *req;
	struct fsr_dev *dev;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 25)
	int ret;
#endif
	int trans_ret;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	int error = 0;
	u32 len = 0;
#endif

	FSRVolSpec *vs;

	DEBUG(DL3,"TINY[I]\n");

	dev = rq->queuedata;
	if (dev->req)
		return;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	while ((dev->req = req = blk_peek_request(rq)) != NULL)
#else
	while ((dev->req = req = elv_next_request(rq)) != NULL) 
#endif
	{
		spin_unlock_irq(rq->queue_lock);
		
		minor = dev->gd->first_minor;
		volume = fsr_vol(minor);
		partno = fsr_part(minor);
		vs = fsr_get_vol_spec(volume);
		spp_mask = vs->nSctsPerPg - 1;
		
		DEBUG(DL3,"TINY[I]: volume(%d), partno(%d)\n", volume, partno);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
		len = blk_rq_cur_bytes(req);
		if (!( blk_rq_pos(req) & spp_mask) && ( blk_rq_cur_sectors(req) != blk_rq_sectors(req)))
		{
			blk_rq_map_sg(rq, req, dev->sg);
			if (!((dev->sg->length >> SECTOR_BITS) & 0x7))
			{
				len = dev->sg->length;
			}
			if (len > blk_rq_bytes(req))
			{
				len = blk_rq_bytes(req);
			}

		}
		trans_ret = bml_transfer(volume, partno, req, len);
#else
		if (!(req->sector & spp_mask) && (req->current_nr_sectors != req->nr_sectors))
		{
			blk_rq_map_sg(rq, req, dev->sg);
			if (!((dev->sg->length >> SECTOR_BITS) & 0x7))
			{
				req->current_nr_sectors = dev->sg->length >> SECTOR_BITS;
			}
			if (req->current_nr_sectors > req->nr_sectors)
			{
				req->current_nr_sectors = req->nr_sectors;
			}
		}
		trans_ret = bml_transfer(volume, partno, req);
#endif
		
		spin_lock_irq(rq->queue_lock);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
		if (trans_ret)
		{
			error = 0;
		} else
		{
			error = -EIO;
		}
		/* don't need to check if request is finished */
		if (blk_rq_sectors(req) <= (len >> 9))
			list_del_init(&req->queuelist);
		__blk_end_request(req, error, len);

#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 25)
		req->hard_cur_sectors = req->current_nr_sectors;
		end_request(req, trans_ret);
#else	
		ret = end_that_request_chunk(req, trans_ret, req->current_nr_sectors << SECTOR_BITS);
		if (!ret)
		{
			add_disk_randomness(req->rq_disk);
			blkdev_dequeue_request(req);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 16)
			end_that_request_last(req, trans_ret);
#else
			end_that_request_last(req);
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 16) */
		}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 25) */

		DEBUG(DL3,"TINY[O]: volume(%d), partno(%d)\n", volume, partno);
	}

	DEBUG(DL3,"TINY[O]\n");
}

/**
 * add each partitions as disk
 * @param volume        a volume number
 * @param partno        a partition number
 * @return              0 on success, otherwise on error
 *
 */
static int bml_add_disk(u32 volume, u32 partno)
{
	u32 minor, sectors;
	struct fsr_dev *dev;
	FSRPartI *pi;
	
	DEBUG(DL3,"TINY[I]: volume(%d), partno(%d)\n", volume, partno);

	dev = kmalloc(sizeof(struct fsr_dev), GFP_KERNEL);
	/* memory error */
	if (!dev)
	{
		return -ENOMEM;
	}
	memset(dev, 0, sizeof(struct fsr_dev));
	
	spin_lock_init(&dev->lock);
	INIT_LIST_HEAD(&dev->list);
	down(&bml_list_mutex);
	list_add(&dev->list, &bml_list);
	up(&bml_list_mutex);
	
	/* init queue */
	dev->queue = blk_init_queue(bml_request, &dev->lock);
	dev->queue->queuedata = dev;
	dev->req = NULL;

	/* alloc scatterlist */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	dev->sg = kmalloc(sizeof(struct scatterlist) * dev->queue->limits.max_phys_segments, GFP_KERNEL);
#else
	dev->sg = kmalloc(sizeof(struct scatterlist) * dev->queue->max_phys_segments, GFP_KERNEL);
#endif
	if (!dev->sg)
	{
		kfree(dev);
		return -ENOMEM;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	memset(dev->sg, 0, sizeof(struct scatterlist) * dev->queue->limits.max_phys_segments);
#else
	memset(dev->sg, 0, sizeof(struct scatterlist) * dev->queue->max_phys_segments);
#endif

	/* Each partition is a physical disk which has one partition */
	dev->gd = alloc_disk(1);
	/* memory error */
	if (!dev->gd) 
	{
		kfree(dev->sg);
		list_del(&dev->list);
		kfree(dev);
		ERRPRINTK("No gendisk in DEV\r\n");
		return -ENOMEM;
	}
	
	minor = fsr_minor(volume, partno);
	
	dev->gd->major = MAJOR_NR;
	dev->gd->first_minor = minor;
	dev->gd->fops = bml_get_block_device_operations();
	dev->gd->queue = dev->queue;
	
	pi = fsr_get_part_spec(volume);
	
	/* check minor number whether it is used for chip */
	if (minor & PARTITION_MASK) 
	{
		/* partition */
		snprintf(dev->gd->disk_name, 32, "%s%d", DEVICE_NAME, minor);
		sectors = (fsr_part_units_nr(pi, partno) *
		                fsr_vol_unitsize(volume, partno)) >> 9;
	} 
	else 
	{
		/* chip */
		snprintf(dev->gd->disk_name, 32, "%s%d/%c", DEVICE_NAME,
		                        minor >> PARTITION_BITS, 'c');
		sectors = fsr_vol_sectors_nr(volume);
	}
	
	/* setup block device parameter array */
	set_capacity(dev->gd, sectors);
	
	add_disk(dev->gd);
	
	DEBUG(DL3,"TINY[O]: volume(%d), partno(%d)\n", volume, partno);

	return 0;
}

/**
 * free all disk structure
 * @param *dev  fsr block device structure (ref. inlcude/linux/fsr/fsr_if.h)
 * @return      none
 *
 */
static void bml_del_disk(struct fsr_dev *dev)
{
	DEBUG(DL3,"TINY[I]\n");

	if (dev->gd) 
	{
		del_gendisk(dev->gd);
		put_disk(dev->gd);
	}

	kfree(dev->sg);

	if (dev->queue)
	{
		blk_cleanup_queue(dev->queue);
	}
	list_del(&dev->list);
	kfree(dev);

	DEBUG(DL3,"TINY[O]\n");
}

/**
 * bml_blkdev_create - create device node
 * @return              none
 */
static int bml_blkdev_create(void)
{
	u32 volume, partno, i;
	FSRPartI *pi;
	unsigned int nparts;
	int ret;
	
	DEBUG(DL3,"TINY[I]\n");

	for (volume = 0; volume < FSR_MAX_VOLUMES; volume++) 
	{
		ret = FSR_BML_Open(volume, FSR_BML_FLAG_NONE);
		
		if (ret != FSR_BML_SUCCESS) 
		{
			ERRPRINTK("No such device or address, %d(0x%x)", volume, ret);
			continue;
		}
		ret = fsr_update_vol_spec(volume);
		if (ret) 
		{
			ERRPRINTK("fsr_update_vol_spec FAIL\r\n");
			FSR_BML_Close(volume, FSR_BML_FLAG_NONE);
			continue;
		}
		pi = fsr_get_part_spec(volume);
		nparts = fsr_parts_nr(pi);
		/*
		 * which is better auto or static?
		 */
		for (i = 0; i < MAX_FLASH_PARTITIONS + 1; i++) 
		{
			/* when partno has -1, it means whole device */
			partno = i - 1;
			/* there is no partition */
			if (i > nparts)
			{
				break;
			}
			
			ret = bml_add_disk(volume, partno);
			if (ret)
			{
				ERRPRINTK("bml_add_disk Fail : %d\r\n", ret);
				continue;
			}
		}
	}
	
	DEBUG(DL3,"TINY[O]\n");

	return 0;
}

/**
 * free resource
 * @return              none
 * @remark bml_blkdev is the build-in code, so it will be never reached
 */
static void bml_blkdev_free(void)
{
	struct fsr_dev *dev;
	struct list_head *this, *next;
	
	down(&bml_list_mutex);
	list_for_each_safe(this, next, &bml_list) 
	{
		dev = list_entry(this, struct fsr_dev, list);
		bml_del_disk(dev);
	}
	up(&bml_list_mutex);
}

/**
 * suspend the bml devices
 * @param dev           device structure
 * @param state         device power management state
 * @return              0 on success
 */
#ifdef CONFIG_PM
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
static int tfsr_suspend(struct platform_device *pdev, pm_message_t state)
#else
static int tfsr_suspend(struct device *dev, u32 state, u32 level)
#endif
{
	int ret = 0;

	if (NULL != bml_module_suspend) 
	{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
		ret = bml_module_suspend(NULL,((struct pm_message){ .event = 0, }));
#else
		ret = bml_module_suspend(NULL, 0, 0);
#endif
		if (ret)
			ERRPRINTK("TinyFSR: bml_module_suspend fail\n");
	} 

	return ret;
}

/**
 * resume the bml devices
 * @param dev           device structure
 * @return              0 on success
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
static int tfsr_resume(struct platform_device *pdev)
#else
static int tfsr_resume(struct device *dev, u32 level)
#endif
{
	int ret = 0;

	DEBUG(DL3,"TINY[I]\n");

	if (NULL != bml_module_resume) 
	{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
		ret = bml_module_resume(NULL);
#else
		ret = bml_module_resume(NULL, 0);
#endif
		if (ret)
			ERRPRINTK("TinyFSR: bml_module_resume fail\n");
	} 

	DEBUG(DL3,"TINY[I]\n");

	return ret;
}

#endif /* end of CONFIG_PM */

/**
 * initialize bml driver structure
 * After linux 2.6.15 version, 
 * platform driver uses and checks struct platform_driver for suspend/resume
 * and platform_driver_register can register struct platform_driver to platform driver.
 * 
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
static struct platform_driver tfsr_driver = {
	.driver = {
		.name		= DEVICE_NAME,
		.owner		= THIS_MODULE,
	},
#ifdef CONFIG_PM
	.suspend	= tfsr_suspend,
	.resume		= tfsr_resume,
#endif
};
#else
static struct device_driver tfsr_driver = {
	.name		= DEVICE_NAME,
	.bus		= &platform_bus_type,
#ifdef CONFIG_PM
	.suspend	= tfsr_suspend,
	.resume		= tfsr_resume,
#endif
};
#endif

/**
 * initialize bml device structure
 */
static struct platform_device tfsr_device = {
	.name	= DEVICE_NAME,
};

/**
 * create device node, it will scan every chips and partitions
 * @return      0 on success, otherwise on error
 */
int __init bml_blkdev_init(void)
{
	DEBUG(DL3,"TINY[I]\n");

#ifdef CONFIG_PM
#endif

	if (register_blkdev(MAJOR_NR, DEVICE_NAME)) 
	{
		ERRPRINTK("TiyFSR: unable to get major %d\n", MAJOR_NR);
		return -EAGAIN;
	}
	
	if (bml_blkdev_create()) 
	{
		unregister_blkdev(MAJOR_NR, DEVICE_NAME);
		ERRPRINTK("TiyFSR: Can't created bml_blkdev_create()\n");
		return -ENOMEM;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
        if (platform_driver_register(&tfsr_driver)) {
#else	
	if (driver_register(&tfsr_driver)) {
#endif
		ERRPRINTK("TinyFSR: Can't register driver(major:%d)\n", MAJOR_NR);
		bml_blkdev_free();
		unregister_blkdev(MAJOR_NR, DEVICE_NAME);
		return -ENODEV;
	}

	if (platform_device_register(&tfsr_device)) {
		ERRPRINTK("TinyFSR: Can't register platform device(major:%d)\n", MAJOR_NR);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
                platform_driver_unregister(&tfsr_driver);
#else
		driver_unregister(&tfsr_driver);
#endif
		bml_blkdev_free();
		unregister_blkdev(MAJOR_NR, DEVICE_NAME);
		return -ENODEV;
	}

	DEBUG(DL3,"TINY[O]\n");

	return 0;
}

/**
 * initialize the bml devices
 * @return              0 on success, otherwise on failure
 */
void __exit bml_blkdev_exit(void)
{

	int ret;
	unsigned int volume;

	for (volume = 0; volume < FSR_MAX_VOLUMES; volume++)
	{
		ret = FSR_BML_Close(volume, FSR_BML_FLAG_NONE);
		if (ret != FSR_BML_SUCCESS)
		{
			DEBUG(DL0,"Volume(%d) has not opened.\n", volume);
		}
	}

	platform_device_unregister(&tfsr_device);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 15)
        platform_driver_unregister(&tfsr_driver);
#else
	driver_unregister(&tfsr_driver);
#endif
	bml_blkdev_free();
	unregister_blkdev(MAJOR_NR, DEVICE_NAME);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samsung Electronics");
MODULE_DESCRIPTION("The kernel 2.6 block device interface for BML");
