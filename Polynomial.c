#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    double coef;
    int expn; //指数得是整数
    struct Node *next;
} Node, *List;

void Create(List *l);
void Print(List l);
int cmp(Node a, Node b); //> 1;= 0;< -1;
void OrderInsert(List *l, double coef, int expn);
void AddPolyn(List l1, List l2, List l3);
void SubstractPolyn(List l1, List l2, List l3);

int main(void)
{
    List l1, l2, l3,l4;
    Create(&l1);
    Create(&l2);
    Create(&l3);Create(&l4);
    //printf("2");
    for (int i = 0; i < 10; i++)
    {
        OrderInsert(&l1, 5.0, i);
    }
    Print(l1);
    for (int i = 0; i < 14; i += 2)
    {
        OrderInsert(&l2, -4.0, i);
    }
    for (int i = 0; i < 14; i += 2)
    {
        OrderInsert(&l4, +4.0, i);
    }
    Print(l2);
    SubstractPolyn(l1,l4,l3);
    //AddPolyn(l1, l2, l3);
    Print(l3);
}

void Create(List *l)
{
    *l = (List)malloc(sizeof(Node));
    (*l)->next = NULL;
}

void Print(List l)
{
    List p1 = l->next;
    while (p1 != NULL)
    {
        if (p1->expn == 0)
        {
            printf("%+g ", p1->coef);
        }
        else
            printf("%+gx^%d ", p1->coef, p1->expn);
        p1 = p1->next;
    }
    printf("\n");
}

int cmp(Node a, Node b)
{
    return a.expn > b.expn;
}

void OrderInsert(List *l, double coef, int expn)
{
    List p1 = *l, p2, p3;
    p2 = p1->next;
    while (p2 != NULL && p2->expn <= expn)
    {
        p1 = p2;
        p2 = p2->next;
    }
    if (expn == p1->expn)
        p1->coef += coef;
    else
    {
        p3 = (List)malloc(sizeof(Node));
        p3->coef = coef;
        p3->expn = expn;
        p1->next = p3;
        p3->next = p2;
    }
}

void AddPolyn(List l1, List l2, List l3)
{
    List p1 = l1->next, p2 = l2->next, p3 = l3;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->expn < p2->expn)
        {
            p3->next = p1;
            p1 = p1->next;
            p3 = p3->next;
        }
        else if (p1->expn > p2->expn)
        {
            p3->next = p2;
            p2 = p2->next;
            p3 = p3->next;
        }
        else
        {
            p3->next = p1;
            p3 = p3->next;
            p3->coef += p2->coef;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    if (p1 != NULL)
    {
        p3->next = p1;
    }
    else if (p2 != NULL)
    {
        p3->next = p2;
    }
}

void SubstractPolyn(List l1, List l2, List l3)
{
    List p1 = l1->next, p2 = l2->next, p3 = l3;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->expn < p2->expn)
        {
            p3->next = p1;
            p1 = p1->next;
            p3 = p3->next;
        }
        else if (p1->expn > p2->expn)
        {
            p3->next = p2;
            p2 = p2->next;
            p3 = p3->next;
            p3->coef = -p3->coef;
        }
        else
        {
            if ((p1->coef - p2->coef) != 0)
            {
                p3->next = p1;
                p3 = p3->next;
                p3->coef -= p2->coef;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    if (p1 != NULL)
    {
        p3->next = p1;
    }
    else if (p2 != NULL)
    {
       p3->next = p2;
       while(p2!=NULL)
       {
           p2->coef = -p2->coef;
           p2 = p2->next;
       } 
    }
}