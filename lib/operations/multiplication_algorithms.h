#ifndef __MULTIPLICATION_ALGORITHMS_H__
#define __MULTIPLICATION_ALGORITHMS_H__

#include "../abn.h"

void abn_mul(abn_t* result, abn_t* op1, abn_t* op2);
void abn_unit_mul(abn_t* result, abn_unit op1, abn_unit op2);

#endif /* __MULTIPLICATION_ALGORITHMS_H__ */
