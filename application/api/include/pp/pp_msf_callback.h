#ifndef PP_MSF_CALLBACK
#define PP_MSF_CALLBACK

#include "pp_api.h"
#include "../common/common_structures.h"

/**
 * This function is called when a msf format 1 message is received, the message is immediately released.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param setupSpec1        Contains the setupspec1 bits, see more in the msf documentation: 14035821_PA_021_extract.doc
 * @param displayText       Zero terminated text string
 * @param callbackNumber    Zero terminated text string */
extern void pp_msf_setupreq_format1_received(UByte setupSpec1, char * displayText, char * callbackNumber);

/**
 * This function is called when a msf format 2 message is received, this can be a single message or a session with or without automatic session connect, see more in parameter description.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param setupSpec1            Contains the setupspec1 bits, see more in the msf documentation: 14035821_PA_021_extract.doc
 * @param displayText           Zero terminated text string
 * @param callbackNumber        Zero terminated text string
 * @param setupSpec2            Contains the setupspec2 bits, see more in the msf documentation: 14035821_PA_021_extract.doc
 * @param setupSpec3            Contains the setupspec3 bits, see more in the msf documentation: 14035821_PA_021_extract.doc
 * @param alertConstruction     Contains the custom alert construction, see the alertConstructiontType.
 * @param displayTimeout        Display timeout in seconds
 * @param dateAndTime           Contains the date and time could be 0, see the dateAndTimeType.
 * @param sessionEstablished    If == 1, this is a session request (TC in spec1) with autoaccept (MU in spec2). If == 0 this can still be a session request (TC) but not with autoaccept (MU).
 * @see pp_msf_send_connect_cfm()
 * @see pp_msf_send_release_ind()
 * @return void
 */
extern void pp_msf_setupreq_format2_received(UByte setupSpec1, char * displayText, char * callbackNumber, UByte setupSpec2, UByte setupSpec3, alertConstructiontType alertConstruction, UByte displayTimeout, dateAndTimeType dateAndTime, UByte sessionEstablished);

/**
 * This function is called when a msf disp req is received, this requires an active msf session (msf format2 with TC set).
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param setupSpec1            Contains the setupspec1 bits, see more in the msf documentation: 14035821_PA_021_extract.doc
 * @param displayText           Zero terminated text string
 * @param callbackNumber        Zero terminated text string
 * @see pp_msf_send_release_ind()
 * @see pp_msf_send_keypad_ind();
 * @return void
 */
extern void pp_msf_DispReq_received(UByte setupSpec1, char * displayText, char * callbackNumber);

/**
 * This function is called when a msf release ind message is received, the msf session is now no longer active.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param reason                The release reason, 0 for normal, different than o for abnormal.
 * @return void
 */
extern void pp_msf_release_received(UByte reason);

/**
 * This function is called when a pp status req message is received, often a ppstatus ind is expected from the fp / applicatoin.
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 * @param statusType            Statustype: 0-255
 * @param data                  data bytes from 0-200
 * @param data_length           Number of databytes.
 * @see pp_msf_send_ppstatus_ind()
 * @return void
 */
extern void pp_msf_ppstatus_req_received(UByte statusType, UByte * data, UByte data_length);

/**
 * This function is called when the last ppstatus_ind has been received by the fp application layer. If you have an active msf session this message may be suppressed by the fp to optimize the data transfer rate (this is most normal if the fp wants to send data back).
 * <br>Refer to common/msf_description.h for an msf overview, and description of the most common msf cases.<br>
 */
extern void pp_msf_ppstatus_ind_ack();

/**
 * This function is called when a broadcast message has been received
 * @param data		The received data
 * @param length	The length of the received data. 0 - 20.
 * @return void
 */
extern void pp_msf_broadcast_received(UByte * data, UByte length);

#endif

