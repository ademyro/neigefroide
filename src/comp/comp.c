#include <stdlib.h>

#include "ast.h"
#include "comp.h"
#include "err.h"
#include "parser.h"
#include "pretty.h"

void compile(const char *fname, char *src) {
    initErrMod(fname, src);

    ParseRes res = parse(src);

    if (!res.success) {
        cliErr("parsing failed; stopping.");
        freeAst(res.ast);

        return;
    }

    freeAst(res.ast);
}
