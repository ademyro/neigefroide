`void initErrMod(const char *fname, char *src)`
* Initializes `err.c`’s file-local `ErrMod mod` struct given the arguments.

`void cliErr(const char *fmt, ...)`
* Creates a `va_list` out of `fmt` and `...` and calls `renderSimpleErr().` 

`void reportErrAt(Loc loc, const char *fmt, ...)`
* Displays the error’s header and location.

`void showOffendingLine(Loc loc, const char *fmt, ...)`
* Prints the line given by `loc` to `stderr` and underlines the columns given 
by `loc` with circumflexes `^.`

`void showHint(Loc loc, const char *fmt, ...)`
* Prints a `-> 💡 ` followed by `fmt` and `...` to `stderr.`
* We actually only need the line from `loc,` but it’d feel out of place if we 
asked a line number while we’re just displaying a hint.

`static ErrMod mod`
* File-local global function that keeps track of the file name and other 
related data.

