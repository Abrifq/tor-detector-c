#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "tor-detector.h"
#define DNS_QUERY_SUFFIX ".dnsel.torproject.org"

void reverseIP(const char* ip, char** dest)
{
    int part1, part2, part3, part4;
    size_t strLen = strlen(ip) + 1;
    char* buf = (char*)malloc(strLen);
    sscanf(ip, "%d.%d.%d.%d", &part1, &part2, &part3, &part4);
    snprintf(buf, strLen, "%d.%d.%d.%d", part4, part3, part2, part1);
    *dest = buf;
    return;
}

int isTorExitNode(const char* ip)
{

    char* reversedIP;
    reverseIP(ip, &reversedIP);
    size_t dnsQueryAddressLength = strlen(reversedIP) + sizeof(DNS_QUERY_SUFFIX); //sizeof already includes the null byte, we don't need to add it by hand.
    char* node = (char*)malloc(dnsQueryAddressLength);
    snprintf(node, dnsQueryAddressLength, "%s%s", reversedIP, DNS_QUERY_SUFFIX);
    struct addrinfo* results = NULL;
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_INET;
    int queryResult = getaddrinfo(node, NULL, &hints, &results);
    if (results != NULL)
        freeaddrinfo(results);
    free(reversedIP);
    free(node);
    return queryResult ? 0 : 1;
}