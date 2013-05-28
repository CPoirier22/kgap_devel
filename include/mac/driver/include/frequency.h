#ifndef FREQUENCY_H_
#define FREQUENCY_H_

#include "../../../common/include/_stddef.h"


void initFrequency(void);
void updatePhaseInfo(BYTE CRCInfo, BYTE slideErrors, signed char phaseOffset);
void updateFrequency();
void setFrequency(BYTE freq);
BYTE getFrequency(void);

#endif /*FREQUENCY_H_*/
