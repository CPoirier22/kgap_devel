#ifndef _OS14428_H__
#define _OS14428_H__

extern void conf_os_wait();
extern void conf_os_bootmode();
extern void conf_InitTasklets(void);
extern void conf_RunTasklets(void);
extern void conf_ResetWatchdogTimer(void);
extern int conf_getHF_TestMode();
extern void conf_enableWatchdog();
extern void conf_turnRedLedOff(void);
extern void conf_turnRedLedOn(void);
extern void conf_toggleRedLed();

#endif
