#ifndef BORROWING_H
#define BORROWING_H

struct Member;
struct Book;

struct BorrowID{
    char borrowing_id[20];
    char member_id[20];
    char book_id[20];
    char ID[20];
    char name[100];
    char date[100];
    char address[200];
    char status[100];
};

void create_borrow(struct BorrowID* borrow, int* count, int capacity);
void view_borrow(struct BorrowID* borrow, int* bo_count);
void update_borrow(struct BorrowID* borrow, int* bo_count);
void delete_borrow(struct BorrowID* borrow, int* bo_count);

#endif