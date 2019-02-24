//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"
#include <stdlib.h>

// Functions prototypes
static void abn_unit_mul(abn_t* result, abn_unit op1, abn_unit op2);
static void abn_simple_mul_algorithm(abn_t* result, abn_t* op1, abn_t* op2);
static void abn_mul_by_unit(abn_t* result, abn_t* op, abn_unit value);

// Public functions

// Multiplies two unsigned numbers
void abn_mul(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume * 2 != result->volume)
	{
		abn_free(result);
	}
	else
	{
		abn_simple_mul_algorithm(result, op1, op2);
	}
}

// Multiplies two signed numbers
// TODO: function shouldn't modify operands
void abn_smul(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume * 2 != result->volume)
	{
		abn_free(result);
	}
	else
	{
		bool operands_are_the_same = false;
		if(op1 == op2)
		{
			op2 = abn_create_copy(op1);
			operands_are_the_same = true;
		}
		bool sign1 = abn_abs(op1);
		bool sign2 = abn_abs(op2);

		abn_mul(result, op1, op2);
		if((sign1 && !sign2) || (!sign1 && sign2))
		{
			abn_neg(result);
		}
		if(sign1)
		{
			abn_neg(op1);
		}
		if(operands_are_the_same)
		{
			abn_free(op2);
		}
		else
		{
			if(sign2)
			{
				abn_neg(op2);
			}
		}
	}
}

void abn_mulu(abn_t* result, abn_t* op, abn_unit value)
{
	if(result->volume < op->volume)
	{
		abn_free(result);
	}
	else
	{
		abn_mul_by_unit(result, op, value);
	}
}

// Private functions

// Multiplies two anb_units and build abn_t type result
// It was assumed that volumes of both operands are equal to the volume of the result divided by 2.
static void abn_unit_mul(abn_t* result, abn_unit op1, abn_unit op2)
{
	static abn_t* tmp = NULL;
	if(tmp == NULL)
	{
		tmp = abn_create(2);
	}
	abn_reset(result);

	abn_halfunit op1l = op1;
	abn_halfunit op1h = ((abn_halfunit*)&op1)[1];
	abn_halfunit op2l = op2;
	abn_halfunit op2h = ((abn_halfunit*)&op2)[1];

	tmp->chain[0] = (abn_unit)op1l * (abn_unit)op2l;
	tmp->chain[1] = 0;
	abn_add(result, tmp);

	tmp->chain[0] = (abn_unit)op1h * (abn_unit)op2l;
	tmp->chain[1] = 0;
	abn_shift_left(tmp, 8*sizeof(abn_halfunit));
	abn_add(result, tmp);

	tmp->chain[0] = (abn_unit)op1l * (abn_unit)op2h;
	tmp->chain[1] = 0;
	abn_shift_left(tmp, 8*sizeof(abn_halfunit));
	abn_add(result, tmp);

	tmp->chain[0] = (abn_unit)op1h * (abn_unit)op2h;
	tmp->chain[1] = 0;
	abn_shift_left(tmp, 8*sizeof(abn_unit));
	abn_add(result, tmp);
}

// Simple multiplication algorithm
// It was assumed that volumes of both operands are equal to the volume of the result divided by 2.
static void abn_simple_mul_algorithm(abn_t* result, abn_t* op1, abn_t* op2)
{
	static abn_t* tmp = NULL;
	if(tmp == NULL)
	{
		tmp = abn_create(result->volume);
	}
	else
	{
		if(tmp->volume < result->volume)
		{
			abn_free(tmp);
			tmp = abn_create(result->volume);
		}
	}
	abn_reset(result);
	for (unsigned int i = 0; i < op1->volume; i++)
	{
		for (unsigned int j = 0; j < op1->volume; j++)
		{
			abn_reset(tmp);
			abn_unit_mul(tmp, op1->chain[i], op2->chain[j]);
			abn_shift_left(tmp, (i + j) * 8 * sizeof(abn_unit));
			abn_add(result, tmp);
		}
	}
}

// Multiplies abn_t by abn_unit
// It was assumed that volumes of both operands are equal to the volume of the result divided by 2. 
static void abn_mul_by_unit(abn_t* result, abn_t* op, abn_unit value)
{
	abn_unit carry = 0;
	static abn_t* tmp = NULL;
	if (NULL == tmp)
	{
		tmp = abn_create(2);
	}
	abn_reset(tmp);
	for (int i=0; i<op->volume; i++)
	{
		abn_unit_mul(tmp, op->chain[i], value);
		abn_adu(tmp, carry);
		carry = tmp->chain[1];
		result->chain[i] = tmp->chain[0];
	}
}
