#ifndef _COMMON_X11_H
#define _COMMON_X11_H

#include <X11/Intrinsic.h>

void x11_fail_on_errors(void);
Display *x11_XOpenDisplay_err(char *nm);

#endif
