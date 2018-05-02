#include "../include/abn.h"

const abn_unit ABN_UNIT_MAX = ((abn_unit)0) - 1;

abn_t* abn_create(unsigned int volume)
{
	abn_t* result = (abn_t*)malloc(sizeof(abn_t));
	result->volume = 0;
	result->chain = (abn_unit*)malloc(volume * sizeof(abn_unit));
	if(result->chain != NULL)
	{
		result->volume = volume;
	}
	return result;
}

abn_t* abn_create_with_zeros(unsigned int volume)
{
	abn_t* result = (abn_t*)malloc(sizeof(abn_t));
	result->volume = 0;
	result->chain = (abn_unit*)calloc(volume, sizeof(abn_unit));
	if(result->chain != NULL)
	{
		result->volume = volume;
	}
	return result;
}

// It's not safe. You should be completly certain that the chain contains appropriate amount of abn_units.
abn_t* abn_create_with_chain(abn_unit* chain, unsigned int volume)
{
	abn_t* result = (abn_t*)malloc(sizeof(abn_t));
	result->chain = chain;
	result->volume = volume;
	return result;
}

abn_t* abn_create_empty()
{
	abn_t* result = (abn_t*)malloc(sizeof(abn_t));
	result->chain = NULL;
	result->volume = 0;
	return result;
}

void abn_free(abn_t* number)
{
	if(number->chain != NULL)
	{
		free(number->chain);
	}
	free(number);
}

bool abn_is_empty(abn_t* op)
{
	if(op->chain == NULL && op->volume == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool abn_are_equal(abn_t* op1, abn_t* op2)
{
	if(op1->volume != op2->volume)
	{
		return false;
	}
	for(int i=0; i<op1->volume; i++)
	{
		if(op1->chain[i] != op2->chain[i])
		{
			return false;
		}
	}
	return true;
}

void abn_reset(abn_t* op)
{
	for(int i=0; i<op->volume; i++)
	{
		op->chain[i] = 0;
	}
}

// It creates a deep copy
void abn_copy(abn_t* destination, abn_t* source)
{
	if(destination->volume != source->volume)
	{
		abn_free(destination);
		destination = abn_create(source->volume);
	}
	for(int i=0; i<source->volume; i++)
	{
		destination->chain[i] = source->chain[i];
	}
}
