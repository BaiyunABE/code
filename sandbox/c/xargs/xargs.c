#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  char input[100];

  int i = 0;
  char* xargv[100];
  
  while (fgets(input, 100, stdin)) {

    i = 0;
    for (int j = 1; j < argc; j++) {
      xargv[i++] = argv[j];
    }

    char* s = strtok(input, " \n");

    while (s != NULL) {
      xargv[i++] = s;
      s = strtok(NULL, " \n");
    }
    
    xargv[i] = NULL;

    int pid = fork();
    if (pid == 0) {
      execvp(xargv[0], &xargv[0]);
    } else if (pid > 0) {
      waitpid(pid, NULL, WUNTRACED | WCONTINUED);
    } else {
      perror("fork");
    }
  }

  return EXIT_SUCCESS;
}
