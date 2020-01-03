#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
/*
    ( 直接入
    ) 找到(
    其他符号 遇到优先级低 或 (
    0+ 1- 2* 3/ 4( 5)
*/
typedef struct
{
    int data[MAXSIZE];
    int top;
} SqStack;
/*
    栈基本操作
*/
void InitStack(SqStack **s);
int Push(SqStack *s, int i);
int Pop(SqStack *s);
/*
    后缀
*/
int youxian(SqStack s, int n); //判断此时 出栈(返回1 或 入栈(返回0
int fuhao(char c);             //0+ 1- 2* 3/ 4( 5)

int kuohao(char *); //括号 匹配为1 不匹配为-1
int EE(char *s);

int main(void)
{
    char *s = "9+(3-1)*3+10/2";
    if (kuohao(s))
    {
        EE(s);
    }
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

int youxian(SqStack s, int n)
{
    if (s.top == -1) //空栈
        return 0;
    if (n == 4)
        return 0;
    else if (n == 5)
        return 1;
    int i = s.data[s.top];

    if (i == 4)
        return 0;
    if (n / 2 > i / 2)
        return 0;
    return 1;
}

int fuhao(char c)
{
    if (c == '+')
        return 0;
    else if (c == '-')
        return 1;
    else if (c == '*')
        return 2;
    else if (c == '/')
        return 3;
    else if (c == '(')
        return 4;
    else if (c == ')')
        return 5;
    return -1;
}

int EE(char *s)
{
    int i = 0;

    SqStack *s1, *s2; //s1数字 s2符号
    InitStack(&s1);
    InitStack(&s2);
    int e = 0; //前一个为数字 1
    int r = 0; //记录临时值
    for (; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9') //数字
        {
            e = 1;
            r = r * 10 + s[i] - '0';
        }
        else
        {
            if (e == 1)
            {
                e = 0;
                Push(s1, r);
                r = 0;
            }

            int t = fuhao(s[i]);
            if (youxian(*s2, t)) //出
            {
                do
                {
                    int q = Pop(s2);
                    if (q == 0)
                    {
                        int x = Pop(s1), y = Pop(s1);
                        Push(s1, x + y);
                    }
                    else if (q == 1)
                    {
                        int x = Pop(s1), y = Pop(s1);
                        Push(s1, y-x);
                    }
                    else if (q == 2)
                    {
                        int x = Pop(s1), y = Pop(s1);
                        Push(s1, x * y);
                    }
                    else if (q == 3)
                    {
                        int x = Pop(s1), y = Pop(s1);
                        Push(s1, y/x);
                    }
                    else if (q==4&&t==5)
                        break;
                } while (youxian(*s2, t));
            }
            //入
            if (t != 5)
                Push(s2, t);
        }
    }
    if (e == 1)
        Push(s1, r);

    int q = Pop(s2);
    
    while (q != -1)
    {

        if (q == 0)
        {
            int x = Pop(s1), y = Pop(s1);
            Push(s1, x + y);
        }
        else if (q == 1)
        {
            int x = Pop(s1), y = Pop(s1);
            Push(s1, y - x);
        }
        else if (q == 2)
        {
            int x = Pop(s1), y = Pop(s1);
            Push(s1, x * y);
        }
        else if (q == 3)
        {
            int x = Pop(s1), y = Pop(s1);
            Push(s1, y / x);
        }
        q = Pop(s2);
    }
    int w = Pop(s1);
    printf("%d", w);
    return w;
}