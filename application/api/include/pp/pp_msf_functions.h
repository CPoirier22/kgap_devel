#ifndef PP_MSF_FUNCTIONS
#define PP_MSF_FUNCTIONS

#include "pp_api.h"

/**
 * send a release ind to the fp, either to reject a session request (format2 with TC) or to disconnect an active session (format2 with TC).
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param reason            Reason to send to the fp.
 * @return UByte            0 for succes, 1 for fail
 */
extern UByte pp_msf_send_release_ind(UByte reason);

/**
 * Send a msf keypad ind to the fp, this requires an active msf sessoin.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param key               The key to send.
 * @see pp_msf_setupreq_format2_received()
 * @return UByte            0 for success, 1 for fail
 */
extern UByte pp_msf_send_keypad_ind(UByte key);

/**
 * Send a pp status ind to the fp.
 * <br>When not using MSF session, PP status indications are handled differently according to what kind of base the module is connected to.
 * <br>When connected to a kt4585 FP, it is possible to send up to 8 ppstatus_ind in a row. After this there should be waited for a call to pp_msf_ppstatus_ind_ack().
 * <br>When connected to a ip600v3 base, it is only possible to send one ppstatus_ind before waiting for an acknowledgment. If a ppstatus_ind is send before this, it will be discarded by the base.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param statusType        Statustype to send
 * @param data              Data to send: 0-100 bytes
 * @param dataLength        Number of databytes
 * @see pp_msf_ppstatus_req_received()
 * @return UByte    0 for succes, 1 for fail.
 */
extern UByte pp_msf_send_ppstatus_ind(UByte statusType, UByte * data, UByte dataLength);

/**
 * Send a connect_cfm signal to the fp, a session request needs to be received first.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @return UByte            0 for success, 1 for fail.
 */
extern UByte pp_msf_send_connect_cfm();

/**
 * Send a msf to destination. Function pp_msf_release_received will be called when the
 * sending is finished. The next MSF can be sent 500 ms after pp_msf_release_received
 * has been called.
 *
 * The msf facility is not intended for high frequency control. Use msf sessions instead
 * or use the data link facilities for maximum bandwidth.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param setupSpec2
 * @param setupSpec3
 * @param alertConstruction
 * @param displayTimeout
 * @param destination
 * @param display
 * @param callbackNumber
 * @see msf_help_generateSetupSpec2()
 * @see msf_help_generateSetupSpec3()
 * @see pp_msf_release_received()
 * @return void
 */
extern void pp_msf_send_outg_message_ind(UByte setupSpec2, UByte setupSpec3, alertConstructiontType alertConstruction, UByte displayTimeout, char * destination, char * display, char * callbackNumber);

/**
 * Send a msf session request to the fixed part. The session will be open and ready usage when the fp accepts, then this function will be called: pp_msf_DispReq_received
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param functionNumber Zero terminated ascii string representing the function number
 * @see pp_msf_DispReq_received
 * @return UByte - status: 0 for succes (the reqeust has been send to the fp, a connect cfm will be received later) different than zero equals error code.
 */
extern UByte pp_msf_send_setup_ind(char * functionNumber);


#endif

