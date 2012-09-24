
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

#define CAMDRV_ENABLE_DEBUG // ON/OFF

#ifdef CAMDRV_ENABLE_DEBUG
#define CAMDRV_DEBUG(fmt, arg...)  \
                do{\
                printk("[S5K4ECGX] " fmt,##arg);}\
                while(0)
#else
#define CAMDRV_DEBUG(fmt, arg...)  
#endif

typedef struct s5k4ecgx_reg {
	unsigned int value;
} s5k4ecgx_short_t;

//you have to know this : p10, p100 is for request delay. 2010-09-01.
s5k4ecgx_short_t s5k4ecgx_init0[] = 
{
                          //****************************************/
{0xFCFCD000},
                 //****************************************/
{0x00100001},	                          // Reset

                 //0028 7000
                 //WRITE 7000021C 0001

{0xFCFCD000},
{0x10300000},	                          // Clear host interrupt so main will wait

{0x00140001},	                          // ARM go

{0xffff0064},
 
{0x007A0000},

{0xF2560000},
{0xF2580000},
{0xF25A0000},
{0xF25C0000},
{0xF25E0000},
{0xF2600000},
{0xF2620001},
{0xF2640001},
{0xF2AC0020},

{0xE3020820},
{0xE3040020},
{0xE4020040},
{0xE4041FC0},

                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //
                 // analog setting start                           //
                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //
{0xF4008A5C},	                          //[15:8]stx_width, [7:0]dstx_width

{0xF4020023},	                          //[14]binning_test, [13]gain_mode, [11:12]row_id, [10]cfpn_test, [9]pd_pix,
                 //[8]teg_en, [7]adc_res, [6]smp_en, [5]ldb_en, [4]ld_en, [3]clp_en
                 //[2]srx_en, [1]dshut_en, [0]dcds_en

{0xF40400A0},	                          //CDS option [6]S1 H
                 //[0]clp_sl H, [1]LDB H, [2]LD L, [3]ALDB x
                 //[4]LD PD, [5]CDS pd, [6]S1 H,
                 //[7]S3 Nx, [8]S3 Px, [9]S4 Nx, [10]S4 Px

{0xF40603AF},	                          //[11:6]rst_mx, [5:0]sig_mx
{0xF4080000},	                          //Avg mode
{0xF40A5554},	                          //MS
{0xF40C0040},	                          //RMP option [6]1: RES gain
{0xF40E464E},	                          //[14]msoff_en, [13:8]off_rst, [7:0]adc_sat,
{0xF4185558},	                          //bias [15:12]pix, [11:8]pix_bst,
                 //[7:4]comp2, [3:0]comp1

{0xF41ACC00},	                          //[15:8]clp_lvl, [7:0]ref_option, [5]pix_bst_en
{0xF41C0010},	                          //[7:0]monit

                 // ISP FE(ADLC)
{0xE4020040},	                          //pedestal +64 (0080)
{0xE4060092},	                          //[7]f_ladlc_en [6:5]f max [4]fadlc_en
                 //[3:2]L max [1]ladlc_en [0]adlc_ch_sel
{0xE4103804},	                          //[15:8]fadlc_filter_co_b, [7:0]fadlc_filter_co_a
{0xE4200003},	                          //adlc_fadlc_filter_refresh
{0xE4220060},	                          //adlc_filter_level_diff_threshold
{0xE42E0004},	                          //dithered l-ADLC(4bit)
{0xE3040020},	                          //[11]active bpr

{0xE2020081},	                          //adc_offset_even
{0xE2040081},	                          //adc_offset_odd
{0xE2060081},	                          //adc_default
{0xE208076C},	                          //adc_max
{0xE20A04A0},	                          //adc_clp 1184=1024+128+32

                 // DBS & RDV
{0xF4100240},	                          //bist_sig_width_e
{0xF4120240},	                          //bist_sig_width_o
{0xF4140040},	                          //[9]dbs_bist_en, [8:0]bist_rst_width
{0xF4169000},	                          //[15]aac_en, [14]GCLK_DIV2_EN, [13:10]dl_cont
                 //[9:8]dbs_mode, [7:0]dbs_option
{0xF4302428},	                          //[13:11]srx_gap1, [10:8]srx_gap0, [7:0]stx_gap
{0xF4320000},	                          //[0]atx_option
{0xF4360000},	                          //[0]hvs_test_reg
{0xF4380000},	                          //[0]dbus_bist_auto
{0xF43A0000},	                          //[7:0]dbr_option

                 // DBLR & PMG
{0xF41E1002},	                          //[15:8]dbr_tune_tgsl, [7:0]dbr_tune_pix
{0xF4200410},	                          //[15:8]dbr_tune_ntg, [7:0]dbr_tune_rg
{0xF4220022},	                          //[15:8]reg_option, [7:4]rosc_tune_ncp, [3:0]rosc_tune_cp
{0xF4240088},	                          //PD [8]inrush_ctrl, [7]fblv, [6]reg_ntg, [5]reg_tgsl, [4]reg_rg, [3]reg_pix, [2]ncp_rosc, [1]cp_rosc, [0]cp
{0xF426009F},	                          //[9]capa_ctrl_en, [8:7]fb_lv, [6:5]dbr_clk_sel, [4:0]cp_capa
{0xF4280000},	                          //[15:0]blst_en_cintr
{0xF42A1800},	                          //[11]blst_en, [10]rfpn_test, [9]sl_off, [8]tx_off, [7:0]rdv_option
{0xF42C0088},	                          //[15:0]pmg_reg_tune
{0xF42E0000},	                          //[15:1]analog_dummy, [0]pd_reg_test

                 //GTG pointer for 10b Normal mode
{0xF4800004},	                          //aig_ld_ptr0
{0xF48205B6},	                          //aig_ld_ptr1
{0xF4840000},	                          //aig_ld_ptr2
{0xF4860000},	                          //aig_ld_ptr3
{0xF4880001},	                          //aig_sl_ptr0
{0xF48A05BA},	                          //aig_sl_ptr1
{0xF48C0000},	                          //aig_sl_ptr2
{0xF48E0000},	                          //aig_sl_ptr3
{0xF4900008},	                          //aig_rx_ptr0
{0xF49205BA},	                          //aig_rx_ptr1
{0xF4940000},	                          //aig_rx_ptr2
{0xF4960000},	                          //aig_rx_ptr3
{0xF49801AB},	                          //aig_tx_ptr0
{0xF49A0226},	                          //aig_tx_ptr1
{0xF49C0000},	                          //aig_tx_ptr2
{0xF49E0000},	                          //aig_tx_ptr3
{0xF4A001AB},	                          //aig_ss_ptr0
{0xF4A205B6},	                          //aig_ss_ptr1
{0xF4A40000},	                          //aig_ss_ptr2
{0xF4A60000},	                          //aig_ss_ptr3
{0xF4A801AB},	                          //aig_sr_ptr0
{0xF4AA05BA},	                          //aig_sr_ptr1
{0xF4AC0000},	                          //aig_sr_ptr2
{0xF4AE0000},	                          //aig_sr_ptr3
{0xF4B001AB},	                          //aig_s1_ptr0
{0xF4B20227},	                          //aig_s1_ptr1
{0xF4B40000},	                          //aig_s1_ptr2
{0xF4B60000},	                          //aig_s1_ptr3
{0xF4B80000},	                          //aig_s1_ptr4
{0xF4BA0000},	                          //aig_s1_ptr5
{0xF4BC0000},	                          //aig_s1_ptr6
{0xF4BE0000},	                          //aig_s1_ptr7
{0xF4C00008},	                          //aig_s3_ptr0
{0xF4C20075},	                          //aig_s3_ptr1
{0xF4C40000},	                          //aig_s3_ptr2
{0xF4C60000},	                          //aig_s3_ptr3
{0xF4C80008},	                          //aig_s4_ptr0
{0xF4CA007E},	                          //aig_s4_ptr1
{0xF4CC0000},	                          //aig_s4_ptr2
{0xF4CE0000},	                          //aig_s4_ptr3
{0xF4D00008},	                          //aig_clp_sl_ptr0
{0xF4D201AB},	                          //aig_clp_sl_ptr1
{0xF4D40000},	                          //aig_clp_sl_ptr2
{0xF4D60000},	                          //aig_clp_sl_ptr3
{0xF4D8009B},	                          //aig_cnt_en_ptr0
{0xF4DA01AB},	                          //aig_cnt_en_ptr1
{0xF4DC0292},	                          //aig_cnt_en_ptr2
{0xF4DE05B2},	                          //aig_cnt_en_ptr3
{0xF4E00000},	                          //aig_cnt_en_ptr4
{0xF4E20000},	                          //aig_cnt_en_ptr5
{0xF4E40000},	                          //aig_cnt_en_ptr6
{0xF4E60000},	                          //aig_cnt_en_ptr7
{0xF4E801AF},	                          //aig_conv_enb_ptr0
{0xF4EA01DF},	                          //aig_conv_enb_ptr1
{0xF4EC0000},	                          //aig_conv_enb_ptr2
{0xF4EE0000},	                          //aig_conv_enb_ptr3
{0xF4F00000},	                          //aig_conv_enb_ptr4
{0xF4F20000},	                          //aig_conv_enb_ptr5
{0xF4F401BF},	                          //aig_conv1_ptr0
{0xF4F601EF},	                          //aig_conv1_ptr1
{0xF4F80000},	                          //aig_conv1_ptr2
{0xF4FA0000},	                          //aig_conv1_ptr3
{0xF4FC0000},	                          //aig_conv1_ptr4
{0xF5900000},	                          //aig_conv1_ptr5
{0xF50001CF},	                          //aig_conv2_ptr0
{0xF50201EF},	                          //aig_conv2_ptr1
{0xF5040000},	                          //aig_conv2_ptr2
{0xF5060000},	                          //aig_conv2_ptr3
{0xF5080000},	                          //aig_conv2_ptr4
{0xF50A0000},	                          //aig_conv2_ptr5
{0xF50C0001},	                          //aig_cnt_rst_ptr0
{0xF50E0009},	                          //aig_cnt_rst_ptr1
{0xF5100086},	                          //aig_off_rst_en_ptr0
{0xF51205C0},	                          //aig_off_rst_en_ptr1
{0xF5140000},	                          //aig_off_rst_en_ptr2
{0xF5160000},	                          //aig_off_rst_en_ptr3
{0xF5180087},	                          //aig_rmp_rst_ptr0
{0xF51A008C},	                          //aig_rmp_rst_ptr1
{0xF51C01AF},	                          //aig_rmp_rst_ptr2
{0xF51E01B4},	                          //aig_rmp_rst_ptr3
{0xF52005B6},	                          //aig_rmp_rst_ptr4
{0xF52205BB},	                          //aig_rmp_rst_ptr5
{0xF5240000},	                          //aig_rmp_rst_1_ptr0
{0xF5260000},	                          //aig_rmp_rst_1_ptr1
{0xF5280000},	                          //aig_rmp_rst_1_ptr2
{0xF52A0000},	                          //aig_rmp_rst_1_ptr3
{0xF52C0000},	                          //aig_rmp_en_ptr0
{0xF52E0000},	                          //aig_rmp_en_ptr1
{0xF5300000},	                          //aig_rmp_en_ptr2
{0xF5320000},	                          //aig_rmp_en_ptr3
{0xF5340000},	                          //aig_rmp_en_ptr4
{0xF5360000},	                          //aig_rmp_en_ptr5
{0xF5380000},	                          //aig_rmp_en_ptr6
{0xF53A0000},	                          //aig_rmp_en_ptr7
{0xF53C01AF},	                          //aig_rmp_mode_ptr0
{0xF53E0000},	                          //aig_rmp_mode_ptr1
{0xF5400000},	                          //aig_rmp_mode_ptr2
{0xF5420009},	                          //aig_pxbst_ptr0
{0xF5440010},	                          //aig_pxbst_ptr1
{0xF5460227},	                          //aig_pxbst_ptr2
{0xF5480236},	                          //aig_pxbst_ptr3
{0xF54A0000},	                          //aig_pxbst_ptr4
{0xF54C0000},	                          //aig_pxbst_ptr5
{0xF54E0000},	                          //aig_pxbst_ptr6
{0xF5500000},	                          //aig_pxbst_ptr7
{0xF5520C0D},	                          //[7:0]lat_st, [15:8]lat_width
{0xF5540C13},	                          //[7:0]hold_st, [15:8]hold_width
{0xF43403EE},	                          //aig_avg_half



                 // Start of Patch data
{0x00287000},
{0x002A3A14},
{0x0F12B510},	                          // 70003A14
{0x0F122100},	                          // 70003A16
{0x0F124B0D},	                          // 70003A18
{0x0F12220C},	                          // 70003A1A
{0x0F12480D},	                          // 70003A1C
{0x0F12C008},	                          // 70003A1E
{0x0F126002},	                          // 70003A20
{0x0F124A0C},	                          // 70003A22
{0x0F12480C},	                          // 70003A24
{0x0F123A24},	                          // 70003A26
{0x0F1287D0},	                          // 70003A28
{0x0F124A0C},	                          // 70003A2A
{0x0F122005},	                          // 70003A2C
{0x0F120200},	                          // 70003A2E
{0x0F128010},	                          // 70003A30
{0x0F128050},	                          // 70003A32
{0x0F12000A},	                          // 70003A34
{0x0F12490A},	                          // 70003A36
{0x0F12480A},	                          // 70003A38
{0x0F122401},	                          // 70003A3A
{0x0F12F000},	                          // 70003A3C
{0x0F12F868},	                          // 70003A3E
{0x0F124909},	                          // 70003A40
{0x0F12480A},	                          // 70003A42
{0x0F120022},	                          // 70003A44
{0x0F12F000},	                          // 70003A46
{0x0F12F863},	                          // 70003A48
{0x0F12BC10},	                          // 70003A4A
{0x0F12BC08},	                          // 70003A4C
{0x0F124718},	                          // 70003A4E
{0x0F1200E5},	                          // 70003A50
{0x0F124EC0},	                          // 70003A52
{0x0F121F10},	                          // 70003A54
{0x0F127000},	                          // 70003A56
{0x0F129999},	                          // 70003A58
{0x0F120000},	                          // 70003A5A
{0x0F123B50},	                          // 70003A5C
{0x0F127000},	                          // 70003A5E
{0x0F123A71},	                          // 70003A60
{0x0F127000},	                          // 70003A62
{0x0F12A08B},	                          // 70003A64
{0x0F120000},	                          // 70003A66
{0x0F123AAD},	                          // 70003A68
{0x0F127000},	                          // 70003A6A
{0x0F12A1A5},	                          // 70003A6C
{0x0F120000},	                          // 70003A6E
{0x0F12B570},	                          // 70003A70
{0x0F12000C},	                          // 70003A72
{0x0F126820},	                          // 70003A74
{0x0F126865},	                          // 70003A76
{0x0F12F000},	                          // 70003A78
{0x0F12F852},	                          // 70003A7A
{0x0F124A1E},	                          // 70003A7C
{0x0F120400},	                          // 70003A7E
{0x0F120C00},	                          // 70003A80
{0x0F128190},	                          // 70003A82
{0x0F124B1D},	                          // 70003A84
{0x0F128819},	                          // 70003A86
{0x0F124288},	                          // 70003A88
{0x0F12D305},	                          // 70003A8A
{0x0F12481C},	                          // 70003A8C
{0x0F12885B},	                          // 70003A8E
{0x0F128840},	                          // 70003A90
{0x0F124298},	                          // 70003A92
{0x0F12D300},	                          // 70003A94
{0x0F128191},	                          // 70003A96
{0x0F128992},	                          // 70003A98
{0x0F12481A},	                          // 70003A9A
{0x0F12002B},	                          // 70003A9C
{0x0F122105},	                          // 70003A9E
{0x0F12F000},	                          // 70003AA0
{0x0F12F846},	                          // 70003AA2
{0x0F126020},	                          // 70003AA4
{0x0F12BC70},	                          // 70003AA6
{0x0F12BC08},	                          // 70003AA8
{0x0F124718},	                          // 70003AAA
{0x0F12B5F8},	                          // 70003AAC
{0x0F120004},	                          // 70003AAE
{0x0F122101},	                          // 70003AB0
{0x0F12000D},	                          // 70003AB2
{0x0F120020},	                          // 70003AB4
{0x0F123810},	                          // 70003AB6
{0x0F124081},	                          // 70003AB8
{0x0F1240A5},	                          // 70003ABA
{0x0F124F12},	                          // 70003ABC
{0x0F12000E},	                          // 70003ABE
{0x0F122C10},	                          // 70003AC0
{0x0F12DA03},	                          // 70003AC2
{0x0F128838},	                          // 70003AC4
{0x0F1243A8},	                          // 70003AC6
{0x0F128038},	                          // 70003AC8
{0x0F12E002},	                          // 70003ACA
{0x0F128878},	                          // 70003ACC
{0x0F1243B0},	                          // 70003ACE
{0x0F128078},	                          // 70003AD0
{0x0F12F000},	                          // 70003AD2
{0x0F12F835},	                          // 70003AD4
{0x0F122C10},	                          // 70003AD6
{0x0F12DA03},	                          // 70003AD8
{0x0F128838},	                          // 70003ADA
{0x0F124328},	                          // 70003ADC
{0x0F128038},	                          // 70003ADE
{0x0F12E002},	                          // 70003AE0
{0x0F128878},	                          // 70003AE2
{0x0F124330},	                          // 70003AE4
{0x0F128078},	                          // 70003AE6
{0x0F124808},	                          // 70003AE8
{0x0F127DC1},	                          // 70003AEA
{0x0F123040},	                          // 70003AEC
{0x0F127101},	                          // 70003AEE
{0x0F12BCF8},	                          // 70003AF0
{0x0F12BC08},	                          // 70003AF2
{0x0F124718},	                          // 70003AF4
{0x0F120000},	                          // 70003AF6
{0x0F1221F8},	                          // 70003AF8
{0x0F127000},	                          // 70003AFA
{0x0F123B50},	                          // 70003AFC
{0x0F127000},	                          // 70003AFE
{0x0F122D38},	                          // 70003B00
{0x0F127000},	                          // 70003B02
{0x0F120940},	                          // 70003B04
{0x0F127000},	                          // 70003B06
{0x0F121100},	                          // 70003B08
{0x0F12D000},	                          // 70003B0A
{0x0F122CA8},	                          // 70003B0C
{0x0F127000},	                          // 70003B0E
{0x0F124778},	                          // 70003B10
{0x0F1246C0},	                          // 70003B12
{0x0F12C000},	                          // 70003B14
{0x0F12E59F},	                          // 70003B16
{0x0F12FF1C},	                          // 70003B18
{0x0F12E12F},	                          // 70003B1A
{0x0F121425},	                          // 70003B1C
{0x0F120001},	                          // 70003B1E
{0x0F124778},	                          // 70003B20
{0x0F1246C0},	                          // 70003B22
{0x0F12C000},	                          // 70003B24
{0x0F12E59F},	                          // 70003B26
{0x0F12FF1C},	                          // 70003B28
{0x0F12E12F},	                          // 70003B2A
{0x0F12A04F},	                          // 70003B2C
{0x0F120000},	                          // 70003B2E
{0x0F124778},	                          // 70003B30
{0x0F1246C0},	                          // 70003B32
{0x0F12C000},	                          // 70003B34
{0x0F12E59F},	                          // 70003B36
{0x0F12FF1C},	                          // 70003B38
{0x0F12E12F},	                          // 70003B3A
{0x0F12A001},	                          // 70003B3C
{0x0F120000},	                          // 70003B3E
{0x0F124778},	                          // 70003B40
{0x0F1246C0},	                          // 70003B42
{0x0F12C000},	                          // 70003B44
{0x0F12E59F},	                          // 70003B46
{0x0F12FF1C},	                          // 70003B48
{0x0F12E12F},	                          // 70003B4A
{0x0F12A1A5},	                          // 70003B4C
{0x0F120000},	                          // 70003B4E
                 // End of Patch Data(Last : 70003B4Eh)
                 // Total Size 316 (0x013C)
                 // Addr : 3A14 , Size : 314(13Ah)

                 //NoisegTuneRegA        0x70003b50
                 //NoisegTuneRegB        0x70003b52


{0x10000001},

{0x002A3B50},
{0x0F120196},	                          // For contrast
{0x0F120180},	                          // For contrast

{0x002A0206},
{0x0F120003},	                          //VCM IIC
{0x002A0214},
{0x0F122F0C},	                          // GPIO 1,2
{0x0F1200C8},
{0x002A0204},
{0x0F120000},

{0x002A020C},
{0x0F120061},	                          // AF Enable GPIO 3

{0x002A071E},
{0x0F1200FF},

{0x002A0296},
{0x0F120100},
{0x0F1200E9},
{0x0F120200},
{0x0F120238},
{0x0F12018C},
{0x0F12016C},
{0x0F1200E6},
{0x0F120132},
{0x0F120001},

{0x002A15CA},
{0x0F120048},	                          //0011
{0x0F12004B},	                          //0036
{0x0F12004D},	                          //0036
{0x0F120050},	                          //003D
{0x0F120053},	                          //0044
{0x0F120056},	                          //004B
{0x0F12005A},	                          //0052
{0x0F12005F},	                          //0059
{0x0F120064},	                          //0060
{0x0F12006A},	                          //0067
{0x0F120070},	                          //006E
{0x0F120075},	                          //0075
{0x0F12007A},
{0x0F120080},
{0x0F120086},
{0x0F12008C},
{0x0F120092},
{0x0F12009A},
{0x0F1200A0},
{0x0F1200A8},
{0x0F1200B0},


                 // Home & LowConf position
{0x002A15B4},
{0x0F120045},
{0x0F126727},

                 //WRITE #af_scene_usSaturatedScene 					0003	                          // Not Using Saturated Sc
                 //WRITE #af_search_usSingleAfFlags 					1000	                          // 1b:Use Fine Search
                 //WRITE #af_pos_usFineStepNumSize 					0302
                 //WRITE #af_search_usFinePeakCount 					0004

                 // Peak Threshold
{0x002A161E},
{0x0F120000},	                          // Full search  ( C0 75%)

                 // BPF configuration
{0x002A16B4},
{0x0F120010},	                          // af_stat_usBpfThresh
{0x002A1678},
{0x0F12FF95},	                          //FFF5                           //Lowlight Scene : GRAD[S] > HPF[L] > BPF[L]

{0x002A15C8},
{0x0F120014},



                 // AF Init
                 //WRITE   #REG_TC_IPRM_CM_Init_AfModeType               0003                             // VCM_I2C actuator
                 //WRITE   #REG_TC_IPRM_LedGpio                          0000                             // No LED GPIO
                 //WRITE   #REG_TC_IPRM_CM_Init_PwmConfig1               0000                             // No PWM
                 //WRITE   #REG_TC_IPRM_CM_Init_PwmConfig2               0000
                 //WRITE   #REG_TC_IPRM_CM_Init_GpioConfig1              0081                             // [3:0]GPIO Number, [7:4]GPIO, Use GPIO_# for enable port
                 //WRITE   #REG_TC_IPRM_CM_Init_GpioConfig2              0000
                 //WRITE   #REG_TC_IPRM_CM_Init_Mi2cBits                 202D                             // [9:8]SCL [11:10]SDA                           //Use GPIO_# for SCL, GPIO_# for SDA
                 //WRITE   #REG_TC_IPRM_CM_Init_Mi2cRateKhz              0190                             // MI2C Speed : 400KHz




                 //AWB Init
                 //White Locus
{0x002A11D0},
{0x0F120125},	                          //0126	                          //012D	                          //012C
{0x0F120130},	                          //0107	                          //012E	                          //011C


{0x002A187C},
{0x0F120FB0},

{0x002A1A3C},
{0x0F12F480},
{0x0F12D000},	                          // senHal_ContPtrs_senModesDataArr
                 //WRITE	700018C6	7000

{0x002A1898},
{0x0F120004},
{0x0F1205B6},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x0F1205BA},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F1205BA},
{0x0F120000},
{0x0F120000},
{0x0F1201AB},
{0x0F120226},
{0x0F120000},
{0x0F120000},
{0x0F1201AB},
{0x0F1205B6},
{0x0F120000},
{0x0F120000},
{0x0F1201AB},
{0x0F1205BA},
{0x0F120000},
{0x0F120000},
{0x0F1201AB},
{0x0F120227},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F120075},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F12007E},
{0x0F120000},
{0x0F120000},
{0x0F120008},
{0x0F1201AB},
{0x0F120000},
{0x0F120000},
{0x0F12009B},
{0x0F1201AB},
{0x0F120292},
{0x0F1205B2},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1201AF},
{0x0F1201DF},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1201BF},
{0x0F1201EF},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F1201CF},
{0x0F1201EF},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x0F120009},
{0x0F120086},
{0x0F1205C0},
{0x0F120000},
{0x0F120000},
{0x0F120087},
{0x0F12008C},
{0x0F1201AF},
{0x0F1201B4},
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
{0x0F1201AF},
{0x0F120000},
{0x0F120000},
{0x0F120009},
{0x0F120010},
{0x0F120227},
{0x0F120236},
{0x0F120000},
{0x0F120000},
{0x0F120000},
{0x0F120000},



{0x002A1AB8},
{0x0F120001},
{0x002A188A},
{0x0F120060},
{0x0F120060},
{0x002A0ECE},
{0x0F120001},
{0x002A1876},
{0x0F120002},
{0x0F120000},
{0x002A1890},
{0x0F1205C0},
{0x002A1A4E},
{0x0F120000},	                          //SRX off
{0x002A1880},
{0x0F120004},	                          //extend Forbidden area line
{0x002A1A46},
{0x0F12009A},	                          //extend right Forbidden area line
{0x002A37BA},
{0x0F12024C},


                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///
                 //	GAS TBL setting
                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///


{0x002A08C0},
{0x0F120001},	                          //0x70000860	                          // 0x0001

                 //?? Table ? ??
                 //0002    	Mon_WBT_CCMindex                          	2   70002086                           //CCM
                 //0070    	Mon_WBT_CCMFstFactor                      	2   70002088
                 //0090    	Mon_WBT_CCMScndFactor                     	2   7000208A
                 //0004    	Mon_WBT_ASindex                           	2   7000208C                           //Alpha
                 //0091    	Mon_WBT_ASFstFactor                       	2   7000208E
                 //006F    	Mon_WBT_ASScndFactor                      	2   70002090

                 //	GAS Alpha table
                 //Horizon [0]
{0x002A08FE},
{0x0F124000},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //IncA [1]
{0x0F124000},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //WW [2]
{0x0F124000},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //CW [3]
{0x0F124000},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //DL50 [4]
{0x0F124200},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //DL65 [5]
{0x0F124500},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //DL75 [6]
{0x0F124A00},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B
                 //Outdoor [7]
{0x0F125000},	                          //R
{0x0F124000},	                          //GR
{0x0F124000},	                          //GB
{0x0F124000},	                          //B

                 //	GAS High table
                 //	GAS High table

{0x002A0D0E},
{0x0F120F00},
{0x0F12000F},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120F00},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120000},
{0x0F12000F},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120000},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F12000F},
{0x0F12000F},
{0x0F120000},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120000},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120000},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F120F0F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F12000F},
{0x0F12000F},
{0x0F12000F},
{0x0F120F00},
{0x0F120F00},
{0x0F12000F},
{0x0F120F0F},
{0x0F120F0F},
{0x0F120F00},
{0x0F120000},
{0x0F120000},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F120F00},
{0x0F12000F},
{0x0F12000F},
{0x0F12000F},
{0x0F12000F},
{0x0F120F00},



{0x002A0D9E},
{0x0F128143},
{0x0F12EB12},
{0x0F12F5D6},
{0x0F122828},
{0x0F12DEE5},
{0x0F120CCD},
{0x0F12DB42},
{0x0F12F790},
{0x0F1221D5},
{0x0F12D279},
{0x0F1219E9},
{0x0F12FDF3},
{0x0F1216FC},
{0x0F120966},
{0x0F12D374},
{0x0F12296A},
{0x0F1204A7},
{0x0F12E567},
{0x0F12F9B9},
{0x0F12F9F7},
{0x0F122FB5},
{0x0F12E5CB},
{0x0F12E3B3},
{0x0F1223C3},
{0x0F120A5C},
{0x0F12F94A},
{0x0F12E9F5},
{0x0F12FE7C},
{0x0F120A41},
{0x0F120AA9},
{0x0F12F7D2},
{0x0F121053},
{0x0F12EF5A},
{0x0F121B9A},
{0x0F120C14},
{0x0F12CFC4},
{0x0F128A6C},
{0x0F12E69D},
{0x0F12FCEF},
{0x0F121A56},
{0x0F12F38D},
{0x0F12FD18},
{0x0F12D82E},
{0x0F12F23A},
{0x0F1225F5},
{0x0F12D605},
{0x0F120935},
{0x0F121149},
{0x0F121281},
{0x0F12121A},
{0x0F12CF02},
{0x0F12261F},
{0x0F1215CA},
{0x0F12CEB5},
{0x0F120ABD},
{0x0F12F12E},
{0x0F123386},
{0x0F12DD86},
{0x0F12E82B},
{0x0F122C9F},
{0x0F12F213},
{0x0F12F995},
{0x0F12F0C2},
{0x0F1204AA},
{0x0F12FEF7},
{0x0F120A53},
{0x0F1207E8},
{0x0F12185C},
{0x0F12DD97},
{0x0F122B08},
{0x0F12FCEC},
{0x0F12DBDA},
{0x0F127D2D},
{0x0F12E3C3},
{0x0F1206EB},
{0x0F120E73},
{0x0F12F6BF},
{0x0F120254},
{0x0F12D8A3},
{0x0F12F9B6},
{0x0F122222},
{0x0F12D689},
{0x0F120825},
{0x0F1211D4},
{0x0F12240D},
{0x0F121085},
{0x0F12BEAD},
{0x0F123A59},
{0x0F1213D7},
{0x0F12C35C},
{0x0F12E7AD},
{0x0F12EEFA},
{0x0F124A1C},
{0x0F12C5C0},
{0x0F12E6CB},
{0x0F123FFB},
{0x0F12166D},
{0x0F12F782},
{0x0F12EA8F},
{0x0F120F0C},
{0x0F12F4BF},
{0x0F120ADD},
{0x0F12F569},
{0x0F121AC2},
{0x0F12DA1F},
{0x0F122550},
{0x0F1217C8},
{0x0F12C4B9},
{0x0F12840B},
{0x0F12E83D},
{0x0F12FD35},
{0x0F1218E8},
{0x0F12F3D9},
{0x0F12FE05},
{0x0F12DA72},
{0x0F12F921},
{0x0F121FAD},
{0x0F12DB29},
{0x0F1204AB},
{0x0F121288},
{0x0F12190D},
{0x0F120597},
{0x0F12CE93},
{0x0F122E99},
{0x0F121149},
{0x0F12CF5E},
{0x0F12FC1D},
{0x0F1204A9},
{0x0F122FE2},
{0x0F12D6E9},
{0x0F12E9E4},
{0x0F122E43},
{0x0F1203CC},
{0x0F12E4DC},
{0x0F12FC85},
{0x0F120592},
{0x0F12F3C3},
{0x0F12162E},
{0x0F12FC7B},
{0x0F12210E},
{0x0F12D8E0},
{0x0F1221B1},
{0x0F121A6F},
{0x0F12C127},



                 // Upload GAS table
                 //WRITE	#ash_nGasAlphaStep				0001	                          //ash_nGasAlphaStep
{0x002A08FC},
{0x0F120001},	                          //ash_bUseGasAlpha

                 //If you use after configuration, this reg. must be turn_on.
                 //WRITE	#REG_TC_DBG_ReInitCmd		0001	                          //REG_TC_DBG_ReInitCmd
                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///
                 //	GAS TBL END
                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///


                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///
                 //	AE START
                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///

                 //AE WEIGHT                                           //5CA weight                           // 4EA FPGA Weight
{0x002A1472},
{0x0F120000},	                          //0000	                          //0000	                          //0000
{0x0F120101},	                          //0000	                          //0000	                          //0101
{0x0F120101},	                          //0000	                          //0000	                          //0101
{0x0F120000},	                          //0000	                          //0000	                          //0000
{0x0F120101},	                          //0101	                          //0101	                          //0101
{0x0F120101},	                          //0101	                          //0101	                          //0101
{0x0F120101},	                          //0101	                          //0101	                          //0101
{0x0F120101},	                          //0101	                          //0101	                          //0101
{0x0F120201},	                          //0101	                          //0101	                          //0201
{0x0F120303},	                          //0201	                          //0301	                          //0303
{0x0F120303},	                          //0102	                          //0103	                          //0303
{0x0F120102},	                          //0101	                          //0101	                          //0102
{0x0F120201},	                          //0101	                          //0101	                          //0201
{0x0F120403},	                          //0202	                          //0705	                          //0403
{0x0F120304},	                          //0202	                          //0507	                          //0304
{0x0F120102},	                          //0101	                          //0101	                          //0102
{0x0F120201},	                          //0101	                          //0101	                          //0201
{0x0F120403},	                          //0202	                          //0705	                          //0403
{0x0F120304},	                          //0202	                          //0507	                          //0304
{0x0F120102},	                          //0101	                          //0101	                          //0102
{0x0F120201},	                          //0201	                          //0101	                          //0201
{0x0F120403},	                          //0202	                          //0503	                          //0403
{0x0F120304},	                          //0202	                          //0305	                          //0304
{0x0F120102},	                          //0102	                          //0101	                          //0102
{0x0F120201},	                          //0201	                          //0101	                          //0201
{0x0F120303},	                          //0202	                          //0301	                          //0303
{0x0F120303},	                          //0202	                          //0103	                          //0303
{0x0F120102},	                          //0102	                          //0101	                          //0102
{0x0F120201},	                          //0101	                          //0101	                          //0201
{0x0F120202},	                          //0101	                          //0101	                          //0202
{0x0F120202},	                          //0101	                          //0101	                          //0202
{0x0F120102},	                          //0101	                          //0101	                          //0102

                 //AE Setting
{0x002A1464},
{0x0F12003C},	                          //
{0x002A146A},
{0x0F12000F},	                          // 000F

{0x002A059C},
{0x0F123520},	                          //(x4 8000/ 80ms)
{0x0F120000},
{0x0F12C350},
{0x0F120000},	                          //(x4 25000/ 250ms)
{0x0F123520},
{0x0F120000},	                          //(x4 8000/ 80ms)
{0x0F12C350},
{0x0F120000},	                          //(x4 25000/ 250ms)
{0x0F120470},	                          //lt_uMaxAnGain1
{0x0F120C00},	                          //lt_uMaxAnGain2
{0x0F120100},
{0x0F121000},	                          //lt_uMaxTotGain (Limit Gain)

{0x002A0554},
{0x0F120111},	                          //
{0x0F1200EF},	                          //

                 //WRITE	#Mon_AAIO_bAFC0									0000	                          // off

                 //WRITE	#REG_SF_USER_FlickerQuant					0002	                          // 0:off 1:50hz 2:60hz
                 //WRITE	#REG_SF_USER_FlickerQuantChanged	0001	                          //

{0x002A0618},
{0x0F120000},	                          //0: table off, 1: table[1] on, 2: table[2] on                           //preview
{0x0F120001},	                          //capture
{0x0F120600},	                          //<- ?? lt_uMaxdigGain2 ?E??.
{0x0F120100},	                          //<- ?? lt_uMaxdigGain2 ?E??.
                 //input

{0x0F120001},
{0x0F120000},	                          // 70000620
{0x002A0624},
{0x0F120A3C},
{0x0F120000},	                          // 70000624
{0x002A0628},
{0x0F120D04},
{0x0F120000},	                          // 70000628
{0x002A062C},
{0x0F123408},
{0x0F120000},	                          // 7000062C
{0x002A0630},
{0x0F125A00},
{0x0F120000},	                          // 70000630
{0x002A0634},
{0x0F129C00},
{0x0F120000},	                          // 70000634
{0x002A0638},
{0x0F124D00},
{0x0F120001},	                          // 70000638
{0x002A063C},
{0x0F12C1D4},
{0x0F120002},	                          // 7000063C
{0x002A0640},
{0x0F12DC00},
{0x0F120005},	                          // 70000640
{0x002A0644},
{0x0F12DC00},
{0x0F120005},	                          // 70000644
                 //                                            			                                    //
                 //                                            			                                    //
{0x002A0648},
{0x0F120001},
{0x0F120000},	                          // 70000648
{0x002A064C},
{0x0F120A3C},
{0x0F120000},	                          // 7000064C
{0x002A0650},
{0x0F120D05},
{0x0F120000},	                          // 70000650
{0x002A0654},
{0x0F123408},
{0x0F120000},	                          // 70000654
{0x002A0658},
{0x0F123408},
{0x0F120000},	                          // 70000658
{0x002A065C},
{0x0F126810},
{0x0F120000},	                          // 7000065C
{0x002A0660},
{0x0F128214},
{0x0F120000},	                          // 70000660
{0x002A0664},
{0x0F12C350},
{0x0F120000},	                          // 70000664
{0x002A0668},
{0x0F12C350},
{0x0F120000},	                          // 70000668
{0x002A066C},
{0x0F12C350},
{0x0F120000},	                          // 7000066C

{0x002A0670},
{0x0F120650},
{0x0F120100},


{0x002A06C8},
{0x0F12452C},
{0x0F120004},
                 //AWB Init
                 //White Locus
                 //WRITE #REG_TC_GP_bPwrSaveInPreView  0001





                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///
                 //CLK Settings

{0x002A0200},
{0x0F125DC0},	                          //70000238
{0x002A021A},
{0x0F120001},	                          //70000252
{0x0F120000},	                          //70000254
{0x0F120000},	                          //70000256
{0x002A0222},
{0x0F122CEC},	                          //7000025A	                          //52MHz
{0x0F1259D8},	                          //7000025C	                          //52MHz
{0x0F1259D8},	                          //7000025E	                          //48MHz
{0x002A0234},
{0x0F120001},	                          //7000026C


                 //Preview
{0x002A02B2},
{0x0F120280},	                          //700002E8
{0x0F1201E0},	                          //700002EA
{0x0F120005},	                          //700002EC
{0x0F1259D8},	                          //700002EE
{0x0F1259D8},	                          //700002F0
{0x002A02C0},
{0x0F120002},	                          //Gated
{0x002A02C8},
{0x0F120000},	                          //700002FE
{0x0F120002},	                          //70000300
{0x0F120001},	                          //70000302
{0x0F120535},	                          //70000304
{0x0F120000},	                          //70000306
{0x002A02BC},
{0x0F120080},

                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //
                 //PREVIEW
{0x002A026E},
{0x0F120000},	                          //700002A2
{0x002A0272},
{0x0F120001},	                          //700002A6
{0x002A0256},
{0x0F120001},	                          //7000028E
{0x002A0270},
{0x0F120001},	                          //700002A4
{0x002A0278},
{0x0F120001},	                          //700002AC
{0x002A0246},
{0x0F120001},	                          //7000027E
{0x0F120001},	                          //70000280

{0xffff012c},


                 // For Capture
{0x002A03A4},
{0x0F120A20},	                          //700002E8
{0x0F120798},	                          //700002EA
{0x0F120005},	                          //700002EC
{0x0F121800},	                          //700002EE
{0x0F122600},	                          //700002F0
{0x002A03B2},
{0x0F120052},	                          //Gated
{0x002A03BA},
{0x0F120000},	                          //700002FE
{0x0F120002},	                          //70000300
{0x0F120000},	                          //70000302
{0x0F120535},	                          //70000304
{0x0F120000},	                          //70000306
{0x002A03AE},
{0x0F120080},


                 // For JPEG

{0x002A0484},
{0x0F12005F},	                          // 95%
{0x0F12005F},	                          // 95%


                 //IndoorZone
{0x002A0FFC},
{0x0F1203B8},	                          //035A	                          //037A	                          //034E	                          //0390	                          //0360	                          //0376	                          //033C	                          //032C	                          //02EA	                          //0336	                          //03BE	                          //awbb_IndoorGrZones_m_BGrid[0]_m_left
{0x0F1203CE},	                          //0396	                          //039E	                          //0380	                          //03B8	                          //03B8	                          //039C	                          //03BC	                          //03BE	                          //033C	                          //038A	                          //03FC	                          //awbb_IndoorGrZones_m_BGrid[0]_m_right
{0x0F12036A},	                          //031C	                          //031C	                          //032C	                          //0350	                          //0336	                          //0310	                          //0300	                          //030A	                          //02C6	                          //02FC	                          //0342	                          //awbb_IndoorGrZones_m_BGrid[1]_m_left
{0x0F1203C4},	                          //039A	                          //039C	                          //0390	                          //03AA	                          //03AA	                          //038C	                          //03B2	                          //0398	                          //0358	                          //0388	                          //03CC	                          //awbb_IndoorGrZones_m_BGrid[1]_m_right
{0x0F120330},	                          //02F0	                          //02F0	                          //030E	                          //031C	                          //030C	                          //02DA	                          //02E0	                          //02EA	                          //02A4	                          //02DC	                          //02DA	                          //awbb_IndoorGrZones_m_BGrid[2]_m_left
{0x0F120396},	                          //0364	                          //0350	                          //0380	                          //038C	                          //038C	                          //0366	                          //0390	                          //0378	                          //0332	                          //036E	                          //039C	                          //awbb_IndoorGrZones_m_BGrid[2]_m_right
{0x0F1202FA},	                          //02C6	                          //02C6	                          //02E4	                          //02E6	                          //02DE	                          //02A6	                          //02C0	                          //02C6	                          //0280	                          //02BC	                          //02AA	                          //awbb_IndoorGrZones_m_BGrid[3]_m_left
{0x0F120362},	                          //0330	                          //0322	                          //0350	                          //0358	                          //0358	                          //0338	                          //0362	                          //035A	                          //030C	                          //0354	                          //0354	                          //awbb_IndoorGrZones_m_BGrid[3]_m_right
{0x0F1202D6},	                          //029A	                          //029A	                          //02BE	                          //02B2	                          //02B2	                          //0286	                          //02A4	                          //02A2	                          //025E	                          //02A0	                          //027A	                          //awbb_IndoorGrZones_m_BGrid[4]_m_left
{0x0F120334},	                          //02FC	                          //02FC	                          //0322	                          //0336	                          //0336	                          //030C	                          //0340	                          //033A	                          //02F0	                          //033A	                          //0324	                          //awbb_IndoorGrZones_m_BGrid[4]_m_right
{0x0F1202AC},	                          //0270	                          //0270	                          //0298	                          //0286	                          //0286	                          //0266	                          //0284	                          //0282	                          //023A	                          //0280	                          //025C	                          //awbb_IndoorGrZones_m_BGrid[5]_m_left
{0x0F120312},	                          //02DC	                          //02DC	                          //02FC	                          //030C	                          //030C	                          //02F4	                          //0324	                          //031E	                          //02D2	                          //0320	                          //02F6	                          //awbb_IndoorGrZones_m_BGrid[5]_m_right
{0x0F120284},	                          //0250	                          //0250	                          //0270	                          //0266	                          //0266	                          //0246	                          //0264	                          //025A	                          //0218	                          //025E	                          //023E	                          //awbb_IndoorGrZones_m_BGrid[6]_m_left
{0x0F1202F0},	                          //02BC	                          //02BE	                          //02DA	                          //02F4	                          //02F4	                          //02CE	                          //0308	                          //0302	                          //02B6	                          //0302	                          //02CE	                          //awbb_IndoorGrZones_m_BGrid[6]_m_right
{0x0F120264},	                          //0230	                          //0230	                          //0252	                          //0246	                          //0246	                          //0226	                          //0244	                          //0236	                          //01F4	                          //023E	                          //0228	                          //awbb_IndoorGrZones_m_BGrid[7]_m_left
{0x0F1202D0},	                          //029E	                          //029E	                          //02BC	                          //02CE	                          //02CE	                          //02B2	                          //02E8	                          //02E2	                          //0298	                          //02E4	                          //02B6	                          //awbb_IndoorGrZones_m_BGrid[7]_m_right
{0x0F120242},	                          //0210	                          //0210	                          //022E	                          //0226	                          //0226	                          //0218	                          //0220	                          //021E	                          //01D2	                          //021C	                          //0210	                          //awbb_IndoorGrZones_m_BGrid[8]_m_left
{0x0F1202B0},	                          //028C	                          //028C	                          //029E	                          //02B2	                          //02B2	                          //0296	                          //02C8	                          //02C2	                          //027C	                          //02C4	                          //02A0	                          //awbb_IndoorGrZones_m_BGrid[8]_m_right
{0x0F120222},	                          //01FA	                          //01FA	                          //0210	                          //0218	                          //0218	                          //020A	                          //0200	                          //0202	                          //01B6	                          //01FA	                          //01FA	                          //awbb_IndoorGrZones_m_BGrid[9]_m_left
{0x0F12029E},	                          //027E	                          //027E	                          //028C	                          //0296	                          //0296	                          //0284	                          //02AC	                          //029E	                          //025A	                          //02A6	                          //0288	                          //awbb_IndoorGrZones_m_BGrid[9]_m_right
{0x0F120210},	                          //01E6	                          //01E6	                          //01FA	                          //01FE	                          //01FE	                          //01FE	                          //01F4	                          //01E8	                          //019C	                          //01EE	                          //01E2	                          //awbb_IndoorGrZones_m_BGrid[10]_m_left
{0x0F120290},	                          //0272	                          //0272	                          //0280	                          //0286	                          //0286	                          //0272	                          //028C	                          //027A	                          //0238	                          //0286	                          //0278	                          //awbb_IndoorGrZones_m_BGrid[10]_m_right
{0x0F1201FC},	                          //01D6	                          //01D6	                          //01E6	                          //01E6	                          //01E6	                          //01FA	                          //01E4	                          //01EC	                          //0180	                          //01E0	                          //01E2	                          //awbb_IndoorGrZones_m_BGrid[11]_m_left
{0x0F120282},	                          //0264	                          //0264	                          //0272	                          //0278	                          //0278	                          //0260	                          //026C	                          //025A	                          //0216	                          //0268	                          //0270	                          //awbb_IndoorGrZones_m_BGrid[11]_m_right
{0x0F1201E8},	                          //01C8	                          //01C8	                          //01D6	                          //01D6	                          //01D6	                          //0200	                          //01D8	                          //01F6	                          //0188	                          //01D2	                          //01E2	                          //awbb_IndoorGrZones_m_BGrid[12]_m_left
{0x0F120276},	                          //0258	                          //0258	                          //0266	                          //0268	                          //0268	                          //024E	                          //0254	                          //0238	                          //01F4	                          //024E	                          //0266	                          //awbb_IndoorGrZones_m_BGrid[12]_m_right
{0x0F1201DC},	                          //01BA	                          //01BA	                          //01C8	                          //01C8	                          //01C8	                          //020C	                          //01CC	                          //0000	                          //0190	                          //01C4	                          //01E2	                          //awbb_IndoorGrZones_m_BGrid[13]_m_left
{0x0F12026A},	                          //024C	                          //024C	                          //0258	                          //025A	                          //025A	                          //023E	                          //0240	                          //0000	                          //01D2	                          //023A	                          //025C	                          //awbb_IndoorGrZones_m_BGrid[13]_m_right
{0x0F1201CE},	                          //01DA	                          //01DA	                          //01BA	                          //01BA	                          //01BA	                          //0000	                          //01D8	                          //0000	                          //0000	                          //01D0	                          //01E2	                          //awbb_IndoorGrZones_m_BGrid[14]_m_left
{0x0F12025E},	                          //021C	                          //021C	                          //024C	                          //024C	                          //024C	                          //0000	                          //022C	                          //0000	                          //0000	                          //0226	                          //0252	                          //awbb_IndoorGrZones_m_BGrid[14]_m_right
{0x0F1201EC},	                          //0000	                          //0000	                          //01DC	                          //01DC	                          //01DC	                          //0000	                          //01E8	                          //0000	                          //0000	                          //01E4	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[15]_m_left
{0x0F12022E},	                          //0000	                          //0000	                          //021C	                          //021C	                          //021C	                          //0000	                          //0218	                          //0000	                          //0000	                          //0212	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[15]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[16]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[16]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[17]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[17]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[18]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[18]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[19]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //awbb_IndoorGrZones_m_BGrid[19]_m_right

{0x0F120005},	                          //0005	                          //awbb_IndoorGrZones_m_GridStep
{0x002A1050},
{0x0F120010},	                          //0011	                          //0011	                          //awbb_IndoorGrZones_ZInfo_m_GridSz
{0x002A1054},
{0x0F120126},	                          //013C	                          //013C	                          //awbb_IndoorGrZones_m_Boffs

                 //OutdoorZone
{0x002A1058},
{0x0F120296},	                          //0284	                          //025A	                          //0278                          //0278	                          //0278                            //027D	                          //awbb_OutdoorGrZones_m_BGrid[0]_m_left
{0x0F1202A6},	                          //0298	                          //0272	                          //02AC                          //02AC	                          //02AA	                          //02AD	                          //awbb_OutdoorGrZones_m_BGrid[0]_m_right
{0x0F12024E},	                          //024E	                          //0234	                          //0234                          //0234	                          //0256                            //024D	                          //awbb_OutdoorGrZones_m_BGrid[1]_m_left
{0x0F1202A4},	                          //0298	                          //027E	                          //029A                          //029A	                          //02A4	                          //02B3	                          //awbb_OutdoorGrZones_m_BGrid[1]_m_right
{0x0F120244},	                          //0240	                          //0226	                          //0226                          //0228	                          //024E                            //0239	                          //awbb_OutdoorGrZones_m_BGrid[2]_m_left
{0x0F12029C},	                          //0298	                          //027E	                          //028E                          //028C	                          //029E	                          //02A5	                          //awbb_OutdoorGrZones_m_BGrid[2]_m_right
{0x0F120242},	                          //0234	                          //021A	                          //021A                          //021C	                          //0246                            //0223                            //awbb_OutdoorGrZones_m_BGrid[3]_m_left
{0x0F120294},	                          //0292	                          //0278	                          //0282                          //0282	                          //0290	                          //0299	                          //awbb_OutdoorGrZones_m_BGrid[3]_m_right
{0x0F12023A},	                          //0234	                          //0218	                          //020C                          //0210	                          //023E                            //0221	                          //awbb_OutdoorGrZones_m_BGrid[4]_m_left
{0x0F12028A},	                          //0288	                          //026C	                          //0272                          //0272	                          //0278	                          //0291	                          //awbb_OutdoorGrZones_m_BGrid[4]_m_right
{0x0F12023A},	                          //022A	                          //020E	                          //0200                          //0200	                          //0000                            //0223	                          //awbb_OutdoorGrZones_m_BGrid[5]_m_left
{0x0F120278},	                          //027E	                          //0264	                          //025A                          //025A	                          //0000	                          //0287	                          //awbb_OutdoorGrZones_m_BGrid[5]_m_right
{0x0F120000},	                          //022C	                          //0212	                          //0200                          //0200	                          //0000                            //0223	                          //awbb_OutdoorGrZones_m_BGrid[6]_m_left
{0x0F120000},	                          //026A	                          //0250	                          //025A                          //025A	                          //0000	                          //0269	                          //awbb_OutdoorGrZones_m_BGrid[6]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000                            //0000	                          //awbb_OutdoorGrZones_m_BGrid[7]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000	                          //awbb_OutdoorGrZones_m_BGrid[7]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000                            //0000	                          //awbb_OutdoorGrZones_m_BGrid[8]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000                            //awbb_OutdoorGrZones_m_BGrid[8]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000                            //0000	                          //awbb_OutdoorGrZones_m_BGrid[9]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000                            //awbb_OutdoorGrZones_m_BGrid[9]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000	                          //awbb_OutdoorGrZones_m_BGrid[10]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000                            //awbb_OutdoorGrZones_m_BGrid[10]_m_right
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000	                          //awbb_OutdoorGrZones_m_BGrid[11]_m_left
{0x0F120000},	                          //0000	                          //0000	                          //0000                          //0000	                          //0000	                          //0000                            //awbb_OutdoorGrZones_m_BGrid[11]_m_right
                 //
{0x0F120004},	                          //0004	                          //0004	                          //0004	                          //0004	                          //awbb_OutdoorGrZones_m_GridStep
{0x002A108C},
{0x0F120006},	                          //0007	                          //0005	                          //0007	                          //0007	                          //awbb_OutdoorGrZones_ZInfo_m_GridSz
{0x002A1090},
{0x0F120224},	                          //0244	                          //0240	                          //01DA	                          //01FE	                          //awbb_OutdoorGrZones_m_Boffs

                 //                          //                          //                          //                          //                          //                          //                          ///LowBRZone                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //
{0x002A1094},
{0x0F120350},	                          //02F0	                          //034D	                          //034D	                          //#awbb_LowBrGrZones_m_BGrid_0__m_left
{0x0F120422},	                          //03C4	                          //045B	                          //045B	                          //#awbb_LowBrGrZones_m_BGrid_0__m_right
{0x0F1202C4},	                          //02B0	                          //02EA	                          //02EA	                          //#awbb_LowBrGrZones_m_BGrid_1__m_left
{0x0F120452},	                          //03F6	                          //0445	                          //0445	                          //#awbb_LowBrGrZones_m_BGrid_1__m_right
{0x0F120278},	                          //0264	                          //02A4	                          //02A4	                          //#awbb_LowBrGrZones_m_BGrid_2__m_left
{0x0F12041C},	                          //03EA	                          //0428	                          //0428	                          //#awbb_LowBrGrZones_m_BGrid_2__m_right
{0x0F120230},	                          //021A	                          //0254	                          //0254	                          //#awbb_LowBrGrZones_m_BGrid_3__m_left
{0x0F1203EE},	                          //03BE	                          //03FB	                          //03FB	                          //#awbb_LowBrGrZones_m_BGrid_3__m_right
{0x0F1201F0},	                          //01CE	                          //0207	                          //0207	                          //#awbb_LowBrGrZones_m_BGrid_4__m_left
{0x0F120392},	                          //038C	                          //03C7	                          //03C7	                          //#awbb_LowBrGrZones_m_BGrid_4__m_right
{0x0F1201C0},	                          //0192	                          //01CF	                          //01CF	                          //#awbb_LowBrGrZones_m_BGrid_5__m_left
{0x0F120340},	                          //0330	                          //0365	                          //0365	                          //#awbb_LowBrGrZones_m_BGrid_5__m_right
{0x0F120194},	                          //0162	                          //019E	                          //019E	                          //#awbb_LowBrGrZones_m_BGrid_6__m_left
{0x0F120302},	                          //02E2	                          //031A	                          //031A	                          //#awbb_LowBrGrZones_m_BGrid_6__m_right
{0x0F12016E},	                          //0132	                          //0170	                          //0170	                          //#awbb_LowBrGrZones_m_BGrid_7__m_left
{0x0F1202C2},	                          //02A0	                          //02DB	                          //02DB	                          //#awbb_LowBrGrZones_m_BGrid_7__m_right
{0x0F120148},	                          //010C	                          //0149	                          //0149	                          //#awbb_LowBrGrZones_m_BGrid_8__m_left
{0x0F120286},	                          //0264	                          //029E	                          //029E	                          //#awbb_LowBrGrZones_m_BGrid_8__m_right
{0x0F12018A},	                          //00E4	                          //0122	                          //0122	                          //#awbb_LowBrGrZones_m_BGrid_9__m_left
{0x0F120242},	                          //0228	                          //025D	                          //025D	                          //#awbb_LowBrGrZones_m_BGrid_9__m_right
{0x0F120000},	                          //012C	                          //00FE	                          //00FE	                          //#awbb_LowBrGrZones_m_BGrid_10__m_left
{0x0F120000},	                          //01E6	                          //022E	                          //022E	                          //#awbb_LowBrGrZones_m_BGrid_10__m_right
{0x0F120000},	                          //00E4	                          //00E4	                          //#awbb_LowBrGrZones_m_BGrid_11__m_left
{0x0F120000},	                          //01F1	                          //01F1	                          //#awbb_LowBrGrZones_m_BGrid_11__m_right

{0x0F120006},	                          //	0x7000104C	                          // 0x0006
{0x002A10C8},
{0x0F12000A},	                          //000C 	                          //
{0x002A10CC},
{0x0F120106},	                          //00D6	                          //

                 //                          //                          //                          //                          //                          //                          //                          //                          //LowTemp Zone                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //
                 //	param_start	awbb_CrclLowT_R_c
{0x002A10D0},
{0x0F120346},
{0x0F120000},	                          //awbb_CrclLowT_R_c[0]
                 //WRITE	7000117A	0000	                          //awbb_CrclLowT_R_c[1]                            //White Locus
                 //	param_end	awbb_CrclLowT_R_c
                 //	param_start	awbb_CrclLowT_B_c
{0x002A10D4},
{0x0F120194},
{0x0F120000},	                          //awbb_CrclLowT_B_c[0]
                 //WRITE	7000117E	0000	                          //awbb_CrclLowT_B_c[1]
                 //	param_end	awbb_CrclLowT_B_c
                 //	param_start	awbb_CrclLowT_Rad_c
{0x002A10D8},
{0x0F124204},
{0x0F120000},	                          //awbb_CrclLowT_Rad_c[0]                          //Gamut Thresholds
                 //WRITE	700010D8	0000	                          //awbb_CrclLowT_Rad_c[1]s002A125C
                 //	param_end	awbb_CrclLowT_Rad_c
                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //


                 //AWB Convergence Speed
{0x002A1444},
{0x0F120008},	                          // ???? ??? Stable
{0x0F120190},	                          // ???? ?? boost
{0x0F1200A0},	                          // ?? AWB ??

                 //                          //Y level control
{0x002A120A},
{0x0F120010},
{0x002A1208},
{0x0F1200C0},	                          //0020	                          //
{0x002A120C},
{0x0F120010},	                          //


                 //White Locus
                 //WRITE	#awbb_IntcR        									0112	                          //012D	                          //012C
                 //WRITE	#awbb_IntcB        									0154	                          //012E	                          //011C
{0x002A11EA},
{0x0F120579},	                          //059D	                          //0565	                          //0628
{0x002A11EE},
{0x0F120000},	                          // Moving equation off
                 //Gamut Thresholds
{0x0F1206F5},	                          //06F6	                          //0823
{0x0F1203A4},	                          //02C9	                          //04D3
{0x0F12002F},	                          //0030	                          //0042
{0x0F12001F},	                          //0019	                          //0025

                 //TVAR_ash_AwbAshCord	                          //70002962 Mon_AWB_RotGain ??? ??? ??? Setting
{0x002A08C8},
{0x0F1200C0},	                          //00BF	                          //00E3                	                          //700008C0                               //Horizon
{0x0F1200DF},	                          //00E3	                          //0128                	                          //700008C2                               //incaA
{0x0F120100},	                          //013A                	                          //700008C4                               //WW
{0x0F120125},	                          //010A	                          //0178                	                          //700008C6                               //CW
{0x0F12015F},	                          //01AD                	                          //700008C8                               //D50
{0x0F12017C},	                          //01AF	                          //01CE                	                          //700008CA                               //D65
{0x0F120194},	                          //700008CC        		                           //D75

                 //SEC SceneDetection Threshold
{0x002A1258},
{0x0F12FEF7},	                          //FED8
{0x0F120021},	                          //0014
{0x0F120E74},	                          //Ahn	                          //0E74
{0x0F120E74},	                          //0122	                          //0122
{0x0F12018F},	                          //0064
{0x0F120096},	                          //0096
{0x0F12000E},	                          //000E
{0x002A1204},
{0x0F120032},	                          //0032
{0x0F12001E},	                          //001E
{0x002A2AF4},
{0x0F120006},	                          //


{0x002A144C},
{0x0F120002},	                          //0002	                          //0000	                          //awbb_GridEnable

                 //grid
{0x002A1426},
{0x0F1200AB},	                          //00AB	                          //00AB	                          //
{0x0F1200BF},	                          //00BF	                          //00BF	                          //
{0x0F1200D2},	                          //00D2	                          //00D2	                          //
{0x0F120093},	                          //0093	                          //0093	                          //
{0x002A1414},
{0x0F1202B8},	                          //02B8	                          //02B8	                          //
{0x0F120313},	                          //0313	                          //0313	                          //
{0x0F120366},	                          //0366	                          //0366	                          //
{0x0F121015},	                          //1015	                          //103C	                          //
{0x0F12106C},	                          //10BD	                          //10AA	                          //
{0x0F1210CA},	                          //117A	                          //1118	                          //
{0x0F121142},	                          //119C	                          //117C	                          //
{0x0F1211BB},	                          //11E7	                          //11F4	                          //
{0x0F121218},	                          //123B	                          //1258	                          //
{0x002A1384},
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //FFE0	                          //FFC0	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //FFC0	                          //FFC0	                          //FFE0	                          //0000	                          //0080	                          //
{0x0F120000},	                          //0000	                          //FFC0	                          //FFC0	                          //FFE0	                          //0000	                          //0100	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //FFE0	                          //FFC0	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //FFC0	                          //FFC0	                          //FFE0	                          //0000	                          //0080	                          //
{0x0F120000},	                          //0000	                          //FFC0	                          //FFC0	                          //FFE0	                          //0000	                          //0100	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //FFE0	                          //FFC0	                          //0000	                          //0000	                          //0000	                          //
{0x0F120000},	                          //0000	                          //FFC0	                          //FFC0	                          //FFE0	                          //0000	                          //0080	                          //
{0x0F120000},	                          //0000	                          //FFC0	                          //FFC0	                          //FFE0	                          //0000	                          //0100	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFC0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFC0	                          //FFF0	                          //FFF0	                          //
{0x0F12FF60},	                          //0000	                          //FFC0	                          //FFE0	                          //FFC0	                          //FFF0	                          //FFC0	                          //
{0x0F12FF06},	                          //0000	                          //FFC0	                          //FFC0	                          //FFC0	                          //FFF0	                          //FF80	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFC0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFC0	                          //FFF0	                          //FFF0	                          //
{0x0F12FF60},	                          //0000	                          //FFC0	                          //FFE0	                          //FFC0	                          //FFF0	                          //FFC0	                          //
{0x0F12FF06},	                          //0000	                          //FFC0	                          //FFC0	                          //FFC0	                          //FFF0	                          //FF80	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFE0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFE0	                          //FFF0	                          //0000	                          //
{0x0F12FFC0},	                          //0000	                          //FFE0	                          //FFE0	                          //FFC0	                          //FFF0	                          //FFF0	                          //
{0x0F12FF60},	                          //0000	                          //FFC0	                          //FFE0	                          //FFC0	                          //FFF0	                          //FFC0	                          //
{0x0F12FF06},	                          //0000	                          //FFC0	                          //FFC0	                          //FFC0	                          //FFF0	                          //FF80	                          //

                 //outdoor
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //FFFE    	                          //awbb_GridCorr_R_Out[0][0]                 	2   70001400
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //FFFE    	                          //awbb_GridCorr_R_Out[0][1]                 	2   70001402
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[0][2]                 	2   70001404
{0x0F12FFC0},	                          //0000	                          //FFE0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[0][3]                 	2   70001406
{0x0F12FFC0},	                          //0000	                          //FFD0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[0][4]                 	2   70001408
{0x0F12FFC0},	                          //0000	                          //FFC0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[0][5]                 	2   7000140A
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //FFFD    	                          //awbb_GridCorr_R_Out[1][0]                 	2   7000140C
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //FFFD    	                          //awbb_GridCorr_R_Out[1][1]                 	2   7000140E
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[1][2]                 	2   70001410
{0x0F12FFC0},	                          //0000	                          //FFE0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[1][3]                 	2   70001412
{0x0F12FFC0},	                          //0000	                          //FFD0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[1][4]                 	2   70001414
{0x0F12FFC0},	                          //0000	                          //FFC0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[1][5]                 	2   70001416
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //FFFC    	                          //awbb_GridCorr_R_Out[2][0]                 	2   70001418
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //FFFC    	                          //awbb_GridCorr_R_Out[2][1]                 	2   7000141A
{0x0F12FFC0},	                          //0000	                          //FFEB	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[2][2]                 	2   7000141C
{0x0F12FFC0},	                          //0000	                          //FFE0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[2][3]                 	2   7000141E
{0x0F12FFC0},	                          //0000	                          //FFD0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[2][4]                 	2   70001420
{0x0F12FFC0},	                          //0000	                          //FFC0	                          //0000	                          //0000    	                          //awbb_GridCorr_R_Out[2][5]                 	2   70001422
                 //                                    	                          //
{0x0F12FFE0},	                          //FFD0	                          //0000	                          //000C    	awbb_GridCorr_B_Out[0][0]                 	2   70001424
{0x0F12FFE0},	                          //FFD0	                          //0000	                          //0006    	awbb_GridCorr_B_Out[0][1]                 	2   70001426
{0x0F12FFE0},	                          //FFD0	                          //0000	                          //0000    	awbb_GridCorr_B_Out[0][2]                 	2   70001428
{0x0F12FFE0},	                          //FFC0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[0][3]                 	2   7000142A
{0x0F12FFE0},	                          //FFC0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[0][4]                 	2   7000142C
{0x0F12FFE0},	                          //FFC0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[0][5]                 	2   7000142E
{0x0F12FFE0},	                          //FFD0	                          //FFE0	                          //0000	                          //000C    	awbb_GridCorr_B_Out[1][0]                 	2   70001430
{0x0F12FFE0},	                          //FFD0	                          //FFE0	                          //0000	                          //0006    	awbb_GridCorr_B_Out[1][1]                 	2   70001432
{0x0F12FFE0},	                          //FFD0	                          //FFE0	                          //0000	                          //0000    	awbb_GridCorr_B_Out[1][2]                 	2   70001434
{0x0F12FFE0},	                          //FFC0	                          //FFE0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[1][3]                 	2   70001436
{0x0F12FFE0},	                          //FFC0	                          //FFD0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[1][4]                 	2   70001438
{0x0F12FFE0},	                          //FFC0	                          //FFC0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[1][5]                 	2   7000143A
{0x0F12FFE0},	                          //FFD0	                          //FFE0	                          //0000	                          //000C    	awbb_GridCorr_B_Out[2][0]                 	2   7000143C
{0x0F12FFE0},	                          //FFD0	                          //FFE0	                          //0000	                          //0006    	awbb_GridCorr_B_Out[2][1]                 	2   7000143E
{0x0F12FFE0},	                          //FFD0	                          //FFE0	                          //0000	                          //0000    	awbb_GridCorr_B_Out[2][2]                 	2   70001440
{0x0F12FFE0},	                          //FFC0	                          //FFE0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[2][3]                 	2   70001442
{0x0F12FFE0},	                          //FFC0	                          //FFD0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[2][4]                 	2   70001444
{0x0F12FFE0},	                          //FFC0	                          //FFC0	                          //0000	                          //0000	                          //0000    	awbb_GridCorr_B_Out[2][5]                 	2   70001446


{0x002A141A},
{0x0F121015},	                          //7000141A
{0x0F12106C},	                          //7000141C
{0x0F1210CA},	                          //7000141E
{0x0F121142},	                          //70001420
{0x0F1211BB},	                          //70001422
{0x0F12123B},	                          //70001424

{0x0F1200AB},	                          //70001426
{0x0F1200BF},	                          //70001428
{0x0F1200D2},	                          //7000142A
{0x0F120093},	                          //7000142C



{0x002A11E8},
{0x0F120020},

{0x002A142E},
{0x0F120000},	                          //00A0	                          //awbb_RGainOff
{0x0F120000},	                          //FFE0                              //awbb_BGainOff
{0x0F120000},	                          //awbb_GGainOff



                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///

                 //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          //                          ///
                 //RGB Indoor Gamma
{0x002A0740},
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120001},	                          //0001	                          //0001	                          //0001	                          //0000	                          //
{0x0F120007},	                          //0007	                          //0007	                          //0007	                          //0008	                          //
{0x0F120020},	                          //002D	                          //002D	                          //002D	                          //002D	                          //
{0x0F12005D},	                          //0075	                          //0075	                          //0075	                          //0076	                          //
{0x0F1200D5},	                          //00E9	                          //00E9	                          //00E9	                          //00E3	                          //
{0x0F120138},	                          //0143	                          //0143	                          //0143	                          //013F	                          //
{0x0F120163},	                          //016B	                          //016B	                          //016C	                          //0169	                          //
{0x0F120189},	                          //018F	                          //018F	                          //0190	                          //018D	                          //
{0x0F1201C6},	                          //01CB	                          //01CB	                          //01CC	                          //01C8	                          //
{0x0F1201F8},	                          //01FD	                          //0202	                          //01FD	                          //01FF	                          //01FA	                          //
{0x0F120222},	                          //0226	                          //022D	                          //0226	                          //022A	                          //0225	                          //
{0x0F120247},	                          //0249	                          //0255	                          //0249	                          //0252	                          //024C	                          //
{0x0F120282},	                          //0282	                          //029D	                          //0282	                          //0296	                          //0290	                          //
{0x0F1202B5},	                          //02B5	                          //02D6	                          //02B5	                          //02D6	                          //02CB	                          //
{0x0F12030F},	                          //030F	                          //033C	                          //030F	                          //033C	                          //0321	                          //
{0x0F12035F},	                          //035F	                          //038D	                          //035F	                          //038D	                          //0373	                          //
{0x0F1203A2},	                          //03A2	                          //03D0	                          //03A2	                          //03D0	                          //03A5	                          //
{0x0F1203D8},	                          //03D8	                          //03F7	                          //03D8	                          //03F7	                          //03D2	                          //
{0x0F1203FF},	                          //03FF	                          //03FF	                          //03FF	                          //03FF	                          //03FF	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120001},	                          //0001	                          //0001	                          //0001	                          //0000	                          //
{0x0F120007},	                          //0007	                          //0007	                          //0007	                          //0008	                          //
{0x0F120020},	                          //002D	                          //002D	                          //002D	                          //002D	                          //
{0x0F12005D},	                          //0075	                          //0075	                          //0075	                          //0076	                          //
{0x0F1200D5},	                          //00E9	                          //00E9	                          //00E9	                          //00E3	                          //
{0x0F120138},	                          //0143	                          //0143	                          //0143	                          //013F	                          //
{0x0F120163},	                          //016B	                          //016B	                          //016C	                          //0169	                          //
{0x0F120189},	                          //018F	                          //018F	                          //0190	                          //018D	                          //
{0x0F1201C6},	                          //01CB	                          //01CB	                          //01CC	                          //01C8	                          //
{0x0F1201F8},	                          //01FD	                          //01FD	                          //01FF	                          //01FA	                          //
{0x0F120222},	                          //0226	                          //0226	                          //022A	                          //0225	                          //
{0x0F120247},	                          //0249	                          //0249	                          //0252	                          //024C	                          //
{0x0F120282},	                          //0282	                          //0282	                          //0296	                          //0290	                          //
{0x0F1202B5},	                          //02B5	                          //02B5	                          //02D6	                          //02CB	                          //
{0x0F12030F},	                          //030F	                          //030F	                          //033C	                          //0321	                          //
{0x0F12035F},	                          //035F	                          //035F	                          //038D	                          //0373	                          //
{0x0F1203A2},	                          //03A2	                          //03A2	                          //03D0	                          //03A5	                          //
{0x0F1203D8},	                          //03D8	                          //03D8	                          //03F7	                          //03D2	                          //
{0x0F1203FF},	                          //03FF	                          //03FF	                          //03FF	                          //03FF	                          //
{0x0F120000},	                          //0000	                          //0000	                          //0000	                          //0000	                          //
{0x0F120001},	                          //0001	                          //0001	                          //0001	                          //0000	                          //
{0x0F120007},	                          //0007	                          //0007	                          //0007	                          //0008	                          //
{0x0F120020},	                          //002D	                          //002D	                          //002D	                          //002D	                          //
{0x0F12005D},	                          //0075	                          //0075	                          //0075	                          //0076	                          //
{0x0F1200D5},	                          //00E9	                          //00E9	                          //00E9	                          //00E3	                          //
{0x0F120138},	                          //0143	                          //0143	                          //0143	                          //013F	                          //
{0x0F120163},	                          //016B	                          //016B	                          //016C	                          //0169	                          //
{0x0F120189},	                          //018F	                          //018F	                          //0190	                          //018D	                          //
{0x0F1201C6},	                          //01CB	                          //01CB	                          //01CC	                          //01C8	                          //
{0x0F1201F8},	                          //01FD	                          //01FD	                          //01FF	                          //01FA	                          //
{0x0F120222},	                          //0226	                          //0226	                          //022A	                          //0225	                          //
{0x0F120247},	                          //0249	                          //0249	                          //0252	                          //024C	                          //
{0x0F120282},	                          //0282	                          //0282	                          //0296	                          //0290	                          //
{0x0F1202B5},	                          //02B5	                          //02B5	                          //02D6	                          //02CB	                          //
{0x0F12030F},	                          //030F	                          //030F	                          //033C	                          //0321	                          //
{0x0F12035F},	                          //035F	                          //035F	                          //038D	                          //0373	                          //
{0x0F1203A2},	                          //03A2	                          //03A2	                          //03D0	                          //03A5	                          //
{0x0F1203D8},	                          //03D8	                          //03D8	                          //03F7	                          //03D2	                          //
{0x0F1203FF},	                          //03FF	                          //03FF	                          //03FF	                          //03FF	                          //

                 //RGB Outdoor Gamma
{0x0F120000},	                          //0000                            //0000	                          //0000	                          //0000                           //0000	                          //0000	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][0]
{0x0F120001},	                          //0001                            //0004	                          //0004	                          //0000                           //0001	                          //0000	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][1]
{0x0F120007},	                          //0007                            //000A	                          //000A	                          //0006                           //0007	                          //0008	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][2]
{0x0F120020},	                          //002D                            //002E	                          //0030	                          //0028                           //002D	                          //002D	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][3]
{0x0F12005D},	                          //0075                            //0074	                          //0075	                          //006C                           //0075	                          //0076	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][4]
{0x0F1200D5},	                          //00E9                            //00EC	                          //00F0	                          //00E2                           //00E9	                          //00E3	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][5]
{0x0F120138},	                          //0143                            //014E	                          //014E	                          //0143                           //0143	                          //013F	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][6]
{0x0F120163},	                          //016B                            //0177	                          //0177	                          //016C                           //016C	                          //0169	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][7]
{0x0F120189},	                          //018F                            //019A	                          //019A	                          //0190                           //0190	                          //018D	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][8]
{0x0F1201C6},	                          //01CB                            //01D1	                          //01D2	                          //01CC                           //01CC	                          //01C8	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][9]
{0x0F1201F8},	                          //01FD                            //01FE	                          //0202	                          //01FF                           //01FF	                          //01FA	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][10]
{0x0F120222},	                          //0226                            //0226	                          //022D	                          //022A                           //022A	                          //0225	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][11]
{0x0F120247},	                          //0249                            //0249	                          //0255	                          //0252                           //0252	                          //024C	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][12]
{0x0F120282},	                          //0282                            //0283	                          //029D	                          //0296                           //0296	                          //0290	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][13]
{0x0F1202B5},	                          //02B5                            //02B5	                          //02D6	                          //02D6                           //02D6	                          //02CB	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][14]
{0x0F12030F},	                          //030F                            //030B	                          //033C	                          //033C                           //033C	                          //0321	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][15]
{0x0F12035F},	                          //035F                            //0358	                          //038D	                          //038D                           //038D	                          //0373	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][16]
{0x0F1203A2},	                          //03A2                            //039D	                          //03D0	                          //03D0                           //03D0	                          //03A5	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][17]
{0x0F1203D8},	                          //03D8                            //03D8	                          //03F7	                          //03F7                           //03F7	                          //03D2	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][18]
{0x002A0806},
{0x0F1203FF},	                          //03FF                            //03FF	                          //03FF	                          //03FF                           //03FF	                          //03FF	                          //TNP_gamma_usGammaLutRGBOutdoor 	[0][19]
{0x002A07E0},
{0x0F120000},	                          //0000                            //0000	                          //0000	                          //0000                           //0000	                          //0000	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][0]
{0x0F120001},	                          //0001                            //0004	                          //0004	                          //0000                           //0001	                          //0000	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][1]
{0x0F120007},	                          //0007                            //000A	                          //000A	                          //0006                           //0007	                          //0008	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][2]
{0x0F120020},	                          //002D                            //002E	                          //0030	                          //0028                           //002D	                          //002D	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][3]
{0x0F12005D},	                          //0075                            //0074	                          //0075	                          //006C                           //0075	                          //0076	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][4]
{0x0F1200D5},	                          //00E9                            //00EC	                          //00F0	                          //00E2                           //00E9	                          //00E3	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][5]
{0x0F120138},	                          //0143                            //014E	                          //014E	                          //0143                           //0143	                          //013F	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][6]
{0x0F120163},	                          //016B                            //0177	                          //0177	                          //016C                           //016C	                          //0169	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][7]
{0x0F120189},	                          //018F                            //019A	                          //019A	                          //0190                           //0190	                          //018D	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][8]
{0x0F1201C6},	                          //01CB                            //01D1	                          //01D2	                          //01CC                           //01CC	                          //01C8	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][9]
{0x0F1201F8},	                          //01FD                            //01FE	                          //0202	                          //01FF                           //01FF	                          //01FA	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][10]
{0x0F120222},	                          //0226                            //0226	                          //022D	                          //022A                           //022A	                          //0225	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][11]
{0x0F120247},	                          //0249                            //0249	                          //0255	                          //0252                           //0252	                          //024C	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][12]
{0x0F120282},	                          //0282                            //0283	                          //029D	                          //0296                           //0296	                          //0290	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][13]
{0x0F1202B5},	                          //02B5                            //02B5	                          //02D6	                          //02D6                           //02D6	                          //02CB	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][14]
{0x0F12030F},	                          //030F                            //030B	                          //033C	                          //033C                           //033C	                          //0321	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][15]
{0x0F12035F},	                          //035F                            //0358	                          //038D	                          //038D                           //038D	                          //0373	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][16]
{0x0F1203A2},	                          //03A2                            //039D	                          //03D0	                          //03D0                           //03D0	                          //03A5	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][17]
{0x0F1203D8},	                          //03D8                            //03D8	                          //03F7	                          //03F7                           //03F7	                          //03D2	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][18]
{0x002A082E},
{0x0F1203FF},	                          //03FF                            //03FF	                          //03FF	                          //03FF                           //03FF	                          //03FF	                          //TNP_gamma_usGammaLutRGBOutdoor 	[1][19]
{0x002A0808},
{0x0F120000},	                          //0000                            //0000	                          //0000	                          //0000                           //0000	                          //0000	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][0]
{0x0F120001},	                          //0001                            //0004	                          //0004	                          //0000                           //0001	                          //0000	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][1]
{0x0F120007},	                          //0007                            //000A	                          //000A	                          //0006                           //0007	                          //0008	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][2]
{0x0F120020},	                          //002D                            //002E	                          //0030	                          //0028                           //002D	                          //002D	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][3]
{0x0F12005D},	                          //0075                            //0074	                          //0075	                          //006C                           //0075	                          //0076	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][4]
{0x0F1200D5},	                          //00E9                            //00EC	                          //00F0	                          //00E2                           //00E9	                          //00E3	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][5]
{0x0F120138},	                          //0143                            //014E	                          //014E	                          //0143                           //0143	                          //013F	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][6]
{0x0F120163},	                          //016B                            //0177	                          //0177	                          //016C                           //016C	                          //0169	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][7]
{0x0F120189},	                          //018F                            //019A	                          //019A	                          //0190                           //0190	                          //018D	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][8]
{0x0F1201C6},	                          //01CB                            //01D1	                          //01D2	                          //01CC                           //01CC	                          //01C8	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][9]
{0x0F1201F8},	                          //01FD                            //01FE	                          //0202	                          //01FF                           //01FF	                          //01FA	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][10]
{0x0F120222},	                          //0226                            //0226	                          //022D	                          //022A                           //022A	                          //0225	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][11]
{0x0F120247},	                          //0249                            //0249	                          //0255	                          //0252                           //0252	                          //024C	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][12]
{0x0F120282},	                          //0282                            //0283	                          //029D	                          //0296                           //0296	                          //0290	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][13]
{0x0F1202B5},	                          //02B5                            //02B5	                          //02D6	                          //02D6                           //02D6	                          //02CB	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][14]
{0x0F12030F},	                          //030F                            //030B	                          //033C	                          //033C                           //033C	                          //0321	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][15]
{0x0F12035F},	                          //035F                            //0358	                          //038D	                          //038D                           //038D	                          //0373	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][16]
{0x0F1203A2},	                          //03A2                            //039D	                          //03D0	                          //03D0                           //03D0	                          //03A5	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][17]
{0x0F1203D8},	                          //03D8                            //03D8	                          //03F7	                          //03F7                           //03F7	                          //03D2	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][18]
{0x0F1203FF},	                          //03FF                            //03FF	                          //03FF	                          //03FF                           //03FF	                          //03FF	                          //TNP_gamma_usGammaLutRGBOutdoor 	[2][19]


                 //
                 //CCM

{0x002A08B2},
{0x0F1200C0},	                          //  700008B2
{0x0F120100},	                          //  700008B4
{0x0F120125},	                          //  700008B6
{0x0F12015F},	                          //  700008B8
{0x0F12017C},	                          //  700008BA
{0x0F120194},	                          //  700008BC


{0x0F120001},	                          //#wbt_bUseOutdoorCCM

                 //param_end	SARR_CcmsArray
                 //Retrieve - TVAR_wbt_pBaseCcms
{0x002A08A4},
{0x0F123F00},
{0x0F127000},	                          //TVAR_wbt_pBaseCcms

{0x002A3F00},
{0x0F12016C},	                          //0135	                          //0158	                          //016C	                          //0179	                          //0125	                          //01C7	                          //015F	#TVAR_wbt_pBaseCcms[0]	                          //                          //hor
{0x0F12FF94},	                          //FFAD	                          //FF9D	                          //FF94	                          //FF8D	                          //FFC0	                          //FFBD	                          //FFC6	#TVAR_wbt_pBaseCcms[1]                            //
{0x0F12FFCE},	                          //FFE1	                          //FFD5	                          //FFCE	                          //FFCA	                          //FFE9	                          //FFE3	                          //FFCF	#TVAR_wbt_pBaseCcms[2]                            //
{0x0F12FF20},	                          //FF14	                          //FF2D	                          //FF20	                          //FEF9	                          //FF2A	                          //FF84	                          //FF8E	#TVAR_wbt_pBaseCcms[3]                            //
{0x0F1201BF},	                          //01AD	                          //019A	                          //01BF	                          //0215	                          //015A	                          //013D	                          //01C4	#TVAR_wbt_pBaseCcms[4]                            //
{0x0F12FF53},	                          //FF49	                          //FF5D	                          //FF53	                          //FF35	                          //FF58	                          //FF6F	                          //FF47	#TVAR_wbt_pBaseCcms[5]                            //
{0x0F12003F},	                          //0061	                          //0057	                          //003F	                          //004A	                          //0002	                          //FFFB	                          //FFFD	#TVAR_wbt_pBaseCcms[6]                            //
{0x0F120007},	                          //002A	                          //0026	                          //0007	                          //000F	                          //FFE1	                          //FFE4	                          //FFF7	#TVAR_wbt_pBaseCcms[7]                            //
{0x0F1201DF},	                          //01CF	                          //01B9	                          //01DF	                          //01F3	                          //0174	                          //015B	                          //016A	#TVAR_wbt_pBaseCcms[8]                            //
{0x0F120110},	                          //00F9	                          //0111	                          //0110	                          //0119	                          //00DF	                          //00C3	                          //010A	#TVAR_wbt_pBaseCcms[9]                            //
{0x0F1200DF},	                          //00C6	                          //00DC	                          //00DF	                          //00E4	                          //00C4	                          //00CA	                          //012F	#TVAR_wbt_pBaseCcms[10]                           //
{0x0F12FF47},	                          //FF4D	                          //FF3B	                          //FF47	                          //FF3D	                          //FF80	                          //FF73	                          //FF57	#TVAR_wbt_pBaseCcms[11]                           //
{0x0F120206},	                          //01DC	                          //01D4	                          //0206	                          //023C	                          //00DB	                          //00FB	                          //013E	#TVAR_wbt_pBaseCcms[12]                           //
{0x0F12FF7F},	                          //FFEE	                          //FFDB	                          //FF7F	                          //FF8F	                          //FF2B	                          //FF67	                          //FFBC	#TVAR_wbt_pBaseCcms[13]                           //
{0x0F120191},	                          //017C	                          //0177	                          //0191	                          //01A2	                          //0137	                          //00D8	                          //0163	#TVAR_wbt_pBaseCcms[14]                           //
{0x0F12FF06},	                          //FED6	                          //FEF6	                          //FF06	                          //FE81	                          //FEED	                          //FF32	                          //FFC0	#TVAR_wbt_pBaseCcms[15]                           //
{0x0F1201BA},	                          //01DC	                          //01C5	                          //01BA	                          //0244	                          //00E9	                          //0125	                          //0138	#TVAR_wbt_pBaseCcms[16]                           //
{0x0F120108},	                          //0108	                          //0108	                          //0108	                          //0148	                          //0083	                          //00AD	                          //0106	#TVAR_wbt_pBaseCcms[17]                           //
{0x0F12016C},	                          //0135	                          //0158	                          //016C	/0179	                          //0125	                          //01C7	                          //015F	#TVAR_wbt_pBaseCcms[18]	                          //                          //incaA
{0x0F12FF94},	                          //FFAD	                          //FF9D	                          //FF94	                          //FF8D	                          //FFC0	                          //FFBD	                          //FFC6	#TVAR_wbt_pBaseCcms[19]                           //
{0x0F12FFCE},	                          //FFE1	                          //FFD5	                          //FFCE	                          //FFCA	                          //FFE9	                          //FFE3	                          //FFCF	#TVAR_wbt_pBaseCcms[20]                           //
{0x0F12FF20},	                          //FF14	                          //FF2D	                          //FF20	                          //FEF9	                          //FF2A	                          //FF84	                          //FF8E	#TVAR_wbt_pBaseCcms[21]                           //
{0x0F1201BF},	                          //01AD	                          //019A	                          //01BF	                          //0215	                          //015A	                          //013D	                          //01C4	#TVAR_wbt_pBaseCcms[22]                           //
{0x0F12FF53},	                          //FF49	                          //FF5D	                          //FF53	                          //FF35	                          //FF58	                          //FF6F	                          //FF47	#TVAR_wbt_pBaseCcms[23]                           //
{0x0F12003F},	                          //0061	                          //0057	                          //003F	                          //004A	                          //0002	                          //FFFB	                          //FFFD	#TVAR_wbt_pBaseCcms[24]                           //
{0x0F120007},	                          //002A	                          //0026	                          //0007	                          //000F	                          //FFE1	                          //FFE4	                          //FFF7	#TVAR_wbt_pBaseCcms[25]                           //
{0x0F1201DF},	                          //01CF	                          //01B9	                          //01DF	                          //01F3	                          //0174	                          //015B	                          //016A	#TVAR_wbt_pBaseCcms[26]                           //
{0x0F120110},	                          //00F9	                          //0111	                          //0110	                          //0119	                          //00DF	                          //00C3	                          //010A	#TVAR_wbt_pBaseCcms[27]                           //
{0x0F1200DF},	                          //00C6	                          //00DC	                          //00DF	                          //00E4	                          //00C4	                          //00CA	                          //012F	#TVAR_wbt_pBaseCcms[28]                           //
{0x0F12FF47},	                          //FF4D	                          //FF3B	                          //FF47	                          //FF3D	                          //FF80	                          //FF73	                          //FF57	#TVAR_wbt_pBaseCcms[29]                           //
{0x0F120206},	                          //01DC	                          //01D4	                          //0206	                          //023C	                          //00DB	                          //00FB	                          //013E	#TVAR_wbt_pBaseCcms[30]                           //
{0x0F12FF7F},	                          //FFEE	                          //FFDB	                          //FF7F	                          //FF8F	                          //FF2B	                          //FF67	                          //FFBC	#TVAR_wbt_pBaseCcms[31]                           //
{0x0F120191},	                          //017C	                          //0177	                          //0191	                          //01A2	                          //0137	                          //00D8	                          //0163	#TVAR_wbt_pBaseCcms[32]                           //
{0x0F12FF06},	                          //FED6	                          //FEF6	                          //FF06	                          //FE81	                          //FEED	                          //FF32	                          //FFC0	#TVAR_wbt_pBaseCcms[33]                           //
{0x0F1201BA},	                          //01DC	                          //01C5	                          //01BA	                          //0244	                          //00E9	                          //0125	                          //0138	#TVAR_wbt_pBaseCcms[34]                           //
{0x0F120108},	                          //0108	                          //0108	                          //0108	                          //0148	                          //0083	                          //00AD	                          //0106	#TVAR_wbt_pBaseCcms[35]                           //
{0x0F12016C},	                          //0179	                          //0125	                          //01C7	                          //015F	#TVAR_wbt_pBaseCcms[36]	                          //                          //WW
{0x0F12FF94},	                          //FF8D	                          //FFC0	                          //FFBD	                          //FFC6	#TVAR_wbt_pBaseCcms[37]                           //
{0x0F12FFCE},	                          //FFCA	                          //FFE9	                          //FFE3	                          //FFCF	#TVAR_wbt_pBaseCcms[38]                           //
{0x0F12FF20},	                          //FEF9	                          //FF2A	                          //FF84	                          //FF8E	#TVAR_wbt_pBaseCcms[39]                           //
{0x0F1201BF},	                          //0215	                          //015A	                          //013D	                          //01C4	#TVAR_wbt_pBaseCcms[40]                           //
{0x0F12FF53},	                          //FF35	                          //FF58	                          //FF6F	                          //FF47	#TVAR_wbt_pBaseCcms[41]                           //
{0x0F12003F},	                          //004A	                          //0002	                          //FFFB	                          //FFFD	#TVAR_wbt_pBaseCcms[42]                           //
{0x0F120007},	                          //000F	                          //FFE1	                          //FFE4	                          //FFF7	#TVAR_wbt_pBaseCcms[43]                           //
{0x0F1201DF},	                          //01F3	                          //0174	                          //015B	                          //016A	#TVAR_wbt_pBaseCcms[44]                           //
{0x0F120110},	                          //0119	                          //00DF	                          //00C3	                          //010A	#TVAR_wbt_pBaseCcms[45]                           //
{0x0F1200DF},	                          //00E4	                          //00C4	                          //00CA	                          //012F	#TVAR_wbt_pBaseCcms[46]                           //
{0x0F12FF47},	                          //FF3D	                          //FF80	                          //FF73	                          //FF57	#TVAR_wbt_pBaseCcms[47]                           //
{0x0F120206},	                          //023C	                          //00DB	                          //00FB	                          //013E	#TVAR_wbt_pBaseCcms[48]                           //
{0x0F12FF7F},	                          //FF8F	                          //FF2B	                          //FF67	                          //FFBC	#TVAR_wbt_pBaseCcms[49]                           //
{0x0F120191},	                          //01A2	                          //0137	                          //00D8	                          //0163	#TVAR_wbt_pBaseCcms[50]                           //
{0x0F12FF06},	                          //FE81	                          //FEED	                          //FF32	                          //FFC0	#TVAR_wbt_pBaseCcms[51]                           //
{0x0F1201BA},	                          //0244	                          //00E9	                          //0125	                          //0138	#TVAR_wbt_pBaseCcms[52]                           //
{0x0F120108},	                          //0148	                          //0083	                          //00AD	                          //0106	#TVAR_wbt_pBaseCcms[53]                           //
{0x0F12017F},	                          //0179	                          //0149	                          //0125	                          //01C7	                          //015F	#TVAR_wbt_pBaseCcms[54]	                          //                          //CW
{0x0F12FF9C},	                          //FF8D	                          //FFAB	                          //FFC0	                          //FFBD	                          //FFC6	#TVAR_wbt_pBaseCcms[55]                           //
{0x0F12FFDD},	                          //FFC6	                          //FFDA	                          //FFE9	                          //FFE3	                          //FFCF	#TVAR_wbt_pBaseCcms[56]                           //
{0x0F12FF20},	                          //FF20	                          //FF21	                          //FF2A	                          //FF84	                          //FF8E	#TVAR_wbt_pBaseCcms[57]                           //
{0x0F120196},	                          //0196	                          //018D	                          //015A	                          //013D	                          //01C4	#TVAR_wbt_pBaseCcms[58]                           //
{0x0F12FF53},	                          //FF53	                          //FF54	                          //FF58	                          //FF6F	                          //FF47	#TVAR_wbt_pBaseCcms[59]                           //
{0x0F12000D},	                          //000D	                          //0002	                          //0002	                          //FFFB	                          //FFFD	#TVAR_wbt_pBaseCcms[60]                           //
{0x0F12FFE8},	                          //FFE8	                          //FFE1	                          //FFE1	                          //FFE4	                          //FFF7	#TVAR_wbt_pBaseCcms[61]                           //
{0x0F120188},	                          //0188	                          //0174	                          //0174	                          //015B	                          //016A	#TVAR_wbt_pBaseCcms[62]                           //
{0x0F120107},	                          //0114	                          //00DF	                          //00DF	                          //00C3	                          //010A	#TVAR_wbt_pBaseCcms[63]                           //
{0x0F1200E1},	                          //00EB	                          //00C4	                          //00C4	                          //00CA	                          //012F	#TVAR_wbt_pBaseCcms[64]                           //
{0x0F12FF3E},	                          //FF27	                          //FF80	                          //FF80	                          //FF73	                          //FF57	#TVAR_wbt_pBaseCcms[65]                           //
{0x0F120114},	                          //0114	                          //00DB	                          //00DB	                          //00FB	                          //013E	#TVAR_wbt_pBaseCcms[66]                           //
{0x0F12FF3B},	                          //FF3B	                          //FF2B	                          //FF2B	                          //FF67	                          //FFBC	#TVAR_wbt_pBaseCcms[67]                           //
{0x0F120148},	                          //0148	                          //0137	                          //0137	                          //00D8	                          //0163	#TVAR_wbt_pBaseCcms[68]                           //
{0x0F12FEF1},	                          //FEF1	                          //FEED	                          //FEED	                          //FF32	                          //FFC0	#TVAR_wbt_pBaseCcms[69]                           //
{0x0F120111},	                          //0111	                          //00E9	                          //00E9	                          //0125	                          //0138	#TVAR_wbt_pBaseCcms[70]                           //
{0x0F12009C},	                          //009C	                          //0083	                          //0083	                          //00AD	                          //0106	#TVAR_wbt_pBaseCcms[71]                           //
{0x0F12017F},	                          //0179	                          //0149	                          //0125	                          //01C7	                          //015F	#TVAR_wbt_pBaseCcms[72]	                          //                          //D50
{0x0F12FF9C},	                          //FF8D	                          //FFAB	                          //FFC0	                          //FFBD	                          //FFC6	#TVAR_wbt_pBaseCcms[73]                           //
{0x0F12FFDD},	                          //FFC6	                          //FFDA	                          //FFE9	                          //FFE3	                          //FFCF	#TVAR_wbt_pBaseCcms[74]                           //
{0x0F12FF20},	                          //FF20	                          //FF21	                          //FF2A	                          //FF84	                          //FF8E	#TVAR_wbt_pBaseCcms[75]                           //
{0x0F120196},	                          //0196	                          //018D	                          //015A	                          //013D	                          //01C4	#TVAR_wbt_pBaseCcms[76]                           //
{0x0F12FF53},	                          //FF53	                          //FF54	                          //FF58	                          //FF6F	                          //FF47	#TVAR_wbt_pBaseCcms[77]                           //
{0x0F12000D},	                          //000D	                          //0002	                          //0002	                          //FFFB	                          //FFFD	#TVAR_wbt_pBaseCcms[78]                           //
{0x0F12FFE8},	                          //FFE8	                          //FFE1	                          //FFE1	                          //FFE4	                          //FFF7	#TVAR_wbt_pBaseCcms[79]                           //
{0x0F120188},	                          //0188	                          //0174	                          //0174	                          //015B	                          //016A	#TVAR_wbt_pBaseCcms[80]                           //
{0x0F120107},	                          //0114	                          //00DF	                          //00DF	                          //00C3	                          //010A	#TVAR_wbt_pBaseCcms[81]                           //
{0x0F1200E1},	                          //00EB	                          //00C4	                          //00C4	                          //00CA	                          //012F	#TVAR_wbt_pBaseCcms[82]                           //
{0x0F12FF3E},	                          //FF27	                          //FF80	                          //FF80	                          //FF73	                          //FF57	#TVAR_wbt_pBaseCcms[83]                           //
{0x0F120114},	                          //0114	                          //00DB	                          //00DB	                          //00FB	                          //013E	#TVAR_wbt_pBaseCcms[84]                           //
{0x0F12FF3B},	                          //FF3B	                          //FF2B	                          //FF2B	                          //FF67	                          //FFBC	#TVAR_wbt_pBaseCcms[85]                           //
{0x0F120148},	                          //0148	                          //0137	                          //0137	                          //00D8	                          //0163	#TVAR_wbt_pBaseCcms[86]                           //
{0x0F12FEF1},	                          //FEF1	                          //FEED	                          //FEED	                          //FF32	                          //FFC0	#TVAR_wbt_pBaseCcms[87]                           //
{0x0F120111},	                          //0111	                          //00E9	                          //00E9	                          //0125	                          //0138	#TVAR_wbt_pBaseCcms[88]                           //
{0x0F12009C},	                          //009C	                          //0083	                          //0083	                          //00AD	                          //0106	#TVAR_wbt_pBaseCcms[89]                           //
{0x0F12017F},	                          //0179	                          //0149	                          //0125	                          //01C7	                          //015F	#TVAR_wbt_pBaseCcms[90]	                          //                          //D65
{0x0F12FF9C},	                          //FF8D	                          //FFAB	                          //FFC0	                          //FFBD	                          //FFC6	#TVAR_wbt_pBaseCcms[91]                           //
{0x0F12FFDD},	                          //FFC6	                          //FFDA	                          //FFE9	                          //FFE3	                          //FFCF	#TVAR_wbt_pBaseCcms[92]                           //
{0x0F12FF20},	                          //FF20	                          //FF21	                          //FF2A	                          //FF84	                          //FF8E	#TVAR_wbt_pBaseCcms[93]                           //
{0x0F120196},	                          //0196	                          //018D	                          //015A	                          //013D	                          //01C4	#TVAR_wbt_pBaseCcms[94]                           //
{0x0F12FF53},	                          //FF53	                          //FF54	                          //FF58	                          //FF6F	                          //FF47	#TVAR_wbt_pBaseCcms[95]                           //
{0x0F12000D},	                          //000D	                          //0002	                          //0002	                          //FFFB	                          //FFFD	#TVAR_wbt_pBaseCcms[96]                           //
{0x0F12FFE8},	                          //FFE8	                          //FFE1	                          //FFE1	                          //FFE4	                          //FFF7	#TVAR_wbt_pBaseCcms[97]                           //
{0x0F120188},	                          //0188	                          //0174	                          //0174	                          //015B	                          //016A	#TVAR_wbt_pBaseCcms[98]                           //
{0x0F120107},	                          //0114	                          //00DF	                          //00DF	                          //00C3	                          //010A	#TVAR_wbt_pBaseCcms[99]                           //
{0x0F1200E1},	                          //00EB	                          //00C4	                          //00C4	                          //00CA	                          //012F	#TVAR_wbt_pBaseCcms[100]                          //
{0x0F12FF3E},	                          //FF27	                          //FF80	                          //FF80	                          //FF73	                          //FF57	#TVAR_wbt_pBaseCcms[101]                          //
{0x0F120114},	                          //0114	                          //00DB	                          //00DB	                          //00FB	                          //013E	#TVAR_wbt_pBaseCcms[102]                          //
{0x0F12FF3B},	                          //FF3B	                          //FF2B	                          //FF2B	                          //FF67	                          //FFBC	#TVAR_wbt_pBaseCcms[103]                          //
{0x0F120148},	                          //0148	                          //0137	                          //0137	                          //00D8	                          //0163	#TVAR_wbt_pBaseCcms[104]                          //
{0x0F12FEF1},	                          //FEF1	                          //FEED	                          //FEED	                          //FF32	                          //FFC0	#TVAR_wbt_pBaseCcms[105]                          //
{0x0F120111},	                          //0111	                          //00E9	                          //00E9	                          //0125	                          //0138	#TVAR_wbt_pBaseCcms[106]                          //
{0x0F12009C},	                          //009C	                          //0083	                          //0083	                          //00AD	                          //0106	#TVAR_wbt_pBaseCcms[107]                          //

                 //	param_end	TVAR_wbt_pBaseCcms
                 //	Retrieve - TVAR_wbt_pOutdoorCcm
{0x002A08AC},
{0x0F123FD8},
{0x0F127000},	                          //
                 //	param_start	TVAR_wbt_pOutdoorCcm
{0x002A3FD8},
{0x0F12017C},	                          //01A3                            //0159	                          //016A	                          //01F8	                          //#TVAR_wbt_pOutdoorCcm[0]
{0x0F12FFA5},	                          //FF8B                            //FF99	                          //FF94	                          //FF7F	                          //#TVAR_wbt_pOutdoorCcm[1]
{0x0F12FFCE},	                          //FFC9                            //FFD0	                          //FFCA	                          //FFCB	                          //#TVAR_wbt_pOutdoorCcm[2]
{0x0F12FEEE},	                          //FEE8                            //FEF9	                          //FF17	                          //FF4B	                          //#TVAR_wbt_pOutdoorCcm[3]
{0x0F12019E},	                          //01B6                            //0185	                          //0176	                          //01BA	                          //#TVAR_wbt_pOutdoorCcm[4]
{0x0F12FF4F},	                          //FF46                            //FF32	                          //FF49	                          //FF8C	                          //#TVAR_wbt_pOutdoorCcm[5]
{0x0F12FFD7},	                          //FFF3                            //FFE0	                          //FFE4	                          //FFBE	                          //#TVAR_wbt_pOutdoorCcm[6]
{0x0F12FFD3},	                          //FFB4                            //FFBA	                          //FFC2	                          //FFC7	                          //#TVAR_wbt_pOutdoorCcm[7]
{0x0F1201A1},	                          //019C                            //0175	                          //0168	                          //01A9	                          //#TVAR_wbt_pOutdoorCcm[8]
{0x0F1200EC},	                          //0104                            //00E0	                          //00E4	                          //0142	                          //#TVAR_wbt_pOutdoorCcm[9]
{0x0F1200D3},	                          //00E2                            //00BF	                          //00C7	                          //0139	                          //#TVAR_wbt_pOutdoorCcm[10]
{0x0F12FF6A},	                          //FF4C                            //FF5F	                          //FF71	                          //FF57	                          //#TVAR_wbt_pOutdoorCcm[11]
{0x0F1200DA},	                          //00DA                            //00C9	                          //00DF	                          //01B5	                          //#TVAR_wbt_pOutdoorCcm[12]
{0x0F12FF20},	                          //FF24                            //FF2A	                          //FF17	                          //FF46	                          //#TVAR_wbt_pOutdoorCcm[13]
{0x0F12014B},	                          //0151                            //0128	                          //0140	                          //0174	                          //#TVAR_wbt_pOutdoorCcm[14]
{0x0F12FEA6},	                          //FE94                            //FEA1	                          //FEC8	                          //FF08	                          //#TVAR_wbt_pOutdoorCcm[15]
{0x0F1200FC},	                          //00EE                            //00D9	                          //00DE	                          //0181	                          //#TVAR_wbt_pOutdoorCcm[16]
{0x0F1200E2},	                          //00CD                            //00A1	                          //00AC	                          //0135	                          //#TVAR_wbt_pOutdoorCcm[17]




{0x002A01AE},
{0x0F120801},

                 //gain ? Setting ??? : DNP?? shutter 1 msec???? ????
                 //NI(noise + index) Mon_AFIT_uNoiseInd : 70001DA4
                 // bWWW_On for outdoor scene
{0x002A0940},
{0x0F120050},	                          // x7.4
{0x0F1200B0},	                          // x3.6
{0x0F120196},	                          // x2.2
{0x0F120245},	                          // x1.5
{0x0F120300},	                          // x1.0




{0x002A0974},
{0x0F120000},	                          //	AFIT16_BRIGHTNESS                                       //AFIT 0
{0x0F120000},	                          //	AFIT16_CONTRAST
{0x0F120000},	                          //	AFIT16_SATURATION
{0x0F120000},	                          //	AFIT16_SHARP_BLUR
{0x0F120000},	                          //	AFIT16_GLAMOUR
{0x0F1200C0},	                          //	AFIT16_bnr_edge_high
{0x0F120064},	                          //	AFIT16_postdmsc_iLowBright
{0x0F120384},	                          //	AFIT16_postdmsc_iHighBright
{0x0F120032},	                          //	AFIT16_postdmsc_iLowSat
{0x0F1201F4},	                          //	AFIT16_postdmsc_iHighSat
{0x0F120070},	                          //	AFIT16_postdmsc_iTune
{0x0F120040},	                          //	AFIT16_yuvemix_mNegRanges_0
{0x0F1200A0},	                          //	AFIT16_yuvemix_mNegRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mNegRanges_2
{0x0F120010},	                          //	AFIT16_yuvemix_mPosRanges_0
{0x0F120040},	                          //	AFIT16_yuvemix_mPosRanges_1
{0x0F1200A0},	                          //	AFIT16_yuvemix_mPosRanges_2
{0x0F121430},	                          //	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh
{0x0F120201},	                          //	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh
{0x0F120204},	                          //	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh
{0x0F12FF04},	                          //	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low
{0x0F1203FF},	                          //	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low
{0x0F120403},	                          //	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin
{0x0F121B06},	                          //	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow
{0x0F126015},	                          //	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH
{0x0F1200C0},	                          //	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune
{0x0F126080},	                          //	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh
{0x0F124080},	                          //	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh
{0x0F120640},	                          //	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed
{0x0F120306},	                          //	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh
{0x0F122003},	                          //	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH
{0x0F12FF01},	                          //	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit
{0x0F120000},	                          //	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2
{0x0F120400},	                          //	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower
{0x0F12365A},	                          //	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow
{0x0F12102A},	                          //	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow
{0x0F12000B},	                          //	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow
{0x0F120600},	                          //	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower
{0x0F125A0F},	                          //	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit
{0x0F120505},	                          //	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope
{0x0F12FF00},	                          //	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR
{0x0F120000},	                          //	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres
{0x0F12FF00},	                          //	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR
{0x0F123014},	                          //	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen
{0x0F120418},	                          //	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh
{0x0F120101},	                          //	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative
{0x0F120800},	                          //	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle
{0x0F121804},	                          //	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh
{0x0F124008},	                          //	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh
{0x0F120540},	                          //	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange
{0x0F128006},	                          //	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad
{0x0F120020},	                          //	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal
{0x0F120000},	                          //	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh
{0x0F121800},	                          //	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat
{0x0F120000},	                          //	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit
{0x0F121E10},	                          //	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff
{0x0F12000B},	                          //	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2
{0x0F120005},	                          //	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2
{0x0F120405},	                          //	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY
{0x0F120205},	                          //	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm
{0x0F120304},	                          //	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm
{0x0F120409},	                          //	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift
{0x0F120306},	                          //	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y
{0x0F120407},	                          //	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y
{0x0F122C04},	                          //	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV
{0x0F12022C},	                          //	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y
{0x0F121402},	                          //	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV
{0x0F120618},	                          //	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL
{0x0F121E02},	                          //	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL
{0x0F128018},	                          //	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower
{0x0F120080},	                          //	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce
{0x0F120080},	                          //	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset
{0x0F120180},	                          //	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H
{0x0F120A0A},	                          //	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C
{0x0F120101},	                          //	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C
{0x0F122A36},	                          //	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh
{0x0F126024},	                          //	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower
{0x0F122A36},	                          //	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise
{0x0F12FFFF},	                          //	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp
{0x0F120808},	                          //	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope
{0x0F120A01},	                          //	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin
{0x0F120106},	                          //	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin
{0x0F123601},	                          //	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin
{0x0F12252A},	                          //	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin
{0x0F123660},	                          //	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin
{0x0F12FF2A},	                          //	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin
{0x0F1208FF},	                          //	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin
{0x0F120008},	                          //	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]
{0x0F120003},	                          //	AFITB_bnr_nClustLevel_C      [0]
{0x0F120000},	                          //	AFIT16_BRIGHTNESS                                     //AFIT 1
{0x0F120000},	                          //	AFIT16_CONTRAST
{0x0F120000},	                          //	AFIT16_SATURATION
{0x0F120000},	                          //	AFIT16_SHARP_BLUR
{0x0F120000},	                          //	AFIT16_GLAMOUR
{0x0F1200C0},	                          //	AFIT16_bnr_edge_high
{0x0F120064},	                          //	AFIT16_postdmsc_iLowBright
{0x0F120384},	                          //	AFIT16_postdmsc_iHighBright
{0x0F120032},	                          //	AFIT16_postdmsc_iLowSat
{0x0F1201F4},	                          //	AFIT16_postdmsc_iHighSat
{0x0F120070},	                          //	AFIT16_postdmsc_iTune
{0x0F120040},	                          //	AFIT16_yuvemix_mNegRanges_0
{0x0F1200A0},	                          //	AFIT16_yuvemix_mNegRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mNegRanges_2
{0x0F120010},	                          //	AFIT16_yuvemix_mPosRanges_0
{0x0F120060},	                          //	AFIT16_yuvemix_mPosRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mPosRanges_2
{0x0F121430},	                          //	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh
{0x0F120201},	                          //	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh
{0x0F120204},	                          //	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh
{0x0F12FF04},	                          //	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low
{0x0F1203FF},	                          //	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low
{0x0F120103},	                          //	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin
{0x0F121205},	                          //	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow
{0x0F12400D},	                          //	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH
{0x0F120080},	                          //	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune
{0x0F122080},	                          //	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh
{0x0F123040},	                          //	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh
{0x0F120630},	                          //	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed
{0x0F120306},	                          //	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh
{0x0F122003},	                          //	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH
{0x0F12FF01},	                          //	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit
{0x0F120404},	                          //	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2
{0x0F120300},	                          //	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower
{0x0F12245A},	                          //	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow
{0x0F121018},	                          //	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow
{0x0F12000B},	                          //	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow
{0x0F120B00},	                          //	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower
{0x0F125A0F},	                          //	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit
{0x0F120505},	                          //	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope
{0x0F12FF00},	                          //	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR
{0x0F120000},	                          //	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres
{0x0F12FF00},	                          //	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR
{0x0F123414},	                          //	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen
{0x0F12041C},	                          //	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh
{0x0F120101},	                          //	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative
{0x0F120800},	                          //	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle
{0x0F121004},	                          //	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh
{0x0F124008},	                          //	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh
{0x0F120540},	                          //	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange
{0x0F128006},	                          //	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad
{0x0F120020},	                          //	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal
{0x0F120000},	                          //	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh
{0x0F121800},	                          //	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat
{0x0F120000},	                          //	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit
{0x0F121E10},	                          //	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff
{0x0F12000B},	                          //	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2
{0x0F120005},	                          //	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2
{0x0F120405},	                          //	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY
{0x0F120205},	                          //	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm
{0x0F120304},	                          //	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm
{0x0F120409},	                          //	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift
{0x0F120306},	                          //	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y
{0x0F120407},	                          //	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y
{0x0F122C04},	                          //	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV
{0x0F12022C},	                          //	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y
{0x0F121402},	                          //	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV
{0x0F120618},	                          //	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL
{0x0F121E02},	                          //	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL
{0x0F128018},	                          //	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower
{0x0F120080},	                          //	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce
{0x0F120080},	                          //	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset
{0x0F120180},	                          //	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H
{0x0F120A0A},	                          //	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C
{0x0F120101},	                          //	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C
{0x0F121B24},	                          //	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh
{0x0F126024},	                          //	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower
{0x0F12181E},	                          //	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise
{0x0F12FFFF},	                          //	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp
{0x0F120808},	                          //	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope
{0x0F120A01},	                          //	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin
{0x0F120106},	                          //	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin
{0x0F122401},	                          //	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin
{0x0F12251B},	                          //	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin
{0x0F121E60},	                          //	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin
{0x0F12FF18},	                          //	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin
{0x0F1208FF},	                          //	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin
{0x0F120008},	                          //	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]
{0x0F120003},	                          //	AFITB_bnr_nClustLevel_C      [0]
{0x0F120000},	                          //	AFIT16_BRIGHTNESS                                       //AFIT 2
{0x0F120000},	                          //	AFIT16_CONTRAST
{0x0F120000},	                          //	AFIT16_SATURATION
{0x0F120000},	                          //	AFIT16_SHARP_BLUR
{0x0F120000},	                          //	AFIT16_GLAMOUR
{0x0F1200C0},	                          //	AFIT16_bnr_edge_high
{0x0F120064},	                          //	AFIT16_postdmsc_iLowBright
{0x0F120384},	                          //	AFIT16_postdmsc_iHighBright
{0x0F120032},	                          //	AFIT16_postdmsc_iLowSat
{0x0F1201F4},	                          //	AFIT16_postdmsc_iHighSat
{0x0F120070},	                          //	AFIT16_postdmsc_iTune
{0x0F120040},	                          //	AFIT16_yuvemix_mNegRanges_0
{0x0F1200A0},	                          //	AFIT16_yuvemix_mNegRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mNegRanges_2
{0x0F120010},	                          //	AFIT16_yuvemix_mPosRanges_0
{0x0F120060},	                          //	AFIT16_yuvemix_mPosRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mPosRanges_2
{0x0F121430},	                          //	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh
{0x0F120201},	                          //	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh
{0x0F120204},	                          //	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh
{0x0F12FF04},	                          //	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low
{0x0F1203FF},	                          //	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low
{0x0F120003},	                          //	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin
{0x0F120C03},	                          //	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow
{0x0F122806},	                          //	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH
{0x0F120060},	                          //	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune
{0x0F121580},	                          //	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh
{0x0F122020},	                          //	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh
{0x0F120620},	                          //	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed
{0x0F120306},	                          //	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh
{0x0F122003},	                          //	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH
{0x0F12FF01},	                          //	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit
{0x0F120404},	                          //	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2
{0x0F120300},	                          //	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower
{0x0F12145A},	                          //	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow
{0x0F121010},	                          //	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow
{0x0F12000B},	                          //	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow
{0x0F120E00},	                          //	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower
{0x0F125A0F},	                          //	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit
{0x0F120504},	                          //	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope
{0x0F12FF00},	                          //	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR
{0x0F120000},	                          //	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres
{0x0F12FF00},	                          //	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR
{0x0F123814},	                          //	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen
{0x0F120428},	                          //	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh
{0x0F120101},	                          //	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative
{0x0F128000},	                          //	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle
{0x0F120A04},	                          //	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh
{0x0F124008},	                          //	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh
{0x0F120540},	                          //	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange
{0x0F128006},	                          //	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad
{0x0F120020},	                          //	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal
{0x0F120000},	                          //	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh
{0x0F121800},	                          //	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat
{0x0F120000},	                          //	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit
{0x0F121E10},	                          //	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff
{0x0F12000B},	                          //	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2
{0x0F120005},	                          //	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2
{0x0F120405},	                          //	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY
{0x0F120207},	                          //	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm
{0x0F120304},	                          //	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm
{0x0F120409},	                          //	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift
{0x0F120306},	                          //	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y
{0x0F120407},	                          //	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y
{0x0F121C04},	                          //	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV
{0x0F120214},	                          //	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y
{0x0F121002},	                          //	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV
{0x0F120610},	                          //	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL
{0x0F121E02},	                          //	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL
{0x0F128018},	                          //	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower
{0x0F120080},	                          //	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce
{0x0F120080},	                          //	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset
{0x0F120180},	                          //	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H
{0x0F120A0A},	                          //	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C
{0x0F120101},	                          //	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C
{0x0F12121B},	                          //	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh
{0x0F126024},	                          //	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower
{0x0F120C0C},	                          //	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise
{0x0F12FFFF},	                          //	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp
{0x0F120808},	                          //	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope
{0x0F120A01},	                          //	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin
{0x0F120106},	                          //	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin
{0x0F121B01},	                          //	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin
{0x0F122512},	                          //	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin
{0x0F120C60},	                          //	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin
{0x0F12FF0C},	                          //	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin
{0x0F1208FF},	                          //	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin
{0x0F120008},	                          //	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]
{0x0F120003},	                          //	AFITB_bnr_nClustLevel_C      [0]
{0x0F120000},	                          //	AFIT16_BRIGHTNESS                                    //AFIT 3
{0x0F120000},	                          //	AFIT16_CONTRAST
{0x0F120000},	                          //	AFIT16_SATURATION
{0x0F120000},	                          //	AFIT16_SHARP_BLUR
{0x0F120000},	                          //	AFIT16_GLAMOUR
{0x0F1200C0},	                          //	AFIT16_bnr_edge_high
{0x0F120064},	                          //	AFIT16_postdmsc_iLowBright
{0x0F120384},	                          //	AFIT16_postdmsc_iHighBright
{0x0F120032},	                          //	AFIT16_postdmsc_iLowSat
{0x0F1201F4},	                          //	AFIT16_postdmsc_iHighSat
{0x0F120070},	                          //	AFIT16_postdmsc_iTune
{0x0F120040},	                          //	AFIT16_yuvemix_mNegRanges_0
{0x0F1200A0},	                          //	AFIT16_yuvemix_mNegRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mNegRanges_2
{0x0F120010},	                          //	AFIT16_yuvemix_mPosRanges_0
{0x0F120060},	                          //	AFIT16_yuvemix_mPosRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mPosRanges_2
{0x0F121430},	                          //	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh
{0x0F120201},	                          //	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh
{0x0F120204},	                          //	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh
{0x0F12FF04},	                          //	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low
{0x0F1203FF},	                          //	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low
{0x0F120003},	                          //	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin
{0x0F120902},	                          //	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow
{0x0F122004},	                          //	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH
{0x0F120050},	                          //	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune
{0x0F121140},	                          //	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh
{0x0F12201C},	                          //	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh
{0x0F120620},	                          //	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed
{0x0F120306},	                          //	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh
{0x0F122003},	                          //	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH
{0x0F12FF01},	                          //	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit
{0x0F120404},	                          //	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2
{0x0F120300},	                          //	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower
{0x0F12145A},	                          //	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow
{0x0F121010},	                          //	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow
{0x0F12000B},	                          //	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow
{0x0F121000},	                          //	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower
{0x0F125A0F},	                          //	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit
{0x0F120503},	                          //	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope
{0x0F12FF00},	                          //	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR
{0x0F120000},	                          //	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres
{0x0F12FF00},	                          //	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR
{0x0F123C14},	                          //	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen
{0x0F12042C},	                          //	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh
{0x0F120101},	                          //	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative
{0x0F12FF00},	                          //	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle
{0x0F120904},	                          //	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh
{0x0F124008},	                          //	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh
{0x0F120540},	                          //	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange
{0x0F128006},	                          //	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad
{0x0F120020},	                          //	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal
{0x0F120000},	                          //	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh
{0x0F121800},	                          //	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat
{0x0F120000},	                          //	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit
{0x0F121E10},	                          //	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff
{0x0F12000B},	                          //	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2
{0x0F120005},	                          //	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2
{0x0F120405},	                          //	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY
{0x0F120206},	                          //	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm
{0x0F120304},	                          //	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm
{0x0F120409},	                          //	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift
{0x0F120305},	                          //	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y
{0x0F120406},	                          //	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y
{0x0F122804},	                          //	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV
{0x0F120228},	                          //	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y
{0x0F121402},	                          //	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV
{0x0F120618},	                          //	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL
{0x0F121E02},	                          //	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL
{0x0F128018},	                          //	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower
{0x0F120080},	                          //	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce
{0x0F120080},	                          //	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset
{0x0F120180},	                          //	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H
{0x0F120A0A},	                          //	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C
{0x0F120101},	                          //	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C
{0x0F120C0F},	                          //	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh
{0x0F126024},	                          //	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower
{0x0F120A0A},	                          //	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise
{0x0F12FFFF},	                          //	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp
{0x0F120808},	                          //	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope
{0x0F120A01},	                          //	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin
{0x0F120106},	                          //	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin
{0x0F120F01},	                          //	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin
{0x0F12250C},	                          //	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin
{0x0F120A60},	                          //	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin
{0x0F12FF0A},	                          //	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin
{0x0F1208FF},	                          //	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin
{0x0F120008},	                          //	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]
{0x0F120003},	                          //	AFITB_bnr_nClustLevel_C      [0]
{0x0F120000},	                          //	AFIT16_BRIGHTNESS                                      //AFIT 4
{0x0F120000},	                          //	AFIT16_CONTRAST
{0x0F120000},	                          //	AFIT16_SATURATION
{0x0F120000},	                          //	AFIT16_SHARP_BLUR
{0x0F120000},	                          //	AFIT16_GLAMOUR
{0x0F1200C0},	                          //	AFIT16_bnr_edge_high
{0x0F120064},	                          //	AFIT16_postdmsc_iLowBright
{0x0F120384},	                          //	AFIT16_postdmsc_iHighBright
{0x0F120032},	                          //	AFIT16_postdmsc_iLowSat
{0x0F1201F4},	                          //	AFIT16_postdmsc_iHighSat
{0x0F120070},	                          //	AFIT16_postdmsc_iTune
{0x0F120040},	                          //	AFIT16_yuvemix_mNegRanges_0
{0x0F1200A0},	                          //	AFIT16_yuvemix_mNegRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mNegRanges_2
{0x0F120010},	                          //	AFIT16_yuvemix_mPosRanges_0
{0x0F120060},	                          //	AFIT16_yuvemix_mPosRanges_1
{0x0F120100},	                          //	AFIT16_yuvemix_mPosRanges_2
{0x0F121430},	                          //	AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh
{0x0F120201},	                          //	AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh
{0x0F120204},	                          //	AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh
{0x0F12FF04},	                          //	AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low
{0x0F1203FF},	                          //	AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low
{0x0F120003},	                          //	AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin
{0x0F120602},	                          //	AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow
{0x0F121803},	                          //	AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH
{0x0F120040},	                          //	AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune
{0x0F120E20},	                          //	AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh
{0x0F122018},	                          //	AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh
{0x0F120620},	                          //	AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed
{0x0F120306},	                          //	AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh
{0x0F122003},	                          //	AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH
{0x0F12FF01},	                          //	AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit
{0x0F120404},	                          //	AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2
{0x0F120200},	                          //	AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower
{0x0F12145A},	                          //	AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow
{0x0F121010},	                          //	AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow
{0x0F12000B},	                          //	AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow
{0x0F121200},	                          //	AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower
{0x0F125A0F},	                          //	AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit
{0x0F120502},	                          //	AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope
{0x0F12FF00},	                          //	AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR
{0x0F120000},	                          //	AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres
{0x0F12FF00},	                          //	AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR
{0x0F124014},	                          //	AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen
{0x0F120430},	                          //	AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh
{0x0F120101},	                          //	AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative
{0x0F12FF00},	                          //	AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle
{0x0F120804},	                          //	AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh
{0x0F124008},	                          //	AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh
{0x0F120540},	                          //	AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange
{0x0F128006},	                          //	AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad
{0x0F120020},	                          //	AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal
{0x0F120000},	                          //	AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh
{0x0F121800},	                          //	AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat
{0x0F120000},	                          //	AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit
{0x0F121E10},	                          //	AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff
{0x0F12000B},	                          //	AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2
{0x0F120005},	                          //	AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0
{0x0F120607},	                          //	AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2
{0x0F120405},	                          //	AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY
{0x0F120205},	                          //	AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm
{0x0F120304},	                          //	AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm
{0x0F120409},	                          //	AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift
{0x0F120306},	                          //	AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y
{0x0F120407},	                          //	AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y
{0x0F122C04},	                          //	AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV
{0x0F12022C},	                          //	AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y
{0x0F121402},	                          //	AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV
{0x0F120618},	                          //	AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL
{0x0F121E02},	                          //	AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL
{0x0F128018},	                          //	AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower
{0x0F120080},	                          //	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce
{0x0F120080},	                          //	AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset
{0x0F120180},	                          //	AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H
{0x0F120A0A},	                          //	AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C
{0x0F120101},	                          //	AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C
{0x0F120C0F},	                          //	AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh
{0x0F126024},	                          //	AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower
{0x0F120808},	                          //	AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise
{0x0F12FFFF},	                          //	AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp
{0x0F120808},	                          //	AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope
{0x0F120A01},	                          //	AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin
{0x0F120106},	                          //	AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin
{0x0F120F01},	                          //	AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin
{0x0F12250C},	                          //	AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin
{0x0F120860},	                          //	AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin
{0x0F12FF08},	                          //	AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin
{0x0F1208FF},	                          //	AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin
{0x0F120008},	                          //	AFIT8_ee_iReduceEdgeSlope_Bin [7:0]
{0x0F120003},	                          //	AFITB_bnr_nClustLevel_C      [0]   bWideWide[1]
{0x0F1223CE},	                          //	"[0]CAFITB_bnr_bypass
                 //[1]CAFITB_bnr_edge_alg
                 //[2]CAFITB_bnr_bClustEnable_H
                 //[3]CAFITB_bnr_bClustEnable_C
                 //[4]CAFITB_bnr_bNewComplexLimit
                 //[5]CAFITB_bnr_bComplexThreshold */
                 //[6]CAFITB_bnr_bDoDisparity
                 //[7]CAFITB_bnr_bDoDenoise
                 //[8]CAFITB_bnr_bAddNoise
                 //[9]CAFITB_bnr_bDirectionalNR
                 //[10]CAFITB_bnr_bDirNRTune
                 //[11]CAFITB_bnr_bNSTDTune
                 //[12]CAFITB_bnr_bNSTDTuneUsingTH */
                 //[13]CAFITB_bnr_bSlopeEstimation
                 //[14]CAFITB_bnr_bSlopeThresh
                 //[15]CAFITB_bnr_bSlopeness       "
{0x0F12FDC8},	                          //	"[0]CAFITB_bnr_bSlopenessTune
                 //[1]CAFITB_bnr_bSlopenessTuneUsingTH
                 //[2]CAFITB_bnr_bSlopeBlur
                 //[3]CAFITB_bnr_bRadialThresholds
                 //[4]CAFITB_bnr_bRadialTune
                 //[5]CAFITB_ee_bypass
                 //[6]CAFITB_ee_bFineSharp
                 //[7]CAFITB_ee_bFSTh
                 //[8]CAFITB_ee_bRadialThresholds
                 //[9]CAFITB_ee_bXY_Coords
                 //[10]CAFITB_ee_bIPNR
                 //[11]CAFITB_ee_bIPNRNeighbor
                 //[12]CAFITB_ee_bSmoothEdge
                 //[13]CAFITB_ee_bWideWide
                 //[14]CAFITB_ee_bMSharpen
                 //[15]CAFITB_ee_bMShThresh               "
{0x0F12112E},	                          //	"[0]CAFITB_ee_bReduceNegMedSh
                 //[1]CAFITB_ee_bDenoisedMedSh
                 //[2]CAFITB_ee_bWSharpen
                 //[3]CAFITB_ee_bWShThresh
                 //[4]CAFITB_ee_bReduceNegWideSh
                 //[5]CAFITB_ee_bDenoisedWideSh
                 //[6]CAFITB_ee_bDoSharpClamping
                 //[7]CAFITB_ee_bReduceNegative
                 //[8]CAFITB_ee_bUseOneLum
                 //[9]CAFITB_ee_bSwapLumas
                 //[10]CAFITB_ee_bEmboss
                 //[11]CAFITB_ee_nSharpWidth
                 //[12]CAFITB_ee_bShDespeckle
                 //[13]CAFITB_ee_bReduceEdge
                 //[14]CAFITB_dmsc_bDesatDarkOnly
                 //[15]CAFITB_dmsc_bColorDenoise   "
{0x0F1283A5},	                          //	"[0]CAFITB_dmsc_bDoDesat
                 //[1]CAFITB_dmsc_bSparkleDesatMain
                 //[2]CAFITB_dmsc_bDecisionDesat
                 //[3]CAFITB_dmsc_bNotSharpVH
                 //[4]CAFITB_dmsc_bLeastEnh
                 //[5]CAFITB_dmsc_bEnhThresh
                 //[6]CAFITB_dmsc_bDemBlur
                 //[7]CAFITB_dmsc_bDecisionThresh
                 //[8]CAFITB_dmsc_bCentGrad
                 //[9]CAFITB_dmsc_bMonochrom
                 //[10]CAFITB_dmsc_bEdgeDesatTune
                 //[11]CAFITB_dmsc_bEdgeDesatMax
                 //[12]CAFITB_dmsc_bEdgeDesat
                 //[13]CAFITB_dmsc_bEdgeDesatLimit
                 //[14]CAFITB_postdmsc_bypass
                 //[15]CAFITB_postdmsc_bSkinColor   "
{0x0F12FE67},	                          //	"[0]CAFITB_postdmsc_bSat */
                 //[1]CAFITB_postdmsc_bBright
                 //[2]CAFITB_postdmsc_bColor
                 //[3]CAFITB_postdmsc_bTune
                 //[4]CAFITB_yuvemix_bypass
                 //[5]CAFITB_yuvemix_bNegSharpReduceCurve
                 //[6]CAFITB_yuvemix_bPosSharpReduceCurve
                 //[7]CAFITB_yuvemix_bTune
                 //[8]CAFITB_yuviirnr_bypass
                 //[9]CAFITB_yuviirnr_bYDenoise
                 //[10]CAFITB_yuviirnr_bUVDenoise
                 //[11]CAFITB_yuviirnr_bMaxThresh_Y
                 //[12]CAFITB_yuviirnr_bMaxThresh_UV
                 //[13]CAFITB_yuviirnr_bYNRStrength
                 //[14]CAFITB_yuviirnr_bUVNRStrength
                 //[1]5CAFITB_yuviirnr_bDistWeightY "
{0x0F120000},                      //	[0]CAFITB_yuviirnr_bWideY
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
{0x0F120100}, // This register should be positioned in fornt of D0001000.	// Check

{0x002A08C6},
{0x0F120001}, // ash_bUseOTPData								0x700008C6	// 0x0000  

{0x002A1432},
{0x0F120000},  // awbb_otp_disable							0x70001432	// 0x0001

{0x002A479E},
{0x0F120001}, //diff. 0000->0001??. 101013 //TNP_Regs_bUseGasAlphaOTP  // OTP Alpha is used, it should be enable.

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



{0x002A47EE},
{0x0F120000}, //diff. ////TNP_Regs_bUseOneCapture
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
{0x0F120000}, //AFC_Default60Hz //0001:60Hz, 0000h:50Hz
{0x002A0EF6},
{0x0F120002}, //AFC_D_ConvAccelerPower

{0x002A1A84},
{0x0F12001C}, //senHal_bExtraAddLine

{0x00287000},   //AF start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{0x002A01F8},  
{0x0F120000},  // REG_TC_IPRM_LedGpio							0x700001F8	// 0x0001
               //diff? ?? //??? driver  Ic ??? ???? ?? //0x002A16E4
               //diff? ?? //??? driver  Ic ??? ???? ??//0x0F120100  // afd_usFlags									0x700016E4	// 0x0000
{0x002A01FA},
{0x0F120003},  // REG_TC_IPRM_CM_Init_AfModeType				0x700001FA	// 0x0000 
{0x0F120000},  // REG_TC_IPRM_CM_Init_PwmConfig1				0x700001FC	// 0x0000 
{0x002A0200},
{0x0F120061},  //REG_TC_IPRM_CM_Init_GpioConfig1
{0x002A0208},
{0x0F122F0C},
{0x0F120190},
{0x002A028E},   //AF window ??. ???? ?????? ??size ? ??
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
{0x0F129002},   //9002 : 2nd search on, 2nd search ? lens ???? ??
{0x002A1616},
{0x0F120002},   //Peak Count [????]
{0x002A15A4},   
{0x0F120801},   //2nd search ?, 0601 :  1code ???? 6+1 ?? position ?? [????]
{0x002A1618},
{0x0F120000},

{0x002A1610},
{0x0F120003},
{0x002A1602},   //Peak Thershold
{0x0F1200E5},
{0x0F120098},

{0x002A1598},
{0x0F120000},   //Home position, AF initial ??? lens ????.
{0x0F12D000},   //AF fail ??? ??? ??. Macro AF : D0, normal AF : 00

{0x002A165E},
{0x0F12FF95},
{0x002A162E},   // AF LowConfThr Setting
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

{0x002A161A},   // AF Policy
{0x0F120000},   // 0000: Shutter_Priority_Current

{0x002A15AA},
{0x0F12003C},

{0x002A15AC},   //AF position table [????]
{0x0F120015},
{0x0F120032},
{0x0F120038},
{0x0F12003E},
{0x0F120044},
{0x0F12004A},
{0x0F120050},
{0x0F120056},
{0x0F12005C},
{0x0F120062},
{0x0F120068},
{0x0F12006E},
{0x0F120074},
{0x0F12007A},
{0x0F120080},
{0x0F120086},
{0x0F12008C},
{0x0F120092},
{0x0F120098},
{0x0F12009E},
{0x0F1200A4},
{0x0F1200AA},
{0x0F1200B0},


{0x002A16E6},   //AF movement control
{0x0F128000},
{0x0F120006},
{0x0F123FF0},
{0x0F1203E8},
{0x0F120000},
{0x0F120080},   //delay2, threshold ??? lens ??? ??. ?? ?? 9? ?????? delay 80h, 12.8ms delay ???.
{0x0F120009},   //threshold
{0x0F120020},   //delay1, threshold ??? lens ??? ??. ?? 9 ??? ??? ????(1st search position table 9?? ???) delay 20h, 3.2ms delay ???.
{0x0F120040},
{0x0F120080},
{0x0F1200C0},
{0x0F1200E0},

{0x002A0286},   //AF initialization
{0x0F120003},   //AF end

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

{0x0F123F00},
{0x0F124000},
{0x0F124000},
{0x0F124000},

{0x0F123F80},
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

{0x002A08E0},
{0x0F120001},

{0x002A1456}, //AE weights
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120302},
{0x0F120203},
{0x0F120101},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120202},
{0x0F120302},
{0x0F120203},
{0x0F120202},
{0x0F120201},
{0x0F120303},
{0x0F120303}, 
{0x0F120102},
{0x0F120101},
{0x0F120202}, 
{0x0F120202}, 
{0x0F120101},

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
{0x0F120005},

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
{0x0F120810}, //REG_0TC_CCFG_usJpegPacketSize
{0x0F120900}, //0600 //REG_0TC_CCFG_usJpegTotalPackets
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
{0x0F120390}, //03B8
{0x0F1203B4}, //03CE
{0x0F120360}, //0350
{0x0F120398}, //03C4
{0x0F120328}, //02F2
{0x0F120380}, //0394
{0x0F1202D6}, //02C0
{0x0F120352}, //0364
{0x0F12029E}, //029E
{0x0F12032A}, //0334
{0x0F12027C}, //027C
{0x0F12030E}, //0312
{0x0F12025E}, //
{0x0F1202F2}, //
{0x0F120246}, //
{0x0F1202D0}, //
{0x0F120230}, //
{0x0F1202B0}, //
{0x0F120218}, //
{0x0F12029E}, //
{0x0F120208}, //
{0x0F120290}, //
{0x0F1201F8}, //
{0x0F120284}, //
{0x0F1201E8}, //
{0x0F120276}, //
{0x0F1201DA}, //
{0x0F12026A}, //
{0x0F1201CE}, //
{0x0F12025E}, //
{0x0F1201EC}, //
{0x0F12022E}, //
{0x0F120000}, //
{0x0F120000}, //
{0x0F120000}, //
{0x0F120000}, //
{0x0F120000}, //
{0x0F120000}, //
{0x0F120000}, //
{0x0F120000}, //

{0x0F120005},
{0x002A1034},
{0x0F120010},
{0x002A1038},
{0x0F120126},

{0x002A103C},
{0x0F120250},  //024A //026C
{0x0F12027E},  //0278 //029A
{0x0F120240},  //023A //025C
{0x0F12029A},  //0294 //02B6
{0x0F120232},  //022C //024E
{0x0F1202A4},  //029E //02C0
{0x0F120226},  //0220 //0240
{0x0F1202A2},  //029C //02BE
{0x0F12021E},  //0218 //023A
{0x0F120298},  //0292 //02B4
{0x0F12021A},  //0214 //023A
{0x0F120290},  //028A //02AA
{0x0F120218},  //0212 //0240
{0x0F120282},  //027C //029E
{0x0F12021C},  //0216 //025C
{0x0F12027A},  //0274 //0294
{0x0F12022E},  //0228 //0000
{0x0F12025C},  //0256 //0000
{0x0F120000},  //0000 //0000
{0x0F120000},  //0000 //0000
{0x0F120000},  //0000 //0000
{0x0F120000},  //0000 //0000
{0x0F120000},  //0000 //0000
{0x0F120000},  //0000 //0000

{0x0F120004},
{0x002A1070},
{0x0F120009}, // awbb_OutdoorGrZones_ZInfo_m_GridSz			0x70001070	// 0x000A
{0x002A1074},
{0x0F12020A}, // awbb_OutdoorGrZones_m_Boffs					0x70001074	// 0x0244


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
{0x0F12FFF8},  // awbb_GridCorr_R_0__2_						0x7000136C	// 0x0000         
{0x0F12FFF8},  // awbb_GridCorr_R_0__3_						0x7000136E	// 0x0000         
{0x0F12FFE0},  // awbb_GridCorr_R_0__4_						0x70001370	// 0x0000         
{0x0F120018},  // awbb_GridCorr_R_0__5_						0x70001372	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_1__0_						0x70001374	// 0xFFFD         
{0x0F120000},  // awbb_GridCorr_R_1__1_						0x70001376	// 0xFFFD         
{0x0F12FFF8},  // awbb_GridCorr_R_1__2_						0x70001378	// 0x0000         
{0x0F12FFF8},  // awbb_GridCorr_R_1__3_						0x7000137A	// 0x0000         
{0x0F12FFE0},  // awbb_GridCorr_R_1__4_						0x7000137C	// 0x0000         
{0x0F120018},  // awbb_GridCorr_R_1__5_						0x7000137E	// 0x0000         
{0x0F120000},  // awbb_GridCorr_R_2__0_						0x70001380	// 0xFFFC         
{0x0F120000},  // awbb_GridCorr_R_2__1_						0x70001382	// 0xFFFC         
{0x0F12FFF8},  // awbb_GridCorr_R_2__2_						0x70001384	// 0x0000         
{0x0F12FFF8},  // awbb_GridCorr_R_2__3_						0x70001386	// 0x0000         
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
{0x0F12FFEC},  // awbb_GridCorr_B_Out_0__0_					0x700013D4	// 0x000C           
{0x0F12FFEC},  // awbb_GridCorr_B_Out_0__1_					0x700013D6	// 0x0006       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_0__2_					0x700013D8	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__3_					0x700013DA	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__4_					0x700013DC	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_0__5_					0x700013DE	// 0x0000       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_1__0_					0x700013E0	// 0x000C       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_1__1_					0x700013E2	// 0x0006       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_1__2_					0x700013E4	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__3_					0x700013E6	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__4_					0x700013E8	// 0x0000       
{0x0F120000},  // awbb_GridCorr_B_Out_1__5_					0x700013EA	// 0x0000       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_2__0_					0x700013EC	// 0x000C       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_2__1_					0x700013EE	// 0x0006       
{0x0F12FFEC},  // awbb_GridCorr_B_Out_2__2_					0x700013F0	// 0x0000       
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
{0x0F120000},  // SARR_usGammaLutRGBIndoor_0__0_				0x70000724	// 0x0000
{0x0F12000A},  // SARR_usGammaLutRGBIndoor_0__1_				0x70000726	// 0x0001
{0x0F120016},  // SARR_usGammaLutRGBIndoor_0__2_				0x70000728	// 0x0007
{0x0F120030},  // SARR_usGammaLutRGBIndoor_0__3_				0x7000072A	// 0x002D
{0x0F120066},  // SARR_usGammaLutRGBIndoor_0__4_				0x7000072C	// 0x0075
{0x0F1200D5},  // SARR_usGammaLutRGBIndoor_0__5_				0x7000072E	// 0x00E9
{0x0F120138},  // SARR_usGammaLutRGBIndoor_0__6_				0x70000730	// 0x0143
{0x0F120163},  // SARR_usGammaLutRGBIndoor_0__7_				0x70000732	// 0x016C
{0x0F120189},  // SARR_usGammaLutRGBIndoor_0__8_				0x70000734	// 0x0190
{0x0F1201C6},  // SARR_usGammaLutRGBIndoor_0__9_				0x70000736	// 0x01CC
{0x0F1201F8},  // SARR_usGammaLutRGBIndoor_0__10_				0x70000738	// 0x01FF
{0x0F120222},  // SARR_usGammaLutRGBIndoor_0__11_				0x7000073A	// 0x022A
{0x0F120247},  // SARR_usGammaLutRGBIndoor_0__12_				0x7000073C	// 0x0252
{0x0F120282},  // SARR_usGammaLutRGBIndoor_0__13_				0x7000073E	// 0x0296
{0x0F1202B5},  // SARR_usGammaLutRGBIndoor_0__14_				0x70000740	// 0x02D6
{0x0F12030F},  // SARR_usGammaLutRGBIndoor_0__15_				0x70000742	// 0x033C
{0x0F12035F},  // SARR_usGammaLutRGBIndoor_0__16_				0x70000744	// 0x038D
{0x0F1203A2},  // SARR_usGammaLutRGBIndoor_0__17_				0x70000746	// 0x03D0
{0x0F1203D8},  // SARR_usGammaLutRGBIndoor_0__18_				0x70000748	// 0x03F7
{0x0F1203FF},  // SARR_usGammaLutRGBIndoor_0__19_				0x7000074A	// 0x03FF
{0x0F120000},  // SARR_usGammaLutRGBIndoor_1__0_				0x7000074C	// 0x0000
{0x0F12000A},  // SARR_usGammaLutRGBIndoor_1__1_				0x7000074E	// 0x0001
{0x0F120016},  // SARR_usGammaLutRGBIndoor_1__2_				0x70000750	// 0x0007
{0x0F120030},  // SARR_usGammaLutRGBIndoor_1__3_				0x70000752	// 0x002D
{0x0F120066},  // SARR_usGammaLutRGBIndoor_1__4_				0x70000754	// 0x0075
{0x0F1200D5},  // SARR_usGammaLutRGBIndoor_1__5_				0x70000756	// 0x00E9
{0x0F120138},  // SARR_usGammaLutRGBIndoor_1__6_				0x70000758	// 0x0143
{0x0F120163},  // SARR_usGammaLutRGBIndoor_1__7_				0x7000075A	// 0x016C
{0x0F120189},  // SARR_usGammaLutRGBIndoor_1__8_				0x7000075C	// 0x0190
{0x0F1201C6},  // SARR_usGammaLutRGBIndoor_1__9_				0x7000075E	// 0x01CC
{0x0F1201F8},  // SARR_usGammaLutRGBIndoor_1__10_				0x70000760	// 0x01FF
{0x0F120222},  // SARR_usGammaLutRGBIndoor_1__11_				0x70000762	// 0x022A
{0x0F120247},  // SARR_usGammaLutRGBIndoor_1__12_				0x70000764	// 0x0252
{0x0F120282},  // SARR_usGammaLutRGBIndoor_1__13_				0x70000766	// 0x0296
{0x0F1202B5},  // SARR_usGammaLutRGBIndoor_1__14_				0x70000768	// 0x02D6
{0x0F12030F},  // SARR_usGammaLutRGBIndoor_1__15_				0x7000076A	// 0x033C
{0x0F12035F},  // SARR_usGammaLutRGBIndoor_1__16_				0x7000076C	// 0x038D
{0x0F1203A2},  // SARR_usGammaLutRGBIndoor_1__17_				0x7000076E	// 0x03D0
{0x0F1203D8},  // SARR_usGammaLutRGBIndoor_1__18_				0x70000770	// 0x03F7
{0x0F1203FF},  // SARR_usGammaLutRGBIndoor_1__19_				0x70000772	// 0x03FF
{0x0F120000},  // SARR_usGammaLutRGBIndoor_2__0_				0x70000774	// 0x0000
{0x0F12000A},  // SARR_usGammaLutRGBIndoor_2__1_				0x70000776	// 0x0001
{0x0F120016},  // SARR_usGammaLutRGBIndoor_2__2_				0x70000778	// 0x0007
{0x0F120030},  // SARR_usGammaLutRGBIndoor_2__3_				0x7000077A	// 0x002D
{0x0F120066},  // SARR_usGammaLutRGBIndoor_2__4_				0x7000077C	// 0x0075
{0x0F1200D5},  // SARR_usGammaLutRGBIndoor_2__5_				0x7000077E	// 0x00E9
{0x0F120138},  // SARR_usGammaLutRGBIndoor_2__6_				0x70000780	// 0x0143
{0x0F120163},  // SARR_usGammaLutRGBIndoor_2__7_				0x70000782	// 0x016C
{0x0F120189},  // SARR_usGammaLutRGBIndoor_2__8_				0x70000784	// 0x0190
{0x0F1201C6},  // SARR_usGammaLutRGBIndoor_2__9_				0x70000786	// 0x01CC
{0x0F1201F8},  // SARR_usGammaLutRGBIndoor_2__10_				0x70000788	// 0x01FF
{0x0F120222},  // SARR_usGammaLutRGBIndoor_2__11_				0x7000078A	// 0x022A
{0x0F120247},  // SARR_usGammaLutRGBIndoor_2__12_				0x7000078C	// 0x0252
{0x0F120282},  // SARR_usGammaLutRGBIndoor_2__13_				0x7000078E	// 0x0296
{0x0F1202B5},  // SARR_usGammaLutRGBIndoor_2__14_				0x70000790	// 0x02D6
{0x0F12030F},  // SARR_usGammaLutRGBIndoor_2__15_				0x70000792	// 0x033C
{0x0F12035F},  // SARR_usGammaLutRGBIndoor_2__16_				0x70000794	// 0x038D
{0x0F1203A2},  // SARR_usGammaLutRGBIndoor_2__17_				0x70000796	// 0x03D0
{0x0F1203D8},  // SARR_usGammaLutRGBIndoor_2__18_				0x70000798	// 0x03F7
{0x0F1203FF},  // SARR_usGammaLutRGBIndoor_2__19_				0x7000079A	// 0x03FF
             // SARR_usGammaLutRGBOutdoor					0x7000079C	// 0x0000    
{0x0F120000},  // SARR_usGammaLutRGBOutdoor_0__0_				0x7000079C	// 0x0000
{0x0F12000B},  // SARR_usGammaLutRGBOutdoor_0__1_				0x7000079E	// 0x0001
{0x0F120019},  // SARR_usGammaLutRGBOutdoor_0__2_				0x700007A0	// 0x0007
{0x0F120036},  // SARR_usGammaLutRGBOutdoor_0__3_				0x700007A2	// 0x002D
{0x0F12006F},  // SARR_usGammaLutRGBOutdoor_0__4_				0x700007A4	// 0x0075
{0x0F1200D8},  // SARR_usGammaLutRGBOutdoor_0__5_				0x700007A6	// 0x00E9
{0x0F120135},  // SARR_usGammaLutRGBOutdoor_0__6_				0x700007A8	// 0x0143
{0x0F12015F},  // SARR_usGammaLutRGBOutdoor_0__7_				0x700007AA	// 0x016C
{0x0F120185},  // SARR_usGammaLutRGBOutdoor_0__8_				0x700007AC	// 0x0190
{0x0F1201C1},  // SARR_usGammaLutRGBOutdoor_0__9_				0x700007AE	// 0x01CC
{0x0F1201F3},  // SARR_usGammaLutRGBOutdoor_0__10_			0x700007B0	// 0x01FF
{0x0F120220},  // SARR_usGammaLutRGBOutdoor_0__11_			0x700007B2	// 0x022A
{0x0F12024A},  // SARR_usGammaLutRGBOutdoor_0__12_			0x700007B4	// 0x0252
{0x0F120291},  // SARR_usGammaLutRGBOutdoor_0__13_			0x700007B6	// 0x0296
{0x0F1202D0},  // SARR_usGammaLutRGBOutdoor_0__14_			0x700007B8	// 0x02D6
{0x0F12032A},  // SARR_usGammaLutRGBOutdoor_0__15_			0x700007BA	// 0x033C
{0x0F12036A},  // SARR_usGammaLutRGBOutdoor_0__16_			0x700007BC	// 0x038D
{0x0F12039F},  // SARR_usGammaLutRGBOutdoor_0__17_			0x700007BE	// 0x03D0
{0x0F1203CC},  // SARR_usGammaLutRGBOutdoor_0__18_			0x700007C0	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBOutdoor_0__19_			0x700007C2	// 0x03FF
{0x0F120000},  // SARR_usGammaLutRGBOutdoor_1__0_				0x700007C4	// 0x0000
{0x0F12000B},  // SARR_usGammaLutRGBOutdoor_1__1_				0x700007C6	// 0x0001
{0x0F120019},  // SARR_usGammaLutRGBOutdoor_1__2_				0x700007C8	// 0x0007
{0x0F120036},  // SARR_usGammaLutRGBOutdoor_1__3_				0x700007CA	// 0x002D
{0x0F12006F},  // SARR_usGammaLutRGBOutdoor_1__4_				0x700007CC	// 0x0075
{0x0F1200D8},  // SARR_usGammaLutRGBOutdoor_1__5_				0x700007CE	// 0x00E9
{0x0F120135},  // SARR_usGammaLutRGBOutdoor_1__6_				0x700007D0	// 0x0143
{0x0F12015F},  // SARR_usGammaLutRGBOutdoor_1__7_				0x700007D2	// 0x016C
{0x0F120185},  // SARR_usGammaLutRGBOutdoor_1__8_				0x700007D4	// 0x0190
{0x0F1201C1},  // SARR_usGammaLutRGBOutdoor_1__9_				0x700007D6	// 0x01CC
{0x0F1201F3},  // SARR_usGammaLutRGBOutdoor_1__10_			0x700007D8	// 0x01FF
{0x0F120220},  // SARR_usGammaLutRGBOutdoor_1__11_			0x700007DA	// 0x022A
{0x0F12024A},  // SARR_usGammaLutRGBOutdoor_1__12_			0x700007DC	// 0x0252
{0x0F120291},  // SARR_usGammaLutRGBOutdoor_1__13_			0x700007DE	// 0x0296
{0x0F1202D0},  // SARR_usGammaLutRGBOutdoor_1__14_			0x700007E0	// 0x02D6
{0x0F12032A},  // SARR_usGammaLutRGBOutdoor_1__15_			0x700007E2	// 0x033C
{0x0F12036A},  // SARR_usGammaLutRGBOutdoor_1__16_			0x700007E4	// 0x038D
{0x0F12039F},  // SARR_usGammaLutRGBOutdoor_1__17_			0x700007E6	// 0x03D0
{0x0F1203CC},  // SARR_usGammaLutRGBOutdoor_1__18_			0x700007E8	// 0x03F7
{0x0F1203F9},  // SARR_usGammaLutRGBOutdoor_1__19_			0x700007EA	// 0x03FF
{0x0F120000},  // SARR_usGammaLutRGBOutdoor_2__0_				0x700007EC	// 0x0000
{0x0F12000B},  // SARR_usGammaLutRGBOutdoor_2__1_				0x700007EE	// 0x0001
{0x0F120019},  // SARR_usGammaLutRGBOutdoor_2__2_				0x700007F0	// 0x0007
{0x0F120036},  // SARR_usGammaLutRGBOutdoor_2__3_				0x700007F2	// 0x002D
{0x0F12006F},  // SARR_usGammaLutRGBOutdoor_2__4_				0x700007F4	// 0x0075
{0x0F1200D8},  // SARR_usGammaLutRGBOutdoor_2__5_				0x700007F6	// 0x00E9
{0x0F120135},  // SARR_usGammaLutRGBOutdoor_2__6_				0x700007F8	// 0x0143
{0x0F12015F},  // SARR_usGammaLutRGBOutdoor_2__7_				0x700007FA	// 0x016C
{0x0F120185},  // SARR_usGammaLutRGBOutdoor_2__8_				0x700007FC	// 0x0190
{0x0F1201C1},  // SARR_usGammaLutRGBOutdoor_2__9_				0x700007FE	// 0x01CC
{0x0F1201F3},  // SARR_usGammaLutRGBOutdoor_2__10_			0x70000800	// 0x01FF
{0x0F120220},  // SARR_usGammaLutRGBOutdoor_2__11_			0x70000802	// 0x022A
{0x0F12024A},  // SARR_usGammaLutRGBOutdoor_2__12_			0x70000804	// 0x0252
{0x0F120291},  // SARR_usGammaLutRGBOutdoor_2__13_			0x70000806	// 0x0296
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

{0x0F120209}, //01D8 
{0x0F12FFA9}, //FFCA 
{0x0F12FFF8}, //FFF2 
{0x0F12FEF1}, //FEF1 
{0x0F12014E}, //014E 
{0x0F12FF18}, //FF18 
{0x0F12FFE6}, //FFC8 
{0x0F12FFDD}, //FFC1 
{0x0F1201B2}, //013A 
{0x0F1200F2}, //0112 
{0x0F1200CA}, //00EE 
{0x0F12FF48}, //FF99 
{0x0F120151}, //009E 
{0x0F12FF50}, //FF5F 
{0x0F120147}, //01A8 
{0x0F12FF75}, //FF75 
{0x0F120187}, //0187 
{0x0F1201BF}, //01BF 
        //   
{0x0F120209}, //01D8
{0x0F12FFA9}, //FFCA
{0x0F12FFF8}, //FFF2
{0x0F12FEF1}, //FEF1
{0x0F12014E}, //014E
{0x0F12FF18}, //FF18
{0x0F12FFE6}, //FFC8
{0x0F12FFDD}, //FFC1
{0x0F1201B2}, //013A
{0x0F1200F2}, //0112
{0x0F1200CA}, //00EE
{0x0F12FF48}, //FF99
{0x0F120151}, //009E
{0x0F12FF50}, //FF5F
{0x0F120147}, //01A8
{0x0F12FF75}, //FF75
{0x0F120187}, //0187
{0x0F1201BF}, //01BF
        //   
{0x0F120209}, //01D8
{0x0F12FFA9}, //FFCA
{0x0F12FFF8}, //FFF2
{0x0F12FEF1}, //FEF1
{0x0F12014E}, //014E
{0x0F12FF18}, //FF18
{0x0F12FFE6}, //FFC8
{0x0F12FFDD}, //FFC1
{0x0F1201B2}, //013A
{0x0F1200F2}, //0112
{0x0F1200CA}, //00EE
{0x0F12FF48}, //FF99
{0x0F120151}, //009E
{0x0F12FF50}, //FF5F
{0x0F120147}, //01A8
{0x0F12FF75}, //FF75
{0x0F120187}, //0187
{0x0F1201BF}, //01BF

{0x002A0890},
{0x0F1248D8},
{0x0F127000},

{0x002A48D8}, //Outdoor ccm
{0x0F1201E6}, //01AA 
{0x0F12FFB9}, //FFC4 
{0x0F12FFC5}, //FFC5 
{0x0F12FE90}, //FF6C 
{0x0F12013F}, //01E8 
{0x0F12FF1B}, //FF79
{0x0F12FFA4}, //FFDE
{0x0F120012}, //0019
{0x0F120231}, //023B
{0x0F1200D5}, //00A7 
{0x0F12010E}, //00F5 
{0x0F12FF36}, //FF5E 
{0x0F1201CE}, //022D
{0x0F12FF83}, //FF9B
{0x0F120195}, //01E1
{0x0F12FEF3}, //FF34
{0x0F120126}, //014B
{0x0F120162}, //01B6

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
{0x0F120080},   //	AfitBaseVals_2__72_		//	AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce               					0x70000B54	// 0x0080
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

{0x002A1C22}, //DRx_uDRxWeight //for AutoCont. function
{0x0F120100}, 
{0x0F120100}, 
{0x0F120100}, 
{0x0F120100}, 
                
{0xFCFCD000},          
{0x00287000},
{0x002A01A2},
{0x0F120A0A},

//Flash init start
{0x00287000},
{0x002A17A8},
{0x0F120001},

{0x00287000},
{0x002A17DC},
{0x0F120001},

{0x00287000},
{0x002A17AE},
{0x0F120280},

{0x00287000},
{0x002A17B0},
{0x0F120210},

{0x00287000},
{0x002A17E2},
{0x0F120000},

{0x00287000},
{0x002A17E4},
{0x0F120001},

{0x00287000},
{0x002A17E6},
{0x0F120500},

{0x00287000},
{0x002A17F4},
{0x0F120030},

{0x00287000},
{0x002A17F6},
{0x0F120030},
//Flash init end

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


};

s5k4ecgx_short_t s5k4ecgx_FPS_5[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_7[] = {

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

};

s5k4ecgx_short_t s5k4ecgx_FPS_60[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_120[] = {

};

s5k4ecgx_short_t s5k4ecgx_Effect_Normal[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0238},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Solarization[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0238},
{0x0F120002}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Negative[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0238},
{0x0F120003}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Sepia[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0238},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Black_White[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0238},
{0x0F120001}
};


s5k4ecgx_short_t s5k4ecgx_WB_Auto[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E0},
{0x0f12077F}
};

s5k4ecgx_short_t s5k4ecgx_WB_Sunny[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E0},
{0x0f120777},
{0x002a04B4},
{0x0f1205E0},
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120530},
{0x0f120001},
{0x002A04C0},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_WB_Cloudy[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E0},
{0x0f120777},
{0x002a04B4},
{0x0f120690}, //710
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120420}, //diff? 485->420?? ??(101012).
{0x0f120001},
{0x002A04C0},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_WB_Tungsten[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E0},
{0x0f120777},
{0x002a04B4},
{0x0f120390}, //diff? 3D0->390?? ??(101012)
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120920},
{0x0f120001},
{0x002A04C0},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_WB_Fluorescent[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E0},
{0x0f120777},
{0x002a04B4},
{0x0f120505},
{0x0f120001},
{0x0f120470}, //400
{0x0f120001},
{0x0f120875},
{0x0f120001},
{0x002A04C0},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_WDR_on[] = {
{0x00287000},
{0x002A1B4A},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_WDR_off[] = {
{0x00287000},
{0x002A1B4A},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_ISO_Auto[] = {

{0xFCFCD000},

{0x00287000},
{0x002A4780},
{0x0F120000},


{0x002A0EF0},
{0x0F120000},
{0x002A04E0},
{0x0F12077F},
{0x002A04CA},
{0x0F120000},

{0x002A04CA},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x002A06B6},
{0x0F120200}
};

s5k4ecgx_short_t s5k4ecgx_ISO_50[] = {
{0xFCFCD000},

{0x00287000},
{0x002A04E0},
{0x0F12065F},
{0x002A04D0},
{0x0F120000},
{0x0F120001},

{0x002A04CA},
{0x0F120001},
{0x0F1201A0},
{0x0F120001},
{0x002A06B6},
{0x0F120100},

{0x002A4780},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_ISO_100[] = {

{0xFCFCD000},

{0x00287000},
{0x002A04E0},
{0x0F12065F},
{0x002A04D0},
{0x0F120000},
{0x0F120001},

{0x002A04CA},
{0x0F120001},
{0x0F1201A0},
{0x0F120001},
{0x002A06B6},
{0x0F120100},

{0x002A4780},
{0x0F120001}

};

s5k4ecgx_short_t s5k4ecgx_ISO_200[] = {
{0xFCFCD000},

{0x00287000},
{0x002A04E0},
{0x0F12065F},
{0x002A04D0},
{0x0F120000},
{0x0F120001},

{0x002A04CA},
{0x0F120001},
{0x0F120340},
{0x0F120001},
{0x002A06B6},
{0x0F120100},

{0x002A4780},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_ISO_400[] = {
 
{0xFCFCD000},

{0x00287000},
{0x002A04E0},
{0x0F12065F},
{0x002A04D0},
{0x0F120000},
{0x0F120001},

{0x002A04CA},
{0x0F120001},
{0x0F120680},
{0x0F120001},
{0x002A06B6},
{0x0F120100},

{0x002A4780},
{0x0F120001}

};

s5k4ecgx_short_t s5k4ecgx_Metering_Matrix[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1456},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101}
};

s5k4ecgx_short_t s5k4ecgx_Metering_Center[] = {
{0xFCFCD000},
{0x00287000},

{0x002A1456}, //AE weights
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120302},
{0x0F120203},
{0x0F120101},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120202},
{0x0F120302},
{0x0F120203},
{0x0F120202},
{0x0F120201},
{0x0F120303},
{0x0F120303}, 
{0x0F120102},
{0x0F120101},
{0x0F120202}, 
{0x0F120202}, 
{0x0F120101}
};

s5k4ecgx_short_t s5k4ecgx_Metering_Spot[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1456},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120101},
{0x0f120101},
{0x0f120000},
{0x0f120000},
{0x0f12010f},
{0x0f120f01},
{0x0f120000},
{0x0f120000},
{0x0f12010f},
{0x0f120f01},
{0x0f120000},
{0x0f120000},
{0x0f120101},
{0x0f120101},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000}
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F12FF30}  //?? 101012
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F12FFA0}
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F12FFC0}
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F12FFE0}
};

s5k4ecgx_short_t s5k4ecgx_EV_Default[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F120020}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F120038} //diff? 40->38?? ??(101012).
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_3[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F120060}
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_4[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022C},
{0x0F12007F}
};


s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_4[] = { // Setting Unavailable
{0xFCFCD000}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_3[] = { // Setting Unavailable
{0xFCFCD000}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F12FFC0}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F12FFE0}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Default[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F120020}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_2[] = {
{0xFCFCD000},
{0x00287000},
{0x002A022E},
{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_3[] = { // Setting Unavailable
{0xFCFCD000}
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_4[] = { // Setting Unavailable
{0xFCFCD000}
};

s5k4ecgx_short_t s5k4ecgx_Auto_Contrast_ON[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1B4A},
{0x0F120000}  //DRx_bDRxBypass
};            
              
s5k4ecgx_short_t s5k4ecgx_Auto_Contrast_OFF[] = {
{0xFCFCD000}, 
{0x00287000}, 
{0x002A1B4A},
{0x0F120001}  //DRx_bDRxBypass
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_3[] = { // Setting Unavailable
{0xFCFCD000}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_2[] = {
{0x00287000},
{0x002A09F4},
{0x0F122010},
{0x002A0AAA},
{0x0F122010},
{0x002A0B60},
{0x0F122010},
{0x002A0C16},
{0x0F122010},
{0x002A0CCC},
{0x0F122010}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_1[] = {
{0x00287000},
{0x002A09F4},
{0x0F124020},
{0x002A0AAA},
{0x0F124020},
{0x002A0B60},
{0x0F124020},
{0x002A0C16},
{0x0F124020},
{0x002A0CCC},
{0x0F124020}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Default[] = {
{0x00287000},
{0x002A09F4},
{0x0F126024},
{0x002A0AAA},
{0x0F126024},
{0x002A0B60},
{0x0F126024},
{0x002A0C16},
{0x0F126024},
{0x002A0CCC},
{0x0F126024}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_1[] = {
{0x00287000},
{0x002A09F4},
{0x0F128040},
{0x002A0AAA},
{0x0F128040},
{0x002A0B60},
{0x0F128040},
{0x002A0C16},
{0x0F128040},
{0x002A0CCC},
{0x0F128040}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_2[] = {
{0x00287000},
{0x002A09F4},
{0x0F12A060},
{0x002A0AAA},
{0x0F12A060},
{0x002A0B60},
{0x0F12A060},
{0x002A0C16},
{0x0F12A060},
{0x002A0CCC},
{0x0F12A060}
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_3[] = { // Setting Unavailable
{0xFCFCD000}
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Minus_2[] = {
{0x00287000},
{0x002A0230},
{0x0F12FF81}
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Minus_1[] = {
{0x00287000},
{0x002A0230},
{0x0F12FFC0}
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Default[] = {
{0x00287000},
{0x002A0230},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Plus_1[] = {
{0x00287000},
{0x002A0230},
{0x0F120040}
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Plus_2[] = {
{0x00287000},
{0x002A0230},
{0x0F12007F}
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_High[] = {
{0x00287000},
{0x002A0472},
{0x0F12005F},
{0x0F12005F}
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_Normal[] = {
{0x00287000},
{0x002A0472},
{0x0F120050},
{0x0F120050}
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_Low[] = {
{0x00287000},
{0x002A0472},
{0x0F12004B},
{0x0F12004B}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Default[] = {
{0x00287000},

{0x002A1456}, //AE weights Center
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120000},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120302},
{0x0F120203},
{0x0F120101},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120202},
{0x0F120302},
{0x0F120203},
{0x0F120202},
{0x0F120201},
{0x0F120303},
{0x0F120303}, 
{0x0F120102},
{0x0F120101},
{0x0F120202}, 
{0x0F120202}, 
{0x0F120101},

{0x002A4780},
{0x0F120000},

{0x002A06AC}, //Max LEI
{0x0F12452C}, //diff. 101012
{0x0F120005}, //diff. 101012

{0x002A0EF0}, //AFC_Default60Hz
{0x0F120000}, //diff? ??(101012).     
{0x002A0EF6}, //diff? ??(101012)
{0x0F120001}, 
{0x002A04E0},
{0x0F12077F},

{0x002A04CA},
{0x0F120000},
{0x0F120000},
{0x0F120001},
{0x002A06B6},
{0x0F120200},

{0x002a2B7E},
{0x0f120001},


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

{0x00287000}, //Effect Normal
{0x002A0238},
{0x0F120000},

{0x002A022E},  //s5k4ecgx_Contrast_Default
{0x0F120000},

{0x002A09F4}, //s5k4ecgx_Sharpness_Default
{0x0F126024},
{0x002A0AAA},
{0x0F126024},
{0x002A0B60},
{0x0F126024},
{0x002A0C16},
{0x0F126024},
{0x002A0CCC},
{0x0F126024},

{0x002A0230}, //s5k4ecgx_Saturation_Default
{0x0F120000},

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
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Portrait[] = {
{0x00287000},
{0x002A09F4},
{0x0F124020},
{0x002A0AAA},
{0x0F124020},
{0x002A0B60},
{0x0F124020},
{0x002A0C16},
{0x0F124020},
{0x002A0CCC},
{0x0F124020}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Nightshot[] = {
{0x00287000}, //?? ??.
{0x002A06AC},
{0x0F12FFFF},
{0x0F1200FF},

{0x002A05FC},
{0x0F120000},
{0x0F120000},

{0x002A0580},
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



{0x002A03AE},
{0x0F121388},
{0x0F121388},
{0x002A02BC},	
{0x0F1209C4},
{0x0F12014D},
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

s5k4ecgx_short_t s5k4ecgx_Scene_Backlight[] = {
{0xFCFCD000},
{0x00287000},

{0x002A1456},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120101},
{0x0f120101},
{0x0f120000},
{0x0f120000},
{0x0f12010f},
{0x0f120f01},
{0x0f120000},
{0x0f120000},
{0x0f12010f},
{0x0f120f01},
{0x0f120000},
{0x0f120000},
{0x0f120101},
{0x0f120101},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000},
{0x0f120000}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Landscape[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1456},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x0f120101},
{0x002A09F4},
{0x0F128040},
{0x002A0AAA},
{0x0F128040},
{0x002A0B60},
{0x0F128040},
{0x002A0C16},
{0x0F128040},
{0x002A0CCC},
{0x0F128040},
{0x002A0230},
{0x0F120040}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Sports[] = {
{0x00287000},
{0x002A05FC},
{0x0F120000},
{0x0F120000},

{0x002A0580},
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
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Party_Indoor[] = {

{0xFCFCD000},

{0x00287000},
{0x002A04E0},
{0x0F12065F},
{0x002A04D0},
{0x0F120000},
{0x0F120001},

{0x002A04CA},
{0x0F120001},
{0x0F120340},
{0x0F120001},
{0x002A06B6},
{0x0F120100},


{0x002A4780},
{0x0F120001},

{0x002A0230},
{0x0F120031}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Beach_Snow[] = {

{0xFCFCD000},

{0x00287000},
{0x002A04E0},
{0x0F12065F},
{0x002A04D0},
{0x0F120000},
{0x0F120001},
{0x002A04CA},
{0x0F120001},
{0x0F1200D0},
{0x0F120001},
{0x002A06B6},
{0x0F120100},


{0x002A4780},
{0x0F120001},

{0x002A0230},
{0x0F120031}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Sunset[] = {
{0xFCFCD000},
{0x00287000},
{0x002a2B7E},
{0x0f120000},

{0x002a04B4},
{0x0f1205E0},
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120520},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Duskdawn[] = {
{0xFCFCD000},
{0x00287000},
{0x002a2B7E},
{0x0f120000},

{0x002a04B4},
{0x0f120575},
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120835},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Fall_Color[] = {
{0x00287000},
{0x002A0230},
{0x0F12007F}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Fireworks[] = {
{0x00287000},
{0x002A062C},
{0x0F120001},
{0x0F120000},
{0x002A0630},
{0x0F121478},
{0x0F120000},
{0x002A0634},
{0x0F121A0A},
{0x0F120000},
{0x002A0638},
{0x0F126810},
{0x0F120000},
{0x002A063C},
{0x0F126810},
{0x0F120000},
{0x002A0640},
{0x0F12D020},
{0x0F120000},
{0x002A0644},
{0x0F120428},
{0x0F120001},
{0x002A0648},
{0x0F121A80},
{0x0F120006},
{0x002A064C},
{0x0F121A80},
{0x0F120006},
{0x002A0650},
{0x0F121A80},
{0x0F120006},

{0x002A03AE},
{0x0F122710},
{0x0F122710},

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
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Text[] = {
{0x00287000},
{0x002A09F4},
{0x0F12A060},
{0x002A0AAA},
{0x0F12A060},
{0x002A0B60},
{0x0F12A060},
{0x002A0C16},
{0x0F12A060},
{0x002A0CCC},
{0x0F12A060}
};

s5k4ecgx_short_t s5k4ecgx_Scene_Candle_Light[] = {
{0xFCFCD000},
{0x00287000},
{0x002a04E0},
{0x0f120777},
{0x002a04B4},
{0x0f1205E0},
{0x0f120001},
{0x0f120400},
{0x0f120001},
{0x0f120530},
{0x0f120001}
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



s5k4ecgx_short_t s5k4ecgx_AF_Return_Inf_pos[] = { // Setting Unavailable

{0x00287000},
{0x002A159A},
{0x0F12CE00}
};

s5k4ecgx_short_t s5k4ecgx_AF_Return_Macro_pos[] = { // Setting Unavailable

};



s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_1[] = {

{0x00287000},
{0x002A0288},   //Wirte Lens Position
{0x0F120000}    //0x0000

};

s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_2[] = {
{0x002A0286},   //
{0x0F120004}    //0x0004 = Manual AF
};


s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_3[] = {
{0x002A160C},   //af search single AFflag
{0x0F129002}    //0x1002 = Normal Mode, 2nd search ON 

};

s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_4[] = {
{0x002A160C},   //af search single AFflag
{0x0F129002}    //0x1002 = Normal Mode, 2nd search ON 

};

s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_1[] = {

{0x00287000},
{0x002A0288},   //Write Lens Position
{0x0F1200D0}    //
};

s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_2[] = {
{0x002A0286},
{0x0F120004}    //0x0004 =  Manual AF
};


s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_3[] = {
{0x002A160C},
{0x0F129042},   //0x1042 = Macro Mode, 2nd Search ON
{0x002A159E},   //macro Start End
{0x0F121500}    //0x16 = start number of table, 0x00 = End number of table

};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_1[] = {// Setting Unavailable
{0x00287000},
{0x002A0288},
{0x0F120000}

};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_2[] = {// Setting Unavailable
{0x002A0286},
{0x0F120004}
};
s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_3[] = {// Setting Unavailable
{0x002A160C},
{0x0F129002}
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_1[] = {// Setting Unavailable

{0x00287000},
{0x002A0288},
{0x0F1200D0}
};


s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_2[] = {// Setting Unavailable
{0x002A0286},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_3[] = {// Setting Unavailable
{0x002A160C},
{0x0F129042},
{0x002A159E},
{0x0F121500}

};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Start[] = {
{0x00287000},
{0x002A0286},
{0x0F120005}
};

                // AE Lock
s5k4ecgx_short_t s5k4ecgx_ae_lock[] = {
{0x00287000},
{0x002A2C5E},
{0x0F120000},
};

                // AE unLock
s5k4ecgx_short_t s5k4ecgx_ae_unlock[] = {
{0x00287000},
{0x002A2C5E},
{0x0F120001},
};

                // AWB Lock
s5k4ecgx_short_t s5k4ecgx_awb_lock[] = {
{0x00287000},
{0x002A2C66},
{0x0F120000},
};

                // AWB unLock
s5k4ecgx_short_t s5k4ecgx_awb_unlock[] = {
{0x00287000},
{0x002A2C66},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_awb_ae_lock[] = {
{0x00287000},
{0x002A2B76}, 
{0x0F120000}, // Mon_AAIO_bAE								0x70002B76	// 0x0000
};

s5k4ecgx_short_t s5k4ecgx_awb_ae_unlock[] = {
{0x00287000},
{0x002A2B76}, 
{0x0F120001}, // Mon_AAIO_bAE								0x70002B76	// 0x0000
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_1[] = {
{0x00287000},
{0x002A0288},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_2[] = {
{0x002A0286},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_3[] = {
{0x002A0286},
{0x0F120002}
};

s5k4ecgx_short_t s5k4ecgx_Face_Detection_On[] = {   // Setting Unavailable

{0x00287000},
{0x002A028E},
{0x0F120100},
{0x0F1200E3},
{0x0F120200},
{0x0F120238},
{0x0F1201C6},
{0x0F120166},
{0x0F120074},
{0x0F120132},
{0x0F120001}
};



s5k4ecgx_short_t s5k4ecgx_Face_Detection_Off[] = {  // Setting Unavailable
{0x00287000},
{0x002A028E},
{0x0F120100},
{0x0F1200E3},
{0x0F120200},
{0x0F120238},
{0x0F1201C6},
{0x0F120166},
{0x0F120074},
{0x0F120132},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_Low_Cap_On[] = {  // AF Not Use IT [????]
{0x00287000}, //Diff. ??.(???? ??. 101012)
{0x002A09EA}, 
{0x0F120D58}, //Diff ??.0A38
{0x002A0AA0},
{0x0F120A53}, //Diff ??. 0A50
};

s5k4ecgx_short_t s5k4ecgx_Low_Cap_Off[] = { // AF Not Use IT [????]
{0x00287000}, //Diff. ??.(???? ??. 101012)
{0x002A09EA},
{0x0F120040},
{0x002A0AA0},
{0x0F120080},
};

s5k4ecgx_short_t s5k4ecgx_Capture_Config[] ={
{0x00287000},
{0x002A1A00}, 
{0x0F12185C}, // senHal_ContPtrs_pSenModeAddr				0x70001A00	// 0x0000
{0x0F127000},
{0x002A023E}, 
{0x0F120001}, // REG_TC_GP_EnableCapture						0x7000023E	// 0x0000
{0x002A024A},
{0x0F120001}, // REG_TC_GP_NewConfigSync						0x7000024A	// 0x0000
{0x002A0240},
//{0x0F120001}  // REG_TC_GP_EnableCaptureChanged				0x70000240	// 0x0000

};

s5k4ecgx_short_t s5k4ecgx_Capture_Start[] ={
{0x00287000},
{0x002A1A00}, 
{0x0F12185C}, // senHal_ContPtrs_pSenModeAddr				0x70001A00	// 0x0000
{0x0F127000},
{0x002A023E}, 
{0x0F120001}, // REG_TC_GP_EnableCapture						0x7000023E	// 0x0000
{0x002A024A},
{0x0F120001}, // REG_TC_GP_NewConfigSync						0x7000024A	// 0x0000
{0x002A0240},
{0x0F120001}  // REG_TC_GP_EnableCaptureChanged				0x70000240	// 0x0000

};

s5k4ecgx_short_t s5k4ecgx_Preview_Return[] ={
{0x00287000},
{0x002A05C4},
{0x0F120000}, // lt_mbr_Peak_behind							0x700005C4	// 0x00CC
{0x002A1A00},
{0x0F12192E}, // senHal_ContPtrs_pSenModeAddr				0x70001A00	// 0x0000 
{0x0F127000},
{0x002A0952},
{0x0F120000}, // afit_bAfitExOffMBR							0x70000952	// 0x0001
{0x002A023E},
{0x0F120000}, // REG_TC_GP_EnableCapture						0x7000023E	// 0x0000 
{0x002A024A},
{0x0F120001}, // REG_TC_GP_NewConfigSync						0x7000024A	// 0x0000 
{0x002A0240},
{0x0F120001}  // REG_TC_GP_EnableCaptureChanged				0x70000240	// 0x0000
};

s5k4ecgx_short_t s5k4ecgx_Flash_init[] = { // Setting Unavailable

};

s5k4ecgx_short_t s5k4ecgx_Pre_Flash_On[] = {

};

s5k4ecgx_short_t s5k4ecgx_Pre_Flash_Off[] = {

};

s5k4ecgx_short_t s5k4ecgx_Main_Flash_On[] = {
{0x00287000},
{0x002A047E},
{0x0F120002},

{0x002A02BC},
{0x0F12014D}, // REG_0TC_PCFG_usMaxFrTimeMsecMult10			0x700002BC	// 0x1964                                                                                            
{0x0F12014D}, // REG_0TC_PCFG_usMinFrTimeMsecMult10			0x700002BE	// 0x0000  

{0x002A03AE},
{0x0F12029A}, // REG_0TC_CCFG_usMaxFrTimeMsecMult10			0x700003AE	// 0x1964     
{0x0F12029A}, // REG_0TC_CCFG_usMinFrTimeMsecMult10			0x700003B0	// 0x0000

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
};



s5k4ecgx_short_t s5k4ecgx_Main_Flash_Off[] = {
{0x00287000},
{0x002A047E},
{0x0F120000},

{0x002A02BC},
{0x0F12029A}, // REG_0TC_PCFG_usMaxFrTimeMsecMult10			0x700002BC	// 0x1964                                                                                            
{0x0F12014D}, // REG_0TC_PCFG_usMinFrTimeMsecMult10			0x700002BE	// 0x0000  

{0x002A03AE},
{0x0F120535}, // REG_0TC_CCFG_usMaxFrTimeMsecMult10			0x700003AE	// 0x1964     
{0x0F12029A}, // REG_0TC_CCFG_usMinFrTimeMsecMult10			0x700003B0	// 0x0000  

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
};

s5k4ecgx_short_t s5k4ecgx_5M_Capture[] = {  /* 2560 x 1920 */

{0xFCFCD000},
{0x00287000},
{0x002A0392},
{0x0F120A00}, // REG_0TC_CCFG_usWidth						0x70000392	// 0x0A20             
{0x0F120780}, // REG_0TC_CCFG_usHeight						0x70000394	// 0x0798             
{0x0F120009}, // REG_0TC_CCFG_Format							0x70000396	// 0x0009                  
{0x002A03AC},
{0x0F120002}, // REG_0TC_CCFG_FrRateQualityType				0x700003AC	// 0x0002       
{0x0F120535}, // REG_0TC_CCFG_usMaxFrTimeMsecMult10			0x700003AE	// 0x1964     
{0x0F12029A}, // REG_0TC_CCFG_usMinFrTimeMsecMult10			0x700003B0	// 0x0000     
{0x002A03AA},
{0x0F120002}, // REG_0TC_CCFG_usFrTimeType					0x700003AA	// 0x0000 
{0x002A026C},
{0x0F120001}  // REG_TC_GP_CapConfigChanged					0x7000026C	// 0x0000    

};

s5k4ecgx_short_t s5k4ecgx_3M_Capture[] = {  /* 2048 x 1536 */

{0xFCFCD000},
{0x00287000},
{0x002A0392},
{0x0F120800}, // REG_0TC_CCFG_usWidth						0x70000392	// 0x0A20       
{0x0F120600}, // REG_0TC_CCFG_usHeight						0x70000394	// 0x0798     
{0x0F120009}, // REG_0TC_CCFG_Format							0x70000396	// 0x0009     
{0x002A03AC},
{0x0F120002},
{0x0F120535},
{0x0F12029A},
{0x002A03AA},
{0x0F120002},
{0x002A026C},
{0x0F120001}

};

s5k4ecgx_short_t s5k4ecgx_2M_Capture[] = {  /* 1600 x 1200 */
{0xFCFCD000},
{0x00287000},
{0x002A0392},
{0x0F120640},
{0x0F1204B0},
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



s5k4ecgx_short_t s5k4ecgx_1M_Capture[] = {  /* 1280 x 960 */
{0xFCFCD000},
{0x00287000},
{0x002A0392},
{0x0F120500},
{0x0F1203C0},
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


s5k4ecgx_short_t s5k4ecgx_VGA_Capture[] = {  /* 640 x 480 */
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

s5k4ecgx_short_t s5k4ecgx_QVGA_Capture[] = {  /* 640 x 480 */
{0xFCFCD000},
{0x00287000},
{0x002A0392},
{0x0F120140},
{0x0F1200F0},
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
{0x002A02A0},
{0x0F1202D0}, // REG_0TC_PCFG_usWidth						0x700002A0	// 0x0A20  
{0x0F1201E0}, // REG_0TC_PCFG_usHeight						0x700002A2	// 0x0798  
{0x0F120005}, // REG_0TC_PCFG_Format							0x700002A4	// 0x0005  
{0x002A02AE},
{0x0F120052}, // REG_0TC_PCFG_PVIMask						0x700002AE	// 0x0042 
{0x002A02B8},
{0x0F120000}, // REG_0TC_PCFG_usFrTimeType					0x700002B8	// 0x0000
{0x0F120001}, // REG_0TC_PCFG_FrRateQualityType				0x700002BA	// 0x0000     
{0x0F12029A}, // REG_0TC_PCFG_usMaxFrTimeMsecMult10			0x700002BC	// 0x1964   
{0x0F12014D}, // REG_0TC_PCFG_usMinFrTimeMsecMult10			0x700002BE	// 0x0000   
{0x002A02CA},
{0x0F120000}, // REG_0TC_PCFG_uPrevMirror					0x700002CA	// 0x0000    
{0x0F120000}, // REG_0TC_PCFG_uCaptureMirror					0x700002CC	// 0x0000  
{0x002A0262},
{0x0F120000}, // REG_TC_GP_ActivePrevConfig					0x70000262	// 0x0000
{0x002A0266},
{0x0F120001}, // REG_TC_GP_PrevOpenAfterChange				0x70000266	// 0x0001 
{0x002A024A},
{0x0F120001}, // REG_TC_GP_NewConfigSync						0x7000024A	// 0x0000
{0x002A0264},
{0x0F120001}  // REG_TC_GP_PrevConfigChanged					0x70000264	// 0x0000
};

s5k4ecgx_short_t s5k4ecgx_640_Preview[] = {  /* 640 x 480 */
{0xFCFCD000},
{0x00287000},
{0x002A02A0},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x002A02AE},
{0x0F120052},
{0x002A02B8},
{0x0F120000},
{0x0F120001},
{0x0F12029A},
{0x0F12014D},
{0x002A02CA},
{0x0F120000},
{0x0F120000},
{0x002A0262},
{0x0F120000},
{0x002A0266},
{0x0F120001},
{0x002A024A},
{0x0F120001},
{0x002A0264},
{0x0F120001}

};

s5k4ecgx_short_t s5k4ecgx_352_Preview[] = {  /* 352 x 288 */
{0xFCFCD000},
{0x00287000},
{0x002A02A0},
{0x0F120160},
{0x0F120120},
{0x0F120005},
{0x002A02AE},
{0x0F120052},
{0x002A02B8},
{0x0F120000},
{0x0F120001},
{0x0F12029A},
{0x0F12014D},
{0x002A02CA},
{0x0F120000},
{0x0F120000},
{0x002A0262},
{0x0F120000},
{0x002A0266},
{0x0F120001},
{0x002A024A},
{0x0F120001},
{0x002A0264},
{0x0F120001}

};


s5k4ecgx_short_t s5k4ecgx_176_Preview[] = {  /* 176 x 144 */
{0xFCFCD000},
{0x00287000},
{0x002A02A0},
{0x0F1200B0},
{0x0F120090},
{0x0F120005},
{0x002A02AE},
{0x0F120052},
{0x002A02B8},
{0x0F120000},
{0x0F120001},
{0x0F12029A},
{0x0F12014D},
{0x002A02CA},
{0x0F120000},
{0x0F120000},
{0x002A0262},
{0x0F120000},
{0x002A0266},
{0x0F120001},
{0x002A024A},
{0x0F120001},
{0x002A0264},
{0x0F120001}
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
#include "s5k4ecgx_evt1_cooper-ltn.h"
#else
#include "s5k4ecgx_evt1_cooper.h"
#endif //CONFIG_SAMSUNG_LTN_COMMON

#endif




