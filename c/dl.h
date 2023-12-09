#ifndef _COMMON_DL_H
#define _COMMON_DL_H

void *xdlopen(const char *fn, int flags);
void *xdlsym(void *handle, const char *symbol);
int xdlclose(void *handle);

#endif
