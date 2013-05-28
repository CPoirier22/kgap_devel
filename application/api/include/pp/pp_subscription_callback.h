#ifndef PP_SUBSCRIPTION_CALLBACK
#define PP_SUBSCRIPTION_CALLBACK

#include "pp_api.h"

/**
 * This function is called when the pp is in search mode and a new base is found.<br>
 * Suggested actions: <br>
 * 1) call pp_subscription_subscribe()<br>
 * 2) ignore, you will be noticed when the next base is found
 * @param readableAri       The found fp as readable ari
 * @param ari               The foudn fp as 5 byte ari (serial number)
 * @see pp_subscription_subscribe()
 * @see pp_subscription_searchForBases()
 * @return void
 */
void pp_subscription_baseFound(char * readableAri, char * ari);

/**
 * This function is called when the pp is finished with the location registration procedure. The pp is now ready to establish and receive voice and msf calls.
 * @param standbyText       The standby text received from the fp
 * @return void
 */
void pp_subscription_loginOk(char * standbyText);

/**
 * This function is called when the pp subscription request is  finished.
 * @param status            The status of the subscription, 0 for success, 1 for internal error, 2 for external error (fp reject or communication error)
 * @see pp_subscription_subscribe()
 * @return void
 */
void pp_subscription_subscribeFinished(UByte status);

/**
 * This function is called when the subscription / login status is changed.
 * @param status            The new status of the subscription.<br>
 * @param index             The subscription index of the subscription.<br>
 * An combination of those bits:<br>
 * SS_Locked = 0x01u<br>
 * SS_Subscripted = 0x02u<br>
 * SS_LocRegSucceeded = 0x04u<br>
 * @return void
 */
void pp_subscription_statusReceived(UByte status, UByte index);

/**
 * This function is called when the pp_subscription_getAriResult() function is finished.
 * @param readableAri       The result as a readable ari (could be "" if no unit found).
 * @param ari               The result as a 5 byte serial number
 * @param index             THe index of the result equal to the requested index, or 0xff if the requested index is empty / invalid.
 * @see pp_subscription_getAriResult()
 * @return void
 */
void pp_subscription_ariResult(char * readableAri, char * ari, UByte index);

/**
 * This function is called when pp_subscription_delete(int index) function is finished.
 * @ param status   The result of the delete request 0 for succes. 1 for failure.
 * @return void
 */
void pp_subscription_deleted(UByte status);

#endif
