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

// Multiplication of two unsigned numbers
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

// Multiplication of two signed numbers
void abn_smul(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume * 2 != result->volume)
	{
		abn_free(result);
	}
	else
	{
		bool sign1 = abn_is_positive(op1);
		bool sign2 = abn_is_positive(op2);
		if(!sign1)
		{
			abn_neg(op1);
		}
		if(!sign2)
		{
			abn_neg(op2);
		}
		abn_mul(result, op1, op2);
		if((sign1 && !sign2) || (!sign1 && sign2))
		{
			abn_neg(result);
		}
		if(!sign1)
		{
			abn_neg(op1);
		}
		if(!sign2)
		{
			abn_neg(op2);
		}
	}
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

void abn_absolute_value(abn_t* arg)
{
	if(abn_is_negative(arg))
	{
		abn_neg(arg);
	}
}
