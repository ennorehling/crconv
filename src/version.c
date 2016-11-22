#include <platform.h>
#include <autoconf.h>
#include "version.h"

#include <stdio.h>

#ifndef CRCONV_VERSION
// the version number, if it was not passed to make with -D
#define CRCONV_VERSION "3.10.0-devel"
#endif

const char *crconv_version(void) {
    return CRCONV_VERSION;
}

int version_no(const char *str) {
    int maj = 0, min = 0, bld = 0;
    sscanf(str, "%d.%d.%d", &maj, &min, &bld);
    return (maj << 16) | (min << 8) | bld;
}
