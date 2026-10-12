#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 16

int buf[MAX];

void init() {
  for (int i = 0; i < MAX; i++)
    buf[i] = 0;
}

void put(int n) {
  buf[n] = 1;
}

enum State {
  STOP,
  UP,
  DOWN,
};

int next(int now, enum State s) {
  int up = MAX;
  int down = 0;
  for (int i = now; i < MAX; i++) {
    if (buf[i] == 1) {
      up = i;
      break;
    }
  }
  for (int i = now; i > 0; i--) {
    if (buf[i] == 1) {
      down = i;
      break;
    }
  }
  if (down == 0)
    return up;
  if (up == MAX)
    return down;
  switch (s) {
    case STOP:
      return (up + down >= 2 * now) ? down : up;
      break;
    case UP:
      return up;
      break;
    case DOWN:
      return down;
      break;
    default:
      return 0;
  }
}

int get(int n) {
  buf[n] = 0;
}

sem_t mutex;

void* customer() {
  printf("Input the floor you want to get, from 1 to 15\n");
  for (;;) {
    int a = 0;
    int rv = scanf("%x", &a);
    // printf("rv = %d\n", rv);
    if (rv == 0) {
      printf("Bad input.\n");
      while (getchar() != '\n');
      printf("Try again.\n");
      continue;
    }
    if (a > 0 && a < MAX) {
      sem_wait(&mutex);
      put(a);
      sem_post(&mutex);
    }
    else {
      printf("This building does not have %d floor\n", a);
    }
  }
}

void* elevator() {
  int now = 1;
  int target = 1;
  enum State s;
  printf("%ld: now: %d\n", clock(), now);
  for (;;) {
    if (now == target) {
      s = STOP;
      sem_wait(&mutex);
      get(target);
      sem_post(&mutex);
    }
    int a = next(now, s);
    if (a != 0 && a != MAX && a != target) {
      target = a;
      printf("next step: %d\n", target);
    }
    if (now < target) {
      s = UP;
      now++;
      printf("%ld: now: %d\n", clock(), now);
    }
    else if (now > target) {
      s = DOWN;
      now--;
      printf("%ld: now: %d\n", clock(), now);
    }
    sleep(1);
  }
}

int main() {
  sem_init(&mutex, 0, 1);
  pthread_t c, e;
  pthread_create(&c, NULL, customer, NULL);
  pthread_create(&e, NULL, elevator, NULL);
  pthread_join(c, NULL);
  pthread_join(e, NULL);
  return 0;
}
