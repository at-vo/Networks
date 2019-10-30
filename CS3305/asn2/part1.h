#ifndef PART1_H
#define PART1_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>   
#include <pthread.h> 

    //initialize global variables
int x = 10 ; int y = 20; int z=0;

void *sumInts(void *num) ;

#endif