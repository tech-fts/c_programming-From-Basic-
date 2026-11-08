#include <stdio.h>
#include <time.h>
#include <string.h>

/*
expese_tracker
day (format), time (auto get using function), name , cost, description
*/

/*
create array to store expense tracker
*/

typedef struct{
    char name[100];
    float cost;
    char desc[300];
    char created_time[20];
}expense_tracker;

int choose_option(){
        int option;

        printf("1: Enter to create expense tracker\n 2: Enter to view all expense or based on date 4: enter to exit\n ");
        scanf("%i", &option);

        return option;
}

void get_current_time(expense_tracker tracker){
    time_t current_time = time(NULL);
    struct tm *created = localtime(&current_time);

    char formatted_time[20];

    strftime(formatted_time,sizeof(formatted_time),
        "%d-%m-%Y %H:%M:%S",created
    );

    strcpy(tracker.created_time, formatted_time);

    printf("Created time is %s\n", tracker.created_time);
}

void create_expense_tracker(expense_tracker tracker, expense_tracker usage_list[], int list_count){

    if(list_count == 0){
        printf("There is no list count to insert data!!");
        return;
    }
    int i = 0;
    while(i < list_count){
        printf("Enter name for your expense: ");
        scanf("%s", &tracker.name);

        printf("Enter cost for your expense: ");
        scanf("%f", &tracker.cost);

        printf("Enter descrption for your expense: ");
        scanf("%s", &tracker.desc);

        get_current_time(tracker);
        usage_list[i] = tracker;
        i++;
    }

}

int main (void)
{
    printf("This is daily expense tracker!!!\n");
    expense_tracker usage;
    int list_count;

    printf("Enter count to access the array: ");
    scanf("%i", &list_count);

    expense_tracker usage_list[list_count];

    for(;;){
        int user_choose = choose_option();
        switch(user_choose){
            case 1:
                create_expense_tracker(usage, usage_list, list_count);
                break;
            
            // case 2:
            //     view_all_expense_tracker(usage);
            //     break;

            case 4:
                printf("Program terminate....");
                return 0;
            
            default:
                break;
        }
    }
    return 0;
}