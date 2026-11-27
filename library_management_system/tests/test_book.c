#include <stdio.h>
#include <string.h>
#include "include\book.h"

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

    strcpy(books[0].id, "B0001");
    strcpy(books[0].title, "C Programming");
    strcpy(books[0].author, "new");
    books[0].year = 1996;
    strcpy(books[0].status, "Borrow");

    printf("view testing function passed");

    viewBooks(books, &count);
}

int main(){
    test_addBook();
    test_viewBook();
    return 0;
}