#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

typedef enum {
    INPUT_ERROR = -1,
    INPUT_EOF = 0,
    INPUT_OK = 1,
    INPUT_INVALID = 2
} InputResult;

InputResult input_read_line(const char *prompt, char *buffer, size_t buffer_size);
InputResult input_read_int(const char *prompt, int min_value, int max_value, int *value);

#endif