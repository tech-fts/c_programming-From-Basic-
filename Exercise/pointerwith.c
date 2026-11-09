#include <stdio.h>
#include <time.h>

struct Item{
    char name[20];
    int originalPrice;
    int salePrice;
    int quantity;
    char buyShopping;
    time_t date;
    struct Item *next;
};

typedef struct shoopingCart{
    int id;
    struct Item *itemList;
    int totalPrice;
}shoppingCart;

int main (void){

    struct Item item1 = {"Laptop", 1000, 800, 5, 'Y', time(NULL)};
    struct Item item2 = {"Phone", 500, 400, 10, 'N', time(NULL)};

    item1.next = &item2;

    printf("Item 1:\n");
    printf("Name(link list): %s\n", item1.name);

    printf("Item 2:\n");
    printf("Name(link list): %s\n", item2.name);

    struct Item *ptr = &item1;
    struct Item *item2_ptr = &item2;

    ptr->next = item2_ptr;

    printf("Item 1 ptr:\n");
    printf("Name(pointer): %s\n", ptr->name);

    printf("Item 2 ptr:\n");
    printf("Name(pointer): %s\n", item2_ptr->name);

    struct shoopingCart cart1 = {1, &item1, item1.salePrice + item2.salePrice};
    struct shoopingCart cart2 = {2, &item2, item2.salePrice};

    cart1.itemList->next = &item2;

    printf("Cart 1:\n");
    printf("Name: %s\n", cart1.itemList->name);

    printf("Cart 2:\n");
    printf("Name: %s\n", cart2.itemList->name);
    return 0;
}