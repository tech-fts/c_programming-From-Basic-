#include <stdio.h>

#include "reports.h"

void print_borrowing_report(const struct BorrowID *borrowings, int count) {
    if (borrowings == NULL || count < 0) {
        fprintf(stderr, "Cannot print borrowing report: invalid borrowing data.\n");
        return;
    }

    printf("\nBorrowing Report\n");
    printf("================\n");
    printf("Total borrowing records: %d\n", count);

    if (count == 0) {
        printf("No borrowing records to report.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%s | Member: %s | Book: %s | Status: %s\n",
               borrowings[i].borrowing_id,
               borrowings[i].member_id,
               borrowings[i].book_id,
               borrowings[i].status);
    }
}