#include "../../include/abn.h"

// It was assumed that volumes of both operands are equal
void abn_simple_add(abn_t* result, abn_t* op1, abn_t* op2)
{
	int carry = 0;
	for(int i = 0; i < op1->volume; i++)
	{
		abn_unit tmp = op1->chain[i];
		result->chain[i] = op1->chain[i] + op2->chain[i] + carry;
		carry = (result->chain[i] < tmp) ? 1 : 0;
	}
}

// Addition
void abn_add(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || result->volume < op1->volume)
	{
		abn_free(result);
	}
	else
	{
		abn_simple_add(result, op1, op2);
	}
}

// Incrementation
void abn_inc(abn_t* arg)
{
	for(int i = 0; i<arg->volume; i++)
	{
		if(arg->chain[i] != ABN_UNIT_MAX)
		{
			arg->chain[i]++;
			break;
		}
		arg->chain[i] = 0;
	}
}

// Decrementation
void abn_dec(abn_t* arg)
{
	for(int i = 0; i<arg->volume; i++)
	{
		if(arg->chain[i] != 0)
		{
			arg->chain[i]--;
			break;
		}
		arg->chain[i] = ABN_UNIT_MAX;
	}
}

// Addition inverse
void abn_neg(abn_t* arg)
{
	abn_not(arg);
	abn_inc(arg);
}

bool abn_is_positive(abn_t* arg)
{
	if( arg->chain[arg->volume-1] > ( ((abn_unit)1) << ( (8*sizeof(abn_unit)) - 1 ) ) )
	{
		return false;
	}
	return true;
}

bool abn_is_negative(abn_t* arg)
{
	if(abn_is_positive(arg))
	{
		return false;
	}
	return true;
}

bool abn_absolute_value(abn_t* arg)
{
	if(abn_is_negative(arg))
	{
		abn_neg(arg);
		return true;
	}
	return false;
}
