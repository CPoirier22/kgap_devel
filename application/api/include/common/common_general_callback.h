#ifndef COMMON_SYSTEM_CALLBACK
#define COMMON_SYSTEM_CALLBACK

#include "../fp/fp_api.h"

/**
 *The previously started timer or a system timeout for this user has now expired (fp).
 *@param user		The user related to the timeout.
 *@param subEvent	The subevent used when the timer was started.
 *@param dataPtr	Pointer to datablock.
 *@param dataLength	Length of the dataPtr.
 *@see general_startTimer()
 *@return 1: no other handlers will be notified abuot this timeout. 0: other handlers will be notified about this timeout.
 */
extern UByte fp_general_timeout(PPIDType user, UByte subEvent, UByte * dataPtr, UByte dataLength);

/**
 *The previously started timer or a system timeout for this user has now expired (pp).
 *@param user       The user related to the timeout.
 *@param subEvent   The subevent used when the timer was started.
 *@param dataPtr    Pointer to datablock.
 *@param dataLength Length of the dataPtr.
 *@see general_startTimer()
 *@return 1: no other handlers will be notified abuot this timeout. 0: other handlers will be notified about this timeout.
 */
extern UByte pp_general_timeout(PPIDType user, UByte subEvent, UByte * dataPtr, UByte dataLength);

/**
 * This function is called when the system is started as a fp and the 3.rd application can start to make calls and sending messages. It might take a while (10-20 seconds) before handsets are locked to the fp.
 * @return void
 */
extern void fp_system_init();

/**
 * This function is called when the system is started as a pp and the 3.rd application can start to make calls and sending messages.
 * @return void
 */
extern void pp_system_init();

/**
 * This function is called when the mac layer has read the eeprom bytes (running as fp) and copied them to the earlier supplied buffer.
 * @param status	1 for read succes, 0 for read fail
 * @param ppid		the user id used when requested a read.
 * @param data		Pointer to the read data, please notice: when returning from this function the data will no longer be available, copy them to another location if you need them for later usage.
 * @param length	Number of bytes read
 * @see general_eeprom_read_req()
 * @return void
 */
extern void fp_general_eeprom_read_res(UByte status, PPIDType ppid, UByte * data, UByte length);

/**
 * This function is called when the mac layer has read the eeprom bytes (running as pp) and copied them to the earlier supplied buffer.
 * @param status    1 for read succes, 0 for read fail
 * @param ppid      the user id used when requested a read.
 * @param data      Pointer to the read data, please notice: when returning from this function the data will no longer be available, copy them to another location if you need them for later usage.
 * @param length    Number of bytes read
 * @see general_eeprom_read_req()
 * @return void
 */
extern void pp_general_eeprom_read_res(UByte status, PPIDType ppid, UByte * data, UByte length);

#endif

