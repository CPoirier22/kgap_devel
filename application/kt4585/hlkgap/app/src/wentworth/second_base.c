/********************************************************************************
 * 																				*
 *		Wentworth Technology Inc												*
 *		77 Industrial Park Road, Unit 201										*
 *		Saco, Maine, USA 04072													*
 *		+1 207-571-9744															*
 *		www.wentworthtechnology.com												*
 *		copyright 2012															*
 *																				*
 ********************************************************************************
 * $History:: second_base.c													  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */

#include "../../../../../../include/os/include/mailprim.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/common/common_general_functions.h"

#include "../dsp/gdsp_all_inits.h"
#include "wentworth_fp.h"
#include "fppp_common.h"

#ifdef SECOND_BASE_CODE

extern void ConnectPCM(void);
extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN);
extern void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length);
extern void ServiceVehicleDetect(BOOLEAN VehicleIsPresent, BOOLEAN GreetPlaying);
extern void BroadcastOrderTaker(PPIDType user, unsigned char value);
extern void BroadcastSystemModeState(PPIDType user);
extern UByte msf_send_broadcast(UByte *data, UByte length, UByte repetitions);
extern void BroadcastCarWaiting(unsigned char value);
extern UByte fp_subscription_removeSubscription(PPIDType user);

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)	{ ; }
}

/*
 * issues commands between main base board and second base board
 *
 */
void SendPCMCommand(WORD cmd)
{
//	char *ptr;
//	ptr = StringPrint(StatusString, "SendPCMCommand(0x");
//	ptr = StrPrintHexWord(ptr, cmd);
//	ptr = StringPrint(ptr, ") ");
//	PrintStatus(0, StatusString);

	p_gendsp_pcm_command_out->value = cmd;
	usec_pause(4000);
	p_gendsp_pcm_command_out->value = 0x0000;
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
	char *ptr;
//	ptr = StringPrint(StatusString, "ServicePCMCommand(0x");
//	ptr = StrPrintHexWord(ptr, cmd);
//	ptr = StringPrint(ptr, ") ");
//	PrintStatus(0, StatusString);
	WWMSF WWMSFVal;
	switch (cmd & 0xFF00)
	{
		case SECOND_BOARD_ind:
			(base_station).SecondBoardPresent = TRUE;
			ConnectPCM();		// connect the PCM[0] bus audio to the mixers
		case 0xA100:
		case 0xA200:
		case 0xA300:
		case 0xA400:
			(base_station).FP2_ARI[(cmd & 0x0F00) >> 8] = (cmd & 0x00FF);
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
				if ((base_station).DisplayScreen == REGISTRATION)
				{
					UByte buffer[50];
					int count;
					IPEIType Ipei;
					char SN[17];

//					// if the database is marked empty and it's on or the database is marked present but it's off, refresh the database to be sure
//					if  ((base_station).QuickDataBoard2[user - MAX_Allowed_Users].EmptyMarker && (cmd & 0x000F))
//					{
//						for (i = 0; i < MAX_Allowed_Users; i++)
//						{
//							(base_station).QuickDataBoard2[i].EmptyMarker = 1;
//							(base_station).QuickDataBoard2[i].Upi[0] = 0xFF;
//							(base_station).QuickDataBoard2[i].Upi[1] = 0xFF;
//							(base_station).QuickDataBoard2[i].Upi[2] = 0xFF;
//							(base_station).QuickDataBoard2[i].Upi[3] = 0xFF;
//						}
//						SendPCMCommand(REQUEST_PP_SN_ind);
//						// TODO: CRP - convert usec_pause to use timer
//						usec_pause(40000);
//					}

					ptr = StringPrint(StatusString, "QuickData[0]=(");
					ptr = StrPrintHexByte(ptr, (base_station).QuickDataBoard2[0].EmptyMarker);
					ptr = StringPrint(ptr, ", ");
					ptr = StrPrintHexByte(ptr, (base_station).QuickDataBoard2[0].Upi[0]);
					ptr = StringPrint(ptr, ", ");
					ptr = StrPrintHexByte(ptr, (base_station).QuickDataBoard2[0].Upi[1]);
					ptr = StringPrint(ptr, ", ");
					ptr = StrPrintHexByte(ptr, (base_station).QuickDataBoard2[0].Upi[2]);
					ptr = StringPrint(ptr, ", ");
					ptr = StrPrintHexByte(ptr, (base_station).QuickDataBoard2[0].Upi[3]);
					ptr = StringPrint(ptr, ") ");
					PrintStatus(0, StatusString);


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
				}
			}
			break;
		case VEHICLE_DET_ind:
			ServiceVehicleDetect(cmd & 0x000F, (cmd & 0x00F0) >> 4);
			break;
		case PP_MIC_ind:
			WWMSFVal.SubStatusType = MIC_MUTE_CMD;
			WWMSFVal.Sub.SetMicMute.MicMute = (cmd & 0x000F);
			HandlePacketFromPP((((cmd & 0x00F0) >> 4) + MAX_Allowed_Users_Dual), (UByte *)&WWMSFVal, sizeof(WWMSFVal));
			break;
		case ORDER_TAKER_ind:
      		if (((cmd & 0x00FF) != 0x00FF) && ((cmd & 0x00FF) >= MAX_Allowed_Users_Dual))
      			BroadcastOrderTaker(((cmd & 0x00FF) - MAX_Allowed_Users_Dual), 1);
      		else if (((cmd & 0x00FF) == 0x00FF) && ((base_station).OrderTakerID >= MAX_Allowed_Users_Dual))
      			BroadcastOrderTaker(((base_station).OrderTakerID - MAX_Allowed_Users_Dual), 0);
			(base_station).OrderTakerID = (cmd & 0x00FF);
			break;
		case SYSTEM_MODE_ind:
			(base_station).InboundVol = (cmd & 0x00F0) >> 4;
			(base_station).SystemMode = (cmd & 0x000F);
			BroadcastSystemModeState(-1);
			general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
			break;
		case BLINK_LED_ind:
			WWMSFVal.SubStatusType = BLINK_LED_CMD;
			WWMSFVal.Sub.SetLEDColor.LEDColor = (cmd & 0x00FF);
			msf_send_broadcast((UByte *)&WWMSFVal, sizeof(WWMSFVal), 0);
			break;
		case CAR_WAITING_ind:
			BroadcastCarWaiting(cmd & 0x00FF);
			break;
		case REGISTER_PP_ind:
			(base_station).RegistrationAllowed = (cmd & 0x000F);
			break;
		case DELETE_PP_ind:
			fp_subscription_removeSubscription(cmd & 0x000F);
			break;
		case LISTEN_ONLY_PP_ind:
			ptr = StringPrint(StatusString, "LISTEN_ONLY_PP_ind:0x");
			ptr = StrPrintHexByte(ptr, (cmd & 0x00FF));
			PrintStatus(0, StatusString);
			(base_station).ListenOnly[(cmd & 0x00F0) >> 4] = (cmd & 0x000F);
			general_startTimer(((cmd & 0x00F0) >> 4), LISTEN_ONLY_MODE_CMD, NULL, 0, 1);
			break;
		case REQUEST_POWER_ON_COUNT_ind:
			if (FIRST_BASE)
				(base_station).PowerOnCount2 = (cmd & 0x00FF) << 8;
			else
			{
				SendPCMCommand(REQUEST_POWER_ON_COUNT_ind  + ((base_station).PowerOnCount >> 8));
				SendPCMCommand(REQUEST_POWER_ON_COUNT2_ind + ((base_station).PowerOnCount & 0x00FF));
			}
			break;
		case REQUEST_POWER_ON_COUNT2_ind:
			if (FIRST_BASE)
				(base_station).PowerOnCount2 += cmd & 0x00FF;
			else
			{
				(base_station).PowerOnCount = 0;
				general_startTimer(-1, WRITE_WT_DEBUG_EEPROM, NULL, 0, 5);	// write current value to EEPROM
			}
			break;
			//////////////////////////////////////////////////////
		case 0xF500:
			ptr = StringPrint(StatusString, "WT_INFO_ind:0x");
			ptr = StrPrintHexByte(ptr, (cmd & 0x00FF));
			PrintStatus(0, StatusString);
			break;
		default:
			ptr = StringPrint(StatusString, "**** PCM cmd not handled !!! ==> cmd = 0x");
			ptr = StrPrintHexWord(ptr, (cmd));
			PrintStatus(0, StatusString);
			break;
	}
}
#endif
