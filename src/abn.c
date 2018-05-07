//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../include/abn.h"

const abn_unit ABN_UNIT_MAX = ((abn_unit)0) - 1;

// Creates abn_t
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

// Creates abn_t based on antoher abn_t
abn_t* abn_create_copy(abn_t* arg)
{
	abn_t* result = abn_create(arg->volume);
	abn_copy(result, arg);
	return result;
}

// Creates an empty abn_t number
abn_t* abn_create_empty()
{
	abn_t* result = (abn_t*)malloc(sizeof(abn_t));
	result->chain = NULL;
	result->volume = 0;
	return result;
}

// Terminates the abn_t number
void abn_free(abn_t* arg)
{
	if(arg->chain != NULL)
	{
		free(arg->chain);
	}
	free(arg);
}

// Return true if the abn_t number is empty
bool abn_is_empty(abn_t* arg)
{
	if(arg->chain == NULL && arg->volume == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Return true if abn_t numbers are equal
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

// Resets the abn_t number
void abn_reset(abn_t* arg)
{
	for(int i=0; i<arg->volume; i++)
	{
		arg->chain[i] = 0;
	}
}

// Creates a deep copy of abn_t number
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
