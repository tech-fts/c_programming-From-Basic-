#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Product {
    char id[20];
    char name[100];
    char category[50];
    float unit_price;
    int stock;
    int min_stock;
};

struct Sale {
    char id[20];
    char name[100];
    float sale_price;
    int quantity;
    time_t sale_date;
};

int user_option(void) {
    int opt;

    printf("1. Add product\n");
    printf("2. Display product\n");
    printf("3. Search product\n");
    printf("4. Update product\n");
    printf("5. Sell product\n");
    printf("6. Low stock report\n");
    printf("7. Inventory Statistics\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &opt);

    return opt;
}

void display_time(time_t new_time)
{
    struct tm *local_time = localtime(&new_time);

    if (local_time == NULL) {
        printf("Invalid time");
        return;
    }

    char date[30];

    strftime(date, sizeof(date), "%d-%m-%Y %H:%M:%S", local_time);

    printf("%s\n", date);
}

void stock_management(struct Sale **salelist, struct Product **pdlist){
    if (salelist == NULL || *salelist == NULL) {
        printf("No more products to sell!\n");
        // struct Sale empty_sale = {0};
        return;
    }

}


struct Sale sale_product(
    struct Sale **salelist,
    struct Product **pdlist,
    int *sale_count,
    int *sale_capacity
)
{
    struct Sale empty_sale = {0};

    if (salelist == NULL || *salelist == NULL ||
        sale_count == NULL || sale_capacity == NULL) {

        printf("Invalid sales list!\n");
        return empty_sale;
    }

    int count = *sale_count;

    // Check capacity
    if (count >= *sale_capacity) {

        printf("Sales capacity is full!\n");

        char sale_option;
        int sale_new_capacity;

        printf("Do you want to extend sales list? (y/n): ");
        scanf(" %c", &sale_option);

        if (sale_option == 'n' || sale_option == 'N') {
            return empty_sale;
        }

        if (sale_option != 'y' && sale_option != 'Y') {
            printf("Invalid option!\n");
            return empty_sale;
        }

        printf("Enter additional capacity: ");
        scanf("%d", &sale_new_capacity);

        if (sale_new_capacity <= 0) {
            printf("Invalid capacity!\n");
            return empty_sale;
        }

        int new_total = *sale_capacity + sale_new_capacity;

        struct Sale *temp = realloc(
            *salelist,
            new_total * sizeof(struct Sale)
        );

        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return empty_sale;
        }

        *salelist = temp;
        *sale_capacity = new_total;
    }

    // Create sale
    snprintf((*salelist)[count].id,
             sizeof((*salelist)[count].id),
             "S%03d", count + 1);

    printf("Enter product name for sale: ");
    scanf("%99s", (*salelist)[count].name);

    printf("Enter sale price: ");
    scanf("%f", &(*salelist)[count].sale_price);

    printf("Enter quantity of product: ");
    scanf("%d", &(*salelist)[count].quantity);

    (*salelist)[count].sale_date = time(NULL);

    struct Sale new_sale = (*salelist)[count];

    (*sale_count)++;

    printf("Sale successfully created!\n");

    stock_management(salelist, pdlist);

    return new_sale;
}

void update_product(struct Product **pdlist, int *count) {

    if (pdlist == NULL || *pdlist == NULL || *count == 0) {
        printf("No products available to update!\n");
        return;
    }

    int found_index = -1;
    char search_name[100];
    char update_option[50];

    printf("\n====== Update Product ======\n");

    // Clear leftover newline before fgets
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter name to search product for update: ");
    fgets(search_name, sizeof(search_name), stdin);

    search_name[strcspn(search_name, "\n")] = '\0';

    // Search product
    for (int i = 0; i < *count; i++) {

        if (strcmp((*pdlist)[i].name, search_name) == 0) {
            found_index = i;
            break;
        }
    }

    // Check product found
    if (found_index == -1) {
        printf("Product not found!\n");
        return;
    }

    // Display product
    printf("\nProduct found!\n");

    printf("%-10s %-20s %-15s %-12s %-10s %-10s\n",
           "ID", "Name", "Category", "Price", "Stock", "Min Stock");

    printf("%-10s %-20s %-15s %-12.2f %-10d %-10d\n",
           (*pdlist)[found_index].id,
           (*pdlist)[found_index].name,
           (*pdlist)[found_index].category,
           (*pdlist)[found_index].unit_price,
           (*pdlist)[found_index].stock,
           (*pdlist)[found_index].min_stock);

    // Select update field
    printf("\nWhich field do you want to update?\n");
    printf("1. name\n");
    printf("2. category\n");
    printf("3. unit_price\n");
    printf("4. stock\n");
    printf("5. min_stock\n");
    printf("Enter field name: ");

    scanf("%49s", update_option);

    // Update selected field
    if (strcmp(update_option, "name") == 0) {

        printf("Enter new name: ");
        scanf(" %99[^\n]", (*pdlist)[found_index].name);

    } else if (strcmp(update_option, "category") == 0) {

        printf("Enter new category: ");
        scanf("%49s", (*pdlist)[found_index].category);

    } else if (strcmp(update_option, "unit_price") == 0) {

        printf("Enter new price: ");
        scanf("%f", &(*pdlist)[found_index].unit_price);

    } else if (strcmp(update_option, "stock") == 0) {

        printf("Enter new stock: ");
        scanf("%d", &(*pdlist)[found_index].stock);

    } else if (strcmp(update_option, "min_stock") == 0) {

        printf("Enter new min stock: ");
        scanf("%d", &(*pdlist)[found_index].min_stock);

    } else {

        printf("Invalid update option!\n");
        return;
    }

    printf("\nProduct updated successfully!\n");
}


void search_product(struct Product **pdlist, int *count) {
    if (pdlist == NULL || *pdlist == NULL || *count == 0) {
        printf("No products available to search!\n");
        return;
    }

    int found = 0;
    char search_name[100];

    printf("\n====== Search Product by Name ======\n");
    printf("Enter product name: ");
    scanf("%99s", search_name);

    printf("%-10s %-20s %-15s %-12s %-10s %-10s\n",
           "ID", "Name", "Category", "Price", "Stock", "Min Stock");

    for (int i = 0; i < *count; i++) {

        if (strcmp((*pdlist)[i].name, search_name) == 0) {

            printf("%-10s %-20s %-15s %-12.2f %-10d %-10d\n",
                   (*pdlist)[i].id,
                   (*pdlist)[i].name,
                   (*pdlist)[i].category,
                   (*pdlist)[i].unit_price,
                   (*pdlist)[i].stock,
                   (*pdlist)[i].min_stock);

            found = 1;
        }
    }

    if (found == 0) {
        printf("Product not found!\n");
    }
}

int create_category(struct Product **pdlist, int *count, char *current_category)
{
    int categoryOpt;

    printf("Enter same category: 1\n");
    printf("Enter different category: 2\n");
    printf("Enter your choice: ");
    scanf("%d", &categoryOpt);

    switch(categoryOpt)
    {
        case 1:
            printf("Enter category: ");
            scanf("%49s", current_category);

            strcpy((*pdlist)[*count].category, current_category);

            return 1;

        case 2:
            printf("Enter category: ");
            scanf("%49s", (*pdlist)[*count].category);

            return 0;

        default:
            printf("Invalid category option!\n");
            return -1;
    }
}

void add_product(struct Product **pdlist, int *init_count, int *count){
    printf("\n\n ====== Adding Product List ======\n\n");
    int same_category = 0, sameCategoryCount = 0;
    char current_category[50] = "";

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

            struct Product *temp = realloc(*pdlist,total_capacity * sizeof(struct Product));

            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                return;
            }

            *pdlist = temp;
            *init_count = total_capacity;

        }
        snprintf((*pdlist)[*count].id,sizeof((*pdlist)[*count].id),"P%03d", *count + 1);

        printf("Enter Name: ");
        getchar();

        fgets((*pdlist)[*count].name,sizeof((*pdlist)[*count].name), stdin);

        (*pdlist)[*count].name[strcspn((*pdlist)[*count].name, "\n")] = '\0';

        if (same_category == 0)
        {
            printf("\n===== Enter category (using one category or change category) =====\n");

            int result = create_category(pdlist, count, current_category);

            if (result == -1) {
                continue;
            }

            same_category = result;
        }
        else
        {
            strcpy((*pdlist)[*count].category, current_category);
        }

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

void user_action(
    int opt,
    struct Product **pdlist,
    int *capacity,
    int *count,
    struct Sale **salelist,
    int *sale_capacity,
    int *sale_count
)
{
    switch (opt)
    {
        case 1:
            add_product(pdlist, capacity, count);
            break;

        case 2:
            display_product(pdlist, count);
            break;

        case 3:
            search_product(pdlist, count);
            break;

        case 4:
            update_product(pdlist, count);
            break;

        case 5:
        {
            struct Sale new_sale = sale_product(
                salelist,
                pdlist,
                sale_count,
                sale_capacity
            );

            printf("Created sale: %s\n", new_sale.id);

            break;
        }

        default:
            printf("Invalid option!\n");
            break;
    }
}

int main(void)
{
    int init_capacity = 2;
    int count = 0;

    struct Product *pdlist = malloc(init_capacity * sizeof(struct Product));

    int sale_capacity = 2, sale_count = 0;
    struct Sale *salelist = malloc(sale_capacity * sizeof(struct Sale));

    if (pdlist == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    if (salelist == NULL){
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

        user_action(
            useropt,
            &pdlist,
            &init_capacity,
            &count,
            &salelist,
            &sale_capacity,
            &sale_count
        );
    }

    free(pdlist);
    return 0;
}