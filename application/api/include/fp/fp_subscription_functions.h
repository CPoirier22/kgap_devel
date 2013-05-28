#ifndef FP_SUBSCRIPTION_FUNCTIONS
#define FP_SUBSCRIPTION_FUNCTIONS

#include "fp_api.h"

/**
 * Calling this function will delete the user from the database, and delete the subscription in the handset if the handset is turned on and in lock.
 * @param user	The user to delete
 * @return UByte: 1 for success, 0 for failed (User does not exist).
 */
extern UByte fp_subscription_removeSubscription(PPIDType user);

/**
 * This function will do a database lookup for the given ipei and return the ppid.
 * @param ipei	The ipei to lookup
 * @return PPIDType: The macthing ppid or 0xffff if not found.
 */
extern PPIDType fp_subscription_lookupUserFromIpei(IPEIType ipei);

/**
 * This function will do a database lookup for the given ppid and copy the ipei to the dstIpei.
 * @param ppid		The ppid to lookup
 * @param dstIpei	The destination pointer for the ipei
 * @return UByte: 1 if the user was found and the ipei has been copied to dstIpei, 0 if the user was not found.
 */
extern UByte fp_subscription_lookupUserFromPPID(PPIDType ppid, IPEIType dstIpei);

/**
 * This function will return the number of pp's that are subscribed. Maximum 10 subscriptions are allowed.
 * @return UByte: The number of subscriptions.
 */
extern UByte fp_subscription_getNumberOfSubscriptions();

/**
 * This function will set the access code of the system.<br>
 * No access code use: 0xffffffff<br>
 * 1234 as access code use: 0xffff1234
 * @param Code_AC	The system access code
 * @return void
 */
extern void fp_subscription_setAccessCode(unsigned long Code_AC);

#endif
