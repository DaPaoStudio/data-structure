#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 100

int visited[MAXSIZE];
int d[MAXSIZE][MAXSIZE];

typedef struct
{
    int data, parent;
} No, Tr[MAXSIZE];

typedef struct
{
    int data[MAXSIZE];
    int top;
} SqStack;

typedef struct Side
{
    int i, j, value;
    struct Side *pi, *pj;
} Side;

typedef struct Node
{
    int data;
    Side *f;
} Node, List[MAXSIZE];

typedef struct
{
    int front;
    int rear;
    int data[MAXSIZE];
} SqQueue;

void visit(Node n);
void Init(List x, int t, int v);
void Print(int e);

int BFS(List x, int i);
void DFS(List x, int i);
void D(List x, int i, int j1, int j2, int k1, int k2, int value);
void TreePaint(int flag, int n, int num, int level);
void DFSStack(List x, int i);

void InitQueue(SqQueue *q);
void EnQueue(SqQueue *q, List x, int i);
int DeQueue(SqQueue *q);

void InitStack(SqStack **s);
int Push(SqStack *s, int i);
int Pop(SqStack *s);
int P(SqStack *s);

Side s1[MAXSIZE], s2[MAXSIZE];
int t1[MAXSIZE], t2[MAXSIZE];
int i1, i2;
int m[MAXSIZE];
Tr tr1, tr2;

int main(void)
{
    List x;
    int t;
    printf("how many:");
    scanf("%d", &t);
    printf("If the edge has a right value,enter 1.If not,enter 0.\n");
    int v;
    scanf("%d", &v);
    Init(x, t, v);
    int p;
    printf("where:");
    scanf("%d", &p);
    tr1[p - 1].parent = -1;
    tr2[p - 1].parent = -1;
    for (int i = 0; i < t; i++)
        visited[i] = 0;
    printf("DFS:\n");
    DFS(x, p);
    //DFSStack(x, p);
    printf("\n");
    Print(1);
    for (int i = 0; i < t; i++)
        visited[i] = 0;
    TreePaint(1, p, t, 1);
    printf("\n");
    for (int i = 0; i < t; i++)
        visited[i] = 0;
    BFS(x, p);

    Print(0);
    for (int i = 0; i < t; i++)
        visited[i] = 0;
    TreePaint(2, p, t, 1);
    printf("\n");
    if (v == 1)
    {
        for (int i = 0; i < t; i++)
            visited[i] = 0;
        printf("from:");
        scanf("%d", &p);
        printf("to:");
        int to1;
        scanf("%d", &to1);
        printf("don't pass by:");
        int k2;
        scanf("%d", &k2);
        D(x, p, 0, 1, to1, k2, 0);
        int y = 0;
        while (d[y][MAXSIZE - 2] != 0)
        {
            if (d[y][0] == 1)
            {
                printf("%d", p);
                int i = 2;
                while (d[y][i] != 0)
                {
                    printf("->%d", d[y][i++]);
                }
                printf(" value:%d\n", d[y][MAXSIZE - 1]);
            }
            y++;
        }
    }
}

void DFS(List x, int i)
{
    visit(x[i - 1]);
    visited[i - 1] = 1;
    Side *p = x[i - 1].f;
    while (p != NULL)
    {
        if (p->i == i)
        {
            if (visited[p->j - 1] == 0)
            {
                t1[i1] = 0;
                s1[i1++] = *p;
                tr1[p->j - 1].parent = i - 1;
                tr1[i - 1].data++;
                DFS(x, p->j);
            }
            p = p->pi;
        }
        else if (p->j == i)
        {
            if (visited[p->i - 1] == 0)
            {
                t1[i1] = 1;
                s1[i1++] = *p;
                tr1[p->i - 1].parent = i - 1;
                tr1[i - 1].data++;
                DFS(x, p->i);
            }
            p = p->pj;
        }
    }
}

void visit(Node n)
{
    printf("%d ", n.data);
}

void Init(List x, int t, int v)
{
    for (int i = 0; i < t; i++)
    {
        x[i].data = i + 1;
        x[i].f = NULL;
    }
    Side **p1, **p2;
    int from, to, value;
    printf("from:");
    scanf("%d", &from);
    while (from != 0 && from <= t)
    {
        printf("to:");
        scanf("%d", &to);
        if (to == 0 && to > t)
            break;
        if (v == 1)
        {
            printf("value:");
            scanf("%d", &value);
        }
        p1 = &x[from - 1].f;
        while (*p1 != NULL)
        {
            if ((*p1)->i == from)
                p1 = &((*p1)->pi);
            else
                p1 = &((*p1)->pj);
        }
        *p1 = (Side *)malloc(sizeof(Side));
        (*p1)->i = from;
        (*p1)->j = to;
        (*p1)->value = value;
        (*p1)->pi = NULL;
        (*p1)->pj = NULL;
        p2 = &x[to - 1].f;
        while (*p2 != NULL)
        {
            if ((*p2)->i == to)
                p2 = &((*p2)->pi);
            else
                p2 = &((*p2)->pj);
        }
        *p2 = *p1;
        printf("from:");
        scanf("%d", &from);
    }
}

void InitQueue(SqQueue *q)
{
    q->front = 0;
    q->rear = 1;
}

void EnQueue(SqQueue *q, List x, int i)
{
    if (q->rear == q->front)
        printf("ERROR");
    else
    {
        Side *p = x[i - 1].f;
        while (p != NULL)
        {
            if (p->i == i)
            {
                if (visited[p->j - 1] == 0)
                {
                    if (m[p->j - 1] == 0)
                    {
                        t2[i2] = 0;
                        s2[i2++] = *p;
                        tr2[p->j - 1].parent = i - 1;
                        tr2[i - 1].data++;
                        m[p->j - 1] = 1;
                    }
                    q->data[q->rear++] = p->j;
                    q->rear = q->rear % MAXSIZE;
                }
                p = p->pi;
            }
            else
            {
                if (visited[p->i - 1] == 0)
                {
                    if (m[p->i - 1] == 0)
                    {
                        t2[i2] = 1;
                        s2[i2++] = *p;
                        tr2[p->i - 1].parent = i - 1;
                        tr2[i - 1].data++;
                        m[p->i - 1] = 1;
                    }
                    q->data[q->rear++] = p->i;
                    q->rear = q->rear % MAXSIZE;
                }
                p = p->pj;
            }
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

int BFS(List x, int i)
{
    printf("BFS:\n");
    SqQueue q;
    InitQueue(&q);
    visit(x[i - 1]);
    visited[i - 1] = 1;
    EnQueue(&q, x, i);
    int p = DeQueue(&q);
    while (p != -1)
    {
        if (visited[p - 1] == 0)
        {
            visit(x[p - 1]);
            visited[p - 1] = 1;

            EnQueue(&q, x, p);
        }
        p = DeQueue(&q);
    }
    printf("\n");
    return 0;
}
void Print(int e)
{
    if (e == 1)
    {
        for (int i = 0; i < i1; i++)
        {
            if (t1[i] == 0)
                printf("%d->%d\n", s1[i].i, s1[i].j);
            else
                printf("%d->%d\n", s1[i].j, s1[i].i);
        }
    }
    else
    {
        for (int i = 0; i < i2; i++)
        {
            if (t2[i] == 0)
                printf("%d->%d\n", s2[i].i, s2[i].j);
            else
                printf("%d->%d\n", s2[i].j, s2[i].i);
        }
    }
}

int j3;

void D(List x, int i, int j1, int j2, int k1, int k2, int value)
{
    d[j1][j2++] = i;
    d[j1][MAXSIZE - 1] += value;
    d[j1][MAXSIZE - 2] = 1; //已使用
    if (i == k1)
    {
        d[j1][0] = 1;
        return;
    }
    visited[i - 1] = 1;
    Side *p = x[i - 1].f;
    int flag = 0;
    int v3 = d[j1][MAXSIZE - 1];
    while (p != NULL)
    {
        if (p->i == i)
        {
            if (visited[p->j - 1] == 0 && p->j != k2)
            {
                if (flag != 0)
                {
                    j3++;
                    for (int p = 1; p < j2; p++)
                    {
                        d[j3][p] = d[j1][p];
                    }
                    d[j3][MAXSIZE - 1] = v3;
                    d[j3][MAXSIZE - 2] = 1;
                }

                D(x, p->j, j3, j2, k1, k2, p->value);

                flag++;
            }
            p = p->pi;
        }
        else if (p->j == i)
        {
            if (visited[p->i - 1] == 0 && p->i != k2)
            {
                if (flag != 0)
                {
                    j3++;
                    for (int p = 1; p < j2; p++)
                    {
                        d[j3][p] = d[j1][p];
                    }
                    d[j3][MAXSIZE - 1] = v3;
                    d[j3][MAXSIZE - 2] = 1;
                }
                D(x, p->i, j3, j2, k1, k2, p->value);
                flag++;
            }
            p = p->pj;
        }
    }
    visited[i - 1] = 0;
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

int P(SqStack *s)
{
    if (s->top == -1)
        return -1;
    return s->data[s->top];
}

void InitStack(SqStack **s)
{
    *s = (SqStack *)malloc(sizeof(SqStack));
    (*s)->top = -1;
}
void DFSStack(List x, int i)
{
    SqStack *s;
    InitStack(&s);
    int t, flag = 0;
    Side *p;
    Push(s, i);
    visit(x[i - 1]);
    visited[i - 1] = 1;
    while (1)
    {
        t = P(s);
        p = x[t - 1].f;
        flag = 0;
        while (p != NULL)
        {
            if (p->i == i)
            {
                if (visited[p->j - 1] == 0)
                {
                    t1[i1] = 0;
                    s1[i1++] = *p;
                    visit(x[p->j - 1]);
                    visited[p->j - 1] = 1;
                    tr1[p->j - 1].parent = i - 1;
                    tr1[i - 1].data++;
                    Push(s, p->j);
                    flag = 1;
                    break;
                }
                p = p->pi;
            }
            else if (p->j == i)
            {
                if (visited[p->i - 1] == 0)
                {
                    t1[i1] = 1;
                    s1[i1++] = *p;
                    visit(x[p->i - 1]);
                    visited[p->i - 1] = 1;
                    tr2[p->i - 1].parent = i - 1;
                    tr1[i - 1].data++;
                    Push(s, p->i);
                    flag = 1;
                    break;
                }
                p = p->pj;
            }
        }
        if (flag == 0)
            if (Pop(s) == -1)
                break;
    }
}
void TreePaint(int flag, int n, int num, int level)
{
    int l = 0;
    while (l++ < 2 * level)
        printf(" ");
    printf("|%d\n", n);
    if (flag == 1)
        for (int t = 0; t < num; t++)
            if (tr1[t].parent == n - 1 && visited[t] == 0)
            {
                TreePaint(flag, t + 1, num, level + 1);
            }
            else
            {
            }

    else if (flag == 2)
    {
        for (int t = 0; t < num; t++)
            if (tr2[t].parent == n - 1 && visited[t] == 0)
            {
                TreePaint(flag, t + 1, num, level + 1);
            }
    }
}