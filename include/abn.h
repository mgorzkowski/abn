#ifndef __ABN_H__
#define __ABN_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

#include "utilities/string_manipulations.h"
#include "operations/addition_algorithms.h"
#include "operations/multiplication_algorithms.h"
#include "operations/shifts.h"
#include "operations/others.h"

abn_t* abn_create(unsigned int volume);
abn_t* abn_create_with_zeros(unsigned int volume);
abn_t* abn_create_with_chain(abn_unit* chain, unsigned int volume);
abn_t* abn_create_empty();

void abn_free(abn_t* op);

bool abn_is_empty(abn_t* op);
bool abn_are_equal(abn_t* op1, abn_t* op2);

#endif /* __ABN_H__ */
