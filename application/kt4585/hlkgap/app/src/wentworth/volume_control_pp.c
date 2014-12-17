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
 * $History:: volume_control_pp.c											  $	*
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

extern wt_headset headset;

extern void PlaySoundPP(unsigned char index);

void CheckVolumeControlPP(UByte key_pressed)
{
	char * ptr = StringPrint(StatusString, "");
	UByte current_button = 0;

//	ptr = StringPrint(StatusString, "--- 0x");
//	ptr = StrPrintHexByte(ptr, key_pressed);
//	ptr = StringPrint(ptr, " --- ");
//	PrintStatus(0, StatusString);

	switch(key_pressed)
	{
		case 0x00:
			PrintStatus(0, " ---- ");
			break;
		case 0x02:
			PrintStatus(0, " V1 ");
			break;
		case 0x04:
			PrintStatus(0, " V2 ");
			break;
		case 0x06:
			PrintStatus(0, " V1 V2 ");
			break;
		case 0x08:
			PrintStatus(0, " V3 ");
			break;
		case 0x0A:
			PrintStatus(0, " V1 V3 ");
			break;
		case 0x0C:
			PrintStatus(0, " V2 V3 ");
			break;
		case 0x0E:
			PrintStatus(0, " V1 V2 V3 ");
			break;
		case 0x10:
			PrintStatus(0, " V4 ");
			break;
		case 0x12:
			PrintStatus(0, " V1 V4 ");
			break;
		case 0x14:
			PrintStatus(0, " V2 V4 ");
			break;
		case 0x16:
			PrintStatus(0, " V1 V2 V4 ");
			break;
		case 0x18:
			PrintStatus(0, " V3 V4 ");
			break;
		case 0x1A:
			PrintStatus(0, " V1 V3 V4 ");
			break;
		case 0x1C:
			PrintStatus(0, " V2 V3 V4 ");
			break;
		case 0x1E:
			PrintStatus(0, " V1 V2 V3 V4 ");
			break;
	}

	// always select the LSb button as a reference
	if (headset.CurrentHeadsetButtonStates & VOL1_BUTTON) current_button = VOL1_BUTTON;
	else if (headset.CurrentHeadsetButtonStates & VOL2_BUTTON) current_button = VOL2_BUTTON;
	else if (headset.CurrentHeadsetButtonStates & VOL3_BUTTON) current_button = VOL3_BUTTON;
	else if (headset.CurrentHeadsetButtonStates & VOL4_BUTTON) current_button = VOL4_BUTTON;

	if (key_pressed == 0)
	{
		if (headset.SwipeWaiting)
		{
			ptr = StringPrint(ptr, "****** ");
			if (headset.Volume_Swipe == SWIPE_UP)
			{
				ptr = StringPrint(ptr, "swipe up ");
				if (headset.SpeakerVolume == MAX_LSR_VOLUME)
					PlaySoundPP(sound_max);
				else
					PlaySoundPP(sound_volume_ascending);
			}
			else if (headset.Volume_Swipe == SWIPE_DOWN)
			{
				ptr = StringPrint(ptr, "swipe down ");
				if (headset.SpeakerVolume == MIN_LSR_VOLUME)
					PlaySoundPP(sound_min);
				else
					PlaySoundPP(sound_volume_descending);
			}
			else
			{
				ptr = StringPrint(ptr, "no swipe: volume 'taps' are ignored! ");
			}
			headset.SwipeWaiting = FALSE;
			headset.Volume_Swipe = 0;
			headset.LastButtonPressed = 0;
			PrintStatus(0, StatusString);
		}
		return;
	}


	if (headset.Volume_Swipe == 0)
	{
		// process swipe until 2 unique volume buttons are detected, ignore the rest of the current swipe

		int lsr_vol = headset.SpeakerVolume;		// 0:min   14:max

		// beginning of volume UP swipe (V1 -> V4)
		if ((current_button & VOL1_BUTTON) && (headset.LastButtonPressed == 0))
		{
			ptr = StringPrint(ptr, " V1 ****** ");
			headset.LastButtonPressed = VOL1_BUTTON;
		}

		// end of volume DOWN swipe (V4 -> V1)
		else if ((current_button & VOL1_BUTTON) && ((headset.LastButtonPressed == VOL2_BUTTON) || (headset.LastButtonPressed == VOL3_BUTTON) || (headset.LastButtonPressed == VOL4_BUTTON)))
		{
			ptr = StringPrint(ptr, " V1 ****** ");
			if (lsr_vol > MIN_LSR_VOLUME)
			{
				lsr_vol -= 2;
				AFESetGainInboundVolumePP(headset.GainSpkrVolume + (lsr_vol - 8));
			}
			headset.LastButtonPressed = VOL1_BUTTON;
			headset.Volume_Swipe = SWIPE_DOWN;
		}

		// beginning of volume DOWN swipe (V4 -> V1)
		else if ((current_button & VOL4_BUTTON) && (headset.LastButtonPressed == 0))
		{
			ptr = StringPrint(ptr, " V4 ****** ");
			headset.LastButtonPressed = VOL4_BUTTON;
		}

		// end of volume UP swipe (V1 -> V4)
		else if ((current_button & VOL4_BUTTON) && ((headset.LastButtonPressed == VOL2_BUTTON) || (headset.LastButtonPressed == VOL3_BUTTON) || (headset.LastButtonPressed == VOL4_BUTTON)))
		{
			ptr = StringPrint(ptr, " V4 ****** ");
			if (lsr_vol < MAX_LSR_VOLUME)
			{
				lsr_vol += 2;
				AFESetGainInboundVolumePP(headset.GainSpkrVolume + (lsr_vol - 8));
			}
			headset.LastButtonPressed = VOL4_BUTTON;
			headset.Volume_Swipe = SWIPE_UP;
		}

		// beginning of unknown volume swipe
		else if ((current_button & VOL2_BUTTON) && (headset.LastButtonPressed == 0))
		{
			ptr = StringPrint(ptr, " V2 ****** ");
			headset.LastButtonPressed = VOL2_BUTTON;
		}

		// middle of volume UP swipe (V1 -> V4)
		else if ((current_button & VOL2_BUTTON) && (headset.LastButtonPressed == VOL1_BUTTON))
		{
			ptr = StringPrint(ptr, " V2 ****** ");
			if (lsr_vol < MAX_LSR_VOLUME)
			{
				lsr_vol += 2;
				AFESetGainInboundVolumePP(headset.GainSpkrVolume + (lsr_vol - 8));
			}
			headset.LastButtonPressed = VOL2_BUTTON;
			headset.Volume_Swipe = SWIPE_UP;
		}

		// middle of volume DOWN swipe (V4 -> V1)
		else if ((current_button & VOL2_BUTTON) && ((headset.LastButtonPressed == VOL3_BUTTON) || (headset.LastButtonPressed == VOL4_BUTTON)))
		{
			ptr = StringPrint(ptr, " V2 ****** ");
			if (lsr_vol > MIN_LSR_VOLUME)
			{
				lsr_vol -= 2;
				AFESetGainInboundVolumePP(headset.GainSpkrVolume + (lsr_vol - 8));
			}
			headset.LastButtonPressed = VOL2_BUTTON;
			headset.Volume_Swipe = SWIPE_DOWN;
		}

		// beginning of unknown volume swipe
		else if ((current_button & VOL3_BUTTON) && (headset.LastButtonPressed == 0))
		{
			ptr = StringPrint(ptr, " V3 ****** ");
			headset.LastButtonPressed = VOL3_BUTTON;
		}

		// middle of volume UP swipe (V1 -> V4)
		else if ((current_button & VOL3_BUTTON) && ((headset.LastButtonPressed == VOL1_BUTTON) || (headset.LastButtonPressed == VOL2_BUTTON)))
		{
			ptr = StringPrint(ptr, " V3 ****** ");
			if (lsr_vol < MAX_LSR_VOLUME)
			{
				lsr_vol += 2;
				AFESetGainInboundVolumePP(headset.GainSpkrVolume + (lsr_vol - 8));
			}
			headset.LastButtonPressed = VOL3_BUTTON;
			headset.Volume_Swipe = SWIPE_UP;
		}

		// middle of volume DOWN swipe (V4 -> V1)
		else if ((current_button & VOL3_BUTTON) && (headset.LastButtonPressed == VOL4_BUTTON))
		{
			ptr = StringPrint(ptr, " V3 ****** ");
			if (lsr_vol > MIN_LSR_VOLUME)
			{
				lsr_vol -= 2;
				AFESetGainInboundVolumePP(headset.GainSpkrVolume + (lsr_vol - 8));
			}
			headset.LastButtonPressed = VOL3_BUTTON;
			headset.Volume_Swipe = SWIPE_DOWN;
		}

		if (lsr_vol < MIN_LSR_VOLUME)
			lsr_vol = MIN_LSR_VOLUME;
		else if (lsr_vol > MAX_LSR_VOLUME)
			lsr_vol = MAX_LSR_VOLUME;

		headset.SpeakerVolume = lsr_vol;
		headset.SwipeWaiting = TRUE;

		PrintStatus(0, StatusString);
	}
}
