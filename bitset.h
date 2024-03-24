// bitset.h
// Řešení IJC-DU1, příklad a), 22.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#ifndef BITSET_H_
#define BITSET_H_

#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;
#define ULONG_SIZE_BIT (sizeof(unsigned long) * 8)

#define bitset_create(jmeno_pole, velikost)               \
    static_assert(velikost > 0 && velikost <= ULONG_MAX); \
    unsigned long jmeno_pole[((velikost / ULONG_SIZE_BIT) + (velikost % ULONG_SIZE_BIT == 0 ? 0 : 1) + 1)] = {velikost};

#define bitset_alloc(jmeno_pole, velikost)                                                                                                                                                                            \
    assert(velikost > 0 && velikost <= ULONG_MAX);                                                                                                                                                                    \
    bitset_t jmeno_pole = calloc(((velikost / ULONG_SIZE_BIT) + (velikost % ULONG_SIZE_BIT == 0 ? 0 : 1) + 1), sizeof(unsigned long) * ((velikost / ULONG_SIZE_BIT) + (velikost % ULONG_SIZE_BIT == 0 ? 0 : 1) + 1)); \
    if (jmeno_pole == NULL)                                                                                                                                                                                           \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti");                                                                                                                                                        \
    jmeno_pole[0] = velikost;

#ifdef USE_INLINE

inline void bitset_free(bitset_t jmeno_pole)
{
    free(jmeno_pole);
}

inline unsigned long bitset_size(bitset_t jmeno_pole)
{
    return jmeno_pole[0];
}

inline void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz)
{
    unsigned long val = bool_vyraz ? ULONG_MAX : 0;
    for (bitset_index_t i = 1; i < (((jmeno_pole[0]) * ULONG_SIZE_BIT) - 1); i++) // bude treba zaokruhlovat ten vypocet, aj macro
    {
        jmeno_pole[i] = val;
    }
}

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz)
{
    if (index >= jmeno_pole[0])
        error_exit("bitset_setbit: index out of bounds\n");
    bitset_index_t cluster = (index % ULONG_SIZE_BIT) + 1;
    index -= (cluster - 1) * ULONG_SIZE_BIT;
    unsigned long pow = 2 << index;
    unsigned long mask = ULONG_MAX - pow;
    jmeno_pole[cluster] &= mask;
    if (bool_vyraz)
    {
        jmeno_pole[cluster] += pow;
    }
}

inline bool bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
    if (index > jmeno_pole[0])
        error_exit("bitset_setbit: index out of bounds\n");
    bitset_index_t cluster = (index % ULONG_SIZE_BIT) + 1;
    index -= (cluster - 1) * ULONG_SIZE_BIT;
    unsigned long tmp = jmeno_pole[cluster];
    unsigned long mask = 2 << index;
    tmp &= mask;
    tmp >>= index;
    return tmp;
}

#else

#define bitset_free(jmeno_pole) \
    free(jmeno_pole)

#define bitset_size(jmeno_pole) \
    jmeno_pole[0]

#define bitset_fill(jmeno_pole, bool_vyraz)                                                                     \
    do                                                                                                          \
    {                                                                                                           \
        unsigned long val = bool_vyraz ? ULONG_MAX : 0;                                                         \
        unsigned long max_cluster = (jmeno_pole[0] / ULONG_MAX) + (jmeno_pole[0] % ULONG_MAX == 0 ? 0 : 1) + 1; \
        for (bitset_index_t i = 1; i < max_cluster; i++)                                                        \
        {                                                                                                       \
            jmeno_pole[i] = val;                                                                                \
        }                                                                                                       \
    } while (0)

#define bitset_setbit(jmeno_pole, index, bool_vyraz)                                                                         \
    do                                                                                                                       \
    {                                                                                                                        \
        if (index >= jmeno_pole[0])                                                                                          \
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)jmeno_pole[0]); \
        bitset_index_t cluster = (index / ULONG_SIZE_BIT) + 1;                                                               \
        bitset_index_t ix = index;                                                                                           \
        ix -= (cluster - 1) * ULONG_SIZE_BIT;                                                                                \
        unsigned long pow = 1UL << ix;                                                                                       \
        unsigned long mask = ULONG_MAX - pow;                                                                                \
        jmeno_pole[cluster] &= mask;                                                                                         \
        if (bool_vyraz)                                                                                                      \
        {                                                                                                                    \
            jmeno_pole[cluster] += pow;                                                                                      \
        }                                                                                                                    \
    } while (0)

#define bitset_getbit(jmeno_pole, index)                                       \
    (index < jmeno_pole[0])                                                    \
        ? ((jmeno_pole[(index / ULONG_SIZE_BIT) + 1] & (2 << index)) >> index) //nikdy nevrati true \ 
        : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)jmeno_pole[0]), 0)

#endif // USE_INLINE

#endif // BITSET_H_