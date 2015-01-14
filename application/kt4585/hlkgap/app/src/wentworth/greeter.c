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
 * $History:: greeter.c														  $	*
 *																				*
 * Initial Revision																*
 ********************************************************************************
 */

#include "../../../../../../include/os/include/mailprim.h"
#include "../../../../../../include/common/include/print_status.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/common/common_general_functions.h"

#include "wentworth_fp.h"
#include "fppp_common.h"

#define CLOCK_PULSE_WIDTH_DELAY		usec_pause(15)

extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

/*
 * Sends an 8-bit command to the greet board
 *
 * greet_cmd :			MESSAGE_PLAY_START, MESSAGE_PLAY_STOP,
 * 						MESSAGE_RECORD_START, MESSAGE_RECORD_STOP,
 * 						MESSAGE_INIT
 * greet_selection :	message number/channel to play/record
 * 						use greet_selection = 1 for MESSAGE_INIT and PCM pass through
 * 						use greet_selection = 2 for MESSAGE_INIT and RTC access
 * recording:			greet_data[0] is the QA or REC bit (LO = playback, HI = record)
 * mux control:			greet_data2[0] is the SET_RTC bit to control the PCM/RTC mux; 1 = RTC, 0 = PCM pass through
 *
 * See ISD1900 datasheet for PLAYBACK/RECORD timing diagrams on page 19 (Direct mode, fixed message configuration)
 */
void RunGreetClock(UByte greet_cmd, UByte greet_selection)
{
	if ((greet_cmd < MESSAGE_PLAY_START) ||
		(greet_cmd > MESSAGE_INIT) ||
		(greet_selection < 1) ||
		(greet_selection > NUM_OF_MESSAGES))
	{
		PrintStatus(0, "*** invalid arguments for RunGreetClock() ! *** ");
		return;
	}

	(base_station).GreetClockRunning = TRUE;
	SET_CLOCK_LO;

	UByte i, greet_data = 0, greet_data2 = 0, greet_data3 = 0, mask;

	switch (greet_cmd)
	{
		case MESSAGE_PLAY_START:
			greet_data = 0xFE, greet_data2 = 0xFE, greet_data3 = 0xFF;	// set Mn LO (HL edge starts playback) and keep QA LO (playback) and SET_RTC LO (PCM)
			GREET_N_LO;													// drive GREET_N low to enable MESSAGE audio path out to BC5
			if (greet_selection < 8)
				greet_data   = ~(0x01 | (1 << greet_selection));
			else if (greet_selection < 15)
				greet_data2 = ~(0x01 | (1 << (greet_selection - 7)));
			else if (greet_selection < 22)
				greet_data3 = ~(0x00 | (1 << (greet_selection - 14)));
			(base_station).MessageIsPlaying = greet_selection;			// flag which MESSAGE is playing
			break;
		case MESSAGE_PLAY_STOP:
			greet_data = 0xFE, greet_data2 = 0xFE, greet_data3 = 0xFF;	// set Mn LO (HL edge stops playback early) and keep QA LO (playback) and SET_RTC LO (PCM)
			GREET_N_HI;													// drive GREET_N high to disable MESSAGE audio path out to BC5
			if (greet_selection < 8)
				greet_data  = ~(0x01 | (1 << greet_selection));
			else if (greet_selection < 15)
				greet_data2 = ~(0x01 | (1 << (greet_selection - 7)));
			else if (greet_selection < 22)
				greet_data3 = ~(0x00 | (1 << (greet_selection - 14)));
			(base_station).MessageIsPlaying = 0;						// flag that MESSAGE is not playing
			break;
		case MESSAGE_RECORD_START:
			greet_data = 0xFF, greet_data2 = 0xFE, greet_data3 = 0xFF;	// set QA HI (record), Mn LO (HL to start recording), and keep SET_RTC LO (PCM)
			GREET_N_HI;													// drive GREET_N high to disable MESSAGE audio path out to BC5
			if (greet_selection < 8)
				greet_data  = ~(0x00 | (1 << greet_selection));
			else if (greet_selection < 15)
				greet_data2 = ~(0x01 | (1 << (greet_selection - 7)));
			else if (greet_selection < 22)
				greet_data3 = ~(0x00 | (1 << (greet_selection - 14)));
			(base_station).MessageIsRecording = greet_selection;		// flag which MESSAGE is recording
			break;
		case MESSAGE_RECORD_STOP:
			greet_data = 0xFF, greet_data2 = 0xFE, greet_data3 = 0xFF;	// set QA HI (record), Mn HI (LH to stop recording), and keep SET_RTC LO (PCM)
			GREET_N_HI;													// drive GREET_N high to disable MESSAGE audio path out to BC5
			(base_station).MessageIsRecording = 0;						// flag that MESSAGE is not recording
			break;
		case MESSAGE_INIT:
			GREET_N_HI;													// drive GREET_N high to disable MESSAGE audio path out to BC5
			greet_data  = 0xFE;											// set Mn  HI and QA LO to initialize device when not in use
			greet_data2 = (greet_selection == 1) ? 0xFE : 0xFF;			// set MnA HI to initialize device when not in use and SET_RTC LO (PCM) or HI (RTC)
			greet_data3 = 0xFF;											// set MnB HI to initialize device when not in use
			usec_pause(100);
			break;
	}

	// greet_data3[7:0] greet_data2[7:0] greet_data[7:0] looks like:
	// 	 23  22  21  20  19  18  17  16  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
	//	M7B M6B M5B M4B M3B M2B M1B M0B M7A M6A M5A M4A M3A M2A M1A RTC M7  M6  M5  M4  M3  M2  M1  QA
	// and I clock out M7B, M6B ...  => ... M2, M1 and then QA

	// MESSAGE_RECORD requires QA to be HI (low after the inverter) before selected Mn
	// so this loop only sets QA HI because otherwise QA is usually LO
	if (greet_cmd == MESSAGE_RECORD_START)
	{
		for (i = 24; i; i--)
		{
			if (i == 9)
				SET_MESSAGE_DATA_LO;	// set SET_RTC LO (PCM)
			else
				SET_MESSAGE_DATA_HI;	// set everything else HI
			CLOCK_PULSE_WIDTH_DELAY;
			SET_CLOCK_HI;				// LH clock edge
			CLOCK_PULSE_WIDTH_DELAY;
			if (i == 1)
				SET_MESSAGE_DATA_HI;	// set control bit HI to latch data bit
			else
				SET_MESSAGE_DATA_LO;	// set control bit LO
			CLOCK_PULSE_WIDTH_DELAY;
			SET_CLOCK_LO;				// HL clock edge clocks control bit
			CLOCK_PULSE_WIDTH_DELAY;
		}
	}

	// these loops send the greet_data3, greet_data2, and greet_data (selected Mn is LO)
	// all commands require Mn to be set LO
	for (i = 8; i; i--)
	{
		mask = (1 << (i - 1));
		if (greet_data3 & mask)			// set data before clock
			SET_MESSAGE_DATA_HI;
		else
			SET_MESSAGE_DATA_LO;
		CLOCK_PULSE_WIDTH_DELAY;
		SET_CLOCK_HI;					// LH clock edge clocks in data bit
		CLOCK_PULSE_WIDTH_DELAY;
		SET_MESSAGE_DATA_LO;			// set control bit LO
		CLOCK_PULSE_WIDTH_DELAY;
		SET_CLOCK_LO;					// HL clock edge clocks control bit
		CLOCK_PULSE_WIDTH_DELAY;
	}
	for (i = 8; i; i--)
	{
		mask = (1 << (i - 1));
		if (greet_data2 & mask)			// set data before clock
			SET_MESSAGE_DATA_HI;
		else
			SET_MESSAGE_DATA_LO;
		CLOCK_PULSE_WIDTH_DELAY;
		SET_CLOCK_HI;					// LH clock edge clocks in data bit
		CLOCK_PULSE_WIDTH_DELAY;
		SET_MESSAGE_DATA_LO;			// set control bit LO
		CLOCK_PULSE_WIDTH_DELAY;
		SET_CLOCK_LO;					// HL clock edge clocks control bit
		CLOCK_PULSE_WIDTH_DELAY;
	}
	for (i = 8; i; i--)
	{
		mask = (1 << (i - 1));
		if (greet_data & mask)			// set data before clock
			SET_MESSAGE_DATA_HI;
		else
			SET_MESSAGE_DATA_LO;
		CLOCK_PULSE_WIDTH_DELAY;
		SET_CLOCK_HI;					// LH clock edge clocks in data bit
		CLOCK_PULSE_WIDTH_DELAY;
		if (i == 1)
			SET_MESSAGE_DATA_HI;		// set control bit HI to latch data
		else
			SET_MESSAGE_DATA_LO;		// set control bit LO
		CLOCK_PULSE_WIDTH_DELAY;
		SET_CLOCK_LO;					// HL clock edge clocks control bit
		CLOCK_PULSE_WIDTH_DELAY;
	}

	// MESSAGE_PLAY_START/MESSAGE_PLAY_STOP requires a LH edge on selected Mn to finish the Mn low pulse
	// for MESSAGE_RECORD_STOP we want to set QA LO again (high after the inverter) for playback
	// so this loop sets Mn HI and QA LO
	if ((greet_cmd == MESSAGE_PLAY_START) ||
		(greet_cmd == MESSAGE_PLAY_STOP) ||
		(greet_cmd == MESSAGE_RECORD_STOP))
	{
		usec_pause(35000);				// 35ms pause for LO Mn pulse
		for (i = 24; i; i--)
		{
			if ((i == 9) || (i == 1))
				SET_MESSAGE_DATA_LO;	// set QA and SET_RTC LO (PCM)
			else
				SET_MESSAGE_DATA_HI;	// set everything else HI
			CLOCK_PULSE_WIDTH_DELAY;
			SET_CLOCK_HI;				// LH clock edge clocks in data bit
			CLOCK_PULSE_WIDTH_DELAY;
			if (i == 1)
				SET_MESSAGE_DATA_HI;	// set control bit HI to latch data
			else
				SET_MESSAGE_DATA_LO;	// set control bit LO
			CLOCK_PULSE_WIDTH_DELAY;
			SET_CLOCK_LO;				// HL clock edge clocks control bit
			CLOCK_PULSE_WIDTH_DELAY;
		}
	}

	SET_MESSAGE_DATA_LO;				// set control bit LO

	if ((base_station).MessageIsPlaying || (base_station).MessageIsRecording)
	{
		// for recording, TEOM TDeb = 30ms, so wait 50ms before starting to check for TEOM during a recording
		general_startTimer(-1, CHECK_TEOM, NULL, 0, 5);
	}

	(base_station).GreetClockRunning = FALSE;
}
