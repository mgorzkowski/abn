#ifndef __SHIFTS_H__
#define __SHIFTS_H__

#include "../abn.h"

void abn_shift_left(abn_t* op, unsigned int distance);
void abn_shift_right(abn_t* op, unsigned int distance);

#endif /* __SHIFTS_H__ */
