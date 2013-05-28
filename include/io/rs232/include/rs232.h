#ifndef RS232_H_
#define RS232_H_

#include "../../../common/include/_stddef.h"
#include "../../../os/include/maildef.h"

extern int initSerial(const char *com_id,
                          void (*mailArrived)(int comID, const char *data, int size, unsigned short int time),
                          void (*messageArrived)(int comID, const char *data, int size),
                          void (*traceArrived)(int comID, const char *data, int size),
                          void (*dduosArrived)(int comID, const char *data, int size),
                          void (*randomArrived)(int comID, const char *data, int size),
                          void (*traceJVMArrived)(int comID, const char *data, int size),
                          void (*recordMacToKgapArrived)(int comID, const char *data, int size),
                          void (*recordKgapToMacArrived)(int comID, const char *data, int size),
                          BOOLEAN RESEND);

extern int checkSerial(void);
extern void sendComMail(int comID, MailType * MailPtr, unsigned int length);
extern void seriealThread(void *p);
#endif /*RS232_H_ */
