#ifndef LIBRARY_BORROWING_H
#define LIBRARY_BORROWING_H

struct BorrowID {
    char borrowing_id[20];
    char member_id[20];
    char book_id[20];
    char ID[20];
    char address[200];
    char status[100];
};

void create_borrow(struct BorrowID *borrow, int *count, int capacity);
void view_borrow(struct BorrowID *borrow, int *count);
void update_borrow(struct BorrowID *borrow, int *count);
void delete_borrow(struct BorrowID *borrow, int *count);

#endif