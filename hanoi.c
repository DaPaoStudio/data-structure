#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

int c = 0;

typedef struct
{
    int data[MAXSIZE];
    int top;
    int i;
} SqStack;

void hanoi(int n,SqStack *s1,SqStack *s2,SqStack *s3);
void InitStack(SqStack **s);
int Push(SqStack *s, int i);
int Pop(SqStack *s);
void move(SqStack *s1,int n,SqStack *s2);
void Init(SqStack **s,int n);
int Read(SqStack s);

int main(void)
{
    SqStack *s1,*s2,*s3;
    Init(&s1,3);
    InitStack(&s2);
    InitStack(&s3);
    s1->i =1;
    s2->i =2;
    s3->i =3;
    hanoi(3,s1,s2,s3);
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

int Read(SqStack s)
{
    int n = s.top,i=-1;
    while(i++<n)
        printf("%d",s.data[i]);
    printf("\n");
}

void InitStack(SqStack **s)
{
    *s = (SqStack *)malloc(sizeof(SqStack));
    (*s)->top = -1;
}

void hanoi(int n,SqStack *s1,SqStack *s2,SqStack *s3)
{
    
    if(n==1)
        move (s1,1,s3);
    else
    {   
        hanoi(n-1,s1,s3,s2); 
        move(s1,n,s3);
        hanoi(n-1,s2,s1,s3);   
    }
}

void move(SqStack *s1,int n,SqStack *s2)
{
    Push(s2,Pop(s1));
    printf("%d Move disk %d from %d to %d\n",++c,n,s1->i,s2->i);
}

void Init(SqStack **s,int n)
{
    InitStack(s);
    for(int i =0 ;i<n;i++)
        Push(*s,n-i);
}