#include <stdio.h>
#include <stdlib.h>
#include "modules/book/book.h"
#include "modules/member/member.h"
#include "modules/borrowing/borrowing.h"

void book_management(void);
void member_management(void);
void borrowing_management(void);

int main(void){
    printf("Welcome to the Library Management System!\n");

    int main_choice;
    do {
        printf("\nMain Menu:\n");
        printf("1. Book Management\n");
        printf("2. Member Management\n");
        printf("3. Borrowing Management\n");
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
            case 3:
                // Code for borrowing management
                borrowing_management();
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
    int initial_capacity = 100; // Initial capacity for the member list
    struct Member* memberlist = malloc(sizeof(struct Member) * initial_capacity);
    int member_count = 0;

    if(memberlist == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    int choice;
    do
    {
        printf("\nMember Management Menu:\n");
        printf("1. Add a Member\n");
        printf("2. View Members\n");
        printf("3. Update Member Information\n");
        printf("4. Delete a Member\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMember(memberlist, &member_count, initial_capacity);
                break;
            case 2:
                viewMembers(memberlist, member_count);
                break;
            case 3:
                updateMember(memberlist, member_count);
                break;
            case 4:
                deleteMember(memberlist, &member_count);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        /* code */
    } while (choice != 0);
    
    // Code for member management
    printf("Member management functionality is not implemented yet.\n");
}

void borrowing_management(void) {
    // Code for borrowing management
    int initial_capacity = 100; // Initial capacity for the borrowing list
    struct BorrowID* borrowlist = malloc(sizeof(struct BorrowID) * initial_capacity);
    int borrow_count = 0;

    if(borrowlist == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    int choice;
    do {
        printf("\nBorrowing Management Menu:\n");
        printf("1. Borrow a Book\n");
        printf("2. Return a Book\n");
        printf("3. View Borrowed Books\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Code to borrow a book
                create_borrow(borrowlist, &borrow_count, initial_capacity);
                printf("Borrowing a book...\n");
                break;
            case 2:
                // Code to return a book
                printf("Returning a book...\n");
                break;
            case 3:
                // Code to view borrowed books
                printf("Viewing borrowed books...\n");
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    printf("Borrowing management functionality is not implemented yet.\n");
}