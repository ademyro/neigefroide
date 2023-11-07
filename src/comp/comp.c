#include <stdlib.h>

#include "ast.h"
#include "comp.h"
#include "err.h"
#include "parser.h"

void compile(const char *fname, char *src) {
    initErrMod(fname, src);

    ParseRes res = parse(src);

    if (!res.success) {
        cliErr("parsing failed; stopping.");
        free(res.ast);

        return;
    }

    free(res.ast);
}
