/*==============================================================================
 ;*  $Header:   K:/PH/SRCLIB/PP5/BASIS/ARCHIVE/H/EeTest.h_v   1.4   18 Nov 2004 13:06:44   MNE  $ *
 ;*
 ;*  DESCRIPTION:
 ;*
 ;*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 ;*  The information in this document is confidential and sole property of
 ;*  RTX Research A/S. (c) Copyright 1997 by RTX Research A/S.
 ;*============================================================================*/

/*============================ MACROS / CONSTANTS ============================*/

typedef enum
{
    no_error = 0x00, error_not_implemented = 0xff
} serial_error_type;

typedef enum
{
    gen_system_event = 0x00, gen_rf_event = 0x01, gen_misc_hardware_event = 0x02, gen_settings_event = 0x03, gen_api_event = 0x04, gen_test_event = 0x50
} gen_info_type;

typedef enum
{
    gen_set_default = 0x00,
    gen_set_default_progressInit = 0x01,
    gen_get_default_progresss = 0x02,
    gen_get_software_and_pcs = 0x03,
    gen_get_buffer_size = 0x04,
    gen_get_buffer_state = 0x05,
    gen_set_old_send_mails_passtrough = 0x06,
    gen_set_sleep = 0x07,
    gen_get_eeprom_size = 0x08,
    gen_set_enter_boot_mode = 0x09,
    gen_send_key_ind = 0x0a,
    gen_get_trap_instructions = 0x0b,
    gen_set_grap_instructions = 0x0c
} gen_system_event_type;

typedef enum
{
    gen_set_testmode = 0x00,
    gen_get_in_lock_status = 0x01,
    gen_set_dect_band = 0x02,
    gen_set_bandgap = 0x03,
    gen_get_rfpi_q_rssi_ch = 0x04,
    gen_set_modulation = 0x05,
    gen_set_offset = 0x06,
    gen_get_frequency = 0x07,
    gen_set_frequency = 0x08,
    gen_set_antenna = 0x09,
    gen_set_tx_burst = 0x0a,
    gen_get_bandgap = 0x0b,
    gen_get_dect_band = 0x0c,
    gen_get_modulation = 0x0d,
    gen_get_offset = 0x0e,
    gen_get_power = 0x0f,
    gen_set_power = 0x10,
    gen_get_dect_ch_offset = 0x11,
    gen_set_dect_ch_offset = 0x12,
    gen_get_dect_encryption = 0x13,
    gen_set_dect_encryption = 0x14,
    gen_get_use_emergency_channel = 0x15,
    gen_set_use_emergency_channel = 0x16,
    gen_get_out_of_range_delay = 0x17,
    gen_set_out_of_range_delay = 0x18,
    gen_get_auto_logon_delay = 0x19,
    gen_set_auto_logon_delay = 0x1a,
    gen_get_pp_offset_factor = 0x1b,
    gen_set_pp_offset_factor = 0x1c,
    gen_get_rssi_busy_level = 0x1d,
    get_set_rssi_busy_level = 0x1e
} gen_rf_event_type;

typedef enum
{
    gen_set_reset = 0x00,
    gen_set_led = 0x01,
    gen_set_delay_reset = 0x02,
    gen_get_last_key_pressed = 0x03,
    gen_get_microphone_dc_voltage = 0x04,
    gen_set_microphone_dc_voltage = 0x05,
    gen_set_dsp_reset = 0x06,
    gen_get_battery_voltage = 0x07,
    gen_get_external_radio_state = 0x08,
    gen_set_external_radio_state = 0x09,
    gen_get_selected_battery = 0x0a,
    gen_set_selected_battery = 0x0b,
    gen_get_batteries_attached = 0x0c,
    gen_get_microphone_damp = 0x0d,
    gen_set_microphone_damp = 0x0e,
    gen_get_audio_loop_back = 0x0f,
    gen_set_audio_loop_back = 0x10,
    gen_get_device_id = 0x11,
    gen_set_device_id = 0x12,
    gen_get_device_id_possible = 0x13,
    gen_set_device_id_possible = 0x14,
    gen_get_led_indication = 0x15,
    gen_set_led_indication = 0x16,
    gen_get_ipei = 0x17,
    gen_set_ipei = 0x18,
    gen_get_ari = 0x19,
    gen_set_ari = 0x1a,
    gen_set_turnoff = 0x1b,
    gen_dump_bmcdef = 0x1c,
    gen_get_device_reg = 0x1d,
    gen_set_device_reg = 0x1e,
    gen_get_CODECS_avail = 0x1f,
    gen_dump_dip = 0x20,
    gen_test = 0x21
} gen_misc_hardware_event_type;

typedef enum
{
    gen_get_st_repeater_type = 0x00,
    gen_set_st_repeater_type = 0x01,
    gen_get_st_max_connections_supported = 0x02,
    gen_set_st_max_connections_supported = 0x03,
    gen_get_max_connection_number = 0x04,
    gen_set_max_connection_number = 0x05,
    gen_get_ari_and_rpn_number = 0x06,
    gen_set_ari_and_rpn_number = 0x07,
    gen_get_monitor_beep = 0x08,
    gen_set_monitor_beep = 0x09,
    gen_get_alternative_base_to_sync_on = 0x0a,
    gen_set_alternative_base_to_sync_on = 0x0b,
    gen_get_alternative_repeater_to_sync_on = 0x0c,
    gen_set_alternative_repeater_to_sync_on = 0x0d,
    gen_get_rpn = 0x0e,
    gen_set_rpn = 0x0f,
    gen_get_st_alternate_settings_capable = 0x10,
    gen_set_st_alternate_settings_capable = 0x11,
    gen_get_kirk_id = 0x12,
    gen_set_kirk_id = 0x13,
    gen_get_hardware_version = 0x14,
    gen_set_hardware_version = 0x15,
    gen_get_pta_variables = 0x16,
    gen_set_pta_variables = 0x17,
    gen_get_pta_variables_part = 0x18,
    gen_set_pta_variables_part = 0x19,
    gen_get_user_test = 0x1a,
    gen_set_user_test = 0x1b,
    gen_get_battery_low_warning = 0x1c,
    gen_set_battery_low_warning = 0x1d,
    gen_get_battery_empty_warning = 0x1e,
    gen_set_battery_empty_warning = 0x1f,
    gen_get_disconnect_from_conference_charging = 0x20,
    gen_set_disconnect_from_conference_charging = 0x21,
    gen_get_headphones_volume_plug_offset = 0x22,
    gen_set_headphones_volume_plug_offset = 0x23,
    gen_get_headphones_volume_steps = 0x24,
    gen_set_headphones_volume_steps = 0x25,
    gen_get_headphones_agc = 0x26,
    gen_set_headphones_agc = 0x27,
    gen_get_menu_auto_return_time = 0x28,
    gen_set_menu_auto_return_time = 0x29,
    gen_get_plug_more_press_time = 0x2a,
    gen_set_plug_more_press_time = 0x2b,
    gen_get_act_as_base_press_time = 0x2c,
    gen_set_act_as_base_press_time = 0x2d,
    gen_get_emergency_channel_max_tx_time = 0x2e,
    gen_set_emergency_channel_max_tx_time = 0x2f,
    gen_get_logon_enabled_timeout = 0x30,
    gen_set_logon_enabled_timeout = 0x31,
    gen_get_menuitems_state = 0x32,
    gen_set_menuitems_state = 0x33,
    gen_get_microphone_sensitivity = 0x34,
    gen_set_microphone_sensitivity = 0x35,
    gen_get_vox_on_values = 0x36,
    gen_set_vox_on_values = 0x37,
    gen_get_vox_off_values = 0x38,
    gen_set_vox_off_values = 0x39,
    gen_get_external_in_sensitivity = 0x3a,
    gen_set_external_in_sensitivity = 0x3b,
    gen_get_external_in_vox = 0x3c,
    gen_set_external_in_vox = 0x3d,
    gen_get_external_out_sensitivity = 0x3e,
    gen_set_external_out_sensitivity = 0x3f,
    gen_get_debug_level = 0x40,
    gen_set_debug_level = 0x41,
    gen_get_access_code = 0x42,
    gen_set_access_code = 0x43,
    gen_get_key_timing = 0x46,
    gen_set_key_timing = 0x47,
    gen_get_current_volume = 0x48,
    gen_get_subscription_mode = 0x49,
    gen_set_subscription_mode = 0x4a,
    gen_set_unit_subscription_configuration = 0x4b,
    gen_get_unit_subscription_configuration = 0x4c,
    gen_set_unit_subscription_access_level = 0x4d,
    gen_set_delete_unit_subscription_configuration = 0x4e,
    gen_get_current_selected_base = 0x4f,
    gen_get_routing_settings = 0x50,
    gen_set_routing_settings = 0x51
} gen_settings_event_type;

typedef enum
{
    gen_get_peltor_state = 0x00, gen_get_subscription_info = 0x01, gen_get_test = 0x02, gen_get_test_count = 0x03
} gen_test_event_type;

typedef enum
{
    TC_READ_FREQ_EEP = 0x01, /* Both handset and fixed part*/
    TC_READ_MOD = 0x02, /* Both handset and fixed part*/
    TC_WRT_MOD = 0x05,
    TC_LOOP_BACK = 0x10,
    TC_GET_DEVICE_ID = 0x11,
    TC_SET_DEVICE_ID = 0x12,
    TEMP_DIVERSITY_MODE = 0x13, /* Same as in Bs : use TC_DISPLAY_TEST2 number if problem occur.*/
    TC_SOFTWARE_RESET = 0x04,
    /*    TC_RFOFF                = 0X15,*/
    /*    TC_SW_VERSION           = 0x16,// HS*/
    TC_GET_IPEI = 0x17,
    TC_SET_IPEI = 0x18,
    TC_GET_ARI = 0x19,
    TC_SET_ARI = 0x1A,
    /*    TC_WRITE_ID             = 0x1B,*/
    /*    TC_READ_ID              = 0x1C,*/
    TC_SET_TxModDCLevel = 0x1D,
    TC_READ_TxModDCLevel = 0x20,
    TC_CURRENT_FREQ = 0x24, /* Handset*/
    TC_LED0 = 0x2F,
    TC_SET_FREQ = 0x36,
    TC_WRT_BANDGAP = 0x39,
    TC_READ_BANDGAP = 0x3A,
    TC_BOOTMODE = 0x3D,
    TC_SET_ALTERNATINGBITS = 0x45,
    TC_VIRTUAL_HS_READ_DSP = 0x48,
    TC_VIRTUAL_HS_ACTIVE_AUTO_SUB = 0x4C,
    TC_VIRTUAL_HS_KEY = 0x4D,
    TC_START_MAC_TRACE = 0x52,
    TC_STOP_MAC_TRACE = 0x53,
    TC_PING = 0x54,
    TC_SET_SEARCH_ARI = 0x55
} TestCommandFunctionType; /*do not add more to this struct, use new generic interface, ask jsj.*/

