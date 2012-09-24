
#ifndef _SAMSUNG_SXGA_H_
#define _SAMSUNG_SXGA_H_

/*******************************************************************************************
 #  Display resolution standards #

	QCIF: 176 x 144
	CIF: 352 x 288
	QVGA: 320 x 240
	VGA: 640 x 480 
	SVGA: 800 x 600 
	XGA: 1024 x 768 
	WXGA: 1280 x 800 
	QVGA: 1280 x 960 
	SXGA: 1280 x 1024 
	SXGA+: 1400 x 1050 
	WSXGA+: 1680 x 1050 
	UXGA: 1600 x 1200 
	WUXGA: 1920 x 1200 
	QXGA: 2048 x 1536
********************************************************************************************/
/*  PCAM  */

//#define PCAM_ENABLE_DEBUG // ON/OFF

#ifdef PCAM_ENABLE_DEBUG
#define PCAM_DEBUG(fmt, arg...)  \
                do{\
                printk("\n\033[1;37;44m<=PCAM=>%s:%d: " fmt "\033[0m", __FUNCTION__, __LINE__, ##arg);}\
                while(0)
#else
#define PCAM_DEBUG(fmt, arg...)  
#endif



#define PCAM_AUTO_TUNNING               0
#define PCAM_SDCARD_DETECT              1
#define PCAM_GET_INFO		        2
#define PCAM_FRAME_CONTROL              3
#define PCAM_AF_CONTROL                 4
#define PCAM_EFFECT_CONTROL             5
#define PCAM_WB_CONTROL                 6
#define PCAM_BR_CONTROL                 7
#define PCAM_ISO_CONTROL                8
#define PCAM_METERING_CONTROL           9
#define PCAM_SCENE_CONTROL		10
#define PCAM_AWB_AE_CONTROL		11
#define PCAM_CR_CONTROL                 12
#define PCAM_SA_CONTROL                 13
#define PCAM_SP_CONTROL                 14
#define PCAM_CPU_CONTROL                15
#define PCAM_DTP_CONTROL                16
#define PCAM_SET_PREVIEW_SIZE           17


#define PCAM_FRAME_AUTO			0
#define PCAM_FRAME_FIX_15		1
#define PCAM_FRAME_FIX_30		2


#define PCAM_EFFECT_NORMAL		0
#define PCAM_EFFECT_NEGATIVE		1
#define PCAM_EFFECT_MONO		2
#define PCAM_EFFECT_SEPIA		3	


#define PCAM_WB_AUTO                    0
#define PCAM_WB_DAYLIGHT                1
#define PCAM_WB_CLOUDY                  2
#define PCAM_WB_FLUORESCENT             3
#define PCAM_WB_INCANDESCENT            4


#define PCAM_BR_STEP_P_4                4
#define PCAM_BR_STEP_P_3                3
#define PCAM_BR_STEP_P_2                2
#define PCAM_BR_STEP_P_1                1
#define PCAM_BR_STEP_0                  0
#define PCAM_BR_STEP_M_1                255//-1
#define PCAM_BR_STEP_M_2                254//-2
#define PCAM_BR_STEP_M_3                253//-3
#define PCAM_BR_STEP_M_4                252//-4

#define PCAM_CR_STEP_P_2                4
#define PCAM_CR_STEP_P_1                3
#define PCAM_CR_STEP_0                  2
#define PCAM_CR_STEP_M_1                1
#define PCAM_CR_STEP_M_2                0

#define PCAM_SA_STEP_P_2                4
#define PCAM_SA_STEP_P_1                3
#define PCAM_SA_STEP_0                  2
#define PCAM_SA_STEP_M_1                1
#define PCAM_SA_STEP_M_2                0

#define PCAM_SP_STEP_P_2                4
#define PCAM_SP_STEP_P_1                3
#define PCAM_SP_STEP_0                  2
#define PCAM_SP_STEP_M_1                1
#define PCAM_SP_STEP_M_2                0




#define PCAM_ISO_AUTO			0
#define PCAM_ISO_50			1
#define PCAM_ISO_100			2
#define PCAM_ISO_200			3
#define PCAM_ISO_400			4


#define PCAM_METERING_NORMAL		0 //CENTER?
#define PCAM_METERING_SPOT		1
#define PCAM_METERING_CENTER		2


#define PCAM_SCENE_OFF			0
#define PCAM_SCENE_PORTRAIT		1
#define PCAM_SCENE_LANDSCAPE		2
#define PCAM_SCENE_SPORTS		3
#define PCAM_SCENE_PARTY		4
#define PCAM_SCENE_BEACH		5
#define PCAM_SCENE_SUNSET		6
#define PCAM_SCENE_DAWN			7
#define PCAM_SCENE_FALL			8
#define PCAM_SCENE_NIGHTSHOT		9
#define PCAM_SCENE_BACKLIGHT		10
#define PCAM_SCENE_FIREWORK		11
#define PCAM_SCENE_TEXT			12
#define PCAM_SCENE_CANDLE		13



#define PCAM_AF_CHECK_STATUS		0
#define PCAM_AF_OFF			1
#define PCAM_AF_SET_NORMAL		2
#define PCAM_AF_SET_MACRO		3
#define PCAM_AF_DO			4
#define PCAM_AF_SET_MANUAL	5



#define PCAM_AF_PROGRESS                1
#define PCAM_AF_SUCCESS                 2
#define PCAM_AF_LOWCONF                 3 //Fail
#define PCAM_AF_CANCELED                4
#define PCAM_AF_TIMEOUT                 5


#define PCAM_AWB_AE_LOCK		0
#define PCAM_AWB_AE_UNLOCK		1


#define PCAM_CPU_CONSERVATIVE		0
#define PCAM_CPU_ONDEMAND		1
#define PCAM_CPU_PERFORMANCE		2		

#define PCAM_DTP_OFF			0
#define PCAM_DTP_ON			1

//for PCAM_SET_PREVIEW_SIZE
#define PCAM_CAMERA_MODE			0
#define PCAM_CAMCORDER_MODE		1

                                                                  
                                                                                
typedef struct samsung_short_t{
        unsigned short subaddr;
        unsigned short value;
//        unsigned short page;
} s5k5ccff_short_t;


				
s5k5ccff_short_t s5k5ccff_init0[] = 
{
//****************************************/
{0xFCFC, 0xD000},
//****************************************/
//===================================================================
// History
//===================================================================
//20100717 : 1st release
//20100806 : 2nd release for EVT0.1
//20101028 : 3rd release for EVT1
//WRITE #awbb_otp_disable  0000 //awb otp use
//==========================================================================================
//-->The below registers are for FACTORY ONLY. if you change them without prior notification,
//   YOU are RESPONSIBLE for the FAILURE that will happen in the future.
//==========================================================================================
//===================================================================
// Reset & Trap and Patch
//===================================================================

// Start of Trap and Patch
//  2010-08-11 13:53:35
{0x0010, 0x0001},
{0x1030, 0x0000},
{0x0014, 0x0001},

{0xFFFF, 0x000A},						//Delay 10ms

// Start of Patch data
{0x0028, 0x7000},
{0x002A, 0x352C},
{0x0F12, 0xB510},                                    // 7000352C 
{0x0F12, 0x4A22},	// 7000352E 
{0x0F12, 0x213B},	// 70003530 
{0x0F12, 0x4822},	// 70003532 
{0x0F12, 0x4C22},	// 70003534 
{0x0F12, 0x2300},	// 70003536 
{0x0F12, 0x8023},	// 70003538 
{0x0F12, 0xC004},	// 7000353A 
{0x0F12, 0x6001},                                    // 7000353C 
{0x0F12, 0x4921},	// 7000353E 
{0x0F12, 0x4821},	// 70003540 
{0x0F12, 0xF000},	// 70003542 
{0x0F12, 0xF9C7},	// 70003544 
{0x0F12, 0x2115},	// 70003546 
{0x0F12, 0x4820},	// 70003548 
{0x0F12, 0x01C9},	// 7000354A 
{0x0F12, 0xF000},	// 7000354C 
{0x0F12, 0xF864},	// 7000354E 
{0x0F12, 0x481E},	// 70003550 
{0x0F12, 0x210B},	// 70003552 
{0x0F12, 0x0189},	// 70003554 
{0x0F12, 0x3018},	// 70003556 
{0x0F12, 0xF000},	// 70003558 
{0x0F12, 0xF85E},	// 7000355A 
{0x0F12, 0x481B},	// 7000355C 
{0x0F12, 0x491C},	// 7000355E 
{0x0F12, 0x300C},	// 70003560 
{0x0F12, 0xF000},	// 70003562 
{0x0F12, 0xF859},	// 70003564 
{0x0F12, 0x4819},	// 70003566 
{0x0F12, 0x491A},	// 70003568 
{0x0F12, 0x3010},	// 7000356A 
{0x0F12, 0xF000},	// 7000356C 
{0x0F12, 0xF854},	// 7000356E 
{0x0F12, 0x4919},	// 70003570 
{0x0F12, 0x481A},	// 70003572 
{0x0F12, 0xF000},	// 70003574 
{0x0F12, 0xF9AE},	// 70003576 
{0x0F12, 0x4919},	// 70003578 
{0x0F12, 0x481A},	// 7000357A 
{0x0F12, 0xF000},	// 7000357C 
{0x0F12, 0xF9AA},	// 7000357E 
{0x0F12, 0x4919},	// 70003580 
{0x0F12, 0x481A},	// 70003582 
{0x0F12, 0xF000},	// 70003584 
{0x0F12, 0xF9A6},	// 70003586 
{0x0F12, 0x4919},	// 70003588 
{0x0F12, 0x481A},	// 7000358A 
{0x0F12, 0xF000},	// 7000358C 
{0x0F12, 0xF9A2},	// 7000358E 
{0x0F12, 0x4919},	// 70003590 
{0x0F12, 0x481A},	// 70003592 
{0x0F12, 0xF000},	// 70003594 
{0x0F12, 0xF99E},	// 70003596 
{0x0F12, 0x4919},	// 70003598 
{0x0F12, 0x481A},	// 7000359A 
{0x0F12, 0xF000},	// 7000359C 
{0x0F12, 0xF99A},	// 7000359E 
{0x0F12, 0x4919},	// 700035A0 
{0x0F12, 0x481A},	// 700035A2 
{0x0F12, 0xF000},	// 700035A4 
{0x0F12, 0xF996},	// 700035A6 
{0x0F12, 0x4919},	// 700035A8 
{0x0F12, 0x481A},	// 700035AA 
{0x0F12, 0xF000},	// 700035AC 
{0x0F12, 0xF992},	// 700035AE 
{0x0F12, 0xBC10},	// 700035B0 
{0x0F12, 0xBC08},	// 700035B2 
{0x0F12, 0x4718},	// 700035B4 
{0x0F12, 0x0000},                                    // 700035B6 
{0x0F12, 0x00B5},	// 700035B8 
{0x0F12, 0x5CC1},	// 700035BA 
{0x0F12, 0x1C08},	// 700035BC 
{0x0F12, 0x7000},	// 700035BE 
{0x0F12, 0x3290},	// 700035C0 
{0x0F12, 0x7000},                                    // 700035C2 
{0x0F12, 0x3637},	// 700035C4 
{0x0F12, 0x7000},	// 700035C6 
{0x0F12, 0xD9E7},	// 700035C8 
{0x0F12, 0x0000},	// 700035CA 
{0x0F12, 0x6FC0},	// 700035CC 
{0x0F12, 0x0000},                                    // 700035CE 
{0x0F12, 0x0A91},	// 700035D0 
{0x0F12, 0x0000},	// 700035D2 
{0x0F12, 0x02C9},	// 700035D4 
{0x0F12, 0x0000},                                    // 700035D6 
{0x0F12, 0x366F},	// 700035D8 
{0x0F12, 0x7000},                                    // 700035DA 
{0x0F12, 0xA607},	// 700035DC 
{0x0F12, 0x0000},                                    // 700035DE 
{0x0F12, 0x36DF},	// 700035E0 
{0x0F12, 0x7000},	// 700035E2 
{0x0F12, 0x7C0D},	// 700035E4 
{0x0F12, 0x0000},	// 700035E6 
{0x0F12, 0x36FB},	// 700035E8 
{0x0F12, 0x7000},	// 700035EA 
{0x0F12, 0x7C2B},	// 700035EC 
{0x0F12, 0x0000},	// 700035EE 
{0x0F12, 0x3717},	// 700035F0 
{0x0F12, 0x7000},	// 700035F2 
{0x0F12, 0x9E89},	// 700035F4 
{0x0F12, 0x0000},	// 700035F6 
{0x0F12, 0x375F},	// 700035F8 
{0x0F12, 0x7000},	// 700035FA 
{0x0F12, 0x495F},	// 700035FC 
{0x0F12, 0x0000},	// 700035FE 
{0x0F12, 0x37B9},	// 70003600 
{0x0F12, 0x7000},	// 70003602 
{0x0F12, 0xE421},	// 70003604 
{0x0F12, 0x0000},	// 70003606 
{0x0F12, 0x37F3},	// 70003608 
{0x0F12, 0x7000},	// 7000360A 
{0x0F12, 0x216D},	// 7000360C 
{0x0F12, 0x0000},	// 7000360E 
{0x0F12, 0x3867},	// 70003610 
{0x0F12, 0x7000},	// 70003612 
{0x0F12, 0x0179},	// 70003614 
{0x0F12, 0x0001},	// 70003616 
{0x0F12, 0xB570},	// 70003618 
{0x0F12, 0x000D},	// 7000361A 
{0x0F12, 0x4C9A},	// 7000361C 
{0x0F12, 0x8821},	// 7000361E 
{0x0F12, 0xF000},	// 70003620 
{0x0F12, 0xF960},	// 70003622 
{0x0F12, 0x8820},	// 70003624 
{0x0F12, 0x4A99},	// 70003626 
{0x0F12, 0x0081},	// 70003628 
{0x0F12, 0x5055},	// 7000362A 
{0x0F12, 0x1C40},	// 7000362C 
{0x0F12, 0x8020},	// 7000362E 
{0x0F12, 0xBC70},	// 70003630 
{0x0F12, 0xBC08},	// 70003632 
{0x0F12, 0x4718},	// 70003634 
{0x0F12, 0x6801},	// 70003636 
{0x0F12, 0x0409},	// 70003638 
{0x0F12, 0x0C09},	// 7000363A 
{0x0F12, 0x6840},	// 7000363C 
{0x0F12, 0x0400},	// 7000363E 
{0x0F12, 0x0C00},	// 70003640 
{0x0F12, 0x4A93},	// 70003642 
{0x0F12, 0x8992},	// 70003644 
{0x0F12, 0x2A00},	// 70003646 
{0x0F12, 0xD00D},	// 70003648 
{0x0F12, 0x2300},	// 7000364A 
{0x0F12, 0x1A80},	// 7000364C 
{0x0F12, 0xD400},	// 7000364E 
{0x0F12, 0x0003},	// 70003650 
{0x0F12, 0x0418},	// 70003652 
{0x0F12, 0x0C00},	// 70003654 
{0x0F12, 0x4B8F},	// 70003656 
{0x0F12, 0x1851},	// 70003658 
{0x0F12, 0x891B},	// 7000365A 
{0x0F12, 0x428B},	// 7000365C 
{0x0F12, 0xD300},	// 7000365E 
{0x0F12, 0x000B},	// 70003660 
{0x0F12, 0x0419},	// 70003662 
{0x0F12, 0x0C09},	// 70003664 
{0x0F12, 0x4A8C},	// 70003666 
{0x0F12, 0x8151},	// 70003668 
{0x0F12, 0x8190},	// 7000366A 
{0x0F12, 0x4770},	// 7000366C 
{0x0F12, 0xB510},	// 7000366E 
{0x0F12, 0x488A},	// 70003670 
{0x0F12, 0x4C8B},	// 70003672 
{0x0F12, 0x88C1},	// 70003674 
{0x0F12, 0x8061},	// 70003676 
{0x0F12, 0x2101},	// 70003678 
{0x0F12, 0x8021},	// 7000367A 
{0x0F12, 0x8840},	// 7000367C 
{0x0F12, 0xF000},	// 7000367E 
{0x0F12, 0xF939},	// 70003680 
{0x0F12, 0x88E0},	// 70003682 
{0x0F12, 0x4A87},	// 70003684 
{0x0F12, 0x2800},	// 70003686 
{0x0F12, 0xD003},	// 70003688 
{0x0F12, 0x4987},	// 7000368A 
{0x0F12, 0x8849},	// 7000368C 
{0x0F12, 0x2900},	// 7000368E 
{0x0F12, 0xD009},	// 70003690 
{0x0F12, 0x2001},	// 70003692 
{0x0F12, 0x03C0},	// 70003694 
{0x0F12, 0x8050},	// 70003696 
{0x0F12, 0x80D0},	// 70003698 
{0x0F12, 0x2000},	// 7000369A 
{0x0F12, 0x8090},	// 7000369C 
{0x0F12, 0x8110},	// 7000369E 
{0x0F12, 0xBC10},	// 700036A0 
{0x0F12, 0xBC08},	// 700036A2 
{0x0F12, 0x4718},	// 700036A4 
{0x0F12, 0x8050},	// 700036A6 
{0x0F12, 0x8920},	// 700036A8 
{0x0F12, 0x80D0},	// 700036AA 
{0x0F12, 0x8960},	// 700036AC 
{0x0F12, 0x0400},	// 700036AE 
{0x0F12, 0x1400},	// 700036B0 
{0x0F12, 0x8090},	// 700036B2 
{0x0F12, 0x89A1},	// 700036B4 
{0x0F12, 0x0409},	// 700036B6 
{0x0F12, 0x1409},	// 700036B8 
{0x0F12, 0x8111},	// 700036BA 
{0x0F12, 0x89E3},	// 700036BC 
{0x0F12, 0x8A24},	// 700036BE 
{0x0F12, 0x2B00},	// 700036C0 
{0x0F12, 0xD104},	// 700036C2 
{0x0F12, 0x17C3},	// 700036C4 
{0x0F12, 0x0F5B},	// 700036C6 
{0x0F12, 0x1818},	// 700036C8 
{0x0F12, 0x10C0},	// 700036CA 
{0x0F12, 0x8090},	// 700036CC 
{0x0F12, 0x2C00},	// 700036CE 
{0x0F12, 0xD1E6},	// 700036D0 
{0x0F12, 0x17C8},	// 700036D2 
{0x0F12, 0x0F40},	// 700036D4 
{0x0F12, 0x1840},	// 700036D6 
{0x0F12, 0x10C0},	// 700036D8 
{0x0F12, 0x8110},	// 700036DA 
{0x0F12, 0xE7E0},	// 700036DC 
{0x0F12, 0xB510},                                    // 700036DE 
{0x0F12, 0x0004},                                    // 700036E0 
{0x0F12, 0x4970},	// 700036E2 
{0x0F12, 0x2204},	// 700036E4 
{0x0F12, 0x6820},	// 700036E6 
{0x0F12, 0x5E8A},	// 700036E8 
{0x0F12, 0x0140},	// 700036EA 
{0x0F12, 0x1A80},	// 700036EC 
{0x0F12, 0x0280},	// 700036EE 
{0x0F12, 0x8849},	// 700036F0 
{0x0F12, 0xF000},	// 700036F2 
{0x0F12, 0xF907},	// 700036F4 
{0x0F12, 0x6020},	// 700036F6 
{0x0F12, 0xE7D2},	// 700036F8 
{0x0F12, 0xB510},	// 700036FA 
{0x0F12, 0x0004},	// 700036FC 
{0x0F12, 0x4969},	// 700036FE 
{0x0F12, 0x2208},	// 70003700 
{0x0F12, 0x6820},	// 70003702 
{0x0F12, 0x5E8A},	// 70003704 
{0x0F12, 0x0140},	// 70003706 
{0x0F12, 0x1A80},	// 70003708 
{0x0F12, 0x0280},	// 7000370A 
{0x0F12, 0x88C9},	// 7000370C 
{0x0F12, 0xF000},	// 7000370E 
{0x0F12, 0xF8F9},	// 70003710 
{0x0F12, 0x6020},	// 70003712 
{0x0F12, 0xE7C4},	// 70003714 
{0x0F12, 0xB510},	// 70003716 
{0x0F12, 0x0004},	// 70003718 
{0x0F12, 0x4962},	// 7000371A 
{0x0F12, 0x4863},	// 7000371C 
{0x0F12, 0x884A},	// 7000371E 
{0x0F12, 0x8B43},	// 70003720 
{0x0F12, 0x435A},	// 70003722 
{0x0F12, 0x2304},	// 70003724 
{0x0F12, 0x5ECB},	// 70003726 
{0x0F12, 0x0A92},	// 70003728 
{0x0F12, 0x18D2},	// 7000372A 
{0x0F12, 0x02D2},	// 7000372C 
{0x0F12, 0x0C12},	// 7000372E 
{0x0F12, 0x88CB},	// 70003730 
{0x0F12, 0x8B80},	// 70003732 
{0x0F12, 0x4343},	// 70003734 
{0x0F12, 0x0A98},	// 70003736 
{0x0F12, 0x2308},	// 70003738 
{0x0F12, 0x5ECB},	// 7000373A 
{0x0F12, 0x18C0},	// 7000373C 
{0x0F12, 0x02C0},	// 7000373E 
{0x0F12, 0x0C00},	// 70003740 
{0x0F12, 0x0411},	// 70003742 
{0x0F12, 0x0400},	// 70003744 
{0x0F12, 0x1409},	// 70003746 
{0x0F12, 0x1400},	// 70003748 
{0x0F12, 0x1A08},	// 7000374A 
{0x0F12, 0x4957},	// 7000374C 
{0x0F12, 0x3980},	// 7000374E 
{0x0F12, 0x6348},	// 70003750 
{0x0F12, 0x0020},	// 70003752 
{0x0F12, 0xC80F},	// 70003754 
{0x0F12, 0xF000},	// 70003756 
{0x0F12, 0xF8DB},	// 70003758 
{0x0F12, 0x6020},	// 7000375A 
{0x0F12, 0xE7A0},	// 7000375C 
{0x0F12, 0xB510},	// 7000375E 
{0x0F12, 0x4C53},	// 70003760 
{0x0F12, 0x4854},	// 70003762 
{0x0F12, 0x78A1},	// 70003764 
{0x0F12, 0x2900},	// 70003766 
{0x0F12, 0xD101},	// 70003768 
{0x0F12, 0x87C1},	// 7000376A 
{0x0F12, 0xE004},	// 7000376C 
{0x0F12, 0x7AE1},	// 7000376E 
{0x0F12, 0x2900},	// 70003770 
{0x0F12, 0xD001},	// 70003772 
{0x0F12, 0x2101},	// 70003774 
{0x0F12, 0x87C1},	// 70003776 
{0x0F12, 0xF000},	// 70003778 
{0x0F12, 0xF8D2},	// 7000377A 
{0x0F12, 0x494E},	// 7000377C 
{0x0F12, 0x8B08},	// 7000377E 
{0x0F12, 0x06C2},	// 70003780 
{0x0F12, 0xD50A},	// 70003782 
{0x0F12, 0x7AA2},	// 70003784 
{0x0F12, 0x0652},	// 70003786 
{0x0F12, 0xD507},	// 70003788 
{0x0F12, 0x2210},	// 7000378A 
{0x0F12, 0x4390},	// 7000378C 
{0x0F12, 0x8308},	// 7000378E 
{0x0F12, 0x484A},	// 70003790 
{0x0F12, 0x7AE1},	// 70003792 
{0x0F12, 0x6B00},	// 70003794 
{0x0F12, 0xF000},	// 70003796 
{0x0F12, 0xF8CB},	// 70003798 
{0x0F12, 0x483D},	// 7000379A 
{0x0F12, 0x89C0},	// 7000379C 
{0x0F12, 0x2801},	// 7000379E 
{0x0F12, 0xD109},	// 700037A0 
{0x0F12, 0x78A0},	// 700037A2 
{0x0F12, 0x2800},	// 700037A4 
{0x0F12, 0xD006},	// 700037A6 
{0x0F12, 0x7AE0},	// 700037A8 
{0x0F12, 0x2800},	// 700037AA 
{0x0F12, 0xD003},	// 700037AC 
{0x0F12, 0x7AA0},	// 700037AE 
{0x0F12, 0x2140},	// 700037B0 
{0x0F12, 0x4308},	// 700037B2 
{0x0F12, 0x72A0},	// 700037B4 
{0x0F12, 0xE773},	// 700037B6 
{0x0F12, 0xB570},	// 700037B8 
{0x0F12, 0x4D3F},	// 700037BA 
{0x0F12, 0x4C3F},	// 700037BC 
{0x0F12, 0x8B28},	// 700037BE 
{0x0F12, 0x0701},	// 700037C0 
{0x0F12, 0xD507},	// 700037C2 
{0x0F12, 0x2108},	// 700037C4 
{0x0F12, 0x4388},	// 700037C6 
{0x0F12, 0x8328},	// 700037C8 
{0x0F12, 0x493D},	// 700037CA 
{0x0F12, 0x6B20},	// 700037CC 
{0x0F12, 0x6B89},	// 700037CE 
{0x0F12, 0xF000},	// 700037D0 
{0x0F12, 0xF8B6},	// 700037D2 
{0x0F12, 0x8B28},	// 700037D4 
{0x0F12, 0x06C1},	// 700037D6 
{0x0F12, 0xD50A},	// 700037D8 
{0x0F12, 0x4935},	// 700037DA 
{0x0F12, 0x7A8A},	// 700037DC 
{0x0F12, 0x0652},	// 700037DE 
{0x0F12, 0xD406},	// 700037E0 
{0x0F12, 0x2210},	// 700037E2 
{0x0F12, 0x4390},	// 700037E4 
{0x0F12, 0x8328},	// 700037E6 
{0x0F12, 0x7AC9},	// 700037E8 
{0x0F12, 0x6B20},	// 700037EA 
{0x0F12, 0xF000},	// 700037EC 
{0x0F12, 0xF8A0},	// 700037EE 
{0x0F12, 0xE71E},	// 700037F0 
{0x0F12, 0xB570},	// 700037F2 
{0x0F12, 0x4C33},	// 700037F4 
{0x0F12, 0x8860},	// 700037F6 
{0x0F12, 0x2800},	// 700037F8 
{0x0F12, 0xD00C},	// 700037FA 
{0x0F12, 0x8820},	// 700037FC 
{0x0F12, 0x4D2C},	// 700037FE 
{0x0F12, 0x2800},	// 70003800 
{0x0F12, 0xD009},	// 70003802 
{0x0F12, 0x0029},	// 70003804 
{0x0F12, 0x31A0},	// 70003806 
{0x0F12, 0x7AC9},	// 70003808 
{0x0F12, 0x2900},	// 7000380A 
{0x0F12, 0xD004},	// 7000380C 
{0x0F12, 0x7AA8},	// 7000380E 
{0x0F12, 0x2180},	// 70003810 
{0x0F12, 0x4308},	// 70003812 
{0x0F12, 0x72A8},	// 70003814 
{0x0F12, 0xE70B},	// 70003816 
{0x0F12, 0x2800},	// 70003818 
{0x0F12, 0xD003},	// 7000381A 
{0x0F12, 0xF000},	// 7000381C 
{0x0F12, 0xF898},	// 7000381E 
{0x0F12, 0x2800},	// 70003820 
{0x0F12, 0xD1F8},	// 70003822 
{0x0F12, 0x2000},	// 70003824 
{0x0F12, 0x8060},	// 70003826 
{0x0F12, 0x8820},	// 70003828 
{0x0F12, 0x2800},	// 7000382A 
{0x0F12, 0xD003},	// 7000382C 
{0x0F12, 0x2008},	// 7000382E 
{0x0F12, 0xF000},	// 70003830 
{0x0F12, 0xF896},	// 70003832 
{0x0F12, 0xE00B},	// 70003834 
{0x0F12, 0x4823},	// 70003836 
{0x0F12, 0x3020},	// 70003838 
{0x0F12, 0x8880},	// 7000383A 
{0x0F12, 0x2800},	// 7000383C 
{0x0F12, 0xD103},	// 7000383E 
{0x0F12, 0x7AA8},	// 70003840 
{0x0F12, 0x2101},	// 70003842 
{0x0F12, 0x4308},	// 70003844 
{0x0F12, 0x72A8},	// 70003846 
{0x0F12, 0x2010},	// 70003848 
{0x0F12, 0xF000},	// 7000384A 
{0x0F12, 0xF889},	// 7000384C 
{0x0F12, 0x8820},	// 7000384E 
{0x0F12, 0x2800},	// 70003850 
{0x0F12, 0xD1E0},	// 70003852 
{0x0F12, 0x480E},	// 70003854 
{0x0F12, 0x89C0},	// 70003856 
{0x0F12, 0x2801},	// 70003858 
{0x0F12, 0xD1DC},	// 7000385A 
{0x0F12, 0x7AA8},	// 7000385C 
{0x0F12, 0x21BF},	// 7000385E 
{0x0F12, 0x4008},	// 70003860 
{0x0F12, 0x72A8},	// 70003862 
{0x0F12, 0xE6E4},	// 70003864 
{0x0F12, 0x6800},	// 70003866 
{0x0F12, 0x4917},	// 70003868 
{0x0F12, 0x8188},	// 7000386A 
{0x0F12, 0x4817},	// 7000386C 
{0x0F12, 0x2201},	// 7000386E 
{0x0F12, 0x8981},	// 70003870 
{0x0F12, 0x4817},	// 70003872 
{0x0F12, 0x0252},	// 70003874 
{0x0F12, 0x4291},	// 70003876 
{0x0F12, 0xD902},	// 70003878 
{0x0F12, 0x2102},	// 7000387A 
{0x0F12, 0x8181},	// 7000387C 
{0x0F12, 0x4770},	// 7000387E 
{0x0F12, 0x2101},	// 70003880 
{0x0F12, 0x8181},	// 70003882 
{0x0F12, 0x4770},	// 70003884 
{0x0F12, 0x0000},	// 70003886 
{0x0F12, 0x3290},	// 70003888 
{0x0F12, 0x7000},	// 7000388A 
{0x0F12, 0x3294},	// 7000388C 
{0x0F12, 0x7000},	// 7000388E 
{0x0F12, 0x04A8},	// 70003890 
{0x0F12, 0x7000},	// 70003892 
{0x0F12, 0x15DC},	// 70003894 
{0x0F12, 0x7000},	// 70003896 
{0x0F12, 0x5000},	// 70003898 
{0x0F12, 0xD000},	// 7000389A 
{0x0F12, 0x064C},	// 7000389C 
{0x0F12, 0x7000},	// 7000389E 
{0x0F12, 0xA000},	// 700038A0 
{0x0F12, 0xD000},	// 700038A2 
{0x0F12, 0x2468},	// 700038A4 
{0x0F12, 0x7000},	// 700038A6 
{0x0F12, 0x11DC},	// 700038A8 
{0x0F12, 0x7000},	// 700038AA 
{0x0F12, 0x2828},	// 700038AC 
{0x0F12, 0x7000},	// 700038AE 
{0x0F12, 0x1E84},	// 700038B0 
{0x0F12, 0x7000},	// 700038B2 
{0x0F12, 0x1BE4},	// 700038B4 
{0x0F12, 0x7000},	// 700038B6 
{0x0F12, 0x2EA8},	// 700038B8 
{0x0F12, 0x7000},	// 700038BA 
{0x0F12, 0x21A4},	// 700038BC 
{0x0F12, 0x7000},	// 700038BE 
{0x0F12, 0x0100},	// 700038C0 
{0x0F12, 0x7000},	// 700038C2 
{0x0F12, 0x01E8},	// 700038C4 
{0x0F12, 0x7000},	// 700038C6 
{0x0F12, 0xF2A0},	// 700038C8 
{0x0F12, 0xD000},	// 700038CA 
{0x0F12, 0x2A44},	// 700038CC 
{0x0F12, 0x7000},	// 700038CE 
{0x0F12, 0xF400},	// 700038D0 
{0x0F12, 0xD000},	// 700038D2 
{0x0F12, 0x4778},	// 700038D4 
{0x0F12, 0x46C0},	// 700038D6 
{0x0F12, 0xC000},	// 700038D8 
{0x0F12, 0xE59F},	// 700038DA 
{0x0F12, 0xFF1C},	// 700038DC 
{0x0F12, 0xE12F},	// 700038DE 
{0x0F12, 0x1F63},	// 700038E0 
{0x0F12, 0x0001},	// 700038E2 
{0x0F12, 0x4778},	// 700038E4 
{0x0F12, 0x46C0},	// 700038E6 
{0x0F12, 0xC000},	// 700038E8 
{0x0F12, 0xE59F},	// 700038EA 
{0x0F12, 0xFF1C},	// 700038EC 
{0x0F12, 0xE12F},	// 700038EE 
{0x0F12, 0x1EDF},	// 700038F0 
{0x0F12, 0x0001},	// 700038F2 
{0x0F12, 0x4778},	// 700038F4 
{0x0F12, 0x46C0},	// 700038F6 
{0x0F12, 0xC000},	// 700038F8 
{0x0F12, 0xE59F},	// 700038FA 
{0x0F12, 0xFF1C},	// 700038FC 
{0x0F12, 0xE12F},	// 700038FE 
{0x0F12, 0xFDAF},	// 70003900 
{0x0F12, 0x0000},	// 70003902 
{0x0F12, 0x4778},	// 70003904 
{0x0F12, 0x46C0},	// 70003906 
{0x0F12, 0xF004},	// 70003908 
{0x0F12, 0xE51F},	// 7000390A 
{0x0F12, 0x2328},	// 7000390C 
{0x0F12, 0x0001},	// 7000390E 
{0x0F12, 0x4778},	// 70003910 
{0x0F12, 0x46C0},	// 70003912 
{0x0F12, 0xC000},	// 70003914 
{0x0F12, 0xE59F},	// 70003916 
{0x0F12, 0xFF1C},	// 70003918 
{0x0F12, 0xE12F},	// 7000391A 
{0x0F12, 0x9E89},	// 7000391C 
{0x0F12, 0x0000},	// 7000391E 
{0x0F12, 0x4778},	// 70003920 
{0x0F12, 0x46C0},	// 70003922 
{0x0F12, 0xC000},	// 70003924 
{0x0F12, 0xE59F},	// 70003926 
{0x0F12, 0xFF1C},	// 70003928 
{0x0F12, 0xE12F},	// 7000392A 
{0x0F12, 0x495F},	// 7000392C 
{0x0F12, 0x0000},	// 7000392E 
{0x0F12, 0x4778},	// 70003930 
{0x0F12, 0x46C0},	// 70003932 
{0x0F12, 0xC000},	// 70003934 
{0x0F12, 0xE59F},	// 70003936 
{0x0F12, 0xFF1C},	// 70003938 
{0x0F12, 0xE12F},	// 7000393A 
{0x0F12, 0xE403},	// 7000393C 
{0x0F12, 0x0000},	// 7000393E 
{0x0F12, 0x4778},	// 70003940 
{0x0F12, 0x46C0},	// 70003942 
{0x0F12, 0xC000},	// 70003944 
{0x0F12, 0xE59F},	// 70003946 
{0x0F12, 0xFF1C},	// 70003948 
{0x0F12, 0xE12F},	// 7000394A 
{0x0F12, 0x24B3},	// 7000394C 
{0x0F12, 0x0001},	// 7000394E 
{0x0F12, 0x4778},	// 70003950 
{0x0F12, 0x46C0},	// 70003952 
{0x0F12, 0xC000},	// 70003954 
{0x0F12, 0xE59F},	// 70003956 
{0x0F12, 0xFF1C},	// 70003958 
{0x0F12, 0xE12F},	// 7000395A 
{0x0F12, 0xFCB5},	// 7000395C 
{0x0F12, 0x0000},	// 7000395E 
{0x0F12, 0x4778},	// 70003960 
{0x0F12, 0x46C0},	// 70003962 
{0x0F12, 0xC000},	// 70003964 
{0x0F12, 0xE59F},	// 70003966 
{0x0F12, 0xFF1C},	// 70003968 
{0x0F12, 0xE12F},	// 7000396A 
{0x0F12, 0x12DF},	// 7000396C 
{0x0F12, 0x0000},	// 7000396E 
// End of Patch Data(Last : 7000396Eh)
// Total Size 1092 (0x0444)
// Addr : 352C , Size : 1090(442h) 
{0x1000, 0x0001},

/// following TnP was included
/// USER_MBCV_CONTROL		0x00000001
///  --> "M_oif_usELFMaxPacketSize" This register was used for MBCV TnP
/// AWB_MODUL_COMP			0x00000002

{0x0028, 0x7000},
{0x002A, 0x04B4},
{0x0F12, 0x0064},             

// AFIT by Normalized Brightness Tuning parameter
{0x0028, 0x7000},
{0x002A, 0x3302},
{0x0F12, 0x0000},	// on/off AFIT by NB option

{0x0F12, 0x0005},	//0014	// NormBR[0]
{0x0F12, 0x0019},	//00D2	// NormBR[1]
{0x0F12, 0x0050},	//0384	// NormBR[2]
{0x0F12, 0x0300},	//07D0	// NormBR[3]
{0x0F12, 0x0375},	//1388	// NormBR[4]

///////////////////////////////////
// Analog & APS settings         
// This register is for FACTORY ONLY. If you change it without prior notification        
// YOU are RESPONSIBLE for the FAILURE that will happen in the future          
///////////////////////////////////
//========================================================================================
// 5CC EVT0 analog register setting
// '10.07.14. Initial Draft
// '10.07.24. 0xE404=0000 -> 1FC0 (Depedestal 0 -> -64d)
// '10.08.16. 0xF410=0001 -> 0000 (for SHBN)
// '10.08.25. 0xF438=0020 -> 0002 (VTGSL=2.96V) by APS
//            0xF43A=0020 -> 0001 (VRG=2.83V) by APS
// '10.09.28. 0xF402=1F02 -> 3F02 ([13]: pixel bias powerdown according to HADR) for Darkshading
//		    0xF416=0000 -> 0001 (AAC_EN enable) for Darkshading
//========================================================================================
//============================= Analog & APS Control =====================================
{0x0028, 0xD000},
{0x002A, 0xF2AC},
{0x0F12, 0x0100},	// analog gain; 0200 x16, 0100 x8, 0080 x4, 0040 x2, 0020 x1
{0x002A, 0xF400},
{0x0F12, 0x001D},	// ldb_en[4], ld_en[3], clp_en[2](N/A), smp_en[1], dshut_en[0]
{0x0F12, 0x3F02},	// cds_test[15:0]; refer to the ATOP_TEST_INFORMATION.

{0x002A, 0xF40A},
{0x0F12, 0x0054},	// adc_sat[7:0]=84d (500mV)
{0x0F12, 0x0002},	// ms[2:0]; 2h@Normal, 2h@PLA, 1h@CNT.AVG
{0x0F12, 0x0008},	// rmp_option[7:0]; [3]SL_Low_PWR_SAVE On
{0x0F12, 0x0000},	// msoff_en; No MS if gain gain is lower than x2
{0x0F12, 0x00A4},	// rmp_init[7:0]

{0x002A, 0xF416},
{0x0F12, 0x0001},	// dbs_option[11:4], dbs_mode[3:2], dbs_bist_en[1], aac_en[0]

{0x002A, 0xF41E},
{0x0F12, 0x0065},	// comp2_bias[7:4], comp1_bias[3:0]

{0x002A, 0xF422},
{0x0F12, 0x0005},	// pix_bias[3:0]

{0x002A, 0xF426},
{0x0F12, 0x00D4},	// clp_lvl[7:0]

{0x002A, 0xF42A},
{0x0F12, 0x0001},	// ref_option[7:0]; [4]OB_PIX monit en, [3]Clamp monit en, [2]Monit amp en, [1]Clamp power-down, [0]CDS power-down during SL=low

{0x002A, 0xF42E},
{0x0F12, 0x0406},	// fb_lv[11:10], pd_fblv[9], capa_ctrl_en[8], pd_inrush_ctrl[7], pd_reg_ntg[6], pd_reg_tgsl[5], pd_reg_rg[4], pd_reg_pix[3], pd_ncp_rosc[2], pd_cp_rosc[1], pd_cp[0]

{0x002A, 0xF434},
{0x0F12, 0x0003},	// dbr_clk_sel[1:0]; PLL_mode=3h, ROSC_mode=0h
{0x0F12, 0x0004},	// reg_tune_pix[7:0]
{0x0F12, 0x0002},	// reg_tune_tgsl[7:0] (2.96V)
{0x0F12, 0x0001},	// reg_tune_rg[7:0] (2.83V)
{0x0F12, 0x0004},	// reg_tune_ntg[7:0]

{0x002A, 0xF446},
{0x0F12, 0x0000},	// blst_en_cintr[15:0]

{0x002A, 0xF466},
{0x0F12, 0x0000},	// srx_en[0]

{0x002A, 0x0054},
{0x0F12, 0x0028},	// pll_pd[10](0:enable, 1:disable), div_clk_en[0](0:enable, 1:disable)
{0x0F12, 0x8888},	// div_dbr[7:4]

{0x002A, 0xF132},
{0x0F12, 0x0206},	// tgr_frame_decription 4
{0x002A, 0xF152},
{0x0F12, 0x0206},	// tgr_frame_decription 7
{0x002A, 0xF1A2},
{0x0F12, 0x0200},	// tgr_frame_params_descriptor_3
{0x002A, 0xF1B2},
{0x0F12, 0x0202},	// tgr_frame_params_descriptor_6
//===========================================================================================

//============================= Line-ADLC Tuning ============================================
{0x002A, 0xE42E},
{0x0F12, 0x0004},	// adlc_qec[2:0]
//===========================================================================================

//============================= Senor BPR ===================================================
{0x002A, 0xE304},
{0x0F12, 0x09CC},	// active_bpr_en[11:11], active_bpr_thresh[10:0]                         
//=======================================================================================    

//===================================================================
// AWB white locus setting - Have to be written after TnP
//===================================================================
{0x0028, 0x7000},
{0x002A, 0x1014},
{0x0F12, 0x0132},	//0138	//awbb_IntcR
{0x0F12, 0x010A},	//011C	//awbb_IntcB

//===================================================================
// AF
//===================================================================
//1. AF interface setting
{0x002A, 0x01A2},
{0x0F12, 0x0003}, //REG_TC_IPRM_CM_Init_AfModeType            // VCM_I2C actuator
{0x0F12, 0x0000}, //REG_TC_IPRM_CM_Init_PwmConfig1           // No PWM
{0x0F12, 0x0000}, //REG_TC_IPRM_CM_Init_PwmConfig2
{0x0F12, 0x0041}, //REG_TC_IPRM_CM_Init_GpioConfig1            // Use GPIO_4 for enable port
{0x0F12, 0x0000}, //REG_TC_IPRM_CM_Init_GpioConfig2
{0x0F12, 0x2A0C}, //REG_TC_IPRM_CM_Init_Mi2cBits            // Use GPIO_5 for SCL, GPIO_6 for SDA
{0x0F12, 0x0190}, //REG_TC_IPRM_CM_Init_Mi2cRateKhz            // MI2C Speed : 400KHz

//2. AF window setting
{0x002A, 0x022C},
{0x0F12, 0x0100},	//REG_TC_AF_FstWinStartX 
{0x0F12, 0x00E3},	//REG_TC_AF_FstWinStartY
{0x0F12, 0x0200},	//REG_TC_AF_FstWinSizeX 
{0x0F12, 0x0238},	//REG_TC_AF_FstWinSizeY
{0x0F12, 0x018C},	//REG_TC_AF_ScndWinStartX
{0x0F12, 0x0166},	//REG_TC_AF_ScndWinStartY
{0x0F12, 0x00E6},	//REG_TC_AF_ScndWinSizeX
{0x0F12, 0x0132},	//REG_TC_AF_ScndWinSizeY
{0x0F12, 0x0001},	//REG_TC_AF_WinSizesUpdated

//3. AF Fine Search Settings
{0x002A, 0x063A},
{0x0F12, 0x00C0}, //#skl_af_StatOvlpExpFactor
{0x002A, 0x064A},
{0x0F12, 0x0001}, //#skl_af_bAfStatOff
{0x002A, 0x1488},
{0x0F12, 0x0000}, //#af_search_usAeStable
{0x002A, 0x1494},
{0x0F12, 0x1002},	//#af_search_usSingleAfFlags, 1000- fine search disable, 1002- fine search on
{0x002A, 0x149E},
{0x0F12, 0x0003}, //#af_search_usFinePeakCount
{0x0F12, 0x0000}, //#af_search_usFineMaxScale
{0x002A, 0x142C},
{0x0F12, 0x0602},	//#af_pos_usFineStepNumSize

//4.  AF Peak Threshold Setting
{0x002A, 0x1498},
{0x0F12, 0x0003},	//#af_search_usMinPeakSamples
{0x002A, 0x148A},
{0x0F12, 0x00CC},	//#af_search_usPeakThr  for 80%
{0x0F12, 0x00A0}, //#af_search_usPeakThrLow

//5.  AF Default Position
{0x002A, 0x1420},
{0x0F12, 0x0000},	//#af_pos_usHomePos
{0x0F12, 0x9600},	//#af_pos_usLowConfPos

//6. AF statistics
{0x002A, 0x14B4},
{0x0F12, 0x0280}, //#af_search_usConfThr_4_  LowEdgeBoth GRAD
{0x002A, 0x14C0},
{0x0F12, 0x03A0}, //#af_search_usConfThr_10_ LowLight HPF
{0x0F12, 0x0320}, //#af_search_usConfThr_11_
{0x002A, 0x14F4},
{0x0F12, 0x0030}, //#af_stat_usMinStatVal
{0x002A, 0x1514},
{0x0F12, 0x0060}, //#af_scene_usSceneLowNormBrThr
// AF Scene Settings
{0x002A, 0x151E},
{0x0F12, 0x0003}, //#af_scene_usSaturatedScene

//7. AF Lens Position Table Settings
{0x002A, 0x1434},
{0x0F12, 0x0010},  //#af_pos_usTableLastInd, 10h + 1h = 17 Steps 

{0x0F12, 0x0030},  //#af_pos_usTable_0_  48  
{0x0F12, 0x0033},  //#af_pos_usTable_1_  51   
{0x0F12, 0x0036},  //#af_pos_usTable_2_  54	
{0x0F12, 0x0039},  //#af_pos_usTable_3_  57	
{0x0F12, 0x003D},  //#af_pos_usTable_4_  61   
{0x0F12, 0x0041},  //#af_pos_usTable_5_  65	
{0x0F12, 0x0045},  //#af_pos_usTable_6_  69	
{0x0F12, 0x0049},  //#af_pos_usTable_7_  73	
{0x0F12, 0x004F},  //#af_pos_usTable_8_  79	
{0x0F12, 0x0055},  //#af_pos_usTable_9_  85	
{0x0F12, 0x005D},  //#af_pos_usTable_10_ 93	
{0x0F12, 0x0065},  //#af_pos_usTable_11_ 101	
{0x0F12, 0x006D},  //#af_pos_usTable_12_ 109	
{0x0F12, 0x0077},  //#af_pos_usTable_13_ 119	
{0x0F12, 0x0083},  //#af_pos_usTable_14_ 131	
{0x0F12, 0x008F},  //#af_pos_usTable_15_ 143	
{0x0F12, 0x0096},  //#af_pos_usTable_16_ 150

//8. VCM AF driver with PWM/I2C 
{0x002A, 0x1558},
{0x0F12, 0x8000}, //#afd_usParam[0]  I2C power down command
{0x0F12, 0x0006}, //#afd_usParam[1]  Position Right Shift 
{0x0F12, 0x3FF0}, //#afd_usParam[2]  I2C Data Mask
{0x0F12, 0x03E8}, //#afd_usParam[3]  PWM Period
{0x0F12, 0x0000}, //#afd_usParam[4]  PWM Divider
{0x0F12, 0x0020}, //#afd_usParam[5]  SlowMotion Delay    reduce lens collision noise.
{0x0F12, 0x0010}, //#afd_usParam[6]  SlowMotion Threshold
{0x0F12, 0x0008}, //#afd_usParam[7]  Signal Shaping
{0x0F12, 0x0040}, //#afd_usParam[8]  Signal Shaping level 
{0x0F12, 0x0080}, //#afd_usParam[9]  Signal Shaping level
{0x0F12, 0x00C0}, //#afd_usParam[10] Signal Shaping level
{0x0F12, 0x00E0}, //#afd_usParam[11] Signal Shaping level

{0x002A, 0x0224},
{0x0F12, 0x0003},	//REG_TC_AF_AfCmd	//Initialize AF subsystem (AF driver, AF algorithm)

//===================================================================
// Flash setting
//===================================================================
{0x002A, 0x018C},
{0x0F12, 0x0001},	//REG_TC_IPRM_AuxConfig	// bit[0] : Flash is in use, bit[1] : Mechanical shutter is in use // 0 : do not use, 1 : use
{0x0F12, 0x0003},	//REG_TC_IPRM_AuxPolarity	// bit[0] : Flash polarity (1 is active high), bit[1] : Mechanical shutter polarity (1 is active high)
{0x0F12, 0x0003},	//REG_TC_IPRM_AuxGpios	//1-4 : Flash GPIO number, If GPIO number is overaped with AF GPIO, F/W could be stop.

//===================================================================
// 1-H timing setting
//===================================================================
{0x002A, 0x1686},
{0x0F12, 0x005C},	//senHal_uAddColsBin
{0x0F12, 0x005C},	//senHal_uAddColsNoBin
{0x0F12, 0x005C},	//senHal_uMinColsHorBin
{0x0F12, 0x005C},	//senHal_uMinColsNoHorBin
{0x0F12, 0x025A},	//senHal_uMinColsAddAnalogBin

//===================================================================
// Forbidden area setting
//===================================================================
{0x002A, 0x1844},
{0x0F12, 0x0000},	//senHal_bSRX    //SRX off

{0x002A, 0x1680},
{0x0F12, 0x0002},	//senHal_NExpLinesCheckFine	//0004    //extend Forbidden area line

//===================================================================
// Preview subsampling mode
//===================================================================
{0x002A, 0x18F8},
{0x0F12, 0x0001},	//senHal_bAACActiveWait2Start
{0x002A, 0x18F6},
{0x0F12, 0x0001},	//senHal_bAlwaysAAC
{0x002A, 0x182C},
{0x0F12, 0x0001},	//senHal_bSenAAC
{0x002A, 0x0EE4},
{0x0F12, 0x0001},	//setot_bUseDigitalHbin
{0x002A, 0x1674},
{0x0F12, 0x0002},	//senHal_SenBinFactor	// 2:2x2, 4:4x4
{0x0F12, 0x0002},	//senHal_SamplingType	// 0:Full, 1:digital, 2:PLA, 3:CA
{0x0F12, 0x0000},	//senHal_SamplingMode	// 0:2x2,	1:4x4

//===================================================================
// PLL setting for Max frequency (EVT0.1) 2010.08.05 - Do not remove
//===================================================================
{0x002A, 0x19AE},
{0x0F12, 0xEA60},	//pll_uMaxSysFreqKhz
{0x0F12, 0x7530},	//pll_uMaxPVIFreq4KH
{0x002A, 0x19C2},
{0x0F12, 0x7530},	//pll_uMaxMIPIFreq4KH
{0x002A, 0x0244},
{0x0F12, 0x7530},	//REG_0TC_PCFG_usMaxOut4KHzRate
{0x002A, 0x0336},
{0x0F12, 0x7530},	//REG_0TC_CCFG_usMaxOut4KHzRate

//===================================================================
// Init Parameters
//===================================================================
//MCLK
{0x002A, 0x0188},
{0x0F12, 0x5DC0},	//REG_TC_IPRM_InClockLSBs
{0x0F12, 0x0000},	//REG_TC_IPRM_InClockMSBs
{0x002A, 0x01B2},
{0x0F12, 0x0003},	//REG_TC_IPRM_UseNPviClocks
{0x0F12, 0x0000},	//REG_TC_IPRM_UseNMipiClocks
{0x002A, 0x01B8},
{0x0F12, 0x0000},	//REG_TC_IPRM_bBlockInternalPllCalc	//1:pll bypass

//SCLK & PCLK
{0x0F12, 0x32C8},	//REG_TC_IPRM_OpClk4KHz_0	//52Mhz	//2EE0	//48Mhz 1F40	//32MHz
{0x0F12, 0x34BC},	//REG_TC_IPRM_MinOutRate4KHz_0	//53.936Mhz	//32A8	//51.872MHz
{0x0F12, 0x34BC},	//REG_TC_IPRM_MaxOutRate4KHz_0	//54.064Mhz	//32E8	//52.128MHz

//SCLK & PCLK
{0x0F12, 0x1F40},	//REG_TC_IPRM_OpClk4KHz_1	//52Mhz	//2EE0	//48Mhz 1F40	//32MHz     
{0x0F12, 0x34BC},	//REG_TC_IPRM_MinOutRate4KHz_1	//53.936Mhz	//32A8	//51.872MHz                
{0x0F12, 0x34BC},	//REG_TC_IPRM_MaxOutRate4KHz_1	//54.064Mhz	//32E8	//52.128MHz                

{0x002A, 0x01CC},
{0x0F12, 0x0001},	//REG_TC_IPRM_InitParamsUpdated


//===================================================================
// Input Width & Height
//===================================================================
{0x002A, 0x01F6},
{0x0F12, 0x0800},	//REG_TC_GP_PrevReqInputWidth		//Sensor Crop Width	2048
{0x0F12, 0x0600},	//REG_TC_GP_PrevReqInputHeight	//Sensor Crop Height 1536
{0x0F12, 0x0000},	//REG_TC_GP_PrevInputWidthOfs		//Sensor HOffset 0
{0x0F12, 0x0000},	//REG_TC_GP_PrevInputHeightOfs	//Sensor VOffset 0
{0x0F12, 0x0800},	//REG_TC_GP_CapReqInputWidth		//Sensor Crop Width	2048
{0x0F12, 0x0600},	//REG_TC_GP_CapReqInputHeight		//Sensor Crop Height 1536
{0x0F12, 0x0000},	//REG_TC_GP_CapInputWidthOfs		//Sensor HOffset 0
{0x0F12, 0x0000},	//REG_TC_GP_CapInputHeightOfs		//Sensor VOffset 0

{0x002A, 0x0216},
{0x0F12, 0x0001},	//REG_TC_GP_bUseReqInputInPre
{0x0F12, 0x0001},	//REG_TC_GP_bUseReqInputInCap

{0x002A, 0x043C},
{0x0F12, 0x0800},	//REG_TC_PZOOM_ZoomInputWidth
{0x0F12, 0x0600},	//REG_TC_PZOOM_ZoomInputHeight
{0x0F12, 0x0000},	//REG_TC_PZOOM_ZoomInputWidthOfs
{0x0F12, 0x0000},	//REG_TC_PZOOM_ZoomInputHeightOfs

//===================================================================
// Preview 0 1024x768 system 52M PCLK 54M
//===================================================================
{0x002A, 0x023E},
{0x0F12, 0x0280},	//REG_0TC_PCFG_usWidth
{0x0F12, 0x01E0},	//REG_0TC_PCFG_usHeight
{0x0F12, 0x0005},	//REG_0TC_PCFG_Format
{0x0F12, 0x34BC},	//REG_0TC_PCFG_usMaxOut4KHzRate
{0x0F12, 0x34BC},	//REG_0TC_PCFG_usMinOut4KHzRate

{0x002A, 0x024C},
{0x0F12, 0x0052},	//REG_0TC_PCFG_PVIMask    => cmk 2010.10.29 0x0042 => 0x0052 Invert Y, C order
{0x0F12, 0x0010},	//REG_0TC_PCFG_OIFMask

{0x002A, 0x0254},
{0x0F12, 0x0000},	//REG_0TC_PCFG_uClockInd
{0x0F12, 0x0000},	//REG_0TC_PCFG_usFrTimeType
{0x0F12, 0x0001},	//REG_0TC_PCFG_FrRateQualityType
{0x0F12, 0x029A},	//REG_0TC_PCFG_usMaxFrTimeMsecMult10	//max frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS
{0x0F12, 0x014E},	//REG_0TC_PCFG_usMinFrTimeMsecMult10	//min frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS

{0x0F12, 0x0000},	//REG_0TC_PCFG_bSmearOutput
{0x0F12, 0x0000},	//REG_0TC_PCFG_sSaturation
{0x0F12, 0x0000},	//REG_0TC_PCFG_sSharpBlur
{0x0F12, 0x0000},	//REG_0TC_PCFG_sColorTemp
{0x0F12, 0x0000},	//REG_0TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000},	//REG_0TC_PCFG_uPrevMirror
{0x0F12, 0x0000},	//REG_0TC_PCFG_uCaptureMirror
{0x0F12, 0x0000},	//REG_0TC_PCFG_uRotation

//===================================================================
// Preview 2 1024x768 system 52M PCLK 54M
//===================================================================
{0x002A, 0x029E},
{0x0F12, 0x0280},	//REG_0TC_PCFG_usWidth  PCAM Preview width 
{0x0F12, 0x01E0},	//REG_0TC_PCFG_usHeight  PCAM Preview height
{0x0F12, 0x0005},	//REG_0TC_PCFG_Format
{0x0F12, 0x34BC},	//REG_0TC_PCFG_usMaxOut4KHzRate
{0x0F12, 0x34BC},	//REG_0TC_PCFG_usMinOut4KHzRate

{0x002A, 0x02AC},
{0x0F12, 0x0052},	//REG_0TC_PCFG_PVIMask  => cmk 2010.10.29 0x0042 => 0x0052 Invert Y, C order
{0x0F12, 0x0010},	//REG_0TC_PCFG_OIFMask

{0x002A, 0x02B4},
{0x0F12, 0x0000},	//REG_0TC_PCFG_uClockInd
{0x0F12, 0x0000},	//REG_0TC_PCFG_usFrTimeType
{0x0F12, 0x0001},	//REG_0TC_PCFG_FrRateQualityType
{0x0F12, 0x09C4},	//REG_0TC_PCFG_usMaxFrTimeMsecMult10	//max frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS
{0x0F12, 0x014E},	//REG_0TC_PCFG_usMinFrTimeMsecMult10	//min frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS

{0x0F12, 0x0000},	//REG_0TC_PCFG_bSmearOutput
{0x0F12, 0x0000},	//REG_0TC_PCFG_sSaturation
{0x0F12, 0x0000},	//REG_0TC_PCFG_sSharpBlur
{0x0F12, 0x0000},	//REG_0TC_PCFG_sColorTemp
{0x0F12, 0x0000},	//REG_0TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000},	//REG_0TC_PCFG_uPrevMirror
{0x0F12, 0x0000},	//REG_0TC_PCFG_uCaptureMirror
{0x0F12, 0x0000},	//REG_0TC_PCFG_uRotation

//===================================================================
// Capture 0 2048x1536 system 52M PCLK 54M
//===================================================================
{0x002A, 0x032E},
{0x0F12, 0x0000},	//REG_0TC_CCFG_uCaptureMode

{0x0F12, 0x0800},	//REG_0TC_CCFG_usWidth
{0x0F12, 0x0600},	//REG_0TC_CCFG_usHeight
{0x0F12, 0x0005},	//REG_0TC_CCFG_Format   //PCAM 5:YUV   9:JPEG
{0x0F12, 0x34BC},	//REG_0TC_CCFG_usMaxOut4KHzRate
{0x0F12, 0x34BC},	//REG_0TC_CCFG_usMinOut4KHzRate

{0x002A, 0x033E},
{0x0F12, 0x0052},	//REG_0TC_CCFG_PVIMask        => cmk 2010.10.29 0x0042 => 0x0052 Invert Y, C order
{0x0F12, 0x0010},	//REG_0TC_CCFG_OIFMask
{0x0F12, 0x03C0},	//REG_0TC_CCFG_usJpegPacketSize

{0x002A, 0x0346},
{0x0F12, 0x0000},	//REG_0TC_CCFG_uClockInd
{0x0F12, 0x0000},	//REG_0TC_CCFG_usFrTimeType
{0x0F12, 0x0002},	//REG_0TC_CCFG_FrRateQualityType
{0x0F12, 0x0535},	//REG_0TC_CCFG_usMaxFrTimeMsecMult10
{0x0F12, 0x029A},	//REG_0TC_CCFG_usMinFrTimeMsecMult10
{0x0F12, 0x0000},	//REG_0TC_CCFG_bSmearOutput
{0x0F12, 0x0000},	//REG_0TC_CCFG_sSaturation
{0x0F12, 0x0000},	//REG_0TC_CCFG_sSharpBlur
{0x0F12, 0x0000},	//REG_0TC_CCFG_sColorTemp
{0x0F12, 0x0000},	//REG_0TC_CCFG_uDeviceGammaIndex

//===================================================================
// Capture 2 2048x1536 system 52M PCLK 54M
//===================================================================
{0x002A, 0x0386},
{0x0F12, 0x0000},	//REG_0TC_CCFG_uCaptureMode

{0x0F12, 0x0800},	//REG_0TC_CCFG_usWidth
{0x0F12, 0x0600},	//REG_0TC_CCFG_usHeight
{0x0F12, 0x0005},	//REG_0TC_CCFG_Format  //PCAM 5:YUV   9:JPEG
{0x0F12, 0x34BC},	//REG_0TC_CCFG_usMaxOut4KHzRate
{0x0F12, 0x34BC},	//REG_0TC_CCFG_usMinOut4KHzRate

{0x002A, 0x0396},
{0x0F12, 0x0052},	//REG_0TC_CCFG_PVIMask        => cmk 2010.10.29 0x0042 => 0x0052 Invert Y, C order
{0x0F12, 0x0010},	//REG_0TC_CCFG_OIFMask
{0x0F12, 0x03C0},	//REG_0TC_CCFG_usJpegPacketSize

{0x002A, 0x039E},
{0x0F12, 0x0000},	//REG_0TC_CCFG_uClockInd
{0x0F12, 0x0000},	//REG_0TC_CCFG_usFrTimeType
{0x0F12, 0x0002},	//REG_0TC_CCFG_FrRateQualityType
{0x0F12, 0x0535},	//REG_0TC_CCFG_usMaxFrTimeMsecMult10
{0x0F12, 0x029A},	//REG_0TC_CCFG_usMinFrTimeMsecMult10
{0x0F12, 0x0000},	//REG_0TC_CCFG_bSmearOutput
{0x0F12, 0x0000},	//REG_0TC_CCFG_sSaturation
{0x0F12, 0x0000},	//REG_0TC_CCFG_sSharpBlur
{0x0F12, 0x0000},	//REG_0TC_CCFG_sColorTemp
{0x0F12, 0x0000},	//REG_0TC_CCFG_uDeviceGammaIndex

{0x002A, 0x0426},
{0x0F12, 0x0055},	//REG_TC_BRC_usCaptureQuality

//PREVIEW
{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreviewChanged

{0xFFFF, 0x0064},   //Delay 100ms

//===================================================================
// AFC
//===================================================================
//Auto
{0x002A, 0x0F08},
{0x0F12, 0x0000},	//AFC_Default60Hz   01:60hz 00:50Hz
{0x002A, 0x04A4},
{0x0F12, 0x067F},	//REG_TC_DBG_AutoAlgEnBits, 065f : Manual AFC on   067f : Manual AFC off

//===================================================================
// Shading (AF module)
//===================================================================
// TVAR_ash_pGAS_high
{0x002A, 0x0D22},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x000F},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F0F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x0F00},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0F00},
{0x0F12, 0x000F},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0000},
{0x0F12, 0x000F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F0F},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0F00},
{0x0F12, 0x0000},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x000F},
{0x0F12, 0x0F00},

// TVAR_ash_pGAS_low
{0x0F12, 0x6CA9},
{0x0F12, 0xF136},
{0x0F12, 0x06A1},
{0x0F12, 0xFE54},
{0x0F12, 0x097B},
{0x0F12, 0xF52E},
{0x0F12, 0xF030},
{0x0F12, 0xF536},
{0x0F12, 0x0783},
{0x0F12, 0xFE44},
{0x0F12, 0x00E9},
{0x0F12, 0xFF3E},
{0x0F12, 0xFCE5},
{0x0F12, 0x0A39},
{0x0F12, 0xFAB6},
{0x0F12, 0xFC00},
{0x0F12, 0x057D},
{0x0F12, 0xFFB6},
{0x0F12, 0x12DB},
{0x0F12, 0xFB17},
{0x0F12, 0x04D5},
{0x0F12, 0x05C6},
{0x0F12, 0xF896},
{0x0F12, 0xFC4C},
{0x0F12, 0xFCCB},
{0x0F12, 0xFB96},
{0x0F12, 0xFBF8},
{0x0F12, 0x0044},
{0x0F12, 0xFCE8},
{0x0F12, 0x0F81},
{0x0F12, 0xF3F5},
{0x0F12, 0x0BE9},
{0x0F12, 0xFBD3},
{0x0F12, 0x00A1},
{0x0F12, 0x0787},
{0x0F12, 0xEE76},
{0x0F12, 0x814D},
{0x0F12, 0xEF4C},
{0x0F12, 0x037D},
{0x0F12, 0x059F},
{0x0F12, 0x047B},
{0x0F12, 0xF588},
{0x0F12, 0xF15C},
{0x0F12, 0xE1E7},
{0x0F12, 0x1C1D},
{0x0F12, 0xECFA},
{0x0F12, 0x0A8E},
{0x0F12, 0x00D5},
{0x0F12, 0xEDF1},
{0x0F12, 0x1FBC},
{0x0F12, 0xE844},
{0x0F12, 0x054F},
{0x0F12, 0x0951},
{0x0F12, 0xF14A},
{0x0F12, 0x2B75},
{0x0F12, 0xEAD0},
{0x0F12, 0x0FB1},
{0x0F12, 0x0296},
{0x0F12, 0xEACD},
{0x0F12, 0x1894},
{0x0F12, 0xEE1E},
{0x0F12, 0x0081},
{0x0F12, 0xF821},
{0x0F12, 0x094D},
{0x0F12, 0x014C},
{0x0F12, 0xF42F},
{0x0F12, 0xF2FD},
{0x0F12, 0x1124},
{0x0F12, 0xF9B2},
{0x0F12, 0xF6ED},
{0x0F12, 0x0D98},
{0x0F12, 0xF984},
{0x0F12, 0x6CF4},
{0x0F12, 0xEE3A},
{0x0F12, 0x095D},
{0x0F12, 0xFCE5},
{0x0F12, 0x0895},
{0x0F12, 0xF6C3},
{0x0F12, 0xF373},
{0x0F12, 0xF0DC},
{0x0F12, 0x0E81},
{0x0F12, 0xF5E9},
{0x0F12, 0x0527},
{0x0F12, 0x00DB},
{0x0F12, 0xF953},
{0x0F12, 0x14F2},
{0x0F12, 0xEC1B},
{0x0F12, 0x0CD5},
{0x0F12, 0xF9ED},
{0x0F12, 0xFFAB},
{0x0F12, 0x1BD3},
{0x0F12, 0xEC85},
{0x0F12, 0x1308},
{0x0F12, 0xF7AF},
{0x0F12, 0xFCE5},
{0x0F12, 0x04E6},
{0x0F12, 0xEF89},
{0x0F12, 0x0598},
{0x0F12, 0xF28A},
{0x0F12, 0x0900},
{0x0F12, 0x0165},
{0x0F12, 0x002B},
{0x0F12, 0xFBA3},
{0x0F12, 0x09E3},
{0x0F12, 0x0045},
{0x0F12, 0xFB3D},
{0x0F12, 0x04E4},
{0x0F12, 0xF70E},
{0x0F12, 0x702E},
{0x0F12, 0xEEA1},
{0x0F12, 0x083A},
{0x0F12, 0xFE09},
{0x0F12, 0x0957},
{0x0F12, 0xF4EA},
{0x0F12, 0xF15F},
{0x0F12, 0xF40B},
{0x0F12, 0x09A2},
{0x0F12, 0xFBC5},
{0x0F12, 0x0007},
{0x0F12, 0x0332},
{0x0F12, 0xFCCD},
{0x0F12, 0x0D2A},
{0x0F12, 0xF2CB},
{0x0F12, 0x072C},
{0x0F12, 0x009C},
{0x0F12, 0xFB04},
{0x0F12, 0x1948},
{0x0F12, 0xF545},
{0x0F12, 0x0CE1},
{0x0F12, 0xF7B3},
{0x0F12, 0x0043},
{0x0F12, 0x023A},
{0x0F12, 0xF177},
{0x0F12, 0x003D},
{0x0F12, 0xFC39},
{0x0F12, 0x040C},
{0x0F12, 0xFB2A},
{0x0F12, 0x08E8},
{0x0F12, 0xFA4B},
{0x0F12, 0x0BCE},
{0x0F12, 0xF4F6},
{0x0F12, 0x08C3},
{0x0F12, 0x0051},
{0x0F12, 0xF4BE},

{0x002A, 0x04A8},
{0x0F12, 0x0001},	//REG_TC_DBG_ReInitCmd

//===================================================================
// Shading - Alpha
//===================================================================
{0x002A, 0x07E8},
{0x0F12, 0x00BC},	//TVAR_ash_AwbAshCord_0_	//HOR
{0x0F12, 0x00ED},	//TVAR_ash_AwbAshCord_1_	//INCA
{0x0F12, 0x0101},	//TVAR_ash_AwbAshCord_2_	//WW
{0x0F12, 0x012D},	//TVAR_ash_AwbAshCord_3_	//CW
{0x0F12, 0x0166},	//TVAR_ash_AwbAshCord_4_	//D50
{0x0F12, 0x0184},	//TVAR_ash_AwbAshCord_5_	//D65
{0x0F12, 0x01A0},	//TVAR_ash_AwbAshCord_6_	//D75

{0x002A, 0x07FE},
{0x0F12, 0x3600},	//3C00	//TVAR_ash_GASAlpha_0__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_0__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_0__2_
{0x0F12, 0x3800},	//4000	//TVAR_ash_GASAlpha_0__3_
{0x0F12, 0x3600},	//3C00	//TVAR_ash_GASAlpha_1__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_1__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_1__2_
{0x0F12, 0x3800},	//4000	//TVAR_ash_GASAlpha_1__3_
{0x0F12, 0x3600},	//3C00	//TVAR_ash_GASAlpha_2__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_2__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_2__2_
{0x0F12, 0x3800},	//4000	//TVAR_ash_GASAlpha_2__3_
{0x0F12, 0x3600},	//3C00	//TVAR_ash_GASAlpha_3__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_3__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_3__2_
{0x0F12, 0x3800},	//4000	//TVAR_ash_GASAlpha_3__3_
{0x0F12, 0x3600},	//3C00	//TVAR_ash_GASAlpha_4__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_4__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_4__2_
{0x0F12, 0x3800},	//4000	//TVAR_ash_GASAlpha_4__3_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_5__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_5__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_5__2_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_5__3_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_6__0_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_6__1_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_6__2_
{0x0F12, 0x4000},	//4000	//TVAR_ash_GASAlpha_6__3_

{0x002A, 0x0836},
{0x0F12, 0x4000},	//TVAR_ash_GASOutdoorAlpha_0_
{0x0F12, 0x4000},	//TVAR_ash_GASOutdoorAlpha_1_
{0x0F12, 0x4000},	//TVAR_ash_GASOutdoorAlpha_2_
{0x0F12, 0x4000},	//TVAR_ash_GASOutdoorAlpha_3_

//===================================================================
// Gamma
//===================================================================
//	param_start	SARR_usGammaLutRGBIndoor

{0x002A, 0x0660},
{0x0F12, 0x0000}, //saRR_usDualGammaLutRGBIndoor[0][0]
{0x0F12, 0x0008}, //saRR_usDualGammaLutRGBIndoor[0][1]
{0x0F12, 0x0015}, //saRR_usDualGammaLutRGBIndoor[0][2]
{0x0F12, 0x0032}, //saRR_usDualGammaLutRGBIndoor[0][3]
{0x0F12, 0x006C}, //saRR_usDualGammaLutRGBIndoor[0][4]
{0x0F12, 0x00D0}, //saRR_usDualGammaLutRGBIndoor[0][5]
{0x0F12, 0x0129}, //saRR_usDualGammaLutRGBIndoor[0][6]
{0x0F12, 0x0151}, //saRR_usDualGammaLutRGBIndoor[0][7]
{0x0F12, 0x0174}, //saRR_usDualGammaLutRGBIndoor[0][8]
{0x0F12, 0x01AA}, //saRR_usDualGammaLutRGBIndoor[0][9]
{0x0F12, 0x01D7}, //saRR_usDualGammaLutRGBIndoor[0][10]
{0x0F12, 0x01FE}, //saRR_usDualGammaLutRGBIndoor[0][11]
{0x0F12, 0x0221}, //saRR_usDualGammaLutRGBIndoor[0][12]
{0x0F12, 0x0252}, //saRR_usDualGammaLutRGBIndoor[0][13]
{0x0F12, 0x0281}, //saRR_usDualGammaLutRGBIndoor[0][14]
{0x0F12, 0x02E1}, //saRR_usDualGammaLutRGBIndoor[0][15]
{0x0F12, 0x0345}, //saRR_usDualGammaLutRGBIndoor[0][16]
{0x0F12, 0x039C}, //saRR_usDualGammaLutRGBIndoor[0][17]
{0x0F12, 0x03D9}, //saRR_usDualGammaLutRGBIndoor[0][18]
{0x0F12, 0x03FF}, //saRR_usDualGammaLutRGBIndoor[0][19]
{0x0F12, 0x0000}, //saRR_usDualGammaLutRGBIndoor[1][0]
{0x0F12, 0x0008}, //saRR_usDualGammaLutRGBIndoor[1][1]
{0x0F12, 0x0015}, //saRR_usDualGammaLutRGBIndoor[1][2]
{0x0F12, 0x0032}, //saRR_usDualGammaLutRGBIndoor[1][3]
{0x0F12, 0x006C}, //saRR_usDualGammaLutRGBIndoor[1][4]
{0x0F12, 0x00D0}, //saRR_usDualGammaLutRGBIndoor[1][5]
{0x0F12, 0x0129}, //saRR_usDualGammaLutRGBIndoor[1][6]
{0x0F12, 0x0151}, //saRR_usDualGammaLutRGBIndoor[1][7]
{0x0F12, 0x0174}, //saRR_usDualGammaLutRGBIndoor[1][8]
{0x0F12, 0x01AA}, //saRR_usDualGammaLutRGBIndoor[1][9]
{0x0F12, 0x01D7}, //saRR_usDualGammaLutRGBIndoor[1][10]
{0x0F12, 0x01FE}, //saRR_usDualGammaLutRGBIndoor[1][11]
{0x0F12, 0x0221}, //saRR_usDualGammaLutRGBIndoor[1][12]
{0x0F12, 0x0252}, //saRR_usDualGammaLutRGBIndoor[1][13]
{0x0F12, 0x0281}, //saRR_usDualGammaLutRGBIndoor[1][14]
{0x0F12, 0x02E1}, //saRR_usDualGammaLutRGBIndoor[1][15]
{0x0F12, 0x0345}, //saRR_usDualGammaLutRGBIndoor[1][16]
{0x0F12, 0x039C}, //saRR_usDualGammaLutRGBIndoor[1][17]
{0x0F12, 0x03D9}, //saRR_usDualGammaLutRGBIndoor[1][18]
{0x0F12, 0x03FF}, //saRR_usDualGammaLutRGBIndoor[1][19]
{0x0F12, 0x0000}, //saRR_usDualGammaLutRGBIndoor[2][0]
{0x0F12, 0x0008}, //saRR_usDualGammaLutRGBIndoor[2][1]
{0x0F12, 0x0015}, //saRR_usDualGammaLutRGBIndoor[2][2]
{0x0F12, 0x0032}, //saRR_usDualGammaLutRGBIndoor[2][3]
{0x0F12, 0x006C}, //saRR_usDualGammaLutRGBIndoor[2][4]
{0x0F12, 0x00D0}, //saRR_usDualGammaLutRGBIndoor[2][5]
{0x0F12, 0x0129}, //saRR_usDualGammaLutRGBIndoor[2][6]
{0x0F12, 0x0151}, //saRR_usDualGammaLutRGBIndoor[2][7]
{0x0F12, 0x0174}, //saRR_usDualGammaLutRGBIndoor[2][8]
{0x0F12, 0x01AA}, //saRR_usDualGammaLutRGBIndoor[2][9]
{0x0F12, 0x01D7}, //saRR_usDualGammaLutRGBIndoor[2][10]
{0x0F12, 0x01FE}, //saRR_usDualGammaLutRGBIndoor[2][11]
{0x0F12, 0x0221}, //saRR_usDualGammaLutRGBIndoor[2][12]
{0x0F12, 0x0252}, //saRR_usDualGammaLutRGBIndoor[2][13]
{0x0F12, 0x0281}, //saRR_usDualGammaLutRGBIndoor[2][14]
{0x0F12, 0x02E1}, //saRR_usDualGammaLutRGBIndoor[2][15]
{0x0F12, 0x0345}, //saRR_usDualGammaLutRGBIndoor[2][16]
{0x0F12, 0x039C}, //saRR_usDualGammaLutRGBIndoor[2][17]
{0x0F12, 0x03D9}, //saRR_usDualGammaLutRGBIndoor[2][18]
{0x0F12, 0x03FF}, //saRR_usDualGammaLutRGBIndoor[2][19]


{0x0F12, 0x0000},	//0000	//0000	//0000	//saRR_usDualGammaLutRGBOutdoor[0][0]
{0x0F12, 0x0008},	//0008	//0008	//0008	//saRR_usDualGammaLutRGBOutdoor[0][1]
{0x0F12, 0x0013},	//0013	//0013	//0013	//saRR_usDualGammaLutRGBOutdoor[0][2]
{0x0F12, 0x002C},	//002B	//002C	//002C	//saRR_usDualGammaLutRGBOutdoor[0][3]
{0x0F12, 0x0062},	//005C	//0057	//0062	//saRR_usDualGammaLutRGBOutdoor[0][4]
{0x0F12, 0x00CD},	//00BB	//00A2	//009A	//saRR_usDualGammaLutRGBOutdoor[0][5]
{0x0F12, 0x0129},	//0109	//00F0	//00FD	//saRR_usDualGammaLutRGBOutdoor[0][6]
{0x0F12, 0x0151},	//012C	//0118	//0129	//saRR_usDualGammaLutRGBOutdoor[0][7]
{0x0F12, 0x0174},	//014C	//013F	//014B	//saRR_usDualGammaLutRGBOutdoor[0][8]
{0x0F12, 0x01AA},	//0185	//0184	//0184	//saRR_usDualGammaLutRGBOutdoor[0][9]
{0x0F12, 0x01D7},	//01B9	//01B8	//01B8	//saRR_usDualGammaLutRGBOutdoor[0][10]
{0x0F12, 0x01FE},	//01E8	//01EA	//01EA	//saRR_usDualGammaLutRGBOutdoor[0][11]
{0x0F12, 0x0221},	//0213	//0216	//0216	//saRR_usDualGammaLutRGBOutdoor[0][12]
{0x0F12, 0x025A},	//0258	//025E	//025E	//saRR_usDualGammaLutRGBOutdoor[0][13]
{0x0F12, 0x028C},	//028D	//0299	//0299	//saRR_usDualGammaLutRGBOutdoor[0][14]
{0x0F12, 0x02E6},	//02EA	//02F9	//02F9	//saRR_usDualGammaLutRGBOutdoor[0][15]
{0x0F12, 0x0331},	//0331	//0341	//0341	//saRR_usDualGammaLutRGBOutdoor[0][16]
{0x0F12, 0x0377},	//0377	//0379	//0379	//saRR_usDualGammaLutRGBOutdoor[0][17]
{0x0F12, 0x03B5},	//03B1	//03B8	//03B8	//saRR_usDualGammaLutRGBOutdoor[0][18]
{0x0F12, 0x03EA},	//03E9	//03E9	//03E9	//saRR_usDualGammaLutRGBOutdoor[0][19]
{0x0F12, 0x0000},	//0000	//0000	//0000	//saRR_usDualGammaLutRGBOutdoor[1][0]
{0x0F12, 0x0008},	//0008	//0008	//0008	//saRR_usDualGammaLutRGBOutdoor[1][1]
{0x0F12, 0x0013},	//0013	//0013	//0013	//saRR_usDualGammaLutRGBOutdoor[1][2]
{0x0F12, 0x002C},	//002B	//002C	//002C	//saRR_usDualGammaLutRGBOutdoor[1][3]
{0x0F12, 0x0062},	//005C	//0057	//0062	//saRR_usDualGammaLutRGBOutdoor[1][4]
{0x0F12, 0x00CD},	//00BB	//00A2	//009A	//saRR_usDualGammaLutRGBOutdoor[1][5]
{0x0F12, 0x0129},	//0109	//00F0	//00FD	//saRR_usDualGammaLutRGBOutdoor[1][6]
{0x0F12, 0x0151},	//012C	//0118	//0129	//saRR_usDualGammaLutRGBOutdoor[1][7]
{0x0F12, 0x0174},	//014C	//013F	//014B	//saRR_usDualGammaLutRGBOutdoor[1][8]
{0x0F12, 0x01AA},	//0185	//0184	//0184	//saRR_usDualGammaLutRGBOutdoor[1][9]
{0x0F12, 0x01D7},	//01B9	//01B8	//01B8	//saRR_usDualGammaLutRGBOutdoor[1][10]
{0x0F12, 0x01FE},	//01E8	//01EA	//01EA	//saRR_usDualGammaLutRGBOutdoor[1][11]
{0x0F12, 0x0221},	//0213	//0216	//0216	//saRR_usDualGammaLutRGBOutdoor[1][12]
{0x0F12, 0x025A},	//0258	//025E	//025E	//saRR_usDualGammaLutRGBOutdoor[1][13]
{0x0F12, 0x028C},	//028D	//0299	//0299	//saRR_usDualGammaLutRGBOutdoor[1][14]
{0x0F12, 0x02E6},	//02EA	//02F9	//02F9	//saRR_usDualGammaLutRGBOutdoor[1][15]
{0x0F12, 0x0331},	//0331	//0341	//0341	//saRR_usDualGammaLutRGBOutdoor[1][16]
{0x0F12, 0x0377},	//0377	//0379	//0379	//saRR_usDualGammaLutRGBOutdoor[1][17]
{0x0F12, 0x03B5},	//03B1	//03B8	//03B8	//saRR_usDualGammaLutRGBOutdoor[1][18]
{0x0F12, 0x03EA},	//03E9	//03E9	//03E9	//saRR_usDualGammaLutRGBOutdoor[1][19]
{0x0F12, 0x0000},	//0000	//0000	//0000	//saRR_usDualGammaLutRGBOutdoor[2][0]
{0x0F12, 0x0008},	//0008	//0008	//0008	//saRR_usDualGammaLutRGBOutdoor[2][1]
{0x0F12, 0x0013},	//0013	//0013	//0013	//saRR_usDualGammaLutRGBOutdoor[2][2]
{0x0F12, 0x002C},	//002B	//002C	//002C	//saRR_usDualGammaLutRGBOutdoor[2][3]
{0x0F12, 0x0062},	//005C	//0057	//0062	//saRR_usDualGammaLutRGBOutdoor[2][4]
{0x0F12, 0x00CD},	//00BB	//00A2	//009A	//saRR_usDualGammaLutRGBOutdoor[2][5]
{0x0F12, 0x0129},	//0109	//00F0	//00FD	//saRR_usDualGammaLutRGBOutdoor[2][6]
{0x0F12, 0x0151},	//012C	//0118	//0129	//saRR_usDualGammaLutRGBOutdoor[2][7]
{0x0F12, 0x0174},	//014C	//013F	//014B	//saRR_usDualGammaLutRGBOutdoor[2][8]
{0x0F12, 0x01AA},	//0185	//0184	//0184	//saRR_usDualGammaLutRGBOutdoor[2][9]
{0x0F12, 0x01D7},	//01B9	//01B8	//01B8	//saRR_usDualGammaLutRGBOutdoor[2][10]
{0x0F12, 0x01FE},	//01E8	//01EA	//01EA	//saRR_usDualGammaLutRGBOutdoor[2][11]
{0x0F12, 0x0221},	//0213	//0216	//0216	//saRR_usDualGammaLutRGBOutdoor[2][12]
{0x0F12, 0x025A},	//0258	//025E	//025E	//saRR_usDualGammaLutRGBOutdoor[2][13]
{0x0F12, 0x028C},	//028D	//0299	//0299	//saRR_usDualGammaLutRGBOutdoor[2][14]
{0x0F12, 0x02E6},	//02EA	//02F9	//02F9	//saRR_usDualGammaLutRGBOutdoor[2][15]
{0x0F12, 0x0331},	//0331	//0341	//0341	//saRR_usDualGammaLutRGBOutdoor[2][16]
{0x0F12, 0x0377},	//0377	//0379	//0379	//saRR_usDualGammaLutRGBOutdoor[2][17]
{0x0F12, 0x03B5},	//03B1	//03B8	//03B8	//saRR_usDualGammaLutRGBOutdoor[2][18]
{0x0F12, 0x03EA},	//03E9	//03E9	//03E9	//saRR_usDualGammaLutRGBOutdoor[2][19]


//===================================================================
// AE - shutter
//===================================================================
//****************************************/
// AE 2009 03 08 - based on TN
//****************************************/
//============================================================
// Frame rate setting
//============================================================
// How to set
// 1. Exposure value
// dec2hex((1 / (frame rate you want(ms))) * 100d * 5d)
//
//
// 2. Analog Digital gain
// dec2hex((Analog gain you want) * 256d)
//              Ex1) Simple Caculation for x3.25?:   3.25x256 = 832[dec] = 0340[hex]
//============================================================
//MBR
{0x002A, 0x01DE},
{0x0F12, 0x0000},	//REG_TC_bUseMBR	//MBR off
//MBR off is needed to prevent a shorter integration time when the scene has blurring in Night shot

//AE_Target
{0x002A, 0x1308},
{0x0F12, 0x003E},	//TVAR_ae_BrAve
{0x002A, 0x130E},
{0x0F12, 0x000F},	//ae_StatMode
//ae_StatMode bit[3] BLC has to be bypassed to prevent AE weight change, especially backlight scene

//AE_state
{0x002A, 0x04EE},
{0x0F12, 0x010E},	//#lt_uLimitHigh
{0x0F12, 0x00F5},	//#lt_uLimitLow

//For 60Hz
{0x002A, 0x0504},
{0x0F12, 0x3415},	//#lt_uMaxExp1
{0x002A, 0x0508},
{0x0F12, 0x681F},	//#lt_uMaxExp2
{0x002A, 0x050C},
{0x0F12, 0x8227},	//#lt_uMaxExp3
{0x002A, 0x0510},
{0x0F12, 0xC350},	//#lt_uMaxExp4

{0x002A, 0x0514},
{0x0F12, 0x3415},	//#lt_uCapMaxExp1
{0x002A, 0x0518},
{0x0F12, 0x681F},	//#lt_uCapMaxExp2
{0x002A, 0x051C},
{0x0F12, 0x8227},	//#lt_uCapMaxExp3
{0x002A, 0x0520},
{0x0F12, 0xC350},	//#lt_uCapMaxExp4

{0x002A, 0x0524},
{0x0F12, 0x01D0},	//#lt_uMaxAnGain1
{0x0F12, 0x01D0},	//#lt_uMaxAnGain2
{0x0F12, 0x02C0},	//#lt_uMaxAnGain3
{0x0F12, 0x0710},	//#lt_uMaxAnGain4

{0x0F12, 0x0100},	//#lt_uMaxDigGain
{0x0F12, 0x8000},	//#lt_uMaxTotGain  Total-gain is limited by #lt_uMaxTotGain

{0x0F12, 0x01D0},	//#lt_uCapMaxAnGain1
{0x0F12, 0x01D0},	//#lt_uCapMaxAnGain2
{0x0F12, 0x02C0},	//#lt_uCapMaxAnGain3
{0x0F12, 0x0710},	//#lt_uCapMaxAnGain4

{0x0F12, 0x0100},	//#lt_uCapMaxDigGain
{0x0F12, 0x8000},	//#lt_uCapMaxTotGain  Total-gain is limited by #lt_uMaxTotGain

//===================================================================
//AE - Weights
//===================================================================
{0x002A, 0x1316},
{0x0F12, 0x0000},	//0000	//ae_WeightTbl_16[0]
{0x0F12, 0x0000},	//0101	//ae_WeightTbl_16[1]
{0x0F12, 0x0000},	//0101	//ae_WeightTbl_16[2]
{0x0F12, 0x0000},	//0000	//ae_WeightTbl_16[3]
{0x0F12, 0x0101},	//0101	//ae_WeightTbl_16[4]
{0x0F12, 0x0101},	//0101	//ae_WeightTbl_16[5]
{0x0F12, 0x0101},	//0101	//ae_WeightTbl_16[6]
{0x0F12, 0x0101},	//0101	//ae_WeightTbl_16[7]
{0x0F12, 0x0101},	//0201	//ae_WeightTbl_16[8]
{0x0F12, 0x0201},	//0303	//ae_WeightTbl_16[9]
{0x0F12, 0x0102},	//0303	//ae_WeightTbl_16[10]
{0x0F12, 0x0101},	//0102	//ae_WeightTbl_16[11]
{0x0F12, 0x0101},	//0201	//ae_WeightTbl_16[12]
{0x0F12, 0x0202},	//0403	//ae_WeightTbl_16[13]
{0x0F12, 0x0202},	//0304	//ae_WeightTbl_16[14]
{0x0F12, 0x0101},	//0102	//ae_WeightTbl_16[15]
{0x0F12, 0x0101},	//0201	//ae_WeightTbl_16[16]
{0x0F12, 0x0202},	//0403	//ae_WeightTbl_16[17]
{0x0F12, 0x0202},	//0304	//ae_WeightTbl_16[18]
{0x0F12, 0x0101},	//0102	//ae_WeightTbl_16[19]
{0x0F12, 0x0201},	//0201	//ae_WeightTbl_16[20]
{0x0F12, 0x0202},	//0403	//ae_WeightTbl_16[21]
{0x0F12, 0x0202},	//0304	//ae_WeightTbl_16[22]
{0x0F12, 0x0102},	//0102	//ae_WeightTbl_16[23]
{0x0F12, 0x0201},	//0201	//ae_WeightTbl_16[24]
{0x0F12, 0x0202},	//0303	//ae_WeightTbl_16[25]
{0x0F12, 0x0202},	//0303	//ae_WeightTbl_16[26]
{0x0F12, 0x0102},	//0102	//ae_WeightTbl_16[27]
{0x0F12, 0x0101},	//0201	//ae_WeightTbl_16[28]
{0x0F12, 0x0101},	//0202	//ae_WeightTbl_16[29]
{0x0F12, 0x0101},	//0202	//ae_WeightTbl_16[30]
{0x0F12, 0x0101},	//0102	//ae_WeightTbl_16[31]

//===================================================================
//AWB-BASIC setting
//===================================================================
{0x002A, 0x1018},
{0x0F12, 0x02A7},	//awbb_GLocusR
{0x0F12, 0x0343},	//awbb_GLocusB
{0x002A, 0x0FFC},
{0x0F12, 0x036C},	//awbb_CrclLowT_R_c
{0x002A, 0x1000},
{0x0F12, 0x011D},	//awbb_CrclLowT_B_c
{0x002A, 0x1004},
{0x0F12, 0x62C1},	//awbb_CrclLowT_Rad_c
{0x002A, 0x1034},
{0x0F12, 0x05F0},	//awbb_GamutWidthThr1
{0x0F12, 0x01F4},	//awbb_GamutHeightThr1
{0x0F12, 0x006C},	//awbb_GamutWidthThr2
{0x0F12, 0x0038},	//awbb_GamutHeightThr2
{0x002A, 0x1020},
{0x0F12, 0x000C},	//awbb_MinNumOfFinalPatches
{0x0F12, 0x001E},	//awbb_MinNumOfLowBrFinalPatches
{0x0F12, 0x0046},	//awbb_MinNumOfLowBr0_FinalPatches
{0x002A, 0x291A},
{0x0F12, 0x0006},	// #Mon_AWB_ByPassMode // [0]Outdoor [1]LowBr [2]LowTemp

{0x002A, 0x11C2},
{0x0F12, 0x0000},	//awbb_RGainOff
{0x0F12, 0x0000},	//awbb_BGainOff
{0x0F12, 0x0000},	//awbb_GGainOff
{0x0F12, 0x00C2},	//awbb_Alpha_Comp_Mode
{0x0F12, 0x0002},	//awbb_Rpl_InvalidOutDoor
{0x0F12, 0x0001},	//awbb_UseGrThrCorr
{0x0F12, 0x00E4},	//awbb_Use_Filters
{0x0F12, 0x053C},	//awbb_GainsInit[0]
{0x0F12, 0x0400},	//awbb_GainsInit[1]
{0x0F12, 0x055C},	//awbb_GainsInit[2]
{0x0F12, 0x001E},	//awbb_WpFilterMinThr
{0x0F12, 0x0190},	//awbb_WpFilterMaxThr
{0x0F12, 0x00A0},	//awbb_WpFilterCoef
{0x0F12, 0x0004},	//awbb_WpFilterSize
{0x0F12, 0x0001},	//awbb_otp_disable

//===================================================================
//AWB-Zone
//===================================================================
//	param_start	awbb_IndoorGrZones_m_BGrid
{0x002A, 0x0F28},
{0x0F12, 0x03C0},	//03BE	//03BA	//awbb_IndoorGrZones_m_BGrid[0]
{0x0F12, 0x03E2},	//03F2	//03E8	//awbb_IndoorGrZones_m_BGrid[1]
{0x0F12, 0x0356},	//0356	//035C	//awbb_IndoorGrZones_m_BGrid[2]
{0x0F12, 0x03FC},	//03FC	//03F6	//awbb_IndoorGrZones_m_BGrid[3]
{0x0F12, 0x031E},	//031E	//0328	//awbb_IndoorGrZones_m_BGrid[4]
{0x0F12, 0x03FE},	//03EC	//03E0	//awbb_IndoorGrZones_m_BGrid[5]
{0x0F12, 0x02F0},	//02F0	//02FE	//awbb_IndoorGrZones_m_BGrid[6]
{0x0F12, 0x03F0},	//03C4	//03AC	//awbb_IndoorGrZones_m_BGrid[7]
{0x0F12, 0x02CA},	//02CA	//02E2	//awbb_IndoorGrZones_m_BGrid[8]
{0x0F12, 0x03CC},	//0392	//0370	//awbb_IndoorGrZones_m_BGrid[9]
{0x0F12, 0x02A8},	//02A8	//02C4	//awbb_IndoorGrZones_m_BGrid[10]
{0x0F12, 0x037A},	//0354	//032E	//awbb_IndoorGrZones_m_BGrid[11]
{0x0F12, 0x0288},	//0288	//029E	//awbb_IndoorGrZones_m_BGrid[12]
{0x0F12, 0x033C},	//0320	//030A	//awbb_IndoorGrZones_m_BGrid[13]
{0x0F12, 0x0266},	//0266	//0278	//awbb_IndoorGrZones_m_BGrid[14]
{0x0F12, 0x031E},	//02FA	//02F2	//awbb_IndoorGrZones_m_BGrid[15]
{0x0F12, 0x0246},	//0246	//0258	//awbb_IndoorGrZones_m_BGrid[16]
{0x0F12, 0x0300},	//02E6	//02E2	//awbb_IndoorGrZones_m_BGrid[17]
{0x0F12, 0x0228},	//0228	//0232	//awbb_IndoorGrZones_m_BGrid[18]
{0x0F12, 0x02E8},	//02CE	//02CA	//awbb_IndoorGrZones_m_BGrid[19]
{0x0F12, 0x020E},	//020E	//0218	//awbb_IndoorGrZones_m_BGrid[20]
{0x0F12, 0x02CA},	//02BE	//02BC	//awbb_IndoorGrZones_m_BGrid[21]
{0x0F12, 0x01F8},	//01F8	//01FE	//awbb_IndoorGrZones_m_BGrid[22]
{0x0F12, 0x02B0},	//02AA	//02A6	//awbb_IndoorGrZones_m_BGrid[23]
{0x0F12, 0x01E8},	//01E8	//01EE	//awbb_IndoorGrZones_m_BGrid[24]
{0x0F12, 0x0296},	//0296	//0290	//awbb_IndoorGrZones_m_BGrid[25]
{0x0F12, 0x01DC},	//01DC	//01E0	//awbb_IndoorGrZones_m_BGrid[26]
{0x0F12, 0x027A},	//027A	//0274	//awbb_IndoorGrZones_m_BGrid[27]
{0x0F12, 0x01E0},	//01E0	//01E6	//awbb_IndoorGrZones_m_BGrid[28]
{0x0F12, 0x0252},	//0252	//024E	//awbb_IndoorGrZones_m_BGrid[29]
{0x0F12, 0x01F2},	//01F2	//01F2	//awbb_IndoorGrZones_m_BGrid[30]
{0x0F12, 0x0226},	//0226	//0226	//awbb_IndoorGrZones_m_BGrid[31]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[32]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[33]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[34]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[35]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[36]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[37]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[38]
{0x0F12, 0x0000},	//0000	//0000	//awbb_IndoorGrZones_m_BGrid[39]
//	param_end	awbb_IndoorGrZones_m_BGrid

{0x0F12, 0x0005},	//awbb_IndoorGrZones_m_Grid
{0x002A, 0x0F80},
{0x0F12, 0x00E6},	//awbb_IndoorGrZones_m_Boff
{0x002A, 0x0F7C},
{0x0F12, 0x0010},

//	param_start	awbb_OutdoorGrZones_m_BGrid
{0x002A, 0x0F84},
{0x0F12, 0x028E},	//0286	//awbb_OutdoorGrZones_m_BGrid[0]
{0x0F12, 0x02A6},	//02A2	//awbb_OutdoorGrZones_m_BGrid[1]
{0x0F12, 0x0276},	//0268	//awbb_OutdoorGrZones_m_BGrid[2]
{0x0F12, 0x02B8},	//02B0	//awbb_OutdoorGrZones_m_BGrid[3]
{0x0F12, 0x0264},	//0254	//awbb_OutdoorGrZones_m_BGrid[4]
{0x0F12, 0x02BE},	//02BE	//awbb_OutdoorGrZones_m_BGrid[5]
{0x0F12, 0x0252},	//0240	//awbb_OutdoorGrZones_m_BGrid[6]
{0x0F12, 0x02C0},	//02BE	//awbb_OutdoorGrZones_m_BGrid[7]
{0x0F12, 0x0244},	//0230	//awbb_OutdoorGrZones_m_BGrid[8]
{0x0F12, 0x02BC},	//02B8	//awbb_OutdoorGrZones_m_BGrid[9]
{0x0F12, 0x0234},	//0224	//awbb_OutdoorGrZones_m_BGrid[10]
{0x0F12, 0x02B2},	//02B0	//awbb_OutdoorGrZones_m_BGrid[11]
{0x0F12, 0x0228},	//0218	//awbb_OutdoorGrZones_m_BGrid[12]
{0x0F12, 0x02A6},	//02A4	//awbb_OutdoorGrZones_m_BGrid[13]
{0x0F12, 0x021E},	//0212	//awbb_OutdoorGrZones_m_BGrid[14]
{0x0F12, 0x029C},	//0296	//awbb_OutdoorGrZones_m_BGrid[15]
{0x0F12, 0x0216},	//020E	//awbb_OutdoorGrZones_m_BGrid[16]
{0x0F12, 0x028A},	//0286	//awbb_OutdoorGrZones_m_BGrid[17]
{0x0F12, 0x0216},	//0210	//awbb_OutdoorGrZones_m_BGrid[18]
{0x0F12, 0x0278},	//0278	//awbb_OutdoorGrZones_m_BGrid[19]
{0x0F12, 0x0220},	//021A	//awbb_OutdoorGrZones_m_BGrid[20]
{0x0F12, 0x026A},	//026A	//awbb_OutdoorGrZones_m_BGrid[21]
{0x0F12, 0x0232},	//0228	//awbb_OutdoorGrZones_m_BGrid[22]
{0x0F12, 0x024A},	//024A	//awbb_OutdoorGrZones_m_BGrid[23]
//	param_end	awbb_OutdoorGrZones_m_BGrid

{0x0F12, 0x0004},	//awbb_OutdoorGrZones_m_Gri
{0x002A, 0x0FB8},
{0x0F12, 0x000C},	//awbb_OutdoorGrZones_ZInfo_m_GridSz
{0x002A, 0x0FBC},
{0x0F12, 0x01E4},	//awbb_OutdoorGrZones_m_Bof

//	param_start	awbb_LowBrGrZones_m_BGrid
{0x002A, 0x0FC0},
{0x0F12, 0x03B2},	//awbb_LowBrGrZones_m_BGrid[0]
{0x0F12, 0x044E},	//awbb_LowBrGrZones_m_BGrid[1]
{0x0F12, 0x0330},	//awbb_LowBrGrZones_m_BGrid[2]
{0x0F12, 0x0454},	//awbb_LowBrGrZones_m_BGrid[3]
{0x0F12, 0x02CC},	//awbb_LowBrGrZones_m_BGrid[4]
{0x0F12, 0x0414},	//awbb_LowBrGrZones_m_BGrid[5]
{0x0F12, 0x026E},	//awbb_LowBrGrZones_m_BGrid[6]
{0x0F12, 0x03D0},	//awbb_LowBrGrZones_m_BGrid[7]
{0x0F12, 0x0226},	//awbb_LowBrGrZones_m_BGrid[8]
{0x0F12, 0x0362},	//awbb_LowBrGrZones_m_BGrid[9]
{0x0F12, 0x01F0},	//awbb_LowBrGrZones_m_BGrid[10]
{0x0F12, 0x0312},	//awbb_LowBrGrZones_m_BGrid[11]
{0x0F12, 0x01CE},	//awbb_LowBrGrZones_m_BGrid[12]
{0x0F12, 0x02CC},	//awbb_LowBrGrZones_m_BGrid[13]
{0x0F12, 0x01B2},	//awbb_LowBrGrZones_m_BGrid[14]
{0x0F12, 0x029E},	//awbb_LowBrGrZones_m_BGrid[15]
{0x0F12, 0x01AC},	//awbb_LowBrGrZones_m_BGrid[16]
{0x0F12, 0x0278},	//awbb_LowBrGrZones_m_BGrid[17]
{0x0F12, 0x01B6},	//awbb_LowBrGrZones_m_BGrid[18]
{0x0F12, 0x0248},	//awbb_LowBrGrZones_m_BGrid[19]
{0x0F12, 0x0000},	//awbb_LowBrGrZones_m_BGrid[20]
{0x0F12, 0x0000},	//awbb_LowBrGrZones_m_BGrid[21]
{0x0F12, 0x0000},	//awbb_LowBrGrZones_m_BGrid[22]
{0x0F12, 0x0000},	//awbb_LowBrGrZones_m_BGrid[23]

//	param_end	awbb_LowBrGrZones_m_BGrid
{0x0F12, 0x0006},	//awbb_LowBrGrZones_m_GridStep
{0x002A, 0x0FF4},
{0x0F12, 0x000A},	//awbb_LowBrGrZones_ZInfo_m_GridSz
{0x002A, 0x0FF8},
{0x0F12, 0x00C2},	//awbb_LowBrGrZones_m_Boffs

//===================================================================
//AWB Scene Detection
//===================================================================
{0x002A, 0x1098},
{0x0F12, 0xFE82},	//awbb_SCDetectionMap_SEC_StartR_B
{0x0F12, 0x001E},	//awbb_SCDetectionMap_SEC_StepR_B
{0x0F12, 0x0E74},	//awbb_SCDetectionMap_SEC_SunnyNB
{0x0F12, 0x0122},	//awbb_SCDetectionMap_SEC_StepNB
{0x0F12, 0x00E4},	//awbb_SCDetectionMap_SEC_LowTempR_B
{0x0F12, 0x0096},	//awbb_SCDetectionMap_SEC_SunnyNBZone
{0x0F12, 0x000E},	//awbb_SCDetectionMap_SEC_LowTempR_BZone

{0x002A, 0x105C},
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_0__0_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_0__2_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_0__4_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_1__1_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_1__3_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_2__0_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_2__2_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_2__4_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_3__1_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_3__3_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_4__0_
{0x0F12, 0x0000},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_4__2_
{0x0F12, 0x0500},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_4__4_
{0x0F12, 0x5555},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_5__1_
{0x0F12, 0x5455},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_5__3_
{0x0F12, 0xAA55},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_6__0_
{0x0F12, 0xAAAA},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_6__2_
{0x0F12, 0xBF54},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_6__4_
{0x0F12, 0xFFFF},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_7__1_
{0x0F12, 0x54FE},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_7__3_
{0x0F12, 0xFF6F},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_8__0_
{0x0F12, 0xFEFF},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_8__2_
{0x0F12, 0x1B54},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_8__4_
{0x0F12, 0xFFFF},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_9__1_
{0x0F12, 0x54FE},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_9__3_
{0x0F12, 0xFF06},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_10__0_
{0x0F12, 0xFEFF},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_10__2_
{0x0F12, 0x0154},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_10__4_
{0x0F12, 0xBFBF},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_11__1_
{0x0F12, 0x54BE},	//#awbb_SCDetectionMap_SEC_SceneDetectionMap_11__3_

//===================================================================
//AWB - GridCorrection
//===================================================================

{0x002A, 0x11E0},
{0x0F12, 0x0002},	//awbb_GridEnable

{0x002A, 0x11A8},
{0x0F12, 0x02C8},	//awbb_GridConst_1[0]
{0x0F12, 0x0325},	//awbb_GridConst_1[1]
{0x0F12, 0x038F},	//awbb_GridConst_1[2]

{0x0F12, 0x0F8E},	//0F8E	//awbb_GridConst_2[0]
{0x0F12, 0x10B3},	//10B3	//awbb_GridConst_2[1]
{0x0F12, 0x1136},	//1127	//awbb_GridConst_2[2]
{0x0F12, 0x1138},	//1138	//awbb_GridConst_2[3]
{0x0F12, 0x118E},	//118E	//awbb_GridConst_2[4]
{0x0F12, 0x1213},	//1213	//awbb_GridConst_2[5]

{0x0F12, 0x00A7},	//awbb_GridCoeff_R_1
{0x0F12, 0x00C2},	//awbb_GridCoeff_B_1
{0x0F12, 0x00BD},	//awbb_GridCoeff_R_2
{0x0F12, 0x00AC},	//awbb_GridCoeff_B_2

{0x002A, 0x1118},
{0x0F12, 0x0000},	//0000	//awbb_GridCorr_R[0][0]
{0x0F12, 0x0014},	//FFEC	//awbb_GridCorr_R[0][1]
{0x0F12, 0x0014},	//FFEC	//awbb_GridCorr_R[0][2]
{0x0F12, 0xFFEC},	//FFEC	//awbb_GridCorr_R[0][3]
{0x0F12, 0xFFEC},	//FFEC	//awbb_GridCorr_R[0][4]
{0x0F12, 0x0050},	//0050	//awbb_GridCorr_R[0][5]
{0x0F12, 0x0000},	//0000	//awbb_GridCorr_R[1][0]
{0x0F12, 0x0014},	//FFEC	//awbb_GridCorr_R[1][1]
{0x0F12, 0x0014},	//FFEC	//awbb_GridCorr_R[1][2]
{0x0F12, 0xFFEC},	//FFEC	//awbb_GridCorr_R[1][3]
{0x0F12, 0xFFEC},	//FFEC	//awbb_GridCorr_R[1][4]
{0x0F12, 0x0050},	//0050	//awbb_GridCorr_R[1][5]
{0x0F12, 0x0000},	//0000	//awbb_GridCorr_R[2][0]
{0x0F12, 0x0014},	//FFEC	//awbb_GridCorr_R[2][1]
{0x0F12, 0x0014},	//FFEC	//awbb_GridCorr_R[2][2]
{0x0F12, 0xFFEC},	//FFEC	//awbb_GridCorr_R[2][3]
{0x0F12, 0xFFEC},	//FFEC	//awbb_GridCorr_R[2][4]
{0x0F12, 0x0050},	//0050	//awbb_GridCorr_R[2][5]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[0][0]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[0][1]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[0][2]
{0x0F12, 0xFF97},	//FF97	//awbb_GridCorr_B[0][3]
{0x0F12, 0xFF97},	//FF97	//awbb_GridCorr_B[0][4]
{0x0F12, 0xFDA8},	//FDA8	//awbb_GridCorr_B[0][5]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[1][0]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[1][1]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[1][2]
{0x0F12, 0xFF97},	//FF97	//awbb_GridCorr_B[1][3]
{0x0F12, 0xFF97},	//FF97	//awbb_GridCorr_B[1][4]
{0x0F12, 0xFDA8},	//FDA8	//awbb_GridCorr_B[1][5]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[2][0]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[2][1]
{0x0F12, 0x0000},	//FFBA	//awbb_GridCorr_B[2][2]
{0x0F12, 0xFF97},	//FF97	//awbb_GridCorr_B[2][3]
{0x0F12, 0xFF97},	//FF97	//awbb_GridCorr_B[2][4]
{0x0F12, 0xFDA8},	//FDA8	//awbb_GridCorr_B[2][5]

{0x002A, 0x1160},
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[0][0]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[0][1]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[0][2]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[0][3]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[0][4]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[0][5]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[1][0]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[1][1]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[1][2]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[1][3]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[1][4]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[1][5]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[2][0]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[2][1]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[2][2]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[2][3]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[2][4]
{0x0F12, 0x0000},	//awbb_GridCorr_R_Out[2][5]
{0x0F12, 0xFFEC},	//awbb_GridCorr_B_Out[0][0]
{0x0F12, 0xFFEC},	//awbb_GridCorr_B_Out[0][1]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[0][2]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[0][3]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[0][4]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[0][5]
{0x0F12, 0xFFEC},	//awbb_GridCorr_B_Out[1][0]
{0x0F12, 0xFFEC},	//awbb_GridCorr_B_Out[1][1]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[1][2]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[1][3]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[1][4]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[1][5]
{0x0F12, 0xFFEC},	//awbb_GridCorr_B_Out[2][0]
{0x0F12, 0xFFEC},	//awbb_GridCorr_B_Out[2][1]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[2][2]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[2][3]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[2][4]
{0x0F12, 0x0000},	//awbb_GridCorr_B_Out[2][5]

//===================================================================
// CCM
//===================================================================
{0x002A, 0x07D2},
{0x0F12, 0x00C0},	//SARR_AwbCcmCord_0_
{0x0F12, 0x00E0},	//SARR_AwbCcmCord_1_
{0x0F12, 0x0110},	//SARR_AwbCcmCord_2_
{0x0F12, 0x0139},	//SARR_AwbCcmCord_3_
{0x0F12, 0x0166},	//SARR_AwbCcmCord_4_
{0x0F12, 0x019F},	//SARR_AwbCcmCord_5_

//	param_start	TVAR_wbt_pBaseCcms
{0x002A, 0x07C4},
{0x0F12, 0x4000},	//TVAR_wbt_pBaseCcms
{0x0F12, 0x7000},

{0x002A, 0x4000},
{0x0F12, 0x01E0},	//020A	//TVAR_wbt_pBaseCcms[0]
{0x0F12, 0xFF90},	//FF7B	//TVAR_wbt_pBaseCcms[1]
{0x0F12, 0xFFF3},	//FFDE	//TVAR_wbt_pBaseCcms[2]
{0x0F12, 0xFF45},	//FF45	//TVAR_wbt_pBaseCcms[3]
{0x0F12, 0x0140},	//0140	//TVAR_wbt_pBaseCcms[4]
{0x0F12, 0xFF4F},	//FF4F	//TVAR_wbt_pBaseCcms[5]
{0x0F12, 0xFFC3},	//FFC3	//TVAR_wbt_pBaseCcms[6]
{0x0F12, 0xFFD5},	//FFD5	//TVAR_wbt_pBaseCcms[7]
{0x0F12, 0x0173},	//0173	//TVAR_wbt_pBaseCcms[8]
{0x0F12, 0x00E7},	//00E7	//TVAR_wbt_pBaseCcms[9]
{0x0F12, 0x00E8},	//00E8	//TVAR_wbt_pBaseCcms[10]
{0x0F12, 0xFEEB},	//FEEB	//TVAR_wbt_pBaseCcms[11]
{0x0F12, 0x00C8},	//00C8	//TVAR_wbt_pBaseCcms[12]
{0x0F12, 0xFF49},	//FF49	//TVAR_wbt_pBaseCcms[13]
{0x0F12, 0x014B},	//014B	//TVAR_wbt_pBaseCcms[14]
{0x0F12, 0xFF68},	//FF68	//TVAR_wbt_pBaseCcms[15]
{0x0F12, 0x0109},	//0109	//TVAR_wbt_pBaseCcms[16]
{0x0F12, 0x00F4},	//00F4	//TVAR_wbt_pBaseCcms[17]

{0x0F12, 0x01E0},	//020A	//TVAR_wbt_pBaseCcms[18]
{0x0F12, 0xFF90},	//FF7B	//TVAR_wbt_pBaseCcms[19]
{0x0F12, 0xFFF3},	//FFDE	//TVAR_wbt_pBaseCcms[20]
{0x0F12, 0xFF45},	//FF45	//TVAR_wbt_pBaseCcms[21]
{0x0F12, 0x0140},	//0140	//TVAR_wbt_pBaseCcms[22]
{0x0F12, 0xFF4F},	//FF4F	//TVAR_wbt_pBaseCcms[23]
{0x0F12, 0xFFC3},	//FFC3	//TVAR_wbt_pBaseCcms[24]
{0x0F12, 0xFFD5},	//FFD5	//TVAR_wbt_pBaseCcms[25]
{0x0F12, 0x0173},	//0173	//TVAR_wbt_pBaseCcms[26]
{0x0F12, 0x00E7},	//00E7	//TVAR_wbt_pBaseCcms[27]
{0x0F12, 0x00E8},	//00E8	//TVAR_wbt_pBaseCcms[28]
{0x0F12, 0xFEEB},	//FEEB	//TVAR_wbt_pBaseCcms[29]
{0x0F12, 0x00C8},	//00C8	//TVAR_wbt_pBaseCcms[30]
{0x0F12, 0xFF49},	//FF49	//TVAR_wbt_pBaseCcms[31]
{0x0F12, 0x014B},	//014B	//TVAR_wbt_pBaseCcms[32]
{0x0F12, 0xFF68},	//FF68	//TVAR_wbt_pBaseCcms[33]
{0x0F12, 0x0109},	//0109	//TVAR_wbt_pBaseCcms[34]
{0x0F12, 0x00F4},	//00F4	//TVAR_wbt_pBaseCcms[35]

{0x0F12, 0x01E0},	//020A	//TVAR_wbt_pBaseCcms[36]
{0x0F12, 0xFF90},	//FF7B	//TVAR_wbt_pBaseCcms[37]
{0x0F12, 0xFFF3},	//FFDE	//TVAR_wbt_pBaseCcms[38]
{0x0F12, 0xFF45},	//FF45	//TVAR_wbt_pBaseCcms[39]
{0x0F12, 0x0140},	//0140	//TVAR_wbt_pBaseCcms[40]
{0x0F12, 0xFF4F},	//FF4F	//TVAR_wbt_pBaseCcms[41]
{0x0F12, 0xFFC3},	//FFC3	//TVAR_wbt_pBaseCcms[42]
{0x0F12, 0xFFD5},	//FFD5	//TVAR_wbt_pBaseCcms[43]
{0x0F12, 0x0173},	//0173	//TVAR_wbt_pBaseCcms[44]
{0x0F12, 0x00E7},	//00E7	//TVAR_wbt_pBaseCcms[45]
{0x0F12, 0x00E8},	//00E8	//TVAR_wbt_pBaseCcms[46]
{0x0F12, 0xFEEB},	//FEEB	//TVAR_wbt_pBaseCcms[47]
{0x0F12, 0x00C8},	//00C8	//TVAR_wbt_pBaseCcms[48]
{0x0F12, 0xFF49},	//FF49	//TVAR_wbt_pBaseCcms[49]
{0x0F12, 0x014B},	//014B	//TVAR_wbt_pBaseCcms[50]
{0x0F12, 0xFF68},	//FF68	//TVAR_wbt_pBaseCcms[51]
{0x0F12, 0x0109},	//0109	//TVAR_wbt_pBaseCcms[52]
{0x0F12, 0x00F4},	//00F4	//TVAR_wbt_pBaseCcms[53]

{0x0F12, 0x01E0},	//020A	//TVAR_wbt_pBaseCcms[54]
{0x0F12, 0xFF90},	//FF7B	//TVAR_wbt_pBaseCcms[55]
{0x0F12, 0xFFF3},	//FFDE	//TVAR_wbt_pBaseCcms[56]
{0x0F12, 0xFF45},	//FF45	//TVAR_wbt_pBaseCcms[57]
{0x0F12, 0x0140},	//0140	//TVAR_wbt_pBaseCcms[58]
{0x0F12, 0xFF4F},	//FF4F	//TVAR_wbt_pBaseCcms[59]
{0x0F12, 0xFFC3},	//FFC3	//TVAR_wbt_pBaseCcms[60]
{0x0F12, 0xFFD5},	//FFD5	//TVAR_wbt_pBaseCcms[61]
{0x0F12, 0x0173},	//0173	//TVAR_wbt_pBaseCcms[62]
{0x0F12, 0x00E7},	//00E7	//TVAR_wbt_pBaseCcms[63]
{0x0F12, 0x00E8},	//00E8	//TVAR_wbt_pBaseCcms[64]
{0x0F12, 0xFEEB},	//FEEB	//TVAR_wbt_pBaseCcms[65]
{0x0F12, 0x00C8},	//00C8	//TVAR_wbt_pBaseCcms[66]
{0x0F12, 0xFF49},	//FF49	//TVAR_wbt_pBaseCcms[67]
{0x0F12, 0x014B},	//014B	//TVAR_wbt_pBaseCcms[68]
{0x0F12, 0xFF68},	//FF68	//TVAR_wbt_pBaseCcms[69]
{0x0F12, 0x0109},	//0109	//TVAR_wbt_pBaseCcms[70]
{0x0F12, 0x00F4},	//00F4	//TVAR_wbt_pBaseCcms[71]

{0x0F12, 0x011D}, 	//TVAR_wbt_pBaseCcms[72]
{0x0F12, 0xFFA7},	//TVAR_wbt_pBaseCcms[73]
{0x0F12, 0xFFEC},	//TVAR_wbt_pBaseCcms[74]
{0x0F12, 0xFF58},	//TVAR_wbt_pBaseCcms[75]
{0x0F12, 0x018C},	//TVAR_wbt_pBaseCcms[76]
{0x0F12, 0xFF1C},	//TVAR_wbt_pBaseCcms[77]
{0x0F12, 0xFFC3},	//TVAR_wbt_pBaseCcms[78]
{0x0F12, 0xFFD5},	//TVAR_wbt_pBaseCcms[79]
{0x0F12, 0x0173},	//TVAR_wbt_pBaseCcms[80]
{0x0F12, 0x00AA},	//TVAR_wbt_pBaseCcms[81]
{0x0F12, 0x00AB},	//TVAR_wbt_pBaseCcms[82]
{0x0F12, 0xFEE1},	//TVAR_wbt_pBaseCcms[83]
{0x0F12, 0x00C8},	//TVAR_wbt_pBaseCcms[84]
{0x0F12, 0xFF49},	//TVAR_wbt_pBaseCcms[85]
{0x0F12, 0x014B},	//TVAR_wbt_pBaseCcms[86]
{0x0F12, 0xFF68},	//TVAR_wbt_pBaseCcms[87]
{0x0F12, 0x0109},	//TVAR_wbt_pBaseCcms[88]
{0x0F12, 0x00F4},	//TVAR_wbt_pBaseCcms[89]

{0x0F12, 0x011D}, //TVAR_wbt_pBaseCcms[90]
{0x0F12, 0xFFA7},	//TVAR_wbt_pBaseCcms[91]
{0x0F12, 0xFFEC},	//TVAR_wbt_pBaseCcms[92]
{0x0F12, 0xFF58},	//TVAR_wbt_pBaseCcms[93]
{0x0F12, 0x018C},	//TVAR_wbt_pBaseCcms[94]
{0x0F12, 0xFF1C},	//TVAR_wbt_pBaseCcms[95]
{0x0F12, 0xFFC3},	//TVAR_wbt_pBaseCcms[96]
{0x0F12, 0xFFD5},	//TVAR_wbt_pBaseCcms[97]
{0x0F12, 0x0173},	//TVAR_wbt_pBaseCcms[98]
{0x0F12, 0x00AA},	//TVAR_wbt_pBaseCcms[99]
{0x0F12, 0x00AB},	//TVAR_wbt_pBaseCcms[100]
{0x0F12, 0xFEE1},	//TVAR_wbt_pBaseCcms[101]
{0x0F12, 0x00C8},	//TVAR_wbt_pBaseCcms[102]
{0x0F12, 0xFF49},	//TVAR_wbt_pBaseCcms[103]
{0x0F12, 0x014B},	//TVAR_wbt_pBaseCcms[104]
{0x0F12, 0xFF68},	//TVAR_wbt_pBaseCcms[105]
{0x0F12, 0x0109},	//TVAR_wbt_pBaseCcms[106]
{0x0F12, 0x00F4},	//TVAR_wbt_pBaseCcms[107]
//	param_end	TVAR_wbt_pBasecms


{0x002A, 0x07CC},
{0x0F12, 0x40D8},	//#TVAR_wbt_pOutdoorCcm
{0x0F12, 0x7000},

{0x002A, 0x40D8},
{0x0F12, 0x0207},	//TVAR_wbt_pOutdoorCcm[0]
{0x0F12, 0xFFBE},	//TVAR_wbt_pOutdoorCcm[1]
{0x0F12, 0xFFE2},	//TVAR_wbt_pOutdoorCcm[2]
{0x0F12, 0xFEAC},	//TVAR_wbt_pOutdoorCcm[3]
{0x0F12, 0x018B},	//TVAR_wbt_pOutdoorCcm[4]
{0x0F12, 0xFF50},	//TVAR_wbt_pOutdoorCcm[5]
{0x0F12, 0x000C},	//TVAR_wbt_pOutdoorCcm[6]
{0x0F12, 0x0000},	//TVAR_wbt_pOutdoorCcm[7]
{0x0F12, 0x0206},	//TVAR_wbt_pOutdoorCcm[8]
{0x0F12, 0x00D0},	//TVAR_wbt_pOutdoorCcm[9]
{0x0F12, 0x00EF},	//TVAR_wbt_pOutdoorCcm[10]
{0x0F12, 0xFF5A},	//TVAR_wbt_pOutdoorCcm[11]
{0x0F12, 0x0220},	//TVAR_wbt_pOutdoorCcm[12]
{0x0F12, 0xFFE7},	//TVAR_wbt_pOutdoorCcm[13]
{0x0F12, 0x01A1},	//TVAR_wbt_pOutdoorCcm[14]
{0x0F12, 0xFEC8},	//TVAR_wbt_pOutdoorCcm[15]
{0x0F12, 0x017D},	//TVAR_wbt_pOutdoorCcm[16]
{0x0F12, 0x0142},	//TVAR_wbt_pOutdoorCcm[17]
//	param_end	TVAR_wbt_pOutdoorCcm


{0x002A, 0x2A64},
{0x0F12, 0x0001},	//#MVAR_AAIO_bFIT
{0x002A, 0x2A68},
{0x0F12, 0x0001},	//#MVAR_AAIO_bAutoCCMandASH
{0x002A, 0x2A3C},
{0x0F12, 0x01DD},	//#Mon_AAIO_PrevFrmData_NormBr

//===================================================================
// AFIT
//===================================================================

//	param_start	afit_uNoiseIndInDoor
{0x002A, 0x085C},
{0x0F12, 0x0049},	//004A	//#afit_uNoiseIndInDoor_0_
{0x0F12, 0x005F},	//005F	//#afit_uNoiseIndInDoor_1_
{0x0F12, 0x00CB},	//00CB	//#afit_uNoiseIndInDoor_2_
{0x0F12, 0x0190},	//01E0	//#afit_uNoiseIndInDoor_3_
{0x0F12, 0x01E0},	//0220	//#afit_uNoiseIndInDoor_4_
//	param_end	afit_uNoiseIndInDoor

{0x002A, 0x08C0},
{0x0F12, 0x0010},	//700008C0	//AFIT NoiseIndex0 Brightness
{0x0F12, 0x0000},	//700008C2        
{0x0F12, 0x0000},	//700008C4        
{0x0F12, 0x0000},	//700008C6
{0x0F12, 0x0000},	//700008C8        
{0x0F12, 0x00C1},	//700008CA        
{0x0F12, 0x0000},	//700008CC        
{0x0F12, 0x03FF},	//700008CE        
{0x0F12, 0x009C},	//700008D0        
{0x0F12, 0x017C},	//700008D2        
{0x0F12, 0x03FF},	//700008D4        
{0x0F12, 0x000C},	//700008D6        
{0x0F12, 0x0010},	//700008D8        
{0x0F12, 0x012C},	//700008DA        
{0x0F12, 0x03E8},	//700008DC        
{0x0F12, 0x0046},	//700008DE        
{0x0F12, 0x005A},	//700008E0        
{0x0F12, 0x0070},	//700008E2        
{0x0F12, 0x000C},	//700008E4	//[15:0]iHystThLow        
{0x0F12, 0x000C},	//700008E6	//[15:0]iHystThHigh        
{0x0F12, 0x01F4},	//700008E8	//[15:0]iHystCenter        
{0x0F12, 0x003C},	//700008EA        
{0x0F12, 0x0008},	//700008EC        
{0x0F12, 0x003C},	//700008EE        
{0x0F12, 0x001E},	//700008F0        
{0x0F12, 0x003C},	//700008F2        
{0x0F12, 0x001E},	//700008F4        
{0x0F12, 0x0A24},	//700008F6        
{0x0F12, 0x1701},	//700008F8        
{0x0F12, 0x0229},	//700008FA        
{0x0F12, 0x1403},	//700008FC        
{0x0F12, 0x0004},	//700008FE        
{0x0F12, 0x0300},	//70000900        
{0x0F12, 0x0000},	//70000902        
{0x0F12, 0x02FF},	//70000904        
{0x0F12, 0x09E8},	//70000906        
{0x0F12, 0x1414},	//70000908        
{0x0F12, 0x0301},	//7000090A        
{0x0F12, 0x0007},	//7000090C        
{0x0F12, 0x4000},	//7000090E        
{0x0F12, 0x7803},	//70000910        
{0x0F12, 0x3C50},	//70000912        
{0x0F12, 0x003C},	//70000914        
{0x0F12, 0x1E80},	//70000916        
{0x0F12, 0x1E08},	//70000918        
{0x0F12, 0x000A},	//7000091A        
{0x0F12, 0x0000},	//7000091C        
{0x0F12, 0x120A},	//7000091E        
{0x0F12, 0x0F00},	//70000920        
{0x0F12, 0x0200},	//70000922        
{0x0F12, 0xFF00},	//70000924        
{0x0F12, 0x0200},	//70000926        
{0x0F12, 0x1B11},	//70000928        
{0x0F12, 0x0000},	//7000092A        
{0x0F12, 0x0009},	//7000092C        
{0x0F12, 0x0406},	//7000092E        
{0x0F12, 0x0605},	//70000930        
{0x0F12, 0x0307},	//70000932        
{0x0F12, 0x0609},	//70000934        
{0x0F12, 0x2C07},	//70000936        
{0x0F12, 0x142C},	//70000938        
{0x0F12, 0x0518},	//7000093A	//[15:8]iUVNRStrengthL, [7:0]iMaxThreshH        
{0x0F12, 0x8005},	//7000093C	//[7:0]iUVNRStrengthH        
{0x0F12, 0x0A80},	//7000093E        
{0x0F12, 0x084B},	//70000940
{0x0F12, 0x0080},	//70000942        
{0x0F12, 0x0101},	//70000944        
{0x0F12, 0x0707},	//70000946        
{0x0F12, 0x4601},	//70000948        
{0x0F12, 0xFF44},	//7000094A        
{0x0F12, 0x50FF},	//7000094C        
{0x0F12, 0x0500},	//7000094E        
{0x0F12, 0x0003},	//70000950        
{0x0F12, 0x1C01},	//70000952        
{0x0F12, 0x0714},	//70000954        
{0x0F12, 0x1464},	//70000956        
{0x0F12, 0x3204},	//70000958        
{0x0F12, 0x3C1E},	//7000095A        
{0x0F12, 0x400F},	//7000095C        
{0x0F12, 0x0204},	//7000095E        
{0x0F12, 0x1403},	//70000960        
{0x0F12, 0x0114},	//70000962        
{0x0F12, 0x0101},	//70000964        
{0x0F12, 0x4446},	//70000966        
{0x0F12, 0x646E},	//70000968        
{0x0F12, 0x0028},	//7000096A        
{0x0F12, 0x030A},	//7000096C        
{0x0F12, 0x0000},	//7000096E        
{0x0F12, 0x141E},	//70000970        
{0x0F12, 0xFF07},	//70000972        
{0x0F12, 0x0432},	//70000974        
{0x0F12, 0x0000},	//70000976        
{0x0F12, 0x0F0F},	//70000978        
{0x0F12, 0x0440},	//7000097A        
{0x0F12, 0x0302},	//7000097C        
{0x0F12, 0x1414},	//7000097E        
{0x0F12, 0x0101},	//70000980        
{0x0F12, 0x4601},	//70000982        
{0x0F12, 0x6E44},	//70000984        
{0x0F12, 0x2864},	//70000986        
{0x0F12, 0x0A00},	//70000988        
{0x0F12, 0x0003},	//7000098A        
{0x0F12, 0x1E00},	//7000098C        
{0x0F12, 0x0714},	//7000098E        
{0x0F12, 0x32FF},	//70000990        
{0x0F12, 0x0004},	//70000992        
{0x0F12, 0x0F00},	//70000994        
{0x0F12, 0x400F},	//70000996        
{0x0F12, 0x0204},	//70000998        
{0x0F12, 0x0003},	//7000099A        
{0x0F12, 0x0001},	//7000099C        
{0x0F12, 0x0000},	//7000099E	//AFIT NoiseIndex1 Brightness       
{0x0F12, 0x0000},	//700009A0        
{0x0F12, 0x0000},	//700009A2        
{0x0F12, 0x0000},	//700009A4        
{0x0F12, 0x0000},	//700009A6        
{0x0F12, 0x00C1},	//700009A8        
{0x0F12, 0x0000},	//700009AA        
{0x0F12, 0x03FF},	//700009AC        
{0x0F12, 0x009C},	//700009AE        
{0x0F12, 0x017C},	//700009B0        
{0x0F12, 0x03FF},	//700009B2        
{0x0F12, 0x000C},	//700009B4        
{0x0F12, 0x0010},	//700009B6        
{0x0F12, 0x012C},	//700009B8        
{0x0F12, 0x03E8},	//700009BA        
{0x0F12, 0x0046},	//700009BC        
{0x0F12, 0x005A},	//700009BE        
{0x0F12, 0x0070},	//700009C0        
{0x0F12, 0x0000},	//700009C2	//[15:0]iHystThLow        
{0x0F12, 0x0000},	//700009C4	//[15:0]iHystThHigh        
{0x0F12, 0x0320},	//700009C6	//[15:0]iHystCenter        
{0x0F12, 0x006E},	//700009C8        
{0x0F12, 0x0014},	//700009CA        
{0x0F12, 0x003C},	//700009CC        
{0x0F12, 0x001E},	//700009CE        
{0x0F12, 0x003C},	//700009D0        
{0x0F12, 0x001E},	//700009D2        
{0x0F12, 0x0A24},	//700009D4        
{0x0F12, 0x1701},	//700009D6        
{0x0F12, 0x0229},	//700009D8        
{0x0F12, 0x1403},	//700009DA        
{0x0F12, 0x0004},	//700009DC        
{0x0F12, 0x0300},	//700009DE        
{0x0F12, 0x0000},	//700009E0        
{0x0F12, 0x02FF},	//700009E2        
{0x0F12, 0x05E8},	//700009E4        
{0x0F12, 0x1414},	//700009E6        
{0x0F12, 0x0301},	//700009E8        
{0x0F12, 0x0007},	//700009EA        
{0x0F12, 0x2000},	//700009EC        
{0x0F12, 0x5003},	//700009EE        
{0x0F12, 0x3228},	//700009F0        
{0x0F12, 0x0032},	//700009F2        
{0x0F12, 0x1E80},	//700009F4        
{0x0F12, 0x1E08},	//700009F6        
{0x0F12, 0x000A},	//700009F8        
{0x0F12, 0x0000},	//700009FA        
{0x0F12, 0x120A},	//700009FC        
{0x0F12, 0x1400},	//700009FE        
{0x0F12, 0x0200},	//70000A00        
{0x0F12, 0xFF00},	//70000A02        
{0x0F12, 0x0200},	//70000A04        
{0x0F12, 0x1B11},	//70000A06        
{0x0F12, 0x0000},	//70000A08        
{0x0F12, 0x0009},	//70000A0A        
{0x0F12, 0x0406},	//70000A0C        
{0x0F12, 0x0605},	//70000A0E        
{0x0F12, 0x0307},	//70000A10        
{0x0F12, 0x0609},	//70000A12        
{0x0F12, 0x2C07},	//70000A14        
{0x0F12, 0x142C},	//70000A16        
{0x0F12, 0x0518},	//70000A18	//[15:8]iUVNRStrengthL, [7:0]iMaxThreshH        
{0x0F12, 0x8005},	//70000A1A	//[7:0]iUVNRStrengthH        
{0x0F12, 0x0580},	//70000A1C        
{0x0F12, 0x0080},	//70000A1E        
{0x0F12, 0x0080},	//70000A20        
{0x0F12, 0x0101},	//70000A22        
{0x0F12, 0x0707},	//70000A24        
{0x0F12, 0x4B01},	//70000A26        
{0x0F12, 0x494B},	//70000A28        
{0x0F12, 0x5044},	//70000A2A        
{0x0F12, 0x0500},	//70000A2C        
{0x0F12, 0x0503},	//70000A2E        
{0x0F12, 0x0D02},	//70000A30        
{0x0F12, 0x071E},	//70000A32        
{0x0F12, 0x1432},	//70000A34        
{0x0F12, 0x3201},	//70000A36        
{0x0F12, 0x2814},	//70000A38        
{0x0F12, 0x200F},	//70000A3A        
{0x0F12, 0x0204},	//70000A3C        
{0x0F12, 0x1E03},	//70000A3E        
{0x0F12, 0x011E},	//70000A40        
{0x0F12, 0x0101},	//70000A42        
{0x0F12, 0x3A3C},	//70000A44        
{0x0F12, 0x585A},	//70000A46        
{0x0F12, 0x0028},	//70000A48        
{0x0F12, 0x030A},	//70000A4A        
{0x0F12, 0x0000},	//70000A4C        
{0x0F12, 0x141E},	//70000A4E        
{0x0F12, 0xFF07},	//70000A50        
{0x0F12, 0x0432},	//70000A52        
{0x0F12, 0x0000},	//70000A54        
{0x0F12, 0x0F0F},	//70000A56        
{0x0F12, 0x0440},	//70000A58        
{0x0F12, 0x0302},	//70000A5A        
{0x0F12, 0x1E1E},	//70000A5C        
{0x0F12, 0x0101},	//70000A5E        
{0x0F12, 0x3C01},	//70000A60        
{0x0F12, 0x5A3A},	//70000A62        
{0x0F12, 0x2858},	//70000A64        
{0x0F12, 0x0A00},	//70000A66        
{0x0F12, 0x0003},	//70000A68        
{0x0F12, 0x1E00},	//70000A6A        
{0x0F12, 0x0714},	//70000A6C        
{0x0F12, 0x32FF},	//70000A6E        
{0x0F12, 0x0004},	//70000A70        
{0x0F12, 0x0F00},	//70000A72        
{0x0F12, 0x400F},	//70000A74        
{0x0F12, 0x0204},	//70000A76        
{0x0F12, 0x0003},	//70000A78        
{0x0F12, 0x0001},	//70000A7A        
{0x0F12, 0x0000},	//70000A7C	//AFIT NoiseIndex2 Brightness               
{0x0F12, 0x0000},	//70000A7E        
{0x0F12, 0x0000},	//70000A80        
{0x0F12, 0x0000},	//70000A82        
{0x0F12, 0x0000},	//70000A84        
{0x0F12, 0x00C1},	//70000A86        
{0x0F12, 0x0000},	//70000A88        
{0x0F12, 0x03FF},	//70000A8A        
{0x0F12, 0x009E},	//70000A8C        
{0x0F12, 0x017C},	//70000A8E        
{0x0F12, 0x03FF},	//70000A90        
{0x0F12, 0x000C},	//70000A92        
{0x0F12, 0x0010},	//70000A94        
{0x0F12, 0x012C},	//70000A96        
{0x0F12, 0x03E8},	//70000A98        
{0x0F12, 0x0046},	//70000A9A        
{0x0F12, 0x005A},	//70000A9C        
{0x0F12, 0x0070},	//70000A9E        
{0x0F12, 0x0000},	//70000AA0	//[15:0]iHystThLow        
{0x0F12, 0x0000},	//70000AA2	//[15:0]iHystThHigh        
{0x0F12, 0x0320},	//70000AA4	//[15:0]iHystCenter        
{0x0F12, 0x008C},	//70000AA6        
{0x0F12, 0x0014},	//70000AA8        
{0x0F12, 0x003C},	//70000AAA        
{0x0F12, 0x001E},	//70000AAC        
{0x0F12, 0x003C},	//70000AAE        
{0x0F12, 0x001E},	//70000AB0        
{0x0F12, 0x0A24},	//70000AB2        
{0x0F12, 0x1701},	//70000AB4        
{0x0F12, 0x0229},	//70000AB6        
{0x0F12, 0x1403},	//70000AB8        
{0x0F12, 0x0004},	//70000ABA        
{0x0F12, 0x0300},	//70000ABC        
{0x0F12, 0x0000},	//70000ABE        
{0x0F12, 0x02FF},	//70000AC0        
{0x0F12, 0x05DE},	//70000AC2        
{0x0F12, 0x1414},	//70000AC4        
{0x0F12, 0x0301},	//70000AC6        
{0x0F12, 0x0007},	//70000AC8        
{0x0F12, 0x1000},	//70000ACA        
{0x0F12, 0x2803},	//70000ACC        
{0x0F12, 0x261E},	//70000ACE        
{0x0F12, 0x0026},	//70000AD0        
{0x0F12, 0x1E80},	//70000AD2        
{0x0F12, 0x1E08},	//70000AD4        
{0x0F12, 0x010A},	//70000AD6        
{0x0F12, 0x0001},	//70000AD8        
{0x0F12, 0x3C0A},	//70000ADA        
{0x0F12, 0x2300},	//70000ADC        
{0x0F12, 0x0200},	//70000ADE        
{0x0F12, 0xFF00},	//70000AE0        
{0x0F12, 0x0200},	//70000AE2        
{0x0F12, 0x1B11},	//70000AE4        
{0x0F12, 0x0000},	//70000AE6        
{0x0F12, 0x0009},	//70000AE8        
{0x0F12, 0x0406},	//70000AEA        
{0x0F12, 0x0605},	//70000AEC        
{0x0F12, 0x0307},	//70000AEE        
{0x0F12, 0x0609},	//70000AF0        
{0x0F12, 0x1C07},	//70000AF2        
{0x0F12, 0x1014},	//70000AF4        
{0x0F12, 0x0510},	//70000AF6	//[15:8]iUVNRStrengthL, [7:0]iMaxThreshH        
{0x0F12, 0x8005},	//70000AF8	//[7:0]iUVNRStrengthH        
{0x0F12, 0x0080},	//70000AFA        
{0x0F12, 0x0080},	//70000AFC        
{0x0F12, 0x0080},	//70000AFE        
{0x0F12, 0x0101},	//70000B00        
{0x0F12, 0x0707},	//70000B02        
{0x0F12, 0x4B01},	//70000B04        
{0x0F12, 0x2A4B},	//70000B06        
{0x0F12, 0x5020},	//70000B08        
{0x0F12, 0x0500},	//70000B0A        
{0x0F12, 0x1C03},	//70000B0C        
{0x0F12, 0x0D0C},	//70000B0E        
{0x0F12, 0x0823},	//70000B10        
{0x0F12, 0x1428},	//70000B12        
{0x0F12, 0x4101},	//70000B14        
{0x0F12, 0x282D},	//70000B16        
{0x0F12, 0x2012},	//70000B18        
{0x0F12, 0x0204},	//70000B1A        
{0x0F12, 0x2803},	//70000B1C        
{0x0F12, 0x0128},	//70000B1E        
{0x0F12, 0x0101},	//70000B20        
{0x0F12, 0x2224},	//70000B22        
{0x0F12, 0x3236},	//70000B24        
{0x0F12, 0x0028},	//70000B26        
{0x0F12, 0x030A},	//70000B28        
{0x0F12, 0x0410},	//70000B2A        
{0x0F12, 0x141E},	//70000B2C        
{0x0F12, 0xFF07},	//70000B2E        
{0x0F12, 0x0432},	//70000B30        
{0x0F12, 0x4050},	//70000B32        
{0x0F12, 0x0F0F},	//70000B34        
{0x0F12, 0x0440},	//70000B36        
{0x0F12, 0x0302},	//70000B38        
{0x0F12, 0x2828},	//70000B3A        
{0x0F12, 0x0101},	//70000B3C        
{0x0F12, 0x2401},	//70000B3E        
{0x0F12, 0x3622},	//70000B40        
{0x0F12, 0x2832},	//70000B42        
{0x0F12, 0x0A00},	//70000B44        
{0x0F12, 0x1003},	//70000B46        
{0x0F12, 0x1E04},	//70000B48        
{0x0F12, 0x0714},	//70000B4A        
{0x0F12, 0x32FF},	//70000B4C        
{0x0F12, 0x5004},	//70000B4E        
{0x0F12, 0x0F40},	//70000B50        
{0x0F12, 0x400F},	//70000B52        
{0x0F12, 0x0204},	//70000B54        
{0x0F12, 0x0003},	//70000B56        
{0x0F12, 0x0001},	//70000B58        
{0x0F12, 0x0000},	//70000B5A	//AFIT NoiseIndex3 Brightness
{0x0F12, 0x0000},	//70000B5C        
{0x0F12, 0x0000},	//70000B5E        
{0x0F12, 0x0000},	//70000B60        
{0x0F12, 0x0000},	//70000B62        
{0x0F12, 0x00C1},	//70000B64        
{0x0F12, 0x0000},	//70000B66        
{0x0F12, 0x03FF},	//70000B68        
{0x0F12, 0x009E},	//70000B6A        
{0x0F12, 0x017C},	//70000B6C        
{0x0F12, 0x03FF},	//70000B6E        
{0x0F12, 0x000C},	//70000B70        
{0x0F12, 0x0010},	//70000B72        
{0x0F12, 0x00C8},	//70000B74        
{0x0F12, 0x03E8},	//70000B76        
{0x0F12, 0x0046},	//70000B78        
{0x0F12, 0x0050},	//70000B7A        
{0x0F12, 0x0070},	//70000B7C        
{0x0F12, 0x0000},	//70000B7E	//[15:0]iHystThLow        
{0x0F12, 0x0000},	//70000B80	//[15:0]iHystThHigh        
{0x0F12, 0x0320},	//70000B82	//[15:0]iHystCenter        
{0x0F12, 0x008C},	//70000B84        
{0x0F12, 0x0014},	//70000B86        
{0x0F12, 0x002D},	//70000B88        
{0x0F12, 0x0019},	//70000B8A        
{0x0F12, 0x002D},	//70000B8C        
{0x0F12, 0x0019},	//70000B8E        
{0x0F12, 0x0A24},	//70000B90        
{0x0F12, 0x1701},	//70000B92        
{0x0F12, 0x0229},	//70000B94        
{0x0F12, 0x1403},	//70000B96        
{0x0F12, 0x0004},	//70000B98        
{0x0F12, 0x0300},	//70000B9A        
{0x0F12, 0x0000},	//70000B9C        
{0x0F12, 0x02FF},	//70000B9E        
{0x0F12, 0x05DE},	//70000BA0        
{0x0F12, 0x1414},	//70000BA2        
{0x0F12, 0x0301},	//70000BA4        
{0x0F12, 0x0007},	//70000BA6        
{0x0F12, 0x1000},	//70000BA8        
{0x0F12, 0x2303},	//70000BAA        
{0x0F12, 0x231A},	//70000BAC        
{0x0F12, 0x0023},	//70000BAE        
{0x0F12, 0x1E80},	//70000BB0        
{0x0F12, 0x1E08},	//70000BB2        
{0x0F12, 0x010A},	//70000BB4        
{0x0F12, 0x0001},	//70000BB6        
{0x0F12, 0x3C0A},	//70000BB8        
{0x0F12, 0x2300},	//70000BBA        
{0x0F12, 0x0200},	//70000BBC        
{0x0F12, 0xFF00},	//70000BBE        
{0x0F12, 0x0200},	//70000BC0        
{0x0F12, 0x1E10},	//70000BC2        
{0x0F12, 0x0000},	//70000BC4        
{0x0F12, 0x0009},	//70000BC6        
{0x0F12, 0x0406},	//70000BC8        
{0x0F12, 0x0705},	//70000BCA        
{0x0F12, 0x0306},	//70000BCC        
{0x0F12, 0x0509},	//70000BCE        
{0x0F12, 0x2806},	//70000BD0        
{0x0F12, 0x1428},	//70000BD2        
{0x0F12, 0x0518},	//70000BD4	//[15:8]iUVNRStrengthL, [7:0]iMaxThreshH        
{0x0F12, 0x8005},	//70000BD6	//[7:0]iUVNRStrengthH        
{0x0F12, 0x0080},	//70000BD8        
{0x0F12, 0x0080},	//70000BDA        
{0x0F12, 0x0080},	//70000BDC        
{0x0F12, 0x0101},	//70000BDE        
{0x0F12, 0x0707},	//70000BE0        
{0x0F12, 0x4B01},	//70000BE2        
{0x0F12, 0x2A4B},	//70000BE4        
{0x0F12, 0x5020},	//70000BE6        
{0x0F12, 0x0500},	//70000BE8        
{0x0F12, 0x1C03},	//70000BEA        
{0x0F12, 0x0D0C},	//70000BEC        
{0x0F12, 0x0823},	//70000BEE        
{0x0F12, 0x1428},	//70000BF0        
{0x0F12, 0x4101},	//70000BF2        
{0x0F12, 0x282D},	//70000BF4        
{0x0F12, 0x2012},	//70000BF6        
{0x0F12, 0x0204},	//70000BF8        
{0x0F12, 0x3C03},	//70000BFA        
{0x0F12, 0x013C},	//70000BFC        
{0x0F12, 0x0101},	//70000BFE        
{0x0F12, 0x1C1E},	//70000C00        
{0x0F12, 0x1E22},	//70000C02        
{0x0F12, 0x0028},	//70000C04        
{0x0F12, 0x030A},	//70000C06        
{0x0F12, 0x0214},	//70000C08        
{0x0F12, 0x0E14},	//70000C0A        
{0x0F12, 0xFF06},	//70000C0C        
{0x0F12, 0x0432},	//70000C0E        
{0x0F12, 0x4052},	//70000C10        
{0x0F12, 0x150C},	//70000C12        
{0x0F12, 0x0440},	//70000C14        
{0x0F12, 0x0302},	//70000C16        
{0x0F12, 0x3C3C},	//70000C18        
{0x0F12, 0x0101},	//70000C1A        
{0x0F12, 0x1E01},	//70000C1C        
{0x0F12, 0x221C},	//70000C1E        
{0x0F12, 0x281E},	//70000C20        
{0x0F12, 0x0A00},	//70000C22        
{0x0F12, 0x1403},	//70000C24        
{0x0F12, 0x1402},	//70000C26        
{0x0F12, 0x060E},	//70000C28        
{0x0F12, 0x32FF},	//70000C2A        
{0x0F12, 0x5204},	//70000C2C        
{0x0F12, 0x0C40},	//70000C2E        
{0x0F12, 0x4015},	//70000C30        
{0x0F12, 0x0204},	//70000C32        
{0x0F12, 0x0003},	//70000C34        
{0x0F12, 0x0001},	//70000C36        
{0x0F12, 0x0000},	//70000C38	//AFIT NoiseIndex4 Brightness        
{0x0F12, 0x0000},	//70000C3A        
{0x0F12, 0x0000},	//70000C3C        
{0x0F12, 0x0000},	//70000C3E        
{0x0F12, 0x0000},	//70000C40        
{0x0F12, 0x00C1},	//70000C42        
{0x0F12, 0x0000},	//70000C44        
{0x0F12, 0x03FF},	//70000C46        
{0x0F12, 0x0008},	//70000C48        
{0x0F12, 0x017C},	//70000C4A        
{0x0F12, 0x03FF},	//70000C4C        
{0x0F12, 0x000C},	//70000C4E        
{0x0F12, 0x0010},	//70000C50        
{0x0F12, 0x0032},	//70000C52        
{0x0F12, 0x028A},	//70000C54        
{0x0F12, 0x0032},	//70000C56        
{0x0F12, 0x01F4},	//70000C58        
{0x0F12, 0x0070},	//70000C5A        
{0x0F12, 0x0001},	//70000C5C	//[15:0]iHystThLow        
{0x0F12, 0x0000},	//70000C5E	//[15:0]iHystThHigh        
{0x0F12, 0x0320},	//70000C60	//[15:0]iHystCenter        
{0x0F12, 0x0070},	//70000C62	//AFIT NoiseIndex4 iLowSharpClamp        
{0x0F12, 0x0014},	//70000C64	//AFIT NoiseIndex4 iHighSharpClamp
{0x0F12, 0x0046},	//70000C66        
{0x0F12, 0x0019},	//70000C68        
{0x0F12, 0x0046},	//70000C6A        
{0x0F12, 0x0019},	//70000C6C        
{0x0F12, 0x0A24},	//70000C6E        
{0x0F12, 0x1701},	//70000C70        
{0x0F12, 0x0229},	//70000C72        
{0x0F12, 0x0503},	//70000C74        
{0x0F12, 0x0101},	//70000C76        
{0x0F12, 0x0101},	//70000C78        
{0x0F12, 0x0000},	//70000C7A        
{0x0F12, 0x02FF},	//70000C7C        
{0x0F12, 0x0496},	//70000C7E        
{0x0F12, 0x1414},	//70000C80        
{0x0F12, 0x0301},	//70000C82        
{0x0F12, 0x0007},	//70000C84        
{0x0F12, 0x1000},	//70000C86        
{0x0F12, 0x2003},	//70000C88        
{0x0F12, 0x1020},	//70000C8A        
{0x0F12, 0x0010},	//70000C8C        
{0x0F12, 0x1E80},	//70000C8E        
{0x0F12, 0x1E06},	//70000C90        
{0x0F12, 0x030C},	//70000C92	//[15:8] iGRDenoiseVal        
{0x0F12, 0x0103},	//70000C94	//[7:0] iGBDenoiseVal        
{0x0F12, 0x5A0A},	//70000C96	//AFIT NoiseIndex4 [15:8] iMSharpen
{0x0F12, 0x2D00},	//70000C98	//AFIT NoiseIndex4 [15:8] iWSharpen
{0x0F12, 0x0100},	//70000C9A        
{0x0F12, 0xFF00},	//70000C9C        
{0x0F12, 0x0200},	//70000C9E        
{0x0F12, 0x1E10},	//70000CA0        
{0x0F12, 0x0000},	//70000CA2        
{0x0F12, 0x0009},	//70000CA4        
{0x0F12, 0x0406},	//70000CA6        
{0x0F12, 0x0705},	//70000CA8        
{0x0F12, 0x0305},	//70000CAA        
{0x0F12, 0x0609},	//70000CAC        
{0x0F12, 0x2C07},	//70000CAE        
{0x0F12, 0x142C},	//70000CB0        
{0x0F12, 0x0518},	//70000CB2	//[15:8]iUVNRStrengthL, [7:0]iMaxThreshH        
{0x0F12, 0x8005},	//70000CB4	//[7:0]iUVNRStrengthH        
{0x0F12, 0x0F80},	//70000CB6        
{0x0F12, 0x0080},	//70000CB8        
{0x0F12, 0x0080},	//70000CBA        
{0x0F12, 0x0101},	//70000CBC        
{0x0F12, 0x0A0A},	//70000CBE        
{0x0F12, 0x3201},	//70000CC0        
{0x0F12, 0x1428},	//70000CC2	//[15:8]iDenThreshLow        
{0x0F12, 0x100C},	//70000CC4	//[7:0]iDenThreshHigh
{0x0F12, 0x0500},	//70000CC6        
{0x0F12, 0x1E02},	//70000CC8	//AFIT NoiseIndex4 [15:8] iDemSharpenLow
{0x0F12, 0x0409},	//0414	//70000CCA	//AFIT NoiseIndex4 [7:0] iDemSharpenHigh
{0x0F12, 0x0828},	//70000CCC        
{0x0F12, 0x5064},	//70000CCE        
{0x0F12, 0x4605},	//70000CD0	//AFIT NoiseIndex4 [15:8] iLowSharpPower
{0x0F12, 0x1E78},	//1EA0 //70000CD2	//AFIT NoiseIndex4 [7:0] iHighSharpPower
{0x0F12, 0x201E},	//70000CD4
{0x0F12, 0x0604},	//70000CD6
{0x0F12, 0x4606},	//70000CD8
{0x0F12, 0x0146},	//70000CDA
{0x0F12, 0x0101},	//70000CDC
{0x0F12, 0x1C18},	//70000CDE
{0x0F12, 0x1819},	//70000CE0
{0x0F12, 0x0028},	//70000CE2
{0x0F12, 0x030A},	//70000CE4
{0x0F12, 0x0514},	//70000CE6
{0x0F12, 0x0C14},	//70000CE8
{0x0F12, 0xFF05},	//70000CEA
{0x0F12, 0x0432},	//70000CEC
{0x0F12, 0x4052},	//70000CEE
{0x0F12, 0x1514},	//70000CF0
{0x0F12, 0x0440},	//70000CF2
{0x0F12, 0x0302},	//70000CF4
{0x0F12, 0x4646},	//70000CF6
{0x0F12, 0x0101},	//70000CF8
{0x0F12, 0x1801},	//70000CFA
{0x0F12, 0x191C},	//70000CFC
{0x0F12, 0x2818},	//70000CFE
{0x0F12, 0x0A00},	//70000D00
{0x0F12, 0x1403},	//70000D02
{0x0F12, 0x1405},	//70000D04
{0x0F12, 0x050C},	//70000D06
{0x0F12, 0x32FF},	//70000D08
{0x0F12, 0x5204},	//70000D0A
{0x0F12, 0x1440},	//70000D0C
{0x0F12, 0x4015},	//70000D0E
{0x0F12, 0x0204},	//70000D10
{0x0F12, 0x0003},	//70000D12
{0x0F12, 0x0001},	//70000D14

{0x0F12, 0xBA7A},	//70000D16
{0x0F12, 0x4FDE},	//70000D18
{0x0F12, 0x137F},	//70000D1A
{0x0F12, 0x3BDE},	//70000D1C
{0x0F12, 0xBF02},	//70000D1E
{0x0F12, 0x00B5},	//70000D20

};

s5k5ccff_short_t s5k5ccff_camcorder_set[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01F6},
{0x0F12, 0x0800},	//REG_TC_GP_PrevReqInputWidth		//Sensor Crop Width	2048
{0x0F12, 0x0600},	//REG_TC_GP_PrevReqInputHeight	//Sensor Crop Height 1536
{0x0F12, 0x0000},	//REG_TC_GP_PrevInputWidthOfs		//Sensor HOffset 0
{0x0F12, 0x0000},	//REG_TC_GP_PrevInputHeightOfs	//Sensor VOffset 0
{0x0F12, 0x0800},	//REG_TC_GP_CapReqInputWidth		//Sensor Crop Width	2048
{0x0F12, 0x0600},	//REG_TC_GP_CapReqInputHeight		//Sensor Crop Height 1368
{0x0F12, 0x0000},	//REG_TC_GP_CapInputWidthOfs		//Sensor HOffset 0
{0x0F12, 0x0000},	//REG_TC_GP_CapInputHeightOfs		//Sensor VOffset 0
{0x002A, 0x0216},
{0x0F12, 0x0001},	//REG_TC_GP_bUseReqInputInPre
{0x0F12, 0x0001},	//REG_TC_GP_bUseReqInputInCap


//Preview Size
{0x002A, 0x023E},
{0x0F12, 0x0280},	//REG_0TC_PCFG_usWidth
{0x0F12, 0x01E0},	//REG_0TC_PCFG_usHeight

{0x002A, 0x029E},
{0x0F12, 0x0280},		//REG_2TC_PCFG_usWidth
{0x0F12, 0x01E0},   //REG_2TC_PCFG_usHeight

//Capture Size
{0x002A, 0x0330},
{0x0F12, 0x0800},	//REG_0TC_CCFG_usWidth
{0x0F12, 0x0600},	//REG_0TC_CCFG_usHeight

{0x002A, 0x0388},
{0x0F12, 0x0800},   //REG_2TC_CCFG_usWidth
{0x0F12, 0x0600},   //REG_2TC_CCFG_usHeight

};



s5k5ccff_short_t s5k5ccff_preview[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreviewChanged
};


s5k5ccff_short_t s5k5ccff_high_snapshot[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig 0000 : capture configuration 선택하여  입력하면 됨.
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync 0001 : update configuration
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged 0001
{0x002A, 0x01E8},
{0x0F12, 0x0001},	//REG_TC_GP_EnableCapture 0001 : capture 수행
{0x0F12, 0x0001},	//REG_TC_GP_EnableCaptureChanged 0001 : 적용

//{0xFFFF, 0x00A0},   //160ms 
};

s5k5ccff_short_t s5k5ccff_snapshot[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig 0000 : capture configuration 선택하여  입력하면 됨.
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync 0001 : update configuration
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged 0001
{0x002A, 0x01E8},
{0x0F12, 0x0001},	//REG_TC_GP_EnableCapture 0001 : capture 수행
{0x0F12, 0x0001},	//REG_TC_GP_EnableCaptureChanged 0001 : 적용

//{0xFFFF, 0x00A0},   //160ms 
};


s5k5ccff_short_t s5k5ccff_lowlight_snapshot[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig 0000 : capture configuration 선택하여  입력하면 됨.
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync 0001 : update configuration
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged 0001
{0x002A, 0x01E8},
{0x0F12, 0x0001},	//REG_TC_GP_EnableCapture 0001 : capture 수행
{0x0F12, 0x0001},	//REG_TC_GP_EnableCaptureChanged 0001 : 적용

//{0xFFFF, 0x00A0},   //160ms
};

s5k5ccff_short_t s5k5ccff_night_snapshot[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x0208},
{0x0F12, 0x0002},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0002},	//REG_TC_GP_ActiveCapConfig 0000 : capture configuration 선택하여  입력하면 됨.
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync 0001 : update configuration
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged 0001
{0x002A, 0x01E8},
{0x0F12, 0x0001},	//REG_TC_GP_EnableCapture 0001 : capture 수행
{0x0F12, 0x0001},	//REG_TC_GP_EnableCaptureChanged 0001 : 적용

//{0xFFFF, 0x012C},   //300ms 
};




s5k5ccff_short_t s5k5ccff_fps_15fix[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x025A},
{0x0F12, 0x029A},	//REG_0TC_PCFG_usMaxFrTimeMsecMult10	//max frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS
{0x0F12, 0x029A},	//REG_0TC_PCFG_usMinFrTimeMsecMult10	//min frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS

{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreviewChanged
};


s5k5ccff_short_t s5k5ccff_fps_30fix[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x025A},
{0x0F12, 0x014E},	//REG_0TC_PCFG_usMaxFrTimeMsecMult10	//max frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS
{0x0F12, 0x014E},	//REG_0TC_PCFG_usMinFrTimeMsecMult10	//min frame time : 30fps 014D 15fps 029a; a6a - 3.75 fps; 0535 - 7.5FPS

{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},	//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreviewChanged
};


//effect off = normal
s5k5ccff_short_t s5k5ccff_effect_off[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x0648},
{0x0F12, 0x0001},		//skl_af_bPregmOff	Pre/Post Gamma Off (원복)  
  
{0x002A, 0x01E2},
{0x0F12, 0x0000},		//REG_TC_GP_SpecialEffects	00:Normal Mode
};

s5k5ccff_short_t s5k5ccff_effect_mono[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01E2},
{0x0F12, 0x0001},		//REG_TC_GP_SpecialEffects	01:Mono Mode
};

s5k5ccff_short_t s5k5ccff_effect_sepia[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01E2},
{0x0F12, 0x0004},		//REG_TC_GP_SpecialEffects	04:Sepia Mode
};

s5k5ccff_short_t s5k5ccff_effect_negative[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01E2},
{0x0F12, 0x0003},		//REG_TC_GP_SpecialEffects	03:Negative Mode
};


s5k5ccff_short_t s5k5ccff_wb_auto[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0F12, 0x0001},		//Mon_AAIO_bAWB		AWB ON
};

s5k5ccff_short_t s5k5ccff_wb_daylight[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x0600},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x0526},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};

s5k5ccff_short_t s5k5ccff_wb_cloudy[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x0710},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x0476},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};

s5k5ccff_short_t s5k5ccff_wb_fluorescent[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x0530},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x07E6},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};

s5k5ccff_short_t s5k5ccff_wb_incandescent[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x03B0},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x0A00},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};

s5k5ccff_short_t s5k5ccff_brightness_m_4[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0xFF70},		//REG_TC_UserBrightness 
{0x002A, 0x1308},	
{0x0F12, 0x001C},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_m_3[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0xFF94},		//REG_TC_UserBrightness 
{0x002A, 0x1308},
{0x0F12, 0x0025},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_m_2[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0xFFB8},		//REG_TC_UserBrightness 
{0x002A, 0x1308},
{0x0F12, 0x002D},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_m_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0xFFDC},		//REG_TC_UserBrightness 
{0x002A, 0x1308},
{0x0F12, 0x0036},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_0[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness 
{0x002A, 0x1308},
{0x0F12, 0x003E},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_p_1[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0020},		//REG_TC_UserBrightness 
{0x002A, 0x1308},
{0x0F12, 0x0041},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_p_2[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0040},		//REG_TC_UserBrightness  
{0x002A, 0x1308},
{0x0F12, 0x0044},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_p_3[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D0},
{0x0F12, 0x0060},		//REG_TC_UserBrightness
{0x002A, 0x1308},
{0x0F12, 0x0047},		//TVAR_ae_BrAve
};

s5k5ccff_short_t s5k5ccff_brightness_p_4[] = 
{
{0xFCFC, 0xD000},                  
{0x0028, 0x7000},                  
{0x002A, 0x01D0},                  
{0x0F12, 0x0082},		//REG_TC_UserBrightness
{0x002A, 0x1308},
{0x0F12, 0x004A},		//TVAR_ae_BrAve
};


s5k5ccff_short_t s5k5ccff_scene_off[] = 
{
// ==========================================================
// 	CAMERA_SCENE_OFF
// ==========================================================
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0F12, 0x0001},		//Mon_AAIO_bAWB		0: AWB OFF, 1: AWB ON

//	01. Portait / Landscape / Text / Fall Color Off
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness
{0x002A, 0x0000},
{0x0F12, 0x0000},		//REG_TC_UserSaturation
{0x0F12, 0x0000},		//REG_TC_UserSharpBlur

{0x0028, 0x7000},
{0x002A, 0x1316},		//ae_WeightTbl_16

{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0201},
{0x0F12, 0x0102},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0101},
{0x0F12, 0x0201},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0102},
{0x0F12, 0x0201},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0102},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},      

//	02. Night / Firework Off
{0x0028, 0x7000},
{0x002A, 0x0504},
{0x0F12, 0x3415},		//lt_uMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0508},
{0x0F12, 0x681F},		//lt_uMaxExp2		681Fh = 26655d =  66.6375ms
{0x002A, 0x050C},
{0x0F12, 0x8227},		//lt_uMaxExp3		8227h = 33319d =  83.2975ms
{0x002A, 0x0510},
{0x0F12, 0xC350},		//lt_uMaxExp4		C350h = 50000d = 125.0000ms
{0x0F12, 0x0000},

{0x002A, 0x0514},
{0x0F12, 0x3415},		//lt_uCapMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0518},
{0x0F12, 0x681F},		//lt_uCapMaxExp2		681Fh = 26655d =  66.6375ms
{0x002A, 0x051C},
{0x0F12, 0x8227},		//lt_uCapMaxExp3		8227h = 33319d =  83.2975ms
{0x002A, 0x0520},
{0x0F12, 0xC350},		//lt_uCapMaxExp4		C350h = 50000d = 125.0000ms
{0x0F12, 0x0000},

{0x002A, 0x0524},
{0x0F12, 0x01D0},		//lt_uMaxAnGain1		0180h	= 0384d	= x1.5000
{0x0F12, 0x01D0},		//lt_uMaxAnGain2		0180h	= 0384d	= x1.5000
{0x0F12, 0x02C0},		//lt_uMaxAnGain3		0250h	= 0592d	= x2.3125
{0x0F12, 0x0710},		//lt_uMaxAnGain4		0710h	= 1808d	= x7.0625

{0x0F12, 0x0100},		//lt_uMaxDigGain
{0x0F12, 0x8000},		//lt_uMaxTotGain

{0x0F12, 0x01D0},		//lt_uCapMaxAnGain1		0180h	= 0384d	= x1.5000
{0x0F12, 0x01D0},		//lt_uCapMaxAnGain2		0180h	= 0384d	= x1.5000
{0x0F12, 0x02C0},		//lt_uCapMaxAnGain3		0250h	= 0592d	= x2.3125
{0x0F12, 0x0710},		//lt_uCapMaxAnGain4		0710h	= 1808d	= x7.0625

{0x0F12, 0x0100},		//lt_uCapMaxDigGain
{0x0F12, 0x8000},		//lt_uCapMaxTotGain

{0x002A, 0x08E4},
{0x0F12, 0x000C},		//AFIT16_demsharpmix1_iHystThLow
{0x0F12, 0x000C},		//AFIT16_demsharpmix1_iHystThHigh
{0x002A, 0x0940},
{0x0F12, 0x084B},		//[15:8] AFIT8_RGB2YUV_iYOffset, [7:0] AFIT8_ccm_oscar_iSaturation


//	03. ISO Auto




{0x002A, 0x04A4},
{0x0F12, 0x067F},		//REG_TC_DBG_AutoAlgEnBits		Auto Algorithm Enable
{0x002A, 0x048C},
{0x0F12, 0x0001},		//REG_SF_USER_FlickerQuant		0:No AFC, 1:50Hz, 2:60Hz
{0x0F12, 0x0001},		//REG_SF_USER_FlickerQuantChanged



{0x002A, 0x0486},
{0x0F12, 0x0000},		//REG_SF_USER_IsoType		0:OFF 3:ISO
{0x002A, 0x048A},
{0x0F12, 0x0001},		//REG_SF_USER_IsoChanged

{0x002A, 0x3302},
{0x0F12, 0x0000},		//AFIT by Normalized Brightness Tunning Parameter

//Preview
{0x002A, 0x0208},
{0x0F12, 0x0000},		//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0000},		//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},		//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},		//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},		//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},		//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreviewChanged 
};

s5k5ccff_short_t s5k5ccff_scene_portrait[] = 
{
// ==========================================================
// 	CAMERA_SCENE_PORTRAIT (Auto/Center/Br0/Auto/Sharp-1/Sat0)
// ==========================================================
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness
{0x002A, 0x01D4},
{0x0F12, 0x0000},		//REG_TC_UserSaturation
{0x0F12, 0xFFF6},		//REG_TC_UserSharpBlur
};

s5k5ccff_short_t s5k5ccff_scene_landscape[] = 
{
// ==========================================================
// 	CAMERA_SCENE_LANDSCAPE (Auto/Matrix/Br0/Auto/Sharp+1/Sat+1)
// ==========================================================
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness
{0x002A, 0x01D4},
{0x0F12, 0x001E},		//REG_TC_UserSaturation
{0x0F12, 0x000A},		//REG_TC_UserSharpBlur
};

s5k5ccff_short_t s5k5ccff_scene_sports[] = 
{
// ==========================================================
// 	CAMERA_SCENE_SPORTS (Sport/Center/Br0/Auto/Sharp0/Sat0)
// ==========================================================
{0xFCFC, 0xD000},
{0x0028, 0x7000},


{0x002A, 0x0504},
{0x0F12, 0x3415},		//lt_uMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0508},
{0x0F12, 0x3415},		//lt_uMaxExp2		3415h = 13333d =  33.3325ms
{0x002A, 0x050C},
{0x0F12, 0x3415},		//lt_uMaxExp3		3415h = 13333d =  33.3325ms
{0x002A, 0x0510},
{0x0F12, 0x3415},		//lt_uMaxExp4		3415h = 13333d =  33.3325ms

{0x002A, 0x0514},
{0x0F12, 0x3415},		//lt_uCapMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0518},
{0x0F12, 0x3415},		//lt_uCapMaxExp2		3415h = 13333d =  33.3325ms
{0x002A, 0x051C},
{0x0F12, 0x3415},		//lt_uCapMaxExp3		3415h = 13333d =  33.3325ms
{0x002A, 0x0520},
{0x0F12, 0x3415},		//lt_uCapMaxExp4		3415h = 13333d =  33.3325ms

};

s5k5ccff_short_t s5k5ccff_scene_party[] = 
{
// ==========================================================
// 	CAMERA_SCENE_PARTYINDOOR (ISO200/Center/Br0/Auto/Sharp0/Sat+1)
// ==========================================================

{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness
{0x002A, 0x01D4},
{0x0F12, 0x001E},		//REG_TC_UserSaturation
{0x0F12, 0x0000},		//REG_TC_UserSharpBlur

//ISO 200


{0x002A, 0x04A4},
{0x0F12, 0x065F},		//REG_TC_DBG_AutoAlgEnBits		Auto Flicker Off
{0x002A, 0x048C},
{0x0F12, 0x0000},		//REG_SF_USER_FlickerQuant		0:No AFC, 1:50Hz, 2:60Hz
{0x0F12, 0x0001},		//REG_SF_USER_FlickerQuantChanged

{0x002A, 0x0504},
{0x0F12, 0xC350},		//lt_uMaxExp1		C350h = 50000d = 125.0000ms
{0x002A, 0x0508},
{0x0F12, 0xC350},		//lt_uMaxExp2		C350h = 50000d = 125.0000ms
{0x002A, 0x050C},
{0x0F12, 0xC350},		//lt_uMaxExp3		C350h = 50000d = 125.0000ms
{0x002A, 0x0510},
{0x0F12, 0xC350},		//lt_uMaxExp4		C350h = 50000d = 125.0000ms

{0x002A, 0x0514},
{0x0F12, 0xC350},		//lt_uCapMaxExp1		C350h = 50000d = 125.0000ms
{0x002A, 0x0518},
{0x0F12, 0xC350},		//lt_uCapMaxExp2		C350h = 50000d = 125.0000ms
{0x002A, 0x051C},
{0x0F12, 0xC350},		//lt_uCapMaxExp3		C350h = 50000d = 125.0000ms
{0x002A, 0x0520},
{0x0F12, 0xC350},		//lt_uCapMaxExp4		C350h = 50000d = 125.0000ms

{0x002A, 0x05EA},
{0x0F12, 0x0100},		//lt_bUseSecISODgain

// ISO Gain
{0x002A, 0x0486},
{0x0F12, 0x0003},		//REG_SF_USER_IsoType		0:OFF 3:ISO
{0x0F12, 0x0400},		//REG_SF_USER_IsoVal
{0x0F12, 0x0001},		//REG_SF_USER_IsoChanged

// AFIT by Normalized Brightness Tuning parameter
{0x002A, 0x3302},
{0x0F12, 0x0001},		//AFIT by Normalized Brightness Tunning Parameter

//Preview
{0x002A, 0x0208},
{0x0F12, 0x0000},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreviewChanged 
};

s5k5ccff_short_t s5k5ccff_scene_beach[] = 
{
// ==========================================================
// 	CAMERA_SCENE_BEACHSNOW (ISO50/Center/Br+1/Auto/Sharp0/Sat+1)
// ==========================================================

{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0014},		//REG_TC_UserBrightness
{0x002A, 0x01D4},
{0x0F12, 0x001E},		//REG_TC_UserSaturation
{0x0F12, 0x0000},		//REG_TC_UserSharpBlur

//ISO 50


{0x002A, 0x04A4},
{0x0F12, 0x065F},		//REG_TC_DBG_AutoAlgEnBits		Auto Flicker Off
{0x002A, 0x048C},
{0x0F12, 0x0000},		//REG_SF_USER_FlickerQuant		0:No AFC, 1:50Hz, 2:60Hz
{0x0F12, 0x0001},		//REG_SF_USER_FlickerQuantChanged

{0x002A, 0x0504},
{0x0F12, 0xC350},		//lt_uMaxExp1		C350h = 50000d = 125.0000ms
{0x002A, 0x0508},
{0x0F12, 0xC350},		//lt_uMaxExp2		C350h = 50000d = 125.0000ms
{0x002A, 0x050C},
{0x0F12, 0xC350},		//lt_uMaxExp3		C350h = 50000d = 125.0000ms
{0x002A, 0x0510},
{0x0F12, 0xC350},		//lt_uMaxExp4		C350h = 50000d = 125.0000ms

{0x002A, 0x0514},
{0x0F12, 0xC350},		//lt_uCapMaxExp1		C350h = 50000d = 125.0000ms
{0x002A, 0x0518},
{0x0F12, 0xC350},		//lt_uCapMaxExp2		C350h = 50000d = 125.0000ms
{0x002A, 0x051C},
{0x0F12, 0xC350},		//lt_uCapMaxExp3		C350h = 50000d = 125.0000ms
{0x002A, 0x0520},
{0x0F12, 0xC350},		//lt_uCapMaxExp4		C350h = 50000d = 125.0000ms

{0x002A, 0x05EA},
{0x0F12, 0x0100},		//lt_bUseSecISODgain

// ISO Gain
{0x002A, 0x0486},
{0x0F12, 0x0003},		//REG_SF_USER_IsoType		0:OFF 3:ISO
{0x0F12, 0x0100},		//REG_SF_USER_IsoVal
{0x0F12, 0x0001},		//REG_SF_USER_IsoChanged

// AFIT by Normalized Brightness Tuning parameter
{0x002A, 0x3302},
{0x0F12, 0x0001},		//AFIT by Normalized Brightness Tunning Parameter

//Preview
{0x002A, 0x0208},
{0x0F12, 0x0000},		//REG_TC_GP_ActivePrevConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},		//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},		//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},		//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},		//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreviewChanged 
};

s5k5ccff_short_t s5k5ccff_scene_sunset[] = 
{
// Use MWB Daylight
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x0600},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x0526},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};

s5k5ccff_short_t s5k5ccff_scene_dawn[] = 
{
// Use MWB CWF
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x04C0},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x07F6},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};

s5k5ccff_short_t s5k5ccff_scene_fall[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness
{0x002A, 0x01D4},
{0x0F12, 0x0032},		//REG_TC_UserSaturation
{0x0F12, 0x000A},		//REG_TC_UserSharpBlur
};

s5k5ccff_short_t s5k5ccff_scene_nightshot[] = 
{
// ==========================================================
// 	CAMERA_SCENE_NIGHT (Night/Center/Br0/Auto/Sharp0/Sat0)
// ==========================================================

{0xFCFC, 0xD000},
{0x0028, 0x7000},  
{0x002A, 0x03A4},
{0x0F12, 0x1388},       //REG_2TC_CCFG_usMaxFrTimeMsecMult10			1388h = 500.0ms =  2fps
{0x0F12, 0x1388},       //REG_2TC_CCFG_usMinFrTimeMsecMult10			1388h = 500.0ms =  2fps

{0x002A, 0x01CC},
{0x0F12, 0x0001},       //REG_TC_IPRM_InitParamsUpdated

{0x002A, 0x0504},
{0x0F12, 0x3415},		//lt_uMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0508},
{0x0F12, 0x681F},		//lt_uMaxExp2		681Fh = 26655d =  66.6375ms
{0x002A, 0x050C},
{0x0F12, 0x8227},		//lt_uMaxExp3		8227h = 33319d =  83.2975ms
{0x002A, 0x0510},
{0x0F12, 0x1A80},		//lt_uMaxExp4		00061A80h = 400000d =  1000ms
{0x0F12, 0x0006},

{0x002A, 0x0514},
{0x0F12, 0x3415},		//lt_uCapMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0518},
{0x0F12, 0x681F},		//lt_uCapMaxExp2		681Fh = 26655d =  66.6375ms
{0x002A, 0x051C},
{0x0F12, 0x8227},		//lt_uCapMaxExp3		8227h = 33319d =  83.2975ms
{0x002A, 0x0520},
{0x0F12, 0x1A80},		//lt_uCapMaxExp4		00061A80h = 400000d =  1000ms
{0x0F12, 0x0006},

{0x002A, 0x0524},
{0x0F12, 0x0180},		//lt_uMaxAnGain1		0180h	= 0384d	= x1.5000
{0x0F12, 0x0180},		//lt_uMaxAnGain2		0180h	= 0384d	= x1.5000
{0x0F12, 0x0250},		//lt_uMaxAnGain3		0250h	= 0592d	= x2.3125
{0x0F12, 0x0800},		//lt_uMaxAnGain4		0710h	= 1808d	= x7.0625

{0x0F12, 0x0100},		//lt_uMaxDigGain
{0x0F12, 0x8000},		//lt_uMaxTotGain

{0x0F12, 0x0180},		//lt_uCapMaxAnGain1		0180h	= 0384d	= x1.5000
{0x0F12, 0x0180},		//lt_uCapMaxAnGain2		0180h	= 0384d	= x1.5000
{0x0F12, 0x0250},		//lt_uCapMaxAnGain3		0250h	= 0592d	= x2.3125
{0x0F12, 0x0800},		//lt_uCapMaxAnGain4		0710h	= 1808d	= x7.0625

{0x0F12, 0x0100},		//lt_uCapMaxDigGain
{0x0F12, 0x8000},		//lt_uCapMaxTotGain

{0x002A, 0x08E4},
{0x0F12, 0x0000},	//000C		//AFIT16_demsharpmix1_iHystThLow
{0x0F12, 0x0000},	//000C		//AFIT16_demsharpmix1_iHystThHigh
{0x002A, 0x0940},
{0x0F12, 0x1080},	//084B		//[15:8] AFIT8_RGB2YUV_iYOffset, [7:0] AFIT8_ccm_oscar_iSaturation

{0x002A, 0x0208},
{0x0F12, 0x0002},	//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0002},	//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},	//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreviewChanged
};

s5k5ccff_short_t s5k5ccff_scene_backlight[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x1316},		//ae_WeightTbl_16

{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0f01}, 
{0x0F12, 0x010f}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0f01}, 
{0x0F12, 0x010f}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000},
};

s5k5ccff_short_t s5k5ccff_scene_firework[] = 
{
// ==========================================================
// 	CAMERA_SCENE_FIREWORK (ISO50/Center/Br0/Auto/Sharp0/Sat0)
// ==========================================================

{0xFCFC, 0xD000},
{0x0028, 0x7000},  

{0x002A, 0x03A4},
{0x0F12, 0x2710},   //REG_2TC_CCFG_usMaxFrTimeMsecMult10			2710h = 1000.0ms =  1fps
{0x0F12, 0x2710},   //REG_2TC_CCFG_usMinFrTimeMsecMult10			2710h = 1000.0ms =  1fps

{0x002A, 0x01CC},
{0x0F12, 0x0001},   //REG_TC_IPRM_InitParamsUpdated

{0x002A, 0x0504},
{0x0F12, 0x3415},		//lt_uMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0508},
{0x0F12, 0x681F},		//lt_uMaxExp2		681Fh = 26655d =  66.6375ms
{0x002A, 0x050C},
{0x0F12, 0x8227},		//lt_uMaxExp3		8227h = 33319d =  83.2975ms
{0x002A, 0x0510},
{0x0F12, 0x1A80},		//lt_uMaxExp4		00061A80h = 400000d =  1000ms
{0x0F12, 0x0006},

{0x002A, 0x0514},
{0x0F12, 0x3415},		//lt_uCapMaxExp1		3415h = 13333d =  33.3325ms
{0x002A, 0x0518},
{0x0F12, 0x681F},		//lt_uCapMaxExp2		681Fh = 26655d =  66.6375ms
{0x002A, 0x051C},
{0x0F12, 0x8227},		//lt_uCapMaxExp3		8227h = 33319d =  83.2975ms
{0x002A, 0x0520},
{0x0F12, 0x1A80},		//lt_uCapMaxExp4		00061A80h = 400000d =  1000ms
{0x0F12, 0x0006},

//ISO 50


{0x002A, 0x04A4},
{0x0F12, 0x065F},		//REG_TC_DBG_AutoAlgEnBits		Auto Flicker Off
{0x002A, 0x048C},
{0x0F12, 0x0000},		//REG_SF_USER_FlickerQuant		0:No AFC, 1:50Hz, 2:60Hz
{0x0F12, 0x0001},		//REG_SF_USER_FlickerQuantChanged

{0x002A, 0x05EA},
{0x0F12, 0x0100},		//lt_bUseSecISODgain

// ISO Gain
{0x002A, 0x0486},
{0x0F12, 0x0003},		//REG_SF_USER_IsoType		0:OFF 3:ISO
{0x0F12, 0x0100},		//REG_SF_USER_IsoVal
{0x0F12, 0x0001},		//REG_SF_USER_IsoChanged

// AFIT by Normalized Brightness Tuning parameter
{0x002A, 0x3302},
{0x0F12, 0x0001},		//AFIT by Normalized Brightness Tunning Parameter

//Firework Mode Preview
{0x002A, 0x0208},
{0x0F12, 0x0002},		//REG_TC_GP_ActivePrevConfig
{0x002A, 0x0210},
{0x0F12, 0x0002},		//REG_TC_GP_ActiveCapConfig
{0x002A, 0x020C},
{0x0F12, 0x0001},		//REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x01F4},
{0x0F12, 0x0001},		//REG_TC_GP_NewConfigSync
{0x002A, 0x020A},
{0x0F12, 0x0001},		//REG_TC_GP_PrevConfigChanged
{0x002A, 0x0212},
{0x0F12, 0x0001},		//REG_TC_GP_CapConfigChanged
{0x002A, 0x01E4},
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreview
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreviewChanged 
};

s5k5ccff_short_t s5k5ccff_scene_text[] = 
{
// ==========================================================
// 	CAMERA_SCENE_TEXT (Auto/Center/Br0/Auto/Sharp+2/Sat0)
// ==========================================================
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x01D0},
{0x0F12, 0x0000},		//REG_TC_UserBrightness
{0x002A, 0x01D4},
{0x0F12, 0x0000},		//REG_TC_UserSaturation
{0x0F12, 0x0014},		//REG_TC_UserSharpBlur
};

s5k5ccff_short_t s5k5ccff_scene_candle[] = 
{
// Use MWB Daylight
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x2A62},
{0x0f12, 0x0000},		//Mon_AAIO_bAWB		AWB OFF

{0x002A, 0x0470},
{0x0f12, 0x0600},		//REG_SF_USER_Rgain
{0x0f12, 0x0001},		//REG_SF_USER_RgainChanged
{0x0f12, 0x0400},		//REG_SF_USER_Ggain
{0x0f12, 0x0001},		//REG_SF_USER_GgainChanged
{0x0f12, 0x0526},		//REG_SF_USER_Bgain
{0x0f12, 0x0001},		//REG_SF_USER_BgainChaged
};


//normal==matrix?
s5k5ccff_short_t s5k5ccff_metering_normal[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x1316},		//ae_WeightTbl_16

{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101},
};

s5k5ccff_short_t s5k5ccff_metering_spot[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x1316},		//ae_WeightTbl_16

{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0f01}, 
{0x0F12, 0x010f}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0f01}, 
{0x0F12, 0x010f}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0101}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000}, 
{0x0F12, 0x0000},
};

s5k5ccff_short_t s5k5ccff_metering_center[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},             
{0x002A, 0x1316},		//ae_WeightTbl_16

{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0201},
{0x0F12, 0x0102},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0101},
{0x0F12, 0x0201},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0102},
{0x0F12, 0x0201},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0102},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},    
};


s5k5ccff_short_t s5k5ccff_iso_auto[] = 
{};

s5k5ccff_short_t s5k5ccff_iso_50[] = 
{};

s5k5ccff_short_t s5k5ccff_iso_100[] = 
{};

s5k5ccff_short_t s5k5ccff_iso_200[] = 
{};

s5k5ccff_short_t s5k5ccff_iso_400[] = 
{};


s5k5ccff_short_t s5k5ccff_awb_ae_lock[] = 
{};


s5k5ccff_short_t s5k5ccff_awb_ae_unlock[] = 
{};


s5k5ccff_short_t s5k5ccff_af_off[] = 
{};


s5k5ccff_short_t s5k5ccff_af_normal_on[] =
{}; 



s5k5ccff_short_t s5k5ccff_af_macro_on[] =
{};



s5k5ccff_short_t s5k5ccff_af_do[] =
{};



s5k5ccff_short_t s5k5ccff_contrast_m_2[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D2},
{0x0F12, 0xFF80},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_contrast_m_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D2},
{0x0F12, 0xFFC0},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_contrast_0[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D2},
{0x0F12, 0x0000},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_contrast_p_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D2},
{0x0F12, 0x0040},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_contrast_p_2[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D2},
{0x0F12, 0x0080},		//REG_TC_UserContrast
};


s5k5ccff_short_t s5k5ccff_saturation_m_2[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D4},
{0x0F12, 0xFF80},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_saturation_m_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D4},
{0x0F12, 0xFFC0},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_saturation_0[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D4},
{0x0F12, 0x0000},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_saturation_p_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D4},
{0x0F12, 0x0040},		//REG_TC_UserContrast   
};

s5k5ccff_short_t s5k5ccff_saturation_p_2[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D4},
{0x0F12, 0x0080},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_sharpness_m_2[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D6},
{0x0F12, 0xFFC0},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_sharpness_m_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D6},
{0x0F12, 0xFFE0},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_sharpness_0[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D6},
{0x0F12, 0x0000},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_sharpness_p_1[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D6},
{0x0F12, 0x0020},		//REG_TC_UserContrast
};

s5k5ccff_short_t s5k5ccff_sharpness_p_2[] = 
{
{0xFCFC, 0xD000}, 
{0x0028, 0x7000}, 
{0x002A, 0x01D6},
{0x0F12, 0x0040},		//REG_TC_UserContrast
};


s5k5ccff_short_t s5k5ccff_dtp_on[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0xD000},
{0x002A, 0xB054},
{0x0F12, 0x0001},
};


s5k5ccff_short_t s5k5ccff_dtp_off[] = 
{
{0xFCFC, 0xD000},
{0x0028, 0xD000},
{0x002A, 0xB054},
{0x0F12, 0x0000},
};


#endif
