#include "../../../../api/include/fp/fp_api.h"
#include "../../../../api/include/fp/fp_voice_callback.h"
#include "../../../../api/include/fp/fp_voice_functions.h"
#include "../../../../api/include/fp/fp_msf_callback.h"
#include "../../../../api/include/fp/fp_msf_functions.h"
#include "../../../../api/include/fp/fp_module2module_callback.h"
#include "../../../../api/include/fp/fp_module2module_functions.h"
#include "../../../../api/include/common/common_general_callback.h"
#include "../../../../api/include/common/common_general_functions.h"
#include "../../../../api/include/common/common_hardware_callback.h"
#include "../../../../api/include/common/common_hardware_functions.h"
#include "../../../../include/eeplayout.h"
#include "../../../../../include/hlkgap/iwu/include/fp/fiwuprim.h"
#include "../../../../../include/os/include/mailprim.h"
#include "../../../../../include/os/include/os_timer.h"
#include "../../../../../include/os/include/intmail.h"
#include "../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../include/io/serial/include/rs232_l2.h"
#include "dsp/gdsp_all_inits.h"
#include "wentworth/fppp_common.h"
#include "wentworth/wentworth_fp.h"
#include "dsp/gdsp_driver_functions_api.h"
#include "wentworth/afe.h"
#include "wentworth/access_bus.h"

extern UByte VEHICLEDETECTTASKTIMER;

extern void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN);
extern void ConvertHexSNtoAriSN(IPEIType Hex_SN, char SerialNumber[11]);
void SendConfiguration(PPIDType user);
extern UByte getSpeechBufferIndex(BYTE Pmid[3]);
extern void CheckNightVolumeTime(void);
extern void RunGreetClock(UByte greet_cmd, UByte greet_selection);
#ifdef SECOND_BASE_CODE
extern void ConnectPCM(void);
extern void SendQuickData(UByte user);
extern void SendPCMCommand(WORD cmd);
#endif
extern void WTInfoDebugScreen();

#ifdef ENABLE_TONEGEN
UByte enable_tonegenerator_for_test=0;
#endif

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

void voice_outgoingCallRequest(PPIDType a, PPIDType b)
{
	voice_callUser(b,a);
	voice_updateDisplay(a,"Calling");
}

void msf_IWUToIWUReceived(unsigned char *data)
{
  IwuToIwuType *IwuToIwuIE = (IwuToIwuType *)data;
  int f;
  char* ptr = StringPrint(StatusString, "IWUToIWU[");
  ptr = StrPrintHexByte(ptr, IwuToIwuIE->LengthOfContents);
  ptr = StringPrint(ptr, ",");
  ptr = StrPrintHexByte(ptr, IwuToIwuIE->ProtocolDiscrim);
  ptr = StringPrint(ptr, ",");
  ptr = StrPrintHexByte(ptr, IwuToIwuIE->DiscrimType);
  ptr = StringPrint(ptr, ",");
  ptr = StrPrintHexByte(ptr, IwuToIwuIE->Emc[0]);
  ptr = StrPrintHexByte(ptr, IwuToIwuIE->Emc[1]);
  ptr = StringPrint(ptr, ",");
  for (f = sizeof(IwuToIwuType); f < IwuToIwuIE->LengthOfContents + 3; f++)
    ptr = StrPrintHexByte(ptr, data[f]);
  ptr = StringPrint(ptr, "]");
  PrintStatus(0, StatusString);
}

void voice_incommingCallAlerting(PPIDType called, PPIDType caller)
{
	voice_updateDisplay(caller,"Alerting");
}

void voice_callConnected(PPIDType called, PPIDType caller)
{
	voice_updateDisplay(called,"Connected");
}

extern void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length);

void voice_callDisconnected(PPIDType disconnectedUser, PPIDType wasConnectedTo,UByte reason)
{
//	CopyToUartTxBuffer((UByte *)"t \"headset deleted\" 10 50\r", 26);
//	PrintStatus(0, "** call disconnected - gray button ");
	_sprintf_(StatusString,"wasconnectedto: %x",wasConnectedTo);
	PrintStatus(0,StatusString);
	/*voice_updateDisplay(wasConnectedTo,"DisconnectedNormal");*/
    voice_disConnectUser(wasConnectedTo);

    // set up registration display "gray" button here
	(base_station).HeadsetIsOn[disconnectedUser] = FALSE;
	if ((base_station).MicIsOn[disconnectedUser])
	{
		WWMSF WWMSFVal;
		WWMSFVal.SubStatusType = MIC_MUTE_CMD;
		WWMSFVal.Sub.SetMicMute.MicMute = 1;              			// 0 is unmute, 1 is mute
		HandlePacketFromPP(disconnectedUser, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
	}
	PMIDType pmid;
    PPID2PMID((PMIDType *) pmid, disconnectedUser);
	if ((base_station).PageMode[(getSpeechBufferIndex(pmid) >> 1)])
	{
		(base_station).PageMode[(getSpeechBufferIndex(pmid) >> 1)] = FALSE;
  		p_dynmixer6->weights[(getSpeechBufferIndex(pmid) >> 1)] = MIXER6_ATTEN;
	}
#ifdef SECOND_BASE_CODE
    if (!FIRST_BASE)
    	SendPCMCommand(PP_ON_ind + (disconnectedUser << 4) + 0);
#endif
    if ((base_station).DisplayScreen == REGISTRATION)
    {
    	UByte buffer[50];
    	int count, i = disconnectedUser;
    	IPEIType Ipei;
    	char SN[17];

    	CopyToUartTxBuffer((UByte *)"f 18BC\r", 7);
		Ipei[0] = 0x01;						// hard coding 0x01 for 1st byte
        memcpy(&Ipei[1], QuickData[i].Upi, 4);
		ConvertIpeiToSN(i, SN, Ipei);
		memcpy(&buffer[0], "m register_box:lbl_0_", 21);
		count = 21;
		count += GetAsciiValue(&buffer[0], (i + 40), count);
		memcpy(&buffer[0] + count, " \"off ", 6);
		count += 6;
		memcpy(&buffer[0] + count, &SN[6], 10);
		count += 10;
		memcpy(&buffer[0] + count, "\"\r", 2);
		count += 2;
		CopyToUartTxBuffer(&buffer[0], count);
    }
    if (disconnectedUser == (base_station).OrderTakerID)
    {
    	(base_station).OrderTakerID = 0xFF;
#ifdef SECOND_BASE_CODE
		if (!FIRST_BASE)
			SendPCMCommand(ORDER_TAKER_ind + 0xFF);
#endif
    }
}

void msf_releaseIndReceived(PPIDType user, UByte releaseReason)
{

    char *ptr;
    ptr = StringPrint(StatusString, "Msf released user: ");
    ptr = StrPrintHexByte(ptr, user);
    ptr = StringPrint(ptr, " reason: ");
    ptr = StrPrintHexByte(ptr, releaseReason);
	PrintStatus(0,StatusString);
}

void msf_msfsetupIndReceived(PPIDType user, char * functionNumber)
{
	msf_send_CONNECT_res(user);
	msf_send_DispReq("Connected","",user, msf_help_generateSetupSpec1(0,0,0,0,0,Pattern_7));
}

int jsjcounter = 0;
int upperJsjcoutner = 0;

void msf_infoIndReceived(PPIDType user, char keyPressed)
{
    msf_send_DispReq("test","1",user,msf_help_generateSetupSpec1(0,0,0,0,0,Pattern_3));
}

void fp_module2module_ack_received(PPIDType user, module2moduleData optionalDataSrc)
{
    /*char * tmpPtr;
    tmpPtr = StringPrint(StatusString,"fp_module2module_ack_received: ");
    tmpPtr = StrPrintHexByte(tmpPtr,optionalDataSrc[0]);
    tmpPtr = StringPrint(tmpPtr," ");
    tmpPtr = StrPrintHexByte(tmpPtr,optionalDataSrc[1]);
    tmpPtr = StringPrint(tmpPtr," ");
    tmpPtr = StrPrintHexByte(tmpPtr,optionalDataSrc[2]);
    tmpPtr = StringPrint(tmpPtr," ");

    PrintStatus(0,StatusString);*/

    if (jsjcounter == 1)
    {
        char * tmpPtr;
        upperJsjcoutner++;
        tmpPtr = StringPrint(StatusString, "module2module commands: 10*");
        tmpPtr = StrPrintHexWord(tmpPtr,upperJsjcoutner);
        PrintStatus(0,StatusString);
    }
    else
    {
        jsjcounter++;
        /* fp_send_module2module(user,optionalDataSrc); */
    }

   /*  msf_send_DispReq("k","",user,msf_help_generateSetupSpec1(0,0,0,0,0,Pattern_4)); */
}

void fp_module2module_received(PPIDType user, module2moduleData dataSrc, module2moduleData ackDataDst)
{
    char * tmpPtr;
    tmpPtr = StringPrint(StatusString,"fp_module2module_received: ");
    tmpPtr = StrPrintHexByte(tmpPtr,dataSrc[0]);
    tmpPtr = StringPrint(tmpPtr," ");
    tmpPtr = StrPrintHexByte(tmpPtr,dataSrc[1]);
    tmpPtr = StringPrint(tmpPtr," ");
    tmpPtr = StrPrintHexByte(tmpPtr,dataSrc[2]);
    tmpPtr = StringPrint(tmpPtr," ");

    ackDataDst[0] = dataSrc[0];
    ackDataDst[1] = dataSrc[1];
    ackDataDst[2] = dataSrc[2];

    PrintStatus(0,StatusString);

   /* msf_send_DispReq("k","",user,msf_help_generateSetupSpec1(0,0,0,0,0,Pattern_4)); */
}

void msf_connectCfmReceived(PPIDType user)
{
	_sprintf_(StatusString,"MSF session ready: %x",user);
	PrintStatus(0,StatusString);
    char * tmpPtr;
    tmpPtr = StringPrint(StatusString,"*** MSF session for user ");
    tmpPtr = StrPrintHexByte(tmpPtr, user);
    tmpPtr = StringPrint(tmpPtr," *** ");
	PrintStatus(0, tmpPtr);
}

void msf_outgMessageIndReceived(PPIDType user, UByte setupSpec2, UByte setupSpec3, UByte alertPattern, UByte alertTone, UByte alertTimeout, UByte displayTimeout, char * dstId, char * displayText, PPIDType callbackId)
{
	PPIDType to;
	to = getIntFromString(dstId);
	_sprintf_(StatusString,"msf to: %x",to);
	PrintStatus(0,StatusString);
	/*msf_setupreq_format1(to,msf_help_generateSetupSpec1(0,0,0,0,0,Pattern_3),displayText,callbackId);*/
	{
	    UByte spec1 = msf_help_generateSetupSpec1(0,0,0,0,0,Pattern_2);
        UByte spec2 = msf_help_generateSetupSpec2(0,0,0);
        UByte spec3 = msf_help_generateSetupSpec3(functionType_dont_touch_led_or_envelope,0,0,0,0);

        dateAndTimeType dateTime;
        alertConstructiontType alertConstruction;
        dateTime.length = 0;
        alertConstruction.alertPattern = alertPattern_not_present;
        alertConstruction.alertTimeout = 0;
        alertConstruction.alertTone = alertToneType_pp_tone_2;

	    msf_setupreq_format2(to,spec1,displayText,callbackId,spec2,spec3,alertConstruction,10,dateTime);
	}
}

void BroadcastBlinkLED(unsigned char value);
void BroadcastSystemModeState(PPIDType user);
void BroadcastOrderTaker(PPIDType user, unsigned char value);
void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length)
{
  int i;
  BOOLEAN OkToTurnMicOff = TRUE;
  PMIDType pmid;

  WWMSF *WWMSFptr = (WWMSF *) data; // typecast to known structure
  switch (WWMSFptr->SubStatusType) // Which command?
  {
    case CONF_FROM_BS: // request for configuration
      SendConfiguration(user);
      break;
    case MIC_MUTE_CMD:
//    {
//      extern int getAllocatedMemory();
//      int mem = getAllocatedMemory();
//      if (mem > 0x1500)
////      if (mem > 0)
//      {
//    	char *ptr;
//        ptr = StringPrint(StatusString, "GetAllocatedMemory [0x");
//        ptr = StrPrintHexWord(ptr, mem);
//        ptr = StringPrint(ptr, "] ");
//        PrintStatus(0, StatusString);
//      }
//    }
#ifdef SECOND_BASE_CODE
      if (!FIRST_BASE)
		SendPCMCommand(PP_MIC_ind + (user << 4) + (WWMSFptr->Sub.SetMicMute.MicMute & 0x000F));
      else
#endif
    	if ((WWMSFptr->Sub.SetMicMute.MicMute & 0x000F) == 1)
      {
//PrintStatus(0, "MicMute == 1");
    	(base_station).MicIsOn[user] = FALSE;
    	// check to see if any other headset MICs are on
//char *ptr;
//ptr = StringPrint(StatusString, "1 - OkToTurnMicOff:(");
//ptr = StrPrintDecByte(ptr, OkToTurnMicOff);
//ptr = StringPrint(ptr, ") VDIsActive:(");
//ptr = StrPrintDecByte(ptr, (base_station).VehicleDetectIsActive);
//ptr = StringPrint(ptr, ") ");
//PrintStatus(0, StatusString);
		for (i = 0; i < MAX_Allowed_Users; i++)
		{
		  if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
		  {
//ptr = StringPrint(StatusString, "Headset[");
//ptr = StrPrintDecByte(ptr, i);
//ptr = StringPrint(ptr, "] is on ");
//PrintStatus(0, StatusString);
		    OkToTurnMicOff = FALSE;
		    i = MAX_Allowed_Users;
		  }
		}
//char *ptr;
//ptr = StringPrint(StatusString, "2 - OkToTurnMicOff:(");
//ptr = StrPrintDecByte(ptr, OkToTurnMicOff);
//ptr = StringPrint(ptr, ") VDIsActive:(");
//ptr = StrPrintDecByte(ptr, (base_station).VehicleDetectIsActive);
//ptr = StringPrint(ptr, ") ");
//PrintStatus(0, StatusString);
#ifdef SECOND_BASE_CODE
		// TODO: review this ... the above code does this already so this is redundant?
		if ((base_station).SecondBoardPresent)
		  for (i = MAX_Allowed_Users_Dual; i < MAX_Allowed_Users; i++)
		  {
			if (((base_station).HeadsetIsOn[i]) && ((base_station).MicIsOn[i]))
			{
//ptr = StringPrint(StatusString, "Headset[");
//ptr = StrPrintDecByte(ptr, i);
//ptr = StringPrint(ptr, "] is on ");
//PrintStatus(0, StatusString);
			  OkToTurnMicOff = FALSE;
			  i = MAX_Allowed_Users;
			}
		  }
#endif
		// if no other headset MICs are on and no vehicle is detected, turn off menu board MIC
		if (OkToTurnMicOff && !(base_station).VehicleDetectIsActive)
		{
		  AFEDisablePostMicPath();								// disable DECT MIC input
		  GRILL_SPEAKER_OFF;									// mute the grill speaker
		  (base_station).GrillShouldBeOn = FALSE;
		  MENU_SPKR_AMP_OFF;									// mute post speaker (enables GREET audio path in to DECT MICP/N)
		  if (((base_station).DisplayScreen == GREETER_SETUP) ||
			  ((base_station).DisplayScreen == MESSAGE_SETUP1) ||
			  ((base_station).DisplayScreen == MESSAGE_SETUP2))	// configure post mic/speaker for greeter recording
		  {
			RefreshOutboundVolume(3);							// temporarily "normalize" for recording level
			AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);		// temporarily set inbound for playback comfort
		  }
		  if ((base_station).SystemMode == SPEED_TEAM)
			PlayQueuedMessage();								// play any waiting alert or reminder
		}
		// if no other headset MICs are on, but a vehicle is detected, turn on blinking LEDs again
		else if (OkToTurnMicOff && (base_station).VehicleDetectIsActive)
		{
		  BroadcastBlinkLED(1);									// 1 = RED LED
		}
//char *ptr;
//ptr = StringPrint(StatusString, "3 - OkToTurnMicOff:(");
//ptr = StrPrintDecByte(ptr, OkToTurnMicOff);
//ptr = StringPrint(ptr, ") VDIsActive:(");
//ptr = StrPrintDecByte(ptr, (base_station).VehicleDetectIsActive);
//ptr = StringPrint(ptr, ") ");
//PrintStatus(0, StatusString);
      }
      else
      {
//PrintStatus(0, "MicMute != 1");
      	(base_station).MicIsOn[user] = TRUE;
//char *ptr;
//ptr = StringPrint(StatusString, "1 - OrderTakerID:(0x");
//ptr = StrPrintHexByte(ptr, (base_station).OrderTakerID);
//ptr = StringPrint(ptr, ") ");
//PrintStatus(0, StatusString);
      	// if PP sends "2", then it is requesting to be the new OT
    	if ((WWMSFptr->Sub.SetMicMute.MicMute & 0x000F) == 2)
    	{
    	  if (((base_station).OrderTakerID != 0xFF) && ((base_station).OrderTakerID != user))
    	  {
    		PrintStatus(0, "canceling existing OT");
    		// cancel the existing OT
#ifdef SECOND_BASE_CODE
      	  if ((base_station).SecondBoardPresent && (user >= MAX_Allowed_Users_Dual))
  			SendPCMCommand(ORDER_TAKER_ind + (user - MAX_Allowed_Users_Dual));
      	  else
#endif
          	BroadcastOrderTaker((base_station).OrderTakerID, 0);
    	  }
		  PrintStatus(0, "assigning new OT");
    	  (base_station).OrderTakerID = user;
    	}

      	if ((((base_station).SystemMode & 0x0F) == AUTO_HANDS_FREE) && ((base_station).OrderTakerID == 0xFF))
      	{
      	  // when in Auto Hands Free mode, assign new order taker if current order taker doesn't exist
      	  (base_station).OrderTakerID = user;
#ifdef SECOND_BASE_CODE
      	  if ((base_station).SecondBoardPresent && (user >= MAX_Allowed_Users_Dual))
  			SendPCMCommand(ORDER_TAKER_ind + (user - MAX_Allowed_Users_Dual));
      	  else
#endif
          	BroadcastOrderTaker((base_station).OrderTakerID, 1);
      	}
//char *ptr;
//ptr = StringPrint(StatusString, "2 - OrderTakerID:(0x");
//ptr = StrPrintHexByte(ptr, (base_station).OrderTakerID);
//ptr = StringPrint(ptr, ") ");
//PrintStatus(0, StatusString);
      	if ((base_station).VehicleDetectIsActive)
      	{
          // order is being taken, shut off all other LEDs if they were on
    	  BroadcastBlinkLED(0);									// 0 = no LED
      	}
    	if ((((base_station).SystemMode & 0x0F) != SPEED_TEAM) &&
    		 ((base_station).DisplayScreen != GREETER_SETUP) &&
    	     ((base_station).DisplayScreen != MESSAGE_SETUP1) &&
    	     ((base_station).DisplayScreen != MESSAGE_SETUP2))
    	{
		  AFESetGainInboundVolumeFP(NORMAL_INBOUND);
		  RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
    	  if ((base_station).P33UsedForGreetMux)
    		GREET_IN_PP_OFF;									// enable BC5 audio path only (no GREET) in to DECT MICP/N
    	  MENU_SPKR_AMP_ON;										// make sure post speaker is on (enables BC5 audio path in to DECT MICP/N)
    	  if ((base_station).GrillSpeakerVolume > 0)
    		GRILL_SPEAKER_ON;									// turn on grill speaker
    	  (base_station).GrillShouldBeOn = TRUE;
    	  // TODO: CRP - convert usec_pause to use timer
    	  usec_pause(65535);
		  usec_pause(65535);
		  AFEEnablePostMicPath();								// enable DECT MIC input since a headset MIC is on
    	}
    	PPID2PMID((PMIDType *) pmid, user);
  		p_dynmixer6->weights[(getSpeechBufferIndex(pmid) >> 1)] = MIXER6_ATTEN;	// make sure channel to menu board speaker is on
  	   	if ((base_station).CarIsWaiting && ((((base_station).SystemMode & 0x0F) == HANDS_FREE) || (((base_station).SystemMode & 0x0F) == PUSH_TO_TALK)))
    	{
    	  PrintStatus(0, "*** CB is HI, GREET_N is HI *** ");
    	  SET_CB_HI;											// drive CB high
    	  GREET_N_HI;											// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
    	  if ((base_station).MessageIsPlaying > 0)
    		RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);
    	  else if ((base_station).MessageIsRecording > 0)
    		RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);
    	}
  	   	(base_station).CarIsWaiting = FALSE;
      }
      break;
    case GET_SYSTEM_MODE:
    {
      char * tmpPtr;
      UByte rev[6];
      tmpPtr = StringPrint(StatusString, "*** PP FW = ");
      rev[GetAsciiValue(&rev[0], (WWMSFptr->Sub.SetSystemMode.SystemMode >> 8), 0)] = '\0';
      tmpPtr = StringPrint(tmpPtr, (char *)rev);
      tmpPtr = StringPrint(tmpPtr, ".");
      rev[GetAsciiValue(&rev[0], (WWMSFptr->Sub.SetSystemMode.SystemMode & 0x00FF), 0)] = '\0';
      tmpPtr = StringPrint(tmpPtr, (char *)rev);
      tmpPtr = StringPrint(tmpPtr, "-AL *** ");
      PrintStatus(0, StatusString);
      BroadcastSystemModeState(user);
      break;
    }
    case PAGE_CMD:
      PPID2PMID((PMIDType *) pmid, user);
      if (WWMSFptr->Sub.SetPage.Page == 1)
      {
		(base_station).PageMode[(getSpeechBufferIndex(pmid) >> 1)] = TRUE;
  		p_dynmixer6->weights[(getSpeechBufferIndex(pmid) >> 1)] = 0x0000;
      }
      else
      {
		(base_station).PageMode[(getSpeechBufferIndex(pmid) >> 1)] = FALSE;
  		p_dynmixer6->weights[(getSpeechBufferIndex(pmid) >> 1)] = MIXER6_ATTEN;
      }
      break;
    default:
      break;
  }
}

UByte msf_ppstatus_ind_received(PPIDType user, UByte statusType, UByte * data, UByte data_length)
{
	int i;
	char * tmpPtr;
	tmpPtr = StringPrint(StatusString, "ppstatus_ind_received. Status: 0x");
	tmpPtr = StrPrintHexByte(tmpPtr, statusType);
	tmpPtr = StringPrint(tmpPtr, " Length: 0x");
	tmpPtr = StrPrintHexByte(tmpPtr, data_length);
	tmpPtr = StringPrint(tmpPtr, " Data:");

	for (i = 0; i < data_length; i++) {
		tmpPtr = StringPrint(tmpPtr, "0x");
		tmpPtr = StrPrintHexByte(tmpPtr, data[i]);
		tmpPtr = StringPrint(tmpPtr, ",");
	}
	PrintStatus(0, StatusString);
	if (statusType == WENTWORTH_PACKET_ID) // to avoid non approved messages
	{
		HandlePacketFromPP(user, data, data_length);
	}
    return 1;
}

WWMSF WWMSFVal; // Could be allocated on stack in function instead, but could also grow to be too large for stack allocation
// SendConfiguration can be changed to handle all kind of generic configuration from FP to PP
// .Debug1 value is sent from FP and can be used by PP for anything we want ...
void SendConfiguration(PPIDType user)
{
  char *tmp;
  tmp = StringPrint(StatusString, "SendConfiguration[");
  tmp = StrPrintHexByte(tmp, user);
  tmp = StringPrint(tmp, "]");
  PrintStatus(0, StatusString);
  WWMSFVal.SubStatusType = CONF_FROM_BS;
  WWMSFVal.Sub.SetConf.Debug1 = 0;              // 0 is normal, 1 is bypass BC5 speaker path; see gdsp_BC5SpeakerPath()
  general_startTimer(user, READ_CONF, (UByte *)&WWMSFVal, sizeof(WWMSFVal), 200);
}

void BroadcastCarWaiting(unsigned char value)
{
	WWMSFVal.SubStatusType = CAR_WAITING_CMD;
	WWMSFVal.Sub.SetCarWaiting.CarWaiting = value;
	msf_send_broadcast((UByte *)&WWMSFVal, sizeof(WWMSFVal), 0);
}

void BroadcastBlinkLED(unsigned char value)
{
	WWMSFVal.SubStatusType = BLINK_LED_CMD;
	WWMSFVal.Sub.SetLEDColor.LEDColor = value;
	msf_send_broadcast((UByte *)&WWMSFVal, sizeof(WWMSFVal), 0);
#ifdef SECOND_BASE_CODE
	if ((base_station).SecondBoardPresent || !FIRST_BASE)
		SendPCMCommand(BLINK_LED_ind + value);
#endif
}

PPIDType start_BroadcastSystemModeState_ppid = 0;
void BroadcastSystemModeState(PPIDType user)
{
    start_BroadcastSystemModeState_ppid = 0;
	general_startTimer(user, SYSTEM_MODE_CMD, NULL, 0, 20);    	// wait for 200ms
#ifdef SECOND_BASE_CODE
	if (FIRST_BASE && (base_station).SecondBoardPresent && (user == (PPIDType) -1))
		SendPCMCommand(SYSTEM_MODE_ind + ((base_station).InboundVol << 4) + (base_station).SystemMode);
#endif
}

void BroadcastOrderTaker(PPIDType user, unsigned char value)
{
	WWMSFVal.SubStatusType = SET_OT_CMD;
	WWMSFVal.Sub.SetOrderTaker.OrderTaker = value;
	general_startTimer(user, SET_OT_CMD, (UByte *)&WWMSFVal, sizeof(WWMSFVal), 50);
}

//static unsigned long m_z = 362436069, m_w = 521288629;
UByte to_print_heap_cnt=0;// Test
UByte fp_general_timeout(PPIDType user, UByte subEvent, UByte * dataPtr, UByte dataLength)
{
	if (subEvent == SYSTEM_MODE_CMD)
	{
	  WWMSFVal.SubStatusType = SYSTEM_MODE_CMD;
	  if ((user < 0) || (user > MAX_Allowed_Users))
	  {
		if ((base_station).ListenOnly[start_BroadcastSystemModeState_ppid] == 0x01)
		  WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + LISTEN_ONLY_MODE;
		else
		  WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + (base_station).SystemMode;
		if ((base_station).BC5Bypassed)
		  WWMSFVal.Sub.SetSystemMode.SystemMode |= 0x8000;			// set BC5 "off" bit
        if ((base_station).HeadsetIsOn[start_BroadcastSystemModeState_ppid])
          msf_send_ppstatusReq(start_BroadcastSystemModeState_ppid, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
        start_BroadcastSystemModeState_ppid++;
#ifdef SECOND_BASE_CODE
        if ((!(base_station).SecondBoardPresent && (start_BroadcastSystemModeState_ppid < MAX_Allowed_Users)) ||
             ((base_station).SecondBoardPresent && (start_BroadcastSystemModeState_ppid < MAX_Allowed_Users_Dual)))
#else
        if (start_BroadcastSystemModeState_ppid < MAX_Allowed_Users)
#endif
          general_startTimer(-1, SYSTEM_MODE_CMD, NULL, 0, 100);    // wait for 1s
	  }
	  else
	  {
		if ((base_station).ListenOnly[user] == 0x01)
		  WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + LISTEN_ONLY_MODE;
		else
		  WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + (base_station).SystemMode;
		if ((base_station).BC5Bypassed)
		  WWMSFVal.Sub.SetSystemMode.SystemMode |= 0x8000;			// set BC5 "off" bit
		msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
	  }
	}
	else if (subEvent == LISTEN_ONLY_MODE_CMD)
	{
//char *ptr;
//ptr = StringPrint(StatusString, "LO_CMD for user:");
//ptr = StrPrintDecByte(ptr, user);
//ptr = StringPrint(ptr, " ");
//PrintStatus(0, StatusString);
	  WWMSFVal.SubStatusType = SYSTEM_MODE_CMD;
	  if ((base_station).ListenOnly[user] == 0x01)
		WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + LISTEN_ONLY_MODE;
	  else
		WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + (base_station).SystemMode;
	  msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
#ifdef SECOND_BASE_CODE
	  if (!FIRST_BASE)
		general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
#endif
	}
	else if (subEvent == SET_OT_CMD)
	{
//PrintStatus(0, "sending SET_OT_CMD ....");
	  WWMSF *WWMSFptr = (WWMSF *) dataPtr; // typecast to known structure
	  WWMSFVal.SubStatusType = SET_OT_CMD;
	  WWMSFVal.Sub.SetOrderTaker.OrderTaker = WWMSFptr->Sub.SetOrderTaker.OrderTaker;
	  msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
//	  if (msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal)))
//		  PrintStatus(0, "send SET_OT_CMD error");
//	  else
//		  PrintStatus(0, "send SET_OT_CMD success");
	}
	else if (subEvent == READ_EEPROM)
	{
	  general_eeprom_read_req(EE_CUSTOMER_AREA, 5, 0);
	}
	else if (subEvent == READ_EEPROM_HEX_ARI)
	{
	  general_eeprom_read_req(EEP_Rfpi, EEP_Rfpi_Length, 1);
	}
	else if (subEvent == ENABLE_SPEECH_BUFFER)
	{
	  extern void EnableSpeechbufferInterrupt(void);
	  EnableSpeechbufferInterrupt();// For some reason this needs to be enabled a little bit later otherwise it crashes
#ifdef ENABLE_TONEGEN
	  extern void EnableTonegeneratorFPToMixer(void);
	  if (enable_tonegenerator_for_test)
	  {
		EnableTonegeneratorFPToMixer();
	  }
#endif
#ifdef ECT_DSP_MESSAGES
	  // HM Test
	  general_startTimer(-1, HM_TIMER_TESTING, NULL, 0, 200);
#endif
//	  general_startTimer(-1, WT_HEAP_CHECK, NULL, 0, 500);
	}
	else if (subEvent == HM_TIMER_TESTING)
	{
	  extern int getAllocatedMemory();
	  extern void *hm_print_heap(unsigned char reset);
	  to_print_heap_cnt++;
	  if (to_print_heap_cnt == 10)
	  {
		if (hm_print_heap(0) != NULL)
		  to_print_heap_cnt--;
		else
		{
		  to_print_heap_cnt = 0;
		  hm_print_heap(1);
		}
	  }
	  general_startTimer(-1, HM_TIMER_TESTING, NULL, 0, 200);
	}
	else if (subEvent == WT_HEAP_CHECK)
	{
	  extern void *hm_print_heap(unsigned char reset);
	  to_print_heap_cnt++;
	  if (to_print_heap_cnt == 10)
	  {
		if (hm_print_heap(0) != NULL)
		{
		  to_print_heap_cnt--;
		  general_startTimer(-1, WT_HEAP_CHECK, NULL, 0, 100);
		}
		else
		{
		  to_print_heap_cnt = 0;
		  hm_print_heap(1);
		}
	  }
	  else
		general_startTimer(-1, WT_HEAP_CHECK, NULL, 0, 100);
	}
	else if (subEvent == READ_CONF)
	{
	  char *tmp;
	  tmp = StringPrint(StatusString, "ConfData[");
	  tmp = StrPrintHexByte(tmp, *dataPtr);
	  tmp = StringPrint(tmp, ",");
	  tmp = StrPrintHexByte(tmp, *(dataPtr+1));
	  tmp = StringPrint(tmp, "]");
	  PrintStatus(0, StatusString);
	  msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, dataPtr, dataLength);
	}
	else if (subEvent == READ_WTDATA_EEPROM)
	{
	  general_eeprom_read_req(EE_WTDATA, EE_WT_NUM_BYTES, 2);
	}
	else if (subEvent == WRITE_WTDATA_EEPROM)
	{
	  char * ptr;
	  UByte test[EE_WT_NUM_BYTES];
	  int i, ii, result = 4, a = 0;

	  test[a++] = FW_REV_MAJOR;
	  test[a++] = FW_REV_MINOR;
	  test[a++] = (base_station).DisplayUserPin[0];
	  test[a++] = (base_station).DisplayUserPin[1];
	  test[a++] = (base_station).DisplayUserPin[2];
	  test[a++] = (base_station).DisplayUserPin[3];
	  test[a++] = ((base_station).SystemMode << 4) | (base_station).DisplayIsLocked;
	  test[a++] = (base_station).InboundVol;
	  test[a++] = (base_station).GrillSpeakerVolume;
	  test[a++] = (base_station).PostSpeakerVolumeDay;
	  test[a++] = (base_station).PostSpeakerVolumeNight;
	  test[a++] = (base_station).NightVolumeTimeStart.timeHourMSB;
	  test[a++] = (base_station).NightVolumeTimeStart.timeHourLSB;
	  test[a++] = (base_station).NightVolumeTimeStart.timeMinMSB;
	  test[a++] = (base_station).NightVolumeTimeStart.timeMinLSB;
	  test[a++] = (base_station).NightVolumeTimeEnd.timeHourMSB;
	  test[a++] = (base_station).NightVolumeTimeEnd.timeHourLSB;
	  test[a++] = (base_station).NightVolumeTimeEnd.timeMinMSB;
	  test[a++] = (base_station).NightVolumeTimeEnd.timeMinLSB;
	  for (i = 0; i < MAX_Allowed_Users; i++)
	  {
		  test[a++] = (base_station).ListenOnly[i];
	  }
	  for (i = 0; i < NUM_OF_MESSAGES; i++)
	  {
		test[a++] = (base_station).Message[i].MessageEnableName;
		for (ii = 0; ii < 4; ii++)
		{
		  test[a++] = (base_station).Message[i].StartTime[ii];
		  test[a++] = (base_station).Message[i].StopTime[ii];
		}
	  }
	  test[a++] = (base_station).GreeterActive;
	  test[a++] = (base_station).GrtrMsgrAuthCode[0];
	  test[a++] = (base_station).GrtrMsgrAuthCode[1];
	  test[a++] = (base_station).GrtrMsgrAuthCode[2];
	  test[a++] = (base_station).GrtrMsgrAuthCode[3];
	  test[a++] = (base_station).PowerOnCount >> 8;
	  test[a++] = (base_station).PowerOnCount & 0x00FF;
	  test[a++] = (base_station).AlangoNear;
	  test[a++] = (base_station).UsingP34ForAlarm;
	  test[a++] = (base_station).PlayGreetInPP;

	  result = general_eeprom_write_req(EE_WTDATA, test, a, 0);
	  ptr = StringPrint(StatusString,"****** eeprom write req result: ");
	  ptr = StrPrintDecByte(ptr, result);
	  ptr = StringPrint(ptr," (for ");
	  ptr = StrPrintDecByte(ptr, a);
	  ptr = StringPrint(ptr," bytes)");
	  PrintStatus(0,StatusString);
	}
	else if (subEvent == WRITE_WT_DEBUG_EEPROM)
	{
	  UByte test[2];

	  test[0] = (base_station).PowerOnCount >> 8;
	  test[1] = (base_station).PowerOnCount & 0x00FF;

	  char * ptr;
	  int result = 4;
	  result = general_eeprom_write_req(EE_WT_POWER_ON_COUNT, test, 2, 0);
	  ptr = StringPrint(StatusString,"****** eeprom counter write req result: ");
	  ptr = StrPrintDecByte(ptr, result);
	  ptr = StringPrint(ptr," ");
	  PrintStatus(0,StatusString);
	}
	else if (subEvent == SETUP_DISPLAY)
	{
#ifdef ECT_DSP_MESSAGES
	  extern unsigned int GetDSPStackRemaining(void);
	  char * ptr;
	  ptr = StringPrint(StatusString,"GetDSPStackRemaining[");
	  ptr = StrPrintDecByte(ptr, GetDSPStackRemaining());
	  ptr = StringPrint(ptr,"]");
	  PrintStatus(0,StatusString);
#endif

	  CopyByteToUartTxBuffer('\r');																// send 3 CRs to make sure display is ready
	  CopyByteToUartTxBuffer('\r');
	  CopyByteToUartTxBuffer('\r');
	  CopyToUartTxBuffer((UByte *)"m startup1", 10);											// start display with parameters
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).DisplayIsLocked);				// e0 locked/unlocked state
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(((base_station).SystemMode & 0x0F) - 1);		// e1 mode
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).VehicleDetectIsActive ? 2 : 1);	// e2 Lane 1 - car present or not
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);											// e3 Lane 2
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).DayTime);						// e4 Volume mode
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);											// e5 detect current volume - not implemented
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).InboundVol);					// e6 inbound volume
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).GrillSpeakerVolume);			// e7 grill current volume
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeDay);		// e8 day volume
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeNight);		// e9 night volume
	  CopyByteToUartTxBuffer('\r');																// complete command string

	  CopyToUartTxBuffer((UByte *)"m startup2", 10);											// start display with parameters
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);											// eA volume lanes info
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);											// eB multi-lane
	  CopyByteToUartTxBuffer('\r');																// complete command string

#ifdef SECOND_BASE_CODE
	  if (!(base_station).SecondBoardPresent && !(base_station).BaseRTC && !(base_station).GreetRTC)
#else
	  if (!(base_station).BaseRTC && !(base_station).GreetRTC)
#endif
	  {
		PrintStatus(0, "Running as single base system with no PCM bus");
		GdspUnhookVector(PCM_BUFFER_INT, DSP1); 												// unhook PCM[3] command interrupt handler
		GdspStop((unsigned short*)p_pcm_buffer);												// shut down p_pcm_buffer DP resource
	  }
	  else
	  {
#ifdef SECOND_BASE_CODE
		if ((base_station).SecondBoardPresent)
		  PrintStatus(0, "Running PCM bus for dual base system");
		if ((base_station).BaseRTC || (base_station).GreetRTC)
#endif
		  PrintStatus(0, "Running PCM bus for Real Time Clock");
	  }
	}
	else if (subEvent == CHECK_TEOM)
	{
	  UByte P3_6 = (P3_DATA_REG & Px_6_DATA);

	  // check TEOM during playback
	  if (((base_station).MessageIsPlaying > 0) && (P3_6 == 0x00))
	  {
//		CopyToUartTxBuffer((UByte *)"t \"TEOM playback sensed LOW\" 25 225\r", 36);
		// check if we need to send button up command
		if ((base_station).MsgBeingEdited == (base_station).MessageIsPlaying)
		{
		  CopyToUartTxBuffer((UByte *)"ssb 43 0\r", 9);			// release play button
		  CopyToUartTxBuffer((UByte *)"xe 43\r", 6);			// enable play button
		  CopyToUartTxBuffer((UByte *)"xe 44\r", 6);			// enable record button
		  CopyToUartTxBuffer((UByte *)"xd 45\r", 6);			// disable stop button
		  GREET_N_HI;											// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
		  MENU_SPKR_AMP_OFF;									// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		  GRILL_SPEAKER_OFF;									// mute grill speaker during playback
		  (base_station).GrillShouldBeOn = FALSE;
		  RefreshOutboundVolume(3);								// temporarily "normalize" for recording level
		  AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);			// temporarily set inbound for playback comfort
		}
		else if ((base_station).VehicleDetectIsActive || ((base_station).MessageIsPlaying > 7))
		{
		  StopTimer(VEHICLEDETECTTASKTIMER); 					// temporarily stop checking vehicle detector
		  // greet played because of vehicle detect and has finished or reminder has finished, re-connect post mic and grill speaker
		  PrintStatus(0, "*** CB is HI, GREET_N is HI *** ");
		  if ((base_station).VehicleDetectIsActive)
		  {
			BroadcastCarWaiting(11);							// send "car waiting in lane 1 + beep" command
#ifdef SECOND_BASE_CODE
			if ((base_station).SecondBoardPresent)
			  SendPCMCommand(CAR_WAITING_ind + 11);				// send "car waiting in lane 1 + beep" command to second base
#endif
		  }
		  SET_CB_HI;											// drive CB high
		  GREET_N_HI;											// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
		  AFESetGainInboundVolumeFP(NORMAL_INBOUND);
		  RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
		  if ((base_station).P33UsedForGreetMux)
			GREET_IN_PP_OFF;									// enable BC5 audio path only (no GREET) in to DECT MICP/N
		  MENU_SPKR_AMP_ON;										// make sure post speaker is on (enables BC5 audio path in to DECT MICP/N)
		  if ((base_station).GrillSpeakerVolume > 0)
			GRILL_SPEAKER_ON;									// turn on grill speaker
		  (base_station).GrillShouldBeOn = TRUE;
		  // TODO: CRP - convert usec_pause to use timer
		  usec_pause(65535);
		  usec_pause(65535);
		  if ((base_station).SystemMode == SPEED_TEAM)
		  {
			AFEDisablePostMicPath();							// disable DECT MIC input for SPEED TEAM mode
			MENU_SPKR_AMP_OFF;									// mute the menu board speaker for SPEED TEAM mode (enables GREET audio path in to DECT MICP/N)
		  }
		  else if ((base_station).VehicleDetectIsActive)
			AFEEnablePostMicPath();								// enable DECT MIC input
		  else
			AFEDisablePostMicPath();							// disable DECT MIC input
	  	  OSStartTimer(VEHICLEDETECTTASKTIMER, 20); 			// 20 x 10ms = 200ms resume checking vehicle detector
		}
		(base_station).MessageIsPlaying = 0;
	  }
	  else if (((base_station).MessageIsPlaying > 0) && (P3_6 == 0x40))
	  {
//		CopyToUartTxBuffer((UByte *)"t \"checking playback TEOM again\" 25 200\r", 40);
		general_startTimer(-1, CHECK_TEOM, NULL, 0, 1);			// check TEOM again in 10ms
	  }
	  // check TEOM during recording
	  else if (((base_station).MessageIsRecording > 0) && (P3_6 == 0x40))
	  {
//		CopyToUartTxBuffer((UByte *)"t \"TEOM recording sensed HI\" 25 225\r", 36);
		CopyToUartTxBuffer((UByte *)"ssb 44 0\r", 9);			// release record button
		CopyToUartTxBuffer((UByte *)"xe 43\r", 6);				// enable play button
		CopyToUartTxBuffer((UByte *)"xe 44\r", 6);				// enable record button
		CopyToUartTxBuffer((UByte *)"xd 45\r", 6);				// disable stop button
		MENU_SPKR_AMP_OFF;										// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		GRILL_SPEAKER_OFF;										// mute grill speaker during playback
		(base_station).GrillShouldBeOn = FALSE;
		RefreshOutboundVolume(3);								// temporarily "normalize" for recording level
		AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);			// temporarily set inbound for playback comfort
		RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// send stop command to configure pins
	  }
	  else if (((base_station).MessageIsRecording > 0) && (P3_6 == 0x00))
	  {
//		CopyToUartTxBuffer((UByte *)"t \"checking recording TEOM again\" 25 200\r", 41);
		general_startTimer(-1, CHECK_TEOM, NULL, 0, 1);			// check TEOM again in 10ms
	  }
	}
#ifdef SECOND_BASE_CODE
	else if (subEvent == SETUP_SECOND_BASE)
	{
	  (base_station).SecondBoardPresent = TRUE;
	  ConnectPCM();								// connect the PCM bus for audio

	  // tell first base that there is a second base and send FP_ARI[] data
	  SendPCMCommand(SECOND_BOARD_ind + (0 << 8) + (base_station).FP_ARI[0]);
	  SendPCMCommand(SECOND_BOARD_ind + (1 << 8) + (base_station).FP_ARI[1]);
	  SendPCMCommand(SECOND_BOARD_ind + (2 << 8) + (base_station).FP_ARI[2]);
	  SendPCMCommand(SECOND_BOARD_ind + (3 << 8) + (base_station).FP_ARI[3]);
	  SendPCMCommand(SECOND_BOARD_ind + (4 << 8) + (base_station).FP_ARI[4]);

	  StopTimer(VEHICLEDETECTTASKTIMER);		// no need to run the VD timer
	  p_dynmixer0->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise
	  p_dynmixer1->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise
	  p_dynmixer2->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise
	  p_dynmixer3->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise
	  p_dynmixer4->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise
	  p_dynmixer5->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise
	  p_dynmixer7->weights[6] = 0x0000;			// mute the post MIC input to prevent adding any noise

	  // this is second base, we'll still use for debug purposes
	  general_startTimer(-1, SETUP_DISPLAY, NULL, 0, 50);    // wait for 500ms
	}
	else if (subEvent == DISPLAY_WT_DEBUG_INFO)
	{
	  WTInfoDebugScreen();
	}
#endif
	else
	{
	  return 0;
	}
	return 0;
}

extern PPIDType fp_subscription_lookupUserFromIpei(IPEIType ipei);
UByte fp_subscription_allowSubscription(IPEIType IPEI)
{
	PPIDType user = 0xFFFF;

	// if "Register" button is pressed or if this headset is still listed in the base's subscription list
	if ((base_station).RegistrationAllowed)
	{
		return 1;
	}
	else
	{
		user = fp_subscription_lookupUserFromIpei(IPEI);
		if (user != 0xFFFF)
		{
			if (QuickData[user].EmptyMarker == 0)
				// still marked as active in the base's subscription list so let it re-subscribe
				return 1;
			else
				// in the base's subscription list but marked as deleted so ignore it
				return 0;
		}
		else
		{
			return 0;
		}
	}
}

extern UByte fp_subscription_getNumberOfSubscriptions();
void fp_subscription_locationRegistration(PPIDType user, IPEIType ipei, UByte status)
{
    char * tmp;
    tmp = StringPrint(StatusString, "Location registration completed for user ");
    tmp = StrPrintHexByte(tmp, user);
    tmp = StringPrint(tmp, " - [");
    tmp = StrPrintHexByte(tmp, ipei[0]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[1]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[2]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[3]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[4]);
    tmp = StringPrint(tmp, "]");

    PrintStatus(0, StatusString);

#ifdef SECOND_BASE_CODE
    if ((base_station).SecondBoardPresent && (fp_subscription_getNumberOfSubscriptions() >= MAX_Allowed_Users_Dual))
    {
    	// if this is second base, release registration button if necessary
    	if ((!FIRST_BASE) && (base_station).RegistrationButtonPressed)
    	{
	    	PrintStatus(0, "second base full - no more registrations allowed on second base");
			CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);
    	}
    	// if this is first base, check second base before releasing registration button
    	else if (FIRST_BASE && (base_station).RegistrationButtonPressed)
    	{
    		int i;
		    UByte base2 = 0;
		    for(i = 0; i < MAX_Allowed_Users_Dual; i++)
		    {
		        if((base_station).QuickDataBoard2[i].EmptyMarker == 0)
		        {
		        	base2++;
		        }
		    }
		    if (base2 >= MAX_Allowed_Users_Dual)
		    {
		    	PrintStatus(0, "first base full - no more registrations allowed");
		    	CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);
		    }
		    else
		    	PrintStatus(0, "first base full - only allowing registrations on second base");
    	}
    	// stop allowing registrations to this base
    	(base_station).RegistrationAllowed = FALSE;
    }
#else
    if (fp_subscription_getNumberOfSubscriptions() >= MAX_Allowed_Users)
    {
    	PrintStatus(0, "base full - no more registrations allowed");
    	CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);
    	// stop allowing registrations to this base
    	(base_station).RegistrationAllowed = FALSE;
    }
#endif
}

UByte fp_subscription_locationRegistrationRequested(PPIDType user, IPEIType ipei)
{
    char * tmp;
    tmp = StringPrint(StatusString, "User requesting location registration:");
    tmp = StrPrintHexByte(tmp, user);
	tmp = StringPrint(tmp, " - [");
    tmp = StrPrintHexByte(tmp, ipei[0]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[1]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[2]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[3]);
    tmp = StringPrint(tmp, ",");
    tmp = StrPrintHexByte(tmp, ipei[4]);
    tmp = StringPrint(tmp, "]");

	PrintStatus(0,StatusString);

	char SN[17];
	ConvertIpeiToSN(user, SN, ipei);

	return 1;
}

void fp_common_gpio_inputport_state_changed(gpio_port port, gpio_state state)
{
    char * ptr;
    ptr = StringPrint(StatusString,"input port changed: ");
    ptr = StrPrintHexByte(ptr,port);
    ptr = StringPrint(ptr," value: ");
    ptr = StrPrintHexByte(ptr,state);
    PrintStatus(0,StatusString);
}

void fp_general_eeprom_read_res(UByte status, PPIDType ppid, UByte * data, UByte length)
{
    char * ptr;
    int i, ii, a;
	UByte test[2];
//	PrintStatus(0, "fp_general_eeprom_read_res");
	if (ppid == 0)
	{
//		ptr = StringPrint(StatusString,"****** (STEP 0: EE_CUSTOMER_AREA) First byte read from eeprom (action_after_logon): 0x");
//		ptr = StrPrintHexByte(ptr, data[0]);
//		ptr = StringPrint(ptr," ");
//		PrintStatus(0,StatusString);
#ifdef ENABLE_TONEGEN
		if (data[0] == 0)
			enable_tonegenerator_for_test=1;
		else
			enable_tonegenerator_for_test=0;
#endif
		general_startTimer(-1, READ_EEPROM_HEX_ARI, NULL, 0, 100);	// Next we read the FP ARI from the EEPROM
	}
	else if (ppid == 1)
	{
		ptr = StringPrint(StatusString, "****** (STEP 1: EEP_Rfpi) FP ARI (hex): ");
		for (i = 0; i < 5; i++)
		{
			(base_station).FP_ARI[i] = data[i];
			ptr = StrPrintHexByte(ptr, data[i]);
			ptr = StringPrint(ptr, " ");
		}
		PrintStatus(0, StatusString);
		general_startTimer(-1, ENABLE_SPEECH_BUFFER, NULL, 0, 100);	// Next we enable the speech buffer
	}
	else if (ppid == 2)
	{
//		ptr = StringPrint(StatusString, "****** (STEP 2: EE_WTDATA) First two WTDATA bytes read from eeprom (FW Rev): ");
//		ptr = StrPrintDecByte(ptr, data[0]);
//		ptr = StringPrint(ptr, ".");
//		ptr = StrPrintDecByte(ptr, data[1]);
//		ptr = StringPrint(ptr, " and current rev is ");
//		ptr = StrPrintDecByte(ptr, FW_REV_MAJOR);
//		ptr = StringPrint(ptr, ".");
//		ptr = StrPrintDecByte(ptr, FW_REV_MINOR);
//		ptr = StringPrint(ptr, "-AL ");
//		PrintStatus(0,StatusString);
//		memset(test, 0xFF, 2);
		test[0] = FW_REV_MAJOR;
		test[1] = FW_REV_MINOR;
		if (memcmp(data, test, 2))
		{
			// any values in EEPROM WTDATA area are for different version (or no version), save current version values now
//			PrintStatus(0,"*** WTDATA is NOT present for current revision *** ");
			general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 100);	// write current values to EEPROM
		}
		else
		{
//			PrintStatus(0,"*** some WTDATA IS present for current revision *** ");
			// read out all the saved WTDATA values
			// FW_REV_MAJOR = data[0]
			// FW_REV_MINOR = data[1]
			a = 2;
			(base_station).DisplayUserPin[0] = data[a++];
			(base_station).DisplayUserPin[1] = data[a++];
			(base_station).DisplayUserPin[2] = data[a++];
			(base_station).DisplayUserPin[3] = data[a++];
			(base_station).DisplayIsLocked = data[a] & 0x0F;
			(base_station).SystemMode = data[a++] >> 4;
			(base_station).InboundVol = data[a++];
			(base_station).GrillSpeakerVolume = data[a++];
			(base_station).PostSpeakerVolumeDay = data[a++];
			(base_station).PostSpeakerVolumeNight = data[a++];
			(base_station).NightVolumeTimeStart.timeHourMSB = data[a++];
			(base_station).NightVolumeTimeStart.timeHourLSB = data[a++];
			(base_station).NightVolumeTimeStart.timeMinMSB = data[a++];
			(base_station).NightVolumeTimeStart.timeMinLSB = data[a++];
			(base_station).NightVolumeTimeEnd.timeHourMSB = data[a++];
			(base_station).NightVolumeTimeEnd.timeHourLSB = data[a++];
			(base_station).NightVolumeTimeEnd.timeMinMSB = data[a++];
			(base_station).NightVolumeTimeEnd.timeMinLSB = data[a++];
			for (i = 0; i < MAX_Allowed_Users; i++)
			{
				(base_station).ListenOnly[i] = data[a++];
			}
			for (i = 0; i < NUM_OF_MESSAGES; i++)
			{
				(base_station).Message[i].MessageEnableName = data[a++];
				for (ii = 0; ii < 4; ii++)
				{
					(base_station).Message[i].StartTime[ii] = data[a++];
					(base_station).Message[i].StopTime[ii] = data[a++];
				}
			}
			(base_station).GreeterActive = data[a++];
			(base_station).GrtrMsgrAuthCode[0] = data[a++];
			(base_station).GrtrMsgrAuthCode[1] = data[a++];
			(base_station).GrtrMsgrAuthCode[2] = data[a++];
			(base_station).GrtrMsgrAuthCode[3] = data[a++];
			(base_station).PowerOnCount = data[a++] << 8;
			(base_station).PowerOnCount += data[a++] + 1;					// increment to count this power on cycle
			(base_station).AlangoNear = data[a++];
			(base_station).UsingP34ForAlarm = data[a++];
			(base_station).PlayGreetInPP = data[a++];

			general_startTimer(-1, WRITE_WT_DEBUG_EEPROM, NULL, 0, 1);		// update power on counter to EEPROM
		}

		ConvertHexSNtoAriSN((base_station).FP_ARI, (base_station).SerialNumber);

		UByte code[4];
		for (i = 0; i < 4; i++)
			code[i] = 0x69 - (base_station).SerialNumber[6 + i];

		/*
		 * WT internal greeter authorization code is:
		 * 			9999	        example:	   9999
		 * -  WT BASE SN			         5244996257
		 * =============			         ==========
		 * 			XXXX                           3742
		 * encoded as ascii:
		 * 0x3X 0x3X 0x3X 0x3X 		0x33 0x37 0x34 0x32
		 *                             =    =    =    =
		 *
		 */
		if (memcmp(&code, &(base_station).GrtrMsgrAuthCode, 4) != 0)
		{
//			PrintStatus(0, "*** Greeter NOT authorized *** ");
			(base_station).GreeterInstalled = FALSE;
			(base_station).GreeterActive = FALSE;
		}
		else
		{
//			PrintStatus(0, "*** Greeter authorized *** ");
			(base_station).GreeterInstalled = TRUE;
			CheckForActiveGreet();								// check if a greet is active
			CheckForActiveMessage();							// check if reminders or the alarm messages are active
		}

		if (memcmp(&(base_station).NightVolumeTimeStart, &(base_station).NightVolumeTimeEnd, 4) != 0)
		{
			(base_station).NighTimeInEffect = TRUE;
			CheckNightVolumeTime();
		}

		// adjust p_gain_inbound MIC gain
		AFESetGainInboundVolumeFP(NORMAL_INBOUND);

		// adjust analog grill speaker circuit
		// using P0[4] VOL_CS
		// using P0[6] UPDOWN_GRILL
		if ((base_station).GrillSpeakerVolume > 0)
		{
			// increment MAX5407 (tap 31 "up" towards tap 0 direction) to decrease attenuation (increase volume)
			UPDOWN_GRILL_UP;							// set up for increment mode
			usec_pause(1);
			VOL_CS_HI;									// lock in increment mode
			for (i = 0; i < (base_station).GrillSpeakerVolume; i++)
			{
				UPDOWN_GRILL_LO;
				UPDOWN_GRILL_HI;
				usec_pause(1);
				UPDOWN_GRILL_LO;
			}
			VOL_CS_LO;									// freeze tap
		}

		// adjust p_gain_spkr_fp POST gain
		(base_station).CurrentOutboundVolume = (base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight;
		AFESetGainSpkrVolumeFP((base_station).CurrentOutboundVolume);

		if ((base_station).AlangoNear)
		{
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
			ALANGO_PROFILE_1;
		}
		else
			ALANGO_PROFILE_0;

		// check for presence of RTC on Base (then check on Greeter if necessary)
		SetupAccess1Bus();
		BASE_RTC_ON;							// look for RTC on base board first
		i = (ReadAccess1(RTC, 0x03) & 0x07);	// use day of week for a test
		WriteAccess1(RTC, 0x03, (8 - i));
		if ((ReadAccess1(RTC, 0x03) & 0x07) == (8 - i))
		{
//			PrintStatus(0, ">>>>  RTC present on Base  <<<<<<< ");
			(base_station).BaseRTC = TRUE;
			WriteAccess1(RTC, 0x03, i);			// restore previous day of week
			if ((base_station).PowerOnCount < 2)
			{
//				PrintStatus(0, "       initializing RTC on Base");
				// initialize the RTC to January 1, 2013 and clear the control/status registers
				WriteAccess1(RTC, 0x00, 0x00);	// seconds
				WriteAccess1(RTC, 0x04, 0x01);	// day of month
				WriteAccess1(RTC, 0x05, 0x01);	// month
				WriteAccess1(RTC, 0x06, 0x13);	// year
				WriteAccess1(RTC, 0x0E, 0x00);	// CONTROL
				WriteAccess1(RTC, 0x0F, 0x00);	// STATUS
				WriteAccess1(RTC, 0x10, 0x00);	// TRICKLE CHARGER
			}
			// set current time from RTC
			(base_station).DisplayTime.timeMinMSB = ReadAccess1(RTC, 0x01);
			(base_station).DisplayTime.timeMinLSB = ((base_station).DisplayTime.timeMinMSB & 0x0F);
			(base_station).DisplayTime.timeMinMSB = ((base_station).DisplayTime.timeMinMSB & 0xF0) >> 4;
			(base_station).DisplayTime.timeHourMSB = ReadAccess1(RTC, 0x02);
			(base_station).DisplayTime.timeHourLSB = ((base_station).DisplayTime.timeHourMSB & 0x0F);
			(base_station).DisplayTime.timeHourMSB = ((base_station).DisplayTime.timeHourMSB & 0xF0) >> 4;
			(base_station).CurrentDay = i - 1;	// base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
			BASE_PCM_ON;						// enable PCM pass through again
		}
		else
		{
//			PrintStatus(0, ">>>>  RTC not present on Base  <<<<<<< ");
			BASE_PCM_ON;
			if ((base_station).GreeterInstalled)
			{
				// look for RTC on greeter next
				(base_station).GreetRTC = TRUE;			// assume RTC is present
				RunGreetClock(MESSAGE_INIT, 2);			// switch Greeter mux to RTC if present
				i = (ReadAccess1(RTC, 0x03) & 0x07);	// use day of week for a test
				WriteAccess1(RTC, 0x03, (8 - i));
				if ((ReadAccess1(RTC, 0x03) & 0x07) == (8 - i))
				{
//					PrintStatus(0, ">>>>  RTC present on Greeter  <<<<<<< ");
					WriteAccess1(RTC, 0x03, i);			// restore previous day of week
					if ((base_station).PowerOnCount < 2)
					{
//						PrintStatus(0, "       initializing RTC on Greeter ");
						// initialize the RTC to January 1, 2013 and clear the control/status registers
						WriteAccess1(RTC, 0x00, 0x00);	// seconds
						WriteAccess1(RTC, 0x04, 0x01);	// day of month
						WriteAccess1(RTC, 0x05, 0x01);	// month
						WriteAccess1(RTC, 0x06, 0x13);	// year
						WriteAccess1(RTC, 0x0E, 0x00);	// CONTROL
						WriteAccess1(RTC, 0x0F, 0x00);	// STATUS
						WriteAccess1(RTC, 0x10, 0x00);	// TRICKLE CHARGER
					}
					// set current time from RTC
					(base_station).DisplayTime.timeMinMSB = ReadAccess1(RTC, 0x01);
					(base_station).DisplayTime.timeMinLSB = ((base_station).DisplayTime.timeMinMSB & 0x0F);
					(base_station).DisplayTime.timeMinMSB = ((base_station).DisplayTime.timeMinMSB & 0xF0) >> 4;
					(base_station).DisplayTime.timeHourMSB = ReadAccess1(RTC, 0x02);
					(base_station).DisplayTime.timeHourLSB = ((base_station).DisplayTime.timeHourMSB & 0x0F);
					(base_station).DisplayTime.timeHourMSB = ((base_station).DisplayTime.timeHourMSB & 0xF0) >> 4;
					(base_station).CurrentDay = i - 1;	// base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
					RunGreetClock(MESSAGE_INIT, 1);		// switch Greeter mux back to PCM pass through if present
				}
				else
				{
//					PrintStatus(0, ">>>>  RTC not present on Greeter  <<<<<<< ");
					RunGreetClock(MESSAGE_INIT, 1);		// switch Greeter mux back to PCM pass through if present
					(base_station).GreetRTC = FALSE;	// Greet RTC is not present
				}
			}
		}
		SetupPCMBus();

#ifdef SECOND_BASE_CODE
		if (!FIRST_BASE)
			general_startTimer(-1, SETUP_SECOND_BASE, NULL, 0, 10);
		else
#endif
			general_startTimer(-1, SETUP_DISPLAY, NULL, 0, 50);    // wait for 500ms
	}
}

void msf_broadcast_cfm(UByte result)
{
//	char *ptr;
//	ptr = StringPrint(StatusString, "Broadcast cfm: ");
//	ptr = StrPrintHexByte(ptr, result);
//	PrintStatus(0, StatusString);
}

void fp_system_init()
{
  PrintStatus(0, "eeprom read req");
  general_startTimer(-1, READ_EEPROM, NULL, 0, 150);	// Request eeprom info in 1500ms, to avoid the answer is received in a task which is not ready
}
