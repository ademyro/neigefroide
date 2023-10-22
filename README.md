# Neve.

Neve is a low-level programming language that aims to balance low-level control
with a clean, friendly syntax.  

Here’s your typical peek:
```rs
struct LinkedNode {
    value: i32,
    next: ?*LinkedNode,

    ext fn new(value: i32) {
        return LinkedNode {
            value: value,
            next: nil
        };
    }
}

fn main() {
    let linked_list = LinkedNode.new(-1); 

    for i in 0..10 {
        linked_list.next = &LinkedNode.new(i); 
        linked_list = linked_list.next;
    }
}
```

Neve is currently under development.  It’s in its very early days of life, and 
we’ll do our best to raise it well.
You can run `make` and build the project from source, but you shouldn’t expect
much from that.  Currently, `nevec` is just a `cat` command with extra steps. 

# Contributing

Great!  Any contribution to the Neve programming language is welcome.  We’ll do 
our best to provide code examples and a roadmap for anyone who whishes to join
the project.

Upon contributing, we encourage you to write clean, maintainable code.  The 
compiler doesn’t need to be exceptionally fast (but the output does.)  Please
try to follow our current code style (use camelCase, keep your headers in 
`include/`, etc.)  We might provide a contributing guide in the future.

# Pronunciation.

Don’t ask why this part was included.
English [nɪv]; Portuguese [ˈnε.vi]
