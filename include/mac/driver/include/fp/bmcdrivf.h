/*****************************************************************************
* Project   : DECT                                                           *
* Module    : Operating system                                               *
* Reference :                                                                *
* Type      : Headerfile for slot switching interrupt handler.               *
* Function  :                                                                *
* Systems   : Base                                                           *
*----------------------------------------------------------------------------*
* $Header:   K:/PH/140211xx/source/bmcdrivf.h_v   1.1.2.4   Jan 29 2004 10:36:40   on  $ *
*****************************************************************************/

#ifndef __BMCDRIVF_H
#define __BMCDRIVF_H

#include "../../../common/include/gapcfg.h"
#include "../../../../common/include/rtxdef.h"
#ifdef SLOT_12
#include "../../include/bmcdef12.h"
#else
#include "../../include/bmcdef6.h"
#endif

#define EVENSLOTS
#define UNALLOCATED 0xff

/* NonGapExtFreqMode values*/
#define EUROPE_SYNT         0
#define CHINA_SYNT          1
#define SOUTH_AMERICA_SYNT  2
#define TAIWAN_SYNT         3
#define USA_SYNT            4
#endif

typedef struct
{
    uint8 Frequency;              /* Default frequency setup*/
    uint8 SyncCfg;                /* S_err[0..3],INV_RDI,INV_TDO,SenseA,PP/Fpn*/
    uint8 MaskSlide;              /* Mask[0..3] Slide[0..3]*/
    uint8 CmVol;                  /* CM5, CM, Vol[5..0]*/
    uint8 DAC;                    /* Don, TM_ANA, DAC[0..5]*/
    uint8 AdpWin;                 /* DPLL[0..2], ADP, WIN[0..3]*/
    uint8 Misc;                   /* ENCoff, SenseS, Ron, nc, SCoff, DOFr, M[0..1]*/
    uint8 AnalogControl;          /* All: C2 ; Gausian only: 7F*/
    uint8 TestByte1;              /* xxx00000*/
    uint8 LrsMicGain;             /* LLLLMMMM*/
    uint8 Vref;                   /* xxxxxx00*/
    uint8 TestByte3;              /* xxxxx000*/
    uint8 TestByte4;              /* 00000000*/
    uint16 InitInstruction;
    uint8 Synt3161Offset;         /* DCBAP100*/
}
BmcInitDataTypeFP;

extern uint16 BmcInstruction;   /* For debugging, manual execution of instructions */
extern uint8 RfChannelOffset;   /*RF channel offset used to shift frequencies during test*/
extern BYTE CurrentDownLinkRxSlot;

extern void InitialWakeBmcFP(void);
extern void InitBmc(BmcInitDataTypeFP * BmcInitData);
extern void InitLMX(BmcInitDataTypeFP * BmcInitData);
extern void GotoDIPLabel_FP(WORD DIPLabel);

extern void InitBmcToContineousReceive(uint8 Freq, uint8 QuadInitLevel);
extern void SetReceiverFrequencyFP(uint8 Slot, uint8 Freq);
extern void SetReceiverToScan(uint8 Slot);
extern void SetPrimRecvScanCarrier(uint8 Freq);
extern signed char DECT_Channel_offset;
extern void SetPrimRecvScanCarrierSlot(uint8 Slot, uint8 Freq);
extern void SetRxSynthesis(SyntRegType *FreqLocation, BYTE Freq);
extern void SetTxSynthesis(SyntRegType *FreqLocation, BYTE Freq);
extern void SelectAntenna(BYTE Slot, BYTE Antenna);

extern __no_init BmcDataRamType BmcDataRam;

typedef struct
{
    uint16 *InputWritePointer;
}
DSPToSpeechBufferConnectionType;

typedef struct
{
    uint16 *OutputWritePointer;
}
SpeechBufferToDSPConnectionType;

typedef struct
{
    uint16 RxBuffer;
}
SpeechBufferAddressTableType;

#ifdef _2_4_GHZ_
#define FreqHoppingIndex PrimRecvScanCarrier_p2
#define EXCLUDE_PATT  0x80
#define RSSIMASK 0x07
#define RSSIINC  0x01
#define QMASK    0x70
#define QINC     0x10
#ifdef EEPROM_HOP_SELECT
extern const BYTE *FreqHopTbl[];
extern const BYTE FreqHopNufTbl[];
#else
extern const uint8 FreqHopSequence[];
#endif
extern uint8 ChannelQualityList[];
extern uint8 FreqHopSQC;
extern uint8 FreqHopIndexExcpShift;
/*
   typedef struct {
   #ifdef _FP_SYNC_
   uint8 FpSyncSlot;      // 7E0
   uint8 FpSyncFreq;      // 7E1
   uint8 FpSyncRfpi[5];   // 7E2
   uint8 FpSyncMaster;    // 7E7
   uint16 BlindSlotInfo;   // 7E8
   uint8 Fill[4];         // 7EA
   #endif
   uint8 Preamble0;         // 7EE
   uint8 Preamble1;         // 7EF
   uint16 RxSyntNdivBasis;   // 7F0
   uint16 TxSyntNdivBasis;   // 7F2
   uint8 SyntNdivInc;       // 7F4
   uint8 SyntRefDiv;        // 7F5
   uint8 TxSyntMode[3];     // 7F6
   uint8 RxSyntMode[3];     // 7F9
   uint8 TestFrequency;     // 7FC
   uint8 PllLatchOffTime;   // 7FD
   uint8 SwitchTime0;       // 7FE
   uint8 SwitchTime1;       // 7FF
   } SynthesisDataType;
   extern SynthesisDataType SynthesisData;
 */

#define NUMBER_OF_ANALOG_LINES       9

#define NUMBER_OF_MAC_AUDIO_BUFFERS  24

typedef enum
{
    EXTTXBUFFER_0,
    EXTRXBUFFER_0,
    EXTTXBUFFER_1,
    EXTRXBUFFER_1,
    EXTTXBUFFER_2,
    EXTRXBUFFER_2,
    EXTTXBUFFER_3,
    EXTRXBUFFER_3,
    EXTTXBUFFER_4,
    EXTRXBUFFER_4,
    EXTTXBUFFER_5,
    EXTRXBUFFER_5,
}
eAudioBufferType;

extern const SpeechBufferAddressTableType SpeechBufferAddressTable[NUMBER_OF_MAC_AUDIO_BUFFERS];
extern DSPToSpeechBufferConnectionType DSPToSpeechBufferConnection[NUMBER_OF_ANALOG_LINES];
extern SpeechBufferToDSPConnectionType SpeechBufferToDSPConnection[NUMBER_OF_ANALOG_LINES];

/*extern void bmcdrivf_ChangeRxBuffer(uint8 Slot, uint8 BufferNr);*/
extern void bmcdrivf_ChangeRxBuffer(uint8 BufferNr);
/*extern void bmcdrivf_SetTransmitBuffer(uint8 Slot);*/
extern void bmcdrivf_SetTransmitBuffer(void);
extern void AverageChannelRssi(uint8 Rssi);
extern void AverageChannelQuality(uint8 Quality);
extern void UpdateRfCarrierExceptions(uint8 Carrier);
extern void ImplementRfCarrierExceptions(uint8 Carrier);
extern void LoadSynthesisRxTxDiv(uint8 Freq);
extern uint8 RfCarrierExceptions[12];
extern uint8 BroadcastExceptionPending;
extern uint8 PrimRecvScanCarrierFP_p2;
extern void InitFreqHopSQC(void);
extern uint8 CurrentFixedFrequency;
extern void RestoreFixedFrequency(void);
extern void bmcdrivx_SetFixedFreq(BYTE Freq);

#ifdef EEPROM_HOP_SELECT
#ifdef AVERAGE_CHANNEL_RSSI
extern uint8 ChannelRssiList[FREQ_HOP_NUF_MAX + 1];     /* FREQ_HOP_NUF defined in gapcfg*/
#endif
extern uint8 ChannelQualityList[FREQ_HOP_NUF_MAX + 1];  /* FREQ_HOP_NUF defined in gapcfg*/
#else
#ifdef AVERAGE_CHANNEL_RSSI
extern uint8 ChannelRssiList[FREQ_HOP_NUF + 1]; /* FREQ_HOP_NUF defined in gapcfg*/
#endif
extern uint8 ChannelQualityList[FREQ_HOP_NUF + 1];      /* FREQ_HOP_NUF defined in gapcfg*/
#endif
#ifdef _FP_POWER_SAVE_MODE_
extern void SetReceiverToPowerSave(uint8 Slot);
#endif
extern const SpeechBufferAddressTableType SpeechBufferAddressTable[NUMBER_OF_MAC_AUDIO_BUFFERS];
#else

#define NUMBER_OF_ANALOG_LINES       12
#define NUMBER_OF_MAC_AUDIO_BUFFERS  NUMBER_OF_ANALOG_LINES * 2
extern const SpeechBufferAddressTableType SpeechBufferAddressTable[NUMBER_OF_MAC_AUDIO_BUFFERS + 2];
extern BYTE SyncCfgSave;
#endif /*was missing?*/

extern DSPToSpeechBufferConnectionType DSPToSpeechBufferConnection[NUMBER_OF_ANALOG_LINES];
extern SpeechBufferToDSPConnectionType SpeechBufferToDSPConnection[NUMBER_OF_ANALOG_LINES];
extern BYTE SpeechBufferUsageTable[NUMBER_OF_MAC_AUDIO_BUFFERS];


extern void SetFrameNumberFP(void);
extern void BuildFPTxSlotFP(uint8 Slot, uint8 Freq, uint8 Antenna);
extern void BuildFPTxSlotShort(uint8 Slot);
extern void BuildFPRxSlotFP(uint8 Slot, uint8 Freq, uint8 Antenna);
extern void SetDownLinkRxCarrier(BYTE Slot, BYTE Freq);
extern void BuildPPRxScanSlot(BYTE Slot);
extern void SEmerGBuf(BYTE Slot, BYTE BufferNr);
extern void ResEmerGBuf(BYTE Slot);
extern void BuildPPTxSlotFP(uint8 Slot, uint8 Freq, uint8 Antenna);
extern void FPSelectDownLinkAntenna(BYTE Antenna);
extern void FPSelectTxAntenna(uint8 Slot, uint8 Antenna);
extern void FPSelectRxAntenna(BYTE Slot, BYTE Antenna);
extern void OutputFromAudioBufferFP(uint8 Slot, uint8 BufferNr);
extern uint8 InputToAudioBufferFP(uint8 Slot, uint8 BufferNr);
extern void MuteAudioBufferFP(BYTE Slot);
extern void IncreaseToNormVolumeFP(uint8 SlotNr);
extern void MuteSpeechBufferFP(uint8 SlotNr);
extern void BuildRxEmptyFP(uint8 Slot);
extern void BuildRxEncryptionFP(uint8 Slot);
extern void BuildTxEncryptionFP(uint8 Slot);
extern void LoadBmcEncKeyFP(uint8 Slot, uint8 * KeyPtr);
extern void StartAdpcmFP(void);
extern void SetComperator(uint16 Level);
extern void SetSearchCarrier(BYTE Freq);
extern void ReSyncronizeNewFreqFP(BYTE Antenna);
extern void SyncronizeToSlotFP(BYTE Slot);
extern void SetCodecMicGain(uint8 Gain);
extern void SetCodecSpkAttenuation(uint8 Gain);
extern void SetSpeakerAttenuation(uint8 Attenuation);
extern void SetAntennaTime(int8 TimeShift);
extern void bmcdrivx_SetModulation(uint8 Modulation);
extern void bmcdrivx_GetQuadTuneValue(uint8 Result[2]);
extern void bmcdriv_SetTxFreq(BYTE Slot, BYTE Freq);
extern void bmcdriv_SetRxFreq(BYTE Slot, BYTE Freq);
void SetModulationFP(BYTE ModulationValue);
extern void ExecOneBmcInstructionFP(uint16 Instruc);
extern void BusyWait1000(void);

#define COMPERATORLEVELSHIFT 4  /* Number of position shifted right before output to DAC */
#define MAXCOMPERATORLEVEL (0x3f<<COMPERATORLEVELSHIFT)
