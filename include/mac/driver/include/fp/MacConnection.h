#ifndef MACCONNECTION_H_
#define MACCONNECTION_H_

typedef enum {
    RELEASED,
    CONNECTPENDING,
    CONNECTED,
    CHOVPENDING,
    HANDOVERPENDING,
    HANDOVER
}CcfStateType;

typedef struct
{
    BYTE Channel,HoChannel;
    BYTE ReqDataSegmentNr;
    BYTE IndDataSegmentNr;
    BYTE Pmid[3];
    BYTE HOparm;
    BYTE EncKey[8];
    BYTE EncStatus;
    BYTE SpeechBuffer;
    CcfStateType State;
    BearerDataReqType BearerDataReq;
    BYTE ChQuality;
    BYTE Lid;
    BYTE ConferenceId;
#ifdef DISTANCE_MEASSUREMENT
    char Phase;
    char SlidingErrors;
    int  Distance;
    int  ScannDistance;
    char Debounce;
    Boolean DistChanged1;
    Boolean DistChanged2;
    char MSF_Time_Out;
    char LastPhase;
    char LastSlidingErrors;
    int  LastDistance;
    long LongDistance;
#endif
}
MacConnectionType;

#endif /*MACCONNECTION_H_*/
