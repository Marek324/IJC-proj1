// no-comment.c
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#include "bitset.h"
#include "eratosthenes.h"

int main()
{
    bitset_create(pole, 100);
    Eratosthenes(pole);

    int prims = 0;
    bitset_index_t primes[10] = {0};

    for (bitset_index_t i = bitset_size(pole)-1; prims < 10; i--)
    {
        if(bitset_getbit(pole, i) == true){
            primes[prims] = i;
            prims++;
        }
    }

    for (int i = 9; i >= 0; i--)
    {
        printf("%lu\n", primes[i]);
    }
    

    return 0;
}