#include <iostream>
#include <cstring>
using namespace std;
typedef struct Node
{
    char ch;
    struct Node *l, *r;
} Node, *Tree;
void f(Tree *t);
void In(Tree t);
int Out(Tree t);
int main(void)
{
    int num;
    scanf("%d",&num);
    Tree t[num];
    for (int i = 0; i < num; i++)
    {
        f(&t[i]);
    }
    for (int i = 0; i < num; i++)
    {
        In(t[i]);
        printf("\n");
        int x = Out(t[i]);
        printf("\n");
        printf("%d\n",x);
    }
    
}

void f(Tree *t)
{
    char ch = getchar();
    while(ch=='\n')
        ch = getchar();
    if (ch != '#')
    {
        (*t) = (Tree)malloc(sizeof(Node));
        (*t)->ch = ch;
        (*t)->l = NULL;
        (*t)->r = NULL;
        f(&((*t)->l));
        f(&((*t)->r));
    }
}
void In(Tree t)
{
    if(t==NULL)
        return ;
    if(t->l!=NULL)
        In(t->l);
    printf("%c ",t->ch);
    if(t->r!=NULL)
        In(t->r);
}

int Out(Tree t)
{
    if(t==NULL)
        return 0;
    int num = 0;
    if(t->l!=NULL)
        num+=Out(t->l);
    if(t->r!=NULL)
        num+=Out(t->r);
    printf("%c ",t->ch);
    if(t->l==NULL&&t->r==NULL)
        num++;
    return num;
}