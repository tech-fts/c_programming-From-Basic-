#include <stdio.h>
#include <string.h>
#include "../include/member.h"

void testAddMember() {
    struct Member members[10];
    int count = 0;
    int capacity = 10;

    addMember(members, &count, capacity);

    if (count != 1) {
        printf("testAddMember failed: Expected count 1, got %d\n", count);
    } else {
        printf("testAddMember passed\n");
    }
}

void testViewMembers() {
    struct Member members[10];
    int count = 0;
    int capacity = 10;

    addMember(members, &count, capacity);
    viewMembers(members, count);

    if (count != 1) {
        printf("testViewMembers failed: Expected count 1, got %d\n", count);
    } else {
        printf("testViewMembers passed\n");
    }
}

void testUpdateMember() {
    struct Member members[10];
    int count = 0;
    int capacity = 10;

    addMember(members, &count, capacity);
    updateMember(members, count);

    if (strcmp(members[0].name, "Updated Name") != 0) {
        printf("testUpdateMember failed: Expected name 'Updated Name', got '%s'\n", members[0].name);
    } else {
        printf("testUpdateMember passed\n");
    }
}

void testDeleteMember() {
    struct Member members[10];
    int count = 0;
    int capacity = 10;

    addMember(members, &count, capacity);
    deleteMember(members, &count);

    if (count != 0) {
        printf("testDeleteMember failed: Expected count 0, got %d\n", count);
    } else {
        printf("testDeleteMember passed\n");
    }
}

int main(){
    testAddMember();
    testViewMembers();
    testUpdateMember();
    testDeleteMember();
    return 0;
}