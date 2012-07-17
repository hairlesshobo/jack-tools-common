#include "int.h"
#include "float.h"
#include "trace.h"

#define TRACE_N                4
#define TRACE_READ(data,n,i)   data[((n)*TRACE_N)+(i)]
#define TRACE_T(data,n)        TRACE_READ(data,n,0)
#define TRACE_X(data,n)        TRACE_READ(data,n,1)
#define TRACE_Y(data,n)        TRACE_READ(data,n,2)
#define TRACE_Z(data,n)        TRACE_READ(data,n,3)

f32 trace_lookup(const f32 * data, i32 data_n, f32 time, i32 access)
{
    i32 trace_n = data_n / TRACE_N;
    if (data_n == TRACE_N) {
	return TRACE_READ(data, 0, access);
    } else if (time <= 0.0) {
	return TRACE_READ(data, 0, access);
    } else if (time >= 1.0) {
	return TRACE_READ(data, trace_n - 1, access);
    } else {
	f32 t_left = TRACE_T(data, 0);
	i32 i;
	for (i = 1; i < trace_n; i++) {
	    f32 t_right = TRACE_T(data, i);
	    if (time >= t_left && time <= t_right) {
		f32 index = (time - t_left) / (t_right - t_left);
		f32 left = TRACE_READ(data, i - 1, access);
		f32 right = TRACE_READ(data, i, access);
		return (index * (right - left)) + left;
	    }
	    t_left = t_right;
	}
    }
    return 0.0;
}
