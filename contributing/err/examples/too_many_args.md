```
error: ⚙️ too many arguments
   in: example.nv:105:29
    |
105 | let result = calculate_total(price, quantity, discount);
    |                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^ expected 2 arguments but got 3
    |
102 | fn calculate_total(price: i32, quantity: i32) {
    |    --------------- ‘calculate_total’ declared here
    -> 💡 provide 2 arguments instead
```
