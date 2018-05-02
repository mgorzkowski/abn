CC=gcc
CFLAGS=-c -Wall -std=c99 -g
OUTDIR=./output
OBJS= \
$(OUTDIR)/abn.o \
$(OUTDIR)/arithmetic.o \
$(OUTDIR)/logic.o \
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

$(OUTDIR)/abn.o: ./src/abn.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/abn.c -o $(OUTDIR)/abn.o

$(OUTDIR)/arithmetic.o: ./src/operations/arithmetic.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/operations/arithmetic.c -o $(OUTDIR)/arithmetic.o

$(OUTDIR)/logic.o: ./src/operations/logic.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/operations/logic.c -o $(OUTDIR)/logic.o

$(OUTDIR)/string_manipulations.o: ./src/utilities/string_manipulations.c ./include/abn.h
	$(CC) $(CFLAGS) ./src/utilities/string_manipulations.c -o $(OUTDIR)/string_manipulations.o

create_outdir:
	mkdir -p $(OUTDIR)

clean-examples:
	rm -rf examples/*/output
