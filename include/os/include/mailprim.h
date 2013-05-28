#ifndef __MAILPRIM_H
#define __MAILPRIM_H
/******************************************************************************
* Project   : DECT
* Module    : General Mail primitive definition
* Reference :
* Type      : Headerfile containing global primitives
* Function  :
* Systems   : Base,Handset
* Comment   : Originates from GAP maildef.h, Feb 97.
*-----------------------------------------------------------------------------
* Copyright (c) 1996 by RTX Research A/S.
* $Header:   K:/ph/srclib/os/basis/archive/h/MAILPRIM.H_v   1.1.1.1.2.0   May 06 2003 12:42:56   on  $ *
*******************************************************************************/

#include "../../common/include/_stddef.h"
#include "../../common/include/bitsdef.h"
#include "../../mac/driver/include/pp/hscsf.h"

#define _0 no_longer_allowed_to_use

#define PELTOR_CONFERENCE_STATUS       0xd0

typedef BYTE PrimitiveType;

enum
{
    _MAC_CON_ind                         = 0x00,       /*  Mcei,Pmid,chf    RFP(CCF)  -> CCFP(DLC)*/
    _MAC_CO_DATA_req                     = 0x01,       /*  Mcei,SDU         CCFP(DLC) -> RFP(CCF)*/
    _MAC_CO_DATA_ind                     = 0x02,       /*  Mcei,SDU         RFP(CCF)  -> CCFP(DLC)*/
    _MAC_CO_DTR_ind                      = 0x03,       /*  Mcei             RFP(CCF)  -> CCFP(DLC)*/
    _MAC_DIS_req                         = 0x04,       /*  Mcei             CCFP(DLC) -> RFP(CCF)*/
    _MAC_DIS_ind                         = 0x05,       /*  Mcei,Reason      RFP(CCF)  -> CCFP(DLC)*/
    _MAC_PAGE_req                        = 0x06,       /*  PT,PFL,LPF,SDU   CCFP(DLC) -> RFP(CCF)*/
    _MAC_ENC_KEY_req                     = 0x07,       /*  Mcei, EncKey     CCFP(DLC) -> RFP(CCF)*/
    _MAC_ENC_EKS_ind                     = 0x08,       /*  Mcei, EncStatus  RFP(CCF)  -> CCFP(DLC)*/
    _CCF_ME_CDM_ind                      = 0x09,       /*                   RFP(LLME) -> CCFP(ME)*/
    _CCF_ME_CDV_ind                      = 0x0A,       /*                   RFP(LLME) -> CCFP(ME)*/
    _CCF_ME_CDV_res                      = 0x0B,       /* CabelDelay        CCFP(ME)  -> RFP(LLME)*/
    _CCF_ME_UPLANE_req                   = 0x0C,       /* Mcei, Un          CCFP(ME)  -> RFP(LLME)*/
    _CCF_ME_PRELOAD_req                  = 0x0D,       /* RFPI ..           CCFP(ME)  -> RFP(LLME)*/
    _CCF_ME_PRELOAD_cfm                  = 0x0E,       /*  ???              RFP(LLME) -> CCFP(ME)*/
    _CCF_ME_MFNO_ind                     = 0x0F,       /*                   RFP(LLME) -> CCFP(ME)*/
    _CCF_ME_MFNO_res                     = 0x10,       /* MultiFrameNumber  CCFP(ME)  -> RFP(LLME)*/
    _MAC_ME_DUMMYBEARER_ind              = 0x11,
    _MAC_ME_DUMMYBEARER_res              = 0x12,
    _CCF_ME_TEST_MODE_req                = 0x13,
    _MAC_CON_req                         = 0x14,       /* Mcei              PP(DLC) -> PP(CCF)*/
    _MAC_CON_cfm                         = 0x15,       /* Mcei              PP(CCF) -> PP(DLC)*/
    _MAC_RES_DLC_ind                     = 0x16,       /* Mcei*/
    _MAC_PAGE_ind                        = 0x17,       /**/
    _MAC_ENC_EKS_req                     = 0x18,       /* Mcei, Command     PP(DLC) -> PP(CCF)*/
    _MAC_ENC_EKS_cfm                     = 0x19,       /* Mcei, Status      PP(DLC) -> PP(CCF)*/
    _MAC_ME_CON_UPLANE_req               = 0x1A,       /* Mcei, Direction   PP(DLC) -> PP(LLME)*/
    _MAC_ME_DIS_UPLANE_req               = 0x1B,       /* Mcei, Direction   PP(DLC) -> PP(LLME)*/
    _MAC_ME_CONHAND_ind                  = 0x1C,       /* Mcei              PP(DLC) -> PP(LLME)*/
    _MAC_ME_PT_SYSTEM_req                = 0x1D,       /* PMID,PARK,PLI*/
    _MAC_ME_FT_SYSTEM_req                = 0x1E,       /* HL_Capabilities, RFPI*/
    _MAC_ME_FT_SYSTEM_ind                = 0x1F,       /* HL_Capabilities, RFPI*/
    _DL_DATA_ind                         = 0x20,
    _S_FRAME_req                         = 0x21,       /* DLC to LCE*/
    _S_FRAME_ind                         = 0x22,       /* CC to LCE*/
    _LCE_RELEASE_req                     = 0x23,       /* LCE to CC*/
    DL_BROADCAST_req                     = 0x24,       /* CC to LCE*/
    _DL_BROADCAST_ind                    = 0x25,       /* LCE to DLC*/
    SCAN_COMPLETE_ind                    = 0x26,       /* DLC to LCE*/
    _MNCC_SETUP_req                      = 0x27,   /* Layer 4 to NWK-CC*/
    _MNCC_SETUP_ACK_req                  = 0x28,       /* Layer 4 to NWK-CC*/
    _MNCC_CONNECT_req                    = 0x29,       /* Layer 4 to NWK-CC*/
    _MNCC_ALERT_req                      = 0x2A,       /* Layer 4 to NWK-CC*/
    _MNCC_RELEASE_req                    = 0x2B,       /* Layer 4 to NWK-CC*/
    _MNCC_RELEASE_res                    = 0x2C,       /* Layer 4 to NWK-CC*/
    _MNCC_MULTIDISPLAY_ind               = 0x2D,
    _MNCC_SETUP_ind                      = 0x2E,
    _MNCC_SETUP_ACK_ind                  = 0x2F,       /* NWK-CC to Layer 4*/
    _MNCC_REJECT_ind                     = 0x30,       /* NWK-CC to Layer 4*/
    _MNCC_CONNECT_ind                    = 0x31,       /* NWK-CC to Layer 4*/
    _MNCC_CONNECT_cfm                    = 0x32,       /* NWK-CC to Layer 4*/
    _MNCC_ALERT_ind                      = 0x33,       /* NWK-CC to Layer 4*/
    _MNCC_RELEASE_ind                    = 0x34,       /* NWK-CC to Layer 4*/
    CLIP_DATA_ind                        = 0x35,       /* NWK-CC to Layer 4*/
    _MNCC_RELEASE_cfm                    = 0x36,
    BUS_TX_MAIL                          = 0x37,       /* NWK-CC to Layer 4*/
    RX_INT_MAIL                          = 0x38,       /* Mail to be transferred on UART0*/
    ACRC_BEARERCFM                       = 0x39,       /* Byte received from UART0*/
    EE_WRITE_DEFAULT_req                 = 0x3A,
    EE_WRITE_req                         = 0x3B,       /* Data write to EEPROM request*/
    EE_READ_req                          = 0x3C,       /* Data read from EEPROM request*/
    EE_DATA_cfm                          = 0x3D,       /* Requested data delivered*/
    HOOK_OFF_req                         = 0x3E,       /* Mail requesting hook-off line condition*/
    HOOK_ON_req                          = 0x3F,
    UTT_ind                              = 0x40,
    MMI_EVENT_ind                        = 0x41,
    MESSAGE                              = 0x42,
    _EXTHOCOM_ind                        = 0x43, /* On ip1200 send ack to gw "ext ho done".*/
    _Link_Info_Ind                       = 0x44,
    RINGVOLTON_ind                       = 0x45,
    RINGVOLTOFF_ind                      = 0x46,
    DIGIT_SEND_cfm                       = 0x47,
    RING_TERMINATE_ind                   = 0x48,
    BEARER_AUDIO_req                     = 0x49,
    MAC_AUDIO_req                        = 0x4A,
    TONE_req                             = 0x4B,
    RING_req                             = 0x4C,       /* RingTone request*/
    KEY_ind                              = 0x4D,       /* A key is pressed in the keyboard*/
    _MNCC_REJECT_req                     = 0x4E,
    BUS_TRACE_EXT_req                    = 0x4F,       /* Extended bus trace request*/
    AUDIO_req                            = 0x50,
    BROADCAST_CHAN_ind                   = 0x51,       /* HS MAC-CSF to MAC-CCF*/
    ALERT_BROADCAST_req                  = 0x52,
    ALERT_BROADCAST_ind                  = 0x53,
    BMCLOWLEVELTEST_req                  = 0x54,
    MACLAYER_TEST_ind                    = 0x55,
    AUDIOCTRL_req                        = 0x56,       /* Handset audio path control*/
    _MNCC_SUBS_CREATE_req                = 0x57,
    _MNCC_SUBS_CREATE_cfm                = 0x58,
    MAC_SEARCH_req                       = 0x59,
    BEARER_SYNCINFO_req                  = 0x5A,
    BEARER_SYNCINFO_cfm                  = 0x5B,
    DISPLAY_CMD_req                      = 0x5C,
    TEST_CMD_req                         = 0x5D,
    LONGBROADCAST_req                    = 0x5E,
    LONGBROADCAST_ind                    = 0x5F,
    MAC_RESET_req                        = 0x60,
    AUDIOLINECTRL_req                    = 0x61,
    _MAC_CON_res                         = 0x62,
    HOOKON_cfm                           = 0x63,
    BUSYTONE_ind                         = 0x64,
    _MM_DETACH_ind                       = 0x65,
    TASK_CMD_req                         = 0x66,
    TASK_CMD_cfm                         = 0x67,
    TONE_VOL_req                         = 0x68,
    PLUGSTATE_ind                        = 0x69,
    PP_BEARER_ACKNOWLEDGED_RELEASE_IND   = 0x6A,
    SET_RPN                              = 0x6B,
    UI_CON_STATE_ind                     = 0x6C,
    DIGIT_NAL_req                        = 0x6D,
    DIGIT_NAL_cfm                        = 0x6E,
    BARRING_REJECT_req                   = 0x6F,
    _MNCC_SEARCH_RFPI_req                = 0x70,
    _MNCC_SEARCH_RFPI_ind                = 0x71,
    _MNCC_SEARCH_STOP_req                = 0x72,
    _MNCC_SUBSCRIPT_SEL_req              = 0x73,
    _MNCC_PROMPT_UPI_ind                 = 0x74,
    _MNCC_PROMPT_UPI_res                 = 0x75,
    _MNCC_SUBS_SELECT_cfm                = 0x76,
    _MNCC_SUBS_ABORT_req                 = 0x77,
    _MNCC_SUBS_STATUS_ind                = 0x78,
    _MNCC_SUBS_REMOVE_req                = 0x79,
    _MNCC_SUBS_REMOVE_cfm                = 0x7A,
    _MNCC_CALL_PROC_ind                  = 0x7B,
    _MNCC_MULTIKEYPAD_ind                = 0x7C,
    _MNCC_IWUTOIWU_ind                   = 0x7D,
    _MNCC_MULTIKEYPAD_req                = 0x7E,
    _MNCC_IWUTOIWU_req                   = 0x7F,
    _MNCC_SIGNAL_req                     = 0x80,
    _MNCC_SIGNAL_ind                     = 0x81,
    LINEPLUG_STATE_ind                   = 0x82,
    MULTIKEYPAD_NAL_cfm                  = 0x83,
    BATTERY_ind                          = 0x84,
    _RFPI_FOUND_ind                      = 0x85,
    _EXTERNAL_RFPI_FOUND_ind             = 0x86,
    PORT_CHANGE_ind                      = 0x87,
    VLOOP_MESS_ind                       = 0x88,      /* PP5 2G4 National*/
    HLKGAPTOMAC                          = 0x89,
    RANDOMREC                            = 0x8A,
    _MF_NO_JUMP                          = 0x8B,      /* Multi frame number jumping*/
    MAC_APPLICATION_TUNNEL			     = 0x8C,
    HW_interface_req                     = 0x8D,
    CONFERENCE_BEARER_req                = 0x8E,
    CONFERENCE_BEARER_cfm                = 0x8F,
    CONFERENCE_BEARER_ind                = 0x90,
    CONFERENCE_CHAN_req                  = 0x91,
#ifdef POSITION_APP
    FAST_RSSI_SCAN_END                   = 0x92,
#else
	_FILLER_92                           = 0x92,
#endif
    MNCL_UNITDATA_req                    = 0x93,
    MNCL_UNITDATA_ind                    = 0x94,
    LINE_IDLE_ind                        = 0x95,
    LINE_PROCEED_DIAL_req                = 0x96,
    NULLMSG                              = 0x97,
    TIMEOUT                              = 0x98,       /* Output from Timer*/
    INITTASK                             = 0x99,       /* First message to task*/
    PP_LOCKED_ind                        = 0x9A,       /* Portable Part locked indication*/
    MAC_WAKEUP_req                       = 0x9B,       /* UI to MAC-CSF*/
    BEARER_QUALITY_ind                   = 0x9C,       /* MAC-CSF to MAC-CCF*/
    BEARER_SCAN_ind                      = 0x9D,       /* MAC-CSF to MAC-CCF*/
    BEARER_SCAN_req                      = 0x9E,       /* MAC-CCF to MAC-CSF*/
    BROADCAST_CHAN_req                   = 0x9F,       /* MAC-CCF to MAC-CSF*/
    BEARER_req                           = 0xA0,       /* MAC-CCF to MAC-CSF*/
    ENC_BEARER_req                       = 0xA1,       /* MAC-CCF to MAC-CSF*/
    BEARER_cfm                           = 0xA2,       /* MAC-CSF to MAC-CCF*/
    BEARER_ind                           = 0xA3,       /* MAC-CSF to MAC-CCF*/
    BEARER_RELEASE_req                   = 0xA4,       /* MAC-CCF to MAC-CSF*/
    BEARER_RELEASE_cfm                   = 0xA5,       /* MAC-CSF to MAC-CCF*/
    BEARER_RELEASE_ind                   = 0xA6,       /* MAC-CSF to MAC-CCF*/
    BEARER_RECONN_req                    = 0xA7,       /* MAC-CCF to MAC-CSF*/
    BEARER_FAIL_ind                      = 0xA8,       /* MAC-CSF to MAC-CCF*/
    BEARER_DATA_req                      = 0xA9,       /* MAC_CCF to MAC-CSF*/
    BEARER_DTR_ind                       = 0xAA,       /* MAC-CSF to MAC-CCF*/
    BEARER_DATA_ind                      = 0xAB,       /* MAC-CSF to MAC_CCF*/
    BEARER_ENC_EKS_req                   = 0xAC,       /* MAC-CCF to MAC-CSF*/
    BEARER_ENC_EKS_ind                   = 0xAD,       /* MAC-CCF to MAC-CSF*/
    BEARER_ENC_EKS_cfm                   = 0xAE,       /* MAC-CCF to MAC-CSF*/
    BEARER_ENC_KEY_req                   = 0xAF,       /* MAC-CCF to MAC-CSF*/
    _DL_ESTABLISH_req                    = 0xB0,       /* LCE to DLC*/
    _DL_ESTABLISH_cfm                    = 0xB1,       /* DLC to LCE*/
    _DL_ESTABLISH_ind                    = 0xB2,       /* DLC to LCE*/
    _DL_RELEASE_req                      = 0xB3,       /* LCE to DLC*/
    _DL_RELEASE_cfm                      = 0xB4,       /* ?? to Bus*/
    _DL_RELEASE_ind                      = 0xB5,       /* DLC to LCE*/
    _DL_DATA_req                         = 0xB6,       /* DLC to LCE*/
    _MAC_ME_SARI_ind                     = 0xB7,       /* LCE to DLC*/
    BUS_TRACE_req                        = 0xB8,
    _FILLER_B9                           = 0xB9,
    BIL3_LOG_MAIL                        = 0xBA,
    BIL3_TMAIL                           = 0xBB,
    BIL3_MAIL_TEST                       = 0xBC,
    BIL3_CTRL_RECEIVED                   = 0xBD,
    BIL3_RESET_RECEIVED                  = 0xBE,
    EECACHE_WRITE_req                    = 0xBF,
    EECACHE_READ_cfm                     = 0xC0,
    EECACHE_READ_req                     = 0xC1,
    CHANGE_PP_STATUS                     = 0xC2,
    START_LOAD_OF_DSP                    = 0xC3,
    LOAD_DSP                             = 0xC4,
    END_LOAD_OF_DSP                      = 0xC5,
    SET_HPIC                             = 0xC6,
    REC_DSP_CMD                          = 0xC7,
    READ_DSP_DATA                        = 0xC8,
    SET_DSP_DATA                         = 0xC9,
    RESET_DSP                            = 0xCA,
    CONF_BEARER_RELEASE_cfm              = 0xCB,
    _FILLER_CC                           = 0xCC,
    _MAC_RFP_STATUS_ind                  = 0xCD,
    _MAC_DIS_cfm                         = 0xCE,
    FULLBROADCAST_req                    = 0xCF,
    LONGBROADCAST_SPLIT0_req             = 0xD0,       /* 0xD0*/
    LONGBROADCAST_SPLIT1_req             = 0xD1,       /* 0xD1*/
    MAC_DEBUG_MAIL                       = 0xD2,
    READ_RSSI_SCANNING_req               = 0xD3,
    READ_RSSI_SCANNING_cfm               = 0xD4,
    _FILLER_D5                           = 0xD5,
    _FILLER_D6                           = 0xD6,
    _FILLER_D7                           = 0xD7,
    _FILLER_D8                           = 0xD8,
    _FILLER_D9                           = 0xD9,
    _FILLER_DA                           = 0xDA,
    UI_DISPLAY_TEST                      = 0xDB,
    _FILLER_DC                           = 0xDC,
    _FILLER_DD                           = 0xDD,
    _FILLER_DE                           = 0xDE,
    PELTOR_FP_START_SUM_RES				 = 0xDF,
    RECORD_MAC_TO_KGAP					 = 0xE0,
    RECORD_KGAP_TO_MAC                   = 0xE1,
    _FILLER_E2	                         = 0xE2,
    PPREADUSER	                         = 0xE3,
    PPREADUSER_RES                       = 0xE4,
    READAC                               = 0xE5,
    READAC_RES                           = 0xE6,
    PELTOR_STATE_WRITE                   = 0xE7,
    PELTOR_STATE_READ_req                = 0xE8,
    PELTOR_STATE_READ_cfm                = 0xE9,
    SEL_SLOT_ind                         = 0xEA,
    PORT_OUT_req                         = 0xEB,
    AUDIOCTRL_CODEC_req                  = 0xEC,
    MACSTATUP_ind                        = 0xED,
    TRAP_STORE_req                       = 0xEE,
    PELTOR_FP_START_SUM                  = 0xEF,
    SERIEL_DATA_cfm                      = 0xF0,
    SERIALACK                            = 0xF1,
    SERIALMAIL                           = 0xF2,
    LASTPRIMITIVE                        = 0xF3,
    FIRST_LOCAL_PRIMITIVE_VAL            = 0xF4,
    FIRST_LOCAL_COMMON_PRIMITIVE         = 0xF5,
    _MAC_ME_FT_SYSTEM_cfm                = 0xF6,
    TRACEMAIL                            = 0xF7,
    JVMMAIL                              = 0xF8,
    TRACEJVM                             = 0xF9,
    PRIMITIVE_FA                         = 0xFA,
    MAILROUTERMAIL                       = 0xFB,
    PRIMITIVE_FC                         = 0xFC,
    PRIMITIVE_FD                         = 0xFD,
    MSFMAIL                              = 0xFE,
    BAT_SURVEILANCE_ind                  = 0xFF
};

#endif

