#ifndef OS_TIMERS_H_
#define OS_TIMERS_H_

void OSInitTimerHandling(void);
UByte OSRegisterTimer(UByte taskId);
UByte OSGetTimerOwner(UByte timerId);
TimerRecordType *OSGetTimer(UByte timerId);
UByte OSGetNumberOfTimers(void);

#endif /*OS_TIMERS_H_*/
