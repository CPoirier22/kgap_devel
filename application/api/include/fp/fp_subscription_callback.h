#ifndef FP_SUBSCRIPTION_CALLBACK
#define FP_SUBSCRIPTION_CALLBACK

#include "fp_api.h"

/**
 * This function is called when a user tries to subscribe to the system.
 * @param IPEI	The ipei for the user trying to subscribe.
 * @return UByte: if returning 1 the subscription will continue, if returning 0 the subscription will be rejected.
 */
extern UByte fp_subscription_allowSubscription(IPEIType IPEI);

/**
 * This function is called when a location registration is completed, either with or without success.
 * @param user		The ppid assigned to the user.
 * @param ipei		The ipei for the user that requested the location registration.
 * @param status	The status for the location registration 1 = succes, 0 = failed.
 * @see fp_subscription_locationRegistrationRequested()
 * @return void
 */
extern void fp_subscription_locationRegistrationFinished(PPIDType user, IPEIType ipei, UByte status);

/**
 * This function is called when a location registration has been requested.
 * @param user		Assigned id to the user
 * @param ipei		The users ipei
 * @see fp_subscription_locationRegistrationFinished()
 * @return UByte: if returning 1 the location registration will continue, if returning 0 the location registration will be rejected.
 */
extern UByte fp_subscription_locationRegistrationRequested(PPIDType user, IPEIType ipei);

#endif
