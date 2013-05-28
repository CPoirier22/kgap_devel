/*
 ********************************************************************
 *
 * Module: comm_esc.h
 *
 * Config-item: ?
 *
 * Contents:    Header file for comm_esc.c.
 *
 * Author: ?Kirk telecom / BJR
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 *
 * $Header:   K:/ph/srclib/util/basis/archive/h/comm_esc.h_v   2.29.1.1   Nov 18 2003 08:55:06   on  $
 *
 * $Log:   K:/ph/srclib/util/basis/archive/h/comm_esc.h_v  $
 *
 *    Rev 2.29.1.1   Nov 18 2003 08:55:06   on
 * Initial version of IP 600
 *
 *    Rev 2.29.1.0   31 Jan 2000 16:22:40   bjr
 * Definition of Events and SubEvent moved to GIMPRIM.H.
 *
 *    Rev 2.29   19 Oct 1999 14:47:32   mth
 * changed TBReadDataCfm to TBReadDataInd
 *
 *    Rev 2.28   16 Sep 1999 12:36:30   klu
 * Added
 * ReadPPDatReq
 * ReadPPDatCfm
 *
 *
 *    Rev 2.27   31 Aug 1999 14:00:56   klu
 * Added    StandBySupplementReq = 0x34, StandBySupplementCfm = 0x35, StandBySupplmntReq   = 0x38, StandBySupplmntCfm   = 0x39
 * and
 * BearingModeReadReq= 0x50, BearingModeReadCfm= 0x51,BearingModeWriteReq= 0x52,BearingModeWriteCfm= 0x53.
 *
 *
 *
 *    Rev 2.26   27 Aug 1999 14:04:26   mth
 * corrected an error
 *
 *    Rev 2.25   26 Aug 1999 13:12:12   mth
 * Added new TelePhoneBook events
 *
 *    Rev 2.24   10 Aug 1999 12:37:44   BJR
 * Added SelectiveCableDelayMeasureReq to SystemOptionsEventType.
 *
 *    Rev 2.23   15 Jun 1999 09:14:26   BJR
 * Added SecurityConfigRWReq, SecurityConfigRWCfm, CallBlockRWReq and CallBlockRWCfm to SystemOptionsEventType.
 * Added RFPReadNVMReq, RFPReadNVMCfm, RFPWriteNVMReq, RFPWriteNVMCfm, RFPReadRAMReq, RFPReadRAMCfm, RFPWriteRAMReq,
 * RFPWriteRAMCfm, RFPInfoReq, RFPInfoCfm, RFPMultipleWriteNVMReq and RFPMultipleWriteNVMCfm to RfpManagementEventType.
 *
 *    Rev 2.22   08 Jun 1999 14:20:04   mth
 * Implemented Diagnostic features
 *
 *    Rev 2.21   04 Jun 1999 15:40:48   BJR
 * Changed RfpManagementEvent to RFPManagementEvent.
 *
 *    Rev 2.20   21 May 1999 10:43:36   BJR
 * Added RFP Management Event with sub-event RFPLoadCodeReq.
 *
 *    Rev 2.19   16 Feb 1999 17:14:14   BJR
 * Added SystemConfBackupReq and SystemConfBackupCfm.
 *
 *    Rev 2.18   15 Feb 1999 16:21:10   BJR
 * Removed SystemConfSlaveBackupReq and SystemConfSlaveBackupCfm.
 * Added NVMBackupReq, NVMBackupInd and NVMBackupRes.
 *
 *    Rev 2.17   27 Jan 1999 09:45:46   mth
 * Added 2 new subevents in DiagnosticEventType  - DiagnosticResetDnicErrorReq
 * and  DiagnosticResetDnicErrorCfm
 *
 *    Rev 2.16   18 Jan 1999 13:21:26   mth
 * Added DiagnosticEvent 0x27 and defined DiagnosticEventType
 *
 *    Rev 2.15   09 Dec 1998 10:22:30   gwr
 * StatusBiFifoReceived & StatusBiFifoTransmit added for debuging SDX CSLC BIFIFO
 *
 *    Rev 2.14   18 Nov 1998 07:44:40   gwr
 * A define is corrected
 *
 *    Rev 2.13   04 Nov 1998 13:16:38   gwr
 * New Userdata events & IwuCallControl events added
 *
 *    Rev 2.12   06 Oct 1998 16:32:06   gwr
 * Change of CCFP role implemented in default mode protocol
 *
 *    Rev 2.11   01 Oct 1998 13:39:16   gwr
 * IwuCallControlEvent, CcSetupLimReq &CcSetupLimCfm added
 *
 *    Rev 2.10   11 Sep 1998 11:57:42   gwr
 * Misselling corrected
 *
 *    Rev 2.9   10 Sep 1998 09:00:16   gwr
 * ReadUserOnLocalNo( of UserDataEventType ) added
 *
 *    Rev 2.8   08 Sep 1998 10:25:12   gwr
 * MsfPreRelReq & MsfAlertReq added
 *
 *    Rev 2.7   23 Jul 1998 13:13:04   gwr
 * LinkCmdModeReq is changed to prevent the SIO.EXE from making wrongfully restarts of older CCFP.
 *
 *    Rev 2.6   13 Jul 1998 10:18:28   gwr
 * Slave CCFP in Command Mode Events is changed.
 *
 *    Rev 2.5   08 Jul 1998 08:10:24   gwr
 * EnterSlaveCmdModeReq change to LinkCmdModeReq and extended to handle shift between the two Commandmode interfaces
 *
 *
 *    Rev 2.4   01 Jul 1998 11:28:56   gwr
 * EnterSlaveCmdModeReq, QuitSlaveCmdModeReq, SioInSlaveCmdModeTxDat, SioInSlaveCmdModeRxDat & CfmOnUnknownRequest added
 *
 *    Rev 2.3   12 Jun 1998 15:17:42   GWR
 * EnterCommandModeInd added
 *
 *    Rev 2.2   27 May 1998 16:28:22   GWR
 * Subevents :
 * CableDelaySlaveReadReq and CableDelaySlaveReadCfm introduced.
 * SystemConfSlaveBackupReq and SystemConfSlaveBackupCfm implemented.
 * CfmOnIlLegalRequest implemented.
 *
 *
 *    Rev 2.1   07 May 1998 14:02:54   GWR
 * Password facility introduced. Clean up after CCFP command mode. DCD supervision for testing
 * the need of a password. Modem dial and hang up made possible from default mode screen.
 *
 *
 *
 *    Rev 2.0   Sep 23 1997 17:22:12   HN
 * SubEvents for PP load added.
 *
 *    Rev 1.20   Aug 27 1997 15:19:20   SC
 * BlockCallReq&Cfm inserted.
 *
 *    Rev 1.19   Aug 15 1997 10:28:00   SC
 * StatusMessageInd corrected to 0x24
 *
 *    Rev 1.18   Aug 14 1997 13:53:00   SC
 * Changed SystemSoftwareVersionReadReq & Cfm to SystemInformationReadReq & Cfm
 *
 *    Rev 1.17   Jul 31 1997 10:36:44   SC
 * Added StatusEvent to SioEventType.
 * Added StatusEvents.
 * Removed EnterCommandModeCfm from ControlEventType.
 * Added SystemOptionsEvent from 0x2d to 0x37.
 *
 *    Rev 1.16   Jul 04 1997 10:39:10   SC
 * NILChar changed to 0x7F.
 *
 *    Rev 1.15   Jun 24 1997 15:00:40   SC
 * SystemFlashLoadReq added to SystemOptionsEvent.
 *
 *    Rev 1.14   Jun 18 1997 14:36:06   CB
 * Added Backup and Restore system options events
 *
 *    Rev 1.13   May 06 1997 13:44:18   CB
 * Test version status 970506.
 *
 *    Rev 1.12   Apr 24 1997 15:43:50   SC
 * EPT defined.
 * ControlEvent, MsfEvent, UserDataEvent, IwuDataEvent, SystemOptionsEvent defined.
 *
 *    Rev 1.11   Apr 16 1997 12:34:56   SC
 * Defined all dle control characters.
 *
 *    Rev 1.10   Apr 15 1997 15:54:44   SC
 * Dle Control characters revised.
 * EnqIdType added.
 *
 *    Rev 1.9   Apr 04 1997 08:55:46   SC
 * NAG values corrected.
 *
 *    Rev 1.8   Mar 11 1997 16:27:14   CB
 * New MSF event values.
 *
 *    Rev 1.7   Mar 11 1997 15:13:56   CB
 * New MSF event values.
 *
 *    Rev 1.6   Mar 06 1997 21:08:28   SC
 * EngChar, EtbChar added.
 * NagArgumentType added.
 *
 *    Rev 1.5   Mar 06 1997 16:53:54   SC
 * EscProtocolTypType udated,
 * MsfEventType added.
 *
 *    Rev 1.4   Jan 10 1997 08:21:04   BJR
 * Added EMR_Error to EscModeResultType.
 *
 *    Rev 1.3   Nov 23 1996 17:59:20   BJR
 * Moved ForceInCommandMode from COMM_F.
 *
 *    Rev 1.2   Nov 14 1996 18:50:34   BJR
 * Adapted new definition of the SIO protocol.
 * Moved def. of the controll characters from COMM_ESC.H.
 * Added CheckForEscDownload.
 *
 *    Rev 1.1   Nov 11 1996 09:48:54   BJR
 * Renamed ESPT_DiagnosticDump to ESPT_DebugDump.
 *
 *    Rev 1.0   Nov 04 1996 13:35:22   BJR
 * First revision.
 *
 ********************************************************************
 */

#ifndef COMM_ESC_H__
#define COMM_ESC_H__

#include "../../../../common/include/bitsdef.h"




#define DLE_LSB_BYTE_MASK  0x00ff
#define DLE_MSB_BYTE_MASK 0xff00


#define NulChar  0x00
#define SohChar    0x01
#define DleSohChar 0x0101
#define StxChar  0x02
#define DleStxChar 0x0102
#define EtxChar  0x03
#define DleEtxChar 0x0103
#define EotChar      0x04
#define DleEotChar   0x0104
#define EnqChar  0x05
#define AckChar    0x06
#define BelChar  0x07
#define BsChar   0x08
#define HtChar   0x09
#define LfChar   0x0a
#define VtChar   0x0b
#define FfChar   0x0c
#define CrChar   0x0d
#define SoChar   0x0e
#define SiChar   0x0f

#define Dc1Char  0x11
#define Dc2Char  0x12
#define Dc3Char  0x13
#define Dc4Char  0x14
#define NakChar    0x15
#define SynChar  0x16
#define EtbChar  0x17
#define DleEtbChar 0x0117
#define CanChar  0x18
#define EmChar   0x19
#define SubChar  0x1a
#define EscChar    0x1b
#define DleEscChar 0x011b
#define FsChar   0x1c
#define Gs    0x1d
#define RsChar   0x1e
#define DleRsChar    0x011e
#define UsChar   0x1f

#define EPT    0x40
#define NILchar      0x7f  /* Unused in ISO 8859-1 character set */




typedef enum
{
    PP2PC   = '1',
    PC2PP
} EnqIdType;

enum
{
    ESPT_DebugDump      = 0x20,
    ESPT_LogDump        = 0x21,
    ESPT_DataDump         = 0x22,
    ESPT_CodeDump       = 0x30,
    ESPT_NvmDump      = 0x31,
    ESPT_MsfMode        = 0x40,
    ESPT_RegistrationMode = 0x41,
    ESPT_SetupMode        = 0x42,
    ESPT_DiagnosticMode   = 0x43
};
typedef UByte EscProtocolTypType;

enum
{
    ESDT_File      = 0x01,
    ESDT_Console   = 0x02
};
typedef UByte DataTypType;

enum
{  TRR_Ok,
   TRR_UnspecifiedError
};
typedef UByte TransResultType;

typedef enum
{
    NAG_Busy    = 0x00,
    NAG_DataToSend,
    NAG_TransmissionError,
    NAG_Idle
} NagArgumentType;

typedef enum
{
    EMR_Ok            = 0x00,
    EMR_NotFinished   = 0x01,
    EMR_RecievedNak   = 0x02,
    EMR_RecievedEsc   = 0x03,
    EMR_Error         = 0x04
} EscModeResultType;


struct SioEventStruct
{
    unsigned char Event;
    unsigned char SubEvent;
    unsigned char Length;
    unsigned char Data[];
};
typedef struct SioEventStruct SioEventStructType;


Boolean RoomForDownload ( U16Bits DataLength, void * DataPtr, U16Bits NeededExtraRoom );
EscModeResultType CheckForEscDownload ( void );
void StartDownload ( EscProtocolTypType EscProtocolTyp, DataTypType DataTyp, char * FileName );
EscModeResultType EndDownload ( TransResultType TransResult );
EscModeResultType SendByteDownload ( UByte Byte );
EscModeResultType EndRecordDownload ( void );
EscModeResultType ContinueEscModeOperation ( void );
void ForceInCommandMode ( void );

#endif /* COMM_ESC_H__ */
