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
 * $History:: wentworth_pp.h                                                   $ *
 *                                                                               *
 * Initial Revision                                                              *
 *********************************************************************************
 */
#ifndef WENTWORTH_PP_H_
#define WENTWORTH_PP_H_

#define TOGGLE_LED			0xA4	// toggle steady RED/GREEN LED on low battery
#define CHECK_OFFSET		0xA5	// check EEPROM[0x03E3-0x03E6] for headset.GainVolume & headset.SpkrVolOffset offsets
#define TOGGLE_TB_FAIL_LED	0xA6	// toggle slow RED/GREEN LED on touchboard fail

#define HM_Filler_D2 		0xD2	// hopefully a filler

#define MIN_LSR_VOLUME		0x00	//  0 = -8dB  (normalized to 8 = 0dB)
#define MAX_LSR_VOLUME		0x0E	// 14 = +6dB  (normalized to 8 = 0dB)

#define MENU_A				1
#define MENU_B				2

/**************************
// headset touch buttons
//				   ----------
//				  /  V4      \
//				 /  V3   CB	  ------|
//				 \ V2		  ------|
//				  \ V1   PB  /
//				   ----------
**************************/
#define PAGE_BUTTON		(0x0001)
#define VOL1_BUTTON		(0x0002)
#define VOL2_BUTTON		(0x0004)
#define VOL3_BUTTON		(0x0008)
#define VOL4_BUTTON		(0x0010)
#define CALL_BUTTON		(0x0020)

#define SWIPE_UP 1
#define SWIPE_DOWN 2

typedef struct
{
  UByte BaseAri[5]; // 0x2E3
  UByte action_after_logon; // retain this for compatibility reasons
  UByte AccessCode[4];
  UByte BaseFilter[6];// 'F' is a wildcard digit, nibble based
} WENTWORTHEEpromStruct;

extern WENTWORTHEEpromStruct WENTWORTHeepromData;

typedef struct
{
	UByte DoublePressWindow, OTDoublePressWindow;	// time to recognize 2nd CB press as double press (in 1/100's of a second)
	UByte PowerOnStatus;
	UByte LastButtonPressed;
	UByte PreviousHeadsetButtonStates;			// < 0000 0000 00C4 321P > are the bit positions
	UByte CurrentHeadsetButtonStates;			// < 0000 0000 00C4 321P > are the bit positions
	BOOLEAN OrderTaker, TakingOrder, Pager;
	BOOLEAN VehicleAlert;
	BOOLEAN CarAtOrderPost;
	UByte OtherLaneWaiting;
	UByte AlertCount;
	UByte BatteryLowCounter;
	int GainVolume, SpkrVolOffset;
	WORD WavAtten;
	int GainSpkrVolume;
	UByte SpeakerVolume;
	UByte Volume_Swipe;
	BOOLEAN SwipeWaiting;
	BOOLEAN GreenLEDisOn, GreenLEDisBlinking;
	BOOLEAN RedLEDisOn, RedLEDisBlinking;
	BOOLEAN YellowLEDisOn, YellowLEDisBlinking;
	UByte CurrentLEDState;						// 0 is menu A off, 1 is menu A RED, 2 is menu A YELLOW, 3 is menu A GREEN, 4 is menu B off, 5 is menu B RED, 6 is menu B YELLOW, 7 is menu B GREEN
	BOOLEAN OTtimer;
	BOOLEAN DualMenu, MenuA, SingleOT;
	UByte PP_IPEI[5];
	char SerialNumber[17];
	UByte SystemMode;
	UByte TouchBoardStatus, TouchBoardFail, TouchBoardCode;
	BOOLEAN IsInTestMode;
#ifdef ENABLE_CHANNEL_MESSAGES
	UByte ChannelInfo, LEDCount;
#endif
} wt_headset;

extern wt_headset headset;

// for REV68 headsets:
// Red LED is tied to DECT P2[0]
// Green LED is tied to DECT P2[1]
#define TurnOnRedLED				P2_SET_DATA_REG = Px_0_SET
#define TurnOnGreenLED				P2_SET_DATA_REG = Px_1_SET
#define TurnOnYellowLED				P2_SET_DATA_REG = (Px_0_SET | Px_1_SET)
#define TurnOffYellowLED			P2_RESET_DATA_REG = (Px_0_RESET | Px_1_RESET)

// for REV68 headsets:
// BC5_MIC2 = PIO1 <-> DECT P3[5] = increment PSKEY_USER35
// BC5_MIC1 = PIO2 <-> DECT P3[6] = decrement PSKEY_USER35
#define BC5IncrementGainHiPP		P3_SET_DATA_REG = Px_5_SET
#define BC5IncrementGainLoPP		P3_RESET_DATA_REG = Px_5_RESET
#define BC5DecrementGainHiPP		P3_SET_DATA_REG = Px_6_SET
#define BC5DecrementGainLoPP		P3_RESET_DATA_REG = Px_6_RESET

// for REV68 headsets:
// BC5_TBD4 = PIO6 <-> DECT P3[7] = toggle use of BC5: LO=On(used)/HI=Off(bypass)
#define BC5IsUsedPP					P3_RESET_DATA_REG = Px_7_RESET
#define BC5BypassPP					P3_SET_DATA_REG = Px_7_SET

// we have to bit-bang the SPI_EN signal to the touch board
#define SPI_EN_HI					P0_SET_DATA_REG = Px_4_SET
#define SPI_EN_LO					P0_RESET_DATA_REG = Px_4_RESET

void InitWentworth_pp(void);

#endif /* WENTWORTH_PP_H_ */
