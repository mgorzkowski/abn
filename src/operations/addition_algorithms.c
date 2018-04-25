#include "../../lib/operations/addition_algorithms.h"

void abn_simple_add(abn_t result, abn_t op1, abn_t op2)
{
	int carry = 0;
	for(int i = 0; i < op1.volume; i++)
	{
		abn_unit tmp = op1.chain[i];
		result.chain[i] = op1.chain[i] + op2.chain[i] + carry;
		carry = (result.chain[i] < tmp) ? 1 : 0;
	}
}

void abn_add(abn_t result, abn_t op1, abn_t op2)
{
	if(op1.volume != op2.volume)
	{
		abn_reset(result);
	}
	else
	{
		abn_simple_add(result, op1, op2);
	}
}
