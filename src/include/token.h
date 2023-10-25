#ifndef nevec_tokens_h
#define nevec_tokens_h

typedef enum {
    EXT, FN, FOR, IF, IN, 
    LET, MUT, SELF, STRUCT, WHILE,

    LPAREN, RPAREN, 
    LBRACE, RBRACE,  
    LBRACKET, RBRACKET,

    ASSIGN, PLUS, MINUS, MULTI, DIVIS,
    AND, OR, EQUAL, NEQUAL, GT, 
    GTE, LT, LTE, EXCLAM,

    IDENTIFIER, INTEGER, FLOAT, STRING, CHARACTER, 

    TFALSE, NIL, TTRUE,
    I8, U8,
    I16, U16,
    I32, U32, F32,
    I64, U64, F64,
    I128, U128, 
    ISIZE, USIZE,
    BOOL, CHAR, STR, 

    SEMICOLON, COLON, COMMA, DOT, DOTDOT,
    QUESTION, PIPE, AMPERSAND,

    ERR, END
} TokenType;

typedef struct {
    int line;
    int col;

    int length;
} Loc;

typedef struct {
    char *start;
    TokenType type;
    Loc loc;
} Token;

Loc newLoc();
Token newToken(char *start, TokenType type, Loc loc);

#endif
