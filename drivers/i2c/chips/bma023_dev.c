#include <linux/kernel.h>
#include <linux/i2c/bma023_dev.h>

bma023_t *p_bma023;				/**< pointer to bma023 device structure  */
int bma023_status = 0 ;

int bma023_init(bma023_t *bma023) 
{
	int comres=0;
    unsigned char data;

    trace_in() ;

    p_bma023 = bma023;															/* assign bma023 ptr */
    p_bma023->dev_addr = bma023_I2C_ADDR;										/* preset SM380 I2C_addr */
    comres += p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, CHIP_ID__REG, &data, 1);	/* read Chip Id */

    p_bma023->chip_id = bma023_GET_BITSLICE(data, CHIP_ID);			/* get bitslice */

    comres += p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ML_VERSION__REG, &data, 1); /* read Version reg */
    p_bma023->ml_version = bma023_GET_BITSLICE(data, ML_VERSION);	/* get ML Version */
    p_bma023->al_version = bma023_GET_BITSLICE(data, AL_VERSION);	/* get AL Version */

    trace_out();
    return comres;
}

int bma023_soft_reset() 
{
    int comres;
    unsigned char data=0;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    data = bma023_SET_BITSLICE(data, SOFT_RESET, 1);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, SOFT_RESET__REG, &data,1); 

    trace_out();
    return comres;
}


int bma023_update_image() 
{
    int comres;
    unsigned char data=0;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    data = bma023_SET_BITSLICE(data, UPDATE_IMAGE, 1);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, UPDATE_IMAGE__REG, &data,1); 

    trace_out();
    return comres;
}


int bma023_set_image (bma023regs_t *bma023Image) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, EE_W__REG,&data, 1);
    data = bma023_SET_BITSLICE(data, EE_W, bma023_EE_W_ON);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, EE_W__REG, &data, 1);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, bma023_IMAGE_BASE, (unsigned char*)bma023Image, bma023_IMAGE_LEN);
    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, EE_W__REG,&data, 1);
    data = bma023_SET_BITSLICE(data, EE_W, bma023_EE_W_OFF);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, EE_W__REG, &data, 1);

    trace_out();
    return comres;
}



int bma023_get_image(bma023regs_t *bma023Image)
{
    int comres;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0){
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, EE_W__REG,&data, 1);
    data = bma023_SET_BITSLICE(data, EE_W, bma023_EE_W_ON);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, EE_W__REG, &data, 1);
    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, bma023_IMAGE_BASE, (unsigned char *)bma023Image, bma023_IMAGE_LEN);
    data = bma023_SET_BITSLICE(data, EE_W, bma023_EE_W_OFF);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, EE_W__REG, &data, 1);

    trace_out();
    return comres;
}

int bma023_get_offset(unsigned char xyz, unsigned short *offset) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, (OFFSET_X_LSB__REG+xyz), &data, 1);
    data = bma023_GET_BITSLICE(data, OFFSET_X_LSB);
    *offset = data;
    comres += p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, (OFFSET_X_MSB__REG+xyz), &data, 1);
    *offset |= (data<<2);

    trace_out();
    return comres;
}


int bma023_set_offset(unsigned char xyz, unsigned short offset) 
{
    int comres;
    unsigned char data;

    trace_in() ;
    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, (OFFSET_X_LSB__REG+xyz), &data, 1);
    data = bma023_SET_BITSLICE(data, OFFSET_X_LSB, offset);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, (OFFSET_X_LSB__REG+xyz), &data, 1);
    data = (offset&0x3ff)>>2;
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, (OFFSET_X_MSB__REG+xyz), &data, 1);

    trace_out();
    return comres;
}


int bma023_set_offset_eeprom(unsigned char xyz, unsigned short offset) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;   
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, (OFFSET_X_LSB__REG+xyz), &data, 1);
    data = bma023_SET_BITSLICE(data, OFFSET_X_LSB, offset);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, (bma023_EEP_OFFSET+OFFSET_X_LSB__REG + xyz), &data, 1);   
    p_bma023->delay_msec(34);
    data = (offset&0x3ff)>>2;
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, (bma023_EEP_OFFSET+ OFFSET_X_MSB__REG+xyz), &data, 1);
    p_bma023->delay_msec(34);

    trace_out();
    return comres;
}




int bma023_set_ee_w(unsigned char eew)
{
    unsigned char data;
    int comres;
    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, EE_W__REG,&data, 1);
    data = bma023_SET_BITSLICE(data, EE_W, eew);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, EE_W__REG, &data, 1);

    trace_out();
    return comres;
}



int bma023_write_ee(unsigned char addr, unsigned char data) 
{	
    int comres;

    trace_in() ;

    if (p_bma023==0) { 			/* check pointers */
        trace_out();
        return E_bma023_NULL_PTR;
    }

    if (p_bma023->delay_msec == 0)
        trace_out();
    return E_bma023_NULL_PTR;

    comres = bma023_set_ee_w( bma023_EE_W_ON );
    addr|=0x20;   /* add eeprom address offset to image address if not applied */
    comres += bma023_write_reg(addr, &data, 1 );
    p_bma023->delay_msec( bma023_EE_W_DELAY );
    comres += bma023_set_ee_w( bma023_EE_W_OFF);

    trace_out();
    return comres;
}


int bma023_selftest(unsigned char st)
{
    int comres;
    unsigned char data;

    trace_in() ;

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, SELF_TEST__REG, &data, 1);
    data = bma023_SET_BITSLICE(data, SELF_TEST, st);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, SELF_TEST__REG, &data, 1);  

    trace_out();
    return comres;  

}


int bma023_set_range(char range) 
{			
    int comres = 0;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    if (range<3) 
    {	
        comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, RANGE__REG, &data, 1 );
        data = bma023_SET_BITSLICE(data, RANGE, range);		  	
        comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, RANGE__REG, &data, 1);
    }

    trace_out();
    return comres;

}


int bma023_get_range(unsigned char *range) 
{
    int comres = 0;
    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, RANGE__REG, range, 1 );

    *range = bma023_GET_BITSLICE(*range, RANGE);

    trace_out();
    return comres;

}


/*
 * bma023_dev_operating()
 *
 *  Perform Chip power Up/Down
 *      mode - bma023_MODE_SLEEP = 0
 *             bma023_MODE_NORMAL = 2   
 */
int bma023_dev_operating(unsigned char mode)
{
    int comres=0 ;
    unsigned char data1, data2;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    debug( "mode= %c, bma023_status= %d", mode, bma023_status ) ;

    if (mode<4 || mode!=1) 
    {
        comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, WAKE_UP__REG, &data1, 1 );
        data1  = bma023_SET_BITSLICE(data1, WAKE_UP, mode);		  
        comres += p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, SLEEP__REG, &data2, 1 );
        data2  = bma023_SET_BITSLICE(data2, SLEEP, (mode>>1));
        comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, WAKE_UP__REG, &data1, 1);
        comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, SLEEP__REG, &data2, 1);
        p_bma023->mode = mode;
    } 

    trace_out();
    return comres;

}

/*
 * bma023_dev_set_staus()
 *
 * bma023_status = [CAL|COMPASS|ACC] 
               ex,  000   CAL: NO,   COMPASS: standby,   ACC: standby 
                    001   CAL: NO,   COMPASS: standby,   ACC: normal
                    010   CAL: NO,   COMPASS: normal,    ACC: standby 
                    011   CAL: NO,   COMPASS: normal,    ACC: normal
                    1XX   CAL: YES,  COMPASS: don't care,ACC: don't care
 *
 */
int bma023_dev_set_status( int module, int param, int cal ) 
{

	trace_in() ;

    if( cal == TRUE )
    {
        bma023_status = bma023_status | ( 1 << 2 ) ;
    }
    else if( cal == FALSE )
    {
    	bma023_status = bma023_status & (~( 1 << 2 ) ) ;
    }

    if( param == STANDBY ) 
    {
        bma023_status= bma023_status & (~(1 << module)) ;
    }
    else if( param == NORMAL )
    {
    	bma023_status= bma023_status | ( 1 << module ) ;
    }
    else
    {
        printk( "bma023_dev_get_status() Fault or Calibration!!!! module= %d, param=%d, cal= %d\n", module, param, cal  ) ;
    }

	trace_out() ;
    return bma023_status ;
}

int bma023_dev_get_status( void )
{
    trace_in() ;

    trace_out() ;
    return bma023_status ;
}

int bma023_set_operation_mode( int module, int param, int cal )
{
	int status= 0 ;

    trace_in() ;

    status= bma023_dev_set_status( module, param, cal ) ;
    printk( "bma023_status= %d\n", bma023_status ) ;

    switch( status )
    {
        case STANDBY:
            bma023_dev_operating( bma023_MODE_SLEEP ) ;
#if 0
            bma023_timer.saved_timer_state= TIMER_OFF ;
            bma023_timer_disable() ;
#endif
            break ;
        case ONLYACCEL:
        case ONLYCOMPASS:
        case ACCELCOMPASS:
            bma023_dev_operating( bma023_MODE_NORMAL ) ;
#if 0
            bma023_timer.saved_timer_state= TIMER_ON ;
            bma023_timer_enable( bma023_timer.polling_time ) ;
#endif
            break ;
        default:
            if( status > ACCELCOMPASS )
            {
            bma023_dev_operating( bma023_MODE_NORMAL ) ;
#if 0
            bma023_timer.saved_timer_state= TIMER_ON ;
            bma023_timer_enable( bma023_timer.polling_time ) ;
#endif
            printk("%s: bma023_dev_set_operation_mode is CALIBRATION\n", __FUNCTION__ );
            }
            else {
            bma023_dev_operating( bma023_MODE_SLEEP ) ;
#if 0
            bma023_timer.saved_timer_state= TIMER_OFF ;
            bma023_timer_disable() ;
#endif
            printk("%s: bma023_dev_set_operation_mode Fault argument!!! Disable of all in force\n", __FUNCTION__ );
            }
            break ;
    }

#if 0
    switch( status )
    {
	case STANDBY:
	    bma023_report_func= NULL ;
	    printk("%s: bma023_dev_set_operation_mode STANDBY\n", __FUNCTION__ );
	break ;
	case ONLYACCEL:
	    bma023_report_func= bma023_report_sensorhal ;
	    printk("%s: bma023_dev_set_operation_mode ONLYACCEL\n", __FUNCTION__ );
	break ;
	case ONLYCOMPASS:
	    bma023_report_func= bma023_report_akmd2 ;
	    printk("%s: bma023_dev_set_operation_mode ONLYCOMPASS\n", __FUNCTION__ );
	break ;
	case ACCELCOMPASS:
	    bma023_report_func= bma023_report_sensorhal_akmd2 ;
	    printk("%s: bma023_dev_set_operation_mode ACCELCOMPASS\n", __FUNCTION__ );
	break ;
	default:
	    if( status > ACCELCOMPASS )
	    {
	        bma023_report_func= bma023_report_calibration ;
	        printk("%s: bma023_dev_set_operation_mode Calibration\n", __FUNCTION__ );
	    }
	    else {
	        bma023_report_func= NULL ;
	        printk("%s: bma023_dev_set_operation_mode Fault argument!!! Disable of all in force\n", __FUNCTION__ );
	    }
        break ;
    }
#endif
    
    trace_out() ; 
    return status ;
}



unsigned char bma023_get_mode(void) 
{
    trace_in() ;
    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;	
    }

    trace_out();
    return p_bma023->mode;

}

int bma023_set_bandwidth(char bw) 
{
    int comres = 0;
    unsigned char data;
    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    if (bw<8) 
    {
        comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, RANGE__REG, &data, 1 );
        data = bma023_SET_BITSLICE(data, BANDWIDTH, bw);
        comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, RANGE__REG, &data, 1 );
    }

    trace_out();
    return comres;


}


int bma023_get_bandwidth(unsigned char *bw) 
{
    int comres = 1;

    trace_in() ;
    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, BANDWIDTH__REG, bw, 1 );		

    *bw = bma023_GET_BITSLICE(*bw, BANDWIDTH);

    trace_out();
    return comres;
}

int bma023_set_wake_up_pause(unsigned char wup)
{
    int comres=0;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, WAKE_UP_PAUSE__REG, &data, 1 );
    data = bma023_SET_BITSLICE(data, WAKE_UP_PAUSE, wup);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, WAKE_UP_PAUSE__REG, &data, 1 );

    trace_out();
    return comres;
}

int bma023_get_wake_up_pause(unsigned char *wup)
{
    int comres = 1;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, WAKE_UP_PAUSE__REG, &data,  1 );		

    *wup = bma023_GET_BITSLICE(data, WAKE_UP_PAUSE);

    trace_out();
    return comres;

}


int bma023_set_low_g_threshold(unsigned char th) 
{
    int comres;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;		
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, LG_THRES__REG, &th, 1);

    trace_out();
    return comres;
}


int bma023_get_low_g_threshold(unsigned char *th)
{

    int comres=1;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;	
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, LG_THRES__REG, th, 1);		

    trace_out();
    return comres;

}


int bma023_set_low_g_countdown(unsigned char cnt)
{
    int comres=0;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, COUNTER_LG__REG, &data, 1 );
    data = bma023_SET_BITSLICE(data, COUNTER_LG, cnt);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, COUNTER_LG__REG, &data, 1 );

    trace_out();
    return comres;
}


int bma023_get_low_g_countdown(unsigned char *cnt)
{
    int comres = 1;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, COUNTER_LG__REG, &data,  1 );		
    *cnt = bma023_GET_BITSLICE(data, COUNTER_LG);

    trace_out();
    return comres;
}


int bma023_set_high_g_countdown(unsigned char cnt)
{
    int comres=1;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, COUNTER_HG__REG, &data, 1 );
    data = bma023_SET_BITSLICE(data, COUNTER_HG, cnt);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, COUNTER_HG__REG, &data, 1 );

    trace_out();
    return comres;
}


int bma023_get_high_g_countdown(unsigned char *cnt)
{
    int comres = 0;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, COUNTER_HG__REG, &data,  1 );		

    *cnt = bma023_GET_BITSLICE(data, COUNTER_HG);

    trace_out();
    return comres;

}


int bma023_set_low_g_duration(unsigned char dur) 
{
    int comres=0;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, LG_DUR__REG, &dur, 1);

    trace_out();
    return comres;
}


int bma023_get_low_g_duration(unsigned char *dur)
{
    int comres=0;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, LG_DUR__REG, dur, 1);				  

    trace_out();
    return comres;
}


int bma023_set_high_g_threshold(unsigned char th) 
{

    int comres=0;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, HG_THRES__REG, &th, 1);

    trace_out();
    return comres;
}

int bma023_get_high_g_threshold(unsigned char *th)
{
    int comres=0;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, HG_THRES__REG, th, 1);		

    trace_out();
    return comres;
}



int bma023_set_high_g_duration(unsigned char dur) 
{
    int comres=0;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, HG_DUR__REG, &dur, 1);

    trace_out();
    return comres;
}


int bma023_get_high_g_duration(unsigned char *dur) {


    int comres=0;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, HG_DUR__REG, dur, 1);		

    trace_out();
    return comres;
}


int bma023_set_any_motion_threshold(unsigned char th) 
{

    int comres=0;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, ANY_MOTION_THRES__REG, &th, 1);

    trace_out();
    return comres;
}


int bma023_get_any_motion_threshold(unsigned char *th)
{
    int comres=0;
    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR; 
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ANY_MOTION_THRES__REG, th, 1);		

    trace_out();
    return comres;

}


int bma023_set_any_motion_count(unsigned char amc)
{
    int comres=0;	
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ANY_MOTION_DUR__REG, &data, 1 );
    data = bma023_SET_BITSLICE(data, ANY_MOTION_DUR, amc);
    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, ANY_MOTION_DUR__REG, &data, 1 );

    trace_out();
    return comres;
}


int bma023_get_any_motion_count(unsigned char *amc)
{
    int comres = 0;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ANY_MOTION_DUR__REG, &data,  1 );		

    *amc = bma023_GET_BITSLICE(data, ANY_MOTION_DUR);

    trace_out();
    return comres;
}



int bma023_set_interrupt_mask(unsigned char mask) 
{
    int comres=0;
    unsigned char data[4];

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    data[0] = mask & bma023_CONF1_INT_MSK;
    data[2] = ((mask<<1) & bma023_CONF2_INT_MSK);		

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, bma023_CONF1_REG, &data[1], 1);
    comres += p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, bma023_CONF2_REG, &data[3], 1);		

    data[1] &= (~bma023_CONF1_INT_MSK);
    data[1] |= data[0];
    data[3] &=(~(bma023_CONF2_INT_MSK));
    data[3] |= data[2];

    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, bma023_CONF1_REG, &data[1], 1);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, bma023_CONF2_REG, &data[3], 1);

    trace_out();
    return comres;	
}


int bma023_get_interrupt_mask(unsigned char *mask) 
{
    int comres=0;
    unsigned char data;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, bma023_CONF1_REG, &data,1);
    *mask = data & bma023_CONF1_INT_MSK;
    p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, bma023_CONF2_REG, &data,1);
    *mask = *mask | ((data & bma023_CONF2_INT_MSK)>>1);

    trace_out();
    return comres;
}


int bma023_reset_interrupt(void) 
{	
    int comres=0;
    unsigned char data=(1<<RESET_INT__POS);	
    trace_in() ;
    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, RESET_INT__REG, &data, 1);
    trace_out();
    return comres;

}


int bma023_read_accel_x(short *a_x) 
{
    int comres;
    unsigned char data[2];

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ACC_X_LSB__REG, data, 2);

    *a_x = bma023_GET_BITSLICE(data[0],ACC_X_LSB) | bma023_GET_BITSLICE(data[1],ACC_X_MSB)<<ACC_X_LSB__LEN;
    *a_x = *a_x << (sizeof(short)*8-(ACC_X_LSB__LEN+ACC_X_MSB__LEN));
    *a_x = *a_x >> (sizeof(short)*8-(ACC_X_LSB__LEN+ACC_X_MSB__LEN));

    trace_out();
    return comres;

}


int bma023_read_accel_y(short *a_y) 
{
    int comres;
    unsigned char data[2];	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ACC_Y_LSB__REG, data, 2);

    *a_y = bma023_GET_BITSLICE(data[0],ACC_Y_LSB) | bma023_GET_BITSLICE(data[1],ACC_Y_MSB)<<ACC_Y_LSB__LEN;
    *a_y = *a_y << (sizeof(short)*8-(ACC_Y_LSB__LEN+ACC_Y_MSB__LEN));
    *a_y = *a_y >> (sizeof(short)*8-(ACC_Y_LSB__LEN+ACC_Y_MSB__LEN));

    trace_out();
    return comres;
}


/** Z-axis acceleration data readout 
  \param *a_z pointer for 16 bit 2's complement data output (LSB aligned)
 */
int bma023_read_accel_z(short *a_z)
{
    int comres;
    unsigned char data[2];	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ACC_Z_LSB__REG, data, 2);

    *a_z = bma023_GET_BITSLICE(data[0],ACC_Z_LSB) | bma023_GET_BITSLICE(data[1],ACC_Z_MSB)<<ACC_Z_LSB__LEN;
    *a_z = *a_z << (sizeof(short)*8-(ACC_Z_LSB__LEN+ACC_Z_MSB__LEN));
    *a_z = *a_z >> (sizeof(short)*8-(ACC_Z_LSB__LEN+ACC_Z_MSB__LEN));

    trace_out();
    return comres;
}


int bma023_read_temperature(unsigned char * temp) 
{
    int comres;	

    trace_in() ;
    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, TEMPERATURE__REG, temp, 1);

    trace_out();
    return comres;

}


int bma023_read_accel_xyz(bma023acc_t * acc)
{
    int comres;
    unsigned char data[6];

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ACC_X_LSB__REG, &data[0],6);

    acc->x = bma023_GET_BITSLICE(data[0],ACC_X_LSB) | (bma023_GET_BITSLICE(data[1],ACC_X_MSB)<<ACC_X_LSB__LEN);
    acc->x = acc->x << (sizeof(short)*8-(ACC_X_LSB__LEN+ACC_X_MSB__LEN));
    acc->x = acc->x >> (sizeof(short)*8-(ACC_X_LSB__LEN+ACC_X_MSB__LEN));

    acc->y = bma023_GET_BITSLICE(data[2],ACC_Y_LSB) | (bma023_GET_BITSLICE(data[3],ACC_Y_MSB)<<ACC_Y_LSB__LEN);
    acc->y = acc->y << (sizeof(short)*8-(ACC_Y_LSB__LEN + ACC_Y_MSB__LEN));
    acc->y = acc->y >> (sizeof(short)*8-(ACC_Y_LSB__LEN + ACC_Y_MSB__LEN));

    /*	
        acc->z = bma023_GET_BITSLICE(data[4],ACC_Z_LSB); 
        acc->z |= (bma023_GET_BITSLICE(data[5],ACC_Z_MSB)<<ACC_Z_LSB__LEN);
        acc->z = acc->z << (sizeof(short)*8-(ACC_Z_LSB__LEN+ACC_Z_MSB__LEN));
        acc->z = acc->z >> (sizeof(short)*8-(ACC_Z_LSB__LEN+ACC_Z_MSB__LEN));
     */	
    acc->z = bma023_GET_BITSLICE(data[4],ACC_Z_LSB) | (bma023_GET_BITSLICE(data[5],ACC_Z_MSB)<<ACC_Z_LSB__LEN);
    acc->z = acc->z << (sizeof(short)*8-(ACC_Z_LSB__LEN + ACC_Z_MSB__LEN));
    acc->z = acc->z >> (sizeof(short)*8-(ACC_Z_LSB__LEN + ACC_Z_MSB__LEN));

    debug( "%d\t, %d\t, %d\n", acc->x, acc->y, acc->z ) ;

    trace_out();
    return comres;
}


int bma023_get_interrupt_status(unsigned char * ist) 
{

    int comres=0;	

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, bma023_STATUS_REG, ist, 1);

    trace_out();
    return comres;
}


int bma023_set_low_g_int(unsigned char onoff) {
    int comres;
    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ENABLE_LG__REG, &data, 1);				

    data = bma023_SET_BITSLICE(data, ENABLE_LG, onoff);

    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, ENABLE_LG__REG, &data, 1);

    trace_out();
    return comres;
}


int bma023_set_high_g_int(unsigned char onoff) 
{
    int comres;

    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ENABLE_HG__REG, &data, 1);				

    data = bma023_SET_BITSLICE(data, ENABLE_HG, onoff);

    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, ENABLE_HG__REG, &data, 1);

    trace_out();
    return comres;
}


int bma023_set_any_motion_int(unsigned char onoff) {
    int comres;

    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, EN_ANY_MOTION__REG, &data, 1);				
    data = bma023_SET_BITSLICE(data, EN_ANY_MOTION, onoff);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, EN_ANY_MOTION__REG, &data, 1);

    trace_out();
    return comres;

}


int bma023_set_alert_int(unsigned char onoff) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ALERT__REG, &data, 1);				
    data = bma023_SET_BITSLICE(data, ALERT, onoff);

    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, ALERT__REG, &data, 1);

    trace_out();
    return comres;

}


int bma023_set_advanced_int(unsigned char onoff) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, ENABLE_ADV_INT__REG, &data, 1);				
    data = bma023_SET_BITSLICE(data, EN_ANY_MOTION, onoff);

    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, ENABLE_ADV_INT__REG, &data, 1);

    trace_out();
    return comres;
}


int bma023_latch_int(unsigned char latched) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, LATCH_INT__REG, &data, 1);				
    data = bma023_SET_BITSLICE(data, LATCH_INT, latched);

    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, LATCH_INT__REG, &data, 1);

    trace_out();
    return comres;
}


int bma023_set_new_data_int(unsigned char onoff) 
{
    int comres;
    unsigned char data;

    trace_in() ;

    if(p_bma023==0)  {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, NEW_DATA_INT__REG, &data, 1);				
    data = bma023_SET_BITSLICE(data, NEW_DATA_INT, onoff);
    comres += p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, NEW_DATA_INT__REG, &data, 1);

    trace_out();
    return comres;
}


int bma023_pause(int msec) 
{

    trace_in() ;
    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }
    else
        p_bma023->delay_msec(msec);	

    trace_out();
    return msec;
}


int bma023_read_reg(unsigned char addr, unsigned char *data, unsigned char len)
{
    int comres;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_READ_FUNC(p_bma023->dev_addr, addr, data, len);

    trace_out();
    return comres;
}


int bma023_write_reg(unsigned char addr, unsigned char *data, unsigned char len) 
{
    int comres;

    trace_in() ;

    if (p_bma023==0) {
        trace_out();
        return E_bma023_NULL_PTR;
    }

    comres = p_bma023->bma023_BUS_WRITE_FUNC(p_bma023->dev_addr, addr, data, len);

    trace_out();
    return comres;
}
