#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_reader.h"
#include "../../include/member.h"
#include "../../include/borrowing.h"

enum { CSV_FIELD_COUNT = 6, CSV_LINE_SIZE = 512 };

static int split_csv_line(char *line, char *fields[CSV_FIELD_COUNT]) {
    line[strcspn(line, "\r\n")] = '\0';
    fields[0] = line;

    int field_count = 1;
    for (char *cursor = line; *cursor != '\0'; cursor++) {
        if (*cursor == ',') {
            if (field_count == CSV_FIELD_COUNT) {
                return 0;
            }
            *cursor = '\0';
            fields[field_count++] = cursor + 1;
        }
    }

    return field_count == CSV_FIELD_COUNT;
}

static int copy_csv_field(char *destination, size_t destination_size, const char *source) {
    size_t length = strlen(source);
    if (length >= destination_size) {
        return 0;
    }
    memcpy(destination, source, length + 1);
    return 1;
}

static int parse_nonnegative_int(const char *text, int *value) {
    char *end;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (text == end || *end != '\0' || errno == ERANGE || parsed < 0 || parsed > INT_MAX) {
        return 0;
    }
    *value = (int)parsed;
    return 1;
}

static int valid_arguments(const void *records, const int *count, int capacity, const char *filename) {
    return records != NULL && count != NULL && filename != NULL &&
           capacity >= 0 && *count >= 0 && *count <= capacity;
}

void read_members_from_csv(struct Member *members, int *count, int capacity, const char *filename) {
    if (!valid_arguments(members, count, capacity, filename)) {
        fprintf(stderr, "Cannot read members: invalid buffer, count, capacity, or filename.\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    char line[CSV_LINE_SIZE];
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return;
    }

    int line_number = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (*count == capacity) {
            fprintf(stderr, "Member CSV capacity (%d) reached; remaining rows were not read.\n", capacity);
            break;
        }

        char *fields[CSV_FIELD_COUNT];
        struct Member member = {0};
        if (split_csv_line(line, fields) &&
            copy_csv_field(member.member_id, sizeof member.member_id, fields[0]) &&
            copy_csv_field(member.name, sizeof member.name, fields[1]) &&
            copy_csv_field(member.phone, sizeof member.phone, fields[2]) &&
            copy_csv_field(member.email, sizeof member.email, fields[3]) &&
            copy_csv_field(member.address, sizeof member.address, fields[4]) &&
            parse_nonnegative_int(fields[5], &member.borrowed_books_count)) {
            members[(*count)++] = member;
        } else {
            fprintf(stderr, "Skipping invalid member CSV row at line %d.\n", line_number);
        }
    }
    fclose(file);
}

void read_borrows_from_csv(struct BorrowID *borrows, int *count, int capacity, const char *filename) {
    if (!valid_arguments(borrows, count, capacity, filename)) {
        fprintf(stderr, "Cannot read borrowings: invalid buffer, count, capacity, or filename.\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    char line[CSV_LINE_SIZE];
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return;
    }

    int line_number = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (*count == capacity) {
            fprintf(stderr, "Borrowing CSV capacity (%d) reached; remaining rows were not read.\n", capacity);
            break;
        }

        char *fields[CSV_FIELD_COUNT];
        struct BorrowID borrowing = {0};
        if (split_csv_line(line, fields) &&
            copy_csv_field(borrowing.borrowing_id, sizeof borrowing.borrowing_id, fields[0]) &&
            copy_csv_field(borrowing.member_id, sizeof borrowing.member_id, fields[1]) &&
            copy_csv_field(borrowing.book_id, sizeof borrowing.book_id, fields[2]) &&
            copy_csv_field(borrowing.ID, sizeof borrowing.ID, fields[3]) &&
            copy_csv_field(borrowing.address, sizeof borrowing.address, fields[4]) &&
            copy_csv_field(borrowing.status, sizeof borrowing.status, fields[5])) {
            borrows[(*count)++] = borrowing;
        } else {
            fprintf(stderr, "Skipping invalid borrowing CSV row at line %d.\n", line_number);
        }
    }
    fclose(file);
}
