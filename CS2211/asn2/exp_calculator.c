#include <stdio.h>

/**
 * Exponent calculator method
 */
float exp_calculator(float a, int n)
{
	if (n == 0) // establish base case
	{
		return 1;
	}
	/* For Positive cases */
	else if (n % 2 == 0 && n > 0) // checks if n is even and greater than 0
	{

		return exp_calculator(a, n / 2) * exp_calculator(a, n / 2);
	}
	else if (n % 2 == 1 && n > 0) // checks if n is odd and greater than 0
	{

		return exp_calculator(a, ((n - 1) / 2)) * a * exp_calculator(a, ((n - 1) / 2));
	}

	/* For Negative Cases */
	else if (n < 0) // checks if n less than 0
	{
		return exp_calculator(1/a,-n);
	}
	
	
}

/* Main Function */ 
int main()
{

	/* Initialize Variables */
	float base;	
	float calcExp;	
	int exponent;
	int checkBase = 0;

	printf("Initializing exp_calculator...\n");

	while (checkBase == 0)
	{
		printf("Enter a base: ");
		scanf(" %f", &base); // assign base
		if (base > 0) // checks if base entered is greater than 0
		{
			checkBase = 1;
		}
		else
		{
			printf("invalid base. Enter a base greater than 0.\n");
		}
	}

	printf("Enter an exponent: ");
	scanf(" %d", &exponent); // assign exponent

	calcExp = exp_calculator(base, exponent);
	printf("%f", calcExp);

	return 0;
}
