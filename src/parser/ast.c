#include <stdlib.h>

#include "ast.h"
#include "mem.h"

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

Ast *newNode() {
    Ast *node = malloc(sizeof (*node));
    return node;
}

AstFn *newFn() {
    AstFn *fn = malloc(sizeof (*fn));    
    return fn;
}

AstRet *newRet() {
    AstRet *ret = malloc(sizeof (*ret));
    return ret;
}

AstBody *newBody() {
    AstBody *body = malloc(sizeof (*body));

    body->size = 0;
    body->cap = 1;
    body->nodes = ALLOC_ARR(Ast *);

    return body;
}

AstBinOp *newBinOp() {
    AstBinOp *binOp = malloc(sizeof (*binOp));
    return binOp;
}

AstUnOp *newUnOp() {
    AstUnOp *unOp = malloc(sizeof (*unOp));
    return unOp;
}

AstInt *newInt() {
    AstInt *intNode = malloc(sizeof (*intNode));
    return intNode;
}

AstFloat *newFloat() {
    AstFloat *floatNode = malloc(sizeof (*floatNode));
    return floatNode;
}

void addToBody(AstBody *body, Ast *node) {
    if (body->size == body->cap) {
        size_t newCap = GROW_CAP(body->cap);
        body->cap = newCap;

        body->nodes = GROW_ARR(Ast *, body->nodes, newCap); 
    }

    body->nodes[body->size++] = node;
}

void tidyBody(AstBody *body) {
    if (body->cap == body->size) {
        return;
    }

    body->cap = body->size;

    // we’re actually shrinking it here
    body->nodes = GROW_ARR(Ast *, body->nodes, body->size);
}

Ast *wrapFn(AstFn *node) {
    Ast *wrapper = newNode();
    wrapper->as.fn = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_FN;

    return wrapper;
}

Ast *wrapBody(AstBody *node) {
    Ast *wrapper = newNode();
    wrapper->as.body = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_BODY;
    
    return wrapper;
}

Ast *wrapRet(AstRet *node) {
    Ast *wrapper = newNode();
    wrapper->as.ret = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_RET;

    return wrapper;
}

Ast *wrapBinOp(AstBinOp *node) {
    Ast *wrapper = newNode();
    wrapper->as.binOp = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_BINOP;

    return wrapper;
}

Ast *wrapUnOp(AstUnOp *node) {
    Ast *wrapper = newNode();
    wrapper->as.unOp = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_UNOP;

    return wrapper;
}

Ast *wrapInt(AstInt *node) {
    Ast *wrapper = newNode();
    wrapper->as.intNode = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_INT;

    return wrapper;
}

Ast *wrapFloat(AstFloat *node) {
    Ast *wrapper = newNode();
    wrapper->as.floatNode = node;
    wrapper->loc = node->loc;
    wrapper->type = NODE_FLOAT;

    return wrapper;
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
