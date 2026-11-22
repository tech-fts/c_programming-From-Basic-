#include <stdio.h>

void swap_numbers(int *a , int *b)
{

    int temp = *a; //create pointer called temp
    *a = *b; //assign value of b to a
    *b = temp; //assign value of temp to b

    // why a is 20 and b is 10 after swapping? why number change?
    // After swapping, the values of `a` and `b` are 20 and 10 respectively

    printf("a is %d, b is %d", *a,*b); //print the swapped values

}

int main()
{
    int num_one = 10, num_two = 20;
    swap_numbers(&num_one, &num_two);
    return 0;
}