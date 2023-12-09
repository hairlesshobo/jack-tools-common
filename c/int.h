#ifndef _COMMON_INT_H
#define _COMMON_INT_H

#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

i32 i32_min(i32 p, i32 q);
i32 i32_max(i32 p, i32 q);

u64 u64_min(u64 p, u64 q);
u64 u64_max(u64 p, u64 q);

#endif
