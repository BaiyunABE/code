#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pipefd[2];
	if (pipe(pipefd)) {
		fprintf(stderr, "pipe failed\n");
		exit(1);
	}
	int rc = fork();
	if (rc < 0) {		// fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {	// child (new process)
		close(pipefd[0]);
		printf("hello\n");
		close(pipefd[1]);
	} else {		// parent goes down this path (main)
		close(pipefd[1]);
		char buf;
		read(pipefd[0], &buf, 1);
		close(pipefd[0]);
		printf("goodbye\n");
	}
	return 0;
}
