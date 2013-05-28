#ifndef SLOTDATATYPE_H_
#define SLOTDATATYPE_H_

#include "../../../../common/include/rtxdef.h"
#include "../../../common/include/gapcfg.h"

typedef struct Oletest
{
    FPBearerRxDataType *RxPtr;
    FPBearerTxDataType *TxPtr;
    uint8 SlotJumpIndex;
    BYTE RfCarrier;
    BYTE TxKeepCnt;
    BYTE ConferenceChannel;
    BYTE Cmd;
    BYTE MuteCount;
    BYTE Ctrl;
    BYTE FmidPmid[4];
    BYTE ConnectionTimer;
    BYTE CsRequestNr;
    BYTE AudioBufferRequest; /* 0xFF: No-request;  0xFE: Rx-disconnect;  Bit6==0: Tx-buffer;  Bit6==1: Tx-Rx-buffer */
    BYTE ConfAudioBuffer;
    BYTE DiversityState;
    BYTE UpLinkSlotScanning;
    BYTE DownLinkSlotScanning;
    BYTE UpdateDownLinkSlotScanningFreq;
    BYTE ScannedFrequency;
    BYTE ForceHO;
    BYTE Rssi_1;
    BYTE Rssi_2;
    WORD Rssi_Sum;
    BYTE Rssi_Count;
    BYTE QualitySum;
    BYTE QualityCount;
    BYTE AllokRec;
    WORD Distance;
    BYTE PagingSegmentBuffer[37];
    BYTE LongPageIndex;
} SlotDataTypeFP; /* B?r flyttes til SlotSw module... */

typedef SlotDataTypeFP SlotDataArrayTypeFP[SLOTCOUNT/SLOTINCREMENT];

extern SlotDataArrayTypeFP SlotDataFP;
extern SlotDataTypeFP      *SdPtrFP;  /* Slot data pointer */

#endif /*SLOTDATATYPE_H_*/
