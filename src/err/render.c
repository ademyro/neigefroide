#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "render.h"

static int digitsIn(int n) {
    return floor(log10(abs(n)) + 1);
}

static void write(const char *s) {
    fprintf(stderr, "%s", s);
}

static void writef(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

static void endFormat() {
    write(RESET "\n");
}

static void renderRawLine(char *src, int line) {
    int currLine = 1; 
    char *curr = src;

    while (currLine != line) {
        curr++;

        if (*curr == '\n') {
            currLine++;
        }
    }

    // advance past the '\n'
    curr++;

    while (*curr != '\n' && *curr != '\0') {
        fputc(*curr, stderr); 
        curr++;
    }
}

void renderErrMsg(const char *fmt, va_list args) {
    write(RED "error" WHITE ": ");

    vfprintf(stderr, fmt, args);
    
    endFormat();
}

void renderLocus(const char *fname, Loc loc) {
    write(BLUE "   in" WHITE ": ");

    writef("%s:%d:%d", fname, loc.line, loc.col);

    endFormat();
}

void renderLine(char *src, int line) {
    int lineDigits = digitsIn(line);

    writef(BLUE "%*s | \n", lineDigits, "");
    writef("%d | " RESET, line); 

    renderRawLine(src, line);

    endFormat();
}

void highlightErr(Loc loc, const char *fmt, va_list args) {
    int lineDigits = digitsIn(loc.line);

    writef(BLUE "%*s |", lineDigits, "");
    writef("%*s", loc.col, "");

    for (int i = 0; i < loc.length; i++) {
        fputc('^', stderr);
    }

    fputc(' ', stderr);

    vfprintf(stderr, fmt, args);

    endFormat();
}

void renderHint(Loc loc, const char *fmt, va_list args) {
    int lineDigits = digitsIn(loc.line);     

    writef(BLUE "%*s -> 💡 ", lineDigits, "");
    
    vfprintf(stderr, fmt, args);

    endFormat();
}
