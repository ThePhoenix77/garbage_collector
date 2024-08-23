#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include <stdlib.h>

typedef struct block
{
    void *ptr;
    struct block *next;
} block;

typedef struct memory_context
{
    block *head; 
} memory_context;

void *my_malloc(memory_context *context, size_t size);
void my_free(memory_context *context, void *ptr);
void free_all(memory_context *context);

#endif
