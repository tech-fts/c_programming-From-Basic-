#include <stdio.h>

typedef struct{
    char name[20];
    char sex;
    char id[20];
    char address[20];
    char email[20];
    int age;
}employee;

void show_employee(const employee *empr){
    printf("Name: %s\n", empr->name);
    printf("Sex: %c\n", empr->sex);
    printf("ID: %s\n", empr->id);
    printf("Address: %s\n", empr->address);
    printf("Email: %s\n", empr->email);
    printf("Age: %d\n\n", empr->age);
}

int main (void){

    employee emp1 = {"Alice", 'F', "E123", "789 Road", "john@gmail.com", 30};

    employee emp2 = {"Bob", 'M', "E456", "321 Lane", "hello@gmail.com", 25};


    employee *emp1_ptr = &emp1;
    employee *emp2_ptr = &emp2;

    show_employee(emp1_ptr);
    show_employee(emp2_ptr);
    return 0;
}