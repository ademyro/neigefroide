#ifndef nevec_type_h
#define nevec_type_h

typedef enum {
    ARCH,
    BIT8,
    BIT16,
    BIT32,
    BIT64
} NumericType;

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STR,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_STRUCT
} TypeType;

typedef struct {
    TypeType type;

    union {
        char *typeName;
        
        struct {
            bool isSigned;
            NumericType bitWidth;
        } integer;

        bool isDoublePrecise;
    };
} Type;

#endif
