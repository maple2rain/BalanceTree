#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "BalanceTree.h"

typedef BiTree QueueType;

typedef struct LQNode{
    QueueType data;
    struct LQNode *next;
}LQNode, *QueuePtr;

typedef struct LQueue{
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
}LQueue;

Status DeQueue(LQueue *Q, QueueType *e);
Status EnQueue(LQueue *Q, QueueType e);
Status GetFrontQueue(LQueue Q, QueueType *e);
int QueueLength(LQueue Q);
Status EmptyQueue(LQueue Q);
void DestroyQueue(LQueue *Q);
Status InitQueue(LQueue *Q);
#endif // QUEUE_H_INCLUDED
