#include "part2.h"

    // looks through file and appropriately assigns queues
int readFile(char* filename, nqueue** arr){
    FILE * fp;
    char str[maxchar];
    // 
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }else{
        // queue counter
        int i=0;    
        // gets line in file
        while(fgets(str,maxchar,fp)!=NULL){
            char * token = strtok(str," ");
            // reads token
            while(token!=NULL){
                //printf("token: %s\n",token);
                // for queue time quantum
                if(token[0] == 't' && token[1]=='q'){
                    token = strtok(NULL," ");
                    arr[i]->tq = atoi(token);
                }
                // if process
                else if(token[0]=='p'){
                    // if queue empty
                    if (arr[i]->first == NULL && arr[i]->last==NULL){ 
                        // create new process object
                        qnode * temp;
                        temp= (qnode*) malloc(sizeof(qnode));
                        temp->name = token;
                        // sets first and last of queue to temp
                        arr[i]->first = temp;
                        arr[i]->last = temp;
                        // advances tokenizer to get burst speed
                        token = strtok(NULL," ");
                        temp->burst=atoi(token);
                    }
                    else{   // queue not empty
                        // create new process object
                        qnode * temp;
                        temp = (qnode*) malloc(sizeof(qnode));
                        temp->name = token;
                        // sets last for queue to temp 
                        arr[i]->last->behind =  temp;
                        arr[i]->last = temp;
                        // advances tokenizer to get burst speed
                        token = strtok(NULL," ");
                        temp->burst=atoi(token);
                    }
                }else if (token[0]=='q'){
                    // read next and skip
                    token = strtok(NULL," ");
                }
                token = strtok(NULL," ");
            }
            i++;  // goes to next queue
        }
    }
    fclose(fp);
    return 0;
}

    // scans through file once to find number of lines
int checkfile(char*filename){
    FILE * fp;
    int lines = 0;
    char str[maxchar];
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return -1;
    }
    while(fgets(str,maxchar,fp)!=NULL){
        lines++;
    }
    return lines;
}

int FCFS(nqueue arr){

}


    /** perform the following tasks in order based on the given input file:
     *  1. Ready queueswill be executedin the order of their queue number
     *  2. CPU schedulingalgorithms FCFS, SJF, and RRwill be applied on each ready queue
     * */
int main(){
    char *filename = "cpu_scheduling_input_file.txt";
    int size = checkfile(filename);
    nqueue* arr[size];
    // allocate memory for each queue object
    for(int i =0;i<size;i++){
        arr[i] = (nqueue*) malloc(sizeof(nqueue));
        arr[i]->first = NULL; arr[i]->last = NULL;

    }
    readFile(filename, arr);



}

