#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct Node
{
    int data;
    int bf;
    struct Node *lchild,*rchild;
} Node,Tree;

BiTree search(BiTree t, int key);
void insert(BiTree *t, int key);
int s(BiTree t, int key, BiTree **p);
void InOrder(BiTree t);
void visit(BiTNode n);
int delete (BiTree *t, int key);
int s2(BiTree t, int key, BiTree *t1, BiTree *t2);

int main(void)
{
    BiTree t = NULL, t2, t3;
    insert(&t, 30);
    insert(&t, 20);
    insert(&t, 40);
    insert(&t, 10);
    insert(&t, 25);
    insert(&t, 23);
    insert(&t, 35);
    printf("%d\n", s2(t, 0, &t2, &t3));
    //printf("%d\n",t3->data);
    delete(&t,35);
    delete(&t,30);
    InOrder(t);
}

BiTree search(BiTree t, int key)
{
    if (t == NULL || t->data == key)
        return t;
    if (t->data > key)
        return search(t->lchild, key);
    return search(t->rchild, key);
}

void insert(BiTree *t, int key)
{
    if (*t == NULL)
    {
        *t = (BiTree)malloc(sizeof(BiTNode));
        (*t)->data = key;
        (*t)->lchild = NULL;
        (*t)->rchild = NULL;
        return;
    }
    BiTree **p;
    p = (BiTree **)malloc(sizeof(BiTNode **));
    if (s(*t, key, p))
    {
        (**p) = (BiTree)malloc(sizeof(BiTNode));
        (**p)->data = key;
        (**p)->lchild = NULL;
        (**p)->rchild = NULL;
    }
}
int s(BiTree t, int key, BiTree **p)
{
    if (t == NULL)
        return 1;
    else if (t->data == key)
        return 0;
    else if (t->data < key)
    {
        *p = &(t->rchild);
        return s(t->rchild, key, p);
    }
    else if (t->data > key)
    {
        *p = &(t->lchild);
        return s(t->lchild, key, p);
    };
}

void InOrder(BiTree t)
{
    if (t->lchild != NULL)
        InOrder(t->lchild);
    visit(*t);
    if (t->rchild != NULL)
        InOrder(t->rchild);
}
void visit(BiTNode n)
{
    printf("%d ", n.data);
}

int delete (BiTree *t, int key)
{
    BiTree *t1,*t2;
    t1 = (BiTree*)malloc(sizeof(BiTNode*));
    t2 = (BiTree*)malloc(sizeof(BiTNode*));
    int flag = s2(*t,key,t1,t2); 
    if(flag == 0)
        return 0;
    /*    
    else if(flag == 3)
    {
        return 0 ; 
    }*/
    else if((*t2)->lchild == NULL&&(*t2)->rchild ==NULL)
    {
        if(flag == 1)
        {
            (*t1) ->lchild = NULL;
            return 1;
        }
        else if(flag ==2)
        {
            (*t1) ->rchild = NULL;
            return 1;
        }
    }
    else if((*t2)->lchild !=NULL&&(*t2)->rchild ==NULL)
    {
        if(flag == 1)
        {
            (*t1)->lchild = (*t2) ->lchild;
            return 1;
        }
        else if(flag ==2)
        {
            (*t1)->rchild = (*t2) ->lchild;
            return 1;
        }
    }
    else if((*t2)->lchild ==NULL&&(*t2)->rchild !=NULL)
    {
        if(flag == 1)
        {
            (*t1)->lchild = (*t2) ->rchild;
            return 1;
        }
        else if(flag ==2)
        {
            (*t1)->rchild = (*t2) ->rchild;
            return 1;
        }
    }
    else if((*t2)->lchild!=NULL&&(*t2)->rchild!=NULL)
    {
        BiTree p = (*t2)->lchild,q=(*t2);
        while(p->rchild!=NULL)
        {
            q = p;
            p = p->rchild;
        }
        (*t2)->data = p->data;
        if(q!=(*t2))
            q->rchild = p->lchild;
        else
            q->lchild = p->lchild;
    }
}
int s2(BiTree t, int key, BiTree *t1, BiTree *t2)
{
    if (t == NULL)
        return 0;
    else if (t->data == key)
    {
        (*t1) = t;
        (*t2) = t;
        return 3;
    }
    else if (t->data > key)
    {
        if (t->lchild == NULL)
            return 0;
        if (t->lchild->data == key)
        {
            *t2 = t->lchild;
            *t1 = t;
            return 1;
        }
        s2(t->lchild, key, t1, t2);
    }
    else
    {
        if (t->rchild == NULL)
            return 0;
        if (t->rchild->data == key)
        {
            *t2 = t->rchild;
            *t1 = t;
            return 2;
        }
        s2(t->rchild, key, t1, t2);
    }
}