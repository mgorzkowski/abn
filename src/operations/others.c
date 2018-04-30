#include "../../include/abn.h"

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
