#ifndef _OS_TIMER_H
#define _OS_TIMER_H

#include "tasks.h"

extern void RunTimerSystem(void);
extern void OSStartTimer(BYTE TimerId, WORD Time);
extern void OSStartTimerMail(TaskIdType TaskId, BYTE Length, MailType * MailPtr, WORD Time);
extern void StopTimer(BYTE TimerId);
extern unsigned char OSRunningTimer(BYTE TimerId);
extern void initializeTimer(void);
extern void checkTimers(void);
extern void visitDeferredMails(int (*visit)(MailType *MailPtr, TaskIdType TaskId));
extern int numberOfDeferredMails(void);
#endif
