#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC = gcc
CFLAGS = -Wall -shared -fPIC
ABN_LIB_DIR = -L../../bin/shared
ABN_INCLUDE_DIR = -I../../include
LIBS = -labn -llua

.PHONEY: all
all: ./abn2lua.so
	@echo 'Build done'

./abn2lua.so: ./abn2lua.c
	$(CC) $(CFLAGS) $? $(ABN_INCLUDE_DIR) $(ABN_LIB_DIR) $(LIBS) -o $@

.PHONEY: clean
clean:
	@rm -rf ./abn2lua.so
	@echo 'Clean done'
