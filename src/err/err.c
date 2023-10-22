#include <stdarg.h>
#include <stdio.h>

#include "err.h"
#include "render.h"

void cliErr(const char *fmt, ...) {
    va_list args;
    
    va_start(args, fmt);
    renderSimpleErr(fmt, args);
    va_end(args);
}
