#ifndef PP_SUBSCRIPTION_FUNCTIONS
#define PP_SUBSCRIPTION_FUNCTIONS

#include "pp_api.h"

/**
 * This function will initiate the subscription towards the readableAri or ari (serial number) with the specified ac code.<br>
 * The status of the subscription will be delivered later in: pp_subscription_subscribeFinished() and if successful the pp_subscription_loginOk() function will be called afterwards (when finishing the login procedure).
 * @param subscriptionIndex     The subscription index in the eeprom to store the subscription if succeeding. Must be 1
 * @param readableAri           The readable ari to subscribe to, if 0 or strlen(readableAri)==0, this parameter is ignored and the ari value are used instead.
 * @param ari                   If the readble ari equals 0 of strlen(readbleAri)==0, this parameter is used as subscription target.
 * @param Code_AC               Ac code, 4 digits are supported specified as nibles in the 4 byte value.<br>
 *                              Examples:<br>
 *                              1) 4711 as ac code, use this value: 0xffff4711<br>
 *                              2) no ac code, use this value: 0xffffffff
 * @see pp_subscription_subscribeFinished()
 * @see pp_subscription_loginOk()
 * @return UByte    0 for success, different than 0 is an error code.
 */
UByte pp_subscription_subscribe(UByte subscriptionIndex, char * readableAri, char * ari,  unsigned long Code_AC);

/**
 * This function will start to search for bases. Results will be delivered in: pp_subscription_baseFound()<br>
 * Do not call this function from pp_system_init.
 * @see pp_subscription_baseFound()
 * @return UByte    0 for success, different than 0 is an error code.
 */
UByte pp_subscription_searchForBases();

/**
 * This function will stop the pp_subscription_searchForBases() request.
 * @see pp_subscription_searchForBases();
 * @return void
 */
void pp_subscription_stopSearch();

/**
 * This function will start the login procedure on the specified index. The pp needs to be subscribe before calling this function<br>
 * Subscription is stored in eeprom, so it's not necessary to subscribe on every power up, but login is required after each power up.<br>
 * When the login procedure is finished, this function will be called: pp_subscription_loginOk
 * @param subscriptionIndex     The subscription index the unit should login to (needs to be subscribed on this index). Must be 1.
 * @see pp_subscription_isIndexSubscribed()
 * @see pp_subscription_isBaseSubscribed()
 * @see pp_subscription_subscribe()
 * @see pp_subscription_loginOk()
 * @return UByte                0 for success, different than 0 is an error code.
 */
UByte pp_subscription_loginToBase(UByte subscriptionIndex);

/**
 * This function will lookup the ari to this subscription index in the eeprom.<br>
 * The result will be delivered in this function pp_subscription_ariResult()
 * @param subscriptionIndex     Index to lookup. Must be 1.
 * @see pp_subscription_ariResult()
 * @return void
 */
void pp_subscription_getAriResult(int subscriptionIndex);

/**
 * This function will delete the subscription data at the specified index.
 * @param index         The index to delete. Must be 1.
 */
void pp_subscription_delete(int index);

#endif
