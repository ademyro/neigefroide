#include <stdlib.h>

#include "ast.h"
#include "pretty.h"
#include "token.h"

static void freeBody(AstBody *body) {
    body->size = 0;
    body->cap = 0;
    body->loc = newLoc();

    free(body->nodes);
    free(body);
}

static void freeFn(AstFn *fn) {
    freeBody(fn->body);      

    fn->loc = newLoc();

    free(fn);
}

static void freeRet(AstRet *ret) {
    freeAst(ret->expr);

    ret->loc = newLoc();

    free(ret);
}

static void freeBinOp(AstBinOp *binOp) {
    freeAst(binOp->left);
    freeAst(binOp->right);

    binOp->loc = newLoc();
    
    free(binOp);
}

static void freeUnOp(AstUnOp *unOp) {
    freeAst(unOp->child);

    unOp->loc = newLoc();

    free(unOp);
}

void freeAst(Ast *ast) {
    switch (ast->type) {
        case NODE_BODY:
            freeBody(ast->as.body); 
            break;

        case NODE_FN:
            freeFn(ast->as.fn);
            break;
        
        case NODE_RET:
            freeRet(ast->as.ret);
            break;

        case NODE_BINOP:
            freeBinOp(ast->as.binOp);
            break;

        case NODE_UNOP:
            freeUnOp(ast->as.unOp);
            break;

        case NODE_INT:
            free(ast->as.intNode);
            break;

        case NODE_FLOAT:
            free(ast->as.floatNode);
            break;

        default:
            ;
    }

    free(ast);
}
