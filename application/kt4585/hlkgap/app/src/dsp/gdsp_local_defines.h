/********************************************************************************
*********************************************************************************
*                                                                               *
*     E ENEEEEEEEEEEEE             CCCC CCC         TTTTTTT TTTTTTTTTT          *
*     E EEEEEEEEEEEEEE          CCCCC  C CCCC             T TTTTT               *
*     E EEEE                   CCCCC    C CCCC            T TTTTT               *
*     E EEEE                  CCCCC      C CCCC           T TTTTT               *
*     E EEEE                 CCCCC                        T TTTTT               *
*     E EEEEEEEEEEEEEE      CCCCC                         T TTTTT               *
*     E EEEEEEEEEEEEEE      C CCCC                        T TTTTT               *
*     E EEEE                 C CCCC                       T TTTTT               *
*     E EEEE                  C CCCC      CCCCC           T TTTTT               *
*     E EEEEEEEEEEEEEE         C CCCC   CCCCC             T TTTTT               *
*     E EEEEEEEEEEEEEE  OO      C CCCCCCCC         OO     T TTTTT     OO        *
*                       OO                         OO                 OO        *
*                                                                               *
*     Electronic Communication Technology A/S.                                  *
*     Sintrupvej 23, DK-8220 Brabrand, Tel.: +45 87441230                       *
*     Website: www.ect.dk                                                       *
*                                                                               *
*********************************************************************************
* $History:: gdsp_local_defines                                               $ *
*                                                                               *
* Initial Revision                                                              *
*********************************************************************************
*/

#ifndef GDSP_LOCAL_DEFINES_H_
#define GDSP_LOCAL_DEFINES_H_

//#define ENABLE_TONEGEN
//#define ECT_DSP_MESSAGES
//#define FOR_TEST_BASE_ONLY				// !! THIS IS ONLY FOR IN-HOUSE TEST RELEASE !!  use this code to activate calibration button on registration screen

#define DSP_SEGMENT_SIZE        	0x1A2C	// was 0x1E00; subtracted 0x428 after removing PAEC, 0x80 after adding message repeater, 0x2C after adding 2nd base, added 0x100 after moving iStack

/*============================================================================*/
/*  Memory allocation                                                         */
/*  Can be changed by user!                                                   */
/*  Default 512 bytes DIP & 3K bytes CR16 memory reserved in front of DSP mem */
/*============================================================================*/
/*#define DSP_SEGMENT_MARGIN      0x30
#define DSP_BG_CODE_START       0x10900 // Start of background code segment
#define DSP_BG_CODE_END         DSP_BG_CODE_START+(GDSP_MAX_MDL2CODE_CODESIZE_DSP1_BACKGND*4) // End of background code segment
#define DSP_CONTEXT1_CODE_START DSP_BG_CODE_END + DSP_SEGMENT_MARGIN
#define DSP_CONTEXT1_CODE_END   DSP_CONTEXT1_CODE_START+(GDSP_MAX_MDL2CODE_CODESIZE_DSP1_8KHZ*4) +0x40// remember minimum 61
#define DSP_DATA_START          DSP_CONTEXT1_CODE_END+DSP_SEGMENT_MARGIN // Start of DSP data pool
#define DSP_DATA_END            DSP_DATA_START+(GDSP_MAX_MDL2CODE_DATASIZE_DSP1_BACKGND*2) + (GDSP_MAX_MDL2CODE_DATASIZE_DSP1_8KHZ*2)// End of DSP data pool
#define DSP_STACK_INIT          DSP_BG_CODE_START+DSP_SEGMENT_SIZE-1// Place last, stack works its way downward//DSP_DATA_END+DSP_SEGMENT_MARGIN+0x100//0x10CFF // Stack is initialized .
*/
#define PP_DSP_BG_CODE_START       0x10900 // Start of background code segment
#define PP_DSP_BG_CODE_END         0x109FF

#define PP_DSP_CONTEXT1_CODE_START 0x10A00
#define PP_DSP_CONTEXT1_CODE_END   0x10BFF // must be (GDSP_MAX_MDL2CODE_CODESIZE_DSP1_8KHZ*4) + 0x94 +0x40 +0x20 "Context save and restore"

#define PP_DSP_DATA_START          0x10C00//0x10B50
#define PP_DSP_DATA_END            0x11AFF
#define PP_BACKGROUND_TRIGGER_FUNC 0x11B00
// stack usage is atthe moment appr. 0x180
#define PP_DSP_STACK_INIT          0x11DF0 //DSP_BG_CODE_START+DSP_SEGMENT_SIZE-1// Place last, stack works its way downward//DSP_DATA_END+DSP_SEGMENT_MARGIN+0x100//0x10CFF // Stack is initialized .

#if (PP_DSP_BG_CODE_END-PP_DSP_BG_CODE_START)<(GDSP_MAX_MDL2CODE_CODESIZE_DSP1_BACKGND*4)
  possible too small codesegment
#endif
#if (PP_DSP_DATA_END-PP_DSP_DATA_START)<(GDSP_MAX_MDL2CODE_DATASIZE_DSP1_BACKGND*2)
  possible too small datasegment
#endif
#if (PP_DSP_STACK_INIT-PP_DSP_DATA_END)<0x7F
  possible too small stack segment - or DSP_DATA_END is not located before DSP_DATA_END
#endif
#if ((PP_DSP_STACK_INIT-PP_DSP_BG_CODE_START)>DSP_SEGMENT_SIZE)
  Error DSP Segment to small, must be GDSP_MAX_MDL2CODE_CODESIZE_DSP1_BACKGND*4+GDSP_MAX_MDL2CODE_DATASIZE_DSP1_BACKGND*2 + 0x80
#endif

// check for 32-bit alignment (ending in 0x0, 0x4, 0x8, or 0xC)
#define FP_DSP_BG_CODE_START		0x10800 										// 0x10800
#define FP_DSP_BG_CODE_END          (FP_DSP_BG_CODE_START + (0x0090 - 1))			// 0x1088F	// space needed = 0x0090
#define FP_DSP_CONTEXT1_CODE_START  (FP_DSP_BG_CODE_END + 1)						// 0x10890	// context save and restore = 0x0310
#define FP_DSP_CONTEXT1_CODE_END    (FP_DSP_CONTEXT1_CODE_START + (0x0310 - 1))		// 0x10B9F	// must be (GDSP_MAX_MDL2CODE_CODESIZE_DSP1_8KHZ*4) + 0x94 +0x40 +0x20 "Context save and restore"
#define FP_DSP_DATA_START           (FP_DSP_CONTEXT1_CODE_END + 1)					// 0x10BA0
#define FP_DSP_DATA_END          	(FP_DSP_DATA_START + (0x1320 - 1)) 				// 0x11EBF	// space needed = 0x1320 ??
#define FP_BACKGROUND_TRIGGER_FUNC	(FP_DSP_DATA_END + 1)							// 0x11EC0
#define FP_DSP_STACK_START         	(FP_BACKGROUND_TRIGGER_FUNC + (BT_PM_size * 2))	// 0x11F00	// 0x40 for BT
#define FP_DSP_STACK_INIT			(FP_DSP_BG_CODE_START + DSP_SEGMENT_SIZE)		// 0x1222C	// leaving 0x032C for DSP stack

#if (FP_DSP_BG_CODE_END-FP_DSP_BG_CODE_START)<(GDSP_MAX_MDL2CODE_CODESIZE_DSP1_BACKGND*4)
  possible too small codesegment
#endif
#if (FP_DSP_DATA_END-FP_DSP_DATA_START)<(GDSP_MAX_MDL2CODE_DATASIZE_DSP1_BACKGND*2)
  possible too small datasegment
#endif
#if (FP_DSP_STACK_INIT-FP_DSP_DATA_END)<0x180
  possible too small stack segment - or DSP_DATA_END is not located before DSP_DATA_END
#endif
#if ((FP_DSP_STACK_INIT-FP_DSP_BG_CODE_START)>DSP_SEGMENT_SIZE)
  Error DSP Segment to small, must be GDSP_MAX_MDL2CODE_CODESIZE_DSP1_BACKGND*4+GDSP_MAX_MDL2CODE_DATASIZE_DSP1_BACKGND*2 + 0x80
#endif

#endif /* GDSP_LOCAL_DEFINES_H_ */
