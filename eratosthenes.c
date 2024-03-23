// erastothenes.c
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#include "bitset.h"
#include <math.h>

void Eratosthenes(bitset_t *pole)
{
    bitset_fill(pole, true);
    bitset_setbit(pole, 0, false);
    bitset_setbit(pole, 1, false);   


    
}