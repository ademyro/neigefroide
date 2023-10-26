#include <math.h>
#include <stdarg.h>

#include "err.h"
#include "render.h"

static ErrMod mod;

void initErrMod(const char *fname, char *src) {
    mod.fname = fname;
    mod.src = src;
}

void cliErr(const char *fmt, ...) {
    va_list args;
    
    va_start(args, fmt);
    renderErrMsg(fmt, args);
    va_end(args);
}

void reportErrAt(Loc loc, const char *fmt, ...) {
    const char *fname = mod.fname;
    va_list args;

    va_start(args, fmt);
    renderErrMsg(fmt, args); 
    renderLocus(fname, loc); 
    va_end(args);
}

void showOffendingLine(Loc loc, const char *fmt, ...) {
    char *src = mod.src;
    va_list args;
    
    renderLine(src, loc.line); 

    va_start(args, fmt);
    highlightErr(loc, fmt, args);
    va_end(args); 
}

void showHint(Loc loc, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    renderHint(loc, fmt, args);
    va_end(args);
}
