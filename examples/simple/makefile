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

./bin/example.elf: ./example.c $(ABN_LIB_DIR)$(ABN_LIB_NAME)
	mkdir -p bin/
	$(CC) $(CFLAGS) example.c -I$(ABN_INCLUDE_DIR) -L$(ABN_LIB_DIR) -labn -o ./bin/example.elf
