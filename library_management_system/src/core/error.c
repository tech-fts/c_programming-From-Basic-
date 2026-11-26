#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "error.h"

void error_report(const char *operation, const char *message) {
    if (operation != NULL && message != NULL) {
        fprintf(stderr, "Error: %s: %s\n", operation, message);
    } else if (operation != NULL) {
        fprintf(stderr, "Error: %s\n", operation);
    } else if (message != NULL) {
        fprintf(stderr, "Error: %s\n", message);
    } else {
        fputs("Error: an unspecified error occurred.\n", stderr);
    }
}

void error_report_errno(const char *operation) {
    int error_number = errno;
    const char *message = strerror(error_number);

    if (operation != NULL) {
        fprintf(stderr, "Error: %s: %s\n", operation, message);
    } else {
        fprintf(stderr, "Error: %s\n", message);
    }
}