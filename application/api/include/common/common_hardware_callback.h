#ifndef COMMON_HARDWARE_CALLBACK
#define COMMON_HARDWARE_CALLBACK

#include "../fp/fp_api.h"
#include "common_hardware_functions.h"

/**
 * This function is called when the mac layer has received the common_playsound() request.
 * @param status    0 if the mac layer has accepted the request and started to play the sound, pp_common_playsound_finished() will be call when the playback is finished.<br>
 *                  1 if the mac layer was allready playing a sound, only one sound can be played at the time, wait for a call to pp_common_playsound_finished(), then soundplayback is possible again.
 * @see pp_common_playsound_finished()
 * @see common_playsound()
 * @return void
 */
extern void pp_common_playsound_ack(UByte status);

/**
 * This function is called when the mac layer has received the common_playsound() request.
 * @param status    0 if the mac layer has accepted the request and started to play the sound, fp_common_playsound_finished() will be call when the playback is finished.<br>
 *                  1 if the mac layer was allready playing a sound, only one sound can be played at the time, wait for a call to fp_common_playsound_finished(), then soundplayback is possible again.
 * @see fp_common_playsound_finished()
 * @see common_playsound()
 * @return void
 */
extern void fp_common_playsound_ack(UByte status);

/**
 * This function is called when the mac layer has finished the common_playsound() request, it is now possible to play another sound.
 * @see common_playsound()
 * @return void
 */
extern void fp_common_playsound_finished();

/**
 * This function is called when the mac layer has finished the common_playsound() request, it is now possible to play another sound.
 * @see common_playsound()
 * @return void
 */
extern void pp_common_playsound_finished();

typedef enum
{
    low,
    high
}gpio_state;

extern void pp_common_gpio_inputport_state_changed(gpio_port port, gpio_state state);

extern void fp_common_gpio_inputport_state_changed(gpio_port port, gpio_state state);
#endif

