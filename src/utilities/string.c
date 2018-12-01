//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../../include/abn.h"
#include <stdlib.h>
#include <string.h>

// Functions prototypes
static char hex_sign_to_char(byte arg);
static char* byte_to_string(byte arg);

// Public functions

// Returns string with abn_t in hexadecimal form
char* abn_unit_to_string(abn_unit arg)
{
	char* result = (char*)malloc(2 * sizeof(abn_unit) + 1);
	result[0] = '\0';
	abn_unit* unit_ptr = &arg;
	byte* byte_ptr = (byte*)unit_ptr;

	for(unsigned int i = 0; i < sizeof(abn_unit); i++)
	{
		char* tmp = byte_to_string(byte_ptr[sizeof(abn_unit) - 1 - i]);
		strcat(result, tmp);
		free(tmp);
	}
	return result;
}

// Returns string with abn_unit in hexadecimal form
char* abn_to_string(abn_t* arg)
{
	char* result = (char*)malloc(2 * arg->volume * sizeof(abn_unit) + 1);
	result[0] = '\0';

	for(unsigned int i = 0; i < arg->volume; i++)
	{
		char* tmp = abn_unit_to_string(arg->chain[arg->volume - 1 - i]);
		strcat(result, tmp);
		free(tmp);
	}
	return result;
}

// Private functions

// Returns char '0'-'F' for a nibble
static char hex_sign_to_char(byte arg)
{
	return arg<10?arg+'0':arg+'A'-10;
}

// Returns string in hexadecimal form for the byte
static char* byte_to_string(byte arg)
{
	char* result = (char*)malloc(3 * sizeof(char));
	if(result != NULL)
	{
		result[0] = hex_sign_to_char((arg & 0xF0)>>4);
		result[1] = hex_sign_to_char(arg & 0x0F);
		result[2] = '\0';
	}
	return result;
}
