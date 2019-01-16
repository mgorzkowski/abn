//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"

// Functions prototypes
static void abn_simple_sum(abn_t* result, abn_t* op1, abn_t* op2);
static void abn_simple_add(abn_t* op1, abn_t* op2);

// Public functions

// Adds second operand to first operand
void abn_add(abn_t* op1, abn_t* op2)
{
	if(op1->volume < op2->volume)
	{
		abn_free(op1);
	}
	else
	{
		abn_simple_add(op1, op2);
	}
	return;
}

// Sums two abn_t numbers and writes result
void abn_sum(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || result->volume < op1->volume)
	{
		abn_free(result);
	}
	else
	{
		if(result != op1 && result != op2)
		{
			abn_reset(result);
			abn_simple_sum(result, op1, op2);
		}
		else
		{
			(result == op1) ? abn_add(result, op2) : abn_add(result, op1);
		}
	}
}

// Increments the abn_t number
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

// Decrements the abn_t number
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

// Returns addition inverse of abn_t number
void abn_neg(abn_t* arg)
{
	abn_not(arg);
	abn_inc(arg);
}

// przesunąć do abn.c
// Returns true if anb_t is positive number
bool abn_is_positive(abn_t* arg)
{
	// nieczytelny warunek
	//if( arg->chain[arg->volume-1] > ( ((abn_unit)1) << ( (8*sizeof(abn_unit)) - 1 ) ) )
	if((arg->chain[arg->volume-1] & ((abn_unit)1<<(8*sizeof(abn_unit)-1))) > 0)
	{
		return false;
	}
	return true;
}

// przesunąć do abn.c
// Returns true if anb_t is negative number
bool abn_is_negative(abn_t* arg)
{
	if(abn_is_positive(arg))
	{
		return false;
	}
	return true;
}

// Turns the abn_t number to it's absolute value and return true if the number was negative before
bool abn_abs(abn_t* arg)
{
	if(abn_is_negative(arg))
	{
		abn_neg(arg);
		return true;
	}
	return false;
}

// Private functions

// It was assumed that volumes of both operands are equal and result is not equal to any operands
static void abn_simple_sum(abn_t* result, abn_t* op1, abn_t* op2)
{
	int carry = 0;
	for(int i = 0; i < op1->volume; i++)
	{
		result->chain[i] = op1->chain[i] + op2->chain[i] + carry;
		carry = ( (0 == carry && (result->chain[i] < op1->chain[i] || result->chain[i] < op2->chain[i]))
			|| (1 == carry && (result->chain[i] <= op1->chain[i] || result->chain[i] <= op2->chain[i])) ) ? 1 : 0;
	}
	if(1 == carry && result->volume > op1->volume)
	{
		result->chain[op1->volume] = 1;
	}
}

// It was asssumded that volume of op1 is grater or equal to volume of op2
static void abn_simple_add(abn_t* op1, abn_t* op2)
{
	int carry = 0;
	for(int i = 0; i < op2->volume; i++)
	{
		op1->chain[i] += op2->chain[i] + carry;
		carry = ((0 == carry && op1->chain[i] < op2->chain[i]) || (1 == carry && op1->chain[i] <= op2->chain[i])) ? 1 : 0;
	}
	for(int i = op2->volume; i < op1->volume; i++)
	{
		op1->chain[i] += carry;
		carry = (0 == op1->chain[i] && 1 == carry) ? 1 : 0;
	}
}
