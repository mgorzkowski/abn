#include "../../lib/operations/shifts.h"

void abn_short_shift_left(abn_t* op, unsigned int distance)
{
	abn_unit carry = 0;
	for(int i=0; i<op->volume; i++)
	{
		abn_unit tmp = op->chain[i] >> (8*sizeof(abn_unit) - distance);
		op->chain[i] <<= distance;
		op->chain[i] += carry;
		carry = tmp;
	}
}

void abn_short_shift_right(abn_t* op, unsigned int distance)
{
	abn_unit carry = 0;
	for(int i=op->volume-1; i>=0; i--)
	{
		abn_unit tmp = op->chain[i] << (8*sizeof(abn_unit) - distance);
		op->chain[i] >>= distance;
		op->chain[i] += carry;
		carry = tmp;
	}
}

void abn_long_shift_left(abn_t* op, unsigned int distance)
{
	for(int i = op->volume-1; i>=0; i--)
	{
		op->chain[i] = (i >= distance ? op->chain[i-distance] : 0);
	}
}

void abn_long_shift_right(abn_t* op, unsigned int distance)
{
	for(int i = 0; i<op->volume; i++)
	{
		op->chain[i] = ((i+distance < op->volume) ? op->chain[i+distance] : 0);
	}
}

void abn_shift_left(abn_t* op, unsigned int distance)
{
	int long_distance = distance / (8*sizeof(abn_unit));
	int short_distance = distance % (8*sizeof(abn_unit));

	if(long_distance != 0)
	{
		abn_long_shift_left(op, long_distance);
	}
	if(short_distance != 0)
	{
		abn_short_shift_left(op, short_distance);
	}
}

void abn_shift_right(abn_t* op, unsigned int distance)
{
	int long_distance = distance / (8*sizeof(abn_unit));
	int short_distance = distance % (8*sizeof(abn_unit));

	if(long_distance != 0)
	{
		abn_long_shift_right(op, long_distance);
	}
	if(short_distance != 0)
	{
		abn_short_shift_right(op, short_distance);
	}
}
