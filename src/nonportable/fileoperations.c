//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"
#include <stdlib.h>
#include <stdio.h>

// Public functions

// Writes abn_t number to the file (hexadecimal format)
void abn_write_to_file(FILE* file, abn_t* number)
{
	char* representation = abn_to_string(number);
	fprintf(file, "%s", representation);
	fflush(file);
	free(representation);
}

// Reads abn_t number from the file (hexadecimal format)
abn_unit abn_read_from_file(FILE* file, abn_t* number)
{
	return -1;
	// TODO: implement this function
}
