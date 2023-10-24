`enum Err`
* `UNEXPECTED_CHARACTER`
    * Whenever an unexpected character is encountered, such as `×` or `↑,` this
    error type will be reported.

`void cliErr(const char *fmt, ...)`
* Creates a `va_list` out of `fmt` and `...` and calls `renderSimpleErr().` 
