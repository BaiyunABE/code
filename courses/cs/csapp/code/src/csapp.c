#include "csapp.h"

static void unix_error(char *msg) // Unix-style error
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

static void posix_error(int code, char *msg) // Posix-style error
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

static void gai_error(int code, char *msg) // Getaddrinfo-style error
{
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}

static void app_error(char *msg) // Getaddrinfo-style error
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

/* stdio */

char *Fgets(char *s, int size, FILE *stream)
{
    char *rptr;
    
    if ((rptr = fgets(s, size, stream)) == NULL && ferror(stream))
        app_error("Fgets error");
    return rptr;
}

void Fputs(const char *s, FILE *stream)
{
    if (fputs(s, stream) == EOF)
        unix_error("Fputs error");
}

/* ecf */

pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) == -1)
        unix_error("Fork error");
    return pid;
}

void Execve(const char *pathname, char *const argv[],
    char *const envp[])
{
    int rc;

    if ((rc = execve(pathname, argv, envp)) == -1)
        unix_error("Execve error");
}

pid_t Wait(int *wstatus)
{
    pid_t pid;

    if ((pid = wait(wstatus)) == -1)
        unix_error("Wait error");
    return pid;
}

/* io */

int Open(const char *pathname, int flags, mode_t mode)
{
    int fd;

    if ((fd = open(pathname, flags, mode)) == -1)
        unix_error("Open error");
    return fd;
}

void Close(int fd)
{
    int rc;

    if ((rc = close(fd)) < 0)
        unix_error("Close error");
}

void *Mmap(void *addr, size_t length, int prot, int flags,
            int fd, off_t offset)
{
    void *rptr;

    if ((rptr = mmap(addr, length, prot, flags, fd, offset)) == MAP_FAILED)
        unix_error("Mmap error");
    return rptr;
}

void Munmap(void *addr, size_t length)
{
    int rc;

    if ((rc = munmap(addr, length)) == -1)
        unix_error("Munmap error");
    return rc;
}

int Dup2(int oldfd, int newfd)
{
    int fd;

    if ((fd = dup2(oldfd, newfd)) == -1)
        unix_error("Dup2 error");
    return fd;
}

ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) // Interrupted by sig handler return
                nread = 0; // and call read() again
            else // errno set by read()
                return -1;
        }
        else if (nread == 0) // EOF
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft); // Return >= 0
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR) // Interrupted by sig handler return
                nwritten = 0; // and call write() again
            else // errno set by write()
                return -1;
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0) { // Refill if buf is empty
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));

        if (rp->rio_cnt < 0) {
            if (errno != EINTR) // Interrupted by sig handler return
                return -1;
        }
        else if (rp->rio_cnt == 0) // EOF
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf; // Reset buffer ptr
    }

    // Copy min(n, rp->rio_cnt) bytes from internal buf to user buf
    cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if (c == '\n') {
                n++;
                break;
            }
        }
        else if (rc == 0) {
            if (n == 1)
                return 0; // EOF, no data read
            else
                break; // EOF, some data was read
        }
        else
            return -1; // Error
    }
    *bufp = 0;
    return n - 1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = rio_read(rp, bufp, nleft)) < 0)
            return -1; // errno set by read()
        else if (nread == 0)
            break; // EOF
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft); // Return >= 0
}

ssize_t Rio_readn(int fd, void *usrbuf, size_t n)
{
    ssize_t rc;

    if ((rc = rio_readn(fd, usrbuf, n)) < 0)
        unix_error("Rio_readn error");
    return rc;
}

ssize_t Rio_writen(int fd, void *usrbuf, size_t n)
{
    ssize_t rc;

    if ((rc = rio_writen(fd, usrbuf, n)) < 0)
        unix_error("Rio_writen error");
    return rc;
}

void Rio_readinitb(rio_t *rp, int fd)
{
    rio_readinitb(rp, fd);
}

ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    ssize_t rc;

    if ((rc = rio_readlineb(rp, usrbuf, maxlen)) < 0)
        unix_error("Rio_readlineb error");
    return rc;
}

ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    ssize_t rc;

    if ((rc = rio_readnb(rp, usrbuf, maxlen)) < 0)
        unix_error("Rio_readnb error");
    return rc;
}

/* netp */

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int connfd;

    if ((connfd = accept(sockfd, addr, addrlen)) == -1)
        unix_error("Accept error");
    return connfd;
}

void Getaddrinfo(const char *node, const char *service,
    const struct addrinfo *hints, struct addrinfo **res)
{
    int rc;

    if ((rc = getaddrinfo(node, service, hints, res)) != 0)
        gai_error(rc, "Getaddrinfo error");
}

void Freeaddrinfo(struct addrinfo *res)
{
    freeaddrinfo(res);
}

int Getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
    char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags)
{
    int rc;

    if ((rc = getnameinfo(addr, addrlen, host, hostlen, serv, servlen, flags)) != 0)
        gai_error(rc, "Getnameinfo error");
    return rc;
}

int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    struct addrinfo hints, *listp, *p;

    // Get a list of potential server addresses
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; // Open a connection
    hints.ai_flags = AI_NUMERICSERV; // ... using a numeric port arg.
    hints.ai_flags |= AI_ADDRCONFIG; // Recommended for connections
    Getaddrinfo(hostname, port, &hints, &listp);

    // Walk the list for one that we can successfully connect to
    for (p = listp; p; p = p->ai_next) {
        // Create a socket descriptor
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue; // Socket failed, try the next

        // Connect to the server
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break; // Success
        Close(clientfd); // Connect failed, try another
    }

    // Clean up
    Freeaddrinfo(listp);
    if (!p) // All connects failed
        return -1;
    else // The last connect succeeded
        return clientfd;
}

#define LISTENQ 1024

int open_listenfd(char *port)
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    // Get a list of potential server addresses
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; // Accept connections
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // ... on any IP address
    hints.ai_flags |= AI_NUMERICSERV; // ... using port number
    Getaddrinfo(NULL, port, &hints, &listp);

    // Walk the list for one that we can bind to
    for (p = listp; p; p = p->ai_next) {
        // Create a socket descriptor
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue; // Socket failed, try the next

        // Eliminates "Address already in use" err from bind
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

        // Bind the descriptor to the address
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break; // Success
        Close(listenfd); // Bind failed, try the next
    }

    // Clean up
    Freeaddrinfo(listp);
    if (!p) // No address worked
        return -1;
    
    // Make it a listening socket ready to accept connection requests
    if (listen(listenfd, LISTENQ) < 0) {
        Close(listenfd);
        return -1;
    }
    return listenfd;
}

int Open_clientfd(char *hostname, char *port)
{
    int rc;

    if ((rc = open_clientfd(hostname, port)) < 0)
        unix_error("Open_clientfd error");
    return rc;
}

int Open_listenfd(char *port)
{
    int rc;

    if ((rc = open_listenfd(port)) < 0)
        unix_error("Open_listenfd error");
    return rc;
}