#include "mm_malloc.h"

#define CAPACITY 4096
#define MIN_FREE_BLOCK_SIZE 32
#define MAGIC 1234567

typedef struct header_t {
	size_t size;
	size_t magic;
} header_t;

typedef struct node_t {
	size_t size;
	struct node_t* next;
} node_t;

static unsigned char buffer[CAPACITY];
static node_t* head;

void print()
{
	printf("head = %p\n", head);
	for (int i = 0; i < 16; i++) {
		printf("%p: ", buffer + 16 * i);
		for (int j = 0; j < 16; j++) {
			printf("%02x ", buffer[16 * i + j]);
		}
		printf("\n");
	}
}

void init()
{
	head = (node_t*)buffer;
	head->size = CAPACITY - sizeof(node_t);
	head->next = NULL;
}

void* mm_malloc(size_t size)
{
	size = (((size >> 4) + ((size & (size_t)0x0f) != 0)) << 4);

	node_t** best = NULL;
	
	for (node_t** pp = &head; *pp != NULL; pp = &(*pp)->next) {
		if ((*pp)->size >= size && (best == NULL || (*pp)->size < (*best)->size)) {
			best = pp;
		}
	}
	
	if (best != NULL) {
		void* ptr = (void*)(*best) + sizeof(header_t); // return ptr to allocated space
		
		if ((*best)->size - size >= MIN_FREE_BLOCK_SIZE) { // split
			node_t* remain = (void*)(*best) + sizeof(header_t) + size;
			remain->size = (*best)->size - size - sizeof(header_t);
			remain->next = (*best)->next;
			(*best)->size = size;
			(*best)->next = (node_t*)MAGIC;
			*best = remain;
		}
		else { // allocate the hole block
			(*best)->next = (node_t*)MAGIC;
			*best = (*best)->next;
		}
		
		return ptr;
	}
	else {
		return NULL;
	}
}

void mm_free(void* ptr)
{
	header_t* hptr = (void*)ptr - sizeof(header_t);
	assert(hptr->magic == MAGIC);
	
	node_t** pp = &head;
	
	for (; *pp != NULL && (void*)(*pp) < (void*)(hptr); pp = &(*pp)->next);
	
	node_t* node = (node_t*)hptr;
	node->next = *pp;
	*pp = node;
	
	// merge
	
	node_t* next = node->next;
	if (next != NULL && (void*)node + sizeof(node_t) + node->size == (void*)next) {
		node->size += sizeof(node_t) + next->size;
		node->next = next->next;
	}
	
	node_t* prev = (void*)(pp) - sizeof(size_t);
	if (pp != &head && (void*)prev + sizeof(node_t) + prev->size == (void*)node) {
		prev->size += sizeof(node_t) + node->size;
		prev->next = node->next;
	}
}

