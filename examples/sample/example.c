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

void print_abn(abn_t* number)
{
	abn_write_to_file(stdout, number);
	fprintf(stdout, "\n");	
}

void example_func(abn_t* number)
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
	const int Volume = 2;
	if(argc != 2)
	{
		return -1;
	}
	FILE* number_file = fopen(argv[1], "r+b");
	abn_t* number = abn_create(Volume);
	abn_read_from_file(number_file, number, Volume*ABN_UNIT_SIZE);
	print_abn(number);
	abn_t * number2 = abn_create_from_string("FEDCBA9876543210", 16);
	print_abn(number2);
	abn_add(number, number2);
	print_abn(number);
	example_func(number);
}