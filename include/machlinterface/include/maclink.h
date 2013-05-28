#ifndef maclink_h
#define maclink_h

#include "../../os/include/maildef.h"

typedef struct
{
    void (*sendMailToMac) (MailType * mail, BYTE length, MailType* (*convert)(MailType * mail, BYTE * newLength), int sessionID, UByte id);
    void (*receiveMailFromMac) (MailType * mail, BYTE length, int decode, int sessionID);
}
MACLink;

#endif /*maclink_h*/
