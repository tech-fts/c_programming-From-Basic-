#include <stdio.h>
#include <stdlib.h>

int user_asking(int stock)
{
    // Implementation for user asking
    printf("How many products? ");
    scanf("%d", &stock);
    return stock;
}

int main (void)
{
    int stock_count = 0, capacity = 2, i;
    int *stock = malloc(capacity * sizeof(int));
    
    stock_count = user_asking(stock_count);

    for (i = 0; i < stock_count; i++) {
        if (i >= capacity) {
            int newcapacity = stock_count - capacity;

            printf("New capacity needed: %d\n", newcapacity);

            printf("Reallocating memory for stock array...\n");

            printf("Enter new capacity: ");
            scanf("%d", &newcapacity);

            stock = realloc(stock, (capacity + newcapacity) * sizeof(int));
            capacity += newcapacity;
        }
        printf("Enter stock for product %d: ", i + 1);
        scanf("%d", &stock[i]);
    }



    free(stock);
    return 0;
}