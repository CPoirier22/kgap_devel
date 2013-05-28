/*
 * msf_description.h
 *
 *  Created on: 04-08-2009
 *      Author: jjust
 */

#ifndef MSF_DESCRIPTION_H_
#define MSF_DESCRIPTION_H_

/** @file
 * <h2>Msf cases:</h2><br>
 * 1) Single msf message from fp to pp<br>
 * 2) Single msf message from pp to fp<br>
 * 3) Single msf message from pp tp pp (routed through fp)<br>
 * 4) Msf session pp initiated<br>
 * 5) Msf session fp initiated<br>
 * 6) Usage of msf session: keypresses and display update<br>
 * 7) Usage of msf session: data transfer with ppstatus ind/req<br>
 * 8) data transfer with ppstatus ind/req<br>
 * 9) Ending a session<br>
 *
 * <h3>1) Single msf message from fp to pp</h3><br>
 * <h4>1.1) simple message format 1:</h4><br>
 * On the fp calling this function #msf_setupreq_format1() <br>
 * will result in a call to this function on the pp: #pp_msf_setupreq_format1_received()<br>
 * After the request from the fp is completed a status / release reason is send to the fp, this function will be called: #msf_releaseIndReceived() <br>
 * <h4>1.2) format 2 with more features:</h4><br>
 * Format 2 can be used to create a more custom message and furthermore it can be used to establish session from the fp, read more under point 4-7 for sessions details.<br>
 * On the fp calling this function #msf_setupreq_format2() <br>
 * will result in a call to this function on the pp: #pp_msf_setupreq_format2_received()<br>
 * After the request from the fp is completed a status / release reason is send to the fp, this function will be called: #msf_releaseIndReceived() <br>
 * If this is a session request, the status / release will be postponed until the session is released.<br>
 * <br>
 *
 * <h3>2) Single msf message from pp to fp</h3><br>
 * On the pp calling this #pp_msf_send_outg_message_ind() function<br>
 * will result in a call to this function on the fp: #msf_outgMessageIndReceived()<br>
 * The fp can choose to route the msf to another user or just use the information in the message, to data transfer look at point 8.<br>
 * For routing look at next point 3.<br>
 * <br>
 *
 * <h3>3) Single msf message from pp to pp (routed through fp)</h3><br>
 * pp1 calls this function #pp_msf_send_outg_message_ind() with the number of pp2<br>
 * This will result in a call to this function on the fp: #msf_outgMessageIndReceived()<br>
 * Now the fp can route the msf to another pp using: #msf_setupreq_format1() or #msf_setupreq_format2()<br>
 * Resulting in call the equivalent function on pp2: #pp_msf_setupreq_format1_received() or #pp_msf_setupreq_format2_received()<br>
 * After the request from the fp to pp2 is completed a status / release reason is send to the fp, this function will then be called: #msf_releaseIndReceived() <br>
 * <br>
 * On the fp you can choose to check if the user exist with this function: #fp_subscription_lookupUserFromPPID() before sending the message.<br>
 * <br>
 * <h3>4) How to initialise Msf session from pp</h3><br>
 * On the fp calling this function: #pp_msf_send_setup_ind() will result in a call to this function: #msf_msfsetupIndReceived()<br>
 * To accept the request the fp has to call this function: #msf_send_CONNECT_res()<br>
 * To reject simple ignore the request or call this function: #msf_send_ReleaseReq()<br>
 * If accepting the session request this function will be called on the pp: #pp_msf_DispReq_received() this function will also be called afterwards when receiving display updates.<br>
 * If accepting the session request the pp and the fp will be in connection until one of the units disconnect.<br>
 * Read more about session usage under point 6 and 7.<br>
 * <br>
 * <h3>5) How to initialise Msf session from fp</h3><br>
 * Calling this function: #msf_setupreq_format2() with the right parameters will result in a session request.<br>
 * The session request can either force the pp to accept the session (mu bit) or it can wait for user / 3rd. application to accept the request before timeout.<br>
 * Read more about creating sessions in #msf_setupreq_format2()<br>
 * On the pp this function will be called: #pp_msf_setupreq_format2_received() read more in function description.<br>
 * If not auto accepted call this function on the pp to accept the session: #pp_msf_send_connect_cfm()<br>
 * Accepting will result in a call to this function on the fp: #msf_connectCfmReceived()<br>
 * If accepting the session request the pp and the fp will be in connection until one of the units disconnect.<br>
 * Read more about session usage under point 6 and 7.<br>
 * <br>
 * <h3>6) Usage of msf session: keypresses and display update</h3><br>
 * When a session has been established the fp can send display updates to the pp using: #msf_send_DispReq()<br>
 * Resulting in a call to this function on the pp: #pp_msf_DispReq_received()<br>
 * The pp can also send keypresses to the fp using this function: #pp_msf_send_keypad_ind()<br>
 * Resulting in a call to this function on the fp: #msf_infoIndReceived()<br>
 * <br>
 * <h3>7) Usage of msf session: data transfer with ppstatus ind/req</h3><br>
 * ppstatus ind/req can be used with or with a session, if you have a session open the data will be send faster because the system doesn´t need no setup a connection first.<br>
 * If you have an active session it will use a dect channel as long as it´s active - keep this in mind.<br>
 * See in next point how to use ppstatus ind/req messages<br>
 * <h3>8) data transfer with ppstatus ind/req</h3><br>
 * <h4>8.1) data from fp to pp</h4><br>
 * On the fp call this function: #msf_send_ppstatusReq()<br>
 * This will result in a call to this function on the pp: #pp_msf_ppstatus_req_received()<br>
 * There will not be send any acknowledge to the fp from the pp, if you want to send an acknowledge you can use an empty ppstatus_ind identified by the statustype.<br>
 * If there is an active session there shouldn´t be any need for acknowledge, unless you expect more data from the fp, and you want to send a ppstatusind as data ready.<br>
 * <h4>8.2) data from pp to fp</h4><br>
 * On the pp call this function: #pp_msf_send_ppstatus_ind()<br>
 * This will result in a call to this function on the fp: #msf_ppstatus_ind_received() if in a session the value returned from this function determines whether or not an acknowledge should be send back to the pp.<br>
 * If there are no active session an acknowledge will allays be send back to the pp.<br>
 * If an acknowledge is sent this function will be called on the pp: #pp_msf_ppstatus_ind_ack()<br>
 * <br>
 * <h3>9) Ending a session</h3><br>
 * <h4>9.1) From pp side</h4><br>
 * To release the session from the pp call this function: #pp_msf_send_release_ind()<br>
 * This will result in a call to this function on the fp: #msf_releaseIndReceived()<br>
 * The session are now closed.<br>
 * <h4>9.2) From fp side</h4><br>
 * To release the session from the fp call this function: #msf_send_ReleaseReq()<br>
 * This will result in a call to this function on the pp: #pp_msf_release_received()<br>
 * The session are now closed.<br>
 */

#endif /* MSF_DESCRIPTION_H_ */
