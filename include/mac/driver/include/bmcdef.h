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

#include "../../../common/include/rtxdef.h"
#include "../../../common/include/_stddef.h"

typedef struct
{
    WORD Command;
}
BmcInstructionType;

typedef BmcInstructionType BmcCtrlRamType[512];

#define SLOTPROGRAMSIZE_FP 8
#define SLOTPROGRAMSIZE_PP 2
#define NOOFBEARERS_PP 6

/*******************************************************************************
 * Block register bank 0x00                                                     *
 * Power control register                                                       *
 * 8 & 24 bits write cycle                                                      *
 *******************************************************************************/
typedef struct
{
unsigned int TX:
    1;            /* uint8  LSB*/
unsigned int RX:
    1;
unsigned int RegBank:
    5;
unsigned int RW:
    1;            /* uin8   MSB*/
unsigned int PLL_N_CNTR_reg:
    12;       /* uint16 LSB*/
unsigned int PLL_TST_mode_reg:
    4;      /* uint16 MSB*/
}
LMX4168_Power_Control_Reg_Type;

/*******************************************************************************
* Block register bank 0x01                                                     *
* Test control register                                                        *
* 8 bits write cycle                                                           *
*******************************************************************************/
typedef struct
{
bitfield NotUsed:
    16;
bitfield SC:
    1;
bitfield RE:
    1;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_Test_Control_Reg_Type;

/*******************************************************************************
* Block register bank 0x02                                                     *
* LNA_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_LNA_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_LNA_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_LNA_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_LNA_pd_03_Type;

/*******************************************************************************
* Block register bank 0x03                                                     *
* MIXER_pd                                                                     *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_MIXER_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_MIXER_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_MIXER_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_MIXER_pd_03_Type;

/*******************************************************************************
* Block register bank 0x04                                                     *
* DOUBLER_pd                                                                   *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DOUBLER_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DOUBLER_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DOUBLER_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DOUBLER_pd_03_Type;

/*******************************************************************************
* Block register bank 0x05                                                     *
* PA_pd                                                                        *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PA_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PA_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PA_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PA_pd_03_Type;

/*******************************************************************************
* Block register bank 0x06                                                     *
* IF_pd                                                                        *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_IF_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield ags12_alfa:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_IF_pd_01_Type;

typedef struct
{
bitfield agc12_TLlow_reg:
    8;
bitfield agc12_THhigh_reg:
    8;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_IF_pd_02_Type;

typedef struct
{
bitfield vga_offset_reg:
    6;
bitfield X:
    1;
bitfield Y:
    1;
bitfield NotUsed:
    8;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_IF_pd_03_Type;

/*******************************************************************************
* Block register bank 0x07                                                     *
* OSC_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_OSC_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield cnt_ro:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_OSC_pd_01_Type;

typedef struct
{
bitfield cnt_clk_calcaptest:
    9;
bitfield X:
    1;
bitfield Y:
    1;
bitfield NotUsed:
    5;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_OSC_pd_02_Type;

typedef struct
{
bitfield if_cal_cap_value:
    6;
bitfield NotUsed:
    10;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_OSC_pd_03_Type;

/*******************************************************************************
* Block register bank 0x08                                                     *
* ADC_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_ADC_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield Tgate_reg:
    4;
bitfield X:
    1;
bitfield NotUsed:
    1;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_ADC_pd_01_Type;

typedef struct
{
bitfield ADC_reg:
    10;
bitfield pd_inv:
    4;
bitfield NotUsed:
    2;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_ADC_pd_02_Type;

typedef struct
{
bitfield PAD_SE_NE_reg:
    8;
bitfield PAD_OE_N_reg:
    8;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_ADC_pd_03_Type;

/*******************************************************************************
* Block register bank 0x09                                                     *
* BIAS_pd                                                                      *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_BIAS_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield bias_trim_reg:
    4;
bitfield NotUsed:
    2;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_BIAS_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_BIAS_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_BIAS_pd_03_Type;

/*******************************************************************************
* Block register bank 0x0A                                                     *
* DAC_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DAC_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield X:
    1;
bitfield dac_tst_val_reg:
    5;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DAC_pd_01_Type;

typedef struct
{
bitfield Y:
    1;
bitfield THsig_reg:
    5;
bitfield rssi_val:
    5;
bitfield NotUsed:
    5;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DAC_pd_02_Type;

typedef struct
{
bitfield agc3_gain:
    4;
bitfield agc2_gain:
    4;
bitfield agc1_gain:
    4;
bitfield NotUsed:
    4;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DAC_pd_03_Type;

/*******************************************************************************
* Block register bank 0x0B                                                     *
* DEM_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DEM_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield agc3_alfa:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DEM_pd_01_Type;

typedef struct
{
bitfield slice_reg:
    7;
bitfield AGC_reg:
    3;
bitfield agc3_TLlow:
    5;
bitfield X:
    1;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DEM_pd_02_Type;

typedef struct
{
bitfield agc3_THhigh:
    5;
bitfield preamble_sym:
    2;
bitfield preamble_del:
    4;
bitfield Dem_reg:
    2;
bitfield Y:
    1;
bitfield NotUsed:
    2;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_DEM_pd_03_Type;

/*******************************************************************************
* Block register bank 0x0C                                                     *
* PLL_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield X:
    1;
bitfield PLL_R_CNTR_reg:
    5;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_pd_01_Type;

typedef struct
{
bitfield PLL_CNTR0_reg:
    2;
bitfield NC:
    1;
bitfield PLL_CNTR1_reg:
    4;
bitfield PLL_tstCP_reg:
    8;
bitfield Y:
    1;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_pd_03_Type;

/*******************************************************************************
* Block register bank 0x0D                                                     *
* VCO_pd                                                                       *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield VCO_reg:
    3;
bitfield VCO_test_cntr_reg:
    3;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_pd_01_Type;

typedef struct
{
bitfield VCO_icoreset_reg:
    4;
bitfield VCO_Ctune_reg:
    6;
bitfield NotUsed:
    6;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_pd_03_Type;

/*******************************************************************************
* Block register bank 0x0E                                                     *
* VCO_bias_pd                                                                  *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_bias_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield Vreg_reg:
    2;
bitfield NotUsed:
    4;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_bias_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_bias_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_bias_pd_03_Type;

/*******************************************************************************
* Block register bank 0x0F                                                     *
* VCO_reg_pd                                                                   *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_reg_pd_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_reg_pd_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_reg_pd_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_reg_pd_03_Type;

/*******************************************************************************
* Block register bank 0x10                                                     *
* VCO_active                                                                   *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_active_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_active_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_active_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_VCO_active_03_Type;

/*******************************************************************************
* Block register bank 0x11                                                     *
* RF_VCO_vftune                                                                *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_RF_VCO_vftune_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield vpwrset:
    2;
bitfield Vset:
    2;
bitfield vf_en:
    1;
bitfield NotUsed:
    1;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_RF_VCO_vftune_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_RF_VCO_vftune_02_Type;

typedef struct
{
bitfield rf_cal_cap:
    6;
bitfield NotUsed:
    10;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_RF_VCO_vftune_03_Type;

/*******************************************************************************
* Block register bank 0x12                                                     *
* PAD_7                                                                        *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_7_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_7_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_7_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_7_03_Type;

/*******************************************************************************
* Block register bank 0x13                                                     *
* PAD_6                                                                        *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_6_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_6_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_6_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_6_03_Type;

/*******************************************************************************
* Block register bank 0x14                                                     *
* PAD_5                                                                        *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_5_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_5_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_5_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_5_03_Type;

/*******************************************************************************
* Block register bank 0x15                                                     *
* PAD_4                                                                        *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_4_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_4_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_4_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PAD_4_03_Type;

/*******************************************************************************
* Block register bank 0x16                                                     *
* PLL_CNTR_reg                                                                 *
* 24 bits write cycle                                                          *
*******************************************************************************/
typedef struct
{
bitfield SetTimeValue:
    10;
bitfield RE:
    1;
bitfield TE:
    1;
bitfield EN:
    1;
bitfield RV:
    1;
bitfield TV:
    1;
bitfield NotUsed:
    1;
bitfield SubBank0:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_CNTR_reg_00_Type;

typedef struct
{
bitfield ResetTimeValue:
    10;
bitfield NotUsed:
    6;
bitfield SubBank1:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_CNTR_reg_01_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank2:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_CNTR_reg_02_Type;

typedef struct
{
bitfield NotUsed:
    16;
bitfield SubBank3:
    2;
bitfield RegBank:
    5;
bitfield RW:
    1;
}
LMX4168_PLL_CNTR_reg_03_Type;

typedef struct
{
    BYTE Reg[3];
}
LMX4168ByteRegType;


typedef struct
{
    LMX4168ByteRegType PowerControlReg;
    LMX4168ByteRegType TestControlReg;

    LMX4168ByteRegType LNA_pd_00;
    LMX4168ByteRegType LNA_pd_01;
    LMX4168ByteRegType LNA_pd_02;
    LMX4168ByteRegType LNA_pd_03;

    LMX4168ByteRegType MIXER_pd_00;
    LMX4168ByteRegType MIXER_pd_01;
    LMX4168ByteRegType MIXER_pd_02;
    LMX4168ByteRegType MIXER_pd_03;

    LMX4168ByteRegType DOUBLER_pd_00;
    LMX4168ByteRegType DOUBLER_pd_01;
    LMX4168ByteRegType DOUBLER_pd_02;
    LMX4168ByteRegType DOUBLER_pd_03;

    LMX4168ByteRegType PA_pd_00;
    LMX4168ByteRegType PA_pd_01;
    LMX4168ByteRegType PA_pd_02;
    LMX4168ByteRegType PA_pd_03;

    LMX4168ByteRegType IF_pd_00;
    LMX4168ByteRegType IF_pd_01;
    LMX4168ByteRegType IF_pd_02;
    LMX4168ByteRegType IF_pd_03;

    LMX4168ByteRegType OSC_pd_00;
    LMX4168ByteRegType OSC_pd_01;
    LMX4168ByteRegType OSC_pd_02;
    LMX4168ByteRegType OSC_pd_03;

    LMX4168ByteRegType ADC_pd_00;
    LMX4168ByteRegType ADC_pd_01;
    LMX4168ByteRegType ADC_pd_02;
    LMX4168ByteRegType ADC_pd_03;

    LMX4168ByteRegType BIAS_pd_00;
    LMX4168ByteRegType BIAS_pd_01;
    LMX4168ByteRegType BIAS_pd_02;
    LMX4168ByteRegType BIAS_pd_03;

    LMX4168ByteRegType DAC_pd_00;
    LMX4168ByteRegType DAC_pd_01;
    LMX4168ByteRegType DAC_pd_02;
    LMX4168ByteRegType DAC_pd_03;

    LMX4168ByteRegType DEM_pd_00;
    LMX4168ByteRegType DEM_pd_01;
    LMX4168ByteRegType DEM_pd_02;
    LMX4168ByteRegType DEM_pd_03;

    LMX4168ByteRegType PLL_pd_00;
    LMX4168ByteRegType PLL_pd_01;
    LMX4168ByteRegType PLL_pd_02;
    LMX4168ByteRegType PLL_pd_03;

    LMX4168ByteRegType VCO_pd_00;
    LMX4168ByteRegType VCO_pd_01;
    LMX4168ByteRegType VCO_pd_02;
    LMX4168ByteRegType VCO_pd_03;

    LMX4168ByteRegType VCO_bias_pd_00;
    LMX4168ByteRegType VCO_bias_pd_01;
    LMX4168ByteRegType VCO_bias_pd_02;
    LMX4168ByteRegType VCO_bias_pd_03;

    LMX4168ByteRegType VCO_reg_pd_00;
    LMX4168ByteRegType VCO_reg_pd_01;
    LMX4168ByteRegType VCO_reg_pd_02;
    LMX4168ByteRegType VCO_reg_pd_03;

    LMX4168ByteRegType VCO_active_00;
    LMX4168ByteRegType VCO_active_01;
    LMX4168ByteRegType VCO_active_02;
    LMX4168ByteRegType VCO_active_03;

    LMX4168ByteRegType RF_VCO_vftune_00;
    LMX4168ByteRegType RF_VCO_vftune_01;
    LMX4168ByteRegType RF_VCO_vftune_02;
    LMX4168ByteRegType RF_VCO_vftune_03;

    LMX4168ByteRegType PAD_7_00;
    LMX4168ByteRegType PAD_7_01;
    LMX4168ByteRegType PAD_7_02;
    LMX4168ByteRegType PAD_7_03;

    LMX4168ByteRegType PAD_6_00;
    LMX4168ByteRegType PAD_6_01;
    LMX4168ByteRegType PAD_6_02;
    LMX4168ByteRegType PAD_6_03;

    LMX4168ByteRegType PAD_5_00;
    LMX4168ByteRegType PAD_5_01;
    LMX4168ByteRegType PAD_5_02;
    LMX4168ByteRegType PAD_5_03;

    LMX4168ByteRegType PAD_4_00;
    LMX4168ByteRegType PAD_4_01;
    LMX4168ByteRegType PAD_4_02;
    LMX4168ByteRegType PAD_4_03;

    LMX4168ByteRegType PLL_CNTR_reg_00;
    LMX4168ByteRegType PLL_CNTR_reg_01;
    /*LMX4168ByteRegType PLL_CNTR_reg_02; // Not used - removed to reduce size below 256 bytes*/
    /*LMX4168ByteRegType PLL_CNTR_reg_03; // -*/
    BYTE Rreg;
    BYTE Flatch[3];
}
LMX4168RegType;
/*#endif*/

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
} PACKED _BmcControlType;

typedef struct
{
    BYTE Control;                 /* Control byte for mute funtion*/
    BYTE Attack;	              /* Attack time 10 mS. steps*/
    BYTE Decay;                   /* Decay time 10 mS. steps*/
}
MuteControlType;

typedef struct
{
    BYTE AdcResult;
    BYTE CRCresult;
    BYTE SlideErrors;
    BYTE ReceivePhase;
    BYTE Ones;
} PACKED RxStatusType;

typedef struct
{
    BYTE AnalogControl; /* All: C2 ; Gausian only: 7F */
    BYTE TestByte1;    /* xxx00000 */
    BYTE LrsMicGain;   /* LLLLMMMM */
    BYTE Vref;         /* xxxxxx00 */
    BYTE TestByte3;    /* xxxxx000 */
    BYTE TestByte4;    /* 00000000 */
} PACKED CodecControlType;

typedef struct
{
    BYTE Byte1,Byte2,Byte3;

} PACKED SyntRegType;

typedef struct
{
    BYTE Bit23_16;                /* size  1*/
    BYTE Bit15_8;                 /* size  1*/
    BYTE Bit7_0;                  /* size  1*/
} PACKED LMX24BitType;                 /* size  3*/

typedef struct
{
    LMX24BitType Register[8];     /* size  3*/
    BYTE NotUsed[32 - 8 * sizeof(LMX24BitType)];
} PACKED LMXSetupParameterType;          /* size 32*/

typedef struct
{
    BYTE R_divide;
    BYTE SyntMode[3];
} PACKED SyntRefModeType;

typedef struct
{
    SyntRegType TxFreq;
    RxStatusType TxStatus;
    BYTE        Head;
    BYTE        Tail[5];
    BYTE        Fill[2];
} PACKED PPBearerTxDataType;

typedef struct
{
    SyntRegType  RxFreq;
    RxStatusType RxStatus;
    BYTE         Head;
    BYTE         Tail[5];
    BYTE         Fill[2];
} PACKED PPBearerRxDataType;

typedef struct
{ /* Provision for signal-quality monitoring. Not used by BMC */
    BYTE   Quality;
    BYTE   Rssi;
    BYTE   Header;
    BYTE   Resv0;
    BYTE   Resv1;
} PACKED BearerStatusType;

typedef struct
{ /* Provision for signal-quality monitoring. Not used by BMC */
    BYTE   Byte1;
    BYTE   Byte2;
} PACKED RSSIMessType;

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
    BYTE             LMX4169FixedPreamble[3];    /* 36*/
    BYTE             LMX4169MeassPreamble[3];    /* 39*/
    BYTE             Fill_4[4];
    BYTE             EncryptionStatus[11];       /* 40*/
    BearerStatusType BearerStatus;
    RSSIMessType     RSSIMess[3];
    BYTE             Fill_5[0x20-16-3*sizeof(RSSIMessType)];
    PPBearerTxDataType BearerTxData[NOOFBEARERS_PP/2];/* 60*/
    PPBearerRxDataType BearerRxData[NOOFBEARERS_PP];
    BYTE             ScratchBfield[4];
    BYTE             SyncPattern[4];
    BYTE             AlternatingBits[8];         /* f8*/
} PACKED BmcDataPPBank0Type;

typedef struct
{
    BYTE Byte0;
    BYTE Byte1;
    BYTE SpeechBuffer0[80],Fillb0[2];
    BYTE SpeechBuffer1[80],Fillb1[2];
    BYTE SilentBuffer[80],Fillb2[2];
    BYTE ByteF8_FF[8];
} PACKED BmcDataPPBank1Type;

typedef struct
{
    PPBearerRxDataType BearerRxData[NOOFBEARERS_PP*2];
} PACKED BmcDataPPBank2Type;

typedef struct
{
    BYTE TempLMX[256];
} PACKED BmcDataPPBank3Type;

typedef struct
{
    BYTE Bank0[256];
}
BmcDataBank1Type;

typedef volatile struct
{
    BYTE Byte[1];
    BmcDataPPBank0Type Bank0;
    BmcDataPPBank1Type Bank1;
    BmcDataPPBank2Type Bank2;
    BmcDataPPBank3Type Bank3;
} PACKED PPBmcDataRamType;

extern BmcCtrlRamType BmcCtrlRam;

#endif
