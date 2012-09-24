// filename: ISSP_Driver_Routines.c
#include "issp_revision.h"
#ifdef PROJECT_REV_304
// Copyright 2006-2007, Cypress Semiconductor Corporation.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
//CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
//INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
//MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
//BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
//OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//LIABILITY, WHETHER IN CONRTACT, STRICT LIABILITY, OR TORT (INCLUDING
//NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND,EXPRESS OR IMPLIED,
// WITH REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Cypress reserves the right to make changes without further notice to the
// materials described herein. Cypress does not assume any liability arising
// out of the application or use of any product or circuit described herein.
// Cypress does not authorize its products for use as critical components in
// life-support systems where a malfunction or failure may reasonably be
// expected to result in significant injury to the user. The inclusion of
// Cypressï¿?product in a life-support systems application implies that the
// manufacturer assumes all risk of such use and in doing so indemnifies
// Cypress against all charges.
//
// Use may be limited by and subject to the applicable Cypress software
// license agreement.
//
//--------------------------------------------------------------------------

//#include <m8c.h>        // part specific constants and macros
//#include "psocapi.h"    // PSoC API definitions for all User Modules

#include "issp_defs.h"
#include "issp_errors.h"
#include "issp_directives.h"

/* CHJ */
#include <mach/gpio.h>
#include <mach/vreg.h>
#include <linux/delay.h>
#include <linux/i2c/europa_tsp_gpio.h>
/* CHJ */

//#include "Device.h"

//#include <intrins.h>

#if defined(CONFIG_MACH_BENI)||defined(CONFIG_MACH_TASS) || defined(CONFIG_MACH_TASSDT) ||defined(CONFIG_MACH_COOPER) || defined(CONFIG_MACH_GIO) 
#define SECURITY_DATA	0xAA
#else
#define SECURITY_DATA	0xFF
#endif
extern    unsigned char    bTargetDataPtr;
extern    unsigned char    abTargetDataOUT[TARGET_DATABUFF_LEN];


// ****************************** PORT BIT MASKS ******************************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
#define SDATA_PIN   0x10        // P1.4
#define SCLK_PIN    0x08        // P1.3
#define XRES_PIN    0x40        // P2.6
#define TARGET_VDD  0x40        // P2.6


// ((((((((((((((((((((((( DEMO ISSP SUBROUTINE SECTION )))))))))))))))))))))))
// ((((( Demo Routines can be deleted in final ISSP project if not used   )))))
// ((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))

// ============================================================================
// InitTargetTestData()
// !!!!!!!!!!!!!!!!!!FOR TEST!!!!!!!!!!!!!!!!!!!!!!!!!!
// PROCESSOR_SPECIFIC
// Loads a 64-Byte array to use as test data to program target. Ultimately,
// this data should be fed to the Host by some other means, ie: I2C, RS232,
// etc. Data should be derived from hex file.
//  Global variables affected:
//    bTargetDataPtr
//    abTargetDataOUT
// ============================================================================
void InitTargetTestData(unsigned char bBlockNum, unsigned char bBankNum)
{
    // create unique data for each block
    for (bTargetDataPtr = 0; bTargetDataPtr < TARGET_DATABUFF_LEN; bTargetDataPtr++)
    {
        abTargetDataOUT[bTargetDataPtr] = 0x55;
    }
}


// ============================================================================
// LoadArrayWithSecurityData()
// !!!!!!!!!!!!!!!!!!FOR TEST!!!!!!!!!!!!!!!!!!!!!!!!!!
// PROCESSOR_SPECIFIC
// Most likely this data will be fed to the Host by some other means, ie: I2C,
// RS232, etc., or will be fixed in the host. The security data should come
// from the hex file.
//   bStart  - the starting byte in the array for loading data
//   bLength - the number of byte to write into the array
//   bType   - the security data to write over the range defined by bStart and
//             bLength
// ============================================================================
void LoadArrayWithSecurityData(unsigned char bStart, unsigned char bLength, unsigned char bType)
{
    // Now, write the desired security-bytes for the range specified
    for (bTargetDataPtr = bStart; bTargetDataPtr < bLength; bTargetDataPtr++)
    {
    	abTargetDataOUT[bTargetDataPtr] = bType;
    }
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// Delay()
// This delay uses a simple "nop" loop. With the CPU running at 24MHz, each
// pass of the loop is about 1 usec plus an overhead of about 3 usec.
//      total delay = (n + 3) * 1 usec
// To adjust delays and to adapt delays when porting this application, see the
// ISSP_Delays.h file.
// ****************************************************************************
// set Delay to delay ( n + 3 ) usec
void Delay(unsigned int n)
{
// TO DO
	udelay( n );	
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// LoadProgramData()
// The final application should load program data from HEX file generated by
// PSoC Designer into a 64 byte host ram buffer.
//    1. Read data from next line in hex file into ram buffer. One record
//      (line) is 64 bytes of data.
//    2. Check host ram buffer + record data (Address, # of bytes) against hex
//       record checksum at end of record line
//    3. If error reread data from file or abort
//    4. Exit this Function and Program block or verify the block.
// This demo program will, instead, load predetermined data into each block.
// The demo does it this way because there is no comm link to get data.
// ****************************************************************************
void LoadProgramData(unsigned char bBlockNum, unsigned char bBankNum)
{
    // >>> The following call is for demo use only. <<<
    // Function InitTargetTestData fills buffer for demo
    InitTargetTestData(bBlockNum, bBankNum);

    // Note:
    // Error checking should be added for the final version as noted above.
    // For demo use this function just returns VOID.
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// fLoadSecurityData()
// Load security data from hex file into 64 byte host ram buffer. In a fully
// functional program (not a demo) this routine should do the following:
//    1. Read data from security record in hex file into ram buffer.
//    2. Check host ram buffer + record data (Address, # of bytes) against hex
//       record checksum at end of record line
//    3. If error reread security data from file or abort
//    4. Exit this Function and Program block
// In this demo routine, all of the security data is set to unprotected (0x00)
// and it returns.
// This function always returns PASS. The flag return is reserving
// functionality for non-demo versions.
// ****************************************************************************
signed char fLoadSecurityData(unsigned char bBankNum)
{
    // >>> The following call is for demo use only. <<<
    // Function LoadArrayWithSecurityData fills buffer for demo
//    LoadArrayWithSecurityData(0,SECURITY_BYTES_PER_BANK, 0x00);
    LoadArrayWithSecurityData(0,SECURITY_BYTES_PER_BANK, SECURITY_DATA);		//PTJ: 0x1B (00 01 10 11) is more interesting security data than 0x00 for testing purposes

    // Note:
    // Error checking should be added for the final version as noted above.
    // For demo use this function just returns PASS.
    return(PASS);
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// fSDATACheck()
// Check SDATA pin for high or low logic level and return value to calling
// routine.
// Returns:
//     0 if the pin was low.
//     1 if the pin was high.
// ****************************************************************************
// return the value of SDA GPIO 
unsigned char fSDATACheck(void)
{
// TO DO
    if ( gpio_get_value ( TSP_SDA ) )
        return(1);
    else
        return(0);
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SCLKHigh()
// Set the SCLK pin High
// ****************************************************************************
// High PIN
// TO DO
void SCLKHigh(void)
{
//	gpio_tlmm_config(GPIO_CFG(TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_direction_output(TSP_SCL, 1);
#if !defined(CONFIG_MACH_BENI)||!defined(CONFIG_MACH_TASS) || !defined(CONFIG_MACH_TASSDT) ||!defined(CONFIG_MACH_COOPER)  || !defined(CONFIG_MACH_GIO)
	Delay(1);
#endif
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SCLKLow()
// Make Clock pin Low
// ****************************************************************************
// high low 
// to do
void SCLKLow(void)
{
//	gpio_tlmm_config(GPIO_CFG(TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);

//	gpio_set_value ( TSP_SCL, 0);
	gpio_direction_output(TSP_SCL, 0);
#if !defined(CONFIG_MACH_BENI)||!defined(CONFIG_MACH_TASS) || !defined(CONFIG_MACH_TASSDT) ||!defined(CONFIG_MACH_COOPER)  || !defined(CONFIG_MACH_GIO)
	Delay(1);
#endif
}

#ifndef RESET_MODE  // Only needed for power cycle mode
// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetSCLKHiZ()
// Set SCLK pin to HighZ drive mode.
// ****************************************************************************
// set to input mode
void SetSCLKHiZ(void)
{
//gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_OUTPUT, GPIO_NO_PULL,GPIO_2MA), GPIO_ENABLE);
//origpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_INPUT, GPIO_NO_PULL,GPIO_2MA), GPIO_ENABLE);
//	gpio_tlmm_config(GPIO_CFG(TSP_SCL, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_direction_input(TSP_SCL);
}
#endif

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetSCLKStrong()
// Set SCLK to an output (Strong drive mode)
// ****************************************************************************
// output mode
// to do
void SetSCLKStrong(void)
{
//gpio_tlmm_config(GPIO_CFG( TSP_SCL, 0, GPIO_OUTPUT, GPIO_NO_PULL,GPIO_2MA), GPIO_ENABLE);
//	gpio_tlmm_config(GPIO_CFG(TSP_SCL, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_direction_output(TSP_SCL ,0);
}


// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetSDATAHigh()
// Make SDATA pin High
// ****************************************************************************
// data high
// to do

void SetSDATAHigh(void)
{
//	gpio_tlmm_config(GPIO_CFG(TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_direction_output(TSP_SDA ,1);
	
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetSDATALow()
// Make SDATA pin Low
// ****************************************************************************
// data low 
// to do

void SetSDATALow(void)
{
//	gpio_tlmm_config(GPIO_CFG(TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
//	gpio_set_value ( TSP_SDA, 0);
	gpio_direction_output(TSP_SDA, 0);
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetSDATAHiZ()
// Set SDATA pin to an input (HighZ drive mode).
// ****************************************************************************
// data input
// to do
void SetSDATAHiZ(void)
{
        //gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_INPUT, GPIO_NO_PULL,GPIO_2MA), GPIO_ENABLE);
//	gpio_tlmm_config(GPIO_CFG(TSP_SDA, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_direction_input(TSP_SDA);
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetSDATAStrong()
// Set SDATA for transmission (Strong drive mode) -- as opposed to being set to
// High Z for receiving data.
// ****************************************************************************
// data output
// to do
void SetSDATAStrong(void)
{
       // gpio_tlmm_config(GPIO_CFG( TSP_SDA, 0, GPIO_OUTPUT, GPIO_NO_PULL,GPIO_2MA), GPIO_ENABLE);
//	gpio_tlmm_config(GPIO_CFG(TSP_SDA, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,
//				GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	gpio_direction_output(TSP_SDA, 1);

}

#ifdef RESET_MODE
// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetXRESStrong()
// Set external reset (XRES) to an output (Strong drive mode).
// ****************************************************************************
void SetXRESStrong(void)
{
    PRT2DM0 |=  XRES_PIN;
    PRT2DM1 &= ~XRES_PIN;
    PRT2DM2 &= ~XRES_PIN;
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// AssertXRES()
// Set XRES pin High
// ****************************************************************************
void AssertXRES(void)
{
    PRT2DR |= XRES_PIN;
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// DeassertXRES()
// Set XRES pin low.
// ****************************************************************************
void DeassertXRES(void)
{
    PRT2DR &= ~XRES_PIN;
}
#else

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// SetTargetVDDStrong()
// Set VDD pin (PWR) to an output (Strong drive mode).
// ****************************************************************************
// voltage GPIO to output  
// to do
void SetTargetVDDStrong(void)
{
// return nothing
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// ApplyTargetVDD()
// Provide power to the target PSoC's Vdd pin through a GPIO.
// ****************************************************************************
// voltage GPIO to HIGH // power on
// to do
void ApplyTargetVDD(void)
{
	struct vreg *vreg_touch;
	
	vreg_touch = vreg_get(NULL, "ldo6");
	vreg_enable(vreg_touch);
}

// ********************* LOW-LEVEL ISSP SUBROUTINE SECTION ********************
// ****************************************************************************
// ****                        PROCESSOR SPECIFIC                          ****
// ****************************************************************************
// ****                      USER ATTENTION REQUIRED                       ****
// ****************************************************************************
// RemoveTargetVDD()
// Remove power from the target PSoC's Vdd pin.
// ****************************************************************************
// voltage GPIO to LOW // power off
// to do
void RemoveTargetVDD(void)
{
	struct vreg *vreg_touch;
	
	vreg_touch = vreg_get(NULL, "ldo6");
	vreg_disable(vreg_touch);
}
#endif
//end of file ISSP_Drive_Routines.c

#endif  //(PROJECT_REV_)
//end of file ISSP_Drive_Routines.c
