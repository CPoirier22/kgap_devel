#ifndef __BMCDRIVP_H
#define __BMCDRIVP_H
/*****************************************************************************
* Project   : DECT
* Module    : BMC driver
* Reference :
* Type      : Headerfile for slot switching interrupt handler.
* Function  :
* Systems   : Handset
*
* Copyright (c) 1996 by Kirk telecom A/S.
* $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/bmcdrivp.h_v   1.5   23 Jan 2006 12:08:28   mne  $ *
* $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/bmcdrivp.h_v  $
 *
 *    Rev 1.5   23 Jan 2006 12:08:28   mne
 * New Interrupt routine added, and Low Duty Cycle changed.
 *
 *    Rev 1.4   07 Sep 2005 09:28:14   mne
 * New functions for 1g9 USA Syntese added.
 *
 *    Rev 1.3   11 Feb 2005 13:56:28   MNE
 * #ifdef _LMX4168_ changed to #ifdef _LMX4169_
 * Unused code removed.
 *
 *    Rev 1.2   18 Nov 2004 13:10:38   MNE
 * Now Codec LSR is placed in EProm and send to HSAudio at RequestLsrMicGain.
*****************************************************************************/

#define EVENSLOTS
#define UNALLOCATED 0xff

/* NonGapExtFreqMode values*/
#define EUROPE_SYNT         0
#define CHINA_SYNT          1
#define SOUTH_AMERICA_SYNT  2
#define TAIWAN_SYNT         3
#define USA_SYNT            4


#ifdef _PMB6610_  /* Infineon synthese*/

#define  RxSynthesisValue_Byte1(chan) (uint16) ((0xFFFF^(0x2290-(int16)(((chan)+DECT_Channel_offset)*64)))>>8)
#define  RxSynthesisValue_Byte2(chan) (uint16) (0xFFFF^(0x2290-(int16)(((chan)+DECT_Channel_offset)*64)))
#define  RxSynthesisValue_Byte3(chan) (0)

#define  TxSynthesisValue_Byte1(chan) (uint16)((0xFFFF^(0x22B0-(int16)(((chan)+DECT_Channel_offset)*64)))>>8)
#define  TxSynthesisValue_Byte2(chan) (uint16)(0xFFFF^(0x22B0-(int16)(((chan)+DECT_Channel_offset)*64)))
#define  TxSynthesisValue_Byte3(chan) (0)
#endif

typedef struct
{
    BYTE SyncCfg;     /* S_err[0..3],INV_RDI,INV_TDO,SenseA,PP/Fpn */
    BYTE Slide_Mask;   /* Slide[0..3] Mask[0..3]*/
    BYTE Vol;          /* Vol[5..0]*/
    BYTE DAC;          /* Don, TM_ANA, DAC[0..5]*/
    BYTE DpllAdpWin;   /* DPLL[0..2], ADP, WIN[0..3]*/
    BYTE Misc;         /* ENCoff, SenseS, Ron, nc, SCoff, DOFr, M[0..1]*/
    BYTE AnalogControl; /* All: C2 ; Gausian only: 7F */
    BYTE TestByte1;    /* xxx00000 */
    BYTE LrsMicGain;   /* LLLLMMMM */
    BYTE Vref;         /* xxxx1000  bit[0..3]=BANDGAP to adjust AVD2/AVD*/
    BYTE TestByte3;    /* xxxxx000 */
    BYTE TestByte4;    /* 00000000 */
    BYTE Reserved[2];
    BYTE Synt3161Offset; /* DCBAP100 */
    BYTE TxMode3161;
    BYTE RxMode3161;
    BYTE MuteCtrl;
}
BmcInitDataTypePP;

typedef struct {
				BYTE RSSI_Messurement;
				BYTE ARI[5];
			   }RSSI_Scan_Type;

extern void InitialWakeBmcPP(void);
extern void InitBmcToSearch(BmcInitDataTypePP *BmcInitData);
extern void InitBmcToContineousReceive(BYTE Freq, BYTE QuadInitLevel);
extern void BuildReceiveSlot(BYTE Slot, BYTE Freq);
extern void BuildIdleRxSlot(void);
extern void SetReceiverFrequencyPP(BYTE Slot, BYTE Freq);
extern void SetScanCarrier(BYTE Freq);
extern void ReSyncronizeNewFreqPP(void);
extern void BuildSuspendSearch(void);
extern void BuildToneInSearch(void);
extern void BuildNoToneInSearch(void);
extern void SetFrameNumberPP(void);
extern void BuildTxSlotPP(BYTE Slot, BYTE Freq);
extern void BuildRxinTxSlot(BYTE Slot, BYTE Freq);
extern void BuildIdleTxSlot(BYTE Slot);
extern void OutputFromAudioBufferPP(BYTE Slot, BYTE BufferNr);
extern void InputToAudioBufferPP(BYTE Slot, BYTE BufferNr);
extern void MuteSpeechBufferPP(BYTE BufferNr);
extern void SideToneOn(void);
extern void SideToneOff(void);
extern void StartAdpcmPP(void);
extern void StopAdpcm(void);
extern void SetVolumenLevel(BYTE Level);
extern void SetCodecGain_Lsr_reg(BYTE Value, WORD Codec_Lsr_reg);
extern void IncreaseToNormVolumePP(void);
extern void ReduceActualVolume(BYTE ForcedMute);
extern void BmcAudioControl(BYTE AudioCmd);
extern void BuildRxEmptyPP(BYTE Slot);
extern void BuildRxEncryptionPP(BYTE Slot);
extern void BuildTxEncryptionPP(BYTE Slot);
extern void LoadBmcEncKeyPP(BYTE *KeyPtr);
extern void SyncronizeToSlotPP(BYTE Slot);
extern void ClearSlot12Int(void);
extern void DisableSlideAdjust(void);
extern void EnableSlideAdjust(void);
extern void BuildSuspendFrame(BYTE FrameCount);
extern void QuadraturTracking(void);
extern BYTE ActiveReceivers;
extern void ContTX(BYTE Freq);
extern void ContRX(BYTE Freq);
void SetModulationPP(BYTE ModulationValue);
void PPSelectDownLinkAntenna(BYTE Slot, BYTE Antenna, BYTE Location);
void PPSelectRxAntenna(BYTE Antenna, BYTE Slot);
void PPSelectTxAntenna(BYTE Antenna, BYTE Slot);

extern BYTE LastGoodDacValue;
extern signed char DECT_Channel_offset;

#define COMPERATORLEVELSHIFT 4 /* Number of position shifted right before output to DAC */
#define MAXCOMPERATORLEVEL (0x3f<<COMPERATORLEVELSHIFT)

void _SetSystemClock(BYTE name, BYTE HighSpeed);


#else

#endif

