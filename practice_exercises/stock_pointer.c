#include <stdio.h>

int main(void){
    int stock = 100;
    printf("Original stock %d",stock );
    int *newstock = &stock;

    *newstock = 150;
    printf("new stock %d",*newstock );
    return 0;
}