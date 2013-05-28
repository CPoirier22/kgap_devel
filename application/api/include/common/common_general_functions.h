#ifndef COMMON_SYSTEM_FUNCTIONS
#define COMMON_SYSTEM_FUNCTIONS

#include "../fp/fp_api.h"

/**
 * if 1 started as fp
 * if 0 started as pp
 */
extern UByte getRunMode(void);

/**
 * Use this function to start a timer, you will be notified later in general_timeout when the timer expires.
 * @param user			The owner of the timer, each pp on a fp can have its own timer - for pp use 0.
 * @param subEvent		This value will help identify time timeout reason later.
 * @param dataPtr		This pointer will be delivered when the timer expires
 * @param dataLength	Length of the dataPtr
 * @param timeoutValue	10�s of milliseconds - 100 is one second.
 * @see fp_general_timeout()
 * @see pp_general_timeout()
 * @return UByte 1 timer has been started, 0 timer has not been started.
 */
extern UByte general_startTimer(PPIDType user, UByte subEvent, UByte * dataPtr, UByte dataLength, int timeoutValue);

/**
 * Use this function to stop a running timer.
 * @param user          The owner of the timer, each pp on a fp can have its own timer - for pp use 0.
 * @return UBute        0 for success, different than 0 for error code:<br>
 *                      1: timer not started<br>
 *                      2: user not found<br>
 */
extern UByte general_stopTimer(PPIDType user);

/**
 * Use this function to write to eeprom. There are no acknoledge at the moment, to ensure the write then read afterwards.
 * @param address		The destination address in eeprom.
 * @param data			The pointer to the source data.
 * @param length		Number of bytes to be written.
 * @param ppid		  	Not used at the moment.
 * @return UByte		0 for succes, different than 0 is an error code.
 */
extern UByte general_eeprom_write_req(WORD address, UByte * data, UByte length, PPIDType ppid);

/**
 * Use this function to read from eeprom. When the read is finished the function: fp_general_eeprom_read_res or pp_general_eeprom_read_res will be called.
 * @param address		The address in eeprom to read from
 * @param length        Number of bytes to read
 * @param ppid          User to identify the req, this will be saved an used as a parameter when the read is finished. Set to 0 when using this function on a pp.
 * @see fp_general_eeprom_read_res
 * @see pp_general_eeprom_read_res
 * @return UByte        0 if the system accepts the req and initiates the reading, different than 0 is an error code.
 */
extern UByte general_eeprom_read_req(WORD address, UByte length, PPIDType ppid);

#endif

