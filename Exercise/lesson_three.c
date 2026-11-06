#include <stdio.h>

#define MAX_list 5

struct shopping{
    char name[50];
    int count;
    float price;
};

void add_shooping_list(struct shopping list, struct shopping buy_list[], int list_count){
    if (list_count == 0){
        printf("Shopping list is empty.\n");
        return;
    }

    int count = 0;

    while (count < list_count ){
        printf("Enter name: ");
        scanf("%s", list.name);

        printf("Enter count for item: ");
        scanf("%i", &list.count);

        printf("Enter price for item: ");
        scanf("%f", &list.price);

        printf("name of the item is %s. count of the item is %i. price of the item is %.1f. \n", list.name, list.count, list.price);
        buy_list[count] = list;
        count++;
    }

}

int main(void){
    int option;
    struct shopping sh_li; struct shopping buy_list[MAX_list];
    printf("This is lesson three.\n");

    printf("Please enter 1 to buy: ");
    scanf("%i", &option);

    switch (option)
    {
    case 1:
        add_shooping_list(sh_li, buy_list, MAX_list);
        break;
    
    default:
        break;
    }
    return 0;
}