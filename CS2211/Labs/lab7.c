#include <stdio.h>

int sum_array(const int *a, int size)
{
	int sum = 0;
	while (*a < size)
	{
		sum += *a;
		a += 1;
	}

	return sum;
}
int sum_two_dimensional_array(const int *a, int n)
{
	int sum = 0;
	while (*a < n)
	{
		sum += *a;
		a += 1;
	}
	return sum;
}

int main()
{

	int arr[6] = {1,2,3,4,5,6};

	int pr = sum_array(arr,sizeof(arr));

	printf("%d\n", pr);


	int arr2[3][3] = {{3,2,1},{3,1,2},{5,2,1}};
	int pr2 = sum_two_dimensional_array(arr2,sizeof(arr2));

	return 0;
}