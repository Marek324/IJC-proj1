// eratosthenes.c
// Řešení IJC-DU1, příklad a), 23.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#include "bitset.h"
#include <math.h>

void Eratosthenes(bitset_t pole)
{
    bitset_fill(pole, true);
    bitset_setbit(pole, 0, false);
    bitset_setbit(pole, 1, false);

    unsigned long n = pole[0];

    bitset_index_t lim = sqrt(n);
    for (bitset_index_t i = 2; i <= lim; i++)
    {
        printf("%lu: %s\n", i, (bitset_getbit(pole, i)) == true ? "true" : "false");
        if ((bitset_getbit(pole, i)) == false)
            continue;
        

        for (bitset_index_t j = 2; (i * j) < n; j++)
        {
            bitset_setbit(pole, (i * j), false);
        }
    }
}