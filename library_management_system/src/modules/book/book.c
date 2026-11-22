#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book.h"

void addBook(struct Book* books, int* count) {
    int enter_book_count;

    printf("How many books do you want to add? ");
    scanf("%d", &enter_book_count);
    while(*count < enter_book_count) {
        // Code to add a book
        int start = *count + 1;

        snprintf(books[*count].id, sizeof(books[*count].id), "B%03d", start);
        
        printf("Enter book title: ");
        scanf(" %[^\n]", books[*count].title);

        printf("Enter book author: ");
        scanf(" %[^\n]", books[*count].author);

        printf("Enter publication year: ");
        scanf("%d", &books[*count].year);

        snprintf(books[*count].status, sizeof(books[*count].status), "available");
        (*count)++;

        printf("Book added successfully!\n");
    }
}

void viewBooks(struct Book* books, int count){
    if (count == 0){
        printf("no book available\n");
        return;
    }

    printf("List of Books:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %s\n", books[i].id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Year: %d\n", books[i].year);
        printf("Status: %s\n", books[i].status);
    }
}

int findBookById(struct Book* books, int count){
    int foundIndex = -1;
    char userChoiceID[sizeof books[0].id];
    printf("Enter the ID of the book you want to update: ");
    if (scanf("%19s", userChoiceID) != 1) {
        printf("Could not read the book ID.\n");
        return -1;
    }

    for (int i = 0; i < count; i++){
        if (strcmp(books[i].id, userChoiceID) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Book with ID %s not found.\n", userChoiceID);
        return -1;
    }
    return foundIndex;
}

void updateBook(struct Book* books, int count){
    if (count == 0){
        printf("no book available\n");
        return;
    }
    // Code to update book information
    int foundIndex = findBookById(books, count);
    if (foundIndex == -1) {
        return;
    }

    printf("What do you want to update?\n");
    printf("1. Title\n");
    printf("2. Author\n");
    printf("3. Publication Year\n");
    printf("Enter your choice: ");
    int updateChoice;
    scanf("%d", &updateChoice);

    switch (updateChoice) {
        case 1:
            printf("Enter new title: ");
            scanf(" %[^\n]", books[foundIndex].title);
            break;
        case 2:
            printf("Enter new author: ");
            scanf(" %[^\n]", books[foundIndex].author);
            break;
        case 3:
            printf("Enter new publication year: ");
            scanf("%d", &books[foundIndex].year);
            printf("\n\n");
            break;
        default:
            printf("Invalid choice. No updates made.\n");
            return;
    }

    printf("Book information updated successfully!\n");
}

void deleteBook(struct Book* books, int* count){
    if (*count == 0){
        printf("no book available\n");
        return;
    }
    // Code to delete a book
    int foundIndex = findBookById(books, *count);
    if (foundIndex == -1) {
        return;
    }

    for (int i = foundIndex; i < *count - 1; i++) {
        books[i] = books[i + 1];
    }
    (*count)--;

    printf("Book deleted successfully!\n");
}