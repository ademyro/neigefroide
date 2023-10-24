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

`static void cat(const char *fname)`
* **Temporary.**
* Prints the contents of `fname` to `stderr.` 
    * Exits if `contents == NULL.`

`static void compile(const char *fname)`
* **Temporary.**
* Calls `cat(fname).`

