/********************************************************************************
 * 																				*
 *		Wentworth Technology Inc												*
 *		77 Industrial Park Road, Unit 201										*
 *		Saco, Maine, USA 04072													*
 *		+1 207-571-9744															*
 *		www.wentworthtechnology.com												*
 *		copyright 2014															*
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
#define INBOUND_P1					9		// max inbound volume for Alango profile1 setting
#define INBOUND_P0					9		// max inbound volume for Alango profile0 setting
#define GRILL						15		// max grill volume
#define OUTBOUND_P1					11		// max outbound volume for Alango profile1 setting
#define OUTBOUND_P0					11		// max outbound volume for Alango profile0 setting
#define DUAL_BASE_MENU_A			1
#define DUAL_BASE_MENU_B			2

#define PCM_ind						0xD5	// use _FILLER_D5 for 2nd FP commands over PCM bus
//#define REGISTER_PP_ind			0xD6	// use _FILLER_D6 for 2nd FP ???
//#define REGISTER_PP_ind			0xD7	// use _FILLER_D7 for 2nd FP ???
//#define REGISTER_PP_ind			0xD8	// use _FILLER_D8 for 2nd FP ???
//#define REGISTER_PP_ind			0xD9	// use _FILLER_D9 for 2nd FP ???
//#define REGISTER_PP_ind			0xDA	// use _FILLER_DA for 2nd FP ???

#define MAX_Allowed_Users_Dual		5		// limit subscribed PPs to 5 per base for two base systems

// commands between FPs
#define SECOND_BOARD_ind			0xA000	// when second base is present & FP_ARI[0] of second base's ARI
//									0xA1nn - 0xA4nn // FP_ARI[1-4] of second base's ARI
#define REQ_FP_ARI_ind				0xA500	// request ARI of other base
#define REQUEST_PP_SN_ind			0x1A00	// request for PP EmptyMarker & SNs info
//									0x10nn - 0x14nn	// PP[0-4]'s EmptyMarker & SN info
#define PP_ON_ind					0x1B00	// report headset on/off from second base
//									0x1Bn0	// PP[n] off
//									0x1Bn1	// PP[n] on
#define VEHICLE_DET_ind				0x1C00	// report second base VD state to first base for messaging
//									0x1C00	// car not present at menu B
//									0x1C01	// car present at menu B
#define PP_MIC_ind					0x1D00	// report PP MIC_MUTE state to second base for messaging
//									0x1Dn0	// PP[n] MIC is muted
//									0x1Dn1	// PP[n] MIC is open - menu A
//									0x1Dn2	// PP[n] MIC is open - menu B
#define ORDER_TAKER_ind				0x1E00	// report new order taker assignment to other base headsets
//									0x1E1n  // PP[n] is new order taker
//									0x1E0n  // PP[n] is no longer an order taker
#define SYSTEM_MODE_ind				0x1F00	// report SYSTEM_MODE command to second base for messaging
//									0x1Fnx	// x is BC5 state; n is SYSTEM_MODE state
#define BLINK_LED_ind				0x2000	// report BLINK_LED command to second base for messaging
//									0x20nn	// nn is BLINK_LED argument sent to PPs
#define CAR_WAITING_ind				0x2100	// report CAR_WAITING command to second base for messaging
//									0x21nn	// nn is CAR_WAITING argument sent to PPs
#define REGISTER_PP_ind				0x2200	// report REGISTER command to second base
//									0x2200	// do not allow registrations
//									0x2201	// allow registrations
#define DELETE_PP_ind				0x2300	// when DELETE button is pressed on the display
//									0x230n	// PP[n] is being deleted from second base
#define LISTEN_ONLY_PP_ind			0x2400	// when LISTEN_ONLY button is pressed on the display
//									0x24n0	// PP[n] is now in LISTEN_ONLY mode
//									0x24n1	// PP[n] is no longer in LISTEN_ONLY mode
#define REQUEST_PUP_MSB_B_ind		0x2500	// request power on count MSB from second base
//									0x25nn  // reply from second base with MSB count
#define REQUEST_PUP_LSB_B_ind		0x2600	// request power on count LSB from second base
//									0x26nn  // reply from second base with LSB count
#define RESET_PUP_B_ind				0x2700	// request second base power up count to be reset
#define PAGE_CMD_ind				0x2800	// report PP PAGE_CMD command to second base for messaging
//									0x28n0	// PP[n] MIC is muted
//									0x28n1	// PP[n] MIC is open for PAGE
#define VOLUME_SETTINGS_B_ind		0x2900	// request volume settings from second base
//									0x29yn	// request volume change: y - volume item (1-4), n = volume value (0-max)
//									0x29Bn	// update InboundVolB
//									0x29Cn	// update GrillSpeakerVolumeB
//									0x29Dn	// update PostSpeakerVolumeDayB
//									0x29En	// update PostSpeakerVolumeNightB
//									0x29Fn	// update AlangoProfile1B
#define UPDATE_CLOCK_B_ind			0x2A00	// update clock on second base
//									0x2Anx	// n is h1, h2, m1, m2, or day; x is clock or day value
#define UPDATE_NITE_START_B_ind		0x2B00	// update night start time on second base
//									0x2Bnx	// n is h1, h2, m1, m2; x is clock value
#define UPDATE_NITE_STOP_B_ind		0x2C00	// update night stop time on second base
//									0x2Cnx	// n is h1, h2, m1, m2; x is clock value
#define UPDATE_MENU_CFG_B_ind		0x2D00	// update lane configuration on second base
//									0x2D0n	// 0: single lane, 1: parallel menus, 2: tandem menus
#define UPDATE_ALANGO_CFG_B_ind		0x2E00	// update ALANGO profile setting on second base
//									0x2E0n	// 0: profile 0 (MA11), 1: profile 1 (MA10)
#define STOP_WATCHDOG_B_ind			0x2F00	// stop WATCHDOG timer on second base
#define GREETER_REQ_ind				0x3000	// send greeter screen request to second base
//									0x3000	// second base does not have greeter installed
//									0x3011	// second base has greeter installed and on
//									0x3010	// second base has greeter installed and off
//									0x3002	// second base has vehicle present
#define GREETER_0x19_ind			0x3100	// handle x19\x01\x0n from display
//									0x310n	// argument n (1-3 = button pressed)
//									0x31m0	// reply from second base when VD is active; 10 = stop playback, 20 = stop recording
#define GREETER_DATA_START_ind		0x3AAA	// signifies start of data
//									0xFFaa	// msg enable data
//									0xnnmm	// start/stop data
#define GREETER_DATA_STOP_ind		0x3FFF	// signifies all data sent
#define GREETER_B_ACTIVE_ind		0x3B00	// request GREETER B status
//									0x3B1n	// report GREETER B status: 0 - GREETER off, 1 - GREETER on
#define GREETER_B_MSG_ind			0x3C00	// report GREETER B message selection
//									0x3Cnn	// nn is greet/message currently selected for editing
#define GREETER_B_AUTH_ind			0x3D00	// report GREETER B authorization code to second base
//									0x3Dnx	// n is index, x is value

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
	VOLUME_B,
	REGISTRATION,
	PIN,
	NEW_PIN,
	NEW_CLOCK,
	GREETER_PIN,
	GREETER_PIN_B,
	GREETER_SETUP,
	MESSAGE_SETUP1,
	MESSAGE_SETUP2,
	NEW_NIGHT_TIME,
	MENU_CONFIG
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
    UByte	EmptyMarker;			// 1
    UByte	Upi [MaxUpiOctets];		// 4   Total 5
} QuickDatabaseCopyType;

typedef struct
{
	UByte PowerOnStatus;
	BOOLEAN BaseRTC, GreetRTC, UpdateFromRTC;
	UByte FP_ARI[5];
	UByte FP2_ARI[5];
	char SerialNumber[11];
	char SerialNumber2[11];
	BOOLEAN ARI2_Received;
	TimeStruct DisplayTime;
	UByte CurrentDay;
	BOOLEAN DayTime, NighTimeInEffect;
	BOOLEAN FillingRegistrationDisplay;
	UByte HeadsetCounter, DeletionCounter, ListenOnlyCounter;
	BOOLEAN HeadsetIsOn[MAX_Allowed_Users];
	BOOLEAN PageMode[6];												// index is based on channel: PP[0] - PP[5]
	BOOLEAN HeadsetButtonIsPressed[MAX_Allowed_Users];
	BOOLEAN MicIsOn[MAX_Allowed_Users];
	BOOLEAN CarIsWaiting;
	BOOLEAN VehicleDetectIsActive;
	UByte DisplayCommand;
	UByte DisplayCommandLength;
	UByte DisplayCommandData[10];
	Screens DisplayScreen;
	Screens DestAfterPin;
	BOOLEAN DisplayValueChanged;
	UByte PinDigitIndex;
	UByte TempPin[4], TempPin2[4];										// used to hold PIN being entered
	UByte DisplayMasterPin[4];											// is always 2580
	UByte SystemMode, NewSystemMode;
	BOOLEAN RegistrationAllowed, RegistrationButtonPressed;
	UByte OrderTakerID;
	BOOLEAN GreeterInstalled;
	UByte ActiveGreetNumber;
	WORD ActiveMessages;
	BOOLEAN FillingMsgDisplay, GreetClockRunning, AlertWaiting, AlertPlayed, BC5Bypassed, PPCalibration;
	UByte MsgCounter;
	UByte MsgBeingEdited;
	MsgDayNames MsgDayBeingEdited;
	UByte MessageIsPlaying, MessageIsRecording;
	UByte CurrentOutboundVolume;
	WORD CurrentInboundVolumeMixerAtten;
	WORD LastPCMCmdRx;
	BOOLEAN IsUS;
	UByte LaneForChannel[6];											// track which menu each channel (0-5) is open to (channel 5 should never be used?)
	QuickDatabaseCopyType QuickDataBoard2[MAX_Allowed_Users_Dual];		// [Empty, SN1, SN2, SN3, SN4] for MAX_Allowed_Users_Dual
	UByte QuickDataIndex;
	BOOLEAN AlangoProfile1B;
	UByte InboundVolB;
	UByte GrillSpeakerVolumeB;
	UByte PostSpeakerVolumeDayB, PostSpeakerVolumeNightB;
	WORD PowerOnCountB;
	BOOLEAN ReceivingGreetData, GreeterScreenB;
	UByte GreeterInstalledB, GreetData_i, GreetData_ii;
	UByte UsingWirelessPost;

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
	BOOLEAN AlangoProfile1;												// 1
	UByte MenuConfig;													// 1
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
#define GRILL_SPEAKER_ON			P2_SET_DATA_REG = Px_0_SET
#define GRILL_SPEAKER_OFF			P2_RESET_DATA_REG = Px_0_RESET

// CP_EN = controls the SHUTDOWN_AMP_MENU_N and GREET audio path
#define MENU_SPKR_AMP_OFF			CP_CTRL_REG &= ~(CP_EN)				// clear CP_EN to turn CP_VOUT1 off; enables GREET audio path in to DECT MICP/N
#define MENU_SPKR_AMP_ON			CP_CTRL_REG |= (0x0001)				// enable CP_EN to turn only CP_VOUT1 on; enables BC5 audio path in to DECT MICP/N

// P0[7] = controls the GREET audio path
#define GREET_N_HI					P0_SET_DATA_REG = Px_7_SET			// enable DECT SPKR+/- audio path out to BC5
#define GREET_N_LO					P0_RESET_DATA_REG = Px_7_RESET		// enables GREET audio path out to BC5

// BC5 PIO6 <-> DECT P1[5] = Alango profiles: LO = profile 0 (MA11), HI = profile 1 (MA10)
#define ALANGO_PROFILE_0			P1_RESET_DATA_REG = Px_5_RESET
#define ALANGO_PROFILE_1			P1_SET_DATA_REG = Px_5_SET

// P3[7] used to set Menu A or Menu B base
#define FIRST_BASE					(P3_DATA_REG & Px_7_DATA)

// P0[5] is	Output-OD-BP for CB (call button signal to external timer)
#define SET_CB_HI					P0_SET_DATA_REG = Px_5_SET
#define SET_CB_LO					P0_RESET_DATA_REG = Px_5_RESET

// P2[1] is	Output-DIO for TBD (clock to WT greet board)
#define SET_CLOCK_HI				P2_SET_DATA_REG = Px_1_SET
#define SET_CLOCK_LO				P2_RESET_DATA_REG = Px_1_RESET

// P2[7] is	Output-OD-BP for GREET_ENABLE_IN (data to WT greet/message repeater board)
#define SET_MESSAGE_DATA_HI			P2_SET_DATA_REG = Px_7_SET
#define SET_MESSAGE_DATA_LO			P2_RESET_DATA_REG = Px_7_RESET

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
