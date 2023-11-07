The `lexer/` module is responsible for lexer/scanner/tokenizer-related tasks.  
It takes the source code and returns a **stream** (not a list) of `Token`s.  It 
works as a single-pass scanner and must be paired up with a parser (which 
we’ll soon implement) to function properly.

The `lexer/` module contains two files: `lexer.c` and `token.c.`
* `lexer.c` is the lexer.  It takes a `char *` pointer, works its way through 
the source code until it can find a meaningful string of text.  It then returns 
a token.
* `token.c` carries the definitions of `Token` and `Loc.`  It can be thought of 
as `lexer.c`’s helper.

So far, we’ve implemented:

* Token types.
* Wrote lexer.
* Wrote temporary compiler code to drive it (refer to `main.compile().`)

What’s left:

* Hopefully, this module should be complete.  Yay!  Feel free to contribute to 
it if you encounter a bug.
