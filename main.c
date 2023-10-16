#include <stdio.h>
#include <stdlib.h>
#include "tor-detector.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <IPv4 address>\nExample: %s 1.1.1.1\n", *argv, *argv);
        exit(2);
    }
    int result = isTorExitNode(argv[1]);
    fprintf(stderr, "Tor DNS query says %s %s belong to a Tor Exit Node\n", argv[1], result ? "does" : "does not");
    return !result;
}