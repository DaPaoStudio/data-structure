#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} Node;

typedef Node *LinkList;
/*
    n为位置 第n个
    i为内容
*/
void CreateList(LinkList *l, int n);
void ReadList(LinkList l);
void InitList(LinkList *l);
int GetElem(LinkList l, int n); //第n个
void ListInsert(LinkList *l, int n, int i);
void ListDelete(LinkList *l, int n);
void MergeList(LinkList *l1, LinkList *l2, LinkList *l3);
void DestoryList(LinkList *l1);
void Remove(LinkList *l1);
void Set(LinkList* l1,int n,int i);
int ListEmpty(LinkList l);
int ListLength(LinkList l);
void Add(LinkList *l,int i);

int main(void)
{
    LinkList l1, l2, l3;
    InitList(&l3);
    CreateList(&l1, 10);
    printf("\n%d\n",ListLength(l1));
    CreateList(&l2, 15);
    ReadList(l1);
    Add(&l1,21);
    ReadList(l1);
    //ListInsert(&l1,2,10);
    ListDelete(&l1, 5);
    ReadList(l1);
    MergeList(&l1, &l2, &l3);
    ReadList(l3);
    Remove(&l3);
    ReadList(l3);
    Set(&l3,2,22);
    ReadList(l3);
}

void InitList(LinkList *l)
{
    *l = (LinkList)malloc(sizeof(Node));
    (*l)->next = NULL;
}

void CreateList(LinkList *l, int n)
{
    *l = (LinkList)malloc(sizeof(Node));
    LinkList p, r;
    r = *l;
    for (int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = i;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

void ReadList(LinkList l)
{
    LinkList p;
    p = l->next;
    while (p != NULL)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}

int GetElem(LinkList l, int n)
{
    for (int i = 0; i < n; i++)
    {
        l = l->next;
    }
    printf("%d", l->data);
    return l->data;
}

void ListInsert(LinkList *l, int n, int i)
{
    int y = 0;
    LinkList p, r;
    p = *l;
    while (y < n - 1)
    {
        p = p->next;
        y++;
    }
    r = (LinkList)malloc(sizeof(Node));
    r->data = i;
    r->next = p->next;
    p->next = r;
}

void ListDelete(LinkList *l, int n)
{
    int y = 0;
    LinkList p, r;
    p = *l;
    while (y < n - 1)
    {
        p = p->next;
        y++;
    }
    r = p->next->next;
    free(p->next);
    p->next = r;
}

void MergeList(LinkList *l1, LinkList *l2, LinkList *l3)
{
    LinkList p = *l1;
    p = p->next;
    LinkList r = *l2;
    r = r->next;
    *l3 = (LinkList)malloc(sizeof(Node));
    LinkList q = *l3;
    while (p && r)
    {
        if (p->data < r->data)
        {
            q->next = p;
            q = p;
            p = p->next;
        }
        else
        {
            q->next = r;
            q = r;
            r = r->next;
        }
    }
    while (p)
    {
        q->next = p;
        q = p;
        p = p->next;
    }
    while (r)
    {
        q->next = r;
        q = r;
        r = r->next;
    }
    q->next = NULL;
}
void DestoryList(LinkList *l1)
{
    LinkList p1 = *l1, p2 = p1->next;
    while (p2 != NULL)
    {
        free(p1);
        p1 = p2;
        p2 = p2->next;
    }
    free(p2);
}

void Remove(LinkList *l1)
{
    LinkList p1 = *l1, p2 = p1->next;
    while (p2->next != NULL)
    {
        p1 = p2;
        p2 = p2->next;
    }
    p1->next = NULL;
    free(p2);
}

void Set(LinkList* l1,int n,int i)
{
    LinkList p1 = *l1;
    for(int q = 0;q<n;q++)
    {
        p1=p1->next;
    }
    p1->data = i;
}

int ListEmpty(LinkList l)
{
    if(l->next == NULL) return 0;
    else return 1;
}

int ListLength(LinkList l)
{
    int i=0;
    while(l->next!=NULL)
    {
        l = l->next;
        i++;
    }
    return i;
}

void Add(LinkList *l,int i)
{
    LinkList p1 =*l,p2;
    while(p1->next!=NULL)
    {
        p1 = p1->next;
    }
    p2 = (LinkList)malloc(sizeof(Node));
    p2->data = i;
    p1->next = p2;
    p2->next = NULL;
}