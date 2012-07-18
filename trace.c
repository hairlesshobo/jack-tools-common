#include <string.h>
#include "int.h"
#include "float.h"
#include "trace.h"

#define TRACE_CPY(r,d,m) memcpy(r,d,m*sizeof(f32))
#define TRACE_PTR(d,m,i) (d + ((i)*(m)))
#define TRACE_READ(d,m,n,i) d[((n)*(m))+(i)]
#define TRACE_T(d,m,n) d[(n)*(m)]

void trace_interpolate(const f32 * d, i32 m, f32 t, f32 z, f32 * r)
{
    i32 i;
    r[0] = t;
    for (i = 1; i < m; i++) {
	f32 p = d[i];
	f32 q = d[i + m];
	r[i] = (z * (q - p)) + p;
    }
    return;
}

/* d = data, n = data length, m = trace degree (including t), r = result */
int trace_lookup(const f32 * d, i32 n, i32 m, f32 time, f32 * r)
{
    i32 trace_n = n / m;
    if (n == m || time <= 0.0) {
	TRACE_CPY(r, d, m);
	return 0;
    } else if (time >= 1.0) {
	TRACE_CPY(r, TRACE_PTR(d, m, trace_n - 1), m);
	return 0;
    } else {
	f32 t_left = TRACE_T(d, m, 0);
	i32 i;
	for (i = 1; i < trace_n; i++) {
	    f32 t_right = TRACE_T(d, m, i);
	    if (time >= t_left && time <= t_right) {
		f32 z = (time - t_left) / (t_right - t_left);
		trace_interpolate(TRACE_PTR(d, m, i), m, time, z, r);
		return 0;
	    }
	    t_left = t_right;
	}
    }
    TRACE_CPY(r, TRACE_PTR(d, m, trace_n - 1), m);
    return -1;
}
