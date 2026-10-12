#include <stdio.h>
#include <pthread.h>
#include "buffer.h"

static pthread_cond_t empty, fill;
static pthread_mutex_t mutex;

void init() {
	pthread_mutex_init(&mutex, NULL);
}

void* producer(void* arg) {
	int i;
	int loops = (int)arg;
	for (i = 0; i < loops; i++) {
		pthread_mutex_lock(&mutex);
		while (count == MAX)
			pthread_cond_wait(&empty, &mutex);
		put(i);
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&mutex);
	}
}

void* consumer(void* arg) {
	int i;
	int loops = (int)arg;
	for (i = 0; i < loops; i++) {
		pthread_mutex_lock(&mutex);
		while (count == 0)
			pthread_cond_wait(&fill, &mutex);
		int tmp = get();
		pthread_cond_signal(&empty);
		printf("%d\n", tmp);
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char* argv[]) {
	pthread_t p1, p2, p3, p4;
	init();
	pthread_create(&p1, NULL, producer, (void*)100);
	pthread_create(&p2, NULL, producer, (void*)100);
	pthread_create(&p3, NULL, consumer, (void*)100);
	pthread_create(&p4, NULL, consumer, (void*)100);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	return 0;
}

