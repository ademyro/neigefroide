The `main.c` module is responsible for Neve’s CLI.  It’s `nevec`’s entry 
point.

So far, we’ve implemented:

* A basic argument checker.
* A file reader.

What’s left:

* Hand off control to the compiler.
* Implement thorough argument parsing.  We want to allow the following options:
    * `-Sn` for “strictness level,” where `n` ranges from 1 to 3.
    * `-On` for “optimization level,” where `n` ranges from 0 to 3.
    * We might as well add more as the project evolves.

