#include "BankAccount.h"

// count num of line
int* countline(char *filename){
    int *counter = (int*) malloc(sizeof(int)*3); // counter for accounts, depositors and client transactions
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
            //TODO:: 
            // unsure how many threads to create
            // while(token!=NULL){
            //     counter[2]+=1;
            //}
        }
    }
    return counter;
}
// remove first char from name
void removeChar(char* name){
    int idxToDel = 0; 
    memmove(&name[idxToDel], &name[idxToDel + 1], strlen(name) - idxToDel);
}

/* Deposit */
void deposit(void* ptr){
    pthread_mutex_lock(&mutex);
    ptr = (depst*) ptr;
    char * temp = strcpy(temp,ptr->name);
    removeChar(temp);
    bankacc* acc = arr[atoi(temp)];
    if(acc->depositFee !=0){
        deposit -= acc->depositFee;
    }s
    acc->balance += deposit;
    acc->transactionNum++;

    pthread_mutex_unlock(&mutex);


}
/*Withdraw*/
void withdraw(void* ptr){
    pthread_mutex_lock(&mutex);

    char * temp = strcpy(temp,name);
    removeChar(temp);
    bankacc* acc = arr[atoi(temp)];
    if(acc->depositFee !=0){
        withdraw += acc->withdrawFee;
    }
    acc->balance -= withdraw;
    acc->transactionNum++;
    pthread_mutex_unlock(&mutex);

}
/*transfer*/
void transfer(void* ptr){
    pthread_mutex_lock(&mutex);

    char * temp1 = strcpy(temp1,name1);
    char * temp2 = strcpy(temp2,name2);

    removeChar(temp1);
    removeChar(temp2);

    bankacc* acc1 = arr[atoi(temp1)];
    bankacc* acc2 = arr[atoi(temp2)];
    
    if(acc1->transferFee !=0){
        acc1->balance-=acc1->transferFee;
    }
    if(acc2->transferFee !=0){
        acc2->balance-=acc2->transferFee;
    }

    acc1->balance -= transfer;
    acc1->transactionNum++;
    acc2->balance += transfer;
    acc2->transactionNum++;
    pthread_mutex_unlock(&mutex);
}



int main(){
    char *filename = "cpu_scheduling_input_file.txt";
    // char * fileout = "cpu_scheduling_output_file.txt";
    int *numAccs = countline(filename); // [accounts, depositors, clients]
    arr = (bankacc**) malloc(sizeof(bankacc*)*(numAccs[0]+1));
    FILE * fp, *wp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){ 
        printf("Could not open file %s",filename);
        exit(1);
    }
    // wp=fopen(fileout,"w");
    // gets line in file until end of depositors
    while(fgets(str,maxchar,fp)!=NULL){
        int depositorsDone = 0;  // check if depositors are done
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
                char * temp = strcpy(temp,token);
                removeChar(temp);
                arr[atoi(temp)] = acc;
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
                if(token[0] == 'd'){
                    token = strtok(NULL, " ");
                    acc->withdrawFee = atoi(token);
                    token = strtok(NULL, " ");

                }                    
                    //transfer fees
                if(token[0] == 'd'){
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
            token = strtok(NULL, " ");
            }
            // depositors
            else if (token[0]=='d'){
                token = strtok(NULL, " ");
                if(strcmp(token,"d")==0){
                    token = strtok(NULL, " ");
                    char* name = strtok(NULL, " ");
                    int dep = atoi(strtok(NULL, " "));
                    deposit(arr,name,dep);
                    token = strtok(NULL, " ");
                    if(token == NULL){
                        depositorsDone++;
                    }
                }
                
            }
        }
        // break loop after depositors are done
        if (numAccs[1]==depositorsDone){
            break;
        }
    }
    // calc transactions
    pthread_t * threadgroup = malloc(sizeof(pthread_t) * numAccs[2]); // creates threadgroup size of the number of clients
    int i;
    while(fgets(str,maxchar,fp)!=NULL){
        char * token = strtok(str," ");
        while(token!=NULL){
            if(token[0]=='c'){ // redundant but checking if its a client line
                token = strtok(NULL, " ");
                if(strcmp(token,"d")==0){
                    depst* temp = (depst*) malloc(sizeof(depst));
                    token = strtok(NULL, " "); // get acc
                    removeChar(token);
                    temp->toArr = arr[atoi(token)]; // get reference to acc in arr
                    token = strtok(NULL, " "); // get amount
                    temp->amount = atoi(token);
                    pthread_create(&threadgroup[atoi(acc->name[2])],NULL,&deposit,&temp); // second null needs to be a struct
                }else if(strcmp(token,"w")==0){
                    token = strtok(NULL, " "); // get acc
                    removeChar(token);
                    bankacc* acc = arr[atoi(token)]; // get reference to acc in arr
                    pthread_create(&threadgroup[atoi(acc->name[2])],NULL,&withdraw,NULL);
                }else if(strcmp(token,"t")==0){
                    token = strtok(NULL, " "); // get acc1
                    removeChar(token);
                    bankacc* acc1 = arr[atoi(token)]; // get reference to acc in arr
                    token = strtok(NULL, " "); // get acc2
                    removeChar(token);
                    bankacc* acc2 = arr[atoi(token)]; // get reference to acc in arr

                }
            }
        }
    }
    //TODO: add num threads as count
    // for (size_t i = 0; i < count; i++)
    // {
    //     pthread_join(threadgroup[i],NULL);
    // }
    
    pthread_mutex_destroy(&mutex);


}