#include <stdio.h>
#include <unistd.h>

int main() {
  
  setvbuf(stdout, NULL, _IOFBF, 0);
  
  for (int i = 0; i < 2; i++) {
    printf("i=*%d, one, pid=%d*\n", i, getpid());
    fork();
    printf("i=*%d, two, pid=%d*\n", i, getpid());
  }
}
