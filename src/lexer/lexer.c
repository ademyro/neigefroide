#include <string.h>

#include "core.h"
#include "lexer.h"
#include "token.h"

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

static bool atEnd(Lexer *lexer) {
    return *lexer->curr == '\0';
}

static int currTokenLength(Lexer *lexer) {
    return (int)(lexer->curr - lexer->start);
}

static char peek(Lexer *lexer) {
    return *lexer->curr;
}

static char peekNext(Lexer *lexer) {
    if (atEnd(lexer)) {
        return '\0';
    }

    return lexer->curr[1];
}

static bool match(Lexer *lexer, char c) {
    if (atEnd(lexer)) {
        return false;
    }

    if (peek(lexer) != c) {
        return false;
    }

    lexer->curr++;
    return true;
}

static bool notMatch(Lexer *lexer, char c) {
    return peek(lexer) != c && !atEnd(lexer);
}

static bool matchSeq(Lexer *lexer, const char *seq) {
    if (atEnd(lexer)) {
        return false;
    }

    // We could check whether ‘seq’ is actually two characters long, but since 
    // we’ll be working with constant string literals, we might not need it.
    return peek(lexer) == seq[0] && peekNext(lexer) == seq[1];
}

static char advance(Lexer *lexer) {
    lexer->curr++; 
    return lexer->curr[-1];
}

static void synchronize(Lexer *lexer) {
    lexer->loc.col += currTokenLength(lexer);    
    lexer->start = lexer->curr;
}


static void newline(Lexer *lexer) {
    synchronize(lexer);
    lexer->loc.line++;
    lexer->loc.col = 1;
}

static Token makeToken(Lexer *lexer, TokenType type) {
    Loc copiedLoc = lexer->loc;
    copiedLoc.length = currTokenLength(lexer);

    Token token = newToken(lexer->start, type, copiedLoc); 

    return token;
}

static Token unexpectedChar(Lexer *lexer) {
    return makeToken(lexer, ERR);
}

static void multilineComment(Lexer *lexer) {
    int depth = 1;

    while (!atEnd(lexer) && depth > 0) {
        advance(lexer);
        lexer->loc.col++;

        if (match(lexer, '\n')) {
            newline(lexer);
        }
        
        if (matchSeq(lexer, "/*")) {
            depth++; 
        } else if (matchSeq(lexer, "*/")) {
            depth--;
        }
    }
}

static void skipWhitespace(Lexer *lexer) {
    while (true) {
        char c = peek(lexer);

        switch (c) {
            case '\n':
                advance(lexer);
                newline(lexer);
                break;

            case ' ':
            case '\t':
            case '\r':
                advance(lexer);
                break;

            case '/':
                if (peekNext(lexer) == '/') {
                    while (notMatch(lexer, '\n')) {
                        advance(lexer);
                    }
                } else if (peekNext(lexer) == '*') {
                    multilineComment(lexer);
                } else {
                    return;
                }
                
                break;

            default:
                return;
        }
    }
}

static TokenType checkKeyword(Lexer *lexer, int start, size_t length, 
                              const char *expected, TokenType type) {
    int identifierLength = start + (int)length;

    if (currTokenLength(lexer) == identifierLength && 
        memcmp(lexer->start + start, expected, length) == 0) {
        return type;
    }

    return IDENTIFIER;
}

static TokenType checkForF(Lexer *lexer) {
    if (currTokenLength(lexer) > 1) {
        switch (lexer->start[1]) {
            case '3':
                return checkKeyword(lexer, 2, 1, "2", F32);

            case '6':
                return checkKeyword(lexer, 2, 1, "4", F64);

            case 'a': 
                return checkKeyword(lexer, 2, 3, "lse", TFALSE);

            case 'o':
                return checkKeyword(lexer, 2, 1, "r", FOR);

            case 'n':
                return currTokenLength(lexer) == 2 ? FN : IDENTIFIER;
        }
    }

    return IDENTIFIER;
}

static TokenType checkForI(Lexer *lexer) {
    if (currTokenLength(lexer) > 1) {
        switch (lexer->start[1]) {
            case 'f':
                return currTokenLength(lexer) == 2 ? IF : IDENTIFIER;

            case 'n':
                return currTokenLength(lexer) == 2 ? IN : IDENTIFIER;

            case '8':
                return currTokenLength(lexer) == 2 ? I8 : IDENTIFIER;

            case '1':
                if (currTokenLength(lexer) == 3) {
                    return checkKeyword(lexer, 2, 1, "6", I16); 
                } else {
                    return checkKeyword(lexer, 2, 1, "28", I128);
                }

                break;

            case '3':
                return checkKeyword(lexer, 2, 1, "2", I32);

            case '6':
                return checkKeyword(lexer, 2, 1, "4", I64);

            case 's':
                return checkKeyword(lexer, 2, 3, "ize", ISIZE);
        }
    }

    return IDENTIFIER;
}

static TokenType checkForS(Lexer *lexer) {
    if (currTokenLength(lexer) > 1) {
        switch (lexer->start[1]) {
            case 'e':
                return checkKeyword(lexer, 2, 2, "lf", SELF);

            case 't':
                if (currTokenLength(lexer) == 3) {
                    return checkKeyword(lexer, 2, 1, "r", STR);
                } else {
                    return checkKeyword(lexer, 2, 4, "ruct", STRUCT);
                }

                break;
        } 
    }

    return IDENTIFIER;
}

static TokenType checkForU(Lexer *lexer) {
    if (currTokenLength(lexer) > 1) {
        switch (lexer->start[1]) {
            case '8':
                return currTokenLength(lexer) == 2 ? U8 : IDENTIFIER;

            case '1':
                if (currTokenLength(lexer) == 3) {
                    return checkKeyword(lexer, 2, 1, "6", U16); 
                } else {
                    return checkKeyword(lexer, 2, 1, "28", U128);
                }

                break;

            case '3':
                return checkKeyword(lexer, 2, 1, "2", U32);

            case '6':
                return checkKeyword(lexer, 2, 1, "4", U64);

            case 's':
                return checkKeyword(lexer, 2, 3, "ize", USIZE);
        }
    }

    return IDENTIFIER;
}

static TokenType identifierType(Lexer *lexer) {
    switch (*lexer->start) {
        case 'b':
            return checkKeyword(lexer, 1, 3, "ool", BOOL);

        case 'c':
            return checkKeyword(lexer, 1, 3, "har", CHAR);

        case 'e':
            return checkKeyword(lexer, 1, 2, "xt", EXT);

        case 'f':
            return checkForF(lexer);

        case 'i':
            return checkForI(lexer);

        case 'l':
            return checkKeyword(lexer, 1, 2, "et", LET);

        case 'm':
            return checkKeyword(lexer, 1, 2, "ut", MUT);

        case 'n':
            return checkKeyword(lexer, 1, 2, "il", NIL);

        case 'r':
            return checkKeyword(lexer, 1, 5, "eturn", RETURN);

        case 's':
            return checkForS(lexer);

        case 'u':
            return checkForU(lexer);

        case 'w':
            return checkKeyword(lexer, 1, 4, "hile", WHILE);
    }

    return IDENTIFIER;
}

static Token string(Lexer *lexer) {
    while (notMatch(lexer, '"')) {
        if (peek(lexer) == '\n') {
            // not using `newline()` because it synchronizes and discards
            // the string’s previous line.
            lexer->loc.line++;
            lexer->loc.col = 1;
        }

        advance(lexer);
    }

    if (atEnd(lexer)) {
        return unexpectedChar(lexer);
    }

    advance(lexer);
    return makeToken(lexer, STRING);
}

static Token number(Lexer *lexer) {
    TokenType numberType = INTEGER;

    while (isDigit(peek(lexer))) {
        advance(lexer);
    }

    if (peek(lexer) == '.' && isDigit(peekNext(lexer))) {
        numberType = FLOAT;
        advance(lexer);

        while (isDigit(peek(lexer))) {
            advance(lexer);
        }
    }

    return makeToken(lexer, numberType);
}

static Token identifier(Lexer *lexer) {
    while (isAlpha(peek(lexer)) || isDigit(peek(lexer))) {
        advance(lexer);
    }

    return makeToken(lexer, identifierType(lexer));
}

void initLexer(Lexer *lexer, char *src) {
    lexer->curr = src;
    lexer->start = src;

    lexer->loc = newLoc();
}

void freeLexer(Lexer *lexer) {
    lexer->loc = newLoc(); 
}

Token nextToken(Lexer *lexer) {
    skipWhitespace(lexer);
    synchronize(lexer);

    if (atEnd(lexer)) {
        return makeToken(lexer, END);
    }

    char c = advance(lexer);

    if (isAlpha(c)) {
        return identifier(lexer);
    }

    if (isDigit(c)) {
        return number(lexer);
    }

    switch (c) {
        case '(': return makeToken(lexer, LPAREN);
        case ')': return makeToken(lexer, RPAREN);
        case '{': return makeToken(lexer, LBRACE);
        case '}': return makeToken(lexer, RBRACE);
        case '[': return makeToken(lexer, LBRACKET);
        case ']': return makeToken(lexer, RBRACKET);
        case '+': return makeToken(lexer, PLUS);
        case '-': return makeToken(lexer, MINUS);
        case '*': return makeToken(lexer, MULTI);
        case '/': return makeToken(lexer, DIVIS);
        case '%': return makeToken(lexer, MODULO);
        case ':': return makeToken(lexer, COLON);
        case '?': return makeToken(lexer, QUESTION);
        case ',': return makeToken(lexer, COMMA);
        case ';': return makeToken(lexer, SEMICOLON);

        case '.':
            return makeToken(lexer, match(lexer, '.') ? DOTDOT : DOT);

        case '!':
            return makeToken(lexer, match(lexer, '=') ? NEQUAL : EXCLAM);

        case '=':
            return makeToken(lexer, match(lexer, '=') ? EQUAL : ASSIGN);

        case '>':
            return makeToken(lexer, match(lexer, '=') ? GTE : GT);

        case '<':
            return makeToken(lexer, match(lexer, '=') ? LTE : LT);

        case '&':
            return makeToken(lexer, match(lexer, '&') ? AND : AMPERSAND);

        case '|':
            return makeToken(lexer, match(lexer, '|') ? OR : PIPE);

        case '"':
            return string(lexer);
    }

    return unexpectedChar(lexer);
}
