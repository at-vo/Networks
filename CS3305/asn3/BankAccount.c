#include "BankAccount.h"

int main(){
    bankacc * arr[];
    char *filename = "cpu_scheduling_input_file.txt";
    // char * fileout = "cpu_scheduling_output_file.txt";
    FILE * fp, *wp;
    //queue arr;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return errno;
    }
    // wp=fopen(fileout,"w");
    // gets line in file
    while(fgets(str,maxchar,fp)!=NULL){
        int procs = 0;  //number of processes
        char * token = strtok(str," "); // get first word
        while (token!=NULL){
            // account creation
            if (token[0]=='a'){
                // create account and set account number
                bankacc * acc = (bankacc *) malloc (sizeof(bankacc));
                acc->name = token;
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


            }
            // depositors
            else if (token[0]=='d'){
                token = strtok(NULL, " ");
                if (token[0]=='d'){
                    token = strtok(NULL, " ");

                }

            }
            token = strtok(NULL, " ");
        }
    }
}