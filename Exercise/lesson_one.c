#include <stdio.h>

int main () {
   int t; 
   char groupA = 'A', groupB = 'B'; 
   char statusA, statusB;

   for (t = (4*3600); t <= 24 * 3600; t += (4*3600)){
           printf("electricity %d\n", t/(4*3600));
           printf("current time is %d hour \n", t/3600);

           if ((t/(4*3600)) % 2){
                   printf("start of the electricity is %c\n", groupA);
           }else{
                   printf("start of the electricity is %c\n", groupB);
           }
    }
   printf("This is end of the day\n");

   // Added a space before %c to clear the input buffer
   printf("Status of the Electricity in %c: ", groupA);
   scanf(" %c", &statusA); 
   
   printf("Status of the Electricity in %c: ", groupB);
   scanf(" %c", &statusB);

   return 0;
}

