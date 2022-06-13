#ifndef _COMMON_COMPARE_H
#define _COMMON_COMPARE_H

// Comparison function suitable for qsort
inline int compare_float(const void *p1, const void *p2)
{
    float f1 = *((float *)p1);
    float f2 = *((float *)p2);
    return f1 > f2 ? 1 : (f1 < f2 ? -1 : 0);
}

#endif
