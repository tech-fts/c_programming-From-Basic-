#include <stdio.h>

void update_cost(float *cost){
    printf("Cost passing from main: %.2f\n", *cost);
}

void update_list(char *name, char *email){
    printf("Name passing from main: %s\n", name);
    printf("Email passing from main: %s\n", email);
}

int main(void) {
    char c = 'A';
    char *p = &c;
    printf("Value of c: %c\n", c); // why not use * in front of p if char type?
    printf("Value through pointer: %c\n", *p);

    int i = 10;
    int *q = &i;
    printf("Value of i: %d\n", i);
    printf("Value through pointer: %d\n", *q); // why * use front of q if integer type?

    float cost = 12000;
    update_cost(&cost);
    printf("Cost inside main: %.2f\n", cost);

    char name[20] = "John Doe";
    char email[50] = "john@gmail.com";

    char *name_ptr = name;

    update_list(name_ptr, email);

    printf("Name inside main: %s\n", name);
    printf("Email inside main: %s\n", email);
    return 0;
}