#include <stdio.h>
#include <string.h>
#include "matrix.h"

int main()
{
	Matrix matrix;
	matrix = matrix_construction();
	printf("Test 1: seeing if matrix is made and nothing is inside\n");
	if (matrix_isin(matrix, "tigger", "school") == '0')
		printf("Test 1 Passed\n");
	else
		printf("Test 1 failed\n");
	printf("Test 2: adding one item and seeing if it exists in the matrix, also prints (check manually)\n");
	matrix_set(matrix, "Timothy", "Goes", 0);
	if (matrix_isin(matrix, "Timothy", "Goes") == '1')
	{
		printf("Test 2 Passed\n");
	}
	else
		printf("Test 2 Failed\n");
	matrix_list(matrix);
	printf("Test 3: add multiple items to the matrix using matrix set, checks to see if all is in there and prints(check manually)\n");

	matrix_set(matrix, "co", "do", 2);
	matrix_set(matrix, "tigger", "bongo", 1);
	matrix_set(matrix, "dinosaur", "train", 5);
	matrix_set(matrix, "froggert", "doggert", 6);
	matrix_set(matrix, "Max", "ruby", 25);
	matrix_set(matrix, "Clifford", "redDog", 22);
	matrix_set(matrix, "Sponge", "bob", 9);
	matrix_set(matrix, "soggy", "doggy", 8);
	matrix_set(matrix, "Bugs", "Life", 2);
	matrix_set(matrix, "bugs", "life", 8);
	matrix_set(matrix, "Clifford", "Bob", 9);
	int check = 0;
	if (matrix_isin(matrix, "Timothy", "Goes") == '1')
		if (matrix_isin(matrix, "Bugs", "Life") == '1')
			if (matrix_isin(matrix, "co", "do") == '1')
				if (matrix_isin(matrix, "dinosaur", "train") == '1')
					if (matrix_isin(matrix, "Max", "ruby") == '1')
						if (matrix_isin(matrix, "soggy", "doggy") == '1')
							if (matrix_isin(matrix, "bugs", "life") == '1')
								if (matrix_isin(matrix, "tigger", "bongo") == '1')
									if (matrix_isin(matrix, "Clifford", "redDog") == '1')
										if (matrix_isin(matrix, "Sponge", "bob") == '1')
											if (matrix_isin(matrix, "Clifford", "Bob") == '1')
												if (matrix_isin(matrix, "froggert", "doggert") == '1')
												{
													check = 1;
													printf("Test 3 Passed\n");
												}

	if (check == 0)
		printf("Test 3 Failed if test\n");
	else
		matrix_list(matrix);

	printf("Test 4: overwrite a matrix using matrix set and increasing a matrix by matrix inc, try incing index not in matrix\n");
	matrix_set(matrix, "soggy", "doggy", 20);
	matrix_inc(matrix, "tigger", "bongo", 301);
	matrix_inc(matrix, "flower", "power", 30);
	Value *value1 = matrix_get(matrix, "soggy", "doggy");
	Value *value2 = matrix_get(matrix, "tigger", "bongo");
	if (*value1 == 20 && *value2 == 302)
		printf("Test 4 passed\n");
	else
		printf("Test 4 failed\n");
	printf("Value 1: %d, Value2: %d\n", *value1, *value2);
	matrix_list(matrix);
	printf("test 5, try to get index not in matrix\n");
	if (matrix_get(matrix, "dog", "frog") == NULL)
		printf("Test 5 passed\n");
	else
		printf("Test 5 failed\n");

	printf("seeing if all values are added and printing properly\n");
	matrix_list(matrix);
	matrix_destruction(matrix);
	return 0;
}
