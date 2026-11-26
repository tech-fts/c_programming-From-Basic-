#include <stdio.h>
#include "borrowing.h"

void create_borrow(struct BorrowID* borrowings, int* count, int capacity) {
    int borrowings_to_add;

    if (borrowings == NULL || count == NULL || capacity < 0) {
        fprintf(stderr, "Cannot add borrowings: invalid borrowing storage.\n");
        return;
    }

    if (*count >= capacity) {
        printf("Borrowing storage is full.\n");
        return;
    }

    printf("How many borrowings do you want to add? ");
    if (scanf("%d", &borrowings_to_add) != 1 || borrowings_to_add <= 0) {
        printf("Enter a positive number of borrowings.\n");
        return;
    }

    int added = 0;
    while (added < borrowings_to_add && *count < capacity) {
        struct BorrowID *borrowing = &borrowings[*count];
        int start = *count + 1;

        snprintf(borrowing->borrowing_id, sizeof borrowing->borrowing_id, "B%03d", start);
        
        printf("Enter member ID: ");
        if (scanf(" %99[^\n]", borrowing->member_id) != 1) {
            printf("Could not read the member ID.\n");
            return;
        }

        printf("Enter book ID: ");
        if (scanf(" %99[^\n]", borrowing->book_id) != 1) {
            printf("Could not read the book ID.\n");
            return;
        }

        (*count)++;
        added++;

        printf("Borrowing added successfully!\n");
    }
}

void view_borrow(struct BorrowID* borrowings, int* count) {
    if (borrowings == NULL || count == NULL || *count <= 0) {
        printf("No borrowings available to view.\n");
        return;
    }

    printf("List of Borrowings:\n");
    for (int i = 0; i < *count; i++) {
        printf("Borrowing ID: %s\n", borrowings[i].borrowing_id);
        printf("Member ID: %s\n", borrowings[i].member_id);
        printf("Book ID: %s\n", borrowings[i].book_id);
        printf("Status: %s\n", borrowings[i].status);
    }
}

void update_borrow(struct BorrowID* borrowings, int* count) {
    if (borrowings == NULL || count == NULL || *count <= 0) {
        printf("No borrowings available to update.\n");
        return;
    }

    char borrowing_id[20];
    printf("Enter the borrowing ID to update: ");
    if (scanf("%19s", borrowing_id) != 1) {
        printf("Could not read the borrowing ID.\n");
        return;
    }

    for (int i = 0; i < *count; i++) {
        if (strcmp(borrowings[i].borrowing_id, borrowing_id) == 0) {
            printf("Enter new status: ");
            if (scanf(" %99[^\n]", borrowings[i].status) != 1) {
                printf("Could not read the new status.\n");
                return;
            }
            printf("Borrowing updated successfully!\n");
            return;
        }
    }

    printf("Borrowing with ID %s not found.\n", borrowing_id);
}

void delete_borrow(struct BorrowID* borrowings, int* count) {
    if (borrowings == NULL || count == NULL || *count <= 0) {
        printf("No borrowings available to delete.\n");
        return;
    }

    char borrowing_id[20];
    printf("Enter the borrowing ID to delete: ");
    if (scanf("%19s", borrowing_id) != 1) {
        printf("Could not read the borrowing ID.\n");
        return;
    }

    for (int i = 0; i < *count; i++) {
        if (strcmp(borrowings[i].borrowing_id, borrowing_id) == 0) {
            for (int j = i; j < *count - 1; j++) {
                borrowings[j] = borrowings[j + 1];
            }
            (*count)--;
            printf("Borrowing deleted successfully!\n");
            return;
        }
    }

    printf("Borrowing with ID %s not found.\n", borrowing_id);
}