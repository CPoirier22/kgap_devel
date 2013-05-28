/******************************************************************************
* Project   : Windows Development Environment                                 *
*                                                                             *
* Module    : BMC simulation                                                  *
*                                                                             *
* Reference : Windows Development Environment system specification            *
*                                                                             *
* Type      : Simulation software                                             *
*                                                                             *
* Function  : Drfinition of the National SC144XX instruction set              *
*                                                                             *
* Systems   : PC simulations                                                  *
*-----------------------------------------------------------------------------*
* Copyright (c) 1998 by RTX Telecom A/S                                       *
* $Header:   K:/PH/140960xx/00/Archive/H/instr428.h_v   1.0   Oct 24 2002 11:51:26   mne  $                                                                 *
*******************************************************************************/

#ifndef __INSTR428_H__
#define __INSTR428_H__





#define  BR             0x01   //    X    X    X    X    X    X
#define  BR_B0          0x10   //                             X
#define  BR_B1          0x11   //                             X
#define  BRK            0x6E   //    X    X    X    X    X    X
#define  JMP            0x02   //    X    X    X    X    X    X
#define  JMP1           0x03   //    X    X    X    X    X    X
#define  JC             0x13   //                                  X
#define  RTN            0x04   //    X    X    X    X    X    X
#define  JMPF           0x12   //                             X
#define  RTNF           0x14   //                             X
#define  WNT            0x08   //    X    X    X    X    X    X
#define  WT             0x09   //    X    X    X    X    X    X
#define  PAG_ON         0x18   //                             X
#define  PAG_OFF        0x19   //                             X
#define  WSC            0x48   //         X    X    X    X    X
#define  RFEN           0x0B   //    X    X    X    X    X    X
#define  RFDIS          0x0A   //    X    X    X    X    X    X
#define  BK_A           0x0E   //    X    X    X    X    X    X
#define  BK_A1          0x05   //         X    X                   X
#define  BK_A2          0x1E   //                                  X
#define  BK_A3          0x15   //                                  X
#define  BK_MA          0x16   //                                  X
#define  BK_C           0x0F   //    X    X    X    X    X    X
#define  BK_MC          0x1F   //                                  X
#define  SLOTZERO       0x0D   //    X    X    X    X    X    X
#define  EN_SL_ADJ      0x2C   //    X    X    X    X    X    X
#define  WNTP1          0x07   //    X    X    X    X    X    X
#define  WNTM1          0x06   //    X    X    X    X    X    X
#define  LD_PTR         0x0C   //    X    X    X    X    X    X
#define  LD_PTR2        0x1C   //                                  X
#define  UNLCK          0x28   //    X    X    X    X    X    X
#define  BCPV           0x4B   //                             X


#define  A_MUTE         0xC1   //    X    X    X    X    X    X
#define  A_MTOFF        0xC9   //         X    X    X    X    X
#define  A_STOFF        0xC2   //    X    X    X    X    X    X
#define  A_STON         0xCC   //    X    X    X    X    X    X
#define  A_RCV0         0x80   //    X    X    X    X    X    X
#define  A_RCV36        0x82   //    X    X    X    X    X    X
#define  A_RCV30        0x83   //    X    X    X    X    X    X
#define  A_RCV24        0x84   //    X    X    X    X    X    X
#define  A_RCV18        0x85   //    X    X    X    X    X    X
#define  A_RCV12        0x86   //    X    X    X    X    X    X
#define  A_RCV6         0x87   //    X    X    X    X    X    X
#define  A_RCV33        0x8A   //    X    X    X    X    X    X
#define  A_RCV27        0x8B   //    X    X    X    X    X    X
#define  A_RCV21        0x8C   //    X    X    X    X    X    X
#define  A_RCV15        0x8D   //    X    X    X    X    X    X
#define  A_RCV9         0x8E   //    X    X    X    X    X    X
#define  A_RCV3         0x8F   //    X    X    X    X    X    X
#define  A_NORM         0xC5   //    X    X    X    X    X    X
#define  A_RST          0xC0   //    X    X    X    X    X    X
#define  A_LDR          0xC6   //    X    X    X    X    X    X
#define  A_LDW          0xC7   //    X    X    X    X    X    X
#define  A_MUTE1        0xCA   //         X    X                   X
#define  A_MTOFF1       0xCB   //         X    X                   X
#define  A_RST1         0xEB   //         X    X                   X
#define  A_LDR1         0xCE   //         X    X    X    X         X
#define  A_LDW1         0xCF   //         X    X    X    X         X
#define  A_MUTE2        0xD1   //                                  X
#define  A_MTOFF2       0xD9   //                                  X
#define  A_RST2         0xD0   //                                  X
#define  A_LDR2         0xD6   //                                  X
#define  A_LDW2         0xD7   //                                  X
#define  A_MUTE3        0xDA   //                                  X
#define  A_MTOFF3       0xDB   //                                  X
#define  A_RST3         0xE3   //                                  X
#define  A_LDR3         0xDE   //                                  X
#define  A_LDW3         0xDF   //                                  X



#define  B_ST           0x31   //    X    X    X    X    X    X
#define  B_TX           0x31   //    X    X    X    X    X    X
#define  B_ST2          0x21   //    X    X    X    X    X    X
#define  B_PPT          0x22   //              X    X    X    X
#define  B_AT           0x32   //    X    X    X    X    X    X
#define  B_AT2          0x37   //    X    X    X    X    X    X
#define  B_BT           0x34   //    X    X    X    X    X    X
#define  B_BTFM         0x23   //              X    X    X    X
#define  B_BTFU         0x25   //    X    X    X    X    X    X B_BT2 in 420
#define  B_BTFP         0x35   //    X    X    X    X    X    X B_BTP in 420
#define  B_BTDU         0x71   //              X    X    X    X
#define  B_BTDP         0x72   //              X    X    X    X
#define  B_ON           0x27   //    X    X    X    X    X    X
#define  B_XON          0x27   //    X    X    X    X    X    X
#define  B_XOFF         0x26   //    X    X    X    X    X    X
#define  B_SR           0x29   //    X    X    X    X    X    X
#define  B_AR           0x3A   //    X    X    X    X    X    X
#define  B_AR2          0x3F   //    X    X    X    X    X    X
#define  B_RON          0x2F   //    X    X    X    X    X    X
#define  B_RINV         0x2E   //    X    X    X    X    X    X
#define  B_BR           0x3C   //    X    X    X    X    X    X
#define  B_BRFU         0x2D   //    X    X    X    X    X    X B_BR2 in 420

#define  B_BRFP         0x3D   //    X    X    X    X    X    X B_BRP in 420
#define  B_BRFD         0x2A   //              X    X    X    X
#define  B_BRDU         0x79   //              X    X    X    X
#define  B_BRDP         0x7A   //              X    X    X    X
#define  B_NIC          0x9F   //                             X
#define  B_XR           0x2B   //    X    X    X    X    X    X
#define  B_XT           0x24   //    X    X    X    X    X    X
#define  B_WB_ON        0x65   //    X    X    X    X    X    X
#define  B_WB_OFF       0x64   //    X    X    X    X    X    X
#define  B_WRS          0x39   //    X    X    X    X    X    X
#define  B_WRS2         0x38   //                             X
#define  B_UNLCK        0x98   //                             X
#define  B_RC           0x33   //    X    X    X    X    X    X
#define  B_RST          0x20   //    X    X    X    X    X    X
#define  B_DIV1         0x4F   //                        X    X
#define  B_DIV2         0x4E   //                        X    X
#define  B_DIV4         0x4D   //                        X    X







#define  C_LD2          0xBA   //              X
#define  C_ON2          0xAE   //              X
#define  C_OFF2         0xAF   //              X



#define  D_LDK           0x50   //    X    X    X    X    X   X
#define  D_PREP          0x44   //    X    X    X    X    X   X
#define  D_WRS           0x5F   //    X    X    X    X    X   X
#define  D_LDS           0x57   //    X    X    X    X    X   X
#define  D_RST           0x40   //    X    X    X    X    X   X


#define  M_WR            0xB9   //    X    X    X    X    X   X
#define  M_RST           0xA9   //    X    X    X    X    X   X
#define  M_INI0          0xA0   //              X    X    X   X
#define  M_INI1          0xA1   //              X    X    X   X
#define  MEN1N           0xA4   //    X    X    X    X    X   X
#define  MEN1            0xA5   //    X    X    X    X    X   X

#define  M_WRS           0xB8   //    Special use only (KM)

#define  P_EN            0xE9   //    X    X    X    X    X   X
#define  P_LDH           0xED   //    X    X    X    X    X   X
#define  P_LDL           0xEC   //    X    X    X    X    X   X
#define  P_FAD           0xE6   //                            X
#define  P_ANT           0xE7   //                            X
#define  P_LD            0xE8   //    X    X    X    X    X   X
#define  P_SC            0xEA   //    X    X    X    X    X   X


#define  U_INT0          0x61   //    X    X    X    X    X   X
#define  U_INT1          0x6B   //    X    X    X    X    X   X
#define  U_INT2          0x6D   //    X    X    X    X    X   X
#define  U_INT3          0x6F   //    X    X    X    X    X   X
#define  U_PSC           0x60   //    X    X    X    X    X   X
#define  U_VINT          0x63   //    X    X    X    X    X   X
#define  U_VNMI          0x4C   //                                 X









#define BMCBANKSHIFT    3      //Number of address bits shifted left in BK_C



#define ADPCM0       0xfd
#define ADPCM1       0xfe
#define ARGPTR       0xff


#define FADANT1      0x05
#define FADANT2      0x04
#define FADANTSEL    0x00
#define RSSIMEAS     0x06




typedef struct
{
    uint8 ADCresult;
    uint8 CRCresult;
    uint8 SlideError;
    uint8 ReceivePhase;
    uint8 Ones;
#ifndef BSUB_EXCLUDE
    uint8 B5_B10_CRC; // 6 bit Bn_CRC
#endif
}
DipRxStatusType;


#define SYNCMASK     0x80
#define ACRCMASK     0x40
#define XCRCMASK     0x02
#define ZMASK        0x01
#define NOACCESSPATT 0x24

#endif
