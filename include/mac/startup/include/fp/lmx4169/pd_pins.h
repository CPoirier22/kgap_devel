/**************************************************************************
 * Project   : DECT PP5                                                   *
 * Module    : Handset Bearer controller.                                 *
 * Reference :                                                            *
 * Type      : SC14428 DIP assembler header file.                         *
 * Function  :                                                            *
 * Systems   : Handset                                                    *
 *------------------------------------------------------------------------*
 * Copyright (c) 2002 by KIRK telecom A/S.                                *
 *                                                                        *
 * $Header$                                                               *
 *                                                                        *
 * $Log$                                                                  *
 **************************************************************************/

#define RADIO_A                 /* select*/
#define     PD_0     (1<<0)     /* PD0 is not available externally*/
#define     PD_1     (1<<1)
#define     PD_2     (1<<2)
#define     PD_3     (1<<3)
#define     PD_4     (1<<4)
#define     PD_5     (1<<5)
#define     PD_6     (1<<6)
#define     PD_7     (1<<7)
#define SEL1_PIN          PD_6
#define SEL1_ON           P_LDH  SEL1_PIN
#define SEL1_OFF          P_LDL  SEL1_PIN

#ifdef PELTOR_HW
#define SEL2_PIN          PD_6
#define SEL2_ON           P_LDL  SEL2_PIN
#define SEL2_OFF          P_LDH  SEL2_PIN
#define SEL12_OFF         WT     1
#else
#define SEL2_PIN          PD_7
#define SEL2_ON           P_LDH  SEL2_PIN
#define SEL2_OFF          P_LDL  SEL2_PIN
#define SEL12_OFF         P_LDL  SEL1_PIN | SEL2_PIN
#endif

#define TP220_PIN         PD_3
#define TP220_ON          P_LDH  TP220_PIN
#define TP220_OFF         P_LDL  TP220_PIN
#define LE1_PIN           PD_2
#define LE1_ON            P_LDH  LE1_PIN
#define LE2_PIN           PD_1
#define LE2_ON            P_LDH  LE2_PIN
#define ADC_PIN           PD_0
#define DIP_ADC_END       P_LDH  ADC_PIN
#define DIP_ADC_START     P_LDL  ADC_PIN
#define LE12_OFF          P_LDL  LE1_PIN | LE2_PIN
#define LE12_ON           P_LDH  LE1_PIN | LE2_PIN

#ifdef PELTOR_HW
#define RFB_SEL_ON        MEN1N
#define RFB_SEL_OFF       MEN1
#else
#ifdef IP6000_CHIP_ANTENNA
#define RFB_SEL_ON        MEN1N
#define RFB_SEL_OFF       MEN1
#else
#define RFB_SEL_ON        MEN1
#define RFB_SEL_OFF       MEN1N
#endif
#endif

#define ANTSEL            0x00
#define ANTDESEL          0x00
