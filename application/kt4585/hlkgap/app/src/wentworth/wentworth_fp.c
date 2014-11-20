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
 * $History:: wentworth_fp.c												  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */
#include "../../../../../../include/os/include/tasks.h"
#include "../../../../../../include/os/include/os.h"
#include "../../../../../../include/os/include/os_tasks.h"
#include "../../../../../../include/os/include/os_mail.h"
#include "../../../../../../include/os/include/intmail.h"
#include "../../../../../../include/os/include/os_timer.h"
#include "../../../../../../include/os/include/os_timers.h"
#include "../../../../../../include/os/include/mailprim.h"
#include "../../../../../../include/os/include/maildef.h"
#include "../../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/mac/startup/include/interrupts.h"
#include "../../../../../../include/hlkgap/common/include/aformat.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../../include/hlkgap/app/include/apdbprim.h"
#include "../../../../../../include/common/include/glibc.h"
#include "../../../../../api/include/common/common_general_functions.h"
#include "../../../../../api/include/fp/fp_msf_functions.h"
#include "../dsp/gdsp_local_defines.h"
#include "wentworth_fp.h"
#include "fppp_common.h"
#include "../dsp/gdsp_all_inits.h"
#include "access_bus.h"
#include "afe.h"

UByte WATCHDOGTASK;
UByte WATCHDOGTASKTIMER;
UByte GENERALFPTASK;
UByte GENERALFPTASKTIMER;
UByte GENERALBC5TASK;
UByte GENERALBC5TASKTIMER;
UByte CLOCKTASK;
UByte CLOCKTASKTIMER;
UByte SYSTEMMODETASK;
UByte SYSTEMMODETASKTIMER;
UByte DISPLAYTASK;
UByte DISPLAYTASKTIMER;
UByte VEHICLEDETECTTASK;
UByte VEHICLEDETECTTASKTIMER;
UByte PPDELETETASK;
UByte PPDELETETASKTIMER;
UByte LISTENONLYTASK;
UByte LISTENONLYTASKTIMER;

wt_base_station base_station;

extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void CopyByteToUartTxBuffer(UByte buffer);
extern void ServiceDisplay();
extern void BroadcastCarWaiting(unsigned char value);
extern void BroadcastSystemModeState(PPIDType user);
extern void BroadcastOrderTaker(PPIDType user, unsigned char value);
extern void RegistrationScreen(UByte cmd);
extern void SetupGreeterScreen();
extern void SetupMessageScreen();
extern void RunGreetClock(UByte greet_cmd, UByte greet_selection);
extern void AFESetGainInboundVolumeFP(int vol_set);
extern void AFEDisablePostMicPath(void);
extern void AFEEnablePostMicPath(void);
extern void AFESetGainSpkrVolumeFP(int vol_set);
extern UByte fp_subscription_removeSubscription(PPIDType user);

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

void check_shutdown_grill_pin(void)
{
	if (P20_STATUS == Px_0_DATA)
	{
		AFEEnablePostMicPath();													// enable DECT MIC input
		MENU_SPKR_AMP_ON;														// make sure post speaker is on (enables BC5 audio path in to DECT MICP/N)
	}
	else
	{
		AFEDisablePostMicPath();												// disable DECT MIC input
		MENU_SPKR_AMP_OFF;														// make sure post speaker is off (disables BC5 audio path in to DECT MICP/N)
	}
}

void check_external_relay_pin(void)
{
	// check alarm pin if Alarm Message is enabled
	if (((base_station).ActiveMessages & 0x2000) == 0x2000)
	{
		if (!(base_station).AlertPlayed && !(base_station).AlertWaiting && (~P1_DATA_REG & Px_2_DATA))
		{
//			PrintStatus(0, "****** ALARM MSG: external relay pin-N / P1[2] is LOW *** ");
			if ((base_station).SystemMode == SPEED_TEAM)
			{
				(base_station).AlertWaiting = TRUE;
				PlayQueuedMessage();
			}
			else if (!(base_station).VehicleDetectIsActive)
			{
				MENU_SPKR_AMP_OFF;												// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
				if (((base_station).GrillSpeakerVolume > 0) && ((base_station).DualBase == DUAL_BASE_MASTER))
				{
					// save GRILL volume but turn it down to 0 to play messages in slave headsets
					(base_station).GrillSpeakerPreviousVolume = (base_station).GrillSpeakerVolume;
					(base_station).GrillSpeakerNeedsToBeRestored = TRUE;
					while ((base_station).GrillSpeakerVolume > 0)
					{
						// decrement MAX5407 (tap 0 "down" towards tap 31 direction) to increase attenuation (decrease volume)
						UPDOWN_GRILL_DOWN;										// set up for decrement mode
						VOL_CS_HI;												// lock in decrement mode
						UPDOWN_GRILL_LO;
						UPDOWN_GRILL_HI;
						usec_pause(1);
						UPDOWN_GRILL_LO;
						VOL_CS_LO;												// freeze tap
						(base_station).GrillSpeakerVolume--;
					}
				}
				if ((base_station).DualBase == DUAL_BASE_MASTER)
				{
					GRILL_SPEAKER_ON;											// enable LO headsets to hear message
					AFEEnableMicSpkrPath();										// connect gain_inbound -> gain_spkr_fp
				}
				else
					GRILL_SPEAKER_OFF;											// mute grill speaker during playback
				AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);					// temporarily set inbound for playback comfort
				AFEEnablePostMicPath();											// enable DECT MIC input
				RunGreetClock(MESSAGE_PLAY_START, NUM_OF_MESSAGES);				// play the alarm message
				(base_station).AlertPlayed = TRUE;
			}
			else
				(base_station).AlertWaiting = TRUE;
		}
		else if (((base_station).AlertPlayed || (base_station).AlertWaiting) && (P1_DATA_REG & Px_2_DATA))
		{
//			PrintStatus(0, "****** ALARM MSG: external relay pin-N / P1[2] is HIGH; reset alert flag *** ");
			if (!(base_station).AlertWaiting)
				(base_station).AlertPlayed = FALSE;
		}
	}
}

void ServiceVehicleDetect(BOOLEAN VehicleIsPresent);
void check_VD_pins(void)
{
	if (!(base_station).VehicleDetectIsActive && (~P1_DATA_REG & Px_1_DATA))
	{
//		PrintStatus(0, "****** VD_3V fired *** ");
		ServiceVehicleDetect(TRUE);
	}
	else if ((base_station).VehicleDetectIsActive && (P1_DATA_REG & Px_1_DATA))
	{
//		PrintStatus(0, "****** VD_3V released *** ");
		ServiceVehicleDetect(FALSE);
	}
}

void ServiceVehicleDetect(BOOLEAN VehicleIsPresent)
{
	int i;
	if (VehicleIsPresent && ((base_station).SystemMode != SPEED_TEAM))
	{
		if ((base_station).DisplayScreen == MAIN)
			CopyToUartTxBuffer((UByte *)"m lane_1:lbl_2\r", 15);				// display car on pad icon
		else
			CopyToUartTxBuffer((UByte *)"set e2 2\r", 9);						// notify that car is on pad
		(base_station).VehicleDetectIsActive = TRUE;
		(base_station).CarIsWaiting = TRUE;
		if ((base_station).GreeterActive && ((base_station).MessageIsPlaying > 0))
		{
			RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);	// stops playback of any greet
			if (((base_station).DisplayScreen == GREETER_SETUP) ||
				((base_station).DisplayScreen == MESSAGE_SETUP1) ||
				((base_station).DisplayScreen == MESSAGE_SETUP2))
			{
				CopyToUartTxBuffer((UByte *)"ssb 43 0\r", 9);					// release play button
				CopyToUartTxBuffer((UByte *)"xe 43\r", 6);						// enable play button
				CopyToUartTxBuffer((UByte *)"xe 44\r", 6);						// enable record button
				CopyToUartTxBuffer((UByte *)"xd 45\r", 6);						// disable stop button
			}
		}
		else if ((base_station).GreeterActive && ((base_station).MessageIsRecording > 0))
		{
			RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording of any greet
			if (((base_station).DisplayScreen == GREETER_SETUP) ||
				((base_station).DisplayScreen == MESSAGE_SETUP1) ||
				((base_station).DisplayScreen == MESSAGE_SETUP2))
			{
				CopyToUartTxBuffer((UByte *)"ssb 44 0\r", 9);					// release record button
				CopyToUartTxBuffer((UByte *)"xe 43\r", 6);						// enable play button
				CopyToUartTxBuffer((UByte *)"xe 44\r", 6);						// enable record button
				CopyToUartTxBuffer((UByte *)"xd 45\r", 6);						// disable stop button
			}
		}
		AFESetGainInboundVolumeFP(NORMAL_INBOUND);
		RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
		if ((base_station).P33UsedForGreetMux)
			GREET_IN_PP_OFF;													// enable BC5 audio path only (no GREET) in to DECT MICP/N
		MENU_SPKR_AMP_ON;														// make sure post speaker is on (enables BC5 audio path in to DECT MICP/N)
		if ((base_station).GrillSpeakerNeedsToBeRestored)
		{
			// restore GRILL volume
			(base_station).GrillSpeakerNeedsToBeRestored = FALSE;
			while ((base_station).GrillSpeakerVolume < (base_station).GrillSpeakerPreviousVolume)
			{
				// increment MAX5407 (tap 31 "up" towards tap 0 direction) to decrease attenuation (increase volume)
				UPDOWN_GRILL_UP;												// set up for increment mode
				usec_pause(1);
				VOL_CS_HI;														// lock in increment mode
				UPDOWN_GRILL_LO;
				UPDOWN_GRILL_HI;
				usec_pause(1);
				UPDOWN_GRILL_LO;
				VOL_CS_LO;														// freeze tap
				(base_station).GrillSpeakerVolume++;
			}
		}
		if (((base_station).GrillSpeakerVolume > 0) || ((base_station).DualBase == DUAL_BASE_MASTER))
			GRILL_SPEAKER_ON;													// turn on grill speaker
		(base_station).GrillShouldBeOn = TRUE;
		if ((base_station).DualBase == DUAL_BASE_MASTER)
			AFEDisableMicSpkrPath();											// re-connect p_dynmixer6 -> gain_spkr_fp
		// TODO: CRP - convert usec_pause to use timer
		usec_pause(65535);
		usec_pause(65535);
		AFEEnablePostMicPath();													// enable DECT MIC input
		if ((base_station).GreeterActive)
		{
    		PrintStatus(0, "*** GREET_N is LO *** ");
    		GREET_N_LO;															// drive GREET_N low connects MESSAGE audio path out to BC5
			if ((base_station).ActiveGreetNumber > 0)
			{
				BroadcastCarWaiting(10);										// send "car waiting in lane 1 + no beep" command
				if ((base_station).PlayGreetInPP)
					GREET_IN_PP_ON;												// enable BC5 and GREET summed audio path in to DECT MICP/N
				RunGreetClock(MESSAGE_PLAY_START, (base_station).ActiveGreetNumber);	// sets up and starts playing active greet
			}
			else
				BroadcastCarWaiting(11);										// send "car waiting in lane 1 + beep" command
		}
		else
			BroadcastCarWaiting(11);											// send "car waiting in lane 1 + beep" command
	}
	else if (!VehicleIsPresent)
	{
		if ((base_station).DisplayScreen == MAIN)								// display no car on pad icon
			CopyToUartTxBuffer((UByte *)"m lane_1:lbl_1\r", 15);
		else
			CopyToUartTxBuffer((UByte *)"set e2 1\r", 9);						// notify that car is not on pad
		(base_station).VehicleDetectIsActive = FALSE;
		(base_station).CarIsWaiting = FALSE;
		AFEDisablePostMicPath();												// disable DECT MIC input
		GRILL_SPEAKER_OFF;														// turn off grill speaker
		(base_station).GrillShouldBeOn = FALSE;
		MENU_SPKR_AMP_OFF;														// turn off post speaker (enables GREET audio path in to DECT MICP/N)
	    BroadcastCarWaiting(0);													// send "no car waiting" command
		for (i = 0; i < MAX_Allowed_Users; i++)
		{
			// if any headset is on from the previous mode, now it is off
			if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
				(base_station).MicIsOn[i] = FALSE;
		}
//		PrintStatus(0, "*** CB is LO, GREET_N is HI *** ");
		SET_CB_LO;																// drive CB low
		GREET_N_HI;																// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
		if ((base_station).GreeterActive)
		{
			if ((base_station).MessageIsPlaying > 0)
				RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);
			PlayQueuedMessage();												// play any waiting alert or reminder
		}
		if (((base_station).DisplayScreen == GREETER_SETUP) ||
			((base_station).DisplayScreen == MESSAGE_SETUP1) ||
			((base_station).DisplayScreen == MESSAGE_SETUP2))					// configure post mic/speaker for greeter recording
		{
			RefreshOutboundVolume(3);											// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);						// temporarily set inbound for playback comfort
		}
	}
}

//============================
// void SendAsciiValue(unsigned long int number)
// takes "number" and sends it to the UART as ASCII byte values
// Example: 135 (or 0x87) will be sent as ASCII bytes '1', '3', and '5'
//============================
void SendAsciiValue(unsigned long int number)
{
	int i;
	BOOLEAN AfterFirstDigit = FALSE;
	unsigned long int count, test, power = 0;

	for (i = 0; i < 9; i++)
	{
		switch(i)
		{
		    case 0: power = 1000000000; break;
		    case 1: power = 100000000; break;
		    case 2: power = 10000000; break;
		    case 3: power = 1000000; break;
		    case 4: power = 100000; break;
			case 5: power = 10000; break;
			case 6: power = 1000; break;
			case 7: power = 100; break;
			case 8: power = 10; break;
		}

		test = 0;
		count = 0;

		while (number >= test)
		{
			if ((test + power) > number)
			{
				number -= test;
				test += power;
			}
			else
			{
				test += power;
				count++;
			}
		}

		switch (count)
		{
			case 1: CopyByteToUartTxBuffer('1'); AfterFirstDigit = TRUE; break;
			case 2: CopyByteToUartTxBuffer('2'); AfterFirstDigit = TRUE; break;
			case 3: CopyByteToUartTxBuffer('3'); AfterFirstDigit = TRUE; break;
			case 4: CopyByteToUartTxBuffer('4'); AfterFirstDigit = TRUE; break;
			case 5: CopyByteToUartTxBuffer('5'); AfterFirstDigit = TRUE; break;
			case 6: CopyByteToUartTxBuffer('6'); AfterFirstDigit = TRUE; break;
			case 7: CopyByteToUartTxBuffer('7'); AfterFirstDigit = TRUE; break;
			case 8: CopyByteToUartTxBuffer('8'); AfterFirstDigit = TRUE; break;
			case 9: CopyByteToUartTxBuffer('9'); AfterFirstDigit = TRUE; break;
		}

		if (count == 0 && AfterFirstDigit)
		{
			CopyByteToUartTxBuffer('0');
		}
	}

	switch (number)
	{
		case 0: CopyByteToUartTxBuffer('0'); break;
		case 1: CopyByteToUartTxBuffer('1'); break;
		case 2: CopyByteToUartTxBuffer('2'); break;
		case 3: CopyByteToUartTxBuffer('3'); break;
		case 4: CopyByteToUartTxBuffer('4'); break;
		case 5: CopyByteToUartTxBuffer('5'); break;
		case 6: CopyByteToUartTxBuffer('6'); break;
		case 7: CopyByteToUartTxBuffer('7'); break;
		case 8: CopyByteToUartTxBuffer('8'); break;
		case 9: CopyByteToUartTxBuffer('9'); break;
	}
}

//============================
// int GetAsciiValue(UByte * buffer_ptr, unsigned long int number, int index)
// takes "number" and converts it to an ASCII string, appends it to buffer_ptr[index] and returns the length of the string
// Example: 135 will create ASCII string "135" and return 3
//============================
int GetAsciiValue(UByte * buffer_ptr, unsigned long int number, int index)
{
	int i, length = 0;
	BOOLEAN AfterFirstDigit = FALSE;
	unsigned long int count, test, power = 0;

	for (i = 0; i < 9; i++)
	{
		switch(i)
		{
		    case 0: power = 1000000000; break;
		    case 1: power = 100000000; break;
		    case 2: power = 10000000; break;
		    case 3: power = 1000000; break;
		    case 4: power = 100000; break;
			case 5: power = 10000; break;
			case 6: power = 1000; break;
			case 7: power = 100; break;
			case 8: power = 10; break;
		}

		test = 0;
		count = 0;

		while (number >= test)
		{
			if ((test + power) > number)
			{
				number -= test;
				test += power;
			}
			else
			{
				test += power;
				count++;
			}
		}

		switch (count)
		{
		    case 1: memcpy(buffer_ptr + index + length++, "1", 1); AfterFirstDigit = TRUE; break;
			case 2: memcpy(buffer_ptr + index + length++, "2", 1); AfterFirstDigit = TRUE; break;
			case 3: memcpy(buffer_ptr + index + length++, "3", 1); AfterFirstDigit = TRUE; break;
			case 4: memcpy(buffer_ptr + index + length++, "4", 1); AfterFirstDigit = TRUE; break;
			case 5: memcpy(buffer_ptr + index + length++, "5", 1); AfterFirstDigit = TRUE; break;
			case 6: memcpy(buffer_ptr + index + length++, "6", 1); AfterFirstDigit = TRUE; break;
			case 7: memcpy(buffer_ptr + index + length++, "7", 1); AfterFirstDigit = TRUE; break;
			case 8: memcpy(buffer_ptr + index + length++, "8", 1); AfterFirstDigit = TRUE; break;
			case 9: memcpy(buffer_ptr + index + length++, "9", 1); AfterFirstDigit = TRUE; break;
		}

		if (count == 0 && AfterFirstDigit)
		{
			memcpy(buffer_ptr + index + length++, "0", 1);
		}
	}

	switch (number)
	{
		case 0: memcpy(buffer_ptr + index + length++, "0", 1); break;
		case 1: memcpy(buffer_ptr + index + length++, "1", 1); break;
		case 2: memcpy(buffer_ptr + index + length++, "2", 1); break;
		case 3: memcpy(buffer_ptr + index + length++, "3", 1); break;
		case 4: memcpy(buffer_ptr + index + length++, "4", 1); break;
		case 5: memcpy(buffer_ptr + index + length++, "5", 1); break;
		case 6: memcpy(buffer_ptr + index + length++, "6", 1); break;
		case 7: memcpy(buffer_ptr + index + length++, "7", 1); break;
		case 8: memcpy(buffer_ptr + index + length++, "8", 1); break;
		case 9: memcpy(buffer_ptr + index + length++, "9", 1); break;
	}
	return length;
}

void CheckNightVolumeTime(void)
{
	BOOLEAN changed;
	// first case is when NightTime is NOT in effect (StartTime is equal to EndTime)
	if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4)== 0)
	{
		if ((base_station).DayTime)
			changed = FALSE;
		else
		{
			(base_station).DayTime = TRUE;
			changed = TRUE;
		}

	}
	// second case is when NightTime DOES span across 23:59 (StartTime is greater than EndTime)
	else if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4) > 0)
	{
		// Night Time volume is enabled so check if we are in Night time
		if (!((memcmp(&(base_station).DisplayTime, &(base_station).NightVolumeTimeStart, 4) < 0) &&
		     ((memcmp(&(base_station).DisplayTime, &(base_station).NightVolumeTimeEnd, 4) > 0) ||
			  (memcmp(&(base_station).DisplayTime, &(base_station).NightVolumeTimeEnd, 4) == 0))))
		{
			// switch to NightTime
			if ((base_station).DayTime)
			{
				(base_station).DayTime = FALSE;
				changed = TRUE;
			}
			else
				changed = FALSE;
		}
		else
		{
			// switch to DayTime
			if ((base_station).DayTime)
				changed = FALSE;
			else
			{
				(base_station).DayTime = TRUE;
				changed = TRUE;
			}
		}
	}
	// third case is when NightTime does NOT span across 23:59 (StartTime is less than EndTime)
	else if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4) < 0)
	{
		// Night Time volume is enabled so check if we are in Night time
		if ((memcmp(&(base_station).DisplayTime, &(base_station).NightVolumeTimeEnd, 4) < 0) &&
		   ((memcmp(&(base_station).DisplayTime, &(base_station).NightVolumeTimeStart, 4) > 0) ||
		    (memcmp(&(base_station).DisplayTime, &(base_station).NightVolumeTimeStart, 4) == 0)))
		{
			// switch to NightTime
			if ((base_station).DayTime)
			{
				(base_station).DayTime = FALSE;
				changed = TRUE;
			}
			else
				changed = FALSE;
		}
		else
		{
			// switch to DayTime
			if ((base_station).DayTime)
				changed = FALSE;
			else
			{
				(base_station).DayTime = TRUE;
				changed = TRUE;
			}
		}
	}

	if (changed)
	{
		if ((base_station).DisplayScreen == MAIN)
			if ((base_station).DayTime)
			CopyToUartTxBuffer((UByte *)"m volume_indicator:lbl_1\r", 25);		// display DayTime icon
		else
			CopyToUartTxBuffer((UByte *)"m volume_indicator:lbl_0\r", 25);		// display NightTime icon
		else
			if ((base_station).DayTime)
				CopyToUartTxBuffer((UByte *)"set e4 1\r", 9);					// notify of DayTime mode
			else
				CopyToUartTxBuffer((UByte *)"set e4 0\r", 9);					// notify of NightTime mode
	}
}

void RefreshOutboundVolume(UByte NewVolume)
{
	if (NewVolume != (base_station).CurrentOutboundVolume)
	{
		AFESetGainSpkrVolumeFP(NewVolume);
		(base_station).CurrentOutboundVolume = NewVolume;
	}
	else
		return;
}

void CheckForActiveGreet()
{
	UByte i, SchedDay = 0, DayMask;
	WORD CurrMins = 0;

//	CopyToUartTxBuffer((UByte *)"t \"                               \" 150 100\r", 44);

	if ((base_station).GreeterActive && ((base_station).SystemMode != SPEED_TEAM))
	{
//		CopyToUartTxBuffer((UByte *)"t \"greets allowed\" 150 100\r", 27);
		// CurrentDay : SchedDay
		//		M	0 : 0
		//		T	1 : 0
		//		W	2 : 0
		//		Th	3 : 0
		//		F	4 : 1
		//		Sa	5 : 2
		//		Su	6 : 3
		if ((base_station).CurrentDay < 3)
			SchedDay = 0;
		else
			SchedDay = (base_station).CurrentDay - 3;
		DayMask = 4 + SchedDay;
		// current time in minutes = (((H2 * 10) + H1) * 60) + (M2 * 10) + M1
		CurrMins = (((base_station).DisplayTime.timeHourMSB * 10) + (base_station).DisplayTime.timeHourLSB) * 60;
		CurrMins += ((base_station).DisplayTime.timeMinMSB * 10) + (base_station).DisplayTime.timeMinLSB;

		if ((base_station).ActiveGreetNumber > 0)
		{
			// first check if previous greet is still active
			i = (base_station).ActiveGreetNumber - 1;
			if (((base_station).Message[i].MessageEnableName & (1 << DayMask)) == (1 << DayMask))
			{
				// check if greet spans 23:59
				if ((base_station).Message[i].StartTime[SchedDay] > (base_station).Message[i].StopTime[SchedDay])
				{
					if ((CurrMins > ((WORD)(base_station).Message[i].StopTime[SchedDay] * 15 + 14)) && (CurrMins < ((WORD)(base_station).Message[i].StartTime[SchedDay] * 15)))
					{
						// outside the current greet's time window so cancel it
						(base_station).ActiveGreetNumber = 0;
					}
				}
				else
				{
					if ((CurrMins < ((WORD)(base_station).Message[i].StartTime[SchedDay] * 15)) || (CurrMins > ((WORD)(base_station).Message[i].StopTime[SchedDay] * 15 + 14)))
					{
						// past the current greet's stop time so cancel it
						(base_station).ActiveGreetNumber = 0;
					}
				}
			}
			else
			{
				(base_station).ActiveGreetNumber = 0;
			}
		}

		if ((base_station).ActiveGreetNumber == 0)
		{
			for (i = 0; i < NUM_OF_GREETS; i++)
			{
				if (((base_station).Message[i].MessageEnableName & (1 << DayMask)) == (1 << DayMask))
				{
					// check if greet spans 23:59
					if ((base_station).Message[i].StartTime[SchedDay] > (base_station).Message[i].StopTime[SchedDay])
					{
						if ((CurrMins <= ((WORD)(base_station).Message[i].StopTime[SchedDay] * 15 + 14)) || (CurrMins >= ((WORD)(base_station).Message[i].StartTime[SchedDay] * 15)))
						{
							(base_station).ActiveGreetNumber = i + 1;
							break;
						}
					}
					else
					{
						if ((CurrMins >= ((WORD)(base_station).Message[i].StartTime[SchedDay] * 15)) && (CurrMins <= ((WORD)(base_station).Message[i].StopTime[SchedDay] * 15 + 14)))
						{
							(base_station).ActiveGreetNumber = i + 1;
						}
					}
				}
			}
		}
	}
}

void CheckForActiveMessage()
{
	UByte i, ii, Today;
	WORD CurrTime;

	// CurrentDay : SchedDay
	//		M	0 : 0
	//		T	1 : 0
	//		W	2 : 0
	//		Th	3 : 0
	//		F	4 : 1
	//		Sa	5 : 2
	//		Su	6 : 3
	if ((base_station).CurrentDay < 3)
		Today = 0;
	else
		Today = (base_station).CurrentDay - 3;

	// current time in minutes = (((H2 * 10) + H1) * 60) + (M2 * 10) + M1
	CurrTime = (((base_station).DisplayTime.timeHourMSB * 10) + (base_station).DisplayTime.timeHourLSB) * 60;
	CurrTime += ((base_station).DisplayTime.timeMinMSB * 10) + (base_station).DisplayTime.timeMinLSB;

	// if the current time is :00, :15, :30, or :45, check if any messages are scheduled to be played
	if ((div16(CurrTime, 15) * 15) == CurrTime)
	{
		CurrTime = div16(CurrTime, 15);					// matches StartTime[]/StopTime[] 15 minute format
		for (i = 7; i < (NUM_OF_MESSAGES - 1); i++)
		{
			// check if message is "on" for current day
			if (((base_station).Message[i].MessageEnableName & (1 << (Today + 4))) == (1 << (Today + 4)))
			{
				// check if the msg start time is =< CurrTime
				if ((base_station).Message[i].StartTime[Today] <= CurrTime)
				{
					// check if message should be playing
					if ((base_station).Message[i].StartTime[Today] == CurrTime)
					{
						// it should be playing so mark it and check the next one
						(base_station).ActiveMessages = (base_station).ActiveMessages | (1 << (i - 7));
					}
					else if ((base_station).Message[i].StopTime[Today] > 0)
					{
						// if it's set up to repeat, check the intervals through the rest of the current day
						for (ii = 1; ii < 96; ii++)
						{
							if (((base_station).Message[i].StartTime[Today] + ((base_station).Message[i].StopTime[Today] * ii) ) > 95)
							{
								// this time slot is past midnight so don't bother checking it and we're done checking this reminder
								ii = 96;
							}
							else if (((base_station).Message[i].StartTime[Today] + ((base_station).Message[i].StopTime[Today] * ii) ) == CurrTime)
							{
								// this interval should be playing so mark it and check the next one
								(base_station).ActiveMessages = (base_station).ActiveMessages | (1 << (i - 7));
								ii = 96;
							}
						}
					}
				}
			}
		}
	}
	// always check if Alarm message is "on" for current day
	if (((base_station).Message[NUM_OF_MESSAGES - 1].MessageEnableName & (1 << (Today + 4))) == (1 << (Today + 4)))
	{
		(base_station).ActiveMessages = (base_station).ActiveMessages | (1 << (NUM_OF_MESSAGES - NUM_OF_GREETS - 1));
	}
	else
	{
		(base_station).ActiveMessages = (base_station).ActiveMessages & ~(1 << (NUM_OF_MESSAGES - NUM_OF_GREETS - 1));
	}
//char *ptr;
//ptr = StringPrint(StatusString, "(base_station).ActiveMessages = 0x");
//ptr = StrPrintHexWord(ptr, (base_station).ActiveMessages);
//ptr = StringPrint(ptr, " ");
//PrintStatus(0, StatusString);
}

void PlayQueuedMessage()
{
	BOOLEAN AnyMicIsOpen = FALSE;
	UByte i;

	// if (no vehicle detect active) AND (the alarm alert message is active) AND (there's an alert waiting to be played)
	if (!(base_station).VehicleDetectIsActive && (((base_station).ActiveMessages & 0x2000) == 0x2000) && (base_station).AlertWaiting)
	{
		if ((base_station).SystemMode == SPEED_TEAM)
		{
			// check for any on keyed headsets before playing active message
			for (i = 0; i < MAX_Allowed_Users; i++)
			{
				if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
				{
					AnyMicIsOpen = TRUE;
					i = MAX_Allowed_Users;
				}
			}
			if (AnyMicIsOpen)
				return;
		}
		MENU_SPKR_AMP_OFF;																	// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		if (((base_station).GrillSpeakerVolume > 0) && ((base_station).DualBase == DUAL_BASE_MASTER))
		{
			// save GRILL volume but turn it down to 0 to play messages in slave headsets
			(base_station).GrillSpeakerPreviousVolume = (base_station).GrillSpeakerVolume;
			(base_station).GrillSpeakerNeedsToBeRestored = TRUE;
			while ((base_station).GrillSpeakerVolume > 0)
			{
				// decrement MAX5407 (tap 0 "down" towards tap 31 direction) to increase attenuation (decrease volume)
				UPDOWN_GRILL_DOWN;															// set up for decrement mode
				VOL_CS_HI;																	// lock in decrement mode
				UPDOWN_GRILL_LO;
				UPDOWN_GRILL_HI;
				usec_pause(1);
				UPDOWN_GRILL_LO;
				VOL_CS_LO;																	// freeze tap
				(base_station).GrillSpeakerVolume--;
			}
		}
		if ((base_station).DualBase == DUAL_BASE_MASTER)
		{
			GRILL_SPEAKER_ON;																// enable LO headsets to hear message
			AFEEnableMicSpkrPath();															// connect gain_inbound -> gain_spkr_fp
		}
		else
			GRILL_SPEAKER_OFF;																// mute grill speaker during playback
		AFEEnablePostMicPath();																// enable DECT MIC input
		AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);										// temporarily set inbound for playback comfort
		RunGreetClock(MESSAGE_PLAY_START, NUM_OF_MESSAGES);									// play the alert
		(base_station).AlertWaiting = FALSE;
		(base_station).AlertPlayed = TRUE;
	}
	// else if any alert is waiting to be played
	else if (((base_station).ActiveMessages & 0x1FFF) != 0x0000)
	{
		// if (no vehicle detect active) AND (not in speed team mode)
		if (!(base_station).VehicleDetectIsActive && (base_station).SystemMode != SPEED_TEAM)
		{
			//look for next active message
			for (i = 0; i < (NUM_OF_MESSAGES - NUM_OF_GREETS - 1); i++)
			{
				// check each reminder to see if it's active
				if (((base_station).ActiveMessages & (1 << i)) == (1 << i))
				{
					(base_station).ActiveMessages = (base_station).ActiveMessages & ~(1 << i);
					MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
					if (((base_station).GrillSpeakerVolume > 0) && ((base_station).DualBase == DUAL_BASE_MASTER))
					{
						// save GRILL volume but turn it down to 0 to play messages in slave headsets
						(base_station).GrillSpeakerPreviousVolume = (base_station).GrillSpeakerVolume;
						(base_station).GrillSpeakerNeedsToBeRestored = TRUE;
						while ((base_station).GrillSpeakerVolume > 0)
						{
							// decrement MAX5407 (tap 0 "down" towards tap 31 direction) to increase attenuation (decrease volume)
							UPDOWN_GRILL_DOWN;												// set up for decrement mode
							VOL_CS_HI;														// lock in decrement mode
							UPDOWN_GRILL_LO;
							UPDOWN_GRILL_HI;
							usec_pause(1);
							UPDOWN_GRILL_LO;
							VOL_CS_LO;														// freeze tap
							(base_station).GrillSpeakerVolume--;
						}
					}
					if ((base_station).DualBase == DUAL_BASE_MASTER)
					{
						GRILL_SPEAKER_ON;													// enable LO headsets to hear message
						AFEEnableMicSpkrPath();												// connect gain_inbound -> gain_spkr_fp
					}
					else
						GRILL_SPEAKER_OFF;													// mute grill speaker during playback
					AFEEnablePostMicPath();													// enable DECT MIC input
					AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
					RunGreetClock(MESSAGE_PLAY_START, (i + 8));								// play the reminder
					i = NUM_OF_MESSAGES - NUM_OF_GREETS - 1;								// skip checking the rest until the next clock tick
				}
			}
		}
		// if (the greeter is active) AND (in speed team mode)
		else if ((base_station).GreeterActive && ((base_station).SystemMode == SPEED_TEAM))
		{
			// check for any on keyed headsets before playing active message
			for (i = 0; i < MAX_Allowed_Users; i++)
			{
				if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
				{
					AnyMicIsOpen = TRUE;
					i = MAX_Allowed_Users;
				}
			}
			if (!AnyMicIsOpen)
			{
				//look for next active message
				for (i = 0; i < (NUM_OF_MESSAGES - NUM_OF_GREETS - 1); i++)
				{
					// check each reminder to see if it's active
					if (((base_station).ActiveMessages & (1 << i)) == (1 << i))
					{
						(base_station).ActiveMessages = (base_station).ActiveMessages & ~(1 << i);
						MENU_SPKR_AMP_OFF;													// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
						if (((base_station).GrillSpeakerVolume > 0) && ((base_station).DualBase == DUAL_BASE_MASTER))
						{
							// save GRILL volume but turn it down to 0 to play messages in slave headsets
							(base_station).GrillSpeakerPreviousVolume = (base_station).GrillSpeakerVolume;
							(base_station).GrillSpeakerNeedsToBeRestored = TRUE;
							while ((base_station).GrillSpeakerVolume > 0)
							{
								// decrement MAX5407 (tap 0 "down" towards tap 31 direction) to increase attenuation (decrease volume)
								UPDOWN_GRILL_DOWN;											// set up for decrement mode
								VOL_CS_HI;													// lock in decrement mode
								UPDOWN_GRILL_LO;
								UPDOWN_GRILL_HI;
								usec_pause(1);
								UPDOWN_GRILL_LO;
								VOL_CS_LO;													// freeze tap
								(base_station).GrillSpeakerVolume--;
							}
						}
						if ((base_station).DualBase == DUAL_BASE_MASTER)
						{
							GRILL_SPEAKER_ON;												// enable LO headsets to hear message
							AFEEnableMicSpkrPath();											// connect gain_inbound -> gain_spkr_fp
						}
						else
							GRILL_SPEAKER_OFF;												// mute grill speaker during playback
						AFEEnablePostMicPath();												// enable DECT MIC input
						AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);						// temporarily set inbound for playback comfort
						RunGreetClock(MESSAGE_PLAY_START, (i + 8));							// play the reminder
						i = NUM_OF_MESSAGES - NUM_OF_GREETS - 1;							// skip checking the rest until the next clock tick
					}
				}
			}
		}
	}
}

// task timer to run clock for external watchdog
static void watchdogtasktimer(MailType * MailPtr)
{
	switch (MailPtr->Primitive)
	{
		case INITTASK:
    		SET_CLOCK_HI;
			OSStartTimer(WATCHDOGTASKTIMER, 100); 			// 100 x 10ms = 1s pause before toggling P2[1]
			break;
		case TIMEOUT:
	    	if (!(base_station).GreetClockRunning)
	    	{
				if (P2_DATA_REG & Px_1_DATA)
					SET_CLOCK_LO;
				else
					SET_CLOCK_HI;
	    	}
			OSStartTimer(WATCHDOGTASKTIMER, 100); 			// 100 x 10ms = 1s pause before toggling P2[1]
			break;
	}
}

static void wentworth_fptask(MailType * MailPtr)
{
	WTMailType *msg_ptr=(WTMailType *)MailPtr; // WT reuse a MailType - we just need to get the first couple of bytes after the primitive
//	char *ptr;
	switch (MailPtr->Primitive)
	{
		case INITTASK:
			break;
		case TIMEOUT:
			break;
		default:
			// save the display command and arguments and call ServiceDisplay()
			(base_station).DisplayCommand = msg_ptr->Primitive;
			(base_station).DisplayCommandLength = msg_ptr->Data[0];
			int i;
			for (i = 0; i < (base_station).DisplayCommandLength; i++)
				(base_station).DisplayCommandData[i] = msg_ptr->Data[i + 1];
			ServiceDisplay();
			break;
	}
}

// general timer
static void generalfptasktimer(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      break;
    case TIMEOUT:
      if ((base_station).FillingRegistrationDisplay)
      {
    	// continue filling out headset registration buttons
    	RegistrationScreen(0x03);
    	return;
      }
      if ((base_station).FillingMsgDisplay)
      {
  		if ((base_station).DisplayScreen == GREETER_SETUP)
    	// continue filling out greeter set up buttons
    	  SetupGreeterScreen();
  		else
  		  SetupMessageScreen();
    	return;
      }
      break;
  }
}

// general timer for handling BC5 pulses
static void generalbc5tasktimer(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      OSStartTimer(GENERALBC5TASKTIMER, 200); 			// 200 x 10ms = 2s pause before reading the EEPROM
      break;
    case TIMEOUT:
#ifdef ECT_DSP_MESSAGES
        extern int getAllocatedMemory();
        char *ptr;
        ptr = StringPrint(StatusString,"GetAllocatedMemory [");
        ptr = StrPrintHexWord(ptr,   getAllocatedMemory());
        ptr = StringPrint(ptr,"] ");
        PrintStatus(0,StatusString);
#endif
      general_startTimer(-1, READ_WTDATA_EEPROM, NULL, 0, 100);	// Next we read previously stored values
      break;
  }
}

// general timer for "clock"
static void clocktasktimer(MailType * MailPtr)
{
	BOOLEAN PreviousDayTime;
	UByte i;
	WORD CurrMins = 0;
	char Days[7][9] =
	{
		"Monday   ",
		"Tuesday  ",
		"Wednesday",
		"Thursday ",
		"Friday   ",
		"Saturday ",
		"Sunday   "
	};

	switch (MailPtr->Primitive)
	{
	case INITTASK:
		OSStartTimer(CLOCKTASKTIMER, 6000); 			// 6000 x 10ms = 1 minute
		break;
    case TIMEOUT:
		// H1 H2 : M1 M2
		if ((base_station).DisplayTime.timeMinLSB < 9)
			(base_station).DisplayTime.timeMinLSB++;
		else
		{
			(base_station).DisplayTime.timeMinLSB = 0;
			if ((base_station).DisplayTime.timeMinMSB < 5)
				(base_station).DisplayTime.timeMinMSB++;
			else
			{
				(base_station).DisplayTime.timeMinMSB = 0;
				if ((base_station).DisplayTime.timeHourLSB < 9)
				{
					if ((base_station).DisplayTime.timeHourMSB < 2)
					{
						(base_station).DisplayTime.timeHourLSB++;
					}
					else if ((base_station).DisplayTime.timeHourLSB < 3)
					{
						(base_station).DisplayTime.timeHourLSB++;
					}
					else
					{
						(base_station).DisplayTime.timeHourLSB = 0;
						(base_station).DisplayTime.timeHourMSB = 0;
						if ((base_station).CurrentDay < 6)
							(base_station).CurrentDay++;
						else
							(base_station).CurrentDay = 0;
					}
				}
				else
				{
					(base_station).DisplayTime.timeHourLSB = 0;
					(base_station).DisplayTime.timeHourMSB++;
				}
			}
		}

		if (((base_station).GreeterActive || (base_station).NighTimeInEffect) && (base_station).DisplayScreen == MAIN)
		{
			CopyToUartTxBuffer((UByte *)"m clock ", 8);
			CopyByteToUartTxBuffer((base_station).DisplayTime.timeHourMSB + 0x30);
			CopyByteToUartTxBuffer((base_station).DisplayTime.timeHourLSB + 0x30);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer((base_station).DisplayTime.timeMinMSB + 0x30);
			CopyByteToUartTxBuffer((base_station).DisplayTime.timeMinLSB + 0x30);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			for (i = 0; i < 9; i++) { CopyByteToUartTxBuffer(Days[(base_station).CurrentDay][i]); }
			CopyByteToUartTxBuffer('\"');
			CopyByteToUartTxBuffer('\r');
		}

		PreviousDayTime = (base_station).DayTime;
		CheckNightVolumeTime();		// update sun/moon icon
		if ((base_station).DayTime != PreviousDayTime)
			RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);

		if ((base_station).GreeterActive)
		{
			CheckForActiveGreet();

			CheckForActiveMessage();
			PlayQueuedMessage();
		}

		if ((base_station).BaseRTC || (base_station).GreetRTC)
		{
			CurrMins = (((base_station).DisplayTime.timeHourMSB * 10) + (base_station).DisplayTime.timeHourLSB) * 60;
			CurrMins += ((base_station).DisplayTime.timeMinMSB * 10) + (base_station).DisplayTime.timeMinLSB;
			if ((base_station).UpdateFromRTC && (CurrMins == 180) && ((base_station).MessageIsPlaying == 0) && ((base_station).MessageIsRecording == 0))
			{
				SetupAccess1Bus();						// switch from PCM to ACCESS1 config
				if ((base_station).BaseRTC)
					BASE_RTC_ON;						// connect Base RTC
				else if ((base_station).GreetRTC)
					RunGreetClock(MESSAGE_INIT, 2);		// connect Greeter RTC
				// set current time from RTC at 03:00
				(base_station).DisplayTime.timeMinMSB = ReadAccess1(RTC, 0x01);
				(base_station).DisplayTime.timeMinLSB = ((base_station).DisplayTime.timeMinMSB & 0x0F);
				(base_station).DisplayTime.timeMinMSB = ((base_station).DisplayTime.timeMinMSB & 0xF0) >> 4;
				(base_station).DisplayTime.timeHourMSB = ReadAccess1(RTC, 0x02);
				(base_station).DisplayTime.timeHourLSB = ((base_station).DisplayTime.timeHourMSB & 0x0F);
				(base_station).DisplayTime.timeHourMSB = ((base_station).DisplayTime.timeHourMSB & 0xF0) >> 4;
				(base_station).CurrentDay = (ReadAccess1(RTC, 0x03) & 0x07) - 1;		// base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
				(base_station).UpdateFromRTC = FALSE;
				if ((base_station).BaseRTC)
					BASE_PCM_ON;						// disconnect Base RTC
				else if ((base_station).GreetRTC)
					RunGreetClock(MESSAGE_INIT, 1);		// disconnect Greeter RTC
				SetupPCMBus();							// switch from ACCESS1 to PCM config
			}
			else if (!(base_station).UpdateFromRTC && CurrMins > 239)
			{
				// set the UpdateFromRTC flag again any time after 04:00
				(base_station).UpdateFromRTC = TRUE;
			}
		}

		OSStartTimer(CLOCKTASKTIMER, 6000); 			// 6000 x 10ms = 1 minute
		break;
	}
}

// general timer used for changing System Mode
static void systemmodetasktimer(MailType * MailPtr)
{
  int i;
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      break;
    case TIMEOUT:
	  if (((base_station).SystemMode != (base_station).NewSystemMode) && ((base_station).NewSystemMode != 0))
	  {
		// a new system mode was selected that is different from current system mode
		(base_station).SystemMode = (base_station).NewSystemMode;
		if ((base_station).OrderTakerID != 0xFF)
		{
		  // reset the order taker when system mode changes
		  BroadcastOrderTaker((base_station).OrderTakerID, 0);
		  (base_station).OrderTakerID = 0xFF;
		}
		if ((base_station).NewSystemMode == SPEED_TEAM)
		  ServiceVehicleDetect(FALSE);
		AFEDisablePostMicPath();				// disable DECT MIC input initially in all modes
		MENU_SPKR_AMP_OFF;						// mute the menu board speaker initially in all modes (enables GREET audio path in to DECT MICP/N)
		if ((base_station).NewSystemMode == PUSH_TO_TALK)
		{
		  BroadcastCarWaiting(0);				// turn off all headsets
		  for (i = 0; i < MAX_Allowed_Users; i++)
		  {
			// if any headset is on from the previous mode, now it is off
			if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
			{
			  (base_station).MicIsOn[i] = FALSE;
			}
		  }
		}
		else if (((base_station).NewSystemMode == HANDS_FREE) || ((base_station).NewSystemMode == AUTO_HANDS_FREE))
		{
		  for (i = 0; i < MAX_Allowed_Users; i++)
		  {
			// if any headset is on from the previous mode, turn the menu board mic back on
			if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
			{
			  AFESetGainInboundVolumeFP(NORMAL_INBOUND);
			  RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
			  if ((base_station).P33UsedForGreetMux)
				GREET_IN_PP_OFF;					// enable BC5 audio path only (no GREET) is enabled to DECT MICP/N
			  MENU_SPKR_AMP_ON;						// enables BC5 audio path in to DECT MICP/N
			  if ((base_station).GrillSpeakerNeedsToBeRestored)
			  {
				// restore GRILL volume
				(base_station).GrillSpeakerNeedsToBeRestored = FALSE;
				while ((base_station).GrillSpeakerVolume < (base_station).GrillSpeakerPreviousVolume)
				{
				  // increment MAX5407 (tap 31 "up" towards tap 0 direction) to decrease attenuation (increase volume)
				  UPDOWN_GRILL_UP;					// set up for increment mode
				  usec_pause(1);
				  VOL_CS_HI;						// lock in increment mode
				  UPDOWN_GRILL_LO;
				  UPDOWN_GRILL_HI;
				  usec_pause(1);
				  UPDOWN_GRILL_LO;
				  VOL_CS_LO;						// freeze tap
				  (base_station).GrillSpeakerVolume++;
				}
			  }
			  if (((base_station).GrillSpeakerVolume > 0) || ((base_station).DualBase == DUAL_BASE_MASTER))
				GRILL_SPEAKER_ON;
			  (base_station).GrillShouldBeOn = TRUE;
			  if ((base_station).DualBase == DUAL_BASE_MASTER)
				AFEDisableMicSpkrPath();			// re-connect p_dynmixer6 -> gain_spkr_fp
			  // TODO: CRP - convert usec_pause to use timer
			  usec_pause(65535);
			  usec_pause(65535);
			  AFEEnablePostMicPath();				// enable DECT MIC input
			  i = MAX_Allowed_Users;
			}
		  }
		}
		BroadcastSystemModeState(-1);
		(base_station).NewSystemMode = 0;
		general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
	  }
	  else
	  {
		// a new system mode was selected, but it is the same as the current system mode
		(base_station).NewSystemMode = 0;
	  }
      break;
  }
}

// general timer used for locking and refreshing display
static void displaytasktimer(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
#ifndef FOR_TEST_BASE_ONLY
      OSStartTimer(DISPLAYTASKTIMER, 30000);				// start 5 minute timer
#endif
      break;
    case TIMEOUT:
      (base_station).DisplayIsLocked = 1;					// refresh the DECT lock flag
      CopyToUartTxBuffer((UByte *)"set e0 1\r", 9);			// refresh the display lock flag
      CopyToUartTxBuffer((UByte *)"bv 200\r", 7);			// refresh the default beep loudness
      CopyToUartTxBuffer((UByte *)"bb 10\r", 6);			// refresh the default beep length

      if (((base_station).DualBase == DUAL_BASE_SLAVE) && ((base_station).DisplayScreen == REGISTRATION))
      {
  		if ((base_station).RegistrationButtonPressed)
  		{
  		  (base_station).RegistrationButtonPressed = FALSE;
  		  (base_station).RegistrationAllowed = FALSE;
  		}
		CopyToUartTxBuffer((UByte *)"m delayed_switch_button_pressed\r", 32);	// virtual button press to switch back to MASTER
      }

	  OSStartTimer(DISPLAYTASKTIMER, 30000);				// re-start 5 minute timer in case Display doesn't receive "m main" command ...
	  CopyToUartTxBuffer((UByte *)"m main\r", 7);			// this will cause the 5 minute timer in ServiceDisplay() to be started again
      break;
  }
}

// timer for checking vehicle detect and external relay
static void vehicledetecttasktimer(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      OSStartTimer(VEHICLEDETECTTASKTIMER, 500); 			// 500 x 10ms = 5s before for checking vehicle detector
      break;
    case TIMEOUT:
	  check_VD_pins();
	  if ((base_station).GreeterActive)
		  check_external_relay_pin();
	  if ((base_station).DualBase == DUAL_BASE_SLAVE)
		check_shutdown_grill_pin();
	  OSStartTimer(VEHICLEDETECTTASKTIMER, 20); 			// 20 x 10ms = 200ms for checking vehicle detector
      break;
  }
}

// timer task used for spacing simultaneous headset deletions
static void ppdeletetasktimer(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      break;
    case TIMEOUT:
      RegistrationScreen(0x1E);
      break;
  }
}

// timer task used for spacing simultaneous listen only assignments
static void listenonlytasktimer(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      break;
    case TIMEOUT:
      // check P3[4] when dual base for UART control of display
      if ((base_station).DualBase == DUAL_BASE_MASTER)
      {
    	if (P34_STATUS == Px_4_DATA)
    	{
    	  // P34_STATUS has gone HI so stop polling
    	  SWITCH_DISPLAY_TO_MASTER;									// switch UART control back to MASTER
    	}
    	else
    	{
    	  // otherwise keep polling P34_STATUS
    	  OSStartTimer(LISTENONLYTASKTIMER, 50); 					// 50 x 10ms = 500ms pause before checking P0[2]
    	}
      }
      else if ((base_station).DualBase == DUAL_BASE_SLAVE)
      {
    	// bring SLAVE STATUS back LO
    	SET_P34_INACTIVE;
      }
      // if not dual base, process normal LISTEN-ONLY command
      else
      {
    	RegistrationScreen(0x1F);
      }
      break;
  }
}

void initializeWentworth_fpTask(void)
{
	// IMPORTANT!!!!  WENTWORTHTASK ID # must match UART strings in "WTMacros_for_display.txt"
	// currently WENTWORTHTASK ID == 0x12
	WENTWORTHTASK = OSRegisterTask(wentworth_fptask, "wentworth_fptask", REALFPTASK);
	WENTWORTHTASKTIMER = OSRegisterTimer(WENTWORTHTASK);
    char * ptr;
	ptr = StringPrint(StatusString, "");
	ptr = StringPrint(ptr, "*** TaskID = 0x");
	ptr = StrPrintHexByte(ptr, WENTWORTHTASK);
	ptr = StringPrint(ptr, " *** ");
	PrintStatus(0, StatusString);
}

void initializeWatchdogTaskTimer(void)
{
  WATCHDOGTASK = OSRegisterTask(watchdogtasktimer, "watchdogtasktimer", REALFPTASK);
  WATCHDOGTASKTIMER = OSRegisterTimer(WATCHDOGTASK);
}

void initializeGeneralFPTaskTimer(void)
{
  GENERALFPTASK = OSRegisterTask(generalfptasktimer, "generalfptasktimer", REALFPTASK);
  GENERALFPTASKTIMER = OSRegisterTimer(GENERALFPTASK);
}

void initializeGeneralBC5TaskTimer(void)
{
  GENERALBC5TASK = OSRegisterTask(generalbc5tasktimer, "generalbc5tasktimer", REALFPTASK);
  GENERALBC5TASKTIMER = OSRegisterTimer(GENERALBC5TASK);
}

void initializeClockTimerTask(void)
{
  CLOCKTASK = OSRegisterTask(clocktasktimer, "clocktasktimer", REALFPTASK);
  CLOCKTASKTIMER = OSRegisterTimer(CLOCKTASK);
}

void initializeSystemModeTimerTask(void)
{
  SYSTEMMODETASK = OSRegisterTask(systemmodetasktimer, "systemmodetasktimer", REALFPTASK);
  SYSTEMMODETASKTIMER = OSRegisterTimer(SYSTEMMODETASK);
}

void initializeDisplayTimerTask(void)
{
  DISPLAYTASK = OSRegisterTask(displaytasktimer, "displaytasktimer", REALFPTASK);
  DISPLAYTASKTIMER = OSRegisterTimer(DISPLAYTASK);
}

void initializeVehicleDetectTimerTask(void)
{
  VEHICLEDETECTTASK = OSRegisterTask(vehicledetecttasktimer, "vehicledetecttasktimer", REALFPTASK);
  VEHICLEDETECTTASKTIMER = OSRegisterTimer(VEHICLEDETECTTASK);
}

void initializePPDeleteTimerTask(void)
{
  PPDELETETASK = OSRegisterTask(ppdeletetasktimer, "ppdeletetasktimer", REALFPTASK);
  PPDELETETASKTIMER = OSRegisterTimer(PPDELETETASK);
}

void initializeListenOnlyTimerTask(void)
{
  LISTENONLYTASK = OSRegisterTask(listenonlytasktimer, "listenonlytasktimer", REALFPTASK);
  LISTENONLYTASKTIMER = OSRegisterTimer(LISTENONLYTASK);
}

static void ConfigUART()
{
	P0_MODE_REG |= P0_0_MODE;					// P0[0] is alternate function: UART UTX
	P0_DIR_REG |= Px_0_DIR;						// P0[0] is output, no resistors

	P0_MODE_REG |= P0_1_MODE;					// P0[1] is alternate function: UART URX
	P0_DIR_REG &= ~Px_1_DIR;					// P0[1] is input, no resistors

	PAD_CTRL_REG |= P001_OD;					// P0[0] is OD output; P0[1] is normal input with pull-up disabled
}

static void ConfigOptionPins()
{
	// if possible, switch P3[3] to output for Greet in PP option
	if ((P3_DATA_REG & Px_3_DATA) == Px_3_DATA)
	{
		PrintStatus(0, "*** P3[3] input is HIGH, Greet in headset option IS available; switching P3[3] to output driven HIGH.");
		P3_DIR_REG |= Px_3_DIR;					// switch P3[3] to output, no pull resistors
		GREET_IN_PP_OFF;						// enable BC5 audio path only (no GREET) in to DECT MICP/N
		(base_station).P33UsedForGreetMux = TRUE;
	}
	else
		PrintStatus(0, "*** P3[3] input is LOW, Greet in headset option NOT available");
}

static void ConfigBC5Pins(void)
{
	// DECT P1[0] -> BC5 PIO2			O-LO  ???
	// DECT P1[3] -> BC5_RESETN			O-HI  ???
	// DECT P1[5] -> BC5 PIO6			O-HI  (LO = profile 0; HI = profile 1)
	// DECT P3[0] -> BC5 PIO5			O-HI  ???
	// DECT P3[1] -> DUAL_TBD			O-LO  ???
	// DECT P3[5] -> BC5 PIO1			O-LO  ???

	// set P1[5,3,0] to be driven by P1_OUT_DATA_REG[5,3,0]
	P1_MODE_REG &= ~(P1_5_MODE | P1_3_MODE | P1_0_MODE);

	// set P3[5,1,0] to be driven by P3_OUT_DATA_REG[5,1,0]
	P3_MODE_REG &= ~(P3_5_MODE | P3_1_MODE | P3_0_MODE);

	// set P1[5,3,0] as outputs
	P1_DIR_REG &= ~(Px_5_DIR | Px_3_DIR | Px_0_DIR);
	P1_DIR_REG |= (Px_5_DIR | Px_3_DIR | Px_0_DIR);

	// set P3[5,1,0] as outputs
	P3_DIR_REG &= ~(Px_5_DIR | Px_1_DIR | Px_0_DIR);
	P3_DIR_REG |= (Px_5_DIR | Px_1_DIR | Px_0_DIR);

	// set P1[3] to be driven LO
	P1_RESET_DATA_REG = Px_3_RESET;				// drive BC5 RESETN low
    PrintStatus(0, "*** BC5 RESETN is LO ");

	// set P1[5] to be driven HI
	P1_SET_DATA_REG = Px_5_SET;					// drive BC5 PIO6 high for Alango profile 1

	// set P3[5,1] and P1[0] as driven LO
	P3_RESET_DATA_REG = Px_5_RESET;				// drive BC5 PIO1 low
	P3_RESET_DATA_REG = Px_1_RESET;				// drive DUAL_TBD low
	P1_RESET_DATA_REG = Px_0_RESET;				// drive BC5 PIO2 low

	// P3[0] to be driven HI
	P3_SET_DATA_REG = Px_0_SET;					// drive BC5 PIO5 high
}

static void ConfigureRemainingPorts()
{
	//	P0[4]	Output-LO-OD-BP			VOL_CS (menu and grill speaker volume control, normally low)
	//	P0[5]	Output-LO-OD-BP			CB (call button signal to external timer)
	//	P0[6]	Output-LO-OD-BP			UPDOWN_GRILL (volume control for grill speaker, normally low)
	//	P0[7]	Output-HI-OD-BP			GREET_N
	//	P1[1]	Input-PU				MENU_VEHICLE_3 (3V signal from loop detector)
	//	P1[2]	Input-PU				EXTERNAL_ALARM_INPUT (signal(s) from external alarm relays)
	//	P2[0]	Output-LO-OD-BP			SHUTDOWN_AMP_GRILL_N (grill speaker amp shutdown)
	//	P2[0]	Input					SHUTDOWN_AMP_GRILL_N (grill speaker amp shutdown sense from MASTER in dual base configuration)
	//	P2[1]	Output-LO-OD-BP			TBD (used as clock for external watchdog timer as well as for WT greet board)
	//	P2[6]	Output-LO-BP			SET_RTC (used to control RTC/PCM pass through mux)
	//	P2[7]	Output-LO-OD-BP			GREET_ENABLE_DATA (used as output to WT greet board)
	//	P3[4]	Input-PD		 		MASTER read STATUS (read signal from slave for dual base configuration)
	//	P3[4]	Output-LO-OD-BP			SLAVE send STATUS (driven signal from slave for dual base configuration)
	//	P3[6]	Input-PU				TIMER_ALERT (input from timer)
	//	P3[7]	Output-HI				UART_CONTROL (output signal to control DISPLAY input: MASTER_CONNECTED=HI, SLAVE_CONNECTED=LO)
	//	LED1	Output-LO				SHUTDOWN_AMP_MENU_N (MENU speaker amp shutdown)

	// set P0[7:4] to be driven by P0_OUT_DATA_REG[7:4]
	P0_MODE_REG &= ~(P0_4_MODE | P0_5_MODE | P0_6_MODE | P0_7_MODE);

	// set P1[2:1] to be driven by P1_OUT_DATA_REG[2:1]
	P1_MODE_REG &= ~(P1_2_MODE | P1_1_MODE);

	// set P2[7,6,1,0] to be driven by P2_OUT_DATA_REG[7,6,1,0]
	P2_MODE_REG &= ~(P2_7_MODE | P2_6_MODE | P2_1_MODE | P2_0_MODE);

	// set P3[7:6,4] to be driven by P3_OUT_DATA_REG[7:6,4]
	P3_MODE_REG &= ~(P3_4_MODE | P3_6_MODE | P3_7_MODE);

	// set P0[7:4] as outputs
	P0_DIR_REG &= ~(Px_4_DIR | Px_5_DIR | Px_6_DIR | Px_7_DIR);
	P0_DIR_REG |= (Px_4_DIR | Px_5_DIR | Px_6_DIR | Px_7_DIR);

	// set P1[2:1] as inputs with pull-up resistors
	P1_DIR_REG &= ~(Px_1_DIR | Px_2_DIR);
	P1_DIR_REG |= (0x0014);

	// set P2[7,6,1,0] as outputs
	P2_DIR_REG |= (Px_0_DIR | Px_1_DIR | Px_6_DIR | Px_7_DIR);

	// set P3[6] as input with pull-up resistor
	// set P3[4] as input with pull-down resistor
	P3_DIR_REG &= ~(Px_4_DIR | Px_6_DIR);
	P3_DIR_REG |= (0x1200);

	// set P3[7] as output driven HI
	P3_DIR_REG |= (Px_7_DIR);
	SWITCH_DISPLAY_TO_MASTER;

	// set P0[7:4] and P2[1:0] to be open-drain
	PAD_CTRL_REG &= ~(P04567_OD | P21_OD | P20_OD);
	PAD_CTRL_REG |= (P04567_OD | P21_OD | P20_OD);

	// set P2[0] to be driven LO
	GRILL_SPEAKER_OFF;							// drive SHUTDOWN_AMP_GRILL_N low

	// set P2[1] to be driven HI
	P2_SET_DATA_REG = Px_1_SET;					// drive TBD high

	// set P2[6] to be driven LO
	BASE_PCM_ON;								// drive SET_RTC low to configure mux for PCM pass though

	// set P2[7] to be driven LO and open-drain
	P2_RESET_DATA_REG = Px_7_RESET;				// drive GREET_ENABLE_DATA low
	PAD_CTRL_REG |= P27_OD;

	// set LED1 to be driven 1x VBAT
	CP_CTRL_REG |= CP_FORCE_MODE;

	// set LED1 to be driven by CP_CTRL_REG[CP_LEVEL1]
	CP_CTRL_REG &= ~(CP_PWM1);

	// set LED1 to be driven 4.0V
	CP_CTRL_REG &= ~(CP_LEVEL1 | CP_EN);		// clear CP_LEVEL1 and CP_EN first
	CP_CTRL_REG |= (0x0009);					// drive SHUTDOWN_AMP_MENU_N high; HI to enable, LO to disable

	// set P0[6:4] to be driven LO and P0[7] to be driven HI
	VOL_CS_LO;									// drive VOL_CS low
	SET_CB_LO;									// drive CB low
	UPDOWN_GRILL_LO;							// drive UPDOWN_GRILL low
	GREET_N_HI;									// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
	PrintStatus(0, "*** init: CB is LO, GREET_N is HI *** ");

	// NOTE: after a watchdog reboot, MAX5407 will NOT be at tap 31, so let's make sure it is first ...
	// increment MAX5407 (tap ? "down" towards tap 31 direction) to increase attenuation (decrease volume)
	UPDOWN_GRILL_DOWN;							// set up for decrement mode
	usec_pause(1);
	VOL_CS_HI;									// lock in decrement mode
	int i;
	for (i = 31; i > 0; i--)
	{
		UPDOWN_GRILL_LO;
		UPDOWN_GRILL_HI;
		usec_pause(1);
		UPDOWN_GRILL_LO;
	}
	VOL_CS_LO;									// freeze tap

	// now set MAX5407 to tap 14 (it's now at tap 31, so move 16 taps "up" from tap 31 to tap 15)
	// increment MAX5407 (tap 31 "up" towards tap 0 direction) to decrease attenuation (increase volume)
	UPDOWN_GRILL_UP;							// set up for increment mode
	usec_pause(1);
	VOL_CS_HI;									// lock in increment mode
	for (i = 16; i > 0; i--)
	{
		UPDOWN_GRILL_LO;
		UPDOWN_GRILL_HI;
		usec_pause(1);
		UPDOWN_GRILL_LO;
	}
	VOL_CS_LO;									// freeze tap
	(base_station).GrillSpeakerVolume = 0;		// set as 0 volume baseline; volume 0 = tap 15, volume 15 = tap 0
}

static void StartPCM()
{
	// P3[7] (SLAVE) is HIGH indicating this is 1st base station board
	// so start PCM bus as slave for board to board communication
	PrintStatus(0, "*** Starting PCM as SLAVE for FP #1 - FIRST Base");

	P2_DIR_REG &= ~Px_5_DIR;					// enable PCM_FSC as an input w/no pull resistor
	P2_DIR_REG |=  Px_4_DIR;					// enable PCM_DO as an output
	P2_DIR_REG &= ~Px_3_DIR;					// enable PCM_DI as an input w/no pull resistor
	P2_DIR_REG &= ~Px_2_DIR;					// enable PCM_CLK as an input w/no pull resistor

	CLK_CODEC_REG = 0x0000;						// disable all clocks

	P2_MODE_REG &= ~(P2_5_MODE | P2_4_MODE | P2_3_MODE | P2_2_MODE);	// clear all the bits in question first
	P2_MODE_REG |= (P2_5_MODE & 0x0400);		// enable PCM_FSC
	P2_MODE_REG |= (P2_4_MODE & 0x0100);		// enable PCM_DO
	P2_MODE_REG |= (P2_3_MODE & 0x0040);		// enable PCM_DI
	P2_MODE_REG |= (P2_2_MODE & 0x0010);		// enable PCM_CLK

	DSP_MAIN_SYNC1_REG = 0;						// clear the entire register: everything at 8kHz

	DSP_PCM_CTRL_REG &= ~PCM_FSC0LEN;			// clear PCM_FSC0LEN bits first (PCM_FSC0LEN is 1-bit)
	DSP_PCM_CTRL_REG |= PCM_EN;					// ensure that PCM bus is enabled (MASTER vs SLAVE is set in gen2dsp_init()
}

static void ConfigureBaseStationVariables()
{
	int i, ii;

	(base_station).PowerOnStatus = 0;
	(base_station).DualLane = FALSE;
	(base_station).BaseRTC = FALSE;
	(base_station).GreetRTC = FALSE;
	(base_station).UpdateFromRTC = FALSE;
	for (i = 0; i < 5; i++)
		(base_station).FP_ARI[i] = 0xFF;
	for (i = 0; i < 10; i++)
		(base_station).SerialNumber[i] = (unsigned char)(i + 48);
	(base_station).SerialNumber[10] = '\0';
	(base_station).DisplayTime.timeHourMSB = 1;						// hour (10's)
	(base_station).DisplayTime.timeHourLSB = 2;						// hour (1's)
	(base_station).DisplayTime.timeMinMSB = 3;						// minute (10's)
	(base_station).DisplayTime.timeMinLSB = 4;						// minute (1's)
	(base_station).CurrentDay = 0;									// base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
	(base_station).NightVolumeTimeStart.timeHourMSB = 0;			// hour (10's)
	(base_station).NightVolumeTimeStart.timeHourLSB = 0;			// hour (1's)
	(base_station).NightVolumeTimeStart.timeMinMSB = 0;				// minute (10's)
	(base_station).NightVolumeTimeStart.timeMinLSB = 0;				// minute (1's)
	(base_station).NightVolumeTimeEnd.timeHourMSB = 0;				// hour (10's)
	(base_station).NightVolumeTimeEnd.timeHourLSB = 0;				// hour (1's)
	(base_station).NightVolumeTimeEnd.timeMinMSB = 0;				// minute (10's)
	(base_station).NightVolumeTimeEnd.timeMinLSB = 0;				// minute (1's)
	(base_station).DayTime = TRUE;
	(base_station).NighTimeInEffect = FALSE;
	(base_station).FillingRegistrationDisplay = FALSE;
	(base_station).HeadsetCounter = MAX_Allowed_Users;
	(base_station).DeletionCounter = MAX_Allowed_Users;
	(base_station).ListenOnlyCounter = MAX_Allowed_Users;
	for (i = 0; i < MAX_Allowed_Users; i++)
	{
		(base_station).HeadsetIsOn[i] = FALSE;
		(base_station).HeadsetButtonIsPressed[i] = FALSE;
		(base_station).MicIsOn[i] = FALSE;
		(base_station).ListenOnly[i] = 0xFF;
	}
	for (i = 0; i < 6; i++)
		(base_station).PageMode[i] = FALSE;
	(base_station).CarIsWaiting = FALSE;
	(base_station).VehicleDetectIsActive = FALSE;
	(base_station).GrillShouldBeOn = FALSE;

	(base_station).DisplayCommand = 0;
	(base_station).DisplayCommandLength = 0;
	for (i = 0; i < 10; i++)
		(base_station).DisplayCommandData[i] = 0;
	(base_station).DisplayScreen = NONE;
	(base_station).DestAfterPin = MAIN;
	(base_station).DisplayValueChanged = FALSE;
	(base_station).PinDigitIndex = 0;
	for (i = 0; i < 4; i++)
	{
		(base_station).TempPin[i] = 0;
		(base_station).TempPin2[i] = 0;
		(base_station).DisplayUserPin[i] = 0;
	}
	(base_station).DisplayMasterPin[0] = 2;
	(base_station).DisplayMasterPin[1] = 5;
	(base_station).DisplayMasterPin[2] = 8;
	(base_station).DisplayMasterPin[3] = 0;
	(base_station).DisplayIsLocked = 0;
	(base_station).InboundVol = 3;									// 0-9 (dB is 2x: 0dB-18dB)
	(base_station).CurrentInboundVolumeMixerAtten = MIXER_ATTEN;
	(base_station).GrillSpeakerVolume = 0;
	(base_station).GrillSpeakerNeedsToBeRestored = FALSE;
	(base_station).GrillSpeakerPreviousVolume = 0;
	(base_station).PostSpeakerVolumeDay = 6;						// initial value
	(base_station).PostSpeakerVolumeNight = 6;						// initial value
	(base_station).CurrentOutboundVolume = 6;						// initial value
	(base_station).SystemMode = HANDS_FREE;
	(base_station).NewSystemMode = 0;
	(base_station).RegistrationAllowed = FALSE;
	(base_station).RegistrationButtonPressed = FALSE;
	(base_station).OrderTakerID = 0xFF;
	for (i = 0; i < 4; i++)
		(base_station).GrtrMsgrAuthCode[i] = 0xFF;
	(base_station).GreeterInstalled = FALSE;
	(base_station).GreeterActive = FALSE;
	(base_station).ActiveGreetNumber = 0;
	(base_station).ActiveMessages = 0;
	(base_station).FillingMsgDisplay = FALSE;
	(base_station).GreetClockRunning = FALSE;
	(base_station).AlertWaiting = FALSE;
	(base_station).AlertPlayed = FALSE;
	(base_station).BC5Bypassed = FALSE;
	(base_station).P33UsedForGreetMux = FALSE;
	(base_station).PPCalibration = FALSE;
	(base_station).CalibratingPPMic = FALSE;
	(base_station).CalibratingPPRcv = FALSE;
	(base_station).MsgCounter = NUM_OF_MESSAGES;
	(base_station).MsgBeingEdited = 0;
	(base_station).MsgDayBeingEdited = MONDAY;
	(base_station).MessageIsPlaying = 0;
	(base_station).MessageIsRecording = 0;
	for (i = 0; i < NUM_OF_MESSAGES; i++)
	{
		if (i < NUM_OF_GREETS)
			(base_station).Message[i].MessageEnableName = 0x00 + i;
		else if (i < (NUM_OF_MESSAGES - 1))
			(base_station).Message[i].MessageEnableName = 0x00 + (i - NUM_OF_GREETS);
		else
			(base_station).Message[i].MessageEnableName = 0x0F;
		if (i < NUM_OF_GREETS)
		{
			for (ii = 0; ii < 4; ii++)
			{
				(base_station).Message[i].StartTime[ii] = (i * 14);   	// 0, 14, 28, 42, 56, 70, 84
				(base_station).Message[i].StopTime[ii] = (i * 14) + 10;
			}
		}
		else
		{
			for (ii = 0; ii < 4; ii++)
			{
				switch(i)
				{
					case NUM_OF_GREETS +  0:	(base_station).Message[i].StartTime[ii] =  4;		break;		// 01:00
					case NUM_OF_GREETS +  1:	(base_station).Message[i].StartTime[ii] = 16;		break;		// 04:00
					case NUM_OF_GREETS +  2:	(base_station).Message[i].StartTime[ii] = 32;		break;		// 08:00
					case NUM_OF_GREETS +  3:	(base_station).Message[i].StartTime[ii] = 44;		break;		// 11:00
					case NUM_OF_GREETS +  4:	(base_station).Message[i].StartTime[ii] = 60;		break;		// 15:00
					case NUM_OF_GREETS +  5:	(base_station).Message[i].StartTime[ii] = 72;		break;		// 18:00
					case NUM_OF_GREETS +  6:	(base_station).Message[i].StartTime[ii] = 88;		break;		// 22:00
					case NUM_OF_GREETS +  7:	(base_station).Message[i].StartTime[ii] =  4;		break;		// 01:00
					case NUM_OF_GREETS +  8:	(base_station).Message[i].StartTime[ii] = 16;		break;		// 04:00
					case NUM_OF_GREETS +  9:	(base_station).Message[i].StartTime[ii] = 32;		break;		// 08:00
					case NUM_OF_GREETS + 10:	(base_station).Message[i].StartTime[ii] = 44;		break;		// 11:00
					case NUM_OF_GREETS + 11:	(base_station).Message[i].StartTime[ii] = 60;		break;		// 15:00
					case NUM_OF_GREETS + 12:	(base_station).Message[i].StartTime[ii] = 72;		break;		// 18:00
					case NUM_OF_GREETS + 13:	(base_station).Message[i].StartTime[ii] = 88;		break;		// 22:00
				}
				(base_station).Message[i].StopTime[ii] = 0; 			// always 0
			}
		}
		(base_station).Message[i].StartIsPressed = FALSE;
		(base_station).Message[i].StopIsPressed = FALSE;
		(base_station).Message[i].OnOffIsPressed = FALSE;
	}
	(base_station).PowerOnCount = 1;
	(base_station).AlangoProfile1 = FALSE;
	(base_station).PlayGreetInPP = FALSE;
	(base_station).DualBase = 0;										// 0: single base, 1: dual base - master, 2: dual base - slave
}

void InitWentworth_fp(void)
{
//	p_base_station = (wt_base_station *) mem_malloc(sizeof(wt_base_station), 0x59);
//	if (p_base_station == 0)
//		PrintStatus(0, "*** ERROR: InitWentworth_fp() out of memory *** ");
//	else
//		PrintStatus(0, "*** InitWentworth_fp() mem_malloc() success *** ");

	ConfigureBaseStationVariables();				// set up all the initial states and display info

	ConfigOptionPins();								// setup P3[3] to support GREET in headset option

	ConfigureRemainingPorts();						// set up all ports per DECT_pin_configs_revx.xls file

	RunGreetClock(MESSAGE_INIT, 1);					// set up WT greet board

	ConfigBC5Pins();								// setup BC5 PIO and RESETN pins

	ConfigUART();									// setup P0[0]/P0[1] as UART UTX / URX

	StartPCM();										// set up and start PCM bus

	initializeGeneralFPTaskTimer();					// generic timer task

	initializeGeneralBC5TaskTimer();				// generic BC5 timer task

	initializeWentworth_fpTask();					// main task for FP

	initializeWatchdogTaskTimer();					// timer task used for toggling P2[1] for external watchdog timer

	initializeClockTimerTask();						// timer task used for clock tick

	initializeSystemModeTimerTask();				// timer task used for changing System Mode

	initializeDisplayTimerTask();					// timer task used for resetting and locking display

	initializeVehicleDetectTimerTask();				// timer task used for checking vehicle detect

	initializePPDeleteTimerTask();					// timer task used for spacing simultaneous headset deletions

	initializeListenOnlyTimerTask();				// timer task used for spacing simultaneous listen only assignments
}
