//
// Copyright (c) 2018-2021 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

//
// THIS FILE CONTAINS FUNCTIONS THAT MAY REQUIRE ADDITIONAL PORTING CODE.
// FOR MORE INFORMATION LOOK AT src/extra/README.md
//

#ifndef ABN_EXTRA_FILEOPERATIONS_H
#define ABN_EXTRA_FILEOPERATIONS_H

#include "../abn.h"
#include <stdio.h>

void abn_write_to_file(FILE *file, abn_t *number);
void abn_read_from_file(FILE *file, abn_t *number, abn_unit bytes);

#endif /* ABN_EXTRA_FILEOPERATIONS_H */
