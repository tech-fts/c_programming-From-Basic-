#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

struct Book {
    char id[20];
    char title[100];
    char author[100];
    int year;
    char status[20];
};

void addBook(struct Book *books, int *count);
void viewBooks(struct Book *books, int count);
void updateBook(struct Book *books, int count);
void deleteBook(struct Book *books, int *count);

#endif