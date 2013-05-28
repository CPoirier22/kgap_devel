/*
 ********************************************************************
 *
 * Module:  faframe.h
 *
 *  Config-item:    ?
 *
 * Contents:    This file contains the various macros and definitions used
 *                  with the FA-frame structure.
 *                  The length calculating macros, use the arrays defined in
 *                  FAFRAME.C file. This is done to speed up the program. It
 *                  does how ever give mode data! This can be changed by
 *                  changing the macros.
 *
 *  Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef FA_FRAME_HEADER__
#define FA_FRAME_HEADER__

#include "../../../common/include/bitsdef.h"

extern const UByte CsArray[64];

/* extern const UByte CsSegmentToByteArray[]; */

#define Cs_CHANNEL_SEGMENT_SIZE     5
#define Cf_CHANNEL_SEGMENT_SIZE     8

#define SEGMENT_COUNT_TO_BYTE_COUNT(SegmentCount) CsSegmentToByteArray[SegmentCount]

#define FA_FRAME_SIGNAL_SIZE(DataLength)          CsArray[DataLength]

#define FA_FRAME_LENGTH_TO_SEGMENT_COUNT(FAFrameLength)  FAFrameLength / Cs_CHANNEL_SEGMENT_SIZE

#define SET_Nr(Nr)  (((Nr) & 0x07) << 5)
#define SET_Ns(Ns)  (((Ns) & 0x07) << 1)

#define FA_C_n_R_MASK               0x02

#define FA_ADR_NLF_SET              0x80
#define FA_ADR_NLF_CLEAR            0x00
#define FA_ADR_CLASS_U_LLN          0x00
#define FA_ADR_CLASS_A_LLN          0x10
#define FA_ADR_CLASS_B_UNASSIGNED   0x70
#define FA_ADR_SAPI_0               0x00
#define FA_ADR_SAPI_3               0x0C
#define FA_ADR_RESERVED             0x01

/*
#define FA_ADR_COMMAND              0x02
#define FA_ADR_RESPONSE             0x00
*/

extern UByte FA_ADR_COMMAND;
extern UByte FA_ADR_RESPONSE;

#define FA_ADDRESS_CLASS_B_REJECT   (FA_ADR_NLF_SET | FA_ADR_CLASS_B_UNASSIGNED | FA_ADR_SAPI_0 | FA_ADR_RESPONSE)

#define FA_CTRL_NUMBERED_INFO       0x00
#define FA_CTRL_RR                  0x01
#define FA_CTRL_RNR                 0x05
#define FA_CTRL_REJ                 0x09
#define FA_CTRL_SABM                    0x2F
#define FA_CTRL_DM                  0x0F
#define FA_CTRL_UI                  0x03
#define FA_CTRL_DISC                    0x43
#define FA_CTRL_UA                  0x63

#define FA_CTRL_SET_POLL            0x10
#define FA_CTRL_SET_FINAL           0x10
#define FA_CTRL_CLEAR_POLL          0x00
#define FA_CTRL_CLEAR_FINAL     0x00

#define FA_CONTROL_CLASS_B_REJECT   (FA_CTRL_RR | FA_CTRL_CLEAR_FINAL | SET_Nr(1))

#define FA_FILL_PATTERN             0xF0

#define FA_MORE                     0x02
#define FA_NO_MORE                  0x00
#define FA_NOT_EXTENDED             0x01
#define FA_EXTENDED                 0x00

#define FA_CONTROL_I                    0x00
#define FA_CONTROL_S                    0x01
#define FA_CONTROL_U                    0x03
#define FA_CONTROL_I_MASK           0x01
#define FA_CONTROL_S_MASK           0x0F
#define FA_CONTROL_U_MASK           0xEF
#define FA_CONTROL_S_n_U_MASK       0x03


#define FA_NLF_MASK                 0x01
#define FA_LLN_MASK                 0x07
#define FA_SAPI_MASK                    0x03
#define FA_MORE_MASK                    0x01
#define FA_LENGTH_MASK              0x3F
#define FA_Ns_n_Nr_MASK             0x07

#define GET_LLN_FROM_FA_FRAME(FAFrame) \
    ((*FAFrame >> 4) & FA_LLN_MASK)

#define GET_SAPI_FROM_FA_FRAME(FAFrame) \
    ((*FAFrame >> 2) & FA_SAPI_MASK)

#define GET_NLF_FROM_FA_FRAME(FAFrame) \
    ((*FAFrame >> 7) & FA_NLF_MASK)

#define GET_Ns_FROM_FA_FRAME(FAFrame) \
    ((*(FAFrame + 1) >> 1) & FA_Ns_n_Nr_MASK)

#define GET_Nr_FROM_FA_FRAME(FAFrame) \
    ((*(FAFrame + 1) >> 5) & FA_Ns_n_Nr_MASK)

#define GET_MORE_FLAG_FROM_FA_FRAME(FAFrame) \
    ((*(FAFrame + 2) >> 1) & FA_MORE_MASK)

#define GET_LENGTH_FROM_FA_FRAME_FIRST_SEGMENT(TheSignal) \
    ((((UByte *) TheSignal)[sizeof(SignalType) + 2] >> 2) & FA_LENGTH_MASK)

#define GET_LENGTH_FROM_FA_FRAME(FAFrame) \
    ((*(FAFrame + 2) >> 2) & FA_LENGTH_MASK)


struct FAFrameHeaderStruct
{
    UByte   Address,
    Control,
    Length;
};
typedef struct FAFrameHeaderStruct FAFrameHeaderType;

struct FAFrameTailStruct
{
    UByte   XCrc,
    YCrc;
};
typedef struct FAFrameTailStruct FAFrameTailType;

struct FAFrameDataStruct
{
    FAFrameHeaderType FAFrameHeader;
};
typedef struct FAFrameDataStruct FAFrameDataType;

#define getFAFrameDataTypeIE(signal) ((unsigned char*)signal + sizeof(FAFrameHeaderType))

struct RRFrameStruct
{
    FAFrameHeaderType FAFrameHeader;
    FAFrameTailType FAFrameTail;
};
typedef struct RRFrameStruct RRFrameType;

#endif /* FA_FRAME_HEADER__ */
