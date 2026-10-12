#include "csapp.h"

int main(int argc, char **argv)
{
    const char *ip_str = argv[1];
    uint32_t ip_addr;
    inet_pton(AF_INET, ip_str, &ip_addr);
    ip_addr = ntohl(ip_addr);
    printf("0x%x\n", ip_addr);
    return EXIT_SUCCESS;
}