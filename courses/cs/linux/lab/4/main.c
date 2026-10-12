#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

pid_t Fork(void)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return pid;
}

int Dup2(int oldfd, int newfd)
{
	int fd = dup2(oldfd, newfd);
	if (fd == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return fd;
}

void Pipe(int pipefd[2])
{
	int rv = pipe(pipefd);
	if (rv == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int Open(const char *pathname, int flags, ...)
{
	int fd;

	if (flags & (O_CREAT | __O_TMPFILE))
	{
		va_list ap;
		va_start(ap, flags);
		mode_t mode = va_arg(ap, mode_t);
		fd = open(pathname, flags, mode);
		va_end(ap);
	}
	else
	{
		fd = open(pathname, flags);
	}

	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	return fd;
}

void Close(int fd)
{
	int rv = close(fd);
	if (rv == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

pid_t Wait(int *wstatus)
{
	pid_t pid = wait(wstatus);
	if (pid == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	return pid;
}

int main()
{
	int pipefd[2];
	Pipe(pipefd);

	if (Fork() == 0)
	{
		Close(pipefd[0]);

		int fd = Open("/etc/passwd", O_RDONLY);
		Dup2(fd, STDIN_FILENO);
		Close(fd);

		Dup2(pipefd[1], STDOUT_FILENO);
		Close(pipefd[1]);

		execlp("grep", "grep", "-v", "usr", NULL);

		perror("execlp");
		exit(EXIT_FAILURE);
	}

	Close(pipefd[1]);

	if (Fork() == 0)
	{
		Dup2(pipefd[0], STDIN_FILENO);
		Close(pipefd[0]);

		int fd = Open("r.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		Dup2(fd, STDOUT_FILENO);
		Close(fd);

		execlp("wc", "wc", "-l", NULL);

		perror("execlp");
		exit(EXIT_FAILURE);
	}

	Close(pipefd[0]);

	Wait(NULL);
	Wait(NULL);

	if (Fork() == 0)
	{
		execlp("cat", "cat", "r.txt", NULL);

		perror("execlp");
		exit(EXIT_FAILURE);
	}

	Wait(NULL);

	return 0;
}