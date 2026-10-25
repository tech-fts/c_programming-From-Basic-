#include <stdio.h>

int main () {
   int t; char groupA = 'A', groupB = 'B';
   for (t = (4*3600); t <= 24 * 3600; t += (4*3600)){
	   printf("electricity %i\n", t/(4*3600));
	   printf("current time is %i hour \n", t/3600);

	   if ( t/(4*3600) % 2){
		   printf("start of the electricity is %c\n", groupA);
	   }else{
		   printf("start of the electricity is %c\n", groupB);
	   }
    }
   printf("This is end of the day");	
   return 0;
}
