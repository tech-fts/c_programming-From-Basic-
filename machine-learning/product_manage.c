#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Product {
    char id[100];
    char name[100];
    char category[50];
    float unit_price;
    int stock;
    int min_stock;
};

struct Sale {
    char id[100];
    char name[100];
    float sale_price;
    int quantity;
    char sale_date[100];
};

char date[30];

void inventory_static(struct Product **pdlist,int *pd_count,struct Sale **salelist,int *sale_count){
    if(*pd_count == 0 || *sale_count == 0){
        printf("Invalid inventory ");
        return;
    }

    int total_product = 0;
    float total_inv_amount;
    for (int i = 0; i < *pd_count; i++ ){
        total_product += (*pdlist)[i].stock;
        total_inv_amount += (*pdlist)[i].unit_price;

        if((*pdlist)[i].stock < (*pdlist)[i].min_stock){
            printf("%s is low stock", (*pdlist)[i].name);
        }
    }
}

void file_writing(struct Sale **salelist){
    FILE *fptr = fopen("sale.csv", "a");

    if(fptr == NULL){
        printf("cannot open csv file!!!");
        return;
    }

    fseek(fptr, 0, SEEK_END); //checking file is empty

    if (ftell(fptr) == 0) {
        fprintf(fptr, "id,name,sale_price,quantity,sale_date\n");
    }

    fprintf(fptr, "%s,%s,%.2f,%d,%s\n",
    (*salelist)[i].id,
    (*salelist)[i].name,
    (*salelist)[i].sale_price,
    (*salelist)[i].quantity,
    (*salelist)[i].sale_date);

    fclose(fptr);
}

int user_option(void) {
    int opt;

    printf("1. Add product\n");
    printf("2. Display product\n");
    printf("3. Search product\n");
    printf("4. Update product\n");
    printf("5. Sell product\n");
    printf("6. Inventory Statistics\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &opt);

    return opt;
}

void display_time(time_t new_time, char *date, size_t size)
{
    struct tm *local_time = localtime(&new_time);

    if (local_time == NULL) {
        printf("Invalid time!\n");
        return;
    }

    if (strftime(date, size, "%d-%m-%Y %H:%M:%S",
                 local_time) == 0) {
        printf("Date formatting failed!\n");
        return;
    }
}

void stock_management(struct Sale **salelist,struct Product **pdlist,int *pd_count,int *sale_count)
{
    if (*salelist == NULL  || *pdlist == NULL || sale_count == NULL) {
        printf("Invalid list!\n");
        return;
    }

    int new_stock;

    for (int i = 0; i < *sale_count; i++) {
        for(int j=0; j< *pd_count; j++){
            if (strcmp((*salelist)[i].name, (*pdlist)[j].name) == 0){
                printf("product stock is %d and sale stock is %d\n",(*pdlist)[j].stock ,(*salelist)[i].quantity);
                new_stock = (*pdlist)[j].stock - (*salelist)[i].quantity;
                (*pdlist)[j].stock = new_stock;
                printf("new stock for product list is %d\n",(*pdlist)[j].stock);
            }
            if((*pdlist)[j].stock < (*pdlist)[j].min_stock){
                printf("Low stock alert!!!! for %99s", (*pdlist)[j].name);
            }
        }
    }
}

void sale_product(struct Sale **salelist,struct Product **pdlist, int *pd_count, int *sale_count,int *sale_capacity)
{
    if (*salelist == NULL || *pdlist == NULL) {
        printf("Invalid list!\n");
        return;
    }

    if( *pd_count == 0){
        printf("no product to sale!!!");
        return;
    }

    int count = *sale_count;

    if (count >= *sale_capacity) {

        printf("Sales capacity is full!\n");

        char sale_option;
        int sale_new_capacity;

        printf("Do you want to extend sales list? (y/n): ");
        if (scanf(" %c", &sale_option) != 1) {
            return;
        }

        if (sale_option == 'n' || sale_option == 'N') {
            return;
        }

        if (sale_option != 'y' && sale_option != 'Y') {
            printf("Invalid option!\n");
            return;
        }

        printf("Enter additional capacity: ");
        if (scanf("%d", &sale_new_capacity) != 1 ||
            sale_new_capacity <= 0) {
            printf("Invalid capacity!\n");
            return;
        }

        int new_total = *sale_capacity + sale_new_capacity;

        struct Sale *temp = realloc(
            *salelist,
            new_total * sizeof(struct Sale)
        );

        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        *salelist = temp;
        *sale_capacity = new_total;
    }

    count = *sale_count;

    snprintf((*salelist)[count].id,
             sizeof((*salelist)[count].id),
             "S%03d", count + 1);

    printf("Enter product name for sale: ");
    if (scanf("%99s", (*salelist)[count].name) != 1) {
        return;
    }

    printf("Enter sale price: ");
    if (scanf("%f", &(*salelist)[count].sale_price) != 1) {
        return;
    }

    printf("Enter quantity of product: ");
    if (scanf("%d", &(*salelist)[count].quantity) != 1) {
        return;
    }

    if((*salelist)[count].quantity == 0){
        printf("no more product to sale!!!");
        return;
    }

    time_t current_time = time(NULL);

    display_time(current_time,(*salelist)[count].sale_date,
        sizeof((*salelist)[count].sale_date)
    );

    (*sale_count)++;

    file_writing(salelist);

    printf("Sale successfully created!\n");

    stock_management(salelist, pdlist, pd_count, sale_count);
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

int add_product(struct Product **pdlist, int *init_count, int *count){
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
                return 1;
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
                return 1;
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
    return *count;
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
        
        if((*pdlist)[i].stock < (*pdlist)[i].min_stock){
                printf("Low stock alert!!!! for %99s\n", (*pdlist)[i].name);
        }
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
            sale_product(salelist,pdlist,count,sale_count,sale_capacity);
            break;
        
        case 6:
            inventory_static(pdlist,count,salelist,sale_count);
            break;

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
    free(salelist);
    return 0;
}