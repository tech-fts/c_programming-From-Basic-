#include <stdio.h>
#include <stdlib.h>
#include "modules/book/book.h"

void book_management(void);
void member_management(void);

int main(void){
    printf("Welcome to the Library Management System!\n");

    int main_choice;
    do {
        printf("\nMain Menu:\n");
        printf("1. Book Management\n");
        printf("2. Member Management\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &main_choice);

        switch (main_choice) {
            case 1:
                book_management();
                break;
            case 2:
                // Code for member management
                member_management();
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (main_choice != 0 && main_choice != 1);
    return 0;
}

void book_management(void) {
    int initial_capacity = 100; // Initial capacity for the book list
    struct Book* booklist = malloc(sizeof(struct Book) * initial_capacity);
    int book_count = 0;

    if(booklist == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add a Book\n");
        printf("2. View Books\n");
        printf("3. Update Book Information\n");
        printf("4. Delete a Book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(booklist, &book_count);
                break;
            case 2:
                // Code to view books
                printf("Viewing books...\n");
                break;
            case 3:
                // Code to update book information
                printf("Updating book information...\n");
                break;
            case 4:
                // Code to delete a book
                printf("Deleting a book...\n");
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

void member_management(void) {
    // Code for member management
    printf("Member management functionality is not implemented yet.\n");
}