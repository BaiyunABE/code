#include <stdio.h>
#include <assert.h>

void print();

void init();

void* mm_malloc(size_t size);

void mm_free(void* ptr);

