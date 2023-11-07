#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "render.h"

static int lineDigits = 1;

static int digitsIn(int n) {
    return (int)floor(log10(abs(n)) + 1);
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

static char *findLine(char *src, int line) {
    if (line == 1) {
        // for some reason, the cleanest approach:
        // if (*curr == '\n') {
        //     currLine++;
        //     // advance past the '\n'
        //     curr++;
        // }
        // causes my code to segfault when currLine = 46, according to gdb
        // (???) here’s the output
        // Program received signal SIGSEGV, Segmentation fault.
        // 0x0000555555555e63 in findLine (...) at src/err/render.c:37
        // 37              if (*curr == '\n') {
        // (gdb) p currLine
        // $1 = 46
        // i don’t know what’s going on and i don’t want to dig deeper.
        return src;
    }

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

    return curr;
}

static void writeFrom(char *src, int until) {
    int col = 1;
    char *curr = src;

    while (col <= until) {
        fputc(*curr, stderr); 
        curr++;
        col++;
    }
}

static void writeLinePipes(int line) {
    writef(BLUE "%*s | \n", lineDigits, "");
    writef("%*d | " RESET, lineDigits, line); 
}

static void highlight(int length, char highlighter) {
    for (int i = 0; i < length; i++) {
        fputc(highlighter, stderr);
    } 

    fputc(' ', stderr);
}

void setLine(int line) {
    lineDigits = digitsIn(line);
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

void renderLine(char *src, Loc loc) {
    int line = loc.line;
    char *lineStart = findLine(src, line);
    int lineEnd = (int)strcspn(lineStart, "\n");

    writeLinePipes(line);

    int col = loc.col - 1;
    int errEnd = col + loc.length;

    writeFrom(lineStart, col);
    write(RED);
    writeFrom(lineStart + col, loc.length);
    write(RESET);
    writeFrom(lineStart + errEnd, lineEnd - errEnd);
    
    endFormat();
}

void highlightErr(Loc loc, const char *fmt, va_list args) {
    writef(BLUE "%*s |", lineDigits, "");
    writef("%*s" RED, loc.col, "");

    highlight(loc.length, '^');

    vfprintf(stderr, fmt, args);

    endFormat();
}

void highlightNote(Loc loc, const char *fmt, va_list args) {
    writef(BLUE "%*s |", lineDigits, "");
    writef("%*s", loc.col, "");

    highlight(loc.length, '-');

    vfprintf(stderr, fmt, args);

    endFormat();
}

void highlightChange(Loc loc, const char *fmt, va_list args) {
    int changeLength = vsnprintf(NULL, 0, fmt, args);
    
    writef(BLUE "%*s |", lineDigits, ""); 
    writef("%*s" GREEN, loc.col, "");

    highlight(changeLength, '+');

    endFormat();
}

void renderHint(const char *fmt, va_list args) {
    writef(BLUE "%*s -> 💡 ", lineDigits, "");
    
    vfprintf(stderr, fmt, args);
    
    endFormat();
}

void renderModifiedLine(char *src, Loc loc, const char *fmt, va_list args) {
    int line = loc.line;
    char *lineStart = findLine(src, line);
    int lineEnd = (int)strcspn(lineStart, "\n\0");

    writeLinePipes(line);

    int col = loc.col;

    writeFrom(lineStart, col);
    write(GREEN);
    vfprintf(stderr, fmt, args);
    write(RESET);
    writeFrom(lineStart + col, lineEnd);

    endFormat();
}

void renderFix(Loc loc, const char *fmt, va_list args) {
    writeLinePipes(loc.line);

    write(GREEN);
    vfprintf(stderr, fmt, args);
    highlightChange(loc, fmt, args);

    endFormat();
}

void renderFmtLine(Loc loc, const char *fmt, va_list args) {
    writeLinePipes(loc.line);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    
    endFormat();
}
