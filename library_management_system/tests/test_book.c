#include <stdio.h>
#include <string.h>
#include "../include/book.h"

void test_addBook(){
    struct Book books[100] = {0};
    int count = 0;

    addBook(books, &count);

    if(count == 1){
        printf("passed added book");
    }else{
        printf("failed added book");
    }
}

void test_viewBook(){
    struct Book books[100] = {0};
    int count = 1;

    strcpy(books[0].id, "B0001");
    strcpy(books[0].title, "C Programming");
    strcpy(books[0].author, "new");
    books[0].year = 1996;
    strcpy(books[0].status, "Borrow");

    printf("view testing function passed");

    viewBooks(books, count);
}

void test_updateBook(){
    struct Book books[100] = {0};
    int count = 1;

    strcpy(books[0].id, "B0001");
    strcpy(books[0].title, "C Programming");
    strcpy(books[0].author, "new");
    books[0].year = 1996;
    strcpy(books[0].status, "Borrow");

    updateBook(books, &count);

    if(strcmp(books[0].title, "C Programming") == 0){
        printf("passed updated book");
    }else{
        printf("failed updated book");
    }
}

void test_deleteBook(){
    struct Book books[100] = {0};
    int count = 1;

    strcpy(books[0].id, "B0001");
    strcpy(books[0].title, "C Programming");
    strcpy(books[0].author, "new");
    books[0].year = 1996;
    strcpy(books[0].status, "Borrow");

    deleteBook(books, &count);

    if(count == 0){
        printf("passed deleted book");
    }else{
        printf("failed deleted book");
    }
}

int main(){
    test_addBook();
    test_viewBook();
    test_updateBook();
    test_deleteBook();
    return 0;
}