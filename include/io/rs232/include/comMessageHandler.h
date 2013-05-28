#ifndef _COMMESSAGEHANDLER_H__
#define _COMMESSAGEHANDLER_H__

#include "../../../common/include/bitsdef.h"
#include "../../../os/include/maildef.h"

#define RETRY_FOREVER 255
#define RETRY_50_TIMES 50
#define NOASSIGNEDSEQNO 0

typedef struct
{
    int lastAcknowledgedSeqNo;
    WORD lastAssignedSeqNo;
    WORD currentMailSeqNo;
    BYTE maxRetries;
    int numberOfAcksReceived, numberOfSerialMails, numberOfResends, numberOfDefers;
    void (*handleMessage) (MailType * mail, unsigned int length, PrimitiveType primitive, unsigned short int time);
    void (*writeBytesToCOM) (UByte * data, unsigned int size, int sendIndex);
    void (*queueMessage) (BYTE Length, SerialMessageType * MailPtr);
    unsigned short int (*getTimeStamp)(void);
    void (*ackHandler)(WORD seqNo);
    int send_index;
}
COMMessageHandler;

COMMessageHandler *initComMessageHandler(void (*messageHandler) (MailType * mail, unsigned int length, PrimitiveType primitive, unsigned short int time), void (*writeBytesToCOM) (UByte * data, unsigned int size, int sendIndex), void (*enqueuer) (BYTE Length, SerialMessageType * MailPtr), unsigned short int (*getTimeStamp)(void), BYTE maxRetries, int sendIndex);
WORD getSeqNo(SerialMessageType * message);
Boolean sendSerialMail(COMMessageHandler * handler, MailType * mail, int length);
SerialMessageType *allocateSerialMessage(COMMessageHandler * handler, MailType * MailPtr, BYTE mailSize, BYTE * size);
void printStatistics(COMMessageHandler * handler, void (*printText) (char *), void (*printNumber) (int));

void receiveSerialMessageTCP(COMMessageHandler * handler, UByte * buffer, unsigned int size);
Boolean sendSerialMessageTCP(COMMessageHandler * handler, PrimitiveType primitive, SerialMessageType * message);
void receiveSerialMessageUDP(COMMessageHandler * handler, UByte * buffer, unsigned int size);
Boolean sendSerialMessageUDP(COMMessageHandler * handler, PrimitiveType primitive, SerialMessageType * message);

extern Boolean (*sendSerialMessageHandler)(COMMessageHandler * handler, PrimitiveType primitive, SerialMessageType * message);
extern void (*receiveSerialMessageHandler)(COMMessageHandler * handler, UByte * buffer, unsigned int length);

#endif
