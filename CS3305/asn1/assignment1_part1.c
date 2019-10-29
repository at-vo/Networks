/**
 * Dat Vo
 * 250983323
 * Create 3 forks to display output upon creation and execute a file through a child
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int cur, par;	// create variables to store pids and to coherently reference them
	pid_t pid1, pid2, pid1_1;	//create pid_t for variables

	pid1 = fork(); // create child1
	if (pid1 < 0)  // if child 1 is unsuccesful
	{
		printf("fork 1 unsuccessful.\n");
		exit(1);
	}
	if (pid1 > 0)
	{	// if parent
		cur = getpid();
		printf("parent process (PID %d) created child_1 (PID %d)\n", cur, pid1);	// display successful creation of child1 by parent
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", cur, pid1);		//display wait before finish child1
		wait(NULL);
		pid2 = fork(); // create child 2 after child 1 finishes
		if (pid2 < 0)
		{
			printf("fork 2 unsuccessful.\n");
			exit(1);
		}
		if(pid2>0){
			wait(NULL);
		}
		if (pid2 == 0) // child 2
		{
			int status;
			cur = getpid();
			par = getppid();
			printf("parent (PID %d) created child_2 (PID %d)\n", par, cur);		// inside child2 display succesful creation of child
			printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2\n", cur);		//print for execute
			status = execl("external_program.out", NULL);	// exec call and end of child 2
			if (status < 0)
			{	// checkf for exec error
				perror("exec");
				printf("main: errno is %d\n", errno);		//	display errornumber
			}
		}
	}
	if (pid1 == 0) // child 1 create
	{
		pid1_1 = fork(); // create child 1.1
		if (pid1_1 < 0)  //for check
		{
			printf("fork 2 unsuccessful.\n");
			exit(1);
		}
		if (pid1_1 > 0)
		{	// if child 1
			cur = getpid();
			printf("child_1 (PID %d) created child_1.1 (PID %d)\n", cur, pid1_1);	// display for creation of child1.1
		}
		if (pid1_1 == 0)
		{
			par = getppid();
			printf("child1 (PID %d) is now complete\n", par);	// last command for child1 inside child1.1
		}	//end of child 1 and child1.1
		
	}
}