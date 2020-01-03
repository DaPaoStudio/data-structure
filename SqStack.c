#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct
{
    int data[MAXSIZE];
    int top;
} SqStack;

void InitStack(SqStack **s);
int Push(SqStack *s, int i);
int Pop(SqStack *s);
int Read(SqStack s);

void conversion(int t, int x); //进制转换 t为十进制数 x为进制
int kuohao(char *);            //匹配为1 不匹配为-1
void LineEdit(char *st);//行编辑器 #退格 @退行

int main(void)
{

    //printf("%d",kuohao("({([)}])"));
    LineEdit("122131#sfse");
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
    for (int i = Pop(&s); i != -1; i = Pop(&s))
        printf("%d ", i);
}

void InitStack(SqStack **s)
{
    *s = (SqStack *)malloc(sizeof(SqStack));
    (*s)->top = -1;
}

void conversion(int t, int x)
{
    SqStack *s;
    InitStack(&s);
    while (t)
    {
        Push(s, t % x);
        t /= x;
    }
    Read(*s);
}

int kuohao(char *s)
{
    int i = 0;
    SqStack *t;
    InitStack(&t);
    while (s[i] != '\0')
    {
        if (s[i] == '(')
            Push(t, 1);
        else if (s[i] == '[')
            Push(t, 2);
        else if (s[i] == '{')
            Push(t, 3);
        else if (s[i] == ')')
            if (Pop(t) != 1)
                return -1;
        if (s[i] == ']')
            if (Pop(t) != 2)
                return -1;
        if (s[i] == '}')
            if (Pop(t) != 3)
                return -1;
        i++;
    }
    if (Pop(t) != -1)
        return -1;
    return 1;
}

void LineEdit(char *st)
{
    SqStack *s1, *s2;
    InitStack(&s1);
    InitStack(&s2);
    for (int i = 0; st[i] != '\0'; i++)
    {
        if (st[i] == '#')
            Pop(s1);
        else if (st[i] == '@')
            for (int j = Pop(s1); j != -1; j = Pop(s1))
                ;
        else if (st[i] == '\n')
        {
            int j = Pop(s1);
            while (j != -1)
            {
                Push(s2, (int)j);
                j = Pop(s1);
            }

            j = Pop(s2);
            while (j != -1)
            {
                char ch = (char)j;
                printf("%c", ch);
                j = Pop(s2);
            }
            printf("\n");
        }
        else
        {
            Push(s1, (int)st[i]);
        }
    }
    int j = Pop(s1);
    while (j != -1)
    {
        Push(s2, (int)j);
        j = Pop(s1);
    }

    j = Pop(s2);
    while (j != -1)
    {
        char ch = (char)j;
        printf("%c", ch);
        j = Pop(s2);
    }
    printf("\n");
}