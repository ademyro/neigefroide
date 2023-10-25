`#define READ_BIN "rb"`
* Convenient `accessMode` macro for `fopen().` 

`int main(int argc, char **argv)`
* Program’s entry point.
    * Calls `cliErr(...)` and exits if `argc < 2.`
    * Calls `compile(fname)` if `argc == 2.`

`static char *readFile(const char *fname)`
* Returns a `char *` pointer to the first character of the file’s content.
    * Returns `NULL` if the file cannot be opened.
    * Returns `NULL` if there’s not enough memory to read `fname.`

`static void compile(const char *fname)`
* **Temporary.**
* Pools for the next token and prints it until we reach an `END` (i.e. `EOF`)
token.

