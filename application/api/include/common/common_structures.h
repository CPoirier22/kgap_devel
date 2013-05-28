#ifndef COMMON_STRUCTURES
#define COMMON_STRUCTURES

typedef enum
{
    Silence, Pattern_2, /* (tone 9 in PP)*/
    Pattern_3, /* (tone 6 in PP)*/
    Pattern_4, /* (tone 7 in PP)*/
    Pattern_5, /* (KeyBeep (known key) in PP)*/
    Pattern_6, /* (KeyClick (unknown key) in PP)*/
    Pattern_7, /* (Accept Tone in PP)*/
    Vibrate
/*If MSFDispReq Error Tone in PP*/
} alertTypes;

typedef enum
{
    alertPattern_not_present = 0x00,/*use alert the alert type specified in setupspec1*/
    alertPattern_continuos = 0x01,
    alertPattern_internal = 0x02,
    alertPattern_external = 0x03,
    alertPattern_alarm = 0x04
} alertPatternType;

typedef enum
{
    alertToneType_alerting_off = 0x00,
    alertToneType_pp_tone_1 = 0x01,
    alertToneType_pp_tone_2 = 0x02,
    alertToneType_pp_tone_3 = 0x03,
    alertToneType_pp_tone_4 = 0x04,
    alertToneType_pp_tone_5 = 0x05,
    alertToneType_pp_tone_6 = 0x06,
    alertToneType_pp_tone_7 = 0x07,
    alertToneType_pp_tone_8 = 0x08,
    alertToneType_pp_tone_9 = 0x09,
    alertToneType_use_pp_tone = 0x0a,
    alertToneType_vibrator = 0x0b,
    alertToneType_key_click = 0x0c,
    alertToneType_key_beep = 0x0d,
    alertToneType_accept_tone = 0x0e,
    alertToneType_error_tone = 0x0f
} alertToneType;

typedef struct
{
    alertPatternType alertPattern;
    alertToneType alertTone;
    UByte alertTimeout;
} alertConstructiontType;

typedef struct
{
    UByte length; /*!< dateAndTimeType value length: Length of the date and time field (in bytes). Length indicates which sub-fields that are present.*/
    UByte day;
    UByte month;
    UByte hour;
    UByte minute;
    UByte year;
    UByte second;
} dateAndTimeType;

typedef enum
{
    functionType_dont_touch_led_or_envelope = 0x00,
    functionType_turn_off_led = 0x01,
    functionType_turn_on_led = 0x02,
    functionType_start_flashing_led = 0x03,
    functionType_turn_off_envelope = 0x04,
    functionType_turn_on_envelope = 0x05,
    functionType_start_flashing_envelope = 0x06,
    functionType_enable_local_use = 0x07
} functionType;

typedef enum
{ /*Implemented for CTP systems Israel*/
    SEND_AS_CC_INFO, /*so they can send LEFT_KEY in a CC_INFO offhooked*/
    SEND_AS_SS_FACILITY
} SendPrimitiveType;

typedef UByte module2moduleData[3];

/**
 * This functions generates the setupSpec1 byte used by msf_setupreq_format1.
 * @param text_call
 * @param display_right_arrow
 * @param display_left_arrow
 * @param enable_right_arrow
 * @param enable_left_arrow
 * @param alertType
 * @see msf_setupreq_format1
 * @return UByte the generated setupspec1
 */

extern UByte msf_help_generateSetupSpec1(UByte text_call, UByte display_right_arrow, UByte display_left_arrow, UByte enable_right_arrow, UByte enable_left_arrow, alertTypes alertType);

/**
 * This function generates the setupSpec2 byte used by msf_setup_req_format2
 * @param PartielUnlock         When bit is set in Page call only the hook key is unlocked (valid for 13309911).Reserved  bit should be set to zero
 * @param NoAcknowledgement     When this bit is set no MSFRelInd is send as acknowledgement.
 * @param SaveInStack           When this is set DisplayText shall be saved in the message stack of the PP. Ignored if TC bit set.
 * @see msf_setupreq_format2()
 * @return UByte the generated setupspec2
 */

extern UByte msf_help_generateSetupSpec2(UByte PartielUnlock, UByte NoAcknowledgement, UByte SaveInStack);

/**
 * This function generates the setupSpec3 byte used by msf_setup_req_format2
 * @param function      Handling of the Light Emitting Diode or the envelope icon
 * @param vibrateTone   The vibrator follows the tone cadence if a tone is specified (both vibrator and tone)
 * @param AlertAlways   same as VibrateAlways, but for tones.
 * @param VibrateAlways If  0, the vibrator will only vibrate if the user has enabled the vibrator in the PP. If 1, the vibrator will always vibrate independent of the local settings in the PP (if vibrate is specified in following).
 * @param msfUp         (Automatically sets up a MSF connection)  is only valid , if “SetupSpec1, TC”=1 (Text Call). Normally a MSF connection is set up by pressing Enter on the PP, when this is set the call is immediately set up.
 * @see msf_setupreq_format2()
 * @return UByte the generated setupspec3
 */

extern UByte msf_help_generateSetupSpec3(functionType function, UByte vibrateTone, UByte AlertAlways, UByte VibrateAlways, UByte msfUp);

#endif
