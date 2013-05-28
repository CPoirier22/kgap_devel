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

extern UByte CBTIMERSEQTASK1TIMER;

extern wt_headset headset;

extern void PlaySoundPP(unsigned char index);
extern void SendMicMuteCmd(unsigned char value);

void CheckCallControlPP(UByte key_pressed)
{
	if (headset.Pager)
	{
		PrintStatus(0, "In Page Mode ... skipped");
		return;
	}

	if ((key_pressed & CALL_BUTTON) && (headset.SystemMode == LISTEN_ONLY_MODE))
	{
		PlaySoundPP(sound_z_listen_only);
		return;
	}
	else if (key_pressed & CALL_BUTTON)
	{
		if (headset.CBtimer)
		{
			// CB pressed < "DoublePressWindow" after previous CB press == double press: Lane B
			StopTimer(CBTIMERSEQTASK1TIMER);
			PlaySoundPP(sound_beep);
			PrintStatus(0, "Lane B active / Green LED on");
			headset.CBtimer = FALSE;
			headset.TakingOrder = TRUE;
			TurnOffRedLED;										// HI = Red LED off
			headset.RedLEDisOn = TRUE;
			TurnOnGreenLED;										// LO = Green LED on
			headset.GreenLEDisOn = TRUE;
		}
		else
		{
			if (!(headset.TakingOrder))
			{
				// CB first press == Lane A
				PrintStatus(0, "Lane A active / Red LED on");
				AFEEnableMicPathPP();
				SendMicMuteCmd(0);						// tell base we've turned on our MIC
				headset.TakingOrder = TRUE;
				headset.RedLEDisOn = TRUE;
				headset.VehicleAlert1 = FALSE;
				PlaySoundPP(sound_beep);
				TurnOnRedLED;								// LO = Red LED on

				if (headset.DualLane)
				{
					headset.CBtimer = TRUE;
					OSStartTimer(CBTIMERSEQTASK1TIMER, headset.DoublePressWindow);
				}
			}
			else
			{
				// CB pressed > "DoublePressWindow" after previous CB press == MIC off
				PlaySoundPP(sound_double_beep);
				AFEDisableMicPathPP();
				PrintStatus(0, "CB OFF / LED off");
				headset.TakingOrder = FALSE;
				TurnOffYellowLED;							// turn off LED completely
				headset.GreenLEDisOn = FALSE;
				headset.RedLEDisOn = FALSE;
				SendMicMuteCmd(1);						// tell base we've turned off our MIC
			}
		}
	}
	else if (headset.SystemMode == PUSH_TO_TALK)
	{
		// CB released == MIC off
		PlaySoundPP(sound_double_beep);
		AFEDisableMicPathPP();
		PrintStatus(0, "CB OFF / LED off");
		headset.TakingOrder = FALSE;
		TurnOffYellowLED;							// turn off LED completely
		headset.GreenLEDisOn = FALSE;
		headset.RedLEDisOn = FALSE;
		SendMicMuteCmd(1);						// tell base we've turned off our MIC
	}

	headset.LastButtonPressed = CALL_BUTTON;
}
