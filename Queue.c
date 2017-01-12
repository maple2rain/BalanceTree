#include "Queue.h"

Status InitQueue(LQueue *Q)
{
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(LQNode));
    Q->rear->next = NULL;
    return OK;
}

void DestroyQueue(LQueue *Q)
{
    QueuePtr tmp;

    for(tmp = Q->front;Q->front != NULL; Q->front = Q->front->next)
    {
        free(tmp);
        tmp = Q->front;
    }
}

Status EmptyQueue(LQueue Q)
{
    if(Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

int QueueLength(LQueue Q)
{
    int count = 0;
    while(Q.front != Q.rear)
    {
        ++count;
        Q.front = Q.front->next;
    }

    return count;
}

Status GetFrontQueue(LQueue Q, QueueType *e)
{
    if(Q.front != NULL)
    {
        *e = Q.front->next->data;
        return OK;
    }
    else
        return FAIL;
}

Status EnQueue(LQueue *Q, QueueType e)
{
    QueuePtr new = (QueuePtr)malloc(sizeof(LQNode));
    if(NULL == new)
        return FAIL;

    new->data = e;
    new->next = NULL;
    Q->rear->next = new;
    Q->rear = new;

    return OK;
}

Status DeQueue(LQueue *Q, QueueType *e)
{
    QueuePtr tmp;
    if(Q->front == Q->rear)
        return FAIL;

    tmp = Q->front->next;
    *e = tmp->data;

    Q->front->next = tmp->next;

    if(Q->rear == tmp)
        Q->rear = Q->front;

    free(tmp);
    return OK;
}
