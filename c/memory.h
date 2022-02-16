#ifndef _COMMON_MEMORY_H
#define _COMMON_MEMORY_H

#include <stddef.h>

inline void *xmalloc(size_t size);
inline void *xcalloc(size_t count, size_t eltsize);
inline void *xrealloc(void *p, size_t size);
inline void *xmemcpy(void *dst,const void *src, size_t n);
inline void *xmemset(void *s, int c, size_t n);

inline float *fmalloc(size_t n);
inline void fmemset(float *data, int n, float value);

#endif
