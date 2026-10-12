#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

char* local_addr;
int port;

void* send() {
  for (;;) {
    printf("dst addr: ");
    char dst_addr[18];
    scanf("%s", dst_addr);
    printf("data: ");
    char data[100];
    scanf("%s", data);
    FILE* fp = fopen("switch.txt", "w");
    fprintf(fp, "%d %s %s %s", port, local_addr, dst_addr, data);
    fclose(fp);
    printf("send \"%s\" to host \"%s\" success.\n", data, dst_addr);
  }
}

void* receive() {
  char filename[6];
  filename[0] = port ^ '0';
  filename[1] = '\0';
  strcat(filename, ".txt");
  for (;;) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
      continue;
    }
    usleep(100000);
    char src_addr[18];
    char dst_addr[18];
    char data[100];
    fscanf(fp, "%s %s %s", src_addr, dst_addr, data);
    fclose(fp);
    remove(filename);
    if (strcmp(dst_addr, local_addr) == 0) {
      printf("receive \"%s\" from host \"%s\".\n", data, src_addr);
    }
  }
}

int main(int argc, char* argv[])
{
  if (argc < 3) {
    printf("Usage: %s <addr> <port>\n", argv[0]);
    exit(1);
  }

  if (strlen(argv[1]) > 17) {
    printf("Illegal MAC addr.\n");
    exit(1);
  }

  local_addr = argv[1];
  port = atoi(argv[2]);
  pthread_t s, r;
  pthread_create(&s, NULL, send, NULL);
  pthread_create(&r, NULL, receive, NULL);
  pthread_join(s, NULL);
  pthread_join(r, NULL);
  return 0;
}
