/**
 * Dat Vo
 * 250983323
 * */
#ifndef BANKACCOUNT_H
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

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct BankAccount
{
    float balance;  
    char * name;
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

typedef struct withdraw
{
    char* account;
    int amount;
    bankacc * toArr;
} wthdrw;

typedef struct deposit
{
    char* account;
    int amount;
    bankacc * toArr;

}depst;

typedef struct transfer
{
    char* account1;
    char* account2;
    int amount;
    bankacc * toArr;

}trnsfr;


bankacc ** arr;
 
#endif