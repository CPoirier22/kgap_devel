#ifndef OS_LIST_H_
#define OS_LIST_H_

#include "../../common/include/rtxdef.h"
#include "tasks.h"

typedef struct MailQueue
{
    void *head;
    void *tail;
    int size;
} MailQueue;

void initMailQueue(MailQueue* mailQueue);
void* allocateMailQueueElement(TaskIdType taskId, BYTE length, MailType *mail);
void deallocateMailQueueElement(void* queueElement);

void queue_last(MailQueue* mailQueue, void* queueElement);
void* remove_head(MailQueue* mailQueue);
void remove_element(MailQueue* mailQueue, void* queueElement);

MailType* getMailFromQueueElement(void* queueElement);
TaskIdType getDestinationFromQueueElement(void* queueElement);
BYTE getLengthFromQueueElement(void* queueElement);

MailQueue* findAndRemove(MailQueue* source, BYTE (*found)(void* queueElement, BYTE param), BYTE param);
int numberOfElements(MailQueue* queue);
char* printQueue(MailQueue* queue);

#endif /*OS_LIST_H_*/
