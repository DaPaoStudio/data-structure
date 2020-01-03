#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100
#define MAX 35277

typedef struct
{
    char ch;
    int weight, parent, lchild, rchild;
} Node, Tree[MAXSIZE];

typedef struct
{
    int front;
    int rear;
    int data[MAXSIZE];
} SqQueue;

void InitQueue(SqQueue *q);
void EnQueue(SqQueue *q, int i);
int DeQueue(SqQueue *q);

int Init(Tree t);
int Encode(Tree t, int flag);
void Decode(Tree t, int n);
void Print();
void TreePaint(Tree t, int n);

void InitTree(Tree t, int m, char s[m], int v[m]);
void Select(Tree t, int pos, int *x, int *y);
void Code(Tree t, int m, char s[m][m]);

/*
    ToBeTran.txt������� �����ļ�����ģʽ����
*/

int main(void)
{
    Tree t;
    char c;
    int flag = 0;
    printf("i ģʽ���ն����룬��������������hfmTree.txt\n");
    printf("e ģʽ�����ڴ�/hfmTree.txt��ȡ�������� ��ToBeTran.txt�������CodeFile.txt\n ��ȷ��hfmTree.txt ToBeTran.txt����\n");
    printf("d ģʽ: �����ڴ��еĹ����������ļ�CodeFile.txt�������TextFile.txt��\n ��ȷ���ڴ����й����������򿪳����ʹ�ù�i/eģʽ��CodeFile.c����\n");
    printf("p ģʽ: ���ն�����ʾCodeFile.txt����CodeFile.txtд��CodePrint.txt\n ��ȷ��CodeFile.txt����\n");
    printf("t ģʽ: ���ն���ʾ�ڴ��еĹ���������������TreePrint.txt\n ��ȷ���ڴ����й����������򿪳����ʹ�ù�i/eģʽ��\n");
    printf("����o�˳�\n");
    printf("\nѡ��ģʽ��");
    fflush(stdin);
    scanf("%c", &c);

    while (c != 'o')
    {
        if (c == 'i')
            flag = Init(t);
        else if (c == 'e')
        {

            flag = Encode(t, flag);
        }

        else if (c == 'd')
        {
            if (flag == 0)
                printf("�ڴ����޹�������\n");
            else
                Decode(t, flag);
        }
        else if (c == 'p')
            Print();
        else if (c == 't')
        {
            if (flag == 0)
                printf("�ڴ����޹�������\n");
            TreePaint(t, flag);
        }
        printf("ѡ��ģʽ��");
        fflush(stdout);
        fflush(stdin);
        c = getchar();
    }
}
void InitTree(Tree t, int m, char s[m], int v[m])
{
    for (int i = 0; i < m; i++)
    {
        t[i].ch = s[i];
        t[i].weight = v[i];
        t[i].parent = -1;
        t[i].lchild = -1;
        t[i].rchild = -1;
    }
    for (int i = m; i < 2 * m - 1; i++)
    {
        t[i].ch = 0;
        t[i].weight = 0;
        t[i].parent = -1;
        t[i].lchild = -1;
        t[i].rchild = -1;
    }
    int pos = m;
    while (pos != 2 * m - 1)
    {
        int x, y;
        Select(t, pos, &x, &y);
        t[pos].lchild = x;
        t[pos].rchild = y;
        t[pos].weight = t[x].weight + t[y].weight;
        t[x].parent = pos;
        t[y].parent = pos;
        pos++;
    }
}
void Select(Tree t, int pos, int *x, int *y)
{
    int x1, x2, w1 = MAX, w2 = MAX;
    for (int i = 0; i < pos; i++)
    {
        if (w1 > t[i].weight && t[i].parent == -1)
        {
            x2 = x1;
            w2 = w1;
            x1 = i;
            w1 = t[i].weight;
        }
        else if (w2 > t[i].weight && t[i].parent == -1)
        {
            x2 = i;
            w2 = t[i].weight;
        }
    }
    *x = x1;
    *y = x2;
}

void Code(Tree t, int m, char s[m][m])
{
    for (int i = 0; i < m; i++)
    {
        char string[m];
        string[m - 1] = '\0';
        int y = m - 2;
        int q = t[i].parent;
        int p = i;
        do
        {
            if (t[q].lchild == p)
                string[y--] = '0';
            else
                string[y--] = '1';
            p = q;
            q = t[q].parent;

        } while (q != -1);
        strcpy(s[i], string + y + 1);
    }
}

int Init(Tree t)
{
    FILE *f = fopen("hfmTree.txt", "w");
    int n;
    printf("�����ַ���");

    scanf("%d", &n);
    char s[n + 1];
    int x[n];
    for (int i = 0; i < n; i++)
    {
        printf("%d�ַ�:", i + 1);
        fflush(stdin);
        scanf("%c", &s[i]);
        printf("%dȨֵ", i + 1);
        fflush(stdin);
        scanf("%d", &x[i]);
    }
    InitTree(t, n, s, x);
    fprintf(f, "%d\n", n);
    for (int i = 0; i < 2 * n - 1; i++)
    {
        fprintf(f, "%c %d %d %d %d\n", t[i].ch, t[i].weight, t[i].parent, t[i].lchild, t[i].rchild);
    }
    fclose(f);
    printf("hfmTree.txtд�����\n");
    return n;
}

int Encode(Tree t, int flag)
{
    int n = flag;
    if (flag == 0)
    {
        FILE *f1 = fopen("hfmTree.txt", "r");
        if (f1 == NULL)
        {
            printf("hfmTree.txt��ʧ��\n");
            return 0;
        }
        fscanf(f1, "%d", &n);
        getc(f1);
        for (int i = 0; i < 2 * n - 1; i++)
        {
            fscanf(f1, "%c %d %d %d %d", &t[i].ch, &t[i].weight, &t[i].parent, &t[i].lchild, &t[i].rchild);
            getc(f1);
        }
        fclose(f1);
    }
    char s[n][n], e[n];
    for (int i = 0; i < n; i++)
        e[i] = t[i].ch;
    Code(t, n, s);
    FILE *f2 = fopen("ToBeTran.txt", "r");
    FILE *f3 = fopen("CodeFile.txt", "w");
    if (f2 == NULL)
    {
        printf("ToBeTran.txt��ʧ��\n");
        return n;
    }
    char ch = getc(f2);
    while (ch != EOF)
    {
        int t = 0;
        while (e[t] != ch)
        {
            if (t > n)
            {
                printf("error\n");
                break;
            };
            t++;
        }
        fprintf(f3, "%s", s[t]);
        ch = getc(f2);
    }
    fclose(f2);
    fclose(f3);
    printf("CodeFile.txtд�����\n");
    return n;
}

void Decode(Tree t, int n)
{
    int parent = 2 * n - 2, pt = 0;
    FILE *f1 = fopen("CodeFile.txt", "r");
    if(f1 == NULL)
    {
        printf("��CodeFile.txtʧ��\n");
        return ;
    }
    FILE *f2 = fopen("TextFile.txt", "w");
    char ch = getc(f1);
    pt = parent;
    while (ch != EOF)
    {
        if (ch == '0')
        {
            pt = t[pt].lchild;
            if (t[pt].lchild == -1 && t[pt].rchild == -1)
            {
                putc(t[pt].ch, f2);
                pt = parent;
            }
        }
        else
        {
            pt = t[pt].rchild;
            if (t[pt].lchild == -1 && t[pt].rchild == -1)
            {
                putc(t[pt].ch, f2);
                pt = parent;
            }
        }
        if(pt == -1)
        {
            printf("�������");
            break;
        }
        ch = getc(f1);
    }
    fclose(f1);
    fclose(f2);
    printf("TextFile.txtд�����\n");
}

void Print()
{
    int t = 0;
    FILE *f1 = fopen("CodeFile.txt", "r");
    if(f1 == NULL)
    {
        printf("CodeFile.c��ʧ��\n");
        return ;
    }
    FILE *f2 = fopen("CodePrin.txt", "w");
    char ch = getc(f1);
    while (ch != EOF)
    {
        t++;
        printf("%c", ch);
        putc(ch, f2);
        if (t % 50 == 0)
        {
            printf("\n");
            putc('\n', f2);
        }
        ch = getc(f1);
    }
    printf("\n");
    fclose(f1);
    fclose(f2);
    printf("CodeFile.txt��ʾ��� CodePrin.txtд�����\n");
}

void TreePaint(Tree t, int n)
{
    FILE *f = fopen("TreePrint.txt", "w");
    SqQueue q, p, l;
    InitQueue(&q);
    InitQueue(&p);
    InitQueue(&l);
    EnQueue(&q, 2 * n - 2);
    EnQueue(&p, 50);
    EnQueue(&l, 1);
    int dot = DeQueue(&q);
    int pos = DeQueue(&p);
    int level = DeQueue(&l);
    int pt = 0, lv = 1;
    while (dot != -1)
    {
        if (level > lv)
        {
            printf("\n");
            fprintf(f, "\n");
            lv++;
            pt = 0;
        }
        while (pt != pos)
        {
            printf(" ");
            fprintf(f, " ");
            pt++;
        }
        printf("%d", t[dot].weight);
        printf("%c", t[dot].ch);
        fprintf(f, "%d", t[dot].weight);
        fprintf(f, "%c", t[dot].ch);
        if (t[dot].lchild != -1)
        {
            EnQueue(&q, t[dot].lchild);
            EnQueue(&p, pos - (100 / pow(2, level + 1)));
            EnQueue(&l, lv + 1);
        }
        if (t[dot].rchild != -1)
        {
            EnQueue(&q, t[dot].rchild);
            EnQueue(&p, pos + (100 / pow(2, level + 1)));
            EnQueue(&l, lv + 1);
        }
        dot = DeQueue(&q);
        pos = DeQueue(&p);
        level = DeQueue(&l);
    }
    fclose(f);
    printf("\n");
    printf("TreePrint.txtд�����\n");
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
        return -1;
    return q->data[++q->front];
}