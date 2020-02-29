#include <stdio.h>
#include <stdlib.h>

/**
 * Jacob Neiman
 * 250960293
 * jneiman2
 *programing using an array with length 2 to compute fibonacci numbers
 **/
unsigned long long int fibo (int n, unsigned long long int * carry){

  //if n is 1 then return the base case 1
  if( n == 1){
        unsigned long long int* toRet = (unsigned long long int)malloc(sizeof(unsigned long long int)*2);

        toRet[0] = 0ULL;
        toRet[1]= 1ULL;
        return toRet;
    }
 //if n is 0 return the base case 0
    if(n == 0){
        unsigned long long int* toRet = (unsigned long long int)malloc(sizeof(unsigned long long int)*2);
                toRet[0] = 0ULL;
                toRet[1]= 0ULL;

        return toRet;
    }
  //finding each term, adding it to the second postion in carry and recursing 
    carry = fibo(n-1,carry);
    unsigned long long int toSend = carry[1] + carry[0];

  //storing previous term and the current term
  carry[0] = carry[1];
    carry[1] = toSend;
    return carry;

}

int main(){

  //finding fibonacci to 300 terms in increments of 10
    for(int i = 0; i <= 30;i ++){
        unsigned long long int * carry = (unsigned long long int)malloc(sizeof(unsigned long long int)2);
        carry=fibo(i*10,carry);
        printf("fibonacci at %d terms: %llu\n", i*10, carry[1]);
        free(carry);
    }
}