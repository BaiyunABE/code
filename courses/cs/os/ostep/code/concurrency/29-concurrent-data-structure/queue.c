#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>

typedef struct __node_t {
	int value;
	struct __node_t* next;
} node_t;

typedef struct queue_t {
	node_t* head;
	node_t* tail;
	pthread_mutex_t head_lock;
	pthread_mutex_t tail_lock;
} queue_t;

void init(queue_t* q)
{
	node_t* tmp = malloc(sizeof(node_t));
	tmp->next = NULL;
	q->head = q->tail = tmp;
	pthread_mutex_init(&q->head_lock, NULL);
	pthread_mutex_init(&q->tail_lock, NULL);
}

void enqueue(queue_t* q, int value)
{
	node_t* tmp = malloc(sizeof(node_t));
	assert(tmp != NULL);
	tmp->value = value;
	tmp->next = NULL;
	
	pthread_mutex_lock(&q->tail_lock);
	q->tail->next = tmp;
	q->tail = tmp;
	pthread_mutex_unlock(&q->tail_lock);
}

int dequeue(queue_t *q, int* value)
{
	pthread_mutex_lock(&q->head_lock);
	node_t *tmp = q->head;
	node_t *new_head = tmp->next;
	if (new_head == NULL) {
		pthread_mutex_unlock(&q->head_lock);
		return -1;
	}
	*value = new_head->value;
	q->head = new_head;
	pthread_mutex_unlock(&q->head_lock);
	free(tmp);
	return 0;
}

queue_t q;

void* inputer(void* args)
{
	for (int i = 0; i < 20; i++) {
		enqueue(&q, i);
		printf("%ld: ENQ %d from thread %ld\n", clock(), i, (long)args);
	}
	return NULL;
}

void* outputer(void* args)
{
	int rc, value, i = 0;
	while (i < 40) {
		rc = dequeue(&q, &value);
		if (rc == 0) {
			printf("%ld: DEQ %d\n", clock(), value);
			i++;
		}
		else {
			printf("%ld: DEQ fail\n", clock());
			sched_yield(); // release CPU, this thread will be move to the top of MLFQ, result in spin-wait. need condition variable to do communication between threads.
		}
	}
	return NULL;
}

int main()
{
	init(&q);
	pthread_t p1, p2, p3;
	pthread_create(&p1, NULL, inputer, (void*)1);
	pthread_create(&p2, NULL, inputer, (void*)2);
	pthread_create(&p3, NULL, outputer, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	return 0;
}

