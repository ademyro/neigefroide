`#define RED "\e[1;31m"`
* Makes output bold red.

`#define GREEN "\e[1;32m"`
* Makes output bold green.

`#define YELLOW "\e[1;33m"`
* Makes output bold yellow.

`#define BLUE "\e[1;34m"`
* Makes output bold blue.

`#define MAGENTA "\e[1;35m"`
* Makes output bold magenta.

`#define WHITE "\e[1;37m"`
* Makes output bold.

`#define RESET "\e[0m"`
* Makes output look regular again.

`void renderErrMsg(const char *fmt, va_list args)`
* Displays a simple error to `stderr` using `write()` and `vfprintf().`  It 
then calls `endFormat().`
    * `error: could not open file test.nv.`

`void renderLocus(const char *fname, Loc loc)`
* Displays the error’s location.
    * `in: test.nv:17:9`

`void renderLine(FILE *file, int line)`
* Prints a few pipes `|` here and there for nice formatting.  It then looks for 
the line `line` in `file` and displays it to `stderr.` 

`void highlightErr(Loc loc, const char *fmt, va_list args)`
* Displays circumflexes `^` beneath the error, along with a message (that 
being `fmt` and `...`)

`void renderHint(const char *fmt, va_list args)`
* Lower-level helper for `err.showHint().`

`static void write(const char *s)`
* Outputs `s` to `stderr.` 

`static void writef(const char *fmt, ...)`
* Accepts a format string and displays it to `stderr` through `vfprintf().`
(I’ll really do anything to avoid writing `fprintf(stderr, ...)` more than 
twice lmao.)

`static void endFormat()`
* Disables fancy formatting and returns to normal.
