#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *elem;
    int length;//length为真实长度
    int listsize;
} SqList;
/*
    i为数据 n为位置
*/
void InitList(SqList* l,int length);
void DestroyList(SqList* l);
void ClearList(SqList* l);
int ListEmpty(SqList* l);
int ListLength(SqList* l);
int GetElem(SqList* l,int i);
int LocateElem(SqList* l,int i);
int PriorElem(SqList*l,int i,int n);
int NextElem(SqList*l,int i,int n);
int ListInsert(SqList*l,int i,int n);
int ListDelete(SqList*l,int n);
void ListTraverse(SqList*l,int (*x)(int t));//对l所有元素调用x函数
void ListUnion(SqList*l1,SqList l2);//合并l1 l2
void MergeList(SqList l1,SqList l2,SqList* l3);//按升序合并l1 l2至l3

int main(void)
{
    SqList l1;
    InitList(&l1,10);
    *l1.elem=10;
    printf("%d",l1.elem[0]);
}

void InitList(SqList* l,int length)
{
    l->elem = (int*)malloc(length*sizeof(int));
    l->listsize = length;
}

void DestroyList(SqList* l)
{
    free(l->elem);
    l->elem = NULL;
    l->length=0;
    l->listsize=0;
}

void ClearList(SqList* l)
{
    for(int i = 0;i<l->length;i++)
    {
        l->elem[i]=0;
    }
}

int ListEmpty(SqList* l)
{
    if(l->elem==NULL) return 0;
    else return 1;
}

int ListLength(SqList* l)
{
    return l->length;
}

int GetElem(SqList* l,int i)
{
    return l->elem[i];
}

int LocateElem(SqList* l,int i)
{
    for(int n=0;n<l->length;n++)
    {
        if(l->elem[n]==i)
            return n;
    }
    return 0;
}

int PriorElem(SqList*l,int i,int n)
{
    int t=LocateElem(l,i);
    return GetElem(l,t-1);
}

int NextElem(SqList*l,int i,int n)
{
    int t=LocateElem(l,i);
    return GetElem(l,t+1);
}

int ListInsert(SqList*l,int i,int n)
{
    if(l->listsize-l->length<1) return 0;
    for(int q=l->length-1;q>=n;q--)
    {
        l->elem[q+1] = l->elem[q];
    }
    l->elem[n] = i;
    l->length++;
    return 1;
}

int ListDelete(SqList*l,int n)
{
    for(int i=n;i<l->length;i++)
    {
        l->elem[i]=l->elem[i+1];
    }
    l->length--;
}

void ListTraverse(SqList*l,int (*x)(int t))
{
    for(int i=0;i<l->length;i++){
        (*x)(l->elem[i]);
    }
}

void ListUnion(SqList*l1,SqList l2)
{
    for(int i=0;i<l2.length;i++)
    {
        if(LocateElem(l1,l2.elem[i]))
        {
            ListInsert(l1,l2.elem[i],l1->length);
        }
    }
}

void MergeList(SqList l1,SqList l2,SqList* l3)
{
    int t = 0,i=0,j=0;
    while(i<l1.length&&j<l2.length)
    {
        if(l1.elem[i]<=l2.elem[j])
        {
            l3->elem[t]=l1.elem[i];
            t++;
            i++;
            l3->length++;
        }
        else 
        {
            l3->elem[t]=l2.elem[j];
            t++;
            j++;
            l3->length++;
        }
    }
    while(i<l1.length)
    {
        l3->elem[t]=l1.elem[i];
        t++;
        i++;
        l3->length++;
    }
    while(j<l2.length)
    {
        l3->elem[t]=l2.elem[j];
        t++;
        j++;
        l3->length++;
    }
}