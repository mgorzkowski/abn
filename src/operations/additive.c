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
static void abn_simple_sub(abn_t* op1, abn_t* op2);
static void abn_simple_add_abn_unit(abn_t* op1, abn_unit value);

// Public functions

// Adds op2 to op1 (op1 as a result)
void abn_add(abn_t* op1, abn_t* op2)
{
	if(op1->volume < op2->volume)
	{
		// should be complition code!
		abn_free(op1);
		return;
	}
	else
	{
		abn_simple_add(op1, op2);
	}
}

// Adds abn_unit (integer) to abn_t number
void abn_adu(abn_t* op1, abn_unit value)
{
	abn_simple_add_abn_unit(op1, value);
}

// Sums two abn_t numbers and writes to result
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

// Subtraction op1 = op1 - op2
void abn_sub(abn_t* op1, abn_t* op2)
{
	if(op1->volume < op2->volume)
	{
		// require compition code;
		abn_free(op1);
		return;
	}
	else
	{
		abn_simple_sub(op1, op2);
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

// It was assumed that volume of op1 is grater or equal to volume of op2
static void abn_simple_add(abn_t* op1, abn_t* op2)
{
	int carry = 0;
	for(int i = 0; i < op2->volume; i++)
	{
		op1->chain[i] += op2->chain[i] + carry;
		carry = (op1->chain[i] < (op2->chain[i] + carry) || (1 == carry && 0 == (op2->chain[i] + carry))) ? 1 : 0;  
	}
	for(int i = op2->volume; i < op1->volume; i++)
	{
		op1->chain[i] += carry;
		carry = (0 == op1->chain[i] && 1 == carry) ? 1 : 0;
	}
}

// It was assumed that volume of op1 is grater or equal to volume of op2
static void abn_simple_sub(abn_t* op1, abn_t* op2)
{
	int carry = 0;
	for(int i = 0; i < op2->volume; i++)
	{
		abn_unit tmp = op1->chain[i];
		op1->chain[i] -= op2->chain[i] + carry;
		carry = ((0 == tmp && 1 == carry) || tmp - carry < op2->chain[i]) ? 1 : 0;
	}
	for(int i = op2->volume; i < op1->volume && 1 == carry; i++)
	{
		op1->chain[i] -= carry;
		carry = (ABN_UNIT_MAX == op1->chain[i]) ? 1 : 0;
	}
}

static void abn_simple_add_abn_unit(abn_t* op1, abn_unit value)
{
	
	op1->chain[0] += value;
	int carry = (op1->chain[0] < value) ? 1 : 0;
	for(int i = 1; 1 == carry && i < op1->volume; i++)
	{
		op1->chain[i] += carry;
		carry = (0 == op1->chain[i]) ? 1 : 0;
	}
}
