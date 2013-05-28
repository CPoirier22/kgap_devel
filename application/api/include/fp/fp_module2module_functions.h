#include "../common/common_structures.h"

/**
 * This function sends a module2module command to the user (pp). When received on the pp this function will be called on the pp #pp_module2module_received().<br>
 * Later when acknowledged by the pp, this function will be called on the fp: #fp_module2module_ack_received().
 * <br>Refer to common/module2module_description.h for a module2module overview, and description of the most common module2module cases.<br>
 * @param user      The user(pp) to receive the message
 * @param data      The data bytes that will be send to the pp.
 * @return UByte    0 for succes, different than 0 for error code.
 */
extern UByte fp_send_module2module(PPIDType user, module2moduleData data);
