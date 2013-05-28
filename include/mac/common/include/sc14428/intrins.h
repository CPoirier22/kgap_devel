
#ifndef __INTRINS_H
#define __INTRINS_H
#define interrupt __interrupt

#if defined DEPLIST
/* If DepList.exe is the caller we must force it to not*/
/* expand InCr16.h as it contains an error directive*/
/* which will only allow the IAR CR16 compiler to use it.*/
#define _INCR16_INCLUDED
#endif

#define Reg_PSR __PSR
#ifndef IGNOREINDEXERWARNING
#include <intrinsics.h>
#endif
#endif
