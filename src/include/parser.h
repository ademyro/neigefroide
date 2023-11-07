#ifndef nevec_parser_h
#define nevec_parser_h

#include "ast.h"
#include "core.h"
#include "lexer.h"
#include "token.h"

typedef struct {
    Token prev;
    Token curr;

    bool hadErr; 

    AstFn *currFn;

    Lexer *lexer;
} Parser;

typedef struct {
    Ast *ast;
    bool success;
} ParseRes;

ParseRes parse(char *src);

#endif
