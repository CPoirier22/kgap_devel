/*
 ********************************************************************
 *
 * Module:      identify.h
 *
 *      Config-item:    ?
 *
 * Contents:    This file contains the process identifiers and related
 *                                      macros.
 *
 *      Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef IDENTIFIERS__
#define IDENTIFIERS__

#include "bitsdef.h"

#define PD_MASK                  0x0F
#define TI_MASK                  0xF0
#define TV_MASK                  0x70
#define TF_MASK                  0x80
#define LCN_MASK                 0x70
#define BCF_MASK                 0x80
#define LLN_MASK                 0x07
#define SAPI_MASK                0x30
#define HOV_MASK                 0x01
#define ULN_MASK                 0x0F
#define UPPER_PMID_MASK          0x0F
#define RPN_MASK                 0xF8

typedef UByte PMIDType[3];

#define SET_PMID(PMID, Address) \
    PMID[0] =       Address[0]; \
    PMID[1] =       Address[1]; \
    PMID[2] =       Address[2];


#define PRIMITIVE_OFFSET                (0x10)
#define PORTABLE_PART_PRIMITIVE_OFFSET  (0x80)

#define NUMBER_OF_PROCESSES             13

/* -------------------------------------------------------------------------- */
#define CPN_I_MASK   0x40
#define CPN_II_MASK  0x10
#define CPN_III_MASK 0x80

#define RPN_IN_MCEI_MASK   0x10 /* 0x78 Changed from 16 to 2 RFPs, why not only one ?,*/
#define LRPN_IN_MCEI_MASK  0xf0
#define CPN_IN_MCEI_MASK   0x80

#define CN_IN_MCEI_MASK    0x0f

#define LRPN_IN_RPN_MASK   0x0F
#define CPN_IN_RPN_MASK    0x10

#define LLID_MASK    0x3F

typedef UByte USNType[1];
typedef UByte XXEIType[4];
typedef UByte DLEIType[4];
typedef UByte MCEIType;
typedef UByte ULEIType[4];

typedef UByte PDType;           /* Using only four lowest bits  */
typedef UByte TIType;           /* Using only four highest bits */

#define SET_USN(XXEI, USN) (XXEI[0]=USN)

#define GET_PD(XXEI) (XXEI[3] & PD_MASK)
#define GET_TV(XXEI) ((XXEI[3] & TV_MASK) >> 4)
#define GET_TF(XXEI) ((XXEI[3] & TF_MASK) >> 7)

#define GET_TIPD(XXEI) (XXEI[3])

#define SET_TIPD(XXEI, TIPD) (XXEI[3]=TIPD)

#define CONV_DL_XX(XXEI, DLEI, TIPD) \
    XXEI[0] = DLEI[0]; \
    XXEI[1] = DLEI[1]; \
    XXEI[2] = DLEI[2]; \
    XXEI[3] = TIPD;

#define SET_XXEI(XXEI, PMID, PD, TV, TF) \
    XXEI[0] = PMID[0]; \
    XXEI[1] = PMID[1]; \
    XXEI[2] = PMID[2]; \
    XXEI[3] = ((PD) & PD_MASK) | \
              (((TV) << 4) & TV_MASK) | \
              (((TF) << 7) & TF_MASK);

#define SET_DLEI(DLEI, PMID, LCN, BCF, LLN, SAPI) \
    DLEI[0] = PMID[0]; \
    DLEI[1] = PMID[1]; \
    DLEI[2] = PMID[2]; \
    DLEI[3] = ((LLN) & LLN_MASK) | \
              (((SAPI) << 4) & SAPI_MASK);

#define GET_LLN(DLEI)                   (DLEI[3] & LLN_MASK)

#define GET_SAPI(DLEI)                  (DLEI[3] & SAPI_MASK)

#define GET_SAPI_n_LLN(DLEI)            (DLEI[3])

#define SET_SAPI_n_LLN(DLEI, LLN, SAPI) \
    DLEI[3]=((LLN) & LLN_MASK) | \
            (((SAPI) << 4) & SAPI_MASK);

#define GET_LCN_FROM_DLEI(DLEI) \
    ((DLEI[2] & LCN_MASK) >> 4)

#define GET_BCF(DLEI) \
    ((DLEI[2] & BCF_MASK) >> 7)

#define GET_BCF_FROM_MCEI(MCEI) \
    ((MCEI[2] & BCF_MASK) >> 7)

#define GET_LCN_FROM_MCEI(MCEI) \
    ((MCEI[2] & LCN_MASK) >> 4)

#define GET_RPN_FROM_MCEI(MCEI) ((MCEI & RPN_IN_MCEI_MASK) >> 3)
#define GET_CPN_FROM_MCEI(MCEI) ((MCEI & CPN_IN_MCEI_MASK) >> 7)
#define GET_CN_FROM_MCEI(MCEI) (MCEI & CN_IN_MCEI_MASK)

#define TEST_CPN_IN_MCEI(MCEI) (MCEI & CPN_IN_MCEI_MASK)

#define GET_CPN_I(Addr) ((Addr[2] & CPN_I_MASK) >> 6)
#define TEST_CPN_I(Addr) (Addr[2] & CPN_I_MASK)
#define GET_CPN_II(Addr) ((Addr[0] & CPN_II_MASK) >> 4)
#define TEST_CPN_II(Addr) (Addr[0] & CPN_II_MASK)
#define GET_CPN_III(Addr) ((Addr[1] & CPN_III_MASK) >> 7)
#define TEST_CPN_III(Addr) (Addr[1] & CPN_III_MASK)

#define GET_CPN_FROM_PMID(PMID) (((PMID[0] & 0x0F) == 0x0E) ? GET_CPN_II(PMID) : GET_CPN_I(PMID))
#define TEST_CPN_IN_PMID(PMID) (((PMID[0] & 0x0F) == 0x0E) ? TEST_CPN_II(PMID) : TEST_CPN_I(PMID))

#define ADDRESSCOPY(Dst,Src) \
   Dst[0]=Src[0]; \
   Dst[1]=Src[1]; \
   Dst[2]=Src[2]; \
   Dst[3]=Src[3]

typedef UByte RPNType;

#ifndef MAX_Allowed_Users
#define MAX_Allowed_Users                   10
#endif

#define SUBSCRIBTION_FILTER_PP_ON           1
#define SUBSCRIBTION_FILTER_FP_ON           2

typedef UByte LIDType;

#define MAX_PPID 2048
typedef U16Bits PPIDType;

/* -------------------------------------------------------------------------- */

#endif /* IDENTIFIERS__ */
