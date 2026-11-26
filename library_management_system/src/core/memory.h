#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *memory_allocate(size_t size);
void *memory_allocate_zeroed(size_t count, size_t size);
void *memory_resize(void *memory, size_t size);
void memory_release(void *memory);

#endif