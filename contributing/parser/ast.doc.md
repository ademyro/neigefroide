`enum NodeType`
* Every Neve node type (function node, return node, etc.)
* `NODE_PARAM`
    * A parameter node.  Not to be confused with an argument node; arguments 
    are expressions passed to a function call, whereas parameters introduce 
    names into the function’s scope.
* `NODE_FN`
    * A function declaration node, with its body, list of arguments, arity and 
    return type.
* `NODE_RET`
    * A return node--returns a value.  Can only appear inside a function.
* `NODE_BIN_OP`
    * A binary operation node.
* `NODE_UN_OP`
    * A unary operation node.
* `NODE_INT`
    * An integer node.  Can have multiple bit widths and can be signed.
* `NODE_FLOAT`
    * A float node.  Can be double precise.

# Wrapper nodes

`struct Ast`
* A regular Ast node.
* `NodeType type`
    * The node’s type.
* `union as`
    * The different nodes `Ast` can be.
    * `AstFn *fn`
    * `AstParam *param`
    * `AstStmt stmt`

`struct AstStmt`
* A statement node.
* `NodeType type`
    * The node’s type.
* `union as`
    * The different nodes `AstStmt` can be.
    * `AstBody *body`
    * `AstRet *ret`
    * `AstExpr *expr`

`struct AstExpr`
* An expression node.
* `NodeType type`
    * The node’s type.
* `union as`
    * The different nodes `AstExpr` can be.
    * `AstBinOp *binOp`
    * `AstUnOp *unOp`
    * `AstInt *intNode`
    * `AstFloat floatNode`

# Nodes

`struct AstBody`
* A dynamically resizeable node that contains multiple `Ast` nodes.
* `int size`
    * The body’s size.
* `ìnt cap`
    * This is regular bookkeeping for the body’s capacity.  If that capacity 
    is exceeded, we resize the body.
* `Ast *body`
    * The body’s list of nodes.
* `Loc loc`
    * The body’s location in the source code.

`struct AstParam`
* A parameter node.
* `Token name`
    * The parameter’s name.
* `Type type`
    * The parameter’s type.
* `Loc loc`
    * The parameter’s location in the source code.

`struct AstFn`
* A function declaration node.
* `Token name`
    * The function’s name.
* `AstParam *params`
    * Statically allocated array of `AstParams.`  Cannot exceed 12 parameters.
* `Type returnType`
    * The function’s return type.  Often inferred.
* `AstBody *body`
    * The function’s body.
* `Loc loc`
    * The function declaration’s location in the source code.

`struct AstRet`
* A return node. 
* `AstExpr *expr`
    * The node’s expression.  Null if there’s no return value.
* `Loc loc`
    * The node’s location in the source code.  Points to the `return` keyword.

`struct AstBinOp`
* A binary operation node.
* `AstExpr *left`
    * The node’s left operand.
* `Token op`
    * The node’s operator.
* `AstExpr *right`
    * The node’s right operand.
* `Loc loc`
    * The binary operation’s location in the source code.  Takes into account 
    the left operand, operator, and right operand. 

`struct AstUnOp`
* A unary operation node.
* `Token op`
    * The unary operation’s token.
* `AstExpr *child`
    * The child being “unary operated.”
* `Loc loc`
    * The unary operation’s location in the source code.  Includes both the 
    operator’s location and the child’s location.

`struct AstInt`
* An integer node.  Can be unsigned and its bit width can vary.
* `NumericType bitWidth`
    * The node’s
