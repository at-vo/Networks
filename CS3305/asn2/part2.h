#ifndef PART2_H
#define PART2_H
#define maxchar 256 // maximum buffer
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>   
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/queue.h>

typedef struct nqueue{
    int num;
    int tq;
    TAILQ_HEAD(tailhead, qnode) head;
} nqueue;

typedef struct qnode{
    char *name;
    int burst;
    TAILQ_ENTRY(qnode) pointers;
} qnode;

int FCFS(nqueue arr, int size,FILE *wp);
int SJF(nqueue arr, int size,FILE *wp);
int RR(nqueue arr, int size,FILE *wp);



#endif