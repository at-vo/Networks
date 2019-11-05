
//#ifdef BANKACCOUNT_H
#define BANKACCOUNT_H
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

typedef struct BankAccount
{
    float balance;  
    char * type;
    char * name;
    int transactionLimit;
    int depositFee;
    int withdrawFee;
    int transactionFee;
    int additionalFee;
    int overdraftProtection;    // no = 0 yes = 1
    int overdraftFee;

}bankacc;



#endif 