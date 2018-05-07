//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include <stdio.h>
#include <stdlib.h>
#include "abn.h"

void print_abn(abn_t op, char* name)
{
	char* representation = abn_to_string(&op);
	printf("%s = [ 0x%s ]\n", name, representation);
	fflush(stdout);
	free(representation);
}

int main()
{
	int size = 16;
	srand(0);
	abn_t* a = abn_create(size);
	abn_t* b = abn_create(size);
	abn_t* c = abn_create(2*size);
	for(int i=0; i<size; i++)
	{
		a->chain[i] = rand();
		b->chain[i] = rand();
	}

	printf("# Create variables:\n");
	print_abn(*a, "a");
	print_abn(*b, "b");

	printf("# a = a + b\n");
	abn_add(a, a, b);
	print_abn(*a, "a");

	printf("# b = a + b\n");
	abn_add(b, a, b);
	print_abn(*b, "b");

	printf("# a = 0\n");
	abn_reset(a);
	print_abn(*a, "a");

	printf("# a = b\n");
	abn_copy(a, b);
	print_abn(*a, "a");

	printf(" # a = a << 8\n");
	abn_shift_left(a, 8);
	print_abn(*a, "a");

	printf(" # a = a << 4\n");
	abn_shift_left(a, 4);
	print_abn(*a, "a");

	printf(" # a = a >> 12\n");
	abn_shift_right(a, 12);
	print_abn(*a, "a");

	printf(" # c = a * b\n");
	abn_mul(c, a, b);
	print_abn(*c, "c");

	printf("# a = 0\n");
	abn_reset(a);
	print_abn(*a, "a");

	printf("# a--\n");
	abn_dec(a);
	print_abn(*a, "a");

	printf("# a is negative\n");
	if(abn_is_negative(a))
		printf("true\n");
	else
		printf("false\n");

	printf("# a = -a\n");
	abn_neg(a);
	print_abn(*a, "a");

	printf("# a is negative\n");
	if(abn_is_negative(a))
		printf("true\n");
	else
		printf("false\n");

	printf("# a--\n");
	abn_dec(a);
	print_abn(*a, "a");

	printf("# a is negative\n");
	if(abn_is_negative(a))
		printf("true\n");
	else
		printf("false\n");

	printf("# a = a or b\n");
	abn_or(a, a, b);
	print_abn(*a, "a");

	printf("# a = a and b<<1\n");
	abn_shift_left(b, 1);
	abn_and(a, a, b);
	print_abn(*a, "a");

	printf("# a = -a");
	abn_neg(a);
	print_abn(*a, "\na");
	print_abn(*b, "b");

	printf("# c = a * b\n");
	abn_mul(c, a, b);
	print_abn(*c, "c");

	printf("# c = a (signed)* b\n");
	abn_smul(c, a, b);
	print_abn(*c, "c");

	printf("# c = -c\n");
	abn_neg(c);
	print_abn(*c, "c");

	abn_free(a);
	abn_free(b);
	abn_free(c);
}
