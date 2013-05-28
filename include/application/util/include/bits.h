#ifndef _BITS_H
#define _BITS_H

#include "../../../common/include/rtxdef.h"

extern uint16 _SetBits(uint16 target, uint16 mask, uint16 value);
extern uint16 _GetBits(uint16 target, uint16 mask);

#define SetBits(target, mask, value) *target = _SetBits(*target, mask, value)
#define GetBits(target, mask) _GetBits(*target, mask)
#define SetWord(target, value) *target = value
#define GetWord(target) *target

#endif
