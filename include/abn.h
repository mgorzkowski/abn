//
// Copyright (c) 2018-2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#ifndef ABN_H
#define ABN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef ABN_UNIT_BITSIZE
#define ABN_UNIT_BITSIZE 32
#endif

typedef unsigned char byte;

// The abn_unit is the most basic type of integer the library works on.
// It should be defined as possible the widest integer type your compiller support.
// The abn_halfunit must be two times shorter.
// eg. abn_unit -> uint32_t, abn_halfunit -> uint16_t
#if ABN_UNIT_BITSIZE == 128
#	define ABN_UNIT_SIZE 16
	typedef uint128_t abn_unit;
	typedef uint64_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 64
#	define ABN_UNIT_SIZE 8
	typedef uint64_t abn_unit;
	typedef uint32_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 32
#	define ABN_UNIT_SIZE 4
	typedef uint32_t abn_unit;
	typedef uint16_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 16
#	define ABN_UNIT_SIZE 2
	typedef uint16_t abn_unit;
	typedef uint8_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 8
#	define ABN_UNIT_SIZE 1
	typedef uint8_t abn_unit;
	typedef uint8_t abn_halfunit;
#else
	#error There is no ABN_UNIT_SIZE set. Compile with appropriate flag (eg. -DABN_UNIT_SIZE=32) or set ABN_UNIT_SIZE in abn.h
	#define ABN_COMPILATION_ERROR
#endif /* ABN_UNIT_BITSIZE */

#ifndef ABN_COMPILATION_ERROR

extern const abn_unit ABN_UNIT_MAX;
extern const abn_unit ABN_UNIT_MIN;

// TODO: rename whole functions and add mnemonics file
#ifdef ABN_MNEMONICS
#	include ""
#endif /* ABN_MNEMONICS */

// Main type of abn library
typedef struct abn_t {
	abn_unit* chain;
	unsigned int volume;	// size in abn_units (in general not in bytes!)
} abn_t;

// TODO: 	Provide set of safe functions 
//		that checks arguments and returns appropriate completion code 
// Completion codes
typedef enum ABN_COMPLETION_CODE
{
	ABN_SUCCESS,
	ABN_ERROR = 0x80,
	ABN_ERROR_ARGUMENT_INVALID
} ABN_COMPLETION_CODE;

// Standard operations
abn_t* abn_create(unsigned int volume);
abn_t* abn_create_from_string(const char* string);
abn_t* abn_create_copy(abn_t* arg);
abn_t* abn_create_empty(void);
void abn_free(abn_t* arg);
void abn_reset(abn_t* arg);
void abn_clone(abn_t* destination, abn_t* source);
void abn_copy(abn_t* destination, abn_t* source);
bool abn_is_empty(abn_t* arg);
byte abn_get_byte(abn_t* arg, unsigned int whichOne);
void abn_set_byte(abn_t* arg, byte value, unsigned int whichOne);

// Basic math operations
bool abn_are_equal(abn_t* arg_a, abn_t* arg_b);
bool abn_is_negative(abn_t* arg);
bool abn_is_positive(abn_t* arg);
bool abn_is_zero(abn_t* arg);
bool abn_is_greater(abn_t* arg_a, abn_t* arg_b);
bool abn_is_less(abn_t* arg_a, abn_t* arg_b);

// String operations
char* abn_to_string(abn_t* arg);
char* abn_unit_to_string(abn_unit arg);
void abn_string_to_abn(const char* string, abn_t* arg);

// Arithmetic operations
void abn_add(abn_t* arg_a, abn_t* arg_b);
void abn_sub(abn_t* arg_a, abn_t* arg_b);
void abn_adu(abn_t* arg, abn_unit value);
void abn_sbu(abn_t* arg, abn_unit value);
void abn_inc(abn_t* arg);
void abn_dec(abn_t* arg);
void abn_mul(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_mulu(abn_t* result, abn_t* arg_a, abn_unit value);
void abn_smul(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_neg(abn_t* arg);
bool abn_abs(abn_t* arg);

// Bit operations
void abn_not(abn_t* arg);
void abn_and(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_or(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_xor(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_nand(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_nor(abn_t* result, abn_t* arg_a, abn_t* arg_b);
void abn_shift_left(abn_t* arg, abn_unit distance);
void abn_shift_right(abn_t* arg, abn_unit distance);
void abn_rotate_left(abn_t* arg, abn_unit distance);
void abn_rotate_right(abn_t* arg, abn_unit distance);

#endif /* ABN_COMPILATION_ERROR */

#endif /* ABN_H */
