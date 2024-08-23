#include "garbage_collector.h"

void add_block(memory_context *context, void *ptr)
{
    block *new_block = malloc(sizeof(block));
    if (!new_block) return; // Handle malloc failure
    new_block->ptr = ptr;
    new_block->next = context->head;
    context->head = new_block;
}

void remove_block(memory_context *context, void *ptr)
{
    block **indirect = &context->head;
    while (*indirect)
    {
        block *current = *indirect;
        if (current->ptr == ptr)
        {
            *indirect = current->next;
            free(current);
            return;
        }
        indirect = &current->next;
    }
}

void *alloc(memory_context *context, size_t size)
{
    void *ptr = malloc(size);
    if (ptr)
    {
        add_block(context, ptr);
    }
    return ptr;
}

void my_free(memory_context *context, void *ptr)
{
    if (ptr)
    {
        remove_block(context, ptr);
        free(ptr);
    }
}

void free_all(memory_context *context)
{
    block *current = context->head;
    while (current)
    {
        block *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    context->head = NULL;
}

void t(){system("leaks a.out");}
int main() {
    atexit(t);
    memory_context context = {NULL}; // Initialize context
    char *data = alloc(&context, 100);
    if (!data)
    {
        perror("malloc failed");
        free_all(&context);
        return 1;
    }

    // Use data...

    my_free(&context, data);
    free_all(&context);
    return 0;
}
