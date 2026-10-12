#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  for (;;) {
    FILE* fp = fopen("switch.txt", "r");
    if (fp == NULL) {
      continue;
    }
    usleep(100000);
    int port;
    char src_addr[17];
    char dst_addr[17];
    char data[100];
    fscanf(fp, "%d %s %s %s", &port, src_addr, dst_addr, data);
    fclose(fp);
    remove("switch.txt");
    printf("receive from port %d: \"%s\" to \"%s\", data: \"%s\".\n", port, src_addr, dst_addr, data);
    for (int i = 0; i < 7; i++) {
      if (i == port) {
        continue;
      }
      char filename[6];
      filename[0] = i ^ '0';
      filename[1] = '\0';
      strcat(filename, ".txt");
      fp = fopen(filename, "w");
      fprintf(fp, "%s %s %s", src_addr, dst_addr, data);
      fclose(fp);
    }
  }
}
