#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

int e[MAXSIZE];
int l[MAXSIZE];

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
    int data[MAXSIZE];
    int top;
} SqStack;

void Tsort(AdjList x, int m, int flag);
void InTsort(AdjList x, int m, int flag);

void Init(AdjList x, int t);
void visit(VNode n);

void InitStack(SqStack **s);
int Push(SqStack *s, int i);
int Pop(SqStack *s);

void ve(AdjList x, int m);
void vl(AdjList x, int m);
void CriticalPath(AdjList x, int m);

int main(void)
{
    AdjList x;
    int t;
    printf("how many:");
    scanf("%d", &t);
    Init(x, t);
    Tsort(x, t, 0);
    InTsort(x, t, 0);
    CriticalPath(x,t);
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
        int w = 0, v = 0;
        int y = 1;
        printf("%d\n", i + 1);
        printf("%d: ", y++);
        scanf("%d", &w);
        if (w != 0)
        {
            printf("value:");
            scanf("%d", &v);
            x[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
            p = x[i].firstarc;
            p->adjvex = w - 1;
            p->nextarc = NULL;
            p->Value = v;
            printf("%d: ", y++);
            scanf("%d", &w);
        }
        while (w != 0)
        {
            printf("value:");
            scanf("%d", &v);
            p->nextarc = (ArcNode *)malloc(sizeof(ArcNode));
            p = p->nextarc;
            p->nextarc = NULL;
            p->adjvex = w - 1;
            p->Value = v;
            printf("%d: ", y++);
            scanf("%d", &w);
        }
    }
}

void visit(VNode n)
{
    printf("%d", n.data);
}

int Push(SqStack *s, int i)
{
    if (s->top == 100)
        return -1;
    s->data[++s->top] = i;
    return 1;
}

int Pop(SqStack *s)
{
    if (s->top == -1)
        return -1;
    return s->data[s->top--];
}
void InitStack(SqStack **s)
{
    *s = (SqStack *)malloc(sizeof(SqStack));
    (*s)->top = -1;
}

void Tsort(AdjList x, int m, int flag)
{
    SqStack *s;
    InitStack(&s);
    int In[m];
    for (int i = 0; i < m; i++)
        In[i] = 0;
    for (int i = 0; i < m; i++)
    {
        ArcNode *p = x[i].firstarc;
        while (p != NULL)
        {
            In[p->adjvex]++;
            p = p->nextarc;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (In[i] == 0)
            Push(s, i);
    }
    int t = Pop(s);
    while (t != -1)
    {
        if (flag == 0)
            printf("%d ", t + 1);
        ArcNode *p = x[t].firstarc;
        while (p != NULL)
        {
            if ((--In[p->adjvex]) == 0)
                Push(s, p->adjvex);
            if (flag == 1)
                if (e[p->adjvex] < e[t] + p->Value)
                    e[p->adjvex] = e[t] + p->Value;
            p = p->nextarc;
        }
        t = Pop(s);
    }
    printf("\n");
}
void InTsort(AdjList x, int m, int flag)
{
    SqStack *s;
    InitStack(&s);
    int Out[m], Node[m][m], In[m], V[m][m];
    for (int i = 0; i < m; i++)
    {
        Out[i] = 0;
        In[i] = 0;
        for (int t = 0; t < m; t++)
        {
            Node[i][t] = -1;
            V[i][t] = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        ArcNode *p = x[i].firstarc;
        while (p != NULL)
        {
            Out[i]++;
            Node[p->adjvex][In[p->adjvex]] = i;
            V[p->adjvex][In[p->adjvex]] = p->Value;
            In[p->adjvex]++;
            p = p->nextarc;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (Out[i] == 0)
            Push(s, i);
    }
    int t = Pop(s);
    while (t != -1)
    {
        if (flag == 0)
            printf("%d ", t + 1);
        int i = 0;
        int p = Node[t][i];
        while (p != -1)
        {
            if ((--Out[p]) == 0)
                Push(s, p);
            if (flag == 1)
                if (l[p] > l[t] - V[t][i])
                    l[p] = l[t] - V[t][i];
            i++;
            p = Node[t][i];
        }
        t = Pop(s);
    }
    printf("\n");
}

void ve(AdjList x, int m)
{
    for (int i = 0; i < m; i++)
        e[i] = 0;
    Tsort(x, m, 1);
}

void vl(AdjList x, int m)
{
    for (int i = 0; i < m; i++)
        l[i] = e[m - 1];
    InTsort(x, m, 1);
}

void CriticalPath(AdjList x, int m)
{
    ve(x, m);
    vl(x, m);
    ArcNode *p;
    int from[MAXSIZE], to[MAXSIZE], e2[MAXSIZE], l2[MAXSIZE];
    int t = 0;
    for (int i = 0; i < m; i++)
    {
        p = x[i].firstarc;
        while (p != NULL)
        {
            from[t] = i;
            to[t] = p->adjvex;
            e2[t] = e[i];
            l2[t] = l[p->adjvex] - p->Value;
            p = p->nextarc;
            t++;
        }
    }
    for (int i = 0; i < t; i++)
    {
        if(e2[i]==l2[i])
            printf("%d->%d\t",from[i]+1,to[i]+1);
    }
    printf("\n");
}