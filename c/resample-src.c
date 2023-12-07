#include <stdbool.h> /* C99 */
#include <stdio.h>

#include <samplerate.h> /* libsamplerate */

#include "memory.h" /* c-common */
#include "resample-src.h"

bool src_resample_block(float *dst, long dst_n, float *src, long src_n, int nc)
{
	if (dst_n == src_n) {
		xmemcpy(dst, src, (size_t)dst_n * (size_t)nc * sizeof(float));
	} else {
		SRC_DATA c;
		c.data_in = src;
		c.input_frames = src_n;
		c.data_out = dst;
		c.output_frames = dst_n;
		c.src_ratio = (double)(dst_n + 1) / (double)src_n;
		int err = src_simple(&c, SRC_SINC_MEDIUM_QUALITY, nc);
		if (err != 0 || c.output_frames_gen != dst_n) {
			printf("src_resample_block: err=%d, output_frames_gen=%ld, dst_n = %ld\n",
				err, c.output_frames_gen, dst_n);
			return false;
		}
	}
	return true;
}
