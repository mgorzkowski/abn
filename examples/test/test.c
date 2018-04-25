#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "abn.h"

// Unit tests
void run_tests();

bool add_test();
bool mul_test();

void abn_print_var(abn_t op, char* name);

int main (int argc, char *argv[])
{
	run_tests();

	return 0;
}

void run_tests()
{
	printf("Testing example:\n");
	int error_counter = 0;
	if(!add_test()) error_counter++;
	if(!mul_test()) error_counter++;

	printf("\nEnd of tests:\n%d errors\n", error_counter);
}

bool add_test()
{
	printf("add_test()\t\t");
	bool test_result = true;

	abn_t* a = abn_create(4);
	abn_t* b = abn_create(4);
	abn_t* e = abn_create(4);
	abn_t* c = abn_create(4);

	srand(time(NULL));

	int tests = 100;
	while(tests--)
	{
		abn_unit carry = 0;
		for(int i=0; i<4; i++)
		{
			a->chain[i] = rand();
			b->chain[i] = rand();
			e->chain[i] = a->chain[i] + b->chain[i] + carry;
			carry = (e->chain[i] < a->chain[i]) ? 1 : 0;
		}

		abn_add(c, a, b);

		if(!abn_are_equal(c, e))
		{
			test_result = false;
			break;
		}
	}

	if(test_result)
	{
		printf("OK!\n");
	}
	else
	{
		printf("Failed!\n");
	}

	abn_free(a);
	abn_free(b);
	abn_free(e);
	abn_free(c);

	return test_result;
}

bool mul_test()
{
	printf("mul_test()\t\t");
	bool test_result = true;

	abn_t* a = abn_create(8);
	abn_t* b = abn_create(8);
	abn_t* e = abn_create(16);
	abn_t* c = abn_create(16);
	abn_t* tmp = abn_create(16);

	srand(0);

	int tests = 1;
	while(tests--)
	{
		for(int i=0; i<8; i++)
		{
			a->chain[i] = rand();
			b->chain[i] = rand();
		}
		abn_reset(e);
		for(int i=0; i<8; i++)
		{
			for (int j = 0; j<8; j++)
			{
				abn_reset(tmp);
				abn_unit_mul(tmp, a->chain[i], b->chain[j]);
				abn_shift_left(tmp, 8 * sizeof(abn_unit) * (i+j));
				abn_add(e, e, tmp);
			}
		}
		abn_mul(c, a, b);

		if(!abn_are_equal(c, e))
		{
			test_result = false;
			break;
		}
	}

	if(test_result)
	{
		printf("OK!\n");
	}
	else
	{
		printf("Failed!\n");
	}

	abn_free(a);
	abn_free(b);
	abn_free(e);
	abn_free(c);

	return test_result;
}
