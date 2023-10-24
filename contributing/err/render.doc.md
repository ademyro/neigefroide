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

`void renderSimpleErr(const char *fmt, va_list args)`
* Displays a simple error to `stderr` using `write()` and `vfprintf().`  It 
then calls `endFormat().`
    * `error: could not open file test.nv.`

`static void write(const char *s)`
* Outputs `s` to `stderr.` 

`static void endFormat()`
* Disables fancy formatting and returns to normal.
