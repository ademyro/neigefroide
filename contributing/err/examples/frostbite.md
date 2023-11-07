```
error: ❄️ dereferencing frostbitten value
   in: example.nv:4:5 
  |
4 |     *ptr = 42;
  |     ^^^^ ‘ptr’ is frostbitten
  |
3 |     ptr.free();
  |     ---------- ptr freed here
  -> 💡 free ‘ptr’ after using it 
```
