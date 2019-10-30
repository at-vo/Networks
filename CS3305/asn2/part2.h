#ifndef PART2_H
#define PART2_H
#define maxchar 100 // maximum buffer
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>   
#include <pthread.h>
#include <string.h>
#include <ctype.h>

typedef struct nqueue{
    int num;
    struct qnode *first,*last;
    int tq;
} nqueue;

typedef struct qnode{
    char *name;
    int burst;
    struct qnode *behind;
} qnode;


int readFile(char* filename, nqueue* arr);
int checkfile(char*filename);
int FCFS(nqueue* arr, int size);
int SJF(nqueue arr);
int RR(nqueue arr);



#endif