#ifndef PP_VOICE_FUNCTIONS
#define PP_VOICE_FUNCTIONS

#include "pp_api.h"

/**
 * This function will initiate a new voice call, and dial "number".<br>
 * It´s required to be idle before calling this function.
 * @param number        The number to dial
 * @return void
 */
extern void pp_voice_call_user(char * number);

/**
 * This function will send a key to the fp, requires to be "voice connected" or "voice offhook".
 * @return  UByte   0 for success, different than 0 for error code.
 */
extern UByte pp_voice_sendKey(UByte key);

/**
 * This function will bring the phone in connect state, either accepting an incoming call or starting an outgoing call. If starting an outgoing call send digits of the number to dial afterwards.<br>
 * It´s required to be idle before calling this function.
 * @return  UByte   0 for success, different than 0 for error code.
 */
extern UByte pp_voice_offhook();

/**
 * This function will release the current call.
 * @return  UByte   0 for success, different than 0 for error code.
 */
extern UByte pp_voice_onhook();

#endif
