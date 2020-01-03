#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 5
/*
    少用一个元素
*/
typedef struct
{
    int front;
    int rear;
    int data[MAXSIZE];
} SqQueue;

void InitQueue(SqQueue *q);
void EnQueue(SqQueue *q, int i);
int DeQueue(SqQueue *q);
int Read(SqQueue q);

int main(void)
{
    SqQueue q;
    InitQueue(&q);
    for (int i = 0; i < MAXSIZE - 1; i++)
        EnQueue(&q, i);
    Read(q);
    for(int t = 0;t<3;t++)
        DeQueue(&q);
    EnQueue(&q,10);
    Read(q);
}

void InitQueue(SqQueue *q)
{
    q->front = 0;
    q->rear = 1;
}

void EnQueue(SqQueue *q, int i)
{
    if (q->rear == q->front)
        printf("ERROR");
    else

    {
        q->data[q->rear++] = i;
        q->rear = q->rear % MAXSIZE;
    }
}

int DeQueue(SqQueue *q)
{
    q->front = q->front % MAXSIZE;
    if (q->front + 1 == q->rear)
        return 0;
    return q->data[++q->front];
}

int Read(SqQueue q)
{
    if (q.front + 1 == q.rear)
        return -1;
    int t;
    if (q.rear <= q.front)
    {
        for (int i = q.front + 1; i < MAXSIZE; i++)
        {
            printf("%d ", q.data[i]);
        }
        for (int i = 0; i <= q.rear-1; i++)
        {
            printf("%d ", q.data[i]);
        }
    }
    else
        for (int i = q.front+1; i <= q.rear-1; i++)
        {
            printf("%d ", q.data[i]);
        }

    printf("\n");
}