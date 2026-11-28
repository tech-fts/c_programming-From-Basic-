#include <stdlib.h>
#include <stdio.h>
#include "csv_writer.h"
#include "../../include/member.h"
#include "../../include/borrowing.h"

void write_members_to_csv(struct Member *members, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fprintf(file, "Member ID,Name,Phone,Email,Address,Borrowed Books Count\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%d\n", members[i].member_id, members[i].name, members[i].phone, members[i].email, members[i].address, members[i].borrowed_books_count);
    }
    fclose(file);
}

void write_borrows_to_csv(struct BorrowID *borrows, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fprintf(file, "Borrow ID,Member ID,Book ID,ID,Address,Status\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", borrows[i].borrowing_id, borrows[i].member_id, borrows[i].book_id, borrows[i].ID, borrows[i].address, borrows[i].status);
    }
    fclose(file);
}