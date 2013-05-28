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

extern void ConvertHexSNtoAriSN(IPEIType Hex_SN, char SerialNumber[11]);
extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void CopyByteToUartTxBuffer(UByte buffer);
extern void BroadcastSystemModeState(PPIDType user);
extern UByte fp_subscription_removeSubscription(PPIDType user);
extern void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length);
extern void CheckNightVolumeTime(void);
extern void RunGreetClock(UByte greet_cmd, UByte greet_selection);
extern UByte fp_subscription_getNumberOfSubscriptions();
#ifdef SECOND_BASE_CODE
extern void SendPCMCommand(WORD cmd);
#endif

extern UByte GENERALFPTASKTIMER;
extern UByte GENERALBC5TASKTIMER;
extern UByte SYSTEMMODETASKTIMER;
extern UByte DISPLAYTASKTIMER;
extern UByte PPDELETETASKTIMER;
extern UByte LISTENONLYTASKTIMER;
extern UByte VEHICLEDETECTTASKTIMER;
extern UByte CLOCKTASKTIMER;
extern UByte WATCHDOGTASKTIMER;

//extern int uart_getbyte(char *data);
static void usec_pause(unsigned int x)			// 0-65535
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

void WTInfoScreen()
{
	int i = 0;

#ifdef SECOND_BASE_CODE
	if ((base_station).SecondBoardPresent)
	{
		UByte test[11] = "0123456789\0";
		if (memcmp((base_station).SerialNumber2, test, 10) == 0)
			ConvertHexSNtoAriSN((base_station).FP2_ARI, (base_station).SerialNumber2);
		CopyToUartTxBuffer((UByte *)"m show_wentworth:dual ", 22);
	}
	else
#endif
	{
		CopyToUartTxBuffer((UByte *)"m show_wentworth:single ", 24);
	}
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
#ifdef SECOND_BASE_CODE
	if ((base_station).SecondBoardPresent)
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
#endif
	CopyByteToUartTxBuffer('\r');

//	general_startTimer(-1, WT_HEAP_CHECK, NULL, 0, 200);
}

void WTInfoDebugScreen()
{
#ifdef SECOND_BASE_CODE
	if (FIRST_BASE && (base_station).SecondBoardPresent)
	{
		CopyToUartTxBuffer((UByte *)"m show_wentworth_debug:dual ", 28);
		SendAsciiValue((base_station).PowerOnCount);
		CopyByteToUartTxBuffer(' ');
		SendAsciiValue((base_station).PowerOnCount2);
		CopyByteToUartTxBuffer('\r');
	}
	else
#endif
	{
		CopyToUartTxBuffer((UByte *)"m show_wentworth_debug:single ", 30);
		SendAsciiValue((base_station).PowerOnCount);
		CopyByteToUartTxBuffer('\r');
	}

	CopyToUartTxBuffer((UByte *)"s 0 10\r", 7);			// black on light gray if required

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for toggling Alango mode
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	if ((base_station).AlangoNear)
		CopyToUartTxBuffer((UByte *)"bdc 4 5 5 20 \"NEAR\" \"FAR\" 26 28\r", 32);
	else
		CopyToUartTxBuffer((UByte *)"bdc 4 5 5 21 \"NEAR\" \"FAR\" 26 28\r", 32);
	CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	CopyToUartTxBuffer((UByte *)"t \"Inbound noise\" 60 18 T\r", 26);
	CopyToUartTxBuffer((UByte *)"t \"canceling\" 60 38 T\r", 22);
	CopyToUartTxBuffer((UByte *)"xa	4 p request_base_command 0\r", 30);
	CopyToUartTxBuffer((UByte *)"xa	4 r request_base_command 1\r", 30);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for halting WatchDog
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	CopyToUartTxBuffer((UByte *)"bdc 5 160 224 20 \"STOP\\nWD\" \"STOPPED\" 43 49\r", 44);
	CopyToUartTxBuffer((UByte *)"xa	5 p request_base_command 2\r", 30);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for toggling Alert input pin between C/P3[4] (default input) and N/P1[2] (optional 12V VD input)
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	if ((base_station).UsingP34ForAlarm)
		CopyToUartTxBuffer((UByte *)"bdc 6 5 105 20 \"pin C\" \"pin N\" 26 28\r", 37);
	else
		CopyToUartTxBuffer((UByte *)"bdc 6 5 105 21 \"pin C\" \"pin N\" 26 28\r", 37);
	CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	CopyToUartTxBuffer((UByte *)"t \"used for\" 60 118 T\r", 22);
	CopyToUartTxBuffer((UByte *)"t \"Alert\" 60 138 T\r", 19);
	CopyToUartTxBuffer((UByte *)"xa	6 p request_base_command 3\r", 30);
	CopyToUartTxBuffer((UByte *)"xa	6 r request_base_command 4\r", 30);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for toggling "Hear Greet in headset" option ... if option is available
	if ((base_station).P33UsedForGreetMux && (base_station).GreeterActive)
	{
		CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
		if ((base_station).PlayGreetInPP)
			CopyToUartTxBuffer((UByte *)"bdc 8 430 5 21 \"NO\" \"YES\" 26 28\r", 32);
		else
			CopyToUartTxBuffer((UByte *)"bdc 8 430 5 20 \"NO\" \"YES\" 26 28\r", 32);
		CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
		CopyToUartTxBuffer((UByte *)"t \"GREET\" 320 18 T\r", 19);
		CopyToUartTxBuffer((UByte *)"t \"in HSet\" 320 38 T\r", 21);
		CopyToUartTxBuffer((UByte *)"xa	8 p request_base_command 7\r", 30);
		CopyToUartTxBuffer((UByte *)"xa	8 r request_base_command 8\r", 30);

		usec_pause(0xFFFF);									// to avoid over running the display input buffer
	}

	// add chip revision comment
	CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	if (CHIP_TEST1_REG == 0x11)
		CopyToUartTxBuffer((UByte *)"t \"chip ver = ES6\" 225 250 T\r", 29);
	else if (CHIP_TEST1_REG == 0x12)
        CopyToUartTxBuffer((UByte *)"t \"chip ver = ES7\" 225 250 T\r", 29);
	else if (CHIP_TEST1_REG == 0x13)
        CopyToUartTxBuffer((UByte *)"t \"chip ver = ES8\" 225 250 T\r", 29);
	else
        CopyToUartTxBuffer((UByte *)"t \"chip ver = ES?\" 225 250 T\r", 29);

	usec_pause(0xFFFF);									// to avoid over running the display input buffer

	// add a bitmap and command for toggling BC5 demo mode
	CopyToUartTxBuffer((UByte *)"f 13B\r", 6);
	if ((base_station).BC5Bypassed)
		CopyToUartTxBuffer((UByte *)"bdc 7 5 55 21 \"ON\" \"OFF\" 26 28\r", 31);
	else
		CopyToUartTxBuffer((UByte *)"bdc 7 5 55 20 \"ON\" \"OFF\" 26 28\r", 31);
	CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	CopyToUartTxBuffer((UByte *)"t \"HSet noise\" 60 68 T\r", 23);
	CopyToUartTxBuffer((UByte *)"t \"canceling\" 60 88 T\r", 22);
	CopyToUartTxBuffer((UByte *)"xa	7 p request_base_command 5\r", 30);
	CopyToUartTxBuffer((UByte *)"xa	7 r request_base_command 6\r", 30);
}

void VolumeAdjustScreen()
{
	UByte vol_item, requested_vol, current_vol;

	(base_station).DisplayValueChanged = TRUE;
	vol_item = (base_station).DisplayCommandData[0];		// which volume control: 0-detect, 1-inbound, 2-grill, 3-day, 4-night
	requested_vol = (base_station).DisplayCommandData[1];	// volume requested
	// INBOUND volume can be 0 - INBOUND_NEAR or 0 - INBOUND_FAR
	if (vol_item == 1)
	{
		if ((base_station).AlangoNear)
		{
			// INBOUND volume can be 0 - INBOUND_NEAR (Alango NEAR setting)
			if (requested_vol > INBOUND_NEAR)
			{
				requested_vol = INBOUND_NEAR;
			}
		}
		else
		{
			// INBOUND volume can be 0 - INBOUND_FAR (Alango FAR setting)
			if (requested_vol > INBOUND_FAR)
			{
				requested_vol = INBOUND_FAR;
			}
		}
	}
	// GRILL volume can be 0 - GRILL
	else if (vol_item == 2)
	{
		if (requested_vol > GRILL)
		{
			requested_vol = GRILL;
		}
	}
	// OUTBOUND volumes are 0 - OUTBOUND_NEAR or OUTBOUND_FAR
	else if ((vol_item == 3) || (vol_item == 4))
	{
		if ((base_station).AlangoNear)
		{
			// OUTBOUND volume can be 0 - OUTBOUND_NEAR (Alango NEAR setting)
			if (requested_vol > OUTBOUND_NEAR)
			{
				requested_vol = OUTBOUND_NEAR;
			}
		}
		else
		{
			// OUTBOUND volume can be 0 - OUTBOUND_FAR (Alango FAR setting)
			if (requested_vol > OUTBOUND_FAR)
			{
				requested_vol = OUTBOUND_FAR;
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
		if ((base_station).GrillShouldBeOn && ((base_station).GrillSpeakerVolume > 0))
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
	CopyToUartTxBuffer((UByte *)"m set_volume ", 13);
	SendAsciiValue(vol_item);
	CopyByteToUartTxBuffer(' ');
	SendAsciiValue(requested_vol);
	CopyByteToUartTxBuffer('\r');
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
#ifdef SECOND_BASE_CODE
		if ((!(base_station).SecondBoardPresent && ((base_station).HeadsetCounter < MAX_Allowed_Users)) ||
		     ((base_station).SecondBoardPresent && ((base_station).HeadsetCounter < MAX_Allowed_Users_Dual)))
#else
		if ((base_station).HeadsetCounter < MAX_Allowed_Users)
#endif
		{
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
#ifdef SECOND_BASE_CODE
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
#endif
		else
		{
			(base_station).FillingRegistrationDisplay = FALSE;
			CopyToUartTxBuffer((UByte *)"touch on\r", 9);
		}
		break;
	case 0x1E:
		// delete one or more headsets
#ifdef SECOND_BASE_CODE
		if ((!(base_station).SecondBoardPresent && ((base_station).DeletionCounter < MAX_Allowed_Users)) ||
		     ((base_station).SecondBoardPresent && ((base_station).DeletionCounter < MAX_Allowed_Users_Dual)))
#else
		if ((base_station).DeletionCounter < MAX_Allowed_Users)
#endif
		{
			i = (base_station).DeletionCounter++;
#ifdef SECOND_BASE_CODE
			while ((!(base_station).SecondBoardPresent && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).DeletionCounter < MAX_Allowed_Users)) ||
			        ((base_station).SecondBoardPresent && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).DeletionCounter < MAX_Allowed_Users_Dual)))
#else
			while ((!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).DeletionCounter < MAX_Allowed_Users))
#endif
			{
				// if the current headset is not pressed, and the next button is ok to check, increment button index
				i = (base_station).DeletionCounter++;
			}
			if ((base_station).HeadsetButtonIsPressed[i])
			{
				(base_station).DisplayValueChanged = TRUE;
				(base_station).HeadsetButtonIsPressed[i] = FALSE;
				fp_subscription_removeSubscription(i);
				CopyToUartTxBuffer((UByte *)"m register_box:lbl_0_", 21);
				SendAsciiValue(i + 40);
				CopyByteToUartTxBuffer(' ');
				CopyByteToUartTxBuffer('\"');
				CopyByteToUartTxBuffer('\"');
				CopyByteToUartTxBuffer('\r');
				(base_station).ListenOnly[i] = 0xFF;
				(base_station).HeadsetIsOn[i] = FALSE;
				if ((base_station).MicIsOn[i])
				{
					WWMSF WWMSFVal;
					WWMSFVal.SubStatusType = MIC_MUTE_CMD;
					WWMSFVal.Sub.SetMicMute.MicMute = 1;              			// 0 is unmute, 1 is mute
					HandlePacketFromPP(i, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
				}
			}
			OSStartTimer(PPDELETETASKTIMER, 50); 			// 50 x 10ms = 500ms pause before checking next button
		}
#ifdef SECOND_BASE_CODE
		else if (FIRST_BASE && ((base_station).DeletionCounter < MAX_Allowed_Users))
		{
			// work with 2nd base headsets on 1st base display
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
				(base_station).ListenOnly[i] = 0xFF;
				(base_station).HeadsetIsOn[i] = FALSE;
				if ((base_station).MicIsOn[i])
				{
					WWMSF WWMSFVal;
					WWMSFVal.SubStatusType = MIC_MUTE_CMD;
					WWMSFVal.Sub.SetMicMute.MicMute = 1;              			// 0 is unmute, 1 is mute
					HandlePacketFromPP(i, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
				}
			}
			OSStartTimer(PPDELETETASKTIMER, 50); 			// 50 x 10ms = 500ms pause before checking next button
		}
#endif
		break;
	case 0x1F:
		// make one or more headsets listen only
#ifdef SECOND_BASE_CODE
		if ((!(base_station).SecondBoardPresent && ((base_station).ListenOnlyCounter < MAX_Allowed_Users)) ||
		     ((base_station).SecondBoardPresent && ((base_station).ListenOnlyCounter < MAX_Allowed_Users_Dual)))
#else
		if ((base_station).ListenOnlyCounter < MAX_Allowed_Users)
#endif
		{
			i = (base_station).ListenOnlyCounter++;
#ifdef SECOND_BASE_CODE
			while ((!(base_station).SecondBoardPresent && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).ListenOnlyCounter < MAX_Allowed_Users)) ||
			        ((base_station).SecondBoardPresent && (!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).ListenOnlyCounter < MAX_Allowed_Users_Dual)))
#else
			while ((!(base_station).HeadsetButtonIsPressed[i]) && ((base_station).ListenOnlyCounter < MAX_Allowed_Users))
#endif
			{
				// if the current headset is not pressed, and the next button is ok to check, increment button index
				i = (base_station).ListenOnlyCounter++;
			}
			if ((base_station).HeadsetButtonIsPressed[i])
			{
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
#ifdef SECOND_BASE_CODE
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
#endif
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
#ifdef SECOND_BASE_CODE
					if ((base_station).SecondBoardPresent && FIRST_BASE)
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
#endif
					CopyToUartTxBuffer((UByte *)"m register_main\r", 16);
					break;
				case GREETER_SETUP:
					if ((base_station).GreeterInstalled)
						CopyToUartTxBuffer((UByte *)"m greeter_setup:screen0\r", 24);
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
				case PIN:
				case NEW_PIN:
				case NEW_CLOCK:
				case GREETER_PIN:
				case NEW_NIGHT_TIME:
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
			if (h1 > 0)
				--h1;
			else
			{
				h1 = 2;
				if (h2 > 3)
					h2 = 3;
			}
			break;
		case 2:
			if (h2 > 0)
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
			if (m1 > 0)
				--m1;
			else
				m1 = 5;
			break;
		case 4:
			if (m2 > 0)
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
		if ((base_station).CurrentDay > 0)
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
		"    Promo 1     ",
		"    Promo 2     ",
		"    Promo 3     "
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

		OSStartTimer(GENERALFPTASKTIMER, 7); 				// 7 x 10ms = 70ms pause before sending next button info
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

//	CopyToUartTxBuffer((UByte *)"t \"btn = [", 10);
//	SendAsciiValue(selected_button);
//	SendAsciiValue((selected_greet * 5) + selected_button);
//	CopyToUartTxBuffer((UByte *)"]\" 150 150\r", 11);

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
		if (((base_station).MsgBeingEdited > 0) && (base_station).MessageIsPlaying)
		{
			RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);		// stops playing a message
			AFEDisablePostMicPath();												// disable DECT MIC input
		}
		else if (((base_station).MsgBeingEdited > 0) && (base_station).MessageIsRecording)
		{
			RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording a message
		}
		(base_station).MsgBeingEdited = 0;
		(base_station).Message[selected_greet].StartIsPressed = FALSE;
		(base_station).Message[selected_greet].StopIsPressed = FALSE;
	}
	else if (((base_station).MsgBeingEdited == 0) && Pressed)
	{
		// one of the edit buttons was pressed so mark this greet as being edited
		(base_station).MsgBeingEdited = selected_greet + 1;

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
//	else
//	{
//		CopyToUartTxBuffer((UByte *)"t \"ERROR: selected = [", 22);
//		SendAsciiValue(selected_greet + 1);
//		CopyToUartTxBuffer((UByte *)"]\" 100 200\r", 11);
//	}
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
		"    Promo 1     ",
		"    Promo 2     ",
		"    Promo 3     "
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

//	CopyToUartTxBuffer((UByte *)"t \"btn = [", 10);
//	SendAsciiValue(btn);
//	CopyToUartTxBuffer((UByte *)"]\" 150 150\r", 11);

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

		OSStartTimer(GENERALFPTASKTIMER, 7); 				// 7 x 10ms = 70ms pause before sending next button info
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

//	CopyToUartTxBuffer((UByte *)"t \"btn = [", 10);
//	SendAsciiValue(selected_button);
//	SendAsciiValue((selected_greet * 5) + selected_button);
//	CopyToUartTxBuffer((UByte *)"]\" 150 150\r", 11);

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
		if (((base_station).MsgBeingEdited > 0) && (base_station).MessageIsPlaying)
		{
			RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);		// stops playing a message
			AFEDisablePostMicPath();												// disable DECT MIC input
		}
		else if (((base_station).MsgBeingEdited > 0) && (base_station).MessageIsRecording)
		{
			RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording a message
		}
		(base_station).MsgBeingEdited = 0;
		(base_station).Message[selected_greet].StartIsPressed = FALSE;
		(base_station).Message[selected_greet].StopIsPressed = FALSE;
	}
	else if (((base_station).MsgBeingEdited == 0) && Pressed)
	{
		// one of the edit buttons was pressed so mark this greet as being edited
		(base_station).MsgBeingEdited = selected_greet + page + 1;

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

//	CopyToUartTxBuffer((UByte *)"t \"btn = [", 10);
//	SendAsciiValue(btn);
//	CopyToUartTxBuffer((UByte *)"]\" 150 150\r", 11);

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
	for (i = 0; i < 4; i++)
		(base_station).TempPin2[i] = 0x30;

	if ((base_station).PinDigitIndex < 4)
		(base_station).TempPin[(base_station).PinDigitIndex] = (base_station).DisplayCommandData[0] + 0x30;

	if ((base_station).PinDigitIndex > 2)
	{
		if (memcmp(&(base_station).TempPin, &(base_station).TempPin2, 4))
			for (i = 0; i < 4; i++)
				(base_station).GrtrMsgrAuthCode[i] = (base_station).TempPin[i];
		else
			for (i = 0; i < 4; i++)
				(base_station).GrtrMsgrAuthCode[i] = 0xFF;

		// save code to EEPROM
		(base_station).DisplayValueChanged = TRUE;
		CopyToUartTxBuffer((UByte *)"m main\r", 7);
	}

	(base_station).PinDigitIndex++;
}

void ServiceDisplay()
{
	// service the Display command that was sent
	int i;
	BOOLEAN PreviousDayTime;

//	char *ptr;
//	ptr = StringPrint(StatusString, "** ServiceDisplay(0x");
//	ptr = StrPrintHexByte(ptr, (base_station).DisplayCommand);
//	ptr = StringPrint(ptr, ") ** ");
//	PrintStatus(0, StatusString);

	StopTimer(DISPLAYTASKTIMER);
	OSStartTimer(DISPLAYTASKTIMER, 30000);				// re-start 5 minute timer

	switch ((base_station).DisplayCommand)
	{
	case 0x01:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x01\" 300 50\r", 21);
		if ((base_station).DisplayScreen == GREETER_SETUP ||
			(base_station).DisplayScreen == MESSAGE_SETUP1 ||
			(base_station).DisplayScreen == MESSAGE_SETUP2 ||
			(base_station).DisplayScreen == NEW_CLOCK)
		{
			CheckForActiveGreet();								// check if selected greet has changed
			CheckForActiveMessage();							// check if reminders or alarm selections have changed
			PlayQueuedMessage();								// start playing any queued reminders or alarm
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
#ifdef SECOND_BASE_CODE
			if ((base_station).SecondBoardPresent && FIRST_BASE)
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
#endif
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
		if ((base_station).DisplayScreen == GREETER_PIN)
			GreeterAuthorizationScreen();
		else
		PINScreen();
		break;
	case 0x07:
		(base_station).PinDigitIndex = 0;
		break;
	case 0x08:
		if ((base_station).NewSystemMode != 0)
			StopTimer(SYSTEMMODETASKTIMER);
		(base_station).NewSystemMode = (base_station).DisplayCommandData[0];
		OSStartTimer(SYSTEMMODETASKTIMER, 300);				// wait 3s before changing
		break;
	case 0x09:
		break;
	case 0x0A:
		(base_station).DisplayScreen = VOLUME;
		CopyToUartTxBuffer((UByte *)"m pre_volume", 12);															// send slider bar max values first
		CopyByteToUartTxBuffer(' ');	SendAsciiValue(10);															// i1 detect max
		CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoNear ? INBOUND_NEAR : INBOUND_FAR);		// i2 inbound max
		CopyByteToUartTxBuffer(' ');	SendAsciiValue(GRILL);														// i3 grill max
		CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoNear ? OUTBOUND_NEAR : OUTBOUND_FAR);	// i4 day max
		CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).AlangoNear ? OUTBOUND_NEAR : OUTBOUND_FAR);	// i5 night max
		CopyByteToUartTxBuffer('\r');																				// complete command string

		CopyToUartTxBuffer((UByte *)"m volume", 8);																	// start volume display with parameters
		CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);															// eA volume lanes info
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
//		else
//			PrintStatus(0, "No RTC present ");
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
//		CopyToUartTxBuffer((UByte *)"t \"case 0x0F\" 300 50\r", 21);
		HandleSettingDay((base_station).DisplayCommandData[0]);
		break;
	case 0x10:
		(base_station).DisplayScreen = MAIN;
		if ((base_station).RegistrationButtonPressed)
		{
			(base_station).RegistrationButtonPressed = FALSE;
			(base_station).RegistrationAllowed = FALSE;
#ifdef SECOND_BASE_CODE
			if ((base_station).SecondBoardPresent)
				SendPCMCommand(REGISTER_PP_ind + FALSE);
#endif
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
				(base_station).GrillShouldBeOn = FALSE;
			}
			else if (!OkToTurnMicOff || (base_station).VehicleDetectIsActive)
			{
				if ((base_station).P33UsedForGreetMux)
					GREET_IN_PP_OFF;												// enable BC5 audio path only (no GREET) is enabled to DECT MICP/N
				if ((base_station).MessageIsPlaying == 0)
					MENU_SPKR_AMP_ON;												// turn post speaker back on (enable BC5 audio path in to DECT MICP/N)
				if ((base_station).GrillSpeakerVolume > 0)
					GRILL_SPEAKER_ON;												// turn grill speaker back on
				(base_station).GrillShouldBeOn = TRUE;
				// TODO: CRP - convert usec_pause to use timer
				usec_pause(65535);
				usec_pause(65535);
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

		if ((base_station).DisplayValueChanged)
		{
			(base_station).DisplayValueChanged = FALSE;
			general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
		}

		PreviousDayTime = (base_station).DayTime;
		CheckNightVolumeTime();		// update sun/moon icon
		if ((base_station).DayTime != PreviousDayTime)
			RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);

		break;
	case 0x11:
		(base_station).DisplayScreen = VOLUME;
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
		if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4) != 0)
			(base_station).NighTimeInEffect = TRUE;
		else
			(base_station).NighTimeInEffect = FALSE;
		break;
	case 0x15:		// register headsets button pressed/released
		if ((base_station).DisplayCommandData[0] == 1)
		{
			(base_station).RegistrationButtonPressed = TRUE;
#ifdef SECOND_BASE_CODE
			if ((base_station).SecondBoardPresent)
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
#else
			if (fp_subscription_getNumberOfSubscriptions() >= MAX_Allowed_Users)
			{
				PrintStatus(0, "already full - no registrations allowed");
				(base_station).RegistrationAllowed = FALSE;
				CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);	// release Registration button
			}
#endif
			else
				(base_station).RegistrationAllowed = TRUE;
		}
		else
		{
			(base_station).RegistrationButtonPressed = FALSE;
			(base_station).RegistrationAllowed = FALSE;
#ifdef SECOND_BASE_CODE
			if ((base_station).SecondBoardPresent)
				SendPCMCommand(REGISTER_PP_ind + FALSE);
#endif
		}
		break;
	case 0x16:
		(base_station).DisplayScreen = NEW_PIN;
		(base_station).PinDigitIndex = 0;
		break;
	case 0x17:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x17\" 10 50\r", 20);
//		originally used for single screen greeter setup
		break;
	case 0x18:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x18\" 10 50\r", 20);
		if ((base_station).DisplayScreen == GREETER_SETUP)
			HandleGreetDisplay();
		else
			HandleMessageDisplay();
		break;
	case 0x19:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x19\" 10 50\r", 20);
		if ((base_station).VehicleDetectIsActive)									// ignore play/record while a car is present
		{
			if ((base_station).DisplayCommandData[0] == 1)
			{
				CopyToUartTxBuffer((UByte *)"ssb 43 0\r", 9);						// release play button
				CopyToUartTxBuffer((UByte *)"xe 43\r", 6);							// enable play button
				CopyToUartTxBuffer((UByte *)"xe 44\r", 6);							// enable record button
				CopyToUartTxBuffer((UByte *)"xd 45\r", 6);							// disable stop button
			}
			else if ((base_station).DisplayCommandData[0] == 2)
			{
				CopyToUartTxBuffer((UByte *)"ssb 44 0\r", 9);						// release record button
				CopyToUartTxBuffer((UByte *)"xe 43\r", 6);							// enable play button
				CopyToUartTxBuffer((UByte *)"xe 44\r", 6);							// enable record button
				CopyToUartTxBuffer((UByte *)"xd 45\r", 6);							// disable stop button
			}
		}
		else if ((base_station).DisplayCommandData[0] == 1)
		{
			MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
			GRILL_SPEAKER_OFF;														// mute grill speaker during playback
			(base_station).GrillShouldBeOn = FALSE;
			RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
			AFEEnablePostMicPath();													// enable DECT MIC input
			RunGreetClock(MESSAGE_PLAY_START, (base_station).MsgBeingEdited);		// sets up and starts playing a message
		}
		else if ((base_station).DisplayCommandData[0] == 2)
		{
			MENU_SPKR_AMP_OFF;														// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
			GRILL_SPEAKER_OFF;														// mute grill speaker during playback
			(base_station).GrillShouldBeOn = FALSE;
			RefreshOutboundVolume(3);												// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);							// temporarily set inbound for playback comfort
			RunGreetClock(MESSAGE_RECORD_START, (base_station).MsgBeingEdited);		// sets up and starts recording a message
		}
		else if ((base_station).MessageIsPlaying > 0)
		{
			RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);		// stops playing a message
			AFEDisablePostMicPath();												// disable DECT MIC input
		}
		else if ((base_station).MessageIsRecording > 0)
		{
			RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// stops recording a message
		}
		break;
	case 0x1A:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x1A\" 10 50\r", 20);
		if ((base_station).DisplayScreen == GREETER_SETUP)
			HandleGreetName((base_station).DisplayCommandData[0]);
		else
			HandleMessageName((base_station).DisplayCommandData[0]);
		break;
	case 0x1B:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x1B\" 10 50\r", 20);
//		PrintStatus(0, "case 0x1B HandleGreet/MessageTime()");
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
#ifdef SECOND_BASE_CODE
		if (FIRST_BASE && (base_station).SecondBoardPresent)
		{
			SendPCMCommand(REQUEST_POWER_ON_COUNT_ind);
			general_startTimer(-1, DISPLAY_WT_DEBUG_INFO, NULL, 0, 10);	// wait for count from second base before displaying screen
		}
		else
#endif
			WTInfoDebugScreen();
		break;
	case 0x41:
		if ((base_station).PowerOnCount)
		{
			(base_station).PowerOnCount = 0;
			general_startTimer(-1, WRITE_WT_DEBUG_EEPROM, NULL, 0, 5);	// write current value to EEPROM
		}
		WTInfoDebugScreen();
		break;
	case 0x42:
#ifdef SECOND_BASE_CODE
		if ((base_station).PowerOnCount2)
		{
			(base_station).PowerOnCount2 = 0;
			SendPCMCommand(REQUEST_POWER_ON_COUNT2_ind);
		}
#endif
		WTInfoDebugScreen();
		break;
	case 0x43:
		(base_station).DisplayScreen = GREETER_PIN;
		(base_station).PinDigitIndex = 0;
		CopyToUartTxBuffer((UByte *)"m pin\r", 6);
		break;
	case 0x44:
		switch ((base_station).DisplayCommandData[0])
		{
			case 0:
				ALANGO_PROFILE_0;						// BC5 PIO6 = LO (far settings)
				(base_station).AlangoNear = FALSE;
				(base_station).DisplayValueChanged = TRUE;
				break;
			case 1:
				if ((base_station).InboundVol > INBOUND_NEAR)
					AFESetGainPP2PPMixer(INBOUND_NEAR);
				if ((base_station).CurrentOutboundVolume > OUTBOUND_NEAR)
				{
					AFESetGainSpkrVolumeFP(OUTBOUND_NEAR);
					(base_station).CurrentOutboundVolume = OUTBOUND_NEAR;
				}
				if ((base_station).PostSpeakerVolumeDay > OUTBOUND_NEAR)
					(base_station).PostSpeakerVolumeDay = OUTBOUND_NEAR;
				if ((base_station).PostSpeakerVolumeNight > OUTBOUND_NEAR)
					(base_station).PostSpeakerVolumeNight = OUTBOUND_NEAR;
				ALANGO_PROFILE_1;						// BC5 PIO6 = HI (near settings)
				(base_station).AlangoNear = TRUE;
				(base_station).DisplayValueChanged = TRUE;
				break;
			case 2:
				CopyToUartTxBuffer((UByte *)"touch off\r", 10);
				StopTimer(WATCHDOGTASKTIMER);
				break;
			case 3:
				// Alert Input button press executes here
				(base_station).UsingP34ForAlarm = FALSE;
				(base_station).DisplayValueChanged = TRUE;
				break;
			case 4:
				// Alert Input button release executes here
				(base_station).UsingP34ForAlarm = TRUE;
				(base_station).DisplayValueChanged = TRUE;
				break;
			case 5:
				// BC5 on/off button press here
				(base_station).BC5Bypassed = TRUE;
				// send BC5 OFF to PPs
				BroadcastSystemModeState(-1);
				break;
			case 6:
				// BC5 on/off button release here
				(base_station).BC5Bypassed = FALSE;
				// send BC5 ON to PPs
				BroadcastSystemModeState(-1);
				break;
			case 7:
				// GREET in headset NO/YES button press here
				// play greet in headset
				(base_station).PlayGreetInPP = TRUE;
				(base_station).DisplayValueChanged = TRUE;
				break;
			case 8:
				// GREET in headset NO/YES button release here
				// do NOT play greet in headset
				(base_station).PlayGreetInPP = FALSE;
				(base_station).DisplayValueChanged = TRUE;
				break;
			default:
				PrintStatus(0, "unknown command request");
				break;
		}
		break;
	case 0x50:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x50\" 10 50\r", 20);
		(base_station).DisplayScreen = GREETER_SETUP;
		(base_station).MsgDayBeingEdited = MONDAY;
		(base_station).MsgBeingEdited = 0;
		(base_station).MsgCounter = 0;
		(base_station).FillingMsgDisplay = TRUE;
		MENU_SPKR_AMP_OFF;															// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		GRILL_SPEAKER_OFF;															// mute grill speaker during playback
		(base_station).GrillShouldBeOn = FALSE;
		RefreshOutboundVolume(3);													// temporarily "normalize" for recording level
		AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);								// temporarily set inbound for playback comfort
		OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 				// 35 x 10ms = 210ms pause before beginning to send button info
		break;
	case 0x51:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x51\" 10 50\r", 20);
		(base_station).DisplayScreen = MESSAGE_SETUP1;
		(base_station).MsgDayBeingEdited = MONDAY;
		(base_station).MsgBeingEdited = 0;
		(base_station).MsgCounter = 7;
		(base_station).FillingMsgDisplay = TRUE;
		MENU_SPKR_AMP_OFF;															// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		GRILL_SPEAKER_OFF;															// mute grill speaker during playback
		(base_station).GrillShouldBeOn = FALSE;
		RefreshOutboundVolume(3);													// temporarily "normalize" for recording level
		AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);								// temporarily set inbound for playback comfort
		OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 				// 35 x 10ms = 210ms pause before beginning to send button info
		break;
	case 0x52:
//		CopyToUartTxBuffer((UByte *)"t \"case 0x52\" 10 50\r", 20);
		(base_station).DisplayScreen = MESSAGE_SETUP2;
		(base_station).MsgDayBeingEdited = MONDAY;
		(base_station).MsgBeingEdited = 0;
		(base_station).MsgCounter = 14;
		(base_station).FillingMsgDisplay = TRUE;
		MENU_SPKR_AMP_OFF;															// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		GRILL_SPEAKER_OFF;															// mute grill speaker during playback
		(base_station).GrillShouldBeOn = FALSE;
		RefreshOutboundVolume(3);													// temporarily "normalize" for recording level
		AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);								// temporarily set inbound for playback comfort
		OSStartTimer(GENERALFPTASKTIMER, GREETER_DISPLAY_SETUP_DELAY); 				// 35 x 10ms = 210ms pause before beginning to send button info
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
