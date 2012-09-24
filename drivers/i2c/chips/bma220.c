/*
 * This software program is licensed subject to the GNU General Public License
 * (GPL).Version 2,June 1991, available at http://www.fsf.org/copyleft/gpl.html

 * (C) Copyright 2010 Bosch Sensortec GmbH
 * All Rights Reserved
 */



/*! \file bma220.c
    \brief This file contains all function implementations for the BMA220 API
    
    Details.
*/

#include <linux/i2c/bma220.h>


bma220_t *p_bma220;				/**< pointer to BMA220 device structure  */


/** API Initialization routine
	\param *bma220 pointer to BMA220 structured type
	\return result of communication routines 
 */
int bma220_init(bma220_t *bma220) 
{
	int comres=0;

	p_bma220 = bma220;								/* assign bma220 ptr */
	if (!p_bma220->dev_addr)
	p_bma220->dev_addr = BMA220_I2C_ADDR;			/* preset BMA220 I2C_addr */
	p_bma220->mode = 0;
	bma220_get_chip_id(&(p_bma220->chip_id));
	p_bma220->interface = 0;
	return comres;
}

/** Get chip ID
	\param *chip_id
	\return result of communication routines 
*/
int bma220_get_chip_id(unsigned char *chip_id) 
{
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CHIP_ID__REG, chip_id, 1 );
	return comres;
}

/* Range configuration

*/

/** Set range
	\param range 0=2g, 1=4g, 2=8g, 3=16g
	\return result of communication routines 
*/
int bma220_set_range(unsigned char range)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_RANGE__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_RANGE, range);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_RANGE__REG, &data, 1);
	return comres;
}

/** Get range
	\param *range 0=2g, 1=4g, 2=8g, 3=16g.
	\return result of communication routines 
*/
int bma220_get_range(unsigned char *range)
{
	unsigned char data;
	int comres = 0;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_RANGE__REG, &data, 1 );
	*range = BMA220_GET_BITSLICE(data, BMA220_RANGE);
	return comres;
}


/* Bandwidth configuration

*/

/** Set Bandwidth (SC_FILT_CONFIG)
	\param bw 0=1kHz, 1=600hz, 2=250Hz, 3=150Hz, 4=75Hz, 5=50Hz.
	\return result of communication routines 
*/
int bma220_set_bandwidth(char bw) 
{
    return bma220_set_sc_filt_config(bw);
}

/** Get Bandwidth (SC_FILT_CONFIG)
	\param *bw 0=1kHz, 1=600hz, 2=250Hz, 3=150Hz, 4=75Hz, 5=50Hz.
	\return result of communication routines 
*/
int bma220_get_bandwidth(unsigned char *bw)
{
	return bma220_get_sc_filt_config(bw);
}

/** Set SC_FILT_CONFIG
	\param sc_filt 0=1kHz, 1=600hz, 2=250Hz, 3=150Hz, 4=75Hz, 5=50Hz.
	\return result of communication routines 
*/
int bma220_set_sc_filt_config(char sc_filt) 
{
	int comres = 0;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	if (sc_filt<16)
	{
  	  comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SC_FILT_CONFIG__REG, &data, 1 );
	  data = BMA220_SET_BITSLICE(data, BMA220_SC_FILT_CONFIG, sc_filt);
	  comres += p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SC_FILT_CONFIG__REG, &data, 1 );
	}
    return comres;
}

/** Get SC_FILT_CONFIG
	\param *sc_filt 0=1kHz, 1=600hz, 2=250Hz, 3=150Hz, 4=75Hz, 5=50Hz.
	\return result of communication routines 
*/
int bma220_get_sc_filt_config(unsigned char *sc_filt)
{
	unsigned char data;
	int comres = 1;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SC_FILT_CONFIG__REG, &data, 1 );		
	*sc_filt = BMA220_GET_BITSLICE(data, BMA220_SC_FILT_CONFIG);
	return comres;
}

/* Mode configuration

*/

/** Set Mode
	\param mode 0=Normal Mode, 1=Sleep Mode, 2=Suspend Mode
	\return result of communication routines
*/
int bma220_set_mode(unsigned char mode) 
{
	int comres = 0;
	if (p_bma220==0) 
		return E_BMA_NULL_PTR;	
		
	if (mode == p_bma220->mode)
		return 0;	
	switch(p_bma220->mode) {
		case 0: if (mode==1)
					comres = bma220_set_sleep_en(1);
				else if (mode==2)
				    comres = bma220_set_suspend();
				break;
		case 1: comres = bma220_set_sleep_en(0);
				if (mode==2)
					comres |= bma220_set_suspend();
				break;
		case 2: comres = bma220_set_suspend();
				if (mode==1)
					comres |= bma220_set_sleep_en(1);
				break;
		default: comres = E_OUT_OF_RANGE;
				break;
	}
	p_bma220->mode = mode;			
	return comres;
}

/** Get mode
	\param *mode 0=Normal Mode, 1=Sleep Mode, 2=Suspend Mode
	\return 0
*/
int bma220_get_mode(unsigned char *mode) 
{
    if (p_bma220==0)
    	return E_BMA_NULL_PTR;

	*mode =  p_bma220->mode;
	return 0;
}

/** Set BMA220 to sleep mode via bus command
	\param sleep	0=disable sleep mode, 1=enable sleep mode
	\return result of communication routines
*/
int bma220_set_sleep_en(unsigned char sleep) 
{
	int comres;
	unsigned char data=0;
	if (p_bma220==0) 
		return E_BMA_NULL_PTR;	
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLEEP_EN__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SLEEP_EN, sleep);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SLEEP_EN__REG, &data, 1);
	return comres;
}

/** Get sleep_en
	\param *sleep	0= sleep mode disabled, 1= sleep mode enabled
	\return result of communication routines
*/
int bma220_get_sleep_en(unsigned char *sleep)
{
	unsigned char data;
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLEEP_EN__REG, &data, 1 );		
	*sleep = BMA220_GET_BITSLICE(data, BMA220_SLEEP_EN);
	return comres;
}

/** Set Sleep duration
	\param sleep_dur 0=2ms, 1=10ms, 2=25ms, 3=50ms, 4=100ms, 5=500ms, 6=1000ms, 7=2000ms.
	\return result of communication routines 
*/
int bma220_set_sleep_dur(unsigned char sleep_dur) 
{
	int comres = 0;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLEEP_DUR__REG, &data, 1 );
	data = BMA220_SET_BITSLICE(data, BMA220_SLEEP_DUR, sleep_dur);
	comres += p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SLEEP_DUR__REG, &data, 1 );
    return comres;
}

/** Get Sleep duration
	\param *sleep_dur 0=2ms, 1=10ms, 2=25ms, 3=50ms, 4=100ms, 5=500ms, 6=1000ms, 7=2000ms.
	\return result of communication routines 
*/  
int bma220_get_sleep_dur(unsigned char *sleep_dur)
{
	unsigned char data;
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLEEP_DUR__REG, &data, 1 );		
	*sleep_dur = BMA220_GET_BITSLICE(data, BMA220_SLEEP_DUR);
	return comres;
}	  

/** Set/reset suspend of BMA220
	\param none
	\return result of communication routines 
	\note calling this function will toggle between normal mode and suspend mode
*/
int bma220_set_suspend() 
{
	int comres;
	unsigned char data=0;
	if (p_bma220==0) 
		return E_BMA_NULL_PTR;

	/* read suspend to toggle between suspend and normal operation mode */
  	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SUSPEND__REG, &data,1);    
	return comres;
}


/* Configuration (other)

*/

/** Perform soft reset of BMA220 via bus command
	\param none
	\return result of communication routines 
*/
int bma220_soft_reset() 
{
	int comres;
	unsigned char data=0;
	if (p_bma220==0) 
		return E_BMA_NULL_PTR;

	/* read softreset twice for setting and releasing the reset */
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SOFTRESET__REG, &data,1);    
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SOFTRESET__REG, &data,1);   
	p_bma220->mode = 0; /* Required to reset mode to normal */
	return comres;
}

/** Set SPI3
	\param spi3 0=4 wire, 1=SPI 3 wire.
	\return result of communication routines 
*/
int bma220_set_spi3(unsigned char spi3)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SPI3__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SPI3, spi3);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SPI3__REG, &data, 1); 
	return comres;
}

/** Get SPI3
	\param *spi3 0=SPI 4 wire, 1=SPI 3 wire.
	\return result of communication routines 
*/
int bma220_get_spi3(unsigned char *spi3)
{
	unsigned char data;
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SPI3__REG, &data, 1 );		
	*spi3 = BMA220_GET_BITSLICE(data, BMA220_SPI3);
	return comres;
}

/** Set Watchdog I2C timeout config
	\param wdt_to 0,1=I2C watchdog is OFF, 2=I2C watchdog of 1ms, 3=I2C watchdog of 10ms.
	\return result of communication routines 
*/
int bma220_set_wdt_to_config(unsigned char wdt_to)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_WDT_TO__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_WDT_TO, wdt_to);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_WDT_TO__REG, &data, 1); 
	return comres;
}

/** Get Serial high Bandwidth
	\param *wdt_to 0,1=I2C watchdog is OFF, 2=I2C watchdog of 1ms, 3=I2C watchdog of 10ms.
	\return result of communication routines 
*/
int bma220_get_wdt_to_config(unsigned char *wdt_to)
{
	unsigned char data;
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_WDT_TO__REG, &data, 1 );		
	*wdt_to = BMA220_GET_BITSLICE(data, BMA220_WDT_TO);
	return comres;
}

/** Set Serial high Bandwidth
	\param serial_high_bw 0=disable, 1=enable.
	\return result of communication routines 
*/
int bma220_set_serial_high_bw(unsigned char serial_high_bw)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SERIAL_HIGH_BW__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SERIAL_HIGH_BW, serial_high_bw);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SERIAL_HIGH_BW__REG, &data, 1); 
	return comres;
}

/** Get Serial high Bandwidth
	\param *serial_high_bw 0=disable, 1=enable.
	\return result of communication routines 
*/
int bma220_get_serial_high_bw(unsigned char *serial_high_bw)
{
	unsigned char data;
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SERIAL_HIGH_BW__REG, &data, 1 );		
	*serial_high_bw = BMA220_GET_BITSLICE(data, BMA220_SERIAL_HIGH_BW);
	return comres;
}


/* Interrupt (other)

*/

/** Set reset interrupt 
	\param none
	\return result of communication routines
*/
int bma220_reset_int(void)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_RESET_INT__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_RESET_INT, 1);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_RESET_INT__REG, &data, 1); 
	return comres;
}

/** Set data ready interrupt
	\param en_data 0=disabled, 1=enabled
	\return result of communication routines
*/
int bma220_set_en_data(unsigned char en_data)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_DATA__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_EN_DATA, en_data);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_EN_DATA__REG, &data, 1); 
	return comres;
}

/** Get data ready interrupt
	\param *en_data 0=disabled, 1=enabled
	\return result of communication routines
*/
int bma220_get_en_data(unsigned char *en_data)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_DATA__REG, &data,1);
	*en_data = BMA220_GET_BITSLICE(data, BMA220_EN_DATA);	
	return comres;
}

/** Set Latch interrupt
	\param latch_int 0=OFF, 1=250ms, 2=500ms, 3=1000ms, 4=2000ms, 5=4000ms, 6=8000ms, 7=ON.
	\return result of communication routines
*/
int bma220_set_latch_int(unsigned char latch_int) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LATCH_INT__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_LATCH_INT , latch_int);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_LATCH_INT__REG, &data, 1); 
	return comres;
}

/** Get Latch interrupt
	\param *latch_int 0=OFF, 1=250ms, 2=500ms, 3=1000ms, 4=2000ms, 5=4000ms, 6=8000ms, 7=ON.
	\return result of communication routines
*/
int bma220_get_latch_int(unsigned char *latch_int) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SERIAL_HIGH_BW__REG, &data, 1 );		
	*latch_int = BMA220_GET_BITSLICE(data, BMA220_SERIAL_HIGH_BW);
	return comres;
}

int bma220_set_direction_interrupt_register(unsigned char data) 
{	
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	return p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_INT_ENABLE1_REG, &data, 1);
}

int bma220_set_interrupt_register(unsigned char int_enable2) 
{	
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_INT_ENABLE2_REG, &data, 1);
	data = data &0xF0;
	data = data | (int_enable2&0x0F);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_INT_ENABLE2_REG, &data, 1);
	return comres;
}

int bma220_get_direction_status_register(unsigned char *direction_status_reg)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_DIRECTION_STATUS_REG, &data, 1);
	*direction_status_reg = data;
	return comres;
}

int bma220_get_interrupt_status_register(unsigned char *interrupt_status_reg)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_INT_STATUS_REG, &data, 1);
	*interrupt_status_reg = data;
	return comres;
}


/** high g interrupt configuration 

*/

/** Set high g interrupt enable configuration (xyz)
	\param en_high_xyz 0=OFF, 1=z On, 2=y On, 3=z,y On, 4=x On, 5=z,y On, 6=y,x On, 7=z,y,x On.
	\return result of communication routines
*/
int bma220_set_en_high_xyz(unsigned char en_high_xyz)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_HIGH_XYZ__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_EN_HIGH_XYZ, en_high_xyz);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_EN_HIGH_XYZ__REG, &data, 1); 
	return comres;
}

/** Get high g interrupt enable configuration (xyz)
	\param *en_high_xyz 0=OFF, 1=z On, 2=y On, 3=z,y On, 4=x On, 5=z,y On, 6=y,x On, 7=z,y,x On.
	\return result of communication routines
*/
int bma220_get_en_high_xyz(unsigned char *en_high_xyz)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_HIGH_XYZ__REG, &data, 1);
	*en_high_xyz = BMA220_GET_BITSLICE(data, BMA220_EN_HIGH_XYZ);
	return comres;
}

/** Set high g interrupt threshold
	\param high_th in LSB
	\return result of communication routines
*/
int bma220_set_high_th(unsigned char high_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HIGH_TH__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_HIGH_TH, high_th);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_HIGH_TH__REG, &data, 1); 
	return comres;
}

/** Get high g interrupt threshold
	\param *high_th in LSB
	\return result of communication routines
*/
int bma220_get_high_th(unsigned char *high_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HIGH_TH__REG, &data, 1);
	*high_th = BMA220_GET_BITSLICE(data, BMA220_HIGH_TH);
	return comres;
}

/** Set high g interrupt hysteresis
	\param high_hy in LSB
	\return result of communication routines
*/
int bma220_set_high_hy(unsigned char high_hy)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HIGH_HY__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_HIGH_HY, high_hy);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_HIGH_HY__REG, &data, 1); 
	return comres;
}

/** Get high g interrupt hysteresis
	\param *high_hy in LSB
	\return result of communication routines
*/
int bma220_get_high_hy(unsigned char *high_hy)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HIGH_HY__REG, &data, 1);
	*high_hy = BMA220_GET_BITSLICE(data, BMA220_HIGH_HY);
	return comres;
}

/** Set high g interrupt duration
	\param high_dur duration in LSB
	\return result of communication routines
*/
int bma220_set_high_dur(unsigned char high_dur)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HIGH_DUR__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_HIGH_DUR, high_dur);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_HIGH_DUR__REG, &data, 1); 
	return comres;
}

/** Get high g interrupt duration
	\param *high_dur duration in LSB
	\return result of communication routines
*/
int bma220_get_high_g_dur(unsigned char *high_dur)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HIGH_DUR__REG, &data,1);
	*high_dur = BMA220_GET_BITSLICE(data, BMA220_HIGH_DUR);	
	return comres;
}


/** low g interrupt configuration 

*/

/** Set low g interrupt enable
	\param en_low 0=OFF, 1=ON.
	\return result of communication routines
*/
int bma220_set_en_low(unsigned char en_low)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_LOW__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_EN_LOW, en_low);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_EN_LOW__REG, &data, 1); 
	return comres;
}

/** Get low g interrupt enable
	\param *en_low 0=OFF, 1=ON.
	\return result of communication routines
*/
int bma220_get_en_low(unsigned char *en_low)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_LOW__REG, &data, 1);
	*en_low = BMA220_GET_BITSLICE(data, BMA220_EN_LOW);
	return comres;
}

/** Set low g interrupt threshold
	\param low_th in LSB.
	\return result of communication routines
*/
int bma220_set_low_th(unsigned char low_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LOW_TH__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_LOW_TH, low_th);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_LOW_TH__REG, &data, 1); 
	return comres;
}

/** Get low g interrupt threshold
	\param *low_th in LSB.
	\return result of communication routines
*/
int bma220_get_low_th(unsigned char *low_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LOW_TH__REG, &data, 1);
	*low_th = BMA220_GET_BITSLICE(data, BMA220_LOW_TH);
	return comres;
}

/** Set low g interrupt hysteresis
	\param low_th in LSB.
	\return result of communication routines
*/
int bma220_set_low_hy(unsigned char low_hy)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LOW_HY__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_LOW_HY, low_hy);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_LOW_HY__REG, &data, 1); 
	return comres;
}

/** Get low g interrupt hysteresis
	\param *low_hy in LSB.
	\return result of communication routines
*/
int bma220_get_low_hy(unsigned char *low_hy)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LOW_HY__REG, &data, 1);
	*low_hy = BMA220_GET_BITSLICE(data, BMA220_LOW_HY);
	return comres;
}

/** Set low g interrupt duration
	\param low_dur duration in LSB
	\return result of communication routines
*/
int bma220_set_low_dur(unsigned char low_dur)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LOW_DUR__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_LOW_DUR, low_dur);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_LOW_DUR__REG, &data, 1); 
	return comres;
}

/** Get low g interrupt duration
	\param *low_dur duration in LSB
	\return result of communication routines
*/
int bma220_get_low_g_dur(unsigned char *low_dur)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_LOW_DUR__REG, &data,1);
	*low_dur = BMA220_GET_BITSLICE(data, BMA220_LOW_DUR);	
	return comres;
}


/** Orientation configuration 

*/

/** Set en_orient
	\param en_orient 0=Disable orientation, 1=Enable orientation
	\return result of communication routines
*/
int bma220_set_en_orient(unsigned char en_orient)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_ORIENT__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_EN_ORIENT, en_orient);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_EN_ORIENT__REG, &data, 1); 
	return comres;
}

int bma220_get_orient_int(unsigned char *orient_int) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ORIENT__REG, &data, 1);
	*orient_int = BMA220_GET_BITSLICE(data, BMA220_ORIENT_INT);
	return comres;
}
/** Get en_orient 
	\param en_orient 0=orientation disabled, 1=orientation enabled
	\return result of communication routines
*/
int bma220_get_en_orient(unsigned char *en_orient) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_ORIENT__REG, &data, 1);
	*en_orient = BMA220_GET_BITSLICE(data, BMA220_EN_ORIENT);
	return comres;
}

/** Set orient_ex
	\param orient_ex
	\return result of communication routines
*/
int bma220_set_orient_ex(unsigned char orient_ex)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ORIENT_EX__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_ORIENT_EX, orient_ex);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_ORIENT_EX__REG, &data, 1); 
	return comres;
}

/** Get orient_ex 
	\param orient_ex
	\return result of communication routines
*/
int bma220_get_orient_ex(unsigned char *orient_ex) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ORIENT_EX__REG, &data, 1);
	*orient_ex = BMA220_GET_BITSLICE(data, BMA220_ORIENT_EX);
	return comres;
}

/** Set orient_blocking
	\param orient_block
	\return result of communication routines
*/
int bma220_set_orient_blocking(unsigned char orient_block)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ORIENT_BLOCKING__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_ORIENT_BLOCKING, orient_block);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_ORIENT_BLOCKING__REG, &data, 1); 
	return comres;
}

/** Get orient_blocking 
	\param *orient_block
	\return result of communication routines
*/
int bma220_get_orient_blocking(unsigned char *orient_block)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ORIENT_BLOCKING__REG, &data, 1);
	*orient_block = BMA220_GET_BITSLICE(data, BMA220_ORIENT_BLOCKING);
	return comres;
}

/** Get bma220 orientation value 
	\param orient returns 3 bit value X00 X01 X10 X11 with X=0 for face up, X=1 for face down
	\return result of communication routines
*/
int bma220_get_orientation(unsigned char *orient) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ORIENT__REG, &data, 1);
	*orient = BMA220_GET_BITSLICE(data, BMA220_ORIENT);
	return comres;
}


/** Tap Sensing configuration 

*/

/** Set Tap Sensing interrupt enable configuration (xyz)
	\param en_tt_xyz 0=OFF, 1=z On, 2=y On, 3=z,y On, 4=x On, 5=z,y On, 6=y,x On, 7=z,y,x On.
	\return result of communication routines
*/
int bma220_set_en_tt_xyz(unsigned char en_tt_xyz)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_TT_XYZ__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_EN_TT_XYZ, en_tt_xyz);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_EN_TT_XYZ__REG, &data, 1); 
	return comres;
}

/** Get Tap Sensing interrupt enable configuration (xyz)
	\param *en_tt_xyz 0=OFF, 1=z On, 2=y On, 3=z,y On, 4=x On, 5=z,y On, 6=y,x On, 7=z,y,x On.
	\return result of communication routines
*/
int bma220_get_en_tt_xyz(unsigned char *en_tt_xyz)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_TT_XYZ__REG, &data, 1);
	*en_tt_xyz = BMA220_GET_BITSLICE(data, BMA220_EN_TT_XYZ);
	return comres;
}

/** Set Tap Sensing threshold
	\param tt_th in LSB.
	\return result of communication routines
*/
int bma220_set_tt_th(unsigned char tt_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_TH__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_TT_TH, tt_th);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_TT_TH__REG, &data, 1); 
	return comres;
}

/** Get Tap Sensing threshold
	\param *tt_th in LSB.
	\return result of communication routines
*/
int bma220_get_tt_th(unsigned char *tt_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_TH__REG, &data, 1);
	*tt_th = BMA220_GET_BITSLICE(data, BMA220_TT_TH);
	return comres;
}

/** Set Tap Sensing duration
	\param tt_dur duration in LSB
	\return result of communication routines
*/
int bma220_set_tt_dur(unsigned char tt_dur)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_DUR__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_TT_DUR, tt_dur);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_TT_DUR__REG, &data, 1); 
	return comres;
}

/** Get Tap Sensing duration
	\param *tt_dur duration in LSB
	\return result of communication routines
*/
int bma220_get_tt_dur(unsigned char *tt_dur)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_DUR__REG, &data,1);
	*tt_dur = BMA220_GET_BITSLICE(data, BMA220_TT_DUR);	
	return comres;
}

/** Set Tap Sensing filt
	\param tt_filt 0=disabled, 1=enabled
	\return result of communication routines
*/
int bma220_set_tt_filt(unsigned char tt_filt)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_FILT__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_TT_FILT, tt_filt);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_TT_FILT__REG, &data, 1); 
	return comres;
}

/** Get Tap Sensing filt
	\param *tt_filt 0=disabled, 1=enabled
	\return result of communication routines
*/
int bma220_get_tt_filt(unsigned char *tt_filt)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_FILT__REG, &data,1);
	*tt_filt = BMA220_GET_BITSLICE(data, BMA220_TT_FILT);	
	return comres;
}

/** Set Tap Sensing tt_samp
	\param tt_samp
	\return result of communication routines
*/
int bma220_set_tt_samp(unsigned char tt_samp)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_SAMP__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_TT_SAMP, tt_samp);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_TT_SAMP__REG, &data, 1); 
	return comres;
}

/** Get Tap Sensing tt_samp
	\param *tt_samp
	\return result of communication routines
*/
int bma220_get_tt_samp(unsigned char *tt_samp)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TT_SAMP__REG, &data,1);
	*tt_samp = BMA220_GET_BITSLICE(data, BMA220_TT_SAMP);	
	return comres;
}

/** Set Tap Sensing tip_en
	\param tip_en 0=Double tap interrupt selected, 1=Single tap interrupt enabled
	\return result of communication routines
*/
int bma220_set_tip_en(unsigned char tip_en)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TIP_EN__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_TIP_EN, tip_en);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_TIP_EN__REG, &data, 1); 
	return comres;
}

/** Get Tap Sensing tip_en
	\param *tip_en 0=Double tap interrupt selected, 1=Single tap interrupt enabled
	\return result of communication routines
*/
int bma220_get_tip_en(unsigned char *tip_en)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_TIP_EN__REG, &data,1);
	*tip_en = BMA220_GET_BITSLICE(data, BMA220_TIP_EN);	
	return comres;
}


/** Slope interrupt configuration
	
*/

/** Set slope interrupt enable configuration (xyz)
	\param en_slope_xyz 0=OFF, 1=z On, 2=y On, 3=z,y On, 4=x On, 5=z,y On, 6=y,x On, 7=z,y,x On.
	\return result of communication routines
*/
int bma220_set_en_slope_xyz(unsigned char en_slope_xyz)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_SLOPE_XYZ__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_EN_SLOPE_XYZ, en_slope_xyz);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_EN_SLOPE_XYZ__REG, &data, 1); 
	return comres;
}

/** Get slope interrupt enable configuration (xyz)
	\param *en_slope_xyz 0=OFF, 1=z On, 2=y On, 3=z,y On, 4=x On, 5=z,y On, 6=y,x On, 7=z,y,x On.
	\return result of communication routines
*/
int bma220_get_en_slope_xyz(unsigned char *en_slope_xyz)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_EN_SLOPE_XYZ__REG, &data, 1);
	*en_slope_xyz = BMA220_GET_BITSLICE(data, BMA220_EN_SLOPE_XYZ);
	return comres;
}

/** Set slope threshold
	\param slope_th in LSB.
	\return result of communication routines
*/
int bma220_set_slope_th(unsigned char slope_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLOPE_TH__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SLOPE_TH, slope_th);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SLOPE_TH__REG, &data, 1); 
	return comres;
}

/** Get slope threshold
	\param *slope_th in LSB.
	\return result of communication routines
*/
int bma220_get_slope_th(unsigned char *slope_th)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLOPE_TH__REG, &data, 1);
	*slope_th = BMA220_GET_BITSLICE(data, BMA220_SLOPE_TH);
	return comres;
}

/** Set slope duration
	\param low_dur duration in LSB
	\return result of communication routines
*/
int bma220_set_slope_dur(unsigned char slope_dur)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLOPE_DUR__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SLOPE_DUR, slope_dur);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SLOPE_DUR__REG, &data, 1); 
	return comres;
}

/** Get slope duration
	\param *slope_dur duration in LSB
	\return result of communication routines
*/
int bma220_get_slope_dur(unsigned char *slope_dur)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLOPE_DUR__REG, &data,1);
	*slope_dur = BMA220_GET_BITSLICE(data, BMA220_SLOPE_DUR);	
	return comres;
}

/** Set slope filt
	\param slope_filt 0=disabled, 1=enabled
	\return result of communication routines
*/
int bma220_set_slope_filt(unsigned char slope_filt)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLOPE_FILT__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SLOPE_FILT, slope_filt);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SLOPE_FILT__REG, &data, 1);
	return comres;
}


/** Get slope filt
	\param *slope_filt 0=disabled, 1=enabled
	\return result of communication routines
*/
int bma220_get_slope_filt(unsigned char *slope_filt)
{
	int comres;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SLOPE_FILT__REG, &data,1);
	*slope_filt = BMA220_GET_BITSLICE(data, BMA220_SLOPE_FILT);	
	return comres;
}


/* Selftest configuration

*/

/** Set sbist(off,x,y,z) Enable/Disable selftest 
	\param sbist 0=off, 1=x axis, 2=y axis, 3=z axis.
	\return result of communication routines 
*/
int bma220_set_sbist(unsigned char sbist)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SBIST__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SBIST, sbist);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SBIST__REG, &data, 1); 
	return comres;
}

/** Get sbist selftest 
	\param *sbist 0=off, 1=x axis, 2=y axis, 3=z axis.
	\return result of communication routines 
*/
int bma220_get_sbist(unsigned char *sbist)
{
	unsigned char data;
	int comres = 0;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SBIST__REG,&data, 1 );
	*sbist = BMA220_GET_BITSLICE(data, BMA220_SBIST);
	return comres;
}

/** Set sbist_sign 
	\param sbist_sign 0=positive stimuli, 1=negative stimuli.
	\return result of communication routines 
*/
int bma220_set_sbist_sign(unsigned char sbist_sign)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SBIST_SIGN__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_SBIST_SIGN, sbist_sign);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_SBIST_SIGN__REG, &data, 1); 
	return comres;
}

/** Get sbist_sign
	\param *sbist_sign 0=positive stimuli, 1=negative stimuli.
	\return result of communication routines 
*/
int bma220_get_sbist_sign(unsigned char *sbist_sign)
{
	unsigned char data;
	int comres = 0;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_SBIST_SIGN__REG, &data, 1 );
	*sbist_sign = BMA220_GET_BITSLICE(data, BMA220_SBIST_SIGN);
	return comres;
}


/* Offset controller functions

*/

/** Set offset word for all 3 axis XYZ
	\param offset struct of three signed char (-32..31)
	\return result of communication routines
*/
int bma220_set_offset_xyz(bma220acc_t offset) 
{
	int comres = 0;
	unsigned char data[3];
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	// Enable write access to offset register by setting cal_manual
	bma220_set_cal_manual(1);

	data[0] =(offset.x<<BMA220_DATA_SHIFT_RIGHT);
	data[1] =(offset.y<<BMA220_DATA_SHIFT_RIGHT);
	data[2] =(offset.z<<BMA220_DATA_SHIFT_RIGHT);

	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_OFFSET_X__REG, data,3);

	// Enable write access to offset register by setting cal_manual
	bma220_set_cal_manual(0);

	return comres;
}

/** Get offset word for all 3 axis XYZ 
	\param *offset pointer to struct of three signed char (-32..31)
	\return result of communication routines
*/
int bma220_get_offset_xyz(bma220acc_t *offset) 
{
	int comres = 0;
	unsigned char data[3];
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	comres |= p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_X__REG, data,3);
	offset->x = (data[0]>>BMA220_DATA_SHIFT_RIGHT);
	offset->y = (data[1]>>BMA220_DATA_SHIFT_RIGHT);
	offset->z = (data[2]>>BMA220_DATA_SHIFT_RIGHT);
	return comres;
}

/** Set cal_manual
	\param cal_manual 0=write access to offset register disabled, 1=write access to offset register enabled
	\return result of communication routines
*/
int bma220_set_cal_manual(unsigned char cal_manual)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CAL_MANUAL__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_CAL_MANUAL, cal_manual);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_CAL_MANUAL__REG, &data, 1);
	return comres;
}

/** Get cal_manual
	\param *cal_manual 0=write access to offset register disabled, 1=write access to offset register enabled
	\return result of communication routines
*/
int bma220_get_cal_manual(unsigned char *cal_manual)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CAL_MANUAL__REG, &data, 1);
	*cal_manual = BMA220_GET_BITSLICE(data, BMA220_CAL_MANUAL);
	return comres;
}

/** Set cal_trigger
	\param cal_trigger 
	\return result of communication routines
*/
int bma220_set_cal_trigger(unsigned char cal_trigger)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CAL_TRIGGER__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_CAL_TRIGGER, cal_trigger);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_CAL_TRIGGER__REG, &data, 1);
	return comres;
}

/** Get cal_rdy
	\param *cal_rdy
	\return result of communication routines
*/
int bma220_get_cal_rdy(unsigned char *cal_rdy) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CAL_RDY__REG, &data, 1);
	*cal_rdy = BMA220_GET_BITSLICE(data, BMA220_CAL_RDY);
	return comres;
}

/** Set offset_reset
	\param offset_reset 
	\return result of communication routines
*/
int bma220_set_offset_reset(unsigned char off_reset)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_RESET__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_OFFSET_RESET, off_reset);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_OFFSET_RESET__REG, &data, 1);
	return comres;
}

/** Set hp_xyz_en
	\param hp_xyz_en 0=OFF, 1=Z ON, 2=Y ON, 3=Z,Y ON, 4=X ON, 5=Z,Y ON, 6=Y,X ON, 7=Z,Y,X ON.
	\return result of communication routines
*/
int bma220_set_hp_xyz_en(unsigned char hp_xyz_en)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HP_XYZ_EN__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_HP_XYZ_EN, hp_xyz_en);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_HP_XYZ_EN__REG, &data, 1);
	return comres;
}

/** Get hp_xyz_en
	\param *hp_xyz_en 0=OFF, 1=Z ON, 2=Y ON, 3=Z,Y ON, 4=X ON, 5=Z,Y ON, 6=Y,X ON, 7=Z,Y,X ON.
	\return result of communication routines
*/
int bma220_get_hp_xyz_en(unsigned char *hp_xyz_en) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_HP_XYZ_EN__REG, &data, 1);
	*hp_xyz_en = BMA220_GET_BITSLICE(data, BMA220_HP_XYZ_EN);
	return comres;
}

/** Set offset_target_x
	\param offset_target_x 0=0g, 1=1g,2=-1g.
	\return result of communication routines
*/
int bma220_set_offset_target_x(unsigned char offset_target_x)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_X__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_OFFSET_TARGET_X, offset_target_x);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_X__REG, &data, 1);
	return comres;
}

/** Get offset_target_x
	\param *offset_target_x 0=0g, 1=1g,2=-1g.
	\return result of communication routines
*/
int bma220_get_offset_target_x(unsigned char *offset_target_x) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_X__REG, &data, 1);
	*offset_target_x = BMA220_GET_BITSLICE(data, BMA220_OFFSET_TARGET_X);
	return comres;
}

/** Set offset_target_y
	\param offset_target_y 0=0g, 1=1g,2=-1g.
	\return result of communication routines
*/
int bma220_set_offset_target_y(unsigned char offset_target_y)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_Y__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_OFFSET_TARGET_Y, offset_target_y);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_Y__REG, &data, 1);
	return comres;
}

/** Get offset_target_y
	\param *offset_target_y 0=0g, 1=1g,2=-1g.
	\return result of communication routines
*/
int bma220_get_offset_target_y(unsigned char *offset_target_y) 
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_Y__REG, &data, 1);
	*offset_target_y = BMA220_GET_BITSLICE(data, BMA220_OFFSET_TARGET_Y);
	return comres;
}

/** Set offset_target_z
	\param offset_target_z 0=0g, 1=1g,2=-1g.
	\return result of communication routines
*/
int bma220_set_offset_target_z(unsigned char offset_target_z)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_Z__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_OFFSET_TARGET_Z, offset_target_z);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_Z__REG, &data, 1);
	return comres;
}

/** Get offset_target_z
	\param *offset_target_z 0=0g, 1=1g,2=-1g.
	\return result of communication routines
*/
int bma220_get_offset_target_z(unsigned char *offset_target_z)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_OFFSET_TARGET_Z__REG, &data, 1);
	*offset_target_z = BMA220_GET_BITSLICE(data, BMA220_OFFSET_TARGET_Z);
	return comres;
}

/** Set cut_off
	\param cut_off
	\return result of communication routines
*/
int bma220_set_cut_off_speed(unsigned char cut_off)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CUT_OFF__REG, &data, 1);
	data = BMA220_SET_BITSLICE(data, BMA220_CUT_OFF, cut_off);
	comres |= p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, BMA220_CUT_OFF__REG, &data, 1);
	return comres;
}

/** Get cut_off
	\param *cut_off
	\return result of communication routines
*/
int bma220_get_cut_off_speed(unsigned char *cut_off)
{
	unsigned char data;
	int comres;
	if (p_bma220 == 0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_CUT_OFF__REG, &data, 1);
	*cut_off = BMA220_GET_BITSLICE(data, BMA220_CUT_OFF);
	return comres;
}


/** Acceleration related functions 

*/

/** Get Acceleration Data for all 3 axis XYZ
	\param *accel pointer to struc of three signed char (-32..31)
	\return result of communication routines
*/
int bma220_read_accel_xyz(bma220acc_t * accel) 
{
	int comres;
	unsigned char data[3];
	
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ACC_X__REG, data,3);

	accel->x = ((signed char)data[0]);	
	accel->x = accel->x >> BMA220_DATA_SHIFT_RIGHT;
	accel->y = ((signed char)data[1]);
	accel->y = accel->y >> BMA220_DATA_SHIFT_RIGHT;
	accel->z = ((signed char)data[2]);
	accel->z = accel->z >> BMA220_DATA_SHIFT_RIGHT;
	return comres;
}

/** Get Acceleration Data for X
	\param *accel_x pointer to signed char (-32..31)
	\return result of communication routines
*/
int bma220_read_accel_x(signed char  *accel_x) 
{
	int comres = 0;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres |= p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ACC_X__REG, &data,1);
	*accel_x = ((signed char) data>>BMA220_DATA_SHIFT_RIGHT);
	return comres;
}

/** Get Acceleration Data for Y
	\param *accel_y pointer to signed char (-32..31)
	\return result of communication routines
*/
int bma220_read_accel_y(signed char  *accel_y) 
{
	int comres = 0;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres |= p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ACC_Y__REG, &data,1);
	*accel_y = ((signed char) data>>BMA220_DATA_SHIFT_RIGHT);
	return comres;
}

/** Get Acceleration Data for Z
	\param *accel_z pointer to signed char (-32..31)
	\return result of communication routines
*/
int bma220_read_accel_z(signed char  *accel_z) 
{
	int comres = 0;
	unsigned char data;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;
	
	comres |= p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, BMA220_ACC_Z__REG, &data,1);
	*accel_z = ((signed char) data>>BMA220_DATA_SHIFT_RIGHT);
	return comres;
}

/** X,Y and Z-axis acceleration data readout from analog interface
	\param *acc pointer to \ref bma220acc_analog_t structure for x,y,z data readout
	\return result of communication routines
	\note data will be read by multi-byte protocol into a 8 byte structure 
*/

/* Direct access to registers

*/

/** read function for raw register access
	\param addr register address
	\param *data pointer to data array for register read back
	\param len number of bytes to be read starting from addr
	\return result of communication routines
*/
int bma220_get_reg(unsigned char addr, unsigned char *data, unsigned char len)
{
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_READ_FUNC(p_bma220->dev_addr, addr, data, len);
	return comres;
}

/** write function for raw register access
	\param addr register address
	\param *data pointer to data array for register write
	\param len number of bytes to be written starting from addr	
	\return result of communication routines
*/
int bma220_set_reg(unsigned char addr, unsigned char *data, unsigned char len) 
{
	int comres;
	if (p_bma220==0)
		return E_BMA_NULL_PTR;

	comres = p_bma220->BMA220_BUS_WRITE_FUNC(p_bma220->dev_addr, addr, data, len);
	return comres;
}
