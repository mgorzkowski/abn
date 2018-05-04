#include "../../include/abn.h"

void abn_not(abn_t* arg)
{
	for(int i = 0; i<arg->volume; i++)
	{
		arg->chain[i] = ~arg->chain[i];
	}
}

void abn_and(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume != result->volume)
	{
		abn_free(result);
	}
	else
	{
  	for(int i=0; i<op1->volume; i++)
    {
      result->chain[i] = op1->chain[i] & op2->chain[i];
    }
	}
}

void abn_or(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume != result->volume)
	{
		abn_free(result);
	}
	else
	{
  	for(int i=0; i<op1->volume; i++)
    {
      result->chain[i] = op1->chain[i] | op2->chain[i];
    }
	}
}

void abn_xor(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume != result->volume)
	{
		abn_free(result);
	}
	else
	{
  	for(int i=0; i<op1->volume; i++)
    {
      result->chain[i] = op1->chain[i] ^ op2->chain[i];
    }
	}
}

void abn_nand(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume != result->volume)
	{
		abn_free(result);
	}
	else
	{
  	for(int i=0; i<op1->volume; i++)
    {
      result->chain[i] = ~(op1->chain[i] & op2->chain[i]);
    }
	}
}

void abn_nor(abn_t* result, abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume || op1->volume != result->volume)
	{
		abn_free(result);
	}
	else
	{
  	for(int i=0; i<op1->volume; i++)
    {
      result->chain[i] = ~(op1->chain[i] | op2->chain[i]);
    }
	}
}
