#include "csapp.h"

#define IP_SIZE 17

int main(int argc, char **argv)
{
    uint32_t ip_addr;
    sscanf(argv[1], "0x%x", &ip_addr);
    ip_addr = htonl(ip_addr);
    char ip_str[IP_SIZE];
    inet_ntop(AF_INET, &ip_addr, ip_str, IP_SIZE);
    puts(ip_str);
    return EXIT_SUCCESS;
}