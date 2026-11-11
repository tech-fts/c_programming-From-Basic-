#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TemperatureTracker {
    float temperature;
    char unit;
    char date[11]; // Format: YYYY-MM-DD
};.

int main (void) 
{
    int init_capacity = 2, i =0;
    struct TemperatureTracker *tracker = (struct TemperatureTracker *)malloc(init_capacity * sizeof(struct TemperatureTracker) );
    if(tracker == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }


    while(i<=init_capacity)
    {
        if(i == init_capacity){
            char choice;
            printf("Can You enter more temperature data? (y/n): ");
            scanf(" %c", &choice);
            if(choice == 'n' || choice == 'N'){
                break;
            }

            int new_capacity;
            printf("Enter new capacity: ");
            scanf("%d", &new_capacity);
            tracker = realloc(tracker, (init_capacity + new_capacity) * sizeof(struct TemperatureTracker));
            printf("Memory reallocation successful. New capacity: %d\n", init_capacity + new_capacity);
            if(tracker == NULL)
            {
                printf("Memory reallocation failed\n");
                return 1;
            }
        }
        printf("Enter Temperature (float): ");
        scanf("%f", &tracker[i].temperature);

        printf("Enter Unit (C/F): ");
        scanf(" %c", &tracker[i].unit);

        printf("Enter Date (YYYY-MM-DD): ");
        scanf("%s", tracker[i].date);
        i++;
    }
    free(tracker);
    return 0;
}