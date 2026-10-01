#include <stdio.h>
#include <stdbool.h>

int main()
{
	int p,i, prime[50], primeIndex = 2;
	bool isPrime;

	prime[0] = 2;
	prime[1] = 3;

	for(p=5; p <= 50; p = p+2)
	{
		isPrime = true;

		for(i=1; isPrime && p/ prime[i] >= prime[i]; i++)
		{
			if( p % prime[i] == 0 )
			{
				prime[primeIndex] = p;
				++primeIndex;
			}
		}
	}

	for(i=0; i < primeIndex; ++i)
	{
		printf("%i", prime[i]);
		printf("\n");
	}
	
	return 0;
}
