#include <stdio.h>

int main(void)
{
    float ori_price = 20000.0;
    float dis_percent = 0.2;

    printf("Original price %.2f\n", ori_price);

    float *new_price = &ori_price;

    float dis_price = *new_price * dis_percent;

    printf("Dis Price %.2f",dis_price);

    return 0;
}