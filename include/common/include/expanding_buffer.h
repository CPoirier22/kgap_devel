#ifndef EXPANDING_BUFFER_H_
#define EXPANDING_BUFFER_H_

#include "bitsdef.h"

typedef struct _expanding_buffer
{
    BYTE* buffer;
    int bufferSize;
}
ExpandingBuffer;

ExpandingBuffer * new_expanding_buffer();
void ensure_buffer(ExpandingBuffer * buffer, int length);
void free_buffer(ExpandingBuffer * buffer);

#endif /*EXPANDING_BUFFER_H_*/
