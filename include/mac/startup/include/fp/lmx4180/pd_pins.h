/**************************************************************************
 * Project   : DECT RFP5                                                  *
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

#define USE_RADIO_A             /* select*/
#define     PD_0     (1<<0)     /* PD0 is not available externally*/
#define     PD_1     (1<<1)
#define     PD_2     (1<<2)
#define     PD_3     (1<<3)
#define     PD_4     (1<<4)
#define     PD_5     (1<<5)
#define     PD_6     (1<<6)
#define     PD_7     (1<<7)
#define MW_SO_PIN         PD_7
#define MW_SO_OFF         P_LDH  MW_SO_PIN
#define MW_SO_ON          P_LDL  MW_SO_PIN
#define SEL2_PIN          PD_6
#define SEL2_ON           P_LDH  SEL2_PIN
#define SEL2_OFF          P_LDL  SEL2_PIN
#define SEL1_PIN          PD_5
#define SEL1_ON           P_LDH  SEL1_PIN
#define SEL1_OFF          P_LDL  SEL1_PIN
#define SEL3_PIN          PD_4
#define SEL3_ON           P_LDH  SEL3_PIN
#define SEL3_OFF          P_LDL  SEL3_PIN
#define SEL123_OFF        P_LDL  SEL1_PIN | SEL2_PIN | SEL3_PIN
#define TP25_PIN          PD_3
#define TP25_ON           P_LDH  TP25_PIN
#define TP25_OFF          P_LDL  TP25_PIN

#ifdef USE_RADIO_A
  /* Use Radio A*/
  #define LE1_PIN         PD_1
  #define LE2_PIN         PD_2
  #define RFB_SEL_ON      MEN1N
  #define RFB_SEL_OFF     MEN1
#else
  /* Use Radio B*/
  #define LE1_PIN         PD_2
  #define LE2_PIN         PD_1
  #define RFB_SEL_ON      MEN1
  #define RFB_SEL_OFF     MEN1N
#endif

#define LE1_ON            P_LDH  LE1_PIN
#define LE2_ON            P_LDL  LE2_PIN
#define ADC_PIN           PD_0
#define DIP_ADC_END       P_LDH  ADC_PIN
#define DIP_ADC_START     P_LDL  ADC_PIN
#define LE12_OFF          P_LDL  LE1_PIN | LE2_PIN
#define LE12_ON           P_LDH  LE1_PIN | LE2_PIN

#define ANTSEL            0x00
#define ANTDESEL          0x00
