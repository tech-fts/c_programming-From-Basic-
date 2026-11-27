#ifndef LIBRARY_MEMBER_H
#define LIBRARY_MEMBER_H

struct Member {
    char member_id[20];
    char name[100];
    char phone[20];
    char email[100];
    char address[200];
    int borrowed_books_count;
};

void addMember(struct Member *members, int *count, int capacity);
void viewMembers(struct Member *members, int count);
void updateMember(struct Member *members, int count);
void deleteMember(struct Member *members, int *count);

#endif