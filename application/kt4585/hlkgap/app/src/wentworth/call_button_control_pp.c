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
 * $History:: call_button_control_pp.c										  $	*
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
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/pp/pp_msf_functions.h"
#include "../../../../../api/include/pp/pp_msf_callback.h"
#include "../../../../../../include/hlkgap/common/include/aformat.h"

#include "../dsp/gdsp_all_inits.h"
#include "../sound/sound.h"
#include "afe.h"
#include "wentworth_pp.h"
#include "fppp_common.h"

extern UByte OTTIMERSEQTASK1TIMER;

extern wt_headset headset;

extern void PlaySoundPP(unsigned char index);
extern void SendPageCmd(unsigned char value);
extern void SendMicMuteCmd(unsigned char value);

void CheckCallControlPP(UByte key_pressed)
{
	if (headset.DualMenu && headset.Pager && (headset.SystemMode == LISTEN_ONLY_MODE))
	{
		PrintStatus(0, "In Page Mode & LO Mode ... CB press/release ignored");
		return;
	}

	if (headset.DualMenu && headset.Pager && !headset.TakingOrder)
	{
		// CB pressed after PB press == assign headset to menu B
		SendPageCmd(0);
		headset.MenuA = FALSE;
		PrintStatus(0, "menu 2 active / Green LED on");
		headset.Pager = FALSE;
		TurnOffYellowLED;
		headset.RedLEDisOn = FALSE;
		headset.YellowLEDisOn = FALSE;
		headset.GreenLEDisOn = FALSE;
		SendMicMuteCmd(3);									// tell base we've turned on our MIC to menu B
		headset.TakingOrder = TRUE;
		headset.VehicleAlert = FALSE;
		PlaySoundPP(sound_double_beep);
		TurnOnGreenLED;
		headset.GreenLEDisOn = TRUE;
		if (headset.CurrentLEDState != 7)
			headset.CurrentLEDState = 4;					// update LED state in case PAGE is used
		if (headset.OtherLaneWaiting == MENU_B)
			headset.OtherLaneWaiting = 0;
		return;
	}

	if (headset.Pager)
	{
		if ((key_pressed & CALL_BUTTON) && ((headset.SystemMode == AUTO_HANDS_FREE) || headset.IsInTestMode))
		{
			// allow for re-assignment of Order Taker or to clear test mode
			PrintStatus(0, "In Page Mode ... CB press started OT timer");
			headset.OTtimer = TRUE;
			OSStartTimer(OTTIMERSEQTASK1TIMER, headset.OTDoublePressWindow);
		}
		else if (headset.OTtimer)
		{
			PrintStatus(0, "In Page Mode ... CB release stopped OT Timer");
			headset.OTtimer = FALSE;
			StopTimer(OTTIMERSEQTASK1TIMER);
		}
		else
			PrintStatus(0, "In Page Mode ... CB press/release ignored");
		return;
	}

	if ((key_pressed & CALL_BUTTON) && (headset.SystemMode == LISTEN_ONLY_MODE))
	{
		PrintStatus(0, "In LO Mode ... CB press ignored");
		PlaySoundPP(sound_z_listen_only);
		return;
	}

	if (key_pressed & CALL_BUTTON)
	{
		if (!(headset.TakingOrder))
		{
			// CB first press == menu A
			headset.MenuA = TRUE;
			PrintStatus(0, "menu A active / Red LED on");
			AFEEnableMicPathPP();
			SendMicMuteCmd(0);								// tell base we've turned on our MIC to menu A
			headset.TakingOrder = TRUE;
			headset.VehicleAlert = FALSE;
			PlaySoundPP(sound_beep);
			TurnOffYellowLED;								// LO = Red and Green LEDs off
			headset.RedLEDisOn = FALSE;
			headset.YellowLEDisOn = FALSE;
			headset.GreenLEDisOn = FALSE;
			TurnOnRedLED;									// LO = Red LED on
			headset.RedLEDisOn = TRUE;
			if (headset.CurrentLEDState != 3)
				headset.CurrentLEDState = 0;				// update LED state in case PAGE is used
			if (headset.OtherLaneWaiting == MENU_A)
				headset.OtherLaneWaiting = 0;
		}
		else
		{
			// CB pressed after previous CB press == MIC off
			PlaySoundPP(sound_double_beep);
			AFEDisableMicPathPP();
			PrintStatus(0, "CB OFF / LED off");
			headset.TakingOrder = FALSE;
			TurnOffYellowLED;								// turn off LED completely
			headset.RedLEDisOn = FALSE;
			headset.YellowLEDisOn = FALSE;
			headset.GreenLEDisOn = FALSE;
			if (headset.MenuA)
				SendMicMuteCmd(1);							// tell base we've turned off our MIC to menu A
			else
				SendMicMuteCmd(4);							// tell base we've turned off our MIC to menu B
		}
	}
	else if (headset.SystemMode == PUSH_TO_TALK)
	{
		// CB released == MIC off
		PlaySoundPP(sound_double_beep);
		AFEDisableMicPathPP();
		PrintStatus(0, "CB OFF / LED off");
		headset.TakingOrder = FALSE;
		TurnOffYellowLED;									// turn off LED completely
		headset.RedLEDisOn = FALSE;
		headset.YellowLEDisOn = FALSE;
		headset.GreenLEDisOn = FALSE;
		if (headset.MenuA)
			SendMicMuteCmd(1);								// tell base we've turned off our MIC to menu A
		else
			SendMicMuteCmd(4);								// tell base we've turned off our MIC to menu B
	}

	headset.LastButtonPressed = CALL_BUTTON;
}
