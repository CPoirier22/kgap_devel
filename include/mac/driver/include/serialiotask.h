#ifndef _SERIALIO_TASK_H__
#define _SERIALIO_TASK_H__

#include "../../../os/include/maildef.h"

extern void sendMailSerial(MailType * MailPtr, BYTE mailSize);
extern void serialioTask(MailType * mail);
extern void setSerialIOLogger(void (*logger)(BYTE *, int ));
/*extern SignalBuffer *getSerialIOTaskSignalBuffer();*/
extern void deinitSerialIoTask(void);

#endif /* _SERIALIO_TASK_H__*/
