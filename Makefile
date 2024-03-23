# Makefile 
# Řešení IJC-DU1, 20.3.2024
# Autor: Marek Hric, FIT
# Přeloženo: gcc 13.2.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

all: primes primes-i no-command

#macros
bitset.o: bitset.h bitset.c error.h
	$(CC) $(CFLAGS) -c -o bitset.o bitset.c

primes: error.o bitset.o
	$(CC) $(CFLAGS) -o primes error.o bitset.o

#inline functions
bitset-i.o: bitset.h bitset.c error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o bitset-i.o bitset.c

primes-i: error.o bitset-i.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o primes error.o bitset.o

no-comment: error.o no-comment.o
	$(CC) $(CFLAGS) -o no-comment no-comment.o error.o

error.o: error.h error.c
	$(CC) $(CFLAGS) -c -o error.o error.c

no-comment.o: no-comment.c error.h
	$(CC) $(CFLAGS) -c -o no-comment.o no-comment.c

clean:
	rm *.o no-comment

run: primes primes-i
	ulimit -s 82000 && ./primes
	ulimit -s 82000 && ./primes-i
	

zip:
	zip xhricma00 .zip *.c *.h Makefile