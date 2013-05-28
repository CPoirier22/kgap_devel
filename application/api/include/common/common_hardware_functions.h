#ifndef COMMON_HARDWARE_FUNCTIONS
#define COMMON_HARDWARE_FUNCTIONS

#include "../fp/fp_api.h"

/**
 * Calling this function will send a sound play request to the mac layer, the function fp_common_playsound_ack / pp_common_playsound_ack will be called with a status (accepted / not accepted), and the function fp_common_playsound_finished / pp_common_playsound_finished will be called when the playback is finished.
 * @param sound_to_play     The sound index to play, should be an element in the sounds enum in flash_sound.h
 * @return void
 */
extern void common_playsound(UByte sound_to_play);

typedef enum
{
    /*p0_0 = 0x00, used by UART_TX (use of this pin by own risk)*/
    /**10k*/
    p0_1 = 0x01,
    /*p0_2 = 0x02, used by SDA2 (use of this pin by own risk)*/
    /*p0_3 = 0x03, used by SCL2 (use of this pin by own risk)*/
    p0_4 = 0x04, p0_5 = 0x05, p0_6 = 0x06, p0_7 = 0x07, p1_0 = 0x10,
    /*p1_1 = 0x11, reserved*/
    /*p1_2 = 0x12, reserved*/
    p1_3 = 0x13, p1_4 = 0x14,
    /*p1_5 = 0x15, reserved*/
    /*p1_6 = 0x16, reserved*/
    /*p1_7 = 0x17, reserved*/
    p2_0 = 0x20, p2_1 = 0x21, p2_2 = 0x22, p2_3 = 0x23, p2_4 = 0x24, p2_5 = 0x25, p2_6 = 0x26, p2_7 = 0x27,
    /**DO, 500 mA*/p3_0 = 0x30,/**DO, 500 mA*/p3_1 = 0x31,
    /*p3_2 = 0x32, Does not exist?*/
    p3_3 = 0x33, P3_4 = 0x34, p3_5 = 0x35, p3_6 = 0x36, p3_7 = 0x37
} gpio_port;

typedef enum
{
    no_resistor_selected = 0x00, pullup_selected = 0x01, pulldown_selected = 0x02
} gpio_resistor_setting;

extern UByte common_gpio_register_input_port(gpio_port port, gpio_resistor_setting resistor_setting);

extern UByte common_gpio_deregister_input_port(gpio_port port);

extern UByte common_gpio_register_output_port(gpio_port port);

extern UByte common_gpio_set_output_port(gpio_port port, UByte value);
/**
 * Reads the temperature of the internal temperature sensor.
 *
 * @param cal Calibration of sensor - between 0 and 210.
 * @return The temperature - range normally within 5 - 55 °C
 */
extern BYTE common_read_temperature(UByte cal);
#endif

