#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/*
expese_tracker
day (format), time (auto get using function), name , cost, description
*/

/*
create array to store expense tracker
*/

/*
write view all expense tracker and view base on date
*/

typedef struct{
    char name[100];
    float cost;
    char desc[300];
    char created_time[20];
}expense_tracker;

int choose_option(){
        int option;

        printf("1: Enter to create expense tracker\n2: Enter to view all expense or based on date\n4: enter to exit: ");
        scanf("%i", &option);

        return option;
}

void get_current_time(expense_tracker *tracker)
{
    time_t current_time = time(NULL);
    struct tm *created = localtime(&current_time);

    strftime(
        tracker->created_time,sizeof(tracker->created_time),"%d-%m-%Y %H:%M:%S",created
    );
}

void create_expense_tracker(expense_tracker tracker, expense_tracker usage_list[], int list_count){

    if(usage_list == NULL){
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

        get_current_time(&tracker);
        usage_list[i] = tracker;
        i++;
    }
    

}

void view_expense_tracker(expense_tracker usage_list[], int list_count){

    if(usage_list == NULL){
        printf("There is no list count to view data!!");
        return;
    }

    int dayOption;

    while(1){
        int viewOption, i;
        printf("Enter to view list\n1: to view all list\n2: to view by date\n3: return to main menu ");
        scanf("%i", &viewOption);

        if(viewOption == 1){
            //view all list
            for(i=0; i<list_count; i++){
                printf("list of all tracker %s\n", usage_list[i].name);
            }
        }else if(viewOption == 2){
            for(i=0; i <list_count; i++){
                printf("Date list   \n%d %s\n",i+1, usage_list[i].created_time);
                printf("Please enter number to see list by day: ");
                scanf("%d", &dayOption);

                if (dayOption == i+1){
                    printf("name from list is %s.\n\n", usage_list[dayOption-1].name);
                }
            }
        }else if(viewOption == 3){
            printf("Return to main menu...\n");
            break;
        }
    }
}

int main (void)
{
    printf("This is daily expense tracker!!!\n");
    expense_tracker usage;
    int list_count;

    printf("Enter count to access the array: ");
    scanf("%i", &list_count);

    expense_tracker *expense_list = (expense_tracker *)malloc(sizeof(expense_tracker) * list_count);

    // I create memory manage using c expense_tracker usage_list[list_count];

    for(;;){
        int user_choose = choose_option();
        switch(user_choose){
            case 1:
                create_expense_tracker(usage, expense_list, list_count);
                break;
            
            case 2:
                view_expense_tracker(expense_list, list_count);
                break;

            case 4:
                printf("Program terminate....");
                return 0;
            
            default:
                break;
        }
    }
    return 0;
}