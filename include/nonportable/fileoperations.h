//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

// THIS FILE CONSTIANS NON FULLY PORTABLE CODE
// You may have problems with using this header file on every platform.

#ifndef ABN_MISC_H
#define ABN_MISC_H

#include "../abn.h"
#include <stdio.h>

void abn_write_to_file(FILE* file, abn_t* number);
abn_unit abn_read_from_file(FILE* file, abn_t* number);

#endif /* ABN_MISC_H */
