#include <stdio.h>
#include <stdlib.h>

typedef struct DuNode 
{
    int data;
    struct DuNode* prior;
    struct DuNode* next;    
}DuNode ,*DuLinkList;

void CreateList(DuLinkList* l,int n);
void ReadList(DuLinkList l);
void ListInsert(DuLinkList* l,int n,int i);
void ListDelete(DuLinkList* l,int n);

int main(void)
{
    DuLinkList l1;
    CreateList(&l1,10);
    ListInsert(&l1,2,3);
    ListDelete(&l1,3);
    ReadList(l1);

}

void CreateList(DuLinkList* l,int n)
{
    (*l) = (DuLinkList)malloc(sizeof(DuNode));
    DuLinkList p1,p2;
    p1 = *l;
    for(int i=0;i<n;i++)
    {
        p2=(DuLinkList)malloc(sizeof(DuNode));
        p2->data = i;
        p1->next = p2;
        (*l)->prior = p2;
        p2->prior = p1;
        p1=p2;
    }
    p2->next = (*l)->next;
}

void ReadList(DuLinkList l)
{
    DuLinkList p = l->next;
    while(p!=l)
    {
        printf("%d",p->data);
        p = p->next;
    }
}

void ListInsert(DuLinkList* l,int n,int i)
{
    DuLinkList p1 = *l,p2,p3;
    for(int q = 0;q<n-1;q++)
    {
        p1 = p1->next;
    }
    p2 = (DuLinkList)malloc(sizeof(DuNode));
    p2->data = i;
    p3 = p1->next;
    p1->next = p2;
    p2->prior = p1;
    p2->next = p3;
    p3 ->prior =p2;
}

void ListDelete(DuLinkList* l,int n)
{
    DuLinkList p1 = *l,p2,p3;
    for(int q = 0;q<n-1;q++)
    {
        p1 = p1->next;
    }
    p2 = p1->next;
    p3 = p2->next;
    p1->next = p3;
    p3->prior = p1;
    free(p2);
}