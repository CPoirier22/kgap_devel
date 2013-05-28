
/*************************************************************************
* Project   : Peltor P840                                                 
* Module    : BMC_PRG.h                                                   
* Reference :                                                             
* Type      : SC14428 DIP header file.                                    
* Function  :                                                             
* Systems   : PP                                                          
*-------------------------------------------------------------------------
* Copyright (c) 2006 by KIRK Telecom A/S.                                 
**************************************************************************/


/* $Header:    $   */


/* Data labels definition */
#define SLOT13INC            0x0001

#define BMCCONTROL_OFS       0x1
#define TXSYNTREFMODE_OFS    0x18
#define LMX4169TIM_OFS       0x1C
#define RXSYNTREFMODE_OFS    0x20
#define LMX4169_NO_TIM_OFS   0x24
#define ALTERNATINGBITS_OFS  0xF8
#define SYNCPATTERN_OFS      0xF4
#define LMX4169_FIX_SLI_OFS  0x2D
#define LMX4169_MEA_SLI_OFS  0x33
#define BEARERRXDATA_OFS     0x90
#define BEARERRXDATA_SIZE    0x10
#define RSSISCANNDATA_OFS    0x200
#define RSSISCANNDATA_SIZE   0x10
#define RSSISCANNSTATUS_OFS  0x3
#define RSSISCANNAFIELD_OFS  0x8
#define RXOFF_OFS            0x30
#define RXSTATUS_OFS         0x3
#define RXAFIELD_OFS         0x8
#define BEARERTXDATA_OFS     0x60
#define BEARERTXDATA_SIZE    0x10
#define TXSTATUS_OFS         0x3
#define TXAFIELD_OFS         0x8
#define SCRATCHRX_OFS        0xF0
#define ENCRYPTION_IV_OFS    0x7
#define ENCRYPTSTATUS_OFS    0x40
#define SILENTBUFFER_OFS     0x1AA
#define SCRATCHBUFFER_OFS    0x1D4
#define SPEECHBUFFER0_OFS    0x102
#define SPEECHBUFFER1_OFS    0x12C
#define SPEECHBUFFER2_OFS    0x156
#define SPEECHBUFFER3_OFS    0x180
