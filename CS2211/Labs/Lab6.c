#include <stdio.h>

int pt2()
{
	int int1, int2, int3, int4, max, min, min2, max2;

	printf("Enter 4 integers: \n");
	scanf(" %d %d %d %d", &int1, &int2, &int3, &int4);
	if (int2 > int1)
	{
		max = int2;
		min = int1;
	}
	else
	{
		max = int1;
		min = int2;
	}

	if (int3 > int4)
	{
		max2 = int3;
		min2 = int4;
	}
	else
	{
		max2 = int4;
		min2 = int3;
	}

	if (max2 > max)
	{
		max = max2;
	}

	if (min2 < min)
	{
		min = min2;
	}

	printf("max: %d\n", max);
	printf("min: %d\n", min);
	return 0;
}

int pt3()
{
	int days, start, dif;
	printf("Enter number of days in month: \n");
	scanf(" %d", &days);
	printf("Enter starting day of the week (1=Sun, 7=Sat):\n");
	scanf(" %d", &start);
	dif = (start - 1);

	for (int j = 0; j < dif; j++)
	{
		printf("    ");
	}

	int p = 7;

	for (int i = 1; i <= days; i++)
	{
		if (i < 10)
		{
			printf(" 0%d ", i);
		}
		else
		{
			printf(" %d ", i);
		}
		if (p - dif == i)
		{
			printf("\n");
			p += 7;
		}
		if (i==days){
			printf("\n");
		}
	}

	return 0;
}

int main()
{

	pt2();

	pt3();
}