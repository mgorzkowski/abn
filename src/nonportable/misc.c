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

// Writes abn_t to the file (format: 'name = [0xnumber]\n')
void abn_print(FILE* file, abn_t* number, char* name)
{
	char* representation = abn_to_string(number);
	fprintf(file, "%s = [ 0x%s ]\n", name, representation);
	fflush(file);
	free(representation);
}
