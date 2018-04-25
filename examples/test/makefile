CC						=	gcc
CFLAGS				=	-Wall -std=c99 -I../../lib
ABN_LIB_DIR		=	../../output/
ABN_LIB_NAME	=	libabn.a

all: ./output/example.elf

run: ./output/example.elf
	./output/example.elf

clean:
	rm -rf ./output

./output/example.elf: ./example.c $(ABN_LIB_DIR)$(ABN_LIB_NAME)
	mkdir -p output/
	$(CC) $(CFLAGS) example.c -L$(ABN_LIB_DIR) -labn -o ./output/example.elf
