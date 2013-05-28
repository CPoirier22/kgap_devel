#ifndef __OS_H
#define __OS_H
/*****************************************************************************
 * Project   : DECT                                                           *
 * Module    : Operating system                                               *
 * Reference : Modulespecification for the Operating system                   *
 * Type      : Headerfile containing global routines and data                 *
 * Function  :                                                                *
 * Systems   : Base,Handset                                                   *
 *----------------------------------------------------------------------------*
 * Copyright (c) 1996 by RTX Research A/S.                                    *
 * $Header:   K:/ph/srclib/os/basis/archive/h/OS.H_V   1.3.1.2   May 06 2003 13:03:42   on  $ *
 *****************************************************************************/

#include "../../common/include/bitsdef.h"
#include "tasks.h"
#include "../../common/include/rtxdef.h"
#include "os_mail.h"
#include "os_timer.h"
#include "private/os_local.h"

#define BUZZER_HIGHSPEED_REQ      0x01
#define AUDIO_HIGHSPEED_REQ       0x02
#define BUSTRACE_HIGHSPEED_REQ    0x04
#define IR_HIGHSPEED_REQ          0x08
#define EE_HIGHSPEED_REQ          0x10
#define BUS_HIGHSPEED_REQ   0x20

typedef struct _osConfiguration
{
    /* Hardware specific interfaces */
    void (*ResetWatchdogTimer)(void);
    void (*enableWatchdog)(void);
    void (*turnRedLedOff)(void);
    void (*turnRedLedOn)(void);
    void (*toggleRedLed)(void);
    void (*disableInterrupt)(void);
    void (*enableInterrupt)(void);

    /* Various functions needed by the OS */
    void (*InitBmc)(void *BmcInitData);
    void (*InitIO)(void);
    void (*InitSystem)(void);
    void (*userInit)(void);
    void (*SignalBuffer_RX_Task)(void);
    int (*deliverMailCallback)(TaskIdType reciever, MailType *mail, BYTE length);
    void (*InitTasklets)(void);
    void (*RunTasklets)(void);
    void (*wait)(void);
    int (*loop)(TaskIdType* CurrentTask);
    void (*bootmode)(void);
    void (*interruptHandler)(void);
    void (*PrintStatus)(uint8 StatusMessageLevel, char *msg);
    int (*printf)(char *fmt, ...);
    void (*CheckForInterruptMail)(TaskIdType* CurrentTask, struct _osConfiguration* conf);
    void (*SetSystemClock)(uint8 name, uint8 HighSpeed);
    void (*mailDump)(BYTE TaskId, void *queueElement, BYTE mailLength);
    void (*checkForInterruptMailCallback)(void);
    void (*reportFatalError)(char* msg);

    /* Interface to task module */
    int (*initTaskAtStartup)(TaskIdType task);
    void (*initializeTasksAndTimers)(void);
    uint8 (*getNumberOfTasks)(void);
    uint8 (*getNumberOfTimers)(void);
    TimerRecordType *(*getTimer)(uint8 id);
    const TaskDefType *(*getTask)(uint8 id);
    TaskIdType (*getTimerOwner)(uint8 id);
    uint8 (*initTaskInControllerTask)(uint8 id);

    /* basic values controlling os behaviour */
    unsigned long int loopCount; /* The number of times the OS loop will run before returnning. 0 means forever*/
} OSConfiguration;

/* Exported functionality */

extern void increaseSystemTick(void);

extern void SetSystemClock(BYTE name, BYTE HighSpeed);
extern void os_bootmode(void);
extern void os_init_time(void);
extern void os_get_time(uint8* hour, uint8* min, uint8* sec);
extern void os_set_time(uint8 hour, uint8 min, uint8 sec);
extern void os_get_date(uint8* day, uint8* month, uint8* year);
extern void os_set_date(uint8 day, uint8 month, uint8 year);
extern uint32 os_up_time(void);
extern uint16 os_up_time_s(void);
extern int printf232(char *fmt, ...);
extern void os_disableInterrupt(void);
extern void os_enableInterrupt(void);
extern void os_resetWatchdog(void);
extern void SystemTurboSpeed(unsigned char on);

extern OSConfiguration *os_get_conf(void);
extern PP_RTC_Type PP_RTC;
/* main entry function into the OS */
int runOS(OSConfiguration * conf, void (*preRunActions)(void));
#endif
