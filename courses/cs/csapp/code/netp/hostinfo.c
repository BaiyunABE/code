#include "csapp.h"

int main(int argc, char **argv)
{
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM; /* Connections only */
    Getaddrinfo(argv[1], NULL, &hints, &listp);

    /* Walk the list and display each IP address */
    flags = NI_NUMERICHOST; /* Display address string instead of domain name */
    for (p = listp; p; p = p->ai_next) {
        //Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        //puts(buf);

        struct sockaddr_in *q = (struct sockaddr_in*)p->ai_addr;
        inet_ntop(q->sin_family, &q->sin_addr, buf, p->ai_addrlen);
        puts(buf);
    }

    /* Clean up */
    freeaddrinfo(listp);
    exit(EXIT_SUCCESS);
}