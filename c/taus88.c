/* c.f. supercollider/include/plugin_interface/SC_RGen.h */
#include <stdint.h>
#include "taus88.h"

extern inline void taus88_std_init(taus88_t *t);
extern inline taus88_t make_taus88(u32 seed);
extern inline u32 taus88u32(taus88_t *t);
extern inline f32 taus88f32(taus88_t *t);
