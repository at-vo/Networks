//
//  lab7p1.c
//  
//
//  Created by Tristan Tsvetanov on 2018-10-31.
//

#include <stdio.h>

int sum_array(int a[], int size)
{
    int sum = 0;
    int *arr = a;

    while (arr != &a[size]) {
        printf("%d\n", *arr);
        sum += *arr;
        arr++;
    }
    
    return sum;
    
    
}

int sum_two_dimensional_array(int a[][3], int n)
{
    int i, j, sum = 0;
    int *row[n];
    int *col;
    
    for ( i = 0; i < n; i++) {
        row[i] = a[i];
    }
    
    col = row[0];
    for ( i = 0; i < n; i++){
        for ( j = 0; j < n; j++){
            sum += *col;
            col++;
        }
        col = row[i];
    }
    
    return sum;
    
}


int main(){
    
//    int a1[11] = {1,2,3,4,5,6,7,8,9,10,11};
    int a1[3] = {1,2,3};

    int a2[3][3] = {{1,2,3},{1,2,3},{1,2,3}};

    
    printf("Sum is: %d\n", sum_array(a1, 3));
    printf("Sum is: %d\n", sum_two_dimensional_array(a2, 3));

    
    return 0;
}
