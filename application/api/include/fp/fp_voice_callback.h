/**
 * All functions relevant for voice signaling. Those functions will be called from the kgap, and 3.rd developers can decide the following actions.
 */


#ifndef FP_VOICE_CALLBACK
#define FP_VOICE_CALLBACK

#include "fp_api.h"


/**
 *An outgoing call request from a handset has arrived.
 *Suggested actions: call the requested user using the function voice_callUser()
 *@param a 	The user requesting the outgoing call
 *@param b	The user to dial
 *@return void
 */
extern void voice_outgoingCallRequest(PPIDType a, PPIDType b);

/**
 *The called handset has now received the paging and is alerting and waiting for the user to answer or reject the call.
 *Suggested actions: update the display of the caller.
 *@param called		The called user, which is now alerting.
 *@param caller		The user who requested the outgoing call.
 *@see voice_updateDisplay()
 *@return void
 */
extern void voice_incommingCallAlerting(PPIDType called, PPIDType caller);

/**
 *The two users are now connected, by default the audio is routed. Suggested actions: update the displays of the 2 users using voice_updateDisplay()
 *@param called 	The called user, now in connect state.
 *@param caller 	The user who requested the outgoing call, now in connect state.
 *@see voice_updateDisplay()
 *@return void
 */
extern void voice_callConnected(PPIDType called, PPIDType caller);

/**
 *The call has now been disconnected, suggested actions: update the display of the last user or disconnect the last user.
 *@param disconnectedUser 	The user are now idle and disconnected from the call.
 *@param wasConnectedTo		This user is not connected to the other user anymore, but is still active, waiting for user disconnect or system disconnect.
 *@param reason				The reason for the disconnect, the most typical ones are normal call clearing or abnormal call release, the abnormal call release happens when the user goes out of range or the unit powers off.
 *@see voice_updateDisplay()
 *@return void
 */
extern void voice_callDisconnected(PPIDType disconnectedUser, PPIDType wasConnectedTo,UByte reason);

#endif
