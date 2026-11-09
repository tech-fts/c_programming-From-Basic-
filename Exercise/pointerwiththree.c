#include <stdio.h>
#include <time.h>

typedef struct Income{
    char name[20];
    float income;
    char unit[10];
    char description[20];
    time_t date;
    struct Income *next;
}Income;

void showIncomePointer(Income *ptr){
    printf("Name: %s\n", ptr->name);
    printf("Income: %.2f\n", ptr->income);
    printf("Unit: %s\n", ptr->unit);
    printf("Description: %s\n", ptr->description);
    printf("Date: %s", ctime(&ptr->date));
}

void showIncome(Income income){
    printf("Name: %s\n", income.name);
    printf("Income: %.2f\n", income.income);
    printf("Unit: %s\n", income.unit);
    printf("Description: %s\n", income.description);
    printf("Date: %s", ctime(&income.date));
}

int main (void){

    Income income1 = {"Salary", 5000.0, "USD", "Monthly salary", time(NULL), NULL};
    Income income2 = {"Freelance", 2000.0, "USD", "Freelance work", time(NULL), NULL};

    Income *ptr1 = &income1;
    Income *ptr2 = &income2;

    printf("Income 1:\n");
    showIncomePointer(ptr1);

    printf("Income 2:\n");
    showIncomePointer(ptr2);

    ptr1->next = ptr2; // Link income1 to income2 why linked?
    ptr2->next = NULL; // Set income2's next to NULL

    printf("Income 1's next income:\n");
    showIncomePointer(ptr1->next);

    return 0;
}