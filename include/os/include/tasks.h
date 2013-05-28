#ifndef _TASKS_H__
#define _TASKS_H__

#include "../../common/include/_stddef.h"
#include "maildef.h"

typedef BYTE TaskIdType;
typedef BYTE TimerIdType;

typedef enum
{
    REALPPTASK,
    REALFPTASK,
    REALCOMMONTASK,
    FUNCTION
} TaskFunctionType;

typedef struct
{
    void (*TaskAddress)(MailType *MailPtr);
    void (*handler)(MailType *MailPtr);
    TaskFunctionType TType;
}
TaskDefType;

typedef struct
{
    WORD Time;
    TimerIdType Next;
}
TimerRecordType;

#define T10_MS    1       /* Timer-constant for waiting 10 ms               */
#define T100_MS   10      /* Timer-constant for waiting 100 ms              */
#define T300_MS   30      /* Timer-constant for waiting 100 ms              */
#define T500_MS   50      /* Timer-constant for waiting 100 ms              */
#define T1_SEC    100     /* Timer-constant for waiting 1 second            */
#define T10_SEC   1000    /* Timer-constant for waiting 10 seconds          */
#define T100_SEC  10000   /* Timer-constant for waiting 100 seconds         */

#endif /* _TASKS_H__*/
