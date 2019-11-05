#include <stdio.h>
#include "matrix.h"

//Matrix construction using bstree ini()
Matrix matrix_construction(void){
    Matrix matrix; 
    matrix = bstree_ini();
    return matrix;
}

//If location (index1, index2) is defined in Matrix m, then return 1. Otherwise, return 0.
unsigned char matrix_isin(Matrix m, Index index1, Index index2){
    unsigned char toReturn;
    Key search = key_gen(index1,index2);
    Data check = bstree_search(m,search);
    if (check==NULL){
        toReturn = '0';
    }else{
        toReturn = '1';
    }
    key_free(search);
    return toReturn;
}

//If location (index1, index2) is defined in Matrix m, then return a pointer to the associated
//value. Otherwise, return NULL.
Value *matrix_get(Matrix m, Index index1, Index index2){
    Key search = key_gen(index1,index2);
    Value* toReturn = bstree_search(m,search);
    if (toReturn==NULL){
        toReturn = NULL;
    }
    key_free(search);
    return toReturn;
}

//Assign value to Matrix m at location (index1, index2). If that location already has value,
//then overwrite.
void matrix_set(Matrix m, Index index1, Index index2, Value value){
    unsigned char toChange = matrix_isin(m,index1,index2);
    if (toChange=='0'){
        Key toIns = key_gen(index1,index2);
        Data val = data_gen(value);
        bstree_insert(m,toIns,val);
    }else{
        Value*toSet = matrix_get(m,index1,index2);
        data_set(toSet,value);
    }
}   

//If location (index1, index2) is defined in Matrix m, then increase the associated value by
//value. Otherwise, report error.
void matrix_inc(Matrix m, Index index1, Index index2, Value value){    
    if(matrix_isin(m,index1,index2)=='0'){
        printf("%s, %s does not exist\n",index1,index2);
    }else{
        Value* toInc = matrix_get(m,index1,index2);
        data_set(toInc,*toInc + value);
    }
}

//Print indices and values in the Matrix m (with bstree traversal()).
void matrix_list(Matrix m){
    bstree_traversal(m);
}

//Free allocated space (with bstree free()).
void matrix_destruction(Matrix m){
    bstree_free(m);
}
