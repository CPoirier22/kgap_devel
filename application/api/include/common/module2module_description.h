/*
 * module2module_description.h
 *
 *  Created on: 28-09-2009
 *      Author: jjust
 */

#ifndef M2M_DESCRIPTION_H_
#define M2M_DESCRIPTION_H_

/** @file
 * Module2module is the fastet way to transfer small data packages / events (3bytes) to and from fp and pp units.<br>
 * The module2module events is only supported on modules and will not work together with other DECT devices.<br>  
 * The module2module uses crc checksum and sends an acknowledge event back to the requesting unit - The acknowledge event can also contain 3 data bytes, this will not slow down the module2module acknowledge, be default the acknowledge bytes will be zeros.<br>
 * Before it´s possible to send module2module commands it´s required to have an active connection either an active voice connection or an active msf session. 
 * <h2>Module2module cases:</h2><br>
 * 1) module2module from pp to fp during voice connection<br>
 * 2) module2module from fp to pp during voice connection<br>
 * 3) module2module from pp to fp during msf session<br>
 * 4) module2module from fp to pp during msf session<br>
 *
 * <h3>1) module2module from pp to fp during voice connection</h3><br>
 * 1.1) Establish a voice connection either:<br>
 * pp<->pp (through a fp)<br>
 * fp<->pp (fp and pp connected)<br><br>
 * 1.2) Call this function on the pp: #pp_send_module2module()<br><br>
 * 1.3) This function will now be called on the fp: #fp_module2module_received()<br>
 * This function gives access to the data send from the pp, and it provides the possibility to set the data, which will be send back in the acknowledge. The acknowledge data bytes are by default 0, and can be left unchanged.<br><br>
 * 1.4) This function will now be called on the pp: #pp_module2module_ack_received() and will contain the optionel ack data bytes or just zeros if not used.<br>
 * <h3>2) module2module from fp to pp during voice connection</h3><br>
 * 1.1) Establish a voice connection either:<br>
 * pp<->pp (through a fp)<br>
 * fp<->pp (fp and pp connected)<br><br>
 * 1.2) Call this function on the fp: #fp_send_module2module()<br><br>
 * 1.3) This function will now be called on the pp: #pp_module2module_received()<br>
 * This function gives access to the data send from the fp, and it provides the possibility to set the data, which will be send back in the acknowledge. The acknowledge data bytes are by default 0, and can be left unchanged.<br><br>
 * 1.4) This function will now be called on the fp: #fp_module2module_ack_received() and will contain the optionel ack data bytes or just zeros if not used.<br>
 * <h3>3) module2module from pp to fp during msf session</h3><br>
 * 1.1) Establish a msf session:<br>
 * fp<->pp (fp and pp connected through msf)<br><br>
 * 1.2) Call this function on the pp: #pp_send_module2module()<br><br>
 * 1.3) This function will now be called on the fp: #fp_module2module_received()<br>
 * This function gives access to the data send from the pp, and it provides the possibility to set the data, which will be send back in the acknowledge. The acknowledge data bytes are by default 0, and can be left unchanged.<br><br>
 * 1.4) This function will now be called on the pp: #pp_module2module_ack_received() and will contain the optionel ack data bytes or just zeros if not used.<br> 
 * <h3>4) module2module from fp to pp during msf session</h3><br>
 * 1.1) Establish a msf session:<br>
 * fp<->pp (fp and pp connected through msf)<br><br>
 * 1.2) Call this function on the fp: #fp_send_module2module()<br><br>
 * 1.3) This function will now be called on the pp: #pp_module2module_received()<br>
 * This function gives access to the data send from the fp, and it provides the possibility to set the data, which will be send back in the acknowledge. The acknowledge data bytes are by default 0, and can be left unchanged.<br><br>
 * 1.4) This function will now be called on the fp: #fp_module2module_ack_received() and will contain the optionel ack data bytes or just zeros if not used.<br> 
 */
 
 #endif
 