#include <stdio.h>
#include "core/memory.h"
#include "book.h"
#include "member.h"
#include "borrowing.h"
#include "utils/input.h"
#include "storage/csv_reader.h"
#include "storage/csv_writer.h"
#include "modules/reports/reports.h"

void book_management(void);
void member_management(void);
void borrowing_management(void);

int main(void){
    printf("Welcome to the Library Management System!\n");

    for (;;) {
        printf("\nMain Menu:\n");
        printf("1. Book Management\n");
        printf("2. Member Management\n");
        printf("3. Borrowing Management\n");
        printf("0. Exit\n");
        int main_choice;
        InputResult input_result = input_read_int("Enter your choice: ", 0, 3, &main_choice);

        if (input_result == INPUT_EOF) {
            printf("\nInput ended. Exiting the program.\n");
            break;
        }
        if (input_result == INPUT_ERROR) {
            return 1;
        }
        if (input_result == INPUT_INVALID) {
            continue;
        }

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
                return 0;
        }
    }

    return 0;
}

void book_management(void) {
    int initial_capacity = 100; // Initial capacity for the book list
    struct Book* booklist = memory_allocate_zeroed((size_t)initial_capacity, sizeof *booklist);
    int book_count = 0;

    if(booklist == NULL) {
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

    memory_release(booklist);
}

void member_management(void) {
    int initial_capacity = 100; // Initial capacity for the member list
    struct Member* memberlist = memory_allocate_zeroed((size_t)initial_capacity, sizeof *memberlist);
    int member_count = 0;

    if(memberlist == NULL) {
        return;
    }

    read_members_from_csv(memberlist, &member_count, initial_capacity, "data/members.csv");

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
    write_members_to_csv(memberlist, member_count, "data/members.csv");
    memory_release(memberlist);
}

void borrowing_management(void) {
    // Code for borrowing management
    int initial_capacity = 100; // Initial capacity for the borrowing list
    struct BorrowID* borrowlist = memory_allocate_zeroed((size_t)initial_capacity, sizeof *borrowlist);
    int borrow_count = 0;

    if(borrowlist == NULL) {
        return;
    }

    read_borrows_from_csv(borrowlist, &borrow_count, initial_capacity, "data/borrowings.csv");

    int choice;
    do {
        printf("\nBorrowing Management Menu:\n");
        printf("1. Borrow a Book\n");
        printf("2. Return a Book\n");
        printf("3. View Borrowed Books\n");
        printf("4. Delete Borrowing Record\n");
        printf("5. Print Borrowing Report\n");
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
                update_borrow(borrowlist, &borrow_count);
                printf("Returning a book...\n");
                break;
            case 3:
                // Code to view borrowed books
                view_borrow(borrowlist, &borrow_count);
                printf("Viewing borrowed books...\n");
                break;
            
            case 4:
                // Code to delete a borrowing record
                delete_borrow(borrowlist, &borrow_count);
                printf("Deleting a borrowing record...\n");
                break;
            case 5:
                print_borrowing_report(borrowlist, borrow_count);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    printf("Borrowing management functionality is not implemented yet.\n");
    write_borrows_to_csv(borrowlist, borrow_count, "data/borrowings.csv");
    memory_release(borrowlist);
}