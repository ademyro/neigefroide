#include <stdlib.h>

#include "ast.h"
#include "core.h"
#include "err.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"

static void initParser(Parser *parser, char *src) {
    parser->hadErr = false;
    parser->currFn = NULL;

    Lexer *lexer = malloc(sizeof (*lexer));
    initLexer(lexer, src);

    parser->lexer = lexer;
}

static void freeParser(Parser *parser) {
    freeLexer(parser->lexer);
    free(parser->lexer);
}

static void reportSimpleErr(Loc loc, const char *msg) {
    reportErrAt(loc, msg);
    showOffendingLine(loc, msg);
} 

static void lexerErr(Token err) {
    char start = *err.start;

    if (start == '"') {
        reportErrAt(err.loc, "🔌 unterminated string");
        showOffendingLine(err.loc, "... until end of file");
        showHint("you might want to insert a ‘\"’ where you missed it");
    } else {
        reportErrAt(err.loc, "🧐 unexpected character");
        showOffendingLine(err.loc, "what is this?");
        showHint("‘%c’ isn't recognized as a valid token", start);
    }
}

static void advance(Parser *parser) {
    Lexer *lexer = parser->lexer;
    parser->prev = parser->curr;

    while (true) {
        parser->curr = nextToken(lexer);

        if (parser->curr.type != ERR) {
            break;
        }

        parser->hadErr = true;
        lexerErr(parser->curr);
    }
}

static bool atEnd(Parser *parser) {
    Token curr = parser->curr;
    return curr.type == END;
}

static bool match(Parser *parser, TokenType type) {
    Token curr = parser->curr;

    if (curr.type != type) {
        return false; 
    }

    advance(parser);
    return true;
}

static bool matchEither(Parser *parser, TokenType first, TokenType second) {
    return match(parser, first) || match(parser, second);
}

static Token expect(Parser *parser, TokenType type, const char *msg) {
    Token curr = parser->curr;

    if (curr.type != type) {
        reportSimpleErr(curr.loc, msg);
    }

    advance(parser);
    return parser->prev;
}

// forward declarations; we’re working with recursive functions.
static Ast *parseDecl(Parser *parser);
static AstFn *parseFn(Parser *parser);
static Ast *parseStmt(Parser *parser);
static AstBody *parseBlock(Parser *parser);
static AstRet *parseRet(Parser *parser);
static Ast *parseExpr(Parser *parser);
// will add `parseAssign`
static Ast *parseOr(Parser *parser);
static Ast *parseAnd(Parser *parser);
static Ast *parseEq(Parser *parser);
static Ast *parseComp(Parser *parser);
static Ast *parseTerm(Parser *parser);
static Ast *parseFactor(Parser *parser);
static Ast *parseUnary(Parser *parser);
// will add `call`
static Ast *parsePrimary(Parser *parser);
static AstInt *parseInt(Parser *parser);
static AstFloat *parseFloat(Parser *parser);

static Ast *parseDecl(Parser *parser) {
    advance(parser);
    Token prev = parser->prev;

    switch (prev.type) {
        case FN: {
            AstFn *fn = parseFn(parser);
            return wrapFn(fn);
        }

        default: {
            Ast *stmt = parseStmt(parser);
            return stmt;
        }
    }
}

static AstFn *parseFn(Parser *parser) {
    AstFn *fn = newFn();

    Token name = expect(parser, IDENTIFIER, "🪪 expected an identifier");

    expect(parser, LPAREN, "📎 expected ‘(’");
    
    // TODO: parameters.
    
    Token paren = expect(parser, RPAREN, "📎 expected ‘)’");

    expect(parser, LBRACE, "⛓️ expected ‘{’");

    Loc loc = mergeLocs(name.loc, paren.loc);

    fn->name = name;
    fn->loc = loc;

    parser->currFn = fn;

    AstBody *body = parseBlock(parser);
    
    fn->body = body;

    return fn;
}

static Ast *parseStmt(Parser *parser) {
    Token curr = parser->curr;

    switch (curr.type) {
        case LBRACE: {
            advance(parser);

            AstBody *body = parseBlock(parser);
            return wrapBody(body);
        }

        case RETURN: {
            advance(parser);

            AstRet *ret = parseRet(parser);
            return wrapRet(ret); 
        }

        default: {
            Ast *expr = parseExpr(parser);

            expect(parser, SEMICOLON, "🔧 missing semicolon");
            
            return expr;
        }
    }
}

static AstBody *parseBlock(Parser *parser) {
    AstBody *body = newBody();

    while (!match(parser, RBRACE)) {
        Ast *node = parseDecl(parser); 
        addToBody(body, node);
    }

    tidyBody(body);

    return body;
}

static AstRet *parseRet(Parser *parser) {
    Ast *expr = parseExpr(parser);
    
    expect(parser, SEMICOLON, "🔧 missing semicolon");

    AstRet *ret = newRet();
    ret->expr = expr;

    return ret;
}

static Ast *parseExpr(Parser *parser) {
    // TODO!
    Ast *or = parseOr(parser);
    return or;
}

static Ast *parseOr(Parser *parser) {
    // TODO!
    return parseAnd(parser);
}

static Ast *parseAnd(Parser *parser) {
    return parseEq(parser);
}

static Ast *parseEq(Parser *parser) {
    // TODO!
    return parseComp(parser);
}

static Ast *parseComp(Parser *parser) {
    // TODO!
    return parseTerm(parser);
}

static Ast *parseTerm(Parser *parser) {
    Ast *left = parseFactor(parser);

    while (matchEither(parser, PLUS, MINUS)) {
        Token op = parser->prev; 
        Ast *right = parseFactor(parser);
        AstBinOp *binOp = newBinOp();

        binOp->left = left;
        binOp->op = op;
        binOp->right = right;

        left = wrapBinOp(binOp);
    }

    return left;
}

static Ast *parseFactor(Parser *parser) {
    Ast *left = parseUnary(parser);

    while (matchEither(parser, MULTI, DIVIS)) {
        Token op = parser->prev; 
        Ast *right = parseUnary(parser);
        AstBinOp *binOp = newBinOp();

        binOp->left = left;
        binOp->op = op;
        binOp->right = right;

        left = wrapBinOp(binOp);
    }

    return left;
}

static Ast *parseUnary(Parser *parser) {
    if (matchEither(parser, MINUS, EXCLAM)) {
        AstUnOp *unOp = newUnOp();    
        Token op = parser->prev;

        Ast *child = parseUnary(parser);

        unOp->op = op;
        unOp->child = child;
        unOp->loc = mergeLocs(op.loc, child->loc);
        return wrapUnOp(unOp);
    }

    return parsePrimary(parser);
}

static Ast *parsePrimary(Parser *parser) {
    Token curr = parser->curr;

    switch (curr.type) {
        case INTEGER: {
            AstInt *intNode = parseInt(parser);
            return wrapInt(intNode);
        }

        case FLOAT: {
            AstFloat *floatNode = parseFloat(parser);
            return wrapFloat(floatNode);
        }

        default: {
            Loc here = curr.loc;

            reportErrAt(here, "🤔 unexpected token");
            showOffendingLine(here, "was looking for a value (like an int)");
            showHint("you might’ve made a typo or forgotten a comma."); 
            showHint("here's an example of a well-formed expression:");
            suggestExample(here, "    let x = y + z - 42;");

            // not sure what to return here  
            Ast *placeholder = newNode();
            return placeholder;
        }
    }
}

static AstInt *parseInt(Parser *parser) {
    AstInt *intNode = newInt();

    Token intToken = parser->curr;
    int tokenLength = intToken.loc.length;
    char *lexeme = copyLexeme(intToken);

    if (tokenLength <= DIGITS_IN_I32) {
        intNode->bitWidth = BIT32; 
        intNode->as.int32 = atoi(lexeme);
    } else {
        intNode->bitWidth = BIT64;
        intNode->as.int64 = atoll(lexeme);
    }

    advance(parser);
    free(lexeme);

    intNode->loc = intToken.loc;
    return intNode;
}

static AstFloat *parseFloat(Parser *parser) {
    AstFloat *floatNode = newFloat();  

    Token floatToken = parser->curr; 
    char *lexeme = copyLexeme(floatToken);

    advance(parser);

    floatNode->isDoublePrecise = match(parser, F32);

    if (floatNode->isDoublePrecise) {
        floatNode->as.doublePrecise = strtod(lexeme, NULL);
    } else {
        floatNode->as.singlePrecise = strtof(lexeme, NULL);
    }

    free(lexeme);
    
    floatNode->loc = floatToken.loc;
    return floatNode;
}

ParseRes parse(char *src) {
    Parser parser;
    initParser(&parser, src);

    advance(&parser);

    AstBody *body = newBody();
    
    while (!atEnd(&parser)) {
        Ast *node = parseDecl(&parser);
        addToBody(body, node);
    }

    tidyBody(body);

    Ast *ast = wrapBody(body);

    bool success = !parser.hadErr;
    ParseRes res = { .ast = ast, .success = success };

    freeParser(&parser);

    return res;
}
