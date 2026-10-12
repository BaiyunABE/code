#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	if (fd == -1) {
		fprintf(stderr, "open failed\n");
		exit(1);
	}
	int rc = fork();
	if (rc < 0) {		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {	// child (new process)
		write(fd, "child is writing\n", 17);
		close(fd);
	} else {		// parent goes down this path (main)
		write(fd, "parent is writing\n", 18);
		close(fd);
	}
	return 0;
}
