# compiler specificatioins

CC=gcc
OFLAGS=-c -Wall -ansi -std=c99
CFLAGS=-Wall -ansi -std=c99
OBJFILES= \
./bin/abn.o \
./bin/addition_algorithms.o \
./bin/multiplication_algorithms.o \
./bin/others.o \
./bin/shifts.o \
./bin/string_manipulations.o


# Rules

all: ./bin/libabn.a

example: ./examples/example.elf

run-example: ./examples/example.elf
	./examples/bin/example.elf

clean:
	rm -r ./bin/*
	rm -r ./examples/bin/*

# Static library compiling

./bin/libabn.a: $(OBJFILES)
	ar rcsv ./bin/libabn.a $(OBJFILES)
	rm $(OBJFILES)

./bin/abn.o: ./src/abn.c ./lib/abn.h
	$(CC) $(OFLAGS) ./src/abn.c -o ./bin/abn.o

./bin/addition_algorithms.o: ./src/operations/addition_algorithms.c ./lib/operations/addition_algorithms.h
	$(CC) $(OFLAGS) ./src/operations/addition_algorithms.c -o ./bin/addition_algorithms.o

bin/multiplication_algorithms.o: ./src/operations/multiplication_algorithms.c ./lib/operations/multiplication_algorithms.h
	$(CC) $(OFLAGS) ./src/operations/multiplication_algorithms.c -o ./bin/multiplication_algorithms.o

bin/others.o: ./src/operations/others.c ./lib/operations/others.h
	$(CC) $(OFLAGS) ./src/operations/others.c -o ./bin/others.o

bin/shifts.o: ./src/operations/shifts.c ./lib/operations/shifts.h
	$(CC) $(OFLAGS) ./src/operations/shifts.c -o ./bin/shifts.o

bin/string_manipulations.o: ./src/utilities/string_manipulations.c ./lib/utilities/string_manipulations.h
	$(CC) $(OFLAGS) ./src/utilities/string_manipulations.c -o ./bin/string_manipulations.o


# Example compiling

./examples/example.elf: ./examples/example.c ./bin/libabn.a
	$(CC) $(CFLAGS) ./examples/example.c -L./bin/ -labn -o ./examples/bin/example.elf
