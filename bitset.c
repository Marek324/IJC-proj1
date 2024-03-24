// bitset.c
// Řešení IJC-DU1, příklad a), 22.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#ifdef USE_INLINE

#include "bitset.h"
extern void bitset_free(bitset_t jmeno_pole);
extern unsigned long bitset_size(bitset_t jmeno_pole);
extern void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz);
extern void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz);
extern bool bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif // USE_INLINE