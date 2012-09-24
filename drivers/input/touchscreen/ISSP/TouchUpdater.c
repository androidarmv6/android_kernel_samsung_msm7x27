// filename: main.c
#include "issp_revision.h"
#ifdef PROJECT_REV_304


/*----------------------------------------------------------------------------
//                               C main line
//----------------------------------------------------------------------------
 */

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "i2c_config.h"
#include "i2clib.h"
#include "TouchIoctl.h"
#endif 

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/earlysuspend.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <mach/gpio.h>
#include <mach/vreg.h>
#include <linux/synaptics_i2c_rmi.h>
#include <linux/device.h>

#include "issp_extern.h"
#include "issp_directives.h"
#include "issp_defs.h"
#include "issp_errors.h"
/* ------------------------------------------------------------------------- */
#define PSOCLENGTH 32768

int touch_fd = 0;
unsigned char bBankCounter;
unsigned int  iBlockCounter;
unsigned int  iChecksumData;
unsigned int  iChecksumTarget;

//char *pSocData;

unsigned char *pSocData;
unsigned char Firmware_Data_HW1[]= 
{
#if defined(CONFIG_MACH_BENI)
#include "Firmware_BENI0A_HW04.h"
#elif defined(CONFIG_MACH_TASS)
#include "Firmware_TASS0C_HW01.h"
#elif defined(CONFIG_MACH_TASSDT)
#include "Firmware_TASSDT0C_HW01.h"
#elif defined(CONFIG_MACH_CALLISTO)
#include "Firmware_ver04.h"
#elif defined(CONFIG_MACH_GIO)
#include "Firmware_GIO03_HW01.h"
#endif
};
unsigned char Firmware_Data_HW2[]= 
{
#if defined(CONFIG_MACH_BENI)
#include "Firmware_BENI02_HW02.h"
#elif defined(CONFIG_MACH_TASS)
#include "Firmware_TASS07_HW11.h"
#elif defined(CONFIG_MACH_TASSDT)
#include "Firmware_TASSDT07_HW11.h"
#elif defined(CONFIG_MACH_CALLISTO)
#include "Firmware_ver04_HW02.h"
#elif defined(CONFIG_MACH_GIO)
#include "Firmware_GIO01_HW02.h"
#endif
};
unsigned char Firmware_Data_HW3[]= 
{
#if defined(CONFIG_MACH_BENI)
#include "Firmware_BENI03_HW03.h"
#elif defined(CONFIG_MACH_GIO)
#include "Firmware_GIO09_HW03.h"
#elif defined(CONFIG_MACH_TASSDT)
#include "Firmware_TASSDT02_HW04.h"
#else
#include "Firmware_cooper06_HW04.h"
#endif
};

unsigned char Firmware_Data_HW4[]= 
{
#if defined(CONFIG_MACH_TASSDT)
#include "Firmware_TASSDT06_HW04.h"
#endif
};
unsigned char Firmware_Data_HW11[]= 
{
#if defined(CONFIG_MACH_GIO)
#include "Firmware_GIO01_HW11.h"
#else
#include "Firmware_GIO03_HW01.h"
#endif
};
unsigned char Firmware_Data_HW21[]= 
{
#if defined(CONFIG_MACH_GIO)
#include "Firmware_GIO01_HW21.h"
#else
#include "Firmware_GIO03_HW01.h"
#endif
};

unsigned char Firmware_Data_HW22[]= 
{
#if defined(CONFIG_MACH_GIO)
#include "Firmware_GIO01_HW22.h"
#else
#include "Firmware_GIO03_HW01.h"
#endif
};

unsigned char Firmware_Data_HW23[]= 
{
#if defined(CONFIG_MACH_GIO)
#include "Firmware_GIO09_HW23.h"
#else
#include "Firmware_GIO03_HW01.h"
#endif
};

extern void SetSCLKHiZ(void);
/* ========================================================================= */
// ErrorTrap()
// Return is not valid from main for PSOC, so this ErrorTrap routine is used.
// For some systems returning an error code will work best. For those, the
// calls to ErrorTrap() should be replaced with a return(bErrorNumber). For
// other systems another method of reporting an error could be added to this
// function -- such as reporting over a communcations port.
/* ========================================================================= */
void ErrorTrap(unsigned char bErrorNumber)
{
#ifndef RESET_MODE
	// Set all pins to highZ to avoid back powering the PSoC through the GPIO
	// protection diodes.
	SetSCLKHiZ();
	SetSDATAHiZ();
	// If Power Cycle programming, turn off the target
	RemoveTargetVDD();
#endif
	//	ioctl(touch_fd, DEV_CTRL_TOUCH_INT_ENABLE,NULL);
//	printk("[TSP] %s,%d error!!\n",__func__,__LINE__);
	//    exit(1);
	//    while (1);
	// return(bErrorNumbers);
}

#if 0
void Delay_int(unsigned int n)  // by KIMC
{
	while(n)
	{
		asm("nop");
		n -= 1;
	}
}
#endif


/* ========================================================================= */
/* MAIN LOOP                                                                 */
/* Based on the diagram in the AN2026                                        */
/* ========================================================================= */

int cypress_update( int HW_ver )
{
	// -- This example section of commands show the high-level calls to -------
	// -- perform Target Initialization, SilcionID Test, Bulk-Erase, Target ---
	// -- RAM Load, FLASH-Block Program, and Target Checksum Verification. ----
	unsigned char fIsError = 0;
	//	unsigned char bTry=0;

	// >>>> ISSP Programming Starts Here <<<<

	//    ioctl(touch_fd, DEV_CTRL_TOUCH_INT_DISABLE,NULL);
	//    ioctl(touch_fd, DEV_CTRL_TOUCH_SET_FLAG,NULL);
	printk(KERN_INFO "[TSP] %s, %d, HW ver=%d\n", __func__, __LINE__,HW_ver);
#if defined(CONFIG_MACH_GIO)
	if( HW_ver == 1)
		pSocData = Firmware_Data_HW1;
	else if ( HW_ver == 2 )
		pSocData = Firmware_Data_HW2;
	else if ( HW_ver == 3 || HW_ver == 0 )
		pSocData = Firmware_Data_HW3;
	else if ( HW_ver == 17 )
		pSocData = Firmware_Data_HW11;
	else if ( HW_ver == 33 )
		pSocData = Firmware_Data_HW21;
	else if ( HW_ver == 34)
		pSocData = Firmware_Data_HW22;
	else if ( HW_ver == 35)
		pSocData = Firmware_Data_HW23;	
#elif defined(CONFIG_MACH_COOPER) 
	if( HW_ver == 4 || HW_ver == 3 || HW_ver == 0 )
		pSocData = Firmware_Data_HW3;
#else
	if( HW_ver == 1 )
		pSocData = Firmware_Data_HW1;
	else if( HW_ver == 2 )
		pSocData = Firmware_Data_HW2;
	else if( HW_ver == 3 )
		pSocData = Firmware_Data_HW3;
	else if( HW_ver == 4 )
		pSocData = Firmware_Data_HW4;
#endif
	else
	{
		printk(KERN_INFO "[TSP] %s, %d, HW ver is wrong!!\n", __func__, __LINE__);
		goto update_err;
	}
#ifdef TX_ON
	UART_Start();
	UART_CPutString("Start HSSP - Ovation");
	UART_PutCRLF();
#endif
	// >>>> ISSP Programming Starts Here <<<<

	// Acquire the device through reset or power cycle
#ifdef RESET_MODE
	UART_CPutString("Reset Mode activated");
#else
	//    UART_CPutString("Power Cycle Mode activated");
	// Initialize the Host & Target for ISSP operations
	fIsError = fPowerCycleInitializeTargetForISSP();
	if (fIsError )
	{
		printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
		ErrorTrap(fIsError);
		goto update_err;
	}
#endif

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("Verify SiliconID");
#endif

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);

	// Run the SiliconID Verification, and proceed according to result.
#if !defined(CONFIG_MACH_TASS) && !defined(CONFIG_MACH_TASSDT) && !defined(CONFIG_MACH_GIO)
	fIsError = fVerifySiliconID();
#endif
	if (fIsError )
	{
		printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
		ErrorTrap(fIsError);
		goto update_err;
	}

#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("End VerifySiliconID");
#endif

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);

#if 1
	// Bulk-Erase the Device.
	fIsError = fEraseTarget();
	if (fIsError )
	{
		printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
		ErrorTrap(fIsError);
		goto update_err;
	}

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("End EraseTarget");
	UART_PutCRLF();
	UART_CPutString("Program Flash Blocks Start");
	UART_PutCRLF();
#endif

#endif

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
#if 1   // program flash block
	//LCD_Char_Position(1, 0);
	//LCD_Char_PrintString("Program Flash Blocks Start");

	//==============================================================//
	// Program Flash blocks with predetermined data. In the final application
	// this data should come from the HEX output of PSoC Designer.

	iChecksumData = 0;     // Calculte the device checksum as you go
	for (iBlockCounter=0; iBlockCounter<BLOCKS_PER_BANK; iBlockCounter++)
	{
		fIsError = fReadWriteSetup();
		if (fIsError )
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

		//LoadProgramData(bBankCounter, (unsigned char)iBlockCounter);
		iChecksumData += iLoadTarget(iBlockCounter);

		fIsError = fProgramTargetBlock(bBankCounter,(unsigned char)iBlockCounter);
		if (fIsError )
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

		fIsError = fReadStatus();
		if (fIsError)
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

#ifdef TX_ON
		UART_PutChar('#');
#endif

	}

#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("Program Flash Blocks End");
#endif

#endif


#if 1  // verify
#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("Verify Start");
	UART_PutCRLF();
#endif

	//=======================================================//
	//PTJ: Doing Verify
	//PTJ: this code isnt needed in the program flow because we use PROGRAM-AND-VERIFY (ProgramAndVerify SROM Func)
	//PTJ: which has Verify built into it.
	// Verify included for completeness in case host desires to do a stand-alone verify at a later date.

	for (iBlockCounter=0; iBlockCounter<BLOCKS_PER_BANK; iBlockCounter++)
	{
		//LoadProgramData(bBankCounter, (unsigned char) iBlockCounter);

		fIsError = fReadWriteSetup();
		if (fIsError )
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

		fIsError = fVerifySetup(bBankCounter,(unsigned char)iBlockCounter);
		if (fIsError)
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

		fIsError = fReadStatus();
		if (fIsError ) {
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

		fIsError = fReadWriteSetup();
		if (fIsError)  {
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

		fIsError = fReadByteLoop(iBlockCounter);
		if (fIsError ) {
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}

#ifdef TX_ON
		UART_PutChar('.');
#endif

	}

#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("Verify End");
#endif

#endif // end verify

#if 1
#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("Security Start");
#endif


	//=======================================================//
	// Program security data into target PSoC. In the final application this
	// data should come from the HEX output of PSoC Designer.
	for (bBankCounter=0; (bBankCounter<NUM_BANKS) ; bBankCounter++)
	{
		//PTJ: READ-WRITE-SETUP used here to select SRAM Bank 1

		fIsError = fReadWriteSetup();
		if (fIsError )
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}
		// Load one bank of security data from hex file into buffer
   		fIsError = fLoadSecurityData(bBankCounter);
		if (fIsError )
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}
		// Secure one bank of the target flash
		fIsError = fSecureTargetFlash();
		if (fIsError )
		{
			printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
			ErrorTrap(fIsError);
			goto update_err;
		}
	}

#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("End Security data");
#endif

#endif


#if 1   // checksum
#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("CheckSum Start");
#endif

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
	//PTJ: Doing Checksum
	iChecksumTarget = 0;
	fIsError = fAccTargetBankChecksum(&iChecksumTarget);
	if (fIsError )
	{
		printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
		ErrorTrap(fIsError);
		goto update_err;
	}

//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);
#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("Checksum : iChecksumTarget (0x");
	UART_PutHexWord(iChecksumTarget);
	UART_CPutString("), iChecksumData (0x");
	UART_PutHexWord(iChecksumData);
	UART_CPutString(")");
#endif

	iChecksumTarget = iChecksumTarget & 0xFFFF;
	iChecksumData = iChecksumData & 0xFFFF;

	if (iChecksumTarget != iChecksumData)
	{
		printk(KERN_INFO "[TSP] %s, %d, iChecksumTarget=%d, iChecksumData=%d\n", __func__, __LINE__,iChecksumTarget, iChecksumData );
		ErrorTrap(CHECKSUM_ERROR);
		goto update_err;
	}

#ifdef TX_ON
	UART_PutCRLF();
	UART_CPutString("End Checksum");
#endif

#endif

	// *** SUCCESS ***
	// At this point, the Target has been successfully Initialize, ID-Checked,
	// Bulk-Erased, Block-Loaded, Block-Programmed, Block-Verified, and Device-
	// Checksum Verified.

	// You may want to restart Your Target PSoC Here.
	ReStartTarget();
//	printk(KERN_INFO "[TSP] %s, %d\n", __func__, __LINE__);

	return 1;

update_err:
	return 0;
}
EXPORT_SYMBOL(cypress_update);

// end of main()

#if 0
int main(int argc, char* argv[])
{
	int fd, ret;
	int readSize = 0;

	if (argc != 2)
	{
		printf("ex) TouchUpdater psoc.bin\n");
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		printf("Can't find %s\n", argv[1]);
		close(fd);
		exit(1);
	}

	pSocData = malloc(sizeof(char)*PSOCLENGTH);

	readSize = read(fd, pSocData, PSOCLENGTH);
	if(readSize != PSOCLENGTH)
	{
		printf("pSoc Read Fail\n");
		close(fd);
		exit(1);
	}
	touch_fd = open("/dev/cypress_ts", O_RDONLY|O_NONBLOCK);
	if (touch_fd < 0)
	{
		printf("Device Open Error!\n");
		exit(1);
	}
	//ret = ioctl(touch_fd, 0, NULL);
	printf("read to program psoc\n");
	cypress_update();

	return 0;
}
#endif

EXPORT_SYMBOL(pSocData);
#endif  //(PROJECT_REV_)
