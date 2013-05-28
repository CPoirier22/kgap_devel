#ifndef FP_API
#define FP_API

#include "../../../../include/common/include/identify.h"
#include "../../../../include/common/include/glibc.h"
#include "../../../../include/common/include/app_util.h"
#include "../../../../include/common/include/print_status.h"
#include "../../../../include/hlkgap/common/include/dispatch.h"
#include "../../../../include/hlkgap/dduos/include/dduos.h"
#include "../../../../include/hlkgap/app/include/apdbprim.h"
#include "../common/common_structures.h"


typedef enum
{
    idle,
    incommingcall,
    outgoingcall,
    connected,
    disconnecting
}
applicationState;

typedef enum
{
    msf_idle,
    msf_session_requested_from_pp,
    msf_connected,
    msf_release_pending
}
msf_state;

struct ApplicationInstanceStructure
{
    PMIDType pmid;
    applicationState state;
    msf_state msfState;
    PPIDType connectedTo;
    TimerType * timer;
};
typedef struct ApplicationInstanceStructure ApplicationInstanceType;

/**
 * This function returns the applicationinstance for the specified user, if the user is idle, a null pointer will be returned.
 * @param ppid	The user to lookup
 * @return ApplicationInstanceType: a pointer to the instancedata or a null pointer if no active instance.
 */
extern ApplicationInstanceType * getApplicationInstanceData(PPIDType ppid);

extern int getIntFromString(char * str);

#endif
