CC=gcc
GSL_HOME=

CFLAGS=-I$(GSL_HOME)/include
LDFLAGS=-L$(GSL_HOME)/lib -lgsl -lgslcblas -lm 

all: zad2

zad2: zad2.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o