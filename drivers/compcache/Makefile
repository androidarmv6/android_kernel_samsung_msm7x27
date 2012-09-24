#KERNELDIR ?= "/lib/modules/$(shell uname -r)/build"

XVM = sub-projects/allocators/xvmalloc-kmod
LZO = sub-projects/compression/lzo-kmod
EXTRA_CFLAGS	:=	-Wall

obj-m		+=	zram.o
zram-objs	:=	zram_drv.o zram_sysfs.o $(XVM)/xvmalloc.o $(LZO)/lzo1x_compress.o $(LZO)/lzo1x_decompress.o

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	@rm -rf *.ko