/**
 * Dat Vo
 * 250983323
 * test the data sharing ability of a thread and process
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(){
    // initialize variables
    int x = 10 ; int y = 20; int z=0;

    pid_t pid;

    pid =  fork();
    if (pid < 0)  // if child is unsuccesful
        {
            printf("fork 1 unsuccessful.\n");
            exit(1);
        }
    
}
