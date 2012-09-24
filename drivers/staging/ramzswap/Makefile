KERNEL_BUILD_PATH ?= "/home/dhiika/kernel-cyanogen-gio/"

XVM = sub-projects/allocators/xvmalloc-kmod
EXTRA_CFLAGS	:=	-DCONFIG_RAMZSWAP_STATS		\
			-Wall

obj-m		+=	ramzswap.o
ramzswap-objs	:=	ramzswap_drv.o $(XVM)/xvmalloc.o

all:
	make -C $(KERNEL_BUILD_PATH) M=$(PWD) modules
	make -C sub-projects/rzscontrol

doc:
	make -C sub-projects/rzscontrol doc

clean:
	make -C $(KERNEL_BUILD_PATH) M=$(PWD) clean
	make -C sub-projects/rzscontrol clean
	@rm -rf *.ko
