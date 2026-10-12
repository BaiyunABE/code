#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int fd = open("test.bin", O_RDWR | O_CREAT | O_TRUNC);

  write(fd, "A", 1);

  *(int*)0 = 42;

  fsync(fd);

  return 0;
}
