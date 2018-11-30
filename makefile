#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
AR=ar
CFLAGS=-c -Wall -std=c99

bindir=./bin
src=\
	$(wildcard src/*.c) \
	$(wildcard src/operations/*.c) \
	$(wildcard src/utilities/*.c)
objs=$(src:.c=.o)

.PHOENY: all
all: create-bindir $(bindir)/libabn.a
	rm $(objs)
	@echo 'Build done'

.PHONEY: clean
clean:
	rm -rf $(objs)
	rm -rf $(bindir)
	@echo 'Clean done'

$(bindir)/libabn.a: $(objs)
	$(AR) rcsv $@ $?

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONEY: create-bindir
create-bindir:
	mkdir -p $(bindir)

.PHONEY: clean-examples
clean-examples:
	make clean -C examples/*
