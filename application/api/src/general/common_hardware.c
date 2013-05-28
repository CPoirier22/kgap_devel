/*
 * common_hardware.c
 *
 *  Created on: 06-08-2009
 *      Author: jjust
 */

#include "../../include/common/common_hardware_functions.h"
#include "../../../../include/machlinterface/include/application_mac_tunnel.h"
#include "../../../../include/common/include/map_480_gcc.h"

extern void sendAppToMac(UByte key, UByte action);

static UByte registered_output_ports[4] = { 0, 0, 0, 0 };

UByte common_gpio_register_input_port(gpio_port port, gpio_resistor_setting resistor_setting)
{
    UByte p_x = (port >> 4) & 3;
    UByte p_bit = port & 0x0f;

    registered_output_ports[p_x] = registered_output_ports[p_x] & (0xff ^ p_bit);

    sendAppToMac(APP_TO_MAC_GPIO_REGISTER_INPUT, (resistor_setting << 6) | port);

    return 0;
}

UByte common_gpio_deregister_input_port(gpio_port port)
{
    sendAppToMac(APP_TO_MAC_GPIO_DEREGISTER_INPUT, port);
    return 0;
}

UByte common_gpio_register_output_port(gpio_port port)
{
    UByte p_x = (port >> 4) & 3;
    UByte p_bit = port & 0x0f;

    registered_output_ports[p_x] |= p_bit;

    sendAppToMac(APP_TO_MAC_GPIO_REGISTER_OUTPUT, port);

    return 0;
}

UByte common_gpio_set_output_port(gpio_port port, UByte value)
{
    UByte p_x = (port >> 4) & 3;
    UByte p_bit = port & 0x0f;
    UByte sendValue = value ? 0x40 : 0;

    if (registered_output_ports[p_x] & p_bit)
    {
        sendAppToMac(APP_TO_MAC_GPIO_SET_OUTPUT, port | sendValue);
        return 0;
    }

    return 1;
}
signed long mult(signed long x, signed long y)
{
    signed long n = 0;
    if ((x < 0 && y < 0) || (y < 0))
    {
        x = 0 - x;
        y = 0 - y;
    }
    while (y > 0)
    {
        if ((y & 1) > 0)
        {
            n += x;
        }
        x <<= 1;
        y >>= 1;
    }
    return n;

}
BYTE common_read_temperature(UByte cal)
{
    /* TODO: make signed if cal can make result be negative.
     *  Can be worked around on receiving end.
     */
    int val;
    ADC_CLEAR_INT_REG = 0;
    ADC_CTRL_REG |= 0x38; /* Temp. sensor*/
    ADC_CTRL_REG |= 0x01; /* Start */
    while (!(ADC_CTRL_REG & (1 << 11)))
        ;
    val = ADC0_REG & 0x03ff;
    ADC_CLEAR_INT_REG = 0;

    return (-div32(mult(val - 2960, 100), 690 + cal)) - 273;
}
