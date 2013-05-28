#include "../common/common_structures.h"

/**
 * This function is called when the fp has acknowledged the last module2module command send from the pp.
 * <br>Refer to common/module2module_description.h for a module2module overview, and description of the most common module2module cases.<br>
 * @param optionalDataSrc   If the fp has added data in the acknowledge event it´s located in the optionalDataSrc, otherwise the optionalDataSrc will contain zeros.
 * @return void
 */
extern void pp_module2module_ack_received(module2moduleData optionalDataSrc);

/**
 * This function is called when a user (fp) has send a module2module to this (fp callng this function #fp_send_module2module()).
 * <br>Refer to common/module2module_description.h for a module2module overview, and description of the most common module2module cases.<br>
 * @param dataSrc       The module2moduleData packet send from the fp
 * @param ackDst        The pp will always send an acknowledge to the fp, by default the data bytes in the acknowledge will be set to 0,
 *                      but by modifying the content of ackDataDst data can be send to the fp embedded in the acknowledge signal.
 * @return void
 */
extern void pp_module2module_received(module2moduleData dataSrc, module2moduleData ackDst);
