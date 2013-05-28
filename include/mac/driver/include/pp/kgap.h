#ifndef __KGAP_H
#define __KGAP_H

#include "../../../../common/include/_stddef.h"
#include "../../../../io/serial/include/rs232_l2.h"
#include "../../../../os/include/maildef.h"

void ResetHandset(void);
void __set_PSR_I_bit();
void RouteMailBiL4(MailType * mail, BYTE size);

#endif
