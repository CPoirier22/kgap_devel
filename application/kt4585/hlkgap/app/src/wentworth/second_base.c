/********************************************************************************
 * 																				*
 *		Wentworth Technology Inc												*
 *		77 Industrial Park Road, Unit 201										*
 *		Saco, Maine, USA 04072													*
 *		+1 207-571-9744															*
 *		www.wentworthtechnology.com												*
 *		copyright 2015															*
 *																				*
 ********************************************************************************
 * $History:: second_base.c													  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */

#include "../../../../../../include/os/include/os_timer.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/common/common_general_functions.h"
#include "../dsp/gdsp_all_inits.h"
#include "wentworth_fp.h"
#include "fppp_common.h"

extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void CopyByteToUartTxBuffer(UByte buffer);
extern void ConvertHexSNtoAriSN(IPEIType Hex_SN, char SerialNumber[11]);
extern void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN);
extern void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length);
extern void BroadcastOrderTaker(PPIDType user, unsigned char value);
extern void BroadcastSystemModeState(PPIDType user);
extern void BroadcastBlinkLED(unsigned char value);
extern void BroadcastCarWaiting(unsigned char value);
extern UByte fp_subscription_removeSubscription(PPIDType user);
extern void VolumeAdjustScreen();
extern void ServiceDisplay();

extern UByte WATCHDOGTASKTIMER;

static void usec_pause(DWORD x)							// -2,147,483,648 to 2,147,483,647
{
    volatile DWORD i;
    for (i = 0; i < x; i++) { ; }
}

/*
 * issues commands between main base board and second base board
 *
 */
void SendPCMCommand(WORD cmd)
{
//CopyToUartTxBuffer((UByte *)"TxPCM\r", 6);				// "cheat" debug msg
char *ptr;
ptr = StringPrint(StatusString, "SendPCMCommand(0x");
ptr = StrPrintHexWord(ptr, cmd);
ptr = StringPrint(ptr, ") ");
PrintStatus(0, StatusString);

	p_gendsp_pcm_command_out->value = cmd;
	usec_pause(2000);
	p_gendsp_pcm_command_out->value = 0x0000;
	usec_pause(2000);
}

/*
 * sends the QuickData from 2nd base to 1st base for use in registration screen
 * the format is 0x1nyy
 *  n == PP number 0-4 (MAX_Allowed_Users_Dual)
 * yy == byte of data
 *
 */
void SendQuickData(void)
{
	int i = 0, ii = 4;
	while (i < MAX_Allowed_Users_Dual)
	{
		if (ii == 4)
		{
			ii = 0;
			SendPCMCommand(0x1000 + (i << 8) + QuickData[i].EmptyMarker);
			if (QuickData[i].EmptyMarker == 0xFF)
				ii = 4;
		}
		else
			SendPCMCommand(0x1000 + (i << 8) + QuickData[i].Upi[ii++]);
		if (ii == 4)
			i++;
	}
}

/*
 * responds to requests between main base board and second base board
 *
 */
void ServicePCMCommand(WORD cmd)
{
//CopyToUartTxBuffer((UByte *)"RxPCM\r", 6);				// "cheat" debug msg
char *ptr;
ptr = StringPrint(StatusString, "ServicePCMCommand(0x");
ptr = StrPrintHexWord(ptr, cmd);
ptr = StringPrint(ptr, ") ");
PrintStatus(0, StatusString);
	int i;
	WWMSF WWMSFVal;

	if ((base_station).ReceivingGreetData)
	{
		if (cmd == GREETER_DATA_STOP_ind)
		{
			(base_station).ReceivingGreetData = FALSE;
			 if (!FIRST_BASE)
				 general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
		}
		else
		{
			if ((cmd & 0xFF00) == 0xFF00)
				(base_station).Message[(base_station).GreetData_i].MessageEnableName = cmd & 0x00FF;
			else
			{
				(base_station).Message[(base_station).GreetData_i].StartTime[(base_station).GreetData_ii] = (cmd & 0xFF00) >> 8;
				(base_station).Message[(base_station).GreetData_i].StopTime[(base_station).GreetData_ii++] = cmd & 0x00FF;
				if ((base_station).GreetData_ii > 3)
				{
					if (++(base_station).GreetData_i < NUM_OF_MESSAGES)
						(base_station).GreetData_ii = 0;
				}
			}
		}
	}
	else if (cmd == GREETER_DATA_START_ind)
	{
		(base_station).GreetData_i = 0;
		(base_station).GreetData_ii = 0;
		(base_station).ReceivingGreetData = TRUE;
		if (FIRST_BASE)
			(base_station).GreeterInstalledB = 1;
	}
	else switch (cmd & 0xFF00)
	{
		case SECOND_BOARD_ind:
		case 0xA100:
		case 0xA200:
		case 0xA300:
		case 0xA400:
			(base_station).FP2_ARI[(cmd & 0x0F00) >> 8] = (cmd & 0x00FF);
			if (FIRST_BASE && ((cmd & 0xFF00) == 0xA100))
				SendPCMCommand(SYSTEM_MODE_ind + ((base_station).BC5Bypassed << 4) + (base_station).SystemMode);
			if ((cmd & 0xFF00) == 0xA400)
			{
				(base_station).ARI2_Received = TRUE;
				ConvertHexSNtoAriSN((base_station).FP2_ARI, (base_station).SerialNumber2);
			}
			break;
		case REQ_FP_ARI_ind:
			// other base is looking for this base's ARI
			SendPCMCommand(SECOND_BOARD_ind + (0 << 8) + (base_station).FP_ARI[0]);
			SendPCMCommand(SECOND_BOARD_ind + (1 << 8) + (base_station).FP_ARI[1]);
			SendPCMCommand(SECOND_BOARD_ind + (2 << 8) + (base_station).FP_ARI[2]);
			SendPCMCommand(SECOND_BOARD_ind + (3 << 8) + (base_station).FP_ARI[3]);
			SendPCMCommand(SECOND_BOARD_ind + (4 << 8) + (base_station).FP_ARI[4]);
			// refresh HeadsetIsOn[] array on other base
			for (i = 0; i < MAX_Allowed_Users_Dual; i++)
				SendPCMCommand(PP_ON_ind + (i << 4) + (base_station).HeadsetIsOn[i]);
			break;
		case REQUEST_PP_SN_ind:
			SendQuickData();
			break;
		case 0x1000:
		case 0x1100:
		case 0x1200:
		case 0x1300:
		case 0x1400:
			if ((base_station).QuickDataIndex == 0)
			{
				(base_station).QuickDataBoard2[(cmd & 0x0F00) >> 8].EmptyMarker = (cmd & 0x00FF);
				if ((cmd & 0x0FF) != 0xFF)
					(base_station).QuickDataIndex++;
			}
			else
				(base_station).QuickDataBoard2[(cmd & 0x0F00) >> 8].Upi[((base_station).QuickDataIndex++) - 1] = (cmd & 0x00FF);
			if ((base_station).QuickDataIndex > 4)
				(base_station).QuickDataIndex = 0;
			break;
		case PP_ON_ind:
			{
				int user = ((cmd & 0x00F0) >> 4) + MAX_Allowed_Users_Dual;
				(base_station).HeadsetIsOn[user] = (cmd & 0x000F);
				if (FIRST_BASE && ((base_station).DisplayScreen == REGISTRATION) && !(base_station).QuickDataBoard2[user - MAX_Allowed_Users_Dual].EmptyMarker)
				{
					UByte buffer[50];
					int count;
					IPEIType Ipei;
					char SN[17];

					CopyToUartTxBuffer((UByte *)"*abt\r", 5);
					CopyToUartTxBuffer((UByte *)"f 18BC\r", 7);
					Ipei[0] = 0x01;						// hard coding 0x01 for 1st byte
					memcpy(&Ipei[1], (base_station).QuickDataBoard2[user - MAX_Allowed_Users_Dual].Upi, 4);
					ConvertIpeiToSN(user, SN, Ipei);
					if ((base_station).HeadsetIsOn[user])
					{
						memcpy(&buffer[0], "m register_box:lbl_1_", 21);
						count = 21;
					}
					else
					{
						memcpy(&buffer[0], "m register_box:lbl_0_", 21);
						count = 21;
					}
					count += GetAsciiValue(&buffer[0], (user + 40), count);
					memcpy(&buffer[0] + count, " \"", 2);
					count += 2;
					if ((base_station).HeadsetIsOn[user])
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
					CopyToUartTxBuffer(&buffer[0], count);
				}
				if (!(base_station).HeadsetIsOn[user])
				{
					WWMSFVal.SubStatusType = MIC_MUTE_CMD;
					WWMSFVal.Sub.SetMicMute.MicMute = 1;
					HandlePacketFromPP(user, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
					if (user == (base_station).OrderTakerID)
						(base_station).OrderTakerID = 0xFF;
				}
			}
			break;
		case VEHICLE_DET_ind:
			//	0x1C00	// car not present at menu B
			//	0x1C01	// car present at menu B
			if ((base_station).DisplayScreen == MAIN)
				CopyToUartTxBuffer((UByte *)"m lane_2:lbl_", 13);
			else
				CopyToUartTxBuffer((UByte *)"set e3 ", 7);
			SendAsciiValue((cmd & 0x0001) + 1);
			CopyByteToUartTxBuffer('\r');
			break;
		case PP_MIC_ind:
			WWMSFVal.SubStatusType = MIC_MUTE_CMD;
			WWMSFVal.Sub.SetMicMute.MicMute = (cmd & 0x000F);
			HandlePacketFromPP((((cmd & 0x00F0) >> 4) + MAX_Allowed_Users_Dual), (UByte *)&WWMSFVal, sizeof(WWMSFVal));
			break;
		case ORDER_TAKER_ind:
			// assign or cancel an OT headset from the other menu that is registered to this base
			BroadcastOrderTaker(((cmd & 0x000F) - MAX_Allowed_Users_Dual), ((cmd & 0x0010) >> 4));
			break;
		case SYSTEM_MODE_ind:
			(base_station).BC5Bypassed = (cmd & 0x00F0) >> 4;
			(base_station).SystemMode = cmd & 0x000F;
			// re-send system mode in case it switched to single menu or toggled BC5 noise canceling
			BroadcastSystemModeState(-1);
			general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);		// write current values to EEPROM
			break;
		case BLINK_LED_ind:
			BroadcastBlinkLED(cmd & 0x00FF);
			break;
		case CAR_WAITING_ind:
			BroadcastCarWaiting(cmd & 0x00FF);
			break;
		case REGISTER_PP_ind:
			if (!FIRST_BASE)
				(base_station).RegistrationAllowed = (cmd & 0x000F);
			break;
		case DELETE_PP_ind:
			fp_subscription_removeSubscription(cmd & 0x000F);
			break;
		case LISTEN_ONLY_PP_ind:
			if ((cmd & 0x000F) == 1)
				(base_station).ListenOnly[(cmd & 0x00F0) >> 4] = 0x01;
			else
				(base_station).ListenOnly[(cmd & 0x00F0) >> 4] = 0xFF;
			general_startTimer(((cmd & 0x00F0) >> 4), LISTEN_ONLY_MODE_CMD, NULL, 0, 1);
			break;
		case REQUEST_PUP_MSB_B_ind:
			if (FIRST_BASE)
				(base_station).PowerOnCountB = ((base_station).PowerOnCountB & 0x00FF) + ((cmd & 0x00FF) << 8);
			else
				SendPCMCommand(REQUEST_PUP_MSB_B_ind  + ((base_station).PowerOnCount >> 8));
			break;
		case REQUEST_PUP_LSB_B_ind:
			if (FIRST_BASE)
				(base_station).PowerOnCountB = ((base_station).PowerOnCountB & 0xFF00) + (cmd & 0x00FF);
			else
				SendPCMCommand(REQUEST_PUP_LSB_B_ind  + ((base_station).PowerOnCount & 0x00FF));
			break;
		case RESET_PUP_B_ind:
			(base_station).PowerOnCount = 0;
			general_startTimer(-1, WRITE_WT_DEBUG_EEPROM, NULL, 0, 5);	// write current value to EEPROM
			break;
		case PAGE_CMD_ind:
			WWMSFVal.SubStatusType = PAGE_CMD;
			WWMSFVal.Sub.SetPage.Page = (cmd & 0x000F);
			HandlePacketFromPP((((cmd & 0x00F0) >> 4) + MAX_Allowed_Users_Dual), (UByte *)&WWMSFVal, sizeof(WWMSFVal));
			break;
		case VOLUME_SETTINGS_B_ind:
			switch (cmd & 0x00F0)
			{
				case 0x10:
				case 0x20:
				case 0x30:
				case 0x40:
					if (!FIRST_BASE)
					{
						(base_station).DisplayCommandData[0] = ((cmd & 0x00F0) >> 4);		// which volume control: 1-inbound, 2-grill, 3-day, 4-night
						(base_station).DisplayCommandData[1] = (cmd & 0x000F);				// volume requested
						VolumeAdjustScreen();
					}
					else
					{
						if ((base_station).DisplayScreen == VOLUME_B)
						{
							CopyToUartTxBuffer((UByte *)"m set_volume ", 13);
							SendAsciiValue((cmd & 0x00F0) >> 4);
							CopyByteToUartTxBuffer(' ');
							SendAsciiValue(cmd & 0x000F);
							CopyByteToUartTxBuffer('\r');
						}
						switch (cmd & 0x00F0)
						{
							case 0x10:
								(base_station).InboundVolB = (UByte)(cmd & 0x000F);
								break;
							case 0x20:
								(base_station).GrillSpeakerVolumeB = (UByte)(cmd & 0x000F);
								break;
							case 0x30:
								(base_station).PostSpeakerVolumeDayB = (UByte)(cmd & 0x000F);
								break;
							case 0x40:
								(base_station).PostSpeakerVolumeNightB = (UByte)(cmd & 0x000F);
								break;
						}
					}
					break;
				case 0xB0:
					(base_station).InboundVolB = (UByte)(cmd & 0x000F);
					break;
				case 0xC0:
					(base_station).GrillSpeakerVolumeB = (UByte)(cmd & 0x000F);
					break;
				case 0xD0:
					(base_station).PostSpeakerVolumeDayB = (UByte)(cmd & 0x000F);
					break;
				case 0xE0:
					(base_station).PostSpeakerVolumeNightB = (UByte)(cmd & 0x000F);
					break;
				case 0xF0:
					(base_station).AlangoProfile1B = (UByte)(cmd & 0x000F);
					break;
			}
			break;
		case UPDATE_CLOCK_B_ind:
			switch (cmd & 0x00F0)
			{
				case 0x10:
					(base_station).DisplayTime.timeHourMSB = cmd & 0x000F;
					break;
				case 0x20:
					(base_station).DisplayTime.timeHourLSB = cmd & 0x000F;
					break;
				case 0x30:
					(base_station).DisplayTime.timeMinMSB = cmd & 0x000F;
					break;
				case 0x40:
					(base_station).DisplayTime.timeMinLSB = cmd & 0x000F;
					break;
				case 0x50:
					(base_station).CurrentDay = cmd & 0x000F;
					(base_station).DisplayCommand = 0x0B;
					(base_station).DisplayCommandData[0] = (base_station).DisplayTime.timeHourMSB;
					(base_station).DisplayCommandData[1] = (base_station).DisplayTime.timeHourLSB;
					(base_station).DisplayCommandData[2] = (base_station).DisplayTime.timeMinMSB;
					(base_station).DisplayCommandData[3] = (base_station).DisplayTime.timeMinLSB;
					ServiceDisplay();
					break;
			}
			break;
		case UPDATE_NITE_START_B_ind:
			switch (cmd & 0x00F0)
			{
				case 0x10:
					(base_station).NightVolumeTimeStart.timeHourMSB = cmd & 0x000F;
					break;
				case 0x20:
					(base_station).NightVolumeTimeStart.timeHourLSB = cmd & 0x000F;
					break;
				case 0x30:
					(base_station).NightVolumeTimeStart.timeMinMSB = cmd & 0x000F;
					break;
				case 0x40:
					(base_station).NightVolumeTimeStart.timeMinLSB = cmd & 0x000F;
					(base_station).DisplayCommand = 0x13;
					(base_station).DisplayCommandData[0] = (base_station).NightVolumeTimeStart.timeHourMSB;
					(base_station).DisplayCommandData[1] = (base_station).NightVolumeTimeStart.timeHourLSB;
					(base_station).DisplayCommandData[2] = (base_station).NightVolumeTimeStart.timeMinMSB;
					(base_station).DisplayCommandData[3] = (base_station).NightVolumeTimeStart.timeMinLSB;
					ServiceDisplay();
					general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);		// write current values to EEPROM
					break;
			}
			break;
		case UPDATE_NITE_STOP_B_ind:
			switch (cmd & 0x00F0)
			{
				case 0x10:
					(base_station).NightVolumeTimeEnd.timeHourMSB = cmd & 0x000F;
					break;
				case 0x20:
					(base_station).NightVolumeTimeEnd.timeHourLSB = cmd & 0x000F;
					break;
				case 0x30:
					(base_station).NightVolumeTimeEnd.timeMinMSB = cmd & 0x000F;
					break;
				case 0x40:
					(base_station).NightVolumeTimeEnd.timeMinLSB = cmd & 0x000F;
					(base_station).DisplayCommand = 0x14;
					(base_station).DisplayCommandData[0] = (base_station).NightVolumeTimeEnd.timeHourMSB;
					(base_station).DisplayCommandData[1] = (base_station).NightVolumeTimeEnd.timeHourLSB;
					(base_station).DisplayCommandData[2] = (base_station).NightVolumeTimeEnd.timeMinMSB;
					(base_station).DisplayCommandData[3] = (base_station).NightVolumeTimeEnd.timeMinLSB;
					ServiceDisplay();
					general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);		// write current values to EEPROM
					break;
			}
			break;
		case UPDATE_MENU_CFG_B_ind:
			(base_station).MenuConfig = cmd & 0x000F;
			CopyToUartTxBuffer((UByte *)"set eA ", 7);								// update volume config setting: menu A or B
			SendAsciiValue((base_station).MenuConfig > 1 ? (base_station).DualBase : 0);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"set e3 ", 7);								// update menu B config setting
			SendAsciiValue((base_station).MenuConfig > 1 ? 1 : 0);
			CopyByteToUartTxBuffer('\r');
			CopyToUartTxBuffer((UByte *)"set eB ", 7);								// update lane config setting
			SendAsciiValue((base_station).MenuConfig);
			CopyByteToUartTxBuffer('\r');
			if ((base_station).SystemMode == AUTO_HANDS_FREE)
			{
				(base_station).SystemMode = HANDS_FREE;
				CopyToUartTxBuffer((UByte *)"set e1 ", 7);
				SendAsciiValue((base_station).SystemMode - 1);
				CopyByteToUartTxBuffer('\r');
			}
			break;
		case UPDATE_ALANGO_CFG_B_ind:
			(base_station).DisplayCommand = 0x43;
			(base_station).DisplayCommandData[0] = cmd & 0x000F;
			ServiceDisplay();
			break;
		case STOP_WATCHDOG_B_ind:
			StopTimer(WATCHDOGTASKTIMER);
			break;
		case GREETER_REQ_ind:
			if (!FIRST_BASE)
			{
				if ((base_station).VehicleDetectIsActive)
					SendPCMCommand(GREETER_REQ_ind + 0x02);			// tell the first base VD is active
				else if (!(base_station).GreeterInstalled)
					SendPCMCommand(GREETER_REQ_ind + 0x00);			// tell the first base there is no greeter
				else
				{
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
					SendPCMCommand(GREETER_REQ_ind + 0x01);			// tell the first base to start displaying greeter screen
				}
			}
			else if (FIRST_BASE)
			{
				if ((cmd & 0x00FF) == 0x02)
				{
					// menu B VD active; returned to main screen
					CopyToUartTxBuffer((UByte *)"m main\r", 7);
				}
				else if ((cmd & 0x00FF) == 0x00)
				{
					// menu B greeter not installed; show promo screen
					(base_station).GreeterInstalledB = 0;
					CopyToUartTxBuffer((UByte *)"m show_greeter_promo\r", 21);
				}
				else if ((cmd & 0x00FF) == 0x01)
				{
					// menu B greeter ok to display
					(base_station).GreeterScreenB = TRUE;
					CopyToUartTxBuffer((UByte *)"m greeter_setup:screen0\r", 24);
				}
			}
			break;
		case GREETER_0x19_ind:
			if (!FIRST_BASE)
			{
				(base_station).DisplayCommand = 0x19;
				(base_station).DisplayCommandData[0] = cmd & 0x000F;
				ServiceDisplay();
			}
			// else handle VD active from second base
			else if (((cmd & 0x00F0) == 0x10) && ((base_station).GreeterScreenB))
			{
				CopyToUartTxBuffer((UByte *)"ssb 43 0\r", 9);					// release play button
				CopyToUartTxBuffer((UByte *)"xe 43\r", 6);						// enable play button
				CopyToUartTxBuffer((UByte *)"xe 44\r", 6);						// enable record button
				CopyToUartTxBuffer((UByte *)"xd 45\r", 6);						// disable stop button
			}
			else if (((cmd & 0x00F0) == 0x20) && ((base_station).GreeterScreenB))
			{
				CopyToUartTxBuffer((UByte *)"ssb 44 0\r", 9);					// release record button
				CopyToUartTxBuffer((UByte *)"xe 43\r", 6);						// enable play button
				CopyToUartTxBuffer((UByte *)"xe 44\r", 6);						// enable record button
				CopyToUartTxBuffer((UByte *)"xd 45\r", 6);						// disable stop button
			}
			else
				PrintStatus(0, "GREETER_0x19_ind CMD ignored");
			break;
		case GREETER_B_ACTIVE_ind:
			if (cmd & 0x00F0)
				(base_station).GreeterActive = cmd & 0x000F;									// update GREETER B active status
			else
				SendPCMCommand(GREETER_B_ACTIVE_ind + 0x10 + (base_station).GreeterActive);		// report GREETER B active status
			break;
		case GREETER_B_MSG_ind:
			(base_station).MsgBeingEdited = cmd & 0x00FF;
			break;
		case GREETER_B_AUTH_ind:
			(base_station).GrtrMsgrAuthCode[(cmd & 0x00F0) >> 4] = (cmd & 0x000F) + 0x30;
			if ((cmd & 0x00F0) == 0x30)
				general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);		// write current values to EEPROM
			break;
			//////////////////////////////////////////////////////
		default:
			ptr = StringPrint(StatusString, "**** PCM cmd not handled !!! ==> cmd = 0x");
			ptr = StrPrintHexWord(ptr, (cmd));
			PrintStatus(0, StatusString);
			break;
	}
}
