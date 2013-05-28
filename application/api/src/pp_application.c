#include "../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../include/hlkgap/common/include/dispatch.h"
#include "../../../include/hlkgap/common/include/sformat.h"
#include "../../../include/hlkgap/iwu/include/pp/piwuprim.h"
#include "../../../include/common/include/print_status.h"
#include "../../../include/common/include/app_util.h"
#include "../../../include/common/include/_log.h"
#include "../../../include/common/include/glibc.h"
#include "../../../include/common/include/bitsdef.h"
#include "../../../include/hlkgap/common/include/aformat.h"
#include "../../../include/os/include/mailprim.h"
#include "../../../include/os/include/tasks.h"
#include "../../../include/machlinterface/include/maclink.h"
#include "../../../include/machlinterface/include/pp/mac.h"
#include "../../../include/os/include/maildef.h"
#include "../include/kt4585app_pp_app.h"
#include "../include/ciss_state.h"
#include "../include/pp_application.h"
#include "../../include/common_application.h"
#include "../include/pp/pp_subscription_callback.h"
#include "../include/pp/pp_subscription_functions.h"
#include "../include/common/common_general_callback.h"
#include "../include/common/common_general_functions.h"
#include "../include/common/common_hardware_callback.h"
#include "../include/common/common_hardware_functions.h"
#include "../include/pp/pp_msf_callback.h"
#include "../include/pp/pp_module2module_callback.h"
#include "../include/pp/pp_module2module_functions.h"
#include "../include/pp/pp_voice_callback.h"
#include "../include/DSPSignalHandler.h"

typedef enum
{
    pp_state_idle = 0, pp_state_incoming_call = 1, pp_state_outgoing_call = 2, pp_state_connected_call = 3, pp_state_overlap_outgoing_call = 4, pp_state_enblock_number_send = 5
} pp_call_state_type;

pp_call_state_type pp_call_state = pp_state_idle;

typedef enum
{
    pp_sub_state_idle = 0, pp_sub_state_delete_req = 1
} pp_sub_state_type;

pp_sub_state_type pp_sub_state = pp_sub_state_idle;

void CallForSearchRFPI(SearchModeType SearchMode, int sessionID);
void CallForSubscription(UByte *rfpi, unsigned long Code_AC, int sessionID);

extern void AskfordefaultEIPE(int sessionId);
extern Boolean NewBuffer(int BufferLength, void **BufferPointer/*, HeapNoType HeapCnt*/);
extern void *FindInfoElement(UByte InfoElementId, UByte * Message, int MessageLength);
extern void sendSelSlotInd(UByte info, int sessionID);
extern void DeleteBuffer(void * BufferPointer);
void *mem_malloc(unsigned int size, BYTE id);
extern MACLink macLink;
extern BYTE Locked2RfpiPP[5];
extern void handle_ss_release(SignalType * TheSignal);
TimerType * pp_timerPt = 0;
UByte pp_lock_state = 0;

void GetCallingPartyNo(CallingPartyNoType *CallingPartyNoPtr, char* dest, int INFO_BUFSIZE)
{
    BYTE i;
    BYTE j = 0;

    if (CallingPartyNoPtr) {
        if (CallingPartyNoPtr->NoTypAndNoPlanId & 0x80) {
            for (i = 0; i < CallingPartyNoPtr->LengthOfContents - 1; i++) {
                dest[j++] = getCallingPartyNoTypeOct3ff(CallingPartyNoPtr)[i];
                if (j == INFO_BUFSIZE)
                    break;
            }
        } else {
            if (!(getCallingPartyNoTypeOct3ff(CallingPartyNoPtr)[0] & 0x60)) /* Presentation allowed*/
            {
                for (i = 0; i < CallingPartyNoPtr->LengthOfContents - 2; i++) {
                    dest[j++] = getCallingPartyNoTypeOct3ff(CallingPartyNoPtr)[i + 1];
                    if (j == INFO_BUFSIZE)
                        break;
                }
            }
        }
    }
    dest[j] = '\0';
}

void enableAudio()
{
    SignalType * startAudio;
    NewSignal(sizeof(SignalType), (void**) &startAudio);
    SendSignal((SignalType*) startAudio, DSP_PROCESS_ID, SETUPAUDIO_EVENT, 0);
}

void stopAudio()
{
    SignalType* stopAudio;
    NewSignal(sizeof(SignalType), (void**) &stopAudio);
    SendSignal((SignalType*) stopAudio, DSP_PROCESS_ID, STOPAUDIO_EVENT, 0);
}

UByte pp_voice_sendKey(UByte key)
{
    MultiKeypadType * MultiKey_p;
    CcInfoPrimType * CcInfoPrim;

    NewSignal(sizeof(CcInfoPrimType) + sizeof(MultiKeypadType) + 1, (void**) &CcInfoPrim);

    MultiKey_p = (MultiKeypadType *) getCcInfoPrimTypeIE(CcInfoPrim);
    MultiKey_p->IEID = MultiKeypadId;
    MultiKey_p->LengthOfContents = 1;
    MultiKey_p->Keypad = key;

    SendSignal((SignalType*) CcInfoPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_INFO_prim);

    return 0;
}

/****************************************************************************
 * Name      : SendSsSetup                                                   *
 * Input     :                                                               *
 * Output    :  -                                                            *
 *---------------------------------------------------------------------------*
 * Description: Send SsSetupPrim for setting up MSF connection               *
 ****************************************************************************/
void SendSsSetup(void)
{
    SsSetupPrimType * SsSetupPrim;

    NewBuffer(sizeof(SsSetupPrimType), (void**) &SsSetupPrim);
    SsSetupPrim->SignalHeader.SignalLength = sizeof(SsSetupPrimType);
    SendSignal((SignalType*) SsSetupPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_SETUP_prim);
}

void SendAlarmTelegram(UByte value)
{
    SsFacilityPrimType * SsFacilityPrim;
    IwuToIwuType * IwuToIwu;
    PPStatusInfoIEType * PPStatusInfoIE;

    /*An IwuToIwu element with KIRK EMC is sent to the base.*/
    NewBuffer(sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(PPStatusInfoIEType) + 1/*1databyte*/, (void**) &SsFacilityPrim);
    SsFacilityPrim->SignalHeader.SignalLength = sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(PPStatusInfoIEType) + 1;
    IwuToIwu = (IwuToIwuType *) getSsFacilityPrimTypeIE(SsFacilityPrim);
    IwuToIwu->IEID = IwuToIwuId;
    IwuToIwu->LengthOfContents = sizeof(IwuToIwuType) - 2 + sizeof(PPStatusInfoIEType) + 1;
    IwuToIwu->ProtocolDiscrim = UserSpecific;
    IwuToIwu->DiscrimType = UseOfEmc;
    *((WORD*) IwuToIwu->Emc) = 0x01C8;
    PPStatusInfoIE = (PPStatusInfoIEType *) getIwuToIwuSIE(IwuToIwu);
    PPStatusInfoIE->IEID = EscapeForExtensionId;
    PPStatusInfoIE->LengthOfContents = sizeof(PPStatusInfoIEType) - 2 + 1;
    PPStatusInfoIE->APEIEID = PPStatusInfoAPEIEId;
    PPStatusInfoIE->StatusType = value;

    getPPStatusInfoIETypeIE(PPStatusInfoIE)[0] = 0;
    /*if (CissState != CISS_CONNECT)*/
    { /*   SendSsSetup();*/
        SsSetupPrimType * SsSetupPrim;
        NewSignal(sizeof(SsSetupPrimType), (void**) &SsSetupPrim);
        SendSignal((SignalType*) SsSetupPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_SETUP_prim);
    }

    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_FACILITY_prim);
    _sprintf_(StatusString, "SendAlarmTelegram %x", value);
    PrintStatus(0x55, StatusString);

} /* Void SendAlarmTelegram(InitiatorType Initiator) */

void SendPPStatusInd(BYTE statusType, BYTE data[], BYTE data_length)
{
    SsFacilityPrimType * SsFacilityPrim;
    IwuToIwuType * IwuToIwu;
    PPStatusInfoIEType * PPStatusInfoIE;

    NewBuffer(sizeof(SignalType) + offsetof(IwuToIwuType,Emc) + 2 + offsetof(PPStatusInfoIEType,StatusType) + 1 + data_length, (void**) &SsFacilityPrim);
    SsFacilityPrim->SignalHeader.SignalLength = sizeof(SignalType) + offsetof(IwuToIwuType,Emc) + 2 + offsetof(PPStatusInfoIEType,StatusType) + 1 + data_length;
    IwuToIwu = (IwuToIwuType *) getSsFacilityPrimTypeIE(SsFacilityPrim);
    IwuToIwu->IEID = IwuToIwuId;
    IwuToIwu->LengthOfContents = offsetof(IwuToIwuType,Emc) + 2 - 2 + offsetof(PPStatusInfoIEType,StatusType) + 1 + data_length;
    IwuToIwu->ProtocolDiscrim = UserSpecific;
    IwuToIwu->DiscrimType = UseOfEmc;
    *((WORD*) IwuToIwu->Emc) = HandsetEMC;
    PPStatusInfoIE = (PPStatusInfoIEType *) getIwuToIwuSIE(IwuToIwu);
    PPStatusInfoIE->IEID = EscapeForExtensionId;
    PPStatusInfoIE->LengthOfContents = offsetof(PPStatusInfoIEType,StatusType) - 1 + data_length;
    PPStatusInfoIE->APEIEID = PPStatusInfoAPEIEId;
    PPStatusInfoIE->StatusType = statusType;
    memcpy((BYTE*) getPPStatusInfoIETypeIE(PPStatusInfoIE), data, data_length);
    SendSsSetup();

    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_FACILITY_prim);
}

void start_pp(int sessionID)
{
    SignalType * ActivateSignal;
    ProcessIdType ProcessId = IWU_PROCESS_ID;
    EventType Event = ACTIVATE_EVENT;
    SubEventType SubEvent = 0;

    NewSignal(sizeof(SignalType), (void**) &ActivateSignal);

    PrintStatus(0, "start_pp");

    InjectSignal(ActivateSignal, ProcessId, Event, SubEvent, sessionID);

    AskfordefaultEIPE(sessionID);
}

static UByte rfpi[5];

void subscribe_to_locked_base(int sessionID)
{
    PrintStatus(0, "CallForSearchRFPI_2");

    CallForSearchRFPI(SM_Passiv, sessionID);

    CallForSubscription((UByte*) &rfpi, 0xFFFFFFFF, sessionID);
}

void handle_om_subs_create(SignalType * TheSignal)
{
    OmSubsCreateCfmType *OmSubsCreateCfm = (OmSubsCreateCfmType *) TheSignal;
    if (OmSubsCreateCfm->NotAccepted) {
        PrintStatus(0, "*** FAILED!!\n");
    } else {
        PrintStatus(0, "*** OK\n");
    }

}

void CallForSearchRFPI(SearchModeType SearchMode, int sessionID)
{
    OmSearchRfpiReqType *OmSearchRfpiReq;
    PrintStatus(0, "CallForSearchRFPI3");

    NewBuffer(sizeof(OmSearchRfpiReqType), (void **) &OmSearchRfpiReq);
    OmSearchRfpiReq->SignalHeader.SignalLength = sizeof(OmSearchRfpiReqType);
    OmSearchRfpiReq->SearchMode = SearchMode;
    InjectSignal((SignalType *) OmSearchRfpiReq, IWU_PROCESS_ID, IWU_PRIMITIVE, OM_SEARCH_RFPI_req, sessionID);
}

void CallForSubsSelect(BYTE SubscriptionNo, int sessionID)
{
    OmSubsSelectReqType *OmSubsSelectReq;
    PrintStatus(0, "CallForSubsSelect");

    NewBuffer(sizeof(OmSubsSelectReqType), (void **) &OmSubsSelectReq);
    OmSubsSelectReq->SignalHeader.SignalLength = sizeof(OmSubsSelectReqType);
    OmSubsSelectReq->SubsNo = SubscriptionNo;
    InjectSignal((SignalType *) OmSubsSelectReq, IWU_PROCESS_ID, IWU_PRIMITIVE, OM_SUBS_SELECT_req, sessionID);
}

/****************************************************************************
 * Name      : SendSubsRemove                                                *
 * Input     :  -                                                            *
 * Output    :  -                                                            *
 *---------------------------------------------------------------------------*
 * Description: Remove the active subscription, set by CallForSubsSelect     *
 ****************************************************************************/
void SendSubsRemove(int sessionID)
{
    OmSubsRemoveReqType * OmSubsRemoveReq;
    NewBuffer(sizeof(OmSubsRemoveReqType), (void**) &OmSubsRemoveReq);
    OmSubsRemoveReq->SignalHeader.SignalLength = sizeof(OmSubsRemoveReqType);
    InjectSignal((SignalType*) OmSubsRemoveReq, IWU_PROCESS_ID, IWU_PRIMITIVE, OM_SUBS_REMOVE_req, sessionID);
}

extern CissStateType CissState;

void CallForSubscription(UByte *rfpi, unsigned long Code_AC, int sessionID)
{
    UByte SignalLen;
    BYTE i, Deployment = 0;
    OmSubsCreateReqType * OmSubsCreateReq;
    FixedIdentityType * FixedIdentity;
    IwuToIwuType * IwuToIwu;
    AcIEType * AcIe_p;
    UByte HandsetLocalNr = 0xF2;
    char* ptr;

    ptr = StringPrint(StatusString, "CallForSubscription[");
    ptr = StrPrintHexByte(ptr, *(rfpi + 0));
    ptr = StrPrintHexByte(ptr, *(rfpi + 1));
    ptr = StrPrintHexByte(ptr, *(rfpi + 2));
    ptr = StrPrintHexByte(ptr, *(rfpi + 3));
    ptr = StrPrintHexByte(ptr, *(rfpi + 4));
    ptr = StringPrint(ptr, "]");

    PrintStatus(0, StatusString);

    if (*(rfpi + 0) & 0x70) /*ARI class B,C or D*/
    {
        i = MaxParkOctets - 1;
        SignalLen = sizeof(OmSubsCreateReqType) + (4 + i) + sizeof(AcIEType);
        PrintStatus(0, "ARI class B,C or D");
    } else /*ARI class A*/
    {
        PrintStatus(0, "ARI class A");
        i = MaxParkOctets;
        if (HandsetLocalNr & 0x0f && (HandsetLocalNr & 0x0f) < 9) {
            SignalLen = sizeof(OmSubsCreateReqType) + (4 + i) + (sizeof(IwuToIwuType) + 2) + sizeof(AcIEType);
            Deployment = 1;
            PrintStatus(0, "Deployment=1\n");
        } else {
            SignalLen = sizeof(OmSubsCreateReqType) + (4 + i) + sizeof(AcIEType);
        }
    }

    NewBuffer(SignalLen, (void**) &OmSubsCreateReq);
    OmSubsCreateReq->SignalHeader.SignalLength = SignalLen;

    FixedIdentity = (FixedIdentityType *) getOmSubsCreateReqTypeIE(OmSubsCreateReq);
    FixedIdentity->IEID = FixedId;
    FixedIdentity->LengthOfContents = i + 2;
    FixedIdentity->IdentityType = ParkCode;

    if (*(rfpi + 0) & 0x70) /*ARI class B,C or D*/
    {
        FixedIdentity->IdentityValue.Park.LengthOfIdentityValue = (31 + 1) | 0x80;
    } else /*ARI class A*/
    {
        FixedIdentity->IdentityValue.Park.LengthOfIdentityValue = (36 + 1) | 0x80;
    }

    memcpy(FixedIdentity->IdentityValue.Park.ParkValue, rfpi, i);

    if (Deployment) /*IwuToIwu info with Eric EMC and local no. send for subscribtion on "DEPLOYMENT BASE"*/
    { /*or Eric base.(To make subscribtion secure and for knowing the number.)*/
        IwuToIwu = (IwuToIwuType *) (getOmSubsCreateReqTypeIE(OmSubsCreateReq) + (4 + i));
        IwuToIwu->IEID = IwuToIwuId;
        IwuToIwu->LengthOfContents = sizeof(IwuToIwuType) - 2 + 2; /* 2 = handset no.*/
        IwuToIwu->ProtocolDiscrim = UserSpecific;
        IwuToIwu->DiscrimType = UseOfEmc;
        if (HandsetLocalNr & 0x80) /* Use Eric EMC if bit 7 set!*/
        {
            *((WORD*) IwuToIwu->Emc) = 0x4B00; /*ERIC_EMC;*/
        } else {
            *((WORD*) IwuToIwu->Emc) = 0x4D00; /* HandsetEMC;*/
        }

        *((WORD*) getIwuToIwuSIE(IwuToIwu)) = (WORD) HandsetLocalNr & 0x000f;
        AcIe_p = (AcIEType *) (getOmSubsCreateReqTypeIE(OmSubsCreateReq) + (4 + i) + sizeof(IwuToIwuType) + 2);
    } else {
        AcIe_p = (AcIEType *) (getOmSubsCreateReqTypeIE(OmSubsCreateReq) + (4 + i));
    }

    AcIe_p->IEID = EscapeForExtensionId;
    AcIe_p->LengthOfContents = MaxAcOctets + 1;
    AcIe_p->PEIEID = AcPEIEId;
    for (i = 0; i < 4; i++)
        /*AC allways 4 bytes!*/
        AcIe_p->Ac[3 - i] = *(((BYTE *) (&Code_AC)) + i); /* Write LONG Code_AC to array AcIe->Ac[]*/

    InjectSignal((SignalType*) OmSubsCreateReq, IWU_PROCESS_ID, IWU_PRIMITIVE, OM_SUBS_CREATE_req, sessionID);
}

static char calluser_number[14];

void callUser_PP(char * number, int sessionId)
{
    CcSetupPrimType * CcSetupPrim;
    BasicServiceType * BasicService;
    memset(calluser_number, 0, 14);
    memcpy(calluser_number, number, strlen(number));

    NewBuffer(sizeof(CcSetupPrimType) + sizeof(BasicServiceType), (void**) &CcSetupPrim);
    CcSetupPrim->SignalHeader.SignalLength = sizeof(CcSetupPrimType) + sizeof(BasicServiceType);
    BasicService = (BasicServiceType *) getCcSetupPrimTypeIE(CcSetupPrim);
    BasicService->IEID = BasicServiceId;
    BasicService->CallClassAndBasicService = 0x80; /*NormalCallSetup*/
    InjectSignal((SignalType*) CcSetupPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_SETUP_prim, sessionId);
}

void pp_voice_call_user(char * number)
{
  if (*number==0) // Empty number - go directly to connection
    pp_call_state = pp_state_connected_call;
  else
    pp_call_state = pp_state_outgoing_call;
    callUser_PP(number, 0);
}

UByte pp_voice_offhook()
{
    if (pp_call_state == pp_state_incoming_call) {
        CcConnectPrimType * CcConnectPrim;
        SignalType * startAudio;

        NewBuffer(sizeof(CcConnectPrimType), (void**) &CcConnectPrim);
        CcConnectPrim->SignalHeader.SignalLength = sizeof(CcConnectPrimType);
        SendSignal((SignalType*) CcConnectPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_CONNECT_prim);

        NewSignal(sizeof(SignalType), (void**) &startAudio);
        SendSignal((SignalType*) startAudio, DSP_PROCESS_ID, SETUPAUDIO_EVENT, 0);
        pp_call_state = pp_state_connected_call;
        return 0;
    } else if (pp_call_state == pp_state_idle) {
        pp_call_state = pp_state_overlap_outgoing_call;
        callUser_PP("", 0);
        return 0;
    } else {
        return 1;
    }
}

UByte pp_voice_onhook()
{
    CcReleasePrimType * CcReleasePrim;
    ReleaseReasonType * ReleaseReason;

    NewBuffer(sizeof(CcReleasePrimType) + sizeof(ReleaseReasonType), (void**) &CcReleasePrim);
    CcReleasePrim->SignalHeader.SignalLength = sizeof(CcReleasePrimType) + sizeof(ReleaseReasonType);
    ReleaseReason = (ReleaseReasonType *) getCcReleasePrimTypeIE(CcReleasePrim);
    ReleaseReason->IEID = ReleaseReasonId;
    ReleaseReason->ReleaseReasonCode = NormalReleaseReason;
    SendSignal((SignalType*) CcReleasePrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_RELEASE_prim);
    return 0;
}

static UByte subscribeTo[5];
static unsigned long subscribeTo_ac_code;
static UByte subscription_mode = 0;

extern int readableAriToRfpi(char * readableAri, char * rfpi);

UByte pp_subscription_subscribe(UByte subscriptionIndex, char * readableAri, char * ari, unsigned long Code_AC)
{
    char* ptr;
    if(subscriptionIndex==0 || subscriptionIndex>1){
        PrintStatus(0,"Illegal index");
        return 2;
    }
    subscribeTo_ac_code = Code_AC;
    if (readableAri != 0 && strlen(readableAri) > 8) {
        readableAriToRfpi(readableAri, (char*) subscribeTo);
    } else if (ari != 0) {
        memcpy(subscribeTo, ari, 5);
    } else {
        return 1;
    }

    ptr = StringPrint(StatusString, "calling search and select[");
    ptr = StrPrintHexByte(ptr, subscribeTo[0]);
    ptr = StrPrintHexByte(ptr, subscribeTo[1]);
    ptr = StrPrintHexByte(ptr, subscribeTo[2]);
    ptr = StrPrintHexByte(ptr, subscribeTo[3]);
    ptr = StrPrintHexByte(ptr, subscribeTo[4]);
    ptr = StringPrint(ptr, "]");

    PrintStatus(0, StatusString);

    CallForSubsSelect(subscriptionIndex, 0);
    subscription_mode = 1;

    return 0;
}

UByte pp_subscription_searchForBases()
{
    CallForSearchRFPI(SM_FindRfpis, 0);
    return 0;
}

void pp_subscription_stopSearch()
{
    CallForSearchRFPI(SM_Passiv, 0);
}

UByte pp_subscription_loginToBase(UByte subscriptionIndex)
{
    if(subscriptionIndex==0 || subscriptionIndex>1){
        PrintStatus(0,"Illegal index");
        return 2;
    }
    CallForSubsSelect(subscriptionIndex, 0);
    return 0;
}

void pp_subscription_getAriResult(int subscriptionIndex)
{
    MacReadPPUserType read;
    if(subscriptionIndex==0 || subscriptionIndex>1){
        PrintStatus(0,"Illegal index");
        return;
    }
    read.Primitive = PPREADUSER;
    read.index = subscriptionIndex;
    macLink.sendMailToMac((MailType *) &read, sizeof(MacReadPPUserType), 0, 0, 30);
}

static UByte indexToDelete = 0xff;

void pp_subscription_delete(int index)
{
    if(index==0 || index>1){
        PrintStatus(0,"Illegal index");
        return;
    }
    pp_sub_state = pp_sub_state_delete_req;
    CallForSubsSelect(index, 0);
    indexToDelete = index;
}

extern UByte at_msf_handler(SignalType * Signal);
extern UByte common_signalHander(SignalType * TheSignal);

#define PP_WAIT_FOR_INIT 0x70

extern UByte timerStarted;
extern char *getReadableARI(UByte* rfpi);

void ApplicationSignalHandler_PP(SignalType * Signal)
{
    if (common_signalHander(Signal)) {
        return;
    }

    switch (Signal->Event)
    {
        case INITIALIZE_EVENT:
        {
            /*DeleteBuffer(Signal);*/
            /*return;*/
            TimerType * timer = NewTimer(APPLICATION_PROCESS_ID_PP, PP_WAIT_FOR_INIT, 0);
            StartTimer(timer, 200);
            PrintStatus(0, "ApplicationSignalHandler_PP.INITIALIZE_EVENT");
            /*pp_system_init();*/
        }
        break;
        case APPLICATION_PRIMITIVE:
        {
            switch (Signal->SubEvent)
            {
                case USERRESULT_EVENT:
                {
                    EE_RfpiType* rfpi;
                    char * readbleAri;
                    rfpi=(EE_RfpiType *)(getSignalData(Signal) + 1);
                    readbleAri= getReadableARI(rfpi->RfpiValue);
                    pp_subscription_ariResult(readbleAri, (char*) rfpi->RfpiValue, getSignalData(Signal)[0]);
                    mem_free(readbleAri);
                }
                break;
                case MSFInd:
                {
                    AppMSFType* msfInd = (AppMSFType*) Signal;
                    char* msf = mem_malloc(msfInd->length + 1, 100);
                    memcpy(msf, getAppMSFTypeIE(msfInd), msfInd->length);
                    msf[msfInd->length] = '\0';
                    PrintStatus(0, msf);
                    mem_free(msf);
                    break;
                }
                case MAC_APP_TUNNEL:
                {
                    KeyActionType * key = (KeyActionType*) Signal;
                    if (key->key == 0xfe) {
                        if (key->action == 0 || key->action == 1) {
                            pp_common_playsound_ack(key->action);
                        } else if (key->action == 2) {
                            pp_common_playsound_finished();
                        }
                    }
                }
                break;

                case 0x86:
                {
                    pp_module2module_ack_received(getSignalData(Signal) + 1);
                }break;
            }
        }
        break;
        case IWU_PRIMITIVE:
        {
            switch (Signal->SubEvent)
            {
                case CC_SETUP_prim:
                {
                    char CallingPartyNo[32];

                    CcSetupPrimType *CcSetupPrim = (CcSetupPrimType *) Signal;
                    CallingPartyNoType *CallingPartyNoPtr;
                    SignalIEType *SignalIE;
                    /*TimerType * timer = NewTimer(APPLICATION_PROCESS_ID_PP, OFFHOOKTIMER, 0);*/
                    /*StartTimer(timer, 200); // wait 2 sec before accepting call*/

                    CallingPartyNoPtr = (CallingPartyNoType *) FindInfoElement(CallingPartyNoId, getCcSetupPrimTypeIE(CcSetupPrim) - 2, CcSetupPrim-> SignalHeader. SignalLength - sizeof(CcSetupPrimType) + 2);

                    GetCallingPartyNo(CallingPartyNoPtr, CallingPartyNo, 32);

                    SignalIE = (SignalIEType *) FindInfoElement(SignalId, getCcSetupPrimTypeIE(CcSetupPrim) - 2, CcSetupPrim->SignalHeader. SignalLength - sizeof(CcSetupPrimType) + 2);
                    if (SignalIE) {
                    } else {
                        PrintStatus(0, "No SignalIE! EXTERNAL_RING");
                    }
                    Signal->SignalLength = sizeof(CcAlertingPrimType);
                    SendSignal(Signal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_ALERTING_prim);

                    pp_call_state = pp_state_incoming_call;
                    pp_voice_incommingCall(CallingPartyNo);
                    return;
                }
                case CC_RELEASE_COM_prim:
                    if (pp_call_state != pp_state_idle) {
                        SignalType* stopAudio;
                        pp_call_state = pp_state_idle;
                        NewSignal(sizeof(SignalType), (void**) &stopAudio);
                        SendSignal((SignalType*) stopAudio, DSP_PROCESS_ID, STOPAUDIO_EVENT, 0);
                        pp_voice_call_released(0);
                    }
                break;
                case CC_RELEASE_prim:
                    Signal->SignalLength = sizeof(CcReleaseComPrimType);
                    SendSignal(Signal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_RELEASE_COM_prim);
                    if (pp_call_state != pp_state_idle) {
                        SignalType* stopAudio;
                        pp_call_state = pp_state_idle;
                        NewSignal(sizeof(SignalType), (void**) &stopAudio);
                        SendSignal((SignalType*) stopAudio, DSP_PROCESS_ID, STOPAUDIO_EVENT, 0);
                        pp_voice_call_released(0);
                    }
                    return;
                case CC_CONNECT_ACK_prim:
                break;
                case CC_CONNECT_prim:
                {
                    if (pp_call_state == pp_state_outgoing_call) {
                        SignalType* mySignal;
                        NewSignal(sizeof(SignalType) + 2 + strlen(calluser_number), (void **) &mySignal);
                        getSignalData(mySignal)[0] = 0x2c;
                        getSignalData(mySignal)[1] = strlen(calluser_number);
                        memcpy(getSignalData(mySignal) + 2, calluser_number, strlen(calluser_number));

                        InjectSignal(mySignal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_INFO_prim, Signal->SessionId);/*CC_INFO_prim (DDU)             0F.80.2C.04.33.30.30.31*/
                    }

                    if (pp_call_state == pp_state_overlap_outgoing_call) {
                        pp_voice_offhook_ready();/*call new api function: pp_voice_offhook_ready*/
                        pp_call_state = pp_state_connected_call; /*??*/
                    } else {
                        pp_call_state = pp_state_connected_call;
                        enableAudio();
                    }
                }
                case CC_INFO_prim: /*do not break*/
                {
                    SignalIEType * SignalIE;
                    MultiDisplayType * MultiDisplayPtr;
                    UByte info_type = 0xff;
                    char * display = 0;
                    UByte display_length = 0;
                    CcInfoPrimType * CcInfoPrim = (CcInfoPrimType *) Signal;

                    SignalIE = (SignalIEType *) FindInfoElement(SignalId, getCcInfoPrimTypeIE(CcInfoPrim) - 2, CcInfoPrim->SignalHeader.SignalLength - sizeof(SignalType) + 2);
                    if (SignalIE != NULL) {
                        info_type = SignalIE->SignalValue;
                    }

                    MultiDisplayPtr = (MultiDisplayType *) FindInfoElement(MultiDisplayId, getCcInfoPrimTypeIE(CcInfoPrim) - 2, CcInfoPrim->SignalHeader.SignalLength - sizeof(SignalType) + 2);
                    if (MultiDisplayPtr != NULL) {
                        UByte cnt = 0;
                        display = ((char*) &MultiDisplayPtr->LengthOfContents) + sizeof(UByte);
                        display_length = MultiDisplayPtr->LengthOfContents;

                        while (display[0] < 0x20 && cnt < display_length)
                        {
                            display++;
                            cnt++;
                        }
                        display_length -= cnt;

                        if (info_type == 0xff) {
                            info_type = 0xfe;
                        }
                    } else {
                        char tmp_display[1];
                        tmp_display[0] = 0;
                        display = tmp_display;
                    }

                    pp_voice_info_received(info_type, display, display_length);
                }
                break;
                case CC_SETUP_ACK_prim:
                if (pp_call_state == pp_state_outgoing_call) {
                    SignalType* mySignal;
                    NewSignal(sizeof(SignalType) + 2 + strlen(calluser_number), (void **) &mySignal);
                    getSignalData(mySignal)[0] = 0x2c;
                    getSignalData(mySignal)[1] = strlen(calluser_number);
                    memcpy(getSignalData(mySignal) + 2, calluser_number, strlen(calluser_number));

                    pp_call_state = pp_state_enblock_number_send;

                    InjectSignal(mySignal, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_INFO_prim, Signal->SessionId);/*CC_INFO_prim (DDU)             0F.80.2C.04.33.30.30.31*/
                }
                break;
                case CC_CALL_PROC_prim:
                break;
                case CC_ALERTING_prim:
                break;
                case OM_SUBS_CREATE_cfm:
                {
                    OmSubsCreateCfmType *OmSubsCreateCfm = (OmSubsCreateCfmType *) Signal;

                    subscription_mode = 0;

                    if (OmSubsCreateCfm->NotAccepted) {
                        PrintStatus(0, "Subscription failed");
                        /*CallForSubscription(baseToSubscribeTo, 0xFFFFFFFF, 0);*/
                        pp_subscription_subscribeFinished(2);
                    } else {
                        PrintStatus(0, "Subscription succeeded");
                        /*setSignalHandler(APPLICATION_PROCESS_ID_PP, PPAlreadySubscribedHandler, 0);*/
                        pp_subscription_subscribeFinished(0);
                    }
                    /*handle_om_subs_create(Signal);*/
                }
                break;
                    /*case OM_SUBS_STATUS_ind:
                     {
                     OmSubsStatusIndType *OmSubsStatusInd = (OmSubsStatusIndType *) Signal;
                     switch (OmSubsStatusInd->Status)
                     {
                     case SS_Locked:
                     break;
                     case SS_Subscripted:
                     break;
                     case SS_Locked | SS_Subscripted:
                     break;
                     case SS_Locked | SS_Subscripted | SS_LocRegSucceeded:
                     break;
                     case SS_LocRegSucceeded:
                     break;
                     default:
                     break;
                     }
                     break;
                     }*/
                case OM_SUBS_STATUS_ind:
                {
                    OmSubsStatusIndType *OmSubsStatusInd = (OmSubsStatusIndType *) Signal;
                    pp_lock_state = OmSubsStatusInd->Status;
                    if (pp_sub_state == pp_sub_state_delete_req) {

                    } else {
                        pp_subscription_statusReceived(OmSubsStatusInd->Status, OmSubsStatusInd->SubsNo);
                    }
                }
                break;

                case OM_SUBS_SELECT_cfm:
                {
                    OmSubsSelectCfmType *OmSubsSelectCfm = (OmSubsSelectCfmType *) Signal;
                    char* tmp;
                    if (OmSubsSelectCfm->NotAccepted) {
                        PrintStatus(0, "Subscription select failed!");
                        if (subscription_mode) {
                            pp_subscription_subscribeFinished(1);
                            subscription_mode = 0;
                        }
                    } else {
                        if (pp_sub_state == pp_sub_state_delete_req) {
                            /*pp_sub_state = pp_sub_state_idle;*/
                            SendSubsRemove(0);
                        } else if (subscription_mode) {
                            /*CallForSearchRFPI(SM_Passiv, 0);*/
                            CallForSubscription(subscribeTo, subscribeTo_ac_code, 0);
                        }
                    }
                    tmp = StatusString;
                    tmp = StringPrint(tmp, "\r\nApplicationSignalHandler - OM_SUBS_SELECT_cfm (NotAccepted = ");
                    tmp = StrPrintHexNibble(tmp, OmSubsSelectCfm->NotAccepted);
                    PrintStatus(0, StatusString);
                }
                break;
                case OM_SEARCH_RFPI_ind:
                {
                    char* readableAri;
                    OmSearchRfpiIndType * OmSearchRfpiInd = (OmSearchRfpiIndType *) Signal;
                    readableAri = getReadableARI(OmSearchRfpiInd->Rfpi);
                    pp_subscription_baseFound(readableAri, (char*) OmSearchRfpiInd->Rfpi);
                    mem_free(readableAri);
                }
                break;
                case OM_PROMPT_UPI_ind:
                break;
                case OM_SUBS_REMOVE_cfm:
                {
                    OmSubsRemoveCfmType *omSubsRemoveCfmType = (OmSubsRemoveCfmType*) Signal;
                    pp_sub_state = pp_sub_state_idle;

                    pp_subscription_deleted(omSubsRemoveCfmType->NotAccepted);
                }
                break;
                case OM_SUBS_REMOVE_ind:
                break;
                case OM_ATTACH_ind:
                {

                    OmAttachIndType * OmAttachInd = (OmAttachIndType *) Signal;
                    IwuToIwuType * IwuToIwuPtr;
                    SysBearerInfoIEType * SysBearerInfoIE;
                    char stbTxt[37];
                    memset(stbTxt, 0, 37);

                    IwuToIwuPtr = (IwuToIwuType *) FindInfoElement(IwuToIwuId, getOmAttachIndTypeIE(OmAttachInd) - 2, OmAttachInd->SignalHeader.SignalLength - sizeof(OmAttachIndType) + 2);
                    if (IwuToIwuPtr != NULL) {
                        if (IwuToIwuPtr->ProtocolDiscrim == UserSpecific && IwuToIwuPtr->DiscrimType == UseOfEmc /*&&
                         (*(WORD *)&IwuToIwuPtr->Emc)==HandsetEMC*/) {
                            StandByTxtIEType *standbyText = (StandByTxtIEType *) FindInfoElement(StandByTxtAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2, OmAttachInd->SignalHeader.SignalLength - sizeof(OmAttachIndType) - sizeof(IwuToIwuType)
                                    + 2);
                            if (standbyText) {
                                memcpy(stbTxt, standbyText->StandByTxt, standbyText->LengthOfContents > 36 ? 36 : (standbyText->LengthOfContents - 1));
                            }

                            SysBearerInfoIE = (SysBearerInfoIEType *) FindInfoElement(SysBearerInfoAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2, OmAttachInd->SignalHeader.SignalLength - sizeof(OmAttachIndType) - sizeof(IwuToIwuType) + 2);

                            if (SysBearerInfoIE != NULL) {
                                sendSelSlotInd(*(BYTE*) &SysBearerInfoIE->SysBearerInfo, Signal->SessionId);
                            }
                        }
                    }
                    pp_subscription_loginOk(stbTxt);
                }
                break;
                case SS_SETUP_prim:
                    handle_ss_setup(Signal);
                break;
                case SS_FACILITY_prim:
                    if (!at_msf_handler(Signal)) {
                        handle_ss_facility(Signal);
                    }
                break;
                case SS_RELEASE_prim:
                {
                    pp_msf_release_received(getSignalData(Signal)[1]);
                    handle_ss_release(Signal);
                }
                break;
                case EE_PRIMITIVE:
                break;
            };
        }
        break;
        case MAC_PRIMITIVE:
        {
        	switch (Signal->SubEvent)
        	{
				case LONGBROADCAST_ind:
				{
					LongBroadcastType *longbroadcastInd = (LongBroadcastType *) Signal;
					if(pp_lock_state == (SS_Locked | SS_Subscripted | SS_LocRegSucceeded)) /*Prevent broadcasts from other systems*/
						pp_msf_broadcast_received(longbroadcastInd->Info, longbroadcastInd->Length);
				}
        	}
        }
        break;
        case TIME_OUT_EVENT:
        {
            TimerType * timerPtr = (TimerType*) Signal;
            UByte dataLength;

            if (Signal->SubEvent == PP_WAIT_FOR_INIT) {
                pp_system_init();
                start_pp(0);
                DeleteBuffer(Signal);
                return;
            }

            dataLength = Signal->SignalLength - timerSize();

            pp_general_timeout(PMID2PPID(Signal->Address), Signal->SubEvent, getTimerData(timerPtr), dataLength);
        }
        break;
    }
    DeleteBuffer(Signal);

}

