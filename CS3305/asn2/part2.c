/**
 * Dat Vo
 * 250983323
 * scheduling algorithms on given input file queues
 * */
#include "part2.h"

    // FCFS algorithm on given queue
int FCFS(nqueue arr,int size, FILE*wp){
    fprintf(wp,"Ready Queue %d Applying FCFS Scheduling:\n",arr.num);
    fprintf(wp,"Order of selection by CPU: \n");
    qnode * np;
    TAILQ_FOREACH(np,&arr.head,pointers){
        fprintf(wp,"%s ",np->name);
    }
    // waiting times
    fprintf(wp,"\n");
    fprintf(wp,"\nIndividual waiting times for each process: \n");
    float wait = 0;
    float waitsum=0;
    // check and increment wait 
    TAILQ_FOREACH(np,&arr.head,pointers){
        fprintf(wp,"%s = %.0f\n",np->name,wait);
        waitsum+=wait;
        wait += np->burst;
    }
    //avg waiting time
    wait = waitsum/size;
    fprintf(wp,"\nAverage waiting time = %.2f\n\n",wait);
    
}
    // SJF algorithm
int SJF(nqueue arr,int size,FILE *wp){
    fprintf(wp,"Ready Queue %d Applying SJF Scheduling: \n",arr.num);
    fprintf(wp,"Order of selection by CPU: \n");
    nqueue newArr;
    // size++;
    char* names[size];
    int bursts[size];
    // sort queue based on burst time
    qnode * np;
    int p=0;
    TAILQ_FOREACH(np,&arr.head,pointers){
        bursts[p] = np->burst;
        names[p] = np->name;
        p++;
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            //Compare array elements
            if (bursts[j] > bursts[i]) {   // Use temporary variable for storing value
				int tmp1 = bursts[i];         
				bursts[i] = bursts[j]; // replace value
				bursts[j] = tmp1; 
                // change names same way
                char* tmp2 = names[i];         
				names[i] = names[j];            
				names[j] = tmp2;            
			}  
		}
	}
    // print order of selection
    for (int i = 0; i < size; i++){
        fprintf(wp,"%s ",names[i]);

    }
    // waiting times same as FCFS
    fprintf(wp,"\n");
    fprintf(wp,"\nIndividual waiting times for each process: \n");
    int wait = 0;
    float waitsum=0;
    for (int i = 0; i < size; i++){
        fprintf(wp,"%s = %d\n",names[i],wait);
        waitsum+=wait;
        wait += bursts[i];
    }
    //avg waiting time
    wait = waitsum/size;
    fprintf(wp,"\nAverage waiting time = %.2f\n\n",wait);
}

// remove p from process name
void removep(char* proc){
    int idxToDel = 0; 
    memmove(&proc[idxToDel], &proc[idxToDel + 1], strlen(proc) - idxToDel);
}

    // RR scheduling
int RR(nqueue arr, int size,FILE *wp){
    fprintf(wp,"Ready Queue %d Applying RR Scheduling:\n",arr.num);
    fprintf(wp,"Order of selection by CPU: \n");
    qnode * np;
    size+=1;
    int tq = arr.tq;
    // add process to queue again if it is greater than tq
    TAILQ_FOREACH(np,&arr.head,pointers){
        int tempBurst = np->burst;
        if((tempBurst-tq)>0){
            qnode *temp = (qnode*) malloc(sizeof(qnode));
            temp->burst = np->burst-tq;
            temp->name = (char*)malloc(sizeof(char));
            strcpy(temp->name,np->name);
            TAILQ_INSERT_TAIL(&arr.head,temp,pointers);
            // printf("q%d:%s\n",arr.num,temp->name);

        }
    }
    TAILQ_FOREACH(np,&arr.head,pointers){
        fprintf(wp,"%s ",np->name);
    }
    // turnaround times
    fprintf(wp,"\n");
    fprintf(wp,"\nTurnaround times for each process: \n");
    int finish[size];
    //create three lists for storing finish and arrival times to their respective process
    for (int i = 1; i < size; i++)
    {
        finish[i] = -1;
    }
    int here[size];
    for (int i = 1; i < size; i++)
    {
        here[i] = -1;
    }
    int proc[size];
    float wait = 0;
    TAILQ_FOREACH(np,&arr.head,pointers){
        // remove p from process
        removep(np->name);
        // convert to number
        int i = atoi(np->name);
        // record arrival and process
        if(here[i]==-1){
            here[i] = wait;
            proc[i] = i;
        }
        // check increment to wait
        int gant=np->burst;
        if ((gant-tq)==0){
            wait+=tq;
        }else if((gant-tq)<0){
            wait+=gant;
        }else if((gant-tq)>0){
            wait+=tq;
        }
        finish[i]=wait;
        // printf("q::%d p%d: arr= %d fin = %d\n",arr.num,i,here[i],finish[i]);
    }
    //  sort by finish times
    for (int i = 1; i < size; i++){
        for (int j = 1; j < size; j++){
            //Compare array elements
            if (finish[j] > finish[i]) {   // Use temporary variable for storing value
				int tmp1 = finish[i];         
				finish[i] = finish[j]; // replace value
				finish[j] = tmp1; 
                // change arrival times same way
                int tmp2 = here[i];         
				here[i] = here[j];            
				here[j] = tmp2; 
                // change process order same way
                int tmp3 = proc[i];         
				proc[i] = proc[j];            
				proc[j] = tmp3;           
			}  
		}
	}
    // print turnaround times
    for (int i = 1; i < size; i++)
    {
        int turnaround = finish[i] - here[i];
        fprintf(wp,"p%d = %d\n",proc[i],turnaround);
    }
}


    /** perform the following tasks in order based on the given input file:
     *  1. Ready queueswill be executedin the order of their queue number
     *  2. CPU schedulingalgorithms FCFS, SJF, and RRwill be applied on each ready queue
     * */
int main(){
    char *filename = "cpu_scheduling_input_file.txt";
    char * fileout = "cpu_scheduling_output_file.txt";
    FILE * fp, *wp;
    nqueue arr;
    char str[maxchar];  //max buffer
    // check if incorrect file
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Could not open file %s",filename);
        return errno;
    }
    wp=fopen(fileout,"w");
    // gets line in file
    while(fgets(str,maxchar,fp)!=NULL){
        int procs=0;  //number of processes
        TAILQ_INIT(&arr.head);
        char * token = strtok(str," ");
        // reads token
        while(token!=NULL){
            // for queue time quantum
            if(token[0] == 't' && token[1]=='q'){
                token = strtok(NULL," ");
                arr.tq = atoi(token);
            }
            // if process
            else if(token[0]=='p'){
                // create new process object
                qnode * temp;
                temp = (qnode*) malloc(sizeof(qnode));
                temp->name = token;
                // advances tokenizer to get burst speed
                token = strtok(NULL," ");
                temp->burst=atoi(token);
                // sets first and last of queue to temp
                TAILQ_INSERT_TAIL(&arr.head,temp,pointers);
                procs++;
            }
            // if queue assign number
            else if (token[0]=='q'){
                token = strtok(NULL," ");
                arr.num=atoi(token);
            }
            token = strtok(NULL," ");
        }
        //call scheduling algorithm on each process
        FCFS(arr,procs,wp);
        SJF(arr,procs,wp);
        RR(arr,procs,wp);
        // destroy queue
        while (!TAILQ_EMPTY(&arr.head)) {
            qnode* n1;
            n1 = TAILQ_FIRST(&arr.head);
            TAILQ_REMOVE(&arr.head, n1, pointers);
            free(n1);
        }
    }
    fclose(fp);
    fclose(wp);

    return 0;
}