#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <assert.h>
#include <sys/stat.h>

int main(int argc, const char* argv[])
{
  int long_mode = 0;
  const char* filename = ".";
  DIR* dp = NULL;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-l") == 0) {
      long_mode = 1;
    }
    else {
      filename = argv[i];
    }
  }
  dp = opendir(filename);
  assert(dp != NULL);
  struct dirent* d;
  while ((d = readdir(dp)) != NULL) {
    printf("inode: %d\n file: '%s'\n", (int)d->d_ino, d->d_name);
    if (long_mode) {
      struct stat info;
      stat(d->d_name, &info);
      printf("  uid: %d\n mode: %d\n", info.st_uid, info.st_mode);
    }
    puts("");
  }
  closedir(dp);
  return 0;
}
