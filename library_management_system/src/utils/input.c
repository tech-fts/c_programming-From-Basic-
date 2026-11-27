#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "input.h"
#include "validation.h"

InputResult input_read_line(const char *prompt, char *buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size == 0 || buffer_size > INT_MAX) {
        fprintf(stderr, "Cannot read input: invalid buffer.\n");
        return INPUT_ERROR;
    }

    if (prompt != NULL) {
        fputs(prompt, stdout);
        fflush(stdout);
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Could not read input");
            return INPUT_ERROR;
        }
        return INPUT_EOF;
    }

    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return INPUT_OK;
    }

    if (!feof(stdin)) {
        int character = getchar();
        if (character == '\n' || character == EOF) {
            if (ferror(stdin)) {
                perror("Could not read input");
                return INPUT_ERROR;
            }
            return INPUT_OK;
        }

        while (character != '\n' && character != EOF) {
            character = getchar();
        }

        if (ferror(stdin)) {
            perror("Could not read input");
            return INPUT_ERROR;
        }

        buffer[0] = '\0';
        fprintf(stderr, "Input is too long.\n");
        return INPUT_INVALID;
    }

    return INPUT_OK;
}

InputResult input_read_int(const char *prompt, int min_value, int max_value, int *value) {
    if (value == NULL || min_value > max_value) {
        fprintf(stderr, "Cannot read an integer: invalid argument.\n");
        return INPUT_ERROR;
    }

    char buffer[128];
    InputResult result = input_read_line(prompt, buffer, sizeof buffer);
    if (result != INPUT_OK) {
        return result;
    }

    int parsed_value;
    if (!validation_parse_int(buffer, &parsed_value)) {
        fprintf(stderr, "Enter a valid whole number.\n");
        return INPUT_INVALID;
    }

    if (!validation_is_in_range(parsed_value, min_value, max_value)) {
        fprintf(stderr, "Enter a number from %d to %d.\n", min_value, max_value);
        return INPUT_INVALID;
    }

    *value = parsed_value;
    return INPUT_OK;
}