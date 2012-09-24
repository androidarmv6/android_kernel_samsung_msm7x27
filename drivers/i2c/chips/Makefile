#
# Makefile for miscellaneous I2C chip drivers.
#
# Do not add new drivers to this directory! It is DEPRECATED.
#
# Device drivers are better grouped according to the functionality they
# implement rather than to the bus they are connected to. In particular:
# * Hardware monitoring chip drivers go to drivers/hwmon
# * RTC chip drivers go to drivers/rtc
# * I/O expander drivers go to drivers/gpio
#

obj-$(CONFIG_SENSORS_MT9T013)	+= mt9t013.o
obj-$(CONFIG_AMP_MAX97000) 	+= max97000.o
obj-$(CONFIG_FSA9280) 	+= fsa9280.o
obj-$(CONFIG_SENSORS_BMA_ACCEL)	+= bma023_dev.o bma_accel_driver.o bma222.o
obj-$(CONFIG_SENSORS_MMC31XX)	+= mmc31xx.o
obj-$(CONFIG_ECOMPASS)		+= mecs.o
obj-$(CONFIG_SENSORS_KR3D_ACCEL)	+= kr3dm_accel_driver.o 
obj-$(CONFIG_SENSORS_TAOS)	+= taos.o
obj-$(CONFIG_SENSORS_GP2A)	+= gp2a.o 

ifeq ($(CONFIG_I2C_DEBUG_CHIP),y)
EXTRA_CFLAGS += -DDEBUG
endif

