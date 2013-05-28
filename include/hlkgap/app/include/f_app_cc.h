#ifndef INTERFACEPRIM_H_
#define INTERFACEPRIM_H_

/*
 * The purpose of this file is to replace gim.
 * the embedded signal in gimmsg_ind and gimmsg_req replaced with new structs.
 */

#define    APPCCSetupReq                0x40        /*Incomming call*/
#define    APPCCConnectAckReq           0x41
#define    APPCCInfoReq                 0x42
#define    APPCCSetupInd                0x43        /*Outgoing call (off hook)*/
#define    APPCCSetupAckReq             0x44
#define    APPCCInfoInd                 0x45
#define    APPCCAbnormal				0x46

#endif /*INTERFACEPRIM_H_*/
