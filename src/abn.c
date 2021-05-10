//
// Copyright (c) 2018-2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../include/abn.h"
#include "abn_private.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Public functions

// Creation operations

// to documentation: bitsize should be aligned to sizeof(abn_unit)
abn_t abn_create(abn_unit *buffer, abn_unit bitsize)
{
    bitsize = ABN_MINIMAL_VALID_BITSIZE(bitsize);
    abn_t result = {
        .chain = buffer,
        .bitsize = bitsize,
        .has_owned_buffer = false,
    };
    return result;
}

// to documentation: buffer_size is bytes,
abn_t abn_create_from_string(abn_unit *buffer, abn_unit buffer_size, const char *string)
{
    abn_unit string_length = strlen(string);
    // one byte is encoded by 2 characters
    if (string_length > buffer_size * 2) {
        // size of given buffer is not sufficient
        return abn_create_empty();
    }

    // one character encodes 4 bits
    abn_t result = abn_create(buffer, string_length * 4);
    abn_string_to_abn(string, &result);

    return result;
}

// to documentation: buffer_size is bytes,
abn_t abn_create_copy(abn_unit *buffer, abn_unit buffer_size, abn_t prototype)
{
    if (prototype.bitsize > buffer_size * 8) {
        // size of given buffer is not sufficient
        return abn_create_empty();
    }

    abn_t result = abn_create(buffer, prototype.bitsize);
    if (ABN_SUCCESS != abn_copy(result, prototype)) {
        // should never happen
        result = abn_create_empty();
    }

    return result;
}

abn_t abn_create_empty(void)
{
    abn_t result = {};
    result.chain = NULL;
    result.bitsize = 0;
    result.has_owned_buffer = false;
    return result;
}

// to documentation: bitsize should be aligned to sizeof(abn_unit)
abn_t abn_alloc(abn_unit bitsize)
{
    bitsize = ABN_MINIMAL_VALID_BITSIZE(bitsize);
    abn_t result = abn_create_empty();
    const abn_unit volume = bitsize / ABN_UNIT_BITSIZE;
    void *buffer = malloc(volume * sizeof(abn_unit));
    if (NULL != buffer) {
        result.bitsize = bitsize;
        result.chain = (abn_unit *)buffer;
        result.has_owned_buffer = true;
    }

    return result;
}

// to documentation: it is have to be said that string shuold be null terminated
abn_t abn_alloc_from_string(const char *string)
{
    assert(strlen(string) <= ABN_STRING_LENGTH_MAX);

    // one character encodes 4 bits
    abn_unit bitsize = strlen(string) * 4;
    abn_t result = abn_alloc(bitsize);
    abn_string_to_abn(string, &result);

    return result;
}

abn_t abn_alloc_copy(abn_t prototype)
{
    if (abn_is_empty(prototype)) {
        return prototype;
    } else {
        abn_t result = abn_alloc(prototype.bitsize);
        if (!abn_is_empty(result)) {
            abn_copy(result, prototype);
        }
        return result;
    }
}

void abn_free(abn_t *number)
{
    if (true == number->has_owned_buffer && NULL != number->chain) {
        free(number->chain);
    }
    *number = abn_create_empty();
}

// Standard operations

// Return true if given number is empty
bool abn_is_empty(abn_t number)
{
    if (number.chain == NULL || number.bitsize == 0) {
        return false;
    } else {
        return true;
    }
}

// Reset the abn_t number
void abn_reset(abn_t number)
{
    for (int i = 0; i < GET_VOLUME(number); i++) {
        number.chain[i] = 0;
    }
}

// Return true if numbers are indentical (are equal and has the same bitsize)
bool abn_are_identical(abn_t number_1, abn_t number_2)
{
    if (number_1.bitsize != number_2.bitsize) {
        return false;
    }
    for (int i = 0; i < GET_VOLUME(number_1); i++) {
        if (number_1.chain[i] != number_2.chain[i]) {
            return false;
        }
    }
    return true;
}

// Copy value from source to destination
ABN_COMPLETION_CODE abn_copy(abn_t destination, abn_t source)
{
    if (destination.bitsize < source.bitsize) {
        return ABN_ERROR_ARGUMENT_INVALID;
    }
    for (int i = 0; i < GET_VOLUME(source); i++) {
        destination.chain[i] = source.chain[i];
    }
    for (int i = GET_VOLUME(source); i < GET_VOLUME(destination); i++) {
        destination.chain[i] = 0;
    }
    return ABN_SUCCESS;
}

// Get desired byte
ABN_COMPLETION_CODE abn_get_byte(byte *result, abn_t number, unsigned int which_one)
{
    if (which_one >= number.bitsize/8) {
        return ABN_ERROR_ARGUMENT_INVALID;
    }

    unsigned int which_unit = which_one / sizeof(abn_unit);
    unsigned int which_byte_in_unit = which_one % sizeof(abn_unit);

    byte *ptr = (byte *)&number.chain[which_unit] + which_byte_in_unit;
    *result = *ptr;

    return ABN_SUCCESS;
}

// Set desired byte
ABN_COMPLETION_CODE abn_set_byte(abn_t number, byte value, unsigned int which_one)
{
    if (which_one >= number.bitsize/8) {
        return ABN_ERROR_ARGUMENT_INVALID;
    }

    unsigned int which_unit = which_one / sizeof(abn_unit);
    unsigned int which_byte_in_unit = which_one % sizeof(abn_unit);

    byte *ptr = (byte *)&number.chain[which_unit] + which_byte_in_unit;
    *ptr = value;

    return ABN_SUCCESS;
}

// Get desired bit
ABN_COMPLETION_CODE abn_get_bit(byte *result, abn_t number, unsigned int which_one)
{
    if (which_one >= number.bitsize) {
        return ABN_ERROR_ARGUMENT_INVALID;
    }

    unsigned int which_unit = which_one / sizeof(abn_unit);
    unsigned int which_byte_in_unit = which_one % sizeof(abn_unit);
    unsigned int which_bit_in_byte = which_one % 8;

    byte *ptr = (byte *)&number.chain[which_unit] + which_byte_in_unit;
    *result = 0x01 & (*ptr >> which_bit_in_byte);

    return ABN_SUCCESS;
}

// Set desired bit
ABN_COMPLETION_CODE abn_set_bit(abn_t number, byte value, unsigned int which_one)
{
    if (which_one >= number.bitsize || value >= 2) {
        return ABN_ERROR_ARGUMENT_INVALID;
    }

    unsigned int which_unit = which_one / sizeof(abn_unit);
    unsigned int which_byte_in_unit = which_one % sizeof(abn_unit);
    unsigned int which_bit_in_byte = which_one % 8;

    byte *ptr = (byte *)&number.chain[which_unit] + which_byte_in_unit;

    if (1 == value) {
        // set bit
        *ptr |= (0x01 << which_bit_in_byte);
    } else {
        // reset bit
        *ptr &= ~(0x01 << which_bit_in_byte);
    }

    return ABN_SUCCESS;
}

// Basic math operations

// Return true if given numbers are equal
bool abn_are_equal(abn_t number_1, abn_t number_2)
{
    // swap to make sure that bitsize of number_1 <= bitsize of number_2
    abn_t temp = abn_create_empty();
    if (number_1.bitsize > number_2.bitsize) {
        temp = number_1;
        number_1 = number_2;
        number_2 = temp;
    }

    for (int i = 0; i < GET_VOLUME(number_1); i++) {
        if (number_1.chain[i] != number_2.chain[i]) {
            return false;
        }
    }

    for (int i = GET_VOLUME(number_1); i < GET_VOLUME(number_2); i++) {
        if (0 != number_2.chain[i]) {
            return false;
        }
    }
    return true;
}

// Return true if given number is positive
bool abn_is_positive(abn_t number)
{
    // zero is not positive number
    if (!abn_is_negative(number) && !abn_is_zero(number)) {
        return true;
    }
    return false;
}

// Return true if given number is negative
bool abn_is_negative(abn_t number)
{
    if (1 == GET_MOST_SIGNIFICANT_BIT(number)) {
        return true;
    }
    return false;
}

// Return true if given number is equal zero
bool abn_is_zero(abn_t number)
{
    for (int i = 0; i < GET_VOLUME(number); i++) {
        if (number.chain[i] != 0) {
            return false;
        }
    }
    return true;
}

// Return true if number_1 > number_2 (unsigned)
bool abn_is_above(abn_t number_1, abn_t number_2)
{
    // this is a volume that is common for both numbers
    abn_unit common_volume = MIN(GET_VOLUME(number_1), GET_VOLUME(number_2));

    // there are tree ways:
    if (number_1.bitsize > number_2.bitsize) {
        // if number_1[common_volume..volume] != 0 then result is set to false
        for (int i = common_volume; i<GET_VOLUME(number_1); i++) {
            if (number_1.chain[i] != 0) {
                return true;
            }
        }
    } else if (number_1.bitsize < number_2.bitsize) {
        // if number_2[common_volume..volume] != 0 then result is set to false
        for (int i = common_volume; i<GET_VOLUME(number_2); i++) {
            if (number_2.chain[i] != 0) {
                return false;
            }
        }
    }

    // compare numbers in range [0..common_volume]
    for (int i = common_volume-1; i >= 0; i--) {
        if (number_1.chain[i] > number_2.chain[i]) {
            return true;
        } else if (number_1.chain[i] < number_2.chain[i]) {
            return false;
        }
    }

    return false;
}

// Return true if number_1 < number_2 (unsigned)
bool abn_is_below(abn_t number_1, abn_t number_2)
{
    // this is a volume that is common for both numbers
    abn_unit common_volume = MIN(GET_VOLUME(number_1), GET_VOLUME(number_2));

    if (number_1.bitsize > number_2.bitsize) {
        // if number_1[common_volume..volume] != 0 then result is set to false
        for (int i = common_volume; i<GET_VOLUME(number_1); i++) {
            if (number_1.chain[i] != 0) {
                return false;
            }
        }
    } else if (number_1.bitsize < number_2.bitsize) {
        // if number_2[common_volume..volume] != 0 then result is set to false
        for (int i = common_volume; i<GET_VOLUME(number_2); i++) {
            if (number_2.chain[i] != 0) {
                return true;
            }
        }
    }

    // compare numbers in range [0..common_volume]
    for (int i = common_volume-1; i >= 0; i--) {
        if (number_1.chain[i] < number_2.chain[i]) {
            return true;
        } else if (number_1.chain[i] > number_2.chain[i]) {
            return false;
        }
    }

    return false;
}

// Return true if number_1 > number_2 (signed)
bool abn_is_greater(abn_t number_1, abn_t number_2)
{
    bool result = false;
    bool is_number_1_negative = abn_is_negative(number_1);
    bool is_number_2_negative = abn_is_negative(number_2);

    if (is_number_1_negative && is_number_1_negative) {
        // both are negative
        result = abn_is_below(number_1, number_2);
    } else if (!is_number_1_negative && !is_number_2_negative) {
        // both are not negative
        result = abn_is_above(number_1, number_2);
    } else if (is_number_1_negative && !is_number_2_negative) {
        // only number_1 is negative
        result = false;
    } else if (!is_number_1_negative && is_number_2_negative) {
        // only number_2 is negative
        result = true;
    }

    return result;
}

// Return true if number_1 < number_2 (signed)
bool abn_is_less(abn_t number_1, abn_t number_2)
{
    bool result = false;
    bool is_number_1_negative = abn_is_negative(number_1);
    bool is_number_2_negative = abn_is_negative(number_2);

    if (is_number_1_negative && is_number_1_negative) {
        // both are negative
        result = abn_is_above(number_1, number_2);
    } else if (!is_number_1_negative && !is_number_2_negative) {
        // both are not negative
        result = abn_is_below(number_1, number_2);
    } else if (is_number_1_negative && !is_number_2_negative) {
        // only number_1 is negative
        result = true;
    } else if (!is_number_1_negative && is_number_2_negative) {
        // only number_2 is negative
        result = false;
    }

    return result;
}
