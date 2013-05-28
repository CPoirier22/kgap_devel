#ifndef SEARCH_FLAG_H_
#define SEARCH_FLAG_H_

#include "../../../../common/include/_stddef.h"

#define M_SEARCHFLG_INHIBIT    0x01
#define M_SEARCHFLG_WAKEUP     0x10
#define M_SEARCHFLG_SEARCH     0x20
#define M_SEARCHFLG_STOPPED    0x40
#define M_SEARCHFLG_INITSLEEP  0x80

void set_search_flag(BYTE value);
BYTE get_search_flag(void);
void set_bit_search_flag(BYTE bit);
void clear_bit_search_flag(BYTE bit);
BYTE get_bit_search_flag(BYTE bit);

#endif /*SEARCH_FLAG_H_*/
