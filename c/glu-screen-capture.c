#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "glu-screen-capture.h"
#include "img-ppm.h"
#include "memory.h"

void glu_screen_capture(char *fn)
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	u8 *d = (u8 *)malloc(w * h * 3);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, d);
	img_write_ppm_file(d, w, h, fn);
	free(d);
}
