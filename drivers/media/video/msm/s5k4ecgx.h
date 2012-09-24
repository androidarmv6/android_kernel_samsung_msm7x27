
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

#define PCAM_ENABLE_DEBUG // ON/OFF

#ifdef PCAM_ENABLE_DEBUG
#define PCAM_DEBUG(fmt, arg...)  \
                do{\
                printk("[S5K4ECGX] " fmt,##arg);}\
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
#define PCAM_SNAPSHOT_SIZE_CONTROL		17
#define PCAM_SET_CAPTURE_MODE 18
#define PCAM_AUTO_CONTRAST_CONTROL 20
#define PCAM_JPEG_QUALITY_CONTROL 21
#define PCAM_ZOOM_CONTROL 22
#define PCAM_CAM_MODE_CONTROL 23
#define PCAM_PREVIEW_SIZE_CONTROL		24
#define PCAM_SENSOR_RESET		        27

#define PCAM_CAM_MODE_CAMERA 0
#define PCAM_CAM_MODE_CAMCORDER 1

#define PCAM_JPEG_QUALITY_SUPERFINE 0
#define PCAM_JPEG_QUALITY_FINE 1
#define PCAM_JPEG_QUALITY_NORMAL 2

#define PCAM_AUTO_CONTRAST_ON 0
#define PCAM_AUTO_CONTRAST_OFF 1

/////////BENI /////////
#define PCAM_FRAME_AUTO			0
#define PCAM_FRAME_FIX_15		15
#define PCAM_FRAME_FIX_20		20
#define PCAM_FRAME_FIX_24		24
#define PCAM_FRAME_FIX_25		25
#define PCAM_FRAME_FIX_30		30
///////////////////////


#define PCAM_EFFECT_NORMAL		0
#define PCAM_EFFECT_NEGATIVE		1
#define PCAM_EFFECT_MONO		2
#define PCAM_EFFECT_SEPIA		3	

#define PCAM_WB_AUTO                    0
#define PCAM_WB_DAYLIGHT                1
#define PCAM_WB_CLOUDY                  2
#define PCAM_WB_FLUORESCENT             3
#define PCAM_WB_INCANDESCENT            4

#define PCAM_BR_STEP_P_4                8
#define PCAM_BR_STEP_P_3                7
#define PCAM_BR_STEP_P_2                6
#define PCAM_BR_STEP_P_1                5
#define PCAM_BR_STEP_0                  4
#define PCAM_BR_STEP_M_1                3
#define PCAM_BR_STEP_M_2                2
#define PCAM_BR_STEP_M_3                1
#define PCAM_BR_STEP_M_4                0

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
#define PCAM_AF_CHECK_2nd_STATUS	6
#define PCAM_AF_CHECK_AE_STATUS	9
#define PCAM_AF_POWEROFF 	10

#define PCAM_AF_PROGRESS                1
#define PCAM_AF_SUCCESS                 2
#define PCAM_AF_LOWCONF                 3 //Fail
#define PCAM_AF_CANCELED                4
#define PCAM_AF_TIMEOUT                 5
#define PCAM_AE_STABLE               6
#define PCAM_AE_UNSTABLE                 7

#define PCAM_AWB_AE_LOCK		0
#define PCAM_AWB_AE_UNLOCK		1

#define PCAM_CPU_CONSERVATIVE		0
#define PCAM_CPU_ONDEMAND		1
#define PCAM_CPU_PERFORMANCE		2

#define PCAM_DTP_OFF			0
#define PCAM_DTP_ON			1

#define PCAM_ZOOM_STEP_0	0
#define PCAM_ZOOM_STEP_1	1
#define PCAM_ZOOM_STEP_2	2
#define PCAM_ZOOM_STEP_3	3
#define PCAM_ZOOM_STEP_4	4
#define PCAM_ZOOM_STEP_5	5
#define PCAM_ZOOM_STEP_6	6
#define PCAM_ZOOM_STEP_7	7
#define PCAM_ZOOM_STEP_8	8

#define PCAM_SNAPSHOT_SIZE_2560x1920_5M	0
#define PCAM_SNAPSHOT_SIZE_2048x1536_3M	1
#define PCAM_SNAPSHOT_SIZE_1600x1200_2M	2
#define PCAM_SNAPSHOT_SIZE_1280x960_1M		3
#define PCAM_SNAPSHOT_SIZE_640x480_VGA		4
#define PCAM_SNAPSHOT_SIZE_320x240_QVGA		5

#define PCAM_PREVIEW_SIZE_720x480_D1	0
#define PCAM_PREVIEW_SIZE_640x480_VGA	1
#define PCAM_PREVIEW_SIZE_320x240_QVGA	2
#define PCAM_PREVIEW_SIZE_176x144_QCIF	3

typedef struct s5k4ecgx_reg {
	unsigned int value;
} s5k4ecgx_short_t;

//you have to know this : p10, p100 is for request delay. 2010-09-01.
s5k4ecgx_short_t s5k4ecgx_init0[] = 
{
//4EC EVT1.1 Setting								//
//revision history									//
//10.15	initial draft								//
//10.16	new TnP fr0m Sun-kyu Kim		//
//10.16 check  EVT1.0 final setting	//
//10.17 fix some bugs.	//
//10.18 BENI Shading//
//10.18 TnP  Sun-kyu Kim some AF code //
//10.18 TnP  Sun-kyu Kim some AF code //
//10.21	AWB boundary , TnP //
                                                                                 
{0xFCFCD000},
{0x00100001},
{0x10300000},
{0x00140001},

{0xFFFF0064},
                                                                      
//*************************************************************************///
//Analog setting																														//
// This register is for FACTORY ONLY. If you change it without prior notific//
//ation. YOU are RESPONSIBLE for the FAILURE that will happen in the future	//
//*************************************************************************///
                                                                      
//Driving current Setting//
{0x0028D000},
{0x002A1082},
{0x0F120155},	//	d0_d4_cd10d0_d4_cd109:0x0155   //
{0x0F120155},	//	d5_d9_cd10d5_d9_cd109:0x0155	//
{0x0F120055},	//	gpio_cd10gpio_cd1:0x0055	//
{0x0F120555},	//	clks_output_cd10clks_output_cd1011:0x0555	//
{0x002A100E},
{0x0F120000},	//	pclk_delay_r	//
                                                                      
{0x002A007A},	//	Analog setting	//
{0x0F120000},
{0x002AE406},
{0x0F120092},
{0x002AE410},
{0x0F123804},
{0x002AE41A},
{0x0F120010}, //101022 ADD adlcptune_total //
{0x002AE420},
{0x0F120003},
{0x0F120060},
{0x002AE42E},
{0x0F120004},
{0x002AF400},
{0x0F125A3C},
{0x0F120023},
{0x0F128080},
{0x0F1203AF},
{0x0F12000A},
{0x0F12AA54},
{0x0F120040},
{0x0F12464E},
{0x0F120240},
{0x0F120240},
{0x0F120040},
{0x0F121000},
{0x0F12555C},
{0x0F12D000},
{0x0F120010},
{0x0F120202},
{0x0F120401},
{0x0F120022},
{0x0F120088},
{0x0F12009F},
{0x0F120000},
{0x0F121800},
{0x0F120088},
{0x0F120000},
{0x0F122428},
{0x0F120000},
{0x0F1203EE},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x002AF552},
{0x0F120708},
{0x0F12080C},
                                                                      
//	For subsampling Size	//
{0x00287000},
{0x002A18BC},
{0x0F120004},	//	#senHal_ContPtrs_senModesDataArr			//
{0x0F1205B6},	//	#senHal_ContPtrs_senModesDataArr_1_   //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_2_   //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_3_   //
{0x0F120001},	//	#senHal_ContPtrs_senModesDataArr_4_   //
{0x0F1205BA},	//	#senHal_ContPtrs_senModesDataArr_5_   //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_6_   //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_7_   //
{0x0F120007},	//	#senHal_ContPtrs_senModesDataArr_8_   //
{0x0F1205BA},	//	#senHal_ContPtrs_senModesDataArr_9_   //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_10_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_11_  //
{0x0F1201F4},	//	#senHal_ContPtrs_senModesDataArr_12_  //
{0x0F12024E},	//	#senHal_ContPtrs_senModesDataArr_13_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_14_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_15_  //
{0x0F1201F4},	//	#senHal_ContPtrs_senModesDataArr_16_  //
{0x0F1205B6},	//	#senHal_ContPtrs_senModesDataArr_17_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_18_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_19_  //
{0x0F1201F4},	//	#senHal_ContPtrs_senModesDataArr_20_  //
{0x0F1205BA},	//	#senHal_ContPtrs_senModesDataArr_21_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_22_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_23_  //
{0x0F1201F4},	//	#senHal_ContPtrs_senModesDataArr_24_  //
{0x0F12024F},	//	#senHal_ContPtrs_senModesDataArr_25_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_26_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_27_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_28_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_29_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_30_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_31_  //
{0x0F120075},	//	#senHal_ContPtrs_senModesDataArr_32_  //
{0x0F1200CF},	//	#senHal_ContPtrs_senModesDataArr_33_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_34_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_35_  //
{0x0F120075},	//	#senHal_ContPtrs_senModesDataArr_36_  //
{0x0F1200D6},	//	#senHal_ContPtrs_senModesDataArr_37_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_38_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_39_  //
{0x0F120004},	//	#senHal_ContPtrs_senModesDataArr_40_  //
{0x0F1201F4},	//	#senHal_ContPtrs_senModesDataArr_41_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_42_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_43_  //
{0x0F1200F0},	//	#senHal_ContPtrs_senModesDataArr_44_  //
{0x0F1201F4},	//	#senHal_ContPtrs_senModesDataArr_45_  //
{0x0F12029E},	//	#senHal_ContPtrs_senModesDataArr_46_  //
{0x0F1205B2},	//	#senHal_ContPtrs_senModesDataArr_47_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_48_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_49_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_50_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_51_  //
{0x0F1201F8},	//	#senHal_ContPtrs_senModesDataArr_52_  //
{0x0F120228},	//	#senHal_ContPtrs_senModesDataArr_53_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_54_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_55_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_56_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_57_  //
{0x0F120208},	//	#senHal_ContPtrs_senModesDataArr_58_  //
{0x0F120238},	//	#senHal_ContPtrs_senModesDataArr_59_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_60_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_61_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_62_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_63_  //
{0x0F120218},	//	#senHal_ContPtrs_senModesDataArr_64_  //
{0x0F120238},	//	#senHal_ContPtrs_senModesDataArr_65_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_66_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_67_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_68_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_69_  //
{0x0F120001},	//	#senHal_ContPtrs_senModesDataArr_70_  //
{0x0F120009},	//	#senHal_ContPtrs_senModesDataArr_71_  //
{0x0F1200DE},	//	#senHal_ContPtrs_senModesDataArr_72_  //
{0x0F1205C0},	//	#senHal_ContPtrs_senModesDataArr_73_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_74_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_75_  //
{0x0F1200DF},	//	#senHal_ContPtrs_senModesDataArr_76_  //
{0x0F1200E4},	//	#senHal_ContPtrs_senModesDataArr_77_  //
{0x0F1201F8},	//	#senHal_ContPtrs_senModesDataArr_78_  //
{0x0F1201FD},	//	#senHal_ContPtrs_senModesDataArr_79_  //
{0x0F1205B6},	//	#senHal_ContPtrs_senModesDataArr_80_  //
{0x0F1205BB},	//	#senHal_ContPtrs_senModesDataArr_81_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_82_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_83_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_84_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_85_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_86_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_87_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_88_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_89_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_90_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_91_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_92_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_93_  //
{0x0F1201F8},	//	#senHal_ContPtrs_senModesDataArr_94_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_95_  //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_96_  //
{0x0F120077},	//	#senHal_ContPtrs_senModesDataArr_97_  //
{0x0F12007E},	//	#senHal_ContPtrs_senModesDataArr_98_  //
{0x0F12024F},	//	#senHal_ContPtrs_senModesDataArr_99_  //
{0x0F12025E},	//	#senHal_ContPtrs_senModesDataArr_100_ //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_101_ //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_102_ //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_103_ //
{0x0F120000},	//	#senHal_ContPtrs_senModesDataArr_104_ //
                                                                      
// For Capture	//
{0x0F120004},	//	#senHal_ContPtrs_senAvgModesDataArr				//
{0x0F1209D1},	//	#senHal_ContPtrs_senAvgModesDataArr_1_  	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_2_  	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_3_  	//
{0x0F120001},	//	#senHal_ContPtrs_senAvgModesDataArr_4_  	//
{0x0F1209D5},	//	#senHal_ContPtrs_senAvgModesDataArr_5_  	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_6_  	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_7_  	//
{0x0F120008},	//	#senHal_ContPtrs_senAvgModesDataArr_8_  	//
{0x0F1209D5},	//	#senHal_ContPtrs_senAvgModesDataArr_9_  	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_10_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_11_ 	//
{0x0F1202AA},	//	#senHal_ContPtrs_senAvgModesDataArr_12_ 	//
{0x0F120326},	//	#senHal_ContPtrs_senAvgModesDataArr_13_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_14_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_15_ 	//
{0x0F1202AA},	//	#senHal_ContPtrs_senAvgModesDataArr_16_ 	//
{0x0F1209D1},	//	#senHal_ContPtrs_senAvgModesDataArr_17_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_18_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_19_ 	//
{0x0F1202AA},	//	#senHal_ContPtrs_senAvgModesDataArr_20_ 	//
{0x0F1209D5},	//	#senHal_ContPtrs_senAvgModesDataArr_21_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_22_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_23_ 	//
{0x0F1202AA},	//	#senHal_ContPtrs_senAvgModesDataArr_24_ 	//
{0x0F120327},	//	#senHal_ContPtrs_senAvgModesDataArr_25_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_26_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_27_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_28_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_29_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_30_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_31_ 	//
{0x0F120008},	//	#senHal_ContPtrs_senAvgModesDataArr_32_ 	//
{0x0F120084},	//	#senHal_ContPtrs_senAvgModesDataArr_33_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_34_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_35_ 	//
{0x0F120008},	//	#senHal_ContPtrs_senAvgModesDataArr_36_ 	//
{0x0F12008D},	//	#senHal_ContPtrs_senAvgModesDataArr_37_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_38_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_39_ 	//
{0x0F120008},	//	#senHal_ContPtrs_senAvgModesDataArr_40_ 	//
{0x0F1202AA},	//	#senHal_ContPtrs_senAvgModesDataArr_41_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_42_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_43_ 	//
{0x0F1200AA},	//	#senHal_ContPtrs_senAvgModesDataArr_44_ 	//
{0x0F1202AA},	//	#senHal_ContPtrs_senAvgModesDataArr_45_ 	//
{0x0F1203AD},	//	#senHal_ContPtrs_senAvgModesDataArr_46_ 	//
{0x0F1209CD},	//	#senHal_ContPtrs_senAvgModesDataArr_47_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_48_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_49_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_50_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_51_ 	//
{0x0F1202AE},	//	#senHal_ContPtrs_senAvgModesDataArr_52_ 	//
{0x0F1202DE},	//	#senHal_ContPtrs_senAvgModesDataArr_53_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_54_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_55_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_56_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_57_ 	//
{0x0F1202BE},	//	#senHal_ContPtrs_senAvgModesDataArr_58_ 	//
{0x0F1202EE},	//	#senHal_ContPtrs_senAvgModesDataArr_59_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_60_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_61_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_62_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_63_ 	//
{0x0F1202CE},	//	#senHal_ContPtrs_senAvgModesDataArr_64_ 	//
{0x0F1202EE},	//	#senHal_ContPtrs_senAvgModesDataArr_65_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_66_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_67_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_68_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_69_ 	//
{0x0F120001},	//	#senHal_ContPtrs_senAvgModesDataArr_70_ 	//
{0x0F120009},	//	#senHal_ContPtrs_senAvgModesDataArr_71_ 	//
{0x0F120095},	//	#senHal_ContPtrs_senAvgModesDataArr_72_ 	//
{0x0F1209DB},	//	#senHal_ContPtrs_senAvgModesDataArr_73_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_74_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_75_ 	//
{0x0F120096},	//	#senHal_ContPtrs_senAvgModesDataArr_76_ 	//
{0x0F12009B},	//	#senHal_ContPtrs_senAvgModesDataArr_77_ 	//
{0x0F1202AE},	//	#senHal_ContPtrs_senAvgModesDataArr_78_ 	//
{0x0F1202B3},	//	#senHal_ContPtrs_senAvgModesDataArr_79_ 	//
{0x0F1209D1},	//	#senHal_ContPtrs_senAvgModesDataArr_80_ 	//
{0x0F1209D6},	//	#senHal_ContPtrs_senAvgModesDataArr_81_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_82_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_83_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_84_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_85_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_86_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_87_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_88_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_89_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_90_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_91_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_92_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_93_ 	//
{0x0F1202AE},	//	#senHal_ContPtrs_senAvgModesDataArr_94_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_95_ 	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_96_ 	//
{0x0F120009},	//	#senHal_ContPtrs_senAvgModesDataArr_97_ 	//
{0x0F120010},	//	#senHal_ContPtrs_senAvgModesDataArr_98_ 	//
{0x0F120327},	//	#senHal_ContPtrs_senAvgModesDataArr_99_ 	//
{0x0F120336},	//	#senHal_ContPtrs_senAvgModesDataArr_100_	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_101_	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_102_	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_103_	//
{0x0F120000},	//	#senHal_ContPtrs_senAvgModesDataArr_104_	//
                                                                      
//WRITE#senHal_TuneStr_AngTuneData1_0_F400		//
//WRITE#senHal_TuneStr_AngTuneData1_1_7C53	 register at Full Size	//
{0x002A1AF8},
{0x0F125A3C},	//	#senHal_TuneStr_AngTuneData1_2_ register at subsampling	//
                                                                      
{0x002A1896},
{0x0F120002},	//	#senHal_SamplingType 0002 03EE: PLA setting	//
{0x0F120000},	//	#senHal_SamplingMode	0 : 2 PLA // 1 : 4PLA	//
{0x0F120003},	//	#senHal_PLAOption	 [0] VPLA enable , [1] HPLA enable	//
                                                                      
{0x002A189E},
{0x0F120FB0},	//	#senHal_ExpMinPixels	//
                                                                      
{0x002A18AC},
{0x0F120060},	//	#senHal_uAddColsBin		//
{0x0F120060},	//	#senHal_uAddColsNoBin	//
{0x0F1205C0},	//	#senHal_uMinColsBin  	//
{0x0F1205C0},	//	#senHal_uMinColsNoBin	//
                                                                      
{0x002A1AEA},
{0x0F128080},	//	#senHal_SubF404Tune  //
{0x0F120080},	//	#senHal_FullF404Tune	//
{0x002A1AE0},
{0x0F120000},	//	#senHal_bSenAAC	//
                                                                      
{0x002A1A72},
{0x0F120000},	//	#senHal_bSRX	SRX off	//
{0x002A18A2},
{0x0F120004},	//	#senHal_NExpLinesCheckFine	extend Forbidden area line	//
{0x002A1A6A},
{0x0F12009A},	//	#senHal_usForbiddenRightOfs	extend right Forbidden area line	//
{0x002A385E},
{0x0F12024C},	//	#Mon_Sen_uExpPixelsOfs	//
                                                                      
{0x002A0EE6},
{0x0F120000},	//	#setot_bUseDigitalHbin	//
{0x002A1B2A},
{0x0F120300},	//	#senHal_TuneStr2_usAngTuneGainTh	2   70001B2A	//
{0x0F1200D6},	//	#senHal_TuneStr2_AngTuneF4CA_0_ 	2   70001B2C	//
{0x0F12008D},	//	#senHal_TuneStr2_AngTuneF4CA_1_ 	2   70001B2E	//
{0x0F1200CF},	//	#senHal_TuneStr2_AngTuneF4C2_0_ 	2   70001B30	//
{0x0F120084},	//	#senHal_TuneStr2_AngTuneF4C2_1_ 	2   70001B32	//
                                                                      
//*************************************************************************///
//OTP setting																																//
//*************************************************************************///
{0x002A0722},
{0x0F120100},	//	#skl_OTP_usWaitTime This reg should be in fornt of D0001000	//
{0x002A0726},	
{0x0F120000},	//	#skl_bUseOTPfunc	OTP shading is used,this reg should be 1	//
{0x002A08D6},	
{0x0F120000},	//	#ash_bUseOTPData	OTP shading is used, this reg should be 1	//
{0x002A146E},	
{0x0F120001},	//	#awbb_otp_disable OTP AWB (0: use AWB Cal.)	//
{0x002A08DC},	
{0x0F120000},	//	#ash_bUseGasAlphaOTP	OTP alpha is used, this reg should be 1 //
                                                                      
//*************************************************************************///
//TnP setting																																//
//*************************************************************************///
// Start of Patch data //
{0x00287000},
{0x002A3AF8},		//10.10.21
{0x0F12B570},    // 70003AF8 
{0x0F124B18},    // 70003AFA 
{0x0F12222F},    // 70003AFC 
{0x0F124818},    // 70003AFE 
{0x0F128C80},    // 70003B00 
{0x0F122100},    // 70003B02 
{0x0F12C008},    // 70003B04 
{0x0F126002},    // 70003B06 
{0x0F12000A},    // 70003B08 
{0x0F124916},    // 70003B0A 
{0x0F124816},    // 70003B0C 
{0x0F122401},    // 70003B0E 
{0x0F12F000},    // 70003B10 
{0x0F12F9F6},    // 70003B12 
{0x0F124915},    // 70003B14 
{0x0F124816},    // 70003B16 
{0x0F120022},    // 70003B18 
{0x0F122502},    // 70003B1A 
{0x0F12F000},    // 70003B1C 
{0x0F12F9F0},    // 70003B1E 
{0x0F124814},    // 70003B20 
{0x0F120261},    // 70003B22 
{0x0F128001},    // 70003B24 
{0x0F122100},    // 70003B26 
{0x0F128041},    // 70003B28 
{0x0F124913},    // 70003B2A 
{0x0F124813},    // 70003B2C 
{0x0F126041},    // 70003B2E 
{0x0F124913},    // 70003B30 
{0x0F124814},    // 70003B32 
{0x0F122403},    // 70003B34 
{0x0F12002A},    // 70003B36 
{0x0F12F000},    // 70003B38 
{0x0F12F9E2},    // 70003B3A 
{0x0F12480F},    // 70003B3C 
{0x0F124912},    // 70003B3E 
{0x0F1230C0},    // 70003B40 
{0x0F1263C1},    // 70003B42 
{0x0F12490D},    // 70003B44 
{0x0F124811},    // 70003B46 
{0x0F123980},    // 70003B48 
{0x0F126408},    // 70003B4A 
{0x0F124910},    // 70003B4C 
{0x0F124811},    // 70003B4E 
{0x0F120022},    // 70003B50 
{0x0F12F000},    // 70003B52 
{0x0F12F9D5},    // 70003B54 
{0x0F12BC70},    // 70003B56 
{0x0F12BC08},    // 70003B58 
{0x0F124718},    // 70003B5A 
{0x0F12017B},    // 70003B5C 
{0x0F124EC2},    // 70003B5E 
{0x0F121F6C},    // 70003B60 
{0x0F127000},    // 70003B62 
{0x0F123B99},    // 70003B64 
{0x0F127000},    // 70003B66 
{0x0F12E38B},    // 70003B68 
{0x0F120000},    // 70003B6A 
{0x0F123BD1},    // 70003B6C 
{0x0F127000},    // 70003B6E 
{0x0F12C3B1},    // 70003B70 
{0x0F120000},    // 70003B72 
{0x0F124780},    // 70003B74 
{0x0F127000},    // 70003B76 
{0x0F123C2F},    // 70003B78 
{0x0F127000},    // 70003B7A 
{0x0F120080},    // 70003B7C 
{0x0F127000},    // 70003B7E 
{0x0F123C6B},    // 70003B80 
{0x0F127000},    // 70003B82 
{0x0F12B49D},    // 70003B84 
{0x0F120000},    // 70003B86 
{0x0F123CFD},    // 70003B88 
{0x0F127000},    // 70003B8A 
{0x0F123CCB},    // 70003B8C 
{0x0F127000},    // 70003B8E 
{0x0F123E59},    // 70003B90 
{0x0F127000},    // 70003B92 
{0x0F12053D},    // 70003B94 
{0x0F120000},    // 70003B96 
{0x0F126808},    // 70003B98 
{0x0F120400},    // 70003B9A 
{0x0F120C00},    // 70003B9C 
{0x0F126849},    // 70003B9E 
{0x0F120409},    // 70003BA0 
{0x0F120C09},    // 70003BA2 
{0x0F124AC1},    // 70003BA4 
{0x0F128992},    // 70003BA6 
{0x0F122A00},    // 70003BA8 
{0x0F12D00D},    // 70003BAA 
{0x0F122300},    // 70003BAC 
{0x0F121A89},    // 70003BAE 
{0x0F12D400},    // 70003BB0 
{0x0F12000B},    // 70003BB2 
{0x0F120419},    // 70003BB4 
{0x0F120C09},    // 70003BB6 
{0x0F1223FF},    // 70003BB8 
{0x0F1233C1},    // 70003BBA 
{0x0F121810},    // 70003BBC 
{0x0F124298},    // 70003BBE 
{0x0F12D800},    // 70003BC0 
{0x0F120003},    // 70003BC2 
{0x0F120418},    // 70003BC4 
{0x0F120C00},    // 70003BC6 
{0x0F124AB9},    // 70003BC8 
{0x0F128150},    // 70003BCA 
{0x0F128191},    // 70003BCC 
{0x0F124770},    // 70003BCE 
{0x0F12B5F3},    // 70003BD0 
{0x0F120004},    // 70003BD2 
{0x0F12B081},    // 70003BD4 
{0x0F129802},    // 70003BD6 
{0x0F126800},    // 70003BD8 
{0x0F120600},    // 70003BDA 
{0x0F120E00},    // 70003BDC 
{0x0F122201},    // 70003BDE 
{0x0F120015},    // 70003BE0 
{0x0F120021},    // 70003BE2 
{0x0F123910},    // 70003BE4 
{0x0F12408A},    // 70003BE6 
{0x0F1240A5},    // 70003BE8 
{0x0F124FB2},    // 70003BEA 
{0x0F120016},    // 70003BEC 
{0x0F122C10},    // 70003BEE 
{0x0F12DA03},    // 70003BF0 
{0x0F128839},    // 70003BF2 
{0x0F1243A9},    // 70003BF4 
{0x0F128039},    // 70003BF6 
{0x0F12E002},    // 70003BF8 
{0x0F128879},    // 70003BFA 
{0x0F1243B1},    // 70003BFC 
{0x0F128079},    // 70003BFE 
{0x0F12F000},    // 70003C00 
{0x0F12F986},    // 70003C02 
{0x0F122C10},    // 70003C04 
{0x0F12DA03},    // 70003C06 
{0x0F128839},    // 70003C08 
{0x0F124329},    // 70003C0A 
{0x0F128039},    // 70003C0C 
{0x0F12E002},    // 70003C0E 
{0x0F128879},    // 70003C10 
{0x0F124331},    // 70003C12 
{0x0F128079},    // 70003C14 
{0x0F1249A8},    // 70003C16 
{0x0F128809},    // 70003C18 
{0x0F122900},    // 70003C1A 
{0x0F12D102},    // 70003C1C 
{0x0F12F000},    // 70003C1E 
{0x0F12F97F},    // 70003C20 
{0x0F122000},    // 70003C22 
{0x0F129902},    // 70003C24 
{0x0F126008},    // 70003C26 
{0x0F12BCFE},    // 70003C28 
{0x0F12BC08},    // 70003C2A 
{0x0F124718},    // 70003C2C 
{0x0F12B538},    // 70003C2E 
{0x0F129C04},    // 70003C30 
{0x0F120015},    // 70003C32 
{0x0F12002A},    // 70003C34 
{0x0F129400},    // 70003C36 
{0x0F12F000},    // 70003C38 
{0x0F12F97A},    // 70003C3A 
{0x0F124A9F},    // 70003C3C 
{0x0F128811},    // 70003C3E 
{0x0F122900},    // 70003C40 
{0x0F12D00F},    // 70003C42 
{0x0F128820},    // 70003C44 
{0x0F124281},    // 70003C46 
{0x0F12D20C},    // 70003C48 
{0x0F128861},    // 70003C4A 
{0x0F128853},    // 70003C4C 
{0x0F124299},    // 70003C4E 
{0x0F12D200},    // 70003C50 
{0x0F121E40},    // 70003C52 
{0x0F120400},    // 70003C54 
{0x0F120C00},    // 70003C56 
{0x0F128020},    // 70003C58 
{0x0F128851},    // 70003C5A 
{0x0F128061},    // 70003C5C 
{0x0F124368},    // 70003C5E 
{0x0F121840},    // 70003C60 
{0x0F126060},    // 70003C62 
{0x0F12BC38},    // 70003C64 
{0x0F12BC08},    // 70003C66 
{0x0F124718},    // 70003C68 
{0x0F12B5F8},    // 70003C6A 
{0x0F120004},    // 70003C6C 
{0x0F126808},    // 70003C6E 
{0x0F120400},    // 70003C70 
{0x0F120C00},    // 70003C72 
{0x0F122201},    // 70003C74 
{0x0F120015},    // 70003C76 
{0x0F120021},    // 70003C78 
{0x0F123910},    // 70003C7A 
{0x0F12408A},    // 70003C7C 
{0x0F1240A5},    // 70003C7E 
{0x0F124F8C},    // 70003C80 
{0x0F120016},    // 70003C82 
{0x0F122C10},    // 70003C84 
{0x0F12DA03},    // 70003C86 
{0x0F128839},    // 70003C88 
{0x0F1243A9},    // 70003C8A 
{0x0F128039},    // 70003C8C 
{0x0F12E002},    // 70003C8E 
{0x0F128879},    // 70003C90 
{0x0F1243B1},    // 70003C92 
{0x0F128079},    // 70003C94 
{0x0F12F000},    // 70003C96 
{0x0F12F953},    // 70003C98 
{0x0F122C10},    // 70003C9A 
{0x0F12DA03},    // 70003C9C 
{0x0F128838},    // 70003C9E 
{0x0F124328},    // 70003CA0 
{0x0F128038},    // 70003CA2 
{0x0F12E002},    // 70003CA4 
{0x0F128878},    // 70003CA6 
{0x0F124330},    // 70003CA8 
{0x0F128078},    // 70003CAA 
{0x0F124884},    // 70003CAC 
{0x0F128800},    // 70003CAE 
{0x0F120400},    // 70003CB0 
{0x0F12D507},    // 70003CB2 
{0x0F124B83},    // 70003CB4 
{0x0F127819},    // 70003CB6 
{0x0F124A83},    // 70003CB8 
{0x0F127810},    // 70003CBA 
{0x0F127018},    // 70003CBC 
{0x0F127011},    // 70003CBE 
{0x0F124982},    // 70003CC0 
{0x0F128188},    // 70003CC2 
{0x0F12BCF8},    // 70003CC4 
{0x0F12BC08},    // 70003CC6 
{0x0F124718},    // 70003CC8 
{0x0F12B510},    // 70003CCA 
{0x0F124980},    // 70003CCC 
{0x0F124881},    // 70003CCE 
{0x0F1269CB},    // 70003CD0 
{0x0F126840},    // 70003CD2 
{0x0F122200},    // 70003CD4 
{0x0F122B00},    // 70003CD6 
{0x0F12D001},    // 70003CD8 
{0x0F1261CA},    // 70003CDA 
{0x0F126248},    // 70003CDC 
{0x0F126A0B},    // 70003CDE 
{0x0F122B00},    // 70003CE0 
{0x0F12D006},    // 70003CE2 
{0x0F12620A},    // 70003CE4 
{0x0F126288},    // 70003CE6 
{0x0F12487B},    // 70003CE8 
{0x0F128A42},    // 70003CEA 
{0x0F12630A},    // 70003CEC 
{0x0F128A80},    // 70003CEE 
{0x0F126348},    // 70003CF0 
{0x0F12F000},    // 70003CF2 
{0x0F12F92D},    // 70003CF4 
{0x0F12BC10},    // 70003CF6 
{0x0F12BC08},    // 70003CF8 
{0x0F124718},    // 70003CFA 
{0x0F12B5F0},    // 70003CFC 
{0x0F12B08B},    // 70003CFE 
{0x0F1220FF},    // 70003D00 
{0x0F121C40},    // 70003D02 
{0x0F124975},    // 70003D04 
{0x0F1289C9},    // 70003D06 
{0x0F12910A},    // 70003D08 
{0x0F12990A},    // 70003D0A 
{0x0F124D70},    // 70003D0C 
{0x0F124281},    // 70003D0E 
{0x0F12D10D},    // 70003D10 
{0x0F124873},    // 70003D12 
{0x0F126AA9},    // 70003D14 
{0x0F126081},    // 70003D16 
{0x0F126A68},    // 70003D18 
{0x0F120200},    // 70003D1A 
{0x0F12F000},    // 70003D1C 
{0x0F12F920},    // 70003D1E 
{0x0F120400},    // 70003D20 
{0x0F120C00},    // 70003D22 
{0x0F12496F},    // 70003D24 
{0x0F12898A},    // 70003D26 
{0x0F1263AA},    // 70003D28 
{0x0F122200},    // 70003D2A 
{0x0F12818A},    // 70003D2C 
{0x0F124A67},    // 70003D2E 
{0x0F128A11},    // 70003D30 
{0x0F129108},    // 70003D32 
{0x0F122101},    // 70003D34 
{0x0F120349},    // 70003D36 
{0x0F124288},    // 70003D38 
{0x0F12D200},    // 70003D3A 
{0x0F120001},    // 70003D3C 
{0x0F124863},    // 70003D3E 
{0x0F128201},    // 70003D40 
{0x0F124C69},    // 70003D42 
{0x0F128820},    // 70003D44 
{0x0F129007},    // 70003D46 
{0x0F124861},    // 70003D48 
{0x0F126AC0},    // 70003D4A 
{0x0F128020},    // 70003D4C 
{0x0F1288E0},    // 70003D4E 
{0x0F129006},    // 70003D50 
{0x0F122140},    // 70003D52 
{0x0F124308},    // 70003D54 
{0x0F1280E0},    // 70003D56 
{0x0F122000},    // 70003D58 
{0x0F12AD03},    // 70003D5A 
{0x0F120041},    // 70003D5C 
{0x0F12190B},    // 70003D5E 
{0x0F12001E},    // 70003D60 
{0x0F123680},    // 70003D62 
{0x0F128BB2},    // 70003D64 
{0x0F12526A},    // 70003D66 
{0x0F124A54},    // 70003D68 
{0x0F12188A},    // 70003D6A 
{0x0F128897},    // 70003D6C 
{0x0F1283B7},    // 70003D6E 
{0x0F1233A0},    // 70003D70 
{0x0F12891F},    // 70003D72 
{0x0F12466E},    // 70003D74 
{0x0F125277},    // 70003D76 
{0x0F128A11},    // 70003D78 
{0x0F128119},    // 70003D7A 
{0x0F121C40},    // 70003D7C 
{0x0F120400},    // 70003D7E 
{0x0F120C00},    // 70003D80 
{0x0F122806},    // 70003D82 
{0x0F12D3EA},    // 70003D84 
{0x0F12F000},    // 70003D86 
{0x0F12F8F1},    // 70003D88 
{0x0F122000},    // 70003D8A 
{0x0F120041},    // 70003D8C 
{0x0F125A6B},    // 70003D8E 
{0x0F12190A},    // 70003D90 
{0x0F12279C},    // 70003D92 
{0x0F1252BB},    // 70003D94 
{0x0F125A71},    // 70003D96 
{0x0F1232A0},    // 70003D98 
{0x0F128111},    // 70003D9A 
{0x0F121C40},    // 70003D9C 
{0x0F120400},    // 70003D9E 
{0x0F120C00},    // 70003DA0 
{0x0F122806},    // 70003DA2 
{0x0F12D3F2},    // 70003DA4 
{0x0F124949},    // 70003DA6 
{0x0F129808},    // 70003DA8 
{0x0F128208},    // 70003DAA 
{0x0F129807},    // 70003DAC 
{0x0F128020},    // 70003DAE 
{0x0F129806},    // 70003DB0 
{0x0F1280E0},    // 70003DB2 
{0x0F12980A},    // 70003DB4 
{0x0F121FC1},    // 70003DB6 
{0x0F1239FD},    // 70003DB8 
{0x0F12D149},    // 70003DBA 
{0x0F124F47},    // 70003DBC 
{0x0F1289F8},    // 70003DBE 
{0x0F121FC1},    // 70003DC0 
{0x0F1239FF},    // 70003DC2 
{0x0F12D144},    // 70003DC4 
{0x0F124849},    // 70003DC6 
{0x0F124C41},    // 70003DC8 
{0x0F128841},    // 70003DCA 
{0x0F128AE2},    // 70003DCC 
{0x0F124351},    // 70003DCE 
{0x0F122204},    // 70003DD0 
{0x0F125E82},    // 70003DD2 
{0x0F1209C9},    // 70003DD4 
{0x0F121889},    // 70003DD6 
{0x0F120209},    // 70003DD8 
{0x0F120C0D},    // 70003DDA 
{0x0F1288C1},    // 70003DDC 
{0x0F128B22},    // 70003DDE 
{0x0F124351},    // 70003DE0 
{0x0F122208},    // 70003DE2 
{0x0F125E82},    // 70003DE4 
{0x0F1209C9},    // 70003DE6 
{0x0F121888},    // 70003DE8 
{0x0F120200},    // 70003DEA 
{0x0F120C06},    // 70003DEC 
{0x0F124839},    // 70003DEE 
{0x0F126AA1},    // 70003DF0 
{0x0F126840},    // 70003DF2 
{0x0F121809},    // 70003DF4 
{0x0F120200},    // 70003DF6 
{0x0F12F000},    // 70003DF8 
{0x0F12F8B2},    // 70003DFA 
{0x0F120400},    // 70003DFC 
{0x0F120C00},    // 70003DFE 
{0x0F120022},    // 70003E00 
{0x0F123246},    // 70003E02 
{0x0F120011},    // 70003E04 
{0x0F12310A},    // 70003E06 
{0x0F122305},    // 70003E08 
{0x0F12F000},    // 70003E0A 
{0x0F12F8B7},    // 70003E0C 
{0x0F120002},    // 70003E0E 
{0x0F1266F8},    // 70003E10 
{0x0F126B20},    // 70003E12 
{0x0F120029},    // 70003E14 
{0x0F12F000},    // 70003E16 
{0x0F12F8B9},    // 70003E18 
{0x0F12466B},    // 70003E1A 
{0x0F128498},    // 70003E1C 
{0x0F126EFA},    // 70003E1E 
{0x0F126B60},    // 70003E20 
{0x0F120031},    // 70003E22 
{0x0F12F000},    // 70003E24 
{0x0F12F8B2},    // 70003E26 
{0x0F12466B},    // 70003E28 
{0x0F1284D8},    // 70003E2A 
{0x0F120039},    // 70003E2C 
{0x0F129809},    // 70003E2E 
{0x0F123170},    // 70003E30 
{0x0F12F000},    // 70003E32 
{0x0F12F8B3},    // 70003E34 
{0x0F120038},    // 70003E36 
{0x0F123060},    // 70003E38 
{0x0F128A02},    // 70003E3A 
{0x0F124925},    // 70003E3C 
{0x0F123980},    // 70003E3E 
{0x0F12808A},    // 70003E40 
{0x0F128A42},    // 70003E42 
{0x0F1280CA},    // 70003E44 
{0x0F128A80},    // 70003E46 
{0x0F128108},    // 70003E48 
{0x0F124926},    // 70003E4A 
{0x0F126BA0},    // 70003E4C 
{0x0F128188},    // 70003E4E 
{0x0F12B00B},    // 70003E50 
{0x0F12BCF0},    // 70003E52 
{0x0F12BC08},    // 70003E54 
{0x0F124718},    // 70003E56 
{0x0F12B570},    // 70003E58 
{0x0F122400},    // 70003E5A 
{0x0F124D24},    // 70003E5C 
{0x0F124825},    // 70003E5E 
{0x0F128881},    // 70003E60 
{0x0F124825},    // 70003E62 
{0x0F128041},    // 70003E64 
{0x0F122101},    // 70003E66 
{0x0F128001},    // 70003E68 
{0x0F12F000},    // 70003E6A 
{0x0F12F89F},    // 70003E6C 
{0x0F124821},    // 70003E6E 
{0x0F123820},    // 70003E70 
{0x0F128BC0},    // 70003E72 
{0x0F12F000},    // 70003E74 
{0x0F12F8A2},    // 70003E76 
{0x0F124B20},    // 70003E78 
{0x0F12220D},    // 70003E7A 
{0x0F120712},    // 70003E7C 
{0x0F1218A8},    // 70003E7E 
{0x0F128806},    // 70003E80 
{0x0F1200E1},    // 70003E82 
{0x0F1218C9},    // 70003E84 
{0x0F1281CE},    // 70003E86 
{0x0F128846},    // 70003E88 
{0x0F12818E},    // 70003E8A 
{0x0F128886},    // 70003E8C 
{0x0F12824E},    // 70003E8E 
{0x0F1288C0},    // 70003E90 
{0x0F128208},    // 70003E92 
{0x0F123508},    // 70003E94 
{0x0F12042D},    // 70003E96 
{0x0F120C2D},    // 70003E98 
{0x0F121C64},    // 70003E9A 
{0x0F120424},    // 70003E9C 
{0x0F120C24},    // 70003E9E 
{0x0F122C07},    // 70003EA0 
{0x0F12D3EC},    // 70003EA2 
{0x0F12BC70},    // 70003EA4 
{0x0F12BC08},    // 70003EA6 
{0x0F124718},    // 70003EA8 
{0x0F120000},    // 70003EAA 
{0x0F1217D0},    // 70003EAC 
{0x0F127000},    // 70003EAE 
{0x0F125000},    // 70003EB0 
{0x0F12D000},    // 70003EB2 
{0x0F121100},    // 70003EB4 
{0x0F12D000},    // 70003EB6 
{0x0F12171A},    // 70003EB8 
{0x0F127000},    // 70003EBA 
{0x0F124780},    // 70003EBC 
{0x0F127000},    // 70003EBE 
{0x0F122FCA},    // 70003EC0 
{0x0F127000},    // 70003EC2 
{0x0F122FC5},    // 70003EC4 
{0x0F127000},    // 70003EC6 
{0x0F122FC6},    // 70003EC8 
{0x0F127000},    // 70003ECA 
{0x0F122ED8},    // 70003ECC 
{0x0F127000},    // 70003ECE 
{0x0F1217E0},    // 70003ED0 
{0x0F127000},    // 70003ED2 
{0x0F122C78},    // 70003ED4 
{0x0F127000},    // 70003ED6 
{0x0F122AB8},    // 70003ED8 
{0x0F127000},    // 70003EDA 
{0x0F1237E0},    // 70003EDC 
{0x0F127000},    // 70003EDE 
{0x0F12210C},    // 70003EE0 
{0x0F127000},    // 70003EE2 
{0x0F120ED6},    // 70003EE4 
{0x0F127000},    // 70003EE6 
{0x0F121484},    // 70003EE8 
{0x0F127000},    // 70003EEA 
{0x0F122558},    // 70003EEC 
{0x0F127000},    // 70003EEE 
{0x0F12A006},    // 70003EF0 
{0x0F120000},    // 70003EF2 
{0x0F120724},    // 70003EF4 
{0x0F127000},    // 70003EF6 
{0x0F12A000},    // 70003EF8 
{0x0F12D000},    // 70003EFA 
{0x0F122270},    // 70003EFC 
{0x0F127000},    // 70003EFE 
{0x0F124778},    // 70003F00 
{0x0F1246C0},    // 70003F02 
{0x0F12C000},    // 70003F04 
{0x0F12E59F},    // 70003F06 
{0x0F12FF1C},    // 70003F08 
{0x0F12E12F},    // 70003F0A 
{0x0F121789},    // 70003F0C 
{0x0F120001},    // 70003F0E 
{0x0F124778},    // 70003F10 
{0x0F1246C0},    // 70003F12 
{0x0F12C000},    // 70003F14 
{0x0F12E59F},    // 70003F16 
{0x0F12FF1C},    // 70003F18 
{0x0F12E12F},    // 70003F1A 
{0x0F12C3B1},    // 70003F1C 
{0x0F120000},    // 70003F1E 
{0x0F124778},    // 70003F20 
{0x0F1246C0},    // 70003F22 
{0x0F12C000},    // 70003F24 
{0x0F12E59F},    // 70003F26 
{0x0F12FF1C},    // 70003F28 
{0x0F12E12F},    // 70003F2A 
{0x0F12C36D},    // 70003F2C 
{0x0F120000},    // 70003F2E 
{0x0F124778},    // 70003F30 
{0x0F1246C0},    // 70003F32 
{0x0F12C000},    // 70003F34 
{0x0F12E59F},    // 70003F36 
{0x0F12FF1C},    // 70003F38 
{0x0F12E12F},    // 70003F3A 
{0x0F12F6D7},    // 70003F3C 
{0x0F120000},    // 70003F3E 
{0x0F124778},    // 70003F40 
{0x0F1246C0},    // 70003F42 
{0x0F12C000},    // 70003F44 
{0x0F12E59F},    // 70003F46 
{0x0F12FF1C},    // 70003F48 
{0x0F12E12F},    // 70003F4A 
{0x0F12B49D},    // 70003F4C 
{0x0F120000},    // 70003F4E 
{0x0F124778},    // 70003F50 
{0x0F1246C0},    // 70003F52 
{0x0F12C000},    // 70003F54 
{0x0F12E59F},    // 70003F56 
{0x0F12FF1C},    // 70003F58 
{0x0F12E12F},    // 70003F5A 
{0x0F12448D},    // 70003F5C 
{0x0F120000},    // 70003F5E 
{0x0F124778},    // 70003F60 
{0x0F1246C0},    // 70003F62 
{0x0F12F004},    // 70003F64 
{0x0F12E51F},    // 70003F66 
{0x0F1229EC},    // 70003F68 
{0x0F120001},    // 70003F6A 
{0x0F124778},    // 70003F6C 
{0x0F1246C0},    // 70003F6E 
{0x0F12C000},    // 70003F70 
{0x0F12E59F},    // 70003F72 
{0x0F12FF1C},    // 70003F74 
{0x0F12E12F},    // 70003F76 
{0x0F12EE03},    // 70003F78 
{0x0F120000},    // 70003F7A 
{0x0F124778},    // 70003F7C 
{0x0F1246C0},    // 70003F7E 
{0x0F12C000},    // 70003F80 
{0x0F12E59F},    // 70003F82 
{0x0F12FF1C},    // 70003F84 
{0x0F12E12F},    // 70003F86 
{0x0F122EF1},    // 70003F88 
{0x0F120000},    // 70003F8A 
{0x0F124778},    // 70003F8C 
{0x0F1246C0},    // 70003F8E 
{0x0F12C000},    // 70003F90 
{0x0F12E59F},    // 70003F92 
{0x0F12FF1C},    // 70003F94 
{0x0F12E12F},    // 70003F96 
{0x0F122DB7},    // 70003F98 
{0x0F120000},    // 70003F9A 
{0x0F124778},    // 70003F9C 
{0x0F1246C0},    // 70003F9E 
{0x0F12C000},    // 70003FA0 
{0x0F12E59F},    // 70003FA2 
{0x0F12FF1C},    // 70003FA4 
{0x0F12E12F},    // 70003FA6 
{0x0F12EB3D},    // 70003FA8 
{0x0F120000},    // 70003FAA 
{0x0F124778},    // 70003FAC 
{0x0F1246C0},    // 70003FAE 
{0x0F12C000},    // 70003FB0 
{0x0F12E59F},    // 70003FB2 
{0x0F12FF1C},    // 70003FB4 
{0x0F12E12F},    // 70003FB6 
{0x0F12F061},    // 70003FB8 
{0x0F120000},    // 70003FBA 
{0x0F124778},    // 70003FBC 
{0x0F1246C0},    // 70003FBE 
{0x0F12C000},    // 70003FC0 
{0x0F12E59F},    // 70003FC2 
{0x0F12FF1C},    // 70003FC4 
{0x0F12E12F},    // 70003FC6 
{0x0F12F0EF},    // 70003FC8 
{0x0F120000},    // 70003FCA 
// End of Patch Data(Last : 70003F32h)//
// Total Size 1084 (043C)//
// Addr : 3AF8  Size : 1082(43Ah)//
// #define	TNP_USER_MBCV_CONTROL		 If the user want to control MBCV manually	//
// #define TNP_4EC_MBR_TUNE			 MBR ON // OFF	//
// #define TNP_4EC_FORBIDDEN_TUNE		 FORBIDDEN TUNING : fix cintc.//
// #define TNP_AF_FINESEARCH_DRIVEBACK		 Fine search option to search on Driveback mode.//
// #define TNP_FLASH_ALG		 for support Flash alg support.	//
                                                                      
//TNP_Regs_usCintrTh         2   70004780	//
//TNP_Regs_usFixedCintc      2   70004782	//
//TNP_Regs_FlsWeightRIn_0_   2   70004784	//
//TNP_Regs_FlsWeightRIn_1_   2   70004786	//
//TNP_Regs_FlsWeightRIn_2_   2   70004788	//
//TNP_Regs_FlsWeightRIn_3_   2   7000478A	//
//TNP_Regs_FlsWeightRIn_4_   2   7000478C	//
//TNP_Regs_FlsWeightRIn_5_   2   7000478E	//
//TNP_Regs_FlsWeightROut_0_  2   70004790	//
//TNP_Regs_FlsWeightROut_1_  2   70004792	//
//TNP_Regs_FlsWeightROut_2_  2   70004794	//
//TNP_Regs_FlsWeightROut_3_  2   70004796	//
//TNP_Regs_FlsWeightROut_4_  2   70004798	//
//TNP_Regs_FlsWeightROut_5_  2   7000479A	//
                                                                      
{0x0028D000},
{0x002A1000},
{0x0F120001},
                                                                      
//*************************************************************************///
//AF setting																																//
//*************************************************************************///
{0x00287000},
{0x002A01FC},
{0x0F120001},	//	#REG_TC_IPRM_LedGpio	//
//s002A1720//
//s0F120100//	//	#afd_usFlags	//
{0x002A01FE},
{0x0F120003},	//	#REG_TC_IPRM_CM_Init_AfModeType	VCM IIC	//
{0x0F120000},	//	#REG_TC_IPRM_CM_Init_PwmConfig1	//
{0x002A0204},
{0x0F120061},	//	#REG_TC_IPRM_CM_Init_GpioConfig1	AF Enable GPIO 6	//
{0x002A020C},
{0x0F122F0C},	//	#REG_TC_IPRM_CM_Init_Mi2cBits	//
{0x0F120190},	//	#REG_TC_IPRM_CM_Init_Mi2cRateKhz	IIC Speed	//
{0x002A0294},
{0x0F120100},	//	#REG_TC_AF_FstWinStartX   	//
{0x0F1200E3},	//	#REG_TC_AF_FstWinStartY   	//
{0x0F120200},	//	#REG_TC_AF_FstWinSizeX    	//
{0x0F120238},	//	#REG_TC_AF_FstWinSizeY    	//
{0x0F1201C6},	//	#REG_TC_AF_ScndWinStartX  	//
{0x0F120166},	//	#REG_TC_AF_ScndWinStartY  	//
{0x0F120074},	//	#REG_TC_AF_ScndWinSizeX   	//
{0x0F120132},	//	#REG_TC_AF_ScndWinSizeY   	//
{0x0F120001},	//	#REG_TC_AF_WinSizesUpdated	//
                                                                      
{0x002A070E},
{0x0F1200FF},	//	#skl_af_StatOvlpExpFactor	//
{0x002A071E},
{0x0F120001},	//	#skl_af_bAfStatOff	//
{0x002A163C},
{0x0F120000},	//	#af_search_usAeStable	//
{0x002A1648},
{0x0F129002},	//	#af_search_usSingleAfFlags	//
{0x002A1652},
{0x0F120002},	//	#af_search_usFinePeakCount	//
{0x0F120000},	//	#af_search_usFineMaxScale	//
{0x002A15E0},
{0x0F120902},	//	#af_pos_usFineStepNumSize	//
                                                                      
{0x002A164C},
{0x0F120003},	//	#af_search_usMinPeakSamples	//
{0x002A163E},
{0x0F1200E5},	//	#af_search_usPeakThr  Full search  ( C0 75%)	//
{0x0F120098},	//	#af_search_usPeakThrLow	//
{0x002A15D4},
{0x0F120000},	//	#af_pos_usHomePos	//
{0x0F12D000},	//	#af_pos_usLowConfPos	//
{0x002A169A},
{0x0F12FF95},	//	#af_search_usConfCheckOrder_1_	//
{0x002A166A},
{0x0F120280},	//	#af_search_usConfThr_4_	//
{0x002A1676},	
{0x0F1203A0},	//	#af_search_usConfThr_10_	//
{0x0F120320},	//	#af_search_usConfThr_11_	//
{0x002A16BC},	
{0x0F120030},	//	#af_stat_usMinStatVal	//
{0x002A16E0},	
{0x0F120060},	//	#af_scene_usSceneLowNormBrThr	//
{0x002A16D4},	
{0x0F120010},	//	#af_stat_usBpfThresh	//
{0x002A1656},	
{0x0F120000},	//	#af_search_usCapturePolicy	//
{0x002A15E6},
{0x0F12003C},	//	#af_pos_usCaptureFixedPos	//
                                                                      
{0x0F120018},	//	#af_pos_usTableLastInd//
{0x0F12002A},	//	#af_pos_usTable_0_    //
{0x0F120030},	//	#af_pos_usTable_1_    //
{0x0F120036},	//	#af_pos_usTable_2_    //
{0x0F12003C},	//	#af_pos_usTable_3_    //
{0x0F120042},	//	#af_pos_usTable_4_    //
{0x0F120048},	//	#af_pos_usTable_5_    //
{0x0F12004E},	//	#af_pos_usTable_6_    //
{0x0F120054},	//	#af_pos_usTable_7_    //
{0x0F12005A},	//	#af_pos_usTable_8_    //
{0x0F120060},	//	#af_pos_usTable_9_    //
{0x0F120066},	//	#af_pos_usTable_10_   //
{0x0F12006C},	//	#af_pos_usTable_11_   //
{0x0F120072},	//	#af_pos_usTable_12_   //
{0x0F120078},	//	#af_pos_usTable_13_   //
{0x0F12007E},	//	#af_pos_usTable_14_   //
{0x0F120084},	//	#af_pos_usTable_15_   //
{0x0F12008A},	//	#af_pos_usTable_16_   //
{0x0F120090},	//	#af_pos_usTable_17_   //
{0x0F120096},	//	#af_pos_usTable_18_   //
{0x0F12009C},	//	#af_pos_usTable_19_   //
{0x0F1200A2},	//	#af_pos_usTable_20_   //
{0x0F1200A8},	//	#af_pos_usTable_21_   //
{0x0F1200AE},	//	#af_pos_usTable_22_   //
{0x0F1200B4},	//	#af_pos_usTable_23_   //
{0x0F1200BA},	//	#af_pos_usTable_24_   //
                                                                      
{0x002A1722},
{0x0F128000},	//	#afd_usParam_0_ 	//
{0x0F120006},	//	#afd_usParam_1_ 	//
{0x0F123FF0},	//	#afd_usParam_2_ 	//
{0x0F1203E8},	//	#afd_usParam_3_ 	//
{0x0F120000},	//	#afd_usParam_4_ 	//
{0x0F120020},	//	#afd_usParam_5_ 	//
{0x0F120010},	//	#afd_usParam_6_ 	//
{0x0F120010},	//	#afd_usParam_7_ 	//
{0x0F120040},	//	#afd_usParam_8_ 	//
{0x0F120080},	//	#afd_usParam_9_ 	//
{0x0F1200C0},	//	#afd_usParam_10_	//
{0x0F1200E0},	//	#afd_usParam_11_	//
                                                                      
{0x002A028C},
{0x0F120003},	//	#REG_TC_AF_AfCmd	//
                                                                      
//*************************************************************************///
//GAS TABLE setting																													//
//*************************************************************************///
{0x002A08B4},
{0x0F120001},	//	#wbt_bUseOutdoorASH	//
                                                                      
//	TVAR_ash_AwbAshCord	Refer Mon_AWB_RotGain	//
{0x002A08BC},
{0x0F1200C0},	//	#TVAR_ash_AwbAshCord_0_//2300K	//
{0x0F1200DF},	//	#TVAR_ash_AwbAshCord_1_//2750K	//
{0x0F120100},	//	#TVAR_ash_AwbAshCord_2_//3300K	//
{0x0F120125},	//	#TVAR_ash_AwbAshCord_3_//4150K	//
{0x0F12015F},	//	#TVAR_ash_AwbAshCord_4_//5250K	//
{0x0F12017C},	//	#TVAR_ash_AwbAshCord_5_//6400K	//
{0x0F120194},	//	#TVAR_ash_AwbAshCord_6_//7500K	//
                                                                      
//	GAS Alpha table	//
{0x002A08F6},
{0x0F124000},	//	#TVAR_ash_GASAlpha//R//2300K				//
{0x0F124000},	//	#TVAR_ash_GASAlpha_0__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_0__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_0__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASAlpha_1__0_//R//2750K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_1__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_1__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_1__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASAlpha_2__0_//R//3300K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_2__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_2__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_2__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASAlpha_3__0_//R//4150K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_3__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_3__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_3__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASAlpha_4__0_//R//5250K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_4__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_4__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_4__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASAlpha_5__0_//R//6400K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_5__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_5__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_5__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__0_//R//7500K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__3_//B         //
                                                                      
{0x0F124000},	//	#TVAR_ash_GASOutdoorAlpha_0_   //R//Outdoor	//
{0x0F124000},	//	#TVAR_ash_GASOutdoorAlpha_1_   //GR        	//
{0x0F124000},	//	#TVAR_ash_GASOutdoorAlpha_2_   //GB        	//
{0x0F124000},	//	#TVAR_ash_GASOutdoorAlpha_3_   //B         	//
                                                                      
{0x002A08F4},
{0x0F120001}, //	#ash_bUseGasAlpha	//
                                                                      
//	GAS High table	 If OTP is used, GAS Setting Should be deleted.	//
//BENI 1.1 module 101018//
{0x002A0D26},
{0x0F120F00},
{0x0F120000},
{0x0F120F0F},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F120000},
{0x0F120F00},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F12000F},
{0x0F12000F},
{0x0F120F00},
{0x0F120000},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F12000F},
{0x0F12000F},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F120F0F},
{0x0F120F0F},
{0x0F120F00},
{0x0F12000F},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F12000F},
{0x0F12000F},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
                                                                      
{0x0F1288D4},
{0x0F12E524},
{0x0F12063A},
{0x0F120CD4},
{0x0F12FC33},
{0x0F12FC2B},
{0x0F12CD44},
{0x0F120517},
{0x0F120D0F},
{0x0F12EA59},
{0x0F12FCE5},
{0x0F12141D},
{0x0F12241A},
{0x0F12FC1F},
{0x0F12DEAA},
{0x0F1231D8},
{0x0F1206DB},
{0x0F12CFAB},
{0x0F12F681},
{0x0F12069F},
{0x0F12241C},
{0x0F12CAB6},
{0x0F12F4B9},
{0x0F12362F},
{0x0F12F6AA},
{0x0F12F13E},
{0x0F1202F2},
{0x0F120446},
{0x0F1203DC},
{0x0F12FFA7},
{0x0F1214EB},
{0x0F120E28},
{0x0F12DCDE},
{0x0F122621},
{0x0F120753},
{0x0F12D1B1},
{0x0F12A7F9},
{0x0F12DE23},
{0x0F12025E},
{0x0F121E7E},
{0x0F12E467},
{0x0F120E5D},
{0x0F12BD82},
{0x0F1200C3},
{0x0F1214F4},
{0x0F12DFBD},
{0x0F120902},
{0x0F120A15},
{0x0F122B46},
{0x0F12FF31},
{0x0F12D736},
{0x0F1237CC},
{0x0F12057A},
{0x0F12D39C},
{0x0F12F9B4},
{0x0F120358},
{0x0F1229EF},
{0x0F12CAAA},
{0x0F12EE51},
{0x0F1232BA},
{0x0F12F3B6},
{0x0F12F8A4},
{0x0F12FCCD},
{0x0F120595},
{0x0F12FE6F},
{0x0F1212A7},
{0x0F121651},
{0x0F1206F6},
{0x0F12DFF9},
{0x0F1225E2},
{0x0F121252},
{0x0F12BC23},
{0x0F128D85},
{0x0F12E5E8},
{0x0F1201A9},
{0x0F121287},
{0x0F12F8B9},
{0x0F12FD24},
{0x0F12CB5A},
{0x0F12FDA3},
{0x0F121782},
{0x0F12E8C6},
{0x0F12EB07},
{0x0F1228B6},
{0x0F1227F8},
{0x0F1209AB},
{0x0F12C926},
{0x0F123FD7},
{0x0F1213E3},
{0x0F12B883},
{0x0F12F34D},
{0x0F12F651},
{0x0F123A6B},
{0x0F12B2A3},
{0x0F12FAF8},
{0x0F123F69},
{0x0F12FA51},
{0x0F12FB36},
{0x0F12FCEA},
{0x0F121222},
{0x0F12F21D},
{0x0F1208AF},
{0x0F1210B1},
{0x0F120D55},
{0x0F12D334},
{0x0F122F22},
{0x0F12089D},
{0x0F12CBF1},
{0x0F1289C0},
{0x0F12E224},
{0x0F120B3A},
{0x0F12058A},
{0x0F12028D},
{0x0F12F94C},
{0x0F12CC9B},
{0x0F12092D},
{0x0F120527},
{0x0F12F537},
{0x0F12F3AE},
{0x0F1217AD},
{0x0F12289E},
{0x0F12F509},
{0x0F12E895},
{0x0F122734},
{0x0F120AD7},
{0x0F12D2AD},
{0x0F12F550},
{0x0F120BB2},
{0x0F121A84},
{0x0F12D4B0},
{0x0F12F2AD},
{0x0F123000},
{0x0F12F372},
{0x0F12F3A4},
{0x0F12020E},
{0x0F12044F},
{0x0F120232},
{0x0F120558},
{0x0F1217E1},
{0x0F12075D},
{0x0F12E7A3},
{0x0F121AAD},
{0x0F120F19},
{0x0F12CCF6},
                                                                      
//*************************************************************************///
//AE setting																																//
//*************************************************************************///
//	AE WEIGHT	//
{0x002A1492},
{0x0F120000},	//	#ae_WeightTbl_16    	//
{0x0F120101},	//	#ae_WeightTbl_16_1_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_2_ 	//
{0x0F120000},	//	#ae_WeightTbl_16_3_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_4_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_5_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_6_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_7_ 	//
{0x0F120201},	//	#ae_WeightTbl_16_8_ 	//
{0x0F120303},	//	#ae_WeightTbl_16_9_ 	//
{0x0F120303},	//	#ae_WeightTbl_16_10_	//
{0x0F120102},	//	#ae_WeightTbl_16_11_	//
{0x0F120201},	//	#ae_WeightTbl_16_12_	//
{0x0F120403},	//	#ae_WeightTbl_16_13_	//
{0x0F120304},	//	#ae_WeightTbl_16_14_	//
{0x0F120102},	//	#ae_WeightTbl_16_15_	//
{0x0F120201},	//	#ae_WeightTbl_16_16_	//
{0x0F120403},	//	#ae_WeightTbl_16_17_	//
{0x0F120304},	//	#ae_WeightTbl_16_18_	//
{0x0F120102},	//	#ae_WeightTbl_16_19_	//
{0x0F120201},	//	#ae_WeightTbl_16_20_	//
{0x0F120403},	//	#ae_WeightTbl_16_21_	//
{0x0F120304},	//	#ae_WeightTbl_16_22_	//
{0x0F120102},	//	#ae_WeightTbl_16_23_	//
{0x0F120201},	//	#ae_WeightTbl_16_24_	//
{0x0F120303},	//	#ae_WeightTbl_16_25_	//
{0x0F120303},	//	#ae_WeightTbl_16_26_	//
{0x0F120102},	//	#ae_WeightTbl_16_27_	//
{0x0F120201},	//	#ae_WeightTbl_16_28_	//
{0x0F120202},	//	#ae_WeightTbl_16_29_	//
{0x0F120202},	//	#ae_WeightTbl_16_30_	//
{0x0F120102},	//	#ae_WeightTbl_16_31_	//
                                                                      
{0x002A1484},
{0x0F12003C},	//	#TVAR_ae_BrAve //
{0x002A148A},
{0x0F12000F},	//	#ae_StatMode	//
{0x002A058C},
{0x0F123520},
{0x0F120000},	//	#lt_uMaxExp1	//
{0x0F12C350},
{0x0F120000},	//	#lt_uMaxExp2	//
{0x0F123520},
{0x0F120000},	//	#lt_uCapMaxExp1	//
{0x0F12C350},
{0x0F120000},	//	#lt_uCapMaxExp2	//
{0x002A059C},
{0x0F120470},	//	#lt_uMaxAnGain1	//
{0x0F120C00},	//	#lt_uMaxAnGain2	//
{0x0F120100},	//	#lt_uMaxDigGain	//
{0x0F121000},	//	#lt_uMaxTotGain	//
{0x002A0544},
{0x0F120111},	//	#lt_uLimitHigh	//
{0x0F1200EF},	//	#lt_uLimitLow	//
{0x002A0F2A},
{0x0F120001},	//	#AFC_Default60Hz	//
{0x002A0F30},
{0x0F120002},	//	#AFC_D_ConvAccelerPower
{0x002A04D6},
{0x0F120002},	//	#REG_SF_USER_FlickerQuant	 0:off 1:50hz 2:60hz	//
{0x0F120001},	//	#REG_SF_USER_FlickerQuantChanged	//
                                                                      
{0x002A0608},
{0x0F120000},	//	#lt_ExpGain_uSubsamplingmode	//
{0x0F120001},	//	#lt_ExpGain_uNonSubsampling	//
{0x0F120600},	//	#lt_ExpGain_ExpCurveGainMaxStr	//
{0x0F120100},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__uMaxDigGain	//
{0x0F120001},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_0_ 	//
{0x0F120A3C},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_1_ 	//
{0x0F120D04},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_2_ 	//
{0x0F124008},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_3_ 	//
{0x0F127000},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_4_ 	//
{0x0F129C00},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_5_ 	//
{0x0F12AD00},
{0x0F120001},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_6_ 	//
{0x0F12F1D4},
{0x0F120002},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_7_ 	//
{0x0F12DC00},
{0x0F120005},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_8_ 	//
{0x0F12DC00},
{0x0F120005},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_9_ 	//
                                                                      
{0x002A0638},
{0x0F120001},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_0_	//
{0x0F120A3C},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_1_ //
{0x0F120D05},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_2_ //
{0x0F123408},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_3_ //
{0x0F123408},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_4_ //
{0x0F126810},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_5_ //
{0x0F128214},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_6_ //
{0x0F12C350},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_7_ //
{0x0F12C350},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_8_ //
{0x0F12C350},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_9_ //
                                                                      
{0x002A0660},
{0x0F120650},	//	#lt_ExpGain_ExpCurveGainMaxStr_1_	//
{0x0F120100},	//	#lt_ExpGain_ExpCurveGainMaxStr_1__uMaxDigGain	//
                                                                      
{0x002A06B8},
{0x0F12452C},
{0x0F120004},	//	#lt_uMaxLei same brightness between preview and capture.	//
                                                                      
{0x002A05D0},
{0x0F120000},	//	#lt_mbr_Peak_behind	//
                                                                      
//*************************************************************************///
//AWB setting																																//
//*************************************************************************///
//	AWB White Locus	should be	in front of REG_TC_IPRM_InitParamsUpdated	//
//	White Locus	//
{0x002A11F0},
{0x0F12012C},	//	#awbb_IntcR	//
{0x0F120121},	//	#awbb_IntcB	//
                                                                      
// IndoorZone	//
{0x002A101C},
{0x0F1203B2},	//03B8	//	#awbb_IndoorGrZones_m_BGrid_0__m_left		//
{0x0F1203C8},	//03CE	//	#awbb_IndoorGrZones_m_BGrid_0__m_right  //
{0x0F120342},	//0350	//	#awbb_IndoorGrZones_m_BGrid_1__m_left   //
{0x0F1203B8},	//03C4	//	#awbb_IndoorGrZones_m_BGrid_1__m_right  //
{0x0F1202E8},	//02F2	//	#awbb_IndoorGrZones_m_BGrid_2__m_left   //
{0x0F12038A},	//0394	//	#awbb_IndoorGrZones_m_BGrid_2__m_right  //
{0x0F1202B4},	//02C0	//	#awbb_IndoorGrZones_m_BGrid_3__m_left   //
{0x0F120356},	//0364	//	#awbb_IndoorGrZones_m_BGrid_3__m_right  //
{0x0F120292},	//029E	//	#awbb_IndoorGrZones_m_BGrid_4__m_left   //
{0x0F120328},	//0334	//	#awbb_IndoorGrZones_m_BGrid_4__m_right  //
{0x0F120270},	//027C	//	#awbb_IndoorGrZones_m_BGrid_5__m_left   //
{0x0F120306},	//0312	//	#awbb_IndoorGrZones_m_BGrid_5__m_right  //
{0x0F120252},	//025E	//	#awbb_IndoorGrZones_m_BGrid_6__m_left   //
{0x0F1202E6},	//02F2	//	#awbb_IndoorGrZones_m_BGrid_6__m_right  //
{0x0F12023C},	//0246	//	#awbb_IndoorGrZones_m_BGrid_7__m_left   //
{0x0F1202C6},	//02D0	//	#awbb_IndoorGrZones_m_BGrid_7__m_right  //
{0x0F120224},	//0230	//	#awbb_IndoorGrZones_m_BGrid_8__m_left   //
{0x0F1202A4},	//02B0	//	#awbb_IndoorGrZones_m_BGrid_8__m_right  //
{0x0F12020E},	//0218	//	#awbb_IndoorGrZones_m_BGrid_9__m_left   //
{0x0F120292},	//029E	//	#awbb_IndoorGrZones_m_BGrid_9__m_right  //
{0x0F1201FC},	//0208	//	#awbb_IndoorGrZones_m_BGrid_10__m_left  //
{0x0F120284},	//0290	//	#awbb_IndoorGrZones_m_BGrid_10__m_right //
{0x0F1201EC},	//01F8	//	#awbb_IndoorGrZones_m_BGrid_11__m_left  //
{0x0F12027A},	//0284	//	#awbb_IndoorGrZones_m_BGrid_11__m_right //
{0x0F1201DC},	//01E8	//	#awbb_IndoorGrZones_m_BGrid_12__m_left  //
{0x0F12026A},	//0276	//	#awbb_IndoorGrZones_m_BGrid_12__m_right //
{0x0F1201CE},	//01DA	//	#awbb_IndoorGrZones_m_BGrid_13__m_left  //
{0x0F12025E},	//026A	//	#awbb_IndoorGrZones_m_BGrid_13__m_right //
{0x0F1201C2},	//01CE	//	#awbb_IndoorGrZones_m_BGrid_14__m_left  //
{0x0F120250},	//025E	//	#awbb_IndoorGrZones_m_BGrid_14__m_right //
{0x0F1201E0},	//01EC	//	#awbb_IndoorGrZones_m_BGrid_15__m_left  //
{0x0F120222},	//022E	//	#awbb_IndoorGrZones_m_BGrid_15__m_right //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_16__m_left  //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_16__m_right //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_17__m_left  //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_17__m_right //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_18__m_left  //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_18__m_right //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_19__m_left  //
{0x0F120000},	//0000	//	#awbb_IndoorGrZones_m_BGrid_19__m_right //
                                                                      
{0x0F120005},	//	#awbb_IndoorGrZones_m_GridStep			//
{0x002A1070},
{0x0F120010},	//	#awbb_IndoorGrZones_ZInfo_m_GridSz  //
{0x002A1074},
{0x0F120116},	//0126	//	#awbb_IndoorGrZones_m_Boffs         //
                                                                      
//	Outdoor Zone	//
{0x002A1078},
{0x0F12026A},	//026C	//	#awbb_OutdoorGrZones_m_BGrid_0__m_left		//
{0x0F120296},	//029A	//	#awbb_OutdoorGrZones_m_BGrid_0__m_right   //
{0x0F12024E},	//025C	//	#awbb_OutdoorGrZones_m_BGrid_1__m_left    //
{0x0F1202A6},	//02B6	//	#awbb_OutdoorGrZones_m_BGrid_1__m_right   //
{0x0F12023E},	//024E	//	#awbb_OutdoorGrZones_m_BGrid_2__m_left    //
{0x0F1202B0},	//02C0	//	#awbb_OutdoorGrZones_m_BGrid_2__m_right   //
{0x0F120230},	//0240	//	#awbb_OutdoorGrZones_m_BGrid_3__m_left    //
{0x0F1202AE},	//02BE	//	#awbb_OutdoorGrZones_m_BGrid_3__m_right   //
{0x0F12022A},	//023A	//	#awbb_OutdoorGrZones_m_BGrid_4__m_left    //
{0x0F1202A6},	//02B4	//	#awbb_OutdoorGrZones_m_BGrid_4__m_right   //
{0x0F120228},	//023A	//	#awbb_OutdoorGrZones_m_BGrid_5__m_left    //
{0x0F12029C},	//02AA	//	#awbb_OutdoorGrZones_m_BGrid_5__m_right   //
{0x0F12022E},	//0240	//	#awbb_OutdoorGrZones_m_BGrid_6__m_left    //
{0x0F120290},	//029E	//	#awbb_OutdoorGrZones_m_BGrid_6__m_right   //
{0x0F12024C},	//025C	//	#awbb_OutdoorGrZones_m_BGrid_7__m_left    //
{0x0F120282},	//0294	//	#awbb_OutdoorGrZones_m_BGrid_7__m_right   //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_8__m_left    //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_8__m_right   //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_9__m_left    //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_9__m_right   //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_10__m_left   //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_10__m_right  //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_11__m_left   //
{0x0F120000},	//0000	//	#awbb_OutdoorGrZones_m_BGrid_11__m_right  //
                                                                      
{0x0F120004},	//	#awbb_OutdoorGrZones_m_GridStep			//
{0x002A10AC},
{0x0F120008},	//	#awbb_OutdoorGrZones_ZInfo_m_GridSz //
{0x002A10B0},
{0x0F1201D4},	//01E2	//	#awbb_OutdoorGrZones_m_Boffs        //
                                                                      
//	LowBR Zone	//
{0x002A10B4},
{0x0F120350},	//	#awbb_LowBrGrZones											//
{0x0F120422},	//	#awbb_LowBrGrZones_m_BGrid_0__m_right   //
{0x0F1202C4},	//	#awbb_LowBrGrZones_m_BGrid_1__m_left    //
{0x0F120452},	//	#awbb_LowBrGrZones_m_BGrid_1__m_right   //
{0x0F120278},	//	#awbb_LowBrGrZones_m_BGrid_2__m_left    //
{0x0F12041C},	//	#awbb_LowBrGrZones_m_BGrid_2__m_right   //
{0x0F120230},	//	#awbb_LowBrGrZones_m_BGrid_3__m_left    //
{0x0F1203EE},	//	#awbb_LowBrGrZones_m_BGrid_3__m_right   //
{0x0F1201F0},	//	#awbb_LowBrGrZones_m_BGrid_4__m_left    //
{0x0F120392},	//	#awbb_LowBrGrZones_m_BGrid_4__m_right   //
{0x0F1201C0},	//	#awbb_LowBrGrZones_m_BGrid_5__m_left    //
{0x0F120340},	//	#awbb_LowBrGrZones_m_BGrid_5__m_right   //
{0x0F120194},	//	#awbb_LowBrGrZones_m_BGrid_6__m_left    //
{0x0F120302},	//	#awbb_LowBrGrZones_m_BGrid_6__m_right   //
{0x0F12016E},	//	#awbb_LowBrGrZones_m_BGrid_7__m_left    //
{0x0F1202C2},	//	#awbb_LowBrGrZones_m_BGrid_7__m_right   //
{0x0F120148},	//	#awbb_LowBrGrZones_m_BGrid_8__m_left    //
{0x0F120286},	//	#awbb_LowBrGrZones_m_BGrid_8__m_right   //
{0x0F12018A},	//	#awbb_LowBrGrZones_m_BGrid_9__m_left    //
{0x0F120242},	//	#awbb_LowBrGrZones_m_BGrid_9__m_right   //
{0x0F120000},	//	#awbb_LowBrGrZones_m_BGrid_10__m_left   //
{0x0F120000},	//	#awbb_LowBrGrZones_m_BGrid_10__m_right  //
{0x0F120000},	//	#awbb_LowBrGrZones_m_BGrid_11__m_left   //
{0x0F120000},	//	#awbb_LowBrGrZones_m_BGrid_11__m_right  //
                                                                      
{0x0F120006},	//	#awbb_LowBrGrZones_m_GridStep      //
{0x002A10E8},
{0x0F12000A},	//	#awbb_LowBrGrZones_ZInfo_m_GridSz  //
{0x002A10EC},
{0x0F120106},	//	#awbb_LowBrGrZones_m_Boffs         //
                                                                      
//	LowTemp Zone	//
{0x002A10F0},
{0x0F120380},
{0x0F120000},	//	#awbb_CrclLowT_R_c  	//
{0x0F120168},
{0x0F120000},	//	#awbb_CrclLowT_B_c    //
{0x0F122D90},
{0x0F120000},	//	#awbb_CrclLowT_Rad_c  //
                                                                      
//	AWB Convergence Speed	//
{0x002A1464},
{0x0F120008},	//	#awbb_WpFilterMinThr	Stable boundary for AWB //
{0x0F120190},	//	#awbb_WpFilterMaxThr	AWB boost	change of WP is large.//
{0x0F1200A0},	//	#awbb_WpFilterCoef	AWB Speed	//
                                                                      
{0x002A1228},
{0x0F1200C0},	//	#awbb_YThreshHigh Max Ythreshold for AWB	//
{0x002A122C},	
{0x0F120010},	//	#awbb_YThreshLow_Low	Min Y th for AWB in LowBR condition.//
{0x002A122A},	
{0x0F120010},	//	#awbb_YThreshLow_Norm	Min Y	th. for AWB Except LowBR condition//
                                                                      
{0x002A120A},
{0x0F1205D5},	//	#awbb_MvEq_RBthresh  //
{0x002A120E},	
{0x0F120000},	//	#awbb_MovingScale10	Moving equation off	//
                                                                      
{0x0F120771},	//	#awbb_GamutWidthThr1	//
{0x0F1203A4},	//	#awbb_GamutHeightThr1 //
{0x0F120036},	//	#awbb_GamutWidthThr2  //
{0x0F12002A},	//	#awbb_GamutHeightThr2 //
                                                                      
{0x002A1278},
{0x0F12FEF7}, //	#awbb_SCDetectionMap_SEC_StartR_B				//
{0x0F120021}, //	#awbb_SCDetectionMap_SEC_StepR_B        //
{0x0F120E74}, //	#awbb_SCDetectionMap_SEC_SunnyNB        //
{0x0F120E74}, //	#awbb_SCDetectionMap_SEC_StepNB         //
{0x0F12018F}, //	#awbb_SCDetectionMap_SEC_LowTempR_B     //
{0x0F120096}, //	#awbb_SCDetectionMap_SEC_SunnyNBZone    //
{0x0F12000E}, //	#awbb_SCDetectionMap_SEC_LowTempR_BZone //
{0x002A1224},
{0x0F120032},	//	#awbb_LowBr	//
{0x0F12001E},	//	#awbb_LowBr_NBzone	//
{0x002A2BA4},
{0x0F120006},	//	#Mon_AWB_ByPassMode //Low Temp Bypass	//
                                                                      
{0x002A146C},
{0x0F120002},	//	#awbb_GridEnable	//
                                                                      
//	Grid	//
{0x002A1434},
{0x0F1202DA},	//0300	//	#awbb_GridConst_1			//
{0x0F12032A},	//036E	//	#awbb_GridConst_1_1_  //
{0x0F120372},	//03C2	//	#awbb_GridConst_1_2_  //
{0x0F121015},	//1015	//	#awbb_GridConst_2     //
{0x0F12106C},	//106C	//	#awbb_GridConst_2_1_  //
{0x0F1210CA},	//10CA	//	#awbb_GridConst_2_2_  //
{0x0F121142},	//1142	//	#awbb_GridConst_2_3_  //
{0x0F1211BB},	//11BB	//	#awbb_GridConst_2_4_  //
{0x0F12123B},	//123B	//	#awbb_GridConst_2_5_  //
{0x0F1200AB},	//00AB	//	#awbb_GridCoeff_R_1   //
{0x0F1200BF},	//00BF	//	#awbb_GridCoeff_B_1   //
{0x0F1200D2},	//00D2	//	#awbb_GridCoeff_R_2   //
{0x0F120093},	//0093	//	#awbb_GridCoeff_B_2   //
                                                                      
//	Indoor Grid Offset	//
{0x002A13A4},
{0x0F120020},	//FFF0	//0000	//0000	#awbb_GridCorr_R				//
{0x0F120010},	//FFF0	//0000	//0000	#awbb_GridCorr_R_0__1_  //
{0x0F120010},	//FFF0	//0000	//0000	#awbb_GridCorr_R_0__2_  //
{0x0F120000},	//0000	//0000	//0000	#awbb_GridCorr_R_0__3_  //
{0x0F120000},	//0008	//0000	//0008	#awbb_GridCorr_R_0__4_  //
{0x0F120000},	//0030	//0000	//0030	#awbb_GridCorr_R_0__5_  //
{0x0F120020},	//FFF0	//0000	//0000	#awbb_GridCorr_R_1__0_  //
{0x0F120010},	//FFF0	//0000	//0000	#awbb_GridCorr_R_1__1_  //
{0x0F120010},	//FFF0	//0000	//0000	#awbb_GridCorr_R_1__2_  //
{0x0F120010},	//0000	//0000	//0000	#awbb_GridCorr_R_1__3_  //
{0x0F120000},	//0008	//0000	//0008	#awbb_GridCorr_R_1__4_  //
{0x0F120000},	//0030	//0000	//0030	#awbb_GridCorr_R_1__5_  //
{0x0F120020},	//FFF0	//0000	//0000	#awbb_GridCorr_R_2__0_  //
{0x0F120010},	//FFF0	//0000	//0000	#awbb_GridCorr_R_2__1_  //
{0x0F120010},	//FFF0	//0000	//0000	#awbb_GridCorr_R_2__2_  //
{0x0F120010},	//0000	//0000	//0000	#awbb_GridCorr_R_2__3_  //
{0x0F120000},	//0008	//0000	//0008	#awbb_GridCorr_R_2__4_  //
{0x0F120000},	//0030	//0000	//0030	#awbb_GridCorr_R_2__5_  //
{0x0F120000},	//FFE0	//0000	//FFE0	#awbb_GridCorr_B        //
{0x0F120000},	//FFE0	//0000	//FFE0	#awbb_GridCorr_B_0__1_  //
{0x0F120000},	//FFC0	//0000	//FFC0	#awbb_GridCorr_B_0__2_  //
{0x0F120040},	//FFC0	//0000	//FFC0	#awbb_GridCorr_B_0__3_  //
{0x0F120000},	//FFA0	//0000	//FFA0	#awbb_GridCorr_B_0__4_  //
{0x0F120000},	//FE36	//0000	//FE36	#awbb_GridCorr_B_0__5_  //
{0x0F120000},	//FFE0	//0000	//FFE0	#awbb_GridCorr_B_1__0_  //
{0x0F120000},	//FFE0	//0000	//FFE0	#awbb_GridCorr_B_1__1_  //
{0x0F120000},	//FFC0	//0000	//FFC0	#awbb_GridCorr_B_1__2_  //
{0x0F120060},	//FFC0	//0000	//FFC0	#awbb_GridCorr_B_1__3_  //
{0x0F120000},	//FFA0	//0000	//FFA0	#awbb_GridCorr_B_1__4_  //
{0x0F120000},	//FE36	//0000	//FE36	#awbb_GridCorr_B_1__5_  //
{0x0F120000},	//FFE0	//0000	//FFE0	#awbb_GridCorr_B_2__0_  //
{0x0F120000},	//FFE0	//0000	//FFE0	#awbb_GridCorr_B_2__1_  //
{0x0F120000},	//FFC0	//0000	//FFC0	#awbb_GridCorr_B_2__2_  //
{0x0F120040},	//FFC0	//0000	//FFC0	#awbb_GridCorr_B_2__3_  //
{0x0F120000},	//FFA0	//0000	//FFA0	#awbb_GridCorr_B_2__4_  //
{0x0F120000},	//FE36	//0000	//FE36	#awbb_GridCorr_B_2__5_  //
                                                                      
//	Outdoor Grid Offset	//
{0x0F12FFB8},	//0000	//	#awbb_GridCorr_R_Out      	//
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_0__1_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_0__2_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_0__3_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_R_Out_0__4_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_R_Out_0__5_  //
{0x0F12FFB8},	//0000	//	#awbb_GridCorr_R_Out_1__0_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_1__1_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_1__2_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_1__3_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_R_Out_1__4_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_R_Out_1__5_  //
{0x0F12FFB8},	//0000	//	#awbb_GridCorr_R_Out_2__0_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_2__1_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_2__2_  //
{0x0F12FFD8},	//0000	//	#awbb_GridCorr_R_Out_2__3_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_R_Out_2__4_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_R_Out_2__5_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_B_Out        //
{0x0F12FFD0},	//0000	//	#awbb_GridCorr_B_Out_0__1_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_0__2_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_0__3_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_0__4_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_0__5_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_B_Out_1__0_  //
{0x0F12FFD0},	//0000	//	#awbb_GridCorr_B_Out_1__1_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_1__2_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_1__3_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_1__4_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_1__5_  //
{0x0F120000},	//0000	//	#awbb_GridCorr_B_Out_2__0_  //
{0x0F12FFD0},	//0000	//	#awbb_GridCorr_B_Out_2__1_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_2__2_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_2__3_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_2__4_  //
{0x0F12FFC0},	//0000	//	#awbb_GridCorr_B_Out_2__5_  //
                                                                      
{0x002A1208},
{0x0F120020},	//	#awbb_MinNumOfChromaClassifyPatches	//
                                                                      
{0x002A144E},
{0x0F120000},	//	#awbb_RGainOff	//
{0x0F120000},	//	#awbb_BGainOff	//
{0x0F120000},	//	#awbb_GGainOff	//
                                                                      
{0x002A145E},
{0x0F120596},	//	#awbb_GainsInit_0_	//
{0x0F120400},	//	#awbb_GainsInit_1_	//
{0x0F12072C},	//	#awbb_GainsInit_2_	//
                                                                      
//*************************************************************************///
//Gamma indoor setting																											//
//*************************************************************************///
{0x002A0734},
{0x0F120001},	//	#SARR_usGammaLutRGBIndoor_0__0_  	//
{0x0F120007},	//	#SARR_usGammaLutRGBIndoor_0__1_   //
{0x0F120010},	//	#SARR_usGammaLutRGBIndoor_0__2_   //
{0x0F120028},	//	#SARR_usGammaLutRGBIndoor_0__3_   //
{0x0F120062},	//	#SARR_usGammaLutRGBIndoor_0__4_   //
{0x0F1200D3},	//	#SARR_usGammaLutRGBIndoor_0__5_   //
{0x0F120130},	//	#SARR_usGammaLutRGBIndoor_0__6_   //
{0x0F120158},	//	#SARR_usGammaLutRGBIndoor_0__7_   //
{0x0F12017D},	//	#SARR_usGammaLutRGBIndoor_0__8_   //
{0x0F1201BE},	//	#SARR_usGammaLutRGBIndoor_0__9_   //
{0x0F1201F8},	//	#SARR_usGammaLutRGBIndoor_0__10_  //
{0x0F12022C},	//	#SARR_usGammaLutRGBIndoor_0__11_  //
{0x0F12025B},	//	#SARR_usGammaLutRGBIndoor_0__12_  //
{0x0F1202AA},	//	#SARR_usGammaLutRGBIndoor_0__13_  //
{0x0F1202EC},	//	#SARR_usGammaLutRGBIndoor_0__14_  //
{0x0F12034E},	//	#SARR_usGammaLutRGBIndoor_0__15_  //
{0x0F120396},	//	#SARR_usGammaLutRGBIndoor_0__16_  //
{0x0F1203C6},	//	#SARR_usGammaLutRGBIndoor_0__17_  //
{0x0F1203E9},	//	#SARR_usGammaLutRGBIndoor_0__18_  //
{0x0F1203F9},	//	#SARR_usGammaLutRGBIndoor_0__19_  //
{0x0F120001},	//	#SARR_usGammaLutRGBIndoor_1__0_   //
{0x0F120007},	//	#SARR_usGammaLutRGBIndoor_1__1_   //
{0x0F120010},	//	#SARR_usGammaLutRGBIndoor_1__2_   //
{0x0F120028},	//	#SARR_usGammaLutRGBIndoor_1__3_   //
{0x0F120062},	//	#SARR_usGammaLutRGBIndoor_1__4_   //
{0x0F1200D3},	//	#SARR_usGammaLutRGBIndoor_1__5_   //
{0x0F120130},	//	#SARR_usGammaLutRGBIndoor_1__6_   //
{0x0F120158},	//	#SARR_usGammaLutRGBIndoor_1__7_   //
{0x0F12017D},	//	#SARR_usGammaLutRGBIndoor_1__8_   //
{0x0F1201BE},	//	#SARR_usGammaLutRGBIndoor_1__9_   //
{0x0F1201F8},	//	#SARR_usGammaLutRGBIndoor_1__10_  //
{0x0F12022C},	//	#SARR_usGammaLutRGBIndoor_1__11_  //
{0x0F12025B},	//	#SARR_usGammaLutRGBIndoor_1__12_  //
{0x0F1202AA},	//	#SARR_usGammaLutRGBIndoor_1__13_  //
{0x0F1202EC},	//	#SARR_usGammaLutRGBIndoor_1__14_  //
{0x0F12034E},	//	#SARR_usGammaLutRGBIndoor_1__15_  //
{0x0F120396},	//	#SARR_usGammaLutRGBIndoor_1__16_  //
{0x0F1203C6},	//	#SARR_usGammaLutRGBIndoor_1__17_  //
{0x0F1203E9},	//	#SARR_usGammaLutRGBIndoor_1__18_  //
{0x0F1203F9},	//	#SARR_usGammaLutRGBIndoor_1__19_  //
{0x0F120001},	//	#SARR_usGammaLutRGBIndoor_2__0_   //
{0x0F120007},	//	#SARR_usGammaLutRGBIndoor_2__1_   //
{0x0F120010},	//	#SARR_usGammaLutRGBIndoor_2__2_   //
{0x0F120028},	//	#SARR_usGammaLutRGBIndoor_2__3_   //
{0x0F120062},	//	#SARR_usGammaLutRGBIndoor_2__4_   //
{0x0F1200D3},	//	#SARR_usGammaLutRGBIndoor_2__5_   //
{0x0F120130},	//	#SARR_usGammaLutRGBIndoor_2__6_   //
{0x0F120158},	//	#SARR_usGammaLutRGBIndoor_2__7_   //
{0x0F12017D},	//	#SARR_usGammaLutRGBIndoor_2__8_   //
{0x0F1201BE},	//	#SARR_usGammaLutRGBIndoor_2__9_   //
{0x0F1201F8},	//	#SARR_usGammaLutRGBIndoor_2__10_  //
{0x0F12022C},	//	#SARR_usGammaLutRGBIndoor_2__11_  //
{0x0F12025B},	//	#SARR_usGammaLutRGBIndoor_2__12_  //
{0x0F1202AA},	//	#SARR_usGammaLutRGBIndoor_2__13_  //
{0x0F1202EC},	//	#SARR_usGammaLutRGBIndoor_2__14_  //
{0x0F12034E},	//	#SARR_usGammaLutRGBIndoor_2__15_  //
{0x0F120396},	//	#SARR_usGammaLutRGBIndoor_2__16_  //
{0x0F1203C6},	//	#SARR_usGammaLutRGBIndoor_2__17_  //
{0x0F1203E9},	//	#SARR_usGammaLutRGBIndoor_2__18_  //
{0x0F1203F9},	//	#SARR_usGammaLutRGBIndoor_2__19_  //
                                                                      
//*************************************************************************///
//Gamma outdoor setting																											//
//*************************************************************************///
{0x0F120000},	//	#SARR_usGammaLutRGBOutdoor_0__0_ 		//
{0x0F12000F},	//	#SARR_usGammaLutRGBOutdoor_0__1_    //
{0x0F120020},	//	#SARR_usGammaLutRGBOutdoor_0__2_    //
{0x0F120043},	//	#SARR_usGammaLutRGBOutdoor_0__3_    //
{0x0F120086},	//	#SARR_usGammaLutRGBOutdoor_0__4_    //
{0x0F1200ED},	//	#SARR_usGammaLutRGBOutdoor_0__5_    //
{0x0F12013E},	//	#SARR_usGammaLutRGBOutdoor_0__6_    //
{0x0F120163},	//	#SARR_usGammaLutRGBOutdoor_0__7_    //
{0x0F120185},	//	#SARR_usGammaLutRGBOutdoor_0__8_    //
{0x0F1201BF},	//	#SARR_usGammaLutRGBOutdoor_0__9_    //
{0x0F1201F2},	//	#SARR_usGammaLutRGBOutdoor_0__10_   //
{0x0F120221},	//	#SARR_usGammaLutRGBOutdoor_0__11_   //
{0x0F12024A},	//	#SARR_usGammaLutRGBOutdoor_0__12_   //
{0x0F120294},	//	#SARR_usGammaLutRGBOutdoor_0__13_   //
{0x0F1202D0},	//	#SARR_usGammaLutRGBOutdoor_0__14_   //
{0x0F12032A},	//	#SARR_usGammaLutRGBOutdoor_0__15_   //
{0x0F12036A},	//	#SARR_usGammaLutRGBOutdoor_0__16_   //
{0x0F12039F},	//	#SARR_usGammaLutRGBOutdoor_0__17_   //
{0x0F1203CC},	//	#SARR_usGammaLutRGBOutdoor_0__18_   //
{0x0F1203F9},	//	#SARR_usGammaLutRGBOutdoor_0__19_   //
{0x0F120000},	//	#SARR_usGammaLutRGBOutdoor_1__0_    //
{0x0F12000F},	//	#SARR_usGammaLutRGBOutdoor_1__1_    //
{0x0F120020},	//	#SARR_usGammaLutRGBOutdoor_1__2_    //
{0x0F120043},	//	#SARR_usGammaLutRGBOutdoor_1__3_    //
{0x0F120086},	//	#SARR_usGammaLutRGBOutdoor_1__4_    //
{0x0F1200ED},	//	#SARR_usGammaLutRGBOutdoor_1__5_    //
{0x0F12013E},	//	#SARR_usGammaLutRGBOutdoor_1__6_    //
{0x0F120163},	//	#SARR_usGammaLutRGBOutdoor_1__7_    //
{0x0F120185},	//	#SARR_usGammaLutRGBOutdoor_1__8_    //
{0x0F1201BF},	//	#SARR_usGammaLutRGBOutdoor_1__9_    //
{0x0F1201F2},	//	#SARR_usGammaLutRGBOutdoor_1__10_   //
{0x0F120221},	//	#SARR_usGammaLutRGBOutdoor_1__11_   //
{0x0F12024A},	//	#SARR_usGammaLutRGBOutdoor_1__12_   //
{0x0F120294},	//	#SARR_usGammaLutRGBOutdoor_1__13_   //
{0x0F1202D0},	//	#SARR_usGammaLutRGBOutdoor_1__14_   //
{0x0F12032A},	//	#SARR_usGammaLutRGBOutdoor_1__15_   //
{0x0F12036A},	//	#SARR_usGammaLutRGBOutdoor_1__16_   //
{0x0F12039F},	//	#SARR_usGammaLutRGBOutdoor_1__17_   //
{0x0F1203CC},	//	#SARR_usGammaLutRGBOutdoor_1__18_   //
{0x0F1203F9},	//	#SARR_usGammaLutRGBOutdoor_1__19_   //
{0x0F120000},	//	#SARR_usGammaLutRGBOutdoor_2__0_    //
{0x0F12000F},	//	#SARR_usGammaLutRGBOutdoor_2__1_    //
{0x0F120020},	//	#SARR_usGammaLutRGBOutdoor_2__2_    //
{0x0F120043},	//	#SARR_usGammaLutRGBOutdoor_2__3_    //
{0x0F120086},	//	#SARR_usGammaLutRGBOutdoor_2__4_    //
{0x0F1200ED},	//	#SARR_usGammaLutRGBOutdoor_2__5_    //
{0x0F12013E},	//	#SARR_usGammaLutRGBOutdoor_2__6_    //
{0x0F120163},	//	#SARR_usGammaLutRGBOutdoor_2__7_    //
{0x0F120185},	//	#SARR_usGammaLutRGBOutdoor_2__8_    //
{0x0F1201BF},	//	#SARR_usGammaLutRGBOutdoor_2__9_    //
{0x0F1201F2},	//	#SARR_usGammaLutRGBOutdoor_2__10_   //
{0x0F120221},	//	#SARR_usGammaLutRGBOutdoor_2__11_   //
{0x0F12024A},	//	#SARR_usGammaLutRGBOutdoor_2__12_   //
{0x0F120294},	//	#SARR_usGammaLutRGBOutdoor_2__13_   //
{0x0F1202D0},	//	#SARR_usGammaLutRGBOutdoor_2__14_   //
{0x0F12032A},	//	#SARR_usGammaLutRGBOutdoor_2__15_   //
{0x0F12036A},	//	#SARR_usGammaLutRGBOutdoor_2__16_   //
{0x0F12039F},	//	#SARR_usGammaLutRGBOutdoor_2__17_   //
{0x0F1203CC},	//	#SARR_usGammaLutRGBOutdoor_2__18_   //
{0x0F1203F9},	//	#SARR_usGammaLutRGBOutdoor_2__19_   //
                                                                      
//*************************************************************************///
//CCM setting																																//
//*************************************************************************///
{0x002A08A6},
{0x0F1200C0},	//	#SARR_AwbCcmCord   	//
{0x0F120100},	//	#SARR_AwbCcmCord_1_ //
{0x0F120125},	//	#SARR_AwbCcmCord_2_ //
{0x0F12015F},	//	#SARR_AwbCcmCord_3_ //
{0x0F12017C},	//	#SARR_AwbCcmCord_4_ //
{0x0F120194},	//	#SARR_AwbCcmCord_5_ //
                                                                      
{0x0F120001},	//	#wbt_bUseOutdoorCCM	//
                                                                      
{0x002A0898},
{0x0F124800},
{0x0F127000},	//	#TVAR_wbt_pBaseCcms	//
{0x002A08A0},
{0x0F1248D8},
{0x0F127000},	//	#TVAR_wbt_pOutdoorCcm	//
                                                                      
{0x002A4800},
{0x0F12016C},	//	#TVAR_wbt_pBaseCcms[0]		hor//
{0x0F12FF94},	//	#TVAR_wbt_pBaseCcms[1]  	//
{0x0F12FFCE},	//	#TVAR_wbt_pBaseCcms[2]  	//
{0x0F12FF20},	//	#TVAR_wbt_pBaseCcms[3]  	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[4]  	//
{0x0F12FF53},	//	#TVAR_wbt_pBaseCcms[5]  	//
{0x0F12003F},	//	#TVAR_wbt_pBaseCcms[6]  	//
{0x0F120007},	//	#TVAR_wbt_pBaseCcms[7]  	//
{0x0F1201DF},	//	#TVAR_wbt_pBaseCcms[8]  	//
{0x0F120110},	//	#TVAR_wbt_pBaseCcms[9]  	//
{0x0F1200DF},	//	#TVAR_wbt_pBaseCcms[10] 	//
{0x0F12FF47},	//	#TVAR_wbt_pBaseCcms[11] 	//
{0x0F120206},	//	#TVAR_wbt_pBaseCcms[12] 	//
{0x0F12FF7F},	//	#TVAR_wbt_pBaseCcms[13] 	//
{0x0F120191},	//	#TVAR_wbt_pBaseCcms[14] 	//
{0x0F12FF06},	//	#TVAR_wbt_pBaseCcms[15] 	//
{0x0F1201BA},	//	#TVAR_wbt_pBaseCcms[16] 	//
{0x0F120108},	//	#TVAR_wbt_pBaseCcms[17] 	//
{0x0F12016C},	//	#TVAR_wbt_pBaseCcms[18]		incaA//
{0x0F12FF94},	//	#TVAR_wbt_pBaseCcms[19] 	//
{0x0F12FFCE},	//	#TVAR_wbt_pBaseCcms[20] 	//
{0x0F12FF20},	//	#TVAR_wbt_pBaseCcms[21] 	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[22] 	//
{0x0F12FF53},	//	#TVAR_wbt_pBaseCcms[23] 	//
{0x0F12003F},	//	#TVAR_wbt_pBaseCcms[24] 	//
{0x0F120007},	//	#TVAR_wbt_pBaseCcms[25] 	//
{0x0F1201DF},	//	#TVAR_wbt_pBaseCcms[26] 	//
{0x0F120110},	//	#TVAR_wbt_pBaseCcms[27] 	//
{0x0F1200DF},	//	#TVAR_wbt_pBaseCcms[28] 	//
{0x0F12FF47},	//	#TVAR_wbt_pBaseCcms[29] 	//
{0x0F120206},	//	#TVAR_wbt_pBaseCcms[30] 	//
{0x0F12FF7F},	//	#TVAR_wbt_pBaseCcms[31] 	//
{0x0F120191},	//	#TVAR_wbt_pBaseCcms[32] 	//
{0x0F12FF06},	//	#TVAR_wbt_pBaseCcms[33] 	//
{0x0F1201BA},	//	#TVAR_wbt_pBaseCcms[34] 	//
{0x0F120108},	//	#TVAR_wbt_pBaseCcms[35] 	//
{0x0F12016C},	//	#TVAR_wbt_pBaseCcms[36]		WW//
{0x0F12FF94},	//	#TVAR_wbt_pBaseCcms[37] 	//
{0x0F12FFCE},	//	#TVAR_wbt_pBaseCcms[38] 	//
{0x0F12FF20},	//	#TVAR_wbt_pBaseCcms[39] 	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[40] 	//
{0x0F12FF53},	//	#TVAR_wbt_pBaseCcms[41] 	//
{0x0F12003F},	//	#TVAR_wbt_pBaseCcms[42] 	//
{0x0F120007},	//	#TVAR_wbt_pBaseCcms[43] 	//
{0x0F1201DF},	//	#TVAR_wbt_pBaseCcms[44] 	//
{0x0F120110},	//	#TVAR_wbt_pBaseCcms[45] 	//
{0x0F1200DF},	//	#TVAR_wbt_pBaseCcms[46] 	//
{0x0F12FF47},	//	#TVAR_wbt_pBaseCcms[47] 	//
{0x0F120206},	//	#TVAR_wbt_pBaseCcms[48] 	//
{0x0F12FF7F},	//	#TVAR_wbt_pBaseCcms[49] 	//
{0x0F120191},	//	#TVAR_wbt_pBaseCcms[50] 	//
{0x0F12FF06},	//	#TVAR_wbt_pBaseCcms[51] 	//
{0x0F1201BA},	//	#TVAR_wbt_pBaseCcms[52] 	//
{0x0F120108},	//	#TVAR_wbt_pBaseCcms[53] 	//
{0x0F120208},	//	#TVAR_wbt_pBaseCcms[54]		CW//
{0x0F12FFD3},	//	#TVAR_wbt_pBaseCcms[55] 	//
{0x0F12FFE9},	//	#TVAR_wbt_pBaseCcms[56] 	//
{0x0F12FF5B},	//	#TVAR_wbt_pBaseCcms[57] 	//
{0x0F12025A},	//	#TVAR_wbt_pBaseCcms[58] 	//
{0x0F12FF80},	//	#TVAR_wbt_pBaseCcms[59] 	//
{0x0F12FFC8},	//	#TVAR_wbt_pBaseCcms[60] 	//
{0x0F12FFC1},	//	#TVAR_wbt_pBaseCcms[61] 	//
{0x0F12013A},	//	#TVAR_wbt_pBaseCcms[62] 	//
{0x0F120112},	//	#TVAR_wbt_pBaseCcms[63] 	//
{0x0F1200EE},	//	#TVAR_wbt_pBaseCcms[64] 	//
{0x0F12FF99},	//	#TVAR_wbt_pBaseCcms[65] 	//
{0x0F12009E},	//	#TVAR_wbt_pBaseCcms[66] 	//
{0x0F12FF5F},	//	#TVAR_wbt_pBaseCcms[67] 	//
{0x0F1201A8},	//	#TVAR_wbt_pBaseCcms[68] 	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[69] 	//
{0x0F120187},	//	#TVAR_wbt_pBaseCcms[70] 	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[71] 	//
{0x0F120208},	//	#TVAR_wbt_pBaseCcms[72]		D50//
{0x0F12FFD3},	//	#TVAR_wbt_pBaseCcms[73] 	//
{0x0F12FFE9},	//	#TVAR_wbt_pBaseCcms[74] 	//
{0x0F12FF5B},	//	#TVAR_wbt_pBaseCcms[75] 	//
{0x0F12025A},	//	#TVAR_wbt_pBaseCcms[76] 	//
{0x0F12FF80},	//	#TVAR_wbt_pBaseCcms[77] 	//
{0x0F12FFC8},	//	#TVAR_wbt_pBaseCcms[78] 	//
{0x0F12FFC1},	//	#TVAR_wbt_pBaseCcms[79] 	//
{0x0F12013A},	//	#TVAR_wbt_pBaseCcms[80] 	//
{0x0F120112},	//	#TVAR_wbt_pBaseCcms[81] 	//
{0x0F1200EE},	//	#TVAR_wbt_pBaseCcms[82] 	//
{0x0F12FF99},	//	#TVAR_wbt_pBaseCcms[83] 	//
{0x0F12009E},	//	#TVAR_wbt_pBaseCcms[84] 	//
{0x0F12FF5F},	//	#TVAR_wbt_pBaseCcms[85] 	//
{0x0F1201A8},	//	#TVAR_wbt_pBaseCcms[86] 	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[87] 	//
{0x0F120187},	//	#TVAR_wbt_pBaseCcms[88] 	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[89] 	//
{0x0F120208},	//	#TVAR_wbt_pBaseCcms[90]		D65//
{0x0F12FFD3},	//	#TVAR_wbt_pBaseCcms[91] 	//
{0x0F12FFE9},	//	#TVAR_wbt_pBaseCcms[92] 	//
{0x0F12FF5B},	//	#TVAR_wbt_pBaseCcms[93] 	//
{0x0F12025A},	//	#TVAR_wbt_pBaseCcms[94] 	//
{0x0F12FF80},	//	#TVAR_wbt_pBaseCcms[95] 	//
{0x0F12FFC8},	//	#TVAR_wbt_pBaseCcms[96] 	//
{0x0F12FFC1},	//	#TVAR_wbt_pBaseCcms[97] 	//
{0x0F12013A},	//	#TVAR_wbt_pBaseCcms[98] 	//
{0x0F120112},	//	#TVAR_wbt_pBaseCcms[99] 	//
{0x0F1200EE},	//	#TVAR_wbt_pBaseCcms[100]	//
{0x0F12FF99},	//	#TVAR_wbt_pBaseCcms[101]	//
{0x0F12009E},	//	#TVAR_wbt_pBaseCcms[102]	//
{0x0F12FF5F},	//	#TVAR_wbt_pBaseCcms[103]	//
{0x0F1201A8},	//	#TVAR_wbt_pBaseCcms[104]	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[105]	//
{0x0F120187},	//	#TVAR_wbt_pBaseCcms[106]	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[107]	//
                                                                      
{0x0F1201AA},	//	#TVAR_wbt_pOutdoorCcm[0]	//
{0x0F12FFB6},	//	#TVAR_wbt_pOutdoorCcm[1]  //
{0x0F12FFD4},	//	#TVAR_wbt_pOutdoorCcm[2]  //
{0x0F12FF6C},	//	#TVAR_wbt_pOutdoorCcm[3]  //
{0x0F1201E8},	//	#TVAR_wbt_pOutdoorCcm[4]  //
{0x0F12FF79},	//	#TVAR_wbt_pOutdoorCcm[5]  //
{0x0F120000},	//	#TVAR_wbt_pOutdoorCcm[6]  //
{0x0F12FFF5},	//	#TVAR_wbt_pOutdoorCcm[7]  //
{0x0F12023C},	//	#TVAR_wbt_pOutdoorCcm[8]  //
{0x0F1200BF},	//	#TVAR_wbt_pOutdoorCcm[9]  //
{0x0F1200E0},	//	#TVAR_wbt_pOutdoorCcm[10] //
{0x0F12FF5B},	//	#TVAR_wbt_pOutdoorCcm[11] //
{0x0F12022D},	//	#TVAR_wbt_pOutdoorCcm[12] //
{0x0F12FF9B},	//	#TVAR_wbt_pOutdoorCcm[13] //
{0x0F1201E1},	//	#TVAR_wbt_pOutdoorCcm[14] //
{0x0F12FF34},	//	#TVAR_wbt_pOutdoorCcm[15] //
{0x0F12014B},	//	#TVAR_wbt_pOutdoorCcm[16] //
{0x0F1201B6},	//	#TVAR_wbt_pOutdoorCcm[17] //
                                                                      
//*************************************************************************///
//AFIT setting																															//
//*************************************************************************///
                                                                      
//	Mon_AFIT_uNoiseInd	//
{0x002A0944},
{0x0F120050},	//	#afit_uNoiseIndInDoor_0_  //
{0x0F1200B0},	//	#afit_uNoiseIndInDoor_1_  //
{0x0F120196},	//	#afit_uNoiseIndInDoor_2_  //
{0x0F120245},	//	#afit_uNoiseIndInDoor_3_  //
{0x0F120300},	//	#afit_uNoiseIndInDoor_4_	//
                                                                      
{0x002A097A},
{0x0F120001},	//	#afit_bUseSenBpr					//
{0x0F1201CC},	//	#afit_usBprThr_0_         //
{0x0F1201CC},	//	#afit_usBprThr_1_         //
{0x0F1201CC},	//	#afit_usBprThr_2_         //
{0x0F1201CC},	//	#afit_usBprThr_3_         //
{0x0F1201CC},	//	#afit_usBprThr_4_         //
{0x0F120180},	//	#afit_NIContrastAFITValue //
{0x0F120196},	//	#afit_NIContrastTh        //
                                                                      
{0x002A0976},
{0x0F120070},	//	#afit_usGamutTh	//
{0x0F120005},	//	#afit_usNeargrayOffset	//
                                                                      
{0x002A0938},
{0x0F120000},	//	#afit_bUseNB_Afit       //
{0x0F120014},	//	#SARR_uNormBrInDoor_0_  //
{0x0F1200D2},	//	#SARR_uNormBrInDoor_1_  //
{0x0F120384},	//	#SARR_uNormBrInDoor_2_  //
{0x0F1207D0},	//	#SARR_uNormBrInDoor_3_  //
{0x0F121388},	//	#SARR_uNormBrInDoor_4_	//
                                                                      
{0x002A098C},
{0x0F120000},	//_BRIGHTNESS	AFIT 0                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120032},	//_postdmsc_iLowSat                                    //
{0x0F1201F4},	//_postdmsc_iHighSat                                   //
{0x0F120070},	//_postdmsc_iTune                                      //
{0x0F120040},	//_yuvemix_mNegRanges_0                                //
{0x0F1200A0},	//_yuvemix_mNegRanges_1                                //
{0x0F120100},	//_yuvemix_mNegRanges_2                                //
{0x0F120010},	//_yuvemix_mPosRanges_0                                //
{0x0F120040},	//_yuvemix_mPosRanges_1                                //
{0x0F1200A0},	//_yuvemix_mPosRanges_2                                //
{0x0F121430},	//_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh           //
{0x0F120201},	//_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh      //
{0x0F120204},	//_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh //
{0x0F123604},	//_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low     //
{0x0F12032A},	//_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low    //
{0x0F120403},	//_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin //
{0x0F121B06},	//_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow   //
{0x0F126015},	//_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH         //
{0x0F1200C0},	//_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune          //
{0x0F126080},	//_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh        //
{0x0F124080},	//_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh  //
{0x0F120640},	//_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed   //
{0x0F120306},	//_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh     //
{0x0F122003},	//_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH //
{0x0F12FF01},	//_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit       //
{0x0F120000},	//_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2 //
{0x0F120400},	//_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower      //
{0x0F12365A},	//_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow       //
{0x0F12102A},	//_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow        //
{0x0F12000B},	//_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow           //
{0x0F120600},	//_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower           //
{0x0F125A0F},	//_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit      //
{0x0F120505},	//_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope   //
{0x0F121802},	//_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR           //
{0x0F120000},	//_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres     //
{0x0F122006},	//_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR     //
{0x0F123028},	//_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen      //
{0x0F120418},	//_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh            //
{0x0F120101},	//_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative      //
{0x0F120800},	//_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle     //
{0x0F121804},	//_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh  //
{0x0F124008},	//_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh   //
{0x0F120540},	//_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange   //
{0x0F128006},	//_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad   //
{0x0F120020},	//_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal    //
{0x0F120000},	//_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh        //
{0x0F121800},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
{0x0F120000},	//_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit         //
{0x0F121E10},	//_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff     //
{0x0F12000B},	//_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0          //
{0x0F120607},	//_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2        //
{0x0F120005},	//_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0        //
{0x0F120607},	//_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2        //
{0x0F120405},	//_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY         //
{0x0F120205},	//_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm          //
{0x0F120304},	//_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm          //
{0x0F120409},	//_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift        //
{0x0F120306},	//_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y     //
{0x0F120407},	//_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y  //
{0x0F121C04},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F120214},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121002},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120610},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F120F02},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F124A18},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120040},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
{0x0F120180},	//_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H    //
{0x0F120A0A},	//_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C     //
{0x0F120101},	//_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C //
{0x0F122A36},	//_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh  //
{0x0F126024},	//_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower  //
{0x0F122A36},	//_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise    //
{0x0F12FFFF},	//_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp  //
{0x0F120808},	//_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope        //
{0x0F120A01},	//_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin       //
{0x0F12010A},	//_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin      //
{0x0F123601},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F12242A},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F123660},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF2A},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1208FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120008},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
{0x0F120001},	//_bnr_nClustLevel_C      [0]                          //
{0x0F120000},	//_BRIGHTNESS	AFIT 1                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120032},	//_postdmsc_iLowSat                                    //
{0x0F1201F4},	//_postdmsc_iHighSat                                   //
{0x0F120070},	//_postdmsc_iTune                                      //
{0x0F120040},	//_yuvemix_mNegRanges_0                                //
{0x0F1200A0},	//_yuvemix_mNegRanges_1                                //
{0x0F120100},	//_yuvemix_mNegRanges_2                                //
{0x0F120010},	//_yuvemix_mPosRanges_0                                //
{0x0F120060},	//_yuvemix_mPosRanges_1                                //
{0x0F120100},	//_yuvemix_mPosRanges_2                                //
{0x0F121430},	//_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh           //
{0x0F120201},	//_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh      //
{0x0F120204},	//_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh //
{0x0F122404},	//_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low     //
{0x0F12031B},	//_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low    //
{0x0F120103},	//_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin //
{0x0F121205},	//_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow   //
{0x0F12400D},	//_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH         //
{0x0F120080},	//_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune          //
{0x0F122080},	//_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh        //
{0x0F123040},	//_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh  //
{0x0F120630},	//_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed   //
{0x0F120306},	//_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh     //
{0x0F122003},	//_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH //
{0x0F12FF01},	//_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit       //
{0x0F120404},	//_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2 //
{0x0F120300},	//_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower      //
{0x0F12245A},	//_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow       //
{0x0F121018},	//_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow        //
{0x0F12000B},	//_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow           //
{0x0F120B00},	//_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower           //
{0x0F125A0F},	//_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit      //
{0x0F120505},	//_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope   //
{0x0F121802},	//_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR           //
{0x0F120000},	//_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres     //
{0x0F122006},	//_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR     //
{0x0F123428},	//_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen      //
{0x0F12041C},	//_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh            //
{0x0F120101},	//_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative      //
{0x0F120800},	//_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle     //
{0x0F121004},	//_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh  //
{0x0F124008},	//_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh   //
{0x0F120540},	//_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange   //
{0x0F128006},	//_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad   //
{0x0F120020},	//_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal    //
{0x0F120000},	//_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh        //
{0x0F121800},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
{0x0F120000},	//_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit         //
{0x0F121E10},	//_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff     //
{0x0F12000B},	//_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0          //
{0x0F120607},	//_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2        //
{0x0F120005},	//_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0        //
{0x0F120607},	//_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2        //
{0x0F120405},	//_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY         //
{0x0F120205},	//_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm          //
{0x0F120304},	//_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm          //
{0x0F120409},	//_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift        //
{0x0F120306},	//_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y     //
{0x0F120407},	//_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y  //
{0x0F121F04},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F120218},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121102},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120611},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F121002},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F128018},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120080},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
{0x0F120180},	//_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H    //
{0x0F120A0A},	//_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C     //
{0x0F120101},	//_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C //
{0x0F121B24},	//_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh  //
{0x0F126024},	//_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower  //
{0x0F121010},	//_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise    //
{0x0F12FFFF},	//_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp  //
{0x0F120808},	//_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope        //
{0x0F120A01},	//_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin       //
{0x0F12010A},	//_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin      //
{0x0F122401},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F12241B},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F121E60},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF18},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1208FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120008},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
{0x0F120001},	//_bnr_nClustLevel_C      [0]                          //
{0x0F120000},	//_BRIGHTNESS	AFIT 2                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120032},	//_postdmsc_iLowSat                                    //
{0x0F1201F4},	//_postdmsc_iHighSat                                   //
{0x0F120070},	//_postdmsc_iTune                                      //
{0x0F120040},	//_yuvemix_mNegRanges_0                                //
{0x0F1200A0},	//_yuvemix_mNegRanges_1                                //
{0x0F120100},	//_yuvemix_mNegRanges_2                                //
{0x0F120010},	//_yuvemix_mPosRanges_0                                //
{0x0F120060},	//_yuvemix_mPosRanges_1                                //
{0x0F120100},	//_yuvemix_mPosRanges_2                                //
{0x0F121430},	//_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh           //
{0x0F120201},	//_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh      //
{0x0F120204},	//_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh //
{0x0F121B04},	//_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low     //
{0x0F120312},	//_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low    //
{0x0F120003},	//_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin //
{0x0F120C03},	//_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow   //
{0x0F122806},	//_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH         //
{0x0F120060},	//_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune          //
{0x0F121580},	//_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh        //
{0x0F122020},	//_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh  //
{0x0F120620},	//_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed   //
{0x0F120306},	//_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh     //
{0x0F122003},	//_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH //
{0x0F12FF01},	//_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit       //
{0x0F120404},	//_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2 //
{0x0F120300},	//_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower      //
{0x0F12145A},	//_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow       //
{0x0F121010},	//_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow        //
{0x0F12000B},	//_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow           //
{0x0F120E00},	//_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower           //
{0x0F125A0F},	//_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit      //
{0x0F120504},	//_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope   //
{0x0F121802},	//_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR           //
{0x0F120000},	//_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres     //
{0x0F122006},	//_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR     //
{0x0F123828},	//_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen      //
{0x0F120428},	//_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh            //
{0x0F120101},	//_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative      //
{0x0F128000},	//_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle     //
{0x0F120A04},	//_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh  //
{0x0F124008},	//_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh   //
{0x0F120540},	//_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange   //
{0x0F128006},	//_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad   //
{0x0F120020},	//_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal    //
{0x0F120000},	//_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh        //
{0x0F121800},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
{0x0F120000},	//_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit         //
{0x0F121E10},	//_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff     //
{0x0F12000B},	//_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0          //
{0x0F120607},	//_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2        //
{0x0F120005},	//_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0        //
{0x0F120607},	//_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2        //
{0x0F120405},	//_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY         //
{0x0F120207},	//_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm          //
{0x0F120304},	//_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm          //
{0x0F120409},	//_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift        //
{0x0F120306},	//_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y     //
{0x0F120407},	//_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y  //
{0x0F122404},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F120221},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121202},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120613},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F121202},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F128018},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120080},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
{0x0F120180},	//_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H    //
{0x0F120A0A},	//_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C     //
{0x0F120101},	//_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C //
{0x0F12121B},	//_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh  //
{0x0F126024},	//_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower  //
{0x0F120C0C},	//_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise    //
{0x0F12FFFF},	//_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp  //
{0x0F120808},	//_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope        //
{0x0F120A01},	//_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin       //
{0x0F12010A},	//_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin      //
{0x0F121B01},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F122412},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F120C60},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF0C},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1208FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120008},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
{0x0F120001},	//_bnr_nClustLevel_C      [0]                          //
{0x0F120000},	//_BRIGHTNESS	AFIT 3                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120032},	//_postdmsc_iLowSat                                    //
{0x0F1201F4},	//_postdmsc_iHighSat                                   //
{0x0F120070},	//_postdmsc_iTune                                      //
{0x0F120040},	//_yuvemix_mNegRanges_0                                //
{0x0F1200A0},	//_yuvemix_mNegRanges_1                                //
{0x0F120100},	//_yuvemix_mNegRanges_2                                //
{0x0F120010},	//_yuvemix_mPosRanges_0                                //
{0x0F120060},	//_yuvemix_mPosRanges_1                                //
{0x0F120100},	//_yuvemix_mPosRanges_2                                //
{0x0F121430},	//_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh           //
{0x0F120201},	//_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh      //
{0x0F120204},	//_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh //
{0x0F121504},	//_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low     //
{0x0F12030F},	//_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low    //
{0x0F120003},	//_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin //
{0x0F120902},	//_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow   //
{0x0F122004},	//_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH         //
{0x0F120050},	//_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune          //
{0x0F121140},	//_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh        //
{0x0F12201C},	//_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh  //
{0x0F120620},	//_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed   //
{0x0F120306},	//_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh     //
{0x0F122003},	//_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH //
{0x0F12FF01},	//_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit       //
{0x0F120404},	//_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2 //
{0x0F120300},	//_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower      //
{0x0F12145A},	//_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow       //
{0x0F121010},	//_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow        //
{0x0F12000B},	//_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow           //
{0x0F121000},	//_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower           //
{0x0F125A0F},	//_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit      //
{0x0F120503},	//_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope   //
{0x0F121802},	//_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR           //
{0x0F120000},	//_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres     //
{0x0F122006},	//_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR     //
{0x0F123C28},	//_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen      //
{0x0F12042C},	//_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh            //
{0x0F120101},	//_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative      //
{0x0F12FF00},	//_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle     //
{0x0F120904},	//_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh  //
{0x0F124008},	//_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh   //
{0x0F120540},	//_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange   //
{0x0F128006},	//_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad   //
{0x0F120020},	//_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal    //
{0x0F120000},	//_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh        //
{0x0F121800},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
{0x0F120000},	//_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit         //
{0x0F121E10},	//_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff     //
{0x0F12000B},	//_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0          //
{0x0F120607},	//_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2        //
{0x0F120005},	//_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0        //
{0x0F120607},	//_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2        //
{0x0F120405},	//_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY         //
{0x0F120206},	//_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm          //
{0x0F120304},	//_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm          //
{0x0F120409},	//_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift        //
{0x0F120305},	//_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y     //
{0x0F120406},	//_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y  //
{0x0F122804},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F120228},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121402},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120618},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F121402},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F128018},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120080},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
{0x0F120180},	//_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H    //
{0x0F120A0A},	//_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C     //
{0x0F120101},	//_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C //
{0x0F120F15},	//_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh  //
{0x0F126024},	//_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower  //
{0x0F120A0A},	//_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise    //
{0x0F12FFFF},	//_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp  //
{0x0F120808},	//_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope        //
{0x0F120A01},	//_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin       //
{0x0F12010A},	//_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin      //
{0x0F121501},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F12240F},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F120A60},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF0A},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1208FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120008},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
{0x0F120001},	//_bnr_nClustLevel_C      [0]                          //
{0x0F120000},	//_BRIGHTNESS	AFIT 4                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120032},	//_postdmsc_iLowSat                                    //
{0x0F1201F4},	//_postdmsc_iHighSat                                   //
{0x0F120070},	//_postdmsc_iTune                                      //
{0x0F120040},	//_yuvemix_mNegRanges_0                                //
{0x0F1200A0},	//_yuvemix_mNegRanges_1                                //
{0x0F120100},	//_yuvemix_mNegRanges_2                                //
{0x0F120010},	//_yuvemix_mPosRanges_0                                //
{0x0F120060},	//_yuvemix_mPosRanges_1                                //
{0x0F120100},	//_yuvemix_mPosRanges_2                                //
{0x0F121430},	//_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh           //
{0x0F120201},	//_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh      //
{0x0F120204},	//_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh //
{0x0F120F04},	//_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low     //
{0x0F12030C},	//_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low    //
{0x0F120003},	//_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin //
{0x0F120602},	//_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow   //
{0x0F121803},	//_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH         //
{0x0F120040},	//_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune          //
{0x0F120E20},	//_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh        //
{0x0F122018},	//_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh  //
{0x0F120620},	//_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed   //
{0x0F120306},	//_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh     //
{0x0F122003},	//_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH //
{0x0F12FF01},	//_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit       //
{0x0F120404},	//_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2 //
{0x0F120200},	//_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower      //
{0x0F12145A},	//_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow       //
{0x0F121010},	//_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow        //
{0x0F12000B},	//_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow           //
{0x0F121200},	//_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower           //
{0x0F125A0F},	//_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit      //
{0x0F120502},	//_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope   //
{0x0F121802},	//_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR           //
{0x0F120000},	//_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres     //
{0x0F122006},	//_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR     //
{0x0F124028},	//_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen      //
{0x0F120430},	//_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh            //
{0x0F120101},	//_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative      //
{0x0F12FF00},	//_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle     //
{0x0F120804},	//_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh  //
{0x0F124008},	//_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh   //
{0x0F120540},	//_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange   //
{0x0F128006},	//_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad   //
{0x0F120020},	//_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal    //
{0x0F120000},	//_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh        //
{0x0F121800},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
{0x0F120000},	//_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit         //
{0x0F121E10},	//_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff     //
{0x0F12000B},	//_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0          //
{0x0F120607},	//_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2        //
{0x0F120005},	//_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0        //
{0x0F120607},	//_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2        //
{0x0F120405},	//_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY         //
{0x0F120205},	//_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm          //
{0x0F120304},	//_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm          //
{0x0F120409},	//_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift        //
{0x0F120306},	//_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y     //
{0x0F120407},	//_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y  //
{0x0F122C04},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F12022C},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121402},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120618},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F121402},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F128018},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120080},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
{0x0F120180},	//_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H    //
{0x0F120A0A},	//_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C     //
{0x0F120101},	//_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C //
{0x0F120C0F},	//_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh  //
{0x0F126024},	//_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower  //
{0x0F120808},	//_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise    //
{0x0F12FFFF},	//_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp  //
{0x0F120808},	//_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope        //
{0x0F120A01},	//_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin       //
{0x0F12010A},	//_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin      //
{0x0F120F01},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F12240C},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F120860},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF08},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1208FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120008},	//_ee_iReduceEdgeSlope_Bin [7:0]							         //
{0x0F120001},	//_bnr_nClustLevel_C      [0]   bWideWide[1]           //
{0x0F1223CE},	//[0]CAFITB_bnr_bypass                                 //
{0x0F12FDC8},	//[0]CAFITB_bnr_bSlopenessTune                         //
{0x0F12112E},	//[0]CAFITB_ee_bReduceNegMedSh                         //
{0x0F1283A5},	//[0]CAFITB_dmsc_bDoDesat                              //
{0x0F12FE67},	//[0]CAFITB_postdmsc_bSat                              //
{0x0F120000},	//[0]CAFITB_yuviirnr_bWideY																				//
                                                                      
//*************************************************************************///
//System setting																														//
//*************************************************************************///
                                                                      
{0x002A01F8},
{0x0F125DC0},	//	#REG_TC_IPRM_InClockLSBs//MCLK    : 24Mhz  	//
{0x002A0212},
{0x0F120002},	//	#REG_TC_IPRM_UseNPviClocks			//
{0x0F120000},	//	#REG_TC_IPRM_UseNMipiClocks     //
{0x0F120000},	//	#REG_TC_IPRM_NumberOfMipiLanes  //
{0x002A021A},
{0x0F123A98},	//	#REG_TC_IPRM_OpClk4KHz_0//SCLK    : 60Mhz				//
{0x0F124F1A},	//	#REG_TC_IPRM_MinOutRate4KHz_0//PCLK Min : 81Mhz //
{0x0F124F1A},	//	#REG_TC_IPRM_MaxOutRate4KHz_0//PCLK Max : 81Mhz //
{0x0F124F1A},	//	#REG_TC_IPRM_OpClk4KHz_1//SCLK    : 81Mhz       //
{0x0F124F1A},	//	#REG_TC_IPRM_MinOutRate4KHz_1//PCLK Min : 81Mhz //
{0x0F124F1A},	//	#REG_TC_IPRM_MaxOutRate4KHz_1//PCLK Max : 81Mhz //
{0x002A022C},
{0x0F120001},	//	#REG_TC_IPRM_InitParamsUpdated       //
                                                                      
//*************************************************************************///
//ETC... setting																														//
//*************************************************************************///
{0x002A0478},
{0x0F12005F},	//	#REG_TC_BRC_usPrevQuality			//
{0x0F12005F},	//	#REG_TC_BRC_usCaptureQuality  //
{0x0F120001},	//	#REG_TC_THUMB_Thumb_bActive   //
{0x0F120280},	//	#REG_TC_THUMB_Thumb_uWidth    //
{0x0F1201E0},	//	#REG_TC_THUMB_Thumb_uHeight   //
{0x0F120005},	//	#REG_TC_THUMB_Thumb_Format    //
{0x002A17DC},
{0x0F120054},	//	#jpeg_ManualMBCV	//
{0x002A1AE4},
{0x0F12001C},	//	#senHal_bExtraAddLine	//
{0x002A0284},
{0x0F120001},	//	#REG_TC_GP_bBypassScalerJpg	//
{0x002A028A},	//	
{0x0F120000},	//	#REG_TC_GP_bUse1FrameCaptureMode 0:Continuous 1:Single frmae//
                                                                      
//*************************************************************************///
//Configuration setting																											//
//*************************************************************************///
{0x002A02A6},
{0x0F120280},	//	#REG_0TC_PCFG_usWidth  //Hsize   : 640			//
{0x0F1201E0},	//	#REG_0TC_PCFG_usHeight//Vsize   : 480       //
{0x0F120005},	//	#REG_0TC_PCFG_Format//5 : YUV7 : Raw9 : JPG //
{0x0F124F1A},	//	#REG_0TC_PCFG_usMaxOut4KHzRate   //
{0x0F124F1A},	//	#REG_0TC_PCFG_usMinOut4KHzRate   //
{0x0F120100},	//	#REG_0TC_PCFG_OutClkPerPix88     //
{0x0F120300},	//	#REG_0TC_PCFG_uBpp88             //
{0x0F120052},	//	#REG_0TC_PCFG_PVIMask            //
{0x0F120000},	//	#REG_0TC_PCFG_OIFMask            //
{0x0F1201E0},	//	#REG_0TC_PCFG_usJpegPacketSize   //
{0x0F120000},	//	#REG_0TC_PCFG_usJpegTotalPackets //
{0x0F120000},	//	#REG_0TC_PCFG_uClockInd          //
{0x0F120000},	//	#REG_0TC_PCFG_usFrTimeType       //
{0x0F120001},	//	#REG_0TC_PCFG_FrRateQualityType  //
{0x0F12029A},	//	#REG_0TC_PCFG_usMaxFrTimeMsecMult10         //
{0x0F12014D},	//	#REG_0TC_PCFG_usMinFrTimeMsecMult10         //
{0x002A02D0},
{0x0F120000},	//	#REG_0TC_PCFG_uPrevMirror										//
{0x0F120000},	//	#REG_0TC_PCFG_uCaptureMirror     //
{0x0F120000},	//	#REG_0TC_PCFG_uRotation          //
                                                                      
{0x002A0396},
{0x0F120000},	//	#REG_0TC_CCFG_uCaptureMode									//
{0x0F120A00},	//	#REG_0TC_CCFG_usWidth            //
{0x0F120780},	//	#REG_0TC_CCFG_usHeight           //
{0x0F120009},	//	#REG_0TC_CCFG_Format             //
{0x0F124F1A},	//	#REG_0TC_CCFG_usMaxOut4KHzRate   //
{0x0F124F1A},	//	#REG_0TC_CCFG_usMinOut4KHzRate   //
{0x0F120100},	//	#REG_0TC_CCFG_OutClkPerPix88     //
{0x0F120300},	//	#REG_0TC_CCFG_uBpp88             //
{0x0F120042},	//	#REG_0TC_CCFG_PVIMask            //
{0x0F120050},	//	#REG_0TC_CCFG_OIFMask            //
{0x0F1203C0},	//	#REG_0TC_CCFG_usJpegPacketSize   //
{0x0F120D00},	//	#REG_0TC_CCFG_usJpegTotalPackets //
{0x0F120001},	//	#REG_0TC_CCFG_uClockInd          //
{0x0F120000},	//	#REG_0TC_CCFG_usFrTimeType       //
{0x0F120002},	//	#REG_0TC_CCFG_FrRateQualityType  //
{0x0F120535},	//	#REG_0TC_CCFG_usMaxFrTimeMsecMult10         //
{0x0F12029A},	//	#REG_0TC_CCFG_usMinFrTimeMsecMult10         //
                                                                      
{0x002A03C2},
{0x0F120001},	//	#REG_1TC_CCFG_uCaptureMode									//
{0x0F120A00},	//	#REG_1TC_CCFG_usWidth            //
{0x0F120780},	//	#REG_1TC_CCFG_usHeight           //
{0x0F120005},	//	#REG_1TC_CCFG_Format             //
{0x0F124F1A},	//	#REG_1TC_CCFG_usMaxOut4KHzRate   //
{0x0F124F1A},	//	#REG_1TC_CCFG_usMinOut4KHzRate   //
{0x0F120100},	//	#REG_1TC_CCFG_OutClkPerPix88     //
{0x0F120300},	//	#REG_1TC_CCFG_uBpp88             //
{0x0F120052},	//	#REG_1TC_CCFG_PVIMask            //
{0x0F120000},	//	#REG_1TC_CCFG_OIFMask            //
{0x0F1201E0},	//	#REG_1TC_CCFG_usJpegPacketSize   //
{0x0F120000},	//	#REG_1TC_CCFG_usJpegTotalPackets //
{0x0F120001},	//	#REG_1TC_CCFG_uClockInd          //
{0x0F120000},	//	#REG_1TC_CCFG_usFrTimeType       //
{0x0F120002},	//	#REG_1TC_CCFG_FrRateQualityType  //
{0x0F120AD0},	//	#REG_1TC_CCFG_usMaxFrTimeMsecMult10         //
{0x0F12029A},	//	#REG_1TC_CCFG_usMinFrTimeMsecMult10         //
                                                                      
{0x002A0250},
{0x0F120A00},	//	#REG_TC_GP_PrevReqInputWidth		//
{0x0F120780},	//	#REG_TC_GP_PrevReqInputHeight  //
{0x0F120010},	//	#REG_TC_GP_PrevInputWidthOfs   //
{0x0F12000C},	//	#REG_TC_GP_PrevInputHeightOfs  //
{0x0F120A00},	//	#REG_TC_GP_CapReqInputWidth    //
{0x0F120780},	//	#REG_TC_GP_CapReqInputHeight   //
{0x0F120010},	//	#REG_TC_GP_CapInputWidthOfs    //
{0x0F12000C},	//	#REG_TC_GP_CapInputHeightOfs   //
{0x002A0494},
{0x0F120A00},	//	#REG_TC_PZOOM_PrevZoomReqInputWidth    	//
{0x0F120780},	//	#REG_TC_PZOOM_PrevZoomReqInputHeight   	//
{0x0F120000},	//	#REG_TC_PZOOM_PrevZoomReqInputWidthOfs 	//
{0x0F120000},	//	#REG_TC_PZOOM_PrevZoomReqInputHeightOfs	//
{0x0F120A00},	//	#REG_TC_PZOOM_CapZoomReqInputWidth     	//
{0x0F120780},	//	#REG_TC_PZOOM_CapZoomReqInputHeight    	//
{0x0F120000},	//	#REG_TC_PZOOM_CapZoomReqInputWidthOfs  	//
{0x0F120000},	//	#REG_TC_PZOOM_CapZoomReqInputHeightOfs 	//
                                                                      
{0x002A0262},
{0x0F120001},	//	#REG_TC_GP_bUseReqInputInPre   	//
{0x0F120001},	//	#REG_TC_GP_bUseReqInputInCap   	//
                                                                      
{0x002A0266},
{0x0F120000},	//	#REG_TC_GP_ActivePrevConfig    	//
{0x002A026A},
{0x0F120001},	//	#REG_TC_GP_PrevOpenAfterChange 	//
{0x002A024E},
{0x0F120001},	//	#REG_TC_GP_NewConfigSync       	//
{0x002A0268},
{0x0F120001},	//	#REG_TC_GP_PrevConfigChanged   	//
{0x002A0270},
{0x0F120001},	//	#REG_TC_GP_CapConfigChanged    	//
{0x002A023E},
{0x0F120001},	//	#REG_TC_GP_EnablePreview       	//
{0x0F120001},	//	#REG_TC_GP_EnablePreviewChanged	//
};

//======================================================================================================//

s5k4ecgx_short_t s5k4ecgx_init_reg1[] = {
{0xFCFCD000},
{0x00040000},
{0xFCFCD000},
{0x00100001}, //Reset
{0xFCFCD000},
{0x10300000}, //Clear host interrupt so main will wait
{0x00140001}
              //delay 10ms
};

s5k4ecgx_short_t s5k4ecgx_init_reg2[] = {
              // This register is for FACTORY ONLY. If you change it without prior notification//
              // YOU are RESPONSIBLE for the FAILURE that will happen in the future//                  
{0x007A0000},
{0xE4060092},
{0xE4103804},
{0xE4200003},
{0xE4220060},
{0xE42E0004},
{0xF4005A3C},
{0xF4020023},
{0xF4048080},
{0xF40603AF},
{0xF408000A},
{0xF40AAA54},
{0xF40C0040},
{0xF40E464E},
{0xF4100240},
{0xF4120240},
{0xF4140040},
{0xF4161000},
{0xF4185558},
{0xF41AD000},
{0xF41C0010},
{0xF41E0202},
{0xF4200401},
{0xF4220022},
{0xF4240088},
{0xF426009F},
{0xF4280000},
{0xF42A1800},
{0xF42C0088},
{0xF42E0000},
{0xF4302428},
{0xF4320000},
{0xF43403EE},
{0xF4360000},
{0xF4380000},
{0xF43A0000},
{0xF4800004},
{0xF48205B6},
{0xF4840000},
{0xF4860000},
{0xF4880001},
{0xF48A05BA},
{0xF48C0000},
{0xF48E0000},
{0xF4900007},
{0xF49205BA},
{0xF4940000},
{0xF4960000},
{0xF49801F4},
{0xF49A024E},
{0xF49C0000},
{0xF49E0000},
{0xF4A001F4},
{0xF4A205B6},
{0xF4A40000},
{0xF4A60000},
{0xF4A801F4},
{0xF4AA05BA},
{0xF4AC0000},
{0xF4AE0000},
{0xF4B001F4},
{0xF4B2024F},
{0xF4B40000},
{0xF4B60000},
{0xF4B80000},
{0xF4BA0000},
{0xF4BC0000},
{0xF4BE0000},
{0xF4C00075},
{0xF4C200CF},
{0xF4C40000},
{0xF4C60000},
{0xF4C80075},
{0xF4CA00D6},
{0xF4CC0000},
{0xF4CE0000},
{0xF4D00004},
{0xF4D201F4},
{0xF4D40000},
{0xF4D60000},
{0xF4D800F0},
{0xF4DA01F4},
{0xF4DC029E},
{0xF4DE05B2},
{0xF4E00000},
{0xF4E20000},
{0xF4E40000},
{0xF4E60000},
{0xF4E801F8},
{0xF4EA0228},
{0xF4EC0000},
{0xF4EE0000},
{0xF4F00000},
{0xF4F20000},
{0xF4F40208},
{0xF4F60238},
{0xF4F80000},
{0xF4FA0000},
{0xF4FC0000},
{0xF5900000},
{0xF5000218},
{0xF5020238},
{0xF5040000},
{0xF5060000},
{0xF5080000},
{0xF50A0000},
{0xF50C0001},
{0xF50E0009},
{0xF51000DE},
{0xF51205C0},
{0xF5140000},
{0xF5160000},
{0xF51800DF},
{0xF51A00E4},
{0xF51C01F8},
{0xF51E01FD},
{0xF52005B6},
{0xF52205BB},
{0xF5240000},
{0xF5260000},
{0xF5280000},
{0xF52A0000},
{0xF52C0000},
{0xF52E0000},
{0xF5300000},
{0xF5320000},
{0xF5340000},
{0xF5360000},
{0xF5380000},
{0xF53A0000},
{0xF53C01F8},
{0xF53E0000},
{0xF5400000},
{0xF5420077},
{0xF544007E},
{0xF546024F},
{0xF548025E},
{0xF54A0000},
{0xF54C0000},
{0xF54E0000},
{0xF5500000},
{0xF5520708},
{0xF554080C},

{0x002A1082},
{0x0F125555},
{0x0F125555},
{0x002A1088},
{0x0F12055D},
{0x002A100E},
{0x0F120000},

{0x00287000},
{0x002A0716},
{0x0F120100},

              // Start of Patch data
{0x00287000},
{0x002A3A10},
{0x0F12B5F8},
{0x0F124A3E},
{0x0F12493E},
{0x0F12483F},
{0x0F12C004},
{0x0F126001},
{0x0F124C3E},
{0x0F122500},
{0x0F128265},
{0x0F128025},
{0x0F12493D},
{0x0F12483E},
{0x0F122701},
{0x0F12002A},
{0x0F12F000},
{0x0F12FC38},
{0x0F12493C},
{0x0F12483D},
{0x0F122602},
{0x0F12003A},
{0x0F12F000},
{0x0F12FC32},
{0x0F12493B},
{0x0F12483C},
{0x0F120032},
{0x0F122703},
{0x0F12F000},
{0x0F12FC2C},
{0x0F128225},
{0x0F12493A},
{0x0F12483A},
{0x0F122604},
{0x0F12003A},
{0x0F12F000},
{0x0F12FC25},
{0x0F12200E},
{0x0F128420},
{0x0F122701},
{0x0F1283E7},
{0x0F124937},
{0x0F124837},
{0x0F120032},
{0x0F122405},
{0x0F12F000},
{0x0F12FC1B},
{0x0F124936},
{0x0F124836},
{0x0F122606},
{0x0F120022},
{0x0F12F000},
{0x0F12FC15},
{0x0F124C28},
{0x0F123460},
{0x0F1281E7},
{0x0F124825},
{0x0F123824},
{0x0F1286C5},
{0x0F124932},
{0x0F124832},
{0x0F120032},
{0x0F122707},
{0x0F12F000},
{0x0F12FC09},
{0x0F124931},
{0x0F124831},
{0x0F122608},
{0x0F12003A},
{0x0F12F000},
{0x0F12FC03},
{0x0F124930},
{0x0F124830},
{0x0F120032},
{0x0F122709},
{0x0F12F000},
{0x0F12FBFD},
{0x0F122005},
{0x0F128160},
{0x0F12492E},
{0x0F12482E},
{0x0F126281},
{0x0F128225},
{0x0F128265},
{0x0F12482D},
{0x0F128320},
{0x0F12482D},
{0x0F128360},
{0x0F120270},
{0x0F1283A0},
{0x0F122005},
{0x0F120300},
{0x0F1283E0},
{0x0F124828},
{0x0F12492A},
{0x0F123840},
{0x0F126001},
{0x0F12492A},
{0x0F12482A},
{0x0F12240A},
{0x0F12003A},
{0x0F12F000},
{0x0F12FBE3},
{0x0F124929},
{0x0F124829},
{0x0F120022},
{0x0F12250B},
{0x0F12F000},
{0x0F12FBDD},
{0x0F124820},
{0x0F124927},
{0x0F123080},
{0x0F126381},
{0x0F124927},
{0x0F124827},
{0x0F12240C},
{0x0F12002A},
{0x0F12F000},
{0x0F12FBD3},
{0x0F124926},
{0x0F124826},
{0x0F120022},
{0x0F12F000},
{0x0F12FBCE},
{0x0F12BCF8},
{0x0F12BC08},
{0x0F124718},
{0x0F120000},
{0x0F120174},
{0x0F124EC1},
{0x0F12FFFE},
{0x0F120000},
{0x0F121EF0},
{0x0F127000},
{0x0F124780},
{0x0F127000},
{0x0F123BF3},
{0x0F127000},
{0x0F12A1D9},
{0x0F120000},
{0x0F123B9D},
{0x0F127000},
{0x0F12A0BD},
{0x0F120000},
{0x0F123C8D},
{0x0F127000},
{0x0F12217B},
{0x0F120000},
{0x0F123CE9},
{0x0F127000},
{0x0F12E0DF},
{0x0F120000},
{0x0F123E73},
{0x0F127000},
{0x0F12053B},
{0x0F120000},
{0x0F123D71},
{0x0F127000},
{0x0F12509B},
{0x0F120000},
{0x0F123FF9},
{0x0F127000},
{0x0F12D42F},
{0x0F120000},
{0x0F123EB5},
{0x0F127000},
{0x0F1249D1},
{0x0F120000},
{0x0F123F4F},
{0x0F127000},
{0x0F121E57},
{0x0F120000},
{0x0F124033},
{0x0F127000},
{0x0F1200C0},
{0x0F127000},
{0x0F124E34},
{0x0F120000},
{0x0F127C53},
{0x0F120000},
{0x0F1240BF},
{0x0F127000},
{0x0F1240FB},
{0x0F127000},
{0x0F12F5D7},
{0x0F120000},
{0x0F12406F},
{0x0F127000},
{0x0F12BAB1},
{0x0F120000},
{0x0F124187},
{0x0F127000},
{0x0F124129},
{0x0F127000},
{0x0F12C10D},
{0x0F120000},
{0x0F124203},
{0x0F127000},
{0x0F12B231},
{0x0F120000},
{0x0F12B570},
{0x0F12000C},
{0x0F126820},
{0x0F126865},
{0x0F12F000},
{0x0F12FB84},
{0x0F124BFC},
{0x0F120402},
{0x0F120C12},
{0x0F12819A},
{0x0F1248FB},
{0x0F1289C1},
{0x0F12428A},
{0x0F12D305},
{0x0F124AFA},
{0x0F128986},
{0x0F128852},
{0x0F1242B2},
{0x0F12D300},
{0x0F128199},
{0x0F128801},
{0x0F122900},
{0x0F12D008},
{0x0F1249F7},
{0x0F12002B},
{0x0F126E0A},
{0x0F122105},
{0x0F121C80},
{0x0F12F000},
{0x0F12FB74},
{0x0F126020},
{0x0F12E006},
{0x0F12899A},
{0x0F1248F3},
{0x0F12002B},
{0x0F122105},
{0x0F12F000},
{0x0F12FB6C},
{0x0F126020},
{0x0F126820},
{0x0F12BC70},
{0x0F12BC08},
{0x0F124718},
{0x0F12B5F8},
{0x0F120004},
{0x0F122000},
{0x0F129000},
{0x0F120020},
{0x0F122501},
{0x0F123810},
{0x0F122601},
{0x0F1240A5},
{0x0F124086},
{0x0F124FEA},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F1243A8},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F1243B0},
{0x0F128078},
{0x0F12F000},
{0x0F12FB59},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F124328},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F124330},
{0x0F128078},
{0x0F1248DA},
{0x0F122105},
{0x0F128982},
{0x0F1248DD},
{0x0F12466B},
{0x0F12F000},
{0x0F12FB41},
{0x0F121C41},
{0x0F124CD7},
{0x0F120049},
{0x0F120040},
{0x0F121909},
{0x0F121900},
{0x0F12466B},
{0x0F128A89},
{0x0F128A80},
{0x0F12881A},
{0x0F12F000},
{0x0F12FB45},
{0x0F128A61},
{0x0F120540},
{0x0F1202C9},
{0x0F120D40},
{0x0F124301},
{0x0F1248D4},
{0x0F128081},
{0x0F1249D4},
{0x0F1248D4},
{0x0F123120},
{0x0F128BC0},
{0x0F128809},
{0x0F121841},
{0x0F120020},
{0x0F123060},
{0x0F128A82},
{0x0F124291},
{0x0F12D205},
{0x0F128AC0},
{0x0F1249CF},
{0x0F127388},
{0x0F122001},
{0x0F1231A0},
{0x0F1270C8},
{0x0F12BCF8},
{0x0F12BC08},
{0x0F124718},
{0x0F12B5F8},
{0x0F1248C6},
{0x0F122200},
{0x0F1230A0},
{0x0F1281C2},
{0x0F126808},
{0x0F124669},
{0x0F12F000},
{0x0F12FB29},
{0x0F12466B},
{0x0F128818},
{0x0F12F000},
{0x0F12FB2D},
{0x0F120005},
{0x0F12466B},
{0x0F128858},
{0x0F12F000},
{0x0F12FB30},
{0x0F120004},
{0x0F122101},
{0x0F121928},
{0x0F1202C9},
{0x0F121A08},
{0x0F120286},
{0x0F120029},
{0x0F120030},
{0x0F12F000},
{0x0F12FB2E},
{0x0F120005},
{0x0F122701},
{0x0F1202BF},
{0x0F120021},
{0x0F120030},
{0x0F12F000},
{0x0F12FB27},
{0x0F1249B5},
{0x0F124AB8},
{0x0F123140},
{0x0F123220},
{0x0F12808D},
{0x0F128295},
{0x0F1280CF},
{0x0F1282D7},
{0x0F128108},
{0x0F128310},
{0x0F12E7CE},
{0x0F126808},
{0x0F120400},
{0x0F120C00},
{0x0F126849},
{0x0F120409},
{0x0F120C09},
{0x0F124AAA},
{0x0F128A12},
{0x0F122A00},
{0x0F12D00D},
{0x0F122300},
{0x0F121A89},
{0x0F12D400},
{0x0F12000B},
{0x0F120419},
{0x0F120C09},
{0x0F1223FF},
{0x0F1233C1},
{0x0F121810},
{0x0F124298},
{0x0F12D800},
{0x0F120003},
{0x0F120418},
{0x0F120C00},
{0x0F124AA9},
{0x0F128150},
{0x0F128191},
{0x0F124770},
{0x0F12B5F8},
{0x0F122400},
{0x0F124DA7},
{0x0F124F9E},
{0x0F1248A7},
{0x0F128C39},
{0x0F128041},
{0x0F122101},
{0x0F128001},
{0x0F12F000},
{0x0F12FAFB},
{0x0F1248A5},
{0x0F128BC0},
{0x0F12F000},
{0x0F12FAFF},
{0x0F12260D},
{0x0F120736},
{0x0F122000},
{0x0F1200E1},
{0x0F1219CA},
{0x0F120041},
{0x0F12194B},
{0x0F12199B},
{0x0F12881B},
{0x0F121851},
{0x0F12844B},
{0x0F121C40},
{0x0F120400},
{0x0F120C00},
{0x0F122804},
{0x0F12D3F4},
{0x0F123508},
{0x0F12042D},
{0x0F120C2D},
{0x0F121C64},
{0x0F120424},
{0x0F120C24},
{0x0F122C07},
{0x0F12D3E9},
{0x0F12E78A},
{0x0F12B5F0},
{0x0F12B087},
{0x0F126808},
{0x0F129006},
{0x0F126848},
{0x0F120405},
{0x0F120C2D},
{0x0F126888},
{0x0F120403},
{0x0F120C1B},
{0x0F124892},
{0x0F128B80},
{0x0F122800},
{0x0F12D100},
{0x0F122300},
{0x0F12001C},
{0x0F124A90},
{0x0F12466E},
{0x0F121E91},
{0x0F121E88},
{0x0F12C607},
{0x0F12498F},
{0x0F120023},
{0x0F122207},
{0x0F120028},
{0x0F12F000},
{0x0F12FAD3},
{0x0F12487E},
{0x0F128BC1},
{0x0F122900},
{0x0F12D030},
{0x0F122100},
{0x0F124888},
{0x0F124A7B},
{0x0F12380A},
{0x0F1288C0},
{0x0F1200C3},
{0x0F12189A},
{0x0F124696},
{0x0F124A86},
{0x0F121C40},
{0x0F12189B},
{0x0F12469C},
{0x0F124B76},
{0x0F1200C0},
{0x0F1218C6},
{0x0F121887},
{0x0F120048},
{0x0F124672},
{0x0F124663},
{0x0F121812},
{0x0F12181B},
{0x0F128C52},
{0x0F128EDB},
{0x0F12435A},
{0x0F120092},
{0x0F120C15},
{0x0F124A6F},
{0x0F121882},
{0x0F12235A},
{0x0F12529D},
{0x0F121833},
{0x0F121838},
{0x0F128C5B},
{0x0F128EC0},
{0x0F124343},
{0x0F120098},
{0x0F120C00},
{0x0F123260},
{0x0F128050},
{0x0F121C49},
{0x0F120409},
{0x0F120C09},
{0x0F122904},
{0x0F12D3E3},
{0x0F124A66},
{0x0F12325A},
{0x0F120013},
{0x0F123308},
{0x0F12E00A},
{0x0F124870},
{0x0F124971},
{0x0F12380A},
{0x0F1288C0},
{0x0F1200C2},
{0x0F121852},
{0x0F123236},
{0x0F121C40},
{0x0F1200C0},
{0x0F121843},
{0x0F123336},
{0x0F122100},
{0x0F124864},
{0x0F123020},
{0x0F124684},
{0x0F124E69},
{0x0F120048},
{0x0F123E0A},
{0x0F128937},
{0x0F125A15},
{0x0F128976},
{0x0F12437D},
{0x0F125A1F},
{0x0F124377},
{0x0F124E65},
{0x0F1219ED},
{0x0F121986},
{0x0F123660},
{0x0F1289F6},
{0x0F124366},
{0x0F1219AD},
{0x0F12022D},
{0x0F120C2D},
{0x0F12AE04},
{0x0F125235},
{0x0F124666},
{0x0F127C76},
{0x0F124375},
{0x0F129E06},
{0x0F12026D},
{0x0F120C2D},
{0x0F125235},
{0x0F121C49},
{0x0F122904},
{0x0F12D3E1},
{0x0F12B007},
{0x0F12BCF0},
{0x0F12BC08},
{0x0F124718},
{0x0F12B5F8},
{0x0F120004},
{0x0F12F7FF},
{0x0F12FF53},
{0x0F122101},
{0x0F12000D},
{0x0F120020},
{0x0F123810},
{0x0F124081},
{0x0F1240A5},
{0x0F124F4A},
{0x0F12000E},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F1243A8},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F1243B0},
{0x0F128078},
{0x0F12F000},
{0x0F12FA5E},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F124328},
{0x0F128038},
{0x0F12E6EC},
{0x0F128878},
{0x0F124330},
{0x0F128078},
{0x0F12E6E8},
{0x0F12B5F8},
{0x0F120004},
{0x0F124F48},
{0x0F124949},
{0x0F1278FA},
{0x0F122001},
{0x0F122A00},
{0x0F12D102},
{0x0F122000},
{0x0F1286C8},
{0x0F12E003},
{0x0F127AFA},
{0x0F122A00},
{0x0F12D000},
{0x0F1286C8},
{0x0F122101},
{0x0F12000D},
{0x0F120020},
{0x0F123810},
{0x0F124081},
{0x0F1240A5},
{0x0F12000E},
{0x0F122C10},
{0x0F12DA04},
{0x0F124932},
{0x0F128808},
{0x0F1243A8},
{0x0F128008},
{0x0F12E003},
{0x0F124930},
{0x0F128848},
{0x0F1243B0},
{0x0F128048},
{0x0F12F000},
{0x0F12FA39},
{0x0F122C10},
{0x0F12DA04},
{0x0F12482C},
{0x0F128801},
{0x0F124329},
{0x0F128001},
{0x0F12E003},
{0x0F124829},
{0x0F128841},
{0x0F124331},
{0x0F128041},
{0x0F124934},
{0x0F128B08},
{0x0F1206C2},
{0x0F12D50A},
{0x0F127ABA},
{0x0F120652},
{0x0F12D507},
{0x0F122210},
{0x0F124390},
{0x0F128308},
{0x0F124830},
{0x0F127AF9},
{0x0F126B00},
{0x0F12F000},
{0x0F12FA27},
{0x0F12481C},
{0x0F123060},
{0x0F1289C0},
{0x0F122800},
{0x0F12D009},
{0x0F1278F8},
{0x0F122800},
{0x0F12D006},
{0x0F127AF8},
{0x0F122800},
{0x0F12D003},
{0x0F127AB8},
{0x0F122140},
{0x0F124308},
{0x0F1272B8},
{0x0F12E69B},
{0x0F12B5F8},
{0x0F120004},
{0x0F124826},
{0x0F128981},
{0x0F122900},
{0x0F12D007},
{0x0F128940},
{0x0F122800},
{0x0F12D104},
{0x0F12481E},
{0x0F1222BF},
{0x0F127A81},
{0x0F124011},
{0x0F127281},
{0x0F122101},
{0x0F12000D},
{0x0F120020},
{0x0F123810},
{0x0F124081},
{0x0F1240A5},
{0x0F124F0E},
{0x0F12000E},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F1243A8},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F1243B0},
{0x0F128078},
{0x0F12F000},
{0x0F12F9FE},
{0x0F122C10},
{0x0F12DA2D},
{0x0F128838},
{0x0F124328},
{0x0F128038},
{0x0F12E674},
{0x0F1221C0},
{0x0F127000},
{0x0F124780},
{0x0F127000},
{0x0F122D00},
{0x0F127000},
{0x0F122AD0},
{0x0F127000},
{0x0F120924},
{0x0F127000},
{0x0F121100},
{0x0F12D000},
{0x0F12E300},
{0x0F12D000},
{0x0F1229D0},
{0x0F127000},
{0x0F122C30},
{0x0F127000},
{0x0F125000},
{0x0F12D000},
{0x0F12A006},
{0x0F120000},
{0x0F12A000},
{0x0F12D000},
{0x0F1206F8},
{0x0F127000},
{0x0F120888},
{0x0F127000},
{0x0F1221DA},
{0x0F127000},
{0x0F1208AC},
{0x0F127000},
{0x0F1220BC},
{0x0F127000},
{0x0F121ECC},
{0x0F127000},
{0x0F122FA4},
{0x0F127000},
{0x0F12235C},
{0x0F127000},
{0x0F120234},
{0x0F127000},
{0x0F128878},
{0x0F124330},
{0x0F128078},
{0x0F12E646},
{0x0F12B570},
{0x0F124D99},
{0x0F124C99},
{0x0F128B28},
{0x0F120701},
{0x0F12D507},
{0x0F122108},
{0x0F124388},
{0x0F128328},
{0x0F124997},
{0x0F126B20},
{0x0F1268C9},
{0x0F12F000},
{0x0F12F9C4},
{0x0F128B28},
{0x0F1206C1},
{0x0F12D50A},
{0x0F124994},
{0x0F127A8A},
{0x0F120652},
{0x0F12D406},
{0x0F122210},
{0x0F124390},
{0x0F128328},
{0x0F127AC9},
{0x0F126B20},
{0x0F12F000},
{0x0F12F9A6},
{0x0F12E5DC},
{0x0F12B570},
{0x0F124D8E},
{0x0F124C8F},
{0x0F1288EA},
{0x0F122A14},
{0x0F12D101},
{0x0F122200},
{0x0F1281A2},
{0x0F12F000},
{0x0F12F9B3},
{0x0F1288E8},
{0x0F122821},
{0x0F12D10F},
{0x0F128B28},
{0x0F122800},
{0x0F12D10C},
{0x0F12200C},
{0x0F125E20},
{0x0F128961},
{0x0F124288},
{0x0F12DC07},
{0x0F124882},
{0x0F123880},
{0x0F126B80},
{0x0F12F000},
{0x0F12F9AB},
{0x0F1289A0},
{0x0F121C40},
{0x0F1281A0},
{0x0F12E5BE},
{0x0F12B5F8},
{0x0F120004},
{0x0F122101},
{0x0F12000D},
{0x0F120020},
{0x0F123810},
{0x0F124081},
{0x0F1240A5},
{0x0F124F7E},
{0x0F12000E},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F1243A8},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F1243B0},
{0x0F128078},
{0x0F12F000},
{0x0F12F99A},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F124328},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F124330},
{0x0F128078},
{0x0F124874},
{0x0F128800},
{0x0F120400},
{0x0F12D504},
{0x0F12F000},
{0x0F12F993},
{0x0F12496E},
{0x0F122012},
{0x0F1280C8},
{0x0F12E5E3},
{0x0F12B570},
{0x0F124E6A},
{0x0F128881},
{0x0F1278F2},
{0x0F124D6E},
{0x0F124C6A},
{0x0F122A00},
{0x0F12D005},
{0x0F128A62},
{0x0F121889},
{0x0F128081},
{0x0F128B61},
{0x0F128029},
{0x0F12E004},
{0x0F128A22},
{0x0F121889},
{0x0F128081},
{0x0F128B21},
{0x0F128029},
{0x0F12F000},
{0x0F12F982},
{0x0F1278F0},
{0x0F122800},
{0x0F12D002},
{0x0F128BE0},
{0x0F1282E8},
{0x0F12E57B},
{0x0F128BA0},
{0x0F1282E8},
{0x0F12E578},
{0x0F12B430},
{0x0F12680B},
{0x0F12684D},
{0x0F12688C},
{0x0F1268C8},
{0x0F124A5F},
{0x0F128054},
{0x0F124958},
{0x0F1278CC},
{0x0F124959},
{0x0F122C00},
{0x0F12D003},
{0x0F128A49},
{0x0F121808},
{0x0F128090},
{0x0F12E002},
{0x0F128A09},
{0x0F121808},
{0x0F128090},
{0x0F1280D3},
{0x0F128115},
{0x0F12BC30},
{0x0F124770},
{0x0F12B5F3},
{0x0F120004},
{0x0F12B081},
{0x0F129802},
{0x0F126800},
{0x0F120600},
{0x0F120E00},
{0x0F122201},
{0x0F120015},
{0x0F120021},
{0x0F123910},
{0x0F12408A},
{0x0F1240A5},
{0x0F124F4D},
{0x0F120016},
{0x0F122C10},
{0x0F12DA03},
{0x0F128839},
{0x0F1243A9},
{0x0F128039},
{0x0F12E002},
{0x0F128879},
{0x0F1243B1},
{0x0F128079},
{0x0F12F000},
{0x0F12F950},
{0x0F122C10},
{0x0F12DA03},
{0x0F128839},
{0x0F124329},
{0x0F128039},
{0x0F12E002},
{0x0F128879},
{0x0F124331},
{0x0F128079},
{0x0F124946},
{0x0F128809},
{0x0F122900},
{0x0F12D102},
{0x0F12F000},
{0x0F12F949},
{0x0F122000},
{0x0F129902},
{0x0F126008},
{0x0F12BCFE},
{0x0F12BC08},
{0x0F124718},
{0x0F12B538},
{0x0F124C40},
{0x0F1289E5},
{0x0F12F000},
{0x0F12F946},
{0x0F121FE8},
{0x0F1238FD},
{0x0F12D132},
{0x0F1289E0},
{0x0F121FC1},
{0x0F1239FF},
{0x0F12D12E},
{0x0F12483C},
{0x0F1269E1},
{0x0F126840},
{0x0F121809},
{0x0F120200},
{0x0F12F000},
{0x0F12F8BA},
{0x0F120400},
{0x0F120C00},
{0x0F124A38},
{0x0F122305},
{0x0F120011},
{0x0F123114},
{0x0F12F000},
{0x0F12F938},
{0x0F120002},
{0x0F1266E0},
{0x0F124D34},
{0x0F128CE0},
{0x0F123D14},
{0x0F1289E9},
{0x0F12F000},
{0x0F12F88A},
{0x0F12466B},
{0x0F128018},
{0x0F128A29},
{0x0F128D20},
{0x0F126EE2},
{0x0F12F000},
{0x0F12F883},
{0x0F12466B},
{0x0F128058},
{0x0F120021},
{0x0F129800},
{0x0F123170},
{0x0F12F000},
{0x0F12F92A},
{0x0F120020},
{0x0F123060},
{0x0F128A02},
{0x0F124928},
{0x0F123980},
{0x0F12808A},
{0x0F128A42},
{0x0F1280CA},
{0x0F128A80},
{0x0F128108},
{0x0F12BC38},
{0x0F12BC08},
{0x0F124718},
{0x0F12B5F8},
{0x0F120004},
{0x0F126808},
{0x0F120400},
{0x0F120C00},
{0x0F122201},
{0x0F120015},
{0x0F120021},
{0x0F123910},
{0x0F12408A},
{0x0F1240A5},
{0x0F124F17},
{0x0F120016},
{0x0F122C10},
{0x0F12DA03},
{0x0F128839},
{0x0F1243A9},
{0x0F128039},
{0x0F12E002},
{0x0F128879},
{0x0F1243B1},
{0x0F128079},
{0x0F12F000},
{0x0F12F90D},
{0x0F122C10},
{0x0F12DA03},
{0x0F128838},
{0x0F124328},
{0x0F128038},
{0x0F12E002},
{0x0F128878},
{0x0F124330},
{0x0F128078},
{0x0F12480D},
{0x0F128800},
{0x0F120400},
{0x0F12D507},
{0x0F124B12},
{0x0F127819},
{0x0F124A12},
{0x0F127810},
{0x0F127018},
{0x0F127011},
{0x0F124905},
{0x0F128188},
{0x0F12E513},
{0x0F120000},
{0x0F122FA4},
{0x0F127000},
{0x0F12235C},
{0x0F127000},
{0x0F120140},
{0x0F127000},
{0x0F1220BC},
{0x0F127000},
{0x0F122DF0},
{0x0F127000},
{0x0F1247E0},
{0x0F127000},
{0x0F121100},
{0x0F12D000},
{0x0F122EE2},
{0x0F127000},
{0x0F12F400},
{0x0F12D000},
{0x0F123200},
{0x0F12D000},
{0x0F1216DE},
{0x0F127000},
{0x0F1236F8},
{0x0F127000},
{0x0F122B90},
{0x0F127000},
{0x0F1217B4},
{0x0F127000},
{0x0F122EDD},
{0x0F127000},
{0x0F122EDE},
{0x0F127000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F1213D5},
{0x0F120001},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12A083},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12A035},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12A1D9},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F122D27},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F127D47},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F127AB1},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F127ACB},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12F004},
{0x0F12E51F},
{0x0F122630},
{0x0F120001},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12ED4D},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12EDDB},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F124EB5},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12053B},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F1249D1},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12D411},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F121E57},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F122603},
{0x0F120001},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12BC3D},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F122601},
{0x0F120001},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12BAB1},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12B89F},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12F077},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12C10D},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12C0C9},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12EAF9},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F122E61},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12E86B},
{0x0F120000},
{0x0F124778},
{0x0F1246C0},
{0x0F12C000},
{0x0F12E59F},
{0x0F12FF1C},
{0x0F12E12F},
{0x0F12B231},
{0x0F120000},

{0x10000001},

{0x002A479E},
{0x0F120000},

{0x002A1432},
{0x0F120000},  // awbb_otp_disable							0x70001432	// 0x0001

{0x002A47EE},
{0x0F120000},
{0x0F12000A},
{0x0F120014},
{0x0F120070},
{0x0F120005},
{0x0F125A3C},

{0x002A4780},
{0x0F120000}, //TNP_Regs_AFIT_bUseNB_Afit
{0x0F120014}, //TNP_Regs_AFIT_usNBIndex_0_
{0x0F1200D2}, //TNP_Regs_AFIT_usNBIndex_1_
{0x0F120384}, //TNP_Regs_AFIT_usNBIndex_2_
{0x0F1207D0}, //TNP_Regs_AFIT_usNBIndex_3_
{0x0F121388}, //TNP_Regs_AFIT_usNBIndex_4_

{0x002A478C},
{0x0F120180}, //TNP_Regs_AFIT_NIContrastTh
{0x0F120196}, //TNP_Regs_AFIT_NIContrastAFITValue
{0x0F120054}, //TNP_Regs_usUserMBCV
{0x0F120001}, //TNP_Regs_bUseSenBpr
{0x0F1201CC}, //TNP_Regs_usBprThr_0_
{0x0F1201CC}, //TNP_Regs_usBprThr_1_
{0x0F1201CC}, //TNP_Regs_usBprThr_2_
{0x0F1201CC}, //TNP_Regs_usBprThr_3_
{0x0F1201CC}, //TNP_Regs_usBprThr_4_

{0x002A0EF0},
{0x0F120001}, //AFC_Default60Hz
{0x002A0EF6},
{0x0F120002}, //AFC_D_ConvAccelerPower

{0x002A1A84},
{0x0F12001C}, //senHal_bExtraAddLine

{0x00287000},
{0x002A01F8},  
{0x0F120000},  // REG_TC_IPRM_LedGpio							0x700001F8	// 0x0001
               // 0x002A16E4
               // 0x0F120100  // afd_usFlags									0x700016E4	// 0x0000
{0x002A01FA},
{0x0F120003},  // REG_TC_IPRM_CM_Init_AfModeType				0x700001FA	// 0x0000 
{0x0F120000},  // REG_TC_IPRM_CM_Init_PwmConfig1				0x700001FC	// 0x0000 
{0x002A0200},
{0x0F120061},  //REG_TC_IPRM_CM_Init_GpioConfig1
{0x002A0208},
{0x0F122F0C},
{0x0F120190},
{0x002A028E},
{0x0F120100},  //REG_TC_AF_FstWinStartX
{0x0F1200E3},  //REG_TC_AF_FstWinStartY
{0x0F120200},  //REG_TC_AF_FstWinSizeX
{0x0F120238},  //REG_TC_AF_FstWinSizeY
{0x0F1201C6},  //REG_TC_AF_ScndWinStartX
{0x0F120166},  //REG_TC_AF_ScndWinStartY
{0x0F120074},  //REG_TC_AF_ScndWinSizeX
{0x0F120132},  //REG_TC_AF_ScndWinSizeY
{0x0F120001},  //REG_TC_AF_WinSizesUpdated

{0x002A0702},
{0x0F1200FF},
{0x002A1600},
{0x0F120000},
{0x002A0712},
{0x0F120001},

{0x002A160C},
{0x0F129002},
{0x002A1616},
{0x0F120003},
{0x002A15A4},
{0x0F121301},
{0x002A1618},
{0x0F120000},

{0x002A1602},
{0x0F1200D8},
{0x0F120098},

{0x002A1598},
{0x0F120000},
{0x0F12D000},

{0x002A165E},
{0x0F12FF95},
{0x002A162E},
{0x0F120280},
{0x002A163A},
{0x0F1203A0},
{0x0F120320},

{0x002A1680},
{0x0F120030},

{0x002A16A4},
{0x0F120060},
{0x002A1698},
{0x0F120010},

{0x002A161A},
{0x0F120000},

{0x002A15AA},
{0x0F12003C},

{0x002A15AC},
{0x0F120017},
{0x0F120016},
{0x0F12001E},
{0x0F120026},
{0x0F12002E},
{0x0F120036},
{0x0F12003E},
{0x0F120046},
{0x0F12004E},
{0x0F120056},
{0x0F12005E},
{0x0F120066},
{0x0F12006E},
{0x0F120076},
{0x0F12007E},
{0x0F120086},
{0x0F12008E},
{0x0F120096},
{0x0F12009E},
{0x0F1200A6},
{0x0F1200AE},
{0x0F1200B6},
{0x0F1200BE},
{0x0F1200C6},
{0x0F1200CE},

{0x002A16E6},
{0x0F128000},
{0x0F120006},
{0x0F123FF0},
{0x0F1203E8},
{0x0F120000},
{0x0F120100},
{0x0F120009},
{0x0F120020},
{0x0F120040},
{0x0F120080},
{0x0F1200C0},
{0x0F1200E0},

{0x002A0286},
{0x0F120003},

{0x002A11B4},
{0x0F12012C},
{0x0F120121},

{0x002A1A00},
{0x0F12192E},
{0x0F127000},

{0x002A185C},
{0x0F120004},
{0x0F1209D1},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x0F1209D5},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F1209D5},
{0x0F120000},
{0x0F120000},
{0x0F1202AA},
{0x0F120326},
{0x0F120000},
{0x0F120000},
{0x0F1202AA},
{0x0F1209D1},
{0x0F120000},
{0x0F120000},
{0x0F1202AA},
{0x0F1209D5},
{0x0F120000},
{0x0F120000},
{0x0F1202AA},
{0x0F120327},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F120084},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F12008D},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F1202AA},
{0x0F120000},
{0x0F120000},
{0x0F1200AA},
{0x0F1202AA},
{0x0F1203AD},
{0x0F1209CD},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1202AE},
{0x0F1202DE},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1202BE},
{0x0F1202EE},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1202CE},
{0x0F1202EE},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x0F120009},
{0x0F120095},
{0x0F1209DB},
{0x0F120000},
{0x0F120000},
{0x0F120096},
{0x0F12009B},
{0x0F1202AE},
{0x0F1202B3},
{0x0F1209D1},
{0x0F1209D6},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1202AE},
{0x0F120000},
{0x0F120000},
{0x0F120009},
{0x0F120010},
{0x0F120327},
{0x0F120336},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},

{0x0F120004},
{0x0F1205B6},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x0F1205BA},
{0x0F120000},
{0x0F120000},
{0x0F120007},
{0x0F1205BA},
{0x0F120000},
{0x0F120000},
{0x0F1201F4},
{0x0F12024E},
{0x0F120000},
{0x0F120000},
{0x0F1201F4},
{0x0F1205B6},
{0x0F120000},
{0x0F120000},
{0x0F1201F4},
{0x0F1205BA},
{0x0F120000},
{0x0F120000},
{0x0F1201F4},
{0x0F12024F},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120075},
{0x0F1200CF},
{0x0F120000},
{0x0F120000},
{0x0F120075},
{0x0F1200D6},
{0x0F120000},
{0x0F120000},
{0x0F120004},
{0x0F1201F4},
{0x0F120000},
{0x0F120000},
{0x0F1200F0},
{0x0F1201F4},
{0x0F12029E},
{0x0F1205B2},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1201F8},
{0x0F120228},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120208},
{0x0F120238},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120218},
{0x0F120238},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x0F120009},
{0x0F1200DE},
{0x0F1205C0},
{0x0F120000},
{0x0F120000},
{0x0F1200DF},
{0x0F1200E4},
{0x0F1201F8},
{0x0F1201FD},
{0x0F1205B6},
{0x0F1205BB},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1201F8},
{0x0F120000},
{0x0F120000},
{0x0F120077},
{0x0F12007E},
{0x0F12024F},
{0x0F12025E},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},

{0x002A1836},
{0x0F120002},
{0x0F120000},
{0x0F120003},

{0x002A183E},
{0x0F120FB0},

{0x002A184C},
{0x0F120060},
{0x0F120060},
{0x0F1205C0},
{0x0F1205C0},

{0x002A1A8A},
{0x0F128080},
{0x0F120080},
{0x002A1A80},
{0x0F120000},

{0x002A1A12},
{0x0F120000},
{0x002A1842},
{0x0F120004},
{0x002A1A0A},
{0x0F12009A},
{0x002A3776},
{0x0F12024C},

{0x002A0EB2},
{0x0F120000},

{0x002A08C6},
{0x0F120000}, // ash_bUseOTPData								0x700008C6	// 0x0000  

{0x002A08A4},
{0x0F120001},

{0x002A08E2},
{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124000},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F124200},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x002A0CF2},  // GAS
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F120000},
{0x0F120000},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F12000F},
{0x0F120000},
{0x0F120F0F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F120F0F},
{0x0F12000F},
{0x0F120F0F},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F120F00},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F12000F},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F120000},
{0x0F120000},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F12000F},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},


{0x002A0D82},
{0x0F128127},
{0x0F12F584},
{0x0F12F97B},
{0x0F1208E5},
{0x0F121876},
{0x0F12DB4E},
{0x0F12DDD4},
{0x0F12EDB4},
{0x0F12273C},
{0x0F12CC8A},
{0x0F121B8A},
{0x0F1208D6},
{0x0F12055C},
{0x0F1215AA},
{0x0F12C9E1},
{0x0F124E12},
{0x0F12DD45},
{0x0F12E116},
{0x0F121DFA},
{0x0F12F0AC},
{0x0F12211F},
{0x0F12CDB6},
{0x0F1208D4},
{0x0F1234F3},
{0x0F12D9C3},
{0x0F120940},
{0x0F120139},
{0x0F120CD0},
{0x0F12E7AD},
{0x0F12FA8D},
{0x0F1218C7},
{0x0F12FBB7},
{0x0F12EEA4},
{0x0F12071D},
{0x0F1228F4},
{0x0F12D394},
{0x0F129774},
{0x0F12F0D3},
{0x0F12F6E8},
{0x0F1216EB},
{0x0F1206FF},
{0x0F12E422},
{0x0F12D451},
{0x0F12E966},
{0x0F122925},
{0x0F12C655},
{0x0F122D69},
{0x0F12FA04},
{0x0F1209DC},
{0x0F120ED8},
{0x0F12DEDB},
{0x0F12351B},
{0x0F12DE49},
{0x0F12F0EA},
{0x0F121BF1},
{0x0F12FF60},
{0x0F120C6E},
{0x0F12E384},
{0x0F1209AA},
{0x0F1221D8},
{0x0F12E2F8},
{0x0F12FB54},
{0x0F12FE39},
{0x0F121011},
{0x0F12EEBA},
{0x0F12F633},
{0x0F120EDE},
{0x0F12058F},
{0x0F12F803},
{0x0F120293},
{0x0F12106F},
{0x0F12EE5C},
{0x0F1287AB},
{0x0F12E9B7},
{0x0F120BE4},
{0x0F12ED1A},
{0x0F123576},
{0x0F12CCC9},
{0x0F12D7D7},
{0x0F12F866},
{0x0F121054},
{0x0F12F530},
{0x0F12EF0C},
{0x0F121C61},
{0x0F121297},
{0x0F120EDC},
{0x0F12DD9C},
{0x0F12220F},
{0x0F120B19},
{0x0F12D716},
{0x0F120C5C},
{0x0F12EB63},
{0x0F121E81},
{0x0F12EAA9},
{0x0F12E606},
{0x0F123263},
{0x0F12EB6D},
{0x0F12164C},
{0x0F12F5C5},
{0x0F12F959},
{0x0F121215},
{0x0F12F025},
{0x0F120DC8},
{0x0F12F290},
{0x0F12F927},
{0x0F12138B},
{0x0F12024C},
{0x0F12EA54},
{0x0F128132},
{0x0F12F39A},
{0x0F12FA43},
{0x0F12091C},
{0x0F12151B},
{0x0F12DFEB},
{0x0F12DE06},
{0x0F12EFCA},
{0x0F1222D7},
{0x0F12D51A},
{0x0F1215E2},
{0x0F12057B},
{0x0F120CE1},
{0x0F120F90},
{0x0F12D2C6},
{0x0F1238B4},
{0x0F12F36A},
{0x0F12E000},
{0x0F1212A2},
{0x0F12F4B8},
{0x0F122216},
{0x0F12D813},
{0x0F12F4B6},
{0x0F1235C1},
{0x0F12E5F8},
{0x0F1208FD},
{0x0F12F39E},
{0x0F120C82},
{0x0F120904},
{0x0F12E2C9},
{0x0F121003},
{0x0F12FE00},
{0x0F12F278},
{0x0F1216D1},
{0x0F12F3C2},
{0x0F12FFDD},  // GAS

{0x002A08E0},
{0x0F120001},

{0x002A1456},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120303},
{0x0F120303},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},

{0x002A1448},
{0x0F12003C},
{0x002A144E},
{0x0F12000F},
{0x002A0580},
{0x0F123520},
{0x0F120000},
{0x0F12C350},
{0x0F120000},
{0x0F123520},
{0x0F120000},
{0x0F12C350},
{0x0F120000},
{0x0F120470},
{0x0F120C00},
{0x0F120100},
{0x0F121000},

{0x002A0538},
{0x0F120111},
{0x0F1200EF},

{0x002A05FC},
{0x0F120000},
{0x0F120001},
{0x0F120600},
{0x0F120100},

{0x0F120001},
{0x0F120000},
{0x002A0608},
{0x0F120A3C},
{0x0F120000},
{0x002A060C},
{0x0F120D04},
{0x0F120000},
{0x002A0610},
{0x0F124008},
{0x0F120000},
{0x002A0614},
{0x0F127000},
{0x0F120000},
{0x002A0618},
{0x0F129C00},
{0x0F120000},
{0x002A061C},
{0x0F12AD00},
{0x0F120001},
{0x002A0620},
{0x0F12F1D4},
{0x0F120002},
{0x002A0624},
{0x0F12DC00},
{0x0F120005},
{0x002A0628},
{0x0F12DC00},
{0x0F120005},

{0x002A062C},
{0x0F120001},
{0x0F120000},
{0x002A0630},
{0x0F120A3C},
{0x0F120000},
{0x002A0634},
{0x0F120D05},
{0x0F120000},
{0x002A0638},
{0x0F123408},
{0x0F120000},
{0x002A063C},
{0x0F123408},
{0x0F120000},
{0x002A0640},
{0x0F126810},
{0x0F120000},
{0x002A0644},
{0x0F128214},
{0x0F120000},
{0x002A0648},
{0x0F12C350},
{0x0F120000},
{0x002A064C},
{0x0F12C350},
{0x0F120000},
{0x002A0650},
{0x0F12C350},
{0x0F120000},

{0x002A0654},
{0x0F120650},
{0x0F120100},

{0x002A06AC},
{0x0F12452C},
{0x0F120004},

{0x002A0280},
{0x0F120001},

{0x002A05C4},
{0x0F120000},

{0x002A0476},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x002A01F4},

{0x0F125DC0},
{0x002A020E},
{0x0F120002},
{0x0F120000},
{0x0F120000},
{0x002A0216},
{0x0F123A98}, // REG_TC_IPRM_sysClocks						0x70000216	// 0x1770
{0x0F124F1A}, // REG_TC_IPRM_MinOutRate4KHz_0				0x70000218	// 0x05DC    
{0x0F124F1A}, // REG_TC_IPRM_MaxOutRate4KHz_0				0x7000021A	// 0x1770    
{0x0F124F1A}, // REG_TC_IPRM_sysClocks_1_					0x7000021C	// 0x1770      
{0x0F124F1A}, // REG_TC_IPRM_MinOutRate4KHz_1				0x7000021E	// 0x1770      
{0x0F124F1A}, // REG_TC_IPRM_MaxOutRate4KHz_1				0x70000220	// 0x2328    
{0x002A0228},    
{0x0F120001},

{0x002A02A0},
{0x0F120280}, // REG_0TC_PCFG_usWidth						0x700002A0	// 0x0A20           
{0x0F1201E0}, // REG_0TC_PCFG_usHeight						0x700002A2	// 0x0798           
{0x0F120005}, // REG_0TC_PCFG_Format							0x700002A4	// 0x0005           
{0x0F124F1A}, // REG_0TC_PCFG_usMaxOut4KHzRate				0x700002A6	// 0xB3B0       
{0x0F124F1A}, // REG_0TC_PCFG_usMinOut4KHzRate				0x700002A8	// 0x05DC       
{0x002A02AE}, 
{0x0F120052}, // REG_0TC_PCFG_PVIMask						0x700002AE	// 0x0042  
{0x002A02B6},   
{0x0F120000}, // REG_0TC_PCFG_uClockInd						0x700002B6	// 0x0000          
{0x0F120000}, // REG_0TC_PCFG_usFrTimeType					0x700002B8	// 0x0000                                                                                                                 
{0x0F120001}, // REG_0TC_PCFG_FrRateQualityType				0x700002BA	// 0x0000                                                                                              
{0x0F12029A}, // REG_0TC_PCFG_usMaxFrTimeMsecMult10			0x700002BC	// 0x1964                                                                                            
{0x0F12014D}, // REG_0TC_PCFG_usMinFrTimeMsecMult10			0x700002BE	// 0x0000                                                                                            
{0x002A02AA}, 
{0x0F120080}, // REG_0TC_PCFG_OutClkPerPix88					0x700002AA	// 0x0100                                                                     
                                                                               
{0x002A024C},
{0x0F120A00},
{0x0F120780},
{0x0F120010},
{0x0F12000C},
{0x0F120A00},
{0x0F120780},
{0x0F120010},
{0x0F12000C},
{0x002A048E},
{0x0F120A00},
{0x0F120780},
{0x0F120000},
{0x0F120000},
{0x0F120A00},
{0x0F120780},
{0x0F120000},
{0x0F120000},

{0x002A025E},
{0x0F120001},
{0x0F120001},

{0x002A0392},
{0x0F120A00}, // REG_0TC_CCFG_usWidth						0x70000392	// 0x0A20   
{0x0F120780}, // REG_0TC_CCFG_usHeight						0x70000394	// 0x0798   
{0x0F120009}, // REG_0TC_CCFG_Format							0x70000396	// 0x0009   
{0x0F124F1A}, // REG_0TC_CCFG_usMaxOut4KHzRate				0x70000398	// 0xB3B0  
{0x0F124F1A}, // REG_0TC_CCFG_usMinOut4KHzRate				0x7000039A	// 0x05DC    
{0x002A03A0},
{0x0F120002},
{0x0F120050}, //REG_0TC_CCFG_OIFMask 
{0x0F120800}, //REG_0TC_CCFG_usJpegPacketSize
{0x0F120600}, //0600 //REG_0TC_CCFG_usJpegTotalPackets
{0x002A03A8},
{0x0F120001},
{0x0F120000},
{0x0F120002},
{0x0F120535},
{0x0F12029A},
{0x002A039C},
{0x0F120080},

{0x002A0476},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},

{0x002A0262},
{0x0F120000},
{0x002A0266},
{0x0F120001},
{0x002A024A},
{0x0F120001},
{0x002A0264},
{0x0F120001},
{0x002A026C},
{0x0F120001},
{0x002A023A},
{0x0F120001},
{0x0F120001},

{0x002A0472},
{0x0F12005F},
{0x0F12005F},


{0x002A0FE0},
{0x0F1203B8},
{0x0F1203CE},
{0x0F120350},
{0x0F1203C4},
{0x0F1202F2},
{0x0F120394},
{0x0F1202C0},
{0x0F120364},
{0x0F12029E},
{0x0F120334},
{0x0F12027C},
{0x0F120312},
{0x0F12025E},
{0x0F1202F2},
{0x0F120246},
{0x0F1202D0},
{0x0F120230},
{0x0F1202B0},
{0x0F120218},
{0x0F12029E},
{0x0F120208},
{0x0F120290},
{0x0F1201F8},
{0x0F120284},
{0x0F1201E8},
{0x0F120276},
{0x0F1201DA},
{0x0F12026A},
{0x0F1201CE},
{0x0F12025E},
{0x0F1201EC},
{0x0F12022E},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},

{0x0F120005},
{0x002A1034},
{0x0F120010},
{0x002A1038},
{0x0F120126},

{0x002A103C},
{0x0F12024A}, //026C
{0x0F120278}, //029A
{0x0F12023A}, //025C
{0x0F120294}, //02B6
{0x0F12022C}, //024E
{0x0F12029E}, //02C0
{0x0F120220}, //0240
{0x0F12029C}, //02BE
{0x0F120218}, //023A
{0x0F120292}, //02B4
{0x0F120214}, //023A
{0x0F12028A}, //02AA
{0x0F120212}, //0240
{0x0F12027C}, //029E
{0x0F120216}, //025C
{0x0F120274}, //0294
{0x0F120228}, //0000
{0x0F120256}, //0000
{0x0F120000}, //0000
{0x0F120000}, //0000
{0x0F120000}, //0000
{0x0F120000}, //0000
{0x0F120000}, //0000
{0x0F120000}, //0000

{0x0F120004},
{0x002A1070},
{0x0F120009}, // awbb_OutdoorGrZones_ZInfo_m_GridSz			0x70001070	// 0x000A
{0x002A1074},
{0x0F120212}, // awbb_OutdoorGrZones_m_Boffs					0x70001074	// 0x0244


{0x002A1078}, // awbb_LowBrGrZones_m_BGrid					0x70001078	// 0x034D      
{0x0F120350}, // awbb_LowBrGrZones_m_BGrid_0_				0x70001078	// 0x034D      
{0x0F120422}, // awbb_LowBrGrZones_m_BGrid_0__m_left			0x70001078	// 0x034D
{0x0F1202C4}, // awbb_LowBrGrZones_m_BGrid_0__m_right		0x7000107A	// 0x045B  
{0x0F120452}, // awbb_LowBrGrZones_m_BGrid_1_				0x7000107C	// 0x02EA      
{0x0F120278}, // awbb_LowBrGrZones_m_BGrid_1__m_left			0x7000107C	// 0x02EA
{0x0F12041C}, // awbb_LowBrGrZones_m_BGrid_1__m_right		0x7000107E	// 0x0445  
{0x0F120230}, // awbb_LowBrGrZones_m_BGrid_2_				0x70001080	// 0x02A4      
{0x0F1203EE}, // awbb_LowBrGrZones_m_BGrid_2__m_left			0x70001080	// 0x02A4
{0x0F1201F0}, // awbb_LowBrGrZones_m_BGrid_2__m_right		0x70001082	// 0x0428  
{0x0F120392}, // awbb_LowBrGrZones_m_BGrid_3_				0x70001084	// 0x0254      
{0x0F1201C0}, // awbb_LowBrGrZones_m_BGrid_3__m_left			0x70001084	// 0x0254
{0x0F120340}, // awbb_LowBrGrZones_m_BGrid_3__m_right		0x70001086	// 0x03FB  
{0x0F120194}, // awbb_LowBrGrZones_m_BGrid_4_				0x70001088	// 0x0207      
{0x0F120302}, // awbb_LowBrGrZones_m_BGrid_4__m_left			0x70001088	// 0x0207
{0x0F12016E}, // awbb_LowBrGrZones_m_BGrid_4__m_right		0x7000108A	// 0x03C7  
{0x0F1202C2}, // awbb_LowBrGrZones_m_BGrid_5_				0x7000108C	// 0x01CF      
{0x0F120148}, // awbb_LowBrGrZones_m_BGrid_5__m_left			0x7000108C	// 0x01CF
{0x0F120286}, // awbb_LowBrGrZones_m_BGrid_5__m_right		0x7000108E	// 0x0365  
{0x0F12018A}, // awbb_LowBrGrZones_m_BGrid_6_				0x70001090	// 0x019E      
{0x0F120242}, // awbb_LowBrGrZones_m_BGrid_6__m_left			0x70001090	// 0x019E
{0x0F120000}, // awbb_LowBrGrZones_m_BGrid_6__m_right		0x70001092	// 0x031A  
{0x0F120000}, // awbb_LowBrGrZones_m_BGrid_7_				0x70001094	// 0x0170      
{0x0F120000}, // awbb_LowBrGrZones_m_BGrid_7__m_left			0x70001094	// 0x0170
{0x0F120000}, // awbb_LowBrGrZones_m_BGrid_7__m_right		0x70001096	// 0x02DB  
             
{0x0F120006},
{0x002A10AC},
{0x0F12000A},
{0x002A10B0},
{0x0F120106},
             
{0x002A10B4},
{0x0F120380},
{0x0F120000},
{0x002A10B8},
{0x0F120168},
{0x0F120000},
{0x002A10BC},
{0x0F122D90},
{0x0F120000},

{0x002A1428},
{0x0F120008},
{0x0F120190},
{0x0F1200A0},

{0x002A11EC},
{0x0F1200C0},
{0x002A11F0},
{0x0F120010},
{0x002A11EE},
{0x0F120010},

{0x002A11CE},
{0x0F1205D5},
{0x002A11D2},
{0x0F120000},
{0x0F120771},
{0x0F1203A4},
{0x0F120036},
{0x0F12002A},

{0x002A08AC},
{0x0F1200C0},
{0x0F1200DF},
{0x0F120100},
{0x0F120125},
{0x0F12015F},
{0x0F12017C},
{0x0F120194},

{0x002A123C},
{0x0F12FEF7},
{0x0F120021},
{0x0F120E74},
{0x0F120E74},
{0x0F12018F},
{0x0F120096},
{0x0F12000E},
{0x002A11E8},
{0x0F120032},
{0x0F12001E},
{0x002A2ABC},
{0x0F120006},

{0x002A1430},
{0x0F120002},

{0x002A140A},
{0x0F1200AB},
{0x0F1200BF},
{0x0F1200D2},
{0x0F120093},
{0x002A13F8},
{0x0F120300},
{0x0F12036E},
{0x0F1203C2},
{0x0F121015},
{0x0F1210E1},
{0x0F121154},
{0x0F1211A8},
{0x0F1211BB},
{0x0F12123B},

{0x002A1368},
{0x0F120000},  // awbb_GridCorr_R_0__0_						0x70001368	// 0xFFFE         
{0x0F120000},  // awbb_GridCorr_R_0__1_						0x7000136A	// 0xFFFE         
{0x0F120000},  // awbb_GridCorr_R_0__2_						0x7000136C	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_0__3_						0x7000136E	// 0x0000         
{0x0F12FFE0},  // awbb_GridCorr_R_0__4_						0x70001370	// 0x0000         
{0x0F120018},  // awbb_GridCorr_R_0__5_						0x70001372	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_1__0_						0x70001374	// 0xFFFD         
{0x0F120000},  // awbb_GridCorr_R_1__1_						0x70001376	// 0xFFFD         
{0x0F120000},  // awbb_GridCorr_R_1__2_						0x70001378	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_1__3_						0x7000137A	// 0x0000         
{0x0F12FFE0},  // awbb_GridCorr_R_1__4_						0x7000137C	// 0x0000         
{0x0F120018},  // awbb_GridCorr_R_1__5_						0x7000137E	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_2__0_						0x70001380	// 0xFFFC         
{0x0F120000},  // awbb_GridCorr_R_2__1_						0x70001382	// 0xFFFC         
{0x0F120000},  // awbb_GridCorr_R_2__2_						0x70001384	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_2__3_						0x70001386	// 0x0000         
{0x0F12FFE0},  // awbb_GridCorr_R_2__4_						0x70001388	// 0x0000         
{0x0F120018},  // awbb_GridCorr_R_2__5_						0x7000138A	// 0x0000         
{0x0F120000},  // awbb_GridCorr_B_0__0_						0x7000138C	// 0x000C           
{0x0F120000},  // awbb_GridCorr_B_0__1_						0x7000138E	// 0x0006         
{0x0F120000},  // awbb_GridCorr_B_0__2_						0x70001390	// 0x0000         
{0x0F120000},  // awbb_GridCorr_B_0__3_						0x70001392	// 0x0000         
{0x0F12FFC0},  // awbb_GridCorr_B_0__4_						0x70001394	// 0x0000         
{0x0F12FEA0},  //56 // awbb_GridCorr_B_0__5_						0x70001396	// 0x0000         
{0x0F120000},  // awbb_GridCorr_B_1__0_						0x70001398	// 0x000C         
{0x0F120000},  // awbb_GridCorr_B_1__1_						0x7000139A	// 0x0006         
{0x0F120000},  // awbb_GridCorr_B_1__2_						0x7000139C	// 0x0000         
{0x0F120000},  // awbb_GridCorr_B_1__3_						0x7000139E	// 0x0000         
{0x0F12FFC0},  // awbb_GridCorr_B_1__4_						0x700013A0	// 0x0000         
{0x0F12FEA0},  // awbb_GridCorr_B_1__5_						0x700013A2	// 0x0000         
{0x0F120000},  // awbb_GridCorr_B_2__0_						0x700013A4	// 0x000C         
{0x0F120000},  // awbb_GridCorr_B_2__1_						0x700013A6	// 0x0006         
{0x0F120000},  // awbb_GridCorr_B_2__2_						0x700013A8	// 0x0000         
{0x0F120000},  // awbb_GridCorr_B_2__3_						0x700013AA	// 0x0000         
{0x0F12FFC0},  // awbb_GridCorr_B_2__4_						0x700013AC	// 0x0000         
{0x0F12FEA0},  // awbb_GridCorr_B_2__5_						0x700013AE	// 0x0000      
         
{0x0F120000},  // awbb_GridCorr_R_Out_0__0_					0x700013B0	// 0xFFFE       
{0x0F120000},  // awbb_GridCorr_R_Out_0__1_					0x700013B2	// 0xFFFE       
{0x0F120000},  // awbb_GridCorr_R_Out_0__2_					0x700013B4	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_0__3_					0x700013B6	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_0__4_					0x700013B8	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_0__5_					0x700013BA	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_1__0_					0x700013BC	// 0xFFFD       
{0x0F120000},  // awbb_GridCorr_R_Out_1__1_					0x700013BE	// 0xFFFD       
{0x0F120000},  // awbb_GridCorr_R_Out_1__2_					0x700013C0	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_1__3_					0x700013C2	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_1__4_					0x700013C4	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_1__5_					0x700013C6	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_2__0_					0x700013C8	// 0xFFFC       
{0x0F120000},  // awbb_GridCorr_R_Out_2__1_					0x700013CA	// 0xFFFC       
{0x0F120000},  // awbb_GridCorr_R_Out_2__2_					0x700013CC	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_2__3_					0x700013CE	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_2__4_					0x700013D0	// 0x0000       
{0x0F120000},  // awbb_GridCorr_R_Out_2__5_					0x700013D2	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__0_					0x700013D4	// 0x000C           
{0x0F120000},  // awbb_GridCorr_B_Out_0__1_					0x700013D6	// 0x0006       
{0x0F120000},  // awbb_GridCorr_B_Out_0__2_					0x700013D8	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__3_					0x700013DA	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__4_					0x700013DC	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__5_					0x700013DE	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__0_					0x700013E0	// 0x000C       
{0x0F120000},  // awbb_GridCorr_B_Out_1__1_					0x700013E2	// 0x0006       
{0x0F120000},  // awbb_GridCorr_B_Out_1__2_					0x700013E4	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__3_					0x700013E6	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__4_					0x700013E8	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__5_					0x700013EA	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_2__0_					0x700013EC	// 0x000C       
{0x0F120000},  // awbb_GridCorr_B_Out_2__1_					0x700013EE	// 0x0006       
{0x0F120000},  // awbb_GridCorr_B_Out_2__2_					0x700013F0	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_2__3_					0x700013F2	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_2__4_					0x700013F4	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_2__5_					0x700013F6	// 0x0000     
                    
{0x002A13FE},        
{0x0F121015},  //  awbb_GridConst_2_0_							0x700013FE	// 0x0F50        
{0x0F12106C},  //  awbb_GridConst_2_1_							0x70001400	// 0x0F94        
{0x0F1210CA},  //  awbb_GridConst_2_2_							0x70001402	// 0x0FD8        
{0x0F121142},  //  awbb_GridConst_2_3_							0x70001404	// 0x103C        
{0x0F1211BB},  //  awbb_GridConst_2_4_							0x70001406	// 0x10C8        
{0x0F12123B},  //  awbb_GridConst_2_5_							0x70001408	// 0x11B8          
                         
{0x0F1200AB},   // awbb_GridCoeff_R_1							0x7000140A	// 0x02C4          
{0x0F1200BF},   // awbb_GridCoeff_B_1							0x7000140C	// 0x02E4          
{0x0F1200D2},   // awbb_GridCoeff_R_2							0x7000140E	// 0x0308          
{0x0F120093},   // awbb_GridCoeff_B_2							0x70001410	// 0x029C     
                    
{0x002A11CC},       
{0x0F120020},       
                    
{0x002A1412},
{0x0F120000}, //R offs
{0x0F12FFE0}, //B offs
{0x0F120000}, //G offs

{0x002A0724},  // SARR_usGammaLutRGBIndoor					0x70000724	// 0x0000    
{0x0F120001},  // SARR_usGammaLutRGBIndoor_0__0_				0x70000724	// 0x0000
{0x0F120005},  // SARR_usGammaLutRGBIndoor_0__1_				0x70000726	// 0x0001
{0x0F12000a},  // SARR_usGammaLutRGBIndoor_0__2_				0x70000728	// 0x0007
{0x0F120016},  // SARR_usGammaLutRGBIndoor_0__3_				0x7000072A	// 0x002D
{0x0F120041},  // SARR_usGammaLutRGBIndoor_0__4_				0x7000072C	// 0x0075
{0x0F1200B6},  // SARR_usGammaLutRGBIndoor_0__5_				0x7000072E	// 0x00E9
{0x0F120128},  // SARR_usGammaLutRGBIndoor_0__6_				0x70000730	// 0x0143
{0x0F120159},  // SARR_usGammaLutRGBIndoor_0__7_				0x70000732	// 0x016C
{0x0F12017D},  // SARR_usGammaLutRGBIndoor_0__8_				0x70000734	// 0x0190
{0x0F1201B7},  // SARR_usGammaLutRGBIndoor_0__9_				0x70000736	// 0x01CC
{0x0F1201E8},  // SARR_usGammaLutRGBIndoor_0__10_				0x70000738	// 0x01FF
{0x0F120214},  // SARR_usGammaLutRGBIndoor_0__11_				0x7000073A	// 0x022A
{0x0F12023B},  // SARR_usGammaLutRGBIndoor_0__12_				0x7000073C	// 0x0252
{0x0F120280},  // SARR_usGammaLutRGBIndoor_0__13_				0x7000073E	// 0x0296
{0x0F1202BB},  // SARR_usGammaLutRGBIndoor_0__14_				0x70000740	// 0x02D6
{0x0F12031C},  // SARR_usGammaLutRGBIndoor_0__15_				0x70000742	// 0x033C
{0x0F120369},  // SARR_usGammaLutRGBIndoor_0__16_				0x70000744	// 0x038D
{0x0F1203A4},  // SARR_usGammaLutRGBIndoor_0__17_				0x70000746	// 0x03D0
{0x0F1203D0},  // SARR_usGammaLutRGBIndoor_0__18_				0x70000748	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBIndoor_0__19_				0x7000074A	// 0x03FF
{0x0F120001},  // SARR_usGammaLutRGBIndoor_1__0_				0x7000074C	// 0x0000
{0x0F120005},  // SARR_usGammaLutRGBIndoor_1__1_				0x7000074E	// 0x0001
{0x0F12000a},  // SARR_usGammaLutRGBIndoor_1__2_				0x70000750	// 0x0007
{0x0F120016},  // SARR_usGammaLutRGBIndoor_1__3_				0x70000752	// 0x002D
{0x0F120041},  // SARR_usGammaLutRGBIndoor_1__4_				0x70000754	// 0x0075
{0x0F1200B6},  // SARR_usGammaLutRGBIndoor_1__5_				0x70000756	// 0x00E9
{0x0F120128},  // SARR_usGammaLutRGBIndoor_1__6_				0x70000758	// 0x0143
{0x0F120159},  // SARR_usGammaLutRGBIndoor_1__7_				0x7000075A	// 0x016C
{0x0F12017D},  // SARR_usGammaLutRGBIndoor_1__8_				0x7000075C	// 0x0190
{0x0F1201B7},  // SARR_usGammaLutRGBIndoor_1__9_				0x7000075E	// 0x01CC
{0x0F1201E8},  // SARR_usGammaLutRGBIndoor_1__10_				0x70000760	// 0x01FF
{0x0F120214},  // SARR_usGammaLutRGBIndoor_1__11_				0x70000762	// 0x022A
{0x0F12023B},  // SARR_usGammaLutRGBIndoor_1__12_				0x70000764	// 0x0252
{0x0F120280},  // SARR_usGammaLutRGBIndoor_1__13_				0x70000766	// 0x0296
{0x0F1202BB},  // SARR_usGammaLutRGBIndoor_1__14_				0x70000768	// 0x02D6
{0x0F12031C},  // SARR_usGammaLutRGBIndoor_1__15_				0x7000076A	// 0x033C
{0x0F120369},  // SARR_usGammaLutRGBIndoor_1__16_				0x7000076C	// 0x038D
{0x0F1203A4},  // SARR_usGammaLutRGBIndoor_1__17_				0x7000076E	// 0x03D0
{0x0F1203D0},  // SARR_usGammaLutRGBIndoor_1__18_				0x70000770	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBIndoor_1__19_				0x70000772	// 0x03FF
{0x0F120001},  // SARR_usGammaLutRGBIndoor_2__0_				0x70000774	// 0x0000
{0x0F120005},  // SARR_usGammaLutRGBIndoor_2__1_				0x70000776	// 0x0001
{0x0F12000a},  // SARR_usGammaLutRGBIndoor_2__2_				0x70000778	// 0x0007
{0x0F120016},  // SARR_usGammaLutRGBIndoor_2__3_				0x7000077A	// 0x002D
{0x0F120041},  // SARR_usGammaLutRGBIndoor_2__4_				0x7000077C	// 0x0075
{0x0F1200B6},  // SARR_usGammaLutRGBIndoor_2__5_				0x7000077E	// 0x00E9
{0x0F120128},  // SARR_usGammaLutRGBIndoor_2__6_				0x70000780	// 0x0143
{0x0F120159},  // SARR_usGammaLutRGBIndoor_2__7_				0x70000782	// 0x016C
{0x0F12017D},  // SARR_usGammaLutRGBIndoor_2__8_				0x70000784	// 0x0190
{0x0F1201B7},  // SARR_usGammaLutRGBIndoor_2__9_				0x70000786	// 0x01CC
{0x0F1201E8},  // SARR_usGammaLutRGBIndoor_2__10_				0x70000788	// 0x01FF
{0x0F120214},  // SARR_usGammaLutRGBIndoor_2__11_				0x7000078A	// 0x022A
{0x0F12023B},  // SARR_usGammaLutRGBIndoor_2__12_				0x7000078C	// 0x0252
{0x0F120280},  // SARR_usGammaLutRGBIndoor_2__13_				0x7000078E	// 0x0296
{0x0F1202BB},  // SARR_usGammaLutRGBIndoor_2__14_				0x70000790	// 0x02D6
{0x0F12031C},  // SARR_usGammaLutRGBIndoor_2__15_				0x70000792	// 0x033C
{0x0F120369},  // SARR_usGammaLutRGBIndoor_2__16_				0x70000794	// 0x038D
{0x0F1203A4},  // SARR_usGammaLutRGBIndoor_2__17_				0x70000796	// 0x03D0
{0x0F1203D0},  // SARR_usGammaLutRGBIndoor_2__18_				0x70000798	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBIndoor_2__19_				0x7000079A	// 0x03FF
             // SARR_usGammaLutRGBOutdoor					0x7000079C	// 0x0000    
{0x0F120000},  // SARR_usGammaLutRGBOutdoor_0__0_				0x7000079C	// 0x0000
{0x0F12000F},  // SARR_usGammaLutRGBOutdoor_0__1_				0x7000079E	// 0x0001
{0x0F120020},  // SARR_usGammaLutRGBOutdoor_0__2_				0x700007A0	// 0x0007
{0x0F120043},  // SARR_usGammaLutRGBOutdoor_0__3_				0x700007A2	// 0x002D
{0x0F120086},  // SARR_usGammaLutRGBOutdoor_0__4_				0x700007A4	// 0x0075
{0x0F1200ED},  // SARR_usGammaLutRGBOutdoor_0__5_				0x700007A6	// 0x00E9
{0x0F12013E},  // SARR_usGammaLutRGBOutdoor_0__6_				0x700007A8	// 0x0143
{0x0F120163},  // SARR_usGammaLutRGBOutdoor_0__7_				0x700007AA	// 0x016C
{0x0F120185},  // SARR_usGammaLutRGBOutdoor_0__8_				0x700007AC	// 0x0190
{0x0F1201BF},  // SARR_usGammaLutRGBOutdoor_0__9_				0x700007AE	// 0x01CC
{0x0F1201F2},  // SARR_usGammaLutRGBOutdoor_0__10_			0x700007B0	// 0x01FF
{0x0F120221},  // SARR_usGammaLutRGBOutdoor_0__11_			0x700007B2	// 0x022A
{0x0F12024A},  // SARR_usGammaLutRGBOutdoor_0__12_			0x700007B4	// 0x0252
{0x0F120294},  // SARR_usGammaLutRGBOutdoor_0__13_			0x700007B6	// 0x0296
{0x0F1202D0},  // SARR_usGammaLutRGBOutdoor_0__14_			0x700007B8	// 0x02D6
{0x0F12032A},  // SARR_usGammaLutRGBOutdoor_0__15_			0x700007BA	// 0x033C
{0x0F12036A},  // SARR_usGammaLutRGBOutdoor_0__16_			0x700007BC	// 0x038D
{0x0F12039F},  // SARR_usGammaLutRGBOutdoor_0__17_			0x700007BE	// 0x03D0
{0x0F1203CC},  // SARR_usGammaLutRGBOutdoor_0__18_			0x700007C0	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBOutdoor_0__19_			0x700007C2	// 0x03FF
{0x0F120000},  // SARR_usGammaLutRGBOutdoor_1__0_				0x700007C4	// 0x0000
{0x0F12000F},  // SARR_usGammaLutRGBOutdoor_1__1_				0x700007C6	// 0x0001
{0x0F120020},  // SARR_usGammaLutRGBOutdoor_1__2_				0x700007C8	// 0x0007
{0x0F120043},  // SARR_usGammaLutRGBOutdoor_1__3_				0x700007CA	// 0x002D
{0x0F120086},  // SARR_usGammaLutRGBOutdoor_1__4_				0x700007CC	// 0x0075
{0x0F1200ED},  // SARR_usGammaLutRGBOutdoor_1__5_				0x700007CE	// 0x00E9
{0x0F12013E},  // SARR_usGammaLutRGBOutdoor_1__6_				0x700007D0	// 0x0143
{0x0F120163},  // SARR_usGammaLutRGBOutdoor_1__7_				0x700007D2	// 0x016C
{0x0F120185},  // SARR_usGammaLutRGBOutdoor_1__8_				0x700007D4	// 0x0190
{0x0F1201BF},  // SARR_usGammaLutRGBOutdoor_1__9_				0x700007D6	// 0x01CC
{0x0F1201F2},  // SARR_usGammaLutRGBOutdoor_1__10_			0x700007D8	// 0x01FF
{0x0F120221},  // SARR_usGammaLutRGBOutdoor_1__11_			0x700007DA	// 0x022A
{0x0F12024A},  // SARR_usGammaLutRGBOutdoor_1__12_			0x700007DC	// 0x0252
{0x0F120294},  // SARR_usGammaLutRGBOutdoor_1__13_			0x700007DE	// 0x0296
{0x0F1202D0},  // SARR_usGammaLutRGBOutdoor_1__14_			0x700007E0	// 0x02D6
{0x0F12032A},  // SARR_usGammaLutRGBOutdoor_1__15_			0x700007E2	// 0x033C
{0x0F12036A},  // SARR_usGammaLutRGBOutdoor_1__16_			0x700007E4	// 0x038D
{0x0F12039F},  // SARR_usGammaLutRGBOutdoor_1__17_			0x700007E6	// 0x03D0
{0x0F1203CC},  // SARR_usGammaLutRGBOutdoor_1__18_			0x700007E8	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBOutdoor_1__19_			0x700007EA	// 0x03FF
{0x0F120000},  // SARR_usGammaLutRGBOutdoor_2__0_				0x700007EC	// 0x0000
{0x0F12000F},  // SARR_usGammaLutRGBOutdoor_2__1_				0x700007EE	// 0x0001
{0x0F120020},  // SARR_usGammaLutRGBOutdoor_2__2_				0x700007F0	// 0x0007
{0x0F120043},  // SARR_usGammaLutRGBOutdoor_2__3_				0x700007F2	// 0x002D
{0x0F120086},  // SARR_usGammaLutRGBOutdoor_2__4_				0x700007F4	// 0x0075
{0x0F1200ED},  // SARR_usGammaLutRGBOutdoor_2__5_				0x700007F6	// 0x00E9
{0x0F12013E},  // SARR_usGammaLutRGBOutdoor_2__6_				0x700007F8	// 0x0143
{0x0F120163},  // SARR_usGammaLutRGBOutdoor_2__7_				0x700007FA	// 0x016C
{0x0F120185},  // SARR_usGammaLutRGBOutdoor_2__8_				0x700007FC	// 0x0190
{0x0F1201BF},  // SARR_usGammaLutRGBOutdoor_2__9_				0x700007FE	// 0x01CC
{0x0F1201F2},  // SARR_usGammaLutRGBOutdoor_2__10_			0x70000800	// 0x01FF
{0x0F120221},  // SARR_usGammaLutRGBOutdoor_2__11_			0x70000802	// 0x022A
{0x0F12024A},  // SARR_usGammaLutRGBOutdoor_2__12_			0x70000804	// 0x0252
{0x0F120294},  // SARR_usGammaLutRGBOutdoor_2__13_			0x70000806	// 0x0296
{0x0F1202D0},  // SARR_usGammaLutRGBOutdoor_2__14_			0x70000808	// 0x02D6
{0x0F12032A},  // SARR_usGammaLutRGBOutdoor_2__15_			0x7000080A	// 0x033C
{0x0F12036A},  // SARR_usGammaLutRGBOutdoor_2__16_			0x7000080C	// 0x038D
{0x0F12039F},  // SARR_usGammaLutRGBOutdoor_2__17_			0x7000080E	// 0x03D0
{0x0F1203CC},  // SARR_usGammaLutRGBOutdoor_2__18_			0x70000810	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBOutdoor_2__19_			0x70000812	// 0x03FF

{0x002A0896},
{0x0F1200C0},
{0x0F120100},
{0x0F120125},
{0x0F12015F},
{0x0F12017C},
{0x0F120194},

{0x0F120001},

{0x002A0888},
{0x0F124800},
{0x0F127000},

{0x002A4800},
{0x0F12016C},
{0x0F12FF94},
{0x0F12FFCE},
{0x0F12FF20},
{0x0F1201BF},
{0x0F12FF53},
{0x0F12003F},
{0x0F120007},
{0x0F1201DF},
{0x0F120110},
{0x0F1200DF},
{0x0F12FF47},
{0x0F120206},
{0x0F12FF7F},
{0x0F120191},
{0x0F12FF06},
{0x0F1201BA},
{0x0F120108},

{0x0F12016C},
{0x0F12FF94},
{0x0F12FFCE},
{0x0F12FF20},
{0x0F1201BF},
{0x0F12FF53},
{0x0F12003F},
{0x0F120007},
{0x0F1201DF},
{0x0F120110},
{0x0F1200DF},
{0x0F12FF47},
{0x0F120206},
{0x0F12FF7F},
{0x0F120191},
{0x0F12FF06},
{0x0F1201BA},
{0x0F120108},

{0x0F12016C},
{0x0F12FF94},
{0x0F12FFCE},
{0x0F12FF20},
{0x0F1201BF},
{0x0F12FF53},
{0x0F12003F},
{0x0F120007},
{0x0F1201DF},
{0x0F120110},
{0x0F1200DF},
{0x0F12FF47},
{0x0F120206},
{0x0F12FF7F},
{0x0F120191},
{0x0F12FF06},
{0x0F1201BA},
{0x0F120108},

{0x0F1201E7}, //0208 
{0x0F12FFC2}, //FFD3 
{0x0F12FFEC}, //FFE9 
{0x0F12FEF1}, //FF5B 
{0x0F12014E}, //025A 
{0x0F12FF18}, //FF80 
{0x0F12FFC8}, //FFC8 
{0x0F12FFC1}, //FFC1 
{0x0F12013A}, //013A 
{0x0F120112}, //0112 
{0x0F1200EE}, //00EE 
{0x0F12FF99}, //FF99 
{0x0F12009E}, //009E 
{0x0F12FF5F}, //FF5F 
{0x0F1201A8}, //01A8 
{0x0F12FF75}, //FF75 
{0x0F120187}, //0187 
{0x0F1201BF}, //01BF 

{0x0F1201E7}, //0208
{0x0F12FFC2}, //FFD3
{0x0F12FFEC}, //FFE9
{0x0F12FEF1}, //FF5B
{0x0F12014E}, //025A
{0x0F12FF18}, //FF80
{0x0F12FFC8}, //FFC8
{0x0F12FFC1}, //FFC1
{0x0F12013A}, //013A
{0x0F120112}, //0112
{0x0F1200EE}, //00EE
{0x0F12FF99}, //FF99
{0x0F12009E}, //009E
{0x0F12FF5F}, //FF5F
{0x0F1201A8}, //01A8
{0x0F12FF75}, //FF75
{0x0F120187}, //0187
{0x0F1201BF}, //01BF

{0x0F1201E7}, //0208
{0x0F12FFC2}, //FFD3
{0x0F12FFEC}, //FFE9
{0x0F12FEF1}, //FF5B
{0x0F12014E}, //025A
{0x0F12FF18}, //FF80
{0x0F12FFC8}, //FFC8
{0x0F12FFC1}, //FFC1
{0x0F12013A}, //013A
{0x0F120112}, //0112
{0x0F1200EE}, //00EE
{0x0F12FF99}, //FF99
{0x0F12009E}, //009E
{0x0F12FF5F}, //FF5F
{0x0F1201A8}, //01A8
{0x0F12FF75}, //FF75
{0x0F120187}, //0187
{0x0F1201BF}, //01BF

{0x002A0890},
{0x0F1248D8},
{0x0F127000},

{0x002A48D8}, //Outdoor ccm
{0x0F1201AA}, 
{0x0F12FFC4}, 
{0x0F12FFC5}, 
{0x0F12FF6C}, 
{0x0F1201E8}, 
{0x0F12FF79},
{0x0F120000},
{0x0F12FFF5},
{0x0F12023C},
{0x0F1200A7}, 
{0x0F1200F5}, 
{0x0F12FF5E}, 
{0x0F12022D},
{0x0F12FF9B},
{0x0F1201E1},
{0x0F12FF34},
{0x0F12014B},
{0x0F1201B6},

{0x002A0924},
{0x0F120050},
{0x0F1200B0},
{0x0F120196},
{0x0F120245},
{0x0F120300},

{0x002A0958},     
{0x0F120000},   //	AfitBaseVals_0__0_		//	AFIT16_BRIGHTNESS                                       //AFIT 0             					0x70000958	// 0x0000
{0x0F120000},   //	AfitBaseVals_0__1_		//	AFIT16_CONTRAST                                                              					0x7000095A	// 0x0000
{0x0F120000},   //	AfitBaseVals_0__2_		//	AFIT16_SATURATION                                                            					0x7000095C	// 0x0000
{0x0F120000},   //	AfitBaseVals_0__3_		//	AFIT16_SHARP_BLUR                                                            					0x7000095E	// 0x0000
{0x0F120000},   //	AfitBaseVals_0__4_		//	AFIT16_GLAMOUR                                                               					0x70000960	// 0x0000
{0x0F1200C0},   //	AfitBaseVals_0__5_		//	AFIT16_bnr_edge_high                                                         					0x70000962	// 0x00C0
{0x0F120064},   //	AfitBaseVals_0__6_		//	AFIT16_postdmsc_iLowBright                                                   					0x70000964	// 0x0032
{0x0F120384},   //	AfitBaseVals_0__7_		//	AFIT16_postdmsc_iHighBright                                                  					0x70000966	// 0x0226
{0x0F120032},   //	AfitBaseVals_0__8_		//	AFIT16_postdmsc_iLowSat                                                      					0x70000968	// 0x0032
{0x0F1201F4},   //	AfitBaseVals_0__9_		//	AFIT16_postdmsc_iHighSat                                                     					0x7000096A	// 0x01F4
{0x0F120070},   //	AfitBaseVals_0__10_		//	AFIT16_postdmsc_iTune                                                        					0x7000096C	// 0x0070
{0x0F120040},   //	AfitBaseVals_0__11_		//	AFIT16_yuvemix_mNegRanges_0                                                  					0x7000096E	// 0x0060
{0x0F1200A0},   //	AfitBaseVals_0__12_		//	AFIT16_yuvemix_mNegRanges_1                                                  					0x70000970	// 0x0100
{0x0F120100},   //	AfitBaseVals_0__13_		//	AFIT16_yuvemix_mNegRanges_2                                                  					0x70000972	// 0x0200
{0x0F120010},   //	AfitBaseVals_0__14_		//	AFIT16_yuvemix_mPosRanges_0                                                  					0x70000974	// 0x0020
{0x0F120040},   //	AfitBaseVals_0__15_		//	AFIT16_yuvemix_mPosRanges_1                                                  					0x70000976	// 0x0060
{0x0F1200A0},   //	AfitBaseVals_0__16_		//	AFIT16_yuvemix_mPosRanges_2                                                  					0x70000978	// 0x0100
{0x0F121430},   //	AfitBaseVals_0__17_		//	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                              					0x7000097A	// 0x1E30
{0x0F120201},   //	AfitBaseVals_0__18_		//	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                         					0x7000097C	// 0x0201
{0x0F120204},   //	AfitBaseVals_0__19_		//	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                    					0x7000097E	// 0x0204
{0x0F123604},   //	AfitBaseVals_0__20_		//	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                        					0x70000980	// 0x2004
{0x0F12032A},   //	AfitBaseVals_0__21_		//	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                       					0x70000982	// 0x0110
{0x0F120403},   //	AfitBaseVals_0__22_		//	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                    					0x70000984	// 0x0201
{0x0F121B06},   //	AfitBaseVals_0__23_		//	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                      					0x70000986	// 0x3C06
{0x0F126015},   //	AfitBaseVals_0__24_		//	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                 					0x70000988	// 0x4012
{0x0F1200C0},   //	AfitBaseVals_0__25_		//	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                  					0x7000098A	// 0x00A0
{0x0F126080},   //	AfitBaseVals_0__26_		//	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                					0x7000098C	// 0x2C80
{0x0F124080},   //	AfitBaseVals_0__27_		//	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh          					0x7000098E	// 0x2050
{0x0F120640},   //	AfitBaseVals_0__28_		//	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed           					0x70000990	// 0x0820
{0x0F120306},   //	AfitBaseVals_0__29_		//	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh             					0x70000992	// 0x0304
{0x0F122003},   //	AfitBaseVals_0__30_		//	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                    					0x70000994	// 0x0003
{0x0F12FF01},   //	AfitBaseVals_0__31_		//	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit               					0x70000996	// 0xFF01
{0x0F120000},   //	AfitBaseVals_0__32_		//	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                    					0x70000998	// 0x0600
{0x0F120400},   //	AfitBaseVals_0__33_		//	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                         					0x7000099A	// 0x0200
{0x0F12365A},   //	AfitBaseVals_0__34_		//	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                          					0x7000099C	// 0x2C5A
{0x0F12102A},   //	AfitBaseVals_0__35_		//	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                           					0x7000099E	// 0x1C18
{0x0F12000B},   //	AfitBaseVals_0__36_		//	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                              					0x700009A0	// 0x0614
{0x0F120600},   //	AfitBaseVals_0__37_		//	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                              					0x700009A2	// 0x0A00
{0x0F125A0F},   //	AfitBaseVals_0__38_		//	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                         					0x700009A4	// 0x5A0F
{0x0F120505},   //	AfitBaseVals_0__39_		//	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                      					0x700009A6	// 0x0502
{0x0F121802},   //	AfitBaseVals_0__40_		//	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                              					0x700009A8	// 0x180C
{0x0F120000},   //	AfitBaseVals_0__41_		//	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                        					0x700009AA	// 0x0000
{0x0F122006},   //	AfitBaseVals_0__42_		//	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                        					0x700009AC	// 0x3018
{0x0F123028},   //	AfitBaseVals_0__43_		//	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                         					0x700009AE	// 0x602A
{0x0F120418},   //	AfitBaseVals_0__44_		//	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                               					0x700009B0	// 0x0830
{0x0F120101},   //	AfitBaseVals_0__45_		//	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                         					0x700009B2	// 0x0103
{0x0F120800},   //	AfitBaseVals_0__46_		//	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                        					0x700009B4	// 0x0000
{0x0F121804},   //	AfitBaseVals_0__47_		//	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                     					0x700009B6	// 0x0004
{0x0F124008},   //	AfitBaseVals_0__48_		//	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                      					0x700009B8	// 0x4000
{0x0F120540},   //	AfitBaseVals_0__49_		//	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                      					0x700009BA	// 0x053F
{0x0F128006},   //	AfitBaseVals_0__50_		//	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                      					0x700009BC	// 0x8006
{0x0F120020},   //	AfitBaseVals_0__51_		//	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                       					0x700009BE	// 0x0020
{0x0F120000},   //	AfitBaseVals_0__52_		//	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                					0x700009C0	// 0x0000
{0x0F121800},   //	AfitBaseVals_0__53_		//	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                    					0x700009C2	// 0x1800
{0x0F120000},   //	AfitBaseVals_0__54_		//	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                 					0x700009C4	// 0x0000
{0x0F121E10},   //	AfitBaseVals_0__55_		//	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                        					0x700009C6	// 0x1E10
{0x0F12000B},   //	AfitBaseVals_0__56_		//	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                  					0x700009C8	// 0x000C
{0x0F120607},   //	AfitBaseVals_0__57_		//	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                					0x700009CA	// 0x0607
{0x0F120005},   //	AfitBaseVals_0__58_		//	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                					0x700009CC	// 0x0005
{0x0F120607},   //	AfitBaseVals_0__59_		//	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                					0x700009CE	// 0x0607
{0x0F120405},   //	AfitBaseVals_0__60_		//	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                 					0x700009D0	// 0x0405
{0x0F120205},   //	AfitBaseVals_0__61_		//	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                  					0x700009D2	// 0x0207
{0x0F120304},   //	AfitBaseVals_0__62_		//	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                  					0x700009D4	// 0x0204
{0x0F120409},   //	AfitBaseVals_0__63_		//	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                					0x700009D6	// 0x0408
{0x0F120306},   //	AfitBaseVals_0__64_		//	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y             					0x700009D8	// 0x0306
{0x0F120407},   //	AfitBaseVals_0__65_		//	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y          					0x700009DA	// 0x0C07
{0x0F121C04},   //	AfitBaseVals_0__66_		//	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV         					0x700009DC	// 0x2408
{0x0F120214},   //	AfitBaseVals_0__67_		//	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y          					0x700009DE	// 0x0818
{0x0F121002},   //	AfitBaseVals_0__68_		//	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV           					0x700009E0	// 0x1006
{0x0F120610},   //	AfitBaseVals_0__69_		//	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL           					0x700009E2	// 0x0010
{0x0F120F02},   //	AfitBaseVals_0__70_		//	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL           					0x700009E4	// 0x1E00
{0x0F124A18},   //	AfitBaseVals_0__71_		//	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower           					0x700009E6	// 0x801A
{0x0F120080},   //	AfitBaseVals_0__72_		//	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce               					0x700009E8	// 0x0080
{0x0F120040},   //	AfitBaseVals_0__73_		//	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                   					0x700009EA	// 0x0080
{0x0F120180},   //	AfitBaseVals_0__74_		//	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                       					0x700009EC	// 0x0180
{0x0F120A0A},   //	AfitBaseVals_0__75_		//	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                        					0x700009EE	// 0x0A0A
{0x0F120101},   //	AfitBaseVals_0__76_		//	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                    					0x700009F0	// 0x0101
{0x0F122A36},   //	AfitBaseVals_0__77_		//	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                     					0x700009F2	// 0x1B3C
{0x0F126024},   //	AfitBaseVals_0__78_		//	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                     					0x700009F4	// 0x4848
{0x0F122A36},   //	AfitBaseVals_0__79_		//	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                       					0x700009F6	// 0x6060
{0x0F12FFFF},   //	AfitBaseVals_0__80_		//	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                     					0x700009F8	// 0xFFFF
{0x0F120808},   //	AfitBaseVals_0__81_		//	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                					0x700009FA	// 0x0808
{0x0F120A01},   //	AfitBaseVals_0__82_		//	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin               					0x700009FC	// 0x0A01
{0x0F12010A},   //	AfitBaseVals_0__83_		//	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin              					0x700009FE	// 0x010A
{0x0F123601},   //	AfitBaseVals_0__84_		//	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin             					0x70000A00	// 0x3C01
{0x0F12242A},   //	AfitBaseVals_0__85_		//	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin             					0x70000A02	// 0x481B
{0x0F123660},   //	AfitBaseVals_0__86_		//	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin              					0x70000A04	// 0x6048
{0x0F12FF2A},   //	AfitBaseVals_0__87_		//	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin              					0x70000A06	// 0xFF60
{0x0F1208FF},   //	AfitBaseVals_0__88_		//	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin         					0x70000A08	// 0x08FF
{0x0F120008},   //	AfitBaseVals_0__89_		//	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                          					0x70000A0A	// 0x0008
{0x0F120001},   //	AfitBaseVals_0__90_		//	AFITB_bnr_nClustLevel_C      [0]                                             					0x70000A0C	// 0x0001
{0x0F120000},   //	AfitBaseVals_1__0_		//	AFIT16_BRIGHTNESS                                     //AFIT 1               					0x70000A0E	// 0x0000
{0x0F120000},   //	AfitBaseVals_1__1_		//	AFIT16_CONTRAST                                                              					0x70000A10	// 0x0000
{0x0F120000},   //	AfitBaseVals_1__2_		//	AFIT16_SATURATION                                                            					0x70000A12	// 0x0000
{0x0F120000},   //	AfitBaseVals_1__3_		//	AFIT16_SHARP_BLUR                                                            					0x70000A14	// 0x0000
{0x0F120000},   //	AfitBaseVals_1__4_		//	AFIT16_GLAMOUR                                                               					0x70000A16	// 0x0000
{0x0F1200C0},   //	AfitBaseVals_1__5_		//	AFIT16_bnr_edge_high                                                         					0x70000A18	// 0x00C0
{0x0F120064},   //	AfitBaseVals_1__6_		//	AFIT16_postdmsc_iLowBright                                                   					0x70000A1A	// 0x0032
{0x0F120384},   //	AfitBaseVals_1__7_		//	AFIT16_postdmsc_iHighBright                                                  					0x70000A1C	// 0x0226
{0x0F120032},   //	AfitBaseVals_1__8_		//	AFIT16_postdmsc_iLowSat                                                      					0x70000A1E	// 0x0032
{0x0F1201F4},   //	AfitBaseVals_1__9_		//	AFIT16_postdmsc_iHighSat                                                     					0x70000A20	// 0x01F4
{0x0F120070},   //	AfitBaseVals_1__10_		//	AFIT16_postdmsc_iTune                                                        					0x70000A22	// 0x0070
{0x0F120040},   //	AfitBaseVals_1__11_		//	AFIT16_yuvemix_mNegRanges_0                                                  					0x70000A24	// 0x0060
{0x0F1200A0},   //	AfitBaseVals_1__12_		//	AFIT16_yuvemix_mNegRanges_1                                                  					0x70000A26	// 0x0100
{0x0F120100},   //	AfitBaseVals_1__13_		//	AFIT16_yuvemix_mNegRanges_2                                                  					0x70000A28	// 0x0200
{0x0F120010},   //	AfitBaseVals_1__14_		//	AFIT16_yuvemix_mPosRanges_0                                                  					0x70000A2A	// 0x0020
{0x0F120060},   //	AfitBaseVals_1__15_		//	AFIT16_yuvemix_mPosRanges_1                                                  					0x70000A2C	// 0x0060
{0x0F120100},   //	AfitBaseVals_1__16_		//	AFIT16_yuvemix_mPosRanges_2                                                  					0x70000A2E	// 0x0100
{0x0F121430},   //	AfitBaseVals_1__17_		//	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                              					0x70000A30	// 0x1E30
{0x0F120201},   //	AfitBaseVals_1__18_		//	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                         					0x70000A32	// 0x0201
{0x0F120204},   //	AfitBaseVals_1__19_		//	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                    					0x70000A34	// 0x0204
{0x0F122404},   //	AfitBaseVals_1__20_		//	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                        					0x70000A36	// 0x1804
{0x0F12031B},   //	AfitBaseVals_1__21_		//	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                       					0x70000A38	// 0x010C
{0x0F120103},   //	AfitBaseVals_1__22_		//	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                    					0x70000A3A	// 0x0101
{0x0F121205},   //	AfitBaseVals_1__23_		//	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                      					0x70000A3C	// 0x2A06
{0x0F12400D},   //	AfitBaseVals_1__24_		//	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                 					0x70000A3E	// 0x300E
{0x0F120080},   //	AfitBaseVals_1__25_		//	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                  					0x70000A40	// 0x0060
{0x0F122080},   //	AfitBaseVals_1__26_		//	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                					0x70000A42	// 0x2080
{0x0F123040},   //	AfitBaseVals_1__27_		//	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh          					0x70000A44	// 0x2038
{0x0F120630},   //	AfitBaseVals_1__28_		//	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed           					0x70000A46	// 0x0820
{0x0F120306},   //	AfitBaseVals_1__29_		//	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh             					0x70000A48	// 0x0304
{0x0F122003},   //	AfitBaseVals_1__30_		//	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                    					0x70000A4A	// 0x0003
{0x0F12FF01},   //	AfitBaseVals_1__31_		//	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit               					0x70000A4C	// 0xFF01
{0x0F120404},   //	AfitBaseVals_1__32_		//	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                    					0x70000A4E	// 0x0600
{0x0F120300},   //	AfitBaseVals_1__33_		//	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                         					0x70000A50	// 0x0200
{0x0F12245A},   //	AfitBaseVals_1__34_		//	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                          					0x70000A52	// 0x1C5A
{0x0F121018},   //	AfitBaseVals_1__35_		//	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                           					0x70000A54	// 0x1214
{0x0F12000B},   //	AfitBaseVals_1__36_		//	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                              					0x70000A56	// 0x060D
{0x0F120B00},   //	AfitBaseVals_1__37_		//	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                              					0x70000A58	// 0x0E00
{0x0F125A0F},   //	AfitBaseVals_1__38_		//	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                         					0x70000A5A	// 0x5A0F
{0x0F120505},   //	AfitBaseVals_1__39_		//	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                      					0x70000A5C	// 0x0502
{0x0F121802},   //	AfitBaseVals_1__40_		//	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                              					0x70000A5E	// 0x180C
{0x0F120000},   //	AfitBaseVals_1__41_		//	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                        					0x70000A60	// 0x0000
{0x0F122006},   //	AfitBaseVals_1__42_		//	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                        					0x70000A62	// 0x3018
{0x0F123428},   //	AfitBaseVals_1__43_		//	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                         					0x70000A64	// 0x602A
{0x0F12041C},   //	AfitBaseVals_1__44_		//	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                               					0x70000A66	// 0x0330
{0x0F120101},   //	AfitBaseVals_1__45_		//	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                         					0x70000A68	// 0x0101
{0x0F120800},   //	AfitBaseVals_1__46_		//	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                        					0x70000A6A	// 0x0000
{0x0F121004},   //	AfitBaseVals_1__47_		//	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                     					0x70000A6C	// 0x0004
{0x0F124008},   //	AfitBaseVals_1__48_		//	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                      					0x70000A6E	// 0x4000
{0x0F120540},   //	AfitBaseVals_1__49_		//	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                      					0x70000A70	// 0x053F
{0x0F128006},   //	AfitBaseVals_1__50_		//	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                      					0x70000A72	// 0x8006
{0x0F120020},   //	AfitBaseVals_1__51_		//	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                       					0x70000A74	// 0x0020
{0x0F120000},   //	AfitBaseVals_1__52_		//	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                					0x70000A76	// 0x0000
{0x0F121800},   //	AfitBaseVals_1__53_		//	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                    					0x70000A78	// 0x1800
{0x0F120000},   //	AfitBaseVals_1__54_		//	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                 					0x70000A7A	// 0x0000
{0x0F121E10},   //	AfitBaseVals_1__55_		//	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                        					0x70000A7C	// 0x1E10
{0x0F12000B},   //	AfitBaseVals_1__56_		//	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                  					0x70000A7E	// 0x000C
{0x0F120607},   //	AfitBaseVals_1__57_		//	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                					0x70000A80	// 0x0607
{0x0F120005},   //	AfitBaseVals_1__58_		//	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                					0x70000A82	// 0x0005
{0x0F120607},   //	AfitBaseVals_1__59_		//	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                					0x70000A84	// 0x0607
{0x0F120405},   //	AfitBaseVals_1__60_		//	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                 					0x70000A86	// 0x0405
{0x0F120205},   //	AfitBaseVals_1__61_		//	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                  					0x70000A88	// 0x0207
{0x0F120304},   //	AfitBaseVals_1__62_		//	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                  					0x70000A8A	// 0x0204
{0x0F120409},   //	AfitBaseVals_1__63_		//	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                					0x70000A8C	// 0x0408
{0x0F120306},   //	AfitBaseVals_1__64_		//	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y             					0x70000A8E	// 0x0306
{0x0F120407},   //	AfitBaseVals_1__65_		//	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y          					0x70000A90	// 0x0C07
{0x0F121F04},   //	AfitBaseVals_1__66_		//	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV         					0x70000A92	// 0x2008
{0x0F120218},   //	AfitBaseVals_1__67_		//	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y          					0x70000A94	// 0x0816
{0x0F121102},   //	AfitBaseVals_1__68_		//	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV           					0x70000A96	// 0x1006
{0x0F120611},   //	AfitBaseVals_1__69_		//	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL           					0x70000A98	// 0x0010
{0x0F121002},   //	AfitBaseVals_1__70_		//	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL           					0x70000A9A	// 0x1E00
{0x0F128018},   //	AfitBaseVals_1__71_		//	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower           					0x70000A9C	// 0x801A
{0x0F120080},   //	AfitBaseVals_1__72_		//	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce               					0x70000A9E	// 0x0080
{0x0F120080},   //	AfitBaseVals_1__73_		//	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                   					0x70000AA0	// 0x0080
{0x0F120180},   //	AfitBaseVals_1__74_		//	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                       					0x70000AA2	// 0x0180
{0x0F120A0A},   //	AfitBaseVals_1__75_		//	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                        					0x70000AA4	// 0x0A0A
{0x0F120101},   //	AfitBaseVals_1__76_		//	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                    					0x70000AA6	// 0x0101
{0x0F121B24},   //	AfitBaseVals_1__77_		//	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                     					0x70000AA8	// 0x152A
{0x0F126024},   //	AfitBaseVals_1__78_		//	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                     					0x70000AAA	// 0x4848
{0x0F121010},   //	AfitBaseVals_1__79_		//	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                       					0x70000AAC	// 0x6060
{0x0F12FFFF},   //	AfitBaseVals_1__80_		//	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                     					0x70000AAE	// 0xFFFF
{0x0F120808},   //	AfitBaseVals_1__81_		//	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                					0x70000AB0	// 0x0808
{0x0F120A01},   //	AfitBaseVals_1__82_		//	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin               					0x70000AB2	// 0x0A01
{0x0F12010A},   //	AfitBaseVals_1__83_		//	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin              					0x70000AB4	// 0x010A
{0x0F122401},   //	AfitBaseVals_1__84_		//	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin             					0x70000AB6	// 0x2A01
{0x0F12241B},   //	AfitBaseVals_1__85_		//	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin             					0x70000AB8	// 0x4815
{0x0F121E60},   //	AfitBaseVals_1__86_		//	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin              					0x70000ABA	// 0x6048
{0x0F12FF18},   //	AfitBaseVals_1__87_		//	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin              					0x70000ABC	// 0xFF60
{0x0F1208FF},   //	AfitBaseVals_1__88_		//	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin         					0x70000ABE	// 0x08FF
{0x0F120008},   //	AfitBaseVals_1__89_		//	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                          					0x70000AC0	// 0x0008
{0x0F120001},   //	AfitBaseVals_1__90_		//	AFITB_bnr_nClustLevel_C      [0]                                             					0x70000AC2	// 0x0001
{0x0F120000},   //	AfitBaseVals_2__0_		//	AFIT16_BRIGHTNESS                                       //AFIT 2             					0x70000AC4	// 0x0000
{0x0F120000},   //	AfitBaseVals_2__1_		//	AFIT16_CONTRAST                                                              					0x70000AC6	// 0x0000
{0x0F120000},   //	AfitBaseVals_2__2_		//	AFIT16_SATURATION                                                            					0x70000AC8	// 0x0000
{0x0F120000},   //	AfitBaseVals_2__3_		//	AFIT16_SHARP_BLUR                                                            					0x70000ACA	// 0x0000
{0x0F120000},   //	AfitBaseVals_2__4_		//	AFIT16_GLAMOUR                                                               					0x70000ACC	// 0x0000
{0x0F1200C0},   //	AfitBaseVals_2__5_		//	AFIT16_bnr_edge_high                                                         					0x70000ACE	// 0x00C0
{0x0F120064},   //	AfitBaseVals_2__6_		//	AFIT16_postdmsc_iLowBright                                                   					0x70000AD0	// 0x0032
{0x0F120384},   //	AfitBaseVals_2__7_		//	AFIT16_postdmsc_iHighBright                                                  					0x70000AD2	// 0x0226
{0x0F120032},   //	AfitBaseVals_2__8_		//	AFIT16_postdmsc_iLowSat                                                      					0x70000AD4	// 0x0032
{0x0F1201F4},   //	AfitBaseVals_2__9_		//	AFIT16_postdmsc_iHighSat                                                     					0x70000AD6	// 0x01F4
{0x0F120070},   //	AfitBaseVals_2__10_		//	AFIT16_postdmsc_iTune                                                        					0x70000AD8	// 0x0070
{0x0F120040},   //	AfitBaseVals_2__11_		//	AFIT16_yuvemix_mNegRanges_0                                                  					0x70000ADA	// 0x0060
{0x0F1200A0},   //	AfitBaseVals_2__12_		//	AFIT16_yuvemix_mNegRanges_1                                                  					0x70000ADC	// 0x0100
{0x0F120100},   //	AfitBaseVals_2__13_		//	AFIT16_yuvemix_mNegRanges_2                                                  					0x70000ADE	// 0x0200
{0x0F120010},   //	AfitBaseVals_2__14_		//	AFIT16_yuvemix_mPosRanges_0                                                  					0x70000AE0	// 0x0020
{0x0F120060},   //	AfitBaseVals_2__15_		//	AFIT16_yuvemix_mPosRanges_1                                                  					0x70000AE2	// 0x0060
{0x0F120100},   //	AfitBaseVals_2__16_		//	AFIT16_yuvemix_mPosRanges_2                                                  					0x70000AE4	// 0x0100
{0x0F121430},   //	AfitBaseVals_2__17_		//	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                              					0x70000AE6	// 0x1E30
{0x0F120201},   //	AfitBaseVals_2__18_		//	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                         					0x70000AE8	// 0x0201
{0x0F120204},   //	AfitBaseVals_2__19_		//	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                    					0x70000AEA	// 0x0204
{0x0F121B04},   //	AfitBaseVals_2__20_		//	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                        					0x70000AEC	// 0x1404
{0x0F120312},   //	AfitBaseVals_2__21_		//	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                       					0x70000AEE	// 0x010A
{0x0F120003},   //	AfitBaseVals_2__22_		//	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                    					0x70000AF0	// 0x0101
{0x0F120C03},   //	AfitBaseVals_2__23_		//	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                      					0x70000AF2	// 0x1E06
{0x0F122806},   //	AfitBaseVals_2__24_		//	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                 					0x70000AF4	// 0x200A
{0x0F120060},   //	AfitBaseVals_2__25_		//	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                  					0x70000AF6	// 0x0050
{0x0F121580},   //	AfitBaseVals_2__26_		//	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                					0x70000AF8	// 0x2080
{0x0F122020},   //	AfitBaseVals_2__27_		//	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh          					0x70000AFA	// 0x2034
{0x0F120620},   //	AfitBaseVals_2__28_		//	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed           					0x70000AFC	// 0x0820
{0x0F120306},   //	AfitBaseVals_2__29_		//	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh             					0x70000AFE	// 0x0304
{0x0F122003},   //	AfitBaseVals_2__30_		//	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                    					0x70000B00	// 0x0003
{0x0F12FF01},   //	AfitBaseVals_2__31_		//	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit               					0x70000B02	// 0xFF01
{0x0F120404},   //	AfitBaseVals_2__32_		//	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                    					0x70000B04	// 0x0802
{0x0F120300},   //	AfitBaseVals_2__33_		//	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                         					0x70000B06	// 0x0200
{0x0F12145A},   //	AfitBaseVals_2__34_		//	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                          					0x70000B08	// 0x185A
{0x0F121010},   //	AfitBaseVals_2__35_		//	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                           					0x70000B0A	// 0x1012
{0x0F12000B},   //	AfitBaseVals_2__36_		//	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                              					0x70000B0C	// 0x060B
{0x0F120E00},   //	AfitBaseVals_2__37_		//	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                              					0x70000B0E	// 0x1000
{0x0F125A0F},   //	AfitBaseVals_2__38_		//	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                         					0x70000B10	// 0x5A0F
{0x0F120504},   //	AfitBaseVals_2__39_		//	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                      					0x70000B12	// 0x0502
{0x0F121802},   //	AfitBaseVals_2__40_		//	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                              					0x70000B14	// 0x180C
{0x0F120000},   //	AfitBaseVals_2__41_		//	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                        					0x70000B16	// 0x0000
{0x0F122006},   //	AfitBaseVals_2__42_		//	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                        					0x70000B18	// 0x3018
{0x0F123828},   //	AfitBaseVals_2__43_		//	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                         					0x70000B1A	// 0x602A
{0x0F120428},   //	AfitBaseVals_2__44_		//	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                               					0x70000B1C	// 0x0330
{0x0F120101},   //	AfitBaseVals_2__45_		//	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                         					0x70000B1E	// 0x0101
{0x0F128000},   //	AfitBaseVals_2__46_		//	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                        					0x70000B20	// 0xFF00
{0x0F120A04},   //	AfitBaseVals_2__47_		//	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                     					0x70000B22	// 0x0004
{0x0F124008},   //	AfitBaseVals_2__48_		//	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                      					0x70000B24	// 0x4000
{0x0F120540},   //	AfitBaseVals_2__49_		//	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                      					0x70000B26	// 0x053F
{0x0F128006},   //	AfitBaseVals_2__50_		//	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                      					0x70000B28	// 0x8006
{0x0F120020},   //	AfitBaseVals_2__51_		//	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                       					0x70000B2A	// 0x0020
{0x0F120000},   //	AfitBaseVals_2__52_		//	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                					0x70000B2C	// 0x0000
{0x0F121800},   //	AfitBaseVals_2__53_		//	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                    					0x70000B2E	// 0x1800
{0x0F120000},   //	AfitBaseVals_2__54_		//	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                 					0x70000B30	// 0x0000
{0x0F121E10},   //	AfitBaseVals_2__55_		//	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                        					0x70000B32	// 0x1E10
{0x0F12000B},   //	AfitBaseVals_2__56_		//	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                  					0x70000B34	// 0x000C
{0x0F120607},   //	AfitBaseVals_2__57_		//	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                					0x70000B36	// 0x0607
{0x0F120005},   //	AfitBaseVals_2__58_		//	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                					0x70000B38	// 0x0005
{0x0F120607},   //	AfitBaseVals_2__59_		//	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                					0x70000B3A	// 0x0607
{0x0F120405},   //	AfitBaseVals_2__60_		//	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                 					0x70000B3C	// 0x0405
{0x0F120207},   //	AfitBaseVals_2__61_		//	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                  					0x70000B3E	// 0x0207
{0x0F120304},   //	AfitBaseVals_2__62_		//	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                  					0x70000B40	// 0x0304
{0x0F120409},   //	AfitBaseVals_2__63_		//	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                					0x70000B42	// 0x040A
{0x0F120306},   //	AfitBaseVals_2__64_		//	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y             					0x70000B44	// 0x0306
{0x0F120407},   //	AfitBaseVals_2__65_		//	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y          					0x70000B46	// 0x0C07
{0x0F122404},   //	AfitBaseVals_2__66_		//	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV         					0x70000B48	// 0x1C08
{0x0F120221},   //	AfitBaseVals_2__67_		//	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y          					0x70000B4A	// 0x0814
{0x0F121202},   //	AfitBaseVals_2__68_		//	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV           					0x70000B4C	// 0x1006
{0x0F120613},   //	AfitBaseVals_2__69_		//	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL           					0x70000B4E	// 0x0010
{0x0F121202},   //	AfitBaseVals_2__70_		//	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL           					0x70000B50	// 0x1E00
{0x0F128018},   //	AfitBaseVals_2__71_		//	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower           					0x70000B52	// 0x801A
{0x0F120680},   //	AfitBaseVals_2__72_		//	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce               					0x70000B54	// 0x0080
{0x0F120080},   //	AfitBaseVals_2__73_		//	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                   					0x70000B56	// 0x0080
{0x0F120180},   //	AfitBaseVals_2__74_		//	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                       					0x70000B58	// 0x0180
{0x0F120A0A},   //	AfitBaseVals_2__75_		//	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                        					0x70000B5A	// 0x0A0A
{0x0F120101},   //	AfitBaseVals_2__76_		//	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                    					0x70000B5C	// 0x0101
{0x0F12141D},   //	AfitBaseVals_2__77_		//	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                     					0x70000B5E	// 0x101E
{0x0F126024},   //	AfitBaseVals_2__78_		//	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                     					0x70000B60	// 0x4848
{0x0F120C0C},   //	AfitBaseVals_2__79_		//	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                       					0x70000B62	// 0x4040
{0x0F12FFFF},   //	AfitBaseVals_2__80_		//	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                     					0x70000B64	// 0xFFFF
{0x0F120808},   //	AfitBaseVals_2__81_		//	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                					0x70000B66	// 0x0808
{0x0F120A01},   //	AfitBaseVals_2__82_		//	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin               					0x70000B68	// 0x0A01
{0x0F12010A},   //	AfitBaseVals_2__83_		//	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin              					0x70000B6A	// 0x010A
{0x0F121B01},   //	AfitBaseVals_2__84_		//	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin             					0x70000B6C	// 0x1E01
{0x0F122412},   //	AfitBaseVals_2__85_		//	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin             					0x70000B6E	// 0x4810
{0x0F120C60},   //	AfitBaseVals_2__86_		//	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin              					0x70000B70	// 0x4048
{0x0F12FF0C},   //	AfitBaseVals_2__87_		//	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin              					0x70000B72	// 0xFF40
{0x0F1208FF},   //	AfitBaseVals_2__88_		//	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin         					0x70000B74	// 0x08FF
{0x0F120008},   //	AfitBaseVals_2__89_		//	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                          					0x70000B76	// 0x0008
{0x0F120001},   //	AfitBaseVals_2__90_		//	AFITB_bnr_nClustLevel_C      [0]                                             					0x70000B78	// 0x0001
{0x0F120000},   //	AfitBaseVals_3__0_		//	AFIT16_BRIGHTNESS                                    //AFIT 3                					0x70000B7A	// 0x0000
{0x0F120000},   //	AfitBaseVals_3__1_		//	AFIT16_CONTRAST                                                              					0x70000B7C	// 0x0000
{0x0F120000},   //	AfitBaseVals_3__2_		//	AFIT16_SATURATION                                                            					0x70000B7E	// 0x0000
{0x0F120000},   //	AfitBaseVals_3__3_		//	AFIT16_SHARP_BLUR                                                            					0x70000B80	// 0x0000
{0x0F120000},   //	AfitBaseVals_3__4_		//	AFIT16_GLAMOUR                                                               					0x70000B82	// 0x0000
{0x0F1200C0},   //	AfitBaseVals_3__5_		//	AFIT16_bnr_edge_high                                                         					0x70000B84	// 0x00C0
{0x0F120064},   //	AfitBaseVals_3__6_		//	AFIT16_postdmsc_iLowBright                                                   					0x70000B86	// 0x0032
{0x0F120384},   //	AfitBaseVals_3__7_		//	AFIT16_postdmsc_iHighBright                                                  					0x70000B88	// 0x0226
{0x0F120032},   //	AfitBaseVals_3__8_		//	AFIT16_postdmsc_iLowSat                                                      					0x70000B8A	// 0x0032
{0x0F1201F4},   //	AfitBaseVals_3__9_		//	AFIT16_postdmsc_iHighSat                                                     					0x70000B8C	// 0x01F4
{0x0F120070},   //	AfitBaseVals_3__10_		//	AFIT16_postdmsc_iTune                                                        					0x70000B8E	// 0x0070
{0x0F120040},   //	AfitBaseVals_3__11_		//	AFIT16_yuvemix_mNegRanges_0                                                  					0x70000B90	// 0x0060
{0x0F1200A0},   //	AfitBaseVals_3__12_		//	AFIT16_yuvemix_mNegRanges_1                                                  					0x70000B92	// 0x0100
{0x0F120100},   //	AfitBaseVals_3__13_		//	AFIT16_yuvemix_mNegRanges_2                                                  					0x70000B94	// 0x0200
{0x0F120010},   //	AfitBaseVals_3__14_		//	AFIT16_yuvemix_mPosRanges_0                                                  					0x70000B96	// 0x0020
{0x0F120060},   //	AfitBaseVals_3__15_		//	AFIT16_yuvemix_mPosRanges_1                                                  					0x70000B98	// 0x0060
{0x0F120100},   //	AfitBaseVals_3__16_		//	AFIT16_yuvemix_mPosRanges_2                                                  					0x70000B9A	// 0x0100
{0x0F121430},   //	AfitBaseVals_3__17_		//	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                              					0x70000B9C	// 0x1430
{0x0F120201},   //	AfitBaseVals_3__18_		//	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                         					0x70000B9E	// 0x0201
{0x0F120204},   //	AfitBaseVals_3__19_		//	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                    					0x70000BA0	// 0x0204
{0x0F121504},   //	AfitBaseVals_3__20_		//	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                        					0x70000BA2	// 0x0804
{0x0F12030F},   //	AfitBaseVals_3__21_		//	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                       					0x70000BA4	// 0x0108
{0x0F120003},   //	AfitBaseVals_3__22_		//	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                    					0x70000BA6	// 0x0101
{0x0F120902},   //	AfitBaseVals_3__23_		//	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                      					0x70000BA8	// 0x1806
{0x0F122004},   //	AfitBaseVals_3__24_		//	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                 					0x70000BAA	// 0x1007
{0x0F120050},   //	AfitBaseVals_3__25_		//	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                  					0x70000BAC	// 0x0040
{0x0F121140},   //	AfitBaseVals_3__26_		//	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                					0x70000BAE	// 0x1880
{0x0F12201C},   //	AfitBaseVals_3__27_		//	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh          					0x70000BB0	// 0x2030
{0x0F120620},   //	AfitBaseVals_3__28_		//	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed           					0x70000BB2	// 0x0820
{0x0F120306},   //	AfitBaseVals_3__29_		//	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh             					0x70000BB4	// 0x0304
{0x0F122003},   //	AfitBaseVals_3__30_		//	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                    					0x70000BB6	// 0x0003
{0x0F12FF01},   //	AfitBaseVals_3__31_		//	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit               					0x70000BB8	// 0xFF01
{0x0F120404},   //	AfitBaseVals_3__32_		//	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                    					0x70000BBA	// 0x0802
{0x0F120300},   //	AfitBaseVals_3__33_		//	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                         					0x70000BBC	// 0x0200
{0x0F12145A},   //	AfitBaseVals_3__34_		//	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                          					0x70000BBE	// 0x145A
{0x0F121010},   //	AfitBaseVals_3__35_		//	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                           					0x70000BC0	// 0x1010
{0x0F12000B},   //	AfitBaseVals_3__36_		//	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                              					0x70000BC2	// 0x020B
{0x0F121000},   //	AfitBaseVals_3__37_		//	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                              					0x70000BC4	// 0x1200
{0x0F125A0F},   //	AfitBaseVals_3__38_		//	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                         					0x70000BC6	// 0x5A0F
{0x0F120503},   //	AfitBaseVals_3__39_		//	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                      					0x70000BC8	// 0x0502
{0x0F121802},   //	AfitBaseVals_3__40_		//	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                              					0x70000BCA	// 0x180C
{0x0F120000},   //	AfitBaseVals_3__41_		//	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                        					0x70000BCC	// 0x0000
{0x0F122006},   //	AfitBaseVals_3__42_		//	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                        					0x70000BCE	// 0x3018
{0x0F123C28},   //	AfitBaseVals_3__43_		//	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                         					0x70000BD0	// 0x602A
{0x0F12042C},   //	AfitBaseVals_3__44_		//	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                               					0x70000BD2	// 0x0330
{0x0F120101},   //	AfitBaseVals_3__45_		//	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                         					0x70000BD4	// 0x0101
{0x0F12FF00},   //	AfitBaseVals_3__46_		//	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                        					0x70000BD6	// 0xFF00
{0x0F120904},   //	AfitBaseVals_3__47_		//	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                     					0x70000BD8	// 0x0004
{0x0F124008},   //	AfitBaseVals_3__48_		//	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                      					0x70000BDA	// 0x4000
{0x0F120540},   //	AfitBaseVals_3__49_		//	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                      					0x70000BDC	// 0x053F
{0x0F128006},   //	AfitBaseVals_3__50_		//	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                      					0x70000BDE	// 0x8006
{0x0F120020},   //	AfitBaseVals_3__51_		//	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                       					0x70000BE0	// 0x0020
{0x0F120000},   //	AfitBaseVals_3__52_		//	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                					0x70000BE2	// 0x0000
{0x0F121800},   //	AfitBaseVals_3__53_		//	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                    					0x70000BE4	// 0x1800
{0x0F120000},   //	AfitBaseVals_3__54_		//	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                 					0x70000BE6	// 0x0000
{0x0F121E10},   //	AfitBaseVals_3__55_		//	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                        					0x70000BE8	// 0x1E10
{0x0F12000B},   //	AfitBaseVals_3__56_		//	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                  					0x70000BEA	// 0x000C
{0x0F120607},   //	AfitBaseVals_3__57_		//	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                					0x70000BEC	// 0x0607
{0x0F120005},   //	AfitBaseVals_3__58_		//	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                					0x70000BEE	// 0x0005
{0x0F120607},   //	AfitBaseVals_3__59_		//	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                					0x70000BF0	// 0x0607
{0x0F120405},   //	AfitBaseVals_3__60_		//	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                 					0x70000BF2	// 0x0405
{0x0F120206},   //	AfitBaseVals_3__61_		//	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                  					0x70000BF4	// 0x0207
{0x0F120304},   //	AfitBaseVals_3__62_		//	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                  					0x70000BF6	// 0x0404
{0x0F120409},   //	AfitBaseVals_3__63_		//	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                					0x70000BF8	// 0x040C
{0x0F120305},   //	AfitBaseVals_3__64_		//	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y             					0x70000BFA	// 0x0306
{0x0F120406},   //	AfitBaseVals_3__65_		//	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y          					0x70000BFC	// 0x0C07
{0x0F122804},   //	AfitBaseVals_3__66_		//	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV         					0x70000BFE	// 0x1808
{0x0F120228},   //	AfitBaseVals_3__67_		//	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y          					0x70000C00	// 0x0812
{0x0F121402},   //	AfitBaseVals_3__68_		//	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV           					0x70000C02	// 0x1006
{0x0F120618},   //	AfitBaseVals_3__69_		//	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL           					0x70000C04	// 0x0010
{0x0F121402},   //	AfitBaseVals_3__70_		//	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL           					0x70000C06	// 0x1E00
{0x0F128018},   //	AfitBaseVals_3__71_		//	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower           					0x70000C08	// 0x801A
{0x0F120080},   //	AfitBaseVals_3__72_		//	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce               					0x70000C0A	// 0x0080
{0x0F120080},   //	AfitBaseVals_3__73_		//	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                   					0x70000C0C	// 0x0080
{0x0F120180},   //	AfitBaseVals_3__74_		//	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                       					0x70000C0E	// 0x0180
{0x0F120A0A},   //	AfitBaseVals_3__75_		//	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                        					0x70000C10	// 0x0A0A
{0x0F120101},   //	AfitBaseVals_3__76_		//	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                    					0x70000C12	// 0x0101
{0x0F121117},   //	AfitBaseVals_3__77_		//	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                     					0x70000C14	// 0x0E1B
{0x0F126024},   //	AfitBaseVals_3__78_		//	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                     					0x70000C16	// 0x4848
{0x0F120A0A},   //	AfitBaseVals_3__79_		//	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                       					0x70000C18	// 0x2020
{0x0F12FFFF},   //	AfitBaseVals_3__80_		//	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                     					0x70000C1A	// 0xFFFF
{0x0F120808},   //	AfitBaseVals_3__81_		//	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                					0x70000C1C	// 0x0808
{0x0F120A01},   //	AfitBaseVals_3__82_		//	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin               					0x70000C1E	// 0x0A01
{0x0F12010A},   //	AfitBaseVals_3__83_		//	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin              					0x70000C20	// 0x010A
{0x0F121501},   //	AfitBaseVals_3__84_		//	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin             					0x70000C22	// 0x1B01
{0x0F12240F},   //	AfitBaseVals_3__85_		//	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin             					0x70000C24	// 0x480E
{0x0F120A60},   //	AfitBaseVals_3__86_		//	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin              					0x70000C26	// 0x2048
{0x0F12FF0A},   //	AfitBaseVals_3__87_		//	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin              					0x70000C28	// 0xFF20
{0x0F1208FF},   //	AfitBaseVals_3__88_		//	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin         					0x70000C2A	// 0x08FF
{0x0F120008},   //	AfitBaseVals_3__89_		//	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                          					0x70000C2C	// 0x0008
{0x0F120001},   //	AfitBaseVals_3__90_		//	AFITB_bnr_nClustLevel_C      [0]                                             					0x70000C2E	// 0x0001
{0x0F120000},   //	AfitBaseVals_4__0_		//	AFIT16_BRIGHTNESS                                      //AFIT 4              					0x70000C30	// 0x0000
{0x0F120000},   //	AfitBaseVals_4__1_		//	AFIT16_CONTRAST                                                              					0x70000C32	// 0x000F
{0x0F120000},   //	AfitBaseVals_4__2_		//	AFIT16_SATURATION                                                            					0x70000C34	// 0x0000
{0x0F120000},   //	AfitBaseVals_4__3_		//	AFIT16_SHARP_BLUR                                                            					0x70000C36	// 0x0000
{0x0F120000},   //	AfitBaseVals_4__4_		//	AFIT16_GLAMOUR                                                               					0x70000C38	// 0x0000
{0x0F1200C0},   //	AfitBaseVals_4__5_		//	AFIT16_bnr_edge_high                                                         					0x70000C3A	// 0x00C0
{0x0F120064},   //	AfitBaseVals_4__6_		//	AFIT16_postdmsc_iLowBright                                                   					0x70000C3C	// 0x0032
{0x0F120384},   //	AfitBaseVals_4__7_		//	AFIT16_postdmsc_iHighBright                                                  					0x70000C3E	// 0x0226
{0x0F120032},   //	AfitBaseVals_4__8_		//	AFIT16_postdmsc_iLowSat                                                      					0x70000C40	// 0x0032
{0x0F1201F4},   //	AfitBaseVals_4__9_		//	AFIT16_postdmsc_iHighSat                                                     					0x70000C42	// 0x01F4
{0x0F120070},   //	AfitBaseVals_4__10_		//	AFIT16_postdmsc_iTune                                                        					0x70000C44	// 0x0070
{0x0F120040},   //	AfitBaseVals_4__11_		//	AFIT16_yuvemix_mNegRanges_0                                                  					0x70000C46	// 0x0060
{0x0F1200A0},   //	AfitBaseVals_4__12_		//	AFIT16_yuvemix_mNegRanges_1                                                  					0x70000C48	// 0x0100
{0x0F120100},   //	AfitBaseVals_4__13_		//	AFIT16_yuvemix_mNegRanges_2                                                  					0x70000C4A	// 0x0200
{0x0F120010},   //	AfitBaseVals_4__14_		//	AFIT16_yuvemix_mPosRanges_0                                                  					0x70000C4C	// 0x0028
{0x0F120060},   //	AfitBaseVals_4__15_		//	AFIT16_yuvemix_mPosRanges_1                                                  					0x70000C4E	// 0x00A0
{0x0F120100},   //	AfitBaseVals_4__16_		//	AFIT16_yuvemix_mPosRanges_2                                                  					0x70000C50	// 0x0140
{0x0F121430},   //	AfitBaseVals_4__17_		//	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                              					0x70000C52	// 0x1430
{0x0F120201},   //	AfitBaseVals_4__18_		//	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                         					0x70000C54	// 0x0201
{0x0F120204},   //	AfitBaseVals_4__19_		//	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                    					0x70000C56	// 0x0204
{0x0F120F04},   //	AfitBaseVals_4__20_		//	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                        					0x70000C58	// 0x1004
{0x0F12030C},   //	AfitBaseVals_4__21_		//	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                       					0x70000C5A	// 0x0110
{0x0F120003},   //	AfitBaseVals_4__22_		//	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                    					0x70000C5C	// 0x0001
{0x0F120602},   //	AfitBaseVals_4__23_		//	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                      					0x70000C5E	// 0x1806
{0x0F121803},   //	AfitBaseVals_4__24_		//	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                 					0x70000C60	// 0x0006
{0x0F120040},   //	AfitBaseVals_4__25_		//	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                  					0x70000C62	// 0x0030
{0x0F120E20},   //	AfitBaseVals_4__26_		//	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                					0x70000C64	// 0x0E20
{0x0F122018},   //	AfitBaseVals_4__27_		//	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh          					0x70000C66	// 0x202C
{0x0F120620},   //	AfitBaseVals_4__28_		//	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed           					0x70000C68	// 0x0820
{0x0F120306},   //	AfitBaseVals_4__29_		//	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh             					0x70000C6A	// 0x0304
{0x0F122003},   //	AfitBaseVals_4__30_		//	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                    					0x70000C6C	// 0x0003
{0x0F12FF01},   //	AfitBaseVals_4__31_		//	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit               					0x70000C6E	// 0xFF01
{0x0F120404},   //	AfitBaseVals_4__32_		//	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                    					0x70000C70	// 0x0A04
{0x0F120200},   //	AfitBaseVals_4__33_		//	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                         					0x70000C72	// 0x0200
{0x0F12145A},   //	AfitBaseVals_4__34_		//	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                          					0x70000C74	// 0x145A
{0x0F121010},   //	AfitBaseVals_4__35_		//	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                           					0x70000C76	// 0x1010
{0x0F12000B},   //	AfitBaseVals_4__36_		//	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                              					0x70000C78	// 0x000B
{0x0F121200},   //	AfitBaseVals_4__37_		//	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                              					0x70000C7A	// 0x1200
{0x0F125A0F},   //	AfitBaseVals_4__38_		//	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                         					0x70000C7C	// 0x5A0F
{0x0F120502},   //	AfitBaseVals_4__39_		//	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                      					0x70000C7E	// 0x0502
{0x0F121802},   //	AfitBaseVals_4__40_		//	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                              					0x70000C80	// 0x180C
{0x0F120000},   //	AfitBaseVals_4__41_		//	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                        					0x70000C82	// 0x0000
{0x0F122006},   //	AfitBaseVals_4__42_		//	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                        					0x70000C84	// 0x3018
{0x0F124028},   //	AfitBaseVals_4__43_		//	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                         					0x70000C86	// 0x482A
{0x0F120430},   //	AfitBaseVals_4__44_		//	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                               					0x70000C88	// 0x0252
{0x0F120101},   //	AfitBaseVals_4__45_		//	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                         					0x70000C8A	// 0x0101
{0x0F12FF00},   //	AfitBaseVals_4__46_		//	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                        					0x70000C8C	// 0xFF00
{0x0F120804},   //	AfitBaseVals_4__47_		//	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                     					0x70000C8E	// 0x0204
{0x0F124008},   //	AfitBaseVals_4__48_		//	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                      					0x70000C90	// 0x4000
{0x0F120540},   //	AfitBaseVals_4__49_		//	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                      					0x70000C92	// 0x053F
{0x0F128006},   //	AfitBaseVals_4__50_		//	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                      					0x70000C94	// 0x8008
{0x0F120020},   //	AfitBaseVals_4__51_		//	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                       					0x70000C96	// 0x0020
{0x0F120000},   //	AfitBaseVals_4__52_		//	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                					0x70000C98	// 0x0000
{0x0F121800},   //	AfitBaseVals_4__53_		//	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                    					0x70000C9A	// 0x1800
{0x0F120000},   //	AfitBaseVals_4__54_		//	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                 					0x70000C9C	// 0x0000
{0x0F121E10},   //	AfitBaseVals_4__55_		//	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                        					0x70000C9E	// 0x1E10
{0x0F12000B},   //	AfitBaseVals_4__56_		//	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                  					0x70000CA0	// 0x000C
{0x0F120607},   //	AfitBaseVals_4__57_		//	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                					0x70000CA2	// 0x0607
{0x0F120005},   //	AfitBaseVals_4__58_		//	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                					0x70000CA4	// 0x0005
{0x0F120607},   //	AfitBaseVals_4__59_		//	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                					0x70000CA6	// 0x0607
{0x0F120405},   //	AfitBaseVals_4__60_		//	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                 					0x70000CA8	// 0x0405
{0x0F120205},   //	AfitBaseVals_4__61_		//	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                  					0x70000CAA	// 0x0207
{0x0F120304},   //	AfitBaseVals_4__62_		//	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                  					0x70000CAC	// 0x0404
{0x0F120409},   //	AfitBaseVals_4__63_		//	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                					0x70000CAE	// 0x040F
{0x0F120306},   //	AfitBaseVals_4__64_		//	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y             					0x70000CB0	// 0x0306
{0x0F120407},   //	AfitBaseVals_4__65_		//	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y          					0x70000CB2	// 0x0C06
{0x0F122C04},   //	AfitBaseVals_4__66_		//	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV         					0x70000CB4	// 0x1208
{0x0F12022C},   //	AfitBaseVals_4__67_		//	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y          					0x70000CB6	// 0x0812
{0x0F121402},   //	AfitBaseVals_4__68_		//	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV           					0x70000CB8	// 0x1006
{0x0F120618},   //	AfitBaseVals_4__69_		//	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL           					0x70000CBA	// 0x0410
{0x0F121402},   //	AfitBaseVals_4__70_		//	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL           					0x70000CBC	// 0x1E01
{0x0F128018},   //	AfitBaseVals_4__71_		//	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower           					0x70000CBE	// 0x8018
{0x0F120080},   //	AfitBaseVals_4__72_		//	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce               					0x70000CC0	// 0x0080
{0x0F120080},   //	AfitBaseVals_4__73_		//	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                   					0x70000CC2	// 0x0080
{0x0F120180},   //	AfitBaseVals_4__74_		//	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                       					0x70000CC4	// 0x0180
{0x0F120A0A},   //	AfitBaseVals_4__75_		//	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                        					0x70000CC6	// 0x0A0A
{0x0F120101},   //	AfitBaseVals_4__76_		//	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                    					0x70000CC8	// 0x0101
{0x0F120C0F},   //	AfitBaseVals_4__77_		//	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                     					0x70000CCA	// 0x0C18
{0x0F126024},   //	AfitBaseVals_4__78_		//	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                     					0x70000CCC	// 0x4848
{0x0F120808},   //	AfitBaseVals_4__79_		//	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                       					0x70000CCE	// 0x2020
{0x0F12FFFF},   //	AfitBaseVals_4__80_		//	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                     					0x70000CD0	// 0xFFFF
{0x0F120808},   //	AfitBaseVals_4__81_		//	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                					0x70000CD2	// 0x0808
{0x0F120A01},   //	AfitBaseVals_4__82_		//	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin               					0x70000CD4	// 0x0A01
{0x0F12010A},   //	AfitBaseVals_4__83_		//	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin              					0x70000CD6	// 0x010A
{0x0F120F01},   //	AfitBaseVals_4__84_		//	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin             					0x70000CD8	// 0x1801
{0x0F12240C},   //	AfitBaseVals_4__85_		//	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin             					0x70000CDA	// 0x480C
{0x0F120860},   //	AfitBaseVals_4__86_		//	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin              					0x70000CDC	// 0x2048
{0x0F12FF08},   //	AfitBaseVals_4__87_		//	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin              					0x70000CDE	// 0xFF20
{0x0F1208FF},   //	AfitBaseVals_4__88_		//	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin         					0x70000CE0	// 0x08FF
{0x0F120008},   //	AfitBaseVals_4__89_		//	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                          					0x70000CE2	// 0x0008
{0x0F120001},   //	AfitBaseVals_4__90_		//	AFITB_bnr_nClustLevel_C      [0]   bWideWide[1]                              					0x70000CE4	// 0x0001
                                          //	"[0]CAFITB_bnr_bypass                                                        
{0x0F1223CE},       
{0x0F12FDC8},	       
{0x0F12112E},	       
{0x0F1293A5},	       
{0x0F12FE67},	       
{0x0F120000},          
                
{0xFCFCD000},          
{0x00287000},
{0x002A01A2},
{0x0F120A0A},

{0xFCFCD000},
{0x00040001},

};

s5k4ecgx_short_t s5k4ecgx_DTP_init[] = {
{0xFCFCD000},
{0x0028D000},
{0x002AB054},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_DTP_stop[] = {
{0xFCFCD000},
{0x0028D000},
{0x002AB054},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_FPS_Auto[] = {
{0xFCFCD000},
{0x00287000},	
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F12029A},
{0x0F12014D},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_FPS_5[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_7[] = {
{0xFCFCD000},
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F120535},
{0x0F120535},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_FPS_10[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_15[] = {
{0xFCFCD000},
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F12029A},
{0x0F12029A},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_FPS_20[] = {
{0xFCFCD000},     
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F1201F4},
{0x0F1201F4},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_FPS_24[] = {
{0xFCFCD000},
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F1201A1},
{0x0F1201A1},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};


s5k4ecgx_short_t s5k4ecgx_FPS_25[] = {
{0xFCFCD000},
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F120190},
{0x0F120190},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_FPS_30[] = {
{0xFCFCD000},
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F12014D},
{0x0F12014D},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0268},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_FPS_60[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_120[] = {

};

s5k4ecgx_short_t s5k4ecgx_Effect_Normal[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Solarization[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120002}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Negative[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120003}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Sepia[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Black_White[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120001}
};


s5k4ecgx_short_t s5k4ecgx_WB_Auto[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E6},
{0x0f12077F}
};

s5k4ecgx_short_t s5k4ecgx_WB_Sunny[] = {
{0xFCFCD000},
{0x00287000},
{0x002A04E6},
{0x0f120777},
{0x002A04BA},
{0x0f1205E0},
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120530},
{0x0f120001},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_WB_Cloudy[] = {
{0xFCFCD000},
{0x00287000},	
{0x002A04E6},	
{0x0F120777},
{0x002A04BA},
{0x0F120710},	
{0x0F120001},	
{0x0F120400},	
{0x0F120001},	
{0x0F120420},	
{0x0F120001},	
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_WB_Tungsten[] = {
{0xFCFCD000},
{0x00287000},
{0x002A04E6},
{0x0F120777},
{0x002A04BA},
{0x0F120390},
{0x0F120001},
{0x0F120400},
{0x0F120001},
{0x0F120920},
{0x0F120001},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_WB_Fluorescent[] = {
{0xFCFCD000},
{0x00287000},
{0x002A04E6},
{0x0F120777},
{0x002A04BA},
{0x0F120505},
{0x0F120001},
{0x0F120400},
{0x0F120001},
{0x0F120875},
{0x0F120001},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_WDR_on[] = {
	{0x00287000},
	{0x002A1BEA},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_WDR_off[] = {
	{0x00287000},
	{0x002A1BEA},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_ISO_Auto[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A0938},
	{0x0F120000},
	{0x002A0F2A},
	{0x0F120001},
	{0x002A04E6},
	{0x0F12077F},
	{0x002A04D0},
	{0x0F120000},
	{0x002A04D0},
	{0x0F120000},
	{0x0F120000},
	{0x0F120001},
	{0x002A06C2},
	{0x0F120200},
};

s5k4ecgx_short_t s5k4ecgx_ISO_50[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0938},
{0x0F120001},   //afit_bUseNB_Afit
{0x0F120014},   //SARR_uNormBrInDoor_0_
{0x0F1200D2},   //SARR_uNormBrInDoor_1_
{0x0F120384},   //SARR_uNormBrInDoor_2_
{0x0F1207D0},   //SARR_uNormBrInDoor_3_
{0x0F121388},   //SARR_uNormBrInDoor_4_

{0x002A04E6},
{0x0F12065F},   //REG_TC_DBG_AutoAlgEnBits
{0x002A04D6},   
{0x0F120000},   //REG_SF_USER_FlickerQuant       
{0x0F120001},   //REG_SF_USER_FlickerQuantChanged
                
{0x002A04D0},   
{0x0F120001},   //REG_SF_USER_IsoType    
{0x0F120100},   //REG_SF_USER_IsoVal     
{0x0F120001},   //REG_SF_USER_IsoChanged 
{0x002A06C2},                            
{0x0F120100},   //lt_bUseSecISODgain  
};

s5k4ecgx_short_t s5k4ecgx_ISO_100[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A04E6},
	{0x0F12065F},
	{0x002A04D6},
	{0x0F120000},
	{0x0F120001},
	{0x002A04D0},
	{0x0F120001},
	{0x0F1201A0},
	{0x0F120001},
	{0x002A06C2},
	{0x0F120100},
	{0x002A0938},
	{0x0F120001},

};

s5k4ecgx_short_t s5k4ecgx_ISO_200[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A04E6},
	{0x0F12065F},
	{0x002A04D6},
	{0x0F120000},
	{0x0F120001},
	{0x002A04D0},
	{0x0F120001},
	{0x0F120340},
	{0x0F120001},
	{0x002A06C2},
	{0x0F120100},
	{0x002A0938},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_ISO_400[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A04E6},
	{0x0F12065F},
	{0x002A04D6},
	{0x0F120000},
	{0x0F120001},
	{0x002A04D0},
	{0x0F120001},
	{0x0F120680},
	{0x0F120001},
	{0x002A06C2},
	{0x0F120100},
	{0x002A0938},
	{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_Metering_Matrix[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A1492},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
};

s5k4ecgx_short_t s5k4ecgx_Metering_Center[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A1492},
	{0x0F120000},
	{0x0F120101},
	{0x0F120101},
	{0x0F120000},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120201},
	{0x0F120303},
	{0x0F120303},
	{0x0F120102},
	{0x0F120201},
	{0x0F120403},
	{0x0F120304},
	{0x0F120102},
	{0x0F120201},
	{0x0F120403},
	{0x0F120304},
	{0x0F120102},
	{0x0F120201},
	{0x0F120403},
	{0x0F120304},
	{0x0F120102},
	{0x0F120201},
	{0x0F120303},
	{0x0F120303},
	{0x0F120102},
	{0x0F120201},
	{0x0F120202},
	{0x0F120202},
	{0x0F120102},
};

s5k4ecgx_short_t s5k4ecgx_Metering_Spot[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A1492},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120101},
	{0x0F120101},
	{0x0F120000},
	{0x0F120000},
	{0x0F12010F},
	{0x0F120F01},
	{0x0F120000},
	{0x0F120000},
	{0x0F12010F},
	{0x0F120F01},
	{0x0F120000},
	{0x0F120000},
	{0x0F120101},
	{0x0F120101},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F12FF30}
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F12FFA0}
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F12FFC8}
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F12FFE0}
};

s5k4ecgx_short_t s5k4ecgx_EV_Default[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F120020}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F120038}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F120060}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0230},
{0x0F12007F}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_4[] = { 
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F12FF81},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_3[] = { 
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F12FFA0},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_2[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F12FFC0},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_1[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F12FFE0},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Default[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_1[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F120020},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_2[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_3[] = { // Setting Unavailable
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F120060},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_4[] = { // Setting Unavailable
	{0xFCFCD000},
	{0x00287000},
	{0x002A0232},
	{0x0F12007F},
};

s5k4ecgx_short_t s5k4ecgx_Auto_Contrast_ON[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Auto_Contrast_OFF[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_3[] = { // Setting Unavailable
	{0x00287000},
	{0x002A0A28},
	{0x0F120000},
	{0x002A0ADE},
	{0x0F120000},
	{0x002A0B94},
	{0x0F120000},
	{0x002A0C4A},
	{0x0F120000},
	{0x002A0D00},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_2[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F122010},
	{0x002A0ADE},
	{0x0F122010},
	{0x002A0B94},
	{0x0F122010},
	{0x002A0C4A},
	{0x0F122010},
	{0x002A0D00},
	{0x0F122010},
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_1[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F124020},
	{0x002A0ADE},
	{0x0F124020},
	{0x002A0B94},
	{0x0F124020},
	{0x002A0C4A},
	{0x0F124020},
	{0x002A0D00},
	{0x0F124020},
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Default[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F126024},
	{0x002A0ADE},
	{0x0F126024},
	{0x002A0B94},
	{0x0F126024},
	{0x002A0C4A},
	{0x0F126024},
	{0x002A0D00},
	{0x0F126024},
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_1[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F128040},
	{0x002A0ADE},
	{0x0F128040},
	{0x002A0B94},
	{0x0F128040},
	{0x002A0C4A},
	{0x0F128040},
	{0x002A0D00},
	{0x0F128040},
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_2[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F12A060},
	{0x002A0ADE},
	{0x0F12A060},
	{0x002A0B94},
	{0x0F12A060},
	{0x002A0C4A},
	{0x0F12A060},
	{0x002A0D00},
	{0x0F12A060},
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_3[] = { 
	{0x00287000},
	{0x002A0A28},
	{0x0F12C080},
	{0x002A0ADE},
	{0x0F12C080},
	{0x002A0B94},
	{0x0F12C080},
	{0x002A0C4A},
	{0x0F12C080},
	{0x002A0D00},
	{0x0F12C080},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Minus_2[] = {
	{0x00287000},
	{0x002A0234},
	{0x0F12FF81},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Minus_1[] = {
	{0x00287000},
	{0x002A0234},
	{0x0F12FFC0},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Default[] = {
	{0x00287000},
	{0x002A0234},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Plus_1[] = {
	{0x00287000},
	{0x002A0234},
	{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Plus_2[] = {
	{0x00287000},
	{0x002A0234},
	{0x0F12007F},
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_High[] = {
	{0x00287000},
	{0x002A0478},
	{0x0F12005F},
	{0x0F12005F},
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_Normal[] = {
	{0x00287000},
	{0x002A0478},
	{0x0F120050},
	{0x0F120050},
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_Low[] = {
	{0x00287000},
	{0x002A0478},
	{0x0F12004B},
	{0x0F12004B},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Default[] = {
{0x00287000},
{0x002A1492},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120303},
{0x0F120303},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120403},
{0x0F120304},
{0x0F120102},
{0x0F120201},
{0x0F120303},
{0x0F120303},
{0x0F120102},
{0x0F120201},
{0x0F120202},
{0x0F120202},
{0x0F120102},
{0x002A0938},	
{0x0F120000},
{0x002A06B8},
{0x0F12452C},
{0x0F120004},
{0x002A0F2A},
{0x0F120001},
{0x002A0F30},
{0x0F120001},
{0x002A04E6},
{0x0F12077F},
{0x002A04D0},
{0x0F120000},
{0x002A04D0},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x002A06C2},
{0x0F120200},
{0x002A2C66},
{0x0F120001},
{0x002A1484},
{0x0F12003C},
{0x002A148A},
{0x0F12000F},
{0x002A058C},
{0x0F123520},
{0x0F120000},
{0x0F12C350},
{0x0F120000},
{0x0F123520},
{0x0F120000},
{0x0F12C350},
{0x0F120000},
{0x0F120470},
{0x0F120C00},
{0x0F120100},
{0x0F121000},
{0x002A0544},
{0x0F120111},
{0x0F1200EF},
{0x002A0608},
{0x0F120000},
{0x0F120001},
{0x002A0A28},
{0x0F126024},
{0x002A0ADE},
{0x0F126024},
{0x002A0B94},
{0x0F126024},
{0x002A0C4A},
{0x0F126024},
{0x002A0D00},
{0x0F126024},
{0x002A0234},
{0x0F120000},
{0x002A0638},
{0x0F120001},
{0x0F120000},
{0x002A063C},
{0x0F120A3C},
{0x0F120000},
{0x002A0640},
{0x0F120D05},
{0x0F120000},
{0x002A0644},
{0x0F123408},
{0x0F120000},	
{0x002A0648},	
{0x0F123408},	
{0x0F120000},	
{0x002A064C},	
{0x0F126810},	
{0x0F120000},	
{0x002A0650},
{0x0F128214},
{0x0F120000},	
{0x002A0654},	
{0x0F12C350},	
{0x0F120000},	
{0x002A0658},	
{0x0F12C350},	
{0x0F120000},	
{0x002A065C},	
{0x0F12C350},	
{0x0F120000},	
{0x002A03B4},	
{0x0F120535},	
{0x0F12029A},	
{0x002A0266},	
{0x0F120000},	
{0x002A026A},	
{0x0F120001},	
{0x002A024E},	
{0x0F120001},	
{0x002A0268},	
{0x0F120001},	
{0x002A0270},	
{0x0F120001},	
{0x002A023E},	
{0x0F120001},	
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Portrait[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F124020},
	{0x002A0ADE},
	{0x0F124020},
	{0x002A0B94},
	{0x0F124020},
	{0x002A0C4A},
	{0x0F124020},
	{0x002A0D00},
	{0x0F124020},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Nightshot[] = {
	{0x00287000},
	{0x002A06B8},
	{0x0F12FFFF},
	{0x0F1200FF},

	{0x002A0608},
	{0x0F120000},
	{0x0F120000},

	{0x002A058C},
	{0x0F12F424},
	{0x0F120001},
	{0x0F12F424},
	{0x0F120001},
	{0x0F12F424},
	{0x0F120001},
	{0x0F12F424},
	{0x0F120001},
	{0x0F120100},
	{0x0F120700},
	{0x0F120100},
	{0x0F122000},

	{0x002A03B4},
	{0x0F121388},
	{0x0F121388},
	{0x002A02C2},
	{0x0F1209C4},
	{0x0F12014D},
	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},
	{0x002A023E},
	{0x0F120001},
	{0x0F120001},

	{0x002A0A1E},
	{0x0F121580},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Backlight[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A1492},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120101},
	{0x0F120101},
	{0x0F120000},
	{0x0F120000},
	{0x0F12010F},
	{0x0F120F01},
	{0x0F120000},
	{0x0F120000},
	{0x0F12010F},
	{0x0F120F01},
	{0x0F120000},
	{0x0F120000},
	{0x0F120101},
	{0x0F120101},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Landscape[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A1492},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x0F120101},
	{0x002A0A28},
	{0x0F128040},
	{0x002A0ADE},
	{0x0F128040},
	{0x002A0B94},
	{0x0F128040},
	{0x002A0C4A},
	{0x0F128040},
	{0x002A0D00},
	{0x0F128040},
	{0x002A0234},
	{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Sports[] = {
	{0x00287000},
	{0x002A0608},
	{0x0F120000},
	{0x0F120000},

	{0x002A058C},
	{0x0F123520},
	{0x0F120000},
	{0x0F123520},
	{0x0F120000},
	{0x0F123520},
	{0x0F120000},
	{0x0F123520},
	{0x0F120000},
	{0x0F120200},
	{0x0F120200},
	{0x0F120200},
	{0x0F120200},

	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},
	{0x002A023E},
	{0x0F120001},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Party_Indoor[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A04E6},
	{0x0F12065F},
	{0x002A04D6},
	{0x0F120000},
	{0x0F120001},

	{0x002A04D0},
	{0x0F120001},
	{0x0F120340},
	{0x0F120001},
	{0x002A06C2},
	{0x0F120100},

	{0x002A0938},
	{0x0F120001},

	{0x002A0234},
	{0x0F120031},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Beach_Snow[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A04E6},
	{0x0F12065F},
	{0x002A04D6},
	{0x0F120000},
	{0x0F120001},
	{0x002A04D0},
	{0x0F120001},
	{0x0F1200D0},
	{0x0F120001},
	{0x002A06C2},
	{0x0F120100},

	{0x002A0938},
	{0x0F120001},

	{0x002A0234},
	{0x0F120031},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Sunset[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A2C66},
	{0x0F120000},

	{0x002A04BA},
	{0x0F1205E0},
	{0x0F120001},
	{0x0F120400},
	{0x0F120001},
	{0x0F120520},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Duskdawn[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A2C66},
	{0x0F120000},

	{0x002A04BA},
	{0x0F120575},
	{0x0F120001},
	{0x0F120400},
	{0x0F120001},
	{0x0F120835},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Fall_Color[] = {
	{0x00287000},
	{0x002A0234},
	{0x0F12007F},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Fireworks[] = {
	{0x00287000},
	{0x002A0638},
	{0x0F120001},
	{0x0F120000},
	{0x002A063C},
	{0x0F121478},
	{0x0F120000},
	{0x002A0640},
	{0x0F121A0A},
	{0x0F120000},
	{0x002A0644},
	{0x0F126810},
	{0x0F120000},
	{0x002A0648},
	{0x0F126810},
	{0x0F120000},
	{0x002A064C},
	{0x0F12D020},
	{0x0F120000},
	{0x002A0650},
	{0x0F120428},
	{0x0F120001},
	{0x002A0654},
	{0x0F121A80},
	{0x0F120006},
	{0x002A0658},
	{0x0F121A80},
	{0x0F120006},
	{0x002A065C},
	{0x0F121A80},
	{0x0F120006},

	{0x002A03B4},
	{0x0F122710},
	{0x0F122710},

	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},
	{0x002A023E},
	{0x0F120001},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Text[] = {
	{0x00287000},
	{0x002A0A28},
	{0x0F12A060},
	{0x002A0ADE},
	{0x0F12A060},
	{0x002A0B94},
	{0x0F12A060},
	{0x002A0C4A},
	{0x0F12A060},
	{0x002A0D00},
	{0x0F12A060},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Candle_Light[] = {
	{0xFCFCD000},
	{0x00287000},
	{0x002A04E6},
	{0x0F120777},
	{0x002A04BA},
	{0x0F1205E0},
	{0x0F120001},
	{0x0F120400},
	{0x0F120001},
	{0x0F120530},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Night_Mode_On[] = {
{0x00287000},
{0x002A062C},
{0x0F120D40},
{0x0F120003},
{0x002A0630},
{0x0F120D40},
{0x0F120003},
{0x002A0634},
{0x0F120D40},
{0x0F120003},
{0x002A0638},
{0x0F120D40},
{0x0F120003},
{0x002A063C},
{0x0F120D40},
{0x0F120003},
{0x002A0640},
{0x0F120D40},
{0x0F120003},
{0x002A0644},
{0x0F120D40},
{0x0F120003},
{0x002A0648},
{0x0F120D40},
{0x0F120003},
{0x002A064C},
{0x0F120D40},
{0x0F120003},
{0x002A0650},
{0x0F120D40},
{0x0F120003},
{0x002A03AE},
{0x0F121388},
{0x0F121388},
{0x002A0262},
{0x0F120000},
{0x002A0266},
{0x0F120001},
{0x002A024A},
{0x0F120001},
{0x002A0264},
{0x0F120001},
{0x002A026C},
{0x0F120001},
{0x002A023A},
{0x0F120001},
{0x0F120001},

{0x002A09EA},
{0x0F121580}
};

s5k4ecgx_short_t s5k4ecgx_Night_Mode_Off[] = {
{0x00287000},
{0x002A062C},
{0x0F120001},
{0x0F120000},
{0x002A0630},
{0x0F120A3C},
{0x0F120000},
{0x002A0634},
{0x0F120D05},
{0x0F120000},
{0x002A0638},
{0x0F123408},
{0x0F120000},
{0x002A063C},
{0x0F123408},
{0x0F120000},
{0x002A0640},
{0x0F126810},
{0x0F120000},
{0x002A0644},
{0x0F128214},
{0x0F120000},
{0x002A0648},
{0x0F12C350},
{0x0F120000},
{0x002A064C},
{0x0F12C350},
{0x0F120000},
{0x002A0650},
{0x0F12C350},
{0x0F120000},

{0x002A03AE},
{0x0F120535},
{0x0F12029A},
{0x002A0262},
{0x0F120000},
{0x002A0266},
{0x0F120001},
{0x002A024A},
{0x0F120001},
{0x002A0264},
{0x0F120001},
{0x002A026C},
{0x0F120001},
{0x002A023A},
{0x0F120001},
{0x0F120001},


{0x002A09EA},
{0x0F120080}
};



s5k4ecgx_short_t s5k4ecgx_AF_Return_Inf_pos[] = {

	{0x00287000},
	{0x002A15D6},
	{0x0F12D000},
};

s5k4ecgx_short_t s5k4ecgx_AF_Return_Macro_pos[] = {
	{0x00287000},
	{0x002A15E8},
	{0x0F120018},
	{0x0F12002A},
	{0x0F120030},
	{0x0F120036},
	{0x0F12003C},
	{0x0F120042},
	{0x0F120048},
	{0x0F12004E},
	{0x0F120054},
	{0x0F12005A},
	{0x0F120060},
	{0x0F120066},
	{0x0F12006C},
	{0x0F120072},
	{0x0F120078},
	{0x0F12007E},
	{0x0F120084},
	{0x0F12008A},
	{0x0F120090},
	{0x0F120096},
	{0x0F12009C},
	{0x0F1200A2},
	{0x0F1200A8},
	{0x0F1200AE},
	{0x0F1200B4},
	{0x0F1200BA},
};



s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_1[] = {
	{0x00287000},
	{0x002A028E},
	{0x0F120000},
	{0x00287000},
	{0x002A028C},
	{0x0F120004},
	{0x00287000},
	{0x002A1648},
	{0x0F129002},

};

s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_2[] = {
{0x002A0286},
{0x0F120004}
};


s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_3[] = {
{0x002A160C},
{0x0F121002}

};

s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_4[] = {
{0x002A160C},   //af search single AFflag
{0x0F129002}    //0x1002 = Normal Mode, 2nd search ON 

};

s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_1[] = {

{0x00287000},
{0x002A0288},
{0x0F1200D0}
};

s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_2[] = {
{0x002A0286},
{0x0F120004}
};


s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_3[] = {
{0x002A160C},
{0x0F121042},
{0x002A159E},
{0x0F121700}

};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_1[] = {
	{0x00287000},
	{0x002A028E},
	{0x0F120000},
	{0x00287000},
	{0x002A028C},
	{0x0F120004},
	{0x00287000},
	{0x002A1648},
	{0x0F129002},
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_2[] = {
{0x002A0286},
{0x0F120004}
};
s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_3[] = {
{0x002A160C},
{0x0F121002}
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_1[] = {
	{0x00287000},
	{0x002A028E},
	{0x0F1200D0},
	{0x00287000},
	{0x002A028C},
	{0x0F120004},
	{0x00287000},
	{0x002A1648},
	{0x0F129042},
	{0x002A15DA},
	{0x0F120C00},
};


s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_2[] = {
{0x002A0286},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_3[] = {
{0x002A160C},
{0x0F121042},
{0x002A159E},
{0x0F120F00}

};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Start[] = {
	{0x00287000},
	{0x002A028C},
	{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_awb_ae_lock[] = {
	{0x00287000},
	{0x002A2C5E},
	{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_awb_ae_unlock[] = {
	{0x00287000},
	{0x002A2C5E},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_1[] = {
	{0x00287000},
	{0x002A028E},
	{0x0F120000},
	{0x00287000},
	{0x002A028C},
	{0x0F120004},
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_2[] = {
{0x002A0286},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_3[] = {
{0x002A0286},
{0x0F120002}
};

s5k4ecgx_short_t s5k4ecgx_Face_Detection_On[] = {
	{0x00287000},
	{0x002A0294},
	{0x0F120100},
	{0x0F1200E3},
	{0x0F120200},
	{0x0F120238},
	{0x0F1201C6},
	{0x0F120166},
	{0x0F120074},
	{0x0F120132},
	{0x0F120001},
};



s5k4ecgx_short_t s5k4ecgx_Face_Detection_Off[] = {
	{0x00287000},
	{0x002A0294},
	{0x0F120100},
	{0x0F1200E3},
	{0x0F120200},
	{0x0F120238},
	{0x0F1201C6},
	{0x0F120166},
	{0x0F120074},
	{0x0F120132},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Low_Cap_On[] = {
	{0x00287000},
	{0x002A0A1E},
	{0x0F120D58},
	{0x002A0AD4},
	{0x0F120A53},
};

s5k4ecgx_short_t s5k4ecgx_Low_Cap_Off[] = {
	{0x00287000},
	{0x002A0A1E},
	{0x0F120040},
	{0x002A0AD4},
	{0x0F120080},
};

s5k4ecgx_short_t s5k4ecgx_Capture_Start[] ={
	{0x00287000},
	{0x002A0242},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0244},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Preview_Return[] ={
	{0x00287000},
	{0x002A05D0},
	{0x0F120000},
	{0x002A0972},
	{0x0F120000},
	{0x002A0242},
	{0x0F120000},
	{0x002A024E},
	{0x0F120001},
	{0x002A0244},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_5M_Capture[] = {  /* 2560 x 1920 */

	{0xFCFCD000},
	{0x00287000},
	{0x002A0398},
	{0x0F120A00},
	{0x0F120780},
	{0x0F120009},

	{0x002A03B2},
	{0x0F120002},
	{0x002A03B0},
	{0x0F120002},
	{0x002A0270},
	{0x0F120001}, 
};

s5k4ecgx_short_t s5k4ecgx_3M_Capture[] = {  /* 2048 x 1536 */

	{0xFCFCD000},
	{0x00287000},
	{0x002A0398},
	{0x0F120800},
	{0x0F120600},
	{0x0F120009},

	{0x002A03B2},
	{0x0F120002},
	{0x002A03B0},
	{0x0F120002},
	{0x002A024E},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},

};

s5k4ecgx_short_t s5k4ecgx_2M_Capture[] = {  /* 1600 x 1200 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A0398},
	{0x0F120640},
	{0x0F1204B0},
	{0x0F120009},
	{0x002A03B2},
	{0x0F120002},
	{0x002A03B0},
	{0x0F120002},
	{0x002A024E},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},
};



s5k4ecgx_short_t s5k4ecgx_1M_Capture[] = {  /* 1280 x 960 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A0398},
	{0x0F120500},
	{0x0F1203C0},
	{0x0F120009},
	{0x002A03B2},
	{0x0F120002},
	{0x002A03B0},
	{0x0F120002},
	{0x002A024E},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},

};


s5k4ecgx_short_t s5k4ecgx_VGA_Capture[] = {  /* 640 x 480 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A0398},
	{0x0F120280},
	{0x0F1201E0},
	{0x0F120009},
	{0x002A03B2},
	{0x0F120002},
	{0x002A03B0},
	{0x0F120002},
	{0x002A024E},
	{0x0F120001},
	{0x002A0270},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_QVGA_Capture[] = {  /* 640 x 480 */
{0xFCFCD000},
{0x00287000},
{0x002A0392},
{0x0F120280},
{0x0F1201E0},
{0x0F120009},
{0x002A03AC},
{0x0F120002},
{0x0F120535},
{0x0F12029A},
{0x002A03AA},
{0x0F120002},
{0x002A026C},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_720_Preview[] = {  /* 720 x 480 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A02A6},
	{0x0F1202D0},
	{0x0F1201E0},
	{0x0F120005},
	{0x002A02B4},
	{0x0F120052},
	{0x002A02BE},
	{0x0F120000},
	{0x0F120001},
	{0x0F12029A},
	{0x0F12014D},
	{0x002A02D0},
	{0x0F120000},
	{0x0F120000},
	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_640_Preview[] = {  /* 640 x 480 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A02A6},
	{0x0F120280},
	{0x0F1201E0},
	{0x0F120005},
	{0x002A02B4},
	{0x0F120052},
	{0x002A02BE},
	{0x0F120000},
	{0x0F120001},
	{0x0F12029A},
	{0x0F12014D},
	{0x002A02D0},
	{0x0F120000},
	{0x0F120000},
	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},

};

s5k4ecgx_short_t s5k4ecgx_352_Preview[] = {  /* 352 x 288 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A02A6},
	{0x0F120160},
	{0x0F120120},
	{0x0F120005},
	{0x002A02B4},
	{0x0F120052},
	{0x002A02BE},
	{0x0F120000},
	{0x0F120001},
	{0x0F12029A},
	{0x0F12014D},
	{0x002A02D0},
	{0x0F120000},
	{0x0F120000},
	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},

};


s5k4ecgx_short_t s5k4ecgx_176_Preview[] = {  /* 176 x 144 */
	{0xFCFCD000},
	{0x00287000},
	{0x002A02A6},
	{0x0F1200B0},
	{0x0F120090},
	{0x0F120005},
	{0x002A02B4},
	{0x0F120052},
	{0x002A02BE},
	{0x0F120000},
	{0x0F120001},
	{0x0F12029A},
	{0x0F12014D},
	{0x002A02D0},
	{0x0F120000},
	{0x0F120000},
	{0x002A0266},
	{0x0F120000},
	{0x002A026A},
	{0x0F120001},
	{0x002A024E},
	{0x0F120001},
	{0x002A0268},
	{0x0F120001},
};

/* Zoom set for 320,176*/
s5k4ecgx_short_t s5k4ecgx_X4_Zoom_0[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120100},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120160},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1201C0},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120220},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120280},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_5[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1202E0},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_6[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120340},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_7[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1203A0},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_8[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120400},
{0x002A049E},
{0x0F120005}
};

/* Zoom set for 1280,640*/
s5k4ecgx_short_t s5k4ecgx_X2_Zoom_0[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120100},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120120},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120140},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120160},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120180},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_5[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1201A0},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_6[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1201C0},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_7[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1201E0},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_8[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120200},
{0x002A049E},
{0x0F120005}
};

/* Zoom set for 720*/
s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_0[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120100},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120118},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120130},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120148},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120160},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_5[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120178},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_6[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120190},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_7[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1201A8},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_8[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F1201C5},
{0x002A049E},
{0x0F120005}
};

/* Zoom set for 1600*/
s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_0[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120100},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120113},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120126},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120139},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F12014C},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_5[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F12015F},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_6[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120172},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_7[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120185},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_8[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F12019A},
{0x002A049E},
{0x0F120005}
};

/* Zoom set for 2048*/
s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_0[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120100},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120108},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120110},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120118},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120120},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_5[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120128},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_6[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120130},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_7[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120138},
{0x002A049E},
{0x0F120005}
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_8[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0488},
{0x0F120140},
{0x002A049E},
{0x0F120005}
};

//latin_cam : support anti-banding hmin84.park 101214
#if defined(CONFIG_SAMSUNG_LTN_COMMON)
#include "s5k4ecgx_evt1-ltn.h"
#else
#include "s5k4ecgx_evt1.h"
#endif //CONFIG_SAMSUNG_LTN_COMMON

#endif




