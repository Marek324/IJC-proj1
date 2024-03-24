// no-comment.c
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#include "bitset.h"
#include "eratosthenes.h"
#include <time.h>

#define N 666000000UL

int main()
{
    clock_t start = clock();
    bitset_create(pole, N);

    Eratosthenes(pole);

    int prims = 0;
    bitset_index_t primes[10] = {0};

    // iterate from the end of pole until 10 numbers are saved in primes
    for (bitset_index_t i = bitset_size(pole) - 1; prims < 10; i--)
    {
        if (bitset_getbit(pole, i))
        {
            primes[prims] = i;
            prims++;
        }
    }

    // print out primes from the end, so they're in descending order
    for (int i = 9; i >= 0; i--)
    {
        printf("%lu\n", primes[i]);
    }
    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC); // ?

    return 0;
}