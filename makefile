CC=gcc
CFLAGS=-c -Wall -std=c99
OUTDIR=./output
OBJS= \
$(OUTDIR)/abn.o \
$(OUTDIR)/addition_algorithms.o \
$(OUTDIR)/multiplication_algorithms.o \
$(OUTDIR)/others.o \
$(OUTDIR)/shifts.o \
$(OUTDIR)/string_manipulations.o

all: create_outdir $(OUTDIR)/libabn.a
	rm $(OBJS)

clean:
	rm -rf $(OUTDIR)

clean-all: clean-examples
	rm -rf $(OUTDIR)

$(OUTDIR)/libabn.a: $(OBJS)
	mkdir -p $(OUTDIR)
	ar rcsv $(OUTDIR)/libabn.a $(OBJS)

$(OUTDIR)/abn.o: ./src/abn.c ./lib/abn.h
	$(CC) $(CFLAGS) ./src/abn.c -o $(OUTDIR)/abn.o

$(OUTDIR)/addition_algorithms.o: ./src/operations/addition_algorithms.c ./lib/operations/addition_algorithms.h
	$(CC) $(CFLAGS) ./src/operations/addition_algorithms.c -o $(OUTDIR)/addition_algorithms.o

$(OUTDIR)/multiplication_algorithms.o: ./src/operations/multiplication_algorithms.c ./lib/operations/multiplication_algorithms.h
	$(CC) $(CFLAGS) ./src/operations/multiplication_algorithms.c -o $(OUTDIR)/multiplication_algorithms.o

$(OUTDIR)/others.o: ./src/operations/others.c ./lib/operations/others.h
	$(CC) $(CFLAGS) ./src/operations/others.c -o $(OUTDIR)/others.o

$(OUTDIR)/shifts.o: ./src/operations/shifts.c ./lib/operations/shifts.h
	$(CC) $(CFLAGS) ./src/operations/shifts.c -o $(OUTDIR)/shifts.o

$(OUTDIR)/string_manipulations.o: ./src/utilities/string_manipulations.c ./lib/utilities/string_manipulations.h
	$(CC) $(CFLAGS) ./src/utilities/string_manipulations.c -o $(OUTDIR)/string_manipulations.o

create_outdir:
	mkdir -p $(OUTDIR)

clean-examples:
	rm -rf examples/*/output
