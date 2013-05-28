#ifndef __DSPTEST_H
#define __DSPTEST_H
/****************************************************************************
*  Program/file: DSPTEST.H
*
*  Copyright (C) by RTX TELECOM A/S, Denmark.
*  These computer program listings and specifications, are the property of
*  RTX TELECOM A/S, Denmark and shall not be reproduced or copied or used in
*  whole or in part without written permission from RTX TELECOM A/S, Denmark.
*
*  Programmer: Michael Steen Jensen
*
*  MODULE:
*  CONTROLLING DOCUMENT:
*  SYSTEM DEPENDENCIES:  None
*
*  DESCRIPTION:
****************************************************************************/

/****************************************************************************
* PVCS info
*****************************************************************************

$Author:   on  $
$Date:   Nov 18 2003 09:59:12  $
$Revision:   1.1  $
$Modtime:   Nov 04 2003 10:03:06  $
*/


/****************************************************************************
*  Include Interfaces
****************************************************************************/

#include "../../../../common/include/_stddef.h"
#include "dsp_dat.h"



/****************************************************************************
*  HW-register configuration
*****************************************************************************/

typedef enum
{
    /* SCP-program "read/write" registers*/
    DSP_HWREG_CFG_PCM0,
    DSP_HWREG_CFG_CODEC_DATA,
    DSP_HWREG_CFG_ADPCM0,
    DSP_HWREG_CFG_ADPCM1,
    DSP_HWREG_CFG_CODEC2_DATA,

    /* SCP program "write-only" registers*/
    DSP_HWREG_CFG_FSK1RAW,
    DSP_HWREG_CFG_FSK1CD,
    DSP_HWREG_CFG_FSK1MARK,
    DSP_HWREG_CFG_CODEC_MIC_GAIN


} ENUM8(DspHwRegCfgEnumType);



/****************************************************************************
*  Switch Table configuration
*****************************************************************************/


typedef enum
{
    /* 00 */ DSP_CON_NO_CONNECTION,

    /* 01 */ DSP_CON_DEVICE_LU1__OFH,       /* LU1 device, offhook*/
    /* 02 */ DSP_CON_DEVICE_LU1__ONH,       /* LU1 device, onhook*/

    /* 03 */ DSP_CON_LU1_ADPCM0,           /* LU1 device <-> ADPCM0*/
    /* 04 */ DSP_CON_LU1_ADPCM0_ADPCM1,    /* LU1 device <-> APPCM0 <-> ADPCM1*/

    /* 05 */ DSP_CON_LU1_SPKPH__PCM0,      /* LU1 device <-> SPKPH device (spkphone using PCM0)*/
    /* 06 */ DSP_CON_LU1_SPKPH__CODEC2,    /* LU1 device <-> SPKPH device (spkphone using CODEC2)*/

    /* 20 */ DSP_CON_TEST_20=0x20,
    /* 21 */ DSP_CON_TEST_21=0x21,
    /* 22 */ DSP_CON_TEST_22=0x22

} ENUM8(DspConEnumType);



typedef enum
{
    DSP_DEVICE_ADPCM0      = BIT0,
    DSP_DEVICE_ADPCM1      = BIT1,
    DSP_DEVICE_ADPCM2      = BIT2,
    DSP_DEVICE_ADPCM3      = BIT3,

    DSP_DEVICE_LU1_A1_IN   = BIT4,
    DSP_DEVICE_LU1_B1_OUT  = BIT5,
    DSP_DEVICE_LU1_B2_IN   = BIT6,
    DSP_DEVICE_LU1_A2_OUT  = BIT7,

    DSP_DEVICE_SPKPH_IN    = BIT8,
    DSP_DEVICE_SPKPH_OUT   = BIT9,
    DSP_DEVICE_TAM_IN      = BIT10,
    DSP_DEVICE_TAM_OUT     = BIT11,

    DSP_DEVICE_NONE = 0xffff

} ENUM16(DspDeviceType);


typedef enum
{
    DSP_TONE_ATTRIB_LU1_B1 = BIT0,
    DSP_TONE_ATTRIB_LU1_A2 = BIT1

} ENUM16(MyDspToneAttribType);





typedef enum
{
    DSP_BLOCK_ID_NONE=0x00,

    DSP_BLOCK_ID_RESERVED

} ENUM8(DspBlockIdType);

#define DSP_CON_DEVICE_LU1__OFH  0
#define DSP_NO_MUTE_ATTRIB       0
#define DSP_MUTE_ATTRIB_ALL   1


typedef uint8 DspToneAttribType ;
typedef uint8 DspConIdType;
typedef uint8 DspMuteAttribType;


void   DspWrite(uint16 addr, uint16 dat);
void   DspWriteBlock(uint16 DestAddr, uint16* OrgAddr,  uint16 NumberOfWords);
void   DspSetBlock(uint16 DestAddr, uint16 FillPattern,  uint16 NumberOfWords);
uint16 DspRead(uint16 addr);

void   DspWriteSwPnt(uint16 block_addr, uint16 inp_addr, uint16 outp_addr);
uint16 DspReadSwPnt(uint16 block_addr, uint16 inp_addr);

void   DspDeactivateBlock(DspBlockIdType BlockId);
void   DspActivateBlock(DspBlockIdType BlockId);

void   DspCfgInit(void);

void   DspInitData(void);
void   DspInit(void);
void   DspInitDriver(void);

boolean DspConnect(DspConIdType connection,DspMuteAttribType Attrib);
boolean DspDisconnect(DspConIdType connection);


/****************************************************************************
*  old 424 interface
*****************************************************************************/

#define DSPDEVICE_ID(i) 0
#define BYTE uint8




typedef enum /* 1 byte */
{
    DEVICE_LINE     = 0
                      ,NUMBER_OF_DSP_DEVICES
    ,DEVICE_NONE=0xff

}  Enum_DspDeviceIdType;
typedef BYTE DspDeviceIdType;

typedef enum
{
    DSP_CODECIO_NOCHANGE,
    DSP_CODECIO_DIFF_OUTPUT,
    DSP_CODECIO_SINGLE_OUTPUT,
    DSP_CODECIO_DIFF_INPUT,
    DSP_CODECIO_MIC2_INPUT,
    DSP_CODECIO_CAP2_INPUT,
    DSP_CODECIO_NO_INPUT,
    DSP_CODECIO_DEFAULT

} DspCodecIoSelectTypeValues;
typedef uint8 DspCodecIoSelectType;



#define DM_CONFERENCE  DM_CONFERENCE_21
typedef enum
{
    DM_CLOSED=0
              ,DM_CONVERSATION
    ,DM_CONFERENCE_21
    ,DM_CONFERENCE_12
    ,DM_CONFERENCE_22
    ,DM_RECORDING
    ,DM_PLAYBACK
    ,DM_PLAY_BS_SPEAKER
    ,DM_PLAY_REC_BIDIREC
    ,DM_RECORDING_BIDIREC
    ,DM_PLAYBACK_BIDIREC
    ,DM_PLAYBACK_BIDIREC2
    ,DM_ONHOOK_CLIP
    ,DM_SPEAKER_TEST
    ,DM_MIC_TEST

} Enum_DspDeviceMode;
typedef BYTE DspDeviceMode;


typedef enum
{
    DSP_DC_LINETASK   = BIT0,    /* task control bit mask*/
    DSP_DC_FSKL1TASK  = BIT1,
    DSP_DC_CLIPTASK   = BIT2,
    DSP_DC_TADTASK    = BIT3,
    DSP_DC_RESERVED   = BIT4,
    DSP_DC_TADDRVTASK = BIT5,
    DSP_DC_INVALID_6  = BIT6,
    DSP_DC_INVALID_7  = BIT7

} Enum_DspDeviceCtrlType;
typedef BYTE DspDeviceCtrlType;


typedef enum
{
    SWA_HS_IN  = BIT0,   /* switch point with audio input from hs*/
    SWA_HS_OUT = BIT1,   /* switch point with audio output to hs*/
    SWA_B_IN   = BIT2,   /* switch point with audio input from b1/b2/b3*/
    SWA_B_OUT  = BIT3,   /* switch point with audio output to b1/b2/b3*/
    SWA_DTMF   = BIT4,   /* switch point where DTMF is to be generated*/
    SWA_MUTE   = BIT5,   /* not used , but could be used for muting*/
    /* specific switch points*/
    SWA_TONE   = BIT6    /* switch point where single tone is to be generated*/

} Enum_DspSwitchAttribType;
typedef BYTE DspSwitchAttribType;


uint8 DspSetCodecIo(DspCodecIoSelectType input, DspCodecIoSelectType output);


DspDeviceMode DspSetDeviceMode(DspDeviceIdType DeviceId,DspDeviceMode DeviceMode);
DspDeviceMode DspGetDeviceMode(DspDeviceIdType DeviceId);
void DspMuteDevice(DspDeviceIdType DeviceId,
                   DspDeviceCtrlType CtrlBitMask,
                   DspSwitchAttribType Attrib);
void DspUnmuteDevice(DspDeviceIdType DeviceId,
                     DspDeviceCtrlType CtrlBitMask,
                     DspSwitchAttribType Attrib);
void DspStartDtmfTone(DspDeviceIdType DeviceId,
                      BYTE DtmfTone,DspSwitchAttribType Attrib);

BOOLEAN DspStartSingleTone(DspDeviceIdType DeviceId, WORD freq, WORD ampl, DspSwitchAttribType Attrib);
void DspStopSingleTone(DspDeviceIdType DeviceId);


void DspStopDtmfTone(DspDeviceIdType DeviceId);
void DspEndDtmfMode(DspDeviceIdType DeviceId);
void DspInitialization(void);
void SetDSPNormalAddr(void);

/****************************************************************************
*  End Of File
*****************************************************************************/


#endif /* #end-ifndef __DSPCFG_H*/


