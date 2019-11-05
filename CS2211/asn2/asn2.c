#include <stdio.h>

float exp_calculator(float a, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n % 2 == 0 && n > 0)
	{
		return exp_calculator(a, n / 2) * exp_calculator(a, n / 2);
	}
	else if (n % 2 == 1 && n > 0)
	{
		return exp_calculator(a, ((n - 1) / 2)) * a * exp_calculator(a, ((n - 1) / 2));
	}
}

int main()
{
	float base;
	int exponent;
	int checkBase = 0;

	printf("Initializing exp_calculator...\n");

	while (checkBase == 0)
	{
		printf("Enter a base: ");
		scanf(" %f", &base);
		if (base > 0)
		{
			checkBase = 1;
		}
		else
		{
			printf("invalid base. Enter a base greater than 0.");
		}
	}

	printf("Enter an exponent: ");
	scanf(" %d", &exponent);

	float calcExp = exp_calculator(base, exponent);
	printf ("%f", calcExp);

	return 0;
}
