#include <stdio.h>
#include <stdlib.h>

int main() {
  long number = rand() % 100 + 1;
  long guess;
  
  puts("猜数字游戏（1-100）");
  
  for (;;) {
    printf("请输入你的猜测: ");
    
    if (scanf("%ld", &guess) == 0) {
      char c;
      while ((c = getchar()) != EOF && c != '\n');
      puts("输入有误，请重新输入！");
      continue;
    }
    
    if (guess < 1 || guess > 100) {
      puts("请输入1-100内的整数！");
      continue;
    }
    
    if (guess > number) {
      puts("太大了！");
    } else if (guess < number) {
      puts("太小了！");
    } else {
      puts("恭喜你，猜对了！");
      break;
    }
  }
  
  return 0;
}
