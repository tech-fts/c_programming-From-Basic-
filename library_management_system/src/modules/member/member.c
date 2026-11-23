#include <stdio.h>
#include <string.h>
#include "member.h"

void addMember(struct Member* members, int* count, int capacity) {
    int members_to_add;

    if (members == NULL || count == NULL || capacity < 0) {
        fprintf(stderr, "Cannot add members: invalid member storage.\n");
        return;
    }

    if (*count >= capacity) {
        printf("Member storage is full.\n");
        return;
    }

    printf("How many members do you want to add? ");
    if (scanf("%d", &members_to_add) != 1 || members_to_add <= 0) {
        printf("Enter a positive number of members.\n");
        return;
    }

    int added = 0;
    while (added < members_to_add && *count < capacity) {
        struct Member *member = &members[*count];
        int start = *count + 1;

        snprintf(member->member_id, sizeof member->member_id, "M%03d", start);
        
        printf("Enter member name: ");
        if (scanf(" %99[^\n]", member->name) != 1) {
            printf("Could not read the member name.\n");
            return;
        }

        printf("Enter member phone number: ");
        if (scanf(" %19[^\n]", member->phone) != 1) {
            printf("Could not read the member phone number.\n");
            return;
        }

        printf("Enter member email: ");
        if (scanf(" %99[^\n]", member->email) != 1) {
            printf("Could not read the member email.\n");
            return;
        }

        printf("Enter member address: ");
        if (scanf(" %199[^\n]", member->address) != 1) {
            printf("Could not read the member address.\n");
            return;
        }

        (*count)++;
        added++;

        printf("Member added successfully!\n");
    }

    if (added < members_to_add) {
        printf("Member storage is full; added %d member(s).\n", added);
    }
}

void viewMembers(struct Member* members, int count) {
    if (count == 0) {
        printf("No members available.\n");
        return;
    }

    printf("List of Members:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %s\n", members[i].member_id);
        printf("Name: %s\n", members[i].name);
        printf("Address: %s\n", members[i].address);
        printf("\n");
    }
}

int findMemberById(struct Member* members, int count){
    int foundIndex = -1;
    char userChoiceID[sizeof members[0].member_id];
    printf("Enter the ID of the member you want to update: ");
    if (scanf("%19s", userChoiceID) != 1) {
        printf("Could not read the member ID.\n");
        return -1;
    }

    for (int i = 0; i < count; i++){
        if (strcmp(members[i].member_id, userChoiceID) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Member with ID %s not found.\n", userChoiceID);
        return -1;
    }
    return foundIndex;
}

void updateMember(struct Member* members, int count) {
    if (count == 0) {
        printf("No members available.\n");
        return;
    }

    // Code to update member information
    int index = findMemberById(members, count);
    if (index == -1) {
        printf("Member not found.\n");
        return; // Member not found
    }

    int choice;
    printf("What would you like to update?\n");
    printf("1. Name\n");
    printf("2. Address\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return;
    }

    switch(choice){
        case 1:
            printf("Enter new name: ");
            if (scanf(" %99[^\n]", members[index].name) != 1) {
                printf("Could not read the member name.\n");
                return;
            }
            printf("Member name updated successfully!\n");
            break;
        case 2:
            printf("Enter new address: ");
            if (scanf(" %199[^\n]", members[index].address) != 1) {
                printf("Could not read the member address.\n");
                return;
            }
            break;
        case 3:
            printf("Enter new phone number: ");
            if (scanf(" %19[^\n]", members[index].phone) != 1) {
                printf("Could not read the member phone number.\n");
                return;
            }
            printf("Member phone number updated successfully!\n");
            break;
        case 4:
            printf("Enter new email: ");
            if (scanf(" %99[^\n]", members[index].email) != 1) {
                printf("Could not read the member email.\n");
                return;
            }
            break;
        case 5:
            printf("Enter new borrowed books count: ");
            if (scanf("%d", &members[index].borrowed_books_count) != 1) {
                printf("Could not read the borrowed books count.\n");
                return;
            }
            printf("Member borrowed books count updated successfully!\n");
            break;
        default:
            printf("Invalid choice. No updates made.\n");
            break;
    }
}

void deleteMember(struct Member* members, int* count) {
    if (*count == 0) {
        printf("No members available to delete.\n");
        return;
    }

    int index = findMemberById(members, *count);
    if (index == -1) {
        printf("Member not found.\n");
        return; // Member not found
    }

    // Shift members to remove the member at index
    for (int i = index; i < *count - 1; i++) {
        members[i] = members[i + 1];
    }
    (*count)--;

    printf("Member deleted successfully!\n");
}