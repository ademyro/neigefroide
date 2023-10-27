#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "err.h"
#include "lexer.h"
#include "token.h"

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

static void compile(const char *fname) {
    char *contents = readFile(fname);
    initErrMod(fname, contents);

    Lexer lexer;
    initLexer(&lexer, contents);
    Token firstToken = nextToken(&lexer);

    while (true) {
        Token token = nextToken(&lexer);

        printf("%2d:%2d %2d ", token.loc.line, token.loc.col, token.type);
        printf("'%.*s'\n", token.loc.length, token.start);

        if (token.type == END) {
            reportErrAt(token.loc, "😱 resource leak (test)");
            showOffendingLine(token.loc, "end of scope, ‘buf’ not freed");
            showNote(firstToken.loc, "‘buf’ declared here");
            showHint(token.loc, "free ‘buf’ before exiting the scope");
            suggestFix(token.loc, "buf.free();");
            break;
        }

        // Hey, that’s temporary okay?
        if (token.type == ERR) {
            reportErrAt(token.loc, "🧐 unexpected character");
            showOffendingLine(token.loc, "what is this?");
            showHint(token.loc, "‘%c’ isn’t recognized as a valid token", 
                     *token.start);
        }
    }

    free(contents);
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
