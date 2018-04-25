CC=gcc
CFLAGS=-Wall -std=c99 -I../../lib
ABN_LIB_DIR=../../output/
ABN_LIB_NAME=libabn.a

all: ./output/test.elf

run: ./output/test.elf
	./output/test.elf

clean:
	rm -rf ./output

./output/test.elf: ./test.c $(ABN_LIB_DIR)$(ABN_LIB_NAME)
	mkdir -p output/
	$(CC) $(CFLAGS) test.c -L$(ABN_LIB_DIR) -labn -o ./output/test.elf
