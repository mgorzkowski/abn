//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#ifndef ABN_H
#define ABN_H

#include <stdint.h>
#include <stdbool.h>

typedef unsigned char byte;

// The abn_unit is the most basic type of integer the library works on.
// It should be defined as possible the widest integer type your compiller support.
// The abn_halfunit must be two times shorter.
// eg. abn_unit -> uint32_t, abn_halfunit -> uint16_t
typedef uint32_t abn_unit;
typedef uint16_t abn_halfunit;

extern const abn_unit ABN_UNIT_MAX;
extern const abn_unit ABN_UNIT_MIN;

// Main type of abn library
typedef struct abn_t {
	abn_unit* chain;
	unsigned int volume;	// size in abn_units (in general not in bytes!)
} abn_t;

// Basic operations
abn_t* abn_create(unsigned int volume);
abn_t* abn_create_copy(abn_t* arg);
abn_t* abn_create_empty(void);
void abn_free(abn_t* arg);
void abn_reset(abn_t* arg);
void abn_copy(abn_t* destination, abn_t* source);
bool abn_is_empty(abn_t* arg);
bool abn_are_equal(abn_t* op1, abn_t* op2);
byte abn_get_byte(abn_t* arg, unsigned int whichOne);
void abn_set_byte(abn_t* arg, byte value, unsigned int whichOne);
char* abn_to_string(abn_t* arg);
char* abn_unit_to_string(abn_unit arg);

// Arithmetic operations
void abn_add(abn_t* op1, abn_t* op2);
void abn_sum(abn_t* result, abn_t* op1, abn_t* op2);
void abn_inc(abn_t* arg);
void abn_dec(abn_t* arg);
void abn_neg(abn_t* arg);
void abn_mul(abn_t* result, abn_t* op1, abn_t* op2);
void abn_smul(abn_t* result, abn_t* op1, abn_t* op2);
bool abn_is_negative(abn_t* arg);
bool abn_is_positive(abn_t* arg);
bool abn_abs(abn_t* arg);

// Bit operations
void abn_not(abn_t* op);
void abn_and(abn_t* result, abn_t* op1, abn_t* op2);
void abn_or(abn_t* result, abn_t* op1, abn_t* op2);
void abn_xor(abn_t* result, abn_t* op1, abn_t* op2);
void abn_nand(abn_t* result, abn_t* op1, abn_t* op2);
void abn_nor(abn_t* result, abn_t* op1, abn_t* op2);
void abn_shift_left(abn_t* op, unsigned int distance);
void abn_shift_right(abn_t* op, unsigned int distance);
void abn_rotate_left(abn_t* arg, unsigned int distance);
void abn_rotate_right(abn_t* arg, unsigned int distance);

#endif /* ABN_H */
