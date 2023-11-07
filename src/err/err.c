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
    setLine(loc.line);

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
    
    renderLine(src, loc); 

    va_start(args, fmt);
    highlightErr(loc, fmt, args);
    va_end(args); 
}

void showNote(Loc loc, const char *fmt, ...) {
    char *src = mod.src;
    va_list args;

    renderLine(src, loc);

    va_start(args, fmt);
    highlightNote(loc, fmt, args);
    va_end(args);
}

void showHint(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    renderHint(fmt, args);
    va_end(args);
}

void suggestFix(Loc fixLoc, const char *fmt, ...) {
    char *src = mod.src;
    va_list args;

    va_start(args, fmt);
    renderModifiedLine(src, fixLoc, fmt, args);
    highlightChange(fixLoc, fmt, args);
    va_end(args);
}

void suggestFixAbove(int line, const char *fmt, ...) {
    char *src = mod.src;
    va_list args;

    Loc fixLoc = newLoc();
    fixLoc.line = line;

    Loc lineBelow = newLoc();
    lineBelow.line = line + 1;

    va_start(args, fmt);
    renderFix(fixLoc, fmt, args);
    renderLine(src, lineBelow);
    va_end(args);
}

void suggestExample(Loc loc, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    renderFmtLine(loc, fmt, args);
    va_end(args);
}
