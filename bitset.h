/*
*   bitset.h
*   Marek Hric //TODO: opravit headers podla zadania
*   259715
*   xhricma00
*/

#ifndef BITSET_H_
#define BITSET_H_

#include <stdbool.h>
#include "error.h"

typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

void bitset_create(bitset_t* jmeno_pole, unsigned velikost);
void bitset_alloc(bitset_t* jmeno_pole, unsigned velikost);
void bitset_free(bitset_t *jmeno_pole);
unsigned bitset_size(bitset_t *jmeno_pole);
void bitset_fill(bitset_t *jmeno_pole, bool bool_vyraz);
void bitset_setbit(bitset_t *jmeno_pole, bitset_index_t index, bool bool_vyraz);
bool bitset_getbit(bitset_t *jmeno_pole, bitset_index_t index);

#endif