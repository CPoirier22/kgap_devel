#ifndef COMMON_APPLICATION_H_
#define COMMON_APPLICATION_H_

#include "../../include/hlkgap/dduos/include/dduos.h"

extern void handleKey(UByte key, UByte action, UByte ppfp);
extern void handleTunnelFromMac(UByte key, UByte action, UByte ppfp);

#define KEY_EVENT 20
#define USERRESULT_EVENT 22
#define STATEREAD_EVENT 23
#define FP_START_SUM_RES 24
#define MAC_APP_TUNNEL 25

typedef struct
{
	SignalType SignalHeader;
	UByte key;
	UByte action;	
}
KeyActionType;

#endif /*COMMON_APPLICATION_H_*/
