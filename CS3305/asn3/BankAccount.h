/**
 * Dat Vo
 * 250983323
 * */
#ifdef BANKACCOUNT_H
#define BANKACCOUNT_H
#define maxchar 256 // maximum buffer
#define overlimit 5000
#define overfee 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>   
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/queue.h>
#include <string.h>

typedef struct BankAccount
{
    float balance;  
    int * name;
    char * type;
    int depositFee;
    int withdrawFee;
    int transferFee;
    int transactionBench;
    int transactionFee;
    int overdraftProtection;    // no = 0 yes = 1
    int overdraftFee;
    int transactionNum;

}bankacc;

void deposit(bankacc** arr, char* name, int deposit);
void withdraw(bankacc** arr, char* name, int withdraw);
void transfer(bankacc** arr, char* name1, char* name2, int transfer);





#endif 