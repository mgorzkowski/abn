#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
CFLAGS=-Wall -g
ABN_LIB_DIR= -L../../bin/static/
ABN_INCLUDE_DIR= -I../../include
LIBS= -labn

.PHONEY: all
all: ./bin/example
	@echo 'Build done'

.PHONEY: run
run: ./bin/example
	./bin/example ./number.bin

./bin/example: ./example.c
	@mkdir -p bin/
	$(CC) $(CFLAGS) $? $(ABN_INCLUDE_DIR) $(ABN_LIB_DIR) $(LIBS) -o $@

.PHONEY: clean
clean:
	@rm -rf ./bin
	@echo 'Clean done'
