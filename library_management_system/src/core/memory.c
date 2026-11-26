#include <stdint.h>
#include <stdlib.h>

#include "error.h"
#include "memory.h"

void *memory_allocate(size_t size) {
    if (size == 0) {
        error_report("memory_allocate", "allocation size must be greater than zero");
        return NULL;
    }

    void *memory = malloc(size);
    if (memory == NULL) {
        error_report_errno("memory_allocate");
    }
    return memory;
}

void *memory_allocate_zeroed(size_t count, size_t size) {
    if (count == 0 || size == 0) {
        error_report("memory_allocate_zeroed", "count and element size must be greater than zero");
        return NULL;
    }

    if (count > SIZE_MAX / size) {
        error_report("memory_allocate_zeroed", "requested allocation size is too large");
        return NULL;
    }

    void *memory = calloc(count, size);
    if (memory == NULL) {
        error_report_errno("memory_allocate_zeroed");
    }
    return memory;
}

void *memory_resize(void *memory, size_t size) {
    if (size == 0) {
        error_report("memory_resize", "new allocation size must be greater than zero");
        return NULL;
    }

    void *resized_memory = realloc(memory, size);
    if (resized_memory == NULL) {
        error_report_errno("memory_resize");
    }
    return resized_memory;
}

void memory_release(void *memory) {
    free(memory);
}