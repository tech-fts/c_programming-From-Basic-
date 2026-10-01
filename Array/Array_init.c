#include <stdio.h>

int main()
{
	int array_value[10] = {1,2,3,4,5,6};
	int i;

	for(i=5; i<10; ++i)
	 array_value[i] = i*i;

	for(i=0; i<10; ++i)
	 printf("array_value[%i] = %i\n", i, array_value[i]);

	return 0;
}
