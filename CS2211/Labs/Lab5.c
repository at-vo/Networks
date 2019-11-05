#include <stdio.h>
#include <math.h>


int main(void)
{
    int x;
    printf("enter x value:");
    scanf("%d", &x);
    int eq = (3 * pow(x, 5)) + (2 * pow(x, 4)) - (5 * pow(x, 3)) - pow(x, 2) - 6;
    printf("%d\n", eq);

    int num1, denom1, num2, denom2, result_num, res_denom;

    printf("enter fractions: ");
    scanf(" %d/%d+", &num1, &denom1);
    scanf(" %d/%d", &num2, &denom2);

    result_num = (num1 * denom2) + (num2 * denom1);
    res_denom = denom1 * denom2;

    printf("the sum is %d/%d\n", result_num, res_denom);

    char numO, numT, numTH;
    printf("enter 3 digit number: \n");
    scanf(" %c %c %c", &numO, &numT, &numTH);
    printf("%c",numTH);
    printf("%c",numT);
    printf("%c",numO);


    return 0;
}
