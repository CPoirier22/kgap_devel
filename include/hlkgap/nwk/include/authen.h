/*----------------------------------------------------------------------------
*  Copyright(C):   1996, RTX A/S,  all rights reserved
*  Project:        Digital European Cordless Telecommunications (DECT)
*  File:           Authen.h
*  Purpose:        Authentication key generation
*----------------------------------------------------------------------------*/



typedef struct
{
    unsigned char e[16];
    unsigned char ks[16];
}
DsaaResType;

extern DsaaResType *ares;



extern void StartRes1AndDckCalculation(unsigned char *key, unsigned char *rs, unsigned char *rand_f);
extern void StartRes2Calculation(unsigned char *key, unsigned char *rs, unsigned char *rand_p);
extern unsigned char ContinueCalculation(void);

extern void EndCalculation(void);

extern void GetRes(unsigned char *res);
extern void GetDck(unsigned char *dck);
extern void GetKs(unsigned char *Ks);
extern void GetKs(unsigned char *Ks);

extern void ConvertAcToK(unsigned char *ac, unsigned char *k);
extern void ConvertUakToK(unsigned char *uak, unsigned char *k);
extern void ConvertUpiAndUakToK(unsigned char *upi, unsigned char *uak, unsigned char *k);
