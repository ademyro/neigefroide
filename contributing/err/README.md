The `err/` module is responsible for Neve’s compiler error messages.  It 
contains two files, `err.c` and `render.c.`
* `err.c` is a sort of middle-man between the compiler’s middle-end or backend 
and the error message frontend (that being `render.c.`)
* `render.c` is responsible for formatting and outputting the compiler error 
messages to `stderr.`

So far, we’ve implemented:

* A nice color formatter.
* A simple error message renderer.
    * `error: too many arguments; aborting.`
* Determine an emoji and a concise header for each `Err.`
* Have better, more intuitive error messages (refer to `examples/.`)
* Implement hints or notes (refer to `examples/` too.) 

What’s left:

* Hopefully, this module should be complete.  Yay!  Feel free to contribute to 
it if you encounter a bug.
