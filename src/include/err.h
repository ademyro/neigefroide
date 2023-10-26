#ifndef nevec_error_h
#define nevec_error_h

#include <stdio.h>

#include "token.h"

typedef struct {
    const char *fname;
    char *src;
} ErrMod;

void initErrMod(const char *fname, char *src);
void cliErr(const char *fmt, ...);
void reportErrAt(Loc loc, const char *fmt, ...);
void showOffendingLine(Loc loc, const char *fmt, ...);
void showHint(Loc loc, const char *fmt, ...);

#endif
