#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3

struct node {
	int id;
	struct node* prev;
	struct node* next;
};

struct node* head;
struct node* tail;
int size;

void init()
{
	/*
			 +------+     +------+
		head---->|      |---->|      |---->NULL
			 | head |     | tail |
		NULL<----|      |<----|      |<----tail
			 +------+     +------+
	*/

	head = malloc(sizeof(struct node));
	tail = malloc(sizeof(struct node));

	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;

	size = 0;
}

void eliminate()
{
	/*
		+-----+     +--------+     +------+
		|     |---->|        |---->|      |
		| ... |     | target |     | tail |
		|     |<----|        |<----|      |
		+-----+     +--------+     +------+
	*/

	struct node* target = tail->prev;
	target->prev->next = tail;
	tail->prev = target->prev;

	free(target);
	size--;
}

void insert(int id)
{
	/*
		+------+     +------+     +-----+
		|      |---->|      |---->|     |
		| head |     | node |     | ... |
		|      |<----|      |<----|     |
		+------+     +------+     +-----+
	*/
	
	if (size >= MAX_SIZE)
		eliminate();

	size++;

	struct node* node = malloc(sizeof(struct node));

	node->id = id;

	node->prev = head;
	node->next = head->next;
	head->next->prev = node;
	head->next = node;
}

void visit(int id)
{
	/*
		+------+     +-----+     +-----+     +--------+     +-----+
		|      |---->|     |---->|     |---->|        |---->|     |
		| head |     | ... |     | cur |     | target |     | ... |
		|      |<----|     |<----|     |<----|        |<----|     |
		+------+     +-----+     +-----+     +--------+     +-----+
	*/
	
	struct node* cur = head;
	while (cur->next != tail) {
		if (cur->next->id == id) {
			struct node* target = cur->next;
			target->next->prev = cur;
			cur->next = target->next;

			target->prev = head;
			target->next = head->next;
			head->next->prev = target;
			head->next = target;
			return;
		}
		cur = cur->next;
	}
	
	insert(id);
}

void print()
{
	for (struct node* cur = head->next; cur != tail; cur = cur->next)
		printf("%d ", cur->id);
	
	printf("\n");
}

void destroy()
{
	struct node* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
	tail = NULL;
}


int main(void)
{
	init();
	visit(0);
	print();
	visit(1);
	print();
	visit(2);
	print();
	visit(3);
	print();
	visit(0);
	print();
	visit(2);
	print();
	destroy();
	return 0;
}
