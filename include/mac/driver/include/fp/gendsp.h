/*
 ********************************************************************
 *
 * Module:	getchar.h
 *
 *	Config-item:	?
 *
 * Contents:    Header file for getchar.c.
 *
 *	Author:	´Kirk telecom / CB
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/PH/140999xx/Xx/Variant/Archive/H/gendsp.h_v   1.5   Jan 29 2004 10:49:12   on  $
 *
 * $Log:   K:/PH/140999xx/Xx/Variant/Archive/H/gendsp.h_v  $
 *
 *    Rev 1.5   Jan 29 2004 10:49:12   on
 * Changed to max 12 speech channels
 *
 *    Rev 1.4   Jan 22 2004 12:19:38   on
 * Double buffering changed
 *
 *    Rev 1.3   Jan 08 2004 15:54:30   on
 * Double buffering introduced
 *
 *    Rev 1.2   Dec 11 2003 08:48:12   on
 * New ADPCM handling
 *
 *    Rev 1.0   May 06 2003 10:38:54   on
 * 1'st version of DZ 500 2G4 A8
 *
 *    Rev 1.2   16 Jan 2001 15:35:38   on
 * Speed optimized
 *
 *    Rev 1.0   Apr 07 1997 08:23:18   CB
 * Initial revision.
 *
 ********************************************************************
 */

#ifndef GENDSP_H__
#define GENDSP_H__

extern unsigned long int SHARED_RAM_START;

#define TRANSMITTED_TESTBYTES   80
#define ADPCM_TEST_CODES        64

#ifdef SLOT_12
#define NUMBER_OF_DSP_SLOTS   12
#else
#define NUMBER_OF_DSP_SLOTS   8
#endif

extern uint32    DSP_START_ADR;
extern uint32    DSP_END_ADR;
extern const uint16    DSP_FP_SIZE;

extern const uint16    DSP_Loop1_DSP_ADDR;
extern const uint16    PP_Handling1_ADDR;
extern const uint16    PP_Handling2_ADDR;
extern const uint16    PP_Handling3_ADDR;
extern const uint16    PP_Handling4_ADDR;
extern const uint16    DSP_LineLoop_ADDR;
extern const uint16    WaitCounter_ADDR;
extern const uint16    CopyCounter_ADDR;
extern const uint16    WriteFinnished_ADDR;
extern const uint16    SyncParam_ADDR;
extern const uint16    PPSyncParam_ADDR;
extern const uint16    CopySyncParamCh6O_ADDR;
extern const uint16    CopySyncParamCh7O;
extern const uint16    CopySyncParamCh8O;
extern const uint16    CopySyncParamCh7O_ADDR;
extern const uint16    CopySyncParamCh8O_ADDR;
extern const uint16    CopySyncParamCh8I_ADDR;
extern const uint16    Tone_HZ500_test;
extern const uint16    SilentBuffer_ADDR;
extern const uint16    SilentBuffer_End_ADDR;
extern const uint16    SchratchBuffer_ADDR;
extern const uint16    SchratchBuffer_End_ADDR;
extern const uint16    HZ500_test_ADDR;
extern const uint16    HZ500_test_end_ADDR;
extern const uint16    CopyChXOutp_OFFSET[NUMBER_OF_DSP_SLOTS];
extern const uint16    CopyChXInp_OFFSET[NUMBER_OF_DSP_SLOTS];
extern const uint16    CR16CopyChXOutp_ADDR0[NUMBER_OF_DSP_SLOTS];
extern const uint16    CR16CopyChXOutp_ADDR1[NUMBER_OF_DSP_SLOTS];
extern const uint16    CR16CopyChXOutp_ADDR2[NUMBER_OF_DSP_SLOTS];
extern const uint16    ChannelX_Start_Out_CON[NUMBER_OF_DSP_SLOTS];
extern const uint16    ChannelX_Start_In_CON[NUMBER_OF_DSP_SLOTS];
extern const uint16    ChannelX_End_In_CON[NUMBER_OF_DSP_SLOTS];
extern const uint16    ChannelX_In_OFFSET[NUMBER_OF_DSP_SLOTS];
extern const uint16    CR16CopyChXInp_ADDR0[NUMBER_OF_DSP_SLOTS];
extern const uint16    CR16CopyChXInp_ADDR1[NUMBER_OF_DSP_SLOTS];
extern const uint16    CR16CopyChXInp_ADDR2[NUMBER_OF_DSP_SLOTS];
extern const uint16    Outp_Buf_CHX_OFFSET[NUMBER_OF_DSP_SLOTS];
extern const uint16    Outp_Read_CHX_ADDR[NUMBER_OF_DSP_SLOTS];
extern const uint16    Inp_Write_CHX_ADDR[NUMBER_OF_DSP_SLOTS];

#endif /* GENDSP_H__ */
