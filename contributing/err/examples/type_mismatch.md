```
error: 🚫 type mismatch
   in: example.nv:71:22
   |
71 | let result = add(a, b);
   |                     ^ expected `i32` but got `f64`
   |
65 | fn add(a: i32, b: i32) { 
   |    --- ‘add’ declared here
   |
70 | let b = 5.1;
   |     - ‘b’ declared here
   -> 💡 make sure ‘b’ is of type `i32.`
```
