```
error: 😱 resource leak
   in: example.nv:28:1
   |
28 | }
   | ^ end of scope, ‘buf’ not freed
   |
23 | let buf = Buffer.new(100); 
   |     --- buf declared here
   -> 💡 free ‘buf’ before exiting the current scope
   |
27 | buf.free();
   | ---------- free ‘buf’
28 | }
```
