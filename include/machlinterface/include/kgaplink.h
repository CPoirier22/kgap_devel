#include "../../os/include/maildef.h"

typedef struct
{
    void (*sendMailToKgap) (MailType * mail, BYTE length, MailType* (*convert)(MailType * mail, BYTE * newLength));
    void (*receiveMailFromKgap) (MailType * mail, BYTE length);
}
KGAPLink;

