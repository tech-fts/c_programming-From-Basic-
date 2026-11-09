#include <stdio.h>
#include <stdlib.h>

int main (void){
    int *ptr = malloc(3 * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Use the allocated memory
    ptr[0] = 42;
    printf("Value at ptr[0]: %d\n", ptr[0]);
    ptr[1] = 84;
    printf("Value at ptr[1]: %d\n", ptr[1]);
    ptr[2] = 126;
    printf("Value at ptr[2]: %d\n", ptr[2]);

    int *new_ptr = realloc(ptr, 5 * sizeof(int));
    if (new_ptr == NULL) {
        printf("Memory reallocation failed\n");
        free(ptr); // Free the original pointer if realloc fails
        return 1;
    }

    ptr = new_ptr; // Update ptr to point to the new memory block   
    new_ptr[3] = 168;
    printf("Value at ptr[3]: %d\n", ptr[3]);
    new_ptr[4] = 210;
    printf("Value at ptr[4]: %d\n", ptr[4]);


    free(ptr);
    ptr = NULL; // Avoid dangling pointer
    return 0;
}