CC=gcc
CFLAGS=-c -Wall -std=c99

OUTDIR=./bin
OBJS= \
$(OUTDIR)/abn.o \
$(OUTDIR)/additive.o \
$(OUTDIR)/multiplicative.o \
$(OUTDIR)/bit.o \
$(OUTDIR)/shift.o \
$(OUTDIR)/string.o

all: create_outdir $(OUTDIR)/libabn.a
	rm $(OBJS)

clean:
	rm -rf $(OUTDIR)

clean-all: clean-examples
	rm -rf $(OUTDIR)


$(OUTDIR)/libabn.a: $(OBJS)
	ar rcsv $(OUTDIR)/libabn.a $(OBJS)

$(OUTDIR)/abn.o: ./src/abn.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/abn.c -o $(OUTDIR)/abn.o

$(OUTDIR)/additive.o: ./src/operations/additive.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/operations/additive.c -o $(OUTDIR)/additive.o

$(OUTDIR)/multiplicative.o: ./src/operations/multiplicative.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/operations/multiplicative.c -o $(OUTDIR)/multiplicative.o

$(OUTDIR)/bit.o: ./src/operations/bit.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/operations/bit.c -o $(OUTDIR)/bit.o

$(OUTDIR)/shift.o: ./src/operations/shift.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/operations/shift.c -o $(OUTDIR)/shift.o

$(OUTDIR)/string.o: ./src/utilities/string.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/utilities/string.c -o $(OUTDIR)/string.o

create_outdir:
	mkdir -p $(OUTDIR)

clean-examples:
	rm -rf examples/*/bin
