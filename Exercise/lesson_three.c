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

void view_shopping_list(struct shopping buy_list[], int list_count){
    if (list_count == 0){
        printf("Shopping list is empty.\n");
        return;
    }

    for (int i = 0; i < list_count; i++){
        printf("name of the item is %s. count of the item is %i. price of the item is %.1f. \n", buy_list[i].name, buy_list[i].count, buy_list[i].price);
    }
}

void search_by_index(struct shopping buy_list[], int list_count){
    if (list_count == 0){
        printf("Shopping list is empty.\n");
        return;
    }

    int index;
    printf("Enter index to search: ");
    scanf("%i", &index);

    if (index < 0 || index >= list_count){
        printf("Invalid index.\n");
        return;
    }

    //printf("name of the item is %s. count of the item is %i. price of the item is %.1f. \n", buy_list[index].name, buy_list[index].count, buy_list[index].price);

    for (int i = 0; i < list_count; i++){
        if (i == index){
            printf("name of the item is %s. count of the item is %i. price of the item is %.1f. \n", buy_list[i].name, buy_list[i].count, buy_list[i].price);
        }
    }
}

int main(void){
    int option;
    struct shopping sh_li; struct shopping buy_list[MAX_list];

    while (1){
        printf("Please enter 1 to buy \n 2 to view shopping list \n 3 to search by index \n 4 to exit: ");
        scanf("%i", &option);

        switch (option)
        {
        case 1:
            add_shooping_list(sh_li, buy_list, MAX_list);
            break;

        case 2:
            view_shopping_list(buy_list, MAX_list);
            break;
        
        case 3:
            search_by_index(buy_list, MAX_list);
            break;
        
        case 4:
            printf("Exiting the program.\n");
            return 0;
        
        default:
            break;
        }
    }

    return 0;
}