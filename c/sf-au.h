#ifndef _COMMON_SF_AU_H
#define _COMMON_SF_AU_H

#include "int.h"
#include "float.h"

void write_au_f32(char *nm,i32 nc,i32 nf,i32 sr,f32 *d);
f32 *read_au_f32(char *nm, i32 *nc, i32 *nf, i32 *sr);

#endif
