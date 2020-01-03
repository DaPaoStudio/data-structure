#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

typedef struct
{
	int front;
	int rear;
	char data[MAXSIZE];
} SqQueue;

typedef struct
{
	char data[MAXSIZE];
	int top;
} SqStack;

void guizheng(char *a, char b[][MAXSIZE], int x);
void tihuan(char a, char b[], char *c); //将b中a替换成c
void change(char *s, char *a, int rule, char b[][MAXSIZE], char s1[]);

void InitQueue(SqQueue *q);
void EnQueue(SqQueue *q, char i);
char DeQueue(SqQueue *q);

void InitStack(SqStack **s);
int Push(SqStack *s, char i);
char Pop(SqStack *s);

int main(void)
{
	/*
	char a[MAXSIZE] = "BA";
	char b[MAXSIZE][MAXSIZE] = {"tAdA", "sae"};
	guizheng(a, b, 2);
	//printf("%s", b[1]);
	char s1[MAXSIZE];
	char s[] = "B(ehnxgz)B";
	change(s, a, 2, b, s1);
	printf("%s", s1);
*/
	char a[MAXSIZE];
	char b[MAXSIZE][MAXSIZE];
	char p;
	int w;
	char s[MAXSIZE];
	printf("自定义规则1 请输入0\n使用默认规则1 请输入1\n");
	scanf("%d", &p);
	getchar();
	if (p == 1)
	{
		w = 2;
		strcpy(a, "BA");
		strcpy(b[0], "tAdA");
		strcpy(b[1], "sae");
	}
	else if (p == 0)
	{
		printf("规则数量：");
		scanf("%d", &w);
		for (int i = 0; i < w; i++)
		{
			char ch;
			printf("一个字符：");
			fflush(stdin);
			scanf("%c", &ch);
			fflush(stdin);
			a[i] = ch;
			printf("替换成：");
			fflush(stdin);
			gets(b[i]);
		}
	}
	printf("需要翻译的语言：");
	gets(s);
	guizheng(a, b, w);
	change(s, a, w, b, s);
	printf("%s", s);
}
void guizheng(char *a, char b[][MAXSIZE], int x)
{
	int i = 0;
	while (i < x)
	{
		for (int n = 0; n < x; n++)
		{
			tihuan(a[i], b[n], b[i]);
		}
		i++;
	}
}

void tihuan(char a, char b[], char *c)
{
	int clength = 0, blength = 0;
	while (c[clength] != '\0')
		clength++;
	while (b[blength] != '\0')
		blength++;
	for (int i = 0; b[i] != '\0'; i++)
	{
		if (a == b[i])
		{
			for (int t = blength - 1; t != i; t--)
			{
				b[t + clength - 1] = b[t];
			}
			for (int t = 0; t < clength; t++, i++)
			{
				b[i] = c[t];
			}
			blength += (clength - 1);
		}
	}
}

void InitQueue(SqQueue *q)
{
	q->front = 0;
	q->rear = 1;
}

void EnQueue(SqQueue *q, char i)
{
	if (q->rear == q->front)
		printf("ERROR");
	else

	{
		q->data[q->rear++] = i;
		q->rear = q->rear % MAXSIZE;
	}
}

char DeQueue(SqQueue *q)
{
	q->front = q->front % MAXSIZE;
	if (q->front + 1 == q->rear)
		return 0;
	return q->data[++q->front];
}

int Push(SqStack *s, char i)
{
	if (s->top == 100)
		return -1;
	s->data[++s->top] = i;
	return 1;
}

char Pop(SqStack *s)
{
	if (s->top == -1)
		return 0;
	return s->data[s->top--];
}

void InitStack(SqStack **s)
{
	*s = (SqStack *)malloc(sizeof(SqStack));
	(*s)->top = -1;
}

void change(char *s, char *a, int rule, char b[][MAXSIZE], char s1[])
{
	int length = 0;
	while (s[length] != '\0')
		length++;
	SqQueue q;
	SqStack *st;
	InitQueue(&q);
	InitStack(&st);
	int i = length - 1;
	while (i != -1)
	{
		if (s[i] == '(')
		{
			char c1 = Pop(st);
			char c2 = Pop(st);
			while (c2 != ')')
			{
				EnQueue(&q, c2);
				c2 = Pop(st);
			}
			c2 = DeQueue(&q);
			while (c2 != 0)
			{
				Push(st, c1);
				Push(st, c2);
				c2 = DeQueue(&q);
			}
			Push(st, c1);
		}
		else
			Push(st, s[i]);
		i--;
	}
	int o = 0;
	int mark = 0;
	char ch = Pop(st);
	while (ch != 0)
	{
		for (int e = 0; e < rule; e++)
		{
			if (ch == a[e])
			{
				for (int p = 0; b[e][p] != '\0'; p++)
				{
					s1[o++] = b[e][p];
				}
				mark = 1;
			}
		}
		if (mark == 0)
			s1[o++] = ch;
		mark = 0;
		ch = Pop(st);
	}
	s1[o] = '\0';
}