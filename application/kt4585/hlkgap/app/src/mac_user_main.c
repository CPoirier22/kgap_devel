#include "../../../../../include/os/include/os.h"
#include "../../../../../include/os/include/os_tasks.h"
#include "../../../../../include/os/include/os_mail.h"
#include "../../../../../include/os/include/intmail.h"
#include "../../../../../include/os/include/os_timers.h"
#include "../../../../../include/os/include/mailprim.h"
#include "../../../../../include/common/include/print_status.h"
#include "../../../../../include/mac/startup/include/interrupts.h"
#include "../../../../../include/common/include/map_480_gcc.h"
#include "dsp/gdsp_all_inits.h"
#include "../../../../../include/mac/eeprom/include/fnvm.h"
#include "wentworth/afe.h"

extern void GdspISR(void);
extern UByte getRunMode(void);

static void myTurnRedLedOff(void)
{
  ;
}

static void myTurnRedLedOn(void)
{
  ;
}

static InterruptHandler clk100handler;
int hmcounter=0;
extern UByte copyBufferCounter;
static void myClk100Handler(void)
{
  hmcounter++;
  copyBufferCounter = 38;
  if (clk100handler != 0)
    clk100handler();
}

BOOLEAN wt_watchdog_running = FALSE;
void My_enableWatchdog(void)
{
//  TIMER_CTRL_REG &= ~WDOG_CTRL;		// NMI
  TIMER_CTRL_REG |= WDOG_CTRL;		// HW reset
  RESET_FREEZE_REG = FRZ_WDOG;
  PrintStatus(0, "Enabling WATCHDOG");
  wt_watchdog_running = TRUE;
//  char* ptr = StringPrint(StatusString, "2nd: wt_counter = ");
//  ptr = StrPrintDecByte(ptr, wt_counter);
//  PrintStatus(0, StatusString);
}

void My_ResetWatchdogTimer(void)
{
//	  char* ptr = StringPrint(StatusString, "1st: wt_counter = ");
//	  ptr = StrPrintDecByte(ptr, wt_counter);
//	  PrintStatus(0, StatusString);
  if (wt_watchdog_running)
	WATCHDOG_REG = 0xFF;
  else
	My_enableWatchdog();
}

extern void uart_sendstring2(char *msg);
void myReportFailure(char* msg)
{
  uart_sendstring2("myReportFailure:\n\r");
  uart_sendstring2(msg);
  while (1) {;}
}

extern BYTE HighDutyCycleCount;
void runTestCode(void);
void mac_user_main(void)
{
  if (getRunMode()) // FP
  {
    clk100handler = get_interrupt_handler(25);
    set_interrupt_handler(25, myClk100Handler);
    OSConfiguration *conf = os_get_conf();
    conf->turnRedLedOff = myTurnRedLedOff;
    conf->turnRedLedOn = myTurnRedLedOn;
    conf->reportFatalError = myReportFailure;
  }
  else // PP
  {
    OSConfiguration *conf = os_get_conf();
    HighDutyCycleCount = 0xff; // no power saving
    conf->turnRedLedOff = myTurnRedLedOff;
    conf->turnRedLedOn = myTurnRedLedOn;
    conf->reportFatalError = myReportFailure;
    conf->ResetWatchdogTimer = My_ResetWatchdogTimer;
    if (FP_EepromInRam.HF_TestMode)
    	runTestCode();
  }
  set_interrupt_handler(29, GdspISR);
  CLK_AMBA_REG |= MCRAM1_EN;
}

static void usec_pause(unsigned int x)
{
    volatile unsigned int i;
    for (i = 0; i < x; i++)
    {
    	;
    }
}

extern void ConfigBC5Pins(void);
extern int gen2dsp_init(void);
extern void StartAdpcmPP(void);
extern void StartCODEC(uint8 amps);
extern void SetLSRGain(unsigned int vol_val);
extern void StartDSP(void);
extern void StartPCM();
extern void gdsp_BC5SpeakerPath(unsigned char bypass);
extern void ConfigLEDPins(void);

void runTestCode(void)
{
	PrintStatus(0, "*** got to HF_TestMode ");
    ConfigBC5Pins();
    P2_SET_DATA_REG = Px_7_SET;						// set DECT P2[7] to be driven HI (BC5 RESETN) to bring BC5 up
    PrintStatus(0, "**** DSPSignalHandler: BC5 RESETN is HI");
    usec_pause(50000);
    if (gen2dsp_init() == GDSP_NO_SUCCESS)
    	PrintStatus(0, "gen2dsp_init() failed!!");
    else
    	PrintStatus(0, "gen2dsp_init() success!!");
    StartAdpcmPP();
    StartCODEC(0x01);								// PP uses only the LSR amp, MIC comes from BC5 via PCM bus
    AFEDisableMicPathPP();							// send NULL to encoder
    AFESetVolume(10);								// set up pre-encoder gain to 10dB
    AFESetGainSpkrVolumePP(5);						// set up pre-LSR gain to 5dB
    SetLSRGain(6);									// 6 => LSR = 0dB
    StartDSP();
    StartPCM();
	gdsp_BC5SpeakerPath(0x10);
	ConfigLEDPins();
	P2_SET_DATA_REG = Px_1_SET;						// turn on Green LED
}
