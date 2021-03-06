//
// Copyright (c) 2018-2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../include/abn.h"
#include <stdlib.h>
#include <string.h>

const abn_unit ABN_UNIT_MAX = ((abn_unit)0) - 1;
const abn_unit ABN_UNIT_MIN = (abn_unit)0;

// Public functions

// Creates abn_t
abn_t *abn_create(unsigned int volume)
{
    abn_t *result = (abn_t *)malloc(sizeof(abn_t));

    result->volume = 0;
    result->chain = (abn_unit *)malloc(volume * sizeof(abn_unit));
    if (result->chain != NULL) {
        result->volume = volume;
    }
    return result;
}

// Creates abn_t from a string in hexadecimal format (without '0x' prefix)
abn_t *abn_create_from_string(const char *string)
{
    abn_unit number_size = strlen(string) / 2;
    abn_t *result = abn_create(number_size / ABN_UNIT_SIZE);

    abn_string_to_abn(string, result);
    return result;
}

// Creates abn_t based on antoher abn_t
abn_t *abn_create_copy(abn_t *arg)
{
    abn_t *result = abn_create(arg->volume);

    abn_clone(result, arg);
    return result;
}

// TODO: consider of having this
// Creates an empty abn_t number
abn_t *abn_create_empty(void)
{
    abn_t *result = (abn_t *)malloc(sizeof(abn_t));

    result->chain = NULL;
    result->volume = 0;
    return result;
}

// Terminates the abn_t number
void abn_free(abn_t *arg)
{
    if (arg->chain != NULL) {
        free(arg->chain);
    }
    free(arg);
}

// Return true if the abn_t number is empty
bool abn_is_empty(abn_t *arg)
{
    if (arg->chain == NULL && arg->volume == 0) {
        return false;
    } else {
        return true;
    }
}

// Return true if abn_t numbers are equal
bool abn_are_equal(abn_t *op1, abn_t *op2)
{
    if (op1->volume != op2->volume) {
        return false;
    }
    for (int i = 0; i < op1->volume; i++) {
        if (op1->chain[i] != op2->chain[i]) {
            return false;
        }
    }
    return true;
}

// Resets the abn_t number
void abn_reset(abn_t *arg)
{
    for (int i = 0; i < arg->volume; i++) {
        arg->chain[i] = 0;
    }
}

// Creates a clone of abn_t number
void abn_clone(abn_t *destination, abn_t *source)
{
    if (destination->volume != source->volume) {
        abn_free(destination);
        destination = abn_create(source->volume);
    }
    for (int i = 0; i < source->volume; i++) {
        destination->chain[i] = source->chain[i];
    }
}

// Copies value from source to destination
void abn_copy(abn_t *destination, abn_t *source)
{
    if (destination->volume < source->volume) {
        abn_free(destination);
        destination = abn_create(source->volume);
    }
    for (int i = 0; i < source->volume; i++) {
        destination->chain[i] = source->chain[i];
    }
    for (int i = source->volume; i < destination->volume; i++) {
        destination->chain[i] = 0;
    }
}

// Setting particular byte
void abn_set_byte(abn_t *arg, byte value, unsigned int whichOne)
{
    unsigned int whichUnit = whichOne / sizeof(abn_unit);
    unsigned int whichByteInUnit = whichOne % sizeof(abn_unit);

    arg->chain[whichUnit] &= ~((abn_unit)0xFF << 8 * whichByteInUnit);
    arg->chain[whichUnit] |= value << 8 * whichByteInUnit;
}

// Getting particular byte
byte abn_get_byte(abn_t *arg, unsigned int whichOne)
{
    unsigned int whichUnit = whichOne / sizeof(abn_unit);
    unsigned int whichByteInUnit = whichOne % sizeof(abn_unit);

    return (arg->chain[whichUnit] >> (8 * whichByteInUnit)) & 0xFF;
}

// Returns true if anb_t is positive number
bool abn_is_positive(abn_t *arg)
{
    // TODO: unreadable if statement
    // if( arg->chain[arg->volume-1] > ( ((abn_unit)1) << ( (8*sizeof(abn_unit)) - 1 ) ) )
    if ((arg->chain[arg->volume - 1] & ((abn_unit)1 << (8 * sizeof(abn_unit) - 1))) > 0) {
        return false;
    }
    return true;
}

// Returns true if anb_t is negative number
bool abn_is_negative(abn_t *arg)
{
    if (abn_is_positive(arg)) {
        return false;
    }
    return true;
}

// Return true if arg is equal zero
bool abn_is_zero(abn_t *arg)
{
    for (int i = 0; i < arg->volume; i++) {
        if (arg->chain[i] != 0) {
            return false;
        }
    }
    return true;
}

// Returns true if arg_a > arg_b (unsigned)
// It was assumed that volumes of both operands are equal
bool abn_is_greater(abn_t *arg_a, abn_t *arg_b)
{
    for (int i = 0; i < arg_a->volume; i++) {
        if (arg_a->chain[i] > arg_b->chain[i]) {
            return true;
        } else if (arg_a->chain[i] < arg_b->chain[i]) {
            return false;
        }
    }
    return false;
}

// Returns true if arg_a < arg_b (unsigned)
// It was assumed that volumes of both operands are equal
bool abn_is_less(abn_t *arg_a, abn_t *arg_b)
{
    for (int i = 0; i < arg_a->volume; i++) {
        if (arg_a->chain[i] < arg_b->chain[i]) {
            return true;
        } else if (arg_a->chain[i] > arg_b->chain[i]) {
            return false;
        }
    }
    return false;
}
