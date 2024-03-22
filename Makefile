# Makefile 
# Řešení IJC-DU1, 20.3.2024
# Autor: Marek Hric, FIT
# Přeloženo: gcc 13.2.0

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

no-comment: error.o no-comment.o
	$(CC) $(CFLAGS) -o no-comment no-comment.o error.o

error.o: error.h error.c
	$(CC) $(CFLAGS) -c -o error.o error.c

no-comment.o: no-comment.c error.h
	$(CC) $(CFLAGS) -c -o no-comment.o no-comment.c

clean:
	rm *.o no-comment
