#include <stdio.h>
int LEN = 3;
/* int sum_two_dimensional_array(int arr[][LEN], int n)
{
    int sum = 0;
    int *ptr;

    
    
    for (ptr = &arr[0][0]; *ptr <n; ptr++) {
        sum+=*ptr;
    }

    return sum;
} */

int main (){

    int arr2[2][3] = {{3,2,1},{4,1,2}};

	int pr2 = sum_two_dimensional_array(arr2,sizeof(arr2));

	printf("%d\n", pr2);

}