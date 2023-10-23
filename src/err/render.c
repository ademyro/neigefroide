#include <stdarg.h>
#include <stdio.h>

#include "render.h"

static void write(const char *s) {
    fprintf(stderr, "%s", s);
}

static void endFormat() {
    fprintf(stderr, RESET "\n");
}

void renderSimpleErr(const char *fmt, va_list args) {
    write(RED "error" WHITE ": ");

    vfprintf(stderr, fmt, args);
    
    endFormat();
}
