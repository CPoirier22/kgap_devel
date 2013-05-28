/*
 ********************************************************************
 *
 * Module: EEPLayOut.h
 *
 * Config-item: ?
 *
 * Contents: This file is the header file for EEPROM layout.
 *
 * Author: ON
 *
 ********************************************************************
 */
#include "../../include/mac/eeprom/include/fnvm.h"

#ifndef EEPROMLAYOUT_HEADER__
#define EEPROMLAYOUT_HEADER__

#define NUMBER_OF_SUBS           100

#define EEP_Rfpi                                    0x0000
#define EEP_Rfpi_Length                             0x0005

#define EEP_FPPPSelect                              0x0005
#define EEP_FPPPSelect_Length                       0x0001

#define EEP_ParkLength                              0x0006
#define EEP_ParkLength_Length                       0x0001

#define EEP_Led_Indication_Enabled                  0x0007
#define EEP_Led_Indication_Enabled_Length           0x0001

#define EEP_RUN_MODE                                0x0008
#define EEP_RUN_Length                              0x0001

#define EEP_DiversityMode                           0x0009
#define EEP_DiversityMode_Length                    0x0001

#define EEP_SERIAL_FILTER                           0x000A
#define EEP_SERIAL_FILTER_Length                    0x0001

#define EEP_SHARED_SUBSCRIPTION_MODE                0x000B
#define EEP_SHARED_SUBSCRIPTION_MODE_Length         0x0001

#define EEP_EXT_CODEC2_REG                          0x000C
#define EEP_EXT_CODEC2_REG_LENGTH                   0x0005

#define EEP_EXT_CODEC3_REG                          0x0011
#define EEP_EXT_CODEC3_REG_LENGTH                   0x0005

#define EEP_RSSI_Compensation                       0x0016
#define EEP_RSSI_Compensation_Length                0x0003

#define EEP_ForceBusy                               0x0019
#define EEP_ForceBusy_Length                        0x0001

#define EEP_HoMask                                  0x001A
#define EEP_HoMask_Length                           0x0001

#define EEP_HandoverInfo                            0x001B
#define EEP_HandoverInfo_Length                     0x0001

#define EEP_FpSyncNoLockResetTimeAddr               0x001C
#define EEP_FpSyncNoLockResetTimeAddr_Length        0x0002

#define EEP_RSSIBusyLevel                           0x001E
#define EEP_RSSIBusyLevel_Length                    0x0001

#define EEP_BandGapDef                              0x001F
#define EEP_BandGapDef_Length                       0x0001

#define EEP_NonGapExtFreqMode                       0x0020
#define EEP_NonGapExtFreqMode_Length                0x0001

#define EEP_RfCarrierAvailInfo                      0x0021
#define EEP_RfCarrierAvailInfo_Length               MAC_RfCarrierAvailInfo_Length

#define EEP_FREQ_ADDRESS                            0x0023
#define EEP_FREQ_ADDRESS_Length                     0x0001

#define EEP_FPBmcInitDataArr                        0x0025
#define EEP_FPBmcInitDataArr_Length                 MAC_BmcInitDataArr_Length

#define EEP_RFcapabilities                          0x0035
#define EEP_RFcapabilities_Length                   MAC_RFcapabilities_Length

#define EEP_ExtFPCap                                0x003a
#define EEP_ExtFPCap_Length                         MAC_ExtFPCap_Length

#define EEP_HF_TestMode                             0x003f
#define EEP_HF_TestMode_Length                      0x0001

#define EEP_ActiveSubsNo                            0x0040
#define EEP_ActiveSubsNo_Length                     0x0001

#define SYSTEM_ARI_LENGTH                           0x0041
#define SYSTEM_ARI_LENGTH_LENGTH                    0x0001

#define EEP_FP_Modulation                           0x0042
#define EEP_FP_Modulation_Length                    0x0001

#define EEP_FP_PP_POSSIBLE                          0x0043
#define EEP_FP_PP_POSSIBLE_LENGTH                   0x0001

#define EEP_PPBmcInitDataArr                        0x0044
#define EEP_PPBmcInitDataArr_Length                 0x0006

#define EEP_FP_ConnectionTimeOut                    0x004a      /*End adr 000A Start adr. dec    10  Size dec       1  Size Hex  0x0001*/
#define EEP_FP_ConnectionTimeOut_Length             0x0001

#define Subs0StartAddr                              0x004b
#define SubsSize                                    0x33
#define Subs0StartAddr_Length                       0x66        /* 2 users 0x33 * 2 == 0x66*/

#define LOCK_ARI                                    0x00b1
#define LOCK_ARI_LENGTH                             0x0005

#define GOOD_SYNC_RSSI                              0x00b6
#define GOOD_SYNC_RSSI_LENGTH                       0x0001

#define EEP_FIXEDDUMMYBEARER                        0x00b7
#define EEP_FIXEDDUMMYBEARER_Length                 0x0001

#define EEP_PP_LockedTime                           0x00b8
#define EEP_PP_LockedTime_Length                    0x0001

#define SubsAccessLevelsAddr                        0x00b9      /* 2 users*/
#define SubsAccessLevelsAddr_Length                 0x0002

#define NEW_SYNC                                    0x00bb
#define NEW_SYNC_LENGTH                             0x0001

#define EEP_Accepted_RSSI_PP                        0x00bc      /*End adr 001B Start adr. dec    27  Size dec       1  Size Hex  0x0001*/
#define EEP_Accepted_RSSI_PP_Length                 0x0001

#define EE_LONG_SLOT		                        0x00bd
#define EE_LONG_SLOT_Length                    	    0x0001

#define EE_DLS                                      0x00be
#define EE_DLS_Length                               0x0001

#define VIRTUAL_HANDSET_SUBSCRIBE_ARI				 0x00bf
#define VIRTUAL_HANDSET_SUBSCRIBE_ARI_LENGTH		 0x0005

#define VIRTUAL_HANDSET_AC				 			 0x00c4
#define VIRTUAL_HANDSET_AC_LENGTH		 			 0x0008

#define FP_LMX4180_SETUP_PARAMETERS_TIMING0          0x00cc
#define FP_LMX4180_SETUP_PARAMETERS_TIMING0_Length   0x0018

#define FP_LMX4180_SETUP_PARAMETERS_TIMING           0x00cc     /* same as above, this is intended*/
#define FP_LMX4180_SETUP_PARAMETERS_TIMING_Length    0x0003

#define FP_LMX4180_SETUP_PARAMETERS_TIMING1          0x00e4

#define FP_LMX4180_SETUP_PARAMETERS_TIMING2          0x00fc

#define FP_LMX4180_SETUP_PARAMETERS_TIMING3          0x0114

#define FP_LMX4180_SETUP_PARAMETERS_TIMING4          0x012c

#define FP_LMX4180_SETUP_PARAMETERS_TIMING5          0x0144

#define FP_LMX4180_SETUP_PARAMETERS_TIMING6          0x015c

#define FP_LMX4180_SETUP_PARAMETER_NO_TIMING         0x0174
#define FP_LMX4180_SETUP_PARAMETER_NO_TIMING_Length  0x0006

#define FP_LMX4180_ALTERNATINGBITS_ADDRESS           0x017A /* start address of the parameters in EEProm*/
#define FP_LMX4180_ALTERNATINGBITS_ADDRESS_Length    0x0008 /* start address of the parameters in EEProm*/

#define FP_SECURITY_CONFIG_1_addr			         0x0182
#define FP_SECURITY_CONFIG_1_length					 0x0001

#define FP_SECURITY_CONFIG_2_addr			         0x0183 /* start address of the parameters in EEProm*/
#define FP_SECURITY_CONFIG_2_length					 0x0001

#define EEP_PP_LockedMode                           0x0184
#define EEP_PP_LockedMode_Length                    0x0001

#define EE_MODULE2MODULE                            0x0185
#define EE_MODULE2MODULE_Length                     0x0001

#define EE_FREE1			                        0x0186
#define EE_FREE1_Length                    			0x002c

#define KirkIdAddr                           		0x01b0
#define KirkIdAddr_Length                    		0x0008

#define HW_PCS                           			0x01B8
#define HW_PCS_Length                    			0x0008

#define pta_variables                           	0x01c0
#define pta_variables_Length                    	0x0020

#define EEP_FactoryEMC                              0x01E0
#define EEP_FactoryEMC_Length                       0x0002

#define EEP_LowQualityLevel                         0x01E2
#define EEP_LowQualityLevel_Length                  0x0001

#define EEP_UserDataArea                            0x01E3
#define EEP_UserDataArea_Length                     0x0100

#define EE_CUSTOMER_AREA                            0x02E3
#define EE_CUSTOMER_AREA_Length                     0x0100

#define EE_FREE2			                        0x03E3
#define EE_FREE2_Length                    			0x021D

#define QuickDataBaseAddr                           0x0600
#define QuickDataBaseAddr_Length                    0x0136

extern const EEPromAdressCodeConverterType EEPromAdressCodeConverterSource[LAST_EEPROM_ADDRESS];

#endif
