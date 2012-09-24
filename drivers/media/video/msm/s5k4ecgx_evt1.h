/////////////////////////////FOR EVT1.1/////////////////////////////

// ARM Initiation //
s5k4ecgx_short_t s5k4ecgx_init_reg1_EVT1[] = {
{0xFCFCD000},
{0x00100001},
{0x10300000},
{0x00140001},
};

s5k4ecgx_short_t s5k4ecgx_init_reg2_EVT1[] = {
//Driving current Setting//
//2mA Driving current Setting//
{0x0028D000},
{0x002A1082},
{0x0F120000},	//	d0_d4_cd10d0_d4_cd109:0x0155   //
{0x0F120000},	//	d5_d9_cd10d5_d9_cd109:0x0155	//
{0x0F120000},	//	gpi300o_cd10gpio_cd1:0x0055	//
{0x0F120000},	//	clks_output_cd10clks_output_cd1011:0x0555	//
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
{0x0F1255FF}, //101119 Comp ADD Ahn //
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
{0x0F1200AA},	//	#enHal_ContPtrs_senAvgModesDataArr_44_ 	//
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

////////*************************************************************/////////
//OTP setting																																//
////////*************************************************************/////////
{0x002A0722},
{0x0F120100},	//	#skl_OTP_usWaitTime This reg should be in fornt of D0001000	//
{0x002A0726},	
{0x0F120001},	//	#skl_bUseOTPfunc	OTP shading is used,this reg should be 1	//
{0x002A08D6},	
{0x0F120001},	//	#ash_bUseOTPData	OTP shading is used, this reg should be 1	//
{0x002A146E},	
{0x0F120000},	//	#awbb_otp_disable OTP AWB (0: use AWB Cal.)	//
{0x002A08DC},	
{0x0F120001},	//	#ash_bUseGasAlphaOTP	OTP alpha is used, this reg should be 1 //

////////*************************************************************/////////
//TnP setting																																//
////////*************************************************************/////////
// Start of Patch data //

// TnP setting //
// Start of Patch data //
{0x00287000},
{0x002A3AF8},
{0x0F12B570},    // 70003AF8 
{0x0F124B39},    // 70003AFA 
{0x0F124939},    // 70003AFC 
{0x0F12483A},    // 70003AFE 
{0x0F122200},    // 70003B00 
{0x0F12C008},    // 70003B02 
{0x0F126001},    // 70003B04 
{0x0F124939},    // 70003B06 
{0x0F124839},    // 70003B08 
{0x0F122401},    // 70003B0A 
{0x0F12F000},    // 70003B0C 
{0x0F12FBD4},    // 70003B0E 
{0x0F124938},    // 70003B10 
{0x0F124839},    // 70003B12 
{0x0F122502},    // 70003B14 
{0x0F120022},    // 70003B16 
{0x0F12F000},    // 70003B18 
{0x0F12FBCE},    // 70003B1A 
{0x0F124837},    // 70003B1C 
{0x0F120261},    // 70003B1E 
{0x0F128001},    // 70003B20 
{0x0F122100},    // 70003B22 
{0x0F128041},    // 70003B24 
{0x0F124936},    // 70003B26 
{0x0F124836},    // 70003B28 
{0x0F126041},    // 70003B2A 
{0x0F124936},    // 70003B2C 
{0x0F124837},    // 70003B2E 
{0x0F122403},    // 70003B30 
{0x0F12002A},    // 70003B32 
{0x0F12F000},    // 70003B34 
{0x0F12FBC0},    // 70003B36 
{0x0F124832},    // 70003B38 
{0x0F124935},    // 70003B3A 
{0x0F1230C0},    // 70003B3C 
{0x0F1263C1},    // 70003B3E 
{0x0F124930},    // 70003B40 
{0x0F124834},    // 70003B42 
{0x0F123980},    // 70003B44 
{0x0F126408},    // 70003B46 
{0x0F124833},    // 70003B48 
{0x0F124934},    // 70003B4A 
{0x0F126388},    // 70003B4C 
{0x0F124934},    // 70003B4E 
{0x0F124834},    // 70003B50 
{0x0F120022},    // 70003B52 
{0x0F122504},    // 70003B54 
{0x0F12F000},    // 70003B56 
{0x0F12FBAF},    // 70003B58 
{0x0F124933},    // 70003B5A 
{0x0F124833},    // 70003B5C 
{0x0F122405},    // 70003B5E 
{0x0F12002A},    // 70003B60 
{0x0F12F000},    // 70003B62 
{0x0F12F881},    // 70003B64 
{0x0F12491F},    // 70003B66 
{0x0F124830},    // 70003B68 
{0x0F120022},    // 70003B6A 
{0x0F122506},    // 70003B6C 
{0x0F1239B6},    // 70003B6E 
{0x0F121D80},    // 70003B70 
{0x0F12F000},    // 70003B72 
{0x0F12F879},    // 70003B74 
{0x0F12482D},    // 70003B76 
{0x0F12492D},    // 70003B78 
{0x0F122407},    // 70003B7A 
{0x0F12002A},    // 70003B7C 
{0x0F12300C},    // 70003B7E 
{0x0F12F000},    // 70003B80 
{0x0F12F872},    // 70003B82 
{0x0F124829},    // 70003B84 
{0x0F12492B},    // 70003B86 
{0x0F120022},    // 70003B88 
{0x0F122508},    // 70003B8A 
{0x0F123010},    // 70003B8C 
{0x0F12F000},    // 70003B8E 
{0x0F12F86B},    // 70003B90 
{0x0F124929},    // 70003B92 
{0x0F124829},    // 70003B94 
{0x0F122409},    // 70003B96 
{0x0F12002A},    // 70003B98 
{0x0F12F000},    // 70003B9A 
{0x0F12FB8D},    // 70003B9C 
{0x0F124928},    // 70003B9E 
{0x0F124828},    // 70003BA0 
{0x0F120022},    // 70003BA2 
{0x0F12250A},    // 70003BA4 
{0x0F12F000},    // 70003BA6 
{0x0F12FB87},    // 70003BA8 
{0x0F124927},    // 70003BAA 
{0x0F124827},    // 70003BAC 
{0x0F12240B},    // 70003BAE 
{0x0F12002A},    // 70003BB0 
{0x0F12F000},    // 70003BB2 
{0x0F12FB81},    // 70003BB4 
{0x0F124926},    // 70003BB6 
{0x0F124826},    // 70003BB8 
{0x0F120022},    // 70003BBA 
{0x0F12250C},    // 70003BBC 
{0x0F12F000},    // 70003BBE 
{0x0F12FB7B},    // 70003BC0 
{0x0F124925},    // 70003BC2 
{0x0F124825},    // 70003BC4 
{0x0F12240D},    // 70003BC6 
{0x0F12002A},    // 70003BC8 
{0x0F12F000},    // 70003BCA 
{0x0F12FB75},    // 70003BCC 
{0x0F124924},    // 70003BCE 
{0x0F124824},    // 70003BD0 
{0x0F120022},    // 70003BD2 
{0x0F12F000},    // 70003BD4 
{0x0F12FB70},    // 70003BD6 
{0x0F12BC70},    // 70003BD8 
{0x0F12BC08},    // 70003BDA 
{0x0F124718},    // 70003BDC 
{0x0F120000},    // 70003BDE 
{0x0F12018F},    // 70003BE0 
{0x0F124EC2},    // 70003BE2 
{0x0F12037F},    // 70003BE4 
{0x0F120000},    // 70003BE6 
{0x0F121F90},    // 70003BE8 
{0x0F127000},    // 70003BEA 
{0x0F123C81},    // 70003BEC 
{0x0F127000},    // 70003BEE 
{0x0F12E38B},    // 70003BF0 
{0x0F120000},    // 70003BF2 
{0x0F123CB9},    // 70003BF4 
{0x0F127000},    // 70003BF6 
{0x0F12C3B1},    // 70003BF8 
{0x0F120000},    // 70003BFA 
{0x0F124780},    // 70003BFC 
{0x0F127000},    // 70003BFE 
{0x0F123D17},    // 70003C00 
{0x0F127000},    // 70003C02 
{0x0F120080},    // 70003C04 
{0x0F127000},    // 70003C06 
{0x0F123D53},    // 70003C08 
{0x0F127000},    // 70003C0A 
{0x0F12B49D},    // 70003C0C 
{0x0F120000},    // 70003C0E 
{0x0F123DFF},    // 70003C10 
{0x0F127000},    // 70003C12 
{0x0F123DB3},    // 70003C14 
{0x0F127000},    // 70003C16 
{0x0F12FFFF},    // 70003C18 
{0x0F1200FF},    // 70003C1A 
{0x0F1217E0},    // 70003C1C 
{0x0F127000},    // 70003C1E 
{0x0F123F7B},    // 70003C20 
{0x0F127000},    // 70003C22 
{0x0F12053D},    // 70003C24 
{0x0F120000},    // 70003C26 
{0x0F120000},    // 70003C28 
{0x0F120A89},    // 70003C2A 
{0x0F126CD2},    // 70003C2C 
{0x0F120000},    // 70003C2E 
{0x0F120000},    // 70003C30 
{0x0F120A9A},    // 70003C32 
{0x0F120000},    // 70003C34 
{0x0F1202D2},    // 70003C36 
{0x0F123FC9},    // 70003C38 
{0x0F127000},    // 70003C3A 
{0x0F129E65},    // 70003C3C 
{0x0F120000},    // 70003C3E 
{0x0F12403D},    // 70003C40 
{0x0F127000},    // 70003C42 
{0x0F127C49},    // 70003C44 
{0x0F120000},    // 70003C46 
{0x0F1240B1},    // 70003C48 
{0x0F127000},    // 70003C4A 
{0x0F127C63},    // 70003C4C 
{0x0F120000},    // 70003C4E 
{0x0F1240CD},    // 70003C50 
{0x0F127000},    // 70003C52 
{0x0F128F01},    // 70003C54 
{0x0F120000},    // 70003C56 
{0x0F12416F},    // 70003C58 
{0x0F127000},    // 70003C5A 
{0x0F127F3F},    // 70003C5C 
{0x0F120000},    // 70003C5E 
{0x0F1241FD},    // 70003C60 
{0x0F127000},    // 70003C62 
{0x0F1298C5},    // 70003C64 
{0x0F120000},    // 70003C66 
{0x0F12B570},    // 70003C68 
{0x0F12000C},    // 70003C6A 
{0x0F120015},    // 70003C6C 
{0x0F120029},    // 70003C6E 
{0x0F12F000},    // 70003C70 
{0x0F12FB2A},    // 70003C72 
{0x0F1249F8},    // 70003C74 
{0x0F1200A8},    // 70003C76 
{0x0F12500C},    // 70003C78 
{0x0F12BC70},    // 70003C7A 
{0x0F12BC08},    // 70003C7C 
{0x0F124718},    // 70003C7E 
{0x0F126808},    // 70003C80 
{0x0F120400},    // 70003C82 
{0x0F120C00},    // 70003C84 
{0x0F126849},    // 70003C86 
{0x0F120409},    // 70003C88 
{0x0F120C09},    // 70003C8A 
{0x0F124AF3},    // 70003C8C 
{0x0F128992},    // 70003C8E 
{0x0F122A00},    // 70003C90 
{0x0F12D00D},    // 70003C92 
{0x0F122300},    // 70003C94 
{0x0F121A89},    // 70003C96 
{0x0F12D400},    // 70003C98 
{0x0F12000B},    // 70003C9A 
{0x0F120419},    // 70003C9C 
{0x0F120C09},    // 70003C9E 
{0x0F1223FF},    // 70003CA0 
{0x0F1233C1},    // 70003CA2 
{0x0F121810},    // 70003CA4 
{0x0F124298},    // 70003CA6 
{0x0F12D800},    // 70003CA8 
{0x0F120003},    // 70003CAA 
{0x0F120418},    // 70003CAC 
{0x0F120C00},    // 70003CAE 
{0x0F124AEB},    // 70003CB0 
{0x0F128150},    // 70003CB2 
{0x0F128191},    // 70003CB4 
{0x0F124770},    // 70003CB6 
{0x0F12B5F3},    // 70003CB8 
{0x0F120004},    // 70003CBA 
{0x0F12B081},    // 70003CBC 
{0x0F129802},    // 70003CBE 
{0x0F126800},    // 70003CC0 
{0x0F120600},    // 70003CC2 
{0x0F120E00},    // 70003CC4 
{0x0F122201},    // 70003CC6 
{0x0F120015},    // 70003CC8 
{0x0F120021},    // 70003CCA 
{0x0F123910},    // 70003CCC 
{0x0F12408A},    // 70003CCE 
{0x0F1240A5},    // 70003CD0 
{0x0F124FE4},    // 70003CD2 
{0x0F120016},    // 70003CD4 
{0x0F122C10},    // 70003CD6 
{0x0F12DA03},    // 70003CD8 
{0x0F128839},    // 70003CDA 
{0x0F1243A9},    // 70003CDC 
{0x0F128039},    // 70003CDE 
{0x0F12E002},    // 70003CE0 
{0x0F128879},    // 70003CE2 
{0x0F1243B1},    // 70003CE4 
{0x0F128079},    // 70003CE6 
{0x0F12F000},    // 70003CE8 
{0x0F12FAF6},    // 70003CEA 
{0x0F122C10},    // 70003CEC 
{0x0F12DA03},    // 70003CEE 
{0x0F128839},    // 70003CF0 
{0x0F124329},    // 70003CF2 
{0x0F128039},    // 70003CF4 
{0x0F12E002},    // 70003CF6 
{0x0F128879},    // 70003CF8 
{0x0F124331},    // 70003CFA 
{0x0F128079},    // 70003CFC 
{0x0F1249DA},    // 70003CFE 
{0x0F128809},    // 70003D00 
{0x0F122900},    // 70003D02 
{0x0F12D102},    // 70003D04 
{0x0F12F000},    // 70003D06 
{0x0F12FAEF},    // 70003D08 
{0x0F122000},    // 70003D0A 
{0x0F129902},    // 70003D0C 
{0x0F126008},    // 70003D0E 
{0x0F12BCFE},    // 70003D10 
{0x0F12BC08},    // 70003D12 
{0x0F124718},    // 70003D14 
{0x0F12B538},    // 70003D16 
{0x0F129C04},    // 70003D18 
{0x0F120015},    // 70003D1A 
{0x0F12002A},    // 70003D1C 
{0x0F129400},    // 70003D1E 
{0x0F12F000},    // 70003D20 
{0x0F12FAEA},    // 70003D22 
{0x0F124AD1},    // 70003D24 
{0x0F128811},    // 70003D26 
{0x0F122900},    // 70003D28 
{0x0F12D00F},    // 70003D2A 
{0x0F128820},    // 70003D2C 
{0x0F124281},    // 70003D2E 
{0x0F12D20C},    // 70003D30 
{0x0F128861},    // 70003D32 
{0x0F128853},    // 70003D34 
{0x0F124299},    // 70003D36 
{0x0F12D200},    // 70003D38 
{0x0F121E40},    // 70003D3A 
{0x0F120400},    // 70003D3C 
{0x0F120C00},    // 70003D3E 
{0x0F128020},    // 70003D40 
{0x0F128851},    // 70003D42 
{0x0F128061},    // 70003D44 
{0x0F124368},    // 70003D46 
{0x0F121840},    // 70003D48 
{0x0F126060},    // 70003D4A 
{0x0F12BC38},    // 70003D4C 
{0x0F12BC08},    // 70003D4E 
{0x0F124718},    // 70003D50 
{0x0F12B5F8},    // 70003D52 
{0x0F120004},    // 70003D54 
{0x0F126808},    // 70003D56 
{0x0F120400},    // 70003D58 
{0x0F120C00},    // 70003D5A 
{0x0F122201},    // 70003D5C 
{0x0F120015},    // 70003D5E 
{0x0F120021},    // 70003D60 
{0x0F123910},    // 70003D62 
{0x0F12408A},    // 70003D64 
{0x0F1240A5},    // 70003D66 
{0x0F124FBE},    // 70003D68 
{0x0F120016},    // 70003D6A 
{0x0F122C10},    // 70003D6C 
{0x0F12DA03},    // 70003D6E 
{0x0F128839},    // 70003D70 
{0x0F1243A9},    // 70003D72 
{0x0F128039},    // 70003D74 
{0x0F12E002},    // 70003D76 
{0x0F128879},    // 70003D78 
{0x0F1243B1},    // 70003D7A 
{0x0F128079},    // 70003D7C 
{0x0F12F000},    // 70003D7E 
{0x0F12FAC3},    // 70003D80 
{0x0F122C10},    // 70003D82 
{0x0F12DA03},    // 70003D84 
{0x0F128838},    // 70003D86 
{0x0F124328},    // 70003D88 
{0x0F128038},    // 70003D8A 
{0x0F12E002},    // 70003D8C 
{0x0F128878},    // 70003D8E 
{0x0F124330},    // 70003D90 
{0x0F128078},    // 70003D92 
{0x0F1248B6},    // 70003D94 
{0x0F128800},    // 70003D96 
{0x0F120400},    // 70003D98 
{0x0F12D507},    // 70003D9A 
{0x0F124BB5},    // 70003D9C 
{0x0F127819},    // 70003D9E 
{0x0F124AB5},    // 70003DA0 
{0x0F127810},    // 70003DA2 
{0x0F127018},    // 70003DA4 
{0x0F127011},    // 70003DA6 
{0x0F1249B4},    // 70003DA8 
{0x0F128188},    // 70003DAA 
{0x0F12BCF8},    // 70003DAC 
{0x0F12BC08},    // 70003DAE 
{0x0F124718},    // 70003DB0 
{0x0F12B538},    // 70003DB2 
{0x0F1248B2},    // 70003DB4 
{0x0F124669},    // 70003DB6 
{0x0F12F000},    // 70003DB8 
{0x0F12FAAE},    // 70003DBA 
{0x0F1248B1},    // 70003DBC 
{0x0F1249B0},    // 70003DBE 
{0x0F1269C2},    // 70003DC0 
{0x0F122400},    // 70003DC2 
{0x0F1231A8},    // 70003DC4 
{0x0F122A00},    // 70003DC6 
{0x0F12D008},    // 70003DC8 
{0x0F1261C4},    // 70003DCA 
{0x0F12684A},    // 70003DCC 
{0x0F126242},    // 70003DCE 
{0x0F126282},    // 70003DD0 
{0x0F12466B},    // 70003DD2 
{0x0F12881A},    // 70003DD4 
{0x0F126302},    // 70003DD6 
{0x0F12885A},    // 70003DD8 
{0x0F126342},    // 70003DDA 
{0x0F126A02},    // 70003DDC 
{0x0F122A00},    // 70003DDE 
{0x0F12D00A},    // 70003DE0 
{0x0F126204},    // 70003DE2 
{0x0F126849},    // 70003DE4 
{0x0F126281},    // 70003DE6 
{0x0F12466B},    // 70003DE8 
{0x0F128819},    // 70003DEA 
{0x0F126301},    // 70003DEC 
{0x0F128859},    // 70003DEE 
{0x0F126341},    // 70003DF0 
{0x0F1249A5},    // 70003DF2 
{0x0F1288C9},    // 70003DF4 
{0x0F1263C1},    // 70003DF6 
{0x0F12F000},    // 70003DF8 
{0x0F12FA96},    // 70003DFA 
{0x0F12E7A6},    // 70003DFC 
{0x0F12B5F0},    // 70003DFE 
{0x0F12B08B},    // 70003E00 
{0x0F1220FF},    // 70003E02 
{0x0F121C40},    // 70003E04 
{0x0F1249A1},    // 70003E06 
{0x0F1289CC},    // 70003E08 
{0x0F124E9E},    // 70003E0A 
{0x0F126AB1},    // 70003E0C 
{0x0F124284},    // 70003E0E 
{0x0F12D101},    // 70003E10 
{0x0F12489F},    // 70003E12 
{0x0F126081},    // 70003E14 
{0x0F126A70},    // 70003E16 
{0x0F120200},    // 70003E18 
{0x0F12F000},    // 70003E1A 
{0x0F12FA8D},    // 70003E1C 
{0x0F120400},    // 70003E1E 
{0x0F120C00},    // 70003E20 
{0x0F124A96},    // 70003E22 
{0x0F128A11},    // 70003E24 
{0x0F129109},    // 70003E26 
{0x0F122101},    // 70003E28 
{0x0F120349},    // 70003E2A 
{0x0F124288},    // 70003E2C 
{0x0F12D200},    // 70003E2E 
{0x0F120001},    // 70003E30 
{0x0F124A92},    // 70003E32 
{0x0F128211},    // 70003E34 
{0x0F124D97},    // 70003E36 
{0x0F128829},    // 70003E38 
{0x0F129108},    // 70003E3A 
{0x0F124A8B},    // 70003E3C 
{0x0F122303},    // 70003E3E 
{0x0F123222},    // 70003E40 
{0x0F121F91},    // 70003E42 
{0x0F12F000},    // 70003E44 
{0x0F12FA7E},    // 70003E46 
{0x0F128028},    // 70003E48 
{0x0F12488E},    // 70003E4A 
{0x0F124987},    // 70003E4C 
{0x0F126BC2},    // 70003E4E 
{0x0F126AC0},    // 70003E50 
{0x0F124282},    // 70003E52 
{0x0F12D201},    // 70003E54 
{0x0F128CC8},    // 70003E56 
{0x0F128028},    // 70003E58 
{0x0F1288E8},    // 70003E5A 
{0x0F129007},    // 70003E5C 
{0x0F122240},    // 70003E5E 
{0x0F124310},    // 70003E60 
{0x0F1280E8},    // 70003E62 
{0x0F122000},    // 70003E64 
{0x0F120041},    // 70003E66 
{0x0F12194B},    // 70003E68 
{0x0F12001E},    // 70003E6A 
{0x0F123680},    // 70003E6C 
{0x0F128BB2},    // 70003E6E 
{0x0F12AF04},    // 70003E70 
{0x0F12527A},    // 70003E72 
{0x0F124A7D},    // 70003E74 
{0x0F12188A},    // 70003E76 
{0x0F128897},    // 70003E78 
{0x0F1283B7},    // 70003E7A 
{0x0F1233A0},    // 70003E7C 
{0x0F12891F},    // 70003E7E 
{0x0F12AE01},    // 70003E80 
{0x0F125277},    // 70003E82 
{0x0F128A11},    // 70003E84 
{0x0F128119},    // 70003E86 
{0x0F121C40},    // 70003E88 
{0x0F120400},    // 70003E8A 
{0x0F120C00},    // 70003E8C 
{0x0F122806},    // 70003E8E 
{0x0F12D3E9},    // 70003E90 
{0x0F12F000},    // 70003E92 
{0x0F12FA5F},    // 70003E94 
{0x0F12F000},    // 70003E96 
{0x0F12FA65},    // 70003E98 
{0x0F124F79},    // 70003E9A 
{0x0F1237A8},    // 70003E9C 
{0x0F122800},    // 70003E9E 
{0x0F12D10A},    // 70003EA0 
{0x0F121FE0},    // 70003EA2 
{0x0F1238FD},    // 70003EA4 
{0x0F12D001},    // 70003EA6 
{0x0F121CC0},    // 70003EA8 
{0x0F12D105},    // 70003EAA 
{0x0F124874},    // 70003EAC 
{0x0F128829},    // 70003EAE 
{0x0F123818},    // 70003EB0 
{0x0F126840},    // 70003EB2 
{0x0F124348},    // 70003EB4 
{0x0F126078},    // 70003EB6 
{0x0F124972},    // 70003EB8 
{0x0F126878},    // 70003EBA 
{0x0F126B89},    // 70003EBC 
{0x0F124288},    // 70003EBE 
{0x0F12D300},    // 70003EC0 
{0x0F120008},    // 70003EC2 
{0x0F126078},    // 70003EC4 
{0x0F122000},    // 70003EC6 
{0x0F120041},    // 70003EC8 
{0x0F12AA04},    // 70003ECA 
{0x0F125A53},    // 70003ECC 
{0x0F12194A},    // 70003ECE 
{0x0F12269C},    // 70003ED0 
{0x0F1252B3},    // 70003ED2 
{0x0F12AB01},    // 70003ED4 
{0x0F125A59},    // 70003ED6 
{0x0F1232A0},    // 70003ED8 
{0x0F128111},    // 70003EDA 
{0x0F121C40},    // 70003EDC 
{0x0F120400},    // 70003EDE 
{0x0F120C00},    // 70003EE0 
{0x0F122806},    // 70003EE2 
{0x0F12D3F0},    // 70003EE4 
{0x0F124965},    // 70003EE6 
{0x0F129809},    // 70003EE8 
{0x0F128208},    // 70003EEA 
{0x0F129808},    // 70003EEC 
{0x0F128028},    // 70003EEE 
{0x0F129807},    // 70003EF0 
{0x0F1280E8},    // 70003EF2 
{0x0F121FE0},    // 70003EF4 
{0x0F1238FD},    // 70003EF6 
{0x0F12D13B},    // 70003EF8 
{0x0F124D64},    // 70003EFA 
{0x0F1289E8},    // 70003EFC 
{0x0F121FC1},    // 70003EFE 
{0x0F1239FF},    // 70003F00 
{0x0F12D136},    // 70003F02 
{0x0F124C5F},    // 70003F04 
{0x0F128AE0},    // 70003F06 
{0x0F12F000},    // 70003F08 
{0x0F12FA34},    // 70003F0A 
{0x0F120006},    // 70003F0C 
{0x0F128B20},    // 70003F0E 
{0x0F12F000},    // 70003F10 
{0x0F12FA38},    // 70003F12 
{0x0F129000},    // 70003F14 
{0x0F126AA1},    // 70003F16 
{0x0F126878},    // 70003F18 
{0x0F121809},    // 70003F1A 
{0x0F120200},    // 70003F1C 
{0x0F12F000},    // 70003F1E 
{0x0F12FA0B},    // 70003F20 
{0x0F120400},    // 70003F22 
{0x0F120C00},    // 70003F24 
{0x0F120022},    // 70003F26 
{0x0F123246},    // 70003F28 
{0x0F120011},    // 70003F2A 
{0x0F12310A},    // 70003F2C 
{0x0F122305},    // 70003F2E 
{0x0F12F000},    // 70003F30 
{0x0F12FA08},    // 70003F32 
{0x0F1266E8},    // 70003F34 
{0x0F126B23},    // 70003F36 
{0x0F120002},    // 70003F38 
{0x0F120031},    // 70003F3A 
{0x0F120018},    // 70003F3C 
{0x0F12F000},    // 70003F3E 
{0x0F12FA29},    // 70003F40 
{0x0F12466B},    // 70003F42 
{0x0F128518},    // 70003F44 
{0x0F126EEA},    // 70003F46 
{0x0F126B60},    // 70003F48 
{0x0F129900},    // 70003F4A 
{0x0F12F000},    // 70003F4C 
{0x0F12FA22},    // 70003F4E 
{0x0F12466B},    // 70003F50 
{0x0F128558},    // 70003F52 
{0x0F120029},    // 70003F54 
{0x0F12980A},    // 70003F56 
{0x0F123170},    // 70003F58 
{0x0F12F000},    // 70003F5A 
{0x0F12FA23},    // 70003F5C 
{0x0F120028},    // 70003F5E 
{0x0F123060},    // 70003F60 
{0x0F128A02},    // 70003F62 
{0x0F124946},    // 70003F64 
{0x0F123128},    // 70003F66 
{0x0F12808A},    // 70003F68 
{0x0F128A42},    // 70003F6A 
{0x0F1280CA},    // 70003F6C 
{0x0F128A80},    // 70003F6E 
{0x0F128108},    // 70003F70 
{0x0F12B00B},    // 70003F72 
{0x0F12BCF0},    // 70003F74 
{0x0F12BC08},    // 70003F76 
{0x0F124718},    // 70003F78 
{0x0F12B570},    // 70003F7A 
{0x0F122400},    // 70003F7C 
{0x0F124D46},    // 70003F7E 
{0x0F124846},    // 70003F80 
{0x0F128881},    // 70003F82 
{0x0F124846},    // 70003F84 
{0x0F128041},    // 70003F86 
{0x0F122101},    // 70003F88 
{0x0F128001},    // 70003F8A 
{0x0F12F000},    // 70003F8C 
{0x0F12FA12},    // 70003F8E 
{0x0F124842},    // 70003F90 
{0x0F123820},    // 70003F92 
{0x0F128BC0},    // 70003F94 
{0x0F12F000},    // 70003F96 
{0x0F12FA15},    // 70003F98 
{0x0F124B42},    // 70003F9A 
{0x0F12220D},    // 70003F9C 
{0x0F120712},    // 70003F9E 
{0x0F1218A8},    // 70003FA0 
{0x0F128806},    // 70003FA2 
{0x0F1200E1},    // 70003FA4 
{0x0F1218C9},    // 70003FA6 
{0x0F1281CE},    // 70003FA8 
{0x0F128846},    // 70003FAA 
{0x0F12818E},    // 70003FAC 
{0x0F128886},    // 70003FAE 
{0x0F12824E},    // 70003FB0 
{0x0F1288C0},    // 70003FB2 
{0x0F128208},    // 70003FB4 
{0x0F123508},    // 70003FB6 
{0x0F12042D},    // 70003FB8 
{0x0F120C2D},    // 70003FBA 
{0x0F121C64},    // 70003FBC 
{0x0F120424},    // 70003FBE 
{0x0F120C24},    // 70003FC0 
{0x0F122C07},    // 70003FC2 
{0x0F12D3EC},    // 70003FC4 
{0x0F12E658},    // 70003FC6 
{0x0F12B510},    // 70003FC8 
{0x0F124834},    // 70003FCA 
{0x0F124C34},    // 70003FCC 
{0x0F1288C0},    // 70003FCE 
{0x0F128060},    // 70003FD0 
{0x0F122001},    // 70003FD2 
{0x0F128020},    // 70003FD4 
{0x0F124831},    // 70003FD6 
{0x0F123820},    // 70003FD8 
{0x0F128BC0},    // 70003FDA 
{0x0F12F000},    // 70003FDC 
{0x0F12F9F2},    // 70003FDE 
{0x0F1288E0},    // 70003FE0 
{0x0F124A31},    // 70003FE2 
{0x0F122800},    // 70003FE4 
{0x0F12D003},    // 70003FE6 
{0x0F124930},    // 70003FE8 
{0x0F128849},    // 70003FEA 
{0x0F122900},    // 70003FEC 
{0x0F12D009},    // 70003FEE 
{0x0F122001},    // 70003FF0 
{0x0F1203C0},    // 70003FF2 
{0x0F128050},    // 70003FF4 
{0x0F1280D0},    // 70003FF6 
{0x0F122000},    // 70003FF8 
{0x0F128090},    // 70003FFA 
{0x0F128110},    // 70003FFC 
{0x0F12BC10},    // 70003FFE 
{0x0F12BC08},    // 70004000 
{0x0F124718},    // 70004002 
{0x0F128050},    // 70004004 
{0x0F128920},    // 70004006 
{0x0F1280D0},    // 70004008 
{0x0F128960},    // 7000400A 
{0x0F120400},    // 7000400C 
{0x0F121400},    // 7000400E 
{0x0F128090},    // 70004010 
{0x0F1289A1},    // 70004012 
{0x0F120409},    // 70004014 
{0x0F121409},    // 70004016 
{0x0F128111},    // 70004018 
{0x0F1289E3},    // 7000401A 
{0x0F128A24},    // 7000401C 
{0x0F122B00},    // 7000401E 
{0x0F12D104},    // 70004020 
{0x0F1217C3},    // 70004022 
{0x0F120F5B},    // 70004024 
{0x0F121818},    // 70004026 
{0x0F1210C0},    // 70004028 
{0x0F128090},    // 7000402A 
{0x0F122C00},    // 7000402C 
{0x0F12D1E6},    // 7000402E 
{0x0F1217C8},    // 70004030 
{0x0F120F40},    // 70004032 
{0x0F121840},    // 70004034 
{0x0F1210C0},    // 70004036 
{0x0F128110},    // 70004038 
{0x0F12E7E0},    // 7000403A 
{0x0F12B510},    // 7000403C 
{0x0F12000C},    // 7000403E 
{0x0F124919},    // 70004040 
{0x0F122204},    // 70004042 
{0x0F126820},    // 70004044 
{0x0F125E8A},    // 70004046 
{0x0F120140},    // 70004048 
{0x0F121A80},    // 7000404A 
{0x0F120280},    // 7000404C 
{0x0F128849},    // 7000404E 
{0x0F12F000},    // 70004050 
{0x0F12F9C0},    // 70004052 
{0x0F126020},    // 70004054 
{0x0F12E7D2},    // 70004056 
{0x0F1238D4},    // 70004058 
{0x0F127000},    // 7000405A 
{0x0F1217D0},    // 7000405C 
{0x0F127000},    // 7000405E 
{0x0F125000},    // 70004060 
{0x0F12D000},    // 70004062 
{0x0F121100},    // 70004064 
{0x0F12D000},    // 70004066 
{0x0F12171A},    // 70004068 
{0x0F127000},    // 7000406A 
{0x0F124780},    // 7000406C 
{0x0F127000},    // 7000406E 
{0x0F122FCA},    // 70004070 
{0x0F127000},    // 70004072 
{0x0F122FC5},    // 70004074 
{0x0F127000},    // 70004076 
{0x0F122FC6},    // 70004078 
{0x0F127000},    // 7000407A 
{0x0F122ED8},    // 7000407C 
{0x0F127000},    // 7000407E 
{0x0F122BD0},    // 70004080 
{0x0F127000},    // 70004082 
{0x0F1217E0},    // 70004084 
{0x0F127000},    // 70004086 
{0x0F122DE8},    // 70004088 
{0x0F127000},    // 7000408A 
{0x0F1237E0},    // 7000408C 
{0x0F127000},    // 7000408E 
{0x0F12210C},    // 70004090 
{0x0F127000},    // 70004092 
{0x0F121484},    // 70004094 
{0x0F127000},    // 70004096 
{0x0F12A006},    // 70004098 
{0x0F120000},    // 7000409A 
{0x0F120724},    // 7000409C 
{0x0F127000},    // 7000409E 
{0x0F12A000},    // 700040A0 
{0x0F12D000},    // 700040A2 
{0x0F122270},    // 700040A4 
{0x0F127000},    // 700040A6 
{0x0F122558},    // 700040A8 
{0x0F127000},    // 700040AA 
{0x0F12146C},    // 700040AC 
{0x0F127000},    // 700040AE 
{0x0F12B510},    // 700040B0 
{0x0F12000C},    // 700040B2 
{0x0F124979},    // 700040B4 
{0x0F122208},    // 700040B6 
{0x0F126820},    // 700040B8 
{0x0F125E8A},    // 700040BA 
{0x0F120140},    // 700040BC 
{0x0F121A80},    // 700040BE 
{0x0F120280},    // 700040C0 
{0x0F1288C9},    // 700040C2 
{0x0F12F000},    // 700040C4 
{0x0F12F986},    // 700040C6 
{0x0F126020},    // 700040C8 
{0x0F12E798},    // 700040CA 
{0x0F12B5FE},    // 700040CC 
{0x0F12000C},    // 700040CE 
{0x0F126825},    // 700040D0 
{0x0F126866},    // 700040D2 
{0x0F1268A0},    // 700040D4 
{0x0F129001},    // 700040D6 
{0x0F1268E7},    // 700040D8 
{0x0F121BA8},    // 700040DA 
{0x0F1242B5},    // 700040DC 
{0x0F12DA00},    // 700040DE 
{0x0F121B70},    // 700040E0 
{0x0F129000},    // 700040E2 
{0x0F12496D},    // 700040E4 
{0x0F12486E},    // 700040E6 
{0x0F12884A},    // 700040E8 
{0x0F128843},    // 700040EA 
{0x0F12435A},    // 700040EC 
{0x0F122304},    // 700040EE 
{0x0F125ECB},    // 700040F0 
{0x0F120A92},    // 700040F2 
{0x0F1218D2},    // 700040F4 
{0x0F1202D2},    // 700040F6 
{0x0F120C12},    // 700040F8 
{0x0F1288CB},    // 700040FA 
{0x0F128880},    // 700040FC 
{0x0F124343},    // 700040FE 
{0x0F120A98},    // 70004100 
{0x0F122308},    // 70004102 
{0x0F125ECB},    // 70004104 
{0x0F1218C0},    // 70004106 
{0x0F1202C0},    // 70004108 
{0x0F120C00},    // 7000410A 
{0x0F120411},    // 7000410C 
{0x0F120400},    // 7000410E 
{0x0F121409},    // 70004110 
{0x0F121400},    // 70004112 
{0x0F121A08},    // 70004114 
{0x0F124962},    // 70004116 
{0x0F1239E0},    // 70004118 
{0x0F126148},    // 7000411A 
{0x0F129801},    // 7000411C 
{0x0F123040},    // 7000411E 
{0x0F127880},    // 70004120 
{0x0F122800},    // 70004122 
{0x0F12D103},    // 70004124 
{0x0F129801},    // 70004126 
{0x0F120029},    // 70004128 
{0x0F12F000},    // 7000412A 
{0x0F12F959},    // 7000412C 
{0x0F128839},    // 7000412E 
{0x0F129800},    // 70004130 
{0x0F124281},    // 70004132 
{0x0F12D814},    // 70004134 
{0x0F128879},    // 70004136 
{0x0F129800},    // 70004138 
{0x0F124281},    // 7000413A 
{0x0F12D20C},    // 7000413C 
{0x0F129801},    // 7000413E 
{0x0F120029},    // 70004140 
{0x0F12F000},    // 70004142 
{0x0F12F955},    // 70004144 
{0x0F129801},    // 70004146 
{0x0F120029},    // 70004148 
{0x0F12F000},    // 7000414A 
{0x0F12F951},    // 7000414C 
{0x0F129801},    // 7000414E 
{0x0F120029},    // 70004150 
{0x0F12F000},    // 70004152 
{0x0F12F94D},    // 70004154 
{0x0F12E003},    // 70004156 
{0x0F129801},    // 70004158 
{0x0F120029},    // 7000415A 
{0x0F12F000},    // 7000415C 
{0x0F12F948},    // 7000415E 
{0x0F129801},    // 70004160 
{0x0F120032},    // 70004162 
{0x0F120039},    // 70004164 
{0x0F12F000},    // 70004166 
{0x0F12F94B},    // 70004168 
{0x0F126020},    // 7000416A 
{0x0F12E5D0},    // 7000416C 
{0x0F12B57C},    // 7000416E 
{0x0F12484C},    // 70004170 
{0x0F12A901},    // 70004172 
{0x0F120004},    // 70004174 
{0x0F12F000},    // 70004176 
{0x0F12F8CF},    // 70004178 
{0x0F12466B},    // 7000417A 
{0x0F1288D9},    // 7000417C 
{0x0F128898},    // 7000417E 
{0x0F124B47},    // 70004180 
{0x0F123346},    // 70004182 
{0x0F121E9A},    // 70004184 
{0x0F12F000},    // 70004186 
{0x0F12F943},    // 70004188 
{0x0F124846},    // 7000418A 
{0x0F124944},    // 7000418C 
{0x0F123812},    // 7000418E 
{0x0F123140},    // 70004190 
{0x0F128A42},    // 70004192 
{0x0F12888B},    // 70004194 
{0x0F1218D2},    // 70004196 
{0x0F128242},    // 70004198 
{0x0F128AC2},    // 7000419A 
{0x0F1288C9},    // 7000419C 
{0x0F121851},    // 7000419E 
{0x0F1282C1},    // 700041A0 
{0x0F120020},    // 700041A2 
{0x0F124669},    // 700041A4 
{0x0F12F000},    // 700041A6 
{0x0F12F8B7},    // 700041A8 
{0x0F12483F},    // 700041AA 
{0x0F12214D},    // 700041AC 
{0x0F128301},    // 700041AE 
{0x0F122196},    // 700041B0 
{0x0F128381},    // 700041B2 
{0x0F12211D},    // 700041B4 
{0x0F123020},    // 700041B6 
{0x0F128001},    // 700041B8 
{0x0F12F000},    // 700041BA 
{0x0F12F931},    // 700041BC 
{0x0F12F000},    // 700041BE 
{0x0F12F937},    // 700041C0 
{0x0F12483A},    // 700041C2 
{0x0F124C3A},    // 700041C4 
{0x0F126E00},    // 700041C6 
{0x0F1260E0},    // 700041C8 
{0x0F12466B},    // 700041CA 
{0x0F128818},    // 700041CC 
{0x0F128859},    // 700041CE 
{0x0F120025},    // 700041D0 
{0x0F121A40},    // 700041D2 
{0x0F123540},    // 700041D4 
{0x0F1261A8},    // 700041D6 
{0x0F124831},    // 700041D8 
{0x0F129900},    // 700041DA 
{0x0F123060},    // 700041DC 
{0x0F12F000},    // 700041DE 
{0x0F12F92F},    // 700041E0 
{0x0F12466B},    // 700041E2 
{0x0F128819},    // 700041E4 
{0x0F121DE0},    // 700041E6 
{0x0F1230F9},    // 700041E8 
{0x0F128741},    // 700041EA 
{0x0F128859},    // 700041EC 
{0x0F128781},    // 700041EE 
{0x0F122000},    // 700041F0 
{0x0F1271A0},    // 700041F2 
{0x0F1274A8},    // 700041F4 
{0x0F12BC7C},    // 700041F6 
{0x0F12BC08},    // 700041F8 
{0x0F124718},    // 700041FA 
{0x0F12B5F8},    // 700041FC 
{0x0F120005},    // 700041FE 
{0x0F126808},    // 70004200 
{0x0F120400},    // 70004202 
{0x0F120C00},    // 70004204 
{0x0F12684A},    // 70004206 
{0x0F120412},    // 70004208 
{0x0F120C12},    // 7000420A 
{0x0F12688E},    // 7000420C 
{0x0F1268CC},    // 7000420E 
{0x0F124922},    // 70004210 
{0x0F12884B},    // 70004212 
{0x0F124343},    // 70004214 
{0x0F120A98},    // 70004216 
{0x0F122304},    // 70004218 
{0x0F125ECB},    // 7000421A 
{0x0F1218C0},    // 7000421C 
{0x0F1202C0},    // 7000421E 
{0x0F120C00},    // 70004220 
{0x0F1288CB},    // 70004222 
{0x0F124353},    // 70004224 
{0x0F120A9A},    // 70004226 
{0x0F122308},    // 70004228 
{0x0F125ECB},    // 7000422A 
{0x0F1218D1},    // 7000422C 
{0x0F1202C9},    // 7000422E 
{0x0F120C09},    // 70004230 
{0x0F122701},    // 70004232 
{0x0F12003A},    // 70004234 
{0x0F1240AA},    // 70004236 
{0x0F129200},    // 70004238 
{0x0F12002A},    // 7000423A 
{0x0F123A10},    // 7000423C 
{0x0F124097},    // 7000423E 
{0x0F122D10},    // 70004240 
{0x0F12DA06},    // 70004242 
{0x0F124A1B},    // 70004244 
{0x0F129B00},    // 70004246 
{0x0F128812},    // 70004248 
{0x0F12439A},    // 7000424A 
{0x0F124B19},    // 7000424C 
{0x0F12801A},    // 7000424E 
{0x0F12E003},    // 70004250 
{0x0F124B18},    // 70004252 
{0x0F12885A},    // 70004254 
{0x0F1243BA},    // 70004256 
{0x0F12805A},    // 70004258 
{0x0F120023},    // 7000425A 
{0x0F120032},    // 7000425C 
{0x0F12F000},    // 7000425E 
{0x0F12F8D7},    // 70004260 
{0x0F122D10},    // 70004262 
{0x0F12DA05},    // 70004264 
{0x0F124913},    // 70004266 
{0x0F129A00},    // 70004268 
{0x0F128808},    // 7000426A 
{0x0F124310},    // 7000426C 
{0x0F128008},    // 7000426E 
{0x0F12E003},    // 70004270 
{0x0F124810},    // 70004272 
{0x0F128841},    // 70004274 
{0x0F124339},    // 70004276 
{0x0F128041},    // 70004278 
{0x0F124D0D},    // 7000427A 
{0x0F122000},    // 7000427C 
{0x0F123580},    // 7000427E 
{0x0F1288AA},    // 70004280 
{0x0F125E30},    // 70004282 
{0x0F122100},    // 70004284 
{0x0F12F000},    // 70004286 
{0x0F12F8E3},    // 70004288 
{0x0F128030},    // 7000428A 
{0x0F122000},    // 7000428C 
{0x0F1288AA},    // 7000428E 
{0x0F125E20},    // 70004290 
{0x0F122100},    // 70004292 
{0x0F12F000},    // 70004294 
{0x0F12F8DC},    // 70004296 
{0x0F128020},    // 70004298 
{0x0F12E587},    // 7000429A 
{0x0F122558},    // 7000429C 
{0x0F127000},    // 7000429E 
{0x0F122AB8},    // 700042A0 
{0x0F127000},    // 700042A2 
{0x0F12145E},    // 700042A4 
{0x0F127000},    // 700042A6 
{0x0F122698},    // 700042A8 
{0x0F127000},    // 700042AA 
{0x0F122BB8},    // 700042AC 
{0x0F127000},    // 700042AE 
{0x0F122998},    // 700042B0 
{0x0F127000},    // 700042B2 
{0x0F121100},    // 700042B4 
{0x0F12D000},    // 700042B6 
{0x0F124778},    // 700042B8 
{0x0F1246C0},    // 700042BA 
{0x0F12C000},    // 700042BC 
{0x0F12E59F},    // 700042BE 
{0x0F12FF1C},    // 700042C0 
{0x0F12E12F},    // 700042C2 
{0x0F121789},    // 700042C4 
{0x0F120001},    // 700042C6 
{0x0F124778},    // 700042C8 
{0x0F1246C0},    // 700042CA 
{0x0F12C000},    // 700042CC 
{0x0F12E59F},    // 700042CE 
{0x0F12FF1C},    // 700042D0 
{0x0F12E12F},    // 700042D2 
{0x0F1216F1},    // 700042D4 
{0x0F120001},    // 700042D6 
{0x0F124778},    // 700042D8 
{0x0F1246C0},    // 700042DA 
{0x0F12C000},    // 700042DC 
{0x0F12E59F},    // 700042DE 
{0x0F12FF1C},    // 700042E0 
{0x0F12E12F},    // 700042E2 
{0x0F12C3B1},    // 700042E4 
{0x0F120000},    // 700042E6 
{0x0F124778},    // 700042E8 
{0x0F1246C0},    // 700042EA 
{0x0F12C000},    // 700042EC 
{0x0F12E59F},    // 700042EE 
{0x0F12FF1C},    // 700042F0 
{0x0F12E12F},    // 700042F2 
{0x0F12C36D},    // 700042F4 
{0x0F120000},    // 700042F6 
{0x0F124778},    // 700042F8 
{0x0F1246C0},    // 700042FA 
{0x0F12C000},    // 700042FC 
{0x0F12E59F},    // 700042FE 
{0x0F12FF1C},    // 70004300 
{0x0F12E12F},    // 70004302 
{0x0F12F6D7},    // 70004304 
{0x0F120000},    // 70004306 
{0x0F124778},    // 70004308 
{0x0F1246C0},    // 7000430A 
{0x0F12C000},    // 7000430C 
{0x0F12E59F},    // 7000430E 
{0x0F12FF1C},    // 70004310 
{0x0F12E12F},    // 70004312 
{0x0F12B49D},    // 70004314 
{0x0F120000},    // 70004316 
{0x0F124778},    // 70004318 
{0x0F1246C0},    // 7000431A 
{0x0F12C000},    // 7000431C 
{0x0F12E59F},    // 7000431E 
{0x0F12FF1C},    // 70004320 
{0x0F12E12F},    // 70004322 
{0x0F127EDF},    // 70004324 
{0x0F120000},    // 70004326 
{0x0F124778},    // 70004328 
{0x0F1246C0},    // 7000432A 
{0x0F12C000},    // 7000432C 
{0x0F12E59F},    // 7000432E 
{0x0F12FF1C},    // 70004330 
{0x0F12E12F},    // 70004332 
{0x0F12448D},    // 70004334 
{0x0F120000},    // 70004336 
{0x0F124778},    // 70004338 
{0x0F1246C0},    // 7000433A 
{0x0F12F004},    // 7000433C 
{0x0F12E51F},    // 7000433E 
{0x0F1229EC},    // 70004340 
{0x0F120001},    // 70004342 
{0x0F124778},    // 70004344 
{0x0F1246C0},    // 70004346 
{0x0F12C000},    // 70004348 
{0x0F12E59F},    // 7000434A 
{0x0F12FF1C},    // 7000434C 
{0x0F12E12F},    // 7000434E 
{0x0F122EF1},    // 70004350 
{0x0F120000},    // 70004352 
{0x0F124778},    // 70004354 
{0x0F1246C0},    // 70004356 
{0x0F12C000},    // 70004358 
{0x0F12E59F},    // 7000435A 
{0x0F12FF1C},    // 7000435C 
{0x0F12E12F},    // 7000435E 
{0x0F12EE03},    // 70004360 
{0x0F120000},    // 70004362 
{0x0F124778},    // 70004364 
{0x0F1246C0},    // 70004366 
{0x0F12C000},    // 70004368 
{0x0F12E59F},    // 7000436A 
{0x0F12FF1C},    // 7000436C 
{0x0F12E12F},    // 7000436E 
{0x0F12A58B},    // 70004370 
{0x0F120000},    // 70004372 
{0x0F124778},    // 70004374 
{0x0F1246C0},    // 70004376 
{0x0F12C000},    // 70004378 
{0x0F12E59F},    // 7000437A 
{0x0F12FF1C},    // 7000437C 
{0x0F12E12F},    // 7000437E 
{0x0F127C49},    // 70004380 
{0x0F120000},    // 70004382 
{0x0F124778},    // 70004384 
{0x0F1246C0},    // 70004386 
{0x0F12C000},    // 70004388 
{0x0F12E59F},    // 7000438A 
{0x0F12FF1C},    // 7000438C 
{0x0F12E12F},    // 7000438E 
{0x0F127C63},    // 70004390 
{0x0F120000},    // 70004392 
{0x0F124778},    // 70004394 
{0x0F1246C0},    // 70004396 
{0x0F12C000},    // 70004398 
{0x0F12E59F},    // 7000439A 
{0x0F12FF1C},    // 7000439C 
{0x0F12E12F},    // 7000439E 
{0x0F122DB7},    // 700043A0 
{0x0F120000},    // 700043A2 
{0x0F124778},    // 700043A4 
{0x0F1246C0},    // 700043A6 
{0x0F12C000},    // 700043A8 
{0x0F12E59F},    // 700043AA 
{0x0F12FF1C},    // 700043AC 
{0x0F12E12F},    // 700043AE 
{0x0F12EB3D},    // 700043B0 
{0x0F120000},    // 700043B2 
{0x0F124778},    // 700043B4 
{0x0F1246C0},    // 700043B6 
{0x0F12C000},    // 700043B8 
{0x0F12E59F},    // 700043BA 
{0x0F12FF1C},    // 700043BC 
{0x0F12E12F},    // 700043BE 
{0x0F12F061},    // 700043C0 
{0x0F120000},    // 700043C2 
{0x0F124778},    // 700043C4 
{0x0F1246C0},    // 700043C6 
{0x0F12C000},    // 700043C8 
{0x0F12E59F},    // 700043CA 
{0x0F12FF1C},    // 700043CC 
{0x0F12E12F},    // 700043CE 
{0x0F12F0EF},    // 700043D0 
{0x0F120000},    // 700043D2 
{0x0F124778},    // 700043D4 
{0x0F1246C0},    // 700043D6 
{0x0F12F004},    // 700043D8 
{0x0F12E51F},    // 700043DA 
{0x0F122824},    // 700043DC 
{0x0F120001},    // 700043DE 
{0x0F124778},    // 700043E0 
{0x0F1246C0},    // 700043E2 
{0x0F12C000},    // 700043E4 
{0x0F12E59F},    // 700043E6 
{0x0F12FF1C},    // 700043E8 
{0x0F12E12F},    // 700043EA 
{0x0F128EDD},    // 700043EC 
{0x0F120000},    // 700043EE 
{0x0F124778},    // 700043F0 
{0x0F1246C0},    // 700043F2 
{0x0F12C000},    // 700043F4 
{0x0F12E59F},    // 700043F6 
{0x0F12FF1C},    // 700043F8 
{0x0F12E12F},    // 700043FA 
{0x0F128DCB},    // 700043FC 
{0x0F120000},    // 700043FE 
{0x0F124778},    // 70004400 
{0x0F1246C0},    // 70004402 
{0x0F12C000},    // 70004404 
{0x0F12E59F},    // 70004406 
{0x0F12FF1C},    // 70004408 
{0x0F12E12F},    // 7000440A 
{0x0F128E17},    // 7000440C 
{0x0F120000},    // 7000440E 
{0x0F124778},    // 70004410 
{0x0F1246C0},    // 70004412 
{0x0F12C000},    // 70004414 
{0x0F12E59F},    // 70004416 
{0x0F12FF1C},    // 70004418 
{0x0F12E12F},    // 7000441A 
{0x0F1298C5},    // 7000441C 
{0x0F120000},    // 7000441E 
{0x0F124778},    // 70004420 
{0x0F1246C0},    // 70004422 
{0x0F12C000},    // 70004424 
{0x0F12E59F},    // 70004426 
{0x0F12FF1C},    // 70004428 
{0x0F12E12F},    // 7000442A 
{0x0F127C7D},    // 7000442C 
{0x0F120000},    // 7000442E 
{0x0F124778},    // 70004430 
{0x0F1246C0},    // 70004432 
{0x0F12C000},    // 70004434 
{0x0F12E59F},    // 70004436 
{0x0F12FF1C},    // 70004438 
{0x0F12E12F},    // 7000443A 
{0x0F127E31},    // 7000443C 
{0x0F120000},    // 7000443E 
{0x0F124778},    // 70004440 
{0x0F1246C0},    // 70004442 
{0x0F12C000},    // 70004444 
{0x0F12E59F},    // 70004446 
{0x0F12FF1C},    // 70004448 
{0x0F12E12F},    // 7000444A 
{0x0F127EAB},    // 7000444C 
{0x0F120000},    // 7000444E 
{0x0F124778},    // 70004450 
{0x0F1246C0},    // 70004452 
{0x0F12C000},    // 70004454 
{0x0F12E59F},    // 70004456 
{0x0F12FF1C},    // 70004458 
{0x0F12E12F},    // 7000445A 
{0x0F127501},    // 7000445C 
{0x0F120000},    // 7000445E 
// End of Patch Data(Last : 7000445Eh)
// Total Size 2408 (0x0968)
// Addr : 3AF8 , Size : 2406(966h) 
                                                        
//TNP_USER_MBCV_CONTROL
//TNP_4EC_MBR_TUNE
//TNP_4EC_FORBIDDEN_TUNE
//TNP_AF_FINESEARCH_DRIVEBACK
//TNP_FLASH_ALG
//TNP_GAS_ALPHA_OTP
//TNP_AWB_MODUL_COMP
//TNP_AWB_INIT_QUEUE
//TNP_AWB_GRID_LOWBR
//TNP_AWB_GRID_MODULECOMP

{0x0028D000},
{0x002A1000},
{0x0F120001},

////////*************************************************************/////////
//AF setting																																//
////////*************************************************************/////////
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

////////*************************************************************/////////
//GAS TABLE setting																													//
////////*************************************************************/////////
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

{0x0F124500},	//	#TVAR_ash_GASAlpha_6__0_//R//7500K  //
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__1_//GR        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__2_//GB        //
{0x0F124000},	//	#TVAR_ash_GASAlpha_6__3_//B         //

{0x0F124800},	//	#TVAR_ash_GASOutdoorAlpha_0_   //R//Outdoor	//
{0x0F124200},	//	#TVAR_ash_GASOutdoorAlpha_1_   //GR        	//
{0x0F124000},	//	#TVAR_ash_GASOutdoorAlpha_2_   //GB        	//
{0x0F124000},	//	#TVAR_ash_GASOutdoorAlpha_3_   //B         	//

{0x002A08F4},
{0x0F120001}, //	#ash_bUseGasAlpha	//

//	GAS High table	 If OTP is used, GAS Setting Should be deleted.	//

////////*************************************************************/////////
//AE setting																																//
////////*************************************************************/////////
//	AE WEIGHT	//
{0x002A1492},
{0x0F120100},	//	#ae_WeightTbl_16    	//
{0x0F120101},	//	#ae_WeightTbl_16_1_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_2_ 	//
{0x0F120001},	//	#ae_WeightTbl_16_3_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_4_ 	//
{0x0F120201},	//	#ae_WeightTbl_16_5_ 	//
{0x0F120102},	//	#ae_WeightTbl_16_6_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_7_ 	//
{0x0F120101},	//	#ae_WeightTbl_16_8_ 	//
{0x0F120202},	//	#ae_WeightTbl_16_9_ 	//
{0x0F120202},	//	#ae_WeightTbl_16_10_	//
{0x0F120101},	//	#ae_WeightTbl_16_11_	//
{0x0F120201},	//	#ae_WeightTbl_16_12_	//
{0x0F120302},	//	#ae_WeightTbl_16_13_	//
{0x0F120203},	//	#ae_WeightTbl_16_14_	//
{0x0F120102},	//	#ae_WeightTbl_16_15_	//
{0x0F120201},	//	#ae_WeightTbl_16_16_	//
{0x0F120302},	//	#ae_WeightTbl_16_17_	//
{0x0F120203},	//	#ae_WeightTbl_16_18_	//
{0x0F120102},	//	#ae_WeightTbl_16_19_	//
{0x0F120101},	//	#ae_WeightTbl_16_20_	//
{0x0F120202},	//	#ae_WeightTbl_16_21_	//
{0x0F120202},	//	#ae_WeightTbl_16_22_	//
{0x0F120101},	//	#ae_WeightTbl_16_23_	//
{0x0F120101},	//	#ae_WeightTbl_16_24_	//
{0x0F120201},	//	#ae_WeightTbl_16_25_	//
{0x0F120102},	//	#ae_WeightTbl_16_26_	//
{0x0F120101},	//	#ae_WeightTbl_16_27_	//
{0x0F120101},	//	#ae_WeightTbl_16_28_	//
{0x0F120101},	//	#ae_WeightTbl_16_29_	//
{0x0F120101},	//	#ae_WeightTbl_16_30_	//
{0x0F120101},	//	#ae_WeightTbl_16_31_	//

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

//Flicker Setting //
{0x002A0F2A},
{0x0F120000},	//	#AFC_Default60Hz	0 : Auto 50Hz, 1 : Auto 60Hz//
{0x002A04E6},
{0x0F12077F}, //Auto bit Flicker Auto on [5]bit ex) AE/AWB Flicker etc..//

{0x002A0F30},
{0x0F120001},	//	#AFC_D_ConvAccelerPower // Flicker speed up : high


{0x002A0588},          //#lt_uInitPostToleranceCnt//
{0x0F120000},          //AE Speed-up//

{0x002A0600},          //#lt_uleiInit ae start//
{0x0F12D000},

{0x002A0608},
{0x0F120001},	//	#lt_ExpGain_uSubsamplingmode	//
{0x0F120001},	//	#lt_ExpGain_uNonSubsampling	//
{0x0F120c00},	//	#lt_ExpGain_ExpCurveGainMaxStr	//
{0x0F120100},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__uMaxDigGain	//
{0x0F120001},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_0_ 	//
{0x0F120A3C},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_1_ 	//
{0x0F120D04},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_2_ 	//
{0x0F124008},
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_3_ 	//
{0x0F127000},   //700Lux
{0x0F120000},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_4_ 	//
{0x0F129C00},   //400Lux
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
{0x0F123408},	// 3408(hex) -> 13320(dec) /400 -> 33.33ms //
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
{0x0F12000C},	//	#lt_uMaxLei same brightness between preview and capture.	//

{0x002A05D0},
{0x0F120000},	//	#lt_mbr_Peak_behind	//

////////*************************************************************/////////
//AWB setting																																//
////////*************************************************************/////////
//	AWB White Locus	should be	in front of REG_TC_IPRM_InitParamsUpdated	//
//	White Locus	//

	// AWB init Start point //
{0x002A145E},
{0x0F120580}, // 0400 //
{0x0F120428}, // 0428 //
{0x0F120780}, // 9B3  //

	// AWB Init //
	//White Locus //
{0x002A11F0},
{0x0F12012C},     //#awbb_IntcR//
{0x0F120121},     //#awbb_IntcB//

	// IndoorZone//
{0x002A101C},
{0x0F120360},
{0x0F12036C},
{0x0F120320},
{0x0F12038A},
{0x0F1202E8},
{0x0F120380},
{0x0F1202BE},
{0x0F12035A},
{0x0F120298},
{0x0F120334},
{0x0F120272},
{0x0F12030E},
{0x0F12024C},
{0x0F1202EA},
{0x0F120230},
{0x0F1202CC},
{0x0F120214},
{0x0F1202B0},
{0x0F1201F8},
{0x0F120294},
{0x0F1201DC},
{0x0F120278},
{0x0F1201C0},
{0x0F120264},
{0x0F1201AA},
{0x0F120250},
{0x0F120196},
{0x0F12023C},
{0x0F120180},
{0x0F120228},
{0x0F12016C},
{0x0F120214},
{0x0F120168},
{0x0F120200},
{0x0F120172},
{0x0F1201EC},
{0x0F12019A},
{0x0F1201D8},
{0x0F120000},
{0x0F120000},

{0x0F120005},     //#awbb_IndoorGrZones_m_GridStep//
{0x002A1070},
{0x0F120013},     //#awbb_IndoorGrZones_ZInfo_m_GridSz//
{0x002A1074},
{0x0F1200EC},     //#awbb_IndoorGrZones_m_Boffs//

	//Outdoor Zone//
{0x002A1078},
{0x0F120232},
{0x0F12025A},
{0x0F12021E},
{0x0F120274},
{0x0F12020E},
{0x0F12028E},
{0x0F120200},
{0x0F120290},
{0x0F1201F4},
{0x0F120286},
{0x0F1201E8},
{0x0F12027E},
{0x0F1201DE},
{0x0F120274},
{0x0F1201D2},
{0x0F120268},
{0x0F1201D0},
{0x0F12025E},
{0x0F1201D6},
{0x0F120252},
{0x0F1201E2},
{0x0F120248},
{0x0F1201F4},
{0x0F12021A},
           
{0x0F120004},     //#awbb_OutdoorGrZones_m_GridStep//
{0x002A10AC},
{0x0F12000C},     //#awbb_OutdoorGrZones_ZInfo_m_GridSz//
{0x002A10B0},
{0x0F1201DA},     //#awbb_OutdoorGrZones_m_Boffs//

	//LowBR Zone//
{0x002A10B4},
{0x0F120348},
{0x0F1203B6},
{0x0F1202B8},
{0x0F1203B6},
{0x0F120258},
{0x0F12038E},
{0x0F120212},
{0x0F120348},
{0x0F1201CC},
{0x0F12030C},
{0x0F1201A2},
{0x0F1202D2},
{0x0F120170},
{0x0F1202A6},
{0x0F12014C},
{0x0F120280},
{0x0F120128},
{0x0F12025C},
{0x0F120146},
{0x0F120236},
{0x0F120164},
{0x0F120212},
{0x0F120000},
{0x0F120000},

{0x0F120006},     //#awbb_LowBrGrZones_m_GridStep//
{0x002A10E8},
{0x0F12000B},     //#awbb_LowBrGrZones_ZInfo_m_GridSz//
{0x002A10EC},
{0x0F1200D2},     //#awbb_LowBrGrZones_m_Boffs//

	//LowTemp Zone//
{0x002A10F0},
{0x0F12039A},
{0x0F120000},     //#awbb_CrclLowT_R_c//
{0x0F1200FE},
{0x0F120000},     //#awbb_CrclLowT_B_c//
{0x0F122284},
{0x0F120000},     //#awbb_CrclLowT_Rad_c//

	//AWB Convergence Speed//
{0x002A1464},
{0x0F120008},
{0x0F120190},
{0x0F1200A0},

{0x002A120A},
{0x0F120540},     //#awbb_MvEq_RBthresh//
{0x002A120E},
{0x0F120000},

{0x0F1205FD},
{0x0F12036B},
{0x0F120020},
{0x0F12001A},

{0x002A1278},
{0x0F12FEF7},
{0x0F120021},
{0x0F1207D0},		//sunny NB//
{0x0F1207D0},		//Cloudy NB //
{0x0F1201C8},
{0x0F120096},
{0x0F120004},
{0x002A1224},
{0x0F120032},
{0x0F12001E},
{0x0F1200E2},
{0x0F120010},
{0x0F120002},     //awbb_YThreshLow_Low //
{0x002A2BA4},
{0x0F120002},     //#Mon_AWB_ByPassMode//

{0x002A146C},
{0x0F120002},     //#awbb_GridEnable//

	//Grid//
{0x002A1434},
{0x0F1202C1},     // awbb_GridConst_1	//
{0x0F12033A},     // awbb_GridConst_1_1_  //
{0x0F12038A},     // awbb_GridConst_1_2_  //
{0x0F12101A},     // awbb_GridConst_2     //
{0x0F121075},     // awbb_GridConst_2_1_  //
{0x0F12113D},     // awbb_GridConst_2_2_  //
{0x0F12113F},     // awbb_GridConst_2_3_  //
{0x0F1211AF},     // awbb_GridConst_2_4_  //
{0x0F1211F0},     // awbb_GridConst_2_5_  //
{0x0F1200B2},     // awbb_GridCoeff_R_1   //
{0x0F1200B8},     // awbb_GridCoeff_B_1   //
{0x0F1200CA},     // awbb_GridCoeff_R_2   //
{0x0F12009D},     // awbb_GridCoeff_B_2   //

	//Indoor Grid Offset//
{0x002A13A4},
{0x0F12FFE0},
{0x0F12FFE0},
{0x0F12FFE0},
{0x0F12FFA0},
{0x0F12FFEE},
{0x0F120096},
{0x0F12FFE0},
{0x0F12FFE0},
{0x0F12FFE0},
{0x0F12FFA0},
{0x0F12FFEE},
{0x0F120096},
{0x0F12FFE0},
{0x0F12FFE0},
{0x0F12FFE0},
{0x0F12FFA0},
{0x0F12FFEE},
{0x0F120096},
{0x0F12FFC0},
{0x0F12FFC0},
{0x0F12FFC0},
{0x0F12FF38},
{0x0F12FEF2},
{0x0F12FE5C},
{0x0F12FFC0},
{0x0F12FFC0},
{0x0F12FFC0},
{0x0F12FF38},
{0x0F12FEF2},
{0x0F12FE5C},
{0x0F12FFC0},
{0x0F12FFC0},
{0x0F12FFC0},
{0x0F12FF38},
{0x0F12FEF2},
{0x0F12FE5C},

	//Outdoor Grid Offset//
{0x0F12FFC0},	//R1
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F120000},
{0x0F120000},
           
{0x0F12FFC0},	//R2
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F120000},
{0x0F120000},
           
{0x0F12FFC0},	//R3
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F120000},
{0x0F120000},
           
{0x0F120010},	//B1
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F120000},
{0x0F120000},
           
{0x0F120010},	//B2
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F120000},
{0x0F120000},
           
{0x0F120010},	//B3
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F12FFD0},
{0x0F120000},
{0x0F120000},

{0x002A1208},
{0x0F120020},

{0x002A144E},
{0x0F120000},     //#awbb_RGainOff//
{0x0F120000},     //#awbb_BGainOff//
{0x0F120000},     //#awbb_GGainOff//

////////*************************************************************/////////
//Gamma indoor setting																											//
////////*************************************************************/////////
{0x002A0734},
{0x0F120001},	//	#SARR_usGammaLutRGBIndoor_0__0_  	//
{0x0F120003},	//	#SARR_usGammaLutRGBIndoor_0__1_   //
{0x0F12000F},	//	#SARR_usGammaLutRGBIndoor_0__2_   //
{0x0F12002B},	//	#SARR_usGammaLutRGBIndoor_0__3_   //
{0x0F120069},	//	#SARR_usGammaLutRGBIndoor_0__4_   //
{0x0F1200D9},	//	#SARR_usGammaLutRGBIndoor_0__5_   //
{0x0F120138},	//	#SARR_usGammaLutRGBIndoor_0__6_   //
{0x0F120163},	//	#SARR_usGammaLutRGBIndoor_0__7_   //
{0x0F120189},	//	#SARR_usGammaLutRGBIndoor_0__8_   //
{0x0F1201C6},	//	#SARR_usGammaLutRGBIndoor_0__9_   //
{0x0F1201F8},	//	#SARR_usGammaLutRGBIndoor_0__10_  //
{0x0F120222},	//	#SARR_usGammaLutRGBIndoor_0__11_  //
{0x0F120249},	//	#SARR_usGammaLutRGBIndoor_0__12_  //
{0x0F12028D},	//	#SARR_usGammaLutRGBIndoor_0__13_  //
{0x0F1202C9},	//	#SARR_usGammaLutRGBIndoor_0__14_  //
{0x0F120327},	//	#SARR_usGammaLutRGBIndoor_0__15_  //
{0x0F120371},	//	#SARR_usGammaLutRGBIndoor_0__16_  //
{0x0F1203AC},	//	#SARR_usGammaLutRGBIndoor_0__17_  //
{0x0F1203DD},	//	#SARR_usGammaLutRGBIndoor_0__18_  //
{0x0F1203FF},	//	#SARR_usGammaLutRGBIndoor_0__19_  //
{0x0F120001},	//	#SARR_usGammaLutRGBIndoor_1__0_   //
{0x0F120003},	//	#SARR_usGammaLutRGBIndoor_1__1_   //
{0x0F12000F},	//	#SARR_usGammaLutRGBIndoor_1__2_   //
{0x0F12002B},	//	#SARR_usGammaLutRGBIndoor_1__3_   //
{0x0F120069},	//	#SARR_usGammaLutRGBIndoor_1__4_   //
{0x0F1200D9},	//	#SARR_usGammaLutRGBIndoor_1__5_   //
{0x0F120138},	//	#SARR_usGammaLutRGBIndoor_1__6_   //
{0x0F120163},	//	#SARR_usGammaLutRGBIndoor_1__7_   //
{0x0F120189},	//	#SARR_usGammaLutRGBIndoor_1__8_   //
{0x0F1201C6},	//	#SARR_usGammaLutRGBIndoor_1__9_   //
{0x0F1201F8},	//	#SARR_usGammaLutRGBIndoor_1__10_  //
{0x0F120222},	//	#SARR_usGammaLutRGBIndoor_1__11_  //
{0x0F120249},	//	#SARR_usGammaLutRGBIndoor_1__12_  //
{0x0F12028D},	//	#SARR_usGammaLutRGBIndoor_1__13_  //
{0x0F1202C9},	//	#SARR_usGammaLutRGBIndoor_1__14_  //
{0x0F120327},	//	#SARR_usGammaLutRGBIndoor_1__15_  //
{0x0F120371},	//	#SARR_usGammaLutRGBIndoor_1__16_  //
{0x0F1203AC},	//	#SARR_usGammaLutRGBIndoor_1__17_  //
{0x0F1203DD},	//	#SARR_usGammaLutRGBIndoor_1__18_  //
{0x0F1203FF},	//	#SARR_usGammaLutRGBIndoor_1__19_  //
{0x0F120001},	//	#SARR_usGammaLutRGBIndoor_2__0_   //
{0x0F120003},	//	#SARR_usGammaLutRGBIndoor_2__1_   //
{0x0F12000F},	//	#SARR_usGammaLutRGBIndoor_2__2_   //
{0x0F12002B},	//	#SARR_usGammaLutRGBIndoor_2__3_   //
{0x0F120069},	//	#SARR_usGammaLutRGBIndoor_2__4_   //
{0x0F1200D9},	//	#SARR_usGammaLutRGBIndoor_2__5_   //
{0x0F120138},	//	#SARR_usGammaLutRGBIndoor_2__6_   //
{0x0F120163},	//	#SARR_usGammaLutRGBIndoor_2__7_   //
{0x0F120189},	//	#SARR_usGammaLutRGBIndoor_2__8_   //
{0x0F1201C6},	//	#SARR_usGammaLutRGBIndoor_2__9_   //
{0x0F1201F8},	//	#SARR_usGammaLutRGBIndoor_2__10_  //
{0x0F120222},	//	#SARR_usGammaLutRGBIndoor_2__11_  //
{0x0F120249},	//	#SARR_usGammaLutRGBIndoor_2__12_  //
{0x0F12028D},	//	#SARR_usGammaLutRGBIndoor_2__13_  //
{0x0F1202C9},	//	#SARR_usGammaLutRGBIndoor_2__14_  //
{0x0F120327},	//	#SARR_usGammaLutRGBIndoor_2__15_  //
{0x0F120371},	//	#SARR_usGammaLutRGBIndoor_2__16_  //
{0x0F1203AC},	//	#SARR_usGammaLutRGBIndoor_2__17_  //
{0x0F1203DD},	//	#SARR_usGammaLutRGBIndoor_2__18_  //
{0x0F1203FF},	//	#SARR_usGammaLutRGBIndoor_2__19_  //

////////*************************************************************/////////
//Gamma outdoor setting																											//
////////*************************************************************/////////
{0x0F120001},	//	#SARR_usGammaLutRGBOutdoor_0__0_ 		//
{0x0F12000B},	//	#SARR_usGammaLutRGBOutdoor_0__1_    //
{0x0F120019},	//	#SARR_usGammaLutRGBOutdoor_0__2_    //
{0x0F120036},	//	#SARR_usGammaLutRGBOutdoor_0__3_    //
{0x0F12006F},	//	#SARR_usGammaLutRGBOutdoor_0__4_    //
{0x0F1200D8},	//	#SARR_usGammaLutRGBOutdoor_0__5_    //
{0x0F120135},	//	#SARR_usGammaLutRGBOutdoor_0__6_    //
{0x0F12015F},	//	#SARR_usGammaLutRGBOutdoor_0__7_    //
{0x0F120185},	//	#SARR_usGammaLutRGBOutdoor_0__8_    //
{0x0F1201C1},	//	#SARR_usGammaLutRGBOutdoor_0__9_    //
{0x0F1201F3},	//	#SARR_usGammaLutRGBOutdoor_0__10_   //
{0x0F120220},	//	#SARR_usGammaLutRGBOutdoor_0__11_   //
{0x0F12024A},	//	#SARR_usGammaLutRGBOutdoor_0__12_   //
{0x0F120291},	//	#SARR_usGammaLutRGBOutdoor_0__13_   //
{0x0F1202D0},	//	#SARR_usGammaLutRGBOutdoor_0__14_   //
{0x0F12032A},	//	#SARR_usGammaLutRGBOutdoor_0__15_   //
{0x0F12036A},	//	#SARR_usGammaLutRGBOutdoor_0__16_   //
{0x0F12039F},	//	#SARR_usGammaLutRGBOutdoor_0__17_   //
{0x0F1203CC},	//	#SARR_usGammaLutRGBOutdoor_0__18_   //
{0x0F1203F9},	//	#SARR_usGammaLutRGBOutdoor_0__19_   //
{0x0F120001},	//	#SARR_usGammaLutRGBOutdoor_1__0_    //
{0x0F12000B},	//	#SARR_usGammaLutRGBOutdoor_1__1_    //
{0x0F120019},	//	#SARR_usGammaLutRGBOutdoor_1__2_    //
{0x0F120036},	//	#SARR_usGammaLutRGBOutdoor_1__3_    //
{0x0F12006F},	//	#SARR_usGammaLutRGBOutdoor_1__4_    //
{0x0F1200D8},	//	#SARR_usGammaLutRGBOutdoor_1__5_    //
{0x0F120135},	//	#SARR_usGammaLutRGBOutdoor_1__6_    //
{0x0F12015F},	//	#SARR_usGammaLutRGBOutdoor_1__7_    //
{0x0F120185},	//	#SARR_usGammaLutRGBOutdoor_1__8_    //
{0x0F1201C1},	//	#SARR_usGammaLutRGBOutdoor_1__9_    //
{0x0F1201F3},	//	#SARR_usGammaLutRGBOutdoor_1__10_   //
{0x0F120220},	//	#SARR_usGammaLutRGBOutdoor_1__11_   //
{0x0F12024A},	//	#SARR_usGammaLutRGBOutdoor_1__12_   //
{0x0F120291},	//	#SARR_usGammaLutRGBOutdoor_1__13_   //
{0x0F1202D0},	//	#SARR_usGammaLutRGBOutdoor_1__14_   //
{0x0F12032A},	//	#SARR_usGammaLutRGBOutdoor_1__15_   //
{0x0F12036A},	//	#SARR_usGammaLutRGBOutdoor_1__16_   //
{0x0F12039F},	//	#SARR_usGammaLutRGBOutdoor_1__17_   //
{0x0F1203CC},	//	#SARR_usGammaLutRGBOutdoor_1__18_   //
{0x0F1203F9},	//	#SARR_usGammaLutRGBOutdoor_1__19_   //
{0x0F120001},	//	#SARR_usGammaLutRGBOutdoor_2__0_    //
{0x0F12000B},	//	#SARR_usGammaLutRGBOutdoor_2__1_    //
{0x0F120019},	//	#SARR_usGammaLutRGBOutdoor_2__2_    //
{0x0F120036},	//	#SARR_usGammaLutRGBOutdoor_2__3_    //
{0x0F12006F},	//	#SARR_usGammaLutRGBOutdoor_2__4_    //
{0x0F1200D8},	//	#SARR_usGammaLutRGBOutdoor_2__5_    //
{0x0F120135},	//	#SARR_usGammaLutRGBOutdoor_2__6_    //
{0x0F12015F},	//	#SARR_usGammaLutRGBOutdoor_2__7_    //
{0x0F120185},	//	#SARR_usGammaLutRGBOutdoor_2__8_    //
{0x0F1201C1},	//	#SARR_usGammaLutRGBOutdoor_2__9_    //
{0x0F1201F3},	//	#SARR_usGammaLutRGBOutdoor_2__10_   //
{0x0F120220},	//	#SARR_usGammaLutRGBOutdoor_2__11_   //
{0x0F12024A},	//	#SARR_usGammaLutRGBOutdoor_2__12_   //
{0x0F120291},	//	#SARR_usGammaLutRGBOutdoor_2__13_   //
{0x0F1202D0},	//	#SARR_usGammaLutRGBOutdoor_2__14_   //
{0x0F12032A},	//	#SARR_usGammaLutRGBOutdoor_2__15_   //
{0x0F12036A},	//	#SARR_usGammaLutRGBOutdoor_2__16_   //
{0x0F12039F},	//	#SARR_usGammaLutRGBOutdoor_2__17_   //
{0x0F1203CC},	//	#SARR_usGammaLutRGBOutdoor_2__18_   //
{0x0F1203F9},	//	#SARR_usGammaLutRGBOutdoor_2__19_   //

////////*************************************************************/////////
//CCM setting																																//
////////*************************************************************/////////
{0x002A08A6},
{0x0F120050},	//	#SARR_AwbCcmCord   	//
{0x0F1200F0},	//	#SARR_AwbCcmCord_1_ //
{0x0F120110},	//	#SARR_AwbCcmCord_2_ //
{0x0F120120},	//	#SARR_AwbCcmCord_3_ //
{0x0F120130},	//	#SARR_AwbCcmCord_4_ //
{0x0F120162},	//	#SARR_AwbCcmCord_5_ //
           
{0x0F120001},	//	#wbt_bUseOutdoorCCM	//
           
{0x002A0898},
{0x0F124800},
{0x0F127000},	//	#TVAR_wbt_pBaseCcms	//
{0x002A08A0},
{0x0F1248D8},
{0x0F127000},	//	#TVAR_wbt_pOutdoorCcm	//
           
{0x002A4800},
{0x0F120119},	//	#TVAR_wbt_pBaseCcms[0]	     hor//
{0x0F12FFA9},	//	#TVAR_wbt_pBaseCcms[1]  	//
{0x0F12FF9D},	//	#TVAR_wbt_pBaseCcms[2]  	//
{0x0F12FF30},	//	#TVAR_wbt_pBaseCcms[3]  	//
{0x0F120130},	//	#TVAR_wbt_pBaseCcms[4]  	//
{0x0F12FF8E},	//	#TVAR_wbt_pBaseCcms[5]  	//
{0x0F12FFF8},	//	#TVAR_wbt_pBaseCcms[6]  	//
{0x0F12FFAC},	//	#TVAR_wbt_pBaseCcms[7]  	//
{0x0F120137},	//	#TVAR_wbt_pBaseCcms[8]  	//
{0x0F120087},	//	#TVAR_wbt_pBaseCcms[9]  	//
{0x0F1200D0},	//	#TVAR_wbt_pBaseCcms[10] 	//
{0x0F12FEE3},	//	#TVAR_wbt_pBaseCcms[11] 	//
{0x0F120162},	//	#TVAR_wbt_pBaseCcms[12] 	//
{0x0F12FF77},	//	#TVAR_wbt_pBaseCcms[13] 	//
{0x0F1200E8},	//	#TVAR_wbt_pBaseCcms[14] 	//
{0x0F12FF40},	//	#TVAR_wbt_pBaseCcms[15] 	//
{0x0F120114},	//	#TVAR_wbt_pBaseCcms[16] 	//
{0x0F1200F4},	//	#TVAR_wbt_pBaseCcms[17] 	//
{0x0F120119},	//	#TVAR_wbt_pBaseCcms[18]		incaA//
{0x0F12FFA9},	//	#TVAR_wbt_pBaseCcms[19] 	//
{0x0F12FF9D},	//	#TVAR_wbt_pBaseCcms[20] 	//
{0x0F12FF30},	//	#TVAR_wbt_pBaseCcms[21] 	//
{0x0F120130},	//	#TVAR_wbt_pBaseCcms[22] 	//
{0x0F12FF8E},	//	#TVAR_wbt_pBaseCcms[23] 	//
{0x0F12FFF8},	//	#TVAR_wbt_pBaseCcms[24] 	//
{0x0F12FFAC},	//	#TVAR_wbt_pBaseCcms[25] 	//
{0x0F120137},	//	#TVAR_wbt_pBaseCcms[26] 	//
{0x0F120087},	//	#TVAR_wbt_pBaseCcms[27] 	//
{0x0F1200D0},	//	#TVAR_wbt_pBaseCcms[28] 	//
{0x0F12FEE3},	//	#TVAR_wbt_pBaseCcms[29] 	//
{0x0F120162},	//	#TVAR_wbt_pBaseCcms[30] 	//
{0x0F12FF77},	//	#TVAR_wbt_pBaseCcms[31] 	//
{0x0F1200E8},	//	#TVAR_wbt_pBaseCcms[32] 	//
{0x0F12FF40},	//	#TVAR_wbt_pBaseCcms[33] 	//
{0x0F120114},	//	#TVAR_wbt_pBaseCcms[34] 	//
{0x0F1200F4},	//	#TVAR_wbt_pBaseCcms[35] 	//
{0x0F120204},	//	#TVAR_wbt_pBaseCcms[36]		WW//
{0x0F12FFB2},	//	#TVAR_wbt_pBaseCcms[37] 	//
{0x0F12FFF5},	//	#TVAR_wbt_pBaseCcms[38] 	//
{0x0F12FEE7},	//	#TVAR_wbt_pBaseCcms[39] 	//
{0x0F120161},	//	#TVAR_wbt_pBaseCcms[40] 	//
{0x0F12FF10},	//	#TVAR_wbt_pBaseCcms[41] 	//
{0x0F12FFDD},	//	#TVAR_wbt_pBaseCcms[42] 	//
{0x0F12FFE6},	//	#TVAR_wbt_pBaseCcms[43] 	//
{0x0F1201B2},	//	#TVAR_wbt_pBaseCcms[44] 	//
{0x0F1200F2},	//	#TVAR_wbt_pBaseCcms[45] 	//
{0x0F1200CA},	//	#TVAR_wbt_pBaseCcms[46] 	//
{0x0F12FF48},	//	#TVAR_wbt_pBaseCcms[47] 	//
{0x0F120151},	//	#TVAR_wbt_pBaseCcms[48] 	//
{0x0F12FF50},	//	#TVAR_wbt_pBaseCcms[49] 	//
{0x0F120147},	//	#TVAR_wbt_pBaseCcms[50] 	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[51] 	//
{0x0F1201BA},	//	#TVAR_wbt_pBaseCcms[52] 	//
{0x0F12018C},	//	#TVAR_wbt_pBaseCcms[53] 	//
{0x0F120204},	//	#TVAR_wbt_pBaseCcms[54]		CW//
{0x0F12FFB2},	//	#TVAR_wbt_pBaseCcms[55] 	//
{0x0F12FFF5},	//	#TVAR_wbt_pBaseCcms[56] 	//
{0x0F12FEF1},	//	#TVAR_wbt_pBaseCcms[57] 	//
{0x0F12014E},	//	#TVAR_wbt_pBaseCcms[58] 	//
{0x0F12FF18},	//	#TVAR_wbt_pBaseCcms[59] 	//
{0x0F12FFE6},	//	#TVAR_wbt_pBaseCcms[60] 	//
{0x0F12FFDD},	//	#TVAR_wbt_pBaseCcms[61] 	//
{0x0F1201B2},	//	#TVAR_wbt_pBaseCcms[62] 	//
{0x0F1200F2},	//	#TVAR_wbt_pBaseCcms[63] 	//
{0x0F1200CA},	//	#TVAR_wbt_pBaseCcms[64] 	//
{0x0F12FF48},	//	#TVAR_wbt_pBaseCcms[65] 	//
{0x0F120151},	//	#TVAR_wbt_pBaseCcms[66] 	//
{0x0F12FF50},	//	#TVAR_wbt_pBaseCcms[67] 	//
{0x0F120147},	//	#TVAR_wbt_pBaseCcms[68] 	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[69] 	//
{0x0F120187},	//	#TVAR_wbt_pBaseCcms[70] 	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[71] 	//
{0x0F120204},	//	#TVAR_wbt_pBaseCcms[72]		D50//
{0x0F12FFB2},	//	#TVAR_wbt_pBaseCcms[73] 	//
{0x0F12FFF5},	//	#TVAR_wbt_pBaseCcms[74] 	//
{0x0F12FEF1},	//	#TVAR_wbt_pBaseCcms[75] 	//
{0x0F12014E},	//	#TVAR_wbt_pBaseCcms[76] 	//
{0x0F12FF18},	//	#TVAR_wbt_pBaseCcms[77] 	//
{0x0F12FFE6},	//	#TVAR_wbt_pBaseCcms[78] 	//
{0x0F12FFDD},	//	#TVAR_wbt_pBaseCcms[79] 	//
{0x0F1201B2},	//	#TVAR_wbt_pBaseCcms[80] 	//
{0x0F1200F2},	//	#TVAR_wbt_pBaseCcms[81] 	//
{0x0F1200CA},	//	#TVAR_wbt_pBaseCcms[82] 	//
{0x0F12FF48},	//	#TVAR_wbt_pBaseCcms[83] 	//
{0x0F120151},	//	#TVAR_wbt_pBaseCcms[84] 	//
{0x0F12FF50},	//	#TVAR_wbt_pBaseCcms[85] 	//
{0x0F120147},	//	#TVAR_wbt_pBaseCcms[86] 	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[87] 	//
{0x0F120187},	//	#TVAR_wbt_pBaseCcms[88] 	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[89] 	//
{0x0F120204},	//	#TVAR_wbt_pBaseCcms[90]		D65//
{0x0F12FFB2},	//	#TVAR_wbt_pBaseCcms[91] 	//
{0x0F12FFF5},	//	#TVAR_wbt_pBaseCcms[92] 	//
{0x0F12FEF1},	//	#TVAR_wbt_pBaseCcms[93] 	//
{0x0F12014E},	//	#TVAR_wbt_pBaseCcms[94] 	//
{0x0F12FF18},	//	#TVAR_wbt_pBaseCcms[95] 	//
{0x0F12FFE6},	//	#TVAR_wbt_pBaseCcms[96] 	//
{0x0F12FFDD},	//	#TVAR_wbt_pBaseCcms[97] 	//
{0x0F1201B2},	//	#TVAR_wbt_pBaseCcms[98] 	//
{0x0F1200F2},	//	#TVAR_wbt_pBaseCcms[99] 	//
{0x0F1200CA},	//	#TVAR_wbt_pBaseCcms[100]	//
{0x0F12FF48},	//	#TVAR_wbt_pBaseCcms[101]	//
{0x0F120151},	//	#TVAR_wbt_pBaseCcms[102]	//
{0x0F12FF50},	//	#TVAR_wbt_pBaseCcms[103]	//
{0x0F120147},	//	#TVAR_wbt_pBaseCcms[104]	//
{0x0F12FF75},	//	#TVAR_wbt_pBaseCcms[105]	//
{0x0F120187},	//	#TVAR_wbt_pBaseCcms[106]	//
{0x0F1201BF},	//	#TVAR_wbt_pBaseCcms[107]	//
           
{0x0F1201E5},	//016E	//	#TVAR_wbt_pOutdoorCcm[0]  //
{0x0F12FFA4},	//FFB9	//	#TVAR_wbt_pOutdoorCcm[1]  //
{0x0F12FFDC},	//FFDB	//	#TVAR_wbt_pOutdoorCcm[2]  //
{0x0F12FE87},	//FF10	//	#TVAR_wbt_pOutdoorCcm[3]  //
{0x0F12013C},	//01D4	//	#TVAR_wbt_pOutdoorCcm[4]  //
{0x0F12FF2A},	//FFA4	//	#TVAR_wbt_pOutdoorCcm[5]  //
{0x0F12FFD2},	//FFDA	//	#TVAR_wbt_pOutdoorCcm[6]  //
{0x0F12FFDF},	//FFEF	//	#TVAR_wbt_pOutdoorCcm[7]  //
{0x0F120236},	//01C2	//	#TVAR_wbt_pOutdoorCcm[8]  //
{0x0F1200EC},	//00C6	//	#TVAR_wbt_pOutdoorCcm[9]  //
{0x0F1200F8},	//00C6	//	#TVAR_wbt_pOutdoorCcm[10] //
{0x0F12FF34},	//FF68	//	#TVAR_wbt_pOutdoorCcm[11] //
{0x0F1201CE},	//011A	//	#TVAR_wbt_pOutdoorCcm[12] //
{0x0F12FF83},	//FEFC	//	#TVAR_wbt_pOutdoorCcm[13] //
{0x0F120195},	//007C	//	#TVAR_wbt_pOutdoorCcm[14] //
{0x0F12FEF3},	//FEE3	//	#TVAR_wbt_pOutdoorCcm[15] //
{0x0F120126},	//011D	//	#TVAR_wbt_pOutdoorCcm[16] //
{0x0F120162},	//016C	//	#TVAR_wbt_pOutdoorCcm[17] //
////***0000******************************************************************/////
//System setting																														//
////*********************************************************************/////

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

////*********************************************************************/////
//ETC... setting																														//
////*********************************************************************/////
{0x002A0478},
{0x0F12005F},	//	#REG_TC_BRC_usPrevQuality			//
{0x0F12005F},	//	#REG_TC_BRC_usCaptureQuality  //
{0x0F120001},	//	#REG_TC_THUMB_Thumb_bActive   //
{0x0F120280},	//	#REG_TC_THUMB_Thumb_uWidth    //
{0x0F1201E0},	//	#REG_TC_THUMB_Thumb_uHeight   //
{0x0F120005},	//	#REG_TC_THUMB_Thumb_Format    //
{0x002A17DC},
{0x0F120054},	//54 44	#jpeg_ManualMBCV	//
{0x002A1AE4},
{0x0F12001C},	//	#senHal_bExtraAddLine	//
{0x002A0284},
{0x0F120001},	//	#REG_TC_GP_bBypassScalerJpg	//
{0x002A028A},	//	
{0x0F120000},	//	#REG_TC_GP_bUse1FrameCaptureMode 0:Continuous 1:Single frmae//

////*********************************************************************/////
//Configuration setting																											//
////*********************************************************************/////
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
{0x0F12014A},	//	#REG_0TC_PCFG_usMinFrTimeMsecMult10         //
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
{0x0F120002},	//	#REG_0TC_CCFG_PVIMask            //
{0x0F120070},	//	#REG_0TC_CCFG_OIFMask            //
{0x0F120810},	//	2064d     #REG_0TC_CCFG_usJpegPacketSize   //
{0x0F120900},	//	2304d    #REG_0TC_CCFG_usJpegTotalPackets //
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

////////*************************************************************/////////
//AFIT setting																															//
////////*************************************************************/////////

//	Mon_AFIT_uNoiseInd	//
{0x002A0944},
{0x0F120050},	//	#afit_uNoiseIndInDoor_0_  //
{0x0F1200B0},	//	#afit_uNoiseIndInDoor_1_  //
{0x0F120196},	//	#afit_uNoiseIndInDoor_2_  //
{0x0F120245},	//	#afit_uNoiseIndInDoor_3_  //
{0x0F120300},	//	#afit_uNoiseIndInDoor_4_	//

{0x002A097A},
{0x0F120000},	//	#afit_bUseSenBpr					//
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
{0x0F12005F},	//_postdmsc_iLowSat                                    //
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
{0x0F122000},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
{0x0F120000},	//_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit         //
{0x0F121E10},	//_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff     //
{0x0F12000B},	//_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0          //
{0x0F120607},	//_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2        //
{0x0F120005},	//_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0        //
{0x0F120607},	//_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2        //
{0x0F120705},	//_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY         //
{0x0F120206},	//_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm          //
{0x0F120304},	//_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm          //
{0x0F120309},	//_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift        //
{0x0F120305},	//_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y     //
{0x0F122006},	//_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y  //
{0x0F121320},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F121014},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121010},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120C10},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F121A0C},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F124A18},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120060},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
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
{0x0F122701},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F12241E},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F122E60},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF22},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1240FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120009},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
{0x0F120001},	//_bnr_nClustLevel_C      [0]                          //
{0x0F120000},	//_BRIGHTNESS	AFIT 1                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120051},	//_postdmsc_iLowSat                                    //
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
{0x0F121980},	//_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh        //
{0x0F12272E},	//_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh  //
{0x0F120629},	//_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed   //
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
{0x0F123828},	//_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen      //
{0x0F120425},	//_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh            //
{0x0F120101},	//_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative      //
{0x0F120800},	//_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle     //
{0x0F121004},	//_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh  //
{0x0F124008},	//_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh   //
{0x0F120540},	//_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange   //
{0x0F128006},	//_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad   //
{0x0F120020},	//_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal    //
{0x0F120000},	//_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh        //
{0x0F122000},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
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
{0x0F122204},	//_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV //
{0x0F12021C},	//_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y  //
{0x0F121102},	//_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV   //
{0x0F120611},	//_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL   //
{0x0F121A02},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
{0x0F128018},	//_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower   //
{0x0F120080},	//_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce       //
{0x0F120080},	//_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset//
{0x0F120180},	//_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H    //
{0x0F120A0A},	//_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C     //
{0x0F120101},	//_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C //
{0x0F12141D},	//_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh  //
{0x0F126024},	//_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower  //
{0x0F121217},	//_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise    //
{0x0F12FFFF},	//_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp  //
{0x0F120808},	//_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope        //
{0x0F120A01},	//_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin       //
{0x0F12010A},	//_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin      //
{0x0F120001},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F122400},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F121660},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF10},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1240FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120009},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
{0x0F120001},	//_bnr_nClustLevel_C      [0]                          //
{0x0F120000},	//_BRIGHTNESS	AFIT 2                                   //
{0x0F120000},	//_CONTRAST                                            //
{0x0F120000},	//_SATURATION                                          //
{0x0F120000},	//_SHARP_BLUR                                          //
{0x0F120000},	//_GLAMOUR                                             //
{0x0F1200C0},	//_bnr_edge_high                                       //
{0x0F120064},	//_postdmsc_iLowBright                                 //
{0x0F120384},	//_postdmsc_iHighBright                                //
{0x0F120043},	//_postdmsc_iLowSat                                    //
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
{0x0F122000},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
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
{0x0F121A02},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
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
{0x0F120001},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F122400},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F120460},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF04},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1240FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120009},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
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
{0x0F122000},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
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
{0x0F121A02},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
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
{0x0F120001},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F122400},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F120260},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF02},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1240FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120009},	//_ee_iReduceEdgeSlope_Bin [7:0]                       //
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
{0x0F122000},	//_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat //
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
{0x0F121A02},	//_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL   //
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
{0x0F120001},	//_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin     //
{0x0F122400},	//_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin     //
{0x0F120060},	//_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin      //
{0x0F12FF00},	//_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin      //
{0x0F1240FF},	//_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin //
{0x0F120009},	//_ee_iReduceEdgeSlope_Bin [7:0]							         //
{0x0F120001},	//_bnr_nClustLevel_C      [0]   bWideWide[1]           //
{0x0F1223CE},	//[0]CAFITB_bnr_bypass                                 //
{0x0F12FDC8},	//[0]CAFITB_bnr_bSlopenessTune                         //
{0x0F12112E},	//[0]CAFITB_ee_bReduceNegMedSh                         //
{0x0F1293A5},	//[0]CAFITB_dmsc_bDoDesat                              //
{0x0F12FE67},	//[0]CAFITB_postdmsc_bSat                              //
{0x0F120000},	//[0]CAFITB_yuviirnr_bWideY																				//


{0x002A0588},	//lt_uInitPostToleranceCnt//
{0x0F120002},	//AE Speed Normal//

};

s5k4ecgx_short_t s5k4ecgx_DTP_init_EVT1[] = {
{0xFCFCD000},
{0x0028D000},
{0x002AB054},
{0x0F120001}
};

s5k4ecgx_short_t s5k4ecgx_DTP_stop_EVT1[] = {
{0xFCFCD000},
{0x0028D000},
{0x002AB054},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_FPS_Auto_EVT1[] = {
{0xFCFCD000},
{0x00287000},	
{0x002A02B4},
{0x0F120052}, //decode//
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F12029A}, //fps min 29A = 0.0015 15fps
{0x0F12014A}, //fps Max 
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

s5k4ecgx_short_t s5k4ecgx_FPS_5_EVT1[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_7_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_FPS_10_EVT1[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_15_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_FPS_20_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_FPS_24_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_FPS_25_EVT1[] = {
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


s5k4ecgx_short_t s5k4ecgx_FPS_30_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F12014A},
{0x0F12014A},
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
s5k4ecgx_short_t s5k4ecgx_FPS_60_EVT1[] = {

};

s5k4ecgx_short_t s5k4ecgx_FPS_120_EVT1[] = {

};

s5k4ecgx_short_t s5k4ecgx_Effect_Normal_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120000}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Solarization_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120002}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Negative_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120003}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Sepia_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120004}
};

s5k4ecgx_short_t s5k4ecgx_Effect_Black_White_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A023C},
{0x0F120001}
};


s5k4ecgx_short_t s5k4ecgx_WB_Auto_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0f12077F
};

s5k4ecgx_short_t s5k4ecgx_WB_Sunny_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program{0x002A04E6},
//0x0f120777

{0x002A04BA},
{0x0f1205F0}, //R

{0x002A04BE},
{0x0f120400}, //G

{0x002A04C2},
{0x0f120588}, //B

{0x002A04C6},
{0x0f120001}
};

s5k4ecgx_short_t s5k4ecgx_WB_Cloudy_EVT1[] = {
{0xFCFCD000},
{0x00287000},	
//0x002a04E6 S/W Program
//0x0F120777

{0x002A04BA},
{0x0F120758}, //R	

{0x002A04BE},
{0x0F120400}, //G	

{0x002A04C2},
{0x0F1204E8}, //B	

{0x002A04C6},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_WB_Tungsten_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0F120777

{0x002A04BA},
{0x0F1203E0}, //R 90

{0x002A04BE},
{0x0F120400}, //G

{0x002A04C2},
{0x0F120988}, //B 20

{0x002A04C6},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_WB_Fluorescent_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0F120777
{0x002A04BA},
{0x0F1205A5}, //R

{0x002A04BE},
{0x0F120400}, //G

{0x002A04C2},
{0x0F1208A8}, //B

{0x002A04C6},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_WDR_on_EVT1[] = {
{0x00287000},
{0x002A1BEA},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_WDR_off_EVT1[] = {
{0x00287000},
{0x002A1BEA},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_ISO_Auto_EVT1[] = {
{0xFCFCD000},
{0x00287000},

//0x002A1484
//0x0F12003C	//	#TVAR_ae_BrAve // 

{0x002A0938},   //afit_bUseNB_Afit
{0x0F120000},    
{0x0F120014},   //SARR_uNormBrInDoor_0_
{0x0F1200D2},   //SARR_uNormBrInDoor_1_
{0x0F120384},   //SARR_uNormBrInDoor_2_
{0x0F1207D0},   //SARR_uNormBrInDoor_3_
{0x0F121388},   //SARR_uNormBrInDoor_4_
                
{0x002A0F2A},   //AFC_Default60Hz
{0x0F120000},   //00:50Hz 01:60Hz           
                
//0x002a04E6 S/W Program
//0x0F12077F
                
{0x002A04D0},   
{0x0F120000},   //REG_SF_USER_IsoType    
{0x0F120000},   //REG_SF_USER_IsoVal     
{0x0F120001},   //REG_SF_USER_IsoChanged 
{0x002A06C2},                            
{0x0F120200},   //lt_bUseSecISODgain  
};

s5k4ecgx_short_t s5k4ecgx_ISO_50_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0938},
{0x0F120001},   //afit_bUseNB_Afit
{0x0F120014},   //SARR_uNormBrInDoor_0_
{0x0F1200D2},   //SARR_uNormBrInDoor_1_
{0x0F120384},   //SARR_uNormBrInDoor_2_
{0x0F1207D0},   //SARR_uNormBrInDoor_3_
{0x0F121388},   //SARR_uNormBrInDoor_4_

//0x002a04E6 S/W Program
//0x0F12065F   //REG_TC_DBG_AutoAlgEnBits
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

s5k4ecgx_short_t s5k4ecgx_ISO_100_EVT1[] = {
{0xFCFCD000},
{0x00287000},

//0x002A1484
//0x0F120038	//	#TVAR_ae_BrAve //

{0x002A0938},
{0x0F120001},   //afit_bUseNB_Afit
{0x0F120014},   //SARR_uNormBrInDoor_0_
{0x0F1200D2},   //SARR_uNormBrInDoor_1_
{0x0F120384},   //SARR_uNormBrInDoor_2_
{0x0F1207D0},   //SARR_uNormBrInDoor_3_
{0x0F121388},   //SARR_uNormBrInDoor_4_
                
//0x002a04E6 S/W Program
//0x0F12065F   //REG_TC_DBG_AutoAlgEnBits  //MWB off老 版快 : 0x075F / MWB on老 版快 : 0x0757
{0x002A04D6},   
{0x0F120000},   //REG_SF_USER_FlickerQuant       
{0x0F120001},   //REG_SF_USER_FlickerQuantChanged
                
{0x002A04D0},   
{0x0F120001},   //REG_SF_USER_IsoType    
{0x0F1201C0},   //REG_SF_USER_IsoVal     
{0x0F120001},   //REG_SF_USER_IsoChanged 
{0x002A06C2},                            
{0x0F120100},   //lt_bUseSecISODgain   

};

s5k4ecgx_short_t s5k4ecgx_ISO_200_EVT1[] = {
{0xFCFCD000},
{0x00287000},

//0x002A1484
//0x0F120038	//	#TVAR_ae_BrAve //

{0x002A0938},
{0x0F120001},   //afit_bUseNB_Afit
{0x0F120014},   //SARR_uNormBrInDoor_0_
{0x0F1203A2},   //SARR_uNormBrInDoor_1_
{0x0F120484},   //SARR_uNormBrInDoor_2_
{0x0F1207D0},   //SARR_uNormBrInDoor_3_
{0x0F121388},   //SARR_uNormBrInDoor_4_
                
//0x002a04E6 S/W Program
//0x0F12065F   //REG_TC_DBG_AutoAlgEnBits  //MWB off老 版快 : 0x075F / MWB on老 版快 : 0x0757
{0x002A04D6},   
{0x0F120000},   //REG_SF_USER_FlickerQuant       
{0x0F120001},   //REG_SF_USER_FlickerQuantChanged
                
{0x002A04D0},   
{0x0F120001},   //REG_SF_USER_IsoType    
{0x0F120380},   //REG_SF_USER_IsoVal     
{0x0F120001},   //REG_SF_USER_IsoChanged 
{0x002A06C2},                            
{0x0F120100},   //lt_bUseSecISODgain  
};

s5k4ecgx_short_t s5k4ecgx_ISO_400_EVT1[]  = {
{0xFCFCD000},
{0x00287000},

//0x002A1484
//0x0F120038	//	#TVAR_ae_BrAve //

{0x002A0938},
{0x0F120001},   //afit_bUseNB_Afit
{0x0F120014},   //SARR_uNormBrInDoor_0_
{0x0F1208D2},   //SARR_uNormBrInDoor_1_
{0x0F120C84},   //SARR_uNormBrInDoor_2_
{0x0F1210D0},   //SARR_uNormBrInDoor_3_
{0x0F121388},   //SARR_uNormBrInDoor_4_
                
//0x002a04E6 S/W Program
//0x0F12065F   //REG_TC_DBG_AutoAlgEnBits
{0x002A04D6},   
{0x0F120000},   //REG_SF_USER_FlickerQuant       
{0x0F120001},   //REG_SF_USER_FlickerQuantChanged

{0x002A04D0},                                      
{0x0F120001},   //REG_SF_USER_IsoType              
{0x0F120700},   //REG_SF_USER_IsoVal               
{0x0F120001},   //REG_SF_USER_IsoChanged           
{0x002A06C2},                                      
{0x0F120100},   //lt_bUseSecISODgain               
};

s5k4ecgx_short_t s5k4ecgx_Metering_Matrix_EVT1[] = {
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

{0x002A0242},
{0x0F120000},
{0x002A024E},
{0x0F120001},
{0x002A0244},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Metering_Center_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1492},
{0x0F120100},
{0x0F120101},
{0x0F120101},
{0x0F120001},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120202},
{0x0F120202},
{0x0F120101},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120101},
{0x0F120202},
{0x0F120202},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},

{0x002A0242},
{0x0F120000},
{0x002A024E},
{0x0F120001},
{0x002A0244},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Metering_Spot_EVT1[] = {
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

{0x002A0242},
{0x0F120000},
{0x002A024E},
{0x0F120001},
{0x002A0244},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_4_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1482},
{0x0F120280},
{0x002A0230},
{0x0F12FF80},
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_3_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1482},
{0x0F120280},
{0x002A0230},
{0x0F12FFB8},
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_2_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1482},
{0x0F120280},
{0x002A0230},
{0x0F12FFD0},
};

s5k4ecgx_short_t s5k4ecgx_EV_Minus_1_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1482},
{0x0F120280},
{0x002A0230},
{0x0F12FFF0},
};

s5k4ecgx_short_t s5k4ecgx_EV_Default_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A147C},
{0x0F120180},
{0x002A1482},
{0x0F120180},
{0x002A0230},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_1_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A147C},
{0x0F1201A0},
{0x002A0230},
{0x0F120020},
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_2_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A147C},
{0x0F1201A0},
{0x002A0230},
{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_3_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A147C},
{0x0F1201A0},
{0x002A0230},
{0x0F120060},
};

s5k4ecgx_short_t s5k4ecgx_EV_Plus_4_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A147C},
{0x0F1201A0},
{0x002A0230},
{0x0F12007F},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_4_EVT1[] = { 
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F12FF81},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_3_EVT1[] = { 
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F12FFA0},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_2_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F12FFC0},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Minus_1_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F12FFE0},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Default_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_1_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F120020},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_2_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_3_EVT1[] = { // Setting Unavailable
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F120060},
};

s5k4ecgx_short_t s5k4ecgx_Contrast_Plus_4_EVT1[] = { // Setting Unavailable
{0xFCFCD000},
{0x00287000},
{0x002A0232},
{0x0F12007F},
};

s5k4ecgx_short_t s5k4ecgx_Auto_Contrast_ON_EVT1[] = {
{0x00287000},
{0x002A1BEA},
{0x0F120000},  //DRx_bDRxBypass
};

s5k4ecgx_short_t s5k4ecgx_Auto_Contrast_OFF_EVT1[] = {
{0x00287000},
{0x002A1BEA},
{0x0F120001},  //DRx_bDRxBypass
};

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_3_EVT1[] = { // Setting Unavailable
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

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_2_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Sharpness_Minus_1_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Sharpness_Default_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_1_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_2_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Sharpness_Plus_3_EVT1[] = { 
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

s5k4ecgx_short_t s5k4ecgx_Saturation_Minus_2_EVT1[] = {
{0x00287000},
{0x002A0234},
{0x0F12FF81},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Minus_1_EVT1[] = {
{0x00287000},
{0x002A0234},
{0x0F12FFC0},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Default_EVT1[] = {
{0x00287000},
{0x002A0234},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Plus_1_EVT1[] = {
{0x00287000},
{0x002A0234},
{0x0F120040},
};

s5k4ecgx_short_t s5k4ecgx_Saturation_Plus_2_EVT1[] = {
{0x00287000},
{0x002A0234},
{0x0F12007F},
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_High_EVT1[] = {
{0x00287000},
{0x002A0478},
{0x0F12005F}, //85%//
{0x0F12005F},
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_Normal_EVT1[] = {
{0x00287000},
{0x002A0478},
{0x0F12005A},
{0x0F12005A},
};

s5k4ecgx_short_t s5k4ecgx_Jpeg_Quality_Low_EVT1[] = {
{0x00287000},
{0x002A0478},
{0x0F120054},
{0x0F120054},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Default_EVT1[] = {
{0x00287000},
{0x002A1492},
{0x0F120100},
{0x0F120101},
{0x0F120101},
{0x0F120001},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120202},
{0x0F120202},
{0x0F120101},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120201},
{0x0F120302},
{0x0F120203},
{0x0F120102},
{0x0F120101},
{0x0F120202},
{0x0F120202},
{0x0F120101},
{0x0F120101},
{0x0F120201},
{0x0F120102},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},
{0x0F120101},

           
{0x002A4800},
{0x0F120119},	//	#TVAR_wbt_pBaseCcms[0]	     hor//
{0x0F12FFA9},	//	#TVAR_wbt_pBaseCcms[1]  	//
{0x0F12FF9D},	//	#TVAR_wbt_pBaseCcms[2]  	//
{0x0F12FF30},	//	#TVAR_wbt_pBaseCcms[3]  	//
{0x0F120130},	//	#TVAR_wbt_pBaseCcms[4]  	//
{0x0F12FF8E},	//	#TVAR_wbt_pBaseCcms[5]  	//
{0x0F12FFF8},	//	#TVAR_wbt_pBaseCcms[6]  	//
{0x0F12FFAC},	//	#TVAR_wbt_pBaseCcms[7]  	//
{0x0F120137},	//	#TVAR_wbt_pBaseCcms[8]  	//
{0x0F120087},	//	#TVAR_wbt_pBaseCcms[9]  	//
{0x0F1200D0},	//	#TVAR_wbt_pBaseCcms[10] 	//
{0x0F12FEE3},	//	#TVAR_wbt_pBaseCcms[11] 	//
{0x0F120162},	//	#TVAR_wbt_pBaseCcms[12] 	//
{0x0F12FF77},	//	#TVAR_wbt_pBaseCcms[13] 	//
{0x0F1200E8},	//	#TVAR_wbt_pBaseCcms[14] 	//
{0x0F12FF40},	//	#TVAR_wbt_pBaseCcms[15] 	//
{0x0F120114},	//	#TVAR_wbt_pBaseCcms[16] 	//
{0x0F1200F4},	//	#TVAR_wbt_pBaseCcms[17] 	//
{0x0F120119},	//	#TVAR_wbt_pBaseCcms[18]		incaA//
{0x0F12FFA9},	//	#TVAR_wbt_pBaseCcms[19] 	//
{0x0F12FF9D},	//	#TVAR_wbt_pBaseCcms[20] 	//
{0x0F12FF30},	//	#TVAR_wbt_pBaseCcms[21] 	//
{0x0F120130},	//	#TVAR_wbt_pBaseCcms[22] 	//
{0x0F12FF8E},	//	#TVAR_wbt_pBaseCcms[23] 	//
{0x0F12FFF8},	//	#TVAR_wbt_pBaseCcms[24] 	//
{0x0F12FFAC},	//	#TVAR_wbt_pBaseCcms[25] 	//
{0x0F120137},	//	#TVAR_wbt_pBaseCcms[26] 	//
{0x0F120087},	//	#TVAR_wbt_pBaseCcms[27] 	//
{0x0F1200D0},	//	#TVAR_wbt_pBaseCcms[28] 	//
{0x0F12FEE3},	//	#TVAR_wbt_pBaseCcms[29] 	//
{0x0F120162},	//	#TVAR_wbt_pBaseCcms[30] 	//
{0x0F12FF77},	//	#TVAR_wbt_pBaseCcms[31] 	//
{0x0F1200E8},	//	#TVAR_wbt_pBaseCcms[32] 	//
{0x0F12FF40},	//	#TVAR_wbt_pBaseCcms[33] 	//
{0x0F120114},	//	#TVAR_wbt_pBaseCcms[34] 	//
{0x0F1200F4},	//	#TVAR_wbt_pBaseCcms[35] 	//

{0x002A0938},
{0x0F120000},

{0x002A0990},
{0x0F120000},
{0x002A0A1E},
{0x0F120060},	//_iSAT

{0x002A06B8},	//#lt_uMaxLei//
{0x0F12452C},
{0x0F12000C},

{0x002A0F2A},
{0x0F120000},  // Flicker 50Hz 
{0x002A0F30},
{0x0F120001},
//0x002a04E6 S/W Program
//0x0F12077F //Auto bit ex) AE/AWB Flicker etc..//
{0x002A04D6},
{0x0F120000},	//	#REG_SF_USER_FlickerQuant	 0:off 1:50hz 2:60hz	//
{0x0F120001},	//	#REG_SF_USER_FlickerQuantChanged	//
{0x002A04D0}, //ISO Auto//
{0x0F120000}, 
{0x0F120000},
{0x0F120001},
{0x002A06C2},
{0x0F120200},
{0x002A0938},
{0x0F120000}, //afit_bUseNB_Afit

{0x002A2C66},
{0x0F120001},

{0x002A1484},
{0x0F12003C}, //AE Target//
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
{0x0F120001},
{0x0F120001},
{0x0F120c00},	//	#lt_ExpGain_ExpCurveGainMaxStr	A Gain//
{0x0F120100},	//	#lt_ExpGain_ExpCurveGainMaxStr_0__uMaxDigGain	//

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

{0x002A0638}, //shutter Table// 
{0x0F120001},                   
{0x0F120000},                   
{0x0F120A3C},                   
{0x0F120000},                   
{0x0F120D04},                   
{0x0F120000},                   
{0x0F123408},                   
{0x0F120000},                   
{0x0F123408},                   
{0x0F120000},                   
{0x0F126810},                   
{0x0F120000},                   
{0x0F128214},                   
{0x0F120000},                   
{0x0F12C350},                   
{0x0F120000},                   
{0x0F12C350},                   
{0x0F120000},                   
{0x0F12C350},                   
{0x0F120000},                   

{0x002A02C2},	//preview//
{0x0F12029A},	//#REG_0TC_PCFG_usMaxFrTimeMsecMult10//
{0x0F12014A},	//#REG_0TC_PCFG_usMinFrTimeMsecMult10//

{0x002A03B4},	//Capture//
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

s5k4ecgx_short_t s5k4ecgx_Scene_Portrait_EVT1[] = {
{0x00287000},
{0x002A0A28},
{0x0F122020},
{0x002A0ADE},
{0x0F122020},
{0x002A0B94},
{0x0F122020},
{0x002A0C4A},
{0x0F122020},
{0x002A0D00},
{0x0F122020},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Nightshot_EVT1[] = {
{0x00287000},
{0x002A06B8},	//#lt_uMaxLei//
{0x0F12FFFF},
{0x0F1200FF},

{0x002A0990},
{0x0F120038},

{0x002A0658},
{0x0F12D090},
{0x0F120007},
{0x0F12D090},
{0x0F120007},

{0x002A03B4},
{0x0F121388},
{0x0F121388},
{0x002A02C2},
{0x0F1209C4},
{0x0F12014A},
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
{0x0F1215C0},

          
{0x002A4800},
{0x0F120113},	//	#TVAR_wbt_pBaseCcms[0]	     hor//
{0x0F12FFBE},	//	#TVAR_wbt_pBaseCcms[1]  	//
{0x0F12FFB5},	//	#TVAR_wbt_pBaseCcms[2]  	//
{0x0F12FF64},	//	#TVAR_wbt_pBaseCcms[3]  	//
{0x0F120124},	//	#TVAR_wbt_pBaseCcms[4]  	//
{0x0F12FFAA},	//	#TVAR_wbt_pBaseCcms[5]  	//
{0x0F12FFFA},	//	#TVAR_wbt_pBaseCcms[6]  	//
{0x0F12FFC1},	//	#TVAR_wbt_pBaseCcms[7]  	//
{0x0F12012A},	//	#TVAR_wbt_pBaseCcms[8]  	//
{0x0F120027},	//	#TVAR_wbt_pBaseCcms[9]  	//
{0x0F120153},	//	#TVAR_wbt_pBaseCcms[10] 	//
{0x0F12FED6},	//	#TVAR_wbt_pBaseCcms[11] 	//
{0x0F120149},	//	#TVAR_wbt_pBaseCcms[12] 	//
{0x0F12FF99},	//	#TVAR_wbt_pBaseCcms[13] 	//
{0x0F1200EE},	//	#TVAR_wbt_pBaseCcms[14] 	//
{0x0F12FF70},	//	#TVAR_wbt_pBaseCcms[15] 	//
{0x0F12010F},	//	#TVAR_wbt_pBaseCcms[16] 	//
{0x0F1200F7},	//	#TVAR_wbt_pBaseCcms[17] 	//
{0x0F120113},	//	#TVAR_wbt_pBaseCcms[18]		incaA//
{0x0F12FFBE},	//	#TVAR_wbt_pBaseCcms[19] 	//
{0x0F12FFB5},	//	#TVAR_wbt_pBaseCcms[20] 	//
{0x0F12FF64},	//	#TVAR_wbt_pBaseCcms[21] 	//
{0x0F120124},	//	#TVAR_wbt_pBaseCcms[22] 	//
{0x0F12FFAA},	//	#TVAR_wbt_pBaseCcms[23] 	//
{0x0F12FFFA},	//	#TVAR_wbt_pBaseCcms[24] 	//
{0x0F12FFC1},	//	#TVAR_wbt_pBaseCcms[25] 	//
{0x0F12012A},	//	#TVAR_wbt_pBaseCcms[26] 	//
{0x0F120027},	//	#TVAR_wbt_pBaseCcms[27] 	//
{0x0F120153},	//	#TVAR_wbt_pBaseCcms[28] 	//
{0x0F12FED6},	//	#TVAR_wbt_pBaseCcms[29] 	//
{0x0F120149},	//	#TVAR_wbt_pBaseCcms[30] 	//
{0x0F12FF99},	//	#TVAR_wbt_pBaseCcms[31] 	//
{0x0F1200EE},	//	#TVAR_wbt_pBaseCcms[32] 	//
{0x0F12FF70},	//	#TVAR_wbt_pBaseCcms[33] 	//
{0x0F12010F},	//	#TVAR_wbt_pBaseCcms[34] 	//
{0x0F1200F7},	//	#TVAR_wbt_pBaseCcms[35] 	//

};

s5k4ecgx_short_t s5k4ecgx_Scene_Backlight_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Scene_Landscape_EVT1[] = {
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
{0x0F12E082},
{0x002A0ADE},
{0x0F12E082},
{0x002A0B94},
{0x0F12E082},
{0x002A0C4A},
{0x0F12E082},
{0x002A0D00},
{0x0F12E082},
{0x002A0234},
{0x0F120030},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Sports_EVT1[] = {
{0x00287000},
{0x002A0638},
{0x0F120001},
{0x0F120000},   //lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_0_
{0x0F120A3C},
{0x0F120000},
{0x0F120D05},
{0x0F120000},
{0x0F123408},
{0x0F120000},
{0x0F123408},
{0x0F120000},
{0x0F123408},
{0x0F120000},
{0x0F123408},
{0x0F120000},
{0x0F123408},
{0x0F120000},
{0x0F123408},
{0x0F120000},
{0x0F123408},
{0x0F120000},

                //ISO x2
{0x002A0938},
{0x0F120001},   //NB mode

{0x002A04D0},
{0x0F120003},
{0x0F120200},
{0x0F120001},
                //ISO x2

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

s5k4ecgx_short_t s5k4ecgx_Scene_Party_Indoor_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0F12065F
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
{0x0F120030},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Beach_Snow_EVT1[] = {
{0xFCFCD000},
{0x00287000},
{0x002A1484},
{0x0F120045},	//#TVAR_ae_BrAve//

{0x002A0938},
{0x0F120001},

//0x002a04E6 S/W Program
//0x0F12065F
{0x002A04D6},
{0x0F120000},
{0x0F120001},

{0x002A04D0},
{0x0F120001},
{0x0F1200D0},
{0x0F120001},
{0x002A06C2},
{0x0F120100},

{0x002A0234},
{0x0F120030},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Sunset_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0F120777
{0x002A04BA},
{0x0F1205F0},
{0x0F120001},
{0x0F120400},
{0x0F120001},
{0x0F120588},
{0x0F120001},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Duskdawn_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0F120777
{0x002A04BA},
{0x0F1205A5},
{0x0F120001},
{0x0F120400},
{0x0F120001},
{0x0F1208A8},
{0x0F120001},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Fall_Color_EVT1[] = {
{0x00287000},
{0x002A0234},
{0x0F120060},
};

s5k4ecgx_short_t s5k4ecgx_Scene_Fireworks_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Scene_Text_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Scene_Candle_Light_EVT1[] = {
{0xFCFCD000},
{0x00287000},
//0x002a04E6 S/W Program
//0x0F120777
{0x002A04BA},
{0x0F1205F0},
{0x0F120001},
{0x0F120400},
{0x0F120001},
{0x0F120588},
{0x0F120001},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_awb_ae_lock_EVT1[] = {
{0x00287000},
{0x002A2C5E},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_awb_ae_unlock_EVT1[] = {
{0x00287000},
{0x002A2C5E},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_AF_Return_Inf_pos_EVT1[] = {
{0x00287000},
{0x002A15D6},
{0x0F12D000},
};

s5k4ecgx_short_t s5k4ecgx_AF_Return_Macro_pos_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_1_EVT1[] = {
{0x00287000},
{0x002A028E},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_2_EVT1[] = {
{0x00287000},
{0x002A028C},
{0x0F120004},
};


s5k4ecgx_short_t s5k4ecgx_AF_Normal_mode_3_EVT1[] = {
{0x00287000},
{0x002A1648},
{0x0F129002},
};

s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_1_EVT1[] = {
{0x00287000},
{0x002A028E},
{0x0F1200D0},
};

s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_2_EVT1[] = {
{0x00287000},
{0x002A028C},
{0x0F120004},
};


s5k4ecgx_short_t s5k4ecgx_AF_Macro_mode_3_EVT1[] = {
{0x00287000},
{0x002A1648},
{0x0F129042},
{0x002A15DA},
{0x0F121800},
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_1_EVT1[] = {
{0x00287000},
{0x002A028E},
{0x0F120000},
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_2_EVT1[] = {
{0x00287000},
{0x002A028C},
{0x0F120004},
};
s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_normal_mode_3_EVT1[] = {
{0x00287000},
{0x002A1648},
{0x0F129002},
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_1_EVT1[] = {
{0x00287000},
{0x002A028E},
{0x0F1200D0},
};


s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_2_EVT1[] = {
{0x00287000},
{0x002A028C},
{0x0F120004},
};

s5k4ecgx_short_t s5k4ecgx_AF_Low_Light_Macro_mode_3_EVT1[] = {
{0x00287000},
{0x002A1648},
{0x0F129042},
{0x002A15DA},
{0x0F120C00},
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Start_EVT1[] = {
{0x00287000},
{0x002A028C},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_1_EVT1[] = {
{0x00287000},
{0x002A028E},
{0x0F120000},
{0x00287000},
{0x002A028C},
{0x0F120004},
};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_2_EVT1[] = {

};

s5k4ecgx_short_t s5k4ecgx_Single_AF_Off_3_EVT1[] = {

};

s5k4ecgx_short_t s5k4ecgx_Face_Detection_On_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Face_Detection_Off_EVT1[] = {
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

s5k4ecgx_short_t s5k4ecgx_Low_Cap_On_EVT1[] = {
{0x00287000},
{0x002A06B8},
{0x0F12552C},
{0x0F120006}, //#lt_uMaxLei//

{0x002A0A1A},
{0x0F124A18}, //#Gamma linearity//


{0x002A0608},
{0x0F120001},	//#lt_ExpGain_uSubsamplingmode//
{0x0F120001},	//#lt_ExpGain_uNonSubsampling//
{0x0F120780},	//#lt_ExpGain_ExpCurveGainMaxStr//

{0x002A0938},
{0x0F120001},    //afit_bUseNB_Afit //
{0x0F120012},	//#SARR_uNormBrInDoor_0_//
{0x0F120022},	//#SARR_uNormBrInDoor_1_//
{0x0F120384},	//#SARR_uNormBrInDoor_2_//
{0x0F1207D0},	//#SARR_uNormBrInDoor_3_//
{0x0F121388},	//#SARR_uNormBrInDoor_4_//
};

s5k4ecgx_short_t s5k4ecgx_Low_Cap_Off_EVT1[] = {
{0x00287000},
{0x002A06B8},
{0x0F12452C},
{0x0F12000C},	//#lt_uMaxLei//

{0x002A0A1A},
{0x0F128F18}, //#Gamma linearity//


{0x002A0608},
{0x0F120001},	//#lt_ExpGain_uSubsamplingmode//
{0x0F120001},	//#lt_ExpGain_uNonSubsampling//
{0x0F120C00},	//#lt_ExpGain_ExpCurveGainMaxStr//

{0x002A0938},
{0x0F120000},	 //afit_bUseNB_Afit //
{0x0F120014},	//#SARR_uNormBrInDoor_0_//
{0x0F1200D2},	//#SARR_uNormBrInDoor_1_//
{0x0F120384},	//#SARR_uNormBrInDoor_2_//
{0x0F1207D0},	//#SARR_uNormBrInDoor_3_//
{0x0F121388},	//#SARR_uNormBrInDoor_4_//
};

s5k4ecgx_short_t s5k4ecgx_Night_Mode_On_EVT1[] = {
{0x00287000},              
{0x002A0608},                                 
{0x0F120001}, /*#lt_ExpGain_uSubsamplingmode*/
{0x0F120001}, /*#lt_ExpGain_uNonSubsampling*/
{0x0F120900}, /*#lt_ExpGain_ExpCurveGainMaxStr*/          
};

s5k4ecgx_short_t s5k4ecgx_Capture_Start_EVT1[] ={
{0x00287000},
{0x002A0A1E},
{0x0F120050},	//don`t touch//
{0x002A0AD4},
{0x0F120074},

{0x002A0242},
{0x0F120001},
{0x002A024E},
{0x0F120001},
{0x002A0244},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_Preview_Return_EVT1[] ={
{0x00287000},
{0x002A0A1E},  
{0x0F120028},	//don`t touch//
{0x002A0AD4},
{0x0F12003C},	

{0x002A0608},
{0x0F120001},	//#lt_ExpGain_uSubsamplingmode//
{0x0F120001},	//#lt_ExpGain_uNonSubsampling//
{0x0F120c00},	//#lt_ExpGain_ExpCurveGainMaxStr//

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


s5k4ecgx_short_t s5k4ecgx_5M_Capture_EVT1[] = {  // 2560 x 1920 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x00287000},
{0x002A0398},
{0x0F120A00},	// #REG_0TC_CCFG_usWidth //
{0x0F120780},	// #REG_0TC_CCFG_usHeight //
{0x0F120009},
{0x002A03B2},
{0x0F120002},
{0x002A03B0},
{0x0F120002},
{0x002A0270},
{0x0F120001},
};

s5k4ecgx_short_t s5k4ecgx_3M_Capture_EVT1[] = {  // 2048 x 1536 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x00287000},
{0x002A0398},
{0x0F120800},	// #REG_0TC_CCFG_usWidth //
{0x0F120600},	// #REG_0TC_CCFG_usHeight //
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

s5k4ecgx_short_t s5k4ecgx_2M_Capture_EVT1[] = {  // 1600 x 1200 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x002A0398},
{0x0F120640},	// #REG_0TC_CCFG_usWidth //
{0x0F1204B0},	// #REG_0TC_CCFG_usHeight //
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



s5k4ecgx_short_t s5k4ecgx_1M_Capture_EVT1[] = {  // 1280 x 960 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x002A0398},
{0x0F120500},	// #REG_0TC_CCFG_usWidth //
{0x0F1203C0},	// #REG_0TC_CCFG_usHeight //
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


s5k4ecgx_short_t s5k4ecgx_VGA_Capture_EVT1[] = {  // 640 x 480 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x002A0398},
{0x0F120280},	// #REG_0TC_CCFG_usWidth //
{0x0F1201E0},	// #REG_0TC_CCFG_usHeight //
{0x0F120009},
{0x002A03B2},
{0x0F120002},
{0x002A03B0},
{0x0F120002},
{0x002A024E},
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0270},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //
};

s5k4ecgx_short_t s5k4ecgx_QVGA_Capture_EVT1[] = {  // 320 x 240 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120140},
{0x0F1200F0},
{0x0F120005},
{0x002A0398},
{0x0F120140},	// #REG_0TC_CCFG_usWidth //
{0x0F1200F0},	// #REG_0TC_CCFG_usHeight //
{0x0F120009},
{0x002A03B2},
{0x0F120002},
{0x002A03B0},
{0x0F120002},
{0x002A024E},
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0270},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //
};

s5k4ecgx_short_t s5k4ecgx_QCIF_Capture_EVT1[] = {  // 320 x 240 //
{0x00287000},
{0x002A0258},
{0x0F120A00},	// #REG_TC_GP_CapReqInputWidth //
{0x0F120780},	// #REG_TC_GP_CapReqInputHeight //
{0x0F120010},	// #REG_TC_GP_CapInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_CapInputHeightOfs //
{0x002A049C},
{0x0F120A00},	// #REG_TC_PZOOM_CapZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_CapZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_CapZoomReqInputHeightOfs //
{0x002A0264},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInCap	//
{0x002A047C},
{0x0F120001},
{0x0F120140},
{0x0F1200F0},
{0x0F120005},
{0x002A0398},
{0x0F120140},	// #REG_0TC_CCFG_usWidth //
{0x0F1200F0},	// #REG_0TC_CCFG_usHeight //
{0x0F120009},
{0x002A03B2},
{0x0F120002},
{0x002A03B0},
{0x0F120002},
{0x002A024E},
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0270},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //
};

s5k4ecgx_short_t s5k4ecgx_720_Preview_EVT1[] = {  // 720 x 480 //
{0x00287000},
{0x002A0250},
{0x0F120A00},	// #REG_TC_GP_PrevReqInputWidth //
{0x0F1206A8},	// #REG_TC_GP_PrevReqInputHeight //
{0x0F120010},	// #REG_TC_GP_PrevInputWidthOfs	//
{0x0F120078},	// #REG_TC_GP_PrevInputHeightOfs //
{0x002A0494},
{0x0F120A00},	// #REG_TC_PZOOM_PrevZoomReqInputWidth //
{0x0F1206A8},	// #REG_TC_PZOOM_PrevZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputHeightOfs //
{0x002A0262},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInPre	//
{0x002A0A1E},
{0x0F120028},
{0x002A0AD4},
{0x0F12003C},
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
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0268},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //
};

s5k4ecgx_short_t s5k4ecgx_640_Preview_EVT1[] = {  // 640 x 480 //
{0x00287000},
{0x002A0250},
{0x0F120A00},	// #REG_TC_GP_PrevReqInputWidth //
{0x0F120780},	// #REG_TC_GP_PrevReqInputHeight //
{0x0F120010},	// #REG_TC_GP_PrevInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_PrevInputHeightOfs //
{0x002A0494},
{0x0F120A00},	// #REG_TC_PZOOM_PrevZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_PrevZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputHeightOfs //
{0x002A0262},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInPre	//
{0x002A0A1E},
{0x0F120028},
{0x002A0AD4},
{0x0F12003C},
{0x002A02A6},
{0x0F120280},
{0x0F1201E0},
{0x0F120005},
{0x002A02B4},
{0x0F120052},
{0x002A02BE},
{0x0F120000},
{0x0F120001},
{0x0F12029A},  //1
{0x0F12014A},  //2 14d
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0268},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //

};

s5k4ecgx_short_t s5k4ecgx_352_Preview_EVT1[] = {  // 352 x 288 //
{0x00287000},
{0x002A0250},
{0x0F120928},	// #REG_TC_GP_PrevReqInputWidth //
{0x0F120780},	// #REG_TC_GP_PrevReqInputHeight //
{0x0F12007C},	// #REG_TC_GP_PrevInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_PrevInputHeightOfs //
{0x002A0494},
{0x0F120928},	// #REG_TC_PZOOM_PrevZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_PrevZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputHeightOfs //
{0x002A0262},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInPre	//
{0x002A0A1E},
{0x0F120028},
{0x002A0AD4},
{0x0F12003C},
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
{0x0F12014A},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0268},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //

};


s5k4ecgx_short_t s5k4ecgx_176_Preview_EVT1[] = {  // 176 x 144 //
{0x00287000},
{0x002A0250},
{0x0F120928},	// #REG_TC_GP_PrevReqInputWidth //
{0x0F120780},	// #REG_TC_GP_PrevReqInputHeight //
{0x0F12007C},	// #REG_TC_GP_PrevInputWidthOfs	//
{0x0F12000C},	// #REG_TC_GP_PrevInputHeightOfs //
{0x002A0494},
{0x0F120928},	// #REG_TC_PZOOM_PrevZoomReqInputWidth //
{0x0F120780},	// #REG_TC_PZOOM_PrevZoomReqInputHeight	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputWidthOfs	//
{0x0F120000},	// #REG_TC_PZOOM_PrevZoomReqInputHeightOfs //
{0x002A0262},
{0x0F120001},	// #REG_TC_GP_bUseReqInputInPre	//
{0x002A0A1E},
{0x0F120028},
{0x002A0AD4},
{0x0F12003C},
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
{0x0F12014A},
{0x002A02D0},
{0x0F120000},
{0x0F120000},
{0x002A0266},
{0x0F120000},
{0x002A026A},
{0x0F120001},
{0x002A024E},
{0x0F120001},	// #REG_TC_GP_NewConfigSync //
{0x002A0268},
{0x0F120001},	// #REG_TC_GP_CapConfigChanged //
};

// Zoom set for 320,176//
s5k4ecgx_short_t s5k4ecgx_X4_Zoom_0_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120100},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_1_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120120},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_2_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120140},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_3_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120160},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_4_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120180},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_5_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201A0},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_6_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201C0},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_7_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201E0},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X4_Zoom_8_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120200},
{0x002A04A4},
{0x0F120005},
};


// Zoom set for 1280 x 640 //
s5k4ecgx_short_t s5k4ecgx_X2_Zoom_0_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120100},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_1_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120120},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_2_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120140},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_3_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120160},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_4_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120180},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_5_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201A0},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_6_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201C0},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_7_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201E0},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X2_Zoom_8_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120200},
{0x002A04A4},
{0x0F120005},
};

// Zoom set for 720//
s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_0_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120100},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_1_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120118},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_2_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120130},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_3_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120148},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_4_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120160},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_5_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120178},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_6_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120190},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_7_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201A8},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_77_Zoom_8_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F1201C5},
{0x002A04A4},
{0x0F120005},
};

// Zoom set for 1600 //
s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_0_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120100},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_1_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120113},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_2_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120126},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_3_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120139},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_4_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F12014C},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_5_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F12015F},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_6_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120172},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_7_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120185},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_6_Zoom_8_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F12019A},
{0x002A04A4},
{0x0F120005},
};

// Zoom set for 2048 //
s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_0_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120100},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_1_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120108},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_2_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120110},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_3_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120118},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_4_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120120},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_5_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120128},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_6_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120130},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_7_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120138},
{0x002A04A4},
{0x0F120005},
};

s5k4ecgx_short_t s5k4ecgx_X1_25_Zoom_8_EVT1[] = {
{0x00287000},
{0x002A048E},
{0x0F120140},
{0x002A04A4},
{0x0F120005},
};
