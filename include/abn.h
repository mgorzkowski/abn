#ifndef __ABN_H__
#define __ABN_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned char byte;

// The abn_unit is the most basic type of integer the library works on and
// it should be defined as possible the widest integer type your compiller support.
// The abn_halfunit must be two times shorter.
// eg. abn_unit -> uint32_t, abn_halfunit -> uint16_t
typedef uint64_t abn_unit;
typedef uint32_t abn_halfunit;

// Main type of abn library
typedef struct abn_t {
	abn_unit* chain;
	unsigned int volume;	// in abn_units (in general not in bytes!)
} abn_t;

abn_t* abn_create(unsigned int volume);
abn_t* abn_create_with_zeros(unsigned int volume);
abn_t* abn_create_with_chain(abn_unit* chain, unsigned int volume);
abn_t* abn_create_empty();
void abn_free(abn_t* op);

bool abn_is_empty(abn_t* op);
bool abn_are_equal(abn_t* op1, abn_t* op2);
char* abn_to_string(abn_t* arg);

// Operations
void abn_add(abn_t* result, abn_t* op1, abn_t* op2);
void abn_mul(abn_t* result, abn_t* op1, abn_t* op2);
void abn_reset(abn_t* op1);
void abn_copy(abn_t* destination, abn_t* source);
void abn_shift_left(abn_t* op, unsigned int distance);
void abn_shift_right(abn_t* op, unsigned int distance);


#endif /* __ABN_H__ */
