//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"

// Private functions prototypes
void abn_short_shift_left(abn_t* arg, unsigned int distance);
void abn_short_shift_right(abn_t* arg, unsigned int distance);
void abn_long_shift_left(abn_t* arg, unsigned int distance);
void abn_long_shift_right(abn_t* arg, unsigned int distance);

// Public functions

// Bit shift left
void abn_shift_left(abn_t* arg, unsigned int distance)
{
	int long_distance = distance / (8*sizeof(abn_unit));
	int short_distance = distance % (8*sizeof(abn_unit));

	if(long_distance != 0)
	{
		abn_long_shift_left(arg, long_distance);
	}
	if(short_distance != 0)
	{
		abn_short_shift_left(arg, short_distance);
	}
}

// Bit shift right
void abn_shift_right(abn_t* arg, unsigned int distance)
{
	int long_distance = distance / (8*sizeof(abn_unit));
	int short_distance = distance % (8*sizeof(abn_unit));

	if(long_distance != 0)
	{
		abn_long_shift_right(arg, long_distance);
	}
	if(short_distance != 0)
	{
		abn_short_shift_right(arg, short_distance);
	}
}

// Bit rotate left
void abn_rotate_left(abn_t* arg, unsigned int distance)
{
	abn_t* tmp = abn_create_copy(arg);
	unsigned int max_rotate = 8 * sizeof(abn_unit) * arg->volume;
	abn_shift_left(arg, distance);
	abn_shift_right(tmp, max_rotate - distance);
	abn_add(arg, arg, tmp);
}

// Bit rotate right
void abn_rotate_right(abn_t* arg, unsigned int distance)
{
	abn_t* tmp = abn_create_copy(arg);
	unsigned int max_rotate = 8 * sizeof(abn_unit) * arg->volume;
	abn_shift_right(arg, distance);
	abn_shift_left(tmp, max_rotate - distance);
	abn_add(arg, arg, tmp);
}

// Private functions

// Shifts left integer number of bits up to 8*sizeof(abn_unit) bits
void abn_short_shift_left(abn_t* arg, unsigned int distance)
{
	abn_unit carry = 0;
	for(int i=0; i<arg->volume; i++)
	{
		abn_unit tmp = arg->chain[i] >> (8*sizeof(abn_unit) - distance);
		arg->chain[i] <<= distance;
		arg->chain[i] += carry;
		carry = tmp;
	}
}

// Shifts right integer number of bits up to 8*sizeof(abn_unit) bits
void abn_short_shift_right(abn_t* arg, unsigned int distance)
{
	abn_unit carry = 0;
	for(int i=arg->volume-1; i>=0; i--)
	{
		abn_unit tmp = arg->chain[i] << (8*sizeof(abn_unit) - distance);
		arg->chain[i] >>= distance;
		arg->chain[i] += carry;
		carry = tmp;
	}
}

// Shifts left integer number of bytes
void abn_long_shift_left(abn_t* arg, unsigned int distance)
{
	for(int i = arg->volume-1; i>=0; i--)
	{
		arg->chain[i] = (i >= distance ? arg->chain[i-distance] : 0);
	}
}

// Shifts right integer number of bytes
void abn_long_shift_right(abn_t* arg, unsigned int distance)
{
	for(int i = 0; i<arg->volume; i++)
	{
		arg->chain[i] = ((i+distance < arg->volume) ? arg->chain[i+distance] : 0);
	}
}
