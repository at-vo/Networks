/**
 * Dat Vo
 * 250983323
 * */
#include "BankAccount.h"

/**
 * countline
 * @param filename name of input file
 * @brief returns a reference to number of each account, 
 *          depositor, and client in input file
 * */
int* countline(char *filename){
    int counter[3];
    // char * fileout = "cpu_scheduling_output_file.txt";
    FILE * fp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        exit(1);
    }
    // gets line in file
    while(fgets(str,maxchar,fp)!=NULL){
        char * token = strtok(str," "); // get first word
        if (token[0]=='a'){            
            counter[0] += 1;
        }else if (token[0]=='d'){
            counter[1]+=1;
        }else if (token[0]=='c'){
            counter[2]+=1;
        }
    }
    return counter;
}

/**
 * deposit
 * @param name account number
 * @param deposit amount to deposit; subject to change 
 * @brief return 1 if transfer success, 0 if failure
 * */int deposit(char*name, int dep){
    pthread_mutex_lock(&mutex);
    bankacc * acc =  arr[atoi(name[1])];
    if(acc->transactionNum>acc->transactionBench){
        dep-=acc->transactionFee;
    }
    if(acc->depositFee>0){
        dep-= acc->depositFee;
    }
    acc->balance+=dep;
    acc->transactionNum+=1;
    pthread_mutex_unlock(&mutex);
    return 1;
}
/**
 * withdraw
 * @param name account number
 * @param withdraw amount to withdraw; subject to change 
 * @brief return 1 if transfer success, 0 if failure
 * */
int withdraw(char*name, int withdraw){
    pthread_mutex_lock(&mutex);
    bankacc* acc = arr[atoi(name[1])];
    if(acc->transactionNum>acc->transactionBench){
        withdraw+=acc->transactionFee;
    }
    if(acc->withdrawFee !=0){
        withdraw += acc->withdrawFee;
    }
    // case when balance < 0
    if((acc->balance-withdraw)<0){
        if(acc->overdraftProtection==1){// if overdraft protection
            int fee = (withdraw-acc->balance)/500;
            fee *= acc->overdraftFee;
            withdraw += fee;
            if((acc->balance-withdraw)<5000){
                pthread_mutex_unlock(&mutex);
                return 0;
            }
        }
        else{//if no protection
            pthread_mutex_unlock(&mutex);
            return 0;
        }
    }
    // if successful withdraw
    acc->balance-=withdraw;
    acc->transactionNum+=1;
    pthread_mutex_unlock(&mutex);
    return 1;
}
/**
 * transfer
 * @param acc1  account to withdraw from
 * @param acc2  account to deposit to
 * @param trans transaction amount
 * @brief return 1 if transfer success, 0 if failure
 * */
int transfer(char*acc1,char*acc2, int trans){
    pthread_mutex_lock(&mutex);
    if(1==withdraw(acc1,trans) && 1==deposit(acc2,withdraw)){
        pthread_mutex_unlock(&mutex);
        return 1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}
/**
 * create account 
 * @param input void pointer for use in thread
 * @brief initializes each account in bankacc arr
 * */
void *createAccount(void*input){
    bankacc* ptr = (bankacc*) input;
    char * token = strtok(ptr->string," "); // get first word
    while (token!=NULL){
        // create account and initialize name, balance, and number of transactions
        bankacc * acc = (bankacc *) malloc (sizeof(bankacc));
        // initialize account to zero
        acc->name = token;
        acc->balance = 0;
        acc->transactionNum = 0;
        token = strtok(NULL," "); // advance token
        // get account type then advance token
        if(strcmp(token,"type")==0){
            token = strtok(NULL, " ");
            acc->type = token;
            token = strtok(NULL, " ");
        }
        // get fees then advance token
            //deposit fees
        if(token[0] == 'd'){
            token = strtok(NULL, " ");
            acc->depositFee = atoi(token);
            token = strtok(NULL, " ");
        }
            //withdraw fees
        if(token[0] == 'w'){
            token = strtok(NULL, " ");
            acc->withdrawFee = atoi(token);
            token = strtok(NULL, " ");
        }                    
            //transfer fees
        if(token[0] == 't'){
            token = strtok(NULL, " ");
            acc->transferFee = atoi(token);
            token = strtok(NULL, " ");
        }
        // set recurring transaction benchmark and fees
        if(strcmp(token,"transactions")==0){
            token = strtok(NULL, " ");
            acc->transactionBench = atoi(token);
            token = strtok(NULL, " ");
            acc->transactionFee = atoi(token);
            token = strtok(NULL, " ");
        }
        // set overdraft
        if(strcmp(token,"overdraft")==0){
            token = strtok(NULL, " ");
            if (token[0]=='Y'){
                acc->overdraftProtection = 1;
                token = strtok(NULL, " ");
                acc->overdraftFee = atoi(token);
            }else if(token[0]=='N'){
                acc->overdraftProtection = 0;
            }                    
        }
    }
    return NULL;
}
/**
 * depositors 
 * @param input void pointer for use in thread
 * @brief calls deposit on specific account
 * */
void *depositors(void*input){
    transac*ptr = (transac*) input;
    char * token = strtok(ptr->string," "); // get first word
    while(token!=NULL){
        if(strcmp(token,"d")==0){
            char* name = strtok(NULL, " ");;
            int dep = atoi(strtok(NULL, " "));
            deposit(name,dep);
        }
        token = strtok(NULL, " ");
    }
    return NULL;
}

/**
 * clients 
 * @param input void pointer for thread
 * @brief calls specific deposit, withdraw 
 *          or transfer on specific account
 * */
void *clients(void *input){
    transac*ptr = (transac*) input;
    char * token = strtok(ptr->string," "); // get first word
    while(token!=NULL){
            // deposit
        if(strcmp(token,"d")==0){
            char* name = strtok(NULL, " ");;    // reference account number
            int dep = atoi(strtok(NULL, " "));  // reference amount for transaction
            if(deposit(name,dep)==1) 
                printf("successful deposit");
            else 
                printf("unsuccessful deposit");
            // withdrawal
        }else if(strcmp(token,"w")==0){
            char* name = strtok(NULL, " ");;
            int dep = atoi(strtok(NULL, " "));
            if(withdraw(name,dep))               
                printf("successful withdrawal");
            else 
                printf("unsuccessful withdrawal");
            //transfer
        }else if(strcmp(token,"t")==0){
            char* acc1 = strtok(NULL, " ");
            char* acc2 = strtok(NULL, " ");;
            int trans = atoi(strtok(NULL, " "));
            if(transfer(acc1,acc2,trans)==1) 
                printf("successful transfer");
            else 
                printf("unsuccessful transfer");
        }
        token = strtok(NULL, " ");  //get next word
    }
}

int main()
{
    char *filename = "cpu_scheduling_input_file.txt";
    int *numAccs = countline(filename); // [accounts, depositors, clients]
    arr = (bankacc**) malloc(sizeof(bankacc*)*(numAccs[0]));  // initializes array of bank accounts
    FILE * fp, *wp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){ 
        printf("Could not open file %s",filename);
        exit(1);
    }
    // create threadgroup based on largest of accounts depositors or clients
    pthread_t * threadgroup;
    if(numAccs[0]>=numAccs[1] && numAccs[0]>=numAccs[2]){
        threadgroup = malloc(sizeof(pthread_t) * numAccs[0]); // creates threadgroup size of the number of accounts
    }else if(numAccs[1]>=numAccs[2] && numAccs[1]>=numAccs[0]){
        threadgroup = malloc(sizeof(pthread_t) * numAccs[1]); // creates threadgroup size of the number of depositors
    }else{
        threadgroup = malloc(sizeof(pthread_t) * numAccs[2]); // creates threadgroup size of the number of clients
    }
    // initialize array of depositors and clients
    transac * depoGroup[numAccs[1]]; 
    transac * cliGroup[numAccs[2]];

    // gets line in file until end of depositors
    while(fgets(str,maxchar,fp)!=NULL){
        char * token = strtok(str," "); // get first word
        while (token!=NULL){
            // account creation
            if (token[0]=='a'){
                // create account and initialize name, balance, and number of transactions
                bankacc * acc = (bankacc *) malloc (sizeof(bankacc));
                // initialize account to zero
                acc->name = token;
                acc->balance = 0;
                acc->transactionNum = 0;
                // add account to array
                arr[atoi(token[1]-1)] = acc;
                strcpy(acc->string,str);
            }else if (token[0]=='d'){
                transac * tran = (transac*) malloc(sizeof(transac));// create transaction
                strcpy(tran->string,str);   //copy string
                depoGroup[atoi(token[3])-1] = tran;    // store in deposit group
                tran->group=threadgroup;
            }else if (token[0]=='c')
            {
                transac * tran = (transac*) malloc(sizeof(transac));// create transaction
                strcpy(tran->string,str);   //copy string
                cliGroup[atoi(token[1])-1] = tran;    // store in client group
            }
        }
    }
    // create accounts using threads
    for (int i = 0; i < numAccs[0]; i++)
        pthread_create(&threadgroup[i],NULL,&createAccount,&arr[i]);
    for (int i = 0; i < numAccs[0]; i++)
        pthread_join(&threadgroup[i],NULL);
    // depositers using threads
    for (size_t i = 0; i < numAccs[1]; i++)
        pthread_create(&threadgroup[i],NULL,&depositors,&depoGroup[i]);
    for (int i = 0; i < numAccs[1]; i++)
        pthread_join(&threadgroup[i],NULL);
    // clients using threads
    for (size_t i = 0; i < numAccs[3]; i++)
        pthread_create(&threadgroup[i],NULL,&transfer,&cliGroup[i]);
    for (int i = 0; i < numAccs[3]; i++)
        pthread_join(&threadgroup[i],NULL);
    
    // write to file
    char * fileout = "cpu_scheduling_output_file.txt";
    wp=fopen(fileout,"w");
    for (int i = 0; i < numAccs[0]; i++)
    {
        fprintf("balance for account[%d]: %d \n",atoi(arr[i]->name[1]),arr[i]->balance);
    }
    
    // destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
