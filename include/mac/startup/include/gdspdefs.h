#ifndef GDSPDEFS_H_INCLUDED
#define GDSPDEFS_H_INCLUDED
/*
 *-----------------------------------------------------------------------------
 *                    NNN
 *           NN     N   NN
 *         NNNNN   N    NNN
 *        NNNNNNN       NNN      N a t i o n a l
 *       NNNN NNNN     NNNN
 *      NNNN   NNNN   NNNN     S e m i c o n d u c t o r   B. V.   ( N S S T )
 *     NNNN     NNNN NNNN
 *     NNN       NNNNNNN     T h e   N e t h e r l a n d s
 *     NNN    N   NNNNN
 *      NNN  N     NN
 *        NNN
 *
 * (C) Copyright National Semiconductor B.V., unpublished work.
 * This computer program includes Confidential, Proprietary Information and
 * is a Trade Secret of National Semiconductor B.V.
 * All use, disclosure, and/or reproduction is prohibited unless authorized
 * in writing. All Rights Reserved.
 *
 *-----------------------------------------------------------------------------
 * Purpose: GDSPDEFS.H - Definitions of GenDSP Algorithm MicroROM Addresses
 *                       and GenDSP IO-Registers.
 * Created: 27/08/2002
 * By:      Michiel Helsloot
 * Version: 2.2
 *-----------------------------------------------------------------------------
 * Automatically filled out by Perforce Version Control
 * $Header:   K:/PH/140960xx/00/Archive/H/GDSPDEFS.H_v   1.0   17 Sep 2003 09:16:56   mne  $
 * $Author:   mne  $
 * $Date:   17 Sep 2003 09:16:56  $
 * $Change$
 *
 *-----------------------------------------------------------------------------
 */

/*========================== Macro definitions & typedefs =============*/

/*
 * Macro to calculate input offset-pointer values
 * x = destination (output) of previous block in signal-path
 * y = start-address of active parameter-block
 *
 * Shift the result 1 bit to the right to get WORD oriented
 * addresses.
 */


#define CONNECT_INPUT_PTR(x, y)   ( (( LWRD((x) - LWRD(y)) >>1 ) & 0x1FFF) )
/*
 * The list below contains the MicroROM addresses of the SeqDSP
 * algorithms. These labels are to be used in combination with the
 * CALL instruction (as operand).
 *
 * NOTE: Using different CALL operands may cause the DSP to lock up
 *       or to execute only parts of the intended algoritms
 */

#ifdef GDSP_ASM
#ifdef GENDSP11
#message 'Assembling for GenDSP v1.1 (SC14428ES1)'
#elif (defined GENDSP20)
#message 'Assembling for GenDSP v2.0 (SC14428ES2)'
#elif (defined GENDSP21)
#message 'Assembling for GenDSP v2.1 (SC14428ES3/SC14429ES1)'
#else
#define GENDSP21
#message 'No GenDSP version definded. Defaulting to GENDSP v2.1.'
#message 'Define other GenDSP versions with GENDSP11 (SC14428ES1), GENDSP20 (SC14428ES2) or GENDSP21 (SC14428ES3/SC14429ES1)'
#endif
#else
#ifdef GENDSP11
#pragma message("Assembling for GenDSP v1.1 (SC14428ES1)")
#elif (defined GENDSP20)
#pragma message("Assembling for GenDSP v2.0 (SC14428ES2)")
#elif (defined GENDSP21)
#pragma message("Assembling for GenDSP v2.1 (SC14428ES3/SC14429ES1)")
#else
#define GENDSP21
#pragma message("No GenDSP version definded. Defaulting to GENDSP v2.1.")
#pragma message("Define other GenDSP versions with GENDSP11 (SC14428ES1), GENDSP20 (SC14428ES2) or GENDSP21 (SC14428ES3/SC14429ES1)")
#endif
#endif

#if ((defined GENDSP11) || (defined GENDSP20))
/*       Symbol      ROM Address        Algorithm Description     Section (AN-D-060 v0.9) */
#define  AEC         1532            /* Acoustic Echo Canceller   4.8.2   */
#define  AGC         26              /* AGC                       4.3.1   */
#define  ANAGC       537             /* Analog AGC                4.3.3   */
#define  AND         53              /* Bitwise AND               4.14.1  */
/* no #define  BUFFER      BUFFER not available on GenDSP 1.1 or GenDSP 2.0 */
#define  CASDET      2499            /* CAS Detector              4.23.2  */
#define  CONF        759             /* Conference                4.5     */
#define  COPYB2B     554             /* Block to Block copy       4.6.1   */
#define  COPYP2B     566             /* Pointer to Block copy     4.6.2   */
#define  COPYP2P     579             /* Pointer to Pointer copy   4.6.3   */
#define  CVSD2LIN    1016            /* CVSD to linear            4.7.2   */
#define  DEC         83              /* Decrement                 4.13.2  */
/* no #define  EDGEDET     EDGEDET not available on GenDSP 1.1 or GenDSP 2.0 */
#define  FSKDET      1079            /* FSK Detection             4.10    */
#define  FSKGEN      1270            /* FSK Generation            4.11    */
#define  HAGC        3317            /* Handsfree AGC             4.3.2   */
#define  HFREE       160             /* Handsfree                 4.12    */
#define  INC         77              /* Increment                 4.13.1  */
#define  LAW2LIN     940             /* A/u law to linear         4.2.2   */
#define  LEC         778             /* Line Echo Canceller       4.8.1   */
#define  LIN2CVSD    958             /* Linear to CVSD            4.7.1   */
#define  LIN2LAW     924             /* Linear to A/u law         4.2.1   */
#define  MONITOR     592             /* MONITOR                   4.15    */
#define  NSHL        89              /* Nibble Shift (left)       4.16.2  */
#define  NSHR        98              /* Nibble Shift (right)      4.16.1  */
#define  OR          61              /* Bitwise OR                4.14.2  */
#define  PFILT       875             /* Prog. filter (biquad)     4.19    */
#define  PLEVDET     2               /* Level detection           4.18    */
#define  PNLEVDET    907             /* Noise detection           4.17    */
#define  SUB         69              /* Subtracor                 4.20    */
#define  SUMM        14              /* Summator                  4.21    */
#define  SUPP        107             /* Suppression               4.12    */
#define  TONEDET     603             /* DTMF detect               4.23    */
#define  TONEGEN     1476            /* Tripple Tone Generation   4.24    */
#define  ZCROSS      43              /* Zero cross detection      4.25    */
#elif (defined GENDSP21)
/*       Symbol      ROM Address        Algorithm Description     Section (AN-D-060 v0.9) */
#define  AEC         1559            /* Acoustic Echo Canceller   4.8.2   */
#define  AGC         26              /* AGC                       4.3.1   */
#define  ANAGC       537             /* Analog AGC                4.3.3   */
#define  AND         53              /* Bitwise AND               4.14.1  */
#define  BUFFER      3304    /* Versatile BUFFER          4.4     */
#define  CASDET      2435            /* CAS Detector              4.23.2  */
#define  CONF        759             /* Conference                4.5     */
#define  COPYB2B     554             /* Block to Block copy       4.6.1   */
#define  COPYP2B     566             /* Pointer to Block copy     4.6.2   */
#define  COPYP2P     579             /* Pointer to Pointer copy   4.6.3   */
#define  CVSD2LIN    1016            /* CVSD to linear            4.7.2   */
#define  DEC         83              /* Decrement                 4.13.2  */
#define  EDGEDET     3343            /* Edge Detection            4.9     */
#define  FSKDET      1079            /* FSK Detection             4.10    */
#define  FSKGEN      1297            /* FSK Generation            4.11    */
#define  HAGC        3253            /* Handsfree AGC             4.3.2   */
#define  HFREE       160             /* Handsfree                 4.12    */
#define  INC         77              /* Increment                 4.13.1  */
#define  LAW2LIN     940             /* A/u law to linear         4.2.2   */
#define  LEC         778             /* Line Echo Canceller       4.8.1   */
#define  LIN2CVSD    958             /* Linear to CVSD            4.7.1   */
#define  LIN2LAW     924             /* Linear to A/u law         4.2.1   */
#define  MONITOR     592             /* MONITOR                   4.15    */
#define  NSHL        89              /* Nibble Shift (left)       4.16.2  */
#define  NSHR        98              /* Nibble Shift (right)      4.16.1  */
#define  OR          61              /* Bitwise OR                4.14.2  */
#define  PFILT       875             /* Prog. filter (biquad)     4.19    */
#define  PLEVDET     2               /* Level detection           4.18    */
#define  PNLEVDET    907             /* Noise detection           4.17    */
#define  SUB         69              /* Subtracor                 4.20    */
#define  SUMM        14              /* Summator                  4.21    */
#define  SUPP        107             /* Suppression               4.22    */
#define  TONEDET     603             /* DTMF detect               4.23    */
#define  TONEGEN     1503            /* Tripple Tone Generation   4.24    */
#define  ZCROSS      43              /* Zero cross detection      4.25    */
#endif


/*
 * The following list contains the SeqDSP internal hardware register
 * addresses. These labels represent addresses within the 8K address-space
 * of the SeqDSP.
 */
/*       Register Name          Address        Description                         */
#define  CODEC_TONEOFF_REG      (0x1FED*2)     /* CODEC Tone Off register          */
#define  SER_INTERFACE0_REG     (0x1FEE*2)     /* Ext. serial interface channel 0  */
#define  SER_INTERFACE1_REG     (0x1FEF*2)     /* Ext. serial interface channel 1  */
#define  SER_INTERFACE2_REG     (0x1FF0*2)     /* Ext. serial interface channel 2  */
#define  SER_INTERFACE3_REG     (0x1FF1*2)     /* Ext. serial interface channel 3  */
#define  CODEC_MIC_GAIN_REG     (0x1FF2*2)     /* Codec mic gain                   */
#define  CODEC_DATA_REG         (0x1FF3*2)     /* Codec data                       */
#define  ADPCM0_REG             (0x1FF4*2)     /* Adpcm channel 0                  */
#define  ADPCM1_REG             (0x1FF5*2)     /* Adpcm channel 1                  */
#define  ADPCM2_REG             (0x1FF6*2)     /* Adpcm channel 2                  */
#define  ADPCM3_REG             (0x1FF7*2)     /* Adpcm channel 3                  */
#define  ZCROSS1_OUT_REG        (0x1FF8*2)     /* Zero crossing 1 output           */
#define  ZCROSS2_OUT_REG        (0x1FF9*2)     /* Zero crossing 2output            */
#define  FSK1_RAWDATA_REG       (0x1FFA*2)     /* raw data for fsk 1.              */
#define  FSK1_CD_REG            (0x1FFB*2)     /* carrier for fsk 1.               */
#define  FSK1_MARKDET_REG       (0x1FFC*2)     /* mark detect for fsk 1.           */
#define  FSK2_RAWDATA_REG       (0x1FFD*2)     /* raw data for fsk 2.              */
#define  FSK2_CD_REG            (0x1FFE*2)     /* carrier for fsk 2.               */
#define  FSK2_MARKDET_REG       (0x1FFF*2)     /* mark detect for fsk 2.           */

#ifdef SC14429
#define CODEC2_DATA_REG      (0x1FEC*2)    /* 2nd Codec Data (only on SC14429) */
#endif

#define  GDSP_REG_FLAG          0x8000         /* Flag for the GenDSP driver to     */
/* identify pointers to unrelocatable*/
/* hardware register-addresses       */
/* See AN-D-074 for more information.*/
/* This flag will not affect other   */
/* DSP applications, since it will be*/
/* truncated by the GenDSP address-  */
/* decoder.                          */

#endif /* FILENAME_INCLUDED  */
