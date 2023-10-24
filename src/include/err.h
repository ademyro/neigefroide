#ifndef nevec_error_h
#define nevec_error_h

typedef enum {
    UNEXPECTED_CHAR
} Err;

void cliErr(const char *fmt, ...);

#endif
