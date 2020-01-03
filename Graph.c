#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

int visited[MAXSIZE];

typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    int Value;
} ArcNode;

typedef struct VNode
{
    int data;
    ArcNode *firstarc;
} VNode, AdjList[MAXSIZE];

typedef struct
{
    AdjList vertics;
    int vexnum, arcnum; //顶点数 弧数
    int kind;
} ALGraph;

typedef struct
{
    int front;
    int rear;
    int data[MAXSIZE];
} SqQueue;

void DFS(AdjList x, int i);
void visit(VNode n);
void Init(AdjList x, int t);
int DFSTraverse(AdjList x, int i);
int BFSTraverse(AdjList x, int i);

void InitQueue(SqQueue *q);
void EnQueue(SqQueue *q, AdjList x, int i);
int DeQueue(SqQueue *q);

int main(void)
{
    AdjList x;
    int t;
    printf("how many:");
    scanf("%d", &t);
    Init(x, t);
    //printf("%d",x[0].firstarc->adjvex);
    //DFSTraverse(x, t);
    BFSTraverse(x, t);
}

void DFS(AdjList x, int i)
{
    visit(x[i]);
    visited[i] = 1;
    ArcNode *p = x[i].firstarc;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
            DFS(x, p->adjvex);
        p = p->nextarc;
    }
}

int DFSTraverse(AdjList x, int i)
{
    int times = 0;
    for (int o = 0; o < i; o++)
        visited[o] = 0;
    for (int w = 0; w < i; w++)
    {
        if (visited[w] == 0)
        {
            DFS(x, w);
            times++;
        }
    }
    return times;
}

void visit(VNode n)
{
    printf("%d", n.data);
}

void Init(AdjList x, int t)
{
    for (int i = 0; i < t; i++)
    {
        x[i].data = i + 1;
        x[i].firstarc = NULL;
    }
    ArcNode *p;
    for (int i = 0; i < t; i++)
    {
        int w = 0;
        int y = 1;
        printf("%d\n", i + 1);
        printf("%d: ", y++);
        scanf("%d", &w);
        if (w != 0)
        {
            x[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
            p = x[i].firstarc;
            p->adjvex = w - 1;
            p->nextarc = NULL;
            printf("%d: ", y++);
            scanf("%d", &w);
        }
        while (w != 0)
        {
            p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
            p = p->nextarc;
            p->nextarc = NULL;
            p->adjvex = w - 1;
            printf("%d: ", y++);
            scanf("%d", &w);
        }
    }
}

void InitQueue(SqQueue *q)
{
    q->front = 0;
    q->rear = 1;
}

void EnQueue(SqQueue *q, AdjList x, int i)
{
    if (q->rear == q->front)
        printf("ERROR");
    else
    {
        ArcNode *p = x[i].firstarc;
        while (p != NULL)
        {
            if (visited[p->adjvex] == 0)
            {
                q->data[q->rear++] = p->adjvex;
                q->rear = q->rear % MAXSIZE;
            }
            p = p->nextarc;
        }
    }
}

int DeQueue(SqQueue *q)
{
    q->front = q->front % MAXSIZE;
    if (q->front + 1 == q->rear)
        return -1;
    return q->data[++q->front];
}

int BFSTraverse(AdjList x, int i)
{
    int times = 0;
    for (int o = 0; o < i; o++)
        visited[o] = 0;
    SqQueue q;
    InitQueue(&q);
    for (int r = 0; r < i; r++)
    {
        if (visited[r] == 0)
        {
            visit(x[r]);
            visited[r]  =1;
            times++;
            EnQueue(&q, x, r);

            int p = DeQueue(&q);
            while (p != -1)
            {
                if (visited[p] == 0)
                {
                    visit(x[p]);
                    visited[p] = 1;
                    EnQueue(&q, x, p);
                }
                p = DeQueue(&q);
            }
        }
    }
    return times;
}