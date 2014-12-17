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
 * $History:: display_control_fp.c											  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */
#include "../../../../../../include/os/include/os_timer.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/common/common_general_functions.h"

#include "../dsp/gdsp_local_defines.h"
#include "afe.h"
#include "wentworth_fp.h"
#include "fppp_common.h"
#include "access_bus.h"

extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void CopyByteToUartTxBuffer(UByte buffer);
extern void BroadcastSystemModeState(PPIDType user);
extern void BroadcastCalOffset(PPIDType user, unsigned char direction);
extern UByte fp_subscription_removeSubscription(PPIDType user);
extern void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length);
extern void CheckNightVolumeTime(void);
extern void RunGreetClock(UByte greet_cmd, UByte greet_selection);
extern UByte fp_subscription_getNumberOfSubscriptions();
extern void SendPCMCommand(WORD cmd);

extern UByte GENERALFPTASKTIMER;
extern UByte GENERALBC5TASKTIMER;
extern UByte SYSTEMMODETASKTIMER;
extern UByte DISPLAYTASKTIMER;
extern UByte PPDELETETASKTIMER;
extern UByte LISTENONLYTASKTIMER;
extern UByte VEHICLEDETECTTASKTIMER;
extern UByte CLOCKTASKTIMER;
extern UByte WATCHDOGTASKTIMER;

static void usec_pause(DWORD x)						// -2,147,483,648 to 2,147,483,647
{
    volatile DWORD i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

void WTInfoScreen()
{
	int i = 0;

	if ((base_station).DualBase)
		CopyToUartTxBuffer((UByte *)"m show_wentworth:dual ", 22);
	else
		CopyToUartTxBuffer((UByte *)"m show_wentworth:single ", 24);

	SendAsciiValue(FW_REV_MAJOR);
	CopyByteToUartTxBuffer(' ');
	SendAsciiValue(FW_REV_MINOR);
	CopyByteToUartTxBuffer(' ');
	for (i = 0; i < 10; i++)
	{
		switch ((base_station).SerialNumber[i])
		{
			case '0':		CopyByteToUartTxBuffer('0');	break;
			case '1':		CopyByteToUartTxBuffer('1');	break;
			case '2':		CopyByteToUartTxBuffer('2');	break;
			case '3':		CopyByteToUartTxBuffer('3');	break;
			case '4':		CopyByteToUartTxBuffer('4');	break;
			case '5':		CopyByteToUartTxBuffer('5');	break;
			case '6':		CopyByteToUartTxBuffer('6');	break;
			case '7':		CopyByteToUartTxBuffer('7');	break;
			case '8':		CopyByteToUartTxBuffer('8');	break;
			case '9':		CopyByteToUartTxBuffer('9');	break;
		}
	}

	if ((base_station).DualBase)
	{
		CopyByteToUartTxBuffer(' ');
		for (i = 0; i < 10; i++)
		{
			switch ((base_station).SerialNumber2[i])
			{
				case '0':		CopyByteToUartTxBuffer('0');	break;
				case '1':		CopyByteToUartTxBuffer('1');	break;
				case '2':		CopyByteToUartTxBuffer('2');	break;
				case '3':		CopyByteToUartTxBuffer('3');	break;
				case '4':		CopyByteToUartTxBuffer('4');	break;
				case '5':		CopyByteToUartTxBuffer('5');	break;
				case '6':		CopyByteToUartTxBuffer('6');	break;
				case '7':		CopyByteToUartTxBuffer('7');	break;
				case '8':		CopyByteToUartTxBuffer('8');	break;
				case '9':		CopyByteToUartTxBuffer('9');	break;
			}
		}
	}
	CopyByteToUartTxBuffer('\r');

	if ((base_station).DualBase && (base_station).IsUS)
	{
		CopyToUartTxBuffer((UByte *)"t \"       SpeedThru EXP (US)\" 13 125 T\r", 39);
	}
	else if ((base_station).DualBase)
	{
		CopyToUartTxBuffer((UByte *)"t \"       SpeedThru EXP (EU)\" 13 125 T\r", 39);
	}
	else if ((base_station).IsUS)
	{
		CopyToUartTxBuffer((UByte *)"t \"         SpeedThru (US)\" 13 125 T\r", 37);
	}
	else
	{
		CopyToUartTxBuffer((UByte *)"t \"         SpeedThru (EU)\" 13 125 T\r", 37);
	}

//	general_startTimer(-1, WT_HEAP_CHECK, NULL, 0, 200);
}

void WTInfoDebugScreen()
{
	if ((base_station).DualBase)
	{
		CopyToUartTxBuffer((UByte *)"m show_wentworth_debug:dual ", 28);
		SendAsciiValue((base_station).PowerOnCount);
		CopyByteToUartTxBuffer(' ');
		SendAsciiValue((base_station).PowerOnCountB);
		CopyByteToUartTxBuffer('\r');
	}
	else
	{
		CopyToUartTxBuffer((UByte *)"m show_wentworth_debug:single ", 30);
		SendAsciiValue((base_station).PowerOnCount);
		CopyByteToUartTxBuffer('\r');
	}

	CopyToUartTxBuffer((UByte *)"s 0 10\r", 7);			// black on light gray if required

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for toggling Alango mode (Profile 0 = MA-11, Profile 1 = MA-10)
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	if ((base_station).AlangoProfile1)
		CopyToUartTxBuffer((UByte *)"bdc 4 5 5 20 \"MA10\" \"MA11\" 26 28\r", 33);
	else
		CopyToUartTxBuffer((UByte *)"bdc 4 5 5 21 \"MA10\" \"MA11\" 26 28\r", 33);
	CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	CopyToUartTxBuffer((UByte *)"t \"Post MIC\" 60 18 T\r", 21);
	CopyToUartTxBuffer((UByte *)"t \"being used\" 60 38 T\r", 23);
	CopyToUartTxBuffer((UByte *)"xa	4 p request_base_command 0\r", 30);
	CopyToUartTxBuffer((UByte *)"xa	4 r request_base_command 1\r", 30);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for toggling BC5 demo mode
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	if ((base_station).BC5Bypassed)
		CopyToUartTxBuffer((UByte *)"bdc 5 5 55 21 \"ON\" \"OFF\" 26 28\r", 31);
	else
		CopyToUartTxBuffer((UByte *)"bdc 5 5 55 20 \"ON\" \"OFF\" 26 28\r", 31);
	CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	CopyToUartTxBuffer((UByte *)"t \"HSet noise\" 60 68 T\r", 23);
	CopyToUartTxBuffer((UByte *)"t \"canceling\" 60 88 T\r", 22);
	CopyToUartTxBuffer((UByte *)"xa	5 p request_base_command 2\r", 30);
	CopyToUartTxBuffer((UByte *)"xa	5 r request_base_command 3\r", 30);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for halting WatchDog
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	CopyToUartTxBuffer((UByte *)"bdc 8 160 224 20 \"STOP\\nWD\" \"STOPPED\" 43 49\r", 44);
	CopyToUartTxBuffer((UByte *)"xa	8 p request_base_command 7\r", 30);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for second greeter in dual base system
	if ((base_station).DualBase)
	{
		CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
		CopyToUartTxBuffer((UByte *)"bd 9 248 224 1 \"\" 0 0 97 98\r", 28);
		CopyToUartTxBuffer((UByte *)"xm	9 request_greet_authorization:x9\r", 36);
		CopyToUartTxBuffer((UByte *)"t \"Greet B\" 303 239 T\r", 22);
		CopyToUartTxBuffer((UByte *)"t \"Code\" 303 259 T\r", 19);
	}

	usec_pause(0xFFFF);									// to avoid over running the display input buffer
}

void VolumeAdjustScreen()
{
	UByte vol_item, requested_vol, current_vol;

	(base_station).DisplayValueChanged = TRUE;
	vol_item = (base_station).DisplayCommandData[0];		// which volume control: 0-detect, 1-inbound, 2-grill, 3-day, 4-night
	requested_vol = (base_station).DisplayCommandData[1];	// volume requested
	// INBOUND volume can be 0 to INBOUND_P1 or 0 to INBOUND_P0
	if (vol_item == 1)
	{
		if ((base_station).AlangoProfile1)
		{
			// INBOUND volume can be 0 to INBOUND_P1 (Alango profile1 setting)
			if (requested_vol > INBOUND_P1)
			{
				requested_vol = INBOUND_P1;
			}
		}
		else
		{
			// INBOUND volume can be 0 to INBOUND_P0 (Alango profile0 setting)
			if (requested_vol > INBOUND_P0)
			{
				requested_vol = INBOUND_P0;
			}
		}
	}
	// GRILL volume can be 0 to GRILL
	else if (vol_item == 2)
	{
		if (requested_vol > GRILL)
		{
			requested_vol = GRILL;
		}
	}
	// OUTBOUND volumes are 0 to OUTBOUND_P1 or OUTBOUND_P0
	else if ((vol_item == 3) || (vol_item == 4))
	{
		if ((base_station).AlangoProfile1)
		{
			// OUTBOUND volume can be 0 to OUTBOUND_P1 (Alango profile1 setting)
			if (requested_vol > OUTBOUND_P1)
			{
				requested_vol = OUTBOUND_P1;
			}
		}
		else
		{
			// OUTBOUND volume can be 0 to OUTBOUND_P0 (Alango profile0 setting)
			if (requested_vol > OUTBOUND_P0)
			{
				requested_vol = OUTBOUND_P0;
			}
		}
	}

	switch (vol_item)
	{
		case 0:		// detect tone volume - not implemented
			break;
		case 1:		// inbound volume
			AFESetGainPP2PPMixer(requested_vol);
			break;
		case 2:		// grill volume
			// adjust analog grill speaker circuit
			// using P0[4] VOL_CS
			// using P0[6] UPDOWN_GRILL
			current_vol = (base_station).GrillSpeakerVolume;
			while (requested_vol != current_vol)
			{
				if (requested_vol > current_vol)
				{
					// increment MAX5407 (tap 31 "up" towards tap 0 direction) to decrease attenuation (increase volume)
					UPDOWN_GRILL_UP;							// set up for increment mode
					usec_pause(1);
					VOL_CS_HI;									// lock in increment mode
					UPDOWN_GRILL_LO;
					UPDOWN_GRILL_HI;
					usec_pause(1);
					UPDOWN_GRILL_LO;
					VOL_CS_LO;									// freeze tap
					current_vol++;
				}
				else if (requested_vol < current_vol)
				{
					// decrement MAX5407 (tap 0 "down" towards tap 31 direction) to increase attenuation (decrease volume)
					UPDOWN_GRILL_DOWN;							// set up for decrement mode
					VOL_CS_HI;									// lock in decrement mode
					UPDOWN_GRILL_LO;
					UPDOWN_GRILL_HI;
					usec_pause(1);
					UPDOWN_GRILL_LO;
					VOL_CS_LO;									// freeze tap
					current_vol--;
				}
			}
			(base_station).GrillSpeakerVolume = requested_vol;
			if ((base_station).GrillSpeakerVolume)
				GRILL_SPEAKER_ON;
			else
				GRILL_SPEAKER_OFF;
			break;
		case 3:		// day volume
			current_vol = (base_station).PostSpeakerVolumeDay;
			if (requested_vol != current_vol)
			{
				if ((base_station).DayTime)
				{
					AFESetGainSpkrVolumeFP(requested_vol);
					(base_station).CurrentOutboundVolume = requested_vol;
				}
				(base_station).PostSpeakerVolumeDay = requested_vol;
			}
			break;
		case 4:		// night volume
			current_vol = (base_station).PostSpeakerVolumeNight;
			if (requested_vol != current_vol)
			{
				if (!(base_station).DayTime)
				{
					AFESetGainSpkrVolumeFP(requested_vol);
					(base_station).CurrentOutboundVolume = requested_vol;
				}
				(base_station).PostSpeakerVolumeNight = requested_vol;
			}
			break;
	}
	// update volume display
	if (!FIRST_BASE)
	{
		SendPCMCommand(VOLUME_SETTINGS_B_ind + (vol_item << 4) + requested_vol);
	}

	if ((base_station).DisplayScreen == VOLUME)
	{
		CopyToUartTxBuffer((UByte *)"m set_volume ", 13);
		SendAsciiValue(vol_item);
		CopyByteToUartTxBuffer(' ');
		SendAsciiValue(requested_vol);
		CopyByteToUartTxBuffer('\r');
	}
	else
		general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// request came from other base, write current values to EEPROM
}

extern void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN);

void RegistrationScreen(UByte cmd)
{
	int i, ii, count;
	IPEIType Ipei;
	char SN[17];
	UByte buffer[50];

	switch (cmd)
	{
		case 0x03:
			// fill buttons with registered headsets
			if ((!(base_station).DualBase && ((base_station).HeadsetCounter < MAX_Allowed_Users)) ||
				 ((base_station).DualBase && ((base_station).HeadsetCounter < MAX_Allowed_Users_Dual)))
			{
#ifdef FOR_TEST_BASE_ONLY
				// !! THIS IS ONLY FOR IN-HOUSE TEST RELEASE !!
				// use this code to activate calibration button on registration screen
				if ((base_station).HeadsetCounter == 0 && !(base_station).PPCalibration)
				{
					// add a bitmap and command for opening headset calibration screen
					CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
					CopyToUartTxBuffer((UByte *)"bdc 6 5 224 20 \"CAL\" \"CAL\" 26 28\r", 33);
					CopyToUartTxBuffer((UByte *)"xa	6 p request_base_command 4\r", 30);
					usec_pause(0xFFFF);									// to avoid over running the display input buffer
				}
#endif
				CopyToUartTxBuffer((UByte *)"s 0 2\r", 6);
				CopyToUartTxBuffer((UByte *)"f 18BC\r", 7);
				i = (base_station).HeadsetCounter++;
				if (QuickData[i].EmptyMarker == 0)
				{
					Ipei[0] = 0x01;					// hard coding 0x01 for 1st byte
					memcpy(&Ipei[1], QuickData[i].Upi, 4);
					ConvertIpeiToSN(i, SN, Ipei);
					if ((base_station).HeadsetIsOn[i])
						memcpy(&buffer[0], "m register_box:lbl_1_", 21);
					else
						memcpy(&buffer[0], "m register_box:lbl_0_", 21);
					count = 21;
					count += GetAsciiValue(&buffer[0], (i + 40), count);
					memcpy(&buffer[0] + count, " \"", 2);
					count += 2;
					if ((base_station).HeadsetIsOn[i])
					{
						memcpy(&buffer[0] + count, "on ", 3);
						count += 3;
					}
					else
					{
						memcpy(&buffer[0] + count, "off ", 4);
						count += 4;
					}
					memcpy(&buffer[0] + count, &SN[6], 10);
					count += 10;
					memcpy(&buffer[0] + count, "\"\r", 2);
					count += 2;
				}
				else
				{
					memcpy(&buffer[0], "m register_box:lbl_0_", 21);
					count = 21;
					count += GetAsciiValue(buffer, (i + 40), count);
					memcpy(&buffer[0] + count, " \"\"\r", 4);
					count += 4;
				}
				CopyToUartTxBuffer(&buffer[0], count);
				OSStartTimer(GENERALFPTASKTIMER, 5); 			// 5 x 10ms = 50ms pause before sending next button info
			}
			else if (FIRST_BASE && ((base_station).HeadsetCounter < MAX_Allowed_Users))
			{
				// work with 2nd base headsets on 1st base display
				CopyToUartTxBuffer((UByte *)"s 0 2\r", 6);
				CopyToUartTxBuffer((UByte *)"f 18BC\r", 7);
				i = (base_station).HeadsetCounter++;
				if ((base_station).QuickDataBoard2[i - MAX_Allowed_Users_Dual].EmptyMarker == 0)
				{
					Ipei[0] = 0x01;					// hard coding 0x01 for 1st byte
					memcpy(&Ipei[1], (base_station).QuickDataBoard2[i - MAX_Allowed_Users_Dual].Upi, 4);
					ConvertIpeiToSN(i, SN, Ipei);
					if ((base_station).HeadsetIsOn[i])
					{
						memcpy(&buffer[0], "m register_box:lbl_1_", 21);
						count = 21;
					}
					else
					{
						memcpy(&buffer[0], "m register_box:lbl_0_", 21);
						count = 21;
					}
					count += GetAsciiValue(&buffer[0], (i + 40), count);
					memcpy(&buffer[0] + count, " \"", 2);
					count += 2;
					if ((base_station).HeadsetIsOn[i])
					{
						memcpy(&buffer[0] + count, "on ", 3);
						count += 3;
					}
					else
					{
						memcpy(&buffer[0] + count, "off ", 4);
						count += 4;
					}
					memcpy(&buffer[0] + count, &SN[6], 10);
					count += 10;
					memcpy(&buffer[0] + count, "\"\r", 2);
					count += 2;
				}
				else
				{
					memcpy(&buffer[0], "m register_box:lbl_0_", 21);
					count = 21;
					count += GetAsciiValue(buffer, (i + 40), count);
					memcpy(&buffer[0] + count, " \"\"\r", 4);
					count += 4;
				}
				CopyToUartTxBuffer(&buffer[0], count);
				OSStartTimer(GENERALFPTASKTIMER, 5); 			// 5 x 10ms = 50ms pause before sending next button info
			}
			else
			{
				if ((base_station).PPCalibration)
				{
					// calibrating headsets, re-paint LISTEN-ONLY and DELETE buttons
					CopyToUartTxBuffer((UByte *)"f 13B\r", 6);												// switch to smaller font
					CopyToUartTxBuffer((UByte *)"r 0 0 480 50 1 00F\r", 19);								// draw a blue square to "erase" normal buttons
					CopyToUartTxBuffer((UByte *)"f 13B\r", 6);												// switch to smaller font
					CopyToUartTxBuffer((UByte *)"xd 15\r", 6);												// disable HELP button
					CopyToUartTxBuffer((UByte *)"xd 29\r", 6);												// disable LISTEN ONLY button
					CopyToUartTxBuffer((UByte *)"bdc 31 10 0 1 \"- DECREASE MIC\" 13 13\r", 37);			// button for decrementing headset MIC volume offset
					CopyToUartTxBuffer((UByte *)"xa 31 p request_base_command 31\r", 32);
					CopyToUartTxBuffer((UByte *)"bdc 32 170 0 1 \"RESET MIC\" 13 13\r", 33);				// button for resetting headset MIC volume offset
					CopyToUartTxBuffer((UByte *)"xa 32 p request_base_command 32\r", 32);
					CopyToUartTxBuffer((UByte *)"bdc 33 330 0 1 \"+ INCREASE MIC\" 13 13\r", 38);			// button for incrementing headset MIC volume offset
					CopyToUartTxBuffer((UByte *)"xa 33 p request_base_command 33\r", 32);
					CopyToUartTxBuffer((UByte *)"bdc 34 10 46 1 \"- DECREASE RCV\" 13 13\r", 38);			// button for decrementing headset RCV volume offset
					CopyToUartTxBuffer((UByte *)"xa 34 p request_base_command 34\r", 32);
					CopyToUartTxBuffer((UByte *)"bdc 35 170 46 1 \"RESET RCV\" 13 13\r", 34);				// button for resetting headset RCV volume offset
					CopyToUartTxBuffer((UByte *)"xa 35 p request_base_command 35\r", 32);
					CopyToUartTxBuffer((UByte *)"bdc 36 330 46 1 \"+ INCREASE RCV\" 13 13\r", 39);			// button for incrementing headset RCV volume offset
					CopyToUartTxBuffer((UByte *)"xa 36 p request_base_command 36\r", 32);
					CopyToUartTxBuffer((UByte *)"bdc 28 330 222 20 \"REG\" \"REG\" 26 28\r", 36);			// replacement REGISTER button
					CopyToUartTxBuffer((UByte *)"xmq 28 register_button_pressed register_button_released\r", 56);
					CopyToUartTxBuffer((UByte *)"bdc 30 380 222 20 \"DEL\" \"DEL\" 26 26\r", 36);			// replacement DELETE button
					CopyToUartTxBuffer((UByte *)"xmq 30 delete_button_pressed delete_button_pressed\r", 51);
				}
				(base_station).FillingRegistrationDisplay = FALSE;
				CopyToUartTxBuffer((UByte *)"touch on\r", 9);
			}
			break;
		case 0x1E:
			// delete one or more headsets
			if ((!(base_station).DualBase && ((base_station).DeletionCounter < MAX_Allowed_Users)) ||
				 ((base_station).DualBase && ((base_station).DeletionCounter < MAX_Allowed_Users_Dual)))
			{
				// these are single base headsets PP[0] - PP[9] or dual base headsets PP[0] - PP[4]
				i = (base_station).DeletionCounter++;
				while ((!(base_station).DualBase && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).DeletionCounter < MAX_Allowed_Users)) ||
						((base_station).DualBase && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).DeletionCounter < MAX_Allowed_Users_Dual)))
				{
					// if the current headset is not pressed, and the next button is ok to check, increment button index
					i = (base_station).DeletionCounter++;
				}
				if ((base_station).HeadsetButtonIsPressed[i])
				{
					if ((base_station).CalibratingPPMic)
					{
						CopyToUartTxBuffer((UByte *)"t \"decrease MIC volume\" 10 250\r", 31);
						BroadcastCalOffset(i, 0);
						break;
					}
					else if ((base_station).CalibratingPPRcv)
					{
						CopyToUartTxBuffer((UByte *)"t \"decrease RCV volume\" 10 250\r", 31);
						BroadcastCalOffset(i, 3);
						break;
					}

					(base_station).DisplayValueChanged = TRUE;
					(base_station).HeadsetButtonIsPressed[i] = FALSE;
					fp_subscription_removeSubscription(i);
					CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);
					SendAsciiValue(i + 40);
					CopyByteToUartTxBuffer(' ');
					CopyByteToUartTxBuffer('\"');
					CopyByteToUartTxBuffer('\"');
					CopyByteToUartTxBuffer('\r');
					(base_station).HeadsetIsOn[i] = FALSE;
					if ((base_station).MicIsOn[i])
					{
						WWMSF WWMSFVal;
						WWMSFVal.SubStatusType = MIC_MUTE_CMD;
						WWMSFVal.Sub.SetMicMute.MicMute = 1;    // 0 is unmute, 1 is mute
						HandlePacketFromPP(i, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
					}
					if ((base_station).OrderTakerID == i)
						(base_station).OrderTakerID = 0xFF;
				}
				OSStartTimer(PPDELETETASKTIMER, 50); 			// 50 x 10ms = 500ms pause before checking next button
			}
			else if (FIRST_BASE && ((base_station).DeletionCounter < MAX_Allowed_Users))
			{
				// these are dual base 2nd base headsets PP[5] - PP[9] on 1st base display
				i = (base_station).DeletionCounter++;
				while ((!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).DeletionCounter < MAX_Allowed_Users))
				{
					// if the current headset is not pressed, and the next button is ok to check, increment button index
					i = (base_station).DeletionCounter++;
				}
				if ((base_station).HeadsetButtonIsPressed[i])
				{
					(base_station).DisplayValueChanged = TRUE;
					(base_station).HeadsetButtonIsPressed[i] = FALSE;
					SendPCMCommand(DELETE_PP_ind + (i - MAX_Allowed_Users_Dual));
					(base_station).QuickDataBoard2[i - MAX_Allowed_Users_Dual].EmptyMarker = 1;
					CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);
					SendAsciiValue(i + 40);
					CopyByteToUartTxBuffer(' ');
					CopyByteToUartTxBuffer('\"');
					CopyByteToUartTxBuffer('\"');
					CopyByteToUartTxBuffer('\r');
					(base_station).HeadsetIsOn[i] = FALSE;
					if ((base_station).MicIsOn[i])
					{
						WWMSF WWMSFVal;
						WWMSFVal.SubStatusType = MIC_MUTE_CMD;	// Command
						WWMSFVal.Sub.SetMicMute.MicMute = 1;    // 0 is unmute, 1 is mute
						HandlePacketFromPP(i, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
					}
					if ((base_station).OrderTakerID == i)
						(base_station).OrderTakerID = 0xFF;
				}
				OSStartTimer(PPDELETETASKTIMER, 50); 			// 50 x 10ms = 500ms pause before checking next button
			}
			break;
		case 0x1F:
			// make one or more headsets listen only
			if ((!(base_station).DualBase && ((base_station).ListenOnlyCounter < MAX_Allowed_Users)) ||
				 ((base_station).DualBase && ((base_station).ListenOnlyCounter < MAX_Allowed_Users_Dual)))
			{
				i = (base_station).ListenOnlyCounter++;
				while ((!(base_station).DualBase && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).ListenOnlyCounter < MAX_Allowed_Users)) ||
						((base_station).DualBase && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).ListenOnlyCounter < MAX_Allowed_Users_Dual)))
				{
					// if the current headset is not pressed, and the next button is ok to check, increment button index
					i = (base_station).ListenOnlyCounter++;
				}
				if ((base_station).HeadsetButtonIsPressed[i])
				{
					if ((base_station).CalibratingPPMic)
					{
						CopyToUartTxBuffer((UByte *)"t \"increase MIC volume\" 10 250\r", 31);
						BroadcastCalOffset(i, 2);
						break;
					}
					else if ((base_station).CalibratingPPRcv)
					{
						CopyToUartTxBuffer((UByte *)"t \"increase RCV volume\" 10 250\r", 31);
						BroadcastCalOffset(i, 5);
						break;
					}

					(base_station).HeadsetButtonIsPressed[i] = FALSE;
					if (QuickData[i].EmptyMarker == 0)
					{
						if ((base_station).ListenOnly[i] == 0xFF)
							(base_station).ListenOnly[i] = 0x01;
						else
							(base_station).ListenOnly[i] = 0xFF;
						(base_station).DisplayValueChanged = TRUE;
						general_startTimer(i, LISTEN_ONLY_MODE_CMD, NULL, 0, 50);    	// send updated mode
						Ipei[0] = 0x01;													// hard coding 0x01 for 1st byte
						memcpy(&Ipei[1], QuickData[i].Upi, 4);
						ConvertIpeiToSN(i, SN, Ipei);
						if ((base_station).HeadsetIsOn[i])
							CopyToUartTxBuffer((UByte *)"m register_box:lbl_1_", 21);	// green
						else
							CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);	// gray
						SendAsciiValue(i + 40);
						CopyByteToUartTxBuffer(' ');
						CopyByteToUartTxBuffer('\"');
						if ((base_station).HeadsetIsOn[i])
							CopyToUartTxBuffer((UByte *)"on ", 3);
						else
							CopyToUartTxBuffer((UByte *)"off ", 4);
						for (ii = 6; ii < 16; ii++)
							CopyByteToUartTxBuffer(SN[ii]);
						CopyByteToUartTxBuffer('\"');
						CopyByteToUartTxBuffer('\r');
					}
					else
					{
						// just in case the headset was deleted but is still listed on the display
						CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);	// gray
						SendAsciiValue(i + 40);
						CopyByteToUartTxBuffer(' ');
						CopyByteToUartTxBuffer('\"');
						CopyByteToUartTxBuffer('\"');
						CopyByteToUartTxBuffer('\r');
					}
				}
				OSStartTimer(LISTENONLYTASKTIMER, 50); 			// 50 x 10ms = 500ms pause before checking next button
			}
			else if (FIRST_BASE && ((base_station).ListenOnlyCounter < MAX_Allowed_Users))
			{
				// work with 2nd base headsets on 1st base display
				i = (base_station).ListenOnlyCounter++;
				while ((!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).ListenOnlyCounter < MAX_Allowed_Users))
				{
					// if the current headset is not pressed, and the next button is ok to check, increment button index
					i = (base_station).ListenOnlyCounter++;
				}
				if ((base_station).HeadsetButtonIsPressed[i])
				{
					(base_station).HeadsetButtonIsPressed[i] = FALSE;
					if ((base_station).QuickDataBoard2[i - MAX_Allowed_Users_Dual].EmptyMarker == 0)
					{
						if ((base_station).ListenOnly[i] == 0xFF)
						{
							(base_station).ListenOnly[i] = 0x01;
							SendPCMCommand(LISTEN_ONLY_PP_ind + ((i - MAX_Allowed_Users_Dual) << 4) + 1);
						}
						else
						{
							(base_station).ListenOnly[i] = 0xFF;
							SendPCMCommand(LISTEN_ONLY_PP_ind + ((i - MAX_Allowed_Users_Dual) << 4) + 0);
						}
						(base_station).DisplayValueChanged = TRUE;
						Ipei[0] = 0x01;													// hard coding 0x01 for 1st byte
						memcpy(&Ipei[1], (base_station).QuickDataBoard2[i - MAX_Allowed_Users_Dual].Upi, 4);
						ConvertIpeiToSN(i, SN, Ipei);
						if ((base_station).HeadsetIsOn[i])
							CopyToUartTxBuffer((UByte *)"m register_box:lbl_1_", 21);	// green
						else
							CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);	// gray
						SendAsciiValue(i + 40);
						CopyByteToUartTxBuffer(' ');
						CopyByteToUartTxBuffer('\"');
						if ((base_station).HeadsetIsOn[i])
							CopyToUartTxBuffer((UByte *)"on ", 3);
						else
							CopyToUartTxBuffer((UByte *)"off ", 4);
						for (ii = 6; ii < 16; ii++)
							CopyByteToUartTxBuffer(SN[ii]);
						CopyByteToUartTxBuffer('\"');
						CopyByteToUartTxBuffer('\r');
					}
					else
					{
						// just in case the headset was deleted but is still listed on the display
						CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);	// gray
						SendAsciiValue(i + 40);
						CopyByteToUartTxBuffer(' ');
						CopyByteToUartTxBuffer('\"');
						CopyByteToUartTxBuffer('\"');
						CopyByteToUartTxBuffer('\r');
					}
				}
				OSStartTimer(LISTENONLYTASKTIMER, 50); 			// 50 x 10ms = 500ms pause before checking next button
			}
			break;
		// 0x28 - 0x31 are button presses for each headset serial number
		case 0x28:
		case 0x29:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x2D:
		case 0x2E:
		case 0x2F:
		case 0x30:
		case 0x31:
			i = (base_station).DisplayCommand - 0x28;
			if ((base_station).DisplayCommandData[0] == 1)
				(base_station).HeadsetButtonIsPressed[i] = TRUE;
			else
				(base_station).HeadsetButtonIsPressed[i] = FALSE;
			break;
	}
}

void PINScreen()
{
	int i = 0;

	if ((base_station).PinDigitIndex < 4)
		(base_station).TempPin[(base_station).PinDigitIndex] = (base_station).DisplayCommandData[0];
	else if ((base_station).PinDigitIndex < 8)
		(base_station).TempPin2[(base_station).PinDigitIndex - 4] = (base_station).DisplayCommandData[0];

	if ((base_station).DisplayScreen == PIN)
	{
		if ((base_station).PinDigitIndex == 0)
		{
			// draw blue square to erase possible thumbs down
			CopyToUartTxBuffer((UByte *)"r 72 146 131 205 1 00F\r", 23);
		}
		else if ((base_station).PinDigitIndex > 2)
		{
			if ((memcmp(&(base_station).TempPin, &(base_station).DisplayMasterPin, 4) == 0)
			 || (memcmp(&(base_station).TempPin, &(base_station).DisplayUserPin, 4) == 0))
			{
				CopyToUartTxBuffer((UByte *)"set e0 0\r", 9);
				(base_station).DisplayIsLocked = 0;
				(base_station).DisplayValueChanged = TRUE;
				switch ((base_station).DestAfterPin)
				{
					case MAIN:
						CopyToUartTxBuffer((UByte *)"m main\r", 7);
						break;
					case TOOLS:
						CopyToUartTxBuffer((UByte *)"m tools\r", 8);
						break;
					case REGISTRATION:
						if ((base_station).DualBase == DUAL_BASE_MENU_A)
						{
							for (i = 0; i < MAX_Allowed_Users_Dual; i++)
							{
								(base_station).QuickDataBoard2[i].EmptyMarker = 1;
								(base_station).QuickDataBoard2[i].Upi[0] = 0xFF;
								(base_station).QuickDataBoard2[i].Upi[1] = 0xFF;
								(base_station).QuickDataBoard2[i].Upi[2] = 0xFF;
								(base_station).QuickDataBoard2[i].Upi[3] = 0xFF;
							}
							SendPCMCommand(REQUEST_PP_SN_ind);			// request PP SNs
						}
						CopyToUartTxBuffer((UByte *)"m register_main\r", 16);
						break;
					case GREETER_SETUP:
						if ((base_station).GreeterInstalled)
						{
							if ((base_station).DualBase)
								CopyToUartTxBuffer((UByte *)"m greeter_screen_setup:lbl_1\r", 29);
							else
								CopyToUartTxBuffer((UByte *)"m greeter_setup:screen0\r", 24);
						}
						else
							CopyToUartTxBuffer((UByte *)"m show_greeter_promo\r", 21);
						break;
					case WENTWORTH_INFO_DEBUG:
						WTInfoDebugScreen();
						break;
					case MESSAGE_SETUP1:
					case MESSAGE_SETUP2:
					case NONE:
					case HELP:
					case WENTWORTH_INFO:
					case VOLUME:
					case VOLUME_B:
					case PIN:
					case NEW_PIN:
					case NEW_CLOCK:
					case GREETER_PIN:
					case GREETER_PIN_B:
					case NEW_NIGHT_TIME:
					case MENU_CONFIG:
						break;
				}
			}
			else
			{
				CopyToUartTxBuffer((UByte *)"m back_key\r", 11);
				CopyToUartTxBuffer((UByte *)"m thumbs_dn\r", 12);
			}
		}
	}
	else
	{
		if ((base_station).PinDigitIndex == 0)
		{
			// draw blue square to erase possible thumbs down
			CopyToUartTxBuffer((UByte *)"r 402 86 461 145 1 00F\r", 23);
		}
		else if ((base_station).PinDigitIndex == 3)
		{
			// switch to next line for re-entering PIN
			CopyToUartTxBuffer((UByte *)"set i8 48\r", 10);
			CopyToUartTxBuffer((UByte *)"set i9 212\r", 11);
		}
		else if ((base_station).PinDigitIndex > 6)
		{
			if (memcmp(&(base_station).TempPin, &(base_station).TempPin2, 4) == 0)
			{
				for (i = 0; i < 4; i++)
					(base_station).DisplayUserPin[i] = (base_station).TempPin[i];
				(base_station).DisplayValueChanged = TRUE;
				CopyToUartTxBuffer((UByte *)"m main\r", 7);
			}
			else
			{
				CopyToUartTxBuffer((UByte *)"m set_pin_back_key\r", 19);
				CopyToUartTxBuffer((UByte *)"m set_pin_thumbs_dn\r", 20);
			}
		}
	}
	(base_station).PinDigitIndex++;
}

/*
 * Display time is in the format H1H2:M1M2
 */
void ValidateClockDigit(UByte up, UByte place, UByte h1, UByte h2, UByte m1, UByte m2, UByte DayNight)
{
	if (up)
	{
		switch (place)
		{
			case 1:
				if (h1 < 2)
				{
					++h1;
					if (h1 == 2)
					{
						if (h2 > 3)
							h2 = 3;
					}
				}
				else
				{
					h1 = 0;
				}
				break;
			case 2:
				if (h1 < 2)
				{
					if (h2 < 9)
						++h2;
					else
						h2 = 0;
				}
				else
				{
					if (h2 < 3)
						++h2;
					else
						h2 = 0;
				}
				break;
			case 3:
				if (m1 < 5)
					++m1;
				else
					m1 = 0;
				break;
			case 4:
				if (m2 < 9)
					++m2;
				else
					m2 = 0;
				break;
		}
	}
	else
	{
		switch (place)
		{
			case 1:
				if (h1)
					--h1;
				else
				{
					h1 = 2;
					if (h2 > 3)
						h2 = 3;
				}
				break;
			case 2:
				if (h2)
					--h2;
				else
				{
					if (h1 < 2)
						h2 = 9;
					else
						h2 = 3;
				}
				break;
			case 3:
				if (m1)
					--m1;
				else
					m1 = 5;
				break;
			case 4:
				if (m2)
					--m2;
				else
					m2 = 9;
				break;
		}
	}

	if (DayNight == 0)
	{
		CopyToUartTxBuffer((UByte *)"m set_clock_time ", 17);
		CopyByteToUartTxBuffer(h1 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(h2 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(m1 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(m2 + 0x30);
		CopyByteToUartTxBuffer('\r');
	}
	else if (DayNight == 1)
	{
		CopyToUartTxBuffer((UByte *)"m set_night_time:start ", 23);
		CopyByteToUartTxBuffer(h1 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(h2 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(m1 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(m2 + 0x30);
		CopyByteToUartTxBuffer('\r');
	}
	else if (DayNight == 2)
	{
		CopyToUartTxBuffer((UByte *)"m set_night_time:end ", 21);
		CopyByteToUartTxBuffer(h1 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(h2 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(m1 + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer(m2 + 0x30);
		CopyByteToUartTxBuffer('\r');
	}
}

void SendTimesToDisplay()
{
	UByte i;
	char Days[7][9] =
	{
		" Monday  ",
		" Tuesday ",
		"Wednesday",
		"Thursday ",
		" Friday  ",
		"Saturday ",
		" Sunday  "
	};

	if ((base_station).DisplayCommandData[0] == 0)
	{
		(base_station).DisplayScreen = NEW_CLOCK;
		CopyToUartTxBuffer((UByte *)"m set_clock ", 12);
		CopyByteToUartTxBuffer((base_station).DisplayTime.timeHourMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).DisplayTime.timeHourLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).DisplayTime.timeMinMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).DisplayTime.timeMinLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer('\"');
		for (i = 0; i < 9; i++) { CopyByteToUartTxBuffer(Days[(base_station).CurrentDay][i]); }
		CopyByteToUartTxBuffer('\"');
		CopyByteToUartTxBuffer('\r');
	}
	else if ((base_station).DisplayCommandData[0] == 1)
	{
		(base_station).DisplayScreen = NEW_NIGHT_TIME;
		CopyToUartTxBuffer((UByte *)"m set_initial_night_start_time ", 31);
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeHourMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeHourLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeMinMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeMinLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeHourMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeHourLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeMinMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeMinLSB + 0x30);
		CopyByteToUartTxBuffer('\r');
	}
	else if ((base_station).DisplayCommandData[0] == 2)
	{
		(base_station).DisplayScreen = NEW_NIGHT_TIME;
		CopyToUartTxBuffer((UByte *)"m set_initial_night_end_time ", 29);
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeHourMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeHourLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeMinMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeEnd.timeMinLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeHourMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeHourLSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeMinMSB + 0x30);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer((base_station).NightVolumeTimeStart.timeMinLSB + 0x30);
		CopyByteToUartTxBuffer('\r');
	}
}

void HandleSettingDay(UByte Next)
{
	UByte i;
	char Days[7][9] =
	{
		" Monday  ",
		" Tuesday ",
		"Wednesday",
		"Thursday ",
		" Friday  ",
		"Saturday ",
		" Sunday  "
	};

	if (Next)
	{
		if ((base_station).CurrentDay < 6)
			(base_station).CurrentDay++;
		else
			(base_station).CurrentDay = 0;
	}
	else
	{
		if ((base_station).CurrentDay)
			(base_station).CurrentDay--;
		else
			(base_station).CurrentDay = 6;
	}

	CopyToUartTxBuffer((UByte *)"m set_clock_day ", 16);
	CopyByteToUartTxBuffer('\"');
	for (i = 0; i < 9; i++) { CopyByteToUartTxBuffer(Days[(base_station).CurrentDay][i]); }
	CopyByteToUartTxBuffer('\"');
	CopyByteToUartTxBuffer('\r');
}

void SetupGreeterScreen()
{
	UByte i, ii, btn;
	char GreetNames[NUM_LABEL_NAMES][16] =
	{
		"   Breakfast    ",
		"Breakfast Promo ",
		"    Morning     ",
		"     Lunch      ",
		"  Lunch Promo   ",
		"   Afternoon    ",
		"     Dinner     ",
		"  Dinner Promo  ",
		"    Evening     ",
		"   Late Night   ",
		"Late Night Promo",
		"     Snack      ",
		"     Closed     ",
		"   Pull Ahead   ",
		"    Promo 1     ",
		"    Promo 2     "
	};

	if ((base_station).MsgCounter < NUM_OF_GREETS)
	{
		i = (base_station).MsgCounter++;
		btn = (i * 5);

		(base_station).Message[i].StartIsPressed = FALSE;
		(base_station).Message[i].StopIsPressed = FALSE;

		if ((base_station).MsgDayBeingEdited == MONDAY)
		{
			CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
			SendAsciiValue(btn++);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			CopyByteToUartTxBuffer('G');
			SendAsciiValue(i + 1);
			CopyByteToUartTxBuffer('\"');
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
			SendAsciiValue(btn);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			for (ii = 0; ii < 16; ii++) { CopyByteToUartTxBuffer(GreetNames[((base_station).Message[i].MessageEnableName & 0x0F)][ii]); }
			CopyByteToUartTxBuffer('\"');
			CopyByteToUartTxBuffer('\r');
		}
		else
			++btn;							// skip greet # and label

		CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
		SendAsciiValue(++btn);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer('\"');
		SendAsciiValue((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4);
		switch ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4) * 4))
		{
			case 0:
				CopyToUartTxBuffer((UByte *)":00\"\r", 5);
				break;
			case 1:
				CopyToUartTxBuffer((UByte *)":15\"\r", 5);
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)":30\"\r", 5);
				break;
			case 3:
				CopyToUartTxBuffer((UByte *)":45\"\r", 5);
				break;
		}

		CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
		SendAsciiValue(++btn);
		CopyByteToUartTxBuffer(' ');
		CopyByteToUartTxBuffer('\"');
		SendAsciiValue((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4);
		switch ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4) * 4))
		{
			case 0:
				CopyToUartTxBuffer((UByte *)":14\"\r", 5);
				break;
			case 1:
				CopyToUartTxBuffer((UByte *)":29\"\r", 5);
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)":44\"\r", 5);
				break;
			case 3:
				CopyToUartTxBuffer((UByte *)":59\"\r", 5);
				break;
		}

		CopyToUartTxBuffer((UByte *)"xd ", 3);
		SendAsciiValue(++btn);
		CopyByteToUartTxBuffer('\r');
		CopyToUartTxBuffer((UByte *)"ssb ", 4);
		SendAsciiValue(btn);
		if (((base_station).Message[i].MessageEnableName & (1 << (4 + (base_station).MsgDayBeingEdited))) == (1 << (4 + (base_station).MsgDayBeingEdited)))
		{
			CopyToUartTxBuffer((UByte *)" 1\r", 3);
			(base_station).Message[i].OnOffIsPressed = TRUE;
		}
		else
		{
			CopyToUartTxBuffer((UByte *)" 0\r", 3);
			(base_station).Message[i].OnOffIsPressed = FALSE;
		}
		CopyToUartTxBuffer((UByte *)"xe ", 3);
		SendAsciiValue(btn);
		CopyByteToUartTxBuffer('\r');

		OSStartTimer(GENERALFPTASKTIMER, 10); 				// 10 x 10ms = 100ms pause before sending next button info
	}
	else
	{
		(base_station).FillingMsgDisplay = FALSE;
		if (!(base_station).GreeterActive)
			CopyToUartTxBuffer((UByte *)"ssb 35 1\r", 9);
		CopyToUartTxBuffer((UByte *)"touch on\r", 9);
	}
}

void HandleGreetDisplay()
{
	UByte selected_greet = (base_station).DisplayCommandData[0] - 1;
	UByte selected_button = (base_station).DisplayCommandData[1];
	BOOLEAN Pressed;

	if ((base_station).DisplayCommandData[2] == 1)
		Pressed = TRUE;
	else
		Pressed = FALSE;

	// if it is greeter enable button, remember it and return
	if (selected_greet == 8)
	{
		(base_station).DisplayValueChanged = TRUE;
		if (Pressed)
		{
			(base_station).GreeterActive = FALSE;
			(base_station).ActiveGreetNumber = 0;
			return;
		}
		else
		{
			(base_station).GreeterActive = TRUE;
			CheckForActiveGreet();
			CheckForActiveMessage();
			return;
		}
	}

	// if it is a day button, remember it, refresh the times and enables, and return
	if (selected_greet == 7)
	{
		(base_station).MsgDayBeingEdited = selected_button;
		(base_station).MsgBeingEdited = 0;
		(base_station).MsgCounter = 0;
		(base_station).FillingMsgDisplay = TRUE;
		OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 		// 35 x 10ms = 210ms pause before beginning to send button info
		return;
	}

	switch (selected_button)
	{
		case 2:					// note that the Start Time button is pressed/released
			if (Pressed)
				(base_station).Message[selected_greet].StartIsPressed = TRUE;
			else
				(base_station).Message[selected_greet].StartIsPressed = FALSE;
			break;
		case 3:					// note that the Stop Time button is pressed/released
			if (Pressed)
				(base_station).Message[selected_greet].StopIsPressed = TRUE;
			else
				(base_station).Message[selected_greet].StopIsPressed = FALSE;
			break;
		case 4:					// if it is the Enable button, just record the state and leave
			(base_station).DisplayValueChanged = TRUE;
			if (Pressed)
			{
				(base_station).Message[selected_greet].OnOffIsPressed = TRUE;
				(base_station).Message[selected_greet].MessageEnableName |= (1 << (4 + (base_station).MsgDayBeingEdited));
			}
			else
			{
				(base_station).Message[selected_greet].OnOffIsPressed = FALSE;
				(base_station).Message[selected_greet].MessageEnableName &= ~(1 << (4 + (base_station).MsgDayBeingEdited));
			}
			return;
	}

	if (!Pressed)
	{
		// When a Mn button is released, stop playing/recording any greet
		if ((base_station).MsgBeingEdited && (base_station).MessageIsPlaying)
		{
			RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);		// stops playing a message
			AFEDisablePostMicPath();												// disable DECT MIC input
		}
		else if ((base_station).MsgBeingEdited && (base_station).MessageIsRecording)
		{
			RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording a message
		}
		(base_station).MsgBeingEdited = 0;
		(base_station).Message[selected_greet].StartIsPressed = FALSE;
		(base_station).Message[selected_greet].StopIsPressed = FALSE;
		if ((base_station).GreeterScreenB)
			SendPCMCommand(GREETER_B_MSG_ind);
	}
	else if (((base_station).MsgBeingEdited == 0) && Pressed)
	{
		// one of the edit buttons was pressed so mark this greet as being edited
		(base_station).MsgBeingEdited = selected_greet + 1;

		if ((base_station).GreeterScreenB)
			SendPCMCommand(GREETER_B_MSG_ind + (base_station).MsgBeingEdited);		// tell greeter B which message is selected

		// if the selected greet is currently Enabled, un-Enable it
		if ((base_station).Message[selected_greet].OnOffIsPressed)
		{
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"ssb ", 4);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyToUartTxBuffer((UByte *)" 0\r", 3);
			CopyToUartTxBuffer((UByte *)"xe ", 3);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyByteToUartTxBuffer('\r');
			(base_station).Message[selected_greet].MessageEnableName &= ~(1 << (4 + (base_station).MsgDayBeingEdited));
			(base_station).Message[selected_greet].OnOffIsPressed = FALSE;
			(base_station).DisplayValueChanged = TRUE;
		}
	}
}

void HandleGreetName(UByte direction)
{
	UByte ii, i = (base_station).MsgBeingEdited - 1;
	UByte btn = (i * 5) + 1;
	char GreetNames[NUM_LABEL_NAMES][16] =
	{
		"   Breakfast    ",
		"Breakfast Promo ",
		"    Morning     ",
		"     Lunch      ",
		"  Lunch Promo   ",
		"   Afternoon    ",
		"     Dinner     ",
		"  Dinner Promo  ",
		"    Evening     ",
		"   Late Night   ",
		"Late Night Promo",
		"     Snack      ",
		"     Closed     ",
		"   Pull Ahead   ",
		"    Promo 1     ",
		"    Promo 2     "
	};

	(base_station).DisplayValueChanged = TRUE;

	if (direction)
	{
		if (((base_station).Message[i].MessageEnableName & 0x0F) == (NUM_LABEL_NAMES - 1))
			(base_station).Message[i].MessageEnableName = ((base_station).Message[i].MessageEnableName & 0xF0);
		else
			(base_station).Message[i].MessageEnableName++;
	}
	else
	{
		if (((base_station).Message[i].MessageEnableName & 0x0F) == 0)
			(base_station).Message[i].MessageEnableName = ((base_station).Message[i].MessageEnableName & 0xF0) + NUM_LABEL_NAMES - 1;
		else
			(base_station).Message[i].MessageEnableName--;
	}

	CopyToUartTxBuffer((UByte *)"m greet_button:lbl_1_", 21);
	SendAsciiValue(btn);
	CopyByteToUartTxBuffer(' ');
	CopyByteToUartTxBuffer('\"');
	for (ii = 0; ii < 16; ii++) { CopyByteToUartTxBuffer(GreetNames[((base_station).Message[i].MessageEnableName & 0x0F)][ii]); }
	CopyByteToUartTxBuffer('\"');
	CopyByteToUartTxBuffer('\r');
}

void HandleGreetTime(UByte direction)
{
	UByte i = (base_station).MsgBeingEdited - 1;
	UByte btn;

	if ((base_station).Message[i].StartIsPressed)
		btn = (i * 5) + 2;
	else
		btn = (i * 5) + 3;

	(base_station).DisplayValueChanged = TRUE;

	if ((base_station).Message[i].StartIsPressed)
	{
		if (direction)
		{
			if ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] == 95)
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] = 0;
			else
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited]++;
		}
		else
		{
			if ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] == 0)
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] = 95;
			else
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited]--;
		}
	}
	else
	{
		if (direction)
		{
			if ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] == 95)
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] = 0;
			else
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited]++;
		}
		else
		{
			if ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] == 0)
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] = 95;
			else
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited]--;
		}
	}

	CopyToUartTxBuffer((UByte *)"m greet_button:lbl_1_", 21);
	SendAsciiValue(btn);
	CopyByteToUartTxBuffer(' ');
	CopyByteToUartTxBuffer('\"');
	if ((base_station).Message[i].StartIsPressed)
	{
		SendAsciiValue((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4);
		switch ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4) * 4))
		{
			case 0:
				CopyToUartTxBuffer((UByte *)":00\"\r", 5);
				break;
			case 1:
				CopyToUartTxBuffer((UByte *)":15\"\r", 5);
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)":30\"\r", 5);
				break;
			case 3:
				CopyToUartTxBuffer((UByte *)":45\"\r", 5);
				break;
		}
	}
	else
	{
		SendAsciiValue((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4);
		switch ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4) * 4))
		{
			case 0:
				CopyToUartTxBuffer((UByte *)":14\"\r", 5);
				break;
			case 1:
				CopyToUartTxBuffer((UByte *)":29\"\r", 5);
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)":44\"\r", 5);
				break;
			case 3:
				CopyToUartTxBuffer((UByte *)":59\"\r", 5);
				break;
		}
	}
}

void SetupMessageScreen()
{
	UByte i, ii, btn, page = 7;
	char MessageNames[NUM_LABEL_NAMES][16] =
	{
		"  Hand Washing  ",
		"   Sanitizer    ",
		"Dining Rm Trash ",
		"HAACP Checklist ",
		" Quality Check  ",
		"Parking Lot Chk ",
		" Restroom Check ",
		"    Pre-Rush    ",
		"   Post-Rush    ",
		"    Message 1   ",
		"    Message 2   ",
		"    Message 3   ",
		"    Message 4   ",
		"    Message 5   ",
		"    Message 6   ",
		"  Check Alarms  "
	};

	if ((base_station).DisplayScreen == MESSAGE_SETUP2)
		page = 14;

	if ((base_station).MsgCounter < (NUM_OF_GREETS + page))
	{
		i = (base_station).MsgCounter++;
		btn = ((i - page) * 5);

		(base_station).Message[i].StartIsPressed = FALSE;
		(base_station).Message[i].StopIsPressed = FALSE;

		if ((base_station).MsgDayBeingEdited == MONDAY)
		{
			CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
			SendAsciiValue(btn++);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			if (i != 20)
			{
				CopyByteToUartTxBuffer('M');
				SendAsciiValue(i - 6);
			}
			else
			{
				CopyByteToUartTxBuffer('A');
				CopyByteToUartTxBuffer('1');
			}
			CopyByteToUartTxBuffer('\"');
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
			SendAsciiValue(btn);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			for (ii = 0; ii < 16; ii++) { CopyByteToUartTxBuffer(MessageNames[((base_station).Message[i].MessageEnableName & 0x0F)][ii]); }
			CopyByteToUartTxBuffer('\"');
			CopyByteToUartTxBuffer('\r');
		}
		else
			++btn;							// skip message # and label

		// don't fill in Start / Repeat boxes for the Alert Message
		if (i != 20)
		{
			CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
			SendAsciiValue(++btn);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			SendAsciiValue((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4);
			switch ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4) * 4))
			{
				case 0:
					CopyToUartTxBuffer((UByte *)":00\"\r", 5);
					break;
				case 1:
					CopyToUartTxBuffer((UByte *)":15\"\r", 5);
					break;
				case 2:
					CopyToUartTxBuffer((UByte *)":30\"\r", 5);
					break;
				case 3:
					CopyToUartTxBuffer((UByte *)":45\"\r", 5);
					break;
			}

			CopyToUartTxBuffer((UByte *)"m greet_button:lbl_0_", 21);
			SendAsciiValue(++btn);
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('\"');
			SendAsciiValue((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4);
			switch ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4) * 4))
			{
				case 0:
					CopyToUartTxBuffer((UByte *)":00\"\r", 5);
					break;
				case 1:
					CopyToUartTxBuffer((UByte *)":15\"\r", 5);
					break;
				case 2:
					CopyToUartTxBuffer((UByte *)":30\"\r", 5);
					break;
				case 3:
					CopyToUartTxBuffer((UByte *)":45\"\r", 5);
					break;
			}

			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue(++btn);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"ssb ", 4);
			SendAsciiValue(btn);
			if (((base_station).Message[i].MessageEnableName & (1 << (4 + (base_station).MsgDayBeingEdited))) == (1 << (4 + (base_station).MsgDayBeingEdited)))
			{
				CopyToUartTxBuffer((UByte *)" 1\r", 3);
				(base_station).Message[i].OnOffIsPressed = TRUE;
			}
			else
			{
				CopyToUartTxBuffer((UByte *)" 0\r", 3);
				(base_station).Message[i].OnOffIsPressed = FALSE;
			}
			CopyToUartTxBuffer((UByte *)"xe ", 3);
			SendAsciiValue(btn);
			CopyByteToUartTxBuffer('\r');
		}
		else
		{
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue(++btn);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue(++btn);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue(++btn);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"ssb ", 4);
			SendAsciiValue(btn);
			if (((base_station).Message[i].MessageEnableName & (1 << (4 + (base_station).MsgDayBeingEdited))) == (1 << (4 + (base_station).MsgDayBeingEdited)))
			{
				CopyToUartTxBuffer((UByte *)" 1\r", 3);
				(base_station).Message[i].OnOffIsPressed = TRUE;
			}
			else
			{
				CopyToUartTxBuffer((UByte *)" 0\r", 3);
				(base_station).Message[i].OnOffIsPressed = FALSE;
			}
			CopyToUartTxBuffer((UByte *)"xe ", 3);
			SendAsciiValue(btn);
			CopyByteToUartTxBuffer('\r');
		}

		OSStartTimer(GENERALFPTASKTIMER, 10); 				// 10 x 10ms = 100ms pause before sending next button info
	}
	else
	{
		(base_station).FillingMsgDisplay = FALSE;
		CopyToUartTxBuffer((UByte *)"touch on\r", 9);
	}
}

void HandleMessageDisplay()
{
	UByte selected_greet = (base_station).DisplayCommandData[0] - 1;
	UByte selected_button = (base_station).DisplayCommandData[1];
	BOOLEAN Pressed;
	UByte page = 7;

	if ((base_station).DisplayScreen == MESSAGE_SETUP2)
		page = 14;

	if ((base_station).DisplayCommandData[2] == 1)
		Pressed = TRUE;
	else
		Pressed = FALSE;

	// if it is a day button, remember it, refresh the times and enables, and return
	if (selected_greet == 7)
	{
		(base_station).MsgDayBeingEdited = selected_button;
		(base_station).MsgBeingEdited = 0;
		(base_station).MsgCounter = page;
		(base_station).FillingMsgDisplay = TRUE;
		OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 		// 35 x 10ms = 210ms pause before beginning to send button info
		return;
	}

	switch (selected_button)
	{
		case 2:					// note that the Start Time button is pressed/released
			if (Pressed)
				(base_station).Message[selected_greet + page].StartIsPressed = TRUE;
			else
				(base_station).Message[selected_greet + page].StartIsPressed = FALSE;
			break;
		case 3:					// note that the Stop Time button is pressed/released
			if (Pressed)
				(base_station).Message[selected_greet + page].StopIsPressed = TRUE;
			else
				(base_station).Message[selected_greet + page].StopIsPressed = FALSE;
			break;
		case 4:					// if it is the Enable button, just record the state and leave
			(base_station).DisplayValueChanged = TRUE;
			if (Pressed)
			{
				(base_station).Message[selected_greet + page].OnOffIsPressed = TRUE;
				(base_station).Message[selected_greet + page].MessageEnableName |= (1 << (4 + (base_station).MsgDayBeingEdited));
			}
			else
			{
				(base_station).Message[selected_greet + page].OnOffIsPressed = FALSE;
				(base_station).Message[selected_greet + page].MessageEnableName &= ~(1 << (4 + (base_station).MsgDayBeingEdited));
			}
			return;
	}

	if (!Pressed)
	{
		// When a Mn button is released, stop playing/recording any greet
		if ((base_station).MsgBeingEdited && (base_station).MessageIsPlaying)
		{
			RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);		// stops playing a message
			AFEDisablePostMicPath();												// disable DECT MIC input
		}
		else if ((base_station).MsgBeingEdited && (base_station).MessageIsRecording)
		{
			RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording a message
		}
		(base_station).MsgBeingEdited = 0;
		(base_station).Message[selected_greet].StartIsPressed = FALSE;
		(base_station).Message[selected_greet].StopIsPressed = FALSE;
		if ((base_station).GreeterScreenB)
			SendPCMCommand(GREETER_B_MSG_ind);
	}
	else if (((base_station).MsgBeingEdited == 0) && Pressed)
	{
		// one of the edit buttons was pressed so mark this greet as being edited
		(base_station).MsgBeingEdited = selected_greet + page + 1;

		if ((base_station).GreeterScreenB)
			SendPCMCommand(GREETER_B_MSG_ind + (base_station).MsgBeingEdited);		// tell greeter B which message is selected

		// if the selected greet is currently Enabled, un-Enable it
		if ((base_station).Message[selected_greet + page].OnOffIsPressed)
		{
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"ssb ", 4);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyToUartTxBuffer((UByte *)" 0\r", 3);
			CopyToUartTxBuffer((UByte *)"xe ", 3);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"xd ", 3);
			SendAsciiValue((selected_greet * 5) + 4);
			CopyByteToUartTxBuffer('\r');
			(base_station).Message[selected_greet + page].MessageEnableName &= ~(1 << (4 + (base_station).MsgDayBeingEdited));
			(base_station).Message[selected_greet + page].OnOffIsPressed = FALSE;
			(base_station).DisplayValueChanged = TRUE;
		}
	}
}

void HandleMessageName(UByte direction)
{
	UByte ii, i, btn;
	char GreetNames[NUM_LABEL_NAMES][16] =
	{
		"  Hand Washing  ",
		"   Sanitizer    ",
		"Dining Rm Trash ",
		"HAACP Checklist ",
		" Quality Check  ",
		"Parking Lot Chk ",
		" Restroom Check ",
		"    Pre-Rush    ",
		"   Post-Rush    ",
		"    Message 1   ",
		"    Message 2   ",
		"    Message 3   ",
		"    Message 4   ",
		"    Message 5   ",
		"    Message 6   ",
		"  Check Alarms  "
	};

	(base_station).DisplayValueChanged = TRUE;

	i = (base_station).MsgBeingEdited - 1;

	if ((base_station).DisplayScreen == MESSAGE_SETUP1)
		btn = ((i - 7) * 5) + 1;
	else
		btn = ((i - 14) * 5) + 1;

	if (direction)
	{
		if (((base_station).Message[i].MessageEnableName & 0x0F) == (NUM_LABEL_NAMES - 1))
			(base_station).Message[i].MessageEnableName = ((base_station).Message[i].MessageEnableName & 0xF0);
		else
			(base_station).Message[i].MessageEnableName++;
	}
	else
	{
		if (((base_station).Message[i].MessageEnableName & 0x0F) == 0)
			(base_station).Message[i].MessageEnableName = ((base_station).Message[i].MessageEnableName & 0xF0) + NUM_LABEL_NAMES - 1;
		else
			(base_station).Message[i].MessageEnableName--;
	}

	CopyToUartTxBuffer((UByte *)"m greet_button:lbl_1_", 21);
	SendAsciiValue(btn);
	CopyByteToUartTxBuffer(' ');
	CopyByteToUartTxBuffer('\"');
	for (ii = 0; ii < 16; ii++) { CopyByteToUartTxBuffer(GreetNames[((base_station).Message[i].MessageEnableName & 0x0F)][ii]); }
	CopyByteToUartTxBuffer('\"');
	CopyByteToUartTxBuffer('\r');
}

void HandleMessageTime(UByte direction)
{
	UByte i = (base_station).MsgBeingEdited - 1;
	UByte ii = 0, btn;

	if ((base_station).MsgBeingEdited < 8)
		ii = (base_station).MsgBeingEdited - 1;
	else if ((base_station).MsgBeingEdited < 15)
		ii = (base_station).MsgBeingEdited - 8;
	else
		ii = (base_station).MsgBeingEdited - 15;

	if ((base_station).Message[i].StartIsPressed)
		btn = (ii * 5) + 2;
	else
		btn = (ii * 5) + 3;

	(base_station).DisplayValueChanged = TRUE;

	if ((base_station).Message[i].StartIsPressed)
	{
		if (direction)
		{
			if ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] == 95)
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] = 0;
			else
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited]++;
		}
		else
		{
			if ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] == 0)
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] = 95;
			else
				(base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited]--;
		}
	}
	else
	{
		if (direction)
	{
			if ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] == 95)
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] = 0;
			else
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited]++;
		}
		else
		{
			if ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] == 0)
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] = 95;
			else
				(base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited]--;
		}
	}

	CopyToUartTxBuffer((UByte *)"m greet_button:lbl_1_", 21);
	SendAsciiValue(btn);
	CopyByteToUartTxBuffer(' ');
	CopyByteToUartTxBuffer('\"');
	if ((base_station).Message[i].StartIsPressed)
	{
		SendAsciiValue((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4);
		switch ((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StartTime[(base_station).MsgDayBeingEdited] / 4) * 4))
		{
			case 0:
				CopyToUartTxBuffer((UByte *)":00\"\r", 5);
				break;
			case 1:
				CopyToUartTxBuffer((UByte *)":15\"\r", 5);
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)":30\"\r", 5);
				break;
			case 3:
				CopyToUartTxBuffer((UByte *)":45\"\r", 5);
				break;
		}
	}
	else
	{
		SendAsciiValue((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4);
		switch ((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] - (((base_station).Message[i].StopTime[(base_station).MsgDayBeingEdited] / 4) * 4))
		{
			case 0:
				CopyToUartTxBuffer((UByte *)":00\"\r", 5);
				break;
			case 1:
				CopyToUartTxBuffer((UByte *)":15\"\r", 5);
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)":30\"\r", 5);
				break;
			case 3:
				CopyToUartTxBuffer((UByte *)":45\"\r", 5);
				break;
		}
	}
}

void GreeterAuthorizationScreen()
{
	int i;

	if ((base_station).PinDigitIndex < 4)
		(base_station).TempPin[(base_station).PinDigitIndex] = (base_station).DisplayCommandData[0] + 0x30;

	if ((base_station).PinDigitIndex > 2)
	{
		for (i = 0; i < 4; i++)
			if ((base_station).DisplayScreen == GREETER_PIN)
				(base_station).GrtrMsgrAuthCode[i] = (base_station).TempPin[i];
			else
				SendPCMCommand(GREETER_B_AUTH_ind + (i << 4) + ((base_station).TempPin[i] - 0x30));

		// save code to EEPROM
		(base_station).DisplayValueChanged = TRUE;
		CopyToUartTxBuffer((UByte *)"m main\r", 7);
	}

	(base_station).PinDigitIndex++;
}

void HandleDebugButton(UByte cmd)
{
	int i = 0;
	(base_station).HeadsetCounter = 0;
	(base_station).DeletionCounter = 0;
	(base_station).ListenOnlyCounter = 0;
	(base_station).CalibratingPPMic = FALSE;
	(base_station).CalibratingPPRcv = FALSE;

	CopyToUartTxBuffer((UByte *)"t \"                                        \" 10 250\r", 52);

	switch (cmd)
	{
		case 31:	// - PP MIC offset
			(base_station).CalibratingPPMic = TRUE;
			RegistrationScreen(0x1E);
			break;
		case 32:	// reset PP MIC offset
			i = (base_station).HeadsetCounter++;
			while ((!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).HeadsetCounter < MAX_Allowed_Users))
			{
				i = (base_station).HeadsetCounter++;
			}
			if ((base_station).HeadsetButtonIsPressed[i])
			{
				CopyToUartTxBuffer((UByte *)"t \"reset MIC volume\" 10 250\r", 28);
				BroadcastCalOffset(i, 1);
			}
			break;
		case 33:	// + PP MIC offset
			(base_station).CalibratingPPMic = TRUE;
			RegistrationScreen(0x1F);
			break;
		case 34:	// - PP RCV offset
			(base_station).CalibratingPPRcv = TRUE;
			RegistrationScreen(0x1E);
			break;
		case 35:	// reset PP RCV offset
		i = (base_station).HeadsetCounter++;
		while ((!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).HeadsetCounter < MAX_Allowed_Users))
		{
				i = (base_station).HeadsetCounter++;
			}
			if ((base_station).HeadsetButtonIsPressed[i])
			{
				CopyToUartTxBuffer((UByte *)"t \"reset RCV volume\" 10 250\r", 28);
				BroadcastCalOffset(i, 4);
			}
			break;
		case 36:	// + PP RCV offset
			(base_station).CalibratingPPRcv = TRUE;
			RegistrationScreen(0x1F);
			break;
	}
}

void ServiceDisplay()
{
	// service the Display command that was sent
	int i;
	BOOLEAN PreviousDayTime;

#ifndef FOR_TEST_BASE_ONLY
	if (FIRST_BASE)
	{
		StopTimer(DISPLAYTASKTIMER);
		OSStartTimer(DISPLAYTASKTIMER, 30000);				// re-start 5 minute timer
	}
#endif

	switch ((base_station).DisplayCommand)
	{
		case 0x01:
			if ((base_station).DisplayScreen == GREETER_SETUP ||
				(base_station).DisplayScreen == MESSAGE_SETUP1 ||
				(base_station).DisplayScreen == MESSAGE_SETUP2 ||
				(base_station).DisplayScreen == NEW_CLOCK)
			{
				if ((base_station).GreeterActive)
				{
					CheckForActiveGreet();							// check if selected greet has changed
					CheckForActiveMessage();						// check if reminders or alarm selections have changed
					PlayQueuedMessage();							// start playing any queued reminders or alarm
				}
			}
			(base_station).DisplayScreen = NONE;
			CopyToUartTxBuffer((UByte *)"*abt\r", 5);
			switch ((base_station).DisplayCommandData[0])
			{
				case 0x01:
					CopyToUartTxBuffer((UByte *)"m main\r", 7);
					break;
				case 0x02:
					CopyToUartTxBuffer((UByte *)"m tools\r", 8);
					break;
				case 0x03:
					if ((base_station).DualBase == DUAL_BASE_MENU_A)
					{
						StopTimer(VEHICLEDETECTTASKTIMER); 						// temporarily stop checking vehicle detector
						for (i = 0; i < MAX_Allowed_Users_Dual; i++)
						{
							(base_station).QuickDataBoard2[i].EmptyMarker = 1;
							(base_station).QuickDataBoard2[i].Upi[0] = 0xFF;
							(base_station).QuickDataBoard2[i].Upi[1] = 0xFF;
							(base_station).QuickDataBoard2[i].Upi[2] = 0xFF;
							(base_station).QuickDataBoard2[i].Upi[3] = 0xFF;
						}
						SendPCMCommand(REQUEST_PP_SN_ind);						// request PP SNs
						OSStartTimer(VEHICLEDETECTTASKTIMER, 100); 				// 100 x 10ms = 1s resume checking vehicle detector
					}
					CopyToUartTxBuffer((UByte *)"m register_main\r", 16);
					break;
				case 0x04:
					CopyToUartTxBuffer((UByte *)"m show_help_main\r", 17);
					break;
				case 0x05:
					if (!(base_station).VehicleDetectIsActive)
					{
						if ((base_station).GreeterInstalled)
							CopyToUartTxBuffer((UByte *)"m greeter_setup:screen0\r", 24);
						else
							CopyToUartTxBuffer((UByte *)"m show_greeter_promo\r", 21);
					}
					else
						CopyToUartTxBuffer((UByte *)"m main\r", 7);
					break;
				case 0x06:
					// same as 0x05 but menu A for dual menu set up
					if (!(base_station).VehicleDetectIsActive)
					{
						if ((base_station).GreeterInstalled)
							CopyToUartTxBuffer((UByte *)"m greeter_setup:screen0\r", 24);
						else
							CopyToUartTxBuffer((UByte *)"m show_greeter_promo\r", 21);
					}
					else
						CopyToUartTxBuffer((UByte *)"m main\r", 7);
					break;
				case 0x07:
					// same as 0x05 but for menu B for dual menu set up
					if (((base_station).DualBase == DUAL_BASE_MENU_A) && (base_station).GreeterInstalledB)
						SendPCMCommand(GREETER_REQ_ind);
					break;
			}
			break;
		case 0x02:
			(base_station).DisplayScreen = WENTWORTH_INFO;
			WTInfoScreen();
			break;
		case 0x03:
			(base_station).DisplayScreen = REGISTRATION;
			(base_station).HeadsetCounter = 0;
			(base_station).FillingRegistrationDisplay = TRUE;
			for (i = 0; i < MAX_Allowed_Users; i++)
				(base_station).HeadsetButtonIsPressed[i] = FALSE;
			RegistrationScreen((base_station).DisplayCommand);
			break;
		case 0x04:
			(base_station).DisplayScreen = TOOLS;
			break;
		case 0x05:
			(base_station).DisplayScreen = PIN;
			(base_station).PinDigitIndex = 0;
			switch ((base_station).DisplayCommandData[0])
			{
				case 0x01:	(base_station).DestAfterPin = MAIN;						break;
				case 0x02:	(base_station).DestAfterPin = TOOLS;					break;
				case 0x03:	(base_station).DestAfterPin = REGISTRATION;				break;
				case 0x04:	(base_station).DestAfterPin = GREETER_SETUP;			break;
				case 0x05:	(base_station).DestAfterPin = WENTWORTH_INFO_DEBUG;		break;
			}
			break;
		case 0x06:
			if (((base_station).DisplayScreen == GREETER_PIN) || ((base_station).DisplayScreen == GREETER_PIN_B))
				GreeterAuthorizationScreen();
			else
				PINScreen();
			break;
		case 0x07:
			(base_station).PinDigitIndex = 0;
			break;
		case 0x08:
			if ((base_station).NewSystemMode)
			{
				StopTimer(SYSTEMMODETASKTIMER);
				(base_station).NewSystemMode = (base_station).NewSystemMode > 4 ? 2 : (base_station).NewSystemMode + 1;
			}
			else
			{
				(base_station).NewSystemMode = (base_station).SystemMode > 4 ? 2 : (base_station).SystemMode + 1;
			}
			if ((base_station).DualBase && ((base_station).MenuConfig > 1) && ((base_station).NewSystemMode == 4))
				(base_station).NewSystemMode++;																			// skip AHF for EXP system
			OSStartTimer(SYSTEMMODETASKTIMER, 300);																		// wait 3s before changing

			CopyToUartTxBuffer((UByte *)"bc 24\r", 6);
			CopyToUartTxBuffer((UByte *)"bc 25\r", 6);
			CopyToUartTxBuffer((UByte *)"bc 26\r", 6);
			CopyToUartTxBuffer((UByte *)"bc 27\r", 6);
			CopyToUartTxBuffer((UByte *)"set e1 ", 7);
			SendAsciiValue((base_station).NewSystemMode - 1);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"m hand_button_press:lbl_", 24);
			SendAsciiValue((base_station).NewSystemMode - 1);
			CopyByteToUartTxBuffer('\r');
			break;
		case 0x09:
			break;
		case 0x0A:
			(base_station).DisplayScreen = VOLUME;
			CopyToUartTxBuffer((UByte *)"m pre_volume", 12);															// send slider bar max values first
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(10);															// i1 detect max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoProfile1 ? INBOUND_P1 : INBOUND_P0);	// i2 inbound max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(GRILL);														// i3 grill max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoProfile1 ? OUTBOUND_P1 : OUTBOUND_P0);	// i4 day max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoProfile1 ? OUTBOUND_P1 : OUTBOUND_P0);	// i5 night max
			CopyByteToUartTxBuffer('\r');																				// complete command string

			CopyToUartTxBuffer((UByte *)"m volume", 8);																	// start volume display with parameters
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).MenuConfig > 1 ? (base_station).DualBase : 0);// eA volume menus info
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);															// e5 detect current volume - not implemented
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).InboundVol);									// e6 inbound volume
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).GrillSpeakerVolume);							// e7 grill current volume
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeDay);						// e8 day volume
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeNight);						// e9 night volume
			CopyByteToUartTxBuffer('\r');																				// complete command string
			break;
		case 0x0B:
			(base_station).DisplayTime.timeHourMSB = (base_station).DisplayCommandData[0];
			(base_station).DisplayTime.timeHourLSB = (base_station).DisplayCommandData[1];
			(base_station).DisplayTime.timeMinMSB = (base_station).DisplayCommandData[2];
			(base_station).DisplayTime.timeMinLSB = (base_station).DisplayCommandData[3];
			if ((base_station).BaseRTC || (base_station).GreetRTC)
			{
				// leaving the time setting screen so save the current time/day to the RTC
				if ((base_station).DualBase == DUAL_BASE_MENU_A)
				{
					SendPCMCommand(UPDATE_CLOCK_B_ind + 0x10 + (base_station).DisplayTime.timeHourMSB);
					SendPCMCommand(UPDATE_CLOCK_B_ind + 0x20 + (base_station).DisplayTime.timeHourLSB);
					SendPCMCommand(UPDATE_CLOCK_B_ind + 0x30 + (base_station).DisplayTime.timeMinMSB);
					SendPCMCommand(UPDATE_CLOCK_B_ind + 0x40 + (base_station).DisplayTime.timeMinLSB);
					SendPCMCommand(UPDATE_CLOCK_B_ind + 0x50 + (base_station).CurrentDay);
				}
				StopTimer(CLOCKTASKTIMER); 				// re-start FP clock timer to sync with RTC
				OSStartTimer(CLOCKTASKTIMER, 6000); 	// 6000 x 10ms = 1 minute
				SetupAccess1Bus();
				if ((base_station).BaseRTC)
					BASE_RTC_ON;						// connect Base RTC
				else if ((base_station).GreetRTC)
					RunGreetClock(MESSAGE_INIT, 2);		// connect Greeter RTC
				WriteAccess1(RTC, 0x00, 0x00);																						// seconds
				WriteAccess1(RTC, 0x01, ((base_station).DisplayTime.timeMinMSB << 4) + (base_station).DisplayTime.timeMinLSB);		// minutes
				WriteAccess1(RTC, 0x02, ((base_station).DisplayTime.timeHourMSB << 4) + (base_station).DisplayTime.timeHourLSB);	// hour
				WriteAccess1(RTC, 0x03, (base_station).CurrentDay + 1);																// day of week; base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
				if ((base_station).BaseRTC)
					BASE_PCM_ON;						// disconnect Base RTC
				else if ((base_station).GreetRTC)
					RunGreetClock(MESSAGE_INIT, 1);		// disconnect Greeter RTC
				SetupPCMBus();
			}
			break;
		case 0x0D:		// increment clock digit
			ValidateClockDigit(1, (base_station).DisplayCommandData[0],
								  (base_station).DisplayCommandData[1],
								  (base_station).DisplayCommandData[2],
								  (base_station).DisplayCommandData[3],
								  (base_station).DisplayCommandData[4],
								  (base_station).DisplayCommandData[5]);
			break;
		case 0x0E:		// decrement clock digit
			ValidateClockDigit(0, (base_station).DisplayCommandData[0],
								  (base_station).DisplayCommandData[1],
								  (base_station).DisplayCommandData[2],
								  (base_station).DisplayCommandData[3],
								  (base_station).DisplayCommandData[4],
								  (base_station).DisplayCommandData[5]);
			break;
		case 0x0F:		// change day
			HandleSettingDay((base_station).DisplayCommandData[0]);
			break;
		case 0x10:
			(base_station).DisplayScreen = MAIN;

			if ((base_station).RegistrationButtonPressed)
			{
				(base_station).RegistrationButtonPressed = FALSE;
				(base_station).RegistrationAllowed = FALSE;
				if ((base_station).DualBase)
					SendPCMCommand(REGISTER_PP_ind + FALSE);
			}

			if ((base_station).GreeterInstalled)
			{
				AFESetGainInboundVolumeFP(NORMAL_INBOUND);								// return post mic/speaker to normal volumes
				RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
				BOOLEAN OkToTurnMicOff = TRUE;
				for (i = 0; i < MAX_Allowed_Users; i++)
				{
					if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
					{
						OkToTurnMicOff = FALSE;
						i = MAX_Allowed_Users;
					}
				}
				// if no other headset MICs are on and no vehicle is detected, turn off menu board MIC
				if (OkToTurnMicOff && !(base_station).VehicleDetectIsActive)
				{
					if ((base_station).MessageIsPlaying == 0)
						AFEDisablePostMicPath();										// disable DECT MIC input
					MENU_SPKR_AMP_OFF;													// leave post speaker off (enables GREET audio path in to DECT MICP/N)
					GRILL_SPEAKER_OFF;													// leave grill speaker off
				}
				else if (!OkToTurnMicOff || (base_station).VehicleDetectIsActive)
				{
					if ((base_station).MessageIsPlaying == 0)
						MENU_SPKR_AMP_ON;												// turn post speaker back on (enable BC5 audio path in to DECT MICP/N)
					if ((base_station).GrillSpeakerVolume)
						GRILL_SPEAKER_ON;												// turn grill speaker back on
					usec_pause(35000);													// to avoid pop when opening post mic
					AFEEnablePostMicPath();												// enable DECT MIC input
				}
			}

			if ((base_station).GreeterActive || (base_station).NighTimeInEffect)
			{
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

			if ((base_station).DisplayValueChanged && !(base_station).GreeterScreenB)
			{
				(base_station).DisplayValueChanged = FALSE;
				general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
			}

			PreviousDayTime = (base_station).DayTime;
			CheckNightVolumeTime();		// update sun/moon icon
			if ((base_station).DayTime != PreviousDayTime)
				RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);

			if ((base_station).PPCalibration)
				(base_station).PPCalibration = FALSE;
			if ((base_station).CalibratingPPMic)
				(base_station).CalibratingPPMic = FALSE;
			if ((base_station).CalibratingPPRcv)
				(base_station).CalibratingPPRcv = FALSE;

			if (FIRST_BASE && (base_station).GreeterScreenB)
			{
				(base_station).GreeterScreenB = FALSE;
				SendPCMCommand(GREETER_DATA_START_ind);
				for (i = 0; i < NUM_OF_MESSAGES; i++)
				{
					SendPCMCommand(0xFF00 + (base_station).Message[i].MessageEnableName);
					SendPCMCommand(((base_station).Message[i].StartTime[0] << 8) + (base_station).Message[i].StopTime[0]);
					SendPCMCommand(((base_station).Message[i].StartTime[1] << 8) + (base_station).Message[i].StopTime[1]);
					SendPCMCommand(((base_station).Message[i].StartTime[2] << 8) + (base_station).Message[i].StopTime[2]);
					SendPCMCommand(((base_station).Message[i].StartTime[3] << 8) + (base_station).Message[i].StopTime[3]);
				}
				SendPCMCommand(GREETER_DATA_STOP_ind);
				SendPCMCommand(GREETER_B_ACTIVE_ind + 0x10 + (base_station).GreeterActive);
				general_eeprom_read_req(EE_WT_GREET_INFO, ((9 * NUM_OF_MESSAGES) + 1), 4);	// restore greeter A data
			}
			break;
		case 0x11:
			if ((base_station).DisplayScreen == VOLUME_B)
				SendPCMCommand(VOLUME_SETTINGS_B_ind + ((base_station).DisplayCommandData[0] << 4) + (base_station).DisplayCommandData[1]);
			else
				VolumeAdjustScreen();
			break;
		case 0x12:
			(base_station).DisplayIsLocked = 1;
			general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
			break;
		case 0x13:
			(base_station).DisplayValueChanged = TRUE;
			(base_station).NightVolumeTimeStart.timeHourMSB = (base_station).DisplayCommandData[0];
			(base_station).NightVolumeTimeStart.timeHourLSB = (base_station).DisplayCommandData[1];
			(base_station).NightVolumeTimeStart.timeMinMSB  = (base_station).DisplayCommandData[2];
			(base_station).NightVolumeTimeStart.timeMinLSB  = (base_station).DisplayCommandData[3];
			if ((base_station).DualBase == DUAL_BASE_MENU_A)
			{
				SendPCMCommand(UPDATE_NITE_START_B_ind + 0x10 + (base_station).NightVolumeTimeStart.timeHourMSB);
				SendPCMCommand(UPDATE_NITE_START_B_ind + 0x20 + (base_station).NightVolumeTimeStart.timeHourLSB);
				SendPCMCommand(UPDATE_NITE_START_B_ind + 0x30 + (base_station).NightVolumeTimeStart.timeMinMSB);
				SendPCMCommand(UPDATE_NITE_START_B_ind + 0x40 + (base_station).NightVolumeTimeStart.timeMinLSB);
			}
			if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4) != 0)
				(base_station).NighTimeInEffect = TRUE;
			else
				(base_station).NighTimeInEffect = FALSE;
			break;
		case 0x14:
			(base_station).DisplayValueChanged = TRUE;
			(base_station).NightVolumeTimeEnd.timeHourMSB = (base_station).DisplayCommandData[0];
			(base_station).NightVolumeTimeEnd.timeHourLSB = (base_station).DisplayCommandData[1];
			(base_station).NightVolumeTimeEnd.timeMinMSB  = (base_station).DisplayCommandData[2];
			(base_station).NightVolumeTimeEnd.timeMinLSB  = (base_station).DisplayCommandData[3];
			if ((base_station).DualBase == DUAL_BASE_MENU_A)
			{
				SendPCMCommand(UPDATE_NITE_STOP_B_ind + 0x10 + (base_station).NightVolumeTimeEnd.timeHourMSB);
				SendPCMCommand(UPDATE_NITE_STOP_B_ind + 0x20 + (base_station).NightVolumeTimeEnd.timeHourLSB);
				SendPCMCommand(UPDATE_NITE_STOP_B_ind + 0x30 + (base_station).NightVolumeTimeEnd.timeMinMSB);
				SendPCMCommand(UPDATE_NITE_STOP_B_ind + 0x40 + (base_station).NightVolumeTimeEnd.timeMinLSB);
			}
			if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4) != 0)
				(base_station).NighTimeInEffect = TRUE;
			else
				(base_station).NighTimeInEffect = FALSE;
			break;
		case 0x15:		// register headsets button pressed/released
			if ((base_station).DisplayCommandData[0] == 1)
			{
				(base_station).RegistrationButtonPressed = TRUE;
				if ((base_station).DualBase)
				{
					UByte base1 = fp_subscription_getNumberOfSubscriptions();
					UByte base2 = 0;
					for(i = 0; i < MAX_Allowed_Users_Dual; i++)
					{
						if((base_station).QuickDataBoard2[i].EmptyMarker == 0)
						{
							base2++;
						}
					}
					// if both have 5 headsets registered, do not allow more registrations
					if ((base1 >= MAX_Allowed_Users_Dual) && (base2 >= MAX_Allowed_Users_Dual))
					{
						PrintStatus(0, "already full - no registrations allowed");
						(base_station).RegistrationAllowed = FALSE;
						CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);	// release Registration button
					}
					// if first base has 5 headsets registered, only allow registrations on second base
					else if (base1 >= MAX_Allowed_Users_Dual)
					{
						PrintStatus(0, "only allowing registrations on second base");
						(base_station).RegistrationAllowed = FALSE;
						SendPCMCommand(REGISTER_PP_ind + TRUE);
					}
					// if second base has 5 headsets registered, only allow registrations on first base
					else if (base2 >= MAX_Allowed_Users_Dual)
					{
						PrintStatus(0, "only allowing registrations on first base");
						(base_station).RegistrationAllowed = TRUE;
					}
					// ok to allow registrations on either base
					else
					{
						PrintStatus(0, "allowing registrations on either base");
						(base_station).RegistrationAllowed = TRUE;
						SendPCMCommand(REGISTER_PP_ind + TRUE);
					}
				}
				else if (fp_subscription_getNumberOfSubscriptions() >= MAX_Allowed_Users)
				{
					PrintStatus(0, "already full - no registrations allowed");
					(base_station).RegistrationAllowed = FALSE;
					CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);	// release Registration button
				}
				else
					(base_station).RegistrationAllowed = TRUE;
			}
			else
			{
				(base_station).RegistrationButtonPressed = FALSE;
				(base_station).RegistrationAllowed = FALSE;
				if ((base_station).DualBase)
					SendPCMCommand(REGISTER_PP_ind + FALSE);
			}
			break;
		case 0x16:
			(base_station).DisplayScreen = NEW_PIN;
			(base_station).PinDigitIndex = 0;
			break;
		case 0x18:
			if ((base_station).DisplayScreen == GREETER_SETUP)
				HandleGreetDisplay();
			else
				HandleMessageDisplay();
			break;
		case 0x19:
			if ((base_station).GreeterScreenB)
				SendPCMCommand(GREETER_0x19_ind + (base_station).DisplayCommandData[0]);
			else
			{
				if ((base_station).VehicleDetectIsActive)									// ignore play/record while a car is present
				{
					if ((base_station).DisplayCommandData[0] == 1)
					{
						if (!FIRST_BASE)
							SendPCMCommand(GREETER_0x19_ind + 0x10);

						if (((base_station).DisplayScreen == GREETER_SETUP)
						 || ((base_station).DisplayScreen == MESSAGE_SETUP1)
						 || ((base_station).DisplayScreen == MESSAGE_SETUP2))
						{
							CopyToUartTxBuffer((UByte *)"ssb 43 0\r", 9);					// release play button
							CopyToUartTxBuffer((UByte *)"xe 43\r", 6);						// enable play button
							CopyToUartTxBuffer((UByte *)"xe 44\r", 6);						// enable record button
							CopyToUartTxBuffer((UByte *)"xd 45\r", 6);						// disable stop button
						}
					}
					else if ((base_station).DisplayCommandData[0] == 2)
					{
						if (!FIRST_BASE)
							SendPCMCommand(GREETER_0x19_ind + 0x10);

						if (((base_station).DisplayScreen == GREETER_SETUP)
						 || ((base_station).DisplayScreen == MESSAGE_SETUP1)
						 || ((base_station).DisplayScreen == MESSAGE_SETUP2))
						{
							CopyToUartTxBuffer((UByte *)"ssb 44 0\r", 9);					// release record button
							CopyToUartTxBuffer((UByte *)"xe 43\r", 6);						// enable play button
							CopyToUartTxBuffer((UByte *)"xe 44\r", 6);						// enable record button
							CopyToUartTxBuffer((UByte *)"xd 45\r", 6);						// disable stop button
						}
					}
				}
				else if ((base_station).DisplayCommandData[0] == 1)
				{
					MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
					GRILL_SPEAKER_OFF;														// mute grill speaker during playback
					RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
					AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
					AFEEnablePostMicPath();													// enable DECT MIC input
					RunGreetClock(MESSAGE_PLAY_START, (base_station).MsgBeingEdited);		// sets up and starts playing a message
				}
				else if ((base_station).DisplayCommandData[0] == 2)
				{
					MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
					GRILL_SPEAKER_OFF;														// mute grill speaker during playback
					RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
					AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
					RunGreetClock(MESSAGE_RECORD_START, (base_station).MsgBeingEdited);		// sets up and starts recording a message
				}
				else if ((base_station).MessageIsPlaying)
				{
					RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);		// stops playing a message
					AFEDisablePostMicPath();												// disable DECT MIC input
				}
				else if ((base_station).MessageIsRecording)
				{
					RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording a message
				}
			}
			break;
		case 0x1A:
			if ((base_station).DisplayScreen == GREETER_SETUP)
				HandleGreetName((base_station).DisplayCommandData[0]);
			else
				HandleMessageName((base_station).DisplayCommandData[0]);
			break;
		case 0x1B:
			if ((base_station).DisplayScreen == GREETER_SETUP)
				HandleGreetTime((base_station).DisplayCommandData[0]);
			else
				HandleMessageTime((base_station).DisplayCommandData[0]);
			break;
		case 0x1C:
			SendTimesToDisplay();
			break;
		case 0x1E:		// delete headset button pressed
			(base_station).DeletionCounter = 0;
			RegistrationScreen((base_station).DisplayCommand);
			break;
		case 0x1F:		// listen-only button pressed
			(base_station).ListenOnlyCounter = 0;
			RegistrationScreen((base_station).DisplayCommand);
			break;
		case 0x28:
		case 0x29:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x2D:
		case 0x2E:
		case 0x2F:
		case 0x30:
		case 0x31:
			RegistrationScreen((base_station).DisplayCommand);
			break;
		case 0x40:
			(base_station).DisplayScreen = WENTWORTH_INFO_DEBUG;
			if ((base_station).DualBase == DUAL_BASE_MENU_A)
			{
				SendPCMCommand(REQUEST_PUP_MSB_B_ind);
				SendPCMCommand(REQUEST_PUP_LSB_B_ind);
				general_startTimer(-1, DISPLAY_WT_DEBUG_INFO, NULL, 0, 10);	// wait for count from second base before displaying screen
			}
			else
				WTInfoDebugScreen();
			break;
		case 0x41:
			if (((base_station).DisplayCommandData[0] == 1) && (base_station).PowerOnCount)
			{
				(base_station).PowerOnCount = 0;
				general_startTimer(-1, WRITE_WT_DEBUG_EEPROM, NULL, 0, 5);	// write current value to EEPROM
			}
			else if (((base_station).DisplayCommandData[0] == 2) && (base_station).PowerOnCountB)
			{
				(base_station).PowerOnCountB = 0;
				SendPCMCommand(RESET_PUP_B_ind);
			}
			WTInfoDebugScreen();
			break;
		case 0x42:
			if ((base_station).DisplayCommandData[0] == 1)
				(base_station).DisplayScreen = GREETER_PIN;			// handle GREETER A authorization
			else
				(base_station).DisplayScreen = GREETER_PIN_B;		// handle GREETER B authorization
			(base_station).PinDigitIndex = 0;
			CopyToUartTxBuffer((UByte *)"m pin\r", 6);
			break;
		case 0x43:
			switch ((base_station).DisplayCommandData[0])
			{
				case 0:
					if ((base_station).InboundVol > INBOUND_P0)
						AFESetGainPP2PPMixer(INBOUND_P0);
					if ((base_station).CurrentOutboundVolume > OUTBOUND_P0)
					{
						AFESetGainSpkrVolumeFP(OUTBOUND_P0);
						(base_station).CurrentOutboundVolume = OUTBOUND_P0;
					}
					if ((base_station).PostSpeakerVolumeDay > OUTBOUND_P0)
						(base_station).PostSpeakerVolumeDay = OUTBOUND_P0;
					if ((base_station).PostSpeakerVolumeNight > OUTBOUND_P0)
						(base_station).PostSpeakerVolumeNight = OUTBOUND_P0;
					ALANGO_PROFILE_0;													// BC5 PIO6 = LO (profile0/ma11 settings)
					(base_station).AlangoProfile1 = FALSE;
					(base_station).DisplayValueChanged = TRUE;
					if ((base_station).DualBase == DUAL_BASE_MENU_A)
						SendPCMCommand(UPDATE_ALANGO_CFG_B_ind);
					else if (!FIRST_BASE)
						general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);		// write current values to EEPROM
					break;
				case 1:
					if ((base_station).InboundVol > INBOUND_P1)
						AFESetGainPP2PPMixer(INBOUND_P1);
					if ((base_station).CurrentOutboundVolume > OUTBOUND_P1)
					{
						AFESetGainSpkrVolumeFP(OUTBOUND_P1);
						(base_station).CurrentOutboundVolume = OUTBOUND_P1;
					}
					if ((base_station).PostSpeakerVolumeDay > OUTBOUND_P1)
						(base_station).PostSpeakerVolumeDay = OUTBOUND_P1;
					if ((base_station).PostSpeakerVolumeNight > OUTBOUND_P1)
						(base_station).PostSpeakerVolumeNight = OUTBOUND_P1;
					ALANGO_PROFILE_1;													// BC5 PIO6 = HI (profile1/ma10 settings)
					(base_station).AlangoProfile1 = TRUE;
					(base_station).DisplayValueChanged = TRUE;
					if ((base_station).DualBase == DUAL_BASE_MENU_A)
						SendPCMCommand(UPDATE_ALANGO_CFG_B_ind + 1);
					else if (!FIRST_BASE)
						general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);		// write current values to EEPROM
					break;
				case 2:
					// BC5 on/off button press here
					(base_station).BC5Bypassed = TRUE;
					// send BC5 OFF to PPs
					BroadcastSystemModeState(-1);
					break;
				case 3:
					// BC5 on/off button release here
					(base_station).BC5Bypassed = FALSE;
					// send BC5 ON to PPs
					BroadcastSystemModeState(-1);
					break;
				case 4:
					// enable calibration screen for testing headsets
					(base_station).PPCalibration = TRUE;
					CopyToUartTxBuffer((UByte *)"m register_main\r", 16);
					break;
				case 7:
					CopyToUartTxBuffer((UByte *)"touch off\r", 10);
					StopTimer(WATCHDOGTASKTIMER);
					if ((base_station).DualBase == DUAL_BASE_MENU_A)
						SendPCMCommand(STOP_WATCHDOG_B_ind);
					break;
				case 31:	// - PP MIC offset
				case 32:	// reset PP MIC offset
				case 33:	// + PP MIC offset
				case 34:	// - PP RCV offset
				case 35:	// reset PP RCV offset
				case 36:	// + PP RCV offset
					HandleDebugButton((base_station).DisplayCommandData[0]);
					break;
				default:
					PrintStatus(0, "unknown command request");
					break;
			}
			break;
		case 0x50:
			(base_station).DisplayScreen = GREETER_SETUP;
			(base_station).MsgDayBeingEdited = MONDAY;
			(base_station).MsgBeingEdited = 0;
			(base_station).MsgCounter = 0;
			(base_station).FillingMsgDisplay = TRUE;
			MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
			GRILL_SPEAKER_OFF;														// mute grill speaker during playback
			RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
			OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 			// 35 x 10ms = 210ms pause before beginning to send button info
			break;
		case 0x51:
			(base_station).DisplayScreen = MESSAGE_SETUP1;
			(base_station).MsgDayBeingEdited = MONDAY;
			(base_station).MsgBeingEdited = 0;
			(base_station).MsgCounter = 7;
			(base_station).FillingMsgDisplay = TRUE;
			MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
			GRILL_SPEAKER_OFF;														// mute grill speaker during playback
			RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
			OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 			// 35 x 10ms = 210ms pause before beginning to send button info
			break;
		case 0x52:
			(base_station).DisplayScreen = MESSAGE_SETUP2;
			(base_station).MsgDayBeingEdited = MONDAY;
			(base_station).MsgBeingEdited = 0;
			(base_station).MsgCounter = 14;
			(base_station).FillingMsgDisplay = TRUE;
			MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
			GRILL_SPEAKER_OFF;														// mute grill speaker during playback
			RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
			OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 			// 35 x 10ms = 210ms pause before beginning to send button info
			break;
		case 0x60:
			(base_station).DisplayScreen = VOLUME_B;
			CopyToUartTxBuffer((UByte *)"m pre_volume", 12);															// send slider bar max values first
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(10);															// i1 detect max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoProfile1B ? INBOUND_P1 : INBOUND_P0);	// i2 inbound max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(GRILL);														// i3 grill max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoProfile1B ? OUTBOUND_P1 : OUTBOUND_P0);	// i4 day max
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoProfile1B ? OUTBOUND_P1 : OUTBOUND_P0);	// i5 night max
			CopyByteToUartTxBuffer('\r');																				// complete command string

			CopyToUartTxBuffer((UByte *)"m volume", 8);																	// start volume display with parameters
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(DUAL_BASE_MENU_B);											// eA volume menus info
			CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);															// e5 detect current volume - not implemented
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).InboundVolB);									// e6 inbound volume
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).GrillSpeakerVolumeB);							// e7 grill current volume
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeDayB);						// e8 day volume
			CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeNightB);						// e9 night volume
			CopyByteToUartTxBuffer('\r');																				// complete command string
			break;
		case 0x61:
			(base_station).DisplayScreen = MENU_CONFIG;
			if ((base_station).DisplayCommandData[0] && (base_station).DualBase)
			{
				(base_station).DisplayValueChanged = TRUE;
				(base_station).MenuConfig = (base_station).DisplayCommandData[0];
				SendPCMCommand(UPDATE_MENU_CFG_B_ind + (base_station).MenuConfig);
				CopyToUartTxBuffer((UByte *)"set eA ", 7);																// update volume config setting: menu A or B
				SendAsciiValue((base_station).MenuConfig > 1 ? (base_station).DualBase : 0);
				CopyByteToUartTxBuffer('\r');
				CopyToUartTxBuffer((UByte *)"set e3 ", 7);																// update menu B config setting
				SendAsciiValue((base_station).MenuConfig > 1 ? 1 : 0);
				CopyByteToUartTxBuffer('\r');
				CopyToUartTxBuffer((UByte *)"set eB ", 7);																// update menu config setting
				SendAsciiValue((base_station).MenuConfig);
				CopyByteToUartTxBuffer('\r');
				if ((base_station).SystemMode == AUTO_HANDS_FREE)
				{
					(base_station).SystemMode = HANDS_FREE;
					CopyToUartTxBuffer((UByte *)"set e1 ", 7);
					SendAsciiValue((base_station).SystemMode - 1);
					CopyByteToUartTxBuffer('\r');
				}
				CopyToUartTxBuffer((UByte *)"m pre_lane_config\r", 18);													// refresh menu config screen with new setting
				BroadcastSystemModeState(-1);																			// update headsets with new menu config
			}
			break;
		default:
			CopyToUartTxBuffer((UByte *)"s 0 1\r", 6);
			CopyToUartTxBuffer((UByte *)"f 13 B\r", 7);
			CopyToUartTxBuffer((UByte *)"t \"No Command ?\" 10 25\r", 23);
			CopyToUartTxBuffer((UByte *)"t \"", 3);
			CopyByteToUartTxBuffer('A');
			CopyByteToUartTxBuffer('[');
			CopyByteToUartTxBuffer((base_station).DisplayCommand);
			CopyByteToUartTxBuffer(']');
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('B');
			CopyByteToUartTxBuffer('[');
			CopyByteToUartTxBuffer((base_station).DisplayCommandData[0]);
			CopyByteToUartTxBuffer(']');
			CopyByteToUartTxBuffer(' ');
			CopyByteToUartTxBuffer('C');
			CopyByteToUartTxBuffer('[');
			CopyByteToUartTxBuffer((base_station).DisplayCommandData[1]);
			CopyByteToUartTxBuffer(']');
			CopyToUartTxBuffer((UByte *)"\" 0 50\r", 7);
			break;
	}
}
