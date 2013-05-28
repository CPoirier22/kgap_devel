#ifndef BMCDEF12_H_
#define BMCDEF12_H_

#include "bmcdef.h" 

#define NOOFBEARERS_FP 12

typedef struct
{
    BYTE SyncCfg;                 /* S_err[0..3],INV_RDI,INV_TDO,SenseA,PP/Fpn*/
    BYTE MaskSlide;               /* Mask[0..3] Slide[0..3]*/
    BYTE CmVol;                   /* CM5, CM, Vol[5..0]*/
    BYTE DAC;                     /* Don, TM_ANA, DAC[0..5]*/
    BYTE AdpWin;                  /* DPLL[0..2], ADP, WIN[0..3]*/
    BYTE Misc;                    /* ENCoff, SenseS, Ron, nc, SCoff, DOFr, M[0..1]*/
    BYTE MFR0_FR_nr;              /* MFR[0..3],FR_nr[0..3]*/
    BYTE MFR4;                    /* MFR[4..11]*/
    BYTE MFR12;                   /* MFR[12..19]*/
    BYTE MFR20_IV28;              /* IV[28..31],MFR[20..23]*/
} PACKED BmcControlType;

typedef struct
{
    SyntRegType DownFreq;         /*      3*/
    RxStatusType DownStatus;      /*  5*/
    BYTE DownHead;                /*  1*/
    BYTE DownTail[5];             /*  5*/
    BmcControlType BmcControl;    /* 10*/
    BYTE EncKey[8];               /*  8*/
    SyntRegType UpFreq;           /*  3*/
    RxStatusType UpStatus;        /*  5*/
    BYTE UpHead;                  /*  1*/
    BYTE UpTail[5];               /*  5*/
    BYTE BmcControl_Short[3];     /* 3*/
    BYTE EncIv[4];                /*  4*/
    BYTE EncStatus[11];           /* 11*/
} PACKED BearerCommonType;

typedef struct
{                                 /* size      addr*/
    SyntRegType NxFreq;           /*  3         00*/
    RxStatusType RxStatus;        /*  5         03*/
    BYTE Head;                    /*  1         08*/
    BYTE Tail[5];                 /*  5         09*/
    BmcControlType BmcControl;    /* 10         0E*/
    BYTE EncKey[8];               /*  8         18*/
    SyntRegType RxSyntRefMode;    /*  3         20  Note: do not use - overlapping!!!!!*/
    BYTE RxFill[0x20 - sizeof(SyntRegType)];
}
FPBearerRxDataType;               /* 35*/

typedef struct
{                                 /* size      addr12   addr6*/
    BYTE TxFill[0x20];            /*  32        00       00*/
    SyntRegType NxFreq;           /*  3         20       40*/
    RxStatusType Reserved_Status; /*  5         23       43*/
    BYTE Head;                    /*  1         28       48*/
    BYTE Tail[5];                 /*  5         29       49*/
    BmcControlType BmcControl;    /* 10         2E       4E*/
    BYTE EncKey[8];               /*  8         38       58*/
}
FPBearerTxDataType;             /* 32*/

#include "bmcdataramtype.h"
#include "fp/slotdatatype.h"

#endif /*BMCDEF12_H_*/
