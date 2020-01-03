#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int bf;
    struct Node *lchild, *rchild;
} Node, *Tree;

void RRotate(Tree *p);
void LRotate(Tree *p);
int InsertAVL(Tree *t, int e, int *taller);
void LeftBalance(Tree *t);
void RightBalance(Tree *t);
void visit(Node n);
void InOrder(Tree t);

int main(void)
{
    Tree t;
    t = NULL;
    int taller;
    for(int i = 1;i<100;i++)
        InsertAVL(&t,i,&taller);
    InOrder(t);
}
void RRotate(Tree *p)
{
    Tree lc = (*p)->lchild;
    (*p)->lchild = lc->rchild;
    lc->rchild = *p;
    *p = lc;
}
void LRotate(Tree *p)
{
    Tree rc = (*p)->rchild;
    (*p)->rchild = rc->lchild;
    rc->lchild = *p;
    *p = rc;
}
int InsertAVL(Tree *t, int e, int *taller)
{
    if (*t == NULL)
    {
        *t = (Tree)malloc(sizeof(Node));
        (*t)->data = e;
        (*t)->lchild = (*t)->lchild = NULL;
        (*t)->bf = 0;
        *taller = 1;
    }
    else
    {
        if (e == (*t)->data)
        {
            *taller = 0;
            return 0;
        }
        if (e > (*t)->data)
        {
            if (!InsertAVL(&((*t)->lchild), e, taller))
                return 0;
            if (*taller)
            {
                switch ((*t)->bf)
                {
                case 1:
                    LeftBalance(t);
                    *taller = 0;
                    break;
                case 0:
                    (*t)->bf = 1;
                    *taller = 1;
                    break;
                case -1:
                    (*t)->bf = 0;
                    *taller = 0;
                    break;
                }
            }
        }
        else
        {
            if (!InsertAVL(&((*t)->rchild), e, taller))
                return 0;
            if (*taller)
                switch ((*t)->bf)
                {
                case 1:
                    (*t)->bf = 0;
                    *taller = 0;
                    break;
                case 0:
                    (*t)->bf = -1;
                    *taller = 1;
                    break;
                case -1:
                    RightBalance(t);
                    *taller = 0;
                    break;
                }
        }
    }
    return 1;
}
void LeftBalance(Tree *t)
{
    Tree lc = (*t)->lchild;
    Tree rd = lc->rchild;
    switch (lc->bf)
    {
    case 1:
        (*t)->bf = lc->bf = 0;
        RRotate(t);
        break;
    case -1:
        switch (rd->bf)
        {
        case 1:
            (*t)->bf = 1;
            lc->bf = 0;
            break;
        case 0:
            (*t)->bf = lc->bf = 0;
            break;
        case -1:
            (*t)->bf = 0;
            lc->bf = 1;
            break;
        }
        rd->bf = 0;
        LRotate(&((*t)->lchild));
        RRotate(t);
    }
}
void RightBalance(Tree *t)
{
    Tree lc = (*t)->rchild;
    Tree rd = lc->lchild;
    switch (lc->bf)
    {
    case -1:
        (*t)->bf = lc->bf = 0;
        LRotate(t);
        break;
    case 1:
        switch (rd->bf)
        {
        case -1:
            (*t)->bf = 1;
            lc->bf = 0;
            break;
        case 0:
            (*t)->bf = lc->bf = 0;
            break;
        case 1:
            (*t)->bf = 0;
            lc->bf = -1;
            break;
        }
        rd->bf = 0;
        RRotate(&((*t)->rchild));
        LRotate(t);
    }
}

void InOrder(Tree t)
{
    if (t->lchild != NULL)
        InOrder(t->lchild);
    visit(*t);
    if (t->rchild != NULL)
        InOrder(t->rchild);
}
void visit(Node n)
{
    printf("%d ", n.data);
}