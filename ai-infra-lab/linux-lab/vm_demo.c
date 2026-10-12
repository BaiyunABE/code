#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALLOC_SIZE 1024 * 1024 * 10  // 每次分配10MB

void print_self_maps() {
    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp) {
        perror("open /proc/self/maps failed");
        return;
    }
    char buf[1024];
    printf("======== /proc/self/maps ========\n");
    while (fgets(buf, sizeof(buf), fp)) {
        printf("%s", buf);
    }
    fclose(fp);
    printf("=================================\n\n");
}

int main() {
    printf("初始内存布局\n");
    print_self_maps();

    // 循环分配堆内存
    for (int i = 0; i < 5; i++) {
        void *p = malloc(ALLOC_SIZE);
        if (p == NULL) {
            perror("malloc fail");
            break;
        }
        printf("第 %d 次 malloc 10MB，地址：%p\n", i+1, p);
        sleep(1);
        print_self_maps();
    }

    return 0;
}
