#ifndef PP_APPLICATION_H_
#define PP_APPLICATION_H_

#include "../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../include/mac/driver/include/pp/hsccf.h"
#include "../../../include/mac/eeprom/include/fnvm.h"

#define MSFInd 0x01
#define HandsetEMC PP_EepromInRam.FactoryEmc

typedef enum {
    CISS_RELEASED,         /* Call Independent Supplementary Services*/
    CISS_SETUP_RECEIVED,   /* used for MSF (Meassage Service Functions)*/
    CISS_CONNECTIONPENDING,
    CISS_CONNECT
} CissStateType;

typedef struct
{
    SignalType SignalHeader;
    UByte length;
}
AppMSFType;

#define getAppMSFTypeIE(signal) ((unsigned char*)signal + offsetof(AppMSFType, length) + sizeof(UByte))

typedef struct
{
  BYTE RPN;
  BYTE RSSI;
} AlarmKeyElementType;

typedef struct
{
  BYTE AlarmKey;  /**/
  AlarmKeyElementType  Base[OTHERBASETABLESIZE+1];
} AlarmKeyType;

void SendSsSetup (void);

#endif /*PP_APPLICATION_H_*/
