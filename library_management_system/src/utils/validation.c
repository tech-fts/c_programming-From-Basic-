#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#include "validation.h"

int validation_is_nonempty(const char *text) {
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 1;
        }
        text++;
    }

    return 0;
}

int validation_parse_int(const char *text, int *value) {
    if (text == NULL || value == NULL || !validation_is_nonempty(text)) {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    long parsed_value = strtol(text, &end, 10);
    if (end == text || errno == ERANGE || parsed_value < INT_MIN || parsed_value > INT_MAX) {
        return 0;
    }

    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            return 0;
        }
        end++;
    }

    *value = (int)parsed_value;
    return 1;
}

int validation_is_in_range(int value, int min_value, int max_value) {
    return min_value <= max_value && value >= min_value && value <= max_value;
}