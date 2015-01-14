#include "../../../include/hlkgap/iwu/include/fp/fiwuprim.h"
#include "../../../include/hlkgap/util/include/bintree.h"
#include "../../../include/hlkgap/app/include/f_app_cc.h"
#include "../../../include/hlkgap/app/include/apssprim.h"
#include "../include/fp/fp_voice_callback.h"
#include "../include/fp/fp_msf_callback.h"
#include "../include/fp/fp_module2module_callback.h"
#include "../include/common/common_general_callback.h"
#include "../include/common/common_general_functions.h"
#include "../../../include/machlinterface/include/maclink.h"
#include "../../kt4585/hlkgap/app/src/wentworth/wentworth_fp.h"
#include "../../kt4585/hlkgap/app/src/wentworth/fppp_common.h"
#include "../../kt4585/hlkgap/app/src/dsp/gdsp_all_inits.h"

extern Boolean NewBuffer(int BufferLength, void **BufferPointer);
extern void *_memcpy(void *DST, const void *SRC, unsigned int LENGTH);
extern void DeleteBuffer(void *BufferPointer);
extern void ConvertIpeiToSN(PPIDType user, char SerialNumber[17], IPEIType Hex_SN);
extern void CopyToUartTxBuffer(UByte * buffer, unsigned int length);
extern void SendQuickData(UByte user);
extern void SendPCMCommand(WORD cmd);

/*extern UByte BSCSFTASK;*/

static BinTreeTopType applicationTree;
static PMIDType tmpPmid;
extern MACLink macLink;

int created = 0;

ApplicationInstanceType * getApplicationInstance(PMIDType PMID)
{
    ApplicationInstanceType *applicationInstanceData;
    applicationInstanceData = (ApplicationInstanceType *) GetNode(&applicationTree, PMID);

    if (applicationInstanceData == NULL) {
        NewBuffer(sizeof(ApplicationInstanceType), (void **) &applicationInstanceData);
        memcpy(applicationInstanceData->pmid, PMID, sizeof(PMIDType));
        applicationInstanceData->state = idle;
        applicationInstanceData->msfState = msf_idle;
        applicationInstanceData->timer = 0;

        AddNode(&applicationTree, applicationInstanceData, applicationInstanceData->pmid);
        created++;
        PrintStatus(0, "created: ");
    }

    return applicationInstanceData;
}

ApplicationInstanceType * getApplicationInstanceData(PPIDType ppid)
{
    PMIDType pmid;
    PPID2PMID(&pmid, ppid);
    return getApplicationInstance(pmid);
}

void handleReleasePrim(SignalType * TheSignal, ApplicationInstanceType * applicationInstanceData)
{
    char* tmp = StatusString;
    tmp = StringPrint(tmp, "Deleting application_fp node: ");
    tmp = StrPrintHexByte(tmp, applicationInstanceData->pmid[2]);
    PrintStatus(0, StatusString);

    if (applicationInstanceData->msfState != msf_idle) {
        applicationInstanceData->state = idle;
        PrintStatus(0, "Not deleted msf not idle.");
    } else if (DeleteNode(&applicationTree, applicationInstanceData->pmid)) {
        DeleteBuffer(applicationInstanceData);
        applicationInstanceData = 0;
        created--;
        PrintStatus(0, "deleted----: \r\n");
    } else {
        PrintStatus(0, "Not deleted");
    }
}

void handleConnectPrim(PMIDType pmid, ApplicationInstanceType * applicationInstanceData)
{
    SignalType *ccconnectSignal;

    NewSignal(sizeof(SignalType) + 5, (void**) &ccconnectSignal);
    memcpy(ccconnectSignal->Address, pmid, 3); /*pmid in address field*/
    getSignalData(ccconnectSignal)[0] = 0x05; /*info element offset*/
    getSignalData(ccconnectSignal)[1] = 0x01; /*UplaneEndpointStart*/
    getSignalData(ccconnectSignal)[2] = 0x02; /*UplaneEndpointStart*/
    getSignalData(ccconnectSignal)[3] = 0x00; /*UplaneEndpointStart*/
    getSignalData(ccconnectSignal)[4] = 0x00; /*UplaneEndpointStart*/

    applicationInstanceData->state = connected;
    SendSignal(ccconnectSignal, APP_CC_PROCESS_ID, APP_CC_PRIMITIVE, APPCCConnectAckReq);
}

void handleAPPCCSetupInd(SignalType * TheSignal, ApplicationInstanceType * applicationInstanceData)
{
    SignalType *appccSetupAckReqSignal;
    char StatusString[256];
    char* tmp = StatusString;
    tmp = StringPrint(tmp, "\r\nApplication: outgoing call start: Calling party number: ");
    tmp = StringPrint(tmp, (char*) (getSignalData(TheSignal) + 1));
    PrintStatus(0, StatusString);

    applicationInstanceData->state = outgoingcall;

    NewSignal(sizeof(SignalType) + 9, (void**) &appccSetupAckReqSignal);
    memcpy(appccSetupAckReqSignal->Address, TheSignal->Address, 4);

    getSignalData(appccSetupAckReqSignal)[0] = 0x08; /*//info element offset*/
    getSignalData(appccSetupAckReqSignal)[1] = 0x01; /*UplaneEndpointStart*/
    getSignalData(appccSetupAckReqSignal)[2] = 0x02; /*UplaneEndpointStart*/
    getSignalData(appccSetupAckReqSignal)[3] = 0x00; /*UplaneEndpointStart*/
    getSignalData(appccSetupAckReqSignal)[4] = 0x00; /*UplaneEndpointStart*/
    getSignalData(appccSetupAckReqSignal)[5] = 0x1e;
    getSignalData(appccSetupAckReqSignal)[6] = 0x02;
    getSignalData(appccSetupAckReqSignal)[7] = 0x85;
    getSignalData(appccSetupAckReqSignal)[8] = 0x88;

    SendSignal(appccSetupAckReqSignal, APP_CC_PROCESS_ID, APP_CC_PRIMITIVE, APPCCSetupAckReq);
}

extern UByte IPEITo12String(UByte *IPEIString, UByte *PackedIPEI);

UByte msf_send_CONNECT_res(PPIDType user)
{
    SignalType * signal;
    PMIDType pmid;
    getApplicationInstanceData(user)->msfState = msf_connected;
    NewSignal(sizeof(SignalType) + 2, (void**) &signal);
    PPID2PMID(&pmid, user);
    memcpy(signal->Address, pmid, sizeof(PMIDType));
    SendSignal(signal, APP_SS_PROCESS_ID, APP_SS_PRIMITIVE, SIO_MSF_CONNECT_res);
    return 1;
}

UByte msf_send_ReleaseReq(PPIDType user, UByte releaseReason)
{
    SignalType * signal;
    PMIDType pmid;

    if (QuickData[user].EmptyMarker != 0)
        return 0;

    getApplicationInstanceData(user)->msfState = msf_release_pending;
    NewSignal(sizeof(SignalType) + 1, (void**) &signal);

    getSignalData(signal)[0] = releaseReason;

    PPID2PMID(&pmid, user);
    memcpy(signal->Address, pmid, sizeof(PMIDType));
    SendSignal(signal, APP_SS_PROCESS_ID, APP_SS_PRIMITIVE, SIO_MSF_RELEASE_req);
    return 1;
}

UByte fp_send_module2module(PPIDType user, module2moduleData data)
{
    SsFacilityPrimType * SsFacilityPrim;
    UByte * dst;
    UByte cnt;

    NewSignal(sizeof(SsFacilityPrimType) + 5, (void**) &SsFacilityPrim);
    dst = (UByte *) getSsFacilityPrimTypeIE(SsFacilityPrim);

    dst[0] = MODULE_SHORT_MSF;

    for (cnt = 1; cnt <= 3; cnt++)
        dst[cnt] = data[cnt - 1];

    PPID2PMID((PMIDType*) SsFacilityPrim->SignalHeader.Address, user);

    SendSignal((SignalType*) SsFacilityPrim, IWU_PROCESS_ID, IWU_PRIMITIVE, SS_TUNNEL_prim);

    return 0;
}

UByte msf_setupreq_format2(PPIDType to, UByte setupSpec1, char * display, PPIDType callbackId, UByte setupSpec2, UByte setupSpec3, alertConstructiontType alertConstruction, UByte displayTimeout, dateAndTimeType dateAndTime)
{
    SignalType * signal;
    PMIDType pmid;
    char callback[12];
    UByte index;

    if (QuickData[to].EmptyMarker != 0)
        return 0;

    PPID2PMID(&pmid, to);

    memset(callback, 0, 12);
    StrPrintHexWord(callback, callbackId);

    NewSignal(sizeof(SignalType) + 3 + strlen(display) + strlen(callback) + 6 + 1 + dateAndTime.length, (void**) &signal);
    getSignalData(signal)[0] = setupSpec1;
    memcpy(getSignalData(signal) + 1, display, strlen(display));
    getSignalData(signal)[1 + strlen(display)] = 0;
    if (strlen(callback) > 0) {
        memcpy(getSignalData(signal) + 1 + strlen(display) + 1, callback, strlen(callback) + 1);
        index = 1 + strlen(display) + 1 + strlen(callback) + 1;
    } else {
        getSignalData(signal)[1 + strlen(display) + 1] = 0;
        index = 1 + strlen(display) + 1 + 1;
    }

    getSignalData(signal)[index++] = setupSpec2;
    getSignalData(signal)[index++] = setupSpec3;
    getSignalData(signal)[index++] = alertConstruction.alertPattern;
    getSignalData(signal)[index++] = alertConstruction.alertTone;
    getSignalData(signal)[index++] = alertConstruction.alertTimeout;
    getSignalData(signal)[index++] = displayTimeout;
    memcpy(getSignalData(signal) + index, (UByte*) &dateAndTime.length, dateAndTime.length + 1);

    memcpy(signal->Address, pmid, 3);
    SendSignal(signal, APP_SS_PROCESS_ID, APP_SS_PRIMITIVE, SIO_MSF_SETUP_req);
    return 1;
}

UByte msf_send_ppstatusReq(PPIDType to, UByte statusType, UByte * data, UByte dataLength)
{
    SignalType * signal;
    PMIDType pmid;

    if (QuickData[to].EmptyMarker != 0)
        return 1;

    if (dataLength > 100)
        return 2;

    PPID2PMID(&pmid, to);

    NewSignal(sizeof(SignalType) + 1 + dataLength, (void**) &signal);
    getSignalData(signal)[0] = statusType;
    memcpy(getSignalData(signal) + 1, data, dataLength);

    memcpy(signal->Address, pmid, 3);
    SendSignal(signal, APP_SS_PROCESS_ID, APP_SS_PRIMITIVE, SIO_PP_STATUS_req);
    return 0;
}

UByte msf_send_broadcast(UByte *data, UByte length, UByte repetitions)
{
	int i;
	BYTE dataCounter = 0;
	BYTE Buff[37];
	UByte numberOfPackets;

	if(length > 20)
		return 0;

	if(mod(length,4))
		numberOfPackets = div32(length, 4) + 1;
	else
		numberOfPackets = div32(length, 4);

    Buff[0] = LONGBROADCAST_req;
    Buff[1] = repetitions; /* Rep count*/
    Buff[2] = mul32(numberOfPackets, 5) + 5; /* Length*/
    Buff[3] = 0xde; /* CLMS header for addr section*/
    Buff[4] = 0xcf; /* Addr section*/
    Buff[5] = 0xff;
    Buff[6] = 0x06; /* Discriminator*/
    Buff[7] = mul32(length, 8); /* Bit counter*/

    for(i = 0; i < mul32(numberOfPackets, 5); i++){
    	if(mod(i,5)){
    		if(dataCounter < length)
    			Buff[i + 8] = data[dataCounter++];
    		else
    			Buff[i + 8] = 0xFF;
    	} else{
    		Buff[i + 8] = div16(i, 5);
    	}
    }

    macLink.sendMailToMac((MailType *) Buff, 33,0,0,0);
    /*SendMail(BSCSFTASK,33,(MailType *) Buff);*/

    return 1;
}

UByte msf_setupreq_format1(PPIDType to, UByte setupSpec1, char * display, PPIDType callbackId)
{
    SignalType * signal;
    PMIDType pmid;
    char callback[12];

    if (QuickData[to].EmptyMarker != 0)
        return 0;

    PPID2PMID(&pmid, to);

    memset(callback, 0, 12);
    StrPrintHexWord(callback, callbackId);

    NewSignal(sizeof(SignalType) + 3 + strlen(display) + strlen(callback), (void**) &signal);
    getSignalData(signal)[0] = setupSpec1;
    memcpy(getSignalData(signal) + 1, display, strlen(display));
    getSignalData(signal)[1 + strlen(display)] = 0;
    if (strlen(callback) > 0) {
        memcpy(getSignalData(signal) + 1 + strlen(display) + 1, callback, strlen(callback) + 1);
    } else {
        getSignalData(signal)[1 + strlen(display) + 1] = 0;
    }

    memcpy(signal->Address, pmid, 3);
    SendSignal(signal, APP_SS_PROCESS_ID, APP_SS_PRIMITIVE, SIO_MSF_SETUP_req);
    return 1;
}

UByte voice_updateDisplay(PPIDType user, char * display)
{
    SignalType *ccinfoSignal;
    ApplicationInstanceType *applicationInstanceData;
    PPID2PMID(&tmpPmid, user);
    applicationInstanceData = getApplicationInstance(tmpPmid);

    if (user != 0xffff && applicationInstanceData != NULL) {
        NewSignal(sizeof(SignalType) + 14, (void**) &ccinfoSignal);

        memcpy(ccinfoSignal->Address, tmpPmid, 3); /*pmid in address field*/
        getSignalData(ccinfoSignal)[0] = 0x01; /*info element offset*/
        getSignalData(ccinfoSignal)[1] = 0x28;
        getSignalData(ccinfoSignal)[2] = 0x02 + strlen(display);
        getSignalData(ccinfoSignal)[3] = 0x04;
        getSignalData(ccinfoSignal)[4] = 0x0C;

        memcpy(getSignalData(ccinfoSignal) + 5, display, strlen(display)); /*multidisplay, iwutoiwu, signal*/

        SendSignal(ccinfoSignal, APP_CC_PROCESS_ID, APP_CC_PRIMITIVE, APPCCInfoReq);
        return 1;
    }
    return 0;
}

UByte voice_disConnectUser(PPIDType user)
{
    if (QuickData[user].EmptyMarker == 0) {
        ApplicationInstanceType *applicationInstanceData;
        PMIDType pmid;

        PPID2PMID((PMIDType *) pmid, user);
        applicationInstanceData = getApplicationInstance(pmid);

        if (applicationInstanceData->state == connected) {
            SignalType *CcReleasePrim;
            UByte Data[2] = { 0x2e, 00 };

            NewSignal(sizeof(SignalType) + 2, (void **) &CcReleasePrim);
            memcpy(CcReleasePrim->Address, pmid, 3);
            CcReleasePrim->Address[3] = 0x00;
            _memcpy(getCcReleasePrimTypeIE(CcReleasePrim), Data, 2);
            SendSignal((SignalType *) CcReleasePrim, IWU_PROCESS_ID, IWU_PRIMITIVE, CC_RELEASE_prim);
            applicationInstanceData->state = idle;
            return 0;
        } else {
            return 2;
        }
    } else {
        return 3;
    }
}

UByte voice_callUser(PPIDType called, PPIDType caller)
{
    ApplicationInstanceType *applicationInstanceData;

    if (QuickData[called].EmptyMarker == 0) {
        SignalType * signal;
        NewSignal(sizeof(SignalType), (void**) &signal);

        PPID2PMID((PMIDType *) signal->Address, called);

        applicationInstanceData = getApplicationInstance(signal->Address);

        if (applicationInstanceData->state == idle) {
            applicationInstanceData->state = incommingcall;
            applicationInstanceData->connectedTo = caller;

            SendSignal((SignalType*) signal, APP_CC_PROCESS_ID, APP_CC_PRIMITIVE, APPCCSetupReq);

            /*setup the outgoing side of the call:*/
            {
                if(caller < MAX_Allowed_Users && QuickData[caller].EmptyMarker == 0){
                    PMIDType pmid;
                    char tmp[13];
                    UByte sum = called;

                    PPID2PMID(&pmid, caller);

                    applicationInstanceData = getApplicationInstance(pmid);
                    applicationInstanceData->connectedTo = called;

                    memset(tmp, 0, 12);
                    tmp[0] = sum + '0';
                    handleConnectPrim(pmid, applicationInstanceData);
                }
                /*{
                 AudioLineCtrlReqType *AudioLineCtrlReq;
                 NewSignal(sizeof(AudioLineCtrlReqType), (void **) &AudioLineCtrlReq);
                 AudioLineCtrlReq->TheSignal.Address[0] = 0x0F;
                 AudioLineCtrlReq->TheSignal.Address[1] = 0;//MeInstance->Mcei;
                 AudioLineCtrlReq->Lid = sum;
                 _memcpy(AudioLineCtrlReq->Pmid,pmid,3);
                 AudioLineCtrlReq->option = 3;
                 PrintStatus(0, "\r\napp: send AUDIOLINECTRL_req to mac layer");

                 SendSignal((SignalType*)AudioLineCtrlReq, CCF_PROCESS_ID, CCF_PRIMITIVE, AUDIOLINECTRL_req);
                 }*/
            }

            return 1;
        } else {
            DeleteBuffer(signal);
            PrintStatus(0, "\r\nnumber found, but user already active.\n");
            return 2;
        }
    } else {
        PrintStatus(0, "\r\nnumber not found...");
        return 3;
    }
}

extern void App_dBSendAppOmSubsRemoveReq(PPIDType PPID);

// this runs whenever a PP is deleted
UByte fp_subscription_removeSubscription(PPIDType user)
{
    if (QuickData[user].EmptyMarker == 0)
    {
        App_dBSendAppOmSubsRemoveReq(user);
		if (user == (base_station).OrderTakerID)
			(base_station).OrderTakerID = 0xFF;
		(base_station).ListenOnly[user] = 0xFF;
	    if ((base_station).DualBase)
	   		SendPCMCommand(PP_ON_ind + (user << 4) + 0);
	    if ((user + 1) == (base_station).UsingWirelessPost)
	    {
	    	(base_station).UsingWirelessPost = 0;
	    	p_dynmixer0->weights[6] = MIC_A_ATTEN;
	    	p_dynmixer1->weights[6] = MIC_A_ATTEN;
	    	p_dynmixer2->weights[6] = MIC_A_ATTEN;
	    	p_dynmixer3->weights[6] = MIC_A_ATTEN;
	    	p_dynmixer4->weights[6] = MIC_A_ATTEN;
	    	p_dynmixer5->weights[6] = MIC_A_ATTEN;
	    }
		general_startTimer(-1, WRITE_WTDATA_EEPROM, NULL, 0, 5);
        return 1;
    }
    return 0;
}

PPIDType fp_subscription_lookupUserFromIpei(IPEIType ipei)
{
    int c;
    for (c = 0; c < MAX_Allowed_Users; c++) {
        if (memcmp(QuickData[c].Upi, &ipei[1], 4) == 0)
            return c;
    }
    return 0xffff;
}

UByte fp_subscription_lookupUserFromPPID(PPIDType ppid, IPEIType dstIpei)
{
    if (QuickData[ppid].EmptyMarker == 0)
    {
    	dstIpei[0] = 0;
        memcpy(&dstIpei[1], QuickData[ppid].Upi, 4);
        return 1;
    }
    return 0;
}

UByte fp_subscription_getNumberOfSubscriptions()
{
    UByte c;
    UByte subscriptions = 0;
    for(c = 0; c < MAX_Allowed_Users; c++)
    {
        if(QuickData[c].EmptyMarker == 0)
        {
            subscriptions++;
        }
    }
    return subscriptions;
}

void handleAPPCCInfoInd(SignalType * TheSignal, ApplicationInstanceType * applicationInstanceData)
{
    if (applicationInstanceData->state == outgoingcall)
    {
        UByte c;
        PPIDType ppid = 0;
        UByte *data = getSignalData(TheSignal);
        int dataLength = data[15];
        char *input = (char*) &data[16];
        for (c = 0; c < dataLength && input[c] >= '0' && input[c] <= '9'; c++)
        {
            ppid *= 10;
            ppid += input[c] - '0';
        }

        voice_outgoingCallRequest(PMID2PPID(applicationInstanceData->pmid), ppid);
    }
}

extern Boolean NewBuffer(int BufferLength, void **BufferPointer);

UByte msf_help_generateSetupSpec1(UByte text_call, UByte display_right_arrow, UByte display_left_arrow, UByte enable_right_arrow, UByte enable_left_arrow, alertTypes alertType)
{
    UByte result = 0;
    result += text_call << 7;
    result += display_right_arrow << 6;
    result += display_left_arrow << 5;
    result += enable_right_arrow << 4;
    result += enable_left_arrow << 3;
    result += alertType & 0x07;
    return result;
}

UByte msf_help_generateSetupSpec2(UByte PartielUnlock, UByte NoAcknowledgement, UByte SaveInStack)
{
    UByte result = 0;
    result += PartielUnlock << 4;
    result += NoAcknowledgement << 1;
    result += SaveInStack;
    return result;
}

UByte msf_help_generateSetupSpec3(functionType function, UByte vibrateTone, UByte AlertAlways, UByte VibrateAlways, UByte msfUp)
{
    UByte result = 0;
    result += function << 7;
    result += vibrateTone << 3;
    result += AlertAlways << 2;
    result += VibrateAlways << 1;
    result += msfUp;
    return result;
}

void msf_send_DispReq(char * displayText, char * callbackNo, PPIDType user, UByte setupSpec)
{
    SioMsfInfoReqType * infoReq;
    int index = 0;
    PMIDType pmid;
    int callBackNoLength = 0;

    PPID2PMID(&pmid, user);

    if (callbackNo != 0) {
        callBackNoLength = strlen(callbackNo);
    }

    NewSignal(sizeof(SignalType) + strlen(displayText) + 1 + 1 + callBackNoLength + 1 + 1, (void**) &infoReq);

    infoReq->PpSetup = setupSpec;

    memcpy(getSioMsfInfoReqTypeIE(infoReq), displayText, strlen(displayText));
    index += strlen(displayText);

    getSioMsfInfoReqTypeIE(infoReq)[index++] = 0x00; /*zero terminate string*/

    if (callbackNo != 0) {
        memcpy(getSioMsfInfoReqTypeIE(infoReq) + index, callbackNo, strlen(callbackNo));
        index += strlen(callbackNo);
    }

    getSioMsfInfoReqTypeIE(infoReq)[index] = 0x00; /*zero terminate string*/

    memcpy((UByte*) infoReq->SignalHeader.Address, &pmid, 3);
    SendSignal((SignalType *) infoReq, APP_SS_PROCESS_ID, APP_SS_PRIMITIVE, SIO_MSF_INFO_req);
}

extern int getNumberOfRunningTimers(void);
extern int getNumberOfQueuedSignals(void);

extern void fp_connect_speech_buffer(PMIDType pmid);

extern UByte common_signalHander(SignalType * TheSignal);

void ApplicationSignalHandler_FP(SignalType * TheSignal)
{
    ApplicationInstanceType * applicationInstanceData;

    if (common_signalHander(TheSignal)) {
        return;
    }

    if (TheSignal->Event == INITIALIZE_EVENT) {
        InitializeTreeTop(&applicationTree, sizeof(PMIDType));
        DeleteBuffer(TheSignal);
        fp_system_init();
        return;
    }

    applicationInstanceData = getApplicationInstance(TheSignal->Address);

    switch (TheSignal->Event)
    {
        case APPLICATION_PRIMITIVE:
        {
          switch (TheSignal->SubEvent)
            {
                case APPCCSetupInd:
                {
                    handleAPPCCSetupInd(TheSignal, applicationInstanceData);

                    // set up registration display "green" button here
                    (base_station).HeadsetIsOn[PMID2PPID(applicationInstanceData->pmid)] = TRUE;

                    if (base_station.DualBase)
                    {
                    	SendQuickData(PMID2PPID(applicationInstanceData->pmid));							// fill .EmptyMarker on other base
                   		SendPCMCommand(PP_ON_ind + (PMID2PPID(applicationInstanceData->pmid) << 4) + 1);	// fill .HeadsetIsOn on other base
                    }

                    if ((base_station).DisplayScreen == REGISTRATION)
                    {
                    	UByte buffer[50];
                    	int i, count;
                    	IPEIType Ipei;
                    	char SN[17];

                		CopyToUartTxBuffer((UByte *)"*abt\r", 5);
                		CopyToUartTxBuffer((UByte *)"f 18BC\r", 7);
                    	i = PMID2PPID(applicationInstanceData->pmid);
						Ipei[0] = 0x01;						// hard coding 0x01 for 1st byte
                		memcpy(&Ipei[1], QuickData[i].Upi, 4);
                		ConvertIpeiToSN(i, SN, Ipei);
    					memcpy(&buffer[0], "m register_box:lbl_1_", 21);
    					count = 21;
    					count += GetAsciiValue(&buffer[0], (i + 40), count);
    					memcpy(&buffer[0] + count, " \"on ", 5);
    					count += 5;
    					memcpy(&buffer[0] + count, &SN[6], 10);
    					count += 10;
    					memcpy(&buffer[0] + count, "\"\r", 2);
    					count += 2;
    					CopyToUartTxBuffer(&buffer[0], count);
                    }

                }
                break;
                case APPCCInfoInd:
                {
                    handleAPPCCInfoInd(TheSignal, applicationInstanceData);
                }
                break;
                case APPCCAbnormal:
                {
                    if (applicationInstanceData) {
                        PrintStatus(0, "abnormal release in application, user found");
                        handleReleasePrim(TheSignal, applicationInstanceData);
                    } else {
                        _sprintf_(StatusString, "abnormal %x %x %x %x", TheSignal->Address[0], TheSignal->Address[1], TheSignal->Address[2], TheSignal->Address[3]);
                        PrintStatus(0, StatusString);
                    }
                }
                break;

                case 0x86:
                {
                    UByte * data = getSignalData(TheSignal);
                    fp_module2module_ack_received(PMID2PPID(TheSignal->Address), &data[1]);
                }
                break;

                case SS_MSF_prim:
                {
                    UByte *messageData;
                    UByte DestinationIdLenght;
                    UByte *DestinationId;
                    UByte DisplaytextLength;
                    UByte *DisplayText;
                    UByte CallBackNumberLength;
                    UByte *CallBackNumber;
                    UByte SSAAAD[SSAAADLength];
                    int index, count;
                    APPMSFind* appMSFind = (APPMSFind*) TheSignal;
                    char* tmp;
                    index = 0;
                    messageData = getAPPMSFindIE(appMSFind);

                    DestinationIdLenght = messageData[index++];
                    DestinationId = (UByte*) mem_malloc(DestinationIdLenght + 1, 0x42);

                    for (count = 0; count < DestinationIdLenght; count++) {
                        DestinationId[count] = messageData[index++];
                    }
                    DestinationId[count] = '\0';

                    DisplaytextLength = messageData[index++];
                    DisplayText = (UByte*) mem_malloc(DisplaytextLength + 1, 0x42);

                    for (count = 0; count < DisplaytextLength; count++) {
                        DisplayText[count] = messageData[index++];
                    }
                    DisplayText[count] = '\0';

                    CallBackNumberLength = messageData[index++];
                    CallBackNumber = (UByte*) mem_malloc(CallBackNumberLength + 1, 0x42);

                    for (count = 0; count < CallBackNumberLength; count++) {
                        CallBackNumber[count] = messageData[index++];
                    }
                    CallBackNumber[count] = '\0';

                    memcpy(&SSAAAD[0], &messageData[index], SSAAADLength);
                    tmp = StatusString;
                    tmp = StringPrint(tmp, "MSF: [");
                    tmp = StringPrint(tmp, (char*) DisplayText);
                    tmp = StringPrint(tmp, "] from [");
                    tmp = StringPrint(tmp, (char*) CallBackNumber);
                    tmp = StringPrint(tmp, "] to [");
                    tmp = StringPrint(tmp, (char*) DestinationId);
                    tmp = StringPrint(tmp, "]");
                    PrintStatus(0, StatusString);

                    if (strlen((char*) DisplayText) == 1) {
                        if ((DisplayText[0] >= '0') && (DisplayText[0] <= '9')) {
                            char * ptr = StringPrint(StatusString, "Dialing: ");
                            UByte receiver = DisplayText[0] - '0';
                            ptr = StrPrintHexByte(ptr, receiver);
                            PrintStatus(0, StatusString);
                            /*callUser((char*) DisplayText, 0, "Call from FP");*/
                        }
                    }

                    msf_outgMessageIndReceived(PMID2PPID(TheSignal->Address), SSAAAD[0], SSAAAD[1], SSAAAD[2], SSAAAD[3], SSAAAD[4], SSAAAD[5], (char*) DestinationId, (char*) DisplayText, PMID2PPID(TheSignal->Address));
                    mem_free(DestinationId);
                    mem_free(DisplayText);
                    mem_free(CallBackNumber);
                }
                break;
            }
        }
        break;

        case IWU_PRIMITIVE:
        {
            switch (TheSignal->SubEvent)
            {
                case CC_ALERTING_prim:
                {
                  if (applicationInstanceData != NULL) {
                        voice_incommingCallAlerting(PMID2PPID(applicationInstanceData->pmid), applicationInstanceData->connectedTo);
                    }
                    PrintStatus(0, "Application: alerting....\n");
                }
                break;
                case CC_CONNECT_prim:
                {
                    if(applicationInstanceData->connectedTo < MAX_Allowed_Users && QuickData[applicationInstanceData->connectedTo].EmptyMarker == 0){
                        extern void setupvoice(PPIDType a, PPIDType b);
                        setupvoice(PMID2PPID(applicationInstanceData->pmid), applicationInstanceData->connectedTo);
                    }

                    PrintStatus(0, "fp_application: CC_CONNECT_prim");

                    handleConnectPrim(TheSignal->Address, applicationInstanceData);
                    voice_callConnected(PMID2PPID(applicationInstanceData->pmid), applicationInstanceData->connectedTo);
                }
                break;
                case CC_RELEASE_prim:
                {
                    if(applicationInstanceData->connectedTo < MAX_Allowed_Users && QuickData[applicationInstanceData->connectedTo].EmptyMarker == 0){
                        ApplicationInstanceType * wasConnectedTo;
                        PPID2PMID(&tmpPmid, applicationInstanceData->connectedTo);
                        wasConnectedTo = getApplicationInstance(tmpPmid);
                        wasConnectedTo->connectedTo = 0xffff;
                    }
                    voice_callDisconnected(PMID2PPID(applicationInstanceData->pmid), applicationInstanceData->connectedTo, 0x00);
                    handleReleasePrim(TheSignal, applicationInstanceData);
                }
                break;
            };

        }
        break;

        case APP_SS_PRIMITIVE:
        {
            switch (TheSignal->SubEvent)
            {
                case SIO_MSF_SETUP_req: /*from serial / ip*/
                {

                }
                break;

                case SIO_MSF_SETUP_ind: /*from pp*/
                {
                    applicationInstanceData->msfState = msf_session_requested_from_pp;
                    msf_msfsetupIndReceived(PMID2PPID(TheSignal->Address), (char*) getSignalData(TheSignal));
                }
                break;

                case SIO_MSF_CONNECT_res:
                {
                    /*SioMsfConnectResType *SioMsfConnectRes = (SioMsfConnectResType *) TheSignal;*/
                }
                break;

                case SIO_MSF_CONNECT_cfm:
                {
                    msf_connectCfmReceived(PMID2PPID(TheSignal->Address));
                }
                break;

                case SIO_MSF_INFO_ind:
                {
                    msf_infoIndReceived(PMID2PPID(TheSignal->Address), getSignalData(TheSignal)[0]);
                }
                break;

                case SIO_MSF_INFO_req:
                {
                    /*SioMsfInfoReqType *SioMsfInfoReq = (SioMsfInfoReqType *) TheSignal;*/
                }
                break;

                case SIO_MSF_RELEASE_req:
                {
                    /*SioMsfReleaseReqType *SioMsfReleaseReq = (SioMsfReleaseReqType *) TheSignal;*/
                }
                break;

                case SIO_MSF_RELEASE_ind:
                {
                    applicationInstanceData->msfState = msf_idle;
                    msf_releaseIndReceived(PMID2PPID(applicationInstanceData->pmid), getSignalData(TheSignal)[0]);
                }
                break;

                case SIO_MSF_OUTG_MESSAGE_ind:
                {
                }
                break;

                case SIO_PP_STATUS_req:
                {
                    /*SioPpStatusReadReqType *SioPpStatusReq = (SioPpStatusReadReqType *) TheSignal;*/
                    /*int i = 0;*/
                }
                break;

                case SIO_PP_STATUS_ind:
                {
                    SioPpStatusIndType *SioPpStatusInd;
                    SioPpStatusInd = (SioPpStatusIndType*) TheSignal;
                    msf_ppstatus_ind_received(PMID2PPID(applicationInstanceData->pmid), SioPpStatusInd->StatusType, getSioPpStatusIndTypeIE(SioPpStatusInd), SioPpStatusInd->SignalHeader.SignalLength
                            - offsetof(SioPpStatusIndType,StatusType) - 1);
                }
                break;
            }
        }
        break;

        case TIME_OUT_EVENT:
        {
            TimerType * timerPtr = (TimerType*) TheSignal;
            PMIDType pmid;
            UByte dataLength = TheSignal->SignalLength - timerSize();

            PPID2PMID(&pmid, (PPIDType) -1);

            if (memcmp(TheSignal->Address, pmid, sizeof(PMIDType)) != 0) {
                getApplicationInstance(TheSignal->Address)->timer = NULL;
            }

            fp_general_timeout(PMID2PPID(TheSignal->Address), TheSignal->SubEvent, getTimerData(timerPtr), dataLength);
        }
        break;
    };
    DeleteBuffer(TheSignal);
}
