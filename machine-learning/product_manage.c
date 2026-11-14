#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    char id[20];
    char name[100];
    char category[50];
    float unit_price;
    int stock;
    int min_stock;
};

int user_option(){
    int opt ;

    printf(" 0. Exit\n 1. add product\n 2. Disaply product\n 3. Search product\n 4. Update product:\n Enter your choice: ");
    scanf("%d", &opt);

    return opt;
}

void add_product(struct Product **pdlist, int *init_count, int *count){
    printf("\n\n ====== Adding Product List ======\n\n");
    
    while(1) {
        if(*count == *init_count){
            printf("Memory is full...\n");

            char more_add;
            int new_capacity, total_capacity;

            printf("Do you want to add more? enter y/n : ");
            scanf(" %c", &more_add);
            
            if (more_add == 'n' || more_add == 'N'){
                printf("no more product add...\n");
                return;
            }

            printf("Enter new capacity: ");
            scanf("%d", &new_capacity);

            if(new_capacity < 0){
                printf("Invalid capacity!\n");
                continue;
            }

            total_capacity = new_capacity + *init_count;

            int index = *count;

            struct Product *temp = realloc(*pdlist, total_capacity * sizeof(struct Product));

            *pdlist = temp;

            *init_count = total_capacity;
            *count = total_capacity;

        }
        snprintf((*pdlist)[*count].id,sizeof((*pdlist)[*count].id),"P%03d", count + 1);

        printf("Enter Name: ");
        getchar();

        fgets((*pdlist)[*count].name,sizeof((*pdlist)[*count].name), stdin);

        (*pdlist)[*count].name[strcspn((*pdlist)[*count].name, "\n")] = '\0';

        printf("Enter category: ");
        scanf("%49s", (*pdlist)[*count].category);

        printf("Enter unit price: ");
        scanf("%f", &(*pdlist)[*count].unit_price);

        printf("Enter stock: ");
        scanf("%d", &(*pdlist)[*count].stock);

        printf("Enter min stock: ");
        scanf("%d", &(*pdlist)[*count].min_stock);
        
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        (*count)++;

        printf("Product added successfully!\n");
    }
}

void display_product(struct Product **pdlist, int *count)
{
    if (pdlist == NULL || *pdlist == NULL || *count == 0) {
        printf("No products available!\n");
        return;
    }

    printf("\n====== View All Products ======\n");

    printf("%-10s %-20s %-15s %-12s %-10s %-10s\n",
           "ID", "Name", "Category", "Price", "Stock", "Min Stock");

    for (int i = 0; i < *count; i++)
    {
        printf("%-10s %-20s %-15s %-12.2f %-10d %-10d\n",
               (*pdlist)[i].id,
               (*pdlist)[i].name,
               (*pdlist)[i].category,
               (*pdlist)[i].unit_price,
               (*pdlist)[i].stock,
               (*pdlist)[i].min_stock);
    }
}

void user_action(int opt, struct Product **pdlist, int capacity, int *count)
{
    switch (opt)
    {
    case 1:
        add_product(pdlist, &capacity, count);
        break;
    
    case 2:
        display_product(pdlist, count);
        break;
    
    default:
        break;
    }
}

int main(void)
{
    int init_capacity = 2;
    int count = 0;

    struct Product *pdlist = malloc(init_capacity * sizeof(struct Product));

    if (pdlist == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1)
    {
        printf("\n====== Product Management ======\n\n");

        int useropt = user_option();

        if (useropt == 0) {
            printf("Exiting program...\n");
            break;
        }

        user_action(useropt, &pdlist, init_capacity, &count);
    }

    free(pdlist);
    return 0;
}