#include "../../include/fp/fp_api.h"

extern ApplicationInstanceType * getApplicationInstance(PMIDType PMID);
extern TimerType * pp_timerPt;
extern UByte getRunMode(void);

static TimerType * fppp_general_timerPt = 0;

UByte general_stopTimer(PPIDType user)
{
    if (user == (PPIDType) -1) {
        if (fppp_general_timerPt != 0) {
            DeleteTimer(fppp_general_timerPt);
            fppp_general_timerPt = 0;
            return 0;
        } else {
            return 1;
        }
    } else if (getRunMode() == 0) {
        if (pp_timerPt != 0) {
            DeleteTimer(pp_timerPt);
            pp_timerPt = 0;
            return 0;
        } else {
            return 1;
        }
    } else if (QuickData[user].EmptyMarker == 0) {
        PMIDType pmid;
        ApplicationInstanceType * applicationInstanceData;
        PPID2PMID(&pmid, user);
        applicationInstanceData = getApplicationInstance(pmid);

        if (applicationInstanceData->timer != 0) {
            DeleteTimer(applicationInstanceData->timer);
            applicationInstanceData->timer = 0;
            return 0;
        }
        return 1;
    }
    return 2;
}

UByte general_startTimer(PPIDType user, UByte subEvent, UByte * dataPtr, UByte dataLength, int timeoutValue)
{
//	char* ptr = StringPrint(StatusString, "general_startTimer[");
//	ptr = StrPrintHexByte(ptr, subEvent);
//	ptr = StringPrint(ptr, ",");
//	ptr = StrPrintHexWord(ptr, timeoutValue);
//	ptr = StringPrint(ptr, "]");
//	PrintStatus(0, StatusString);

	if (user == (PPIDType) -1) {
        PMIDType pmid;
        PPID2PMID(&pmid, user);

        if (getRunMode() == 0) {
            fppp_general_timerPt = NewTimer(APPLICATION_PROCESS_ID_PP, subEvent, dataLength);
        } else {
            fppp_general_timerPt = NewTimer(APPLICATION_PROCESS_ID_FP, subEvent, dataLength);
        }

        if (dataLength) {
            memcpy(getTimerData(fppp_general_timerPt), dataPtr, dataLength);
        }
        memcpy(fppp_general_timerPt->SignalHeader.Address, pmid, sizeof(PMIDType));

        StartTimer(fppp_general_timerPt, timeoutValue);
        return 1;
    } else if (getRunMode() == 0) {
        pp_timerPt = NewTimer(APPLICATION_PROCESS_ID_PP, subEvent, dataLength);
        if (dataLength) {
            memcpy(getTimerData(pp_timerPt), dataPtr, dataLength);
        }
        StartTimer(pp_timerPt, timeoutValue);
        return 1;
    } else if (QuickData[user].EmptyMarker == 0) {
        PMIDType pmid;
        ApplicationInstanceType * applicationInstanceData;
        PPID2PMID(&pmid, user);
        applicationInstanceData = getApplicationInstance(pmid);

        applicationInstanceData->timer = NewTimer(APPLICATION_PROCESS_ID_FP, subEvent, dataLength);
        if (dataLength) {
            memcpy(getTimerData(applicationInstanceData->timer), dataPtr, dataLength);
        }
        memcpy(applicationInstanceData->timer->SignalHeader.Address, pmid, sizeof(PMIDType));
        StartTimer(applicationInstanceData->timer, timeoutValue);
        return 1;
    }
    return 0;
}

