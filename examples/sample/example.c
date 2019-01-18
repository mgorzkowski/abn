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

void example_func(void)
{
	abn_t* number = abn_create(4);
	abn_reset(number);
	print_abn(number);
	abn_inc(number);
	print_abn(number);
	abn_set_byte(number, 0xFF, 0);
	print_abn(number);
	abn_inc(number);
	print_abn(number);
}

int main(void)
{
	example_func();	
}