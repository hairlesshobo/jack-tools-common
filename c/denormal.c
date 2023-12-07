/* http://carlh.net/plugins/denormals.php */

#include <stdio.h>

#include "denormal.h"

#if _DENORMAL_FE
#include <fenv.h>
void disable_denormals(void)
{
	fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
}
#elif _DENORMAL_MM
#include <xmmintrin.h>
void disable_denormals(void)
{
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
}
#else
void disable_denormals(void)
{
	fprintf(stderr, "disable_denormals: not implemented");
}
#endif
