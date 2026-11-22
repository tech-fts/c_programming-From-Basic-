#ifndef BOOK_H
#define BOOK_H

struct Book {
    char id[20];
    char title[100];
    char author[100];
    int year;
    char status[20]; // e.g., "available", "checked out"
};

void addBook(struct Book* books, int* count);
void viewBooks(struct Book* books, int count);
void updateBook(struct Book* books, int count);
void deleteBook(struct Book* books, int* count);

#endif // BOOK_H