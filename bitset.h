// bitset.h
// Řešení IJC-DU1, příklad a), 22.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0
// definicia makier a inline funkcii

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

// vytvara lokalne pole {velikost, 0, 0, ...}
#define bitset_create(jmeno_pole, velikost)               \
    static_assert(velikost > 0 && velikost <= ULONG_MAX); \
    unsigned long jmeno_pole[((velikost / ULONG_SIZE_BIT) + (velikost % ULONG_SIZE_BIT == 0 ? 0 : 1) + 1)] = {velikost};

// dynamicky alokuje pole plne nul, na 0. index da velikost
#define bitset_alloc(jmeno_pole, velikost)                                                                                             \
    assert(velikost > 0 && velikost <= ULONG_MAX);                                                                                     \
    bitset_t jmeno_pole = calloc(((velikost / ULONG_SIZE_BIT) + (velikost % ULONG_SIZE_BIT == 0 ? 0 : 1) + 1), sizeof(unsigned long)); \
    if (jmeno_pole == NULL)                                                                                                            \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti");                                                                         \
    jmeno_pole[0] = velikost;

// pouzije inline funkcie ked preklada s -DUSE_INLINE, makra ked nie
#ifdef USE_INLINE

// uvolni pamat
inline void bitset_free(bitset_t jmeno_pole)
{
    free(jmeno_pole);
}

// vracia pocet pouzitelnych bitov v bitset
inline unsigned long bitset_size(bitset_t jmeno_pole)
{
    return jmeno_pole[0];
}

// vyplni cely bitset 0 alebo 1
inline void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz)
{
    unsigned long val = bool_vyraz ? ULONG_MAX : 0;
    unsigned long max_cluster = (jmeno_pole[0] / ULONG_SIZE_BIT) + 1;
    for (bitset_index_t i = 1; i < max_cluster; i++)
    {
        jmeno_pole[i] = val;
    }
}

// nastavi bit na na indexe index na 0 alebo 1
inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz)
{
    if (index >= jmeno_pole[0])
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)jmeno_pole[0]);
    bitset_index_t cluster = (index / ULONG_SIZE_BIT) + 1; // poradie ulongu v poli na ktorom sa nachadza index
    bitset_index_t ix = index;
    ix -= (cluster - 1) * ULONG_SIZE_BIT; // indexe na danom ulongu
    unsigned long pow = 1UL << ix;        // 2^ix
    unsigned long mask = ULONG_MAX - pow;
    jmeno_pole[cluster] &= mask; // nastavi bit na 0
    if (bool_vyraz)              // ked ma byt bit true nastavi ho na 1
    {
        jmeno_pole[cluster] += pow;
    }
}

// vracia 0 alebo 1 podla bitu na indexe index
inline bool bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
    if (index >= jmeno_pole[0])
        error_exit("bitset_setbit: index out of bounds\n");
    return (((jmeno_pole[(index / ULONG_SIZE_BIT) + 1]) >> (index % ULONG_SIZE_BIT)) & 1UL);
    // presunie bit ktory chceme na zaciatok a vynuluje vsetky zvysne bity
    // vrati 1 alebo 0
}

#else

// uvolni pamat
#define bitset_free(jmeno_pole) \
    free(jmeno_pole)

// vracia pocet pouzitelnych bitov v bitset
#define bitset_size(jmeno_pole) \
    jmeno_pole[0]

// vyplni bitset 1 alebo 0
#define bitset_fill(jmeno_pole, bool_vyraz)                               \
    do                                                                    \
    {                                                                     \
        unsigned long val = bool_vyraz ? ULONG_MAX : 0;                   \
        unsigned long max_cluster = (jmeno_pole[0] / ULONG_SIZE_BIT) + 1; \
        for (bitset_index_t i = 1; i < max_cluster; i++)                  \
        {                                                                 \
            jmeno_pole[i] = val;                                          \
        }                                                                 \
    } while (0)

// nastavi bit na na indexe index na 0 alebo 1, rovnaka logika ako v inline funkcii
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

// vracia 0 alebo 1 podla bitu na indexe index, rovnaka logika ako v inline funkcii
#define bitset_getbit(jmeno_pole, index)                                                   \
    (index < jmeno_pole[0])                                                                \
        ? (((jmeno_pole[(index / ULONG_SIZE_BIT) + 1]) >> (index % ULONG_SIZE_BIT)) & 1UL) \
        : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, jmeno_pole[0]), 0)

#endif // USE_INLINE

#endif // BITSET_H_