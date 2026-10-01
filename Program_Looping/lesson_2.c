#include <stdio.h>

int main()
{
	int temp, u, v;

	printf("Pelase type in two nonnegative number.\n");
	scanf("%i%i", &u, &v);

	while(v != 0)
	{
		temp = u%v;
		u = v;
		v = temp;
	}

	printf("Their greatest commom divider is %i\n", u);
	return 0;
}
