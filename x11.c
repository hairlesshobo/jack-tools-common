#include <stdio.h>
#include <stdlib.h>

#include "failure.h"
#include "x11.h"

static int
x11_error_fail(Display *d, XErrorEvent *e)
{
  char message[128];
  XGetErrorText(d, e->error_code, message, 128);
  fprintf(stderr, "x11_error_fail: %s\n", message);
  FAILURE;
  return 1;
}

static int
x11_io_error_fail(Display *d)
{
  fprintf(stderr, "x11_io_error_fail\n");
  FAILURE;
  return 1;
}

void x11_fail_on_errors(void)
{
  XSetErrorHandler(x11_error_fail);
  XSetIOErrorHandler(x11_io_error_fail);
}

Display *x11_XOpenDisplay_err(char *nm)
{
    Display *d = XOpenDisplay(nm);
    if (!d) {
        fprintf(stderr, "x11: ERROR: XOpenDisplay failed\n");
        exit(1);
    }
    return d;
}
