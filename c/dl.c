#include <stdio.h> /* C99 */

#include <dlfcn.h> /* POSIX.1-2001 */

#include "failure.h"

void *xdlopen(const char *fn,int flags)
{
    void *m = dlopen(fn, flags);
    die_when(m == NULL,"DLOPEN ERROR: %s, %s\n", fn, dlerror());
    return m;
}

void *xdlsym(void *handle, const char *symbol)
{
    void *f = dlsym(handle,symbol);
    die_when(f == NULL,"DLSYM ERROR: %s, %s\n", symbol, dlerror());
    return f;
}

int xdlclose(void *handle)
{
    int err = dlclose(handle);
    die_when(err != 0,"DLCLOSE ERROR: %s\n", dlerror());
    return err;
}
