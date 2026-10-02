#include <stdio.h>

int main()
{
	int ratingCounter[11], i, response;

	for( i=1; i < 10; ++i)
	{
		ratingCounter[i] = 0;
	}

	printf("Enter your response\n");

	while(1)
	{
		scanf("%i", &response);

		if(response >= 999)
		{
			break;
		}

		if(response < 1 || response > 10 )
		{
			printf("Bad response: %i\n", response);
		}else{
			ratingCounter[response];
		}
	}

	printf("\n\n Rating       Number of Response\n");
	printf("------------------------------\n");

	for(i = 1; i <= 10; ++i)
	{
		printf("%4i%4i\n", i, ratingCounter[i]);
	}

	return 0;


}
