#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define PARKING_LOT_SIZE 5
#define CAR_SIZE 9

sem_t full, empty, mutex;
int parking_lot[PARKING_LOT_SIZE];

void print_parking_lot()
{
	printf("[ ");
	for (int i = 0; i < PARKING_LOT_SIZE; i++)
		printf("%d ", parking_lot[i]);
	printf("]\n");
}

int put(int cid)
{
	printf("%ld: car %d in\n", time(NULL), cid);
	int pos = 0;
	while (parking_lot[pos] != 0)
		pos++;
	parking_lot[pos] = cid;
	print_parking_lot();
	return pos;
}

void get(int pos)
{
	printf("%ld: car %d out\n", time(NULL), parking_lot[pos]);
	parking_lot[pos] = 0;
	print_parking_lot();
}

void* car(void* arg)
{
	sleep(rand() % 5 + 1);
	
	int cid = (int)(long)arg;
	sem_wait(&empty);
	sem_wait(&mutex);
	int pos = put(cid);
	sem_post(&mutex);
	sem_post(&full);
	
	sleep(rand() % 5 + 1);
	
	sem_wait(&full);
	sem_wait(&mutex);
	get(pos);
	sem_post(&mutex);
	sem_post(&empty);
}

void init()
{
	srand(time(NULL));
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, PARKING_LOT_SIZE);
	sem_init(&mutex, 0, 1);
	for (int i = 0; i < PARKING_LOT_SIZE; i++)
		parking_lot[i] = 0;
}

int main()
{
	pthread_t p[CAR_SIZE];
	init();
	for (int i = 0; i < CAR_SIZE; i++)
		pthread_create(&p[i], NULL, car, (void*)(long)(i + 1));
	for (int i = 0; i < CAR_SIZE; i++)
		pthread_join(p[i], NULL);
	return 0;
}
