/*
 ********************************************************************
 *
 * Module: f_nvm.h
 *
 * Config-item: ?
 *
 * Contents: This file is the header file for f_nvm.c.
 *
 * Author: MK
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */
#ifndef F_NONVOLMEM_HEADER__
#define F_NONVOLMEM_HEADER__


#include "../../../common/include/identify.h"
#include "../../../hlkgap/common/include/sformat.h"

#ifndef ADPCM_ADJUSTMENT
#define Input_Offset                      0x0000
#define Output_Offset                     0x0001
#define Nibble_Adjust                     0x0001
#endif

#define EEDEFAULT_NORMAL   0x00
#define EEDEFAULT_FORCED   0x01
#define EEDEFAULT_FF_FILL  0x02

#define EE_WRITE_DELAY_LOOPCOUNT 5000   /*500*/
#define EE_PAGE_SIZE 16
#define EE_DEVICEADDRESS 0xA0   /* 1010 0000 = Device address for page 0 write.*/
#define EE_WRITE_TIME    (3*T10_MS)     /* 20-30ms*/

#define EN_ACCESS2_INT  (1<<7)
#define EN_ACCESS_BUS2  (1<<0)
#define ACCESS2_INT (1<<5)

#define NON_VOL_MEM_WRITE_TIMER           0
#define NON_VOL_MEM_WRITE_TIME_OUT_VALUE  2

/*============================ MACROS / CONSTANTS ============================*/

typedef U16Bits NonVolMemAddrType;

struct NonVolMemQueueEntryStruct
{
    U16Bits WriteBeginAddress, WriteEndAddress;
    UByte AttemptCounter;
    struct NonVolMemQueueEntryStruct *NextEntry;
};
typedef struct NonVolMemQueueEntryStruct NonVolMemQueueEntryType;

typedef enum
{ SPIIdle,
  SPIReady1,
  SPIReady2,
  SPIWrEnable,
  SPIWrite1,
  SPIWrite2,
  SPIWrite3,
  SPIReceive1,
  SPIReceive2,
  SPIReceive3,
  SPIReceive4
} SPIModeType;

#define EEPROMWRSR               0x01
#define EEPROMWRITE              0x02
#define EEPROMREAD               0x03
#define EEPROMWRDI               0x04
#define EEPROMRDSR               0x05
#define EEPROMWREN               0x06


typedef enum {
    FP_RFPI,     /* 00: Get FP RFPI code from EEPROM*/
    FP_RFCARRIER,    /* 01: Get RF carrier available from EEPROM*/
    FP_CONNECT_TO,    /* 02: Get FP connection time-out*/
    FP_BMCINITDATAARR,   /* 03: Get FP BMC initialization parameters.*/
    FP_EEPROM_FREQ,    /* 04: Get FP frequency setting.*/
    FP_RFCAPABILITIES,   /* 05: Get FP RF capabilities.*/
    FP_FIXEDDUMMYBEARER,  /* 06: Get FP fixed dummybearer.*/
    FP_DIVERSITYMODE,   /* 07: Get FP diversity*/
    FP_EXTFPCAP,    /* 08: Get FP extended FP capabilities*/
    FP_TXMODDCLEVEL,   /* 09: Get FP TX modulation DC level 12 slot only*/
    FP_HFTESTMODE,    /* 0A: Get FP RF testmode value.*/
    FP_BANDGAPDEF,    /* 0B: Get FP bandgap value.*/
    FP_NONGAPEXTFREQMODE,  /* 0C: Get FP frequency range*/
    FP_RSSIBUSYLEVEL,   /* 0D: Get FP RSSI busy level, USA version.*/
    FP_RXSYNCSEARCHTIMEADDR, /* 0E: Get FP search sync time out.*/
    FP_SYNCNOLOCKRESETTIME,  /* 0F: Get FP time out from no lock to restart search*/

    FP_HANDOVERINFO,   /* 10: Get FP handover info.*/
    FP_HOMASK,                  /* 11: Get FP handover mask.*/
    FP_FORCEBUSY,    /* 12: Get FP flag force busy active*/
    FP_LMXSETUPTIMING0,   /* 13: Get 1'st 24 byte of FP LMX 4169 setup table*/
    FP_LMXSETUPTIMING1,   /* 14: Get 2'nd 24 byte of FP LMX 4169 setup table*/
    FP_LMXSETUPTIMING2,   /* 15: Get 3'rd 24 byte of FP LMX 4169 setup table*/
    FP_LMXSETUPTIMING3,   /* 16: Get 4'th 24 byte of FP LMX 4169 setup table*/
    FP_LMXSETUPTIMING4,   /* 17: Get 5'th 24 byte of FP LMX 4169 setup table*/
    FP_LMX4169_ALTERNATINGBITS_ADDRESS,   /* 18: Get 6'th 24 byte of FP LMX 4169 setup table*/
    FP_LMXCALIBRATION,          /* 19: Get FP calibration sequence.*/
    FP_LMXSETUPTIM,    /* 1A: Get FP LMX setup timing.*/
    FP_LMXSETUPNOTIM,   /* 1B: Get FP LMX setup no timing.*/
    PP_EEPROMINRAM,    /* 1C: Get content of EEPROMInRam*/
    PP_NOTINRAMADDRESS,   /* 1D: Get content of EEPROMNotInRam*/
    PP_BMCINITDATA_ADDRESS,  /* 1E: Get BMC init data array.*/
    PP_EEPROM_FREQ,    /* 1F: Get PP frequency setting.*/

    PP_BMC_LSR_MIC_GAIN,  /* 20: Get PP loudspeaker mic. gain*/
    PP_BMCCONFIG,    /* 21: Get PP BMC configuration*/
    PP_VOLUMENSTEPLOW,   /* 22: Get PP volumen step low*/
    PP_VOLUMENSTEPMEDIUMLOW, /* 23: Get PP volumen step next low*/
    PP_VOLUMENSTEPMEDIUM,  /* 24: Get PP volumen step medium.*/
    PP_VOLUMENSTEPMEDIUMHIGH,   /* 25: Get PP volumen step next high.*/
    PP_VOLUMENSTEPHIGH,   /* 26: Get PP volumen step high.*/
    PP_CODEC_LSR_REG_OFF_HOOK, /* 27: Get value of codec LSR reg. for off hook.*/
    PP_CODEC_LSR_REG_OFF_HOOK_HEADSET, /* 28: Get value of codec LSR reg. for headset mode*/
    PP_CODEC_LSR_REG_OFF_HOOK_HAND_FREE, /* 29: Get value of codec LSR reg. for hands free mode*/
    PP_MICLSRHFREE,    /* 2A: Get PP loudspeaker mic. gain for handsfree mode.*/
    PP_MICLSHEADSET,   /* 2B: Get PP loudspeaker mic. gain for headset mode.*/
    PP_IPEIEE,     /* 2C: Get PP serial number, IPEI.*/
    PP_DSP_FILTER1_ADDRESS,  /* 2D: Get PP mic. filter*/
    PP_DSP_FILTER4_ADDRESS,  /* 2E: Get PP headset filter.*/
    PP_DSP_FILTER3_ADDRESS,  /* 2F: Get PP loudspeaker filter.*/

    PP_DSP_FILTER2_ADDRESS,  /* 30: Get PP ear filter.*/
    PP_DSP_FILTER5_ADDRESS,  /* 31: Get PP handsfree filter.*/
    PP_BMC_ALTERNATINGBITS,  /* 32: Get PP alternating bits.*/
    PP_LANGUAGE_ENABLED,  /* 33: Get PP show language.*/
    PP_EE_LANGUAGE_NAME,  /* 34: Get PP language name*/
    PP_AUTO_LOGIN_2_PARAMETERS, /* 35: Get auto login parameters*/
    PP_ActiveSubsNo,   /* 36: Get PP active subscription number.*/
    PP_P_EEMenu_SW_Number,  /* 37; Get PP SW number*/
    PP_P_EEMenu_PIE_Number,  /* 38: Get PP PIE number.*/
    PP_P_Item_Number,   /* 39: Get PP item number*/
    PP_P_HW_PCS,    /* 3A: Get PP HW PCS number.*/
    PP_P_Initial_SW_Number,  /* 3B: Get initial SW number.*/
    PP_P_Initial_SW_PIE,  /* 3C: Get initial PIE number.*/
    PP_P_YEAR_WEEK,    /* 3D: Get production year and week.*/
    PP_STANDBYTXT_DEFAULT_ADDRESS, /* 3E: Get standby text default*/
    PP_STANDBYTXT_KIRK_ADDRESS, /* 3F: Get Kirk standby text*/

    PP_HFREE_PARAMETERS,  /* 40: Get PP handsfree parameters.-*/
    PP_Test_Data_Factory,  /* 41: Get saved production data*/
    PP_FUNC_KEY_DELAY,   /* 42: Get function key delay.*/
    PP_BATTERY,     /* 43: Get battery charge parameters.*/
    PP_MAIL_SETUP_PAR,   /* 44: Get PP mail setup parameters.*/
    PP_TEL_BOOK_ADDRESS,  /* 45: Get telephone book.*/
    PP_BOOK_INDEX,    /* 46: Get telephone book index*/
    PP_Subs0StartAddr,   /* 47: Get subscription data.*/
    PP_REDIAL,     /* 48: Get redial numbers*/
    PP_STACK_INDEKS,   /* 49: Get stack index*/
    PP_MAIL,     /* 4A: Get mail.*/
    PP_MAIL_INDEX,    /* 4B: Get mail index.*/
    PP_STACK_DATE,    /* 4C: Get stack date.*/
    PP_SUB_LOCAL_NO,   /* 4D: Get subset local number*/
    PP_SPEED_DAIL,    /* 4E: Get speed dial.*/
    PP_LMX4169_SETUP_PARAMETER_NO_TIMING, /* 4F: Get PP LMXX setup parameters not timed*/

    PP_LMX4169_SETUP_PARAMETERS_TIMING, /* 50: Get PP LMXX setup parameters timed*/
    PP_LMX4169_SETUP_PARAMETERS_TABLE, /* 51: Get PP LMXX setup parameters timed*/
    PP_LMX4169_CALIBRATION_PARAMETERS, /* 52: Get PP LMXX calibration parameters*/
    PP_LMX4169_ALTERNATINGBITS_ADDRESS, /* 53: Get PP LMXX alternating bits*/
    PP_MAX_RSSI,    /* 54: Get PP max RSSI value.*/
    FP_PP_SELECT,	/* 55: FP / PP select*/
    FP_CONFIG1,		/* 56: FP config (RFP5)*/
    PP_FactoryEMC,  /* 57: Factory EMC*/
    PP_MacFunctionConfig,	/* 58: MAC function configuration.*/
    PP_AutoLockinTimer,     /* 59: Auto Login timer*/
    PP_AutoLockinOutLockTimer,  /* 5A: Auto Login out of lock timer*/
    PP_Display_Contrast,		/* 5B: Display contrast*/
    PP_Password,				/* 5C: Password for menus*/
    PP_FixedTxtFunctionNo,		/* 5D: 1'st char in MSF call*/
    PP_HandsetLocalNr,			/* 5E: Handset local number.*/
    PP_ConnectionTimeOut,		/* 5F: PP connection time out.*/

    PP_lockedTime,				/* 60: PP lockedTime.*/
    PP_Accepted_RSSI_PP,		/* 61: Accepted_RSSI_PP*/
    PP_LowQualityLevel,			/* 62: Signal quality for handover*/
    PP_LockMode,				/* 63: Power saving modes allowed*/
    PP_RSSI_Compensation,		/* 64: RSSI compensation table.*/
    PP_UIFunctionConfig2,		/* 65: User interface configuration*/
    PP_LowBattVoltage,			/* 66: Low battery voltage*/
    PP_Startup_Logo,			/* 67: Display logo at startup*/
    PP_UIFunctionConfig,		/* 68: User interface configuration*/
    PP_Prof1SetupA,				/* 69: Profile 1 setup A*/
    PP_Prof1SetupB,				/* 6A: Profile 1 setup B*/
    PP_Prof1SetupC,				/* 6B: Profile 1 setup C*/
    PP_PP_Type,					/* 6C: PP type*/
    PP_AdvancedUIConfig,		/* 6D: Advanced UI Config*/
    PP_AdvancedUISettings,      /* 6E: Advanced UI Settings*/
    SHARED_SUBSCRIPTION_MODE,   /* 6F: subscription mode    bit 0: fp limit to known == 1, bit 1: pp limit to known == 1*/
    PP_BUZZER_VOLUME,    		/* 70: Buzzer volume PP*/
    PP_COMFORT_VOLUME,          /* 71: Peltor comfort tone volume*/
    PP_LSRMICGAIN,              /* 72: Get PP loudspeaker mic. gain.*/
    SERIAL_FILTER,				/* 73: get serial filter*/
    FP_Modulation,				/* 74: FP_Modulation*/
    PP_Modulation,				/* 75: PP_Modulation*/
    KIRK_ID,					/* 76: KIRK_ID*/
    VOX_LEVEL,					/* 77: vox levels 6*2 byte*/
    USE_EMERGENCY_CHANNEL,		/* 78: Use emergency channel (on/off)*/
    USE_DECT_ENCRYPTION,	    /* 79: Use Dect Encryption (on/off)*/
    BATTERY_LOW_WARNING,		/* 7A: Battery low warning (minutes remaining on battery)*/
    BATTERY_EMPTY_WARNING,		/* 7B: Battery empty warning (minutes remaining on battery)*/
    DISCONNECT_FROM_CONFWHENCH, /* 7C: Disconnect from conference when charging*/
    HEADPHONES_VOLUME_PLUGOFF,  /* 7D: Headphones Volume Plug Offset*/
    NOT_USED,							/* 7E: Headphones AGC (EARL)*/
    LED_INDICATION_ENABLED,		/* 7F: Led Indication Enabled*/
    AC_CODE,					/* 80: AC CODE (both used by FP and PP)*/
    PTA_VARIABLES,				/* 81: PTA variables 32 bytes, only used by pta.*/
    FP_PP_POSSIBLE,				/* 82: FP_PP possible, which type: fp, pp, fppp, mlitary*/
    PELTOR_STATE,				/* 83: Peltor state backup*/
    PARK_LENGTH,				/* 84: park length, fp value in dummybearer info*/
    VOX_DELAY,					/* 85: Vox attack delay time*/
    VOX_OFF_LEVEL,				/* 86: Vox levels 6x2 byte*/
    VOX_DECAY,					/* 87: Vox decay delay time*/
    TRAP_SOUND_PLAY,			/* 88: Play error message on next startup*/
    TRAP_INFO,				    /* 89: Trap Info*/
    FP_LOCK_ARI1,				/* 8A: Lock ari1*/
    MIC_SENSITIVITY,			/* 8B: Microphone sensitivity levels for: low impedans, dynamic, electret, carbon*/
    CODEC2_REGISTERS,			/* 8c: Register values for external CODEC 2 setup*/
    CODEC3_REGISTERS,			/* 8d: Register values for external CODEC 3 setup*/
    KEY_TIMING,					/* 8e: KEY timing 10ï¿½s of milliseconds: double click, long key, reserved*/
    FP_NEW_SYNC,                /* 8F: New syncronizing method*/
    FP_GOOD_SYNC_RSSI,          /* 90: Minimum RSSI value for sync*/
    FP_SYSTEM_ARI1_LENGTH,      /* 91: System ARI1 length for FP syncronization*/
    USER_TEXT,                  /* 92: user text, readable zero terminated string. (max 50 bytes inkl. zero).*/
    AGC_PARAMETERS,             /* 93: AGC parameters for mic input.*/
    RUN_MODE,                   /* 94: Run mode, only mac or dduos?*/
    TX_POWER_DAC_1G8,           /* 95: DAC value controlling TX power when in 1G8 mode (RFP5)*/
    TX_POWER_DAC_1G9,           /* 96: DAC value controlling TX power when in 1G9 mode (RFP5)*/
    FP_P_HW_PCS,                /* 97: Get FP HW PCS number.*/
    FP_CABLE_DELAY,             /* 98: Get RFP5 Cable Delay*/
    PELTORPPCONFIGTYPE,			/* 99: Get EEP_PELTORPPCONFIGTYPE*/
    PELTORFPCONFIGTYPE,			/* 9a: GET EEP_PELTORFPCONFIGTYPE*/
    DSP_CONF,					/* 9b: GET DSP_CONF type*/
    EMERGENCY_CHANNEL_MAX_TX_TIME, /* 9c: EMERGENCY_CHANNEL_MAX_TX_TIME*/
    PP_MUTE_CONTROL, 			/* 9d: PP_MUTE_CONTROL*/
    FP_LOCK_ARI2,				/* 9e: Lock ari2*/
    FP_SYSTEM_ARI2_LENGTH,      /* 9f: System ARI2 length for FP syncronization*/
    FP_LMXSETUPTIMING5,         /* 100: Get 6'th 24 byte of FP LMX 4169 setup table*/
    FP_LMXSETUPTIMING6,         /* 101: Get 7'th 24 byte of FP LMX 4169 setup table*/
    KT4585AUTOSUB,				/* 102: 5 byte ari used by auto subscription (virtual handset)*/
    FP_SECURITY_CONFIG_1,		/* 103: 1'st security confugaration byte*/
    FP_SECURITY_CONFIG_2,       /* 104: 2'nd security confugaration byte*/
    FPPP_DLS,                   /* 105: DLS*/
    LONG_SLOT,                  /* 106: Long slot (640 bits B-field) or short (320 bits)*/
    MODULE2MODULE,              /* 107: Module2Module bearerf/p optimized*/
    SOFTWARE_PCS,               /* 108: Software version number*/
    LAST_EEPROM_ADDRESS
}EEPromAdressCodeType;

typedef struct
{
    WORD  Address;
    WORD  Length;
}
EEPromAdressCodeConverterType;

#define MAC_RfCarrierAvailInfo_Length   0x0002
#define MAC_BmcInitDataArr_Length       0x0010
#define MAC_RFcapabilities_Length       0x0005
#define MAC_ExtFPCap_Length             0x0005

typedef struct
{
	BYTE Power_Control;
	BYTE Mode_Control;
	BYTE Transmit_Gain;
	BYTE Receive_Level;
	BYTE Auxillary;
} ExtCodecDataType;

typedef struct
{
	BYTE Channels[12];
	BYTE ExtCodec[2];
	BYTE ConferenceGain[5];
	BYTE DSPConfMode;
} DSPConfSettings;

typedef struct
{
    BYTE FP_PP_Select;
    BYTE RfCarrierAvailInfo[MAC_RfCarrierAvailInfo_Length];  /* 0005 - 0006*/
    WORD CableDelay;
    BYTE BmcInitDataArr[MAC_BmcInitDataArr_Length];        /* 0009 - 0018*/
    BYTE RFcapabilities[MAC_RFcapabilities_Length];          /* 0019 - 001d*/
    BYTE ExtFPCap[MAC_ExtFPCap_Length];       /* 0027 - 002b*/
    BYTE HF_TestMode;           /* 0044*/
    BYTE BandGapDef;           /* 0062*/
    BYTE NonGapExtFreqMode;          /* 0063*/
    BYTE RSSIBusyLevel;    /* 006b*/
    WORD FpSyncNoLockResetTimeAddr; /* 04e8 - 04e9*/
    BYTE HandoverInfo;       /* 04ea*/
    BYTE HoMask;     /* 04eb*/
    BYTE ForceBusy;     /* 04ec*/
    BYTE RssiComp1, RssiComp2, RssiComp3;
    BYTE Config1;
    BYTE NoOfAllowedUsersAddr[2]; /* 1fed - 1fee*/
    BYTE VOIPMACAddr[17];   /* 1fef - 1fff*/
    ExtCodecDataType CODEC[2];
    BYTE NewSync;
    BYTE GoodSync;
    BYTE FP_Lock_Ari1[5];
    BYTE FP_Lock_Ari1_Length;
    BYTE FP_Lock_Ari2[5];
    BYTE FP_Lock_Ari2_Length;
    BYTE EepromFrequency;
	BYTE EepromFrequencyCoarse;
    DSPConfSettings DSPConf;
    BYTE longSlot;
}
FP_EepromInRamType;

typedef struct
{
    WORD FactoryEmc;
    BYTE MacFunctionConfig;
    BYTE AutoLoginLoginTimer;     /* Re.: Auto login: Time for login to finish (in seconds)*/
    BYTE AutoLoginOutLockTimer;   /* Re.: Auto login: Time to be out of lock before search (in seconds)*/
    BYTE Display_Contrast;
    BYTE BuzzerVolumeAdjust; /*HDM*/
    BYTE Free1;
    BYTE Free2;
    BYTE EEP_Password[2];
    BYTE FixedTxtFunctionNo;
    BYTE HandsetLocalNr;
    BYTE ConnectionTimeOut;
    BYTE PPlockedTime;            /* Number of MultiFrames with no valid RFPI (approx. 2 sec)*/
    BYTE AcceptableRssiLevel;
    BYTE RssiMargien;
    BYTE LowQualityLevel;
    BYTE LockMode;
    BYTE RssiComp1, RssiComp2, RssiComp3;
    BYTE UIfunctionConfig2;
    BYTE LowBattVoltage;
    BYTE EmptyBattVoltage;
    BYTE Startup_Logo;
    BYTE UIfunctionConfig;
    BYTE _NonGapExtFreqMode;
    BYTE Prof1SetupA;             /*setupflags for profile1*/
    BYTE Prof1SetupB;             /*ringertone and ringervol for profile1*/
    BYTE Prof1SetupC;             /*buzzervol for profile1*/
    BYTE PP_Type;                 /* 0x55=4020, 0xAA=4040*/
    BYTE AdvancedUIConfig;
    BYTE AdvancedUISettings;
    BYTE VolumenStepLow;
    BYTE VolumenStepMediumLow;
    BYTE VolumenStepMedium;
    BYTE VolumenStepMediumHigh;
    BYTE VolumenStepHigh;
    BYTE PlugOffset;
    BYTE Comf_Tone_Volume[2*5];
    BYTE Codec_LSR_OffHook[2];
    BYTE Codec_LSR_OffHook_Headset[2];
    BYTE Codec_LSR_OffHook_HFree[2];
    BYTE Codec_Mic_Loudsp;
    BYTE Codec_Mic_HFree;
    BYTE Codec_Mic_Headset;
}
PP_EepromInRamType;


typedef enum {Searching,
              CheckPtHead,
              CheckQtHead,
              GetARIAfterQtHead,
              SyncronizedToMaster,
              PossibleOutOfSync} SyncType;

extern UByte System_Par_Received;
extern UByte System_ARI_ORG[MaxAriOctets];
extern UByte System_ARI[MaxAriOctets];
extern UByte System_ARI_SYNC_MASTER[MaxAriOctets];
extern unsigned long lSystem_ARI_SYNC_MASTER;
extern UByte System_ARI_SYNC_ALT[MaxAriOctets];
extern unsigned long lSystem_ARI_SYNC_ALT;
extern UByte System_SyncSlave;
extern UByte System_ARI_length;
extern UByte System_Sync_length;
extern SyncType Syncronized;
extern UByte System_Sync_Timeout;


#define TermAccRightsAtAuthFail  0x01
#define KeyAllocAtSubsCreate     0x02
#define AuthAtLocReg             0x04
#define AuthAtIncCall            0x08
#define AuthAtOutCall            0x10


#define SubsNotAllowed 0x01
typedef struct
{
    UByte EmptyMarker;
    UByte Upi[MaxUpiOctets];
    UByte Uak[MaxUakOctets];
    UByte CheckSum;
}
SubsDataSlotType;

extern far BYTE AccessCode[3 + 3][3];
extern far BYTE GapAccessCode[4];
extern far BYTE GapProtocolConfigFlag;
extern far BYTE FEHandlingMode;
extern far WORD LogPreservationReasons;
extern far SubsDataSlotType SubsDataInRam;

#ifndef IGNOREINDEXERWARNING
#ifndef SIZE_OF_NON_VOL_MEM
#error Must define SIZE_OF_NON_VOL_MEM in build file
#endif
#endif

extern __no_init FP_EepromInRamType FP_EepromInRam;
extern __no_init PP_EepromInRamType PP_EepromInRam;

extern WORD SPISendQueIndex;
extern WORD SPISendQueCount;
extern WORD SPIRecQueIndex;
extern WORD SPIRecQueCount;
extern BYTE SPIMode;
extern WORD EEPROMAddress;
extern BYTE EEstatus;

Boolean UserDefault(BYTE Mode,BYTE Filler);
Boolean FillEEProm(BYTE Filler);
void *GetPhysicalAddress(NonVolMemAddrType NonVolMemAddr);
void InitNonVolMem(void);
/*void BurnDefault(BYTE Mode, void (*resetWatchDog) (void));*/
void BurnDefault(BYTE Mode);
void BusyWait5ms(void);
void LoadNonVolMemData(void);
void ReadEEPromData(UByte * DestinPtr, EEPromAdressCodeType AddrCode);
Boolean WriteEEPromData(UByte * srcPtr, EEPromAdressCodeType AddrCode);
BYTE ReadEEbyte(WORD EEaddress);
WORD EeGetPageSize(void);
void AwaitEepromReady(void);

#endif
