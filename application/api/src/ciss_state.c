#include "../../../include/common/include/_stddef.h"
#include "../../../include/common/include/glibc.h"
#include "../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../include/hlkgap/iwu/include/pp/piwuprim.h"
#include "../../../include/hlkgap/common/include/aformat.h"
#include "../../../include/hlkgap/common/include/sformat.h"
#include "../../../include/hlkgap/common/include/dispatch.h"
#include "../../../include/mac/eeprom/include/fnvm.h"
#include "../../../include/os/include/os.h"
#include "../../../include/mac/driver/include/pp/taskdef.h"
#include "../../../include/machlinterface/include/maclink.h"
#include "../include/pp_application.h"
#include "../include/pp/pp_msf_callback.h"

extern MACLink macLink;
/* extern int currentSessionId;*/

extern PP_EepromInRamType PP_EepromInRam;

extern Boolean NewBuffer(int BufferLength, void **BufferPointer/*, HeapNoType HeapCnt*/);
extern void DeleteBuffer(void * BufferPointer);
extern void *FindInfoElement(UByte InfoElementId, UByte * Message, int MessageLength);

extern void PrintStatus(UByte StatusMessageLevel, char *msg);

#define PP6_NUMBER_SIZE     24
#define MESSAGE_LENGTH      72
#define MESSAGE_BUFSIZE     (MESSAGE_LENGTH+1)
#define PP6_NUMBER_BUFSIZE  (PP6_NUMBER_SIZE+1)

/*
 typedef enum
 {
 CISS_RELEASED,         // Call Independent Supplementary Services
 CISS_SETUP_RECEIVED,   // used for MSF (Meassage Service Functions)
 CISS_CONNECTIONPENDING,
 CISS_CONNECT
 }
 CissStateType;
 */

CissStateType CissState = CISS_RELEASED;

typedef struct
{
    UByte IEID;
    UByte LengthOfContents;
    UByte ProtocolDiscrim;
    UByte DiscrimType;
} FacilityType;

#define getFacilityTypeIE(signal) ((unsigned char*)signal + offsetof(FacilityType, DiscrimType) + sizeof(UByte))

void handle_ss_setup(SignalType * TheSignal)
{
    CissState = CISS_SETUP_RECEIVED;
}

void handle_ss_release(SignalType * TheSignal)
{
    CissState = CISS_RELEASED;
}

void SendCissRelease(void)
{
    SsReleasePrimType * SsReleasePrim;
    ReleaseReasonType * ReleaseReason;

    PrintStatus(0, "Releasing Ciss");
    NewBuffer(sizeof(SsReleasePrimType) + sizeof(ReleaseReasonType), (void**) &SsReleasePrim);
    SsReleasePrim->SignalHeader.SignalLength = sizeof(SsReleasePrimType) + sizeof(ReleaseReasonType);

    ReleaseReason = (ReleaseReasonType *) getSsReleasePrimTypeIE(SsReleasePrim);
    ReleaseReason->IEID = ReleaseReasonId;
    ReleaseReason->ReleaseReasonCode = NormalReleaseReason;
    SendSignal((SignalType*) SsReleasePrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_RELEASE_prim);

    CissState = CISS_RELEASED;
}

/****************************************************************************
 * Name      : SendMsfMessage                                                *
 * Input     : Destination,    eg. "159"                                     *
 *           : Message,        eg. "Beers in the basement"                   *
 *           : Callbacknumber, eg. "304"                                     *
 * Output    :  -                                                            *
 *---------------------------------------------------------------------------*
 * Description:                                                              *
 ****************************************************************************/
void SendMsfMessage(char *Destination, char *Message)
{
    SsFacilityPrimType * SsFacilityPrim;
    IwuToIwuType * IwuToIwu;
    char *Callbacknumber = "";
    MSFOutgMessageIEType * MSFOutgMessageIE;
    BYTE DestLen = strlen(Destination);
    BYTE MsgLen = strlen(Message);
    BYTE CallBackLen = strlen(Callbacknumber);
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

    MSFOutgMessageIE->SetupSpec2 = 0;

    getMSFOutgMessageIETypeIE(MSFOutgMessageIE)[0] = DestLen;
    memcpy((BYTE*) getMSFOutgMessageIETypeIE(MSFOutgMessageIE) + 1, Destination, DestLen);
    getMSFOutgMessageIETypeIE(MSFOutgMessageIE)[DestLen + sizeof(DestLen)] = MsgLen;
    memcpy((BYTE*) getMSFOutgMessageIETypeIE(MSFOutgMessageIE) + DestLen + sizeof(DestLen) + 1, Message, MsgLen);
    getMSFOutgMessageIETypeIE(MSFOutgMessageIE)[DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen)] = CallBackLen;
    if (CallBackLen) {
        memcpy((BYTE*) getMSFOutgMessageIETypeIE(MSFOutgMessageIE) + DestLen + sizeof(DestLen) + MsgLen + sizeof(MsgLen) + 1, Callbacknumber, CallBackLen);
    }
    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_FACILITY_prim);
}

extern void *mem_malloc(unsigned int size, BYTE id);

void SendMsfFunction(char * functionNumber)
{
    SsFacilityPrimType * SsFacilityPrim;
    IwuToIwuType * IwuToIwu;
    MsfFunctionIEType * MSFFunctionIE;

    NewBuffer(sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(MsfFunctionIEType) + strlen(functionNumber) + 1, (void**) &SsFacilityPrim);
    SsFacilityPrim->SignalHeader.SignalLength = sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(MsfFunctionIEType) + strlen(functionNumber) + 1;
    IwuToIwu = (IwuToIwuType *) getSsFacilityPrimTypeIE(SsFacilityPrim);
    IwuToIwu->IEID = IwuToIwuId;
    IwuToIwu->LengthOfContents = sizeof(IwuToIwuType) - 2 + sizeof(MsfFunctionIEType) + strlen(functionNumber) + 1;
    IwuToIwu->ProtocolDiscrim = UserSpecific;
    IwuToIwu->DiscrimType = UseOfEmc;
    *((WORD*) IwuToIwu->Emc) = HandsetEMC;
    MSFFunctionIE = (MsfFunctionIEType *) getIwuToIwuSIE(IwuToIwu);
    MSFFunctionIE->IEID = EscapeForExtensionId;
    MSFFunctionIE->LengthOfContents = sizeof(MsfFunctionIEType) - 2 + strlen(functionNumber) + 1;
    MSFFunctionIE->APEIEID = MsfFunctionAPEIEId;

    memcpy((BYTE*) &MSFFunctionIE->FunctionNo[0], functionNumber, strlen(functionNumber) + 1); /*StatusInfo*/

    if (CissState != CISS_CONNECT) {
        SendSsSetup();
        CissState = CISS_CONNECT;
    }
    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_FACILITY_prim);
}

void sendShortFacility(UByte data[], UByte length)
{
    SsFacilityPrimType * SsFacilityPrim;
    UByte * dst;
    UByte cnt;

    NewSignal(sizeof(SsFacilityPrimType) + 5, (void**) &SsFacilityPrim);
    dst = (UByte *) getSsFacilityPrimTypeIE(SsFacilityPrim);

    dst[0] = MODULE_SHORT_MSF;

    for (cnt=1; cnt<=length&&cnt<5; cnt++)
        dst[cnt] = data[cnt-1];
    for (;cnt<5;cnt++)
        dst[cnt] = 0xff;

    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_TUNNEL_prim);
}

/****************************************************************************
 * Name      : SendFacility                                                  *
 * Input     :  -                                                            *
 * Output    :  -                                                            *
 *---------------------------------------------------------------------------*
 * Description:                                                              *
 ****************************************************************************/
void SendFacility(BYTE Key, SendPrimitiveType Primitive)
{
    CcInfoPrimType * CcInfoPrim;
    SsFacilityPrimType * SsFacilityPrim;
    IwuToIwuType * IwuToIwu;
    MsfKeypadInfoIEType * MsfKeypadInfoIE;

    /*An IwuToIwu element with KIRK EMC is sent to the base, for every keypress.*/
    if (Primitive == SEND_AS_CC_INFO) {
        NewBuffer(sizeof(CcInfoPrimType) + sizeof(IwuToIwuType) + sizeof(MsfKeypadInfoIEType), (void**) &CcInfoPrim);
        CcInfoPrim->SignalHeader.SignalLength = sizeof(CcInfoPrimType) + sizeof(IwuToIwuType) + sizeof(MsfKeypadInfoIEType);
        IwuToIwu = (IwuToIwuType *) getCcInfoPrimTypeIE(CcInfoPrim);
    } else {
        NewBuffer(sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(MsfKeypadInfoIEType), (void**) &SsFacilityPrim);
        SsFacilityPrim->SignalHeader.SignalLength = sizeof(SsFacilityPrimType) + sizeof(IwuToIwuType) + sizeof(MsfKeypadInfoIEType);
        IwuToIwu = (IwuToIwuType *) getSsFacilityPrimTypeIE(SsFacilityPrim);
    }
    IwuToIwu->IEID = IwuToIwuId;
    IwuToIwu->LengthOfContents = sizeof(IwuToIwuType) - 2 + sizeof(MsfKeypadInfoIEType);
    IwuToIwu->ProtocolDiscrim = UserSpecific;
    IwuToIwu->DiscrimType = UseOfEmc;
    *((WORD*) IwuToIwu->Emc) = HandsetEMC;
    MsfKeypadInfoIE = (MsfKeypadInfoIEType *) getIwuToIwuSIE(IwuToIwu);
    MsfKeypadInfoIE->IEID = EscapeForExtensionId;
    MsfKeypadInfoIE->LengthOfContents = sizeof(MsfKeypadInfoIEType) - 2;
    MsfKeypadInfoIE->APEIEID = MsfKeypadInfoAPEIEId;

    MsfKeypadInfoIE->KeypadInfo = Key;

    if (Primitive == SEND_AS_CC_INFO)
        SendSignal((SignalType*) CcInfoPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_INFO_prim);
    else
        SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_FACILITY_prim);
}

extern void pp_msf_ppstatus_ind_ack();

UByte ppstatusindsend = 0;

void handle_ss_facility(SignalType * TheSignal)
{
    SsFacilityPrimType * SsFacilityPrim = (SsFacilityPrimType *) TheSignal;
    IwuToIwuType * IwuToIwuPtr;
    MsfSetupIEType * MsfSetupIE;
    StandByTxtIEType * StandByTxtIE;
    PPStatusInfoIEType * PPStatusInfoIE;
    FacilityType * FacilityPtr;
    MenuSelectSetupRequestIEType * MenuSelectSetupReqIE;
    AsciiStrRequestIEType * AsciiStrReqIE;
    char pp_msf_buffer[128];

    FacilityPtr = (FacilityType *) FindInfoElement(FacilityId, getSsFacilityPrimTypeIE(SsFacilityPrim) - 2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) + 2);

    IwuToIwuPtr = (IwuToIwuType *) FindInfoElement(IwuToIwuId, getSsFacilityPrimTypeIE(SsFacilityPrim) - 2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) + 2);

    if (FacilityPtr != NULL) {
        if (0x30 == getFacilityTypeIE(FacilityPtr)[12]) /* Check for Sequence*/
        {
            /* Look for Tag's only Tag3 is interesting */
            BYTE n = 14;

            if (0xa1 == getFacilityTypeIE(FacilityPtr)[14]) /*Tag1*/
                n += getFacilityTypeIE(FacilityPtr)[15] + 2;

            if (0xa2 == getFacilityTypeIE(FacilityPtr)[n]) /*Tag2*/
                n = n + getFacilityTypeIE(FacilityPtr)[n + 1] + 2;

        }
    }

    if (IwuToIwuPtr != NULL) {

        PPStatusInfoIE = (PPStatusInfoIEType *) FindInfoElement(PPStatusInfoAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2);
        if (PPStatusInfoIE != NULL) {
            if (CissState != CISS_CONNECT)
                CissState = CISS_RELEASED;
            if (PPStatusInfoIE->StatusType == 0x04 && ((PPStatusInfoIE->LengthOfContents - 2) == 0)) {
                pp_msf_ppstatus_ind_ack();
                if (CissState != CISS_CONNECT)
                {
                    SendCissRelease();
                }
            } else {
                ppstatusindsend = 0;
                pp_msf_ppstatus_req_received(PPStatusInfoIE->StatusType, getPPStatusInfoIETypeIE(PPStatusInfoIE), PPStatusInfoIE->LengthOfContents - 2);
                if (ppstatusindsend == 0)
                {
                    if (CissState != CISS_CONNECT)
                    {
                        SendCissRelease();
                    }
                }
            }
            return;
        }
    }

    switch (CissState)
    {
        case CISS_SETUP_RECEIVED:
            CissState = CISS_CONNECTIONPENDING;

        case CISS_CONNECT:
            if (IwuToIwuPtr != NULL) {
                if (IwuToIwuPtr->ProtocolDiscrim == UserSpecific) {
                    if (IwuToIwuPtr->DiscrimType == UseOfEmc) {
                        /*if ((*(WORD *)&IwuToIwuPtr->Emc)== PP_EepromInRam.FactoryEmc )*/
                        {
                            MsfSetupIE = (MsfSetupIEType *) FindInfoElement(MsfSetupAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2);

                            if (MsfSetupIE != NULL) {
                                if (!(MsfSetupIE->PpSetup & 0x80) && (CissState == CISS_CONNECTIONPENDING)) /*Page call (bit 7=0)*/
                                {
#define TxtLength      getMsfSetupIETypeIE(MsfSetupIE)[0]
#define CallbackLength getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+1]
#define SetupSpec2     getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+2]
#define SetupSpec3     getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+3]
#define AlertPattern   getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+4]
#define AlertTone      getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+5]
#define AlertTimeout   getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+6]
#define DisplayTimeout getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+7]
#define DateTimeLength getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+8]
#define BCD_Day        getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+9]
#define BCD_Month      getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+10]
#define BCD_Hour       getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+11]
#define BCD_Minute     getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+12]
#define BCD_Year       getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+13]
#define BCD_Second     getMsfSetupIETypeIE(MsfSetupIE)[TxtLength+CallbackLength+14]

                                    SendCissRelease();
                                } /* end of if "Page Call"*/
                                /**************/

                                else /*Text call*/
                                {
                                    if (MsfSetupIE->LengthOfContents < (TxtLength + CallbackLength + 5)) /*Format I setup*/
                                    {
                                    } else /*Format II setup*/
                                    {
                                        if (SetupSpec3 & MU_MASK) /* bit 0="MSF UP" (auto setup MSF connection)*/
                                        {
                                            SendFacility(0x11, SEND_AS_SS_FACILITY); /*ascii DC1 for ENTER. (auto offhook)*/
                                            CissState = CISS_CONNECT;
                                        }
                                    }
                                } /*END Text call*/

                                if (MsfSetupIE->LengthOfContents < (TxtLength + CallbackLength + 5)) /*Format I setup*/
                                {
                                    /*AppMSFType* msfType;

                                     NewSignal(sizeof(AppMSFType) + TxtLength, (void**) &msfType);

                                     memcpy(msfType->msf, (BYTE*) &MsfSetupIE->IE[1], TxtLength);
                                     msfType->length = TxtLength;

                                     SendSignal((SignalType *) msfType, APPLICATION_PROCESS_ID_PP, APPLICATION_PRIMITIVE, MSFInd);*/
                                    memset(pp_msf_buffer, 0, 128);
                                    memcpy(pp_msf_buffer, getMsfSetupIETypeIE(MsfSetupIE) + 1, TxtLength);
                                    memcpy(&pp_msf_buffer[TxtLength + 1], getMsfSetupIETypeIE(MsfSetupIE) + TxtLength + 2, CallbackLength);

                                    if (CissState == CISS_CONNECT) {
                                        pp_msf_DispReq_received(MsfSetupIE->PpSetup, pp_msf_buffer, &pp_msf_buffer[TxtLength + 1]);
                                    } else {
                                        pp_msf_setupreq_format1_received(MsfSetupIE->PpSetup, pp_msf_buffer, &pp_msf_buffer[TxtLength + 1]);
                                    }
                                    return;
                                } else /*Format II setup*/
                                {
                                    alertConstructiontType alertType;
                                    dateAndTimeType dateTime;
                                    memset(pp_msf_buffer, 0, 128);
                                    memcpy(pp_msf_buffer, getMsfSetupIETypeIE(MsfSetupIE) + 1, TxtLength);
                                    memcpy(&pp_msf_buffer[TxtLength + 1], getMsfSetupIETypeIE(MsfSetupIE) + TxtLength + 2, CallbackLength);

                                    alertType.alertPattern = (alertPatternType) AlertPattern;
                                    alertType.alertTone = (alertToneType) AlertTone;
                                    alertType.alertTimeout = AlertTimeout;

                                    memset(&dateTime, 0, 7);
                                    dateTime.length = DateTimeLength;
                                    if (DateTimeLength > 0)
                                        dateTime.day = BCD_Day;
                                    if (DateTimeLength > 1)
                                        dateTime.month = BCD_Month;
                                    if (DateTimeLength > 2)
                                        dateTime.hour = BCD_Hour;
                                    if (DateTimeLength > 3)
                                        dateTime.minute = BCD_Minute;
                                    if (DateTimeLength > 4)
                                        dateTime.year = BCD_Year;
                                    if (DateTimeLength > 5)
                                        dateTime.second = BCD_Second;

                                    pp_msf_setupreq_format2_received(MsfSetupIE->PpSetup, pp_msf_buffer, &pp_msf_buffer[TxtLength + 1], SetupSpec2, SetupSpec3, alertType, DisplayTimeout, dateTime, CissState == CISS_CONNECT);
                                }
                            }
                            StandByTxtIE = (StandByTxtIEType *) FindInfoElement(StandByTxtAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2);
                            if (StandByTxtIE != NULL) {
                                MenuSelectSetupReqIE = (MenuSelectSetupRequestIEType *) FindInfoElement(MenuSelectSetupReqAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) -2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType)
                                        - sizeof(IwuToIwuType) + 2);
                                if (MenuSelectSetupReqIE != NULL) {
                                    if (MenuSelectSetupReqIE->LengthOfContents > 4) {
                                        CissState = CISS_CONNECT;
                                    }
                                }

                                AsciiStrReqIE = (AsciiStrRequestIEType *) FindInfoElement(AsciiStrReqAPEIEId, getIwuToIwuSIE(IwuToIwuPtr) - 2, SsFacilityPrim->SignalHeader.SignalLength - sizeof(SsFacilityPrimType) - sizeof(IwuToIwuType) + 2);
                                if (AsciiStrReqIE != NULL) {
                                    if (AsciiStrReqIE->LengthOfContents > 3) {
                                        CissState = CISS_CONNECT;
                                    }
                                }
                                SendCissRelease();
                            }
                        }
                    } else {
                        SendCissRelease();
                    }
                } else {
                    SendCissRelease();
                }
            } else /* error*/
            {
                SendCissRelease();
            }
        break;
        default: /* Handset in wrong state.*/
            SendCissRelease();
        break;
    } /*end of case*/
}

