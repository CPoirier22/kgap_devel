#include "../../../../api/include/fp/fp_api.h"
#include "../../../../api/include/fp/fp_voice_callback.h"
#include "../../../../api/include/fp/fp_voice_functions.h"
#include "../../../../api/include/fp/fp_msf_callback.h"
#include "../../../../api/include/fp/fp_msf_functions.h"
#include "../../../../api/include/fp/fp_module2module_callback.h"
#include "../../../../api/include/fp/fp_module2module_functions.h"
#include "../../../../api/include/fp/fp_subscription_functions.h"
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
extern void ConnectPCM(void);
extern void SendPCMCommand(WORD cmd);
extern void WTInfoDebugScreen();
extern void ServiceVehicleDetect(BOOLEAN VehicleIsPresent);

#ifdef ENABLE_TONEGEN
UByte enable_tonegenerator_for_test=0;
#endif

static void usec_pause(DWORD x)						// -2,147,483,648 to 2,147,483,647
{
    volatile DWORD i;
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

void fp_IWUToIWUReceived(unsigned char *data)
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
	voice_updateDisplay(caller,"Connected");
}

extern void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length);

// this runs whenever a PP is powered off
void voice_callDisconnected(PPIDType disconnectedUser, PPIDType wasConnectedTo,UByte reason)
{
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
		(base_station).OrderTakerID = 0xFF;
    if ((base_station).DualBase)
   		SendPCMCommand(PP_ON_ind + (disconnectedUser << 4) + 0);
    if ((disconnectedUser + 1) == (base_station).UsingWirelessPost)
    {
    	(base_station).UsingWirelessPost = 0;
    	p_dynmixer0->weights[6] = MIC_A_ATTEN;
    	p_dynmixer1->weights[6] = MIC_A_ATTEN;
    	p_dynmixer2->weights[6] = MIC_A_ATTEN;
    	p_dynmixer3->weights[6] = MIC_A_ATTEN;
    	p_dynmixer4->weights[6] = MIC_A_ATTEN;
    	p_dynmixer5->weights[6] = MIC_A_ATTEN;
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
void BroadcastWirelessPostCmd(PPIDType user, WORD cmd);
void UpdateDualMenuMixers();
void HandlePacketFromPP(PPIDType user, UByte * data, UByte data_length)
{
  int i;
  BOOLEAN OkToTurnMicOff = TRUE;
  WORD req;
  PMIDType pmid;

  WWMSF *WWMSFptr = (WWMSF *) data; // typecast to known structure
  switch (WWMSFptr->SubStatusType) // Which command?
  {
    case CONF_FROM_BS: // request for configuration
      SendConfiguration(user);
      break;
    case MIC_MUTE_CMD:
      PPID2PMID((PMIDType *) pmid, user);

	  // save the request
      req = WWMSFptr->Sub.SetMicMute.MicMute & 0x000F;

      // if running a dual base system and if this headset is registered to this base, update the mixers
  	  // 0 is open to menu A, 1 is mute menu A, 2 is become OT menu A, 3 is open to menu B, 4 is mute menu B, 5 is become OT menu B
	  if ((base_station).DualBase && (user < MAX_Allowed_Users_Dual))
	  {
		if ((req == 0) || (req == 1) || (req == 2))
		  (base_station).LaneForChannel[getSpeechBufferIndex(pmid) >> 1] = DUAL_BASE_MENU_A;
		else
		  (base_station).LaneForChannel[getSpeechBufferIndex(pmid) >> 1] = DUAL_BASE_MENU_B;

		if ((req == 0) || (req == 2) || (req == 3) || (req == 5))
		  UpdateDualMenuMixers();

		// if it's on this base but it's NOT at this menu, notify other base and do nothing else
		if ((!FIRST_BASE && (((req & 0x000F) == 0) || ((req & 0x000F) == 1) || ((req & 0x000F) == 2)))
		  || (FIRST_BASE && (((req & 0x000F) == 3) || ((req & 0x000F) == 4) || ((req & 0x000F) == 5))))
		{
		  SendPCMCommand(PP_MIC_ind + (user << 4) + req);
		  break;
		}
	  }
	  // if not on this base and it's NOT at this menu, ignore the request the request
	  else if ((!FIRST_BASE && (((req & 0x000F) == 0) || ((req & 0x000F) == 1) || ((req & 0x000F) == 2)))
 	         || (FIRST_BASE && (((req & 0x000F) == 3) || ((req & 0x000F) == 4) || ((req & 0x000F) == 5))))
 	  {
		// not at this menu and not on this base; do nothing (should not get here)
		break;
	  }

      // 0 is open to menu A, 1 is mute menu A, 2 is become OT menu A, 3 is open to menu B, 4 is mute menu B, 5 is become OT menu B
	  if (((WWMSFptr->Sub.SetMicMute.MicMute & 0x000F) == 1) || ((WWMSFptr->Sub.SetMicMute.MicMute & 0x000F) == 4))
      {
		// closing a headset mic here !!!
    	(base_station).MicIsOn[user] = FALSE;
    	// check to see if any other headset MICs are on
    	for (i = 0; i < MAX_Allowed_Users; i++)
		{
		  if ((base_station).HeadsetIsOn[i] && (base_station).MicIsOn[i])
		  {
		    OkToTurnMicOff = FALSE;
		    i = MAX_Allowed_Users;
		  }
		}
		// if no other headset MICs are on and no vehicle is detected, turn off menu board MIC
		if (OkToTurnMicOff && !(base_station).VehicleDetectIsActive)
		{
		  if (!(base_station).UsingWirelessPost)
		  {
		    AFEDisablePostMicPath();							// disable DECT MIC input
		    GRILL_SPEAKER_OFF;									// mute the grill speaker
		    MENU_SPKR_AMP_OFF;									// mute post speaker (enables GREET audio path in to DECT MICP/N)
		  }
		  else
		  {
			BroadcastWirelessPostCmd((base_station).UsingWirelessPost - 1, 0x0000 + ((base_station).InboundVol << 4) + (base_station).CurrentOutboundVolume);
		  }
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
		// if no other headset MICs are on and a vehicle is present, turn on blinking LEDs again
		else if (OkToTurnMicOff && (base_station).VehicleDetectIsActive)
		{
		  if (!FIRST_BASE)
			BroadcastBlinkLED(7);								// 7 = menu B LED on
		  else
		    BroadcastBlinkLED(1);								// 1 = menu A LED on
		}
      }
      else
      {
  		// opening a headset mic here !!!
      	(base_station).MicIsOn[user] = TRUE;

		// 0 is open to menu A, 1 is mute menu A, 2 is become OT menu A, 3 is open to menu B, 4 is mute menu B, 5 is become OT menu B
		// if PP sends "2" (OT menu A) or "5" (OT menu B), then it is requesting to be the new OT
    	if (((WWMSFptr->Sub.SetMicMute.MicMute & 0x000F) == 2) || ((WWMSFptr->Sub.SetMicMute.MicMute & 0x000F) == 5))
    	{
    	  if (((base_station).OrderTakerID != 0xFF) && ((base_station).OrderTakerID != user))
    	  {
    		// cancel existing menu OT if one exists
    		if ((base_station).DualBase && ((base_station).OrderTakerID >= MAX_Allowed_Users_Dual))
      		  SendPCMCommand(ORDER_TAKER_ind + (base_station).OrderTakerID);		// cancel current menu OT on other base
    		else
      		  BroadcastOrderTaker((base_station).OrderTakerID, 0);					// cancel current menu OT on this base
    	  }
		  (base_station).OrderTakerID = user;
    	}

      	if ((((base_station).SystemMode & 0x0F) == AUTO_HANDS_FREE) && ((base_station).OrderTakerID == 0xFF))
      	{
      	  // when in Auto Hands Free mode, assign new order taker for this menu if current order taker doesn't exist
      	  (base_station).OrderTakerID = user;
      	  if ((base_station).DualBase && (user >= MAX_Allowed_Users_Dual))
      		SendPCMCommand(ORDER_TAKER_ind + 0x10 + (base_station).OrderTakerID);
      	  else
      		BroadcastOrderTaker((base_station).OrderTakerID, 1);
      	}

      	if ((base_station).VehicleDetectIsActive)
      	{
          // order is being taken, shut off all other LEDs if they were on
      	  if (!FIRST_BASE)
      		BroadcastBlinkLED(4);								// 4 = menu B LED off
      	  else
      		BroadcastBlinkLED(0);								// 0 = menu A LED off
      	}

		// 0 is open to menu A, 1 is mute menu A, 2 is become OT menu A, 3 is open to menu B, 4 is mute menu B, 5 is become OT menu B
    	if ((((base_station).SystemMode & 0x0F) != SPEED_TEAM) &&
    		 ((base_station).DisplayScreen != GREETER_SETUP) &&
    	     ((base_station).DisplayScreen != MESSAGE_SETUP1) &&
    	     ((base_station).DisplayScreen != MESSAGE_SETUP2))
    	{
		  AFESetGainInboundVolumeFP(NORMAL_INBOUND);
		  RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
		  if (!(base_station).UsingWirelessPost)
		  {
    	    MENU_SPKR_AMP_ON;									// make sure post speaker is on (enables BC5 audio path in to DECT MICP/N)
    	    if ((base_station).GrillSpeakerVolume)
    		  GRILL_SPEAKER_ON;									// turn on grill speaker
    	    if (!(base_station).VehicleDetectIsActive)
    		  usec_pause(35000);								// to avoid pop when opening post mic
    	    AFEEnablePostMicPath();								// enable DECT MIC input since a headset MIC is on
		  }
		  else
		  {
			BroadcastWirelessPostCmd((base_station).UsingWirelessPost - 1, 0x0100 + ((base_station).InboundVol << 4) + (base_station).CurrentOutboundVolume);
		  }
    	}
    	PPID2PMID((PMIDType *) pmid, user);
  		p_dynmixer6->weights[(getSpeechBufferIndex(pmid) >> 1)] = MIXER6_ATTEN;	// make sure channel to menu board speaker is on
  	   	if ((base_station).CarIsWaiting && (((base_station).SystemMode & 0x0F) != SPEED_TEAM))
    	{
    	  SET_CB_HI;											// drive CB high
    	  GREET_N_HI;											// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
    	  if ((base_station).MessageIsPlaying)
    		RunGreetClock(MESSAGE_PLAY_STOP, (base_station).MessageIsPlaying);
    	  else if ((base_station).MessageIsRecording)
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
      req = WWMSFptr->Sub.SetPage.Page & 0x000F;
      (base_station).PageMode[(getSpeechBufferIndex(pmid) >> 1)] = req;
      // if running a dual base system and this headset is registered to this base, update the mixer
	  if ((base_station).DualBase)
		UpdateDualMenuMixers();									// process dual base page request
	  else
		p_dynmixer6->weights[(getSpeechBufferIndex(pmid) >> 1)] = req ? 0x0000 : MIXER6_ATTEN;	// 1 is open to page, 0 is mute
      break;
    case VEHICLE_DETECT_CMD:
      ServiceVehicleDetect(WWMSFptr->Sub.SetVehicleDetect.VDinfo);
      break;
    case WIRELESS_POST_CMD:
      (base_station).UsingWirelessPost = user + 1;						// increment by 1 to use as a zero/non-zero flag
      general_startTimer(user, WIRELESS_POST_CMD, NULL, 0, 500);		// wireless post seems to need long delay before receiving
      p_dynmixer0->weights[6] = 0x0000;
      p_dynmixer1->weights[6] = 0x0000;
      p_dynmixer2->weights[6] = 0x0000;
      p_dynmixer3->weights[6] = 0x0000;
      p_dynmixer4->weights[6] = 0x0000;
      p_dynmixer5->weights[6] = 0x0000;
      break;
    default:
      break;
  }
}

UByte msf_ppstatus_ind_received(PPIDType user, UByte statusType, UByte * data, UByte data_length)
{
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
	WWMSFVal.SubStatusType = CONF_FROM_BS;
	WWMSFVal.Sub.SetConf.Debug1 = 0;              				// 0 is normal, 1 is bypass BC5 speaker path; see gdsp_BC5SpeakerPath()
	general_startTimer(user, READ_CONF, (UByte *)&WWMSFVal, sizeof(WWMSFVal), 200);
}

// 0 is no car on menu A, 10 is car on menu A + no beep, 11 is car on menu A + beep, 1 is no car on menu B, 20 is car on menu B + no beep, 21 is car on menu B + beep
void BroadcastCarWaiting(unsigned char value)
{
	WWMSFVal.SubStatusType = CAR_WAITING_CMD;
	WWMSFVal.Sub.SetCarWaiting.CarWaiting = value;
	msf_send_broadcast((UByte *)&WWMSFVal, sizeof(WWMSFVal), 0);
	if ((((base_station).DualBase == DUAL_BASE_MENU_A) && ((value == 0) || (value == 10) || (value == 11)))
	 || (((base_station).DualBase == DUAL_BASE_MENU_B) && ((value == 1) || (value == 20) || (value == 21))))
		SendPCMCommand(CAR_WAITING_ind + value);				// send "car waiting at menu x" command to other base
}

// 0 is menu A off, 1 is menu A RED, 2 is menu A YELLOW, 3 is menu A GREEN, 4 is menu B off, 5 is menu B RED, 6 is menu B YELLOW, 7 is menu B GREEN
void BroadcastBlinkLED(unsigned char value)
{
	WWMSFVal.SubStatusType = BLINK_LED_CMD;
	WWMSFVal.Sub.SetLEDColor.LEDColor = value;
	msf_send_broadcast((UByte *)&WWMSFVal, sizeof(WWMSFVal), 0);
	if ((((base_station).DualBase == DUAL_BASE_MENU_A) && ((value == 0) || (value == 1) || (value == 2) || (value == 3)))
	 || (((base_station).DualBase == DUAL_BASE_MENU_B) && ((value == 4) || (value == 5) || (value == 6) || (value == 7))))
		SendPCMCommand(BLINK_LED_ind + value);					// send "headset blink LED" command to other base
}

PPIDType start_BroadcastSystemModeState_ppid = 0;
void BroadcastSystemModeState(PPIDType user)
{
    start_BroadcastSystemModeState_ppid = 0;
	general_startTimer(user, SYSTEM_MODE_CMD, NULL, 0, 20);    	// wait for 200ms
	if (((base_station).DualBase == DUAL_BASE_MENU_A) && (user == (PPIDType) -1))
		SendPCMCommand(SYSTEM_MODE_ind + ((base_station).BC5Bypassed << 4) + (base_station).SystemMode);
}

void BroadcastOrderTaker(PPIDType user, unsigned char value)
{
	WWMSFVal.SubStatusType = SET_OT_CMD;
	WWMSFVal.Sub.SetOrderTaker.OrderTaker = value;
	general_startTimer(user, SET_OT_CMD, (UByte *)&WWMSFVal, sizeof(WWMSFVal), 50);
}

void BroadcastCalOffset(PPIDType user, unsigned char offset)
{
	WWMSFVal.SubStatusType = CAL_PP_CMD;
	WWMSFVal.Sub.SetPPOffset.PPOffset = offset;
	general_startTimer(user, CAL_PP_CMD, (UByte *)&WWMSFVal, sizeof(WWMSFVal), 50);
}

void BroadcastWirelessPostCmd(PPIDType user, WORD cmd)
{
	WWMSFVal.SubStatusType = WIRELESS_POST_CMD;
	WWMSFVal.Sub.SetVehicleDetect.VDinfo = cmd;
    msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
}

// manage mixers for dual menu systems
void UpdateDualMenuMixers()
{
	// update mixer0 (PP[0]): enable input channel only if it is open to this output channel's menu
	p_dynmixer0->weights[0] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer0->weights[1] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer0->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer0->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer0->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[0] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer0->weights[5] = ((base_station).LaneForChannel[0] == (base_station).DualBase ? 0x7FFF : 0x0000);
	p_dynmixer0->weights[6] = ((base_station).LaneForChannel[0] == (base_station).DualBase ? MIC_A_ATTEN : 0x0000);
	p_dynmixer0->weights[7] = ((base_station).LaneForChannel[0] == (base_station).DualBase ? 0x0000 : 0x7FFF);

	// update mixer1 (PP[1]): enable input channel only if it is open to this output channel's menu
	p_dynmixer1->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer1->weights[1] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer1->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer1->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer1->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[1] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer1->weights[5] = ((base_station).LaneForChannel[1] == (base_station).DualBase ? 0x7FFF : 0x0000);
	p_dynmixer1->weights[6] = ((base_station).LaneForChannel[1] == (base_station).DualBase ? MIC_A_ATTEN : 0x0000);
	p_dynmixer1->weights[7] = ((base_station).LaneForChannel[1] == (base_station).DualBase ? 0x0000 : 0x7FFF);

	// update mixer2 (PP[2]): enable input channel only if it is open to this output channel's menu
	p_dynmixer2->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer2->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer2->weights[2] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer2->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer2->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[2] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer2->weights[5] = ((base_station).LaneForChannel[2] == (base_station).DualBase ? 0x7FFF : 0x0000);
	p_dynmixer2->weights[6] = ((base_station).LaneForChannel[2] == (base_station).DualBase ? MIC_A_ATTEN : 0x0000);
	p_dynmixer2->weights[7] = ((base_station).LaneForChannel[2] == (base_station).DualBase ? 0x0000 : 0x7FFF);

	// update mixer3 (PP[3]): enable input channel only if it is open to this output channel's menu
	p_dynmixer3->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer3->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer3->weights[2] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer3->weights[3] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer3->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[3] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer3->weights[5] = ((base_station).LaneForChannel[3] == (base_station).DualBase ? 0x7FFF : 0x0000);
	p_dynmixer3->weights[6] = ((base_station).LaneForChannel[3] == (base_station).DualBase ? MIC_A_ATTEN : 0x0000);
	p_dynmixer3->weights[7] = ((base_station).LaneForChannel[3] == (base_station).DualBase ? 0x0000 : 0x7FFF);

	// update mixer4 (PP[4]): enable input channel only if it is open to this output channel's menu
	p_dynmixer4->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer4->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer4->weights[2] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer4->weights[3] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer4->weights[4] = ((base_station).LaneForChannel[5] == (base_station).LaneForChannel[4] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer4->weights[5] = ((base_station).LaneForChannel[4] == (base_station).DualBase ? 0x7FFF : 0x0000);
	p_dynmixer4->weights[6] = ((base_station).LaneForChannel[4] == (base_station).DualBase ? MIC_A_ATTEN : 0x0000);
	p_dynmixer4->weights[7] = ((base_station).LaneForChannel[4] == (base_station).DualBase ? 0x0000 : 0x7FFF);

	// update mixer5 (PP[5]): enable input channel only if it is open to this output channel's menu
	p_dynmixer5->weights[0] = ((base_station).LaneForChannel[0] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer5->weights[1] = ((base_station).LaneForChannel[1] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer5->weights[2] = ((base_station).LaneForChannel[2] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer5->weights[3] = ((base_station).LaneForChannel[3] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer5->weights[4] = ((base_station).LaneForChannel[4] == (base_station).LaneForChannel[5] ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer5->weights[5] = ((base_station).LaneForChannel[5] == (base_station).DualBase ? 0x7FFF : 0x0000);
	p_dynmixer5->weights[6] = ((base_station).LaneForChannel[5] == (base_station).DualBase ? MIC_A_ATTEN : 0x0000);
	p_dynmixer5->weights[7] = ((base_station).LaneForChannel[5] == (base_station).DualBase ? 0x0000 : 0x7FFF);

	// update mixer6 (this base SPKR): enable input channel only if it is open to this base's menu and not in PAGE mode
	p_dynmixer6->weights[0] = (((base_station).LaneForChannel[0] != (base_station).DualBase) || (base_station).PageMode[0] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer6->weights[1] = (((base_station).LaneForChannel[1] != (base_station).DualBase) || (base_station).PageMode[1] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer6->weights[2] = (((base_station).LaneForChannel[2] != (base_station).DualBase) || (base_station).PageMode[2] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer6->weights[3] = (((base_station).LaneForChannel[3] != (base_station).DualBase) || (base_station).PageMode[3] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer6->weights[4] = (((base_station).LaneForChannel[4] != (base_station).DualBase) || (base_station).PageMode[4] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer6->weights[5] = (((base_station).LaneForChannel[5] != (base_station).DualBase) || (base_station).PageMode[5] ? 0x0000 : MIXER6_ATTEN);

	// update mixer7 (to PCM[0], this menu to other base PPs): enable input channel only if it is open to this base's menu
	p_dynmixer7->weights[0] = ((base_station).LaneForChannel[0] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer7->weights[1] = ((base_station).LaneForChannel[1] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer7->weights[2] = ((base_station).LaneForChannel[2] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer7->weights[3] = ((base_station).LaneForChannel[3] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer7->weights[4] = ((base_station).LaneForChannel[4] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);
	p_dynmixer7->weights[5] = ((base_station).LaneForChannel[5] != (base_station).DualBase ? 0x0000 : (base_station).CurrentInboundVolumeMixerAtten);

	// update mixer8 (to PCM[1], other menu to other base SPKR): enable input channel only if it is open to the other base's menu and not in PAGE mode
	p_dynmixer8->weights[0] = (((base_station).LaneForChannel[0] == (base_station).DualBase) || (base_station).PageMode[0] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer8->weights[1] = (((base_station).LaneForChannel[1] == (base_station).DualBase) || (base_station).PageMode[1] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer8->weights[2] = (((base_station).LaneForChannel[2] == (base_station).DualBase) || (base_station).PageMode[2] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer8->weights[3] = (((base_station).LaneForChannel[3] == (base_station).DualBase) || (base_station).PageMode[3] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer8->weights[4] = (((base_station).LaneForChannel[4] == (base_station).DualBase) || (base_station).PageMode[4] ? 0x0000 : MIXER6_ATTEN);
	p_dynmixer8->weights[5] = (((base_station).LaneForChannel[5] == (base_station).DualBase) || (base_station).PageMode[5] ? 0x0000 : MIXER6_ATTEN);

	// update mixer9 (to PCM[2], other menu to other base PPs): enable input channel only if it is open to the other base's menu
	p_dynmixer9->weights[0] = ((base_station).LaneForChannel[0] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer9->weights[1] = ((base_station).LaneForChannel[1] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer9->weights[2] = ((base_station).LaneForChannel[2] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer9->weights[3] = ((base_station).LaneForChannel[3] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer9->weights[4] = ((base_station).LaneForChannel[4] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
	p_dynmixer9->weights[5] = ((base_station).LaneForChannel[5] != (base_station).DualBase ? (base_station).CurrentInboundVolumeMixerAtten : 0x0000);
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
		if ((base_station).MenuConfig > 1)
		  WWMSFVal.Sub.SetSystemMode.SystemMode |= (base_station).MenuConfig << 8;
		if ((base_station).BC5Bypassed)
		  WWMSFVal.Sub.SetSystemMode.SystemMode |= 0x8000;			// set BC5 "off" bit
        if ((base_station).HeadsetIsOn[start_BroadcastSystemModeState_ppid])
          msf_send_ppstatusReq(start_BroadcastSystemModeState_ppid, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
        start_BroadcastSystemModeState_ppid++;
        if ((!(base_station).DualBase && (start_BroadcastSystemModeState_ppid < MAX_Allowed_Users)) ||
             ((base_station).DualBase && (start_BroadcastSystemModeState_ppid < MAX_Allowed_Users_Dual)))
          general_startTimer(-1, SYSTEM_MODE_CMD, NULL, 0, 100);    // wait for 1s
	  }
	  else
	  {
		if ((base_station).ListenOnly[user] == 0x01)
		  WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + LISTEN_ONLY_MODE;
		else
		  WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + (base_station).SystemMode;
		if ((base_station).MenuConfig > 1)
		  WWMSFVal.Sub.SetSystemMode.SystemMode |= (base_station).MenuConfig << 8;
		if ((base_station).BC5Bypassed)
		  WWMSFVal.Sub.SetSystemMode.SystemMode |= 0x8000;			// set BC5 "off" bit
		msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
	  }
	}
	else if (subEvent == LISTEN_ONLY_MODE_CMD)
	{
	  WWMSFVal.SubStatusType = SYSTEM_MODE_CMD;
	  if ((base_station).ListenOnly[user] == 0x01)
		WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + LISTEN_ONLY_MODE;
	  else
		WWMSFVal.Sub.SetSystemMode.SystemMode = ((base_station).InboundVol << 4) + (base_station).SystemMode;
	  if ((base_station).MenuConfig > 1)
		WWMSFVal.Sub.SetSystemMode.SystemMode |= (base_station).MenuConfig << 8;
	  if ((base_station).BC5Bypassed)
		WWMSFVal.Sub.SetSystemMode.SystemMode |= 0x8000;			// set BC5 "off" bit
	  msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
	  if (!FIRST_BASE)
		general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);	// write current values to EEPROM
	}
	else if (subEvent == SET_OT_CMD)
	{
	  WWMSF *WWMSFptr = (WWMSF *) dataPtr; // typecast to known structure
	  WWMSFVal.SubStatusType = SET_OT_CMD;
	  WWMSFVal.Sub.SetOrderTaker.OrderTaker = WWMSFptr->Sub.SetOrderTaker.OrderTaker;
	  msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
	}
	else if (subEvent == CAL_PP_CMD)
	{
	  WWMSF *WWMSFptr = (WWMSF *) dataPtr; // typecast to known structure
	  WWMSFVal.SubStatusType = CAL_PP_CMD;
	  WWMSFVal.Sub.SetPPOffset.PPOffset = WWMSFptr->Sub.SetPPOffset.PPOffset;
	  msf_send_ppstatusReq(user, WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
	}
	else if (subEvent == READ_EEPROM)
	{
	  general_eeprom_read_req(EE_CUSTOMER_AREA, 5, 0);
	  general_startTimer(-1, READ_COUNTRY_EEPROM, NULL, 0, 5);
	}
	else if (subEvent == READ_COUNTRY_EEPROM)
	{
	  general_eeprom_read_req(EEP_NonGapExtFreqMode, 3, 3);
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
	  test[a++] = (base_station).AlangoProfile1;
	  test[a++] = (base_station).MenuConfig;
	  test[a++] = (base_station).DualBase;

	  result = general_eeprom_write_req(EE_WTDATA, test, a, 0);
	  ptr = StringPrint(StatusString, "****** eeprom write req result: ");
	  ptr = StrPrintDecByte(ptr, result);
	  ptr = StringPrint(ptr, " (for ");
	  ptr = StrPrintDecByte(ptr, a);
	  ptr = StringPrint(ptr, " bytes)");
	  PrintStatus(0, StatusString);
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

	  CopyByteToUartTxBuffer('\r');																				// send 3 CRs to make sure display is ready
	  CopyByteToUartTxBuffer('\r');
	  CopyByteToUartTxBuffer('\r');
	  CopyToUartTxBuffer((UByte *)"m startup1", 10);															// start display with parameters
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).DisplayIsLocked);								// e0 locked/unlocked state
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(((base_station).SystemMode & 0x0F) - 1);						// e1 mode
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).VehicleDetectIsActive ? 2 : 1);				// e2 menu A - car present or not
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).MenuConfig > 1 ? 1 : 0);						// e3 menu B - car present or not
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).DayTime);										// e4 Volume mode
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue(0);															// e5 detect current volume - not implemented
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).InboundVol);									// e6 inbound volume
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).GrillSpeakerVolume);							// e7 grill current volume
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeDay);						// e8 day volume
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).PostSpeakerVolumeNight);						// e9 night volume
	  CopyByteToUartTxBuffer('\r');																				// complete command string

	  CopyToUartTxBuffer((UByte *)"m startup2", 10);															// start display with parameters
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).MenuConfig > 1 ? (base_station).DualBase : 0);// eA volume menus info
	  CopyByteToUartTxBuffer(' ');	SendAsciiValue((base_station).MenuConfig);									// eB multi-menu
	  CopyByteToUartTxBuffer('\r');																				// complete command string

#ifdef FOR_TEST_BASE_ONLY
	  // !! THIS IS ONLY FOR IN-HOUSE TEST RELEASE !!
	  // use this code to activate calibration button on registration screen
	  usec_pause(300000);
	  CopyToUartTxBuffer((UByte *)"zs 50\r", 6);
	  CopyToUartTxBuffer((UByte *)"xs 128 0 0 479 271\r", 19);
	  CopyToUartTxBuffer((UByte *)"xm 128 main\r", 12);
	  CopyToUartTxBuffer((UByte *)"f 14x24\r", 8);
	  CopyToUartTxBuffer((UByte *)"t \"                       \" 13 100 T\r", 37);
	  CopyToUartTxBuffer((UByte *)"t \"         TEST BASE !!!!\" 13 100 T\r", 37);
	  CopyToUartTxBuffer((UByte *)"t \"        TAP TO CONTINUE\" 13 150 T\r", 37);
#endif

	  if (!(base_station).DualBase && !(base_station).BaseRTC && !(base_station).GreetRTC)
	  {
		PrintStatus(0, "Not running PCM bus for Real Time Clock nor Dual Lane");
		GdspUnhookVector(PCM_BUFFER_INT, DSP1); 				// unhook PCM[3] command interrupt handler
		GdspStop((unsigned short*)p_pcm_buffer);				// shut down p_pcm_buffer DP resource
	  }
	  else
	  {
		if ((base_station).DualBase)
		  PrintStatus(0, "Running PCM bus for dual base system");
		if ((base_station).BaseRTC || (base_station).GreetRTC)
		  PrintStatus(0, "Running PCM bus for Real Time Clock");
	  }
	  if (((base_station).DualBase == DUAL_BASE_MENU_A) && !(base_station).ARI2_Received)
		SendPCMCommand(REQ_FP_ARI_ind);
	}
	else if (subEvent == CHECK_TEOM)
	{
	  UByte P3_6 = (P3_DATA_REG & Px_6_DATA);					// P3[6] is TIMER_ALERT: input from external timer or WT greeter

	  // check TEOM during playback
	  if ((base_station).MessageIsPlaying && (P3_6 == 0x00))
	  {
		// check if we need to send button up command
		if ((base_station).MsgBeingEdited == (base_station).MessageIsPlaying)
		{
		  if (!FIRST_BASE)
			SendPCMCommand(GREETER_0x19_ind + 0x10);

		  if (((base_station).DisplayScreen == GREETER_SETUP)
		   || ((base_station).DisplayScreen == MESSAGE_SETUP1)
		   || ((base_station).DisplayScreen == MESSAGE_SETUP2))
		  {
			CopyToUartTxBuffer((UByte *)"ssb 43 0\r", 9);		// release play button
			CopyToUartTxBuffer((UByte *)"xe 43\r", 6);			// enable play button
			CopyToUartTxBuffer((UByte *)"xe 44\r", 6);			// enable record button
			CopyToUartTxBuffer((UByte *)"xd 45\r", 6);			// disable stop button
		  }
		  GREET_N_HI;											// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
		  MENU_SPKR_AMP_OFF;									// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		  GRILL_SPEAKER_OFF;									// mute grill speaker during playback
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
			if (!FIRST_BASE)
			  BroadcastCarWaiting(21);							// send "car waiting in menu B + beep" command
			else
			  BroadcastCarWaiting(11);							// send "car waiting in menu A + beep" command
		  }
		  SET_CB_HI;											// drive CB high
		  GREET_N_HI;											// drive GREET_N high connects DECT SPKR+/- audio path out to BC5
		  AFESetGainInboundVolumeFP(NORMAL_INBOUND);
		  RefreshOutboundVolume((base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight);
		  usec_pause(35000);									// to avoid pop when opening post mic
		  if ((base_station).SystemMode == SPEED_TEAM)
		  {
			AFEDisablePostMicPath();							// disable DECT MIC input for SPEED TEAM mode
			MENU_SPKR_AMP_OFF;									// mute the menu board speaker for SPEED TEAM mode (enables GREET audio path in to DECT MICP/N)
		  }
		  else if ((base_station).VehicleDetectIsActive)
		  {
			AFEEnablePostMicPath();								// enable DECT MIC input
			MENU_SPKR_AMP_ON;									// make sure post speaker is on (enables BC5 audio path in to DECT MICP/N)
			if ((base_station).GrillSpeakerVolume)
			  GRILL_SPEAKER_ON;									// turn on grill speaker
		  }
		  else
		  {
			AFEDisablePostMicPath();							// disable DECT MIC input
			MENU_SPKR_AMP_OFF;									// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		  }
	  	  OSStartTimer(VEHICLEDETECTTASKTIMER, 20); 			// 20 x 10ms = 200ms resume checking vehicle detector
		}
		(base_station).MessageIsPlaying = 0;
	  }
	  else if ((base_station).MessageIsPlaying && (P3_6 == 0x40))
	  {
		general_startTimer(-1, CHECK_TEOM, NULL, 0, 1);			// check TEOM again in 10ms
	  }
	  // check TEOM during recording
	  else if ((base_station).MessageIsRecording && (P3_6 == 0x40))
	  {
	    if (!FIRST_BASE)
		  SendPCMCommand(GREETER_0x19_ind + 0x20);

	    if (((base_station).DisplayScreen == GREETER_SETUP)
	     || ((base_station).DisplayScreen == MESSAGE_SETUP1)
	     || ((base_station).DisplayScreen == MESSAGE_SETUP2))
	    {
		  CopyToUartTxBuffer((UByte *)"ssb 44 0\r", 9);			// release record button
		  CopyToUartTxBuffer((UByte *)"xe 43\r", 6);			// enable play button
		  CopyToUartTxBuffer((UByte *)"xe 44\r", 6);			// enable record button
		  CopyToUartTxBuffer((UByte *)"xd 45\r", 6);			// disable stop button
	    }
		MENU_SPKR_AMP_OFF;										// mute post speaker during playback (enables GREET audio path in to DECT MICP/N)
		GRILL_SPEAKER_OFF;										// mute grill speaker during playback
		RefreshOutboundVolume(3);								// temporarily "normalize" for recording level
		AFESetGainInboundVolumeFP(GREET_COMFORT_VOL);			// temporarily set inbound for playback comfort
		RunGreetClock(MESSAGE_RECORD_STOP, (base_station).MessageIsRecording);	// send stop command to configure pins
	  }
	  else if ((base_station).MessageIsRecording && (P3_6 == 0x00))
	  {
		general_startTimer(-1, CHECK_TEOM, NULL, 0, 1);			// check TEOM again in 10ms
	  }
	}
	else if (subEvent == SETUP_SECOND_BASE)
	{
	  // tell first base that there is a second base and send FP_ARI[] data
	  SendPCMCommand(SECOND_BOARD_ind + (0 << 8) + (base_station).FP_ARI[0]);
	  SendPCMCommand(SECOND_BOARD_ind + (1 << 8) + (base_station).FP_ARI[1]);
	  SendPCMCommand(SECOND_BOARD_ind + (2 << 8) + (base_station).FP_ARI[2]);
	  SendPCMCommand(SECOND_BOARD_ind + (3 << 8) + (base_station).FP_ARI[3]);
	  SendPCMCommand(SECOND_BOARD_ind + (4 << 8) + (base_station).FP_ARI[4]);

	  // send volume settings to first base
	  SendPCMCommand(VOLUME_SETTINGS_B_ind + 0xB0 + (base_station).InboundVol);
	  SendPCMCommand(VOLUME_SETTINGS_B_ind + 0xC0 + (base_station).GrillSpeakerVolume);
	  SendPCMCommand(VOLUME_SETTINGS_B_ind + 0xD0 + (base_station).PostSpeakerVolumeDay);
	  SendPCMCommand(VOLUME_SETTINGS_B_ind + 0xE0 + (base_station).PostSpeakerVolumeNight);
	  SendPCMCommand(VOLUME_SETTINGS_B_ind + 0xF0 + (base_station).AlangoProfile1B);

	  // if greeter installed, send greeter data to first base
	  if ((base_station).GreeterInstalled)
	  {
		SendPCMCommand(GREETER_DATA_START_ind);
		SendPCMCommand(GREETER_DATA_STOP_ind);
	  }

	  // this is second base, we'll still use for debug purposes
	  general_startTimer(-1, SETUP_DISPLAY, NULL, 0, 50);    // wait for 500ms
	}
	else if (subEvent == DISPLAY_WT_DEBUG_INFO)
	{
	  WTInfoDebugScreen();
	}
	else if (subEvent == WIRELESS_POST_CMD)
	{
      BroadcastWirelessPostCmd((base_station).UsingWirelessPost - 1, 0x0200 + ((base_station).InboundVol << 4) + (base_station).CurrentOutboundVolume);
	}
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

    if ((base_station).DualBase && (fp_subscription_getNumberOfSubscriptions() >= MAX_Allowed_Users_Dual))
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
		    	PrintStatus(0, "both bases full - no more registrations allowed");
		    	CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);
		    }
		    else
		    	PrintStatus(0, "first base full - only allowing registrations on second base");
    	}
    	// stop allowing registrations to this base
    	(base_station).RegistrationAllowed = FALSE;
    }
    else if (!(base_station).DualBase && (fp_subscription_getNumberOfSubscriptions() >= MAX_Allowed_Users))
    {
    	PrintStatus(0, "base full - no more registrations allowed");
    	CopyToUartTxBuffer((UByte *)"ssb 28 0\r", 9);
    	// stop allowing registrations to this base
    	(base_station).RegistrationAllowed = FALSE;
    }
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
    int i, ii, a;
	UByte test[2];
	if (ppid == 0)
	{
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
		for (i = 0; i < 5; i++)
			(base_station).FP_ARI[i] = data[i];
		general_startTimer(-1, ENABLE_SPEECH_BUFFER, NULL, 0, 100);	// Next we enable the speech buffer
	}
	else if (ppid == 2)
	{
		test[0] = FW_REV_MAJOR;
		test[1] = FW_REV_MINOR;
		if (memcmp(data, test, 2))
		{
			// any values in EEPROM WTDATA area are for different version (or no version), save current version values now
			general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 100);	// write current values to EEPROM
		}
		else
		{
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
				(base_station).ListenOnly[i] = data[a++];
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
			(base_station).AlangoProfile1 = data[a++];
			(base_station).MenuConfig = data[a++];
			(base_station).DualBase = data[a++];

			if ((base_station).SystemMode > NOT_LOCKED)
				(base_station).SystemMode = HANDS_FREE;						// in case EEPROM was corrupted during a crash

			if ((base_station).DualBase)
				for (i = 0; i < 6; i++)
					(base_station).LaneForChannel[i] = DUAL_BASE_MENU_A;

			AFESetGainPP2PPMixer((base_station).InboundVol);				// update mixer weights in case InboundVol has changed from default

			general_startTimer(-1, WRITE_WT_DEBUG_EEPROM, NULL, 0, 1);		// update power on counter to EEPROM
		}

		ConvertHexSNtoAriSN((base_station).FP_ARI, (base_station).SerialNumber);

		if (!(base_station).DualBase)
		{
			PrintStatus(0, "Production - single base");
			(base_station).MenuConfig = 0;					// single menu ONLY
			DSP_PCM_CTRL_REG &= ~PCM_EN;					// disable PCM bus since it is not needed
		}
		else if ((base_station).DualBase == DUAL_BASE_MENU_A)
		{
			PrintStatus(0, "Production - dual base - menu A");
			if ((base_station).MenuConfig == 0)
				(base_station).MenuConfig = 1;				// single Menu STX
		}
		else if ((base_station).DualBase == DUAL_BASE_MENU_B)
		{
			PrintStatus(0, "Production - dual base - menu B");
			if ((base_station).MenuConfig == 0)
				(base_station).MenuConfig = 1;				// single Menu STX
		}
		else
		{
			PrintStatus(0, "Warning - DualBase variable invalid !!!!  changing to single base");
			(base_station).DualBase = 0;					// assume it should be single base
			(base_station).MenuConfig = 0;					// single menu ONLY
			DSP_PCM_CTRL_REG &= ~PCM_EN;					// disable PCM bus since it is not needed
		}

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
			(base_station).GreeterInstalled = FALSE;
			(base_station).GreeterActive = FALSE;
		}
		else
		{
			(base_station).GreeterInstalled = TRUE;
			CheckForActiveGreet();							// check if a greet is active
			CheckForActiveMessage();						// check if reminders or the alarm messages are active
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
		if ((base_station).GrillSpeakerVolume)
		{
			// increment MAX5407 (tap 31 "up" towards tap 0 direction) to decrease attenuation (increase volume)
			UPDOWN_GRILL_UP;								// set up for increment mode
			usec_pause(1);
			VOL_CS_HI;										// lock in increment mode
			for (i = 0; i < (base_station).GrillSpeakerVolume; i++)
			{
				UPDOWN_GRILL_LO;
				UPDOWN_GRILL_HI;
				usec_pause(1);
				UPDOWN_GRILL_LO;
			}
			VOL_CS_LO;										// freeze tap
		}

		// adjust p_gain_spkr_fp POST gain
		(base_station).CurrentOutboundVolume = (base_station).DayTime ? (base_station).PostSpeakerVolumeDay : (base_station).PostSpeakerVolumeNight;
		AFESetGainSpkrVolumeFP((base_station).CurrentOutboundVolume);

		if ((base_station).AlangoProfile1)
		{
			// profile 1 / MA10
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
			ALANGO_PROFILE_1;
		}
		else
		{
			// profile 0 / MA11
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
			ALANGO_PROFILE_0;
		}

		// check for presence of RTC on Base (then check on Greeter if necessary)

		SetupAccess1Bus();
		BASE_RTC_ON;										// look for RTC on base board first
		i = (ReadAccess1(RTC, 0x03) & 0x07);				// use day of week for a test
		WriteAccess1(RTC, 0x03, (8 - i));
		if ((ReadAccess1(RTC, 0x03) & 0x07) == (8 - i))
		{
			(base_station).BaseRTC = TRUE;
			WriteAccess1(RTC, 0x03, i);						// restore previous day of week
			if ((base_station).PowerOnCount < 2)
			{
				// initialize the RTC to January 1, 2014 and clear the control/status registers
				WriteAccess1(RTC, 0x00, 0x00);				// seconds
				WriteAccess1(RTC, 0x04, 0x01);				// day of month
				WriteAccess1(RTC, 0x05, 0x01);				// month
				WriteAccess1(RTC, 0x06, 0x0E);				// year
				WriteAccess1(RTC, 0x0E, 0x00);				// CONTROL
				WriteAccess1(RTC, 0x0F, 0x00);				// STATUS
				WriteAccess1(RTC, 0x10, 0x00);				// TRICKLE CHARGER
			}
			// set current time from RTC
			(base_station).DisplayTime.timeMinMSB = ReadAccess1(RTC, 0x01);
			(base_station).DisplayTime.timeMinLSB = ((base_station).DisplayTime.timeMinMSB & 0x0F);
			(base_station).DisplayTime.timeMinMSB = ((base_station).DisplayTime.timeMinMSB & 0xF0) >> 4;
			(base_station).DisplayTime.timeHourMSB = ReadAccess1(RTC, 0x02);
			(base_station).DisplayTime.timeHourLSB = ((base_station).DisplayTime.timeHourMSB & 0x0F);
			(base_station).DisplayTime.timeHourMSB = ((base_station).DisplayTime.timeHourMSB & 0xF0) >> 4;
			(base_station).CurrentDay = i - 1;				// base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
			BASE_PCM_ON;									// enable PCM pass through again
		}
		else
		{
			BASE_PCM_ON;
			if ((base_station).GreeterInstalled)
			{
				// look for RTC on greeter next
				(base_station).GreetRTC = TRUE;				// assume RTC is present
				RunGreetClock(MESSAGE_INIT, 2);				// switch Greeter mux to RTC if present
				i = (ReadAccess1(RTC, 0x03) & 0x07);		// use day of week for a test
				WriteAccess1(RTC, 0x03, (8 - i));
				if ((ReadAccess1(RTC, 0x03) & 0x07) == (8 - i))
				{
					WriteAccess1(RTC, 0x03, i);				// restore previous day of week
					if ((base_station).PowerOnCount < 2)
					{
						// initialize the RTC to January 1, 2014 and clear the control/status registers
						WriteAccess1(RTC, 0x00, 0x00);		// seconds
						WriteAccess1(RTC, 0x04, 0x01);		// day of month
						WriteAccess1(RTC, 0x05, 0x01);		// month
						WriteAccess1(RTC, 0x06, 0x0E);		// year
						WriteAccess1(RTC, 0x0E, 0x00);		// CONTROL
						WriteAccess1(RTC, 0x0F, 0x00);		// STATUS
						WriteAccess1(RTC, 0x10, 0x00);		// TRICKLE CHARGER
					}
					// set current time from RTC
					(base_station).DisplayTime.timeMinMSB = ReadAccess1(RTC, 0x01);
					(base_station).DisplayTime.timeMinLSB = ((base_station).DisplayTime.timeMinMSB & 0x0F);
					(base_station).DisplayTime.timeMinMSB = ((base_station).DisplayTime.timeMinMSB & 0xF0) >> 4;
					(base_station).DisplayTime.timeHourMSB = ReadAccess1(RTC, 0x02);
					(base_station).DisplayTime.timeHourLSB = ((base_station).DisplayTime.timeHourMSB & 0x0F);
					(base_station).DisplayTime.timeHourMSB = ((base_station).DisplayTime.timeHourMSB & 0xF0) >> 4;
					(base_station).CurrentDay = i - 1;		// base is 0-6:Mon-Sun; RTC is 1-7:Mon-Sun
					RunGreetClock(MESSAGE_INIT, 1);			// switch Greeter mux back to PCM pass through if present
				}
				else
				{
					RunGreetClock(MESSAGE_INIT, 1);			// switch Greeter mux back to PCM pass through if present
					(base_station).GreetRTC = FALSE;		// Greet RTC is not present
				}
			}
		}

		P1_SET_DATA_REG = Px_3_SET;							// drive BC5 RESETN high to bring BC5 up
		PrintStatus(0, "*** BC5 RESETN is HI ");

		SetupPCMBus();										// make sure PCM bus is set up in case ACCESSBUS was used for RTC

		if (base_station.DualBase)
			ConnectPCM();

		if (!FIRST_BASE)
			general_startTimer(-1, SETUP_SECOND_BASE, NULL, 0, 10);
		else
			general_startTimer(-1, SETUP_DISPLAY, NULL, 0, 50); // wait for 500ms
	}
	else if (ppid == 3)										// result of US vs EU setting
	{
		if (data[0] == 0x00)
			(base_station).IsUS = FALSE;
	}
	else if (ppid == 4)										// to restore original greeter settings for this base
	{
		a = 0;
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
	}
}

void fp_system_init()
{
  PrintStatus(0, "eeprom read req");
  general_startTimer(-1, READ_EEPROM, NULL, 0, 150);		// Request eeprom info in 1500ms, to avoid the answer is received in a task which is not ready
}
