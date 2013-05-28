/* Opcode file for the 14428 */
/* Copied from 14408, not up to date yet!!!! */
/* header must be added */

/* timer commands  000 */
/*#define            0x00 not used */
#define  BR           0x01 /* BRanch to address field. */
#define  JMP          0x02 /* JuMP to addressed field. RTN address <- Cur address +1 */
#define  JMP1         0x03 /* JuMP1 if flag1 to addressed field */
#define  RTN          0x04 /* ReTurN to return address */
#define  BK_A1        0x05 /* BanK switching opcode Adpcm channel 1 */
#define  WNTM1        0x06 /* slot counter min 1 */
#define  WNTP1        0x07 /* slot counter plus 1 */
#define  WNT          0x08 /* Wait for next N Timeslot */
#define  WT           0x09 /* WaiT for next n bauds */
#define  RFDIS        0x0A /* RF clock DISable */
#define  RFEN         0x0B /* RF clock ENable */
#define  LD_PTR       0x0C /* LoaD PoinTeR register with parameter */
#define  SLOTZERO     0x0D /* to synchronize slot zero */
#define  BK_A         0x0E /* BanK switching opcode Adpcm channel 0 */
#define  BK_C         0x0F /* BanK switching opcode Chip */

#define  BR_B0        0x10 /* Branch sequencer RAM bank 0 always */
#define  BR_B1        0x11 /* Branch sequencer RAM bank 1 always */
#define  JMPF         0x12 /* jump far to subroutine */
/*#define             0X13 NOT USED */
#define  RTNF         0x14 /* return far from subroutine */
/*#define             0X15 NOT USED */
/*#define             0X16 NOT USED */
/*#define             0X17 NOT USED */
#define  PAG_ON       0x18 /* switch paging mode on */
#define  PAG_OFF      0x19 /* switch paging mode off */
/*#define             0X1A NOT USED */
/*#define             0X1B NOT USED */
/*#define             0X1C NOT USED */
/*#define             0X1D NOT USED */
/*#define             0X1E NOT USED */
/*#define             0X1F NOT USED */

/* BMC coMMANDS ----- 001 ----- */
#define  B_RST        0x20 /* ReSeT */
#define  B_ST2        0x21 /* Transmit S-field in auto mode 0x22 not used 0x23 not used */
#define  B_PPT        0x22 /* Prolonged preamble transmit */
#define  B_BTFM       0x23 /* used */
#define  B_XT         0x24 /* Transmit X-field */
#define  B_BTFU       0x25 /* Transmit full slot unprotected B-field*/
#define  B_BT2        0x25 /* Transmit B-field in auto mode */
#define  B_XOFF       0x26 /* X off */
#define  B_XON        0x27 /* X on */
#define  UNLCK        0x28 /* set UNLoCK mode : reset slot counter on uw-field found */
#define  B_SR         0x29 /* Receive S-field */
#define  B_BRFD       0x2A /* used */
#define  B_XR         0x2B /* Receive X-field */
#define  EN_SL_ADJ    0x2C /* ENable SLot counter ADJustment */
#define  B_BR2        0x2D /* Receive B-field in auto mode */
#define  B_RINV       0x2E /* B-filed R CRC last bit. This bit must be INVerted */
#define  B_RON        0x2F /* B-filed R CRC on */

/*#define             0X30 NOT USED */
#define  B_ST         0x31 /* Transmit S-field */
#define  B_AT         0x32 /* Transmit A-field */
#define  B_RC         0x33 /* Read Control */
#define  B_BT         0x34 /* Transmit B-field */
#define  B_BTP        0x35 /* Transmit B-field protected */
/*#define             0X36 NOT USED */
#define  B_AT2        0x37 /* Transmit A-field in auto mode */
/*#define             0X38 NOT USED */
#define  B_WRS        0x39 /* WRite Status */
#define  B_AR         0x3A /* Receive A-field */
/*#define             0X3B  NOT USED */
#define  B_BR         0x3C /* Receive B-field */
#define  B_BRP        0x3D /* Receive B-field protected */
/*#define            0X3E    NOT USED */
#define  B_AR2        0x3F /* Receive A-field in auto mode */

/* Key stREAM GENErator commands -010 */
#define  D_RST        0x40 /* ReSeT key stream generator */
/*#define            0X41  NOT USED */
/*#define            0X42  ENABLE KEYSTREAM GENERATION */
/*#define            0X43  DIABLE KEYSTREAM GENERATION */
#define  D_PREP       0x44 /* PREProcess Keystream data */
/*#define            0X45 NOT USED */
/*#define            0X46 NOT USED */
/*#define            0X47 NOT USED */
#define  WSC          0x48 /* WAIT for synchronization */
#define  A_RX         0x49 /* Set adpcm Receive channel */
#define  A_TX         0x4A /* Set adpcm Transmit channel */
/*#define            0X4B    NOT USED */
/*#define            0X4C    NOT USED */
#define  B_DIV4       0x4D /* used */
#define  B_DIV2       0x4E /* used */
#define  B_DIV1       0x4F /* used */

#define  D_LDK        0x50 /* load 16 byte encryption key */
/*#define            0X51  NOT USED */
/*#define            0X52  NOT USED */
/*#define            0X53  NOT USED */
/*#define            0X54  NOT USED */
/*#define            0X55  NOT USED */
/*#define            0X56  NOT USED */
#define  D_LDS        0x57 /* LoaD keystream Status */
/*#define            0X58  NOT USED */
/*#define            0X59  NOT USED */
/*#define            0X5A  NOT USED */
/*#define            0X5B  NOT USED */
/*#define            0X5C  NOT USED */
/*#define            0X5D  NOT USED */
/*#define            0X5E  1NOT USED */
#define  D_WRS        0x5F /* WRite Keystream Status */

/* U compUTER COMMands -011- */
#define  U_PSC        0x60 /* Output clk prescalar active divide by 16    default */
#define  U_INT0       0x61 /* Set interrupt output. */
/*#define             0X62  RECEIVE CLOCK INTERN. */
#define  U_VINT       0x63 /* vectored interrupt */
#define  B_WB_OFF     0x64 /* B-field write 6X command should not activate BMC */
#define  B_WB_ON      0x65 /* B-field write 6X command should activate BMC */
/*#define             0X66    CLK TO 1MC */
/*#define             0X67    CLK TO 3MC */
/*#define             0X68    DIVIDE UC_CLK PRESCALAR OUTPUT BY 8 */
/*#define             0X69    DIVIDE UC_CLK PRESCALAR OUTPUT BY 4 */
/*#define             0X6A    DIVIDE UC_CLK PRESCALAR OUTPUT BY 2 */
#define  U_INT1       0x6B /* Set interrupt output. */
/*#define             0X6C  DIVIDE UC_CLK PRESCALAR OUTPUT BY 1 */
#define  U_INT2       0x6D /* Set interrupt output. */
#define  BRK          0x6E /* set breakpoint */
#define  U_INT3       0x6F /* Set interrupt output. */

/*#define             0X70  NOT USED */
#define  B_BTDU       0x71 /* Transmit double slot B-field in auto mode */
#define  B_BTDP       0x72 /* Transmit double slot B-field protected */
/*#define             0X73  NOT USED */
/*#define             0X74  NOT USED */
/*#define             0X75  NOT USED */
/*#define             0X76  NOT USED */
/*#define             0X77  NOT USED */
/*#define             0X78  NOT USED */
#define  B_BRDU       0x79 /* Receive double slot B-field in auto mode */
#define  B_BRDP       0x7A /* Receive double slot B-field protected */
/*#define             0X7B  NOT USED */
/*#define             0X7C  NOT USED */
/*#define             0X7D  NOT USED */
/*#define             0X7E  NOT USED */
/*#define             0X7F  NOT USED */

/* ADPCM COMMANDS -100-x- */
#define  A_RCV0       0x80 /* Set ReCeive Volume level */
/*#define             0X81 NOT USED */
#define  A_RCV36      0x82 /* Set ReCeive Volume level */
#define  A_RCV30      0x83 /* Set ReCeive Volume level */
#define  A_RCV24      0x84 /* Set ReCeive Volume level */
#define  A_RCV18      0x85 /* Set ReCeive Volume level */
#define  A_RCV12      0x86 /* Set ReCeive Volume level */
#define  A_RCV6       0x87 /* Set ReCeive Volume level */
/*#define             0X88  NOT USED */
/*#define             0X89  NOT USED */
#define  A_RCV33      0x8A /* Set ReCeive Volume level */
#define  A_RCV27      0x8B /* Set ReCeive Volume level */
#define  A_RCV21      0x8C /* Set ReCeive Volume level */
#define  A_RCV15      0x8D /* Set ReCeive Volume level */
#define  A_RCV9       0x8E /* Set ReCeive Volume level */
#define  A_RCV3       0x8F /* Set ReCeive Volume level */

/*#define             0X90  NOT USED */
/*#define             0X91  NOT USED */
/*#define             0X92  NOT USED */
/*#define             0X93  NOT USED */
/*#define             0X94  NOT USED */
/*#define             0X95  NOT USED */
/*#define             0X96  NOT USED */
/*#define             0X97  NOT USED */
/*#define             0X98  NOT USED */
/*#define             0X99  NOT USED */
/*#define             0X9A  NOT USED */
/*#define             0X9B  NOT USED */
/*#define             0X9C  NOT USED */
/*#define             0X9D  NOT USED */
/*#define             0X9E  NOT USED */
/*#define             0X9F  NOT USED */

/* Micro WIRE COMMands -101-1- + 0110 */
#define  M_INI0       0xA0  /* Micro wire initialization 0 */
#define  M_INI1       0xA1  /* Micro wire initialization 1 */
/*#define             0XA2     MICRO WIRE ENABLE 3 => '0' */
/*#define             0XA3     MICRO WIRE ENABLE 3 => '1' */
#define  MEN1N        0xA4  /* Micro wire ENable 1 => '0' */
#define  MEN1         0xA5  /* Micro wire ENable 1 => '1' */
/*#define             0XA6     MICRO WIRE ENABLE 2 => '0' */
/*#define             0XA7     MICRO WIRE ENABLE 2 => '1' */
/*#define             0XA8     MICRO WIRE READ */
#define  M_RST        0xA9  /* Micro wire Reset */
/*#define             0XAA  NOT USED */
/*#define             0XAB  NOT USED */
/*#define             0XAC  NOT USED */
/*#define             0XAD  NOT USED */
#define  C_ON2        0xAE /* codec2 on  */
#define  C_OFF2       0xAF /* codec2 off */
/*#define             0XB0  NOT USED */
/*#define             0XB1  NOT USED */
/*#define             0XB2  NOT USED */
/*#define             0XB3  NOT USED */
/*#define             0XB4  NOT USED */
/*#define             0XB5  NOT USED */
/*#define             0XB6  NOT USED */
/*#define             0XB7  NOT USED */
/*#define             0XB8  MICRO WIRE WRITE STATUS. */
#define  M_WR         0xB9 /* Micro Wire write */
#define  C_LD2        0xBA /* Load codec 2 control */
/*#define             0XBB  NOT USED */
/*#define             0XBC  NOT USED */
/*#define             0XBD  NOT USED */
/*#define             0XBE  NOT USED */
/*#define             0XBF  NOT USED */

/* ADPCM COMMANDS -110-- */
#define  A_RST        0xC0 /* ReSeT +PoWerDown */
#define  A_MUTE       0xC1 /* Set Mute on */
#define  A_STOFF      0xC2 /* Set SiDeTone off */
/*#define             0XC3  */
/*#define             0XC4  SET DATA MODE */
#define  A_NORM       0xC5 /*  */
#define  A_LDR        0xC6 /* LoaD data RAM ADPCM Read-address and reset counter */
#define  A_LDW        0xC7 /* LoaD data RAM ADPCM Write-address */
/*#define             0XC8  SET MUTE ON */
#define  A_MTOFF      0xC9 /* Set Mute on */
#define  A_MUTE1      0xCA /* Set Mute on */
#define  A_MTOFF1     0xCB /* Set Mute on */
#define  A_STON       0xCC /* Set Mute on */
/*#define             0XCD  NOT USED */
#define  A_LDR1       0xCE /* Set Mute on */
#define  A_LDW1       0xCF /* Set Mute on */

/*#define             0XD0  NOT USED */
/*#define             0XD1  NOT USED */
/*#define             0XD2  NOT USED */
/*#define             0XD3  NOT USED */
/*#define             0XD4  NOT USED */
/*#define             0XD5  NOT USED */
/*#define             0XD6  NOT USED */
/*#define             0XD7  NOT USED */
/*#define             0XD8  NOT USED */
/*#define             0XD9  NOT USED */
/*#define             0XDA  NOT USED */
/*#define             0XDB  NOT USED */
/*#define             0XDC  NOT USED */
/*#define             0XDD  NOT USED */
/*#define             0XDE  NOT USED */
/*#define             0XDF  NOT USED */

/*#define             0XE0  NOT USED */
#define  A_ST18       0xE1 /* Set sidetone -18 */
/*#define             0XE2  NOT USED */
/*#define             0XE3  NOT USED */
/*#define             0XE4  NOT USED */
/*#define             0XE5  NOT USED */
#define  P_FAD        0xE6 /* Fase antenna diversity */
#define  P_ANT        0xE7 /* Antenna selection */

/* Pin coMMANDS -1110- */
#define  P_LD         0xE8 /* Set PowerDown pins to parameter 0 or '1' */
#define  P_EN         0xE9 /* Set PowerDown pins programmed value after reset */
#define  P_SC         0xEA /* Set PowerDown pins synchronisation control */
#define  A_RST1       0xEB /* Set Mute on */
#define  P_LDL        0xEC /* Set PowerDown pins to parameter 0 or '1' */
#define  P_LDH        0xED /* Set PowerDown pins to parameter 0 or '1'  */

/* codec-AFE COMMAnds -111x- */
#define  C_ON         0xEE /* Codec on */
#define  C_OFF        0xEF /* Codec off */
/*#define             0XF0  NOT USED */
/*#define             0XF1  NOT USED */
/*#define             0XF2  NOT USED */
/*#define             0XF3  NOT USED */
/*#define             0XF4  NOT USED */
/*#define             0XF5  NOT USED */
/*#define             0XF6  NOT USED */
/*#define             0XF7  NOT USED */
/*#define             0XF8  NOT USED */
/*#define             0XF9  NOT USED */
#define  C_LD         0xFA /* load AFE control bytes */
/*#define             0xFB  not used */
/*#define             0xFC  not used */
/*#define             0xFD  not used */
/*#define             0xFE  not used */
/*#define             0xFF  not used */

