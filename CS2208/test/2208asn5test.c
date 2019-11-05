#include <stdio.h>

int power(int x, unsigned int n)
{
    int y;
    if (n == 0)
        return 1;

    if (n & 1)
        return x * power(x, n - 1);
    else
    {
        y = power(x, n >> 1);
        return y * y;
    }
}

int main()
{
    int x = 2;int n=4;
    int p = power(x,n);
    printf("%d",p);
}