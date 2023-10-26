#include "token.h"

Loc newLoc() {
    Loc loc = { .line = 1, .col = 1, .length = 0 };
    return loc;
}

Token newToken(char *start, TokenType type, Loc loc) {
    Token token = { .start = start, .type = type, .loc = loc };
    return token;
}
