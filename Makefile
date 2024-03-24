# Makefile 
# Řešení IJC-DU1, 20.3.2024
# Autor: Marek Hric, FIT
# Přeloženo: gcc 13.2.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2 -fsanitize=address
LDLIBS = -lm -fsanitize=address

.PHONY: all run clean

all: no-comment primes primes-i

primes: primes.c error.o eratosthenes.o eratosthenes.h

primes-i: primes-i.o eratosthenes-i.o error.o bitset-i.o

%-i.o: %.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

no-comment: no-comment.o error.o error.h

clean:
	rm -f *.o no-comment primes primes-i

run: primes primes-i
	ulimit -s 82000 && ./primes
	ulimit -s 82000 && ./primes-i
	
zip:
	zip xhricma00.zip *.c *.h Makefile