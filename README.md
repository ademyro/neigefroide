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

# Pronunciation.

Don’t ask why this part was included.
English [nɪv]; Portuguese [ˈnε.vi]
