#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
CFLAGS=-Wall -std=c99
ABN_LIB_DIR=../../bin/
ABN_INCLUDE_DIR=../../include
ABN_LIB_NAME=libabn.a

all: ./bin/example.elf

run: ./bin/example.elf
	./bin/example.elf

clean:
	rm -rf ./bin

./bin/example.elf: ./example.c
	mkdir -p bin/
	$(CC) $(CFLAGS) $? -I$(ABN_INCLUDE_DIR) -L$(ABN_LIB_DIR) -labn -o $@
