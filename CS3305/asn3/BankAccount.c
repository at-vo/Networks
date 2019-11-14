#include "BankAccount.h"

// count num of accounts
int countAcc(char *filename){
    int accs = 0;  //number of processes
    // char * fileout = "cpu_scheduling_output_file.txt";
    FILE * fp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return errno;
    }
    // gets line in file
    while(fgets(str,maxchar,fp)!=NULL){
        char * token = strtok(str," "); // get first word
        if (token[0]=='a'){
            accs += 1;
        }else{
            break;
        }
    }
    return accs;
}

int countDep(char *filename){
    int deps = 0;  //number of depositors
    // char * fileout = "cpu_scheduling_output_file.txt";
    FILE * fp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return errno;
    }
    // gets line in file
    while(fgets(str,maxchar,fp)!=NULL){
        char * token = strtok(str," "); // get first word
        if (token[0]=='d'){
            deps += 1;
        }else if(token[0]=='a'){
            // ignore
        }else{
            break;
        }
    }
    return deps;
}

// remove first char from name
void removeChar(char* name){
    int idxToDel = 0; 
    memmove(&name[idxToDel], &name[idxToDel + 1], strlen(name) - idxToDel);
}

void deposit(bankacc** arr, char* name, int deposit){
    char * temp = strcpy(temp,name);
    removeChar(temp);
    bankacc* acc = arr[atoi(temp)];
    if(acc->depositFee !=0){
        deposit -= acc->depositFee;
    }
    acc->balance += deposit;
    acc->transactionNum++;

}
void withdraw(bankacc** arr, char* name, int withdraw){
    char * temp = strcpy(temp,name);
    removeChar(temp);
    bankacc* acc = arr[atoi(temp)];
    if(acc->depositFee !=0){
        withdraw += acc->withdrawFee;
    }
    acc->balance -= withdraw;
    acc->transactionNum++;
}
void transfer(bankacc** arr, char* name1, char* name2, int transfer){
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
}



int main(){
    char *filename = "cpu_scheduling_input_file.txt";
    // char * fileout = "cpu_scheduling_output_file.txt";
    int numAccs = countAcc(filename);
    int numDeps = countDep(filename);
    bankacc * arr[numAccs+1];
    FILE * fp, *wp;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return errno;
    }
    // wp=fopen(fileout,"w");
    // gets line in file
    while(fgets(str,maxchar,fp)!=NULL){
        int depositorsDone = 0;  // check if depositors are done
        char * token = strtok(str," "); // get first word
        while (token!=NULL){
            // account creation
            if (token[0]=='a'){
                // create account and initialize name, balance, and number of transactions
                bankacc * acc = (bankacc *) malloc (sizeof(bankacc));
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
        // break loop before 
        if (numDeps==depositorsDone){
            break;
        }
    }

}