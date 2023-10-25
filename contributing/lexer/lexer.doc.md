`struct Lexer`
* Keeps track of the Lexer’s state (position, start, etc.)
* `char *curr`
    * Lexer’s current character.
* `char *start`
    * Lexer’s start character--points to the start of a multi-character token, 
    like an identifier.
* `Loc loc`
    * Lexer’s current location.

`void initLexer(Lexer *lexer, char *src)`
* Initializes `lexer`’s state given `src.`

`Token nextToken(Lexer *lexer)`
* Returns the next token given Lexer’s current state.

`static bool isDigit(char c)`
* Checks whether `c` is a digit (`0..9.`)

`static bool isAlpha(char c)`
* Checks whether `c` is alphabetical (`a..Z | _.`)

`static bool atEnd(Lexer *lexer)`
* Returns `true` if the lexer’s current character is a null terminator.

`static int currTokenLength(Lexer *lexer)`
* Returns the length of Lexer’s latest parsed token.

`static char peek(Lexer *lexer)`
* Returns `lexer->curr.`

`static char peekNext(Lexer *lexer)`
* Returns the character right after `lexer->curr.`  Returns `\0` if `atEnd().`

`static bool match(Lexer *lexer, char c)`
* Advances and returns true if `lexer->curr == c.`

`static bool notMatch(Lexer *lexer, char c)`
* Returns the opposite of `match(),` but doesn’t advance.

`static bool matchSeq(Lexer *lexer, const char *seq)`
* `seq` must be two characters long.
* Returns true if the lexer’s current character and the one right after that 
match `seq[0]` and `seq[1],` respectively.

`static char advance(Lexer *lexer)`
* Advances and returns the previous character (the one `lexer->curr` was 
pointing to before advancing.)

`static Token makeToken(Lexer *lexer, TokenType type)`
* Returns a new token given the lexer’s current state.

`static Token unexpectedChar(Lexer *lexer)`
* Returns an `ERR` token.

`static void synchronize(Lexer *lexer)`
* Sets `lexer->start` to `lexer->curr` and updates the lexer’s current column.

`static void multilineComment(Lexer *lexer)`
* Skips a multiline comment.

`static TokenType checkKeyword(Lexer *lexer, int start, int length, 
const char *expected, TokenType type)`
* Helper function that checks whether the latest token is a keyword.

`static TokenType checkForF(Lexer *lexer)`
* Helper function that checks whether an identifier starting with `f` is a 
keyword.

`static TokenType checkForI(Lexer *lexer)`
* Helper function that checks whether an identifier starting with `i` is a 
keyword.

`static TokenType checkForS(Lexer *lexer)`
* Helper function that checks whether an identifier starting with `s` is a 
keyword.

`static TokenType checkForU(Lexer *lexer)`
* Helper function that checks whether an identifier starting with `u` is a 
keyword.

`static TokenType identifierType(Lexer *lexer)`
* Checks whether the latest token is a keyword.

`static Token string(Lexer *lexer)`
* Scans a string.

`static Token number(Lexer *lexer)`
* Scans a number (could be an `INTEGER` or a `FLOAT.`)

`static Token identifier(Lexer *lexer)`
* Scans an identifier.  It then hands off the control to `identifierType().`
