/********************************************************************************
 *********************************************************************************
 *                                                                               *
 *     E ENEEEEEEEEEEEE             CCCC CCC         TTTTTTT TTTTTTTTTT          *
 *     E EEEEEEEEEEEEEE          CCCCC  C CCCC             T TTTTT               *
 *     E EEEE                   CCCCC    C CCCC            T TTTTT               *
 *     E EEEE                  CCCCC      C CCCC           T TTTTT               *
 *     E EEEE                 CCCCC                        T TTTTT               *
 *     E EEEEEEEEEEEEEE      CCCCC                         T TTTTT               *
 *     E EEEEEEEEEEEEEE      C CCCC                        T TTTTT               *
 *     E EEEE                 C CCCC                       T TTTTT               *
 *     E EEEE                  C CCCC      CCCCC           T TTTTT               *
 *     E EEEEEEEEEEEEEE         C CCCC   CCCCC             T TTTTT               *
 *     E EEEEEEEEEEEEEE  OO      C CCCCCCCC         OO     T TTTTT     OO        *
 *                       OO                         OO                 OO        *
 *                                                                               *
 *     Electronic Communication Technology A/S.                                  *
 *     Sintrupvej 23, DK-8220 Brabrand, Tel.: +45 87441230                       *
 *     Website: www.ect.dk                                                       *
 *                                                                               *
 *********************************************************************************
 * $History:: wentworth_pp.c                                                   $ *
 *                                                                               *
 * Initial Revision                                                              *
 *********************************************************************************
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
#include "../../../../../../include/hlkgap/common/include/aformat.h"
#include "../../../../../../include/common/include/map_480_gcc.h"
#include "../../../../../api/include/common/common_general_functions.h"
#include "../sound/sound.h"
#include "afe.h"
#include "fppp_common.h"
#include "wentworth_pp.h"

//#define SetBits(a,f,d)	( SetWord( a, (GetWord(a)&(~(WORD)f)) | ((WORD)(d)<<SHIF(f)) ))

typedef struct
{
        PrimitiveType Primitive;
        UByte Data[5];
} HMMailType;

WENTWORTHEEpromStruct WENTWORTHeepromData;

UByte OTTIMERSEQTASK1;
UByte OTTIMERSEQTASK1TIMER;
UByte DIAGTIMERSEQTASK1;
UByte DIAGTIMERSEQTASK1TIMER;
UByte BC5TIMERSEQTASK1;
UByte BC5TIMERSEQTASK1TIMER;
UByte PPTIMERSEQTASK1;
UByte PPTIMERSEQTASK1TIMER;
UByte PPTOUCHTIMERSEQTASK1;
UByte PPTOUCHTIMERSEQTASK1TIMER;
UByte PPWATCHDOGTASK;
UByte PPWATCHDOGTASKTIMER;
UByte PPVEHICLEDETECTTASK;
UByte PPVEHICLEDETECTTASKTIMER;

wt_headset headset;

extern void PlayFinished(void);
extern void PlaySoundPP(unsigned char index);
extern void CheckVolumeControlPP(UByte);
extern void CheckCallControlPP(UByte);
extern void SendVehicleDetectCmd(unsigned char value);
extern void SendPageCmd(unsigned char value);
extern void SendMicMuteCmd(unsigned char value);
extern void CheckPageControlPP(UByte);
extern void InitMicMuteHandling(void);
extern void RequestConfFromBS(void);
extern UByte get_locked_channel(void);

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

UByte spi_write_one_byte(UByte spi_tx_data)
{
	UByte spi_rx_data;

	SPI_EN_LO;

	SPI_RX_TX_REG0 = spi_tx_data;
	while (SPI_CTRL_REG & SPI_TXH) { }							// wait until Tx buffer clears
	while (!(SPI_CTRL_REG & SPI_INT_BIT)) { }					// wait until Rx buffer fills
	spi_rx_data = SPI_RX_TX_REG0;
	SPI_CLEAR_INT_REG = 0;

	SPI_EN_HI;
	usec_pause(400);

	return spi_rx_data;
}

void spi_write_bytes(UByte *data, UByte data_length)
{
	int i;

	SPI_EN_LO;

	for (i = 0; i < data_length; i++)
	{
		SPI_RX_TX_REG0 = data[i];
		while (SPI_CTRL_REG & SPI_TXH) { }						// wait until Tx buffer clears
		while (!(SPI_CTRL_REG & SPI_INT_BIT)) { }				// wait until Rx buffer fills
		SPI_CLEAR_INT_REG = 0;
		usec_pause(400);
	}

	SPI_EN_HI;
	usec_pause(10000);											// pause to reset SPI slave for next SPI command

	return;
}

void check_touch_board(void)
{
	headset.TouchBoardStatus = 1;
	char *ptr = StringPrint(StatusString, "touch board status: ");

	spi_write_one_byte(0xC9);									// get Device ID
	if (spi_write_one_byte(0x00) != 0x59)
	{
		// slow the SPI bus down and try again
		SPI_CTRL_REG &= ~(0x0001);								// disable SPI bus
		SPI_CTRL_REG = (SPI_CLK | SPI_POL | SPI_PHA);			// SPI bus @ 375kHz
		SPI_CTRL_REG |= (0x0001);								// enable SPI bus

		spi_write_one_byte(0xC9);								// get Device ID
		if (spi_write_one_byte(0x00) != 0x59)
		{
			// note: older headsets with the SPI lines cut will fail this and continue on normally
			ptr = StringPrint(ptr, " invalid DeviceID - unless older \"cut trace\" headset, check touch board connection !!! ");
			PrintStatus(0, StatusString);
			headset.TouchBoardStatus = 2;
			TurnOffYellowLED;
		    TurnOnRedLED;										// LO = Red LED on
		    headset.TouchBoardFail = 1;
		    headset.TouchBoardCode = 1;							// Device ID fail
		    OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 10);
			return;
		}
	}

	spi_write_one_byte(0xC2);									// Device Status
	if ((spi_write_one_byte(0x00) & 0x04) == 0)					// check EEPROM status bit
	{
		spi_write_one_byte(0xC3);								// EEPROM CRC
		if ((spi_write_one_byte(0x00) & 0x47) == 0x47)			// check EEPROM CRC
		{
			if ((SPI_CTRL_REG & SPI_CLK) == 0x00)
				ptr = StringPrint(ptr, " valid EEPROM status and CRC @667kHz SPI bus - no programming necessary ");
			else
				ptr = StringPrint(ptr, " valid EEPROM status and CRC @375kHz slower SPI bus - no programming necessary ");
			PrintStatus(0, StatusString);
			headset.TouchBoardStatus = 2;
			OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 10);
			return;
		}
	}

	UByte data[43] = { 0x01,									// Send Setups
					   0xA0, 0x00, 0x28, 0x12, 0x06, 0x06,
			           0x12, 0x00, 0x00, 0x80, 0x80, 0x80,
			           0x80, 0x80, 0x80, 0x80, 0x00, 0x7F,
			           0x00, 0x00, 0x1D, 0x16, 0x16, 0x16,
			           0x12, 0x1E, 0x2A, 0x2A, 0x2A, 0x2A,
			           0x00, 0x7A, 0x7F, 0x7A, 0x7A, 0x7A,
			           0x7A, 0x7F, 0x7A, 0x7A, 0x7A, 0x7A };
	spi_write_bytes(data, sizeof(data));

	spi_write_one_byte(0xC4);									// get RAM CRC
	if (spi_write_one_byte(0x00) == 0x47)
	{
		spi_write_one_byte(0x0A);								// Store to EEPROM
		OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 25); 			// 25 x 10ms = 250ms for Store to EEPROM to complete
		return;
	}
	else
	{
		if ((SPI_CTRL_REG & SPI_CLK) == 0x00)
		{
			// slow the SPI bus down and try again
			SPI_CTRL_REG &= ~(0x0001);							// disable SPI bus
			SPI_CTRL_REG = (SPI_CLK | SPI_POL | SPI_PHA);		// SPI bus @ 375kHz
			SPI_CTRL_REG |= (0x0001);							// enable SPI bus

			UByte data[43] = { 0x01,							// Send Setups
							   0xA0, 0x00, 0x28, 0x12, 0x06, 0x06,
							   0x12, 0x00, 0x00, 0x80, 0x80, 0x80,
							   0x80, 0x80, 0x80, 0x80, 0x00, 0x7F,
							   0x00, 0x00, 0x1D, 0x16, 0x16, 0x16,
							   0x12, 0x1E, 0x2A, 0x2A, 0x2A, 0x2A,
							   0x00, 0x7A, 0x7F, 0x7A, 0x7A, 0x7A,
							   0x7A, 0x7F, 0x7A, 0x7A, 0x7A, 0x7A };
			spi_write_bytes(data, sizeof(data));

			spi_write_one_byte(0xC4);							// get RAM CRC
			if (spi_write_one_byte(0x00) == 0x47)
			{
				spi_write_one_byte(0x0A);						// Store to EEPROM
				OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 25); 	// 25 x 10ms = 250ms for Store to EEPROM to complete
				return;
			}
			else
			{
				ptr = StringPrint(ptr, " invalid RAM CRC after programming @667kHz and @375kHz ");
				PrintStatus(0, StatusString);
				TurnOffYellowLED;
			    TurnOnRedLED;									// LO = Red LED on
			    headset.TouchBoardFail = 1;
			    headset.TouchBoardCode = 2;						// RAM fail
				return;
			}
		}
		else
		{
			ptr = StringPrint(ptr, " invalid RAM CRC after programming @375kHz ");
			PrintStatus(0, StatusString);
			TurnOffYellowLED;
		    TurnOnRedLED;										// LO = Red LED on
		    headset.TouchBoardFail = 1;
		    headset.TouchBoardCode = 2;							// RAM fail
			return;
		}
	}
}

void finish_programming_touch_board(void)
{
	char *ptr = StringPrint(StatusString, "touch board status: ");

	spi_write_one_byte(0xC3);									// get EEPROM CRC
	if (spi_write_one_byte(0x00) == 0x47)
	{
		if ((SPI_CTRL_REG & SPI_CLK) == 0x00)
			ptr = StringPrint(ptr, " EEPROM programming SUCCESSFUL @667kHz ");
		else
			ptr = StringPrint(ptr, " EEPROM programming SUCCESSFUL @375kHz ");
	}
	else
	{
		if ((SPI_CTRL_REG & SPI_CLK) == 0x00)
		{
			// slow the SPI bus down and try again
			SPI_CTRL_REG &= ~(0x0001);							// disable SPI bus
			SPI_CTRL_REG = (SPI_CLK | SPI_POL | SPI_PHA);		// SPI bus @ 375kHz
			SPI_CTRL_REG |= (0x0001);							// enable SPI bus

			spi_write_one_byte(0xC3);							// get EEPROM CRC
			if (spi_write_one_byte(0x00) == 0x47)
				ptr = StringPrint(ptr, " EEPROM programming SUCCESSFUL @375kHz ");
		}
		else
		{
			ptr = StringPrint(ptr, " RAM programming successful, but EEPROM programming not successful @375kHz ");
		    headset.TouchBoardCode = 3;							// RAM ok, EEPROM fail
		}
	}
	PrintStatus(0, StatusString);
    headset.TouchBoardStatus = 2;
    OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 10);
}

void check_touch_pins(void)
{
  // headset not in a call yet, and not in test mode, so ignore button presses
  if (((headset.SystemMode == UNREGISTERED) || (headset.SystemMode == NOT_LOCKED)) && !headset.IsInTestMode) return;

  UByte key_pressed = 0x00;
  UByte changed_keys = 0x00;

  // pressed keys: HIGH in P1_DATA_REG; HIGH in key_pressed
  key_pressed = (P1_DATA_REG & 0x003F) & (PAGE_BUTTON | VOL4_BUTTON | VOL3_BUTTON | VOL2_BUTTON | CALL_BUTTON);		// ignore V1

  // save previous states
  headset.PreviousHeadsetButtonStates = headset.CurrentHeadsetButtonStates;

  // save current states
  headset.CurrentHeadsetButtonStates = key_pressed;

  // determine which keys have changed state
  changed_keys = key_pressed ^ headset.PreviousHeadsetButtonStates;

  // do nothing if key states have not changed
  if (changed_keys == 0) return;

  if (WENTWORTHTASK!=0xFF) // (-1) Important if we by chance forget to start this task, then the application will hang
  {
	if (changed_keys & CALL_BUTTON)
	  CheckCallControlPP(key_pressed);
	if (changed_keys & PAGE_BUTTON)
	  CheckPageControlPP(key_pressed);
	if ((changed_keys & VOL1_BUTTON) || (changed_keys & VOL2_BUTTON) || (changed_keys & VOL3_BUTTON) || (changed_keys & VOL4_BUTTON))
	  CheckVolumeControlPP(key_pressed);
  }
}

static void wentworth_pptask(MailType * MailPtr)
{
	HMMailType *msg_ptr=(HMMailType *)MailPtr; // HM reuse a MailType - we just need to get the first couple of bytes after the primitive
	switch (MailPtr->Primitive)
	{
		case INITTASK:
			break;
		case HM_Filler_D2:
			// Data[0]: 1 = Playback_finished (from void PlaybackInt(WORD intvec))
			if (msg_ptr->Data[0]==1)
				PlayFinished();
			break;
		case TIMEOUT:
			// manage LED blinking and Alert tone for vehicle detect
			if (headset.CarAtOrderPost && (headset.TakingOrder == FALSE) && (headset.Pager == FALSE))
			{
				// check if nine 170ms periods has passed
				if (headset.AlertCount > 8)
				{
					if (headset.VehicleAlert && !headset.MenuA)
						PlaySoundPP(sound_double_beep);
					else if (headset.VehicleAlert)
						PlaySoundPP(sound_vehicle_detect_100ms);
					headset.AlertCount = 1;
				}
				else
				{
					headset.AlertCount++;
				}

				// if LEDs are blinking due to vehicle detect
				if (headset.RedLEDisBlinking)
				{
					if (headset.AlertCount > 3)
					{
						TurnOffYellowLED;
						headset.RedLEDisOn = FALSE;
						headset.YellowLEDisOn = FALSE;
						headset.GreenLEDisOn = FALSE;
					}
					else
					{
						TurnOnRedLED;
						headset.RedLEDisOn = TRUE;
						headset.YellowLEDisOn = FALSE;
						headset.GreenLEDisOn = FALSE;
					}
				}
				else if (headset.GreenLEDisBlinking)
				{
					if ((headset.AlertCount == 2) || (headset.AlertCount > 3))
					{
						TurnOffYellowLED;
						headset.RedLEDisOn = FALSE;
						headset.YellowLEDisOn = FALSE;
						headset.GreenLEDisOn = FALSE;
					}
					else
					{
						TurnOnGreenLED;
						headset.RedLEDisOn = FALSE;
						headset.YellowLEDisOn = FALSE;
						headset.GreenLEDisOn = TRUE;
					}
				}
				OSStartTimer(WENTWORTHTASKTIMER, 17);					// 17 x 10ms = 170ms pause
			}
			else if ((headset.TakingOrder == FALSE) && (headset.Pager == FALSE))
			{
				TurnOffYellowLED;
				headset.AlertCount = 0;
				headset.VehicleAlert = FALSE;
				headset.RedLEDisBlinking = FALSE;
				headset.YellowLEDisBlinking = FALSE;
				headset.GreenLEDisBlinking = FALSE;
				headset.RedLEDisOn = FALSE;
				headset.YellowLEDisOn = FALSE;
				headset.GreenLEDisOn = FALSE;
			}
			break;
	}
}

// timer to be used for re-assigning Order Taker in Auto Hands Free mode
static void ottimerseqtask1(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      break;
    case TIMEOUT:
      // using this timer for single OT mode since there is no AHF mode at the same time
      if (headset.SingleOT & (headset.OtherLaneWaiting > 0))
      {
  		if (headset.MenuA & !headset.TakingOrder)
  		  PlaySoundPP(sound_double_beep);			// play notification for lane B
  		else if (!headset.MenuA & !headset.TakingOrder)
  		  PlaySoundPP(sound_vehicle_detect_100ms);	// play notification for lane A
  		OSStartTimer(OTTIMERSEQTASK1TIMER, 400);	// check again in 4s
  		break;
      }
      headset.OTtimer = FALSE;						// indicate timer is not running
      // pressed keys: HIGH in P1_DATA_REG
      if (((P1_DATA_REG & 0x003F) & (PAGE_BUTTON | CALL_BUTTON)) == (PAGE_BUTTON | CALL_BUTTON))
      {
        if (!headset.IsInTestMode)
        {
      	  // PB released == pager off
      	  SendPageCmd(0);
      	  PrintStatus(0, "Page - off");
      	  headset.Pager = FALSE;
      	  // now make sure CB is on
      	  AFEEnableMicPathPP();
      	  SendMicMuteCmd(2);						// tell base we've turned on our MIC, request to be new OT
      	  headset.OrderTaker = TRUE;
      	  headset.TakingOrder = TRUE;
      	  headset.RedLEDisOn = TRUE;
      	  headset.VehicleAlert = FALSE;
      	  PlaySoundPP(sound_AHFmode);
      	  TurnOnRedLED;								// LO = Red LED on
      	  headset.LastButtonPressed = CALL_BUTTON;
        }
        else
        {
          // reset test bit in EEPROM to restore production mode
          UByte test[1];
          test[0] = 0xFF;
          general_eeprom_write_req(EE_FIRST_ACTION, test, 1, 0);
    	  PlaySoundPP(sound_z_headset_on);
        }
      }
      break;
  }
}

// timer to be used for Diagnostic mode
static void diagtimerseqtask1(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      break;
    case TIMEOUT:
      TurnOffYellowLED;
      if (headset.PowerOnStatus == 0)
      {
    	PrintStatus(0, "YELLOW");
    	TurnOnYellowLED;
    	OSStartTimer(DIAGTIMERSEQTASK1TIMER, 75);
    	headset.PowerOnStatus++;
      }
      else if (headset.PowerOnStatus == 1)
      {
    	PlaySoundPP(sound_z_headset_connected);
    	PrintStatus(0, "GREEN");
    	TurnOnGreenLED;
    	OSStartTimer(DIAGTIMERSEQTASK1TIMER, 100);
    	headset.PowerOnStatus++;
      }
      else if (headset.PowerOnStatus == 2)
      {
		headset.PowerOnStatus++;
//		RequestConfFromBS();								// HM Inserted request for configuration
PrintStatus(0, "OOOOOOOO requesting SYSTEM MODE and starting 0x16 timer from diagtimerseqtask1()");
		extern void RequestSystemMode(void);
		RequestSystemMode();
        general_startTimer(0, GET_SYSTEM_MODE, NULL, 0, 200);	// check to make sure we know what mode we're in
#ifdef ENABLE_CHANNEL_MESSAGES
        headset.ChannelInfo = get_locked_channel();
        char* ptr = StringPrint(StatusString, "Initial Freq/Slot = 0x");
        ptr = StrPrintHexByte(ptr, headset.ChannelInfo);
        ptr = StringPrint(ptr, " ");
        PrintStatus(0, StatusString);
        general_startTimer(0, CHECK_CHANNEL, NULL, 0, 500);
#endif
      }
      break;
  }
}

// timer to be used for BC5
static void bc5timerseqtask1(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
	case INITTASK:
	  P2_SET_DATA_REG = Px_7_SET;				// set DECT P2[7] to be driven HI (BC5 RESETN) to bring BC5 up
	  OSStartTimer(BC5TIMERSEQTASK1TIMER, 5);	// 5 x 10ms = 50ms pulse for BC5 to start up ...
      PrintStatus(0, "**** BC5TIMER - INITTASK: BC5 RESETN = HI");
      break;
    case TIMEOUT:
      BC5IncrementGainLoPP;						// send HL edge to BC5 PIO1
      BC5DecrementGainLoPP;						// send HL edge to BC5 PIO2
      if (headset.PowerOnStatus == 0)
      {
    	  P2_RESET_DATA_REG = Px_7_RESET;		// set DECT P2[7] to be driven LO (BC5 RESETN) to reset BC5 again
		  PrintStatus(0, "**** BC5TIMER - TIMEOUT: BC5 RESETN = LO");
      }
      break;
  }
}

//void TurnOff ()
//{
//  __disable_interrupt();
//  BAT_CTRL_REG&=~(REG_ON | LDO1_ON);
//  while (1) {;}
//}

// timer to be used for checking battery voltage
static void pptimerseqtask1(MailType * MailPtr)
{
  char * ptr;
  int val;
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      OSStartTimer(PPTIMERSEQTASK1TIMER, 3000); 				// 3000 x 10ms = 30s
      break;
    case TIMEOUT:
      if (headset.WirelessPost)
    	break;
	  BAT_CTRL2_REG |= NTC_DISABLE;
	  ADC_CLEAR_INT_REG = 0;
	  ADC_CTRL_REG |= 0x10; /* ADC_IN_3_0 = 0010b = ADC2 input) */
	  ADC_CTRL_REG |= 0x01; /* Start */
	  while (!(ADC_CTRL_REG & (1 << 11)))
		  ;
	  val = ADC0_REG & 0x03ff;
	  ADC_CLEAR_INT_REG = 0;

	  ptr = StringPrint(StatusString, "**** ADC2: [0x");
	  ptr = StrPrintHexWord(ptr, val);

	  // switch to checking every 30 seconds if battery is below 3.4V (Vbat)
	  // formula for trip point is (((target Vbat x 0.294) / 1.8) x 1024)
	  // or -- val < target Vbat x 167.25
	  if (val < 0x0238)
	  {
		  headset.BatteryLowCounter++;
		  ptr = StringPrint(ptr, "]  Battery LOW **** ");
		  if (headset.BatteryLowCounter > 14)					// after 4 "LOW BATTERY" messages in a row, shut down BC5
		  {
			  PlaySoundPP(sound_z_headset_off);
	    	  P2_RESET_DATA_REG = Px_7_RESET;					// set DECT P2[7] to be driven LO (BC5 RESETN) to reset BC5 again
//			  TurnOff();
	    	  TurnOffYellowLED;
			  headset.RedLEDisOn = FALSE;
			  headset.YellowLEDisOn = FALSE;
			  headset.GreenLEDisOn = FALSE;
	    	  TurnOnRedLED;
	    	  headset.RedLEDisOn = TRUE;
	    	  StopTimer(PPTOUCHTIMERSEQTASK1TIMER);
	    	  spi_write_one_byte(0x05);
	    	  general_startTimer(0, TOGGLE_LED, NULL, 0, 100);
		  }
		  else if (headset.BatteryLowCounter > 10)				// 10 times in a row gives 5 minutes before playing "LOW BATTERY" and shutting down BC5
		  {
			  PlaySoundPP(sound_z_low_battery);
			  OSStartTimer(PPTIMERSEQTASK1TIMER, 3000); 		// 3000 x 10ms = 30s
		  }
		  else
		  {
			  OSStartTimer(PPTIMERSEQTASK1TIMER, 3000); 		// 3000 x 10ms = 30s
		  }
	  }
	  else
	  {
		  headset.BatteryLowCounter = 0;
		  ptr = StringPrint(ptr, "]  Battery OK **** ");
		  OSStartTimer(PPTIMERSEQTASK1TIMER, 30000); 			// 30000 x 10ms = 5 minutes
	  }
	  PrintStatus(0, StatusString);
      break;
  }
}

// timer to be used for checking touch board inputs
static void pptouchtimerseqtask1(MailType * MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      check_touch_board();
      break;
    case TIMEOUT:
      if (headset.TouchBoardStatus == 3)
      {
    	check_touch_pins();
    	OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 10); 			// 10 x 10ms = 100ms
      }
      else if (headset.TouchBoardStatus == 2)
      {
      	headset.TouchBoardStatus = 3;
      	OSStartTimer(PPTOUCHTIMERSEQTASK1TIMER, 10); 			// 10 x 10ms = 100ms
      	if (headset.TouchBoardFail)
		  general_startTimer(0, TOGGLE_TB_FAIL_LED, NULL, 0, 100);
		switch (headset.TouchBoardCode)
		{
		  case 1:
			PrintStatus(0, "    TOUCHBOARD FAIL: CAN'T READ DEVICE ID               ");
			break;
		  case 2:
			PrintStatus(0, "    TOUCHBOARD FAIL: CAN'T PROGRAM RAM                  ");
			break;
		  case 3:
			PrintStatus(0, "    TOUCHBOARD WARNING: CAN'T PROGRAM EEPROM (RAM OK)   ");
			break;
		}
      }
      else
    	finish_programming_touch_board();
      break;
  }
}

// task timer to run clock for external watchdog when PP being used as wireless post
static void watchdogtasktimerpp(MailType * MailPtr)
{
	switch (MailPtr->Primitive)
	{
		case INITTASK:
    		SET_CLOCK_HI;
			OSStartTimer(PPWATCHDOGTASKTIMER, 100); 			// 100 x 10ms = 1s pause before toggling P2[1]
			break;
		case TIMEOUT:
			if (P2_DATA_REG & Px_1_DATA)
				SET_CLOCK_LO;
			else
				SET_CLOCK_HI;
			OSStartTimer(PPWATCHDOGTASKTIMER, 100); 			// 100 x 10ms = 1s pause before toggling P2[1]
			break;
	}
}

// timer for checking vehicle detect when PP being used as a wireless post
static void vehicledetecttasktimerpp(MailType * MailPtr)
{
	switch (MailPtr->Primitive)
	{
		case INITTASK:
			break;
		case TIMEOUT:
			if (!headset.VehicleDetectIsActive && (~P1_DATA_REG & Px_1_DATA))
			{
				headset.VehicleDetectIsActive = TRUE;
				SendVehicleDetectCmd(TRUE);						// VD 3V fired
			}
			else if (headset.VehicleDetectIsActive && (P1_DATA_REG & Px_1_DATA))
			{
				headset.VehicleDetectIsActive = FALSE;
				SendVehicleDetectCmd(FALSE);					// VD 3V released
			}
			OSStartTimer(PPVEHICLEDETECTTASKTIMER, 20); 		// 20 x 10ms = 200ms for checking vehicle detector
			break;
	}
}

void initializeWentworth_ppTask(void)
{
	WENTWORTHTASK = OSRegisterTask(wentworth_pptask, "wentworth_pptask", REALPPTASK);
	WENTWORTHTASKTIMER = OSRegisterTimer(WENTWORTHTASK);
}

void initializeOTTimerTask(void)
{
	OTTIMERSEQTASK1 = OSRegisterTask(ottimerseqtask1, "ottimerseqtask1", REALPPTASK);
	OTTIMERSEQTASK1TIMER = OSRegisterTimer(OTTIMERSEQTASK1);
}

void initializeDiagTimerTask(void)
{
	DIAGTIMERSEQTASK1 = OSRegisterTask(diagtimerseqtask1, "diagtimerseqtask1", REALPPTASK);
	DIAGTIMERSEQTASK1TIMER = OSRegisterTimer(DIAGTIMERSEQTASK1);
}

void initializeBC5TimerTask(void)
{
	BC5TIMERSEQTASK1 = OSRegisterTask(bc5timerseqtask1, "bc5timerseqtask1", REALPPTASK);
	BC5TIMERSEQTASK1TIMER = OSRegisterTimer(BC5TIMERSEQTASK1);
}

void initializePPTimerTask(void)
{
	PPTIMERSEQTASK1 = OSRegisterTask(pptimerseqtask1, "pptimerseqtask1", REALPPTASK);
	PPTIMERSEQTASK1TIMER = OSRegisterTimer(PPTIMERSEQTASK1);
}

void initializePPTouchTimerTask(void)
{
	PPTOUCHTIMERSEQTASK1 = OSRegisterTask(pptouchtimerseqtask1, "pptouchtimerseqtask1", REALPPTASK);
	PPTOUCHTIMERSEQTASK1TIMER = OSRegisterTimer(PPTOUCHTIMERSEQTASK1);
}

void initializeWatchdogTaskTimerPP(void)
{
	PPWATCHDOGTASK = OSRegisterTask(watchdogtasktimerpp, "watchdogtasktimerpp", REALPPTASK);
	PPWATCHDOGTASKTIMER = OSRegisterTimer(PPWATCHDOGTASK);
}

void initializeVehicleDetectTimerTaskPP(void)
{
	PPVEHICLEDETECTTASK = OSRegisterTask(vehicledetecttasktimerpp, "vehicledetecttasktimerpp", REALPPTASK);
	PPVEHICLEDETECTTASKTIMER = OSRegisterTimer(PPVEHICLEDETECTTASK);
}

static void ConfigUART()
{
	P0_MODE_REG |= P0_0_MODE;					// P0[0] is alternate function: UART UTX
	P0_DIR_REG |= Px_0_DIR;						// P0[0] is output, no resistors

	P0_MODE_REG |= P0_1_MODE;					// P0[1] is alternate function: UART URX
	P0_DIR_REG &= ~Px_1_DIR;					// P0[1] is input, no resistors

	PAD_CTRL_REG |= P001_OD;					// P0[0] is OD output; P0[1] is normal input with pull-up disabled
}

static void ConfigOptionPins()
{
	// reading P3[3] confirms headset board (high) or base station board (low)
	// reading P3[4] confirms US (high) or European RF frequencies (low)

	P3_MODE_REG &= ~P3_3_MODE;					// P3[3] used as headset (HI) / base (LO) selector
	P3_DIR_REG &= ~Px_3_DIR;					// P3[3] is input, with pull-up resistor
	P3_DIR_REG |= (Px_3_DIR & 0x0040);			// P3[3] is input, with pull-up resistor

	P3_MODE_REG &= ~P3_4_MODE;					// P3[4] used as US (HI) / Europe (LO) selector
	P3_DIR_REG &= ~Px_4_DIR;					// P3[4] is input, with pull-up resistor
	P3_DIR_REG |= (Px_4_DIR & 0x0100);			// P3[4] is input, with pull-up resistor
}

void ConfigLEDPins(void)
{
	// LED1 = P2[0] = Red LED
	// LED2 = P2[1] = Green LED

	// set P2[1,0] to be driven by P2_OUT_DATA_REG[1,0]
	P2_MODE_REG &= ~(0x000F);

	// set P2[1,0] as outputs
	P2_DIR_REG |= (Px_1_DIR | Px_0_DIR);		// P2[1:0] output

	// set P2[1,0] as OD outputs
	PAD_CTRL_REG |= P20_OD;						// P2[0] is OD
	PAD_CTRL_REG |= P21_OD;						// P2[1] is OD

	// set P2[1,0] as driven HI (LEDs initially are off)
	TurnOffYellowLED;							// turn off Red and Green LEDs
}

void ConfigBC5Pins(void)
{
	// DECT P3[5] -> BC5_MIC2 PIO1
	// DECT P3[6] -> BC5_MIC1 PIO2
	// DECT P3[7] -> BC5_TBD4
	// DECT P2[6] -> BC5_MIC3
	// DECT P2[7] -> BC5_RESETN

	// set P3[7:5] to be driven by P3_OUT_DATA_REG[7:5]
	P3_MODE_REG &= ~(0xFC00);

	// set P2[7:6] to be driven by P2_OUT_DATA_REG[7:6]
	P2_MODE_REG &= ~(0xA000);

	// set P3[7:5] as outputs
	P3_DIR_REG &= ~(0xFC00);
	P3_DIR_REG |= (0xFC00);

	// set P2[7:6] as outputs
	P2_DIR_REG |= (Px_7_DIR | Px_6_DIR);

	// set P3[7:5] as driven LO
	BC5IncrementGainLoPP;						// drive BC5 PIO1 low
	BC5DecrementGainLoPP;						// drive BC5 PIO2 low
	BC5IsUsedPP;								// drive BC5 PIO6 low

	// set P2[7] to be driven LO (BC5 RESETN)
	P2_RESET_DATA_REG = Px_7_RESET;

	// set P2[6] to be driven LO (BC5 MIC3)
	P2_RESET_DATA_REG = Px_6_RESET;
}

static void ConfigSPIPins(void)
{
	// P0[4] -> SPI_EN_DECT (SS input to ATMEL touch sensor; HI to disable SPI)
	// P0[5] -> SPI_CLK_DECT
	// P0[6] -> SPI_DO_DECT (MOSI - DECT is master)
	// P0[7] -> SPI_DI_DECT (MISO - DECT is master)

	// set P0[7:5] to be SPI function (01b)
	P0_MODE_REG &= ~(0x3F00);
	P0_MODE_REG |= (0x1500);

	// set P0[4] (SPI_EN) to be output driven by P0_OUT_DATA_REG[4]
	P0_MODE_REG &= ~(0x00C0);

	// set P0[6:4] as outputs
	P0_DIR_REG |= (Px_6_DIR | Px_5_DIR | Px_4_DIR);

	// set P0[7] as input w/PD
	P0_DIR_REG &= ~Px_7_DIR;
	P0_DIR_REG |= (0x8000);

	// P0[7:4] as normal mode (not OD)
	PAD_CTRL_REG &= ~(P04567_OD);

	// set P0[4] (SPI_EN) as normally driven HI and toggled manually as needed
	P0_SET_DATA_REG = (Px_4_SET);

	// configure and then enable the SPI bus running at 667kHz
	SPI_CTRL_REG = (SPI_POL | SPI_PHA);
	SPI_CTRL_REG |= (0x0001);
}

void StartPCM()
{
    PrintStatus(0, "*** Starting PCM for PP ");

    P2_DIR_REG |=  Px_5_DIR;					// enable PCM_FSC as an output
    P2_DIR_REG |=  Px_4_DIR;					// enable PCM_DO as an output
    P2_DIR_REG &= ~Px_3_DIR;					// enable PCM_DI as an input w/no pull resistor
    P2_DIR_REG |=  Px_2_DIR;					// enable PCM_CLK as an output

    P2_MODE_REG &= ~(P2_5_MODE | P2_4_MODE | P2_3_MODE | P2_2_MODE);	// clear all the bits in question first
    P2_MODE_REG |= (P2_5_MODE & 0x0400);		// enable PCM_FSC
    P2_MODE_REG |= (P2_4_MODE & 0x0100);		// enable PCM_DO
    P2_MODE_REG |= (P2_3_MODE & 0x0040);		// enable PCM_DI
    P2_MODE_REG |= (P2_2_MODE & 0x0010);		// enable PCM_CLK

	DSP_PCM_CTRL_REG &= ~PCM_FSC0LEN;			// clear PCM_FSC0LEN bits first
	DSP_PCM_CTRL_REG |= (PCM_EN | PCM_MASTER);	// set PCM_EN, PCM_MASTER (PCM_FSC0LEN is 1-bit)

	DSP_MAIN_SYNC1_REG = 0;						// clear the entire register: everything at 8kHz

	CLK_CODEC_REG |= 0x4000;					// set CLK_PCM_EN
}

void InitHeadsetVariables(void)
{
	// set P1[5:0] to be driven by P1_OUT_DATA_REG[5:0]
	P1_MODE_REG &= ~(0x0019);

	// set P1[5:0] as inputs
	P1_DIR_REG &= ~(0x0FFF);					// input, no pull resistor
	P1_DIR_REG |= (0x0AAA);						// input, with pull-down resistor

	// initialize the headset status
	headset.DoublePressWindow = 50;				// 50 x 10ms = 0.5 of a second
	headset.OTDoublePressWindow = 200;			// 200 x 10ms = 2 seconds
	headset.PowerOnStatus = 0;
	headset.LastButtonPressed = 0;
	headset.PreviousHeadsetButtonStates = 0x0000;
	headset.CurrentHeadsetButtonStates = 0x0000;
	headset.OrderTaker = FALSE;
	headset.TakingOrder = FALSE;
	headset.Pager = FALSE;
	headset.VehicleAlert = FALSE;
	headset.CarAtOrderPost = FALSE;
	headset.OtherLaneWaiting = 0;
	headset.AlertCount = 0;
	headset.BatteryLowCounter = 0;
	headset.GainVolume = 1;						// dB; pre-TX GAIN block
	headset.SpkrVolOffset = 0;					// only used for calibrating receiver levels at production test
	headset.WavAtten = 0x0E32;					// .wav attenuation dB = (InboundVol x -2) - 13.1;
	headset.GainSpkrVolume = -1;				// dB; post decoder GAIN block: set as FP InboundVol x 2
	headset.SpeakerVolume = 6;					// dB; used for additional PP volume, normalized by subtracting 8dB (0 = -8dB, 8 = 0dB, 14 = +6dB)
	headset.Volume_Swipe = 0;
	headset.SwipeWaiting = FALSE;
	headset.GreenLEDisOn = FALSE;
	headset.GreenLEDisBlinking = FALSE;
	headset.RedLEDisOn = FALSE;
	headset.RedLEDisBlinking = FALSE;
	headset.YellowLEDisOn = FALSE;
	headset.YellowLEDisBlinking = FALSE;
	headset.CurrentLEDState = 0;
	headset.OTtimer = FALSE;
	headset.DualMenu = FALSE;
	headset.MenuA = TRUE;
	headset.SingleOT = FALSE;
	headset.SystemMode = UNREGISTERED;
	headset.TouchBoardStatus = 0;
	headset.TouchBoardFail = 0;
	headset.TouchBoardCode = 0;
	headset.IsInTestMode = FALSE;
	headset.WirelessPost = FALSE;
	headset.VehicleDetectIsActive = FALSE;
#ifdef ENABLE_CHANNEL_MESSAGES
	headset.ChannelInfo = 0;
	headset.LEDCount = 0;
#endif
}

void InitWentworth_pp(void)
{
  initializeWentworth_ppTask();				// task which handles all the headset button presses and LED blinking
  initializeOTTimerTask();					// timer task used by Page Button for OT assignment in AHF
  initializeDiagTimerTask();				// timer task used by Diagnostic mode
  initializeBC5TimerTask();					// timer task used by BC5
  initializePPTimerTask();					// timer task used to monitor battery voltage
  initializePPTouchTimerTask();				// timer task used to monitor touch board inputs
  initializeWatchdogTaskTimerPP();			// timer task used for toggling P2[1] for external watchdog timer when PP being used as a wireless post
  initializeVehicleDetectTimerTaskPP();		// timer task used for checking vehicle detect when PP being used as a wireless post

  ConfigBC5Pins();							// setup BC5 PIO and RESETN pins

  ConfigUART();								// setup P0[0]/P0[1] as UART UTX / URX

  StartPCM();								// setup PCM bus for external microphone

  ConfigOptionPins();						// setup P3[3]/P3[4] as headset (vs base) / US (vs Europe)

  ConfigLEDPins();							// setup P2[0]/P2[1] as Red / Green LEDs

  ConfigSPIPins();							// setup SPI for programming board

  InitHeadsetVariables();					// setup keyb pins P1[5:0] as sources for headset buttons
}
