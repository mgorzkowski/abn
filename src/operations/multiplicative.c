//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"

// Private functions prototypes
void abn_unit_mul(abn_t* result, abn_unit op1, abn_unit op2);
void abn_simple_mul_algorithm(abn_t* result, abn_t* op1, abn_t* op2);

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

// Private functions

// Multiplies two anb_units and build anb_t type result
// It was assumed that volumes of both operands are equal to the volume of the result divided by 2.
void abn_unit_mul(abn_t* result, abn_unit op1, abn_unit op2)
{
	static abn_t* tmp = NULL;
	static abn_t* tmp2 = NULL;
	if(tmp == NULL || tmp2 == NULL)
	{
		tmp = abn_create(2);
		tmp2 = abn_create(2);
	}
	abn_reset(tmp);

	abn_halfunit op1l = op1;
	abn_halfunit op1h = ((abn_halfunit*)&op1)[1];
	abn_halfunit op2l = op2;
	abn_halfunit op2h = ((abn_halfunit*)&op2)[1];

	tmp2->chain[0] = (abn_unit)op1l * (abn_unit)op2l;
	tmp2->chain[1] = 0;
	abn_add(tmp, tmp, tmp2);

	tmp2->chain[0] = (abn_unit)op1h * (abn_unit)op2l;
	tmp2->chain[1] = 0;
	abn_shift_left(tmp2,  8*sizeof(abn_halfunit));
	abn_add(tmp, tmp, tmp2);

	tmp2->chain[0] = (abn_unit)op1l * (abn_unit)op2h;
	tmp2->chain[1] = 0;
	abn_shift_left(tmp2, 8*sizeof(abn_halfunit));
	abn_add(tmp, tmp, tmp2);

	tmp2->chain[0] = (abn_unit)op1h * (abn_unit)op2h;
	tmp2->chain[1] = 0;
	abn_shift_left(tmp2, 8*sizeof(abn_unit));
	abn_add(result, tmp, tmp2);
}

// Simple multiplication algorithm
// It was assumed that volumes of both operands are equal to the volume of the result divided by 2.
void abn_simple_mul_algorithm(abn_t* result, abn_t* op1, abn_t* op2)
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
	for (int i = 0; i < op1->volume; i++)
	{
		for (int j = 0; j < op1->volume; j++)
		{
			abn_reset(tmp);
			abn_unit_mul(tmp, op1->chain[i], op2->chain[j]);
			abn_shift_left(tmp, (i + j) * 8 * sizeof(abn_unit));
			abn_add(result, result, tmp);
		}
	}
}
