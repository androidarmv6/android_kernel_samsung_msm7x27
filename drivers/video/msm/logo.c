/* drivers/video/msm/logo.c
 *
 * Show Logo in RLE 565 format
 *
 * Copyright (C) 2008 Google Incorporated
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
#include <linux/types.h>
#include <linux/fb.h>
#include <linux/vt_kern.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>

#include <linux/irq.h>
#include <asm/system.h>

#define fb_width(fb)	((fb)->var.xres)
#define fb_height(fb)	((fb)->var.yres)
#define fb_size(fb)	((fb)->var.xres * (fb)->var.yres * 2)

static void memset16(void *_ptr, unsigned short val, unsigned count)
{
	unsigned short *ptr = _ptr;
	count >>= 1;
	while (count--)
		*ptr++ = val;
}

/* convert RGB565 to RBG8888 */
static void memset16_rgb8888(void *_ptr, unsigned short val, unsigned count)
{
	unsigned short *ptr = _ptr;
	unsigned short red; 
	unsigned short green;
	unsigned short blue;
#if defined(CONFIG_MACH_TASS_CHN_CU) || defined(CONFIG_MACH_COOPER_CHN_CU)
	blue = (val & 0xF800) >> 8;
	red = ( val & 0x7E0) >> 3;
	green = (val & 0x1F) << 3;
#else
	red = ( val & 0xF800) >> 8;
	green = (val & 0x7E0) >> 3;
	blue = (val & 0x1F) << 3;
#endif
	count >>= 1;
	while (count--)
	{
		*ptr++ = (red<<8) | green;
		*ptr++ = blue;
	}
}

/* 565RLE image format: [count(2 bytes), rle(2 bytes)] */
#ifdef CONFIG_FB_MSM_SEC_BOOTLOGO
int load_565rle_image_onfb( char *filename, int start_x, int start_y)
{
	int fd, err = 0;
	unsigned count, max;
	unsigned short *data, *bits, *ptr;
	struct fb_info *info;
#if defined(CONFIG_MACH_CALLISTO) || defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_LUCAS)
	unsigned short *p_line; // minhyo0512
	unsigned short sp, c_pixel; // minhyo0512
	unsigned draw_pixel;
#endif
	
	info = registered_fb[0];
	
	if (!info) {
		printk(KERN_WARNING "%s: Can not access framebuffer\n",
			__func__);
		return -ENODEV;
	}

	fd = sys_open(filename, O_RDONLY, 0);
	if (fd < 0) {
		printk(KERN_WARNING "%s: Can not open %s\n",
			__func__, filename);
		return -ENOENT;
	}
	count = (unsigned)sys_lseek(fd, (off_t)0, 2);
	if (count == 0) {
		sys_close(fd);
		err = -EIO;
		goto err_logo_close_file;
	}
	sys_lseek(fd, (off_t)0, 0);
	data = kmalloc(count, GFP_KERNEL);
	if (!data) {
		printk(KERN_WARNING "%s: Can not alloc data\n", __func__);
		err = -ENOMEM;
		goto err_logo_close_file;
	}
	if ((unsigned)sys_read(fd, (char *)data, count) != count) {
		err = -EIO;
		goto err_logo_free_data;
	}

	max = fb_width(info) * fb_height(info);


	ptr = data;
	bits = (unsigned short *)(info->screen_base+(info->fix.line_length*start_y) );
//	printk("====minhyodebug:info->fix.line_length=%d, \n", info->fix.line_length);
//	printk("====minhyodebug:max=fb_wid x fb_height : %d x %d = %d\n", fb_width(info), fb_height(info), max);

#if defined(CONFIG_MACH_CALLISTO) || defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS)
	p_line = bits;
	sp = 0; // start pixel in Line
	while (count > 3) {
		unsigned n = ptr[0];  // pixel count

		if (n > max)
			break;
		draw_pixel = n;
		while(draw_pixel > 0)
		{
#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)
		if(sp == 320) // 20100909 hongkuk.son for COOPER.rle ( booting logo )
#elif defined(CONFIG_MACH_CALLISTO) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS)
			if(sp == 240)
#endif
			{
				// move next-line
                p_line += (info->fix.line_length / 2);
				sp = 0;
			}

#if defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO)			
			if( (sp + draw_pixel) >= 320) // 20100909 hongkuk.son for COOPER.rle ( booting logo )
				c_pixel = 320 - sp; // 20100909 hongkuk.son for COOPER.rle ( booting logo )
#elif defined(CONFIG_MACH_CALLISTO) || defined(CONFIG_MACH_BENI) || defined(CONFIG_MACH_TASS)
			if( (sp + draw_pixel) >= 240)
				c_pixel = 240 - sp;
#endif
			else
				c_pixel = draw_pixel;

			// draw pixels
           #if 1 // minhyo-rgb888
		memset16_rgb8888(&p_line[sp*2], ptr[1], c_pixel<<1);
           #else
           memset16(&p_line[sp], ptr[1], c_pixel<<1);
           #endif
			
			draw_pixel -= c_pixel; // decrease drawed-pixel-count
			sp += c_pixel;
		}
		
		max -= n;
		ptr += 2;
		count -= 4;
	}
#elif defined(CONFIG_MACH_LUCAS)
	p_line = bits;
	sp = 0; // start pixel in Line
	while (count > 3) {
		unsigned n = ptr[0];  // pixel count

		if (n > max)
			break;
		draw_pixel = n;
		while(draw_pixel > 0)
		{
			if(sp == 320)
			{
				// move next-line
                p_line += (info->fix.line_length / 2);
				sp = 0;
			}
			
			if( (sp + draw_pixel) >= 320)
				c_pixel = 320 - sp;
			else
				c_pixel = draw_pixel;

			// draw pixels
           #if 1 // minhyo-rgb888
		memset16_rgb8888(&p_line[sp*2], ptr[1], c_pixel<<1);
           #else
           memset16(&p_line[sp], ptr[1], c_pixel<<1);
           #endif
			
			draw_pixel -= c_pixel; // decrease drawed-pixel-count
			sp += c_pixel;
		}
		
		max -= n;
		ptr += 2;
		count -= 4;
	}	
#else
	if (info->node == 1 || info->node == 2) {
		err = -EPERM;
		pr_err("%s:%d no info->creen_base on fb%d!\n",
		       __func__, __LINE__, info->node);
		goto err_logo_free_data;
	}
	bits = (unsigned short *)(info->screen_base);
	while (count > 3) {
		unsigned n = ptr[0];
		if (n > max)
			break;
		/* blank space - if one image, this can be removed */
		if ( n >= 352 )
			bits += 130 * (info->fix.line_length) / 2;
		/* blank space - end */

		memset16_rgb8888(bits, ptr[1], n << 1);
		bits += n*2; // for rgb8888
		max -= n;
		ptr += 2;
		count -= 4;
	}
#endif

err_logo_free_data:
	kfree(data);
err_logo_close_file:
	sys_close(fd);
	return err;
}
#endif

/* 565RLE image format: [count(2 bytes), rle(2 bytes)] */
int load_565rle_image(char *filename)
{
	struct fb_info *info;
	int fd, count, err = 0;
	unsigned max;
	unsigned short *data, *bits, *ptr;

	info = registered_fb[0];
	if (!info) {
		printk(KERN_WARNING "%s: Can not access framebuffer\n",
			__func__);
		return -ENODEV;
	}

	fd = sys_open(filename, O_RDONLY, 0);
	if (fd < 0) {
		printk(KERN_WARNING "%s: Can not open %s\n",
			__func__, filename);
		return -ENOENT;
	}
	count = sys_lseek(fd, (off_t)0, 2);
	if (count <= 0) {
		err = -EIO;
		goto err_logo_close_file;
	}
	sys_lseek(fd, (off_t)0, 0);
	data = kmalloc(count, GFP_KERNEL);
	if (!data) {
		printk(KERN_WARNING "%s: Can not alloc data\n", __func__);
		err = -ENOMEM;
		goto err_logo_close_file;
	}
	if (sys_read(fd, (char *)data, count) != count) {
		err = -EIO;
		goto err_logo_free_data;
	}

	max = fb_width(info) * fb_height(info);
	ptr = data;
	bits = (unsigned short *)(info->screen_base);
	while (count > 3) {
		unsigned n = ptr[0];
		if (n > max)
			break;
		memset16(bits, ptr[1], n << 1);
		bits += n;
		max -= n;
		ptr += 2;
		count -= 4;
	}

err_logo_free_data:
	kfree(data);
err_logo_close_file:
	sys_close(fd);
	return err;
}
EXPORT_SYMBOL(load_565rle_image);
