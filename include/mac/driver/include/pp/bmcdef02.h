/****************************************************************************
 * Project   : DECT                                                          *
 * Module    : Defintion for BMC                                             *
 * Reference :                                                               *
 * Type      : Headerfile                                                    *
 * Function  :                                                               *
 * Systems   : Handset                                                       *
 *---------------------------------------------------------------------------*
 * Kirk Telecom A/S. All rights reserved.                                    *
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/bmcdef02.h_v   1.4   07 Sep 2005 09:28:14   mne  $
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/bmcdef02.h_v  $
 *
 *    Rev 1.4   07 Sep 2005 09:28:14   mne
 * New functions for 1g9 USA Syntese added.
 *
 ****************************************************************************/

#ifndef __BMCDEF_H
#define __BMCDEF_H

#include "../../../../common/include/_stddef.h"

#define SLOTPROGRAMSIZE 2
#define NOOFBEARERS 6

#ifdef __TURBOC__
typedef struct
{
    BYTE Command;
    BYTE Parameter;
}
BmcInstructionType;
#else
typedef union  {
    WORD Command;
} BmcInstructionType;
#endif

typedef BmcInstructionType BmcCtrlRamType[256];

typedef struct
{
    BYTE SyncCfg;      /* S_err[0..3],INV_RDI,INV_TDO,SenseA,PP/Fpn*/
    BYTE Slide_Mask;   /* Slide[0..3] Mask[0..3]*/
    BYTE Vol;          /* Vol[5..0]*/
    BYTE DAC;          /* Don, TM_ANA, DAC[0..5]*/
    BYTE DpllAdpWin;   /* DPLL[0..2], ADP, WIN[0..3]*/
    BYTE Misc;         /* ENCoff, SenseS, Ron, nc, SCoff, DOFr, M[0..1]*/
    BYTE MFR0_FR_nr;   /* MFR[0..3],FR_nr[0..3]*/
    BYTE MFR4;        /* MFR[4..11]                                */
    BYTE MFR12;       /* MFR[12..19]                               */
    BYTE MFR20_IV28;  /* IV[28..31],MFR[20..23]                    */
    BYTE IV32[3];     /* IV[32..39],IV[40..47],IV[48..55]          */
}
_BmcControlType;

typedef struct
{
    BYTE AdcResult;
    BYTE CRCresult;
    BYTE SlideErrors;
    BYTE ReceivePhase;
    BYTE Ones;
}
RxStatusType;

typedef struct
{
    BYTE Byte1,Byte2,Byte3;

}
SyntRegType;

typedef struct
{
    BYTE R_divide;
    BYTE SyntMode[3];
}
SyntRefModeType;

typedef struct
{
    SyntRegType TxFreq;
    RxStatusType TxStatus;
    BYTE        Head;
    BYTE        Tail[5];
    BYTE        Fill[2];


}
BearerTxDataType;

typedef struct
{
    SyntRegType  RxFreq;
    RxStatusType RxStatus;
    BYTE         Head;
    BYTE         Tail[5];
    BYTE         Fill[2];

}
BearerRxDataType;

typedef struct
{ /* Provision for signal-quality monitoring. Not used by BMC */
    BYTE   Quality;
    BYTE   Rssi;
    BYTE   Header;
    BYTE   Resv0;
    BYTE   Resv1;
}
BearerStatusType;

typedef struct
{ /* Provision for signal-quality monitoring. Not used by BMC */
    BYTE   Byte1;
    BYTE   Byte2;
}
RSSIMessType;

typedef struct
{
    /*-- Bank 0 --*/
    /*BYTE             Reserved00;*/
    _BmcControlType   BmcControl;
    BYTE             Iv56;   /* This should be part of BmcControl */
    BYTE             EncryptionKey[8];
    BYTE             Max_RSSI;
    SyntRefModeType  TxSyntRefMode;              /* 18*/
    BYTE             LMX4169Timing[3];           /* 1C Holds 24 Bit control word to LMX4169 typ. 04 00 00*/
    BYTE             Fill_1[1];
    SyntRefModeType  RxSyntRefMode;              /* 20*/
    BYTE             LMX4169NoTiming[3];         /* 24 Holds 24 Bit control word to LMX4169 typ. 05 77 D0*/
    BYTE             Fill_2[1];                  /* 27*/
    SyntRegType      SyntReference;              /* 28*/
    BYTE             SyntReference_1;
    BYTE             ScanRssiLevel;
    BYTE             LMX4169FixedSlice[3];       /* 2D Holds 24 Bit control word to LMX4169 typ. 39 00 35*/
    SyntRegType      RxOff;                      /* 30*/
    BYTE             LMX4169MeassSlice[3];       /* 33 Holds 24 Bit control word to LMX4169 typ. 39 00 3F*/
    BYTE             Fill_4[2];
    CodecControlType CodecIdleControl;           /* 38*/
    BYTE Fill05[2];
    BYTE             EncryptionStatus[11];       /* 40*/
    BearerStatusType BearerStatus;
    RSSIMessType     RSSIMess[3];
    BYTE             Fill_5[0x20-16-3*sizeof(RSSIMessType)];
    BearerTxDataType BearerTxData[NOOFBEARERS/2];/* 60*/
    BearerRxDataType BearerRxData[NOOFBEARERS];
    BYTE             ScratchBfield[4];
    BYTE             SyncPattern[4];
    BYTE             AlternatingBits[8];         /* f8*/
}
BmcDataPPBank0Type;

typedef struct
{
    BYTE Byte0;
    BYTE Byte1;
    BYTE SpeechBuffer0[40],Fillb0[2];
    BYTE SpeechBuffer1[40],Fillb1[2];
    BYTE SpeechBuffer2[40],Fillb2[2];
    BYTE SpeechBuffer3[40],Fillb3[2];
    BYTE SilentBuffer[40], Fillb4[2];
    BYTE ScratchBuffer[40],Fillb5[2];
    BYTE ByteFE,ByteFF;
}
BmcDataPPBank1Type;

typedef struct
{
    BYTE TempLMX[256];
}
BmcDataPPBank2Type;

typedef volatile struct
{
    BYTE Byte[1];
    BmcDataPPBank0Type Bank0;
    BmcDataPPBank1Type Bank1;
    BmcDataPPBank2Type Bank3;
}
BmcDataRamPPType;

typedef union
{
    BmcDataRamPPType   PPBank;
} BmcDataRamType;

extern BmcDataRamType BmcDataRam;

/*extern BmcDataRamPPType BmcDataRamPP; // KEH two 'banks' of shared DIP data memory*/
extern BmcCtrlRamType BmcCtrlRam;

#endif
