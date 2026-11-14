
#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int age;
    float marks;
};

int main(void)
{
    int init_capacity = 2;
    int i = 0;

    struct Student *std_list =
        malloc(init_capacity * sizeof(struct Student));

    if (std_list == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Initial Capacity: %d\n", init_capacity);

    while (1)
    {
        if (i == init_capacity) {
            printf("\nMemory is Full!\n");

            char more_opt;
            int new_capacity;

            printf("Do you want to add more students? (y/n): ");
            scanf(" %c", &more_opt);

            if (more_opt == 'n' || more_opt == 'N') {
                break;
            }

            if (more_opt != 'y' && more_opt != 'Y') {
                printf("Invalid choice!\n");
                continue;
            }

            printf("Enter additional capacity: ");
            if (scanf("%d", &new_capacity) != 1 || new_capacity <= 0) {
                printf("Invalid capacity!\n");
                free(std_list);
                return 1;
            }

            int new_capacity_total =
                init_capacity + new_capacity;

            struct Student *temp = realloc(
                std_list,
                new_capacity_total * sizeof(struct Student)
            );

            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                free(std_list);
                return 1;
            }

            std_list = temp;
            init_capacity = new_capacity_total;

            printf("Memory reallocation successful!\n");
            printf("New capacity: %d\n", init_capacity);
        }

        printf("\nEnter student name: ");
        scanf("%49s", std_list[i].name);

        printf("Enter student age: ");
        scanf("%d", &std_list[i].age);

        printf("Enter student marks: ");
        scanf("%f", &std_list[i].marks);

        i++;
    }

    printf("\n===== Avrage marks for students =====\n");

    float total_marks , average_mark;

    for(int j = 0; j < i; j++){
        printf("\nName: %s", std_list[j].name);
        printf("\nAge: %d", std_list[j].age);
        printf("\nMarks: %.2f\n", std_list[j].marks);

        total_marks += std_list[j].marks;
    }

    printf("\n====== Average Marks for each student ======\n");

    average_mark = total_marks/i;
    printf("Average mark is: %.2f\n", average_mark);

    float highest_mark = std_list[0].marks;
    float lowest_mark = std_list[0].marks;
    
    for(int j = 0; j < i; j++){
        if (std_list[j].marks > highest_mark){
            highest_mark = std_list[j].marks;
        }

        if (std_list[j].marks < lowest_mark){
            lowest_mark = std_list[j].marks;
        }
    }

    printf("Highest marks is : %.2f\n", highest_mark);
    printf("Lowest marks is : %.2f\n", lowest_mark);

    printf("\n====== Collect lowest and highest mark ======\n");

    int lowest_count , highest_count = 0 , pass_count, failed_count;
    for(int j = 0; j < i; j++){
        if (std_list[j].marks < 40){
            lowest_count += 1;
            failed_count += 1;
        }

        if (std_list[j].marks > 40){
            highest_count += 1;
            pass_count += 1;
        }
    }

    printf("Highest marks student is: %d\n", highest_count);
    printf("Lowest marks student is: %d\n", lowest_count);

    printf("\n====== passed students and failed students ======\n");

    printf("Passed students are: %d\n",pass_count );
    printf("Failed students are: %d\n", failed_count);

    // // Display student records
    // printf("\n===== Student Records =====\n");

    // float total_marks = 0;
    // int highest_index = 0;

    // for (int j = 0; j < i; j++) {
    //     printf("\nName: %s", std_list[j].name);
    //     printf("\nAge: %d", std_list[j].age);
    //     printf("\nMarks: %.2f\n", std_list[j].marks);

    //     total_marks += std_list[j].marks;

    //     if (std_list[j].marks >
    //         std_list[highest_index].marks) {
    //         highest_index = j;
    //     }
    // }

    // if (i > 0) {
    //     printf("\nAverage Marks: %.2f\n", total_marks / i);

    //     printf("Highest Marks: %s (%.2f)\n",
    //            std_list[highest_index].name,
    //            std_list[highest_index].marks);
    // } else {
    //     printf("\nNo student records entered.\n");
    // }

    free(std_list);
    std_list = NULL;

    return 0;
}
