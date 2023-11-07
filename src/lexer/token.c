#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "token.h"

Loc newLoc() {
    Loc loc = { .line = 1, .col = 1, .length = 0 };
    return loc;
}

Loc mergeLocs(Loc left, Loc right) {
    int line = (left.line + right.line) / 2;     

    int col = (int)fmin(left.col, right.col);

    int length = abs(left.col - right.col);

    Loc loc = { .line = line, .col = col, .length = length };
    return loc;
}

Token newToken(char *start, TokenType type, Loc loc) {
    Token token = { .start = start, .type = type, .loc = loc };
    return token;
}

char *copyLexeme(Token token) {
    size_t length = (size_t)token.loc.length;

    char *lexeme = malloc(length + 1);
    memcpy(lexeme, token.start, length);
    lexeme[length] = '\0';

    return lexeme;
}
