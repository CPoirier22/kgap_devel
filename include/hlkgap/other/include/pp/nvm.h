#ifndef _NVM_H__
#define _NVM_H__

#include "../../../../common/include/bitsdef.h"
#include "../../../common/include/sformat.h"
#include "../../../dduos/include/dduos.h"

#define TIPD_APPLICATION 0x08

typedef struct
{
    SignalType SignalHeader;
    UByte ReturnTIPD;
    UByte SubsNo;
    U16Bits DataTypes;
}
EeReadDataReqType;

#define getEeReadDataReqTypeDataPtr(signal) ((void **)((unsigned char*)signal + offsetof(EeReadDataReqType, DataTypes) + sizeof(U16Bits)))

typedef struct
{
    SignalType SignalHeader;
    UByte SubsNo;
    U16Bits DataTypes;
}
EeStoreDataReqType;

#define getEeStoreDataReqTypeIE(signal) ((unsigned char*)signal + offsetof(EeStoreDataReqType, DataTypes) + sizeof(U16Bits))

typedef struct
{
    SignalType  SignalHeader;
}
EeReadDataCfmType;

enum                            /* Bits in DataTypes */
{
    EEDT_Ipui = 0x0001u,
    EEDT_Park = 0x0002u,
    EEDT_SubsNo = 0x0004u,
    EEDT_Lal = 0x0008u,
    EEDT_Rfpi = 0x0010u,
    EEDT_ZapField = 0x0020u,
    EEDT_ServiceClass = 0x0040u,
    EEDT_UakAc = 0x0100u,
    EEDT_Ipei = 0X0200u,
    EEDT_PPEEPROMINRAM = 0X0400u,
    EEDT_ANYADDRESS = 0X0800u
};

enum
{
    EE_READ_DATA_req = 0x00,
    EE_READ_DATA_cfm = 0x01,
    EE_STORE_DATA_req = 0x04
};

void setAddressData(WORD Addr, BYTE Len);

#endif /* _NVM_H__*/
