/*
 ********************************************************************
 *
 * Module: app_util.h
 *
 * Config-item: ?
 *
 * Contents: Definition of common utility functions on the application layer.
 *
 * Author: Kirk telecom / HN
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef APP_UTIL_HEADER__
#define APP_UTIL_HEADER__

#include "bitsdef.h"
#include "../../hlkgap/app/include/apdbprim.h"

typedef UByte SecurityConfigType;

/*Security bitflags:*/
#define TermAccRightsAtAuthFail  0x01
#define KeyAllocAtSubsCreate     0x02
#define AuthAtLocReg             0x04
#define AuthAtIncCall            0x08
#define AuthAtOutCall            0x10



#define FunctionBit0            0x00000001      /*Basic MSF functions (Format I)*/
#define FunctionBit1            0x00000002      /*CLIP via SIO-port*/
#define FunctionBit2            0x00000004      /*MSF format II and mail from PP to PP*/
#define FunctionBit3            0x00000008      /*Location registration indication to GIM and SIO*/
#define FunctionBit4            0x00000010      /*System telephoneBook*/
#define FunctionBit5            0x00000020      /*IWU VOIP allowed (this means H323 is allowed)*/
#define FunctionBit6            0x00000040      /*PPStatus to posistion/long messages*/
#define FunctionBit7            0x00000080      /*Telemetric*/
#define FunctionBit8            0x00000100      /*MSF via NIF*/
#define FunctionBit9            0x00000200      /*Application CPU via SIO-port*/
#define FunctionBit10           0x00000400      /*IWU VOIP- Skinny allowed (to allow skinny FunctionBit5 and FunctionBit10 has to be TRUE)*/
#define FunctionBit11           0x00000800
#define FunctionBit12           0x00001000
#define FunctionBit13           0x00002000
#define FunctionBit14           0x00004000
#define FunctionBit15           0x00008000
#define FunctionBit16           0x00010000
#define FunctionBit17           0x00020000
#define FunctionBit18           0x00040000
#define FunctionBit19           0x00080000
#define FunctionBit20           0x00100000
#define FunctionBit21           0x00200000
#define FunctionBit22           0x00400000
#define FunctionBit23           0x00800000
#define FunctionBit24           0x01000000
#define FunctionBit25           0x02000000
#define FunctionBit26           0x04000000
#define FunctionBit27           0x08000000
#define FunctionBit28           0x10000000
#define FunctionBit29           0x20000000
#define FunctionBit30           0x40000000
#define FunctionBit31           0x80000000


extern SecurityConfigType SecurityConfig1;
extern SecurityConfigType SecurityConfig2;

void WriteSecurityConfig(SecurityConfigType SecurityConfig1);

void InitAppUtil(void);

char NibbleToChar(UByte Nibble);
UByte IPEIToString(UByte * IPEIString, UByte * PackedIPEI);
UByte PackedIPEIToIPEI(UByte * IPEI, UByte * PackedIPEI);
Boolean StringToIPEI(UByte * PackedIPEI, UByte * IPEIString);
void SendSubsDataReq(IPEIType IPEI, PMIDType RetAddr, ProcessIdType ReturnProcId);

typedef enum
{
    UNKNOWN = 0x80,
    MACTEST_RESET,
    WARMSTART,
    RESET_CCFP_TIMEOUT,
    WATCHDOG_RESET,
    DIVIDE_BY_ZERO_RESET,
    DDU_ERROR_RESET,
    CODED_FATAL_EX_RES,
    CLEAN_HEAP_RESET,
    LOAD_NVM_RESET,
    SIO_RESTART,
    PROG_ARI_RESET,
    NO_MASTER_SYNC_RESET,
    INFINITE_LOOP_ETC,
    DIP_DOWN_1,
    DIP_DOWN_2,
    DIP_DOWN_3,
    DIP_DOWN_4,
    LOST_CONTACT_WITH_IP,
    HANGING_INSTANCE              /*0x93*/
}
ForcePowerResetType;

void ForcePowerReset(ForcePowerResetType ResetReason);

PPIDType PMID2PPID(PMIDType Pmid);
void PPID2PMID(PMIDType * PMID, PPIDType PPID);
Boolean PMIDEQUAL(PMIDType PMID1, PMIDType PMID2);

char Convert2Bytes2One(char c1, char c2);

UByte LocalNo2String(UByte * String, UByte * LocalNo);
void String2LocalNo(UByte * LocalNo, UByte * String);
Boolean String2AC(UByte * ConvAC, UByte * ACString);
UByte AC2String(UByte * ACString, UByte * AC);

int readableAriToRfpi(char * readableAri, char * rfpi);

extern char *getReadableARI(UByte* rfpi);
extern void getReadableEPEI(char *strEPEI, BYTE IPEI_FromEEProm[]);
extern void memcpy5(BYTE * Dest, BYTE * Source);

#endif /* APP_UTIL_HEADER__ */
