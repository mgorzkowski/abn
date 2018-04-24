#include "./../../lib/operations/others.h"

void abn_reset(abn_t op)
{
	for(int i=0; i<op.volume; i++)
	{
		op.chain[i] = 0;
	}
}
