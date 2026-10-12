#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct qnode {
	int pid;
	struct qnode* next;
};

struct queue {
	struct qnode* head;
	struct qnode* rear;
};

void create(struct queue* q)
{
	q->head = malloc(sizeof(struct qnode));
	assert(q->head != NULL);
	q->rear = q->head;
}

void print(const struct queue* q)
{
	for (const struct qnode* cur = q->head->next; cur != NULL; cur = cur->next)
		printf("%d ", cur->pid);
	printf("\n");
}

void destroy(struct queue* q)
{
	struct qnode* tmp;
	while (q->head != NULL) {
		tmp = q->head;
		q->head = q->head->next;
		free(tmp);
	}
	q->rear = NULL;
}

int empty(const struct queue* q)
{
	return q->head == q->rear;
}

void push(struct queue* q, int pid)
{
	struct qnode* new_node = malloc(sizeof(struct qnode));
	assert(new_node != NULL);
	new_node->pid = pid;
	new_node->next = NULL;
	q->rear->next = new_node;
	q->rear = new_node;
}

int top(const struct queue* q)
{
	return q->head->next->pid;
}

void pop(struct queue* q)
{
	struct qnode* target = q->head->next;
	q->head->next = q->head->next->next;
	if (q->rear == target)
		q->rear = q->head;
	free(target);
}

void merge(struct queue* q0, struct queue* qi)
{
	q0->rear->next = qi->head->next;
	q0->rear = qi->rear;
	qi->head->next = NULL;
	qi->rear = qi->head;
}

#define QUEUE_LIST_SIZE 3
#define PROC_LIST_SIZE 10
#define PROC_MAX_TIME 20
#define PROC_MOVE_TIME 20

struct queue q[QUEUE_LIST_SIZE];
int proc[PROC_LIST_SIZE];
int t;
int pid;
int qid;

void get_qid()
{
	qid = QUEUE_LIST_SIZE;
	for (int i = 0; i < QUEUE_LIST_SIZE; i++) {
		if (!empty(&q[i])) {
			qid = i;
			break;
		}
	}
}

void init()
{
	for (int i = 0; i < QUEUE_LIST_SIZE; i++)
		create(&q[i]);
	
	printf("init process:\n");
	for (int i = 0; i < PROC_LIST_SIZE; i++) {
		proc[i] = rand() % PROC_MAX_TIME + 1;
		push(&q[0], i);
		printf("pid: %d, time: %d\n", i, proc[i]);
	}
	printf("\n");
	
	t = 0;
	
	get_qid();
}

void print_mlfq()
{
	for (int i = 0; i < QUEUE_LIST_SIZE; i++) {
		printf("q%d: ", i);
		print(&q[i]);
	}
}

void flush_mlfq()
{
	printf("flush MLFQ.\n");
	for (int i = 1; i < QUEUE_LIST_SIZE; i++) {
		if (!empty(&q[i])) {
			merge(&q[0], &q[i]);
		}
	}

}

void dispatch()
{
	while (qid != QUEUE_LIST_SIZE) {
		pid = top(&q[qid]);
		pop(&q[qid]);
		proc[pid]--;
		if (proc[pid] <= 0) {
			proc[pid] = 0;
			printf("process %d is done.\n", pid);
		}
		else if (proc[pid] < 5) { // I/O
			printf("process %d do I/O.\n", pid);
			push(&q[qid], pid);
		}
		else { // CPU
			printf("process %d use full CPU.\n", pid);
			proc[pid]--;
			push(&q[qid == QUEUE_LIST_SIZE - 1 ? QUEUE_LIST_SIZE - 1 : qid + 1], pid);
		}
		
		print_mlfq();
		
		t++;
		if (t % PROC_MOVE_TIME == 0) {
			flush_mlfq();
			print_mlfq();
		}
		for (int i = 0; i < PROC_LIST_SIZE; i++)
			printf("pid: %d, time: %d\n", i, proc[i]);
		printf("\n");
		
		get_qid();
	}
	
	printf("all done.\n");
}

void close_sys()
{
	for (int i = 0; i < QUEUE_LIST_SIZE; i++)
		destroy(&q[i]);
}

int main(void)
{
	init();
	
	dispatch();
	
	close_sys();
	
	return 0;
}
