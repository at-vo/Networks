#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int main()
{
    Matrix matrix = matrix_construction();
    char k1[365];
    char k2[365];
    char peek;
    scanf(""); // open buffer
    while (peek !='\n'){
        peek = getchar();
        if (peek=='\n'){ // check empty buffer
            break;
        }else{
            ungetc(peek,stdin); 
            scanf(" %s %s ", k1, k2); // assign string
            if (k1[0]!='\0'&& k2[0]!='\0'){ // check if empty string
                if (matrix_isin(matrix,k1,k2)=='1'){ // check occurrence
                    matrix_inc(matrix,k1,k2,1);
                }else{
                    matrix_set(matrix,k1,k2,1);
                }
            }else{
                break;
            }
        }
        k1[0]='\0';
        k2[0]='\0';
    }
    matrix_list(matrix); // print matrix
    matrix_destruction(matrix); // free memory

    return 0;
}
