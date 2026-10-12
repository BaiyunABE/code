#include "vsfs.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
  vsfs_init();
  vsfs_create("foo");
  return EXIT_SUCCESS;
}
