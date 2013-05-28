#ifndef __DSP_DAT_H
#define __DSP_DAT_H

/****************************************************************************
*  Program/file: DSP_DAT.H
*
*  Copyright (C) by RTX TELECOM A/S, Denmark.
*  These computer program listings and specifications, are the property of
*  RTX TELECOM A/S, Denmark and shall not be reproduced or copied or used in
*  whole or in part without written permission from RTX TELECOM A/S, Denmark.
*
*  Programmer: RTX
*
*  MODULE:
*  CONTROLLING DOCUMENT:
*  SYSTEM DEPENDENCIES:
*
*  DESCRIPTION:
*
****************************************************************************/



/****************************************************************************
* PVCS Info
****************************************************************************/

/*
$Author:   on  $
$Date:   Jan 29 2004 10:43:10  $
$Revision:   1.1  $
$Modtime:   Jan 26 2004 09:34:18  $
*/


/****************************************************************************
* Macro Definitions
****************************************************************************/


#define DSP_MAX_SCP_CODE_SIZE 42

/****************************************************************************
* Types
****************************************************************************/


typedef enum
{
    DSP_DATAINIT_DATA,
    DSP_DATAINIT_FILL,
    DSP_DATAINIT_END

} ENUM8(DspDataInitType);


/****************************************************************************
* HW-REG Control Type 1
****************************************************************************/

#define DSP_WRTOREG_PTR_SIZE    (0x09+0x08)
#define DSP_REG_IN_PTR_SIZE     DSP_WRTOREG_PTR_SIZE

#define DSP_RDFROMREG_PTR_SIZE  0x09
#define DSP_REG_OUT_SIZE        DSP_RDFROMREG_PTR_SIZE


/****************************************************************************
* DSP-parameter RAM layout
****************************************************************************/

#define SIZE_OFF_DSP_RAM_FP 0x1A00

typedef struct
{




    /*uint16  AbsDSPprogram[0x17FF];*/
/*    uint16  AbsDSPprogram[0x140a];*/
    char  AbsDSPprogram[SIZE_OFF_DSP_RAM_FP];

}
DspParamFPRamType;

/****************************************************************************
* DSP Parameter-RAM
****************************************************************************/

extern DspParamFPRamType DspParamRam_FP;


extern const uint16 HwRegCtrl_InitTbl[];

extern const uint16 AbsDSPprogram[DSP_MAX_SCP_CODE_SIZE];


/****************************************************************************
* DSP RAM
****************************************************************************/




#define DSPRAM_HWREGCTRL                    0x0000   /* 0x0000*/
#define DSPRAM_HWREGCTRL_COPYP2P            0x0000   /* 0x0000*/
#define DSPRAM_HWREGCTRL_COPYP2B            0x0006   /* 0x0003*/
#define DSPRAM_HWREGCTRL_WRTOREG_PTR        0x000C   /* 0x0006*/
#define DSPRAM_HWREGCTRL_RDFROMREG_PTR      0x002E   /* 0x0017*/
#define DSPRAM_HWREGCTRL_REG_IN             0x0040   /* 0x0020*/
#define DSPRAM_HWREGCTRL_REG_OUT            0x0062   /* 0x0031*/



#define DSPRAM_SILENCE_OUT                  0x0074   /* 0x003A*/



#define DSPRAM_SCRATCH_IN                   0x0076   /* 0x003B*/


/****************************************************************************
* DSP HW-REG control (Type 1)
****************************************************************************/




#define GET_DSPRAM_HWREG_IN(reg)    (DSPRAM_HWREGCTRL_REG_IN+2*reg)
#define GET_DSPRAM_HWREG_OUT(reg)   (DSPRAM_HWREGCTRL_REG_OUT+2*reg)


#define DSPRAM_HWREG  DSPRAM_HWREGCTRL_COPYP2P

#define DSPRAM_HWREG_CODEC1             DSPRAM_HWREG
#define DSPRAM_HWREG_CODEC1_IN          GET_DSPRAM_HWREG_IN(DSP_HWREG_CFG_CODEC_DATA)
#define DSPRAM_HWREG_CODEC1_OUT         GET_DSPRAM_HWREG_OUT(DSP_HWREG_CFG_CODEC_DATA)

#define DSPRAM_HWREG_ADPCM0             DSPRAM_HWREG
#define DSPRAM_HWREG_ADPCM0_IN          GET_DSPRAM_HWREG_IN(DSP_HWREG_CFG_ADPCM0)
#define DSPRAM_HWREG_ADPCM0_OUT         GET_DSPRAM_HWREG_OUT(DSP_HWREG_CFG_ADPCM0)
#define DSPRAM_HWREG_ADPCM1             DSPRAM_HWREG
#define DSPRAM_HWREG_ADPCM1_IN          GET_DSPRAM_HWREG_IN(DSP_HWREG_CFG_ADPCM1)
#define DSPRAM_HWREG_ADPCM1_OUT         GET_DSPRAM_HWREG_OUT(DSP_HWREG_CFG_ADPCM1)


typedef uint16 DspHwRegCfgTblType;


/****************************************************************************
* END OF FILE
****************************************************************************/
#endif

