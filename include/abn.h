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

/* *INDENT-OFF* */

#ifndef ABN_UNIT_BITSIZE
    // this is default bitsize, modify it if you need
    #define ABN_UNIT_BITSIZE 32
#endif

// The abn_unit is the basic type of integer the library works on.
// It should be defined as possible the widest integer type your compiller support.
// The abn_halfunit must be two times shorter.
// eg. abn_unit -> uint32_t, abn_halfunit -> uint16_t
#if ABN_UNIT_BITSIZE == 128
    typedef uint128_t abn_unit;
    typedef uint64_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 64
    typedef uint64_t abn_unit;
    typedef uint32_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 32
    typedef uint32_t abn_unit;
    typedef uint16_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 16
    typedef uint16_t abn_unit;
    typedef uint8_t abn_halfunit;
#elif ABN_UNIT_BITSIZE == 8
    typedef uint8_t abn_unit;
    typedef uint8_t abn_halfunit;
#else
    #error ABN_UNIT_BITSIZE is not defined. Build with appropriate flag (eg. -DABN_UNIT_BITSIZE=32) or set ABN_UNIT_BITSIZE here in abn.h
    #define ABN_COMPILATION_ERROR
#endif /* ABN_UNIT_BITSIZE */

/* *INDENT-ON* */

#ifndef ABN_COMPILATION_ERROR

// abn_unit is unsigned integer type thus this subtraction is not an undefined behaviour
#define ABN_UNIT_MAX                            (((abn_unit)0) - 1)
#define ABN_UNIT_MIN                            ((abn_unit)0)
#define ABN_STRING_LENGTH_MAX                   (ABN_UNIT_MAX/4 + 1)

#define ABN_IS_BITSIZE_VALID(bitsize)           (((bitsize)%sizeof(abn_unit)==0) ? true : false)
#define ABN_MINIMAL_VALID_BITSIZE(bitsize)      (ABN_IS_BITSIZE_VALID(bitsize) ? (bitsize) : ((bitsize)/sizeof(abn_unit)+1))

typedef uint8_t byte;

// TODO: maybe to rename some names:
// volume -> capasity?
// bitsize -> ???

// Main type of abn library
typedef struct abn_t {
    // sequence of elemets that contains part of the number
    abn_unit *chain;
    // bitsize must be multiply of ABN_UNIT_BITSIZE
    abn_unit bitsize;
    // has owned buffer allocated on the heap
    bool has_owned_buffer;
} abn_t;

// Completion codes
typedef enum ABN_COMPLETION_CODE {
    ABN_SUCCESS,
    ABN_ERROR = 0x80,
    ABN_ERROR_ARGUMENT_INVALID
} ABN_COMPLETION_CODE;

// TODO: change all malloc calls to abn_malloc, that should be implemented by the user (weak implementation with just malloc)
// Creation operations
abn_t abn_create(abn_unit *buffer, abn_unit bitsize);
abn_t abn_create_from_string(abn_unit *buffer, abn_unit buffer_size, const char *string);
abn_t abn_create_copy(abn_unit *buffer, abn_unit buffer_size, abn_t prototype);
abn_t abn_create_empty(void);
abn_t abn_alloc(abn_unit bitsize);
abn_t abn_alloc_from_string(const char *string);
abn_t abn_alloc_copy(abn_t prototype);
void abn_free(abn_t *number);

// Standard operations
bool abn_is_empty(abn_t number);
void abn_reset(abn_t number);
bool abn_are_identical(abn_t number_1, abn_t number_2);
ABN_COMPLETION_CODE abn_copy(abn_t destination, abn_t source);
ABN_COMPLETION_CODE abn_get_byte(byte *result, abn_t arg, unsigned int which_one);
ABN_COMPLETION_CODE abn_set_byte(abn_t arg, byte value, unsigned int which_one);
ABN_COMPLETION_CODE abn_get_bit(byte *result, abn_t arg, unsigned int which_one);
ABN_COMPLETION_CODE abn_set_bit(abn_t arg, byte value, unsigned int which_one);

// Basic math operations
bool abn_are_equal(abn_t number_1, abn_t number_2);
bool abn_is_positive (abn_t number);
bool abn_is_negative (abn_t number);
bool abn_is_zero (abn_t number);
bool abn_is_above(abn_t number_1, abn_t number_2);
bool abn_is_below(abn_t number_1, abn_t number_2);
bool abn_is_greater(abn_t number_1, abn_t number_2);
bool abn_is_less(abn_t number_1, abn_t number_2);

// String operations
//mg: it should be specified how the string must looks like
//mg: string should look like this: "A76A44B5" - proper size, in hexadecimal form, without any additional characters like minus.
//mg: string like "-123" is not supported yet
char*   abn_to_string (abn_t *arg);
char*   abn_unit_to_string (abn_unit arg);
void    abn_string_to_abn (const char *string, abn_t *arg);

// Arithmetic operations
//mg: in documentation should be said what happened if number is overflowed (set to zero or lock to MAX value, or return error code)
//mg: check english names of operands (like odjemna, odjemnik in polish)
//mg: rename this functions to be more informative (add -> additiona, mulu - > multiply_by_unit, etc.)
void    abn_add (abn_t *arg_a, abn_t *arg_b);
void    abn_sub (abn_t *arg_a, abn_t *arg_b);
void    abn_adu (abn_t *arg, abn_unit value);
void    abn_sbu (abn_t *arg, abn_unit value);
void    abn_inc (abn_t *arg);
void    abn_dec (abn_t *arg);
//mg: in documenation should be said that result can be te same what first arg (if it is true, ofc.)
void    abn_mul (abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_mulu (abn_t *result, abn_t *arg_a, abn_unit value);
//mg: is it necessary? (I guess - yes)
void    abn_smul (abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_neg (abn_t *arg);
bool    abn_abs (abn_t *arg);

// Bit operations
//mg: why bit operations have separate result, but shift operations not?
//mg: determine what if arguments has different size
void    abn_not(abn_t *arg);
void    abn_and(abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_or(abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_xor(abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_nand(abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_nor(abn_t *result, abn_t *arg_a, abn_t *arg_b);
void    abn_shift_left(abn_t *arg, abn_unit distance);
void    abn_shift_right(abn_t *arg, abn_unit distance);
void    abn_rotate_left(abn_t *arg, abn_unit distance);
void    abn_rotate_right(abn_t *arg, abn_unit distance);

// TODO: (proposal) to create api that facilitate creating sub-numbers

// TODO: Rename whole functions (full names) and add mnemonics file
// #ifdef ABN_MNEMONICS
//     #include ""
// #endif /* ABN_MNEMONICS */

#endif  /* ABN_COMPILATION_ERROR */

#endif  /* ABN_H */
