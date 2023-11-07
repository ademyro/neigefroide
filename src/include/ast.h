#ifndef nevec_ast_h
#define nevec_ast_h

#include "core.h"
#include "token.h"
#include "type.h"

typedef enum {
    NODE_BODY,
    NODE_PARAM,
    NODE_FN,
    NODE_RET,
    NODE_BIN,
    NODE_UNOP,
    NODE_INT,
    NODE_FLOAT
} NodeType;

// Declarations.
typedef struct Ast Ast;

typedef struct {
    size_t size;
    size_t cap;

    Ast **nodes;

    Loc loc;
} AstBody;

typedef struct {
    Token name;
    Type type;

    Loc loc;
} AstParam;

typedef struct {
    Token name;
    AstParam *params;
    Type returnType;

    AstBody *body;

    Loc loc;
} AstFn;

typedef struct {
    Ast *expr;

    Loc loc;
} AstRet;

typedef struct {
    Ast *left; 
    Token op;
    Ast *right;

    Loc loc;
} AstBinOp;

typedef struct {
    Token op;
    Ast *child;

    Loc loc;
} AstUnOp;

typedef struct {
    NumericType bitWidth;     

    union {
        int8_t int8;
        int16_t int16;
        int int32;
        int64_t int64;
    } as;

    Loc loc;
} AstInt;

typedef struct {
    bool isDoublePrecise;  

    union {
        float singlePrecise;
        double doublePrecise;
    } as;

    Loc loc;
} AstFloat;

struct Ast {
    NodeType type;

    union {
        AstFn *fn;
        AstParam *param;
        AstBody *body;
        AstRet *ret;
        AstBinOp *binOp;
        AstUnOp *unOp;
        AstInt *intNode;
        AstFloat *floatNode;
    } as;

    Loc loc;
};

Ast *newNode(); 
AstFn *newFn();
AstRet *newRet();
AstBody *newBody();
AstBinOp *newBinOp();
AstUnOp *newUnOp();
AstInt *newInt();
AstFloat *newFloat();
void addToBody(AstBody *body, Ast *node);
void tidyBody(AstBody *body);
Ast *wrapFn(AstFn *node);
Ast *wrapBody(AstBody *node);
Ast *wrapRet(AstRet *node);
Ast *wrapBinOp(AstBinOp *node);
Ast *wrapUnOp(AstUnOp *node);
Ast *wrapInt(AstInt *node);
Ast *wrapFloat(AstFloat *node);
#endif
