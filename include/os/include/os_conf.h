#ifndef _OS_CONF_H
#define _OS_CONF_H

#include "os_mail.h"
#include "os_timer.h"
#include "private/os_local.h"
#include "os.h"

void conf_ResetWatchdogTimer(void);
void conf_enableWatchdog(void);
void conf_turnRedLedOff(void);
void conf_turnRedLedOn(void);
void conf_toggleRedLed(void);
void conf_disableInterrupt(void);
void conf_enableInterrupt(void);
void conf_InitBmc (void *BmcInitData);
void conf_InitIO(void);
void conf_InitSystem(void);
void conf_userInit(void);
void conf_SignalBuffer_RX_Task(void);
int conf_deliverMailCallback(TaskIdType reciever, MailType *mail, BYTE length);
void conf_InitTasklets(void);
void conf_RunTasklets(void);
void conf_wait(void);
int conf_loop(TaskIdType* CurrentTask);
void conf_bootmode(void);
void conf_interruptHandler(void);
void conf_PrintStatus(uint8 StatusMessageLevel, char *msg);
void conf_CheckForInterruptMail(TaskIdType* CurrentTask, OSConfiguration* conf);
void conf_SetSystemClock(uint8 name, uint8 HighSpeed);
int conf_initTaskAtStartup(TaskIdType task);
void conf_initializeTasksAndTimers(void);
uint8 conf_getNumberOfTasks(void);
uint8 conf_getNumberOfTimers(void);
TimerRecordType* conf_getTimer(uint8 id);
const TaskDefType* conf_getTask(uint8 id);
uint8 conf_initTaskInControllerTask(uint8 id);
TaskIdType conf_getTimerOwner(uint8 id);
void conf_mailDump(BYTE TaskId, void *queueElement, BYTE mailLength);
void conf_checkForInterruptMailCallback(void);
void conf_reportFatalError(char* msg);

#endif
