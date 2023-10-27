`void initErrMod(const char *fname, char *src)`
* Initializes `err.c`’s file-local `ErrMod mod` struct given the arguments.

`void cliErr(const char *fmt, ...)`
* Creates a `va_list` out of `fmt` and `...` and calls `renderSimpleErr().` 

`void reportErrAt(Loc loc, const char *fmt, ...)`
* Displays the error’s header and location.

`void showOffendingLine(Loc loc, const char *fmt, ...)`
* Prints the line given by `loc` to `stderr` and underlines the columns given 
by `loc` with circumflexes `^.`

`void showNote(Loc loc, const char *fmt, ...)`
* Displays a note at `loc,` such as `--- buf declared here.`  It also displays 
the line given by `loc.`

`void showHint(Loc loc, const char *fmt, ...)`
* Prints a `-> 💡 ` followed by `fmt` and `...` to `stderr.`
* We actually only need the line from `loc,` but it’d feel out of place if we 
asked a line number while we’re just displaying a hint.

`void suggestFix(Loc fixLoc, const char *fmt, ...)`
* Modifies the source code given `fmt` and `...` and adds `+` symbols 
underneath the change.

`void suggestFixAbove(int line, const char *fmt, ...)`
* Displays a new line above the error given `fmt` and `...` and adds `+` 
symbols underneath the change.

`static ErrMod mod`
* File-local global function that keeps track of the file name and other 
related data.

