# Makefile 
# Řešení IJC-DU1, 24.3.2024
# Autor: Marek Hric, FIT
# Přeloženo: gcc 13.2.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2 
LDLIBS = -lm 

.PHONY: all run clean

all: no-comment primes primes-i

primes: primes.c eratosthenes.o error.o
	$(CC) $(CFLAGS) -o primes primes.c eratosthenes.o error.o $(LDLIBS)

eratosthenes.o: eratosthenes.c bitset.h 
	$(CC) $(CFLAGS) -c -o eratosthenes.o eratosthenes.c $(LDLIBS)

primes-i: primes.c eratosthenes-i.o bitset-i.o error.o
	$(CC) $(CFLAGS) -o primes-i primes.c eratosthenes-i.o error.o bitset-i.o $(LDLIBS)

eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS) -c -o eratosthenes-i.o eratosthenes.c $(LDLIBS)

bitset-i.o : bitset.h bitset.c 
	$(CC) $(CFLAGS) -c -DUSE_INLINE -o bitset-i.o bitset.c 

no-comment: no-comment.c error.o error.h
	$(CC) $(CFLAGS) -o no-comment no-comment.c error.o

error.o: error.h error.c
	$(CC) $(CFLAGS) -c -o error.o error.c

clean:
	rm -f *.o no-comment primes primes-i

run: primes primes-i
	ulimit -s 131072 && ./primes
	ulimit -s 131072 && ./primes-i
	
zip:
	zip xhricma00.zip *.c *.h Makefile