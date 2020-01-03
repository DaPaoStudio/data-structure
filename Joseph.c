#include <stdio.h>
#include <stdlib.h>

typedef struct DuNode
{
    int data;
    int location;
    struct DuNode *next;
} DuNode, *DuLinkList;

void CreateList(DuLinkList *l, int n);
void ListDelete(DuLinkList *l, int *m);

int main(void)
{
    int n, m;
    DuLinkList l;
    printf("How many people:");
    scanf("%d", &n);
    CreateList(&l, n);
    printf("m:");
    scanf("%d", &m);
    while (n > 0)
    {
        m %= n;
        if (m == 0)
            m = n;
        ListDelete(&l, &m);
        n--;
    }
}
void CreateList(DuLinkList *l, int n)
{
    int d;
    (*l) = (DuLinkList)malloc(sizeof(DuNode));
    DuLinkList p1, p2;
    p1 = *l;
    for (int i = 0; i < n; i++)
    {
        p2 = (DuLinkList)malloc(sizeof(DuNode));
        printf("%d:", i + 1);
        scanf("%d", &d);
        p2->location = i + 1;
        p2->data = d;
        p1->next = p2;
        p1 = p2;
    }
    p2->next = (*l)->next;
}
void ListDelete(DuLinkList *l, int *m)
{
    DuLinkList p1 = *l, p2, p3;
    int q = 1;
    while (q < (*m))
    {
        p1 = p1->next;
        q++;
    }
    p2 = p1->next;
    printf("%d ", p2->location);
    p3 = p2->next;
    p1->next = p3;
    *m = p2->data;
    (*l)->next = p3;
    free(p2);
}