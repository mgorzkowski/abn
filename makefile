#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC=gcc
AR=ar
CFLAGS=-c -Wall

bindir=./bin
src=\
	$(wildcard src/*.c) \
	$(wildcard src/operations/*.c) \
	$(wildcard src/utilities/*.c) \
	$(wildcard src/nonportable/*.c)
objs=$(src:.c=.o)

.PHOENY: all
all: create-bindir $(bindir)/libabn.a
	@rm -rf $(objs)
	@echo 'Build done'

.PHONEY: shared-lib
shared-lib: create-bindir $(bindir)/libabn.so
	@rm -rf $(objs)
	@echo 'Build done'

.PHONEY: clean
clean:
	@rm -rf $(objs)
	@rm -rf $(bindir)
	@rm -fr ./wrappers/*.pyc
	@make clean -C examples/simple_c_example
	@echo 'Clean done'

$(bindir)/libabn.a: $(objs)
	$(AR) rcsv $@ $?

$(bindir)/libabn.so: CFLAGS += -fpic
$(bindir)/libabn.so: $(objs)
	$(CC) -shared $? -o $@
	@rm -rf $(objs)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONEY: create-bindir
create-bindir:
	@mkdir -p $(bindir)

.PHONEY: build-example
build-example:
	@make -C examples/simple_c_example

.PHONEY: clean-example
clean-example:
	@make clean -C examples/simple_c_example
