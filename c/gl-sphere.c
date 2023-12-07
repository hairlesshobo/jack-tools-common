#include "gl-sphere.h"
#include <GL/gl.h>
#include <GL/glu.h>

void spherel(void)
{
	int n = 16;
	GLUquadric *q = gluNewQuadric();
	gluQuadricDrawStyle(q, GLU_LINE);
	gluQuadricNormals(q, GLU_SMOOTH);
	gluSphere(q, 1.0, n, n);
	gluDeleteQuadric(q);
}
