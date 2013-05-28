#include "../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../include/hlkgap/dduos/include/heap.h"
#include "../../../../../include/hlkgap/common/include/dispatch.h"
#include "../../../../../include/hlkgap/app/include/apdbprim.h"
#include "../../../../../include/common/include/print_status.h"
#include "../../../../../include/common/include/glibc.h"

extern void (*FPAppDBHandler)(SignalType * Signal);

static int isLegalEPEI(IPEIType IPEI)
{
    return 1;
}

#define PERIODICTIMER 0x90

void FPsubscriptionHandler(SignalType * signal)
{
    switch (signal->Event)
    {
        case INITIALIZE_EVENT:
        {
            PrintStatus(0, "FPsubscriptionHandler - INITIALIZE_EVENT");
            TimerType * periodicTimer = NewTimer(APP_DB_PROCESS_ID, PERIODICTIMER, 0);
            StartTimer(periodicTimer, 500);
        }
        break;
        case APP_DB_PRIMITIVE:
        {
            switch (signal->SubEvent)
            {
                case SUBS_DATA_req:
                {
                    PrintStatus(0, "FPsubscriptionHandler - SUBS_DATA_req");
                    SubsDataReqType *SubsDataReq = (SubsDataReqType *) signal;

                    if (isLegalEPEI(SubsDataReq->IPEI)) {
                    } else { /* Send reject*/
                        SubsDataCfmType *SubsDataCfm;

                        NewSignal(sizeof(SubsDataCfmType), (void **) &SubsDataCfm);
                        SubsDataCfm->SignalHeader.SignalLength = sizeof(SubsDataCfmType);
                        memcpy(SubsDataCfm->SignalHeader.Address, SubsDataReq->ReturnAddress, sizeof(AddressType));
                        memcpy(SubsDataCfm->IPEI, SubsDataReq->IPEI, IPEISize);
                        memset(SubsDataCfm->AC_UPI, 0xff, MaxAcOctets);

                        SubsDataCfm->Error = InvalidIPEI;
                        SubsDataCfm->PPID = 0;

                        SendSignal((SignalType *) SubsDataCfm, SubsDataReq->ReturnProcessId, APP_DB_PRIMITIVE, SUBS_DATA_cfm);
                        DeleteBuffer(signal);
                        return;
                    }
                }
            }
        }
        break;
        case TIME_OUT_EVENT:
        {
            switch (signal->SubEvent)
            {
                case PERIODICTIMER:
                {
                    PrintStatus(0, "FPsubscriptionHandler - PERIODICTIMER");
                    char* ptr;
                    int c, subscribedUsers;
                    TimerType * periodicTimer = NewTimer(APP_DB_PROCESS_ID, PERIODICTIMER, 0);
                    StartTimer(periodicTimer, 500);

                    subscribedUsers = 0;
                    for (c = 0; c < MAX_Allowed_Users; c++)
                    {
                        if (QuickData[c].EmptyMarker == 0)
                        {
                            subscribedUsers++;
                        }
                    }

                    ptr = StringPrint(StatusString, "FP:[");
                    ptr = StrPrintHexWord(ptr, subscribedUsers);
                    ptr = StringPrint(ptr, "] subscribed users");
                    PrintStatus(0, StatusString);

                    DeleteBuffer(signal);
                    return;
                }
            }
        }
    }
    FPAppDBHandler(signal);
}

