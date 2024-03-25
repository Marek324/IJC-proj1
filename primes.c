// no-comment.c
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0
// Volanie Eratosthenes a vypis poslednych 10 prvocisel

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

    // Prechadza polom odzadu a uklada ich do pola primes, kym ich nie je 10
    for (bitset_index_t i = bitset_size(pole) - 1; prims < 10; i--)
    {
        if (bitset_getbit(pole, i))
        {
            primes[prims] = i;
            prims++;
        }
    }

    // vypis pola primes odzadu, aby boli vo vzsotupnom poradi
    for (int i = 9; i >= 0; i--)
    {
        printf("%lu\n", primes[i]);
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC); 

    return 0;
}