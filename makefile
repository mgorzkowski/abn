#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
AR=ar
CFLAGS=-c -Wall -std=c99
BINDIR=./bin
OBJS= \
$(BINDIR)/abn.o \
$(BINDIR)/additive.o \
$(BINDIR)/multiplicative.o \
$(BINDIR)/bit.o \
$(BINDIR)/shift.o \
$(BINDIR)/string.o

all: create-bindir $(BINDIR)/libabn.a
	rm $(OBJS)

clean:
	rm -rf $(BINDIR)

clean-all: clean-examples
	rm -rf $(BINDIR)
	rm include/*.h.gch

$(BINDIR)/libabn.a: $(OBJS)
	$(AR) rcsv $@ $?

$(BINDIR)/abn.o: ./src/abn.c
	$(CC) $(CFLAGS) $? -o $@

$(BINDIR)/additive.o: ./src/operations/additive.c
	$(CC) $(CFLAGS) $? -o $@

$(BINDIR)/multiplicative.o: ./src/operations/multiplicative.c
	$(CC) $(CFLAGS) $? -o $@

$(BINDIR)/bit.o: ./src/operations/bit.c
	$(CC) $(CFLAGS) $? -o $@

$(BINDIR)/shift.o: ./src/operations/shift.c
	$(CC) $(CFLAGS) $? -o $@

$(BINDIR)/string.o: ./src/utilities/string.c
	$(CC) $(CFLAGS) $? -o $@

create-bindir:
	mkdir -p $(BINDIR)

clean-examples:
	rm -rf examples/*/bin
