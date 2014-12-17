/********************************************************************************
 *********************************************************************************
 *                                                                               *
 *     E ENEEEEEEEEEEEE             CCCC CCC         TTTTTTT TTTTTTTTTT          *
 *     E EEEEEEEEEEEEEE          CCCCC  C CCCC             T TTTTT               *
 *     E EEEE                   CCCCC    C CCCC            T TTTTT               *
 *     E EEEE                  CCCCC      C CCCC           T TTTTT               *
 *     E EEEE                 CCCCC                        T TTTTT               *
 *     E EEEEEEEEEEEEEE      CCCCC                         T TTTTT               *
 *     E EEEEEEEEEEEEEE      C CCCC                        T TTTTT               *
 *     E EEEE                 C CCCC                       T TTTTT               *
 *     E EEEE                  C CCCC      CCCCC           T TTTTT               *
 *     E EEEEEEEEEEEEEE         C CCCC   CCCCC             T TTTTT               *
 *     E EEEEEEEEEEEEEE  OO      C CCCCCCCC         OO     T TTTTT     OO        *
 *                       OO                         OO                 OO        *
 *                                                                               *
 *     Electronic Communication Technology A/S.                                  *
 *     Sintrupvej 23, DK-8220 Brabrand, Tel.: +45 87441230                       *
 *     Website: www.ect.dk                                                       *
 *                                                                               *
 *********************************************************************************
 * $History:: fppp_common.h                                                    $ *
 *                                                                               *
 * Initial Revision                                                              *
 *********************************************************************************
 */
#ifndef FPPP_COMMON_H_
#define FPPP_COMMON_H_

#define FW_REV_MAJOR	2
#define FW_REV_MINOR	0
#define FW_REV_STR 	"WT FW 2.0-AL *** support for dual bases; EXP & dual lane systems *** "
// max length ==>   "___________________________________________________________________________________________________"

//#define ENABLE_CHANNEL_MESSAGES

#define WENTWORTH_PACKET_ID 0xBA

extern UByte WENTWORTHTASK;
extern UByte WENTWORTHTASKTIMER;

// FIRST_ACTION byte in PP EEPROM
#define EE_FIRST_ACTION			0x02E8	// used for toggling test mode of headset (0x22 = test mode, 0xFF = production)

// this is located in the EE_FREE2 area of EEPROM (0x021D / 541 bytes available)
#define EE_WTDATA				0x03E3	// beginning of WT data area

// in case we only need to read a specific value from PP EEPROM
#define EE_WT_PP_MIC_GAIN_FLAG	0x03E3	// 1	0xFF is no offset, 0x00 is positive offset, 0x01 is negative offset
#define EE_WT_PP_MIC_GAIN_VALUE	0x03E4	// 1	offset to headset.GainVolume
#define EE_WT_PP_RCV_GAIN_FLAG	0x03E5	// 1	0xFF is no offset, 0x00 is positive offset, 0x01 is negative offset
#define EE_WT_PP_RCV_GAIN_VALUE	0x03E6	// 1	offset to headset.SpkrVolOffset

// in case we only need to read a specific value from FP EEPROM
#define EE_FW_REV_MAJOR			0x03E3	// 1
#define EE_FW_REV_MINOR			0x03E4	// 1
#define EE_WT_USER_PIN			0x03E5	// 4
#define EE_WT_MODE_LOCK			0x03E9	// 1	([7:4]mode; [3:0]lock)
#define EE_WT_INBOUND			0x03EA	// 1
#define EE_WT_GRILL				0x03EB	// 1
#define EE_WT_OUTBOUND_DAY		0x03EC	// 1
#define EE_WT_OUTBOUND_NIGHT	0x03ED	// 1
#define EE_WT_NIGHTVOLSTART		0x03EE	// 4
#define EE_WT_NIGHTVOLEND		0x03F2	// 4
#define EE_WT_LISTEN_ONLY		0x03F6	// 10   = 29 bytes
#define EE_WT_GREET_INFO		0x0400	// 63	(enable-label and start/stop for MT, F, Sa, & Su => 9 x 7 = 63)
#define EE_WT_MESSAGE_INFO		0x043F	// 126	(enable-label and start/repeat for MT, F, Sa, & Su => 9 x 14 = 126)
#define EE_WT_GRTR_MSGR_ENABLE	0x04BD	// 1
#define EE_WT_GREET_AUTH_CODE	0x04BE	// 4
#define EE_WT_POWER_ON_COUNT	0x04C2	// 2
#define EE_WT_ALANGO_STATE		0x04C4	// 1	(0 = MA-11/profile 0, 1 = MA-10/profile 1)
#define EE_WT_MENU_CONFIG		0x04C5	// 1	(0 = single menu ONLY; 1 = single menu EXP; 2 = parallel menus 1OT; 3 = tandem menus 1OT; 4 = parallel menus 2OT, 5 = tandem menus 2OT)
#define EE_WT_DUAL_BASE			0x04C6	// 1	(0 = no dual base; 1 = MENU A; 2 = MENU B)
										//====> 29 + 63 + 126 + 10 = 228 bytes

#define EE_WT_NUM_BYTES			0x00E4	// 228 bytes

#define MIC_MUTE_CMD        	0x11
#define SET_OT_CMD				0x12
#define CAR_WAITING_CMD			0x13
#define BLINK_LED_CMD			0x14
#define SYSTEM_MODE_CMD			0x15
#define GET_SYSTEM_MODE			0x16
#define PAGE_CMD				0x17
#define READ_EEPROM				0x18
#define ENABLE_SPEECH_BUFFER	0x19
#define READ_CONF				0x1A
#define READ_EEPROM_HEX_ARI		0x1B
#define LISTEN_ONLY_MODE_CMD	0x1C
#define CAL_PP_CMD				0x1D
#define CONF_FROM_BS			0x80
#define WRITE_WT_DEBUG_EEPROM	0x81
#define READ_WTDATA_EEPROM		0x82
#define WRITE_WTDATA_EEPROM		0x83
#define SETUP_DISPLAY			0x84
#ifdef ENABLE_CHANNEL_MESSAGES
#define CHECK_CHANNEL			0x85
#endif
#define CHECK_TEOM				0x86
#define	SETUP_SECOND_BASE		0x87
#define DISPLAY_WT_DEBUG_INFO	0x88
#define READ_COUNTRY_EEPROM		0x89
#define HM_TIMER_TESTING		0x2A

#define WT_HEAP_CHECK			0x2C

// SYSTEM MODES == VVMM (VV = base inbound volume, MM = system mode)
#define UNREGISTERED			0x01
#define HANDS_FREE				0x02
#define PUSH_TO_TALK			0x03
#define AUTO_HANDS_FREE			0x04
#define SPEED_TEAM				0x05
#define LISTEN_ONLY_MODE		0x06
#define NOT_LOCKED				0x07

typedef struct
{
  WORD MicMute; 		// 0 is open to menu A, 1 is mute menu A, 2 is become OT menu A, 3 is open to menu B, 4 is mute menu B, 5 is become OT menu B
} SetMicMuteStruct;

typedef struct
{
  WORD CarWaiting; 		// 0 is no car on menu A, 10 is car on menu A + no beep, 11 is car on menu A + beep, 1 is no car on menu B, 20 is car on menu B + no beep, 21 is car on menu B + beep
} SetCarWaitingStruct;

typedef struct
{
  WORD LEDColor; 		// 0 is menu A off, 1 is menu A RED, 2 is menu A YELLOW, 3 is menu A GREEN, 4 is menu B off, 5 is menu B RED, 6 is menu B YELLOW, 7 is menu B GREEN
} SetLEDStruct;

typedef struct
{
  WORD SystemMode;		// aabbccdd - aa: 0x80 is BC5 off bit; bb is menu config; cc is base inbound volume; dd is base system mode
} SetSystemModeStruct;

typedef struct
{
  WORD Page; 			// 0 is off, 1 is on
} SetPageStruct;

typedef struct
{
  // .Debug1 value is sent from FP and can be used by PP for anything we want ...
  // 0 is normal mode, 1 is bypassing BC5 in speaker path; see gdsp_BC5SpeakerPath()
  WORD Debug1;
} SetConfStruct;

typedef struct
{
  WORD OrderTaker;		// 0 is headset is not Order Taker, 1 is headset is Order Taker
} SetOrderTakerStruct;

typedef struct
{
  WORD PPOffset; 		// 0/3 is negative, 1/4 is reset, 2/5 is positive
} SetPPOffsetStruct;

typedef union
{
  SetMicMuteStruct SetMicMute;
  SetCarWaitingStruct SetCarWaiting;
  SetLEDStruct SetLEDColor;
  SetSystemModeStruct SetSystemMode;
  SetSystemModeStruct GetSystemMode;
  SetPageStruct SetPage;
  SetConfStruct SetConf;
  SetOrderTakerStruct SetOrderTaker;
  SetPPOffsetStruct SetPPOffset;
} SubType;

typedef struct
{
   unsigned char SubStatusType;
   SubType Sub;
} WWMSF;

#endif /* FPPP_COMMON_H_ */
