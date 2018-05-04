#include "../../include/abn.h"

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

void abn_long_shift_left(abn_t* arg, unsigned int distance)
{
	for(int i = arg->volume-1; i>=0; i--)
	{
		arg->chain[i] = (i >= distance ? arg->chain[i-distance] : 0);
	}
}

void abn_long_shift_right(abn_t* arg, unsigned int distance)
{
	for(int i = 0; i<arg->volume; i++)
	{
		arg->chain[i] = ((i+distance < arg->volume) ? arg->chain[i+distance] : 0);
	}
}

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
