#ifndef GLIBC_H_
#define GLIBC_H_

#ifdef PCCOMPILE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#else
#define offsetof(type, member)   ((unsigned long int)(&((type *)0)->member))
#define RAND_MAX        32767
extern void *memset(void *dst, int c, unsigned long int length);
extern void *memcpy(void *, const void *, unsigned long int length);
extern unsigned long int strlen(const char *);
extern int memcmp(const void*, const void *, unsigned long int);
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern void *memmove(void *,const void *, unsigned long int);
#endif
extern int rand(void);
extern int abs(int);
extern int div16(int, int);
extern signed long int div32(signed long int x, signed long int y);
extern int mod(int, int);
extern signed long int mod32(signed long int x, signed long int y);
extern signed long int mul32(signed long int x, signed long int y);
#endif /* GLIBC_H_ */
