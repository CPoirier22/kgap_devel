#ifndef OS_TASKS_H_
#define OS_TASKS_H_

#include "tasks.h"

void OSInitTaskHandling(void);
UByte OSRegisterTask(void (*handler)(MailType *MailPtr), char *name,TaskFunctionType type);
void OSRegisterProxy(int (*proxy)(MailType *MailPtr), UByte taskId);
void OSDeregisterProxy(int (*proxy)(MailType *MailPtr), UByte taskId);
UByte OSGetNumberOfTasks(void);
const TaskDefType *OSGetTask(UByte taskId);
int OSGetDiscardedMails(void);
char* OSGetTaskName(UByte taskId);

#endif /*OS_TASKS_H_*/
