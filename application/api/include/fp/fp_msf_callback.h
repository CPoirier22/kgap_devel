#ifndef FP_MSF_CALLBACK
#define FP_MSF_CALLBACK

#include "fp_api.h"

/**
 * This function is called when a msf session or when a single msf has been released.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user 				The user sending the release reason.
 * @param releaseReason		The most normal one are: 0 normal release and 0x11 out of range, for further release reasons see the msf documentation.
 * @return void
 */
extern void msf_releaseIndReceived(PPIDType user, UByte releaseReason);

/**
 * This function is called when a msf session request has been send from a pp.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user 				The user sending the session request.
 * @param functionNumber 	Zero terminated ascii string containing the function number.
 * @return void
 */
extern void msf_msfsetupIndReceived(PPIDType user, char * functionNumber);

/**
 * This function is call when a keypress is send from a phone with a msf session active.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user			The user / phone pressing a key.
 * @param keyPressed	Ascii value for the key pressed, 0x31 is the numeric '1' key.
 * @return void
 */
extern void msf_infoIndReceived(PPIDType user, char keyPressed);

/*
 * This function is called when the user accept the msf session request, or if the mu bit is set and the phone auto accept the msf session request.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user			The user / phone accepting the session request.
 * @return void
 */
extern void msf_connectCfmReceived(PPIDType user);

/**
 * This function is called when a handset want to send a message to another handset, the application can route this message to the other handset using msf_setupreq_format2 or msf_setupreq_format1.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user           The user trying to send the msf
 * @param setupSpec2     Format 2 settings from the sender.
 * @param setupSpec3     Format 3 settigs from the sender.
 * @param alertPattern   Alert pattern from the sender
 * @param alertTone      The alert tone from the sender
 * @param alertTimeout   The alert timeout from the sender
 * @param displayTimeout The display timeout from the sender
 * @param dstId          The receiver of this message, zero terminated ascii string.
 * @param displayText    The display text from the sender.
 * @param callbackId     The callback id from the sender, often equal to user but not necessarily.
 * @see msf_setupreq_format1()
 * @see msf_setupreq_format2()
 * @return void
 */
extern void msf_outgMessageIndReceived(PPIDType user, UByte setupSpec2, UByte setupSpec3, UByte alertPattern, UByte alertTone, UByte alertTimeout, UByte displayTimeout, char * dstId, char * displayText, PPIDType callbackId);

/**
 * This function is called when a handset has send a ppstatus_ind to this fp.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user          The user sending this messages
 * @param statusType    The statustype of this message, some are reserved by Polycom devices, read more in the msf documentation to ensure compatibility.
 * @param data          The data in the message (could be NULL)
 * @param data_length   The length of the data pointer (could be 0)
 * @return UByte        The user should return 0 or 1 when this functions is called.<br>
 * If you have an active msf session return 1 if you want an acknowledge message to be send back to the pp, 0 if you don´t want to send an acknowledge message.<br>
 * If there are no active msf session an acknowledge will be send anyway, and the return value of this function will be ignored.
 */
extern UByte msf_ppstatus_ind_received(PPIDType user, UByte statusType, UByte * data, UByte data_length);

/**
 * This function is called when sending a msf broadcast, indicating if the broadcast has been send or discarded.
 * @param result		The status of the send broadcast. 1 if the broadcast has been send. 0 if it has been discarded.
 * @return void
 */
extern void msf_broadcast_cfm(UByte result);

/**
 * This function is called when an IWU To IWU element is received
 * @param data			The IWU To IWU element
 * @return void
 */
extern void msf_IWUToIWUReceived(unsigned char *data);

#endif
