#ifndef _OS_MAIL_H
#define _OS_MAIL_H

#include "maildef.h"
#include "tasks.h"
#include "../../common/include/rtxdef.h"

extern void SendMail(TaskIdType TaskId, BYTE Length, MailType * MailPtr);
extern void Direct_SendMail(TaskIdType TaskId, BYTE Length, MailType * MailPtr);
extern void SendMailP0(TaskIdType TaskId, PrimitiveType PrimitiveIdentifier);
extern void SendMailP1(TaskIdType TaskId, PrimitiveType PrimitiveIdentifier, BYTE Parm1);
extern void SendMailP2(TaskIdType TaskId, PrimitiveType PrimitiveIdentifier, BYTE Parm1, BYTE Parm2);
extern void SendMailP3(TaskIdType TaskId, PrimitiveType Primitive, BYTE Parm1, BYTE Parm2, BYTE Parm3);
extern void SendMailP4(TaskIdType TaskId, PrimitiveType Primitive, BYTE Parm1, BYTE Parm2, BYTE Parm3, BYTE Parm4);
extern void SendMailP5(TaskIdType TaskId, PrimitiveType Primitive, BYTE Parm1, BYTE Parm2, BYTE Parm3, BYTE Parm4, BYTE Parm5);
extern void SendMailP7(TaskIdType TaskId, PrimitiveType Primitive, BYTE Parm1, BYTE Parm2, BYTE Parm3, BYTE Parm4, BYTE Parm5, BYTE Parm6, BYTE Parm7);

extern void QueueCurrentMail(void);
extern BYTE ResumeQueuedMail(void);
extern boolean checkMail(void);
extern boolean MailQueueEmpty(void);
extern BYTE getMailLength(void);

#endif
