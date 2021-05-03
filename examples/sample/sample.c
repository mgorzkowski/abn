//
// Copyright (c) 2018-2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include <stdio.h>
#include <stdlib.h>

#include "abn.h"
#include "extra/fileoperations.h"

static void print_abn(abn_t* number)
{
	abn_write_to_file(stdout, number);
	fprintf(stdout, "\n");
}

static void example_func(abn_t* number)
{
	abn_reset(number);
	print_abn(number);
	abn_inc(number);
	print_abn(number);
	abn_set_byte(number, 0xFF, 0);
	print_abn(number);
	abn_inc(number);
	print_abn(number);
}

int main(int argc, char** argv)
{
	abn_t* number = abn_create_from_string("FEDCBA9876543210");
	print_abn(number);
	printf("----------------\n");
	example_func(number);
	return 0;
}