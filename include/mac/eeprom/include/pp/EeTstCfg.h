/*==============================================================================
;*  $Header:   K:/PH/140960xx/00/Archive/H/EeTstCfg.h_v   1.1   17 Sep 2003 08:13:10   mne  $ *
;*
;*  DESCRIPTION: This files should be in the project directory. The purpose of
;*               the file is to allow disabling of some functionalities of the
;*               eetest batch file interface.
;*               Only those functionalities that have defines are included in
;*               the eetest.c.
;*
;*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;*  The information in this document is confidential and sole property of
;*  RTX Research A/S. (c) Copyright 1998 by RTX Research A/S.
;*============================================================================*/

/*============================ MACROS / CONSTANTS ============================*/

#ifdef _RFP_
#define F_ECHO_SUPPRESSOR_OFF
#define F_ECHO_SUPPRESSOR_ON
#define F_ECHO_CANCELLER_OFF
#define F_ECHO_CANCELLER_ON
#define F_TEMP_DIVERSITY_MODE
#ifdef _TAD_
#define F_TC_TAD_STATUS            /* Return 16 bit status from TAD*/
#define F_TC_CLIP_STATUS           /* Return 16 bit status from CLIP module*/
#define F_TC_TAD_TESTCMD
#endif
#else
#ifdef PELTOR_PP
#define F_TEMP_DIVERSITY_MODE
#endif
/*  #define F_TC_LOOP_BACK*/
/*  #define F_TC_DIALTONE*/
#define F_TC_DISPLAY_TEST
/*  #define F_TC_SLEEP*/
#endif

/* COMMON FOR HS AND BS.*/
#define F_TC_USERDEFAULT
#define F_TC_BUZZER
#define F_TC_READ_COMP           /* HS*/
#define F_TC_READ_RSSI
#define F_TC_WRITE_RSSI          /* HS*/
#define F_WRITE_MODULATION
#define F_TC_RFOFF
#define F_TC_SW_VERSION          /* HS*/
/*  #define F_TC_READ_BATTERY_VOLTAGE// HS*/
/*  #define F_TC_READ_BATTERY_TEMP   // HS*/
/*  #define F_TC_FLASH_CHECKSUM*/
/*  #define F_TC_KEYTEST             // HS*/
#define F_TC_READ_LR
#define F_TC_WRITE_ID
#define F_TC_READ_ID
#define F_TC_SET_QUAD

#define F_TC_BACKLIGHT
#define F_TC_WRITE_LR
#define F_TC_READ_COMP_RSSI      /* HS*/
#define F_TC_NO_SLEEP            /* HS*/
#define F_TC_CURRENT_FREQ        /* HS*/
#define F_TC_SOFTWARE_RESET
/*  #define F_TC_DETECT_HEADSET*/
#define F_TC_INT_SPEAK
#define F_TC_DETECT_CHARGE
#define F_TC_LED0
#define F_TC_SWITCH_OFF
#define F_TC_VIBRATOR
/*  #define F_TC_DEF_PRG_FLAG*/
#define F_TC_WRT_DEFAULT
/*  #define F_TC_DEF_PRG_INIT*/
/*  #define F_TC_READ_UI_STATE*/
#define F_TC_READ_RSSI_Q_R_C
/*  #define F_TC_CHECK_EE_CACHE_EMPTY*/
#define F_TC_WRT_BANDGAP

/*=================================== END ====================================*/
