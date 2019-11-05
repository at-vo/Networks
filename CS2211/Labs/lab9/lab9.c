#include <stdio.h>

int main(void) {
    int i, n, sum;
    printf("Please input an integer: ");
    scanf("%d", n);
    printf("The integer just read is: %d\n", n);
    for (i=1; i<=n; i++ ) {
    sum += i;
    }
    printf("The sum from 1 to %d is %d\n", n, sum);
}

