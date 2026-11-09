#include <stdio.h>

typedef struct student{
    char name[20];
    char sex;
    char id[20];
    char address[20];
    char email[20];
    struct student *next;
}student;

void showStudent(student *ptr){
    printf("Name: %s\n", ptr->name);
    printf("Sex: %c\n", ptr->sex);
    printf("ID: %s\n", ptr->id);
    printf("Address: %s\n", ptr->address);
    printf("Email: %s\n", ptr->email);
}

void showTwo(student *stu2){
    printf("Name: %s\n", stu2->name);
    printf("Sex: %c\n", stu2->sex);
    printf("ID: %s\n", stu2->id);
    printf("Address: %s\n", stu2->address);
    printf("Email: %s\n", stu2->email);
}

int main(void){

    student stu1 = {"John", 'M', "123456", "123 Street", "john@gmail.com"};
    student stu2 = {"Mary", 'F', "654321", "456 Avenue", "mary@gmail.com"};
    student *ptr = &stu1;
    student *stu2_ptr = &stu2;

    ptr->next = stu2_ptr;

    printf("Student 1:\n");
    printf("Name: %s\n", ptr->name);

    printf("Student 2:\n");
    printf("Name: %s\n", stu2_ptr->name);

    showStudent(ptr);

    showTwo(stu2_ptr);

    return 0;
}