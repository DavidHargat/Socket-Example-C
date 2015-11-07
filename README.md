# Socket Example in C

This example contains a basic library to wrap C socket implimentation, `socklib.h`.

`main.c` contains an echo server implimented using `socklib.h`.

I didn't research secure ways to interface with sockets while creating this, so you shouldn't use this for anything that should be secure.

This was created for my own knowledge/amusement.

### build

`make`

or

`gcc main.c socklib.h -o main`

should output an executable `main`

### run

`./main`


### reusing socklib.h

place it in your project's directory and include it with:

`#include "socklib.h"`

follow the documentation (or read the source/example) for usage

### dependencies

gcc - https://gcc.gnu.org/