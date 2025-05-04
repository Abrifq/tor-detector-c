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
make lib
cp libtor-detector.so $YOUR_PROJECT_DIR/libs
cd $YOUR_PROJECT_DIR
gcc -L libs your-code.c -l tor-detector -o your-app
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
> Hint: `gcc your-code.c -o your-app`

## Using it as a terminal program

```sh
gcc -Wall -Werror -Wextra main.c tor-detector.c -o tor-detect
./tor-detector 1.2.3.4 # insert your ip here
```

## Known Bugs

Due to a bug within glibc's `getaddrinfo` implementation, (I have `glibc 2.35-0ubuntu9`) when it returns ENOADDR, there is a chance it might return null pointer to the library but forget to free the buffer it allocated itself.
**This will cause a memory leak or a segmentation fault** if the IP address given was not a tor exit IP address, however extensive testing is required to see the actual impact.
