/* c.f. supercollider/include/plugin_interface/SC_RGen.h */
#include <stdint.h>
#include "taus88.h"

extern inline void taus88_std_init(struct taus88 *t);
extern inline struct taus88 make_taus88(u32 seed);
extern inline u32 taus88_u32(struct taus88 *t);
extern inline f32 taus88_f32(struct taus88 *t);
extern inline f64 taus88_f64(struct taus88 *t);
