#include "../common/common_structures.h"

/**
 * This function sends a module2module command to the fp. When received on the fp this function will be called on the fp #fp_module2module_received().<br>
 * Later when acknowledged by the fp, this function will be called on the pp: #pp_module2module_ack_received().
 * <br>Refer to common/module2module_description.h for a module2module overview, and description of the most common module2module cases.<br>
 * @param data      The data bytes that will be send to the fp.
 * @return UByte    0 for succes, different than 0 for error code.
 */
extern UByte pp_send_module2module(module2moduleData data);
