#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

NAME=libabn
SNAME=$(NAME).a
DNAME=$(NAME).so
CC=gcc
AR=ar
CFLAGS=-c -Wall -g -fPIC
BINDIR=./bin
STATIC_BINDIR=$(BINDIR)/static
SHARED_BINDIR=$(BINDIR)/shared
SRC=\
	$(wildcard src/*.c) \
	$(wildcard src/operations/*.c) \
	$(wildcard src/utilities/*.c) \
	$(wildcard src/nonportable/*.c)
OBJ=$(SRC:.c=.o)

.PHOENY: all shared static clean test

all: $(STATIC_BINDIR)/$(SNAME) $(SHARED_BINDIR)/$(DNAME)
	@rm -rf $(OBJ)
	@echo 'Build done'

static: $(STATIC_BINDIR)/$(SNAME)
	@rm -rf $(OBJ)
	@echo 'Build done'

shared: $(SHARED_BINDIR)/$(DNAME)
	@rm -rf $(OBJ)
	@echo 'Build done'

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BINDIR)
	@rm -rf ./wrappers/python/*.pyc
	@rm -rf ./tests/*/*.pyc
	@rm -rf ./tests/*.pyc

	@echo 'Clean done'

test: $(SHARED_BINDIR)/$(DNAME)
	@rm -rf $(OBJ)
	chmod +x ./tests/run.py
	cd ./tests && ./run.py -vv

$(STATIC_BINDIR)/$(SNAME): $(OBJ)
	mkdir -p $(STATIC_BINDIR)
	$(AR) rcsv $@ $?

$(SHARED_BINDIR)/$(DNAME): LDFLAGS += -shared
$(SHARED_BINDIR)/$(DNAME): $(OBJ)
	mkdir -p $(SHARED_BINDIR)
	$(CC) $(LDFLAGS) $? -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@