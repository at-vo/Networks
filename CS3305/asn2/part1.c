/**
 * Dat Vo
 * 250983323
 * test the data sharing ability of a thread and process
 * */

#include "part1.h"
    
    // function to sum ints for thread
void *sumInts(void *num) 
{ 
    z=x+y;
} 

int main(){
    pid_t pid;
    pid =  fork();
    if (pid < 0)  // if child is unsuccesful
    {
        printf("fork unsuccessful.\n");
        exit(1);
    }
    if (pid > 0){   // on parent
        wait(NULL); //parent waits for child to finish
        printf("from parent: z=%d\n",z);
        pthread_t thread1;
        pthread_create(&thread1,NULL,sumInts,NULL);     // create thread
        pthread_join(thread1,NULL); // wait for thread to finish
        printf("from parent (after thread): z=%d\n",z);        

    }
    if (pid == 0){  // on child
        z = x+y;    //add x and y
        printf("from child: z=%d\n",z);
    }
    
}
