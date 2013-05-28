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
 * $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/pd_pins.h_v   1.5   11 Feb 2005 13:56:28   MNE  $                                                               *
 *                                                                        *
 * $Log:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/pd_pins.h_v  $                                                                  *
 *
 *    Rev 1.5   11 Feb 2005 13:56:28   MNE
 * #ifdef _LMX4168_ changed to #ifdef _LMX4169_
 * Unused code removed.
 *
 *    Rev 1.4   11 Aug 2004 13:13:30   MNE
 * National changes.
 **************************************************************************/


#define     PD_1     (1<<1)
#define     PD_2     (1<<2)
#define     PD_3     (1<<3)
#define     PD_4     (1<<4)
#define     PD_5     (1<<5)
#define     PD_6     (1<<6)
#define     PD_7     (1<<7)

#define RFB_SEL_ON       MEN1
#define RFB_SEL_OFF      MEN1N

#ifdef _PP6_PLATFORM_
	#define LE2_ON           MEN1
	#define LE2_OFF          MEN1N
#else
    #ifdef _SC14480_
	    #define LE2_ON           MEN1
	    #define LE2_OFF          MEN1N
    #else
	    #ifdef _IP6000_PLATFORM_
		    #define LE2_PIN          PD_1
		    #define LE2_ON           P_LDH  LE2_PIN
		    #define LE2_OFF          P_LDL  LE2_PIN
	    #else
		    #ifdef PELTOR_HW
			    #define LE2_PIN          PD_1
			    #define LE2_ON           P_LDH  LE2_PIN
			    #define LE2_OFF          P_LDL  LE2_PIN
		    #else
			    #ifndef IGNOREINDEXERWARNING
				    #error Define _PP6_PLATFORM_ or _IP6000_PLATFORM_
			    #endif
		    #endif
	    #endif /*_IP6000_PLATFORM_*/
    #endif /*_PP6_PLATFORM_*/
#endif
#ifdef PELTOR_HW

	#define ANT_SEL_PIN      PD_6
	#define ANT_SEL_HIGH     P_LDH,  ANT_SEL_PIN
	#define ANT_SEL_LOW      P_LDL,  ANT_SEL_PIN
#else
	#define ANT_SEL_HIGH     WT,	 1
	#define ANT_SEL_LOW      WT,	 1
#endif

#define LE1_PIN          PD_2
#define LE1_ON           P_LDH  LE1_PIN
#define LE1_OFF          P_LDL  LE1_PIN

#define RXDSG_ON         WT 1
#define RXDSG_OFF        WT 1

#define PA_PIN           PD_3
#define PA_ON            P_LDH  PA_PIN
#define PA_OFF           P_LDL  PA_PIN

#define POW_PIN          PD_7
#define POW_OFF          WT 1   /*P_LDH  POW_PIN*/
#define POW_ON           WT 1   /*P_LDL  POW_PIN*/

#define RX_ON            WT     1
#define RX_OFF           WT     1

#define DIP_ADC_END      P_LDH  1<<0
#define DIP_ADC_START    P_LDL  1<<0


/* FAD antenna select signals*/
#define FADANT1      0x05
#define FADANT2      0x04
#define FADANTSEL    0x00
#define RSSIMEAS     0x06
#define ANTDESEL     0x00
