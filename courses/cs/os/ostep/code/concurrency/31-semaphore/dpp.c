#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

//#define DIJKSTRA

sem_t forks[5];

int left(int p) { return p; }
int right(int p) { return (p + 1) % 5; }

void think(int p) {
	printf("p%d is thinking\n", p);
}

void getforks(int p) {
	printf("p%d want to eat\n", p);
#ifdef DIJKSTRA 
	if (p == 4) {
		sem_wait(&forks[right(p)]);
		printf("p%d take f%d\n", p, right(p));
		sem_wait(&forks[left(p)]);
		printf("p%d take f%d\n", p, left(p));
		return;
	}
#endif
	sem_wait(&forks[left(p)]);
	printf("p%d take f%d\n", p, left(p));
	sem_wait(&forks[right(p)]);
	printf("p%d take f%d\n", p, right(p));
}

void eat(int p) {
	printf("p%d is eating\n", p);
}

void putforks(int p) {
	printf("p%d finish eating\n", p);
	sem_post(&forks[left(p)]);
	sem_post(&forks[right(p)]);
}

void* philosopher(void* arg) {
	int p = (int)arg;
	while (1) {
		think(p);
		getforks(p);
		eat(p);
		putforks(p);
	}
}

void init() {
	for (int i = 0; i < 5; i++)
		sem_init(&forks[i], 0, 1);
}

int main() {
	pthread_t p[5];
	init();
	
	for (int i = 0; i < 5; i++)
		pthread_create(&p[i], NULL, philosopher, (void*)i);
	
	for (int i = 0; i < 5; i++)
		pthread_join(p[i], NULL);
	return 0;
}

