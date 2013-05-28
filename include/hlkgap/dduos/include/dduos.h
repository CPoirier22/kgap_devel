/*
 ********************************************************************
 *
 * Module: dduos.h
 *
 *
 ********************************************************************
 */
#ifndef DDU_OS__
#define DDU_OS__

#include "../../../common/include/bitsdef.h"

/* -------------------- Signals -------------------- */
typedef DWORD ProcessIdType;
typedef DWORD EventType;
typedef UByte SubEventType;
typedef UByte AddressType[4];   /* 32 bits destination address */

struct private_SignalStructure
{
    ProcessIdType ProcessId;
    ProcessIdType SourceProcessId;
    int SessionId;
    EventType Event;
    SubEventType SubEvent;
    U16Bits SignalLength;
    AddressType Address;
    struct private_SignalStructure *PreviousSignalPointer;
    struct private_SignalStructure *NextSignalPointer;
};

#define getSignalData(signal) ((unsigned char*)signal + offsetof(struct private_SignalStructure, NextSignalPointer) + sizeof(struct private_SignalStructure *))

#define signalSize() (offsetof(struct private_SignalStructure, NextSignalPointer) + sizeof(struct private_SignalStructure *))

typedef struct private_SignalStructure SignalType;

typedef Boolean SignalFilterFunction(SignalType * Signal);

typedef void (*DispatcherFunction) (SignalType * TheSignal);

/* -------------------- Timers -------------------- */

struct TimerStructure
{
    SignalType SignalHeader;
    U16Bits StartTime;
    U16Bits TimeOutValue;
};

#define timerSize() (offsetof(struct TimerStructure, TimeOutValue) + sizeof(U16Bits))
#define getTimerData(timer) ((unsigned char*)timer + offsetof(struct TimerStructure, TimeOutValue) + sizeof(U16Bits))

typedef struct TimerStructure TimerType;

typedef struct _dduosConfiguration
{
    DWORD (*CurrentTime) (void);
    int (*deliverSignalCallback) (SignalType * TheSignal);
    DispatcherFunction (*getSignalHandler)(ProcessIdType ProcessId, int sessionId);
    ProcessIdType (*getSignalHandlerId)(DispatcherFunction func, int sessionId);
}
dduosConfiguration;

/* functions */
void setSignalHandler(ProcessIdType pid, DispatcherFunction handler, int sessionId);
DispatcherFunction getSignalHandler(ProcessIdType ProcessId, int sessionId);
Boolean NewSignal(int BufferLength, void **BufferPointer);
Boolean NewSignal_(int BufferLength, void **BufferPointer, BYTE id);
void SuspendSignal(SignalType * Signal);
void SendSignal(SignalType * Signal, ProcessIdType ProcessId, EventType Event, SubEventType SubEvent);
void InjectSignal(SignalType * Signal, ProcessIdType ProcessId, EventType Event, SubEventType SubEvent, int sessionID);
void DeleteSignal(SignalType * Signal);
void FlushSignal(ProcessIdType ProcessId, SignalFilterFunction * SignalFilter);
Boolean CheckSignalQueue(void);
TimerType *NewTimer(ProcessIdType ProcessId, SubEventType SubEvent, int AdditionalDataSize);
void SuspendTimer(TimerType * Timer);
void StartTimer(TimerType * Timer, U16Bits TimeOutValue);
int getNumberOfRunningTimers(void);
int getNumberOfQueuedSignals(void);
Boolean TimeOut(U16Bits StartTime, U16Bits TimeOutValue, U16Bits Now);
int CheckTimerQueue(void);
void DeleteTimer(TimerType * Timer);
void InitializeDDUOS(dduosConfiguration *cfg);
void QueueSignal(SignalType ** FirstSignalAddr, SignalType ** LastSignalAddr, SignalType * Signal);
void DequeueSignal(SignalType ** FirstSignalAddr, SignalType ** LastSignalAddr, SignalType * Signal);
void RestoreSignals(SignalType * FirstSignal, SignalType * LastSignal);
Boolean timersWaiting(void);
void stopDDUOS(void);
void startSignalHandler(ProcessIdType ProcessId, int sessionId);
dduosConfiguration* getDDUOSConf(void);
BYTE getSourceProcessId();

void setSessionId(int id);
#endif /* DDU_OS__ */
