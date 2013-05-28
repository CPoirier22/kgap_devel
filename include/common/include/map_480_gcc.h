#ifndef _MAP480GCC_INCLUDED
#define _MAP480GCC_INCLUDED

#include "rtxdef.h"
#include "_stddef.h"

#define P1_DIR_REG               *((volatile unsigned short*)0xFF4846)
#define P1_MODE_REG              *((volatile unsigned short*)0xFF4848)
#define P2_DIR_REG               *((volatile unsigned short*)0xFF4856)
#define P2_MODE_REG              *((volatile unsigned short*)0xFF4858)
#define P2_SET_DATA_REG          *((volatile unsigned short*)0xFF4852)
#define P2_RESET_DATA_REG        *((volatile unsigned short*)0xFF4854)
// HM Added - start
#define P0_DATA_REG              *((volatile unsigned short*)0xFF4830)
#define P0_SET_DATA_REG          *((volatile unsigned short*)0xFF4832)
#define P0_RESET_DATA_REG        *((volatile unsigned short*)0xFF4834)
#define P1_DATA_REG              *((volatile unsigned short*)0xFF4840)
#define P1_SET_DATA_REG          *((volatile unsigned short*)0xFF4842)
#define P1_RESET_DATA_REG        *((volatile unsigned short*)0xFF4844)
#define P2_DATA_REG              *((volatile unsigned short*)0xFF4850)
#define P3_DATA_REG              *((volatile unsigned short*)0xFF4860)
#define P3_SET_DATA_REG          *((volatile unsigned short*)0xFF4862)
#define P3_RESET_DATA_REG        *((volatile unsigned short*)0xFF4864)
#define P3_DIR_REG               *((volatile unsigned short*)0xFF4866)
#define P3_MODE_REG              *((volatile unsigned short*)0xFF4868)
#define INT0_PRIORITY_REG        *((volatile unsigned short*)0xFF5404)
#define INT3_PRIORITY_REG        *((volatile unsigned short*)0xFF540A)
#define KEY_GP_INT_REG           *((volatile unsigned short*)0xFF49B0)
#define KEY_BOARD_INT_REG        *((volatile unsigned short*)0xFF49B2)
#define KEY_DEBOUNCE_REG         *((volatile unsigned short*)0xFF49B4)
#define KEY_STATUS_REG           *((volatile unsigned short*)0xFF49B6)
#define ADC_CTRL_REG             *((volatile unsigned short*)0xFF4960)
#define ADC_CTRL1_REG            *((volatile unsigned short*)0xFF4962)
#define ADC_CLEAR_INT_REG        *((volatile unsigned short*)0xFF4964)
#define ADC0_REG                 *((volatile unsigned short*)0xFF4966)
#define CLK_CODEC_DIV_REG        *((volatile unsigned short*)0xFF4002)
#define CLK_PER_DIV_REG          *((volatile unsigned short*)0xFF400C)
#define MEM_CONFIG_REG           *((volatile unsigned short*)0xFF5006)               
#define SPI_CTRL_REG             *((volatile unsigned short*)0xFF4940)
#define SPI_RX_TX_REG0           *((volatile unsigned short*)0xFF4942)
#define SPI_RX_TX_REG1           *((volatile unsigned short*)0xFF4944)
#define SPI_CLEAR_INT_REG        *((volatile unsigned short*)0xFF4946)
#define CLK_PER10_DIV_REG        *((volatile unsigned short*)0xFF400E)
#define DSP_INT_REG        		 *((volatile unsigned short*)0x1027FD8)
#define DSP_CTRL_REG             *((volatile unsigned short*)0x1027FD0)
#define DSP_INT_REG              *((volatile unsigned short*)0x1027FD8)
#define DSP_INT_MASK_REG         *((volatile unsigned short*)0x1027FDA)
#define DSP_INT_PRIO1_REG        *((volatile unsigned short*)0x1027FDC)
#define DSP_INT_PRIO2_REG        *((volatile unsigned short*)0x1027FDE)
#define DSP_MAIN_SYNC0_REG       *((volatile unsigned short*)0x1027F80)
#define DSP_MAIN_SYNC1_REG       *((volatile unsigned short*)0x1027F82)
#define DSP_OVERFLOW_REG         *((volatile unsigned short*)0x1027FE0)
#define DSP_PCM_CTRL_REG         *((volatile unsigned short*)0x1027FB6)






// __no_init volatile uint16               @ 0x1027FD8; // DSP to CR16Cplus interrupt vector
#define DSP_INT_REG_ADDR 0x1027FD8 // DSP to CR16Cplus interrupt vector

// HM Added - end
#define RESET_INT_PENDING_REG    *((volatile unsigned short*)0xFF5402)
#define WATCHDOG_REG             *((volatile unsigned short*)0xFF4C00)
#define ACCESS2_CTRL_REG         *((volatile unsigned short*)0xFF4932)
#define ACCESS2_CLEAR_INT_REG    *((volatile unsigned short*)0xFF4934)
#define ACCESS2_IN_OUT_REG       *((volatile unsigned short*)0xFF4930)
#define P0_MODE_REG              *((volatile unsigned short*)0xFF4838)
#define CP_CTRL_REG              *((volatile unsigned short*)0xFF481C)
#define P0_DIR_REG               *((volatile unsigned short*)0xFF4836)
#define PAD_CTRL_REG             *((volatile unsigned short*)0xFF481E)
#define CLK_FREQ_TRIM_REG        *((volatile unsigned short*)0xFF400A)
#define RF_RSSI_REG              *((volatile unsigned short*)0xFF7048)
#define BANDGAP_REG              *((volatile unsigned short*)0xFF4810)
#define CLK_AMBA_REG             *((volatile unsigned short*)0xFF4000)
#define BAT_CTRL_REG             *((volatile unsigned short*)0xFF4812)
#define BAT_CTRL2_REG            *((volatile unsigned short*)0xFF4814)
#define BAT_STATUS_REG           *((volatile unsigned short*)0xFF4816)
#define CLK_XTAL_CTRL_REG        *((volatile unsigned short*)0xFF4018)
#define CLK_PLL_DIV_REG          *((volatile unsigned short*)0xFF4012)
#define CLK_PLL_CTRL_REG         *((volatile unsigned short*)0xFF4010)
#define SET_FREEZE_REG           *((volatile unsigned short*)0xFF5000)
#define CLK_AUX_REG              *((volatile unsigned short*)0xFF401A)
#define DIP_CTRL_REG             *((volatile unsigned short*)0xFF6006) 
#define INT1_PRIORITY_REG        *((volatile unsigned short*)0xFF5406)
#define DIP_STATUS_REG           *((volatile unsigned short*)0xFF6004)
#define SET_INT_PENDING_REG      *((volatile unsigned short*)0xFF5400)
#define DEBUG_REG                *((volatile unsigned short*)0xFF5004)
#define DIP_PC_REG               *((volatile unsigned short*)0xFF6002)
#define DIP_STATUS1_REG          *((volatile unsigned short*)0xFF6008)
#define RF_RFCAL_CTRL_REG        *((volatile unsigned short*)0xFF7040)
#define RF_PLL_CTRL2_REG         *((volatile unsigned short*)0xFF7052)
#define RF_PORT_RSSI_SI_REG      *((volatile unsigned short*)0xFF700A)
#define RF_TX_SI_REG             *((volatile unsigned short*)0xFF700C)
#define RF_RX_SI_REG             *((volatile unsigned short*)0xFF700E)
#define RF_PORT1_DCF_REG         *((volatile unsigned short*)0xFF7010)
#define RF_PORT3_DCF_REG         *((volatile unsigned short*)0xFF7014)
#define RF_PLLCLOSED_DCF_REG     *((volatile unsigned short*)0xFF7018)
#define RF_ADC_DCF_REG           *((volatile unsigned short*)0xFF7022)
#define RF_IF_DCF_REG            *((volatile unsigned short*)0xFF7024)
#define RF_LNAMIX_DCF_REG        *((volatile unsigned short*)0xFF7026)
#define RF_PADR_DCF_REG          *((volatile unsigned short*)0xFF7028)
#define RF_DEM_CTRL_REG          *((volatile unsigned short*)0xFF7044)
#define RF_PLL_CTRL3_REG         *((volatile unsigned short*)0xFF7054)
#define RF_SLICER_REG            *((volatile unsigned short*)0xFF7058)
#define RF_SYNTH_CTRL1_REG       *((volatile unsigned short*)0xFF7080)
#define RF_SYNTH_CTRL2_REG       *((volatile unsigned short*)0xFF7082)
#define RF_AGC_REG               *((volatile unsigned short*)0xFF7084)
#define RF_REF_OSC_REG           *((volatile unsigned short*)0xFF7094)
#define RF_ADC_CTRL_REG          *((volatile unsigned short*)0xFF7096)
#define RF_RFIO_CTRL_REG         *((volatile unsigned short*)0xFF7098)
#define RF_BIAS_CTRL_REG         *((volatile unsigned short*)0xFF709A)
#define RF_PLL_CTRL5_REG         *((volatile unsigned short*)0xFF70AC)
#define RF_PLL_CTRL6_REG         *((volatile unsigned short*)0xFF70AE)
#define UART_RX_TX_REG           *((volatile unsigned short*)0xFF4902)
#define UART_CTRL_REG            *((volatile unsigned short*)0xFF4900)
#define UART_CLEAR_TX_INT_REG    *((volatile unsigned short*)0xFF4904)
#define INT2_PRIORITY_REG        *((volatile unsigned short*)0xFF5408)
#define INT0_PRIORITY_REG        *((volatile unsigned short*)0xFF5404)
#define UART_CLEAR_RX_INT_REG    *((volatile unsigned short*)0xFF4906)
#define CODEC_TONE_REG           *((volatile unsigned short*)0xFF5806)
#define CODEC_VREF_REG           *((volatile unsigned short*)0xFF5804)
#define CODEC_MIC_REG            *((volatile unsigned short*)0xFF5800)
#define CODEC_ADDA_REG           *((volatile unsigned short*)0xFF5808)
#define CODEC_LSR_REG            *((volatile unsigned short*)0xFF5802)
#define CLASSD_CTRL_REG          *((volatile unsigned short*)0xFF5C00)
#define CLASSD_NR_REG            *((volatile unsigned short*)0xFF5C08)
#define CLASSD_CLEAR_INT_REG     *((volatile unsigned short*)0xFF5C02)
#define CLK_CODEC_REG            *((volatile unsigned short*)0xFF4004)
#define CLK_DSP_REG              *((volatile unsigned short*)0xFF4006)
#define CHIP_REVISION_REG        *((volatile unsigned char*)0xFFFBFC)
#define CHIP_TEST1_REG           *((volatile unsigned char*)0xFFFBFD)

#define TIMER_CTRL_REG           *((volatile unsigned char*)0xFF4970)
#define RESET_FREEZE_REG         *((volatile unsigned char*)0xFF5002)



#define CLEAR_PENDING_ACCESS_INTERRUPT     RESET_INT_PENDING_REG = CLR_ACCESS_INT_PENDING
#define CLEAR_PENDING_CLK100_INTERRUPT     RESET_INT_PENDING_REG = CLR_CLK100_INT_PENDING
#define CLEAR_PENDING_CT_INTERRUPT         RESET_INT_PENDING_REG = CLR_CT_INT_PENDING
#define CLEAR_PENDING_DIP_INTERRUPT        RESET_INT_PENDING_REG = CLR_DIP_INT_PENDING
#define CLEAR_PENDING_DSP_INTERRUPT        RESET_INT_PENDING_REG = CLR_DSP_INT_PENDING
#define CLEAR_PENDING_KEYB_INTERRUPT       RESET_INT_PENDING_REG = CLR_KEYB_INT_PENDING
#define CLEAR_PENDING_P10_INTERRUPT        RESET_INT_PENDING_REG = CLR_P10_INT_PENDING
#define CLEAR_PENDING_SPI_INTERRUPT        RESET_INT_PENDING_REG = CLR_SPI_INT_PENDING
#define CLEAR_PENDING_TIMER0_INTERRUPT     RESET_INT_PENDING_REG = CLR_TIM0_INT_PENDING
#define CLEAR_PENDING_TIMER1_INTERRUPT     RESET_INT_PENDING_REG = CLR_TIM1_INT_PENDING
#define CLEAR_PENDING_UART_RI_INTERRUPT    RESET_INT_PENDING_REG = CLR_UART_RX_INT_PENDING
#define CLEAR_PENDING_UART_RX_INTERRUPT    RESET_INT_PENDING_REG = CLR_UART_RX_INT_PENDING
#define CLEAR_PENDING_UART_TI_INTERRUPT    RESET_INT_PENDING_REG = CLR_UART_TI_INT_PENDING

#define CLK_AMBA_REG_ADDR                            0xFF4000
#define DIP_CTRL_REG_ADDR                            0xFF6006
#define DIP_STATUS_REG_ADDR                          0xFF6004
#define RF_PLL_CTRL2_REG_ADDR                        0xFF7052
#define RF_PLL_CTRL4_REG_ADDR                        0xFF7056
#define RF_BURST_MODE_SHADOW2_REG_ADDR               0xFF7072
#define DSP_MAIN_SYNC0_REG_ADDR                      0x1027F80
#define DSP_MAIN_SYNC1_REG_ADDR                      0x1027F82
#define DSP_MAIN_CTRL_REG_ADDR                       0x1027FBC
#define DSP_MAIN_CNT_REG_ADDR                        0x1027F84
#define DSP_PC_START_REG_ADDR                        0x1027FD4
#define DSP_INT_MASK_REG_ADDR                        0x1027FDA
#define DSP_RAM_IN0_REG_ADDR                         0x1027F9A
#define DSP_CTRL_REG_ADDR                            0x1027FD0
#define DSP_INT_PRIO1_REG_ADDR                       0x1027FDC
#define DSP_PCM_CTRL_REG_ADDR                        0x1027FB6
#define DSP_PCM_IN0_REG_ADDR                         0x1027FAE
#define DSP_PCM_IN1_REG_ADDR                         0x1027FB0 
#define DSP_PCM_IN2_REG_ADDR                         0x1027FB2 
#define DSP_PCM_IN3_REG_ADDR                         0x1027FB4 
#define DSP_PC_START_REG_ADDR                        0x1027FD4
#define DSP_INT_MASK_REG_ADDR                        0x1027FDA
#define DSP_INT_PRIO2_REG_ADDR                       0x1027FDE
#define DSP_IRQ_START_REG_ADDR                       0x1027FD6
#define DSP_INT_REG_ADDR                             0x1027FD8
#define INT0_PRIORITY_REG_ADDR 0xFF5404
#define RESET_INT_PENDING_REG_ADDR   0xFF5402
#define CLK_PLL_CTRL_REG_ADDR                       (0xFF4010)  /* PLL1 control register */
#define CLK_CODEC_DIV_REG_ADDR 0xFF4002
#define MEM_CONFIG_REG_ADDR 0xFF5006
#define CLK_PER_DIV_REG_ADDR 0xFF400C
#define CLK_PLL_DIV_REG_ADDR 0xFF4012
#define CLK_CODEC_REG_ADDR 0xFF4004
#define CODEC_VREF_REG_ADDR 0xFF5804
#define CODEC_ADDA_REG_ADDR 0xFF5808
#define CODEC_LSR_REG_ADDR 0xFF5802
#define CODEC_MIC_REG_ADDR 0xFF5800
#define CLK_DSP_REG_ADDR 0xFF4006

#define CLR_ACCESS_INT_PENDING             0x0001
#define CLR_CLK100_INT_PENDING             0x0200
#define CLR_CT_INT_PENDING                 0x0008
#define CLR_DIP_INT_PENDING                0x0400
#define CLR_DSP_INT_PENDING                0x2000
#define CLR_KEYB_INT_PENDING               0x0002
#define CLR_P10_INT_PENDING                0x0004
#define CLR_SPI_INT_PENDING                0x0040
#define CLR_TIM0_INT_PENDING               0x0080
#define CLR_TIM1_INT_PENDING               0x0100
#define CLR_UART_RX_INT_PENDING            0x0010
#define CLR_UART_TI_INT_PENDING            0x0020

#define UART_RI_INT_PEND                   (0x0010)
#define UART_TI_INT_PEND                   (0x0020)
#define CLK100_INT_PEND                    (0x0200)
#define SCL_VAL                            (0x0004)
#define SDA_VAL                            (0x0008)
#define ACKn                               (0x0002)
#define MCRAM1_EN                          (0x0080)
#define SRAM1_EN                           (0x0020)
#define REG_ON                             (0x0001)
#define LDORF_LEVEL                        (0x000C)
#define XTAL_DIV                           (0x0002)
#define PLL_CLK_SEL                        (0x0008)
#define FRZ_WDOG                           (0x0008)
#define BXTAL_EN                           (0x0018)
#define CLK100_INT_PRIO                    (0x0070)
#define CLK100_POS                         (0x0004)
#define SW_RESET                           (0x0080)
#define URST                               (0x0080)
#define P2_7_MODE                          (0x8000)
#define RFCAL_MODE                         (0x0018)
#define DIP_INT_VEC                        (0x000F)
#define MODCAL_PERIOD                      (0x00FF)
#define KMOD_ALPHA                         (0xE000)
#define MODINDEX                           (0x3F00)
#define SHADOW_EN                          (0x0010)
#define CN_SHW                             (0x00FF)
#define RX_ASSERT                          (0x0008)
#define TX_ASSERT                          (0x0004)
#define GAUSS_GAIN                         (0x00FF)
#define UART_TEN                           (0x0002)
#define UART_TI                            (0x0020)
#define P0_0_MODE                          (0x0001)
#define BAUDRATE                           (0x001C)
#define UART_REN                           (0x0001)
#define UART_MODE                          (0x0080)
#define UART_TI_INT_PRIO                   (0x0070)
#define UART_RI_INT_PRIO                   (0x0007)
#define RF_BB_MODE                         (0x0300)
#define CID_PR_DIS                         (0x0002)
#define VREF_INIT                          (0x0010)
#define MICH_ON                            (0x0800)
#define DA_DITH_OFF                        (0x0040)
#define AD_DITH_OFF                        (0x0080)
#define LSRP_PD                            (0x0004)
#define LSRN_PD                            (0x0020)
#define LSRATT                             (0x01C0)
#define CLASSD_PD                          (0x0001)
#define CLASSD_MOPEN                       (0x4000)
#define CLASSD_POPEN                       (0x8000)
#define DSP_CLK_EN                         (0x0008)
#define RAMIN0_SYNC                        (0x0003)
#define RAMOUT0_SYNC                       (0x0300)
#define DSP_SYNC0                          (0x0003)
#define DSP_SYNC1                          (0x000C)
#define DSP_SYNC2                          (0x0030)
#define AD_SYNC                            (0x00C0)
#define DA_CLASSD_SYNC                     (0x0300)
#define DA_LSR_SYNC                        (0x0C00)
#define ADC_SYNC                           (0x3000)
#define PCM_SYNC                           (0xC000)
#define DSP_MAIN_REL                       (0xFF00)
#define DSP_MAIN_CTRL                      (0x0300)
#define DA_PD                              (0x0001)
#define AD_PD                              (0x0002)
#define MIC_PD                             (0x0004)
#define VREF_PD                            (0x0001)
#define VREF_FILT_PD                       (0x0002)
#define VREF_FILT_CADJ                     (0x80000000)
#define VREF_INIT                          (0x0010)
#define AMP1V5_PD                          (0x0020)
#define VREF_BG_PD                         (0x0040)
#define BIAS_PD                            (0x0080)
#define AGND_LSR_PD                        (0x0100)
#define REFINT_PD                          (0x0200)
#define LDO1_ON                            (0x0002)

#define DSP_INT_PRIO                       (0x0070)

#define ACCESS_INT_PEND                    (0x0001)
#define KEYB_INT_PEND                      (0x0002)
#define RESERVED_INT_PEND                  (0x0004)
#define CT_CLASSD_INT_PEND                 (0x0008)
#define UART_RI_INT_PEND                   (0x0010)
#define UART_TI_INT_PEND                   (0x0020)
#define SPI_INT_PEND                       (0x0040)
#define TIM0_INT_PEND                      (0x0080)
#define TIM1_INT_PEND                      (0x0100)
#define CLK100_INT_PEND                    (0x0200)
#define DIP_INT_PEND                       (0x0400)
#define AD_INT_PEND                        (0x0800)
#define DSP_INT_PEND                       (0x2000)

#define PCM_EN                             (0x0001)
#define PCM_MASTER                         (0x0002)
#define DSP_PCM_SYNC                       (0x0004)
#define PCM_FSC0LEN                        (0x0018)
#define PCM_FSC0DEL                        (0x0020)
#define PCM_PPOD                           (0x0040)
#define PCM_CLKINV                         (0x0080)

#define CLEAR_UART_TI_FLAG UART_CLEAR_TX_INT_REG = 0
#define CLEAR_UART_RI_FLAG UART_CLEAR_RX_INT_REG = 0

extern signed char DECT_Channel_offset;



/*====================================================*/
struct __ACCESS1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_EN_ACCESS_BUS                      : 1;
    WORD BITFLD_ACKn                               : 1;
    WORD BITFLD_SCL_VAL                            : 1;
    WORD BITFLD_SDA_VAL                            : 1;
    WORD BITFLD_ACCESSx_INT                        : 1;
    WORD BITFLD_EN_ACCESS_INT                      : 1;
    WORD BITFLD_SCL_OD                             : 1;
    WORD BITFLD_SDA_OD                             : 1;
    WORD BITFLD_SCK_NUM                            : 1;
    WORD BITFLD_SCK_SEL                            : 2;
};

#define EN_ACCESS_BUS                      (0x0001)
#define ACKn                               (0x0002)
#define SCL_VAL                            (0x0004)
#define SDA_VAL                            (0x0008)
#define ACCESSx_INT                        (0x0010)
#define EN_ACCESS_INT                      (0x0020)
#define SCL_OD                             (0x0040)
#define SDA_OD                             (0x0080)
#define SCK_NUM                            (0x0100)
#define SCK_SEL                            (0x0600)


/*====================================================*/
struct __ACCESS2_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_EN_ACCESS_BUS                      : 1;
    WORD BITFLD_ACKn                               : 1;
    WORD BITFLD_SCL_VAL                            : 1;
    WORD BITFLD_SDA_VAL                            : 1;
    WORD BITFLD_ACCESSx_INT                        : 1;
    WORD BITFLD_EN_ACCESS_INT                      : 1;
    WORD BITFLD_SCL_OD                             : 1;
    WORD BITFLD_SDA_OD                             : 1;
    WORD BITFLD_SCK_NUM                            : 1;
    WORD BITFLD_SCK_SEL                            : 2;
};

#define EN_ACCESS_BUS                      (0x0001)
#define ACKn                               (0x0002)
#define SCL_VAL                            (0x0004)
#define SDA_VAL                            (0x0008)
#define ACCESSx_INT                        (0x0010)
#define EN_ACCESS_INT                      (0x0020)
#define SCL_OD                             (0x0040)
#define SDA_OD                             (0x0080)
#define SCK_NUM                            (0x0100)
#define SCK_SEL                            (0x0600)


/*====================================================*/
struct __ADC_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_ADC_START                          : 1;
    WORD BITFLD_ADC_AUTO                           : 1;
    WORD BITFLD_ADC_ALT                            : 1;
    WORD BITFLD_ADC_IN_3_0                         : 4;
    WORD BITFLD_ADC_TEST                           : 4;
    WORD BITFLD_ADC_INT                            : 1;
    WORD BITFLD_ADC_MINT                           : 1;
    WORD BITFLD_ADC0_PR_DIS                        : 1;
    WORD BITFLD_ADC1_PR_DIS                        : 1;
    WORD BITFLD_ADC2_PR_DIS                        : 1;
};

#define ADC_START                          (0x0001)
#define ADC_AUTO                           (0x0002)
#define ADC_ALT                            (0x0004)
#define ADC_IN_3_0                         (0x0078)
#define ADC_TEST                           (0x0780)
#define ADC_INT                            (0x0800)
#define ADC_MINT                           (0x1000)
#define ADC0_PR_DIS                        (0x2000)
#define ADC1_PR_DIS                        (0x4000)
#define ADC2_PR_DIS                        (0x8000)


/*====================================================*/
struct __ADC_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_ADC_IN_3_0_1                       : 4;
};

#define ADC_IN_3_0_1                       (0x000F)


/*====================================================*/
struct __ADC0_REG
/*====================================================*/
{
    WORD BITFLD_ADC0_VAL                           : 10;
};

#define ADC0_VAL                           (0x03FF)


/*====================================================*/
struct __ADC1_REG
/*====================================================*/
{
    WORD BITFLD_ADC1_VAL                           : 10;
};

#define ADC1_VAL                           (0x03FF)


/*====================================================*/
struct __BANDGAP_REG
/*====================================================*/
{
    WORD BITFLD_BANDGAP_VI                         : 4;
    WORD BITFLD_BANDGAP_VIT                        : 2;
    WORD BITFLD_BANDGAP_I                          : 3;
};

#define BANDGAP_VI                         (0x000F)
#define BANDGAP_VIT                        (0x0030)
#define BANDGAP_I                          (0x01C0)


/*====================================================*/
struct __BAT_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_REG_ON                             : 1;
    WORD BITFLD_LDORF_ON                           : 1;
    WORD BITFLD_LDORF_LEVEL                        : 2;
};

#define REG_ON                             (0x0001)
#define LDORF_ON                           (0x0002)
#define LDORF_LEVEL                        (0x000C)


/*====================================================*/
struct __BAT_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_CHARGE_LEVEL                       : 5;
    WORD BITFLD_CHARGE_ON                          : 1;
    WORD BITFLD_NTC_DISABLE                        : 1;
    WORD                                           : 1;
    WORD BITFLD_CHARGE_CUR                         : 3;
    WORD BITFLD_SOC_ON                             : 1;
    WORD BITFLD_SOC_CAL                            : 1;
    WORD BITFLD_SOC_TEST1                          : 1;
    WORD BITFLD_SOC_TEST2                          : 1;
};

#define CHARGE_LEVEL                       (0x001F)
#define CHARGE_ON                          (0x0020)
#define NTC_DISABLE                        (0x0040)
#define CHARGE_CUR                         (0x0700)
#define SOC_ON                             (0x0800)
#define SOC_CAL                            (0x1000)
#define SOC_TEST1                          (0x2000)
#define SOC_TEST2                          (0x4000)


/*====================================================*/
struct __BAT_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_VBAT3_STS                          : 1;
    WORD BITFLD_PON_STS                            : 1;
    WORD BITFLD_CHARGE_STS                         : 1;
    WORD BITFLD_CHARGE_I_LIMIT                     : 1;
};

#define VBAT3_STS                          (0x0001)
#define PON_STS                            (0x0002)
#define CHARGE_STS                         (0x0004)
#define CHARGE_I_LIMIT                     (0x0008)


/*====================================================*/
struct __BMC_CTRL_REG
/*====================================================*/
{
    WORD                                           : 8;
    WORD BITFLD_SIO_PD                             : 1;
    WORD                                           : 4;
    WORD BITFLD_BCNT_INH                           : 1;
};

#define SIO_PD                             (0x0100)
#define BCNT_INH                           (0x2000)


/*====================================================*/
struct __BMC_CTRL2_REG
/*====================================================*/
{
    WORD                                           : 3;
    WORD BITFLD_RCV_CTL                            : 5;
    WORD BITFLD_RCK_SEL                            : 1;
};

#define RCV_CTL                            (0x00F8)
#define RCK_SEL                            (0x0100)


/*====================================================*/
struct __CHIP_REVISION_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_REVISION_ID                        : 4;
};

#define REVISION_ID                        (0x00F0)


/*====================================================*/
struct __CLASSD_BUZZER_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_BUZ_GAIN                    : 4;
    WORD BITFLD_CLASSD_BUZ_MODE                    : 1;
};

#define CLASSD_BUZ_GAIN                    (0x000F)
#define CLASSD_BUZ_MODE                    (0x0010)


/*====================================================*/
struct __CLASSD_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_PD                          : 1;
    WORD BITFLD_CLASSD_PROT                        : 1;
    WORD BITFLD_CLASSD_VOUT                        : 2;
    WORD BITFLD_CLASSD_CLIP                        : 3;
    WORD BITFLD_CLASSD_INT_BIT                     : 1;
    WORD BITFLD_CLASSD_DITH_D                      : 2;
    WORD BITFLD_CLASSD_DITH_A                      : 2;
    WORD BITFLD_CLASSD_MODE                        : 1;
    WORD BITFLD_CLASSD_MINT                        : 1;
    WORD BITFLD_CLASSD_MOPEN                       : 1;
    WORD BITFLD_CLASSD_POPEN                       : 1;
};

#define CLASSD_PD                          (0x0001)
#define CLASSD_PROT                        (0x0002)
#define CLASSD_VOUT                        (0x000C)
#define CLASSD_CLIP                        (0x0070)
#define CLASSD_INT_BIT                     (0x0080)
#define CLASSD_DITH_D                      (0x0300)
#define CLASSD_DITH_A                      (0x0C00)
#define CLASSD_MODE                        (0x1000)
#define CLASSD_MINT                        (0x2000)
#define CLASSD_MOPEN                       (0x4000)
#define CLASSD_POPEN                       (0x8000)


/*====================================================*/
struct __CLASSD_TEST_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_SWITCH                      : 1;
    WORD BITFLD_CLASSD_RST_D                       : 1;
    WORD BITFLD_CLASSD_RST_A                       : 1;
    WORD BITFLD_CLASSD_FORCE                       : 1;
    WORD BITFLD_CLASSD_DIG_MUTE                    : 1;
    WORD BITFLD_CLASSD_ANA_TEST                    : 3;
};

#define CLASSD_SWITCH                      (0x0001)
#define CLASSD_RST_D                       (0x0002)
#define CLASSD_RST_A                       (0x0004)
#define CLASSD_FORCE                       (0x0008)
#define CLASSD_DIG_MUTE                    (0x0010)
#define CLASSD_ANA_TEST                    (0x00E0)


/*====================================================*/
struct __CLASSD_NR_REG
/*====================================================*/
{
    WORD BITFLD_CLASSD_NR_ACTIVE                   : 1;
    WORD BITFLD_CLASSD_NR_LVL                      : 3;
    WORD BITFLD_CLASSD_NR_TON                      : 4;
    WORD BITFLD_CLASSD_NR_HYST                     : 2;
    WORD BITFLD_CLASSD_NR_ZERO                     : 2;
};

#define CLASSD_NR_ACTIVE                   (0x0001)
#define CLASSD_NR_LVL                      (0x000E)
#define CLASSD_NR_TON                      (0x00F0)
#define CLASSD_NR_HYST                     (0x0300)
#define CLASSD_NR_ZERO                     (0x0C00)


/*====================================================*/
struct __CLK_AMBA_REG
/*====================================================*/
{
    WORD BITFLD_HCLK_DIV                           : 3;
    WORD BITFLD_PCLK_DIV                           : 2;
    WORD BITFLD_SRAM1_EN                           : 1;
    WORD                                           : 1;
    WORD BITFLD_MCRAM1_EN                          : 1;
    WORD                                           : 1;
    WORD BITFLD_HCLK_PRE                           : 1;
    WORD BITFLD_MEM_STROBE                         : 3;
};

#define HCLK_DIV                           (0x0007)
#define PCLK_DIV                           (0x0018)
#define SRAM1_EN                           (0x0020)
#define MCRAM1_EN                          (0x0080)
#define HCLK_PRE                           (0x0200)
#define MEM_STROBE                         (0x1C00)


/*====================================================*/
struct __CLK_AUX_REG
/*====================================================*/
{
    WORD                                           : 3;
    WORD BITFLD_BXTAL_EN                           : 2;
    WORD BITFLD_OWI_DIV                            : 2;
    WORD BITFLD_OWI_SEL                            : 1;
    WORD BITFLD_XDIV                               : 1;
};

#define BXTAL_EN                           (0x0018)
#define OWI_DIV                            (0x0060)
#define OWI_SEL                            (0x0080)
#define XDIV                               (0x0100)


/*====================================================*/
struct __CLK_CODEC_DIV_REG
/*====================================================*/
{
    WORD BITFLD_CODEC_DIV                          : 7;
    WORD BITFLD_CODEC_CLK_SEL                      : 2;
};

#define CODEC_DIV                          (0x007F)
#define CODEC_CLK_SEL                      (0x0180)


/*====================================================*/
struct __CLK_CODEC_REG
/*====================================================*/
{
    WORD BITFLD_CLK_MAIN_SEL                       : 2;
    WORD BITFLD_CLK_AD_SEL                         : 2;
    WORD BITFLD_CLK_DA_CLASSD_SEL                  : 2;
    WORD BITFLD_CLK_DA_LSR_SEL                     : 2;
    WORD BITFLD_CLK_PCM_SEL                        : 2;
};

#define CLK_MAIN_SEL                       (0x0003)
#define CLK_AD_SEL                         (0x000C)
#define CLK_DA_CLASSD_SEL                  (0x0030)
#define CLK_DA_LSR_SEL                     (0x00C0)
#define CLK_PCM_SEL                        (0x0300)


/*====================================================*/
struct __CLK_DSP_REG
/*====================================================*/
{
    WORD BITFLD_CLK_DSP_DIV                        : 3;
    WORD BITFLD_CLK_DSP_EN                         : 1;
};

#define CLK_DSP_DIV                        (0x0007)
#define CLK_DSP_EN                         (0x0008)


/*====================================================*/
struct __CLK_FREQ_TRIM_REG
/*====================================================*/
{
    WORD BITFLD_FINE_ADJ                           : 8;
    WORD BITFLD_COARSE_ADJ                         : 3;
};

#define FINE_ADJ                           (0x00FF)
#define COARSE_ADJ                         (0x0700)


/*====================================================*/
struct __CLK_PER_DIV_REG
/*====================================================*/
{
    WORD BITFLD_PER_DIV                            : 7;
    WORD BITFLD_PER_CLK_SEL                        : 2;
};

#define PER_DIV                            (0x007F)
#define PER_CLK_SEL                        (0x0180)


/*====================================================*/
struct __CLK_PER10_DIV_REG
/*====================================================*/
{
    WORD BITFLD_PER10_DIV                          : 3;
    WORD BITFLD_PER10_CLK_SEL                      : 2;
    WORD BITFLD_PER20_DIV                          : 3;
};

#define PER10_DIV                          (0x0007)
#define PER10_CLK_SEL                      (0x0018)
#define PER20_DIV                          (0x00E0)


/*====================================================*/
struct __CLK_PLL_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TESTMODE_SEL                       : 1;
    WORD BITFLD_CP_ON                              : 1;
    WORD BITFLD_PLL_OUT_DIV                        : 1;
    WORD BITFLD_PLL_CLK_SEL                        : 1;
    WORD BITFLD_VCO_ON                             : 1;
    WORD                                           : 1;
    WORD BITFLD_HF_SEL                             : 1;
    WORD BITFLD_PLL_DIP_DIV                        : 4;
    WORD BITFLD_DYN_SW                             : 1;
    WORD BITFLD_DIV2_CLK_SEL                       : 1;
};

#define TESTMODE_SEL                       (0x0001)
#define CP_ON                              (0x0002)
#define PLL_OUT_DIV                        (0x0004)
#define PLL_CLK_SEL                        (0x0008)
#define VCO_ON                             (0x0010)
#define HF_SEL                             (0x0040)
#define PLL_DIP_DIV                        (0x0780)
#define DYN_SW                             (0x0800)
#define DIV2_CLK_SEL                       (0x1000)


/*====================================================*/
struct __CLK_PLL_DIV_REG
/*====================================================*/
{
    WORD BITFLD_XD1                                : 2;
    WORD BITFLD_VD1                                : 3;
};

#define XD1                                (0x0003)
#define VD1                                (0x001C)


/*====================================================*/
struct __CLK_XTAL_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_OSC300KHZ                          : 1;
    WORD BITFLD_XTAL_DIV                           : 1;
};

#define OSC300KHZ                          (0x0001)
#define XTAL_DIV                           (0x0002)


/*====================================================*/
struct __CODEC_ADDA_REG
/*====================================================*/
{
    WORD BITFLD_DA_PD                              : 1;
    WORD BITFLD_AD_PD                              : 1;
    WORD BITFLD_DA_CADJ                            : 2;
    WORD BITFLD_AD_CADJ                            : 2;
    WORD BITFLD_DA_DITH_OFF                        : 1;
    WORD BITFLD_AD_DITH_OFF                        : 1;
    WORD BITFLD_DA_HBW                             : 1;
    WORD BITFLD_LPF_PD                             : 1;
    WORD BITFLD_LPF_BW                             : 3;
    WORD BITFLD_ADC_VREF_LSR                       : 2;
    WORD BITFLD_AUTO_SYNC                          : 1;
};

#define DA_PD                              (0x0001)
#define AD_PD                              (0x0002)
#define DA_CADJ                            (0x000C)
#define AD_CADJ                            (0x0030)
#define DA_DITH_OFF                        (0x0040)
#define AD_DITH_OFF                        (0x0080)
#define DA_HBW                             (0x0100)
#define LPF_PD                             (0x0200)
#define LPF_BW                             (0x1C00)
#define ADC_VREF_LSR                       (0x6000)
#define AUTO_SYNC                          (0x8000)


/*====================================================*/
struct __CODEC_LSR_REG
/*====================================================*/
{
    WORD BITFLD_LSRP_MODE                          : 2;
    WORD BITFLD_LSRP_PD                            : 1;
    WORD BITFLD_LSRN_MODE                          : 2;
    WORD BITFLD_LSRN_PD                            : 1;
    WORD BITFLD_LSRATT                             : 3;
    WORD BITFLD_LSREN_SE                           : 1;
};

#define LSRP_MODE                          (0x0003)
#define LSRP_PD                            (0x0004)
#define LSRN_MODE                          (0x0018)
#define LSRN_PD                            (0x0020)
#define LSRATT                             (0x01C0)
#define LSREN_SE                           (0x0200)


/*====================================================*/
struct __CODEC_MIC_REG
/*====================================================*/
{
    WORD BITFLD_MIC_MODE                           : 2;
    WORD BITFLD_MIC_PD                             : 1;
    WORD BITFLD_MIC_MUTE                           : 1;
    WORD BITFLD_MIC_GAIN                           : 4;
    WORD BITFLD_MIC_OFFCOM_SG                      : 1;
    WORD BITFLD_MIC_OFFCOM_ON                      : 1;
    WORD BITFLD_DSP_CTRL                           : 1;
    WORD BITFLD_MICH_ON                            : 1;
    WORD BITFLD_MIC_CADJ                           : 2;
};

#define MIC_MODE                           (0x0003)
#define MIC_PD                             (0x0004)
#define MIC_MUTE                           (0x0008)
#define MIC_GAIN                           (0x00F0)
#define MIC_OFFCOM_SG                      (0x0100)
#define MIC_OFFCOM_ON                      (0x0200)
#define DSP_CTRL                           (0x0400)
#define MICH_ON                            (0x0800)
#define MIC_CADJ                           (0x3000)


/*====================================================*/
struct __CODEC_TEST_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TCR                                : 12;
    WORD BITFLD_COR_ON                             : 1;
    WORD BITFLD_COR_STAT                           : 1;
    WORD BITFLD_CODEC_PROT                         : 1;
};

#define TCR                                (0x0FFF)
#define COR_ON                             (0x1000)
#define COR_STAT                           (0x2000)
#define CODEC_PROT                         (0x4000)


/*====================================================*/
struct __CODEC_TONE_REG
/*====================================================*/
{
    WORD BITFLD_CID_PD                             : 1;
    WORD BITFLD_CID_PR_DIS                         : 1;
    WORD BITFLD_RNG_PD                             : 1;
    WORD BITFLD_RNG_PR_DIS                         : 1;
    WORD BITFLD_PARA_PD                            : 1;
    WORD BITFLD_PARA_PR_DIS                        : 1;
    WORD BITFLD_RNG_CMP_PD                         : 1;
};

#define CID_PD                             (0x0001)
#define CID_PR_DIS                         (0x0002)
#define RNG_PD                             (0x0004)
#define RNG_PR_DIS                         (0x0008)
#define PARA_PD                            (0x0010)
#define PARA_PR_DIS                        (0x0020)
#define RNG_CMP_PD                         (0x0040)


/*====================================================*/
struct __CODEC_VREF_REG
/*====================================================*/
{
    WORD BITFLD_VREF_PD                            : 1;
    WORD BITFLD_VREF_FILT_PD                       : 1;
    WORD BITFLD_VREF_FILT_CADJ                     : 16;
    WORD BITFLD_VREF_INIT                          : 1;
    WORD BITFLD_AMP1V5_PD                          : 1;
    WORD BITFLD_VREF_BG_PD                         : 1;
    WORD BITFLD_BIAS_PD                            : 1;
    WORD BITFLD_AGND_LSR_PD                        : 1;
    WORD BITFLD_REFINT_PD                          : 1;
};

#define VREF_PD                            (0x0001)
#define VREF_FILT_PD                       (0x0002)
#define VREF_FILT_CADJ                     (0x80000000)
#define VREF_INIT                          (0x0010)
#define AMP1V5_PD                          (0x0020)
#define VREF_BG_PD                         (0x0040)
#define BIAS_PD                            (0x0080)
#define AGND_LSR_PD                        (0x0100)
#define REFINT_PD                          (0x0200)


/*====================================================*/
struct __CP_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_CP_EN                              : 2;
    WORD BITFLD_CP_LEVEL1                          : 2;
    WORD BITFLD_CP_LEVEL2                          : 2;
    WORD BITFLD_CP_PWM1                            : 1;
    WORD BITFLD_CP_PWM2                            : 1;
    WORD BITFLD_CP_FREQ                            : 2;
    WORD BITFLD_CP_PARALLEL                        : 1;
    WORD BITFLD_CP_MODE                            : 1;
    WORD BITFLD_CP_TEST_ADC1                       : 1;
    WORD BITFLD_CP_TEST_ADC2                       : 1;
    WORD BITFLD_CP_FORCE_MODE                      : 2;
};

#define CP_EN                              (0x0003)
#define CP_LEVEL1                          (0x000C)
#define CP_LEVEL2                          (0x0030)
#define CP_PWM1                            (0x0040)
#define CP_PWM2                            (0x0080)
#define CP_FREQ                            (0x0300)
#define CP_PARALLEL                        (0x0400)
#define CP_MODE                            (0x0800)
#define CP_TEST_ADC1                       (0x1000)
#define CP_TEST_ADC2                       (0x2000)
#define CP_FORCE_MODE                      (0xC000)


/*====================================================*/
struct __DEBUG_REG
/*====================================================*/
{
    WORD BITFLD_CLK100_EDGE                        : 1;
    WORD BITFLD_CLK100_NEG                         : 1;
    WORD BITFLD_CLK100_POS                         : 1;
    WORD BITFLD_CLK100_SRC                         : 1;
    WORD BITFLD_ENV_B01                            : 1;
    WORD                                           : 2;
    WORD BITFLD_SW_RESET                           : 1;
    WORD                                           : 3;
    WORD BITFLD_CR16_DBGM                          : 1;
};

#define CLK100_EDGE                        (0x0001)
#define CLK100_NEG                         (0x0002)
#define CLK100_POS                         (0x0004)
#define CLK100_SRC                         (0x0008)
#define ENV_B01                            (0x0010)
#define SW_RESET                           (0x0080)
#define CR16_DBGM                          (0x0800)


/*====================================================*/
struct __DIP_PC_REG
/*====================================================*/
{
    WORD BITFLD_DIP_PC                             : 8;
    WORD BITFLD_DIP_BANK                           : 1;
};

#define DIP_PC                             (0x00FF)
#define DIP_BANK                           (0x0100)


/*====================================================*/
struct __DIP_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_DIP_INT_VEC                        : 4;
    WORD BITFLD_PD1_INT                            : 1;
    WORD BITFLD_DIP_BRK_INT                        : 1;
    WORD BITFLD_PRESCALER                          : 1;
    WORD BITFLD_URST                               : 1;
};

#define DIP_INT_VEC                        (0x000F)
#define PD1_INT                            (0x0010)
#define DIP_BRK_INT                        (0x0020)
#define PRESCALER                          (0x0040)
#define URST                               (0x0080)


/*====================================================*/
struct __DIP_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DIP_INT_VEC                        : 4;
    WORD BITFLD_PD1_INT                            : 1;
    WORD BITFLD_DIP_BRK_INT                        : 1;
    WORD BITFLD_PRESCALER                          : 1;
    WORD BITFLD_URST                               : 1;
};

#define DIP_INT_VEC                        (0x000F)
#define PD1_INT                            (0x0010)
#define DIP_BRK_INT                        (0x0020)
#define PRESCALER                          (0x0040)
#define URST                               (0x0080)


/*====================================================*/
struct __DIP_STATUS1_REG
/*====================================================*/
{
    WORD BITFLD_DIP_VNMI_VEC                       : 4;
};

#define DIP_VNMI_VEC                       (0x000F)


/*====================================================*/
struct __DIP_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_DIP_VNMI_VEC                       : 4;
};

#define DIP_VNMI_VEC                       (0x000F)


/*====================================================*/
struct __DIP_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_DBUF                               : 1;
    WORD BITFLD_PRE_ACT                            : 1;
    WORD BITFLD_BRK_PRE_OVR                        : 1;
    WORD                                           : 1;
    WORD BITFLD_PD1_INT                            : 1;
    WORD BITFLD_DIP_BRK                            : 1;
    WORD                                           : 2;
    WORD BITFLD_SLOTCNT_RES                        : 1;
};

#define DBUF                               (0x0001)
#define PRE_ACT                            (0x0002)
#define BRK_PRE_OVR                        (0x0004)
#define PD1_INT                            (0x0010)
#define DIP_BRK                            (0x0020)
#define SLOTCNT_RES                        (0x0100)


/*====================================================*/
struct __DIP_MOD_SEL_REG
/*====================================================*/
{
    WORD BITFLD_ARMOD0                             : 1;
    WORD BITFLD_ARMOD1                             : 1;
    WORD BITFLD_ARMOD2                             : 1;
    WORD BITFLD_ARMOD3                             : 1;
    WORD BITFLD_AWMOD0                             : 1;
    WORD BITFLD_AWMOD1                             : 1;
    WORD BITFLD_AWMOD2                             : 1;
    WORD BITFLD_AWMOD3                             : 1;
};

#define ARMOD0                             (0x0001)
#define ARMOD1                             (0x0002)
#define ARMOD2                             (0x0004)
#define ARMOD3                             (0x0008)
#define AWMOD0                             (0x0010)
#define AWMOD1                             (0x0020)
#define AWMOD2                             (0x0040)
#define AWMOD3                             (0x0080)


/*====================================================*/
struct __DIP_SLOT_NUMBER_REG
/*====================================================*/
{
    WORD BITFLD_SLOT_CNTER                         : 5;
};

#define SLOT_CNTER                         (0x001F)


/*====================================================*/
struct __DMA0_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA1_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA2_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA3_A_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_A_STARTH                      : 9;
};

#define DMAx_A_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA0_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA1_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA2_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA3_B_STARTH_REG
/*====================================================*/
{
    WORD BITFLD_DMAx_B_STARTH                      : 9;
};

#define DMAx_B_STARTH                      (0x01FF)


/*====================================================*/
struct __DMA0_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DMA1_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DMA2_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DMA3_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DMA_ON                             : 1;
    WORD BITFLD_BW                                 : 2;
    WORD BITFLD_DINT_MODE                          : 1;
    WORD BITFLD_DREQ_MODE                          : 1;
    WORD BITFLD_BINC                               : 1;
    WORD BITFLD_AINC                               : 1;
    WORD BITFLD_CIRCULAR                           : 1;
    WORD BITFLD_DMA_PRIO                           : 2;
};

#define DMA_ON                             (0x0001)
#define BW                                 (0x0006)
#define DINT_MODE                          (0x0008)
#define DREQ_MODE                          (0x0010)
#define BINC                               (0x0020)
#define AINC                               (0x0040)
#define CIRCULAR                           (0x0080)
#define DMA_PRIO                           (0x0300)


/*====================================================*/
struct __DSP_CLASSD_BUZZOFF_REG
/*====================================================*/
{
    WORD                                           : 15;
    WORD BITFLD_BUZZOFF                            : 1;
};

#define BUZZOFF                            (0x8000)


/*====================================================*/
struct __DSP_CODEC_MIC_GAIN_REG
/*====================================================*/
{
    WORD                                           : 12;
    WORD BITFLD_DSP_MIC_GAIN                       : 4;
};

#define DSP_MIC_GAIN                       (0xF000)


/*====================================================*/
struct __DSP_CTRL_REG
/*====================================================*/
{
    WORD                                           : 2;
    WORD BITFLD_DSP_EN                             : 1;
    WORD BITFLD_DSP_CLK_EN                         : 1;
    WORD BITFLD_DSP_CR16_INT                       : 1;
    WORD                                           : 3;
    WORD BITFLD_DBG_EN                             : 1;
};

#define DSP_EN                             (0x0004)
#define DSP_CLK_EN                         (0x0008)
#define DSP_CR16_INT                       (0x0010)
#define DBG_EN                             (0x0100)


/*====================================================*/
struct __DSP_INT_PRIO1_REG
/*====================================================*/
{
    WORD BITFLD_DSP_INT2_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT1_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT0_PRIO                      : 3;
};

#define DSP_INT2_PRIO                      (0x0007)
#define DSP_INT1_PRIO                      (0x0070)
#define DSP_INT0_PRIO                      (0x0700)


/*====================================================*/
struct __DSP_INT_PRIO2_REG
/*====================================================*/
{
    WORD BITFLD_DSP_INT5_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT4_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT3_PRIO                      : 3;
};

#define DSP_INT5_PRIO                      (0x0007)
#define DSP_INT4_PRIO                      (0x0070)
#define DSP_INT3_PRIO                      (0x0700)


/*====================================================*/
struct __DSP_IRQ_START_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_DSP_IRQ_START                      : 12;
};

#define DSP_IRQ_START                      (0xFFF0)


/*====================================================*/
struct __DSP_MAIN_SYNC0_REG
/*====================================================*/
{
    WORD BITFLD_RAMIN0_SYNC                        : 2;
    WORD BITFLD_RAMIN1_SYNC                        : 2;
    WORD BITFLD_RAMIN2_SYNC                        : 2;
    WORD BITFLD_RAMIN3_SYNC                        : 2;
    WORD BITFLD_RAMOUT0_SYNC                       : 2;
    WORD BITFLD_RAMOUT1_SYNC                       : 2;
    WORD BITFLD_RAMOUT2_SYNC                       : 2;
    WORD BITFLD_RAMOUT3_SYNC                       : 2;
};

#define RAMIN0_SYNC                        (0x0003)
#define RAMIN1_SYNC                        (0x000C)
#define RAMIN2_SYNC                        (0x0030)
#define RAMIN3_SYNC                        (0x00C0)
#define RAMOUT0_SYNC                       (0x0300)
#define RAMOUT1_SYNC                       (0x0C00)
#define RAMOUT2_SYNC                       (0x3000)
#define RAMOUT3_SYNC                       (0xC000)


/*====================================================*/
struct __DSP_MAIN_SYNC1_REG
/*====================================================*/
{
    WORD BITFLD_DSP_SYNC0                          : 2;
    WORD BITFLD_DSP_SYNC1                          : 2;
    WORD BITFLD_DSP_SYNC2                          : 2;
    WORD BITFLD_AD_SYNC                            : 2;
    WORD BITFLD_DA_CLASSD_SYNC                     : 2;
    WORD BITFLD_DA_LSR_SYNC                        : 2;
    WORD BITFLD_ADC_SYNC                           : 2;
    WORD BITFLD_PCM_SYNC                           : 2;
};

#define DSP_SYNC0                          (0x0003)
#define DSP_SYNC1                          (0x000C)
#define DSP_SYNC2                          (0x0030)
#define AD_SYNC                            (0x00C0)
#define DA_CLASSD_SYNC                     (0x0300)
#define DA_LSR_SYNC                        (0x0C00)
#define ADC_SYNC                           (0x3000)
#define PCM_SYNC                           (0xC000)


/*====================================================*/
struct __DSP_MAIN_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DSP_MAIN_PRESET                    : 8;
    WORD BITFLD_DSP_MAIN_CTRL                      : 2;
};

#define DSP_MAIN_PRESET                    (0x00FF)
#define DSP_MAIN_CTRL                      (0x0300)


/*====================================================*/
struct __DSP_OVERFLOW_REG
/*====================================================*/
{
    WORD BITFLD_INT_OVERFLOW                       : 6;
    WORD BITFLD_WTF_OVERFLOW                       : 1;
    WORD BITFLD_IRQ_OVERFLOW                       : 1;
    WORD BITFLD_M_INT_OVERFLOW                     : 6;
    WORD BITFLD_M_WTF_OVERFLOW                     : 1;
    WORD BITFLD_M_IRQ_OVERFLOW                     : 1;
};

#define INT_OVERFLOW                       (0x003F)
#define WTF_OVERFLOW                       (0x0040)
#define IRQ_OVERFLOW                       (0x0080)
#define M_INT_OVERFLOW                     (0x3F00)
#define M_WTF_OVERFLOW                     (0x4000)
#define M_IRQ_OVERFLOW                     (0x8000)


/*====================================================*/
struct __DSP_PCM_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_PCM_EN                             : 1;
    WORD BITFLD_PCM_MASTER                         : 1;
    WORD BITFLD_DSP_PCM_SYNC                       : 1;
    WORD BITFLD_PCM_FSC0LEN                        : 2;
    WORD BITFLD_PCM_FSC0DEL                        : 1;
    WORD BITFLD_PCM_PPOD                           : 1;
    WORD BITFLD_PCM_CLKINV                         : 1;
};

#define PCM_EN                             (0x0001)
#define PCM_MASTER                         (0x0002)
#define DSP_PCM_SYNC                       (0x0004)
#define PCM_FSC0LEN                        (0x0018)
#define PCM_FSC0DEL                        (0x0020)
#define PCM_PPOD                           (0x0040)
#define PCM_CLKINV                         (0x0080)


/*====================================================*/
struct __DSP_VQI_REG
/*====================================================*/
{
    WORD BITFLD_BVQI_ON                            : 4;
};

#define BVQI_ON                            (0x000F)


/*====================================================*/
struct __DSP_ZCROSS1_OUT_REG
/*====================================================*/
{
    WORD BITFLD_DSP_ZCROSSx                        : 1;
};

#define DSP_ZCROSSx                        (0x8000)


/*====================================================*/
struct __DSP_ZCROSS2_OUT_REG
/*====================================================*/
{
    WORD BITFLD_DSP_ZCROSSx                        : 1;
};

#define DSP_ZCROSSx                        (0x8000)


/*====================================================*/
struct __FLASH_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_PROG_MODE                          : 2;
    WORD BITFLD_FLASH_SEL2                         : 1;
    WORD BITFLD_FLASH_SEL1                         : 1;
    WORD BITFLD_PROG_WRS                           : 1;
    WORD BITFLD_PROG_ERS                           : 1;
    WORD BITFLD_PROG_INFO_SEL2                     : 1;
    WORD BITFLD_PROG_INFO_SEL1                     : 1;
    WORD BITFLD_PROG_RMIN                          : 1;
    WORD BITFLD_FLASH_WPROT                        : 1;
    WORD BITFLD_FLASH_RPROT                        : 1;
};

#define PROG_MODE                          (0x0003)
#define FLASH_SEL2                         (0x0004)
#define FLASH_SEL1                         (0x0008)
#define PROG_WRS                           (0x0010)
#define PROG_ERS                           (0x0020)
#define PROG_INFO_SEL2                     (0x0040)
#define PROG_INFO_SEL1                     (0x0080)
#define PROG_RMIN                          (0x0100)
#define FLASH_WPROT                        (0x0200)
#define FLASH_RPROT                        (0x0400)


/*====================================================*/
struct __INT0_PRIORITY_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_DSP_INT_PRIO                       : 3;
};

#define DSP_INT_PRIO                       (0x0070)


/*====================================================*/
struct __INT1_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_TIM1_INT_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_CLK100_INT_PRIO                    : 3;
    WORD                                           : 1;
    WORD BITFLD_DIP_INT_PRIO                       : 3;
    WORD                                           : 1;
    WORD BITFLD_AD_INT_PRIO                        : 3;
};

#define TIM1_INT_PRIO                      (0x0007)
#define CLK100_INT_PRIO                    (0x0070)
#define DIP_INT_PRIO                       (0x0700)
#define AD_INT_PRIO                        (0x7000)


/*====================================================*/
struct __INT2_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_UART_RI_INT_PRIO                   : 3;
    WORD                                           : 1;
    WORD BITFLD_UART_TI_INT_PRIO                   : 3;
    WORD                                           : 1;
    WORD BITFLD_SPI_INT_PRIO                       : 3;
    WORD                                           : 1;
    WORD BITFLD_TIM0_INT_PRIO                      : 3;
};

#define UART_RI_INT_PRIO                   (0x0007)
#define UART_TI_INT_PRIO                   (0x0070)
#define SPI_INT_PRIO                       (0x0700)
#define TIM0_INT_PRIO                      (0x7000)


/*====================================================*/
struct __INT3_PRIORITY_REG
/*====================================================*/
{
    WORD BITFLD_ACCESS_INT_PRIO                    : 3;
    WORD                                           : 1;
    WORD BITFLD_KEYB_INT_PRIO                      : 3;
    WORD                                           : 1;
    WORD BITFLD_RESERVED_INT_PRIO                  : 3;
    WORD                                           : 1;
    WORD BITFLD_CT_CLASSD_INT_PRIO                 : 3;
};

#define ACCESS_INT_PRIO                    (0x0007)
#define KEYB_INT_PRIO                      (0x0070)
#define RESERVED_INT_PRIO                  (0x0700)
#define CT_CLASSD_INT_PRIO                 (0x7000)


/*====================================================*/
struct __KEY_GP_INT_REG
/*====================================================*/
{
    WORD BITFLD_INT6_CTRL                          : 3;
    WORD BITFLD_INT7_CTRL                          : 3;
    WORD BITFLD_INT8_CTRL                          : 3;
};

#define INT6_CTRL                          (0x0007)
#define INT7_CTRL                          (0x0038)
#define INT8_CTRL                          (0x01C0)


/*====================================================*/
struct __KEY_BOARD_INT_REG
/*====================================================*/
{
    WORD BITFLD_INT0_EN                            : 1;
    WORD BITFLD_INT1_EN                            : 1;
    WORD BITFLD_INT2_EN                            : 1;
    WORD BITFLD_INT3_EN                            : 1;
    WORD BITFLD_INT4_EN                            : 1;
    WORD BITFLD_INT5_EN                            : 1;
    WORD BITFLD_INT_PON_EN                         : 1;
    WORD BITFLD_INT_CHARGE_EN                      : 1;
    WORD BITFLD_CHARGE_CTRL                        : 1;
    WORD BITFLD_PON_CTRL                           : 1;
    WORD BITFLD_KEY_LEVEL                          : 1;
    WORD BITFLD_KEY_REL                            : 1;
    WORD BITFLD_CHARGE_EDGE                        : 1;
};

#define INT0_EN                            (0x0001)
#define INT1_EN                            (0x0002)
#define INT2_EN                            (0x0004)
#define INT3_EN                            (0x0008)
#define INT4_EN                            (0x0010)
#define INT5_EN                            (0x0020)
#define INT_PON_EN                         (0x0040)
#define INT_CHARGE_EN                      (0x0080)
#define CHARGE_CTRL                        (0x0100)
#define PON_CTRL                           (0x0200)
#define KEY_LEVEL                          (0x0400)
#define KEY_REL                            (0x0800)
#define CHARGE_EDGE                        (0x1000)


/*====================================================*/
struct __KEY_DEBOUNCE_REG
/*====================================================*/
{
    WORD BITFLD_DEBOUNCE                           : 6;
    WORD BITFLD_KEY_REPEAT                         : 6;
};

#define DEBOUNCE                           (0x003F)
#define KEY_REPEAT                         (0x0FC0)


/*====================================================*/
struct __KEY_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_KEY_STATUS                         : 4;
};

#define KEY_STATUS                         (0x000F)


/*====================================================*/
struct __MEM_CONF_REG
/*====================================================*/
{
    WORD BITFLD_T_RC                               : 3;
};

#define T_RC                               (0x0007)


/*====================================================*/
struct __PC_START_REG
/*====================================================*/
{
    WORD BITFLD_PC_START10                         : 2;
    WORD BITFLD_PC_START                           : 14;
};

#define PC_START10                         (0x0003)
#define PC_START                           (0xFFFC)


/*====================================================*/
struct __PAD_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_P04567_OD                          : 1;
    WORD BITFLD_P023_OD                            : 1;
    WORD BITFLD_P001_OD                            : 1;
    WORD BITFLD_P27_OD                             : 1;
    WORD BITFLD_P225_OD                            : 1;
    WORD BITFLD_P234_OD                            : 1;
    WORD BITFLD_P21_OD                             : 1;
    WORD BITFLD_P20_OD                             : 1;
    WORD BITFLD_LED3_CUR                           : 1;
    WORD BITFLD_LED4_CUR                           : 1;
    WORD BITFLD_P4_OD                              : 1;
    WORD BITFLD_P5_OD                              : 1;
};

#define P04567_OD                          (0x0001)
#define P023_OD                            (0x0002)
#define P001_OD                            (0x0004)
#define P27_OD                             (0x0008)
#define P225_OD                            (0x0010)
#define P234_OD                            (0x0020)
#define P21_OD                             (0x0040)
#define P20_OD                             (0x0080)
#define LED3_CUR                           (0x0100)
#define LED4_CUR                           (0x0200)
#define P4_OD                              (0x0400)
#define P5_OD                              (0x0800)


/*====================================================*/
struct __P0_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DATA                          : 1;
    WORD BITFLD_Px_1_DATA                          : 1;
    WORD BITFLD_Px_2_DATA                          : 1;
    WORD BITFLD_Px_3_DATA                          : 1;
    WORD BITFLD_Px_4_DATA                          : 1;
    WORD BITFLD_Px_5_DATA                          : 1;
    WORD BITFLD_Px_6_DATA                          : 1;
    WORD BITFLD_Px_7_DATA                          : 1;
};

#define Px_0_DATA                          (0x0001)
#define Px_1_DATA                          (0x0002)
#define Px_2_DATA                          (0x0004)
#define Px_3_DATA                          (0x0008)
#define Px_4_DATA                          (0x0010)
#define Px_5_DATA                          (0x0020)
#define Px_6_DATA                          (0x0040)
#define Px_7_DATA                          (0x0080)


/*====================================================*/
struct __P1_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DATA                          : 1;
    WORD BITFLD_Px_1_DATA                          : 1;
    WORD BITFLD_Px_2_DATA                          : 1;
    WORD BITFLD_Px_3_DATA                          : 1;
    WORD BITFLD_Px_4_DATA                          : 1;
    WORD BITFLD_Px_5_DATA                          : 1;
    WORD BITFLD_Px_6_DATA                          : 1;
    WORD BITFLD_Px_7_DATA                          : 1;
};

#define Px_0_DATA                          (0x0001)
#define Px_1_DATA                          (0x0002)
#define Px_2_DATA                          (0x0004)
#define Px_3_DATA                          (0x0008)
#define Px_4_DATA                          (0x0010)
#define Px_5_DATA                          (0x0020)
#define Px_6_DATA                          (0x0040)
#define Px_7_DATA                          (0x0080)


/*====================================================*/
struct __P2_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DATA                          : 1;
    WORD BITFLD_Px_1_DATA                          : 1;
    WORD BITFLD_Px_2_DATA                          : 1;
    WORD BITFLD_Px_3_DATA                          : 1;
    WORD BITFLD_Px_4_DATA                          : 1;
    WORD BITFLD_Px_5_DATA                          : 1;
    WORD BITFLD_Px_6_DATA                          : 1;
    WORD BITFLD_Px_7_DATA                          : 1;
};

#define Px_0_DATA                          (0x0001)
#define Px_1_DATA                          (0x0002)
#define Px_2_DATA                          (0x0004)
#define Px_3_DATA                          (0x0008)
#define Px_4_DATA                          (0x0010)
#define Px_5_DATA                          (0x0020)
#define Px_6_DATA                          (0x0040)
#define Px_7_DATA                          (0x0080)


/*====================================================*/
struct __P3_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DATA                          : 1;
    WORD BITFLD_Px_1_DATA                          : 1;
    WORD BITFLD_Px_2_DATA                          : 1;
    WORD BITFLD_Px_3_DATA                          : 1;
    WORD BITFLD_Px_4_DATA                          : 1;
    WORD BITFLD_Px_5_DATA                          : 1;
    WORD BITFLD_Px_6_DATA                          : 1;
    WORD BITFLD_Px_7_DATA                          : 1;
};

#define Px_0_DATA                          (0x0001)
#define Px_1_DATA                          (0x0002)
#define Px_2_DATA                          (0x0004)
#define Px_3_DATA                          (0x0008)
#define Px_4_DATA                          (0x0010)
#define Px_5_DATA                          (0x0020)
#define Px_6_DATA                          (0x0040)
#define Px_7_DATA                          (0x0080)


/*====================================================*/
struct __P0_SET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_SET                           : 1;
    WORD BITFLD_Px_1_SET                           : 1;
    WORD BITFLD_Px_2_SET                           : 1;
    WORD BITFLD_Px_3_SET                           : 1;
    WORD BITFLD_Px_4_SET                           : 1;
    WORD BITFLD_Px_5_SET                           : 1;
    WORD BITFLD_Px_6_SET                           : 1;
    WORD BITFLD_Px_7_SET                           : 1;
};

#define Px_0_SET                           (0x0001)
#define Px_1_SET                           (0x0002)
#define Px_2_SET                           (0x0004)
#define Px_3_SET                           (0x0008)
#define Px_4_SET                           (0x0010)
#define Px_5_SET                           (0x0020)
#define Px_6_SET                           (0x0040)
#define Px_7_SET                           (0x0080)


/*====================================================*/
struct __P1_SET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_SET                           : 1;
    WORD BITFLD_Px_1_SET                           : 1;
    WORD BITFLD_Px_2_SET                           : 1;
    WORD BITFLD_Px_3_SET                           : 1;
    WORD BITFLD_Px_4_SET                           : 1;
    WORD BITFLD_Px_5_SET                           : 1;
    WORD BITFLD_Px_6_SET                           : 1;
    WORD BITFLD_Px_7_SET                           : 1;
};

#define Px_0_SET                           (0x0001)
#define Px_1_SET                           (0x0002)
#define Px_2_SET                           (0x0004)
#define Px_3_SET                           (0x0008)
#define Px_4_SET                           (0x0010)
#define Px_5_SET                           (0x0020)
#define Px_6_SET                           (0x0040)
#define Px_7_SET                           (0x0080)


/*====================================================*/
struct __P2_SET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_SET                           : 1;
    WORD BITFLD_Px_1_SET                           : 1;
    WORD BITFLD_Px_2_SET                           : 1;
    WORD BITFLD_Px_3_SET                           : 1;
    WORD BITFLD_Px_4_SET                           : 1;
    WORD BITFLD_Px_5_SET                           : 1;
    WORD BITFLD_Px_6_SET                           : 1;
    WORD BITFLD_Px_7_SET                           : 1;
};

#define Px_0_SET                           (0x0001)
#define Px_1_SET                           (0x0002)
#define Px_2_SET                           (0x0004)
#define Px_3_SET                           (0x0008)
#define Px_4_SET                           (0x0010)
#define Px_5_SET                           (0x0020)
#define Px_6_SET                           (0x0040)
#define Px_7_SET                           (0x0080)


/*====================================================*/
struct __P3_SET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_SET                           : 1;
    WORD BITFLD_Px_1_SET                           : 1;
    WORD BITFLD_Px_2_SET                           : 1;
    WORD BITFLD_Px_3_SET                           : 1;
    WORD BITFLD_Px_4_SET                           : 1;
    WORD BITFLD_Px_5_SET                           : 1;
    WORD BITFLD_Px_6_SET                           : 1;
    WORD BITFLD_Px_7_SET                           : 1;
};

#define Px_0_SET                           (0x0001)
#define Px_1_SET                           (0x0002)
#define Px_2_SET                           (0x0004)
#define Px_3_SET                           (0x0008)
#define Px_4_SET                           (0x0010)
#define Px_5_SET                           (0x0020)
#define Px_6_SET                           (0x0040)
#define Px_7_SET                           (0x0080)


/*====================================================*/
struct __P0_RESET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_RESET                         : 1;
    WORD BITFLD_Px_1_RESET                         : 1;
    WORD BITFLD_Px_2_RESET                         : 1;
    WORD BITFLD_Px_3_RESET                         : 1;
    WORD BITFLD_Px_4_RESET                         : 1;
    WORD BITFLD_Px_5_RESET                         : 1;
    WORD BITFLD_Px_6_RESET                         : 1;
    WORD BITFLD_Px_7_RESET                         : 1;
};

#define Px_0_RESET                         (0x0001)
#define Px_1_RESET                         (0x0002)
#define Px_2_RESET                         (0x0004)
#define Px_3_RESET                         (0x0008)
#define Px_4_RESET                         (0x0010)
#define Px_5_RESET                         (0x0020)
#define Px_6_RESET                         (0x0040)
#define Px_7_RESET                         (0x0080)


/*====================================================*/
struct __P1_RESET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_RESET                         : 1;
    WORD BITFLD_Px_1_RESET                         : 1;
    WORD BITFLD_Px_2_RESET                         : 1;
    WORD BITFLD_Px_3_RESET                         : 1;
    WORD BITFLD_Px_4_RESET                         : 1;
    WORD BITFLD_Px_5_RESET                         : 1;
    WORD BITFLD_Px_6_RESET                         : 1;
    WORD BITFLD_Px_7_RESET                         : 1;
};

#define Px_0_RESET                         (0x0001)
#define Px_1_RESET                         (0x0002)
#define Px_2_RESET                         (0x0004)
#define Px_3_RESET                         (0x0008)
#define Px_4_RESET                         (0x0010)
#define Px_5_RESET                         (0x0020)
#define Px_6_RESET                         (0x0040)
#define Px_7_RESET                         (0x0080)


/*====================================================*/
struct __P2_RESET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_RESET                         : 1;
    WORD BITFLD_Px_1_RESET                         : 1;
    WORD BITFLD_Px_2_RESET                         : 1;
    WORD BITFLD_Px_3_RESET                         : 1;
    WORD BITFLD_Px_4_RESET                         : 1;
    WORD BITFLD_Px_5_RESET                         : 1;
    WORD BITFLD_Px_6_RESET                         : 1;
    WORD BITFLD_Px_7_RESET                         : 1;
};

#define Px_0_RESET                         (0x0001)
#define Px_1_RESET                         (0x0002)
#define Px_2_RESET                         (0x0004)
#define Px_3_RESET                         (0x0008)
#define Px_4_RESET                         (0x0010)
#define Px_5_RESET                         (0x0020)
#define Px_6_RESET                         (0x0040)
#define Px_7_RESET                         (0x0080)


/*====================================================*/
struct __P3_RESET_DATA_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_RESET                         : 1;
    WORD BITFLD_Px_1_RESET                         : 1;
    WORD BITFLD_Px_2_RESET                         : 1;
    WORD BITFLD_Px_3_RESET                         : 1;
    WORD BITFLD_Px_4_RESET                         : 1;
    WORD BITFLD_Px_5_RESET                         : 1;
    WORD BITFLD_Px_6_RESET                         : 1;
    WORD BITFLD_Px_7_RESET                         : 1;
};

#define Px_0_RESET                         (0x0001)
#define Px_1_RESET                         (0x0002)
#define Px_2_RESET                         (0x0004)
#define Px_3_RESET                         (0x0008)
#define Px_4_RESET                         (0x0010)
#define Px_5_RESET                         (0x0020)
#define Px_6_RESET                         (0x0040)
#define Px_7_RESET                         (0x0080)


/*====================================================*/
struct __P0_DIR_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DIR                           : 2;
    WORD BITFLD_Px_1_DIR                           : 2;
    WORD BITFLD_Px_2_DIR                           : 2;
    WORD BITFLD_Px_3_DIR                           : 2;
    WORD BITFLD_Px_4_DIR                           : 2;
    WORD BITFLD_Px_5_DIR                           : 2;
    WORD BITFLD_Px_6_DIR                           : 2;
    WORD BITFLD_Px_7_DIR                           : 2;
};

#define Px_0_DIR                           (0x0003)
#define Px_1_DIR                           (0x000C)
#define Px_2_DIR                           (0x0030)
#define Px_3_DIR                           (0x00C0)
#define Px_4_DIR                           (0x0300)
#define Px_5_DIR                           (0x0C00)
#define Px_6_DIR                           (0x3000)
#define Px_7_DIR                           (0xC000)


/*====================================================*/
struct __P1_DIR_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DIR                           : 2;
    WORD BITFLD_Px_1_DIR                           : 2;
    WORD BITFLD_Px_2_DIR                           : 2;
    WORD BITFLD_Px_3_DIR                           : 2;
    WORD BITFLD_Px_4_DIR                           : 2;
    WORD BITFLD_Px_5_DIR                           : 2;
    WORD BITFLD_Px_6_DIR                           : 2;
    WORD BITFLD_Px_7_DIR                           : 2;
};

#define Px_0_DIR                           (0x0003)
#define Px_1_DIR                           (0x000C)
#define Px_2_DIR                           (0x0030)
#define Px_3_DIR                           (0x00C0)
#define Px_4_DIR                           (0x0300)
#define Px_5_DIR                           (0x0C00)
#define Px_6_DIR                           (0x3000)
#define Px_7_DIR                           (0xC000)


/*====================================================*/
struct __P2_DIR_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DIR                           : 2;
    WORD BITFLD_Px_1_DIR                           : 2;
    WORD BITFLD_Px_2_DIR                           : 2;
    WORD BITFLD_Px_3_DIR                           : 2;
    WORD BITFLD_Px_4_DIR                           : 2;
    WORD BITFLD_Px_5_DIR                           : 2;
    WORD BITFLD_Px_6_DIR                           : 2;
    WORD BITFLD_Px_7_DIR                           : 2;
};

#define Px_0_DIR                           (0x0003)
#define Px_1_DIR                           (0x000C)
#define Px_2_DIR                           (0x0030)
#define Px_3_DIR                           (0x00C0)
#define Px_4_DIR                           (0x0300)
#define Px_5_DIR                           (0x0C00)
#define Px_6_DIR                           (0x3000)
#define Px_7_DIR                           (0xC000)


/*====================================================*/
struct __P3_DIR_REG
/*====================================================*/
{
    WORD BITFLD_Px_0_DIR                           : 2;
    WORD BITFLD_Px_1_DIR                           : 2;
    WORD BITFLD_Px_2_DIR                           : 2;
    WORD BITFLD_Px_3_DIR                           : 2;
    WORD BITFLD_Px_4_DIR                           : 2;
    WORD BITFLD_Px_5_DIR                           : 2;
    WORD BITFLD_Px_6_DIR                           : 2;
    WORD BITFLD_Px_7_DIR                           : 2;
};

#define Px_0_DIR                           (0x0003)
#define Px_1_DIR                           (0x000C)
#define Px_2_DIR                           (0x0030)
#define Px_3_DIR                           (0x00C0)
#define Px_4_DIR                           (0x0300)
#define Px_5_DIR                           (0x0C00)
#define Px_6_DIR                           (0x3000)
#define Px_7_DIR                           (0xC000)


/*====================================================*/
struct __P0_MODE_REG
/*====================================================*/
{
    WORD BITFLD_P0_0_MODE                          : 1;
    WORD BITFLD_P0_1_MODE                          : 1;
    WORD BITFLD_P0_2_MODE                          : 2;
    WORD BITFLD_P0_3_MODE                          : 2;
    WORD BITFLD_P0_4_MODE                          : 2;
    WORD BITFLD_P0_5_MODE                          : 2;
    WORD BITFLD_P0_6_MODE                          : 2;
    WORD BITFLD_P0_7_MODE                          : 2;
};

#define P0_0_MODE                          (0x0001)
#define P0_1_MODE                          (0x0002)
#define P0_2_MODE                          (0x000C)
#define P0_3_MODE                          (0x0030)
#define P0_4_MODE                          (0x00C0)
#define P0_5_MODE                          (0x0300)
#define P0_6_MODE                          (0x0C00)
#define P0_7_MODE                          (0x3000)


/*====================================================*/
struct __P1_MODE_REG
/*====================================================*/
{
    WORD BITFLD_P1_0_MODE                          : 1;
    WORD BITFLD_P1_1_MODE                          : 1;
    WORD BITFLD_P1_2_MODE                          : 1;
    WORD BITFLD_P1_3_MODE                          : 1;
    WORD BITFLD_P1_4_MODE                          : 1;
    WORD BITFLD_P1_5_MODE                          : 3;
    WORD BITFLD_RF_BB_MODE                         : 2;
};

#define P1_0_MODE                          (0x0001)
#define P1_1_MODE                          (0x0002)
#define P1_2_MODE                          (0x0004)
#define P1_3_MODE                          (0x0008)
#define P1_4_MODE                          (0x0010)
#define P1_5_MODE                          (0x00E0)
#define RF_BB_MODE                         (0x0300)


/*====================================================*/
struct __P2_MODE_REG
/*====================================================*/
{
    WORD BITFLD_P2_0_MODE                          : 2;
    WORD BITFLD_P2_1_MODE                          : 2;
    WORD BITFLD_P2_2_MODE                          : 2;
    WORD BITFLD_P2_3_MODE                          : 2;
    WORD BITFLD_P2_4_MODE                          : 2;
    WORD BITFLD_P2_5_MODE                          : 2;
    WORD BITFLD_INT6_MODE                          : 1;
    WORD BITFLD_P2_6_MODE                          : 1;
    WORD BITFLD_INT7_MODE                          : 1;
    WORD BITFLD_P2_7_MODE                          : 1;
};

#define P2_0_MODE                          (0x0003)
#define P2_1_MODE                          (0x000C)
#define P2_2_MODE                          (0x0030)
#define P2_3_MODE                          (0x00C0)
#define P2_4_MODE                          (0x0300)
#define P2_5_MODE                          (0x0C00)
#define INT6_MODE                          (0x1000)
#define P2_6_MODE                          (0x2000)
#define INT7_MODE                          (0x4000)
#define P2_7_MODE                          (0x8000)


/*====================================================*/
struct __P3_MODE_REG
/*====================================================*/
{
    WORD BITFLD_P3_0_MODE                          : 2;
    WORD BITFLD_P3_1_MODE                          : 2;
    WORD BITFLD_P3_2_MODE                          : 2;
    WORD BITFLD_P3_3_MODE                          : 2;
    WORD BITFLD_P3_4_MODE                          : 2;
    WORD BITFLD_P3_5_MODE                          : 2;
    WORD BITFLD_P3_6_MODE                          : 2;
    WORD BITFLD_P3_7_MODE                          : 2;
};

#define P3_0_MODE                          (0x0003)
#define P3_1_MODE                          (0x000C)
#define P3_2_MODE                          (0x0030)
#define P3_3_MODE                          (0x00C0)
#define P3_4_MODE                          (0x0300)
#define P3_5_MODE                          (0x0C00)
#define P3_6_MODE                          (0x3000)
#define P3_7_MODE                          (0xC000)


/*====================================================*/
struct __RESET_FREEZE_REG
/*====================================================*/
{
    WORD BITFLD_FRZ_DIP                            : 1;
    WORD BITFLD_FRZ_TIM0                           : 1;
    WORD BITFLD_FRZ_TIM1                           : 1;
    WORD BITFLD_FRZ_WDOG                           : 1;
    WORD BITFLD_FRZ_DMA0                           : 1;
    WORD BITFLD_FRZ_DMA1                           : 1;
    WORD BITFLD_FRZ_DMA2                           : 1;
    WORD BITFLD_FRZ_DMA3                           : 1;
};

#define FRZ_DIP                            (0x0001)
#define FRZ_TIM0                           (0x0002)
#define FRZ_TIM1                           (0x0004)
#define FRZ_WDOG                           (0x0008)
#define FRZ_DMA0                           (0x0010)
#define FRZ_DMA1                           (0x0020)
#define FRZ_DMA2                           (0x0040)
#define FRZ_DMA3                           (0x0080)


/*====================================================*/
struct __RESET_INT_PENDING_REG
/*====================================================*/
{
    WORD BITFLD_ACCESS_INT_PEND                    : 1;
    WORD BITFLD_KEYB_INT_PEND                      : 1;
    WORD BITFLD_RESERVED_INT_PEND                  : 1;
    WORD BITFLD_CT_CLASSD_INT_PEND                 : 1;
    WORD BITFLD_UART_RI_INT_PEND                   : 1;
    WORD BITFLD_UART_TI_INT_PEND                   : 1;
    WORD BITFLD_SPI_INT_PEND                       : 1;
    WORD BITFLD_TIM0_INT_PEND                      : 1;
    WORD BITFLD_TIM1_INT_PEND                      : 1;
    WORD BITFLD_CLK100_INT_PEND                    : 1;
    WORD BITFLD_DIP_INT_PEND                       : 1;
    WORD BITFLD_AD_INT_PEND                        : 1;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT_PEND                       : 1;
};

#define ACCESS_INT_PEND                    (0x0001)
#define KEYB_INT_PEND                      (0x0002)
#define RESERVED_INT_PEND                  (0x0004)
#define CT_CLASSD_INT_PEND                 (0x0008)
#define UART_RI_INT_PEND                   (0x0010)
#define UART_TI_INT_PEND                   (0x0020)
#define SPI_INT_PEND                       (0x0040)
#define TIM0_INT_PEND                      (0x0080)
#define TIM1_INT_PEND                      (0x0100)
#define CLK100_INT_PEND                    (0x0200)
#define DIP_INT_PEND                       (0x0400)
#define AD_INT_PEND                        (0x0800)
#define DSP_INT_PEND                       (0x2000)


/*====================================================*/
struct __SET_FREEZE_REG
/*====================================================*/
{
    WORD BITFLD_FRZ_DIP                            : 1;
    WORD BITFLD_FRZ_TIM0                           : 1;
    WORD BITFLD_FRZ_TIM1                           : 1;
    WORD BITFLD_FRZ_WDOG                           : 1;
    WORD BITFLD_FRZ_DMA0                           : 1;
    WORD BITFLD_FRZ_DMA1                           : 1;
    WORD BITFLD_FRZ_DMA2                           : 1;
    WORD BITFLD_FRZ_DMA3                           : 1;
};

#define FRZ_DIP                            (0x0001)
#define FRZ_TIM0                           (0x0002)
#define FRZ_TIM1                           (0x0004)
#define FRZ_WDOG                           (0x0008)
#define FRZ_DMA0                           (0x0010)
#define FRZ_DMA1                           (0x0020)
#define FRZ_DMA2                           (0x0040)
#define FRZ_DMA3                           (0x0080)


/*====================================================*/
struct __SET_INT_PENDING_REG
/*====================================================*/
{
    WORD BITFLD_ACCESS_INT_PEND                    : 1;
    WORD BITFLD_KEYB_INT_PEND                      : 1;
    WORD BITFLD_UART1_RI_TI_INT_PEND               : 1;
    WORD BITFLD_CT_CLASSD_INT_PEND                 : 1;
    WORD BITFLD_UART_RI_INT_PEND                   : 1;
    WORD BITFLD_UART_TI_INT_PEND                   : 1;
    WORD BITFLD_SPI_INT_PEND                       : 1;
    WORD BITFLD_TIM0_INT_PEND                      : 1;
    WORD BITFLD_TIM1_INT_PEND                      : 1;
    WORD BITFLD_CLK100_INT_PEND                    : 1;
    WORD BITFLD_DIP_INT_PEND                       : 1;
    WORD BITFLD_AD_INT_PEND                        : 1;
    WORD                                           : 1;
    WORD BITFLD_DSP_INT_PEND                       : 1;
};

#define ACCESS_INT_PEND                    (0x0001)
#define KEYB_INT_PEND                      (0x0002)
#define UART1_RI_TI_INT_PEND               (0x0004)
#define CT_CLASSD_INT_PEND                 (0x0008)
#define UART_RI_INT_PEND                   (0x0010)
#define UART_TI_INT_PEND                   (0x0020)
#define SPI_INT_PEND                       (0x0040)
#define TIM0_INT_PEND                      (0x0080)
#define TIM1_INT_PEND                      (0x0100)
#define CLK100_INT_PEND                    (0x0200)
#define DIP_INT_PEND                       (0x0400)
#define AD_INT_PEND                        (0x0800)
#define DSP_INT_PEND                       (0x2000)


/*====================================================*/
struct __SPI_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_SPI_ON                             : 1;
    WORD BITFLD_SPI_PHA                            : 1;
    WORD BITFLD_SPI_POL                            : 1;
    WORD BITFLD_SPI_CLK                            : 2;
    WORD BITFLD_SPI_DO                             : 1;
    WORD BITFLD_SPI_SMN                            : 1;
    WORD BITFLD_SPI_WORD                           : 2;
    WORD BITFLD_SPI_RST                            : 1;
    WORD BITFLD_SPI_FORCE_DO                       : 1;
    WORD BITFLD_SPI_TXH                            : 1;
    WORD BITFLD_SPI_DI                             : 1;
    WORD BITFLD_SPI_INT_BIT                        : 1;
    WORD BITFLD_SPI_MINT                           : 1;
    WORD BITFLD_SPI_EN_CTRL                        : 1;
};

#define SPI_ON                             (0x0001)
#define SPI_PHA                            (0x0002)
#define SPI_POL                            (0x0004)
#define SPI_CLK                            (0x0018)
#define SPI_DO                             (0x0020)
#define SPI_SMN                            (0x0040)
#define SPI_WORD                           (0x0180)
#define SPI_RST                            (0x0200)
#define SPI_FORCE_DO                       (0x0400)
#define SPI_TXH                            (0x0800)
#define SPI_DI                             (0x1000)
#define SPI_INT_BIT                        (0x2000)
#define SPI_MINT                           (0x4000)
#define SPI_EN_CTRL                        (0x8000)


/*====================================================*/
struct __TIMER_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TIM0_CTRL                          : 1;
    WORD BITFLD_TIM1_CTRL                          : 1;
    WORD BITFLD_CLK_CTRL0                          : 1;
    WORD BITFLD_CLK_CTRL1                          : 1;
    WORD BITFLD_WDOG_CTRL                          : 1;
    WORD BITFLD_TIM1_MODE                          : 1;
    WORD BITFLD_CLK_DIV8                           : 1;
    WORD BITFLD_TIM2_CTRL                          : 1;
};

#define TIM0_CTRL                          (0x0001)
#define TIM1_CTRL                          (0x0002)
#define CLK_CTRL0                          (0x0004)
#define CLK_CTRL1                          (0x0008)
#define WDOG_CTRL                          (0x0010)
#define TIM1_MODE                          (0x0020)
#define CLK_DIV8                           (0x0040)
#define TIM2_CTRL                          (0x0080)


/*====================================================*/
struct __TIMER2_DUTY1_REG
/*====================================================*/
{
    WORD BITFLD_T2_DUTY1                           : 14;
};

#define T2_DUTY1                           (0x3FFF)


/*====================================================*/
struct __TIMER2_DUTY2_REG
/*====================================================*/
{
    WORD BITFLD_T2_DUTY2                           : 14;
};

#define T2_DUTY2                           (0x3FFF)


/*====================================================*/
struct __TEST_ENV_REG
/*====================================================*/
{
    WORD BITFLD_BOOT                               : 1;
    WORD                                           : 3;
    WORD BITFLD_ENV_SDI                            : 1;
    WORD BITFLD_ENV_REG7_5                         : 3;
};

#define BOOT                               (0x0001)
#define ENV_SDI                            (0x0010)
#define ENV_REG7_5                         (0x00E0)


/*====================================================*/
struct __TONE_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_GATESRC1                           : 2;
    WORD BITFLD_CLKSRC1                            : 2;
    WORD BITFLD_TIMER_RELOAD1                      : 4;
    WORD BITFLD_CT1_INT                            : 1;
    WORD BITFLD_MCT1_INT                           : 1;
    WORD BITFLD_GATE_EDGE1                         : 1;
};

#define GATESRC1                           (0x0003)
#define CLKSRC1                            (0x000C)
#define TIMER_RELOAD1                      (0x00F0)
#define CT1_INT                            (0x0100)
#define MCT1_INT                           (0x0200)
#define GATE_EDGE1                         (0x0400)


/*====================================================*/
struct __TONE_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_GATESRC2                           : 2;
    WORD BITFLD_CLKSRC2                            : 2;
    WORD BITFLD_TIMER_RELOAD2                      : 4;
    WORD BITFLD_CT2_INT                            : 1;
    WORD BITFLD_MCT2_INT                           : 1;
    WORD BITFLD_GATE_EDGE2                         : 1;
};

#define GATESRC2                           (0x0003)
#define CLKSRC2                            (0x000C)
#define TIMER_RELOAD2                      (0x00F0)
#define CT2_INT                            (0x0100)
#define MCT2_INT                           (0x0200)
#define GATE_EDGE2                         (0x0400)


/*====================================================*/
struct __TRACE_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_SIZE                         : 3;
    WORD BITFLD_TRACE_COND                         : 1;
    WORD BITFLD_EXT_EVENTS_ON                      : 1;
    WORD BITFLD_DIP_EVENTS_ON                      : 1;
    WORD BITFLD_DSP_EVENTS_ON                      : 1;
    WORD BITFLD_BUS_EVENTS_ON                      : 1;
    WORD BITFLD_D_TRACE_EV_ON                      : 1;
    WORD BITFLD_I_TRACE_EV_ON                      : 1;
    WORD BITFLD_D_TRACE_ON                         : 1;
    WORD BITFLD_I_TRACE_ON                         : 1;
    WORD BITFLD_TRACE_COND_EXT                     : 3;
    WORD BITFLD_TRACE_MODE                         : 1;
};

#define TRACE_SIZE                         (0x0007)
#define TRACE_COND                         (0x0008)
#define EXT_EVENTS_ON                      (0x0010)
#define DIP_EVENTS_ON                      (0x0020)
#define DSP_EVENTS_ON                      (0x0040)
#define BUS_EVENTS_ON                      (0x0080)
#define D_TRACE_EV_ON                      (0x0100)
#define I_TRACE_EV_ON                      (0x0200)
#define D_TRACE_ON                         (0x0400)
#define I_TRACE_ON                         (0x0800)
#define TRACE_COND_EXT                     (0x7000)
#define TRACE_MODE                         (0x8000)


/*====================================================*/
struct __TRACE_STATUS_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_IDX                          : 11;
    WORD                                           : 2;
    WORD BITFLD_TRACE_TOUCH                        : 1;
    WORD BITFLD_TRACE_EOB                          : 1;
    WORD BITFLD_TRACE_BUSY                         : 1;
};

#define TRACE_IDX                          (0x07FF)
#define TRACE_TOUCH                        (0x2000)
#define TRACE_EOB                          (0x4000)
#define TRACE_BUSY                         (0x8000)


/*====================================================*/
struct __TRACE_START0_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_START0                       : 15;
};

#define TRACE_START0                       (0x7FFF)


/*====================================================*/
struct __TRACE_LEN0_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_LEN0                         : 15;
};

#define TRACE_LEN0                         (0x7FFF)


/*====================================================*/
struct __TRACE_START1_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_START1                       : 15;
};

#define TRACE_START1                       (0x7FFF)


/*====================================================*/
struct __TRACE_LEN1_REG
/*====================================================*/
{
    WORD BITFLD_TRACE_LEN1                         : 15;
};

#define TRACE_LEN1                         (0x7FFF)


/*====================================================*/
struct __UART_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_UART_REN                           : 1;
    WORD BITFLD_UART_TEN                           : 1;
    WORD BITFLD_BAUDRATE                           : 3;
    WORD BITFLD_TI                                 : 1;
    WORD BITFLD_RI                                 : 1;
    WORD BITFLD_UART_MODE                          : 1;
    WORD BITFLD_IRDA_EN                            : 1;
    WORD BITFLD_INV_URX                            : 1;
    WORD BITFLD_INV_UTX                            : 1;
};

#define UART_REN                           (0x0001)
#define UART_TEN                           (0x0002)
#define BAUDRATE                           (0x001C)
#define UART_TI                            (0x0020)
#define UART_RI                            (0x0040)
#define UART_MODE                          (0x0080)
#define IRDA_EN                            (0x0100)
#define INV_URX                            (0x0200)
#define INV_UTX                            (0x0400)


/*====================================================*/
struct __UART_ERROR_REG
/*====================================================*/
{
    WORD BITFLD_PAR_STATUS                         : 1;
    WORD BITFLD_DMA_PARITY_ERROR                   : 1;
};

#define PAR_STATUS                         (0x0001)
#define DMA_PARITY_ERROR                   (0x0002)


/*====================================================*/
struct __RF_BURST_MODE_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_CN                                 : 7;
    WORD BITFLD_RFCAL                              : 6;
    WORD BITFLD_RSSI_PA_MODE                       : 1;
    WORD BITFLD_FAD                                : 2;
    WORD BITFLD_RX_TX                              : 2;
};

#define CN                                 (0x007F)
#define RFCAL                              (0x1F80)
#define RSSI_PA_MODE                       (0x2000)
#define FAD                                (0xC000)
#define RX_TX                              (0x30000)


/*====================================================*/
struct __RF_BURST_MODE_SHADOW1_REG
/*====================================================*/
{
    WORD BITFLD_CN_SHW                             : 8;
    WORD BITFLD_RFCAL_SHW                          : 6;
    WORD BITFLD_RSSI_PA_MODE_SHW                   : 1;
};

#define CN_SHW                             (0x00FF)
#define RFCAL_SHW                          (0x3F00)
#define RSSI_PA_MODE_SHW                   (0x4000)


/*====================================================*/
struct __RF_BURST_MODE_SHADOW2_REG
/*====================================================*/
{
    WORD BITFLD_FAD_SHW                            : 2;
    WORD BITFLD_TX_ASSERT                          : 1;
    WORD BITFLD_RX_ASSERT                          : 1;
    WORD BITFLD_SHADOW_EN                          : 1;
};

#define FAD_SHW                            (0x0003)
#define TX_ASSERT                          (0x0004)
#define RX_ASSERT                          (0x0008)
#define SHADOW_EN                          (0x0010)


/*====================================================*/
struct __RF_ALW_EN_REG
/*====================================================*/
{
    WORD BITFLD_PORT4_ALW_EN                       : 1;
    WORD BITFLD_PORT3_ALW_EN                       : 1;
    WORD BITFLD_PORT2_ALW_EN                       : 1;
    WORD BITFLD_PORT1_ALW_EN                       : 1;
    WORD BITFLD_PLLCLOSED_ALW_EN                   : 1;
    WORD BITFLD_SYNTH_ALW_EN                       : 1;
    WORD BITFLD_BIAS_ALW_EN                        : 1;
    WORD BITFLD_RSSIPH_ALW_EN                      : 1;
    WORD BITFLD_DEM_ALW_EN                         : 1;
    WORD BITFLD_ADC_ALW_EN                         : 1;
    WORD BITFLD_IF_ALW_EN                          : 1;
    WORD BITFLD_LNAMIX_ALW_EN                      : 1;
    WORD BITFLD_PADR_ALW_EN                        : 1;
};

#define PORT4_ALW_EN                       (0x0001)
#define PORT3_ALW_EN                       (0x0002)
#define PORT2_ALW_EN                       (0x0004)
#define PORT1_ALW_EN                       (0x0008)
#define PLLCLOSED_ALW_EN                   (0x0010)
#define SYNTH_ALW_EN                       (0x0020)
#define BIAS_ALW_EN                        (0x0040)
#define RSSIPH_ALW_EN                      (0x0080)
#define DEM_ALW_EN                         (0x0100)
#define ADC_ALW_EN                         (0x0200)
#define IF_ALW_EN                          (0x0400)
#define LNAMIX_ALW_EN                      (0x0800)
#define PADR_ALW_EN                        (0x1000)


/*====================================================*/
struct __RF_PORT1_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_EN_BY_TX                           : 1;
    WORD BITFLD_EN_BY_RX                           : 1;
    WORD BITFLD_SSI                                : 1;
    WORD BITFLD_PA_PS                              : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define EN_BY_TX                           (0x1000)
#define EN_BY_RX                           (0x2000)
#define SSI                                (0x4000)
#define PA_PS                              (0x8000)


/*====================================================*/
struct __RF_PORT2_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_EN_BY_TX                           : 1;
    WORD BITFLD_EN_BY_RX                           : 1;
    WORD BITFLD_SSI                                : 1;
    WORD BITFLD_PA_PS                              : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define EN_BY_TX                           (0x1000)
#define EN_BY_RX                           (0x2000)
#define SSI                                (0x4000)
#define PA_PS                              (0x8000)


/*====================================================*/
struct __RF_PORT3_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_EN_BY_TX                           : 1;
    WORD BITFLD_EN_BY_RX                           : 1;
    WORD BITFLD_SSI                                : 1;
    WORD BITFLD_PA_PS                              : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define EN_BY_TX                           (0x1000)
#define EN_BY_RX                           (0x2000)
#define SSI                                (0x4000)
#define PA_PS                              (0x8000)


/*====================================================*/
struct __RF_PORT4_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_EN_BY_TX                           : 1;
    WORD BITFLD_EN_BY_RX                           : 1;
    WORD BITFLD_SSI                                : 1;
    WORD BITFLD_PA_PS                              : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define EN_BY_TX                           (0x1000)
#define EN_BY_RX                           (0x2000)
#define SSI                                (0x4000)
#define PA_PS                              (0x8000)


/*====================================================*/
struct __RF_PLLCLOSED_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
    WORD BITFLD_SSI                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)
#define SSI                                (0x4000)


/*====================================================*/
struct __RF_SYNTH_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)


/*====================================================*/
struct __RF_BIAS_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)


/*====================================================*/
struct __RF_RSSIPH_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)


/*====================================================*/
struct __RF_DEM_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
    WORD BITFLD_SSI                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)
#define SSI                                (0x4000)


/*====================================================*/
struct __RF_ADC_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
    WORD BITFLD_SSI                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)
#define SSI                                (0x4000)


/*====================================================*/
struct __RF_IF_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
    WORD BITFLD_SSI                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)
#define SSI                                (0x4000)


/*====================================================*/
struct __RF_LNAMIX_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
    WORD BITFLD_SSI                                : 1;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)
#define SSI                                (0x4000)


/*====================================================*/
struct __RF_PADR_DCF_REG
/*====================================================*/
{
    WORD BITFLD_SET_OFFSET                         : 6;
    WORD BITFLD_RESET_OFFSET                       : 6;
    WORD BITFLD_DIS                                : 1;
    WORD BITFLD_RX_SENSITIVE                       : 1;
    WORD BITFLD_PADR_SSI                           : 2;
};

#define SET_OFFSET                         (0x003F)
#define RESET_OFFSET                       (0x0FC0)
#define DIS                                (0x1000)
#define RX_SENSITIVE                       (0x2000)
#define PADR_SSI                           (0xC000)


/*====================================================*/
struct __RF_FAD_WINDOW_DCF_REG
/*====================================================*/
{
    WORD BITFLD_FAD_SWAP                           : 6;
    WORD BITFLD_FAD_DECIDE                         : 6;
};

#define FAD_SWAP                           (0x003F)
#define FAD_DECIDE                         (0x0FC0)


/*====================================================*/
struct __RF_RFCAL_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_RFCAL_STEPS                        : 3;
    WORD BITFLD_RFCAL_MODE                         : 2;
    WORD BITFLD_RFCAL_PERIOD                       : 2;
};

#define RFCAL_STEPS                        (0x0007)
#define RFCAL_MODE                         (0x0018)
#define RFCAL_PERIOD                       (0x0060)


/*====================================================*/
struct __RF_DEM_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_DEM_INVERT                         : 1;
    WORD BITFLD_SLICE_EN                           : 1;
    WORD BITFLD_SLICE_EARLY                        : 1;
    WORD BITFLD_SLICE_VAL                          : 8;
};

#define DEM_INVERT                         (0x0001)
#define SLICE_EN                           (0x0002)
#define SLICE_EARLY                        (0x0080)
#define SLICE_VAL                          (0xFF00)


/*====================================================*/
struct __RF_PREAMBLE_REG
/*====================================================*/
{
    WORD BITFLD_PREAMBLE_DEL                       : 6;
    WORD BITFLD_AFC_VAL                            : 2;
    WORD BITFLD_AFC_EN                             : 1;
    WORD BITFLD_AFC_SETTLE_DEL                     : 2;
    WORD BITFLD_PREAMBLE_SYM                       : 2;
    WORD BITFLD_GATE_DATA                          : 1;
    WORD BITFLD_HALF_BIT_RATE                      : 1;
    WORD BITFLD_SYNC_RX_DATA                       : 1;
};

#define PREAMBLE_DEL                       (0x003F)
#define AFC_VAL                            (0x00C0)
#define AFC_EN                             (0x0100)
#define AFC_SETTLE_DEL                     (0x0600)
#define PREAMBLE_SYM                       (0x1800)
#define GATE_DATA                          (0x2000)
#define HALF_BIT_RATE                      (0x4000)
#define SYNC_RX_DATA                       (0x8000)


/*====================================================*/
struct __RF_SLICER_RESULT_REG
/*====================================================*/
{
    WORD BITFLD_AFC_VAL                            : 2;
    WORD BITFLD_SLICE_VAL                          : 8;
};

#define AFC_VAL                            (0x00C0)
#define SLICE_VAL                          (0xFF00)


/*====================================================*/
struct __RF_RSSI_REG
/*====================================================*/
{
    WORD BITFLD_RFCAL_CAP                          : 6;
    WORD                                           : 2;
    WORD BITFLD_RSSI_VAL                           : 6;
    WORD BITFLD_FAD_CHOICE                         : 1;
};

#define RFCAL_CAP                          (0x003F)
#define RSSI_VAL                           (0x3F00)
#define FAD_CHOICE                         (0x4000)


/*====================================================*/
struct __RF_PORT_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_PORT1_INV                          : 1;
    WORD BITFLD_PORT2_INV                          : 1;
    WORD BITFLD_PORT3_INV                          : 1;
    WORD BITFLD_PORT4_INV                          : 1;
    WORD BITFLD_ANT_INACTIVE_VAL                   : 1;
};

#define PORT1_INV                          (0x0001)
#define PORT2_INV                          (0x0002)
#define PORT3_INV                          (0x0004)
#define PORT4_INV                          (0x0008)
#define ANT_INACTIVE_VAL                   (0x0010)


/*====================================================*/
struct __RF_PAD_IO_REG
/*====================================================*/
{
    WORD BITFLD_P0_OE                              : 1;
    WORD BITFLD_P0N_OE                             : 1;
    WORD BITFLD_P1_OE                              : 1;
    WORD BITFLD_P2_OE                              : 1;
    WORD BITFLD_P3_OE                              : 1;
    WORD BITFLD_P4_OE                              : 1;
    WORD BITFLD_P0_IE                              : 1;
    WORD BITFLD_PAD_OE                             : 6;
};

#define P0_OE                              (0x0001)
#define P0N_OE                             (0x0002)
#define P1_OE                              (0x0004)
#define P2_OE                              (0x0008)
#define P3_OE                              (0x0010)
#define P4_OE                              (0x0020)
#define P0_IE                              (0x0040)
#define PAD_OE                             (0x003F)


/*====================================================*/
struct __RF_TRIM_CTRL_REG
/*====================================================*/
{
    WORD                                           : 4;
    WORD BITFLD_PADR_ITRIM                         : 2;
};

#define PADR_ITRIM                         (0x0030)


/*====================================================*/
struct __RF_PLL_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_CH_ZERO                            : 13;
    WORD BITFLD_SGN_NEG                            : 1;
    WORD BITFLD_CS_MO                              : 2;
};

#define CH_ZERO                            (0x1FFF)
#define SGN_NEG                            (0x2000)
#define CS_MO                              (0xC000)


/*====================================================*/
struct __RF_PLL_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_GAUSS_GAIN                         : 8;
    WORD BITFLD_MODINDEX                           : 6;
    WORD BITFLD_MODE20M                            : 1;
    WORD BITFLD_MODE58                             : 1;
};

#define GAUSS_GAIN                         (0x00FF)
#define MODINDEX                           (0x3F00)
#define MODE20M                            (0x4000)
#define MODE58                             (0x8000)


/*====================================================*/
struct __RF_PLL_CTRL3_REG
/*====================================================*/
{
    WORD BITFLD_FASTLOCK_PERIOD                    : 10;
    WORD BITFLD_FASTLOCK                           : 1;
    WORD BITFLD_LOCK_TIME                          : 2;
};

#define FASTLOCK_PERIOD                    (0x03FF)
#define FASTLOCK                           (0x0400)
#define LOCK_TIME                          (0x1800)


/*====================================================*/
struct __RF_PLL_CTRL4_REG
/*====================================================*/
{
    WORD BITFLD_MODCAL_PERIOD                      : 8;
    WORD BITFLD_MODCAL_TRIG                        : 1;
    WORD BITFLD_SD1_ORDER                          : 2;
    WORD BITFLD_SD2_ORDER                          : 2;
    WORD BITFLD_KMOD_ALPHA                         : 3;
};

#define MODCAL_PERIOD                      (0x00FF)
#define MODCAL_TRIG                        (0x0100)
#define SD1_ORDER                          (0x0600)
#define SD2_ORDER                          (0x1800)
#define KMOD_ALPHA                         (0xE000)


/*====================================================*/
struct __TEST_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_FEEDBACK                           : 1;
    WORD                                           : 1;
    WORD BITFLD_SHOW_HCLK                          : 1;
    WORD BITFLD_SHOW_CLOCKSWITCHING                : 1;
    WORD BITFLD_SHOW_PCLK                          : 1;
    WORD BITFLD_SHOW_HCLK_DRA                      : 1;
    WORD BITFLD_FLAG                               : 1;
    WORD BITFLD_SHOW_RINGING                       : 1;
    WORD BITFLD_XTAL_OSC_TEST                      : 1;
    WORD BITFLD_SPU_LOCAL_LOOP                     : 1;
    WORD BITFLD_SHOW_HREADY                        : 1;
    WORD BITFLD_SHOW_bckout                        : 1;
    WORD BITFLD_PCTEST                             : 1;
    WORD BITFLD_REMAP_DSPROM                       : 1;
    WORD BITFLD_SHOW_DPLL                          : 1;
    WORD BITFLD_RCK_CONTROL                        : 1;
};

#define FEEDBACK                           (0x0001)
#define SHOW_HCLK                          (0x0004)
#define SHOW_CLOCKSWITCHING                (0x0008)
#define SHOW_PCLK                          (0x0010)
#define SHOW_HCLK_DRA                      (0x0020)
#define FLAG                               (0x0040)
#define SHOW_RINGING                       (0x0080)
#define XTAL_OSC_TEST                      (0x0100)
#define SPU_LOCAL_LOOP                     (0x0200)
#define SHOW_HREADY                        (0x0400)
#define SHOW_bckout                        (0x0800)
#define PCTEST                             (0x1000)
#define REMAP_DSPROM                       (0x2000)
#define SHOW_DPLL                          (0x4000)
#define RCK_CONTROL                        (0x8000)


/*====================================================*/
struct __TEST_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_RIPPLE_COUNTER                     : 1;
    WORD                                           : 2;
    WORD BITFLD_SHOW_ADC_COMP                      : 1;
    WORD BITFLD_SHOW_LSB_SOC                       : 1;
    WORD BITFLD_POWER_TEST_OUT                     : 1;
    WORD BITFLD_POWER                              : 6;
    WORD BITFLD_XTAL_AMPL_TEST_140mV              : 1;
    WORD BITFLD_DCDC_GAIN                          : 2;
    WORD BITFLD_DCDC_RC                            : 1;
};

#define RIPPLE_COUNTER                     (0x0001)
#define SHOW_ADC_COMP                      (0x0008)
#define SHOW_LSB_SOC                       (0x0010)
#define POWER_TEST_OUT                     (0x0020)
#define POWER                              (0x0FC0)
#define XTAL_AMPL_TEST_140mV               (0x1000)
#define DCDC_GAIN                          (0x6000)
#define DCDC_RC                            (0x8000)


/*====================================================*/
struct __RF_SYNTH_CTRL1_REG
/*====================================================*/
{
    WORD BITFLD_VCO_EXTERNAL                       : 1;
    WORD BITFLD_VCO_VTUNE_MID                      : 1;
    WORD BITFLD_VCO_MOD_EN                         : 1;
    WORD BITFLD_VCO_CUR_SET                        : 1;
    WORD BITFLD_LF_VCO_DIS                         : 1;
    WORD BITFLD_VCO_TUNE_EXT                       : 1;
    WORD                                           : 1;
    WORD BITFLD_DIV2_EN_ALL                        : 1;
    WORD BITFLD_DIV2_CUR_SET                       : 3;
    WORD                                           : 1;
    WORD BITFLD_PFD_SLOW_RESET                     : 1;
    WORD BITFLD_PFD_POLARITY                       : 1;
    WORD BITFLD_GDAC_VCO_DIS                       : 1;
    WORD BITFLD_VCO_MOD_EXT                        : 1;
};

#define VCO_EXTERNAL                       (0x0001)
#define VCO_VTUNE_MID                      (0x0002)
#define VCO_MOD_EN                         (0x0004)
#define VCO_CUR_SET                        (0x0008)
#define LF_VCO_DIS                         (0x0010)
#define VCO_TUNE_EXT                       (0x0020)
#define DIV2_EN_ALL                        (0x0080)
#define DIV2_CUR_SET                       (0x0700)
#define PFD_SLOW_RESET                     (0x1000)
#define PFD_POLARITY                       (0x2000)
#define GDAC_VCO_DIS                       (0x4000)
#define VCO_MOD_EXT                        (0x8000)


/*====================================================*/
struct __RF_SYNTH_CTRL2_REG
/*====================================================*/
{
    WORD BITFLD_VCO_BIAS_SWITCH                    : 2;
    WORD                                           : 5;
    WORD BITFLD_LF_BW_TRIM                         : 3;
    WORD BITFLD_CP_DRIVE                           : 2;
    WORD BITFLD_DIV2_IR_TRIM                       : 4;
};

#define VCO_BIAS_SWITCH                    (0x0003)
#define LF_BW_TRIM                         (0x0380)
#define CP_DRIVE                           (0x0C00)
#define DIV2_IR_TRIM                       (0xF000)


/*====================================================*/
struct __RF_AGC_REG
/*====================================================*/
{
    WORD BITFLD_AGC12_EXTERN                       : 1;
    WORD                                           : 1;
    WORD BITFLD_AGC_FREEZE                         : 1;
    WORD BITFLD_AGC_PD_RESET                       : 1;
    WORD BITFLD_GAIN_AGC1                          : 4;
    WORD BITFLD_GAIN_AGC2                          : 3;
};

#define AGC12_EXTERN                       (0x0001)
#define AGC_FREEZE                         (0x0004)
#define AGC_PD_RESET                       (0x0008)
#define GAIN_AGC1                          (0x00F0)
#define GAIN_AGC2                          (0x0700)


/*====================================================*/
struct __RF_AGC_RESULT_REG
/*====================================================*/
{
    WORD BITFLD_GAIN_AGC1                          : 4;
    WORD BITFLD_GAIN_AGC2                          : 3;
};

#define GAIN_AGC1                          (0x00F0)
#define GAIN_AGC2                          (0x0700)


/*====================================================*/
struct __RF_AGC12_TH_REG
/*====================================================*/
{
    WORD BITFLD_AGC12_TH_LOW                       : 7;
    WORD BITFLD_AGC12_TH_HIGH                      : 7;
};

#define AGC12_TH_LOW                       (0x007F)
#define AGC12_TH_HIGH                      (0x3F80)


/*====================================================*/
struct __RF_AGC12_ALPHA_REG
/*====================================================*/
{
    WORD BITFLD_AGC12_ALPHA                        : 6;
};

#define AGC12_ALPHA                        (0x003F)


/*====================================================*/
struct __RF_DC_OFFSET_REG
/*====================================================*/
{
    WORD BITFLD_DC_OFFSET                          : 6;
    WORD                                           : 6;
    WORD BITFLD_DC_OFFSET_EXTERN                   : 1;
};

#define DC_OFFSET                          (0x003F)
#define DC_OFFSET_EXTERN                   (0x1000)


/*====================================================*/
struct __RF_DC_OFFSET12_REG
/*====================================================*/
{
    WORD BITFLD_DC_OFFSET_GAIN1                    : 6;
    WORD BITFLD_DC_OFFSET_GAIN2                    : 6;
};

#define DC_OFFSET_GAIN1                    (0x003F)
#define DC_OFFSET_GAIN2                    (0x0FC0)


/*====================================================*/
struct __RF_DC_OFFSET34_REG
/*====================================================*/
{
    WORD BITFLD_DC_OFFSET_GAIN3                    : 6;
    WORD BITFLD_DC_OFFSET_GAIN4                    : 6;
};

#define DC_OFFSET_GAIN3                    (0x003F)
#define DC_OFFSET_GAIN4                    (0x0FC0)


/*====================================================*/
struct __RF_IQ_DC_OFFSET_REG
/*====================================================*/
{
    WORD BITFLD_DC_OFFSET_GAIN5                    : 6;
    WORD BITFLD_IF_IOS_CAL                         : 4;
    WORD BITFLD_IF_QOS_CAL                         : 4;
    WORD BITFLD_IQOS_CAL_DIS                       : 1;
};

#define DC_OFFSET_GAIN5                    (0x003F)
#define IF_IOS_CAL                         (0x03C0)
#define IF_QOS_CAL                         (0x3C00)
#define IQOS_CAL_DIS                       (0x4000)


/*====================================================*/
struct __RF_IF_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_IF_CAL_CAP                         : 6;
    WORD BITFLD_EXTERN_IF_CAL_CAP                  : 1;
    WORD BITFLD_IF_CUR_SET                         : 2;
    WORD BITFLD_IF_MUTE                            : 1;
    WORD BITFLD_IF_CAPA_BIAS                       : 2;
    WORD BITFLD_IF_TEST_SELECT                     : 4;
};

#define IF_CAL_CAP                         (0x003F)
#define EXTERN_IF_CAL_CAP                  (0x0040)
#define IF_CUR_SET                         (0x0180)
#define IF_MUTE                            (0x0200)
#define IF_CAPA_BIAS                       (0x0C00)
#define IF_TEST_SELECT                     (0xF000)


/*====================================================*/
struct __RF_IFCAL_RESULT_REG
/*====================================================*/
{
    WORD BITFLD_IF_CAL_CAP                         : 6;
    WORD BITFLD_IF_IOS_CAL                         : 4;
    WORD BITFLD_IF_QOS_CAL                         : 4;
};

#define IF_CAL_CAP                         (0x003F)
#define IF_IOS_CAL                         (0x03C0)
#define IF_QOS_CAL                         (0x3C00)


/*====================================================*/
struct __RF_REF_OSC_REG
/*====================================================*/
{
    WORD BITFLD_CNT_RO                             : 6;
    WORD BITFLD_CNT_CLK                            : 9;
};

#define CNT_RO                             (0x003F)
#define CNT_CLK                            (0x7FC0)


/*====================================================*/
struct __RF_ADC_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_ADC_CUR_SET                        : 3;
    WORD BITFLD_ADC_VCO_HI_RANGE                   : 1;
    WORD BITFLD_ADC_VTUNE_PIN                      : 1;
    WORD BITFLD_ADC_DIV16_TEST                     : 1;
    WORD BITFLD_ADC_NCLK_PIN                       : 1;
    WORD BITFLD_ADC_USE_EXT_CLK                    : 1;
    WORD BITFLD_ADC_VCO_ALW_EN                     : 1;
    WORD BITFLD_ADC_CLOOP_ALW_EN                   : 1;
};

#define ADC_CUR_SET                        (0x0007)
#define ADC_VCO_HI_RANGE                   (0x0008)
#define ADC_VTUNE_PIN                      (0x0010)
#define ADC_DIV16_TEST                     (0x0020)
#define ADC_NCLK_PIN                       (0x0040)
#define ADC_USE_EXT_CLK                    (0x0080)
#define ADC_VCO_ALW_EN                     (0x0100)
#define ADC_CLOOP_ALW_EN                   (0x0200)


/*====================================================*/
struct __RF_RFIO_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_PADR_CSHORT                        : 3;
    WORD BITFLD_PADR_CUR_SET                       : 2;
    WORD                                           : 2;
    WORD BITFLD_PADR_ATTN                          : 1;
    WORD                                           : 1;
    WORD BITFLD_LNA_LOWGAIN0                       : 1;
    WORD BITFLD_LNA_LOWGAIN1                       : 1;
    WORD BITFLD_IRM_GAIN                           : 2;
};

#define PADR_CSHORT                        (0x0007)
#define PADR_CUR_SET                       (0x0018)
#define PADR_ATTN                          (0x0080)
#define LNA_LOWGAIN0                       (0x0200)
#define LNA_LOWGAIN1                       (0x0400)
#define IRM_GAIN                           (0x1800)


/*====================================================*/
struct __RF_BIAS_CTRL_REG
/*====================================================*/
{
    WORD BITFLD_FILT_ALW_DIS                       : 1;
    WORD BITFLD_BREF_HIGH_CUR                      : 1;
    WORD BITFLD_BIAS_REF_BGR                       : 1;
    WORD BITFLD_EXT_CUR_CONT                       : 1;
    WORD BITFLD_BIAS_CONT                          : 1;
    WORD BITFLD_LDO_CONT                           : 1;
    WORD BITFLD_LDO_ALW_EN                         : 1;
};

#define FILT_ALW_DIS                       (0x0001)
#define BREF_HIGH_CUR                      (0x0002)
#define BIAS_REF_BGR                       (0x0004)
#define EXT_CUR_CONT                       (0x0008)
#define BIAS_CONT                          (0x0010)
#define LDO_CONT                           (0x0020)
#define LDO_ALW_EN                         (0x0040)


/*====================================================*/
struct __RF_TEST_MODE_REG
/*====================================================*/
{
    WORD BITFLD_TGATE_MIXER_IF                     : 1;
    WORD BITFLD_TGATE_IF_PINS                      : 1;
    WORD BITFLD_ADC_TST                            : 1;
    WORD BITFLD_RO_TO_PINS                         : 1;
    WORD BITFLD_PLL_TST_MODE                       : 3;
    WORD BITFLD_DEM_OUT_TST                        : 1;
    WORD BITFLD_TEST_DRIFT                         : 1;
    WORD BITFLD_DEM_RETRIGGER                      : 1;
    WORD BITFLD_SLICE_MON                          : 1;
    WORD BITFLD_TGATE_MIXER_PINS                   : 1;
};

#define TGATE_MIXER_IF                     (0x0001)
#define TGATE_IF_PINS                      (0x0002)
#define ADC_TST                            (0x0004)
#define RO_TO_PINS                         (0x0008)
#define PLL_TST_MODE                       (0x0070)
#define DEM_OUT_TST                        (0x0080)
#define TEST_DRIFT                         (0x0100)
#define DEM_RETRIGGER                      (0x0200)
#define SLICE_MON                          (0x0400)
#define TGATE_MIXER_PINS                   (0x0800)


/*====================================================*/
struct __RF_LDO_TEST_REG
/*====================================================*/
{
    WORD BITFLD_LDO_SEL                            : 4;
    WORD BITFLD_LDO_PARAM_SEL                      : 2;
};

#define LDO_SEL                            (0x000F)
#define LDO_PARAM_SEL                      (0x0030)


/*====================================================*/
struct __RF_PLL_CTRL5_REG
/*====================================================*/
{
    WORD BITFLD_MOD_VAL                            : 10;
    WORD BITFLD_MOD_VAL_EN                         : 1;
    WORD BITFLD_DITH_PERIOD                        : 5;
};

#define MOD_VAL                            (0x03FF)
#define MOD_VAL_EN                         (0x0400)
#define DITH_PERIOD                        (0xF800)


/*====================================================*/
struct __RF_PLL_CTRL6_REG
/*====================================================*/
{
    WORD BITFLD_NGAUSS                             : 2;
    WORD BITFLD_ANA_DELAY                          : 2;
    WORD BITFLD_DIG_DELAY                          : 2;
};

#define NGAUSS                             (0x0003)
#define ANA_DELAY                          (0x1800)
#define DIG_DELAY                          (0x6000)


/*====================================================*/
struct __RF_GAUSS_GAIN_MSB_REG
/*====================================================*/
{
    WORD BITFLD_GAUSS_GAIN_MSB                     : 11;
};

#define GAUSS_GAIN_MSB                     (0x07FF)


/*====================================================*/
struct __RF_INTERNALPA_REG
/*====================================================*/
{
    WORD BITFLD_TEST0                              : 1;
    WORD BITFLD_TEST1                              : 1;
    WORD BITFLD_TEST2                              : 1;
    WORD BITFLD_TEST3                              : 1;
    WORD BITFLD_TEST4                              : 1;
    WORD BITFLD_TEST5                              : 1;
    WORD BITFLD_TEST6                              : 1;
    WORD BITFLD_TEST7                              : 1;
    WORD BITFLD_TEST8                              : 1;
    WORD BITFLD_TEST9                              : 1;
    WORD BITFLD_TEST10                             : 1;
    WORD BITFLD_TEST11                             : 1;
    WORD BITFLD_TEST12                             : 1;
    WORD BITFLD_TEST13                             : 1;
    WORD BITFLD_TEST14                             : 1;
    WORD BITFLD_TEST15                             : 1;
};

#define TEST0                              (0x0001)
#define TEST1                              (0x0002)
#define TEST2                              (0x0004)
#define TEST3                              (0x0008)
#define TEST4                              (0x0010)
#define TEST5                              (0x0020)
#define TEST6                              (0x0040)
#define TEST7                              (0x0080)
#define TEST8                              (0x0100)
#define TEST9                              (0x0200)
#define TEST10                             (0x0400)
#define TEST11                             (0x0800)
#define TEST12                             (0x1000)
#define TEST13                             (0x2000)
#define TEST14                             (0x4000)
#define TEST15                             (0x8000)


/*====================================================*/
struct __RF_PA_RESERVED1_REG
/*====================================================*/
{
    WORD BITFLD_TEST0                              : 1;
    WORD BITFLD_TEST1                              : 1;
    WORD BITFLD_TEST2                              : 1;
    WORD BITFLD_TEST3                              : 1;
    WORD BITFLD_TEST4                              : 1;
    WORD BITFLD_TEST5                              : 1;
    WORD BITFLD_TEST6                              : 1;
    WORD BITFLD_TEST7                              : 1;
    WORD BITFLD_TEST8                              : 1;
    WORD BITFLD_TEST9                              : 1;
    WORD BITFLD_TEST10                             : 1;
    WORD BITFLD_TEST11                             : 1;
    WORD BITFLD_TEST12                             : 1;
    WORD BITFLD_TEST13                             : 1;
    WORD BITFLD_TEST14                             : 1;
    WORD BITFLD_TEST15                             : 1;
};

#define TEST0                              (0x0001)
#define TEST1                              (0x0002)
#define TEST2                              (0x0004)
#define TEST3                              (0x0008)
#define TEST4                              (0x0010)
#define TEST5                              (0x0020)
#define TEST6                              (0x0040)
#define TEST7                              (0x0080)
#define TEST8                              (0x0100)
#define TEST9                              (0x0200)
#define TEST10                             (0x0400)
#define TEST11                             (0x0800)
#define TEST12                             (0x1000)
#define TEST13                             (0x2000)
#define TEST14                             (0x4000)
#define TEST15                             (0x8000)


/*====================================================*/
struct __RF_PA_RESERVED2_REG
/*====================================================*/
{
    WORD BITFLD_TEST0                              : 1;
    WORD BITFLD_TEST1                              : 1;
    WORD BITFLD_TEST2                              : 1;
    WORD BITFLD_TEST3                              : 1;
    WORD BITFLD_TEST4                              : 1;
    WORD BITFLD_TEST5                              : 1;
    WORD BITFLD_TEST6                              : 1;
    WORD BITFLD_TEST7                              : 1;
    WORD BITFLD_TEST8                              : 1;
    WORD BITFLD_TEST9                              : 1;
    WORD BITFLD_TEST10                             : 1;
    WORD BITFLD_TEST11                             : 1;
    WORD BITFLD_TEST12                             : 1;
    WORD BITFLD_TEST13                             : 1;
    WORD BITFLD_TEST14                             : 1;
    WORD BITFLD_TEST15                             : 1;
};

#define TEST0                              (0x0001)
#define TEST1                              (0x0002)
#define TEST2                              (0x0004)
#define TEST3                              (0x0008)
#define TEST4                              (0x0010)
#define TEST5                              (0x0020)
#define TEST6                              (0x0040)
#define TEST7                              (0x0080)
#define TEST8                              (0x0100)
#define TEST9                              (0x0200)
#define TEST10                             (0x0400)
#define TEST11                             (0x0800)
#define TEST12                             (0x1000)
#define TEST13                             (0x2000)
#define TEST14                             (0x4000)
#define TEST15                             (0x8000)





/*
 * Missing bit field definitions for GPIO registers
 * This is not done in the datasheet to avoid very long tables
 * that contain no extra information.
 */


#define __GPIO_DATA_REG        __GPIO_BITFIELD_REG
#define __GPIO_DIR_REG         __GPIO_BITFIELD_REG
#define __GPIO_PUPD_REG        __GPIO_BITFIELD_REG
#define __GPIO_INT_EN_REG      __GPIO_BITFIELD_REG

/*====================================================*/
struct __GPIO_BITFIELD_REG
/*====================================================*/
{
    WORD BITFLD_GPIO_0                        : 1;
    WORD BITFLD_GPIO_1                        : 1;
    WORD BITFLD_GPIO_2                        : 1;
    WORD BITFLD_GPIO_3                        : 1;
    WORD BITFLD_GPIO_4                        : 1;
    WORD BITFLD_GPIO_5                        : 1;
    WORD BITFLD_GPIO_6                        : 1;
    WORD BITFLD_GPIO_7                        : 1;
    WORD BITFLD_GPIO_8                        : 1;
    WORD BITFLD_GPIO_9                        : 1;
    WORD BITFLD_GPIO_10                       : 1;
    WORD BITFLD_GPIO_11                       : 1;
    WORD BITFLD_GPIO_12                       : 1;
    WORD BITFLD_GPIO_13                       : 1;
    WORD BITFLD_GPIO_14                       : 1;
    WORD BITFLD_GPIO_15                       : 1;
};

#define GPIO_0                        (0x0001)
#define GPIO_1                        (0x0002)
#define GPIO_2                        (0x0004)
#define GPIO_3                        (0x0008)
#define GPIO_4                        (0x0010)
#define GPIO_5                        (0x0020)
#define GPIO_6                        (0x0040)
#define GPIO_7                        (0x0080)
#define GPIO_8                        (0x0100)
#define GPIO_9                        (0x0200)
#define GPIO_10                       (0x0400)
#define GPIO_11                       (0x0800)
#define GPIO_12                       (0x1000)
#define GPIO_13                       (0x2000)
#define GPIO_14                       (0x4000)
#define GPIO_15                       (0x8000)

#define SHIF(a) ((a)&0x0001?0: (a)&0x0002?1: (a)&0x0004?2: (a)&0x0008?3:\
                 (a)&0x0010?4: (a)&0x0020?5: (a)&0x0040?6: (a)&0x0080?7:\
                 (a)&0x0100?8: (a)&0x0200?9: (a)&0x0400?10:(a)&0x0800?11:\
                 (a)&0x1000?12:(a)&0x2000?13:(a)&0x4000?14: 15)

#define DSHIF(a)((a)&0x00000001?0: (a)&0x00000002?1: (a)&0x00000004?2: (a)&0x00000008?3:\
                 (a)&0x00000010?4: (a)&0x00000020?5: (a)&0x00000040?6: (a)&0x00000080?7:\
                 (a)&0x00000100?8: (a)&0x00000200?9: (a)&0x00000400?10:(a)&0x00000800?11:\
                 (a)&0x00001000?12:(a)&0x00002000?13:(a)&0x00004000?14:(a)&0x00008000?15:\
                 (a)&0x00010000?16:(a)&0x00020000?17:(a)&0x00040000?18:(a)&0x00080000?19:\
                 (a)&0x00100000?20:(a)&0x00200000?21:(a)&0x00400000?22:(a)&0x00800000?23:\
                 (a)&0x01000000?24:(a)&0x02000000?25:(a)&0x04000000?26:(a)&0x08000000?27:\
                 (a)&0x10000000?28:(a)&0x20000000?29:(a)&0x40000000?30: 31)


extern signed char DECT_Channel_offset;

#define DSP_MAIN_REL                       (0xFF00)
extern void __enable_interrupt(void);
extern void __disable_interrupt(void);
extern void __set_PSR_I_bit(void);


#endif
