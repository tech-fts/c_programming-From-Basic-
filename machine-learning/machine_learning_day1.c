#include <stdio.h>

typedef struct{
    float study_hour;
    float attance;
    int result;
}Student;

int main(void){

    Student students[5] = {
        {2,40,1},
        {3,50,1},
        {1,30,0},
        {4,60,1},
        {2,20,0}
    };

    float total_hour = 0;
    int passed = 0;

    for(int i = 0; i < 5; i++){
        total_hour += students[i].study_hour;
        if(students[i].result == 1){
            passed++;
        }

        printf("Student %d: %.0f hours studied, %.0f%%, %s\n", i+1, students[i].study_hour, students[i].attance, students[i].result ? "Pass" : "Fail" );
    }

    printf("\nAverage Study Hours: %.2f\n", total_hour /5);

    printf("Total Passed: %d\n", passed);
    printf("Total Failed: %d\n", 5-passed);

    return 0;
}