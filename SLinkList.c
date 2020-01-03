#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 100

typedef struct List
{
    int data;
    int cur;
}Node,SLinkList[MAXSIZE];
/*
    0.cur存储空闲空间
    cur相当于指针
    最后一个节点的cur为第一个元素
*/

void InitList(SLinkList t);
int Malloc_SL(SLinkList t);
void Free_SL(SLinkList t,int k);
void ListInsert(SLinkList t,int i,int n);
void ListDelete(SLinkList t,int i);
int Locate(SLinkList t,int i); //返回i-1的位置
void ReadList(SLinkList t);
void difference(SLinkList t1,SLinkList t2);//结果保存 t1(暂时未写完 比较麻烦)

int main(void)
{
    SLinkList l1;
    InitList(l1);
    for(int i =1;i<MAXSIZE;i++)
        ListInsert(l1,i,i);
    for(int j =5;j<MAXSIZE-3;j+=5)
        ListDelete(l1,j);
    ReadList(l1);
}

void InitList(SLinkList t)
{
    for(int i=0;i<MAXSIZE-1;i++)
    {
        t[i].cur = i+1;
    }
    t[MAXSIZE-1].cur=0;
}

int Malloc_SL(SLinkList t)
{
    int i = t[0].cur;
    if(t[0].cur)
        t[0].cur = t[i].cur;
    return i;
}

void Free_SL(SLinkList t,int k)
{
    t[k].cur = t[0].cur;
    t[0].cur = k;
}

void ListInsert(SLinkList t,int i,int n)
{
    int j,k,l;
    j = Malloc_SL(t);
    if(j)
    {
        t[j].data = n;
        k=Locate(t,i);//第i-1个元素
        t[j].cur = t[k].cur;
        t[k].cur = j;
    }
}

void ListDelete(SLinkList t,int i)
{
    int k=Locate(t,i),j=t[k].cur;
    t[k].cur = t[j].cur;
    Free_SL(t,j);
}

int Locate(SLinkList t,int i)
{
    int k = MAXSIZE-1;
    for(int j = 1;j<=i-1;j++)
        k = t[k].cur;
    return k;
}

void ReadList(SLinkList t)
{
    int x = 0;
    int j = t[MAXSIZE-1].cur;
    while(t[j].cur!=0)
    {
        printf("%d\t",t[j].data);
        j = t[j].cur;
        x++;
        if(x%10==0)
            printf("\n");
    }
}
/*
void difference(SLinkList t1,SLinkList t2)
{
    int j2 = t2[MAXSIZE-1].cur;
    int j22=1;
    int j1 = t1[MAXSIZE-1].cur;
    int j11=1;
    while(t2[j2].cur!=0)
    {
        while(t1[j1].cur!=0)
        {
            if(t1[j1].data==t2[j2].data)
            {
                ListDelete(t1,j11);
            }
            else 
            {
                ListInsert(t1,)
            }
            j1 = t1[j1].cur;j11++;
        }
        j1 = t1[MAXSIZE-1].cur;
        j11=1;
        j2 = t2[j].cur;j22++;
    }
}
*/