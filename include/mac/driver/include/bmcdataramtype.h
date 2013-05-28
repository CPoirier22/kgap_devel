#ifndef BMCDATARAMTYPE_H_
#define BMCDATARAMTYPE_H_

typedef union
{
    FPBearerTxDataType BearerTxData;        /* 32*/
    FPBearerRxDataType BearerRxData;        /* 35*/
} PACKED BearerDataType;

typedef struct
{
    /*-- Bank 0 --*/
    BYTE SpeechBuffer0[40];       /* Transmit buffers for line 0*/
    BYTE SpeechBuffer1[40];       /* Receive buffers for line 0*/
    BYTE SpeechBuffer2[40];       /* Transmit buffers for line 1*/
    BYTE SpeechBuffer3[40];       /* Receive buffers for line 1*/
    BYTE SpeechBuffer4[40];       /* Transmit buffers for line 2*/
    BYTE SpeechBuffer5[40];       /* Receive buffers for line 2*/
    BYTE FillInt0;                /* Command used to request RSSI from LMX4180 (0x80 | 0x24)*/
    LMX24BitType LMX4180CalibSynt;    /* 2D Holds 24 Bit control word to LMX4169 typ. 39 00 35*/
    LMX24BitType LMX4169FixedSlice;    /* 2D Holds 24 Bit control word to LMX4169 typ. 39 00 35*/
    LMX24BitType LMX4169MeassSlice;    /* 33 Holds 24 Bit control word to LMX4169 typ. 39 00 3F*/
    SyntRegType LMX4169Timing;    /* 03 24 Holds 24 Bit control word to LMX4169 typ. 05 77 D0*/
    SyntRegType LMX4169NoTiming;  /* 03 24 Holds 24 Bit control word to LMX4169 typ. 05 77 D0*/
    /*-- Bank 1 --*/
    BYTE SpeechBuffer6[40];       /* Transmit buffers for line 3*/
    BYTE SpeechBuffer7[40];       /* Receive buffers for line 3*/
    BYTE SpeechBuffer8[40];       /* Transmit buffers for line 4*/
    BYTE SpeechBuffer9[40];       /* Receive buffers for line 4*/
    BYTE SpeechBuffer10[40];      /* Transmit buffers for line 5*/
    BYTE SpeechBuffer11[40];      /* Receive buffers for line 5*/
    BYTE FillInt1[8];
    BYTE AlternatingBits[8];      /* f8*/
    /*-- Bank 2 --*/
    BYTE SpeechBuffer12[40];      /* Transmit buffers for line 6*/
    BYTE SpeechBuffer13[40];      /* Receive buffers for line 6*/
    BYTE SpeechBuffer14[40];      /* Transmit buffers for line 7*/
    BYTE SpeechBuffer15[40];      /* Receive buffers for line 7*/
    BYTE SpeechBuffer16[40];      /* Transmit buffers for line 8*/
    BYTE SpeechBuffer17[40];      /* Receive buffers for line 8*/
    BYTE RSSIMess[12];
    BYTE FillInt2[16-12];
    /*-- Bank 3 - 5 --*/
    BearerDataType BearerData[NOOFBEARERS_FP];

    /*-- Bank 6 --*/
    BYTE SpeechBuffer18[40];      /* Transmit buffers for line 9*/
    BYTE SpeechBuffer19[40];      /* Receive buffers for line 9*/
    BYTE SpeechBuffer20[40];      /* Transmit buffers for line 10*/
    BYTE SpeechBuffer21[40];      /* Receive buffers for line 10*/
    BYTE SpeechBuffer22[40];      /* Transmit buffers for line 11*/
    BYTE SpeechBuffer23[40];      /* Receive buffers for line 11*/
    SyntRegType LMXTempStorage;   /* 03*/
    BYTE FillInt5[16 - sizeof(SyntRegType) - 1];
    BYTE ControlRegister;
    /*-- Bank 7 --*/
    LMXSetupParameterType LMXSetupParameterTim[8];
} PACKED BmcDataFPBank0Type;

typedef union
{
    BYTE Byte[0x800];
    BmcDataFPBank0Type Bank0;
    BmcDataFPBank0Type Bank1;
    PPBmcDataRamType   PPBank;
} PACKED BmcDataRamType;

extern BmcDataRamType BmcDataRam;
#define BmcDataRam(x)      BmcDataRam.x

#endif /*BMCDATARAMTYPE_H_*/
