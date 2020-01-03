#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

/*
    双亲表示法
*/
typedef struct PTNode
{
    int data;
    int parent;
} PTNode;

typedef struct 
{
    PTNode nodes[MAXSIZE];
    int r,n;//根位置和结点数
} PTree;

/*
    孩子表示法
*/
typedef struct CTNode 
{
    int child;
    struct  CTNode *next;
} *ChildPtr; //孩子结点

typedef struct 
{
    int data;
    ChildPtr firstchild;
} CTBox;

typedef struct 
{
    CTBox nodes[MAXSIZE];
    int r,n;
} CTree;

/*
    孩子兄弟表示法
*/
typedef struct CSNode
{
    int data;
    struct CSNode *firstchild,*nextschild;
} CSNode ,*CSTree;

int find_mfset(PTree s,int i);
void merge_mfset(PTree* s,int i,int j);
void mix_mfset(PTree* s,int i,int j);
int fix_mfset(PTree* s,int i);

int main(void)
{

}

int find_mfset(PTree s,int i)
{
    if(i<1||i>s.n)
        return -1;
    int j;
    for(j=i;s.nodes[j].parent>0;j=s.nodes[j].parent); 
        return j;
}

void merge_mfset(PTree* s,int i,int j)
{
    s->nodes[i].parent = j;
}

void mix_mfset(PTree* s,int i,int j)
{
    if(s->nodes[i].parent>s->nodes[j].parent)
    {
        s->nodes[j].parent+=s->nodes[i].parent;
        s->nodes[i].parent = j;
    }
    else 
    {
        s->nodes[i].parent += s->nodes[i].parent;
        s->nodes[j].parent = i;
    }
}

int fix_mfset(PTree* s,int i)
{
    int j,t;
    for(j = i;s->nodes[j].parent>0;j=s->nodes[j].parent);
    for(int k = i;k!=j;k=t)
    {
        t=s->nodes[k].parent;
        s->nodes[k].parent=j; 
    }
}