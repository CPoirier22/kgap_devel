/* $Header:   K:/PH/140960xx/00/Archive/H/bmcdef.h_v   1.1   17 Sep 2003 08:11:22   mne  $ */
#include "../../../common/include/gapcfg.h"
#include "../bmcdef.h"

#ifndef __BMCDEF_H
#define __BMCDEF_H


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
    BYTE Command;
    BYTE Parameter;
} BmcInstructionType;
#endif

typedef BmcInstructionType BmcCtrlRamType[256];



typedef struct
{
    BYTE Byte1,Byte2;
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
    BYTE        Head;
    BYTE        Tail[5];
}
BearerTxDataType;

typedef struct
{
    SyntRegType  RxFreq;
    RxStatusType RxStatus;
    BYTE         Head;
    BYTE         Tail[5];
    BYTE         Fill[3];
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
{
    BYTE             ControlRegister;
    BmcControlType   BmcControl;
    BYTE             Iv56;   /* This should be part of BmcControl */
    BYTE             EncryptionKey[8];
    BYTE             Fill0[1];
    SyntRefModeType  TxSyntRefMode;
    SyntRefModeType  RxSyntRefMode;
    SyntRegType      SyntReference;
    BYTE             SyntReference_1;
    BYTE             ScanRssiLevel;
    CodecControlType CodecControl;
    CodecControlType CodecIdleControl;
    BYTE             EncryptionStatus[11];
    BearerStatusType BearerStatus;
    BYTE             Fill1[0x20];
    BearerTxDataType BearerTxData[NOOFBEARERS];
    BearerRxDataType BearerRxData[NOOFBEARERS];
    BYTE             ScratchBfield[8];
    BYTE             SyncPattern[4];
    SyntRegType      ScanFreq;
    BYTE             AlternatingBits[2];
}
BmcDataBank0Type;

typedef struct
{
#ifdef __TURBOC__
    BYTE Bank0[256];
#endif
    BYTE ControlRegister;
    BYTE Byte1;
    BYTE SpeechBuffer0[40],Fillb0[2];
    BYTE SpeechBuffer1[40],Fillb1[2];
    BYTE SpeechBuffer2[40],Fillb2[2];
    BYTE SpeechBuffer3[40],Fillb3[2];
    BYTE SilentBuffer[40], Fillb4[2];
    BYTE ScratchBuffer[40],Fillb5[2];
}
BmcDataBank1Type;

typedef union {
    BYTE ControlRegister;
    BYTE Byte[512];
    BmcDataBank0Type Bank0;
    BmcDataBank1Type Bank1;
}BmcDataRamType;

extern BmcCtrlRamType BmcCtrlRam;
extern BmcDataRamType BmcDataRamPP;

#endif
