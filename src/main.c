#include <stdio.h>
#include <stdlib.h>

#include "err.h"

#define READ_BIN "rb"

static char *readFile(const char *fname) {
    FILE *file = fopen(fname, READ_BIN); 

    if (file == NULL) {
        cliErr("could not open file %s.", fname);    
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);

    char *buf = malloc(fsize + 1);
    size_t end = fread(buf, sizeof (char), fsize, file);

    if (buf == NULL) {
        cliErr("not enough memory to read %s.", fname);
        return NULL;
    }

    buf[end] = '\0';

    fclose(file);

    return buf;
}

static void cat(const char *fname) {
    char *contents = readFile(fname);      

    if (contents == NULL) {
        exit(1);
    }

    fprintf(stderr, "%s", contents);
    free(contents);
}

static void compile(const char *fname) {
    // Temporary code to get the compiler driving.
    cat(fname);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cliErr("too few arguments; aborting.");
        exit(1);
    } else if (argc == 2) {
        const char *fname = argv[1];
        compile(fname);
    }
}
