`enum TokenType`
* All sorts of tokens that can be scanned.

`struct Loc`
* Stores the location of a token.
* `int line`
    * The token’s line.
* `int col`
    * The token’s column.
* `int length`
    * The token’s length (necessary when working with identifiers.)

`struct Token`
* A source token.
* `char *start`
    * The token’s “starting point,” its first character.
* `TokenType type`
    * The token’s type.
* `Loc loc`
    * The token’s location.

`Loc newLoc()`
* Returns a new `Loc` struct.  By default, a token’s position is set to:
    * line 1,
    * col 1,
    * length 0.

`Token newToken(char *start, TokenType type, Loc loc)`
* Returns a new `Token` struct given the parameters passed to it.

