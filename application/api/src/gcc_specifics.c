#include "../../../include/common/include/_stddef.h"
#include "../../../include/common/include/glibc.h"
#include "../../../include/common/include/print_status.h"
#include "../../../include/common/include/map_480_gcc.h"
#include "stdarg.h"


#ifdef GCCCOMPILE
unsigned char cstack[0x400];
unsigned char istack[0x100] __attribute__ ((section (".data")));
unsigned short StackEnd;
#else
unsigned char cstack[0x400];
unsigned char istack[0x100];
unsigned short StackEnd;
#endif
extern void initSegmentsFP(void);
extern void initSegmentsPP(void);
extern void initSegmentsServ(void);

#define MAX_STRING_SIZE 100
typedef unsigned int size_t;
#define EOF     (-1)

void initSegments(void)
{
    initSegmentsFP();
    initSegmentsPP();
    initSegmentsServ();
}

signed int PutChar(char *pStr, char c)
{
    *pStr = c;
    return 1;
}

signed int PutString(char *pStr, const char *pSource)
{
    signed int num = 0;

    while (*pSource != 0) {

        *pStr++ = *pSource++;
        num++;
    }

    return num;
}

signed int PutUnsignedInt(
    char *pStr,
    char fill,
    signed int width,
    unsigned int value)
{
    signed int num = 0;
    width--;
    if ((div16(value,10)) > 0) {

        num = PutUnsignedInt(pStr, fill, width, (div16(value,10)));
        pStr += num;
    }
    else {
        while (width > 0) {

            PutChar(pStr, fill);
            pStr++;
            num++;
            width--;
        }
    }
    num += PutChar(pStr, mod(value,10) + '0');
    return num;
}

signed int PutSignedInt(
    char *pStr,
    char fill,
    signed int width,
    signed int value)
{
    signed int num = 0;
    unsigned int absolute;

    if (value < 0) {

        absolute = -value;
    }
    else {

        absolute = value;
    }

    width--;

    if (div16(absolute,10) > 0) {

        if (value < 0) {

            num = PutSignedInt(pStr, fill, width, -div16(absolute,10));
        }
        else {

            num = PutSignedInt(pStr, fill, width, div16(absolute,10));
        }
        pStr += num;
    }
    else {

        if (value < 0) {

            width--;
        }

        while (width > 0) {

            PutChar(pStr, fill);
            pStr++;
            num++;
            width--;
        }

        if (value < 0) {

            num += PutChar(pStr, '-');
            pStr++;
        }
    }

    num += PutChar(pStr, mod(absolute,10) + '0');
    return num;
}

signed int PutHexa(
    char *pStr,
    char fill,
    signed int width,
    unsigned char maj,
    unsigned int value)
{
    signed int num = 0;

    width--;

    if ((value >> 4) > 0) {

        num += PutHexa(pStr, fill, width, maj, value >> 4);
        pStr += num;
    }
    else {

        while (width > 0) {

            PutChar(pStr, fill);
            pStr++;
            num++;
            width--;
        }
    }

    if ((value & 0xF) < 10) {

        PutChar(pStr, (value & 0xF) + '0');
    }
    else if (maj) {

        PutChar(pStr, (value & 0xF) - 10 + 'A');
    }
    else {

        PutChar(pStr, (value & 0xF) - 10 + 'a');
    }
    num++;

    return num;
}

signed int kt_vsnprintf(char *pStr, size_t length, const char *pFormat, va_list ap)
{
    char          fill;
    unsigned char width;
    signed int    num = 0;
    signed int    size = 0;

    if (pStr) {

        *pStr = 0;
    }
    while (*pFormat != 0 && size < length) {

        if (*pFormat != '%') {

            *pStr++ = *pFormat++;
            size++;
        }
        else if (*(pFormat+1) == '%') {

            *pStr++ = '%';
            pFormat += 2;
            size++;
        }
        else {

            fill = ' ';
            width = 0;
            pFormat++;

            if (*pFormat == '0') {

                fill = '0';
                pFormat++;
            }
            while ((*pFormat >= '0') && (*pFormat <= '9')) {

                width = (width*10) + *pFormat-'0';
                pFormat++;
            }
            if (size + width > length) {

                width = length - size;
            }
            switch (*pFormat) {
            case 'd':
            case 'i': num = PutSignedInt(pStr, fill, width, va_arg(ap, signed int)); break;
            case 'u': num = PutUnsignedInt(pStr, fill, width, va_arg(ap, unsigned int)); break;
            case 'x': num = PutHexa(pStr, fill, width, 0, va_arg(ap, unsigned int)); break;
            case 'X': num = PutHexa(pStr, fill, width, 1, va_arg(ap, unsigned int)); break;
            case 's': num = PutString(pStr, va_arg(ap, char *)); break;
            case 'c': num = PutChar(pStr, va_arg(ap, unsigned int)); break;
            default:
                return EOF;
            }

            pFormat++;
            pStr += num;
            size += num;
        }
    }
    if (size < length) {

        *pStr = 0;
    }
    else {

        *(--pStr) = 0;
        size--;
    }

    return size;
}

signed int kt_snprintf(char *pString, size_t length, const char *pFormat, ...)
{
    va_list    ap;
    signed int rc;

    va_start(ap, pFormat);
    rc = kt_vsnprintf(pString, length, pFormat, ap);
    va_end(ap);

    return rc;
}


signed int kt_vsprintf(char *pString, const char *pFormat, va_list ap)
{
    return kt_vsnprintf(pString, MAX_STRING_SIZE, pFormat, ap);
}

signed int kt_vfprintf(const char *pFormat, va_list ap)
{
    /*char pStr[MAX_STRING_SIZE];  HM use StatusString?*/
    char *pStr=StatusString;
    char pError[] = "increase MAX_STRING_SIZE\n\r";
    signed int rc;
    rc=kt_vsprintf(pStr, pFormat, ap);
    if (rc >= MAX_STRING_SIZE) {

        PrintStatus(0, pError);
        while (1);
    }

    PrintStatus(0, pStr);
    return rc;

}

signed int kt_vprintf(const char *pFormat, va_list ap)
{
    return kt_vfprintf(pFormat, ap);
}


int _sprintf_(char* str, char* fmt, ...)
{
  va_list ap;
  signed int result;
  va_start(ap, fmt);
  result = kt_vsprintf(str, fmt, ap);
  va_end(ap);

  return result;
//    int i = strlen(fmt);
//    memcpy(str, fmt, i + 1);
//    return i;
}

int _printf_(char* fmt, ...)
{
  va_list ap;
  int i;
  va_start(ap, fmt);
  i = kt_vprintf(fmt, ap);
  va_end(ap);
    return i;
//    int i = strlen(fmt);
//    PrintStatus(0, fmt);
//    return i;
}

unsigned long Get_stack_bottom(void)
{
    return (unsigned long) &cstack[0];
}

unsigned long Get_istack_bottom(void)
{
    return (unsigned long) &istack[0];
}

typedef unsigned int USItype        __attribute__ ((mode (SI)));

USItype __mulsi3(USItype a, USItype b)
{
    USItype c = 0;

    while (a != 0) {
        if (a & 1)
            c += b;
        a >>= 1;
        b <<= 1;
    }

    return c;
}

extern char bdata, edata, erodata, bbss, ebss, bmcdrams, bmcdrame;

static void clearRAM(void)
{
    char *src = (char*)0x8000;
    while (src < (char*)0x9fff)
    {
        *src++ = 0x00;
    }
    src = (char*)0x10000;
    while (src < (char*)0x13fff)
    {
        *src++ = 0x00;
    }
}

void init_compiler_specifics(void)
{
    char *src = &erodata;
    char *dst = &bdata;

    clearRAM();
    /* ROM has data at end of text; copy it. */
    while (dst < &edata) {
        *dst++ = *src++;
    }

    dst = &bbss;

    while (dst < &ebss) {
        *dst++ = 0;
    }

    dst = &bmcdrams;

    while (dst < &bmcdrame) {
        *dst++ = 0;
    }

    StackEnd = (unsigned short) &cstack[1023];
}


