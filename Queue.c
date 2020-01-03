#include <stdio.h>
#include <stdlib.h>

typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode,*QPtr;

typedef struct
{
    QPtr front;
    QPtr rear;
}LinkQueue;

void EnQueue(LinkQueue *l,int i);
void InitQueue(LinkQueue **l);
int DeQueue(LinkQueue *l);
void Read(LinkQueue l);

int main(void)
{
    LinkQueue *l1;
    InitQueue(&l1);
    EnQueue(l1,1);
    EnQueue(l1,2);
    DeQueue(l1);
    Read(*l1);
}

void InitQueue(LinkQueue** q)
{
    *q = (LinkQueue*)malloc(sizeof(LinkQueue));
    (*q)->front = (QNode*)malloc(sizeof(QNode));
    (*q)->rear = (*q)->front;
    (*q)->front->next = NULL;
}

void EnQueue(LinkQueue *l,int i)
{
    QPtr p1,p2 = l->rear;
    p1=(QNode*)malloc(sizeof(QNode));
    p1->data = i;
    p1 ->next = NULL;
    p2->next = p1;
    l->rear = p1;
}

int DeQueue(LinkQueue *l)
{
    if(l->front==l->rear)
        return -1;
    int x = l->front->next->data;
    l->front->next = l->front->next->next;
}

void Read(LinkQueue l)
{
    QPtr p = l.front->next;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        if(p==l.rear)
            break;
        p = p->next;
    }
    printf("\n");
}