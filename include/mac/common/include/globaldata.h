/*
 This module contains global data used by the MAC layer in the RFP.
*/

#include "../../../common/include/_stddef.h"


/* LED States*/
#define LED_OFF           0x00
#define LED_ON              0x01
#define LED_OPERATING_BUSY      0x02
#define LED_OPERATING_ACTIVE    0x03
#define LED_OPERATING_NO_ACTIVE 0x04
#define LED_OPERATING_NO_SYNC 0x05

void ToggleRed(void);
void LogOutputMail(BYTE Destination, void * p);
void LedTimerHandler(void);
extern BYTE LogMailFlag;

