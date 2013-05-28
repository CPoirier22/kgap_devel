#include "../common/common_structures.h"

/**
 * This function is called when a user (pp) has send a module2module to the fp (pp callng this function #pp_send_module2module()).
 * <br>Refer to common/module2module_description.h for a module2module overview, and description of the most common module2module cases.<br>
 * @param user          The user sending the module2module command.
 * @param dataSrc       The module2moduleData packet send from the user
 * @param ackDataDst    The fp will always send an acknowledge to the pp, by default the data bytes in the acknowledge will be set to 0,
 *                      but by modifying the content of ackDataDst data can be send to the pp embedded in the acknowledge signal.
 * @return void
 */
extern void fp_module2module_received(PPIDType user, module2moduleData dataSrc, module2moduleData ackDataDst);

/**
 * This function is called when the user has acknowledged the last module2module command send from the fp.
 * <br>Refer to common/module2module_description.h for a module2module overview, and description of the most common module2module cases.<br>
 * @param user              The user sending the module2module acknowledge
 * @param optionalDataSrc   If the pp has added data in the acknowledge event it´s located in the optionalDataSrc, otherwise the optionalDataSrc will contain zeros.
 * @return void
 */
extern void fp_module2module_ack_received(PPIDType user, module2moduleData optionalDataSrc);
