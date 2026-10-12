#ifndef _CSAPP_H_
#define _CSAPP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

/* stdio */

char *Fgets(char *s, int size, FILE *stream);
void Fputs(const char *s, FILE *stream);

/* ecf */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t Fork(void);
void Execve(const char *pathname, char *const argv[],
    char *const envp[]);
pid_t Wait(int *wstatus);

/* io */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAXLINE 1000
#define MAXBUF 1000

int Open(const char *pathname, int flags, mode_t mode);
void Close(int fd);
void *Mmap(void *addr, size_t length, int prot, int flags,
    int fd, off_t offset);
void Munmap(void *addr, size_t length);
int Dup2(int oldfd, int newfd);

#define RIO_BUFSIZE 8192

typedef struct {
    int rio_fd;                 // Descriptor for this internal buf
    int rio_cnt;                // Unread bytes in internal buf
    char *rio_bufptr;           // Next unread byte in internal buf
    char rio_buf[RIO_BUFSIZE];  // Internal buffer
} rio_t;

ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

ssize_t Rio_readn(int fd, void *usrbuf, size_t n);
ssize_t Rio_writen(int fd, void *usrbuf, size_t n);
void Rio_readinitb(rio_t *rp, int fd);
ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n);


/* netp */
#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif // __USE_XOPEN2K
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

typedef struct sockaddr SA;

void Getaddrinfo(const char *node, const char *service,
    const struct addrinfo *hints, struct addrinfo **res);

void Freeaddrinfo(struct addrinfo *res);

int Getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
    char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags);

int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);

int Open_clientfd(char *hostname, char *port);
int Open_listenfd(char *port);

#endif // _CSAPP_H_