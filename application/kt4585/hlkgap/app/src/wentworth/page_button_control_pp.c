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
 * $History:: page_button_control_pp.c										  $	*
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

#include "../sound/sound.h"
#include "afe.h"
#include "wentworth_pp.h"
#include "fppp_common.h"

extern wt_headset headset;

extern void PlaySoundPP(unsigned char index);
extern void SendPageCmd(unsigned char value);
extern void HandlePacketFromFP(UByte * data, UByte data_length);

void CheckPageControlPP(UByte key_pressed)
{
	if (headset.TakingOrder)
	{
		PrintStatus(0, "In Call Mode ... PB press ignored");
		return;
	}

	if (key_pressed & PAGE_BUTTON)
	{
		if (!(headset.Pager))
		{
			// PB first press == Pager
			SendPageCmd(1);
			PlaySoundPP(sound_PAGEmode);
			TurnOffYellowLED;
			TurnOnRedLED;
			PrintStatus(0, "Page - on");
			headset.Pager = TRUE;
			general_startTimer(0, 0xA0, NULL, 0, 10);		// delay AFEEnableMicPathPP() 100ms until menu board speaker is muted
		}
	}
	else
	{
		// PB released == pager off
		general_startTimer(0, 0xA2, NULL, 0, 10);			// delay AFEDisableMicPathPP() 100ms to be consistent with previous AFEEnableMicPathPP()
		SendPageCmd(0);
		PlaySoundPP(sound_double_beep);
		PrintStatus(0, "Page - off");
		headset.Pager = FALSE;

		WWMSF WWMSFVal;
		WWMSFVal.SubStatusType = BLINK_LED_CMD;
		WWMSFVal.Sub.SetPage.Page = headset.CurrentLEDState;
		HandlePacketFromFP((UByte *)&WWMSFVal, sizeof(WWMSFVal));
	}

	headset.LastButtonPressed = PAGE_BUTTON;
}
