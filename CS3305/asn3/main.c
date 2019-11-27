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
    nqueue* ptr = (nqueue*)input;
    qnode * np;
    TAILQ_FOREACH(np,&ptr->head,pointers){
        if(np->type=='d'){
            deposit(np->account1,np->amount);
        }else if(np->type=='w'){
            withdraw(np->account1,np->amount);
        }else if(np->type=='t'){
            transfer(np->account1,np->account2 ,np->amount);
        }
    }
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
    // create threadgroup based on clients
    pthread_t threadgroup[numAccs[2]];
    // initialize array of clients
    nqueue * cliGroup[numAccs[2]];

    
    char * zzz;
    // gets line in file and adds it to respective structure
    while(fgets(str,maxchar,fp)!=NULL){
        zzz = (char*) malloc(sizeof(str));
        strcpy(zzz,str);    //  copy string to use for client
        char * token = strtok(str," "); // get first word
        // account creation
        if (token[0]=='a'){
            // create account and initialize name, balance, and number of transactions
            bankacc * acc = (bankacc *) malloc (sizeof(bankacc));
            // initialize account to zero
            acc->name = makeNum(token);
            // add account to array
            arr[acc->name-arrAdjust] = acc;
            // initialize account to zero
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
        // depositor creation
        }else if (token[0]=='d'){
            token = strtok(NULL, " ");
            while(token!=NULL){
                if(token[0]=='d'&&token[1]=='\0'){
                    token = strtok(NULL, " ");
                    int name = makeNum(token);
                    int dep = atoi(strtok(NULL, " "));
                    deposit(name,dep);
                }
                token = strtok(NULL, " ");
            }
        // client creation
        }else if (token[0]=='c'){
            nqueue que;
            TAILQ_INIT(&que.head);
            char* account = (char*) malloc(sizeof(token));
            strcpy(account,token);
            token = strtok(NULL, " ");
            if(token[0]=='d'){
                qnode*node = (qnode*) malloc(sizeof(qnode));
                node->type = token[0];
                token = strtok(NULL, " ");
                node->account1 = makeNum(token);
                node->amount = atoi(strtok(NULL, " "));
                TAILQ_INSERT_TAIL(&que.head,node,pointers);
            }else if(token[0]=='w'){
                qnode*node = (qnode*) malloc(sizeof(qnode));
                node->type = token[0];
                token = strtok(NULL, " ");
                node->account1 = makeNum(token);
                node->amount = atoi(strtok(NULL, " "));
                TAILQ_INSERT_TAIL(&que.head,node,pointers);
            }else if(token[0]=='t'){
                qnode*node = (qnode*) malloc(sizeof(qnode));
                node->type = token[0];
                token = strtok(NULL, " ");
                node->account1 = makeNum(token);
                token = strtok(NULL, " ");
                node->account2 = makeNum(token);
                node->amount = atoi(strtok(NULL, " "));
                TAILQ_INSERT_TAIL(&que.head,node,pointers);
            }
            int num = makeNum(account);
            cliGroup[num];
        }
        free(zzz);
    }
    fclose(fp);
    //clients using threads
    for (size_t i = 0; i < numAccs[2]; i++){
        if(pthread_create(&threadgroup[i],NULL,clients,(void *)cliGroup[i])!=0){
            printf("thread not created");
            exit(1);
        }
    }
    for (int i = 0; i < numAccs[2]; i++){
        pthread_join(threadgroup[i],NULL);
    }
    
    // write to file
    char * fileout = "assignment_3_output_file.txt";
    wp=fopen(fileout,"w");
    for (int i = 0; i < numAccs[0]; i++)
        fprintf(wp,"balance for account[%d]: %d \n",arr[i]->name,arr[i]->balance);

    // destroy mutex & queues
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < numAccs[2]; i++)
    {
        while (!TAILQ_EMPTY(&cliGroup[i]->head)) {
            qnode* n1;
            n1 = TAILQ_FIRST(&cliGroup[i]->head);
            TAILQ_REMOVE(&cliGroup[i]->head, n1, pointers);
            free(n1);
        }
    }
    

    return 0;
}
