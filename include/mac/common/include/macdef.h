#ifndef __MACDEF_H
#define __MACDEF_H
/*****************************************************************************
* Project   : DECT                                                           *
* Module    : MAC configuration definition module.                           *
* Reference :                                                                *
* Type      : Headerfile for definition of MAC configuration.                *
* Function  :                                                                *
* Systems   : Base,Handset                                                   *
*----------------------------------------------------------------------------*
* Copyright (c) 1994 by RTX Research Aps.                                    *
* $Header:   K:/ph/srclib/mac/basis/archive/h/MACDEF.H_V   1.3.2.0   May 06 2003 12:33:36   on  $ *
*****************************************************************************/

/*#include "../../../common/include/_stddef.h"*/

#define WATCH_DOG_COUNTER_VAL 255

#define NOSTANDARDXCRC
#define CT0HEADNR 0
#define CT1HEADNR 1
#define NTHEADNR  3
#define QTHEADNR  4
#define MTHEADNR  6
#define FMTHEADNR 7
#define PTHEADNR  7

#define CT0HEAD 0x00
#define CT1HEAD 0x20
#define QTHEAD  0x80
#define NTHEAD  0x60
#define MTHEAD  0xc0
#define FMTHEAD 0xe0
#define PTHEAD  0xe0

#define Q2PATT 0x01
#define Q1PATT 0x10
#define NOBFIELDPATT  0x0e
#define IN_BFIELDPATT 0x00

#define ACCESS_REQ            0x00
#define BEARER_HO_REQ         0x01
#define CONNECTION_HO_REQ     0x02
#define BEARER_CFM            0x04
#define BEARER_WAIT           0x05
#define BEARER_ATTRIBUTES_REQ 0x06
#define BEARER_ATTRIBUTES_CFM 0x07
#define BEARER_RELEASE        0x0f

#define ADV_ACCESS_REQ        0x10
#define ADV_BEARER_HO_REQ     0x11
#define ADV_CONNECTION_HO_REQ 0x02
#define ADV_BEARER_CFM        0x14
#define ADV_BEARER_WAIT       0x15
#define ADV_ATTRIBUTES_T_REQ  0x16
#define ADV_ATTRIBUTES_T_CFM  0x17
#define ADV_BANDWIDTH_T_REQ   0x18
#define ADV_BANDWIDTH_T_CFM   0x19
#define ADV_CHANNEL_LIST      0x1a
#define ADV_BEARER_RELEASE    0x1f


#define MAC_ALERT_REQ 0x08



#define ZERO_PAGE_LENGTH       0
#define SHORT_PAGE_LENGTH     20
#define FULL_PAGE_LENGTH      36
#define LONG_PAGE_LENGTH(x) (x*36)




#define RSSI_TO_HIGH         1
#define HSCCF_RELEASE        2
#define ACRC_OR_RELEASE_1    3
#define FT_RELEASE_1         4
#define WRONG_FIRST_RESPONS  5
#define NO_CONFIRM_REC       6
#define ERROR_IN_OTHER       7
#define ENCRYPTION_FAIL      8
#define WRONG_ATTRIBUTES_RES 9
#define WRONG_FIRST_RESPONS_2 0xa
#define WRONG_FIRST_RESPONS_3 0xb
#define MAC_MODIFICATION_FAIL 0xc

#define NO_WAIT_RFP_BUSY     0x0d
#define ACRC_OR_RELEASE_10   0x0e
#define ACRC_OR_RELEASE_11   0x0f


typedef enum                    /* 1 byte */
{
    bearer_rel_UNKNOWN,
    bearer_rel_BEARER_REDUCE_CAP,
    bearer_rel_CONNECTION_RELEASE,
    bearer_rel_BEARER_SETUP_FAIL,
    bearer_rel_BEARER_HOV_COMPLETED,
    bearer_rel_ATTEMPT_HOV_TO_NEW_CLUSTER,
    bearer_rel_TIMEOUT_SIGNAL_LOSS,
    bearer_rel_TIMEOUT_HANDSHAKE_SIGNAL,
    bearer_rel_SLOT_TYPE_UNACCEPTABLE,
    bearer_rel_MAC_SERVICE_UNACCEPTABLE,
    bearer_rel_RFP_BUSY,
    bearer_rel_REVERSE_DIRECTION,
    bearer_rel_DUPLICATE_PMID,
    bearer_rel_PMID_UNACCEPTABLE,
    bearer_rel_RESERVED1,
    bearer_rel_RESERVED2,
    bearer_rel_OTHER_SIDE1 = 0x10,
    bearer_rel_OTHER_SIDE2 = 0x20,
    bearer_rel_OTHER_SIDE3 = 0x30,
    bearer_rel_OTHER_SIDE4 = 0x40,
    bearer_rel_OTHER_SIDE5 = 0x50,
    bearer_rel_OTHER_SIDE6 = 0x60,
    bearer_rel_OTHER_SIDE7 = 0x70,
    bearer_rel_OTHER_SIDE8 = 0x80,
    bearer_rel_OTHER_SIDE9 = 0x90,
    bearer_rel_OTHER_SIDEA = 0xA0,
    bearer_rel_OTHER_SIDEB = 0xB0,
    bearer_rel_OTHER_SIDEC = 0xC0,
    bearer_rel_RELASE_FROM_UPPER
} Enum_eBearerReleaseCause;

typedef BYTE eBearerReleaseCause;



#define ENC_START_REQ        0x50
#define ENC_START_CONF       0x51
#define ENC_START_GRANT      0x52


#define QUA_FT_REQ_PPR       0x37       /* next parameter must be 0x0F see ETS. 300-175-3 V1.4.2 table 50*/
#define QUA_PT_CFM_PPR       0x37       /* next parameter must be 0x0F*/

#define QUA_PT_REQ_PPR       0x37       /* next parameter must be 0x00 see ETS. 300-175-3 V1.4.2 table 50*/
#define QUA_FT_CFM_PPR       0x37       /* next parameter must be 0x00*/


/*--- Mac layer test messages ---*/

#define MACTEST_FORCED_TX 0x0
#define MACTEST_LOOPBACK 0x1
#define MACTEST_DIVERSITY_CTRL 0x2
#define MACTEST_FORCE_BEARER_HANDOVER 0x3
#define MACTEST_ESCAPE 0x4
#define MACTEST_NETWORK_TEST 0x5
#define MACTEST_CLEAR 0xf
#define MACTEST_ENABLE 0x10


#define MAC_SUPER_VISION_TIME 90

#endif
