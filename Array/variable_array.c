#include <stdio.h>

int main(void)
{
	int i, numfibs;
	printf("How Many Fibonacci do you want (between 1 and 75)?");
	scanf("%i", &numfibs);

	if(numfibs < 1 || numfibs > 75)
	{
		printf("Bad number, sorry!\n");
		return 1;
	}

	unsigned long long int Fibonacci[numfibs];

	Fibonacci[0] = 0;
	Fibonacci[1] = 1;

	for(i=2; i < numfibs; ++i)
	{
		Fibonacci[i] = Fibonacci[i-2] + Fibonacci[i-1];
	}

	for(i=0; i < numfibs; ++i)
	{
		printf("%1lu", Fibonacci[i]);
	}

	printf("\n");

	return 0;
}
