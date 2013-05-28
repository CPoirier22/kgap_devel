#include "../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../include/hlkgap/dduos/include/heap.h"
#include "../../../../../include/hlkgap/util/include/msgutil.h"
#include "../../../../../include/common/include/print_status.h"
#include "../../../../../include/common/include/glibc.h"
#include "../../../../../include/hlkgap/iwu/include/pp/piwuprim.h"
#include "../../../../../include/hlkgap/common/include/dispatch.h"
#include "../../../../../include/hlkgap/other/include/pp/nvm.h"
#include "../../../../include/eeplayout.h"
#include "../../../../include/kt4585.h"
#include "../../../../api/include/pp_application.h"
#include "../../../../api/include/DSPSignalHandler.h"

extern void callUser_PP(char * number, int sessionId);

void PPconnectionHandler(SignalType * Signal);

#define INFO_BUFSIZE 32

UByte firsttime = 1;
extern UByte* pp_get_speech_buffer(UByte index);
extern void handle_ss_setup(SignalType * TheSignal);
extern void handle_ss_facility(SignalType * TheSignal);
extern void GetCallingPartyNo(CallingPartyNoType *CallingPartyNoPtr, char* dest, int h);

#define OFFHOOKTIMER 0x62
#define PEIODICTIMER 0x63
#define SENDMSFTIMER 0x64

static int connected = 0;

static void off_hook(void)
{
    CcConnectPrimType * CcConnectPrim;
    SignalType * startAudio;

    NewBuffer(sizeof(CcConnectPrimType), (void**) &CcConnectPrim);
    CcConnectPrim->SignalHeader.SignalLength = sizeof(CcConnectPrimType);
    SendSignal((SignalType*) CcConnectPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_CONNECT_prim);

    NewBuffer(sizeof(SignalType), (void**) &startAudio);
    SendSignal((SignalType*) startAudio, DSP_PROCESS_ID, SETUPAUDIO_EVENT, 0);
}

void on_hook(void)
{
    CcReleasePrimType * CcReleasePrim;
    ReleaseReasonType * ReleaseReason;

    NewBuffer(sizeof(CcReleasePrimType) + sizeof(ReleaseReasonType), (void**) &CcReleasePrim);
    CcReleasePrim->SignalHeader.SignalLength = sizeof(CcReleasePrimType) + sizeof(ReleaseReasonType);
    ReleaseReason = (ReleaseReasonType *) getCcReleasePrimTypeIE(CcReleasePrim);
    ReleaseReason->IEID = ReleaseReasonId;
    ReleaseReason->ReleaseReasonCode = NormalReleaseReason;
    SendSignal((SignalType*) CcReleasePrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_RELEASE_prim);
}

extern void SendMsfMessage(char *Destination, char *Message);

extern void TZ_connectionHandler(SignalType * Signal);

static char numberToDial[5];

static void PPDialingHandler(SignalType * Signal)
{
    switch (Signal->Event)
    {
        case IWU_PRIMITIVE:
        {
            switch (Signal->SubEvent)
            {
                case CC_CONNECT_prim:
                {
                    SignalType * startAudio;
                    NewBuffer(sizeof(SignalType), (void**) &startAudio);
                    SendSignal((SignalType*) startAudio, DSP_PROCESS_ID, SETUPAUDIO_EVENT, 0);
                    connected = 1;
                }
                case CC_INFO_prim: /*do not break*/
                {
                    if (connected == 1) {
                        SignalType* mySignal;
                        NewSignal(sizeof(SignalType) + 2 + strlen(numberToDial), (void **) &mySignal);
                        getSignalData(mySignal)[0] = 0x2c;
                        getSignalData(mySignal)[1] = strlen(numberToDial);
                        memcpy(getSignalData(mySignal) + 2, numberToDial, strlen(numberToDial));
                        InjectSignal(mySignal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_INFO_prim, Signal->SessionId);
                    }
                }
                break;
                case CC_RELEASE_prim:
                {
                    if (connected == 1) {
                        Signal->SignalLength = sizeof(CcReleaseComPrimType);
                        SendSignal(Signal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_RELEASE_COM_prim);
                        connected = 0;
                        setSignalHandler(APPLICATION_PROCESS_ID_PP, PPconnectionHandler, 0);
                        return;
                    }
                }
                break;
            }
        }
    }
    DeleteBuffer(Signal);
}

static UByte eepromData[5];

static void EEPROMWriteReadTestHandler(SignalType * Signal)
{
    switch (Signal->Event)
    {
        case EE_PRIMITIVE:
            switch (Signal->SubEvent)
            {
                case EE_READ_DATA_cfm:
                {
                    char* ptr;
                    EeStoreDataReqType *EeStoreDataReq;

                    ptr = StringPrint(StatusString, "EE_READ_DATA_cfm[");
                    ptr = StrPrintHexWord(ptr, EEP_UserDataArea);
                    ptr = StringPrint(ptr, "]=[");
                    ptr = StrPrintHexByte(ptr, eepromData[0]);
                    ptr = StringPrint(ptr, "]");
                    PrintStatus(0, StatusString);

                    eepromData[0]++;

                    NewSignal(sizeof(EeStoreDataReqType) + 1, (void **) &EeStoreDataReq);
                    getSignalData(EeStoreDataReq)[0] = eepromData[0];
                    EeStoreDataReq->DataTypes = EEDT_ANYADDRESS;
                    EeStoreDataReq->SubsNo = 0;
                    setAddressData(EEP_UserDataArea, 1);
                    SendSignal((SignalType *) EeStoreDataReq, EE_PROCESS_ID, EE_PRIMITIVE, EE_STORE_DATA_req);

                    setSignalHandler(APPLICATION_PROCESS_ID_PP, PPconnectionHandler, 0);
                }
                break;
            }
    }
    DeleteBuffer(Signal);
}

void PPconnectionHandler(SignalType * Signal)
{
    switch (Signal->Event)
    {
        case APPLICATION_PRIMITIVE:
        {
            switch (Signal->SubEvent)
            {
                case MSFInd:
                {
                    AppMSFType* msfInd = (AppMSFType*) Signal;
                    char* msf = mem_malloc(msfInd->length + 1, 100);
                    memcpy(msf, getAppMSFTypeIE(msfInd), msfInd->length);
                    msf[msfInd->length] = '\0';
                    PrintStatus(0, msf);
                    if (strlen(msf) > 4) {
                        if (memcmp(msf, "DIAL", 4) == 0) {
                            char *number = &msf[4];
                            if (strlen(number) < 5) {
                                TimerType * timer = NewTimer(APPLICATION_PROCESS_ID_PP, WAIT_CONNECTION, 0);
                                StartTimer(timer, 200); /* wait 2 sec before dialing call*/
                                memcpy(numberToDial, number, strlen(number));
                                numberToDial[strlen(number)] = '\0';
                            }
                        }
                    }
                    mem_free(msf);
                    break;
                }
            }
        }
        break;
        case IWU_PRIMITIVE:
        {
            switch (Signal->SubEvent)
            {
                case CC_SETUP_prim:
                {
                    char* ptr;
                    char CallingPartyNo[INFO_BUFSIZE];

                    CcSetupPrimType *CcSetupPrim = (CcSetupPrimType *) Signal;
                    CallingPartyNoType *CallingPartyNoPtr;
                    SignalIEType *SignalIE;
                    TimerType * timer = NewTimer(APPLICATION_PROCESS_ID_PP, OFFHOOKTIMER, 0);
                    StartTimer(timer, 200); /* wait 2 sec before accepting call*/

                    CallingPartyNoPtr = (CallingPartyNoType *) FindInfoElement(CallingPartyNoId, getCcSetupPrimTypeIE(CcSetupPrim) - 2, CcSetupPrim-> SignalHeader. SignalLength - sizeof(CcSetupPrimType) + 2);

                    GetCallingPartyNo(CallingPartyNoPtr, CallingPartyNo, 32);

                    SignalIE = (SignalIEType *) FindInfoElement(SignalId, getCcSetupPrimTypeIE(CcSetupPrim) - 2, CcSetupPrim->SignalHeader. SignalLength - sizeof(CcSetupPrimType) + 2);
                    if (SignalIE) {
                    } else {
                        PrintStatus(0, "No SignalIE! EXTERNAL_RING");
                    }
                    Signal->SignalLength = sizeof(CcAlertingPrimType);
                    SendSignal(Signal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_ALERTING_prim);

                    ptr = StringPrint(StatusString, "CallingPartyNo [");
                    ptr = StringPrint(ptr, CallingPartyNo);
                    ptr = StringPrint(ptr, "]");
                    PrintStatus(0, StatusString);
                    connected = 1;
                    return;
                }
                case CC_RELEASE_COM_prim:
                break;
                case CC_RELEASE_prim:
                {
                    SignalType* stopAudio;
                    Signal->SignalLength = sizeof(CcReleaseComPrimType);
                    SendSignal(Signal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_RELEASE_COM_prim);
                    NewSignal(sizeof(SignalType), (void**) &stopAudio);
                    SendSignal((SignalType*) stopAudio, DSP_PROCESS_ID, STOPAUDIO_EVENT, 0);
                    return;
                }
                case CC_CONNECT_ACK_prim:
                {
                    EeReadDataReqType *EeReadDataReq;
                    NewSignal(sizeof(EeReadDataReqType) + sizeof(void *), (void **) &EeReadDataReq);
                    EeReadDataReq->ReturnTIPD = TIPD_APPLICATION;
                    EeReadDataReq->DataTypes = EEDT_ANYADDRESS;
                    /* getEeReadDataReqTypeDataPtr(EeReadDataReq)[0] = (void *) &eepromData; */
                    memset(&eepromData, 0x00, 1);
                    setAddressData(EEP_UserDataArea, 1);
                    SendSignal((SignalType *) EeReadDataReq, EE_PROCESS_ID, EE_PRIMITIVE, EE_READ_DATA_req);
                    setSignalHandler(APPLICATION_PROCESS_ID_PP, EEPROMWriteReadTestHandler, 0);
                }
                break;
                case CC_CONNECT_prim:
                {
                    if (firsttime) {
                        UByte * tmp;
                        /* UByte cnt;*/

                        /*MuteTransmitter();*/

                        /*for (cnt=0; cnt < 6; cnt++)*/
                        {
                            tmp = pp_get_speech_buffer(0);
                            if (tmp != 0) {
                                UByte count;
                                char* ptr;
                                ptr = StringPrint(StatusString, "***Buffer: [");
                                ptr = StrPrintHexAddr(ptr, (unsigned long) tmp);

                                for (count = 0; count < 40; count++) {
                                    tmp[count] = 0x00;
                                }

                                tmp[0] = 0xCA;
                                tmp[1] = 0xFE;
                                tmp[2] = 0xBA;
                                tmp[3] = 0xBE;
                                tmp[4] = 0;
                                tmp[5] = 0;
                                tmp[6] = 0xff;
                                tmp[7] = 0xff;

                                ptr = StringPrint(ptr, "]");
                                PrintStatus(0, StatusString);

                                {
                                    TimerType* connectionTimer = NewTimer(APPLICATION_PROCESS_ID_PP, PEIODICTIMER, 0);
                                    StartTimer(connectionTimer, 500); /* Wait 1 sec*/
                                    PrintStatus(0, "start the timer");
                                }
                            } else {
                                PrintStatus(0, "tmp==0");
                            }
                        }
                        firsttime = 0;
                    }
                }
                case CC_INFO_prim: /*do not break*/
                break;
                case CC_SETUP_ACK_prim:
                break;
                case CC_CALL_PROC_prim:
                break;
                case CC_ALERTING_prim:
                break;
                case SS_SETUP_prim:
                    handle_ss_setup(Signal);
                break;
                case SS_FACILITY_prim:
                    handle_ss_facility(Signal);
                break;
                default:
                {
                    char* ptr;
                    ptr = StringPrint(StatusString, "Unknown IWU_PRIMITIVE [0x");
                    ptr = StrPrintHexByte(ptr, Signal->SubEvent);
                    ptr = StringPrint(ptr, "]");
                    PrintStatus(0, StatusString);
                }
            }
        }
        break;
        case TIME_OUT_EVENT:
        {
            switch (Signal->SubEvent)
            {
                case SENDMSFTIMER:
                {
                    /*                    PrintStatus(0, "Sending MSF");*/
                    /*                    SendMsfMessage("2001", "OK!");*/
                }
                break;
                case WAIT_CONNECTION:
                {
                    callUser_PP(numberToDial, 0);
                    setSignalHandler(APPLICATION_PROCESS_ID_PP, PPDialingHandler, 0);
                }
                break;
                case OFFHOOKTIMER:
                {
                    if (connected) {
                        PrintStatus(0, "Accepting call!");
                        off_hook();
                    }
                }
                break;

                case PEIODICTIMER:
                {
                    UByte * tmp;
                    TimerType* connectionTimer = NewTimer(APPLICATION_PROCESS_ID_PP, PEIODICTIMER, 0);
                    PrintStatus(0, "PEIODICTIMER");
                    StartTimer(connectionTimer, 500); /* Wait 1 sec*/

                    tmp = pp_get_speech_buffer(1);
                    if (tmp != 0) {
                        int c;
                        char* ptr;
                        ptr = StringPrint(StatusString, "***Buffer: [");
                        ptr = StrPrintHexAddr(ptr, (unsigned long) tmp);
                        ptr = StringPrint(ptr, "-");

                        for (c = 0; c < 8; c++) {
                            ptr = StrPrintHexByte(ptr, tmp[c]);
                            ptr = StringPrint(ptr, ",");
                        }

                        ptr = StringPrint(ptr, "]");
                        PrintStatus(0, StatusString);

                    } else {
                        PrintStatus(0, "tmp==0");
                    }
                }
                break;
                default:
                {
                    PrintStatus(0, "Unknown TIME_OUT_EVENT in connection handler");
                }
            }
        }
        break;
        default:
        {
            PrintStatus(0, "Unknown event to connection handler");
        }
    }
    DeleteBuffer(Signal);
}
