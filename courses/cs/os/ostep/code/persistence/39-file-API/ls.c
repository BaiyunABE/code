#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <assert.h>

int main(int argc, char* argv[])
{
  DIR* dp = NULL;
  if (argc < 2)
    dp = opendir(".");
  else
    dp = opendir(argv[1]);
  assert(dp != NULL);
  struct dirent* d;
  while ((d = readdir(dp)) != NULL) {
    printf("%d %s\n", (int)d->d_ino, d->d_name);
  }
  closedir(dp);
  return 0;
}
