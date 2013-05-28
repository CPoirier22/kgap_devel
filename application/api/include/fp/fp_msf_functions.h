#ifndef FP_MSF_FUNCTIONS
#define FP_MSF_FUNCTIONS

#include "fp_api.h"

/**
 * This functions sends a msf to the selected user according to our msf documentation.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param to			The selected user
 * @param setupSpec1	use msf_help_generateSetupSpec1
 * @param display		The display text, zero terminated ascii string.
 * @param callbackId	The callback number to be shown in the receiver handset, zero terminated ascii string, use zero termination for no callback id.
 * @see msf_releaseIndReceived()
 * @see msf_help_generateSetupSpec1()
 * @return UByte 0 for msf send actual delivery status will arrive lator in msf_releaseIndReceived, different than 0 contains error code.
 */
extern UByte msf_setupreq_format1(PPIDType to, UByte setupSpec1, char * display, PPIDType callbackId);

/**
 * This functions sends a msf to the selected user according to our msf documentation.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param to				The selected user
 * @param setupSpec1		use msf_help_generateSetupSpec1
 * @param display			The display text, zero terminated ascii string.
 * @param callbackId		The callback number to be shown in the receiver handset, zero terminated ascii string, use zero termination for no callback id.
 * @param setupSpec2		use msf_help_generateSetupSpec2
 * @param setupSpec3		use msf_help_generateSetupSpec3
 * @param alertConstruction alert settings, see struct details.
 * @param displayTimeout	Specifies in seconds how long DisplayText shall be shown on the display of the PP before it is replaced by the standby text. Only used if TC = 0. The value 00h indicates not present. If not present the DisplayText will stay shown until a new MSF setup or until the PP is operated by its user.
 * @param dateAndTime		date and time settings, see struct details.
 * @see msf_releaseIndReceived()
 * @see msf_help_generateSetupSpec1()
 * @see msf_help_generateSetupSpec2()
 * @see msf_help_generateSetupSpec3()
 * @see #alertConstructiontType
 * @see #dateAndTimeType
 * @return UByte 0 for msf send actual delivery status will arrive lator in msf_releaseIndReceived, different than 0 contains error code.
 */
extern UByte msf_setupreq_format2(PPIDType to, UByte setupSpec1, char * display, PPIDType callbackId, UByte setupSpec2, UByte setupSpec3, alertConstructiontType alertConstruction, UByte displayTimeout, dateAndTimeType dateAndTime);

/**
 * This function can be called when the user has requested a msf session received in: msf_msfsetupIndReceived
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user	The user to send a connect res to.
 * @see msf_msfsetupIndReceived()
 * @return UByte 0 for succes, different than 0 for error.
 */
extern UByte msf_send_CONNECT_res(PPIDType user);


/**
 * This function will updated the display for the selected user, this function must only be called when we have an active msf session, otherwise nothing will happen.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param displayText	The actual displayText, zero terminated ascii string.
 * @param callbackNo	The callback number to be shown in the receiver handset, zero terminated ascii string, use zero termination for no callback id.
 * @param user			The selected user
 * @param setupSpec		use msf_help_generateSetupSpec1
 * @see msf_help_generateSetupSpec1
 * @return void
 */
extern void msf_send_DispReq(char * displayText, char * callbackNo, PPIDType user, UByte setupSpec);


/**
 * This function will disconnect the active msf session with the user, if no active session nothing will happen.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param user				The user to disconnect
 * @param releaseReason 	The release reason to send to the user.
 * @return UByte: 1 for succes, 0 for error.
 */
extern UByte msf_send_ReleaseReq(PPIDType user, UByte releaseReason);

/**
 * This function will send s ppstatusreq message to the user with the specified statustype and the suplied data.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param to                The user to receive the message
 * @param statusType        The statustype of the message
 * @param data              The raw data bytes to be send (can be NULL)
 * @param dataLength        The length of the data pointer (can be 0) 0-100 bytes
 * @return UByte            0 for success and different than 0 for error code.
 */
extern UByte msf_send_ppstatusReq(PPIDType to, UByte statusType, UByte * data, UByte dataLength);

/**
 * This function will send a msf broadcast to all connected PP's.
 * <br>It is only possible to send one broadcast at a time. If calling this method before the previous broadcast has been send, the current broadcast will be discarded.
 * <br>A callback to msf_broadcast_cfm indicates if the broadcast has been send.
 * @param data				The raw bytes to send
 * @param length			The length of the data pointer. Maximum of 20 bytes.
 * @param repetitions		The number of times the broadcast should be repeated
 * @see msf_broadcast_cfm()
 * @return UByte			1 if the length is in range. Else 0.
 */
extern UByte msf_send_broadcast(UByte *data, UByte length, UByte repetitions);

#endif


