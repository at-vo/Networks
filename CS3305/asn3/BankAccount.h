/**
 * Dat Vo
 * 250983323
 * */
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#define maxchar 256 // maximum buffer
#define overlimit 5000
#define overfee 500
#define arrAdjust 1
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


typedef struct nqueue{
    TAILQ_HEAD(tailhead, qnode) head; //= TAILQ_HEAD_INITIALIZER(head);
}nqueue;

typedef struct qnode{
    char type;
    int amount;
    int account1;
    int account2;
    TAILQ_ENTRY(qnode) pointers;
}qnode;


typedef struct BankAccount
{
    int balance;  
    int name;
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
bankacc ** arr;
 
#endif