This module takes care of parsing-related tasks, including the AST’s 
definition (see `ast.h.`)  It (will) contain two files; `parser.c` and 
`ast.c.`  
* `ast.c` provides functions related to AST manipulation (node 
initialization, comparison, etc.) 
* `parser.c` parses the stream of tokens given to it.  It then returns a 
heap-allocated AST, with an `AstBody` node as its root.

So far, we’ve implemented:

* The AST structs.

What’s left:

* Implement parser helpers.
    * Stuff like `newNode(), wrapNode(),` etc.
* Parse a basic `fn main() { return 0; }` file.
* Define missing AST nodes.
