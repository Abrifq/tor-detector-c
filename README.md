# Tor Exit Node Detector for C

A quick way to test if an IP belongs to a TOR Exit node.

Uses the new DNS Exit Node querying method (newer than the comparing to list file, April 2020)

Also check out [nodeJS port of this project](https://github.com/Abrifq/tor-detector-js)

## Basic Usage in C

### Via linking to library

```c
#include <tor-detector.h>
int main (){
    char ipBuffer[16];
    scanf("%15s",ipBuffer);
    int isExit = isExitNode(ipBuffer);
    return !isExit;
}
```

Don't forget to link!

```sh
gcc -shared -o bin/tor-detect.so -c tor-detector.c
gcc -o bin/your-program bin/tor-detect.so your-code.c #static link
# or
## TODO ADD DYNAMIC LINKING (sorry guys, lol)
```

### Via including the source

```c
#include <tor-detector.c>
int main (){
    char ipBuffer[16];
    scanf("%15s",ipBuffer);
    int isExit = isExitNode(ipBuffer);
    return !isExit;
}
```

I'm sure you can compile it yourself.
<!-- TODO: welp, add instructions just in case! -->

## Using it as a terminal program

```sh
gcc -Wall -Werror -Wextra main.c tor-detector.c -o tor-detect
./tor-detector 1.2.3.4 # insert your ip here
```
