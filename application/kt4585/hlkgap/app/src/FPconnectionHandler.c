#include "../../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../../include/hlkgap/util/include/print_signal.h"
#include "../../../../../include/hlkgap/app/include/f_app_cc.h"
#include "../../../../../include/hlkgap/app/include/apdbprim.h"
#include "../../../../../include/hlkgap/app/include/apssprim.h"
#include "../../../../../include/hlkgap/dduos/include/heap.h"
#include "../../../../../include/common/include/print_status.h"
#include "../../../../../include/common/include/rtxdef.h"
#include "../../../../../include/common/include/glibc.h"
#include "../../../../../include/hlkgap/iwu/include/fp/fiwuprim.h"
#include "../../../../../include/hlkgap/common/include/dispatch.h"
#include "../../../../../include/hlkgap/common/include/aformat.h"
#include "../../../../../include/hlkgap/common/include/sformat.h"
#include "../../../../../include/mac/driver/include/dip_instructions.h"
#include "../../../../../include/mac/startup/include/pp/bmc_prg.h"
#include "../../../../include/kt4585.h"
#include "../../../../api/include/DSPSignalHandler.h"

extern void (*FPApplicationHandler)(SignalType * Signal);
extern UByte * fp_get_speech_buffer(BYTE Pmid[3], UByte rxtx);
extern UByte getChannel(BYTE Pmid[3]);
extern UByte getSpeechBufferIndex(BYTE Pmid[3]);
extern Boolean StringToIPEI(UByte *PackedIPEI, UByte *IPEIString);

#define MAC_APP_TUNNEL 25

typedef struct
{
    PMIDType pmid;
    UByte channel;
    UByte speechBufferIndex;
    UByte* speechBuffer;
} fpinstance;

fpinstance instances[2];

int connected_instances = 0;

void OutputFromAudioBufferFP(BYTE Slot, BYTE BufferNr);

void routeSpeech()
{
    PrintStatus(0, "try to route the data.....");
    instances[0].channel = getChannel(instances[0].pmid);
    instances[1].channel = getChannel(instances[1].pmid);
    instances[0].speechBufferIndex = getSpeechBufferIndex(instances[0].pmid);
    instances[1].speechBufferIndex = getSpeechBufferIndex(instances[1].pmid);
    OutputFromAudioBufferFP(instances[0].channel & 0x0f, instances[1].speechBufferIndex + 1);
    OutputFromAudioBufferFP(instances[1].channel & 0x0f, instances[0].speechBufferIndex + 1);
}

extern void PPID2PMID(PMIDType * PMID, PPIDType PPID);

void setupvoice(PPIDType a, PPIDType b)
{
	PPID2PMID(&instances[0].pmid,a);
	PPID2PMID(&instances[1].pmid,b);
	connected_instances=2;
	routeSpeech();
}


extern const WORD BufferOffsetDefines[];
extern void ExecOneBmcInstructionFP(uint16 Instruc);
extern void ExecOneBmcInstructionPP(WORD Instruc);

void fp_connect_speech_buffer(PMIDType pmid)
{
    char * str;
    UByte index = getSpeechBufferIndex(pmid);
    WORD RXspeechBufferID;
    WORD TXspeechBufferID;
    SignalType * startCodec;

    str = StringPrint(StatusString, "index = [0x");
    str = StrPrintHexByte(str, index);
    str = StringPrint(str, "]");
    PrintStatus(0, StatusString);

#ifndef PCCOMPILE
    RXspeechBufferID = BufferOffsetDefines[index + 1];
    TXspeechBufferID = BufferOffsetDefines[index];
#endif

    ExecOneBmcInstructionFP((BK_MA << 8) | ((RXspeechBufferID & 0xf800) >> 8)); /* set main bank for ADPCM*/
    ExecOneBmcInstructionFP((BK_A << 8) | ((RXspeechBufferID & 0x0700) >> 3)); /* set bank for ADPCM*/
    ExecOneBmcInstructionFP((A_LDR << 8) | (RXspeechBufferID & 0x00ff)); /* set ADPCM 0 read pointer offset*/
    ExecOneBmcInstructionFP((A_LDW << 8) | ((TXspeechBufferID & 0x00ff))); /* set ADPCM 0 write pointer offset*/
    ExecOneBmcInstructionFP((A_RX << 8) | 0); /* use ADPCM 0*/
    ExecOneBmcInstructionFP((A_TX << 8) | 0); /* use ADPCM 0*/
    ExecOneBmcInstructionFP((WORD) (A_NORM << 8));

    NewSignal(sizeof(SignalType) + 1, (void**) &startCodec);
    getSignalData(startCodec)[0] = RXspeechBufferID;
    SendSignal((SignalType*) startCodec, DSP_PROCESS_ID, STARTCODEC_EVENT, 0);
}

void pp_connect_speech_buffer(void)
{
	ExecOneBmcInstructionPP((BK_A << 8) | ((SPEECHBUFFER1_OFS & 0x0700) >> 3)); /* set bank for ADPCM*/
    ExecOneBmcInstructionPP((WORD) (A_NORM << 8));
    PrintStatus(0, "Started ADPCM module 4");
}

void connectPPtoFP(PMIDType pp)
{
    memcpy(instances[0].pmid,pp,3);
    fp_connect_speech_buffer(instances[0].pmid);
}

