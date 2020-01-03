#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct
{
    int ord;
    int x;
    int y;
    int di; // 0上走 1右 2下 3左
} Path;

typedef struct
{
    Path data[MAXSIZE];
    int top;
} SqStack;

void InitStack(SqStack **s);
int Push(SqStack *s, Path p);
int Pop(SqStack *s, Path **t);
int Read(SqStack s);

Path InitPath(int ord, int x, int y);
int MazePath(Path start, Path end);
int Pass(Path t);
void FoorPrint(Path t);
Path Next(Path *t);
int P(Path p[], int t, int x, int y, int num, int m[num][num]);

void Print();

int mg[10][10] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
int mg2[10][10] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main(void)
{
    //printf("1");
    /*
    int t = MazePath(InitPath(0, 1, 1), InitPath(0, 8, 8));
    printf("%d\n", t);
*/
    Path p[100];
    p[0].x = 1;
    p[0].y = 1;
    int o = P(p,0,8,8,10,mg);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            printf("%d", mg[i][j]);
        printf("\n");
    }
    for (int j = 0; j <= o; j++)
            printf("<%d %d>\n", p[j].x,p[j].y);
}

int Push(SqStack *s, Path p)
{
    if (s->top == 100)
        return -1;
    s->data[++s->top] = p;
    return 1;
}

int Pop(SqStack *s, Path **t)
{
    if (s->top == -1)
        return -1;
    *t = &(s->data[s->top--]);
    return 1;
}

int Read(SqStack s)
{
    Path *p;
    for (int i = Pop(&s, &p); i != -1; i = Pop(&s, &p))
        printf("%d x:%d y:%d di:%d", p->ord, p->x, p->y, p->di);
}

void InitStack(SqStack **s)
{
    *s = (SqStack *)malloc(sizeof(SqStack));
    (*s)->top = -1;
}

Path InitPath(int ord, int x, int y)
{
    Path *t;
    t = (Path *)malloc(sizeof(Path));
    t->ord = ord;
    t->x = x;
    t->y = y;
    t->di = 0;
    return *t;
}

int MazePath(Path start, Path end)
{
    SqStack *s;
    InitStack(&s);
    Path *p1 = &start;
    Path p2;
    do
    {
        printf("%d,%d\n", p1->x, p1->y);
        if (p1->di <= 3)
        {
            FoorPrint(*p1);

            Push(s, *p1);
            if (p1->x == end.x && p1->y == end.y)
            {
                Read(*s);
                printf("\n");
                return 1;
            }
            *p1 = Next(p1);
            FoorPrint(*p1);
        }
        else
        {
            if (s->top != -1) //s不是空
            {
                Pop(s, &p1);
            }
            else
            {
                Read(*s);
                return -1;
            }
        }
    } while (s->top != -1);
    Read(*s);
    return -2;
}

int Pass(Path t)
{
    return (!mg2[t.x][t.y]);
}

void FoorPrint(Path t)
{
    mg2[t.x][t.y] = 1;
}

Path Next(Path *t)
{
    if (t->di == 0)
    {
        t->di++;
        if (Pass(InitPath(0, t->x - 1, t->y)))
            return InitPath(0, t->x - 1, t->y);
    }
    if (t->di == 1)
    {
        t->di++;
        if (Pass(InitPath(0, t->x, t->y + 1)))
            return InitPath(0, t->x, t->y + 1);
    }
    if (t->di == 2)
    {
        t->di++;
        if (Pass(InitPath(0, t->x + 1, t->y)))
            return InitPath(0, t->x + 1, t->y);
    }
    if (t->di == 3)
    {
        t->di++;
        if (Pass(InitPath(0, t->x, t->y - 1)))
            return InitPath(0, t->x, t->y - 1);
    }
    if (t->di == 4)
    {
        t->di++;
        return *t;
    }
    t->di++;
    return *t;
}

void Print()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            printf("%d", mg2[i][j]);
        printf("\n");
    }
}

int P(Path p[], int t, int x, int y, int num, int m[num][num])
{
    m[p[t].x][p[t].y]=1;
    if (p[t].x == x && p[t].y == y)
        return t;
    if (p[t].x + 1<num&&m[p[t].x + 1][p[t].y] == 0)
    {
        p[t + 1].x = p[t].x + 1;
        p[t + 1].y = p[t].y;
        int r = P(p,t+1,x,y,num,m);
        if(r!=0)
            return r;
    }
    if (p[t].y+1<num&&m[p[t].x ][p[t].y+1] == 0)
    {
        p[t + 1].x = p[t].x ;
        p[t + 1].y = p[t].y+1;
        int r = P(p,t+1,x,y,num,m);
        if(r!=0)
            return r;
    }
    if (p[t].x-1>=0&&m[p[t].x-1][p[t].y] == 0)
    {
        p[t + 1].x = p[t].x-1 ;
        p[t + 1].y = p[t].y;
        int r = P(p,t+1,x,y,num,m);
        if(r!=0)
            return r;
    }
    if (p[t].y-1>=0&&m[p[t].x][p[t].y-1] == 0)
    {
        p[t + 1].x = p[t].x ;
        p[t + 1].y = p[t].y-1;
        int r = P(p,t+1,x,y,num,m);
        if(r!=0)
            return r;
    }
    return 0;
}