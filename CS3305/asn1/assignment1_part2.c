/**
 * Dat Vo
 * 250983323
 * Communication between pipe to add x and y from reading them in from parent and child respectively
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{ 
    int x,y, fd[2];
    pid_t pid;

    if (pipe(fd) < 0)
    {   //check pipe error
        perror("pipe error");
        exit(0);
    }
    printf("A pipe is created for communication between parent (PID %d) and child (PID %d)\n", getpid()),pid;    //print for pipe successful creation
    pid = fork();   //create child fork
    if (pid < 0)
    {   // check fork error
        perror("fork error");
        exit(0);
    }
    if (pid > 0)
    {
        printf("parent (PID %d) created a child (PID %d)\n", getpid(), pid);        //print upon successful creation of child
        x = atoi(argv[1]);  // change x to int
        printf("parent (PID %d) Reading X = %d from the user\n", getpid(), x);      //print on reading x from user 
        wait(NULL);     // wait for child after read x
        read(fd[0], &y, sizeof(int));       // read y from pipe
        printf("parent (PID %d) Reading Y from the pipe (Y = %d)\n", getpid(), y);
        x += y; // add y to x
        printf("parent (PID %d) adding X + Y = %d\n", getpid(), x);
    }   //end of parent
    if (pid == 0)
    {
        y = atoi(argv[2]);  // change y to int
        printf("parent (PID %d) Reading Y = %d from the user\n", getpid(), y);
        printf("child (PID %d) Writing Y into the pipe\n", getpid());
        write(fd[1], &y, sizeof(int));      // write y to pipe
    }   //end of child
}