#include <stdio.h>

int main()
{
	int numberOfGrades, i, grade;
	int gradeTotal = 0;
	int failureCount = 0;
	float average;

	printf("How many grade will you be entering?");
	scanf("%i", &numberOfGrades);

	for( i=0; i <= numberOfGrades; ++i)
	{
		printf("Enter grade %i: ", i);
		scanf("%i", &grade);

		gradeTotal = gradeTotal + grade;

		if(grade < 65)
		{
			++failureCount;
		}
	}

		average = (float) gradeTotal / numberOfGrades;

		printf("\nGrade average = %.2f\n", average);
		printf("Number of failures = %i\n", failureCount);
		return 0;
}

