#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TemperatureTracker {
    float temperature;
    char unit;
    char date[11];
};

int main(void)
{
    int init_capacity = 2;
    int i = 0;

    struct TemperatureTracker *tracker =
        malloc(init_capacity * sizeof(struct TemperatureTracker));

    if (tracker == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (1)
    {
        // Check whether the allocated memory is full
        if (i == init_capacity)
        {
            char choice;

            printf("Can you enter more temperature data? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'n' || choice == 'N')
            {
                break;
            }

            int new_capacity;

            printf("Enter additional capacity: ");
            scanf("%d", &new_capacity);

            if (new_capacity <= 0)
            {
                printf("Invalid capacity\n");
                continue;
            }

            int new_capacity_total = init_capacity + new_capacity;

            struct TemperatureTracker *temp =
                realloc(tracker,
                        new_capacity_total * sizeof(struct TemperatureTracker));

            if (temp == NULL)
            {
                printf("Memory reallocation failed\n");
                free(tracker);
                return 1;
            }

            tracker = temp;
            init_capacity = new_capacity_total;

            printf("Memory reallocation successful. New capacity: %d\n",
                   init_capacity);
        }

        printf("\nEnter Temperature (float): ");
        scanf("%f", &tracker[i].temperature);

        printf("Enter Unit (C/F): ");
        scanf(" %c", &tracker[i].unit);

        printf("Enter Date (YYYY-MM-DD): ");
        scanf("%10s", tracker[i].date);

        i++;
    }

    printf("\n--- Temperature Records ---\n");

    for (int j = 0; j < i; j++)
    {
        printf("%.2f %c - %s\n",
               tracker[j].temperature,
               tracker[j].unit,
               tracker[j].date);
    }

    free(tracker);
    tracker = NULL;

    return 0;
}