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
 * @return an int array with the number of each lines 
 *          [accounts,depositors,clients]
 * */
int* countline(char *filename){
    
    int * counter = (int*) malloc(sizeof(int)*3);
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
 * removechar
 * @param name word to be shortened
 * @brief removes first char in the given word
 * */
void removeChar(char* name){
    
    int idxToDel = 0; 
    memmove(&name[idxToDel], &name[idxToDel + 1], strlen(name) - idxToDel);
}

/**
 * make number
 * @param token word to turn into number
 * @brief turns a toen into a number with atoi after removing chars from it
 * @return int of number
 * */
int makeNum (char* token){
    char * temp = (char*) malloc(sizeof(token));
    strcpy(temp,token);
    removeChar(temp);
    int toReturn = atoi(temp);
    free(temp);
    return toReturn;
}


/**
 * deposit
 * @param name account number
 * @param deposit amount to deposit; subject to change 
 * @brief return 1 if transfer success, 0 if failure
 * */
int deposit(int name, int dep){
    
    pthread_mutex_lock(&mutex);
    bankacc * acc =  arr[name-arrAdjust];   // adjust array to get right name
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
int withdraw(int name, int withdraw){
    
    pthread_mutex_lock(&mutex);
    bankacc* acc = arr[name-arrAdjust];
    if(acc->transactionNum>acc->transactionBench){
        withdraw+=acc->transactionFee;
    }
    if(acc->withdrawFee !=0){
        withdraw += acc->withdrawFee;
    }
    // case when balance < 0
    if((acc->balance-withdraw)<0){
        if(acc->overdraftProtection==1){// if overdraft protection
            int fee = (withdraw-acc->balance)/overfee;
            fee *= acc->overdraftFee;
            withdraw += fee;
            if((acc->balance-withdraw)<overlimit){
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
 * @return 1 if transfer success, 0 if failure
 * */
int transfer(int acc1,int acc2, int trans){
    
    pthread_mutex_lock(&mutex);
    bankacc* a1 = arr[acc1-arrAdjust];
    bankacc* a2 = arr[acc2-arrAdjust];
    int init = trans; // 
    // withdraw a1
    if(a1->transactionNum>a1->transactionBench){
        trans+=a1->transactionFee;
    }
    if(a1->transferFee !=0){
        trans += a1->transferFee;
    }
    // case when account1 balance < 0
    if((a1->balance-trans)<0){
        if(a1->overdraftProtection==1){// if overdraft protection
            int fee = (trans-a1->balance)/overfee;
            fee *= a1->overdraftFee;
            trans += fee;
            if((a1->balance-trans)<overlimit){
                pthread_mutex_unlock(&mutex);
                return 0;
            }
        }
        else{//if no protection
            pthread_mutex_unlock(&mutex);
            return 0;
        }
    }
    // if successful withdraw from a1
    a1->balance-=trans;
    a1->transactionNum+=1;

    //deposit a2
    trans = init;
    if(a2->transactionNum>a2->transactionBench){
        trans-=a2->transactionFee;
    }
    if(a2->transferFee>0){
        trans-= a2->depositFee;
    }
    a2->balance+=trans;
    a2->transactionNum+=1;
    
    pthread_mutex_unlock(&mutex);
    return 1;
}


/**
 * clients 
 * @param input void pointer for thread
 * @brief calls specific deposit, withdraw 
 *          or transfer on specific account
 * */
void *clients(void *input){
    //pthread_mutex_lock(&mutex);
    char*save = (char*) input;
    char * token = strtok_r((char*) input," ",&save); // get first word
    while(token!=NULL){
            // deposit
        if(token[0]=='d'){
            token = strtok_r(NULL, " ",&save);
            int name = makeNum(token);
            int dep = atoi(strtok_r(NULL, " ",&save));  // reference amount for transaction
            if(deposit(name,dep)==1) 
                printf("successful deposit account: %d, amount: %d balance: [%d]\n",name,dep,arr[name-arrAdjust]->balance);
            else 
                printf("unsuccessful deposit account: %d, amount: %d balance: [%d]\n",name,dep,arr[name-arrAdjust]->balance);
            // withdrawal
        }else if(token[0]=='w'){
            token = strtok_r(NULL, " ",&save);
            int name = makeNum(token);
            int with = atoi(strtok_r(NULL, " ",&save));
            if(withdraw(name,with)==1)               
                printf("successful withdraw account: %d, amount: %d balance: [%d]\n",name,with,arr[name-arrAdjust]->balance);
            else 
                printf("unsuccessful withdraw account: %d, amount: %d balance: [%d]\n",name,with,arr[name-arrAdjust]->balance);
            //transfer
        }else if(token[0]=='t'){
            token = strtok_r(NULL, " ",&save);
            int acc1 = makeNum(token);
            token = strtok_r(NULL, " ",&save);
            int acc2 = makeNum(token);
            int trans = atoi(strtok_r(NULL, " ",&save));
            if(transfer(acc1,acc2,trans)==1) 
                printf("successful transfer account: %d[%d], account: %d[%d], amount: %d\n",acc1,arr[acc1-arrAdjust]->balance,acc2,arr[acc2-arrAdjust]->balance,trans);
            else 
                printf("unsuccessful transfer account: %d[%d], account: %d[%d], amount: %d\n",acc1,arr[acc1-arrAdjust]->balance,acc2,arr[acc2-arrAdjust]->balance,trans);
        }
        token = strtok_r(NULL, " ",&save);  //get next word
    }
    //pthread_mutex_unlock(&mutex);

}

int main(int argc, char *argv[])
{
    char *filename = "assignment_3_input_file.txt";
    int *numAccs = countline(filename); // [accounts, depositors, clients]
    arr = (bankacc**) malloc(sizeof(bankacc*)*(numAccs[0]));  // initializes array of bank accounts
    FILE * fp, *wp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){ 
        printf("Could not open file %s",filename);
        exit(1);
    }
    pthread_t threadgroup[numAccs[2]]; // creates threadgroup size: number of clients

    // initialize array of clients
    char * cliGroup[numAccs[2]];

    // gets line in file and adds it to respective structure
    while(fgets(str,maxchar,fp)!=NULL){
        char * save = str;
        char * token =strtok_r(str," ",&save); // get first word
        // account creation
        if (token[0]=='a'){
            // create account and initialize name, balance, and number of transactions
            bankacc * acc = (bankacc *) malloc (sizeof(bankacc));
            // initialize account to zero
            int name = makeNum(token);
            acc->name = name;
            acc->balance = 0;
            acc->transactionNum = 0;
            arr[name-arrAdjust] = acc;
            token = strtok_r(NULL," ", &save); // advance token
            // get account type then advance token
            if(strcmp(token,"type")==0){
                token = strtok_r(NULL, " ",&save);
                acc->type = token;
                token = strtok_r(NULL, " ",&save);
            }
            // get fees then advance token
                //deposit fees
            if(token[0] == 'd'){
                token = strtok_r(NULL, " ",&save);
                acc->depositFee = atoi(token);
                token = strtok_r(NULL, " ",&save);
            }
                //withdraw fees
            if(token[0] == 'w'){
                token = strtok_r(NULL, " ",&save);
                acc->withdrawFee = atoi(token);
                token = strtok_r(NULL, " ",&save);
            }                    
                //transfer fees
            if(token[0] == 't'){
                token = strtok_r(NULL, " ",&save);
                acc->transferFee = atoi(token);
                token = strtok_r(NULL, " ",&save);
            }
            // set recurring transaction benchmark and fees
            if(strcmp(token,"transactions")==0){
                token = strtok_r(NULL, " ",&save);
                acc->transactionBench = atoi(token);
                token = strtok_r(NULL, " ",&save);
                acc->transactionFee = atoi(token);
                token = strtok_r(NULL, " ",&save);
            }
            // set overdraft
            if(strcmp(token,"overdraft")==0){
                token = strtok_r(NULL, " ",&save);
                if (token[0]=='Y'){
                    acc->overdraftProtection = 1;
                    token = strtok_r(NULL, " ",&save);
                    acc->overdraftFee = atoi(token);
                }else if(token[0]=='N'){
                    acc->overdraftProtection = 0;
                }  
            }
        // depositor creation
        }else if (token[0]=='d'){
            token = strtok_r(NULL, " ",&save);
            while(token!=NULL){
                if(strcmp(token,"d")==0){
                    token = strtok_r(NULL, " ",&save);
                    int name = makeNum(token);
                    int dep = atoi(strtok_r(NULL, " ",&save));
                    deposit(name,dep);
                }
                token = strtok_r(NULL, " ",&save);
            }
        // client creation
        }else if (token[0]=='c'){
            char * tran = (char*) malloc(sizeof(char)*maxchar);// create transaction
            strcpy(tran,save);
            int name = makeNum(token);
            cliGroup[name-arrAdjust] = tran;    // store in client group
        }
    }
    fclose(fp);

    for (int i = 0; i < numAccs[0]; i++)
    {
        printf("account[%d] initial balance:[%d]\n\n",arr[i]->name,arr[i]->balance);
    }
    

    // clients using threads
    for (size_t i = 0; i < numAccs[2]; i++){
        if(pthread_create(&threadgroup[i],NULL,clients,cliGroup[i])!=0){
            printf("thread not created");
            exit(1);
        }
    }
    for (int i = 0; i < numAccs[2]; i++)
        {pthread_join(threadgroup[i],NULL);}
    
    // write to file
    char * fileout = "assignment_3_output_file.txt";
    wp=fopen(fileout,"w");
    for (int i = 0; i < numAccs[0]; i++)
        fprintf(wp,"balance for account[%d]: %d \n",arr[i]->name,arr[i]->balance);

    // destroy mutex
    pthread_mutex_destroy(&mutex);


    return 0;
}
