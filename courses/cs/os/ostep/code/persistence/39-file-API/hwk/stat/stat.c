#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
  if (argc < 2) {
    puts("usage: ./stat <filename>");
    exit(1);
  }
  struct stat info;
  stat(argv[1], &info);
  printf("  Size: %ld\n", info.st_size);
  printf("Blocks: %ld\n", info.st_blocks);
  printf(" Links: %ld\n", info.st_nlink);
  return 0;
}
