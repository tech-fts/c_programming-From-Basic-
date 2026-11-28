#include <stdio.h>
#include <string.h>
#include "../include/borrowing.h"

void test_create_borrow() {
    struct BorrowID borrow[10];
    int count = 0;
    int capacity = 10;

    create_borrow(borrow, &count, capacity);
    if (count != 1) {
        printf("test_create_borrow failed: expected count 1, got %d\n", count);
    } else {
        printf("test_create_borrow passed\n");
    }
}

void test_view_borrow() {
    struct BorrowID borrow[10];
    int count = 0;
    int capacity = 10;

    create_borrow(borrow, &count, capacity);
    view_borrow(borrow, &count);

    if (count != 1) {
        printf("test_view_borrow failed: expected count 1, got %d\n", count);
    } else {
        printf("test_view_borrow passed\n");
    }
}

void test_update_borrow() {
    struct BorrowID borrow[10];
    int count = 0;
    int capacity = 10;

    create_borrow(borrow, &count, capacity);
    update_borrow(borrow, &count);

    if (strcmp(borrow[0].status, "Updated") != 0) {
        printf("test_update_borrow failed: expected status 'Updated', got '%s'\n", borrow[0].status);
    } else {
        printf("test_update_borrow passed\n");
    }
}

void test_delete_borrow() {
    struct BorrowID borrow[10];
    int count = 0;
    int capacity = 10;

    create_borrow(borrow, &count, capacity);
    delete_borrow(borrow, &count);
    if(count != 0) {
        printf("test_delete_borrow failed: expected count 0, got %d\n", count);
    } else {
        printf("test_delete_borrow passed\n");
    }
}

int main(){
    test_create_borrow();
    test_view_borrow();
    test_update_borrow();
    test_delete_borrow();
    return 0;
}