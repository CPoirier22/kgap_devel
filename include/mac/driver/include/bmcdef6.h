#ifndef BMCDEF6_H_
#define BMCDEF6_H_

#include "bmcdef.h"
/*#include "../../../driver/include/bmcdef.h"*/

#define NOOFBEARERS_FP 6

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
    BYTE IV32[4];     /* IV[32..39],IV[40..47],IV[48..55]          */
} PACKED BmcControlType;

typedef struct
{                                 /* size      addr*/
    SyntRegType NxFreq;           /*  3         00*/
    RxStatusType RxStatus;        /*  5         03*/
    BYTE Head;                    /*  1         08*/
    BYTE Tail[5];                 /*  5         09*/
    BmcControlType BmcControl;    /* 14         0E*/
    BYTE EncStatus[11];           /* 11         18*/
    SyntRegType RxSyntRefMode;    /*  3         23*/
    BYTE Rssi4180;                /*  1         26*/
    BYTE GetRssiReg;              /*  1                  67*/
    BYTE TrafficBearer;           /*  1                  68*/
    BYTE RssiAdcCopy;
    BYTE RxFill[0x60 - 3 - sizeof(SyntRegType) - 1 - 1 - 1 - 1 - 4];
} PACKED FPBearerRxDataType;               /* 35*/

typedef struct
{                                 /* size      addr12   addr6*/
    BYTE TxFill[0x40];            /*  64        00       00*/
    SyntRegType NxFreq;           /*  3         20       40*/
    RxStatusType Reserved_Status; /*  5         23       43*/
    BYTE Head;                    /*  1         28       48*/
    BYTE Tail[5];                 /*  5         29       49*/
    BmcControlType BmcControl;    /* 14         2E       4E*/
    BYTE EncKeyTest[8];               /*  8         38       58*/
    BYTE TxFill1[3];              /*  3                  60*/
    SyntRegType TxFill2;          /*  3                  63*/
    BYTE Rssi4180;                /*  1                  66*/
    BYTE GetRssiReg;              /*  1                  67*/
    BYTE TxFill3[0x20 - 3 - sizeof(SyntRegType) - 1 - 1 - 4];
} PACKED FPBearerTxDataType;             /* 32*/

#include "bmcdataramtype.h"
#include "fp/slotdatatype.h"

#endif /*BMCDEF6_H_*/
