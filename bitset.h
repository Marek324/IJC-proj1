// bitset.h
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#ifndef BITSET_H_
#define BITSET_H_

#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;
#define ULONG_SIZE_BIT (sizeof(unsigned long) * CHAR_BIT)

// void bitset_create(bitset_t **jmeno_pole, unsigned velikost);
// void bitset_alloc(bitset_t **jmeno_pole, unsigned velikost);
// void bitset_free(bitset_t **jmeno_pole);
// unsigned bitset_size(bitset_t **jmeno_pole);
// void bitset_fill(bitset_t **jmeno_pole, bool bool_vyraz);
// void bitset_setbit(bitset_t **jmeno_pole, bitset_index_t index, bool bool_vyraz);
// bool bitset_getbit(bitset_t **jmeno_pole, bitset_index_t index);

#define bitset_create(jmeno_pole, velikost)               \
    static_assert(velikost > 0 && velikost <= ULONG_MAX); \
    bitset_index_t jmeno_pole[(velikost / ULONG_SIZE_BIT) + 1 + (velikost % ULONG_SIZE_BIT == 0 ? 0 : 1)] = {velikost};

#define bitset_alloc(jmeno_pole, velikost)                                                                                        \
    assert(velikost > 0 && velikost <= ULONG_MAX);                                                                                \
    bitset_t jmeno_pole = calloc((velikost / ULONG_SIZE_BIT + velikost % ULONG_SIZE_BIT == ? 0 : 1), sizeof(bitset_index_t) + 1); \
    if (jmeno_pole == NULL)                                                                                                       \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti");                                                                    \
    jmeno_pole[0] = velikost;

#ifdef USE_INLINE

inline void foo()
{
    printf("Hello, world! inline\n");
};

#else

#define foo                             \
    do                                  \
    {                                   \
        printf("Hello, world! macro\n") \
    } while (0)

#endif // USE_INLINE

#endif // BITSET_H_