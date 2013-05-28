#ifndef FP_VOICE_FUNCTIONS
#define FP_VOICE_FUNCTIONS

/**
 * All functions relevant for voice signaling. Those functionsare allowed to be call by 3.rd developers.
 */


#include "fp_api.h"

/**
 *This function will initiate a call from caller to called, the caller needs to be in offhook state. Caller will be in offhook state after voice_outgoingCallRequst has been called.
 *@param called the user to call.
 *@param caller the initiator of the call.
 *@see voice_outgoingCallRequest()
 *@return 1 call initiated, 2 called user busy, 3 called user unknown.
 */
extern UByte voice_callUser(PPIDType called, PPIDType caller);

/**
 *This function updates the display for the user, the user needs to be active in a voice call, otherwise the function will not have any affect.
 *@param user		The user we want to update the display
 *@param display 	The actual display text, zero terminated ascii string.
 *@return UByte 0 if ok, different than 0 errorcode.
 */
extern UByte voice_updateDisplay(PPIDType user, char * display);

/**
 * This function disconnects the user from the voice call.
 * @param user      The user we want to disconnect
 * @return UBYte    0 if ok, different than 0 errorcode.
 */
extern UByte voice_disConnectUser(PPIDType user);

#endif
