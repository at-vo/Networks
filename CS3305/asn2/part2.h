#ifndef PART2_H
#define PART2_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>   
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#define maxchar 100 // maximum buffer

typedef struct node{
    char *name;
    int burst;
    struct qnode *behind;
} qnode;

typedef struct queue{
    struct qnode *first,*last;
    int tq;
} nqueue;

#endif