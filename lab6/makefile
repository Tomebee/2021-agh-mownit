CC = gcc
CFLAGS = -I/usr/include/gsl
LDFLAGS = -L/usr/lib -lgsl -lgslcblas -lm 

rownania : rownania.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 

clean :
	rm rownania