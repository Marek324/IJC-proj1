#ifdef USE_INLINE

#include "bitset.h"
extern void bitset_free(bitset_t *jmeno_pole);
extern unsigned long bitset_size(bitset_t *jmeno_pole);
extern void bitset_fill(bitset_t *jmeno_pole, bool_vyraz);
extern void bitset_setbit(bitset_t *jmeno_pole, bitset_index_t index, bool bool_vyraz);
extern bool bitset_getbit(bitset_t *jmeno_pole, bitset_index_t index);

#endif // USE_INLINE