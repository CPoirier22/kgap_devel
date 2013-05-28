#include "../../include/pp/pp_msf_functions.h"
#include "../../include/pp_application.h"
#include "../../../../include/hlkgap/common/include/aformat.h"

extern CissStateType CissState;
extern void SendCissRelease(void);
extern void SendFacility(BYTE Key,SendPrimitiveType Primitive);
extern void SendPPStatusInd(BYTE statusType, BYTE data[], BYTE data_length);
extern Boolean NewBuffer(int BufferLength, void **BufferPointer/*, HeapNoType HeapCnt*/);

UByte pp_msf_send_release_ind(UByte reason)
{
    if (CissState != CISS_RELEASED)
    {
        SendCissRelease();
        return 1;
    }
    return 0;
}

extern void sendShortFacility(UByte data[],UByte length);

UByte pp_send_module2module(module2moduleData data)
{
    if (CissState == CISS_CONNECT || 1/*voice connected*/)
    {
        sendShortFacility(data,3);
        return 1;
    }
    return 0;
}

UByte pp_msf_send_keypad_ind(UByte key)
{
    if (CissState == CISS_CONNECT)
    {
        SendFacility(key,SEND_AS_SS_FACILITY);
        return 1;
    }
    return 0;
}

extern UByte ppstatusindsend;

UByte pp_msf_send_ppstatus_ind(UByte statusType, UByte * data, UByte dataLength)
{
    if (dataLength > 100)
    {
        return 1;
    }
    else
    {
        ppstatusindsend = 1;
        SendPPStatusInd(statusType, data, dataLength);
        return 0;
    }
}

UByte pp_msf_send_connect_cfm()
{
    if (CissState == CISS_SETUP_RECEIVED || CissState == CISS_CONNECTIONPENDING)
    {
        SendFacility(0x11,SEND_AS_SS_FACILITY); /*ascii DC1 for ENTER. (auto offhook)*/
        CissState = CISS_CONNECT;
        return 1;
    }
    return 0;
}

void SendMsfFunction(char * functionNumber);

UByte pp_msf_send_setup_ind(char * functionNumber)
{
    if (CissState == CISS_RELEASED)
    {

        SendMsfFunction(functionNumber);
        return 0;
    }
    else
    {
        PrintStatus(0,"ciss not released");
        return 1;
    }

}

void pp_msf_send_outg_message_ind(UByte setupSpec2, UByte setupSpec3, alertConstructiontType alertConstruction, UByte displayTimeout, char * destination, char * display, char * callbackNumber)
{

    SsFacilityPrimType * SsFacilityPrim;
    IwuToIwuType * IwuToIwu;
    MSFOutgMessageIEType * MSFOutgMessageIE;
    BYTE DestLen = strlen(destination);
    BYTE MsgLen = strlen(display);
    BYTE CallBackLen = destination==0?0:strlen(callbackNumber);
    BYTE OutgMessLen = sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(MSFOutgMessageIEType) + DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen) + CallBackLen + sizeof(CallBackLen);
    SendSsSetup();

    NewBuffer(OutgMessLen, (void**) &SsFacilityPrim);
    SsFacilityPrim->SignalHeader.SignalLength = OutgMessLen;

    IwuToIwu = (IwuToIwuType *) getSsFacilityPrimTypeIE(SsFacilityPrim);
    IwuToIwu->IEID = IwuToIwuId;
    IwuToIwu->LengthOfContents = sizeof(IwuToIwuType) - 2 + sizeof(MSFOutgMessageIEType) + DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen) + CallBackLen + sizeof(CallBackLen);
    IwuToIwu->ProtocolDiscrim = UserSpecific;
    IwuToIwu->DiscrimType = UseOfEmc;
    *((WORD*) IwuToIwu->Emc) = HandsetEMC;

    MSFOutgMessageIE = (MSFOutgMessageIEType *) getIwuToIwuSIE(IwuToIwu);
    MSFOutgMessageIE->IEID = EscapeForExtensionId;
    MSFOutgMessageIE->LengthOfContents = sizeof(MSFOutgMessageIEType) - 2 + DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen) + CallBackLen + sizeof(CallBackLen);
    MSFOutgMessageIE->APEIEID = MSFOutgMessageAPEIEId;

    MSFOutgMessageIE->SetupSpec2=setupSpec2;
    MSFOutgMessageIE->SetupSpec3=setupSpec3;
    MSFOutgMessageIE->AlertPattern = alertConstruction.alertPattern;
    MSFOutgMessageIE->AlertTimeout = alertConstruction.alertTimeout;
    MSFOutgMessageIE->AlertTone = alertConstruction.alertTone;
    MSFOutgMessageIE->DisplayTimeout = displayTimeout;


    getMSFOutgMessageIETypeIE(MSFOutgMessageIE)[0] = DestLen;
    memcpy((BYTE*) getMSFOutgMessageIETypeIE(MSFOutgMessageIE) + 1, destination, DestLen);
    getMSFOutgMessageIETypeIE(MSFOutgMessageIE)[DestLen + sizeof(DestLen)] = MsgLen;
    memcpy((BYTE*) getMSFOutgMessageIETypeIE(MSFOutgMessageIE) + DestLen + sizeof(DestLen) + 1, display, MsgLen);
    getMSFOutgMessageIETypeIE(MSFOutgMessageIE)[DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen)] = CallBackLen;
    if (CallBackLen) {
        memcpy((BYTE*) getMSFOutgMessageIETypeIE(MSFOutgMessageIE) + DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen) + 1, callbackNumber, CallBackLen);
    }
    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_FACILITY_prim);
}
