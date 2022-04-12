#ifndef _COMMON_HASH_H
#define _COMMON_HASH_H

#include <stdint.h>

// Thomas Wang's 32-bit integer hash. http://www.concentric.net/~Ttwang/tech/inthash.htm
inline int32_t int32_hash(int32_t inKey) {
    uint32_t hash = (uint32_t)inKey;
    hash += ~(hash << 15);
    hash ^= hash >> 10;
    hash += hash << 3;
    hash ^= hash >> 6;
    hash += ~(hash << 11);
    hash ^= hash >> 16;
    return (int32_t)hash;
}

// Thomas Wang's 64-bit integer hash.
inline int64_t int64_hash(int64_t inKey) {
    uint64_t hash = (uint64_t)inKey;
    hash += ~(hash << 32);
    hash ^= (hash >> 22);
    hash += ~(hash << 13);
    hash ^= (hash >> 8);
    hash += (hash << 3);
    hash ^= (hash >> 15);
    hash += ~(hash << 27);
    hash ^= (hash >> 31);
    return (int64_t)hash;
}

#endif
