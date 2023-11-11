#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "ast.h"
#include "core.h"
#include "pretty.h"
#include "token.h"
#include "type.h"

static int indentation = 0;

static void write(const char *fmt, ...) {
    va_list args; 

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

static void newline() {
    write("\n%*s", indentation, "");
}

static void indent() {
    indentation += 2;
}

static void unindent() {
    indentation -= 2;
}

static void printBody(AstBody *body) {
    write("Body");
    indent();
    newline();

    for (size_t i = 0; i < body->size; i++) {
        prettyPrint(body->nodes[i]);
    } 
    
    unindent();
    newline();
}

static void printFn(AstFn *fn) {
    char *name = copyLexeme(fn->name);

    // [!] add arguments & return type later
    write("Fn %s [!]", name);
    indent(); 
    newline();

    printBody(fn->body);    

    unindent();
    newline();

    free(name);
}

static void printRet(AstRet *ret) {
    write("Ret");
    indent();
    newline();

    prettyPrint(ret->expr);

    unindent();
    newline();
}

static void printBinOp(AstBinOp *binOp) {
    char *op = copyLexeme(binOp->op);

    write("( ");
    
    prettyPrint(binOp->left);
    write(" %s ", op); 
    prettyPrint(binOp->right);

    write(" )");
    
    free(op);
}

static void printUnOp(AstUnOp *unOp) {
    char *op = copyLexeme(unOp->op);

    write("( ");

    write("%s ", op);
    prettyPrint(unOp->child); 

    write(" )");

    free(op);
}

static void printInt(AstInt *intNode) {
    write("Int");

    switch (intNode->bitWidth) {
        case ARCH: {
            size_t value = intNode->as.size;

            write("Size '%zu'", value);
            break;
        }
        
        case BIT8: {
            int8_t value = intNode->as.int8;

            write("8 '%hhd'", value);
            break;
        }
        
        case BIT16: {
            int16_t value = intNode->as.int16;
            
            write("16 '%hd'", value);
            break;
        }

        case BIT32: {
            int32_t value = intNode->as.int32;

            write("32 '%d'", value);
            break;
        }

        case BIT64: {
            int64_t value = intNode->as.int64;

            write("64 '%lld'", value);
            break;
        }
    }
}

static void printFloat(AstFloat *floatNode) {
    write("Float"); 

    if (floatNode->isDoublePrecise) {
        double value = floatNode->as.doublePrecise;

        write("64 '%lf'", value);
    } else {
        float value = floatNode->as.singlePrecise;

        write("32 '%f'", value);
    }
}

void prettyPrint(Ast *ast) {
    switch (ast->type) {
        case NODE_BODY:
            printBody(ast->as.body);
            break;

        case NODE_FN:
            printFn(ast->as.fn);
            break;

        case NODE_RET:
            printRet(ast->as.ret);
            break;

        case NODE_BINOP:
            printBinOp(ast->as.binOp);
            break;
        
        case NODE_UNOP:
            printUnOp(ast->as.unOp);
            break;

        case NODE_INT:
            printInt(ast->as.intNode);
            break;

        case NODE_FLOAT:
            printFloat(ast->as.floatNode);
            break;

        default:
            ;
    }
}
