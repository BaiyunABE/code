#include "bio.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int fd;

void bio_init()
{
  fd = open("disk.img", O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
  }
}

void bio_read(int blocks, void* buf, int num)
{
  lseek(fd, blocks * BLK_SIZE, SEEK_SET);
  read(fd, buf, num);
}

void bio_write(int blocks, void* buf, int num)
{
  lseek(fd, blocks * BLK_SIZE, SEEK_SET);
  write(fd, buf, num);
}
