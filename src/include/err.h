#ifndef nevec_error_h
#define nevec_error_h

typedef enum {
    UNEXPECTED_CHARACTER
} Err;

void cliErr(const char *fmt, ...);

#endif
