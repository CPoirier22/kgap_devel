#ifndef PP_VOICE_CALLBACK
#define PP_VOICE_CALLBACK

#include "pp_api.h"

/**
 * This function is called when to call has been released from the fp.
 * @param reason            The release reason, 0 for normal, different than 0 for abnormal
 * @return void
 */
extern void pp_voice_call_released(UByte reason);

/**
 * This function is called when a new info element is received. see possible info types below:<br>
 * infotype:<br>
 * DialToneOn             0x00<br>
 * RingBackToneOn          0x01<br>
 * InterceptToneOn         0x02<br>
 * NetworkCongestionToneOn  0x03<br>
 *  BusyToneOn              0x04<br>
 *  ConfirmToneOn           0x05<br>
 *  AnswerToneOn            0x06<br>
 *  CallWaitingToneOn       0x07<br>
 *  OffHookWarningToneOn    0x08<br>
 *  TonesOff                0x3f<br>
 *  AlertingOnPattern0        0x40<br>
 *  AlertingOnPattern1        0x41<br>
 *  AlertingOnPattern2        0x42<br>
 *  AlertingOnPattern3        0x43<br>
 *  AlertingOnPattern4        0x44<br>
 *  AlertingOnPattern5        0x45<br>
 *  AlertingOnPattern6        0x46<br>
 *  AlertingOnPattern7        0x47<br>
 *  AlertingOnContinuous     0x48<br>
 *  AlertingOff             0x4f<br>
 *  Only display received  0xfe<br>
 *  NoInfoReceived         0xff<br><br>
 *
 * The display can contain: acsii characters (display content) and / or, display commands:<br>
 *  {<br>
 *                DISP_CLEAR,               // 0<br>
 *                DISP_CLEAR_INDICATORS,    // 1<br>
 *                DISP_CLEAR_ROWS,          // 2<br>
 *                DISP_CLEAR_ROW,           // 3<br>
 *                DISP_CURSOR_BS,           // 4<br>
 *                DISP_CURSOR_LEFT,         // 5<br>
 *                DISP_CURSOR_RIGHT,        // 6<br>
 *                DISP_CURSOR_SET,          // 7<br>
 *                DISP_OUTPUT_CHAR,         // 8<br>
 *                DISP_SET_INDICATOR,       // 9<br>
 *                DISP_GET_CAPABILITIES,    // A<br>
 *               DISP_OUTPUT_STR,          // B<br>
 *                DISP_SELFTEST,            // C<br>
 *                DISP_UPDATE,              // D<br>
 *                DISP_PAUSE,               // E<br>
 *                DISP_CURSOR_BLINK,        // F<br>
 *                DISP_UP_ONE_ROW,          // 10<br>
 *                DISP_DOWN_ONE_ROW,        // 11<br>
 *                DISP_RETURN_CURRENT_ROW,  // 12<br>
 *                DISP_SHOW_LOGO,           // 13<br>
 *                DISP_OUTPUT_DDSTR         // 14<br>
 *              }TDisplayCommand;<br>
 * @param infoType      See above description
 * @param info          See above description, could be empty check infoLength.
 * @param infoLength    Length of the info, could be empty (0).
 * @return void
 */
extern void pp_voice_info_received(UByte infoType, char * info, UByte infoLength);

/**
 * This function is called when an incoming call request is received. use pp_voice_offhook to accept the call
 * @param from          Calling party number
 * @see pp_voice_offhook()
 * @return void
 */
extern void pp_voice_incommingCall(char * from);

/**
 * This function is called when an outgoing offhook has succeeded, now it´s possible to send digits to the base overlap style.
 * @return void
 */
extern void pp_voice_offhook_ready();

#endif
