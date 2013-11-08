/********************************************************************************
 * 																				*
 *		Wentworth Technology Inc												*
 *		77 Industrial Park Road, Unit 201										*
 *		Saco, Maine, USA 04072													*
 *		+1 207-571-9744															*
 *		www.wentworthtechnology.com												*
 *		copyright 2011															*
 *																				*
 ********************************************************************************
 * $History:: wentworth_fp.h												  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */
#ifndef WENTWORTH_FP_H_
#define WENTWORTH_FP_H_

//         20log(atten/32767) = dB
//       10^(dB/20) x 32767 = atten
//	   convenient chart for hex ratios:
//		0x7FFF/0x7FFF = 1.000 (  0.0dB)
//		0x7333/0x7FFF = 0.900 ( -0.9dB)
//		0x6666/0x7FFF = 0.800 ( -1.9dB)
//		0x5FFF/0x7FFF = 0.750 ( -2.5dB)
//		0x5999/0x7FFF = 0.700 ( -3.1dB)
//		0x4CCC/0x7FFF = 0.600 ( -4.4dB)
//		0x3FFF/0x7FFF = 0.500 ( -6.0dB)
//		0x3333/0x7FFF = 0.400 ( -8.0dB)
//		0x2CCC/0x7FFF = 0.350 ( -9.1dB)
//		0x2A9F/0x7FFF = 0.333 ( -9.6dB)
//		0x2666/0x7FFF = 0.300 (-10.5dB)
//		0x2333/0x7FFF = 0.275 (-11.2dB)
//		0x1FFF/0x7FFF = 0.250 (-12.0dB)
//		0x1999/0x7FFF = 0.200 (-14.0dB)
//		0x1249/0x7FFF = 0.143 (-16.9dB) 1/7
//		0x0FFF/0x7FFF = 0.125 (-18.1dB)
//		0x0CCC/0x7FFF = 0.100 (-20.0dB)
//		0x0999/0x7FFF = 0.075 (-22.5dB)
//		0x0666/0x7FFF = 0.050 (-26.0dB)
//		0x0333/0x7FFF = 0.025 (-32.0dB)
//		0x0188/0x7FFF = 0.012 (-38.4dB)
//		0x00C4/0x7FFF = 0.006 (-44.4dB)
//		0x0000/0x7FFF = mute  (-90.0dB)

#define NUM_OF_GREETS				7		// number of greets available
#define NUM_OF_MESSAGES		    	NUM_OF_GREETS + 13 + 1	// number of greets + messages + 1 alert available
#define NUM_LABEL_NAMES				16		// number of different greet/message labels
#define GREET_COMFORT_VOL			-5		// for -10dB gain_inbound during GREET message headset playback
#define NORMAL_INBOUND				1		// for 2dB gain_inbound during normal operation
#define INBOUND_NEAR				9		// max inbound volume for Alango NEAR setting
#define INBOUND_FAR					9		// max inbound volume for Alango FAR setting
#define GRILL						15		// max grill volume
#define OUTBOUND_NEAR				11		// max outbound volume for Alango NEAR setting
#define OUTBOUND_FAR				11		// max outbound volume for Alango FAR setting
#define DUAL_BASE_MASTER			1
#define DUAL_BASE_SLAVE				2

//#define PCM_ind					0xD5	// use _FILLER_D5 for 2nd FP commands over PCM bus
//#define REGISTER_PP_ind			0xD6	// use _FILLER_D6 for 2nd FP ???
//#define REGISTER_PP_ind			0xD7	// use _FILLER_D7 for 2nd FP ???
//#define REGISTER_PP_ind			0xD8	// use _FILLER_D8 for 2nd FP ???
//#define REGISTER_PP_ind			0xD9	// use _FILLER_D9 for 2nd FP ???
//#define REGISTER_PP_ind			0xDA	// use _FILLER_DA for 2nd FP ???

typedef struct
{
	PrimitiveType Primitive;
	UByte Data[100];
} WTMailType;

typedef enum {
	NONE,
	MAIN,
	HELP,
	WENTWORTH_INFO,
	WENTWORTH_INFO_DEBUG,
	TOOLS,
	VOLUME,
	REGISTRATION,
	PIN,
	NEW_PIN,
	NEW_CLOCK,
	GREETER_PIN,
	GREETER_SETUP,
	MESSAGE_SETUP1,
	MESSAGE_SETUP2,
	NEW_NIGHT_TIME,
	CAL_PP_PIN
} Screens;

typedef struct
{
	UByte timeHourMSB;		// 10's : 0 - 2
	UByte timeHourLSB;		//  1's : 0 - 9
	UByte timeMinMSB;		// 10's : 0 - 5
	UByte timeMinLSB;		//  1's : 0 - 9
} TimeStruct;

typedef enum {
	MONDAY,
	FRIDAY,
	SATDAY,
	SUNDAY,
	MAXDAY
} MsgDayNames;

typedef struct
{
	UByte MessageEnableName;								// [7:4] = Su,Sa,F,MT enables and [3:0] = name index
	UByte StartTime[MAXDAY], StopTime[MAXDAY];				// times are: 0-95 x 15 minute intervals
	BOOLEAN StartIsPressed, StopIsPressed, OnOffIsPressed;
} MsgStruct;

typedef struct
{
	UByte PowerOnStatus;
	BOOLEAN DualLane, BaseRTC, GreetRTC, UpdateFromRTC;
	UByte FP_ARI[5];
	char SerialNumber[11];
	TimeStruct DisplayTime;
	UByte CurrentDay;
	BOOLEAN DayTime, NighTimeInEffect;
	BOOLEAN FillingRegistrationDisplay;
	UByte HeadsetCounter, DeletionCounter, ListenOnlyCounter;
	BOOLEAN HeadsetIsOn[MAX_Allowed_Users];
	BOOLEAN PageMode[6];
	BOOLEAN HeadsetButtonIsPressed[MAX_Allowed_Users];
	BOOLEAN MicIsOn[MAX_Allowed_Users];
	BOOLEAN CarIsWaiting;
	BOOLEAN VehicleDetectIsActive;
	BOOLEAN GrillShouldBeOn;
	UByte DisplayCommand;
	UByte DisplayCommandLength;
	UByte DisplayCommandData[10];
	Screens DisplayScreen;
	Screens DestAfterPin;
	BOOLEAN DisplayValueChanged;
	UByte PinDigitIndex;
	UByte TempPin[4], TempPin2[4];										// used to hold PIN being entered
	UByte DisplayMasterPin[4], DisplayCalPPPin[4];						// is always 2580 & 1793
	UByte SystemMode, NewSystemMode;
	BOOLEAN RegistrationAllowed, RegistrationButtonPressed;
	UByte OrderTakerID;
	BOOLEAN GreeterInstalled;
	UByte ActiveGreetNumber;
	WORD ActiveMessages;
	BOOLEAN FillingMsgDisplay, GreetClockRunning, AlertWaiting, AlertPlayed, BC5Bypassed, P33UsedForGreetMux, PPCalibration, CalibratingPPMic, CalibratingPPRcv;
	UByte MsgCounter;
	UByte MsgBeingEdited;
	MsgDayNames MsgDayBeingEdited;
	UByte MessageIsPlaying, MessageIsRecording;
	UByte CurrentOutboundVolume;
	WORD CurrentInboundVolumeMixerAtten;

	// these things need to be saved in EEPROM
	//	WORD FW_REV_MAJOR & FW_REV_MINOR								// 2
	UByte DisplayUserPin[4];											// 4
	UByte DisplayIsLocked;												// 1
	UByte InboundVol;													// 1
	UByte GrillSpeakerVolume;											// 1
	UByte PostSpeakerVolumeDay, PostSpeakerVolumeNight;					// 2
	TimeStruct NightVolumeTimeStart, NightVolumeTimeEnd;				// 8
	UByte ListenOnly[MAX_Allowed_Users];								// 10 = 29 bytes (for general info)
	MsgStruct Message[NUM_OF_MESSAGES];									// 9 x (7 + 13 + 1) (9 bytes for each of 21 messages)
	BOOLEAN GreeterActive;												// 1
	UByte GrtrMsgrAuthCode[4];											// 4 = 194 bytes (for greeter info)
	WORD PowerOnCount;													// 2
	BOOLEAN AlangoNear, PlayGreetInPP;									// 2
	UByte DualBase;														// 1
} wt_base_station;														// EEPROM total = 29 + 194 + 5 = 228 bytes
extern wt_base_station base_station;

// MAX5407_CS <-> DECT P0[4] = VOL_CS = increment/decrement mode
// MAX5407_U/D <-> DECT P0[6] = UPDOWN_GRILL = increment/decrement action
#define VOL_CS_HI					P0_SET_DATA_REG = Px_4_SET
#define VOL_CS_LO					P0_RESET_DATA_REG = Px_4_RESET
#define UPDOWN_GRILL_HI				P0_SET_DATA_REG = Px_6_SET
#define UPDOWN_GRILL_LO				P0_RESET_DATA_REG = Px_6_RESET
#define UPDOWN_GRILL_UP				P0_SET_DATA_REG = Px_6_SET
#define UPDOWN_GRILL_DOWN			P0_RESET_DATA_REG = Px_6_RESET

//	P2[0] = SHUTDOWN_AMP_GRILL_N (grill speaker amp shutdown) = enable (HI) or disable (LO) grill speaker amp
#define P20_STATUS					(P2_DATA_REG & Px_0_DATA)
#define GRILL_SPEAKER_ON			P2_SET_DATA_REG = Px_0_SET
#define GRILL_SPEAKER_OFF			P2_RESET_DATA_REG = Px_0_RESET

// CP_EN = controls the SHUTDOWN_AMP_MENU_N and GREET audio path
#define MENU_SPKR_AMP_OFF			CP_CTRL_REG &= ~(CP_EN)				// clear CP_EN to turn CP_VOUT1 off; enables GREET audio path in to DECT MICP/N
#define MENU_SPKR_AMP_ON			CP_CTRL_REG |= (0x0001)				// enable CP_EN to turn only CP_VOUT1 on; enables BC5 audio path in to DECT MICP/N

// if P3[3] is being used (starting with rev F boards), it controls the GREET audio path
#define GREET_IN_PP_ON				P3_RESET_DATA_REG = Px_3_RESET		// enable BC5 and GREET summed audio path in to DECT MICP/N
#define GREET_IN_PP_OFF				P3_SET_DATA_REG = Px_3_SET			// enable BC5 audio path only (no GREET) in to DECT MICP/N

// P0[7] = controls the GREET audio path
#define GREET_N_HI					P0_SET_DATA_REG = Px_7_SET			// enable DECT SPKR+/- audio path out to BC5
#define GREET_N_LO					P0_RESET_DATA_REG = Px_7_RESET		// enables GREET audio path out to BC5

// BC5 PIO6 <-> DECT P1[5] = Alango profiles: LO = profile 0/far, HI = profile 1/near
#define ALANGO_PROFILE_0			P1_RESET_DATA_REG = Px_5_RESET
#define ALANGO_PROFILE_1			P1_SET_DATA_REG = Px_5_SET

// P0[5] is	Output-OD-BP for CB (call button signal to external timer)
#define SET_CB_HI					P0_SET_DATA_REG = Px_5_SET
#define SET_CB_LO					P0_RESET_DATA_REG = Px_5_RESET

// P2[1] is	Output-DIO for TBD (clock to WT greet board)
#define SET_CLOCK_HI				P2_SET_DATA_REG = Px_1_SET
#define SET_CLOCK_LO				P2_RESET_DATA_REG = Px_1_RESET

// P2[7] is	Output-OD-BP for GREET_ENABLE_IN (data to WT greet/message repeater board)
#define SET_MESSAGE_DATA_HI			P2_SET_DATA_REG = Px_7_SET
#define SET_MESSAGE_DATA_LO			P2_RESET_DATA_REG = Px_7_RESET

// P3[7] is mux control for display UART
#define SWITCH_DISPLAY_TO_MASTER	P3_SET_DATA_REG = Px_7_SET
#define SWITCH_DISPLAY_TO_SLAVE		P3_RESET_DATA_REG = Px_7_RESET

// P3[4] is	MASTER_IN/SLAVE_OUT ACTIVE status
#define P34_STATUS					(P3_DATA_REG & Px_4_DATA)
#define SET_P34_ACTIVE				P3_SET_DATA_REG = Px_4_SET
#define SET_P34_INACTIVE			P3_RESET_DATA_REG = Px_4_RESET

#define GREETER_DISPLAY_SETUP_DELAY	35									// delay before filling screen with buttons

#define MESSAGE_PLAY_START			0x01
#define MESSAGE_PLAY_STOP			0x02
#define MESSAGE_RECORD_START		0x03
#define MESSAGE_RECORD_STOP			0x04
#define MESSAGE_INIT				0x05

void SendAsciiValue(unsigned long int number);
int GetAsciiValue(UByte * buffer, unsigned long int number, int index);
void RefreshOutboundVolume(UByte NewVolume);
void CheckForActiveGreet(void);
void CheckForActiveMessage(void);
void PlayQueuedMessage(void);
void InitWentworth_fp(void);

#endif /* WENTWORTH_FP_H_ */
