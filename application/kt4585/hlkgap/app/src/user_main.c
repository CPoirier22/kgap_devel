#include "../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../include/hlkgap/common/include/dispatch.h"
#include "../../../../../include/common/include/print_status.h"
#include "../../../../../include/common/include/_log.h"
#include "../../../../../include/common/include/glibc.h"
#include "../../../../../include/hlkgap/iwu/include/pp/piwuprim.h"
#include "../../../../../include/common/include/app_util.h"
#include "../../../../../include/hlkgap/app/include/f_appdef.h"
#include "../../../../../include/hlkgap/app/include/apssprim.h"
#include "../../../../../include/hlkgap/util/include/bintree.h"
#include "../../../../../include/mac/eeprom/include/fnvm.h"
#include "../../../../../include/os/include/maildef.h"
#include "../../../../../include/os/include/tasks.h"
#include "../../../../../include/os/include/os_tasks.h"
#include "../../../../../include/os/include/os_timer.h"
#include "../../../../../include/os/include/os_timers.h"
#include "../../../../../include/os/include/os_mail.h"
#include "../../../../../include/common/include/map_480_gcc.h"
#include "wentworth/wentworth_pp.h"
#include "wentworth/wentworth_fp.h"
#include "wentworth/fppp_common.h"

// this is in main.c source code
//#ifdef GCCCOMPILE
//BYTE DummyRam[1] __attribute__ ((section (".dummysegment"))); // to catch .bmc ram overflow when linking
//#endif

#ifdef GCCCOMPILE
BYTE DummyRam2[1] __attribute__ ((section (".dummysegment2"))); /* to catch .data overflow when linking*/
#endif

UByte WENTWORTHTASK = -1;
UByte WENTWORTHTASKTIMER = -1;

void (*FPAppDBHandler)(SignalType * Signal) = 0;
extern BYTE UartNoBufferOverflow; /* flag to avoid transmit buffer overflow 0=disabled, 1=enabled*/
extern UByte getRunMode(void);

int _ProxyHandler(MailType *MailPtr)
{
  return 0; // called from within idle loop - usually outputs "PP Lock" on debug port
}

int user_main(int argv, char **args)
{
  char * ptr;
  UByte rev[6];
  ptr = StringPrint(StatusString, "");
  ptr = StringPrint(ptr, "***** FW rev ");
  rev[GetAsciiValue(&rev[0], FW_REV_MAJOR, 0)] = '\0';
  ptr = StringPrint(ptr, (char *)rev);
  ptr = StringPrint(ptr, ".");
  rev[GetAsciiValue(&rev[0], FW_REV_MINOR, 0)] = '\0';
  ptr = StringPrint(ptr, (char *)rev);
  ptr = StringPrint(ptr, "-AL *****");
  PrintStatus(0, StatusString);
  //UartNoBufferOverflow=1;
  if (FP_EepromInRam.FP_PP_Select)
  {
	    InitWentworth_fp();
  }
  else
  {
    OSRegisterProxy(_ProxyHandler,0x0C); // use this code to avoid PP Lock debug messages
    InitWentworth_pp();
  }
  return 0;
}
