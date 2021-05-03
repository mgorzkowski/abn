//
// Copyright (c) 2018-2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"

// private functions prototypes
static void abn_simple_add(abn_t* op1, abn_t* op2);
static void abn_simple_sub(abn_t* op1, abn_t* op2);
static void abn_simple_add_abn_unit(abn_t* op1, abn_unit value);
static void abn_simple_sub_abn_unit(abn_t* arg, abn_unit value);

// Public functions

// Adds op2 to op1 (op1 as a result)
void abn_add(abn_t* op1, abn_t* op2)
{
	if (NULL == op1->chain || NULL == op2->chain || op1->volume < op2->volume)
	{
		abn_free(op1);
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

// Subtraction an abn_unit
void abn_subu(abn_t* arg, abn_unit value)
{
	abn_simple_sub_abn_unit(arg, value);
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

// It was assumed that volume of op1 is grater or equal to volume of op2
static void abn_simple_add(abn_t* op1, abn_t* op2)
{
	abn_unit carry = 0;
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
	abn_unit carry = 0;
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
	abn_unit carry = (op1->chain[0] < value) ? 1 : 0;
	for(int i = 1; 1 == carry && i < op1->volume; i++)
	{
		op1->chain[i] += carry;
		carry = (0 == op1->chain[i]) ? 1 : 0;
	}
}

static void abn_simple_sub_abn_unit(abn_t* arg, abn_unit value)
{
	abn_unit carry = (arg->chain[0] < value) ? 1 : 0;
	arg->chain[0] -= value;
	for(int i = 1; 1 == carry && i < arg->volume; i++)
	{
		arg->chain[i] -= carry;
		carry = (ABN_UNIT_MAX == arg->chain[i]) ? 1 : 0;
	}
}
