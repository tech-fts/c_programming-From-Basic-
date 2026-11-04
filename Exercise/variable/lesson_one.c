#include <stdio.h>
#include <string.h>

int main (void)
{
    int         integerVar = 100;
    float       floatingVar = 331.79;
    double      doubleVar = 8.44e+11;
    char        charVar = 'W';
    char        multiCharVar [100] = "I am a enginner"; 
    _Bool       boolVar = 0;

    printf("IntegerVar = %i\n", integerVar);
    printf("floatingVar = %f\n", floatingVar);
    printf("doubleVar = %e\n", doubleVar);
    printf("doubleVar = %g\n", doubleVar);
    printf("charVar = %c\n", charVar);
    printf("Multi: %s\n", multiCharVar);

    printf("boolVar = %i\n", boolVar);

    return 0;
}