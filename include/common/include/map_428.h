#ifndef __MAP_428_H
#define __MAP_428_H

#include "rtxdef.h"

#define SPI_INT_PEND             0x0040

#define SCL_VAL  (1<<2)
#define SDA_VAL  (1<<3)
#define ACKn     (1<<1)

#define RESET                              {DEBUG_REG |= SW_RESET;}
#define ACCESS_INT_PEND                    BIT0
#define ACH0_PD                            (0x0004)
#define ACH1_PD                            (0x0008)
#define ACH2_PD                            (0x0010)
#define ACH3_PD                            (0x0020)
#define ACS1_EN                            BIT1
#define ACS2_EN                            BIT3
#define ADC0                               0x00 /* used in AdCtrlRegType*/
#define ADC0_SCALER_EN                     BIT2
#define ADC1                               BIT3 /* used in AdCtrlRegType*/
#define ADC2                               BIT4 /* used in AdCtrlRegType*/
#define ADC_IN_3_0                         (0x0078)
#define ADC_SEL0                           0x00
#define ADC_SEL1                           BIT3
#define ADC_SEL2                           BIT4
#define ADC_SEL_DAC                        (BIT3|BIT4|BIT5)
#define ADC_START                          BIT0
#define ADDA_COFF                          (0x0400)
#define ADPCM_PD                           (0x4000)
#define AD_DITH_OFF                        (0x0008)
#define AD_LPF_ADJ                         (0x0020)
#define AD_PD                              (0x0001)
#define AGC_PD                             (0x0001)
#define AGND_INIT                          (0x0004)
#define AGND_PD                            (0x0008)
#define AMP1V5_PD                          (0x0020)
#define BANDGAP                            (0x000F)
#define BAUDRATE_115200                    (BIT2|BIT3)
#define BAUDRATE_19200                     BIT2
#define BAUDRATE_57600                     BIT3
#define BAUDRATE_9600                      0x00
#define BG_CUR                             (0x01C0)
#define BG_VOLT                            (0x0030)
#define BIAS_PD                            (0x0080)
#define BMCCLOCKPRC                        BIT6 /*BMC control pattern to select clock prescaler*/
#define BMCRESET                           BIT7 /*BMC control pattern to reset*/
#define BUZATT                             (0x0180)
#define BUZMODE                            (0x0200)
#define CH0_PD                             (0x0100)
#define CH1_PD                             (0x0080)
#define CH23_PD                            (0x0040)
#define CHARGE_STOP                        (0x0060)
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
#define CLEAR_UART_RI_FLAG                 P0_CLEAR_RX_INT_REG = 0
#define CLEAR_UART_TI_FLAG                 P0_CLEAR_TX_INT_REG = 0
#define CLK100_EDGE                        BIT0
#define CLK100_EN                          (0x0080)
#define CLK100_INT_PEND                    BIT9
#define CLK100_NEG                         BIT1
#define CLK100_POS                         BIT2
#define CLK100_SRC                         BIT3
#define CLKSRC_144KHZ                      0x0
#define CLKSRC_ECZ                         0x8
#define CLKSRC_ECZ2                        0xC
#define CLKSRC_METERING                    0x4
#define CLK_CTRL0                          BIT2
#define CLK_CTRL1                          BIT3
#define CLK_CTRL_CP_ON                     BIT1
#define CLK_CTRL_LPF_SEL                   BIT5
#define CLK_CTRL_PLL_SCK                   BIT3
#define CLK_CTRL_VCO_ON                    BIT4
#define CLK_CTRL_VDDRF_SEL                 BIT6
#define CLK_CTRL_XDIV                      BIT2
#define CLK_DIV8                           (0x0040)
#define CLK_DIV_0                          0x00
#define CLK_DIV_1                          0x10
#define CLK_DIV_10                         0xA0
#define CLK_DIV_11                         0xB0
#define CLK_DIV_12                         0xC0
#define CLK_DIV_13                         0xD0
#define CLK_DIV_14                         0xE0
#define CLK_DIV_15                         0xF0
#define CLK_DIV_2                          0x20
#define CLK_DIV_3                          0x30
#define CLK_DIV_4                          0x40
#define CLK_DIV_5                          0x50
#define CLK_DIV_6                          0x60
#define CLK_DIV_7                          0x70
#define CLK_DIV_8                          0x80
#define CLK_DIV_9                          0x90
#define CLK_DIV_RATIO_1                    0x01
#define CLK_DIV_RATIO_2                    0x02
#define CLK_DIV_RATIO_3                    0x03
#define CLK_DIV_RATIO_4                    0x04
#define CLK_DIV_RATIO_5                    0x05
#define CLK_DIV_RATIO_6                    0x06
#define CLK_DIV_RATIO_7                    0x07
#define CLK_DIV_RATIO_8                    0x00
#define CLR_ACCESS_INT_PENDING             0x0001
#define CLR_CLK100_INT_PENDING             0x0200
#define CLR_CT_INT_PENDING                 0x0008
#define CLR_DIP_INT_PENDING                0x0400
#define CLR_DSP_INT_PENDING                0x0800
#define CLR_KEYB_INT_PENDING               0x0002
#define CLR_P10_INT_PENDING                0x0004
#define CLR_SPI_INT_PENDING                0x0040
#define CLR_TIM0_INT_PENDING               0x0080
#define CLR_TIM1_INT_PENDING               0x0100
#define CLR_UART_RX_INT_PENDING            0x0010
#define CLR_UART_TI_INT_PENDING            0x0020
#define CL_SELECT_BIT                      0x08
#define COARSE_ADJ_BIT                     0x05
#define CODEC_DIV_CLK_DIV                  (BIT0|BIT1|BIT2|BIT3|BIT4|BIT5)
#define CODEC_DIV_CLK_SEL_PLL              BIT7
#define CODEC_LSR_LSRATT                   (BIT11|BIT12|BIT13)
#define CODEC_LSR_LSREN_SE                 BIT9
#define CODEC_LSR_LSRHS_MODE               (BIT6|BIT7)
#define CODEC_LSR_LSRHS_PD                 BIT8
#define CODEC_LSR_LSRN_MODE                (BIT3|BIT4)
#define CODEC_LSR_LSRN_PD                  BIT5
#define CODEC_LSR_LSRP_MODE                (BIT0|BIT1)
#define CODEC_LSR_LSRP_PD                  BIT2
#define CODEC_LSR_LSR_GND_PD               BIT10
#define CODEC_MIC_DSP_CTRL                 BIT10
#define CODEC_MIC_MIC_GAIN                 (BIT4|BIT5|BIT6|BIT7)
#define CODEC_MIC_MIC_MODE                 (BIT0|BIT1)
#define CODEC_MIC_MIC_MUTE                 BIT3
#define CODEC_MIC_MIC_PD                   BIT2
#define CODEC_MIC_OFFCOM_ON                BIT9
#define CODEC_MIC_OFFCOM_SG                BIT8
#define CODEC_TONE_MTR_CID_PD              BIT8
#define CODEC_TONE_MTR_CMP_PD              BIT1
#define CODEC_TONE_MTR_FILT                BIT3
#define CODEC_TONE_MTR_FILT_PD             BIT2
#define CODEC_TONE_MTR_GAIN                (BIT5|BIT6)
#define CODEC_TONE_MTR_GAIN_MODE           BIT7
#define CODEC_TONE_MTR_GAIN_PD             BIT4
#define CODEC_TONE_RNG_CMP_PD              BIT0
#define CODEC_VREF_AGND_INIT               BIT2
#define CODEC_VREF_AGND_PD                 BIT3
#define CODEC_VREF_AMP1V5_PD               BIT5
#define CODEC_VREF_BIAS_PD                 BIT7
#define CODEC_VREF_PD                      BIT0
#define CODEC_VREF_VBUF_INIT               BIT4
#define CODEC_VREF_VREF_BG_PD              BIT6
#define CODEC_VREF_VREF_HS_PD              BIT1
#define COD_PD                             (0x0002)
#define CT_INT_PEND                        BIT3
#define DACK0_EN                           BIT0
#define DACK1_EN                           BIT2
#define DAC_PD                             BIT1
#define DA_DITH_OFF                        (0x0004)
#define DA_LPF_ADJ                         (0x0010)
#define DA_PD                              (0x0002)
#define DC_ON                              (0x0800)
#define DC_VOUT                            (0x000C)
#define DC_V_CTRL                          (0x0400)
#define DIP_BRK_INT                        (0x0020)
#define DIP_INT_PEND                       BIT10
#define DIP_INT_VEC                        (0x000F)
#define DISABLE_UART_RI_INTERRUPTS         SET_UART_INT_RI_PRIO(0)
#define DISABLE_UART_RX                    P0_UART_CTRL_REG &= ~UART_REN
#define DISABLE_UART_TI_INTERRUPTS         SET_UART_INT_TI_PRIO(0)
#define DISABLE_UART_TX                    P0_UART_CTRL_REG &= ~UART_TEN
#define DMA_PARITY_ERROR                   BIT1
#define DSP_CTRL                           (0x0400)
#define DSP_INT_PEND                       BIT11
#define ENABLE_UART_RI_INTERRUPTS(pri)     SET_UART_RI_INT_PRIO(pri)
#define ENABLE_UART_RX                     P0_UART_CTRL_REG |= UART_REN
#define ENABLE_UART_TI_INTERRUPTS(pri)     SET_UART_TI_INT_PRIO(pri)
#define ENABLE_UART_TX                     P0_UART_CTRL_REG |= UART_TEN
#define ENV_B1                             BIT4
#define FINE_ADJ_BIT                       0x00
#define FRZ_DIP                            (0x0001)
#define FRZ_DMA0                           (0x0010)
#define FRZ_DMA1                           (0x0020)
#define FRZ_DMA2                           (0x0040)
#define FRZ_DMA3                           (0x0080)
#define FRZ_TIM0                           (0x0002)
#define FRZ_TIM1                           (0x0004)
#define FRZ_WDOG                           (0x0008)
#define FSK1_PD                            (0x2000)
#define FSK2_PD                            (0x1000)
#define GATESRC_CLK100                     0x0
#define GATESRC_ECZ                        0x2
#define GATESRC_ECZ2                       0x3
#define GATESRC_RINGING_VBAT3              0x1
#define GDSP_PD                            (0x8000)
#define HACK_EN                            BIT5
#define HOLD_EN                            BIT4
#define INIT_UART_PORT                     P0_DIR_REG = ((P0_DIR_REG & ~BIT1) | BIT0)
#define KEYB_INT_PEND                      BIT1
#define LDO1_ON                            (0x0002)
#define LPM                                (0x0010)
#define LSRATT                             (0x3800)
#define LSREN_SE                           (0x0200)
#define LSRHS_MODE                         (0x00C0)
#define LSRHS_PD                           (0x0100)
#define LSRN_MODE                          (0x0018)
#define LSRN_PD                            (0x0020)
#define LSRP_MODE                          (0x0003)
#define LSRP_PD                            (0x0004)
#define LSR_GND_PD                         (0x0400)
#define MCT_INT                            BIT9
#define MIC_GAIN                           (0x00F0)
#define MIC_MODE                           (0x0003)
#define MIC_MUTE                           (0x0008)
#define MIC_PD                             (0x0004)
#define MODE0_PD                           (0x0100)
#define OFFCOM_ON                          (0x0200)
#define OFFCOM_SG                          (0x0100)
#define OVERFLOW_PD                        (0x0200)
#define P0_UART_TX_REG                     P0_UART_RX_TX_REG
#define P10_EDGE_SENSITIVE                 BIT9
#define P10_INT_EN                         BIT0 /* If keyborad interrupt*/
#define P10_INT_PEND                       BIT2
#define P10_NEG_LEVEL_EDGE                 BIT8 /* If set then negative edge or level*/
#define P10_TO_P10_ISR_INT_EN              BIT10        /* If P10 interrupt is to special P10_ISR*/
#define P11_INT_EN                         BIT1
#define P12_EDGE_SENSITIVE                 BIT12
#define P12_EDGE_SENSITIVE                 BIT12
#define P12_INT_EN                         BIT2
#define P12_NEG_LEVEL_EDGE                 BIT11        /* If set then negative edge or level*/
#define P12_NEG_LEVEL_EDGE                  BIT11       /* If set then negative edge or level*/
#define P12_TO_P12_ISR_INT_EN              BIT13        /* If P12 interrupt is to special P12_ISR (Keyborad ISR)*/
#define P12_TO_P12_ISR_INT_EN              BIT13        /* If P12 interrupt is to special P12_ISR (Keyborad ISR)*/
#define P13_INT_EN                         BIT3
#define P14_INT_EN                         BIT4
#define P15_INT_EN                         BIT5
#define P16_INT_EN                         BIT6
#define P17_INT_EN                         BIT7
#define PAR_STATUS                         BIT0
#define PD1_INT                            (0x0010)
#define PLL_DIV_VD12_XD4                   0x6180
#define POWER_DOWN_ADPCM                   BIT14
#define POWER_DOWN_ADPCM0                  BIT2
#define POWER_DOWN_ADPCM1                  BIT3
#define POWER_DOWN_ADPCM2                  BIT4
#define POWER_DOWN_ADPCM3                  BIT5
#define POWER_DOWN_AGC                     BIT0
#define POWER_DOWN_CODEC                   BIT1
#define POWER_DOWN_FSK_1                   BIT13
#define POWER_DOWN_FSK_2                   BIT12
#define POWER_DOWN_GENDSP                  BIT15
#define POWER_DOWN_PCM_0                   BIT8
#define POWER_DOWN_PCM_1                   BIT7
#define POWER_DOWN_PCM_2_3                 BIT6
#define POWER_DOWN_SEQ_OF                  BIT9
#define POWER_DOWN_ZC_1                    BIT11
#define POWER_DOWN_ZC_2                    BIT10
#define POW_CLK_SEL                        (0x0380)
#define PRESCALER                          (0x0040)
#define PWM_MODE                           (0x0003)
#define RDI_DIG                            BIT12
#define RDI_HIZ                            BIT14
#define REFINT_PD                          (0x0040)
#define REG_ON                             (0x0001)
#define RESET_ALL_PENDING                  0xFFFF
#define RF_RESET_BIT                       BIT4
#define RUNWATCHDOG()                      { RESET_FREEZE_REG = BIT3;  }
#define RedLedOn                           BIT5
#define SCK_NUM                            (0x0008)
#define SCK_SEL                            (0x0004)
#define SDA_MODE                           (0x0010)
#define SPI_CLK                            (0x0018)
#define SPI_CLR_MASK                       (0x009f)
#define SPI_DO                             (0x0020)
#define SPI_EN                             (0x0020)
#define SPI_FORCE_DO                       (0x0400)
#define SPI_ON                             (0x0001)
#define SPI_PHA                            (0x0002)
#define SPI_POL                            (0x0004)
#define SPI_RST                            (0x0200)
#define SPI_SMN                            (0x0040)
#define SPI_TXH                            (0x0800)
#define SPI_WORD                           (0x0180)
#define STOPWATCHDOG()                     { SET_FREEZE_REG = BIT3;  }
#define SWRESET                            {DEBUG_REG |= SW_RESET;}
#define SW_RESET                           BIT7
#define TIM0_CTRL                          BIT0
#define TIM0_INT_PEND                      BIT7
#define TIM1_CTRL                          BIT1
#define TIM1_INT_PEND                      BIT8
#define TIM1_MODE                          (0x0020)
#define TIMER0_RUN                         BIT0
#define TIMER1_RUN                         BIT1
#define TIMER_RELOAD_DIV1                  0x00
#define TIMER_RELOAD_DIV10                 0x90
#define TIMER_RELOAD_DIV11                 0xa0
#define TIMER_RELOAD_DIV12                 0xb0
#define TIMER_RELOAD_DIV13                 0xc0
#define TIMER_RELOAD_DIV14                 0xd0
#define TIMER_RELOAD_DIV15                 0xe0
#define TIMER_RELOAD_DIV16                 0xf0
#define TIMER_RELOAD_DIV2                  0x10
#define TIMER_RELOAD_DIV3                  0x20
#define TIMER_RELOAD_DIV4                  0x30
#define TIMER_RELOAD_DIV5                  0x40
#define TIMER_RELOAD_DIV6                  0x50
#define TIMER_RELOAD_DIV7                  0x60
#define TIMER_RELOAD_DIV8                  0x70
#define TIMER_RELOAD_DIV9                  0x80
#define TRIGWATCHDOG(x)                    { WATCHDOG_REG = x; }
#define UART_10125_EVEN_PAR                BIT7
#define UART_10125_EVEN_PAR                BIT7
#define UART_115200BAUD                    (BIT2|BIT3)
#define UART_19200BAUD                     BIT2
#define UART_57600BAUD                     BIT3
#define UART_9600BAUD                      0x00
#define UART_INV_URX                       BIT9
#define UART_INV_URX                       BIT9
#define UART_INV_UTX                       BIT10
#define UART_INV_UTX                       BIT10
#define UART_IRDA_EN                       BIT8
#define UART_REN                           BIT0
#define UART_RI                            BIT6
#define UART_RX_ENABLE                     BIT0
#define UART_RX_INTERRUPT                  BIT6
#define UART_RX_INT_PEND                   BIT4
#define UART_TEN                           BIT1
#define UART_TI                            BIT5
#define UART_TI_INT_PEND                   BIT5
#define UART_TX_ENABLE                     BIT1
#define UART_TX_INTERRUPT                  BIT5
#define URST                               (0x0080)
#define UTX_EN                             BIT0
#define VBUF_INIT                          (0x0010)
#define VREF_BG_PD                         (0x0040)
#define VREF_HS_PD                         (0x0002)
#define VREF_PD                            (0x0001)
#define WDOG_CTRL                          (0x0010)
#define ZC1_PD                             (0x0800)
#define ZC2_PD                             (0x0400)

#define RedLedOn                BIT5

#ifdef SNAP
#define RED_LED_OFF                             \
    {                                           \
      P1_SET_OUTPUT_DATA_REG = RedLedOn;      \
    }

#define RED_LED_ON                              \
    {                                           \
      P1_RESET_OUTPUT_DATA_REG = RedLedOn;        \
    }
#endif

#ifndef IGNOREINDEXWARNING
#ifndef PLATFORM_PC
__no_init volatile uint16 ACCESS2_CTRL_REG @ 0xFFE084;  /* ACCESS2 CONTROL register*/
__no_init volatile uint16 ACCESS2_IN_OUT_REG @ 0xFFE082;        /* ACCESS receive/transmit register*/
__no_init volatile uint16 ACS0_CTRL_REG @ 0xFFE110;     /* ACS0 control register*/
__no_init volatile uint16 ACS0_HIGH_REG @ 0xFFE118;     /* Upper address boundary for auxiliary chip select (ACS0)*/
__no_init volatile uint16 ACS0_LOW_REG @ 0xFFE116;      /* Lower address boundary for auxiliary chip select (ACS0)*/
__no_init volatile uint16 ACS1_CTRL_REG @ 0xFFE112;     /* ACS1 control register*/
__no_init volatile uint16 ACS1_HIGH_REG @ 0xFFE11C;     /* Upper address boundary for auxiliary chip select (ACS1)*/
__no_init volatile uint16 ACS1_LOW_REG @ 0xFFE11A;      /* Lower address boundary for auxiliary chip select (ACS1)*/
__no_init volatile uint16 ACS2_CTRL_REG @ 0xFFE114;     /* ACS2 control register*/
__no_init volatile uint16 ACS2_HIGH_REG @ 0xFFE120;     /* Upper address boundary for auxiliary chip select (ACS2)*/
__no_init volatile uint16 ACS2_LOW_REG @ 0xFFE11E;      /* Lower address boundary for auxiliary chip select (ACS2)*/
__no_init volatile uint16 ADC_REG @ 0xFFE0B2;   /* 8 bits ADC value or 8 bits DAC if ADC disabled*/
__no_init volatile uint16 AD_CTRL_REG @ 0xFFE0B0;       /* P2 DAC, ADC start, ADC selection*/
__no_init volatile uint16 BANDGAP_REG @ 0xFFE07C;       /* Bandgap for Baterry management unit*/
__no_init volatile uint16 BAT_CTRL_REG @ 0xFFE07A;      /* Baterry management control register*/
__no_init volatile uint16 BAT_STATUS_REG @ 0xFFE100;    /* Battery management status register (PON, CHARGE, VBAT3)*/
__no_init volatile uint16 BMC_CTRL_REG @ 0xFFE380;      /* BMC control register*/
__no_init volatile uint16 BMC_RX_SFIELDH_REG @ 0xFFE38A;        /* BMC Rx S field register High*/
__no_init volatile uint16 BMC_RX_SFIELDL_REG @ 0xFFE388;        /* BMC Rx S field register Low*/
__no_init volatile uint16 BMC_SRam[512] @ 0xFFD000;
__no_init volatile uint16 BMC_TX_SFIELDH_REG @ 0xFFE386;        /* BMC Tx S field register High*/
__no_init volatile uint16 BMC_TX_SFIELDL_REG @ 0xFFE384;        /* BMC Tx S field register Low*/
__no_init volatile uint16 BOOT_ROM_START @ 0xFFF000;    /* Boot ROM (1k - 0xFFF3FE)*/
__no_init volatile uint16 CLEAR_ACCESS2_INT_REG @ 0xFFE088;     /* clear ACCESS bus 2 interrupt*/
__no_init volatile uint16 CLEAR_P2_ACCESS_INT_REG @ 0xFFE086;   /* clear P2 ACCESS bus interrupt*/
__no_init volatile uint16 CLK_CTRL_REG @ 0xFFE322;      /* Crystal, PLL control register*/
__no_init volatile uint16 CLK_DIV_REG @ 0xFFE102;       /* Bits 2-0 determines main clock divider 1,2,3,4,5,6,7,8 (def = 8)*/
__no_init volatile uint16 CODEC_ADDA_REG @ 0xFFE228;    /* Codec ad/da control register*/
__no_init volatile uint16 CODEC_DIV_REG @ 0xFFE328;     /* Peripheral divider register*/
__no_init volatile uint16 CODEC_LSR_REG @ 0xFFE222;     /* Codec loudspeaker control register*/
__no_init volatile uint16 CODEC_MIC_REG @ 0xFFE220;     /* Codec microphone control register*/
__no_init volatile uint16 CODEC_OFFSET_ERROR_REG @ 0xFFE22A;    /* Codec offset error compensation register*/
__no_init volatile uint16 CODEC_TEST_CTRL_REG @ 0xFFE22C;       /* Codec test control register*/
__no_init volatile uint16 CODEC_TONE_REG @ 0xFFE226;    /* Codec tone control register*/
__no_init volatile uint16 CODEC_VREF_REG @ 0xFFE224;    /* Codec vref control register*/
__no_init volatile uint16 DAC_REG @ 0xFFE0B6;           /* 8 bits DAC value*/
/*__no_init volatile uint16 DEBUG_REG @ 0xFFE108;         // DEBUG_REG for boot program control and debug contro*/
__no_init volatile uint16 DEBUG_REG @ 0xFFE108;         /* KEH!!! was declared wrong at 0xFFF108 DEBUG_REG for boot program control and debug contro*/
__no_init volatile uint16 DIP_CTRL1_REG @ 0xFFE30A;     /* DIP Control register, clears DIP_INT if read*/
__no_init volatile uint16 DIP_CTRL_REG @ 0xFFE306;      /* DIP Control register1*/
__no_init volatile uint16 DIP_PC_REG @ 0xFFE302;        /* DIP program counter*/
__no_init volatile uint16 DIP_SLOT_NUMBER_REG @ 0xFFE30C;       /* DIP slot number register, returns the current slot number*/
__no_init volatile uint16 DIP_STACK_REG @ 0xFFE300;     /* DIP Stack pointer. (read only). The DIP stack is 4 deep*/
__no_init volatile uint16 DIP_STATUS1_REG @ 0xFFE308;   /* DIP Control register,*/
__no_init volatile uint16 DIP_STATUS_REG @ 0xFFE304;    /* DIP Control register,*/
__no_init volatile uint16 DMA0_A_IDX_REG @ 0xFFE184;    /* DMA Receive index A of channel 0*/
__no_init volatile uint16 DMA0_A_STARTH @ 0xFFE182;     /* _REG Start address Low A of DMA channel 0*/
__no_init volatile uint16 DMA0_A_STARTL @ 0xFFE180;     /* _REG Start address Low A of DMA channel 0*/
__no_init volatile uint16 DMA0_B_IDX_REG @ 0xFFE18A;    /* DMA Receive B index channel 0*/
__no_init volatile uint16 DMA0_B_STARTH_REG @ 0xFFE188; /* Start address High B of DMA channel 0*/
__no_init volatile uint16 DMA0_B_STARTL_REG @ 0xFFE186; /* Start address Low B of DMA channel 0*/
__no_init volatile uint16 DMA0_CTRL_REG @ 0xFFE190;     /* Control register for the DMA channel 0*/
__no_init volatile uint16 DMA0_INT_REG @ 0xFFE18C;      /* DMA receive interrupt register channel 0*/
__no_init volatile uint16 DMA0_LEN_REG @ 0xFFE18E;      /* DMA receive length register channel 0*/
__no_init volatile uint16 DMA1_A_IDX_REG @ 0xFFE1A4;    /* DMA Receive index Aof channel 1*/
__no_init volatile uint16 DMA1_A_STARTH_REG @ 0xFFE1A2; /* Start address High A of DMA channel 1*/
__no_init volatile uint16 DMA1_A_STARTL_REG @ 0xFFE1A0; /* Start address Low A of DMA channel 1*/
__no_init volatile uint16 DMA1_B_IDX_REG @ 0xFFE1AA;    /* DMA Receive index B channel 1*/
__no_init volatile uint16 DMA1_B_STARTH_REG @ 0xFFE1A8; /* Start address High B of DMA channel 1*/
__no_init volatile uint16 DMA1_B_STARTL_REG @ 0xFFE1A6; /* Start address Low B of DMA channel 1*/
__no_init volatile uint16 DMA1_CTRL_REG @ 0xFFE1B0;     /* Control register for the DMA channel 1*/
__no_init volatile uint16 DMA1_INT_REG @ 0xFFE1AC;      /* DMA receive interrupt register channel 1*/
__no_init volatile uint16 DMA1_LEN_REG @ 0xFFE1AE;      /* DMA receive length register channel 1*/
__no_init volatile uint16 DMA2_A_IDX_REG @ 0xFFE1C4;    /* DMA Receive index A of channel 2*/
__no_init volatile uint16 DMA2_A_STARTH_REG @ 0xFFE1C2; /* Start address High A of DMA channel 2*/
__no_init volatile uint16 DMA2_A_STARTL_REG @ 0xFFE1C0; /* Start address Low A of DMA channel 2*/
__no_init volatile uint16 DMA2_B_IDX_REG @ 0xFFE1CA;    /* DMA Receive index B channel 2*/
__no_init volatile uint16 DMA2_B_STARTH_REG @ 0xFFE1C8; /* Start address High B of DMA channel 2*/
__no_init volatile uint16 DMA2_B_STARTL_REG @ 0xFFE1C6; /* Start address Low B of DMA channel 2*/
__no_init volatile uint16 DMA2_CTRL_REG @ 0xFFE1D0;     /* Control register for the DMA channel 2*/
__no_init volatile uint16 DMA2_INT_REG @ 0xFFE1CC;      /* DMA receive interrupt register channel 2*/
__no_init volatile uint16 DMA2_LEN_REG @ 0xFFE1CE;      /* DMA receive length register channel 2*/
__no_init volatile uint16 DMA3_A_IDX_REG @ 0xFFE1E4;    /* DMA Receive index A of channel 3*/
__no_init volatile uint16 DMA3_A_STARTH_REG @ 0xFFE1E2; /* Start address High A of DMA channel 3*/
__no_init volatile uint16 DMA3_A_STARTL_REG @ 0xFFE1E0; /* Start address Low A of DMA channel 3*/
__no_init volatile uint16 DMA3_B_IDX_REG @ 0xFFE1EA;    /* DMA Receive index B channel 3*/
__no_init volatile uint16 DMA3_B_STARTH_REG @ 0xFFE1E8; /* Start address High B of DMA channel 3*/
__no_init volatile uint16 DMA3_B_STARTL_REG @ 0xFFE1E6; /* Start address Low B of DMA channel 3*/
__no_init volatile uint16 DMA3_CTRL_REG @ 0xFFE1F0;     /* Control register for the DMA channel 3*/
__no_init volatile uint16 DMA3_INT_REG @ 0xFFE1EC;      /* DMA receive interrupt register channel 3*/
__no_init volatile uint16 DMA3_LEN_REG @ 0xFFE1EE;      /* DMA receive length register channel 3*/
__no_init volatile uint16 DSP_ADDR_REG @ 0xFFE258;      /* GENDSP address register used by JPO instruction*/
__no_init volatile uint16 DSP_CTRL_REG @ 0xFFE240;      /* GENDSP control register*/
__no_init volatile uint16 DSP_INT_MASK_REG @ 0xFFE244;  /* GENDSP interrupt mask register*/
__no_init volatile uint16 DSP_STATUS_REG @ 0xFFE242;    /* GENDSP status register*/
__no_init volatile uint16 FLASH_CNTR_REG @ 0xFFE130;    /* Flash control register 1, 2*/
__no_init volatile uint16 FLASH_DTERASE_REG @ 0xFFE13C; /* Data Flash erase time (page)*/
__no_init volatile uint16 FLASH_DTPROG_REG @ 0xFFE13A;  /* Data Flash program time*/
__no_init volatile uint16 FLASH_PTERASE_ @ 0xFFE136;    /* REG Flash erase time (page)*/
__no_init volatile uint16 FLASH_PTME_REG @ 0xFFE138;    /* Flash erase time (mass)*/
__no_init volatile uint16 FLASH_PTNVH1_REG @ 0xFFE132;  /* Flash NVSTR hold time (mass erase)*/
__no_init volatile uint16 FLASH_PTPROG_REG @ 0xFFE134;  /* Flash program time*/
__no_init volatile uint16 FREQ_TRIM_REG @ 0xFFE0B4;     /* 8 bits DAC value trimming register.*/
__no_init volatile uint16 FSK1_IN_REG @ 0xFFE248;       /* FSK channel 1input register*/
__no_init volatile uint16 FSK2_IN_REG @ 0xFFE24A;       /* FSK channel 2 input register*/
__no_init volatile uint16 FSK_MARK_ERROR_REG @ 0xFFE246;        /* FSK mark error control register*/
__no_init volatile uint16 INT0_PRIORITY_REG @ 0xFFE204; /* Interrupt priority register 0*/
__no_init volatile uint16 INT1_PRIORITY_REG @ 0xFFE206; /* Interrupt priority register 1*/
__no_init volatile uint16 INT2_PRIORITY_REG @ 0xFFE208; /* Interrupt priority register 2*/
__no_init volatile uint16 P0_CLEAR_RX_INT_REG @ 0xFFE036;       /* UART clear receive interrupt*/
__no_init volatile uint16 P0_CLEAR_TX_INT_REG @ 0xFFE034;       /* UART clear transmit interrupt*/
__no_init volatile uint16 P0_DIR_REG @ 0xFFE026;        /* P0 direction register*/
__no_init volatile uint16 P0_ENV_REG @ 0xFFE02A;        /* CR16C boot mode control register*/
__no_init volatile uint16 P0_IN_OUT_DATA_REG @ 0xFFE020;        /* Port 0 input output REGister*/
__no_init volatile uint16 P0_MODE_REG @ 0xFFE028;       /* P0.6 and P0.7 control bits for ACSn and AD19*/
__no_init volatile uint16 P0_RESET_OUTPUT_DATA_REG @ 0xFFE024;  /* P0 reset port pins register*/
__no_init volatile uint16 P0_SET_OUTPUT_DATA_REG @ 0xFFE022;    /* P0 set port pins register*/
__no_init volatile uint16 P0_TEST_CTRL_REG @ 0xFFE02C;  /* Test control register*/
__no_init volatile uint16 P0_UART_CTRL_REG @ 0xFFE030;  /* UART control register*/
__no_init volatile uint16 P0_UART_ERROR_REG @ 0xFFE038; /* UART Parity error register*/
__no_init volatile uint16 P0_UART_RX_TX_REG @ 0xFFE032; /* UART data transmit/receive register*/
__no_init volatile uint16 P1_DEBOUNCE_REG @ 0xFFE05C;   /* P1 keyboard debounce timer register*/
__no_init volatile uint16 P1_DIR_REG @ 0xFFE056;        /* P1 direction register*/
__no_init volatile uint16 P1_INT_EN_REG @ 0xFFE05A;     /* P1 keyboard interrupt enable register*/
__no_init volatile uint16 P1_IN_OUT_DATA_REG @ 0xFFE050;        /* P1 Data register*/
__no_init volatile uint16 P1_MODE_REG @ 0xFFE058;       /* P1 mode register*/
__no_init volatile uint16 P1_RESET_OUTPUT_DATA_REG @ 0xFFE054;  /* P1 reset port pins register*/
__no_init volatile uint16 P1_SET_OUTPUT_DATA_REG @ 0xFFE052;    /* P1 set port pins register*/
__no_init volatile uint16 P2_ACCESS_OUT_REG @ 0xFFE080; /* ACCESS transmit register*/
__no_init volatile uint16 P2_DIR_REG @ 0xFFE076;        /* P2 direction register*/
__no_init volatile uint16 P2_IN_OUT_DATA_REG @ 0xFFE070;        /* P2 Data register*/
__no_init volatile uint16 P2_MODE_REG @ 0xFFE078;       /* P2 I/O selection.*/
__no_init volatile uint16 P2_RESET_OUTPUT_DATA_REG @ 0xFFE074;  /* P2 reset port pins register*/
__no_init volatile uint16 P2_SET_OUTPUT_DATA_REG @ 0xFFE072;    /* P2 set port pins register*/
__no_init volatile uint16 P3_DIR_REG @ 0xFFE0A6;        /* P3 direction register*/
__no_init volatile uint16 P3_IN_OUT_DATA_REG @ 0xFFE0A0;        /* P3 Data register*/
__no_init volatile uint16 P3_MODE_REG @ 0xFFE0A8;       /* P3 mode register.*/
__no_init volatile uint16 P3_RESET_OUTPUT_DATA_REG @ 0xFFE0A4;  /* P3 reset port pins register*/
__no_init volatile uint16 P3_SET_OUTPUT_DATA_REG @ 0xFFE0A2;    /* P3 set port pins register*/
__no_init volatile uint16 PCM0_CTRL_REG @ 0xFFE254;     /* PCM 0 control register*/
__no_init volatile uint16 PCM0_IN_OUT_REG @ 0xFFE24C;   /* PCM channel 0 input/output register*/
__no_init volatile uint16 PCM1_CTRL_REG @ 0xFFE256;     /* PCM 1control register*/
__no_init volatile uint16 PCM1_IN_OUT_REG @ 0xFFE24E;   /* PCM channel 1 input/output register*/
__no_init volatile uint16 PCM2_IN_OUT_REG @ 0xFFE250;   /* PCM channel 2 input/output register*/
__no_init volatile uint16 PCM3_IN_OUT_REG @ 0xFFE252;   /* PCM channel 3 input/output register*/
__no_init volatile uint16 PC_START_REG @ 0xFFE20A;      /* CR16 startup adress*/
__no_init volatile uint16 PER_DIV_REG @ 0xFFE326;       /* Peripheral divider register*/
__no_init volatile uint16 PHASE_INFO_REG @ 0xFFE25A;    /* PCM 8kHz phase info register*/
__no_init volatile uint16 PLL_DIV_REG @ 0xFFE324;       /* PLL control register*/
__no_init volatile uint16 PositionDataLatch @ 0x800080;
__no_init volatile uint16 RESET_FREEZE_REG @ 0xFFE106;  /* Release watchdog, timer1, timer0 and DIP during debugging after setting in freeze mode*/
__no_init volatile uint16 RESET_INT_PENDING_REG @ 0xFFE202;     /* Reset interrupt pending register*/
__no_init volatile uint16 SCU_CPS_LEN_REG @ 0xFFE34A;   /* If the number of bits between CFP1 and CFP2 is greater or equal to the value in SCU_CPS_LEN_REG, the SCU_TS_CPS_REG is updated.*/
__no_init volatile uint16 SCU_CTRL_REG @ 0xFFE340;      /* SCU Control register*/
__no_init volatile uint16 SCU_ID_REG @ 0xFFE346;        /* Connection ID register*/
__no_init volatile uint16 SCU_NWIDH_REG @ 0xFFE344;     /* Network ID register High*/
__no_init volatile uint16 SCU_NWIDL_REG @ 0xFFE342;     /* Network ID register Low*/
__no_init volatile uint16 SCU_OFFSET_REG @ 0xFFE348;    /* Fixed value added to TS_xxx_REG value to tune for various RF solutions (except for TS_CRC_REG)*/
__no_init volatile uint16 SCU_TS_ANORM_REG @ 0xFFE364;  /* ANORM activation timeslot*/
__no_init volatile uint16 SCU_TS_CFP1_REG @ 0xFFE352;   /* Calculated start of CFP1 period.*/
__no_init volatile uint16 SCU_TS_CPS_REG @ 0xFFE358;    /* Calculated CPS timeslot. If 0 then no CPS present*/
__no_init volatile uint16 SCU_TS_CRC_REG @ 0xFFE350;    /* Calculated start of TDMA CRC field*/
__no_init volatile uint16 SCU_TS_ICBS_REG @ 0xFFE35A;   /* Calculated ICBS timeslot. If 0 then no ICBS present*/
__no_init volatile uint16 SCU_TS_MDLS_REG @ 0xFFE360;   /* Calculated Main downlink timeslot shadow*/
__no_init volatile uint16 SCU_TS_MDL_REG @ 0xFFE35C;    /* Calculated Main downlink timeslot*/
__no_init volatile uint16 SCU_TS_MULS_REG @ 0xFFE362;   /* Calculated Main uplink timeslot shadow*/
__no_init volatile uint16 SCU_TS_MUL_REG @ 0xFFE35E;    /* Calculated Main uplink timeslot*/
__no_init volatile uint16 SCU_TS_RDL_REG @ 0xFFE354;    /* Calculated Retry downlink timeslot*/
__no_init volatile uint16 SCU_TS_RUL_REG @ 0xFFE356;    /* Calculated Retry uplink timeslot*/
__no_init volatile uint16 SET_FREEZE_REG @ 0xFFE104;    /* Freeze watchdog, timer1, timer0 and DIP during debugging*/
__no_init volatile uint16 SET_INT_PENDING_REG @ 0xFFE200;       /* Set interrupt pending register*/
__no_init volatile uint16 SPI_CTRL_REG @ 0xFFE090;
__no_init volatile uint16 SPI_RX_TX_REG0 @ 0xFFE092;
__no_init volatile uint16 SPI_RX_TX_REG1 @ 0xFFE094;
__no_init volatile uint16 TIMER0_ON_REG @ 0xFFE0D0;     /* 16 bits Timer0 on register (Note 9)*/
__no_init volatile uint16 TIMER0_RELOAD_M_REG @ 0xFFE0D2;       /* 2 x 16 bits reload value for Timer0.(Note 9)*/
__no_init volatile uint16 TIMER0_RELOAD_N_REG @ 0xFFE0D4;       /**/
__no_init volatile uint16 TIMER1_RELOAD_M_REG @ 0xFFE0D6;       /* 2 x 16 bits reload value for Timer1(Note 9)*/
__no_init volatile uint16 TIMER1_RELOAD_N_REG @ 0xFFE0D8;       /**/
__no_init volatile uint16 TIMER_CTRL_REG @ 0xFFE0DA;    /* Starts timer0 or timer1, sets timer modes and timer clock fre-quencies*/
__no_init volatile uint16 TIM_CTRL_REG @ 0xFFE320;      /* TIM Control register*/
__no_init volatile uint16 TONE_CLEAR_INT1_REG @ 0xFFE0C6;       /* Clears CT1 interrupt and TONE_LATCH1_REG*/
__no_init volatile uint16 TONE_CLEAR_INT2_REG @ 0xFFE0CE;       /* Clears CT2 interrupt and TONE_LATCH2_REG*/
__no_init volatile uint16 TONE_COUNTER1_REG @ 0xFFE0C2; /* Tone Counter 1*/
__no_init volatile uint16 TONE_COUNTER2_REG @ 0xFFE0CA; /* Tone Counter 2*/
__no_init volatile uint16 TONE_CTRL1_REG @ 0xFFE0C0;    /* Tone control register 1*/
__no_init volatile uint16 TONE_CTRL2_REG @ 0xFFE0C8;    /* Tone control 2*/
__no_init volatile uint16 TONE_LATCH1_REG @ 0xFFE0C4;   /* Tone Latch 1*/
__no_init volatile uint16 TONE_LATCH2_REG @ 0xFFE0CC;   /* Tone Latch 2*/
__no_init volatile uint16 WATCHDOG_REG @ 0xFFE0E0;      /* Watchdog preset value. Decremented every 10 msec.*/
__no_init volatile uint8 VERSION_REG0 @ 0xFFFFFA;       /* Version register 0*/
__no_init volatile uint8 VERSION_REG1 @ 0xFFFFFB;       /* Version register 1*/
__no_init volatile uint8 VERSION_REG2 @ 0xFFFFFC;       /* Version register 2*/
__no_init volatile uint8 VERSION_REG3 @ 0xFFFFFD;       /* Version register 3*/
__no_init volatile uint8 VERSION_REG4 @ 0xFFFFFE;       /* Version register 4*/
__no_init volatile uint8 VERSION_REG5 @ 0xFFFFFF;       /* Version register 5*/
#endif
#endif

#define SET_DSP_INT_PRIO(prio)                                                            \
    {                                                                                     \
          register uint16 w = __get_processor_register(Reg_PSR);                          \
          __disable_interrupt();                                                             \
          INT0_PRIORITY_REG = (uint16)((INT0_PRIORITY_REG & 0x0fff) | (prio << 12));      \
          __set_processor_register(Reg_PSR,w);                                            \
    }

#define SET_TIM0_INT_PRIO(prio) {                                                         \
          register uint16 w = __get_processor_register(Reg_PSR);                          \
          __disable_interrupt();                                                             \
          INT1_PRIORITY_REG = (uint16)((INT1_PRIORITY_REG & 0x0fff) | (prio<<12));        \
          __set_processor_register(Reg_PSR,w);                                            \
    }

#define SET_TIM1_INT_PRIO(prio)                                                           \
       {                                                                                  \
             register uint16 w = __get_processor_register(Reg_PSR);                       \
             __disable_interrupt();                                                          \
             INT0_PRIORITY_REG = (uint16)((INT0_PRIORITY_REG & 0xfff0) | prio);           \
             __set_processor_register(Reg_PSR,w);                                         \
       }

#define SET_DIP_INT_PRIO(prio)                                                            \
{                                                                                         \
  __disable_interrupt();                                                                  \
  INT0_PRIORITY_REG = (uint16)(INT0_PRIORITY_REG | (prio << 8));                          \
  __enable_interrupt();                                                                   \
}

#define SET_CLK100_INT_PRIO(prio)                                                         \
   {                                                                                      \
      register uint16 w = __get_processor_register(Reg_PSR);                              \
      __disable_interrupt();                                                                 \
      INT0_PRIORITY_REG = (uint16)((INT0_PRIORITY_REG & 0xff0f) | (prio<<4));             \
      __set_processor_register(Reg_PSR,w);                                                \
   }

#define RF_RESET_LOW                            \
    {                                           \
      P1_RESET_OUTPUT_DATA_REG = RF_RESET_BIT;  \
    }

#define RF_RESET_HIGH                           \
    {                                           \
      P1_SET_OUTPUT_DATA_REG = RF_RESET_BIT;    \
    }

#define SET_SPI_INT_PRIO(prio)                                    \
    {                                                             \
          register uint16 w = __get_processor_register(Reg_PSR);  \
          __disable_interrupt();                                     \
          INT1_PRIORITY_REG = (uint16)((INT1_PRIORITY_REG & 0xf0ff) | (prio << 8));      \
          __set_processor_register(Reg_PSR,w);                    \
    }

#define SET_UART_RX_INT_PRIO(prio)                               \
{                                                                \
  __disable_interrupt();                                         \
  INT1_PRIORITY_REG = (uint16)(INT1_PRIORITY_REG | prio);        \
  __enable_interrupt();                                          \
}

#define SET_UART_TX_INT_PRIO(prio)                               \
{                                                                \
  __disable_interrupt();                                         \
  INT1_PRIORITY_REG = (uint16)(INT1_PRIORITY_REG | (prio<<4));   \
  __enable_interrupt();                                          \
}

#define  RxSynthesisValue_Byte1(chan) (0x02)
#define  RxSynthesisValue_Byte2(chan) (0x08)
#define  RxSynthesisValue_Byte3(chan) (uint8)((0x95-(int8)(((chan)+DECT_Channel_offset)*2)))

#define  TxSynthesisValue_Byte1(chan) (0x01)
#define  TxSynthesisValue_Byte2(chan) (0x08)
#define  TxSynthesisValue_Byte3(chan) (uint8)((0x94-(int8)(((chan)+DECT_Channel_offset)*2)))

#endif /*  __MAP_428_H*/
