#include "../../../../api/include/pp/pp_subscription_callback.h"
#include "../../../../api/include/pp/pp_subscription_functions.h"
#include "../../../../api/include/common/common_general_functions.h"
#include "../../../../api/include/common/common_general_callback.h"
#include "../../../../api/include/common/common_hardware_functions.h"
#include "../../../../api/include/common/common_hardware_callback.h"
#include "../../../../api/include/pp/pp_msf_functions.h"
#include "../../../../api/include/pp/pp_msf_callback.h"
#include "../../../../api/include/pp/pp_module2module_functions.h"
#include "../../../../api/include/pp/pp_module2module_callback.h"
#include "../../../../api/include/pp/pp_voice_functions.h"
#include "../../../../../include/hlkgap/common/include/aformat.h"
#include "../../../../include/eeplayout.h"
#include "../../../../api/include/DSPSignalHandler.h"
#include "sound/sound.h"
#include "wentworth/subscription_pp.h"
#include "wentworth/fppp_common.h"
#include "wentworth/wentworth_pp.h"
#include "wentworth/afe.h"
#include "dsp/gdsp_all_inits.h"

extern UByte WENTWORTHTASKTIMER;
extern UByte OTTIMERSEQTASK1TIMER;

static UByte info_cnt = 0;

extern void StartTonegeneratorPP(unsigned int argsin,unsigned int argcos, unsigned char filterenabled);
extern void PlaySoundPP(unsigned char index);
extern void OSStartTimer(BYTE TimerId, WORD Time);
extern void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN);
extern void AFEDisableMicPathPP(void);
extern void SendPageCmd(unsigned char value);
extern void SendMicMuteCmd(unsigned char value);
extern void CheckCallControlPP(UByte key_pressed);

void pp_common_playsound_ack(UByte status)
{
  if (status != 0)
  {
    PrintStatus(0, "playback failed");
  }
  else
  {
    PrintStatus(0, "playback started");
  }
}

void pp_common_playsound_finished()
{

}

void pp_common_gpio_inputport_state_changed(gpio_port port, gpio_state state)
{
  char * ptr;
  ptr = StringPrint(StatusString, "input port changed: ");
  ptr = StrPrintHexByte(ptr, port);
  ptr = StringPrint(ptr, " value: ");
  ptr = StrPrintHexByte(ptr, state);
  PrintStatus(0, StatusString);
}

void pp_voice_offhook_ready()
{
  general_startTimer(0, 0x25, NULL, 0, 50);
}

void pp_voice_info_received(UByte infoType, char * info, UByte infoLength)
{
  if (infoType == 0xfe)
  {
    if (memcmp(info, "Enter number", 12) == 0)
    {
      general_startTimer(0, 0x25, NULL, 0, 50);
    }
    else if (memcmp(info, "Connected", 9) == 0)
    {
      module2moduleData data;
      data[0] = 0x11;
      data[1] = 0x22;
      data[2] = 0x33;
      /*general_startTimer(0,0x78,NULL,0,30*100); limit connect time to 30 seconds: demonstrate call disconnect
       pp_send_module2module(data); */
    }
  }
}
extern void PlayRingingMelody(int sound_index);
void pp_voice_incommingCall(char * from)
{
  PrintStatus(0, "Incoming call..");
  PlayRingingMelody(sound_ring_once);
  general_startTimer(0, 0x24, NULL, 0, 200);/*accept call after timeout*/
}

void pp_voice_call_released(UByte reason)
{
  SignalType* stopAudio;
  PrintStatus(0,"Call released");
  NewSignal(sizeof(SignalType), (void**) &stopAudio);
  SendSignal((SignalType*) stopAudio, DSP_PROCESS_ID, STOPAUDIO_EVENT, 0);

  general_startTimer(0, 0x7C, NULL, 0, 300);/* try to reconnect call*/
}

static UByte overlapDialingCnt = 0;
static char * overlapNumber = "7";

extern UByte bearerptrace;
extern int tonegenerator_running;
extern unsigned char base_locked;

extern void RequestSystemMode(void);
extern UByte get_locked_channel(void);

UByte pp_general_timeout(PPIDType user, UByte subEvent, UByte * dataPtr, UByte dataLength)
{
  char* ptr = StringPrint(StatusString, "General timeout[0x");
  ptr = StrPrintHexByte(ptr, subEvent);
  ptr = StringPrint(ptr, "]");
  PrintStatus(0, StatusString);
  if (subEvent == GET_SYSTEM_MODE)
  {
	if ((headset.SystemMode == UNREGISTERED) || (headset.SystemMode == NOT_LOCKED))
	{
PrintStatus(0, "######## requesting SYSTEM MODE and starting 0x16 timer from pp_general_timeout()");
	  // start timer to check system mode again in 2 seconds
	  general_startTimer(0, GET_SYSTEM_MODE, NULL, 0, 200);		// check again make sure we know what mode we're in
	  RequestSystemMode();										// ask base again what mode we're in since we didn't get an answer yet
	}
	else
	{
	  // just let timer expire since we know we have a system mode now
PrintStatus(0, "@@@@@@@ let 0x16 timer expire");
	}
  }
  else if (subEvent == 0x21)
  {
    pp_voice_call_user("1");
    PrintStatus(0, "calling 1 ...");
  }
  else if (subEvent == 0x22)
  {
    pp_voice_call_user("0");
    PrintStatus(0, "calling 0 ...");
  }
  else if (subEvent == 0x24)
  {
    pp_voice_call_user("");
  }
  else if (subEvent == 0x25)
  {
    if (overlapDialingCnt < strlen(overlapNumber))
    {
      pp_voice_sendKey(overlapNumber[overlapDialingCnt++]);
      general_startTimer(0, 0x25, NULL, 0, 50);
    }
  }
  else if (subEvent == 0x26)
  {
    pp_subscription_delete(1);
  }
  else if (subEvent == 0x27)
  {
    /*pp_msf_send_setup_ind("1");*/
    UByte data[5];
    memset(data, 0x44, 5);
    pp_msf_send_ppstatus_ind(0x20, data, 5);
  }
  else if (subEvent == 0x28)
  {
    pp_msf_send_setup_ind("1");
  }
  else if (subEvent == 0x78)
  {
    pp_voice_onhook();
  }
  else if (subEvent == 0x79)
  {
    StartTonegeneratorPP(0x5A83,0x5A83,0);
//    PlayRingingMelody(sound_ring_once);
    tonegenerator_running=0;
    general_startTimer(0, 0x7A, NULL, 0, 200);
  }
  else if (subEvent == 0x7A)
  {
    StartTonegeneratorPP(0x5A83,0x5A83,0);
//    PlayRingingMelody(sound_ring_once);
  }
  else if (subEvent == 0x7B)
  {
   	StartAutomaticSubscription();
  }
  else if (subEvent == 0x7C)
  {
    if (base_locked)
      pp_voice_call_user("");
    else
      general_startTimer(0, 0x7C, NULL, 0, 300);/* try to reconnect call*/
  }
  else if (subEvent == 0xA0)
  {
	AFEEnableMicPathPP();
  }
  else if (subEvent == 0xA1)
  {
	PlaySoundPP(sound_double_beep);
  }
  else if (subEvent == 0xA2)
  {
	AFEDisableMicPathPP();
  }
  else if (subEvent == 0xA3)
  {
	CheckCallControlPP(CALL_BUTTON);
  }
  else if (subEvent == TOGGLE_LED)
  {
	TurnOffYellowLED;
	headset.YellowLEDisOn = FALSE;
	if (headset.RedLEDisOn)
	{
	  headset.RedLEDisOn = FALSE;
	  TurnOnGreenLED;
	  headset.GreenLEDisOn = TRUE;
	}
	else
	{
	  headset.GreenLEDisOn = FALSE;
	  TurnOnRedLED;
	  headset.RedLEDisOn = TRUE;
	}
	general_startTimer(0, TOGGLE_LED, NULL, 0, 100);
  }
  else if (subEvent == TOGGLE_TB_FAIL_LED)
  {
	// when touch board fails to program, slowly blink RED/GREEN
	switch (headset.TouchBoardFail)
	{
	  case 0:
	  {
		// off -> RED
		TurnOnRedLED;
	    headset.RedLEDisOn = TRUE;
	    headset.TouchBoardFail = 1;
	    break;
	  }
	  case 1:
	  {
		// RED -> off
	    TurnOffYellowLED;
	    headset.RedLEDisOn = FALSE;
	    headset.YellowLEDisOn = FALSE;
	    headset.GreenLEDisOn = FALSE;
	    headset.TouchBoardFail = 2;
	    break;
	  }
	  case 2:
	  {
		// off -> GREEN
		TurnOnGreenLED;
		headset.GreenLEDisOn = TRUE;
		headset.TouchBoardFail = 3;
	    break;
	  }
	  case 3:
	  {
		// GREEN - off
	    TurnOffYellowLED;
	    headset.RedLEDisOn = FALSE;
	    headset.YellowLEDisOn = FALSE;
	    headset.GreenLEDisOn = FALSE;
	    headset.TouchBoardFail = 0;
	    break;
	  }
	}
	  general_startTimer(0, TOGGLE_TB_FAIL_LED, NULL, 0, 100);
  }
#ifdef ENABLE_CHANNEL_MESSAGES
  else if (subEvent == CHECK_CHANNEL)
  {
	if (headset.GreenLEDisOn && (headset.LEDCount++ > 3))
	{
	  TurnOffYellowLED;
	  headset.RedLEDisOn = FALSE;
	  headset.YellowLEDisOn = FALSE;
	  headset.GreenLEDisOn = FALSE;
	  headset.LEDCount = 0;
	}
	UByte channel_check = get_locked_channel();
	if (channel_check != headset.ChannelInfo)
	{
	  ptr = StringPrint(StatusString, "changed from Freq/Slot 0x");
	  ptr = StrPrintHexByte(ptr, headset.ChannelInfo);
	  ptr = StringPrint(ptr, " to 0x");
	  ptr = StrPrintHexByte(ptr, channel_check);
	  ptr = StringPrint(ptr, " ");
	  PrintStatus(0, StatusString);
	  headset.ChannelInfo = channel_check;
	  TurnOnGreenLED;
	  headset.GreenLEDisOn = TRUE;
	  headset.LEDCount = 1;
	}
	general_startTimer(0, CHECK_CHANNEL, NULL, 0, 500);	// check again in 5sec
  }
#endif
  else if (subEvent == CHECK_OFFSET)
  {
	// check for headset.GainVolume and headset.SpkrVolOffset offsets
	if (general_eeprom_read_req(EE_FREE2, 4, 0) == 1)
	  PrintStatus(0, "**** EE_FREE2 read failed");
  }
  else
  {
    return 0;
  }
  return 1;
}

WWMSF WWMSFVal; // Could be allocated on stack in function instead, but could also grow to be too large for stack allocation

void SendMicMuteCmd(unsigned char value)
{
  WWMSFVal.SubStatusType = MIC_MUTE_CMD;			// Command
  WWMSFVal.Sub.SetMicMute.MicMute = value;  		// set post MIC command 0 = open to menu A, 1 = is mute menu A, 2 is become OT menu A, 3 is open to menu B, 4 is mute menu B, 5 is become OT menu B
  pp_msf_send_ppstatus_ind(WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
}

void RequestSystemMode(void)
{
  WWMSFVal.SubStatusType = GET_SYSTEM_MODE; 		// Command
  WWMSFVal.Sub.GetSystemMode.SystemMode = (FW_REV_MAJOR << 8) + FW_REV_MINOR;	// use data to tell base what FW is running in PP
  pp_msf_send_ppstatus_ind(WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
}

void RequestConfFromBS(void)
{
  WWMSFVal.SubStatusType = CONF_FROM_BS; 			// Command
  WWMSFVal.Sub.SetConf.Debug1 = 0;					// data: don't care
  pp_msf_send_ppstatus_ind(WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
}

extern void gdsp_BC5SpeakerPath(unsigned char bypass);
// .Debug1 value is sent from FP and can be used by PP for anything we want ...
void HandleConfigurationFromBS(SubType *Sub)
{
  gdsp_BC5SpeakerPath(Sub->SetConf.Debug1); 		// Test only - can be removed or replaced
}

void SendPageCmd(unsigned char value)
{
  WWMSFVal.SubStatusType = PAGE_CMD; 				// Command
  WWMSFVal.Sub.SetPage.Page = value;  				// Page command: 0 is off, 1 is on
  pp_msf_send_ppstatus_ind(WENTWORTH_PACKET_ID, (UByte *)&WWMSFVal, sizeof(WWMSFVal));
}

void HandlePacketFromFP(UByte * data, UByte data_length)
{
  WWMSF *WWMSFptr = (WWMSF *) data; 				// typecast to known structure
  switch (WWMSFptr->SubStatusType) 					// Which command?
  {
    case CONF_FROM_BS:
      HandleConfigurationFromBS(&WWMSFptr->Sub);
      break;
    case CAR_WAITING_CMD:
      if ((headset.MenuA && ((WWMSFptr->Sub.SetCarWaiting.CarWaiting == 0) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 10) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 11)))
       || (!headset.MenuA && ((WWMSFptr->Sub.SetCarWaiting.CarWaiting == 1) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 20) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 21))))
      {
		headset.CarAtOrderPost = FALSE;
		headset.VehicleAlert = FALSE;
		headset.AlertCount = 0;
		TurnOffYellowLED;
		headset.RedLEDisBlinking = FALSE;
		headset.RedLEDisOn = FALSE;
		headset.GreenLEDisBlinking = FALSE;
		headset.GreenLEDisOn = FALSE;
		headset.YellowLEDisBlinking = FALSE;
		headset.YellowLEDisOn = FALSE;
		headset.TakingOrder = FALSE;
      }

      // listen for "other lane"
      if ((!headset.MenuA && ((WWMSFptr->Sub.SetCarWaiting.CarWaiting == 0) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 10) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 11)))
       ||  (headset.MenuA && ((WWMSFptr->Sub.SetCarWaiting.CarWaiting == 1) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 20) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 21))))
      {
  		headset.OtherLaneWaiting = 0;
      }

      switch (WWMSFptr->Sub.SetCarWaiting.CarWaiting)
      {
		case 0:												// CAR_WAITING_CMD - LANE A NO CAR
		  if (headset.MenuA)
		  {
			headset.CurrentLEDState = 0;
			if (headset.TakingOrder)
			{
			  PlaySoundPP(sound_double_beep);
			}
		  }
		  break;
		case 1:												// CAR_WAITING_CMD - LANE B NO CAR
		  if (!headset.MenuA)
		  {
		    headset.CurrentLEDState = 4;
		    if (headset.TakingOrder)
		    {
			  PlaySoundPP(sound_double_beep);
		    }
		  }
		  break;
		case 10:											// CAR_WAITING_CMD - LANE A + NO BEEP
		  if (headset.MenuA)
		  {
			headset.CarAtOrderPost = TRUE;
			headset.CurrentLEDState = 0;
		  }
		  break;
		case 20:											// CAR_WAITING_CMD - LANE B + NO BEEP
		  if (!headset.MenuA)
		  {
			headset.CarAtOrderPost = TRUE;
			headset.CurrentLEDState = 4;
		  }
		  break;
		case 11:											// CAR_WAITING_CMD - LANE A + BEEP
		  if (headset.MenuA)
		  {
			headset.CarAtOrderPost = TRUE;
			headset.CurrentLEDState = 1;
			if ((headset.SystemMode == AUTO_HANDS_FREE) && headset.OrderTaker)
			{
			  general_startTimer(0, 0xA3, NULL, 0, 60);		// pause 0.6s before opening MIC
			}
			else
			{
			  PlaySoundPP(sound_vehicle_detect_100ms);
			  headset.VehicleAlert = TRUE;
			  headset.AlertCount = 1;						// pause 9 170ms periods before beeping again
			  TurnOnRedLED;									// HI = Red LED on
			  headset.RedLEDisOn = TRUE;
			  headset.RedLEDisBlinking = TRUE;
			  OSStartTimer(WENTWORTHTASKTIMER, 50);			// 50 x 10ms = 0.5s before toggling
			}
		  }
		  else if (headset.SingleOT)
		  {
			headset.OtherLaneWaiting = MENU_A;
			PlaySoundPP(sound_vehicle_detect_100ms);		// play notification for lane A
			OSStartTimer(OTTIMERSEQTASK1TIMER, 400);		// check again in 4s
		  }
		  break;
		case 21:											// CAR_WAITING_CMD - LANE B + DOUBLE BEEP
		  if (!headset.MenuA)
		  {
		    headset.CarAtOrderPost = TRUE;
		    headset.CurrentLEDState = 7;
		    if ((headset.SystemMode == AUTO_HANDS_FREE) && headset.OrderTaker)
		    {
			  general_startTimer(0, 0xA3, NULL, 0, 60);		// pause 0.6s before opening MIC
		    }
		    else
		    {
		      PlaySoundPP(sound_double_beep);
		      headset.VehicleAlert = TRUE;
		      headset.AlertCount = 1;						// pause 9 170ms periods before beeping again
		      TurnOnGreenLED;								// HI = Green LED on
		      headset.GreenLEDisOn = TRUE;
		      headset.GreenLEDisBlinking = TRUE;
		      OSStartTimer(WENTWORTHTASKTIMER, 50);			// 50 x 10ms = 0.5s before toggling
		    }
		  }
		  else if (headset.SingleOT)
		  {
			headset.OtherLaneWaiting = MENU_B;
			PlaySoundPP(sound_double_beep);					// play notification for lane B
			OSStartTimer(OTTIMERSEQTASK1TIMER, 400);		// check again in 4s
		  }
		  break;
		default:
		  break;
      }
      if ((!headset.Pager && headset.MenuA && ((WWMSFptr->Sub.SetCarWaiting.CarWaiting == 0) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 10) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 11)))
       || (!headset.Pager && !headset.MenuA && ((WWMSFptr->Sub.SetCarWaiting.CarWaiting == 1) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 20) || (WWMSFptr->Sub.SetCarWaiting.CarWaiting == 21))))
      {
    	AFEDisableMicPathPP();								// shut off MIC if not PAGE mode
      }
      else if (headset.Pager)
      {
    	TurnOnRedLED;										// HI = Red LED on
    	headset.RedLEDisOn = TRUE;							// keep Red LED on in PAGE mode
      }
      break;
    case BLINK_LED_CMD:
      if (headset.SingleOT && (((WWMSFptr->Sub.SetLEDColor.LEDColor == 0) && !headset.MenuA) || ((WWMSFptr->Sub.SetLEDColor.LEDColor == 4) && headset.MenuA)))
    	headset.OtherLaneWaiting = 0;						// "other" lane is no longer waiting
	  if ((headset.TakingOrder == FALSE) && (headset.Pager == FALSE))
	  {
	    switch (WWMSFptr->Sub.SetLEDColor.LEDColor)
	    {
		  case 0:		// Lane 1 LED off
			if (headset.MenuA)
			{
		      headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOffYellowLED;								// LO = Red and Green LEDs off
			  headset.GreenLEDisBlinking = FALSE;
			  headset.GreenLEDisOn = FALSE;
			  headset.RedLEDisBlinking = FALSE;
			  headset.RedLEDisOn = FALSE;
			  headset.VehicleAlert = FALSE;
			}
		    break;
		  case 1:		// RED LED on
			if (headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOffYellowLED;								// LO = Red and Green LEDs off
			  headset.GreenLEDisBlinking = FALSE;
			  headset.GreenLEDisOn = FALSE;
		      TurnOnRedLED;									// HI = Red LED on
		      headset.RedLEDisBlinking = TRUE;
		      headset.RedLEDisOn = TRUE;
		      OSStartTimer(WENTWORTHTASKTIMER, 50);			// 50 x 10ms = 0.5s before toggling
			}
		    break;
		  case 2:		// YELLOW LED on
			if (headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOnYellowLED;								// HI = Red and Green LEDs on
			  headset.GreenLEDisBlinking = TRUE;
			  headset.GreenLEDisOn = TRUE;
			  headset.RedLEDisBlinking = TRUE;
			  headset.RedLEDisOn = TRUE;
			}
		    break;
		  case 3:		// GREEN LED on
			if (headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOffYellowLED;								// LO = Red and Green LEDs off
			  headset.RedLEDisBlinking = FALSE;
			  headset.RedLEDisOn = FALSE;
			  TurnOnGreenLED;								// HI = Green LED on
			  headset.GreenLEDisBlinking = TRUE;
			  headset.GreenLEDisOn = TRUE;
			}
		    break;
		  case 4:		// menu B LED off
			if (!headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOffYellowLED;								// LO = Red and Green LEDs off
			  headset.GreenLEDisBlinking = FALSE;
			  headset.GreenLEDisOn = FALSE;
			  headset.RedLEDisBlinking = FALSE;
			  headset.RedLEDisOn = FALSE;
			  headset.VehicleAlert = FALSE;
			}
		    break;
		  case 5:		// menu B RED LED on
			if (!headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOffYellowLED;								// LO = Red and Green LEDs off
			  headset.GreenLEDisBlinking = FALSE;
			  headset.GreenLEDisOn = FALSE;
		      TurnOnRedLED;									// HI = Red LED on
		      headset.RedLEDisBlinking = TRUE;
		      headset.RedLEDisOn = TRUE;
			}
		    break;
		  case 6:		// menu B YELLOW LED on
			if (!headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOnYellowLED;								// HI = Red and Green LEDs on
			  headset.GreenLEDisBlinking = TRUE;
			  headset.GreenLEDisOn = TRUE;
			  headset.RedLEDisBlinking = TRUE;
			  headset.RedLEDisOn = TRUE;
			}
		    break;
		  case 7:		// menu B GREEN LED on
			if (!headset.MenuA)
			{
			  headset.CurrentLEDState = WWMSFptr->Sub.SetLEDColor.LEDColor;
			  TurnOffYellowLED;								// LO = Red and Green LEDs off
			  headset.RedLEDisBlinking = FALSE;
			  headset.RedLEDisOn = FALSE;
			  TurnOnGreenLED;								// HI = Green LED on
			  headset.GreenLEDisBlinking = TRUE;
			  headset.GreenLEDisOn = TRUE;
			  OSStartTimer(WENTWORTHTASKTIMER, 50);			// 50 x 10ms = 0.5s before toggling
			}
			break;
		  default:
		    break;
	    }
	  }
	  break;
    case SYSTEM_MODE_CMD:
      headset.GainSpkrVolume = ((WWMSFptr->Sub.SetSystemMode.SystemMode & 0x00F0) >> 3) - 7;	// GainSpkrVolume = (base_station).InboundVol x 2 - 7 offset
      if ((WWMSFptr->Sub.SetSystemMode.SystemMode & 0x0F00) > 0x0100)
      {
    	headset.DualMenu = TRUE;
    	if (((WWMSFptr->Sub.SetSystemMode.SystemMode & 0x0F00) == 0x0200)
    	 || ((WWMSFptr->Sub.SetSystemMode.SystemMode & 0x0F00) == 0x0300))
    	{
    	  headset.SingleOT = TRUE;						// dual menus, 1OT
    	}
    	else
    	{
    	  headset.SingleOT = FALSE;						// dual menus, 2OTs
    	}
      }
      else
      {
    	headset.DualMenu = FALSE;
    	headset.MenuA = TRUE;
    	headset.SingleOT = FALSE;
    	if (headset.CurrentLEDState > 3)
		  headset.CurrentLEDState -= 4;
      }
      if (WWMSFptr->Sub.SetSystemMode.SystemMode & 0x8000)
      {
    	AFESetGainSpkrVolumePP(headset.SpkrVolOffset);	// set up pre-LSR gain
    	BC5BypassPP;
      }
      else
      {
    	BC5IsUsedPP;
    	AFESetGainSpkrVolumePP(12 + headset.SpkrVolOffset);	// set up pre-LSR gain
      }
      switch (headset.GainSpkrVolume)						// adjust summator accordingly:
      {														// in2_ptr dB = (InboundVol x -2) - 13.1
		case -7: headset.WavAtten = 0x1C53; break;			// -13.1dB (Inbound Volume = 0)
		case -5: headset.WavAtten = 0x1680; break;			// -15.1dB (Inbound Volume = 1)
		case -3: headset.WavAtten = 0x11DF; break;			// -17.1dB (Inbound Volume = 2)
		case -1: headset.WavAtten = 0x0E32; break;			// -19.1dB (Inbound Volume = 3)
		case  1: headset.WavAtten = 0x0B46; break;			// -21.1dB (Inbound Volume = 4)
		case  3: headset.WavAtten = 0x08F5; break;			// -23.1dB (Inbound Volume = 5)
		case  5: headset.WavAtten = 0x071D; break;			// -25.1dB (Inbound Volume = 6)
		case  7: headset.WavAtten = 0x05A6; break;			// -27.1dB (Inbound Volume = 7)
		case  9: headset.WavAtten = 0x047D; break;			// -29.1dB (Inbound Volume = 8)
		case 11: headset.WavAtten = 0x0390; break;			// -31.1dB (Inbound Volume = 9)
      }
      AFESetGainInboundVolumePP(headset.GainSpkrVolume + (headset.SpeakerVolume - 8));	// set up post summator gain
      // only play "SYSTEM MODE" announcement when it's system mode change and not a base inbound volume change
      if (headset.SystemMode != (WWMSFptr->Sub.SetSystemMode.SystemMode & 0x000F))
      {
	    headset.SystemMode = WWMSFptr->Sub.SetSystemMode.SystemMode & 0x000F;
	    headset.OrderTaker = FALSE;							// clear OT assignment on system mode change
	    switch (headset.SystemMode)
	    {
	      case HANDS_FREE:
	    	PlaySoundPP(sound_HFmode);
		    break;
	      case PUSH_TO_TALK:
	    	PlaySoundPP(sound_PTTmode);
		    if (headset.TakingOrder)
		    {
			  general_startTimer(0, 0xA1, NULL, 0, 200);	// wait for PTT to finish playing before playing double_beep
			  AFEDisableMicPathPP();
			  PrintStatus(0, "CB OFF / LED off");
			  headset.TakingOrder = FALSE;
			  TurnOffYellowLED;								// turn off LED completely
			  headset.RedLEDisOn = FALSE;
			  headset.YellowLEDisOn = FALSE;
			  headset.GreenLEDisOn = FALSE;
			  SendMicMuteCmd(1);							// tell base we've turned off our MIC
		    }
		    break;
	      case AUTO_HANDS_FREE:
	    	PlaySoundPP(sound_AHFmode);
	    	break;
	      case SPEED_TEAM:
		    PlaySoundPP(sound_STmode);
		    break;
	      case LISTEN_ONLY_MODE:
		    PlaySoundPP(sound_LISTENmode);
	        if (headset.TakingOrder)
		    {
	    	  general_startTimer(0, 0xA1, NULL, 0, 200);	// wait for LO to finish playing before playing double_beep
	    	  AFEDisableMicPathPP();
	    	  PrintStatus(0, "CB OFF / LED off");
	    	  headset.TakingOrder = FALSE;
	    	  TurnOffYellowLED;								// turn off LED completely
			  headset.RedLEDisOn = FALSE;
			  headset.YellowLEDisOn = FALSE;
			  headset.GreenLEDisOn = FALSE;
	    	  SendMicMuteCmd(1);							// tell base we've turned off our MIC
		    }
		    break;
	      default:
	        PrintStatus(0, "**** SYSTEM MODE = UNKNOWN ");
	        break;
	    }
      }
      break;
	case SET_OT_CMD:
	  if (WWMSFptr->Sub.SetOrderTaker.OrderTaker == 1)
		headset.OrderTaker = TRUE;
	  else
		headset.OrderTaker = FALSE;
	  break;
	case CAL_PP_CMD:
	  // headset.GainVolume has a range of -5 to +7 for +/- 6dB calibration
	  // headset.SpkrVolOffset has a range of -6 to +6 for +/- 6dB calibration
	  switch (WWMSFptr->Sub.SetPPOffset.PPOffset)
	  {
	    case 0:	// - PP MIC offset
		  if (headset.GainVolume > -5)
		    --headset.GainVolume;
		  AFESetVolume(headset.GainVolume);
		  break;
	    case 1:	// reset PP MIC offset
	      headset.GainVolume = 1;
	      AFESetVolume(headset.GainVolume);
	      break;
	    case 2:	// + PP MIC offset
		  if (headset.GainVolume < 7)
		    ++headset.GainVolume;
		  AFESetVolume(headset.GainVolume);
		  break;
	    case 3:	// - PP RCV offset
		  if (headset.SpkrVolOffset > -6)
		    --headset.SpkrVolOffset;
		  AFESetGainSpkrVolumePP(12 + headset.SpkrVolOffset);
		  break;
	    case 4:	// reset PP RCV offset
		  headset.SpkrVolOffset = 0;
		  AFESetGainSpkrVolumePP(12 + headset.SpkrVolOffset);
		  break;
	    case 5:	// + PP RCV offset
		  if (headset.SpkrVolOffset < 6)
		    ++headset.SpkrVolOffset;
		  AFESetGainSpkrVolumePP(12 + headset.SpkrVolOffset);
		  break;
	  }
	  // now set up EEPROM values
	  if (headset.GainVolume == 1)
	  {
		data[0] = 0xFF;
		data[1] = 0xFF;
	  }
	  else if (headset.GainVolume > 1)
	  {
		data[0] = 0x00;
		data[1] = headset.GainVolume - 1;
	  }
	  else
	  {
		data[0] = 0x01;
		data[1] = 1 - headset.GainVolume;
	  }
	  if (headset.SpkrVolOffset == 0)
	  {
		data[2] = 0xFF;
		data[3] = 0xFF;
	  }
	  else if (headset.SpkrVolOffset > 0)
	  {
		data[2] = 0x00;
		data[3] = headset.SpkrVolOffset;
	  }
	  else
	  {
		data[2] = 0x01;
		data[3] = 0 - headset.SpkrVolOffset;
	  }
	  general_eeprom_write_req(EE_FREE2, data, 4, 0);
	  break;
    default:
      break;
  }
}

void pp_msf_ppstatus_req_received(UByte statusType, UByte * data, UByte data_length)
{
  int i;
  char * tmpPtr;
  tmpPtr = StringPrint(StatusString, "ppstatus_req_received. Status: ");
  tmpPtr = StrPrintHexByte(tmpPtr, statusType);
  tmpPtr = StringPrint(tmpPtr, " Length: ");
  tmpPtr = StrPrintHexByte(tmpPtr, data_length);
  tmpPtr = StringPrint(tmpPtr, " Data:");
  for (i = 0; i < data_length; i++)
  {
    tmpPtr = StrPrintHexByte(tmpPtr, data[i]);
    tmpPtr = StringPrint(tmpPtr, ",");
  }
  PrintStatus(0, StatusString);

  if (statusType == WENTWORTH_PACKET_ID) // to avoid non approved messages
  {
    HandlePacketFromFP(data, data_length);
  }
}

void pp_msf_ppstatus_ind_ack()
{
  PrintStatus(0, "ppstatus_ind_ack received");
}

void pp_msf_release_received(UByte reason)
{
  _sprintf_(StatusString, "session released: %x", reason);
  PrintStatus(0, StatusString);
}

int jsjm2m = 0;

void pp_module2module_received(module2moduleData dataSrc, module2moduleData ackDst)
{
  ackDst[0] = dataSrc[0];
  ackDst[1] = dataSrc[1];
  ackDst[2] = dataSrc[2];
  /*PrintStatus(0,"pp_module2module_received"); */

  jsjm2m++;

  if (jsjm2m == 3)
  {
    PrintStatus(0, "send keys start");
    pp_msf_send_keypad_ind(1);
    pp_msf_send_keypad_ind(2);
    pp_msf_send_keypad_ind(3);
    pp_msf_send_keypad_ind(4);
    pp_msf_send_keypad_ind(5);
    PrintStatus(0, "send keys end");
  }
}

void pp_module2module_ack_received(module2moduleData optionalDataSrc)
{
  module2moduleData tmp;
  tmp[0] = 0x11;
  tmp[1] = 0x22;
  tmp[2] = info_cnt++;
  pp_send_module2module(tmp);
}

void pp_msf_DispReq_received(UByte setupSpec1, char * displayText, char * callbackNumber)
{
  if (info_cnt < 5)
  {
    info_cnt++;
    pp_msf_send_keypad_ind('1');
  }
}

void pp_msf_setupreq_format2_received(UByte setupSpec1, char * displayText, char * callbackNumber, UByte setupSpec2, UByte setupSpec3, alertConstructiontType alertConstruction, UByte displayTimeout, dateAndTimeType dateAndTime,
    UByte sessionEstablished)
{
  char* ptr;
  ptr = StringPrint(StatusString, "Msf2: ");
  ptr = StringPrint(ptr, displayText);
  ptr = StringPrint(ptr, " From : ");
  ptr = StringPrint(ptr, callbackNumber);
  PrintStatus(0, StatusString);

  if (setupSpec1 & 0x80 && !(setupSpec3 & MU_MASK)) /*session request received, mu not set*/
  {
    PrintStatus(0, "session request received, mu not set");
    pp_msf_send_connect_cfm();
  }

  info_cnt = 0;
}

void pp_msf_setupreq_format1_received(UByte setupSpec1, char * displayText, char * callbackNumber)
{
  _sprintf_(StatusString, "Msf: %s From : %s", displayText, callbackNumber);
  PrintStatus(0, StatusString);
}


extern void enableAudio();
extern char *getReadableARI(UByte* rfpi);
void pp_general_eeprom_read_res(UByte status, PPIDType ppid, UByte * data, UByte length)
{
  if (status == 1 && length == sizeof(WENTWORTHEEpromStruct))
  {
	PrintStatus(0, "EE_CUSTOMER_AREA read");
    char * readable;
    char * tmp = StatusString;
    memcpy((BYTE *) &WENTWORTHeepromData, data, length);

    if (WENTWORTHeepromData.action_after_logon == 0x22)
    {
      PrintStatus(0, "--- AMI TEST MODE ---");
      headset.IsInTestMode = TRUE;
      enableAudio();
      gdsp_BC5SpeakerPath(0x10);
    }

    /* Print */
    tmp = StringPrint(tmp, "ARI Received: ");
    tmp = StrPrintHexByte(tmp, WENTWORTHeepromData.BaseAri[0]);
    tmp = StringPrint(tmp, " ");
    tmp = StrPrintHexByte(tmp, WENTWORTHeepromData.BaseAri[1]);
    tmp = StringPrint(tmp, " ");
    tmp = StrPrintHexByte(tmp, WENTWORTHeepromData.BaseAri[2]);
    tmp = StringPrint(tmp, " ");
    tmp = StrPrintHexByte(tmp, WENTWORTHeepromData.BaseAri[3]);
    tmp = StringPrint(tmp, " ");
    tmp = StrPrintHexByte(tmp, WENTWORTHeepromData.BaseAri[4]);
    PrintStatus(0, StatusString);

    tmp = StatusString;
    tmp = StringPrint(tmp, "Action after logon: ");
    tmp = StrPrintHexByte(tmp, WENTWORTHeepromData.action_after_logon);
    PrintStatus(0, StatusString);

    readable = getReadableARI(WENTWORTHeepromData.BaseAri);
    tmp = StatusString;
    tmp = StringPrint(tmp, "readable ari: ");
    tmp = StringPrint(tmp, readable);
    PrintStatus(0, StatusString);
    /* End print*/

    ReadySubscription();

    mem_free(readable);
  }
  else if (status == 1 && length == 5)
  {
	PrintStatus(0, "EEPROM[0-5] read");
    memcpy((BYTE *) &headset.PP_IPEI, data, length);
    PrintStatus(0, "*** saved PP_IPEI ***");
    ConvertIpeiToSN(0, headset.SerialNumber, headset.PP_IPEI);
  }
  else if (status == 1 && length == 4)
  {
	PrintStatus(0, "*** EE_FREE2 read ***");
	if (data[0] != 0xFF)
	{
	  if (data[0] == 0)
		headset.GainVolume = 1 + data[1];
	  else
		headset.GainVolume = 1 - data[1];
	}
	else
	{
	  headset.GainVolume = 1;
	}
	if (data[2] != 0xFF)
	{
	  if (data[2] == 0)
		headset.SpkrVolOffset = data[3];
	  else
		headset.SpkrVolOffset = 0 - data[3];
	}
	else
	{
	  headset.SpkrVolOffset = 0;
	}
  }
}

void pp_msf_broadcast_received(UByte * data, UByte length){
	int i;
	char *tmp;
	tmp = StringPrint(StatusString, "*** pp_msf_broadcast_received:");
	for(i = 0; i < length; i++){
		tmp = StringPrint(tmp, " 0x");
		tmp = StrPrintHexByte(tmp, data[i]);
	}
	PrintStatus(0, StatusString);

	if (data[0] == CAR_WAITING_CMD || data[0] == BLINK_LED_CMD)
	{
	    HandlePacketFromFP(data, length);
	}
}

void pp_system_init()
{
  PrintStatus(0, "pp user application initialized....");
  general_eeprom_read_req(EE_CUSTOMER_AREA, sizeof(WENTWORTHEEpromStruct), 0);
  general_startTimer(0, CHECK_OFFSET, NULL, 0, 10);		// check for headset.GainVolume offset in 100ms
}

