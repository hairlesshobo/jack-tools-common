#include <stdio.h> /* C99 */

#include <dlfcn.h> /* POSIX.1-2001 */

#include "failure.h"

void *xdlopen(const char *fn,int flags)
{
    void *m = dlopen(fn, flags);
    if (!m) {
        die("DLOPEN ERROR: %s, %s\n", fn, dlerror());
    }
    return m;
}

void *xdlsym(void *handle, const char *symbol)
{
    void *f = dlsym(handle,symbol);
    if (!f) {
        die("DLSYM ERROR: %s, %s\n", symbol, dlerror());
    }
    return f;
}

int xdlclose(void *handle)
{
    int err = dlclose(handle);
    if (err != 0) {
        die("DLCLOSE ERROR: %s\n", dlerror());
    }
    return err;
}
