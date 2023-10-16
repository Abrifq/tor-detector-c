
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "tor-detector.h"
#define DNS_QUERY_SUFFIX ".dnsel.torproject.org"

void reverseIP(const char *ip, char **dest)
{
    int part1, part2, part3, part4;
    char *buf = malloc(strlen(ip));
    sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
    sprintf(buf, "%d.%d.%d.%d", part4, part3, part2, part1);
    *dest = buf;
    return;
}

int isTorExitNode(const char *ip)
{

    char *reversedIP;
    reverseIP(ip, &reversedIP);
    char *node = malloc(strlen(reversedIP) + sizeof(DNS_QUERY_SUFFIX));
    sprintf(node, "%s" DNS_QUERY_SUFFIX,
            reversedIP);
    struct addrinfo *results;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    int queryResult = getaddrinfo(node, NULL, &hints, &results);
    freeaddrinfo(results);
    free(reversedIP);
    free(node);
    return queryResult ? 0 : 1;
}