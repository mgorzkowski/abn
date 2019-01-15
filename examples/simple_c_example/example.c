//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include <stdio.h>
#include <stdlib.h>
#include "abn.h"
#include "nonportable/fileoperations.h"

void print_abn_number(FILE* file, abn_t* number, char* name)
{
	fprintf(file, "%s = [", name);
	abn_write_to_file(file, number);
	fprintf(file, "]\n");	
}

int main()
{
	int size = 4;
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
	print_abn_number(stdout, a, "a");
	print_abn_number(stdout, b, "b");

	printf("# a = a + b\n");
	abn_sum(a, a, b);
	print_abn_number(stdout, a, "a");

	printf("# b = a + b\n");
	abn_sum(b, a, b);
	print_abn_number(stdout, b, "b");

	printf("# a = 0\n");
	abn_reset(a);
	print_abn_number(stdout, a, "a");

	printf("# a = b\n");
	abn_copy(a, b);
	print_abn_number(stdout, a, "a");

	printf(" # a = a << 8\n");
	abn_shift_left(a, 8);
	print_abn_number(stdout, a, "a");

	printf(" # a = a << 4\n");
	abn_shift_left(a, 4);
	print_abn_number(stdout, a, "a");

	printf(" # a = a >> 12\n");
	abn_shift_right(a, 12);
	print_abn_number(stdout, a, "a");

	printf(" # c = a * b\n");
	abn_mul(c, a, b);
	print_abn_number(stdout, c, "c");

	printf("# a = 0\n");
	abn_reset(a);
	print_abn_number(stdout, a, "a");

	printf("# a--\n");
	abn_dec(a);
	print_abn_number(stdout, a, "a");

	printf("# a is negative\n");
	if(abn_is_negative(a))
		printf("true\n");
	else
		printf("false\n");

	printf("# a = -a\n");
	abn_neg(a);
	print_abn_number(stdout, a, "a");

	printf("# a is negative\n");
	if(abn_is_negative(a))
		printf("true\n");
	else
		printf("false\n");

	printf("# a--\n");
	abn_dec(a);
	print_abn_number(stdout, a, "a");

	printf("# a is negative\n");
	if(abn_is_negative(a))
		printf("true\n");
	else
		printf("false\n");

	printf("# a = a or b\n");
	abn_or(a, a, b);
	print_abn_number(stdout, a, "a");

	printf("# a = a and b<<1\n");
	abn_shift_left(b, 1);
	abn_and(a, a, b);
	print_abn_number(stdout, a, "a");

	printf("# a = -a");
	abn_neg(a);
	print_abn_number(stdout, a, "\na");
	print_abn_number(stdout, b, "b");

	printf("# c = a * b\n");
	abn_mul(c, a, b);
	print_abn_number(stdout, c, "c");

	printf("# c = a (signed)* b\n");
	abn_smul(c, a, b);
	print_abn_number(stdout, c, "c");

	printf("# c = -c\n");
	abn_neg(c);
	print_abn_number(stdout, c, "c");

	printf("# c = ror(c, 8)\n");
	abn_rotate_right(c, 8);
	print_abn_number(stdout, c, "c");

	printf("# c = ror(c, 1)\n");
	abn_rotate_right(c, 1);
	print_abn_number(stdout, c, "c");

	printf("# c = rol(c, 8)\n");
	abn_rotate_left(c, 8);
	print_abn_number(stdout, c, "c");

	printf("# c = rol(c, 1)\n");
	abn_rotate_left(c, 1);
	print_abn_number(stdout, c, "c");

	byte bt;

	printf("# c[byte:3]\n");
	bt = abn_get_byte(c, 3);
	printf("c[byte:3] = %x\n", bt);

	printf("# c[byte:4]\n");
	bt = abn_get_byte(c, 4);
	printf("c[byte:4] = %x\n", bt);

	printf("# c[byte:5]\n");
	bt = abn_get_byte(c, 5);
	printf("c[byte:5] = %x\n", bt);

	bt = 0x4A;
	printf("# c[byte:3] = 0x%x\n", bt);
	abn_set_byte(c, bt, 3);
	print_abn_number(stdout, c, "c");

	bt = 0x8F;
	printf("# c[byte:4] = 0x%x\n", bt);
	abn_set_byte(c, bt, 4);
	print_abn_number(stdout, c, "c");

	bt = 0x81;
	printf("# c[byte:5] = 0x%x\n", bt);
	abn_set_byte(c, bt, 5);
	print_abn_number(stdout, c, "c");

	abn_reset(a);
	abn_dec(a);
	abn_reset(b);
	abn_dec(b);
	abn_reset(c);
	print_abn_number(stdout, a, "a");
	print_abn_number(stdout, b, "b");
	abn_sum(c, b, a);
	print_abn_number(stdout, c, "c");

	abn_free(a);
	abn_free(b);
	abn_free(c);
}
