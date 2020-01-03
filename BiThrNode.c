#include <stdio.h>
#include <stdlib.h>

typedef struct BiThrNode
{
	int data;
	struct BiThrNode *lchild,*rchild;
	int LTag, RTag;
}BiThrNode,*BiTree;

BiTree pre;

void InitTree(BiTree t, int x, int r);
void InOrderTreading(BiTree *Thrt,BiTree p);
void InOrder(BiTree t);
void visit(BiTree t);
void InThreading(BiTree p);

int main(void)
{
	BiTree t,P;
	t = (BiTree)malloc(sizeof(BiThrNode));
	InitTree(t,4,1);
	//printf("%d", t->lchild->data);
	InOrderTreading(&P, t);
	InOrder(P);
}

void InitTree(BiTree t, int x, int r)
{
	t->data = r;
	t->lchild = NULL;
	t->rchild = NULL;
	t->LTag = 1;
	t->RTag = 1;
	if (x == 1)
		return;
	t->lchild = (BiThrNode*)malloc(sizeof(BiThrNode));
	t->rchild = (BiThrNode*)malloc(sizeof(BiThrNode));
	t->LTag = 0;
	t->RTag = 0;
	InitTree(t->lchild, x - 1, 2 * r);
	InitTree(t->rchild, x - 1, 2 * r + 1);
}

void InOrderTreading(BiTree* Thrt, BiTree p)
{
	(*Thrt) = (BiTree)malloc(sizeof(BiThrNode));
	(*Thrt)->LTag = 0;
	(*Thrt)->RTag = 1;
	(*Thrt)->rchild = *Thrt;
	(*Thrt)->lchild = p;
	pre = *Thrt;
	InThreading(p);
	pre->rchild = *Thrt;
	pre->RTag = 1;
	(*Thrt)->rchild = pre;
}

void InThreading(BiTree p)
{
	if (p != NULL)
	{
		InThreading(p->lchild);
		if (p->lchild == NULL)
		{
			p->LTag = 1;
			p->lchild = pre;
		}
		if (pre->rchild == NULL)
		{
			pre->RTag = 1;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}

void InOrder(BiTree t)
{
	BiTree p = t->lchild;
	while (p != t)
	{
		while (p->LTag == 0)
			p = p->lchild;
		visit(p);
		while (p->RTag == 1 && p->rchild != t)
		{
			p = p->rchild;
			visit(p);
		}
		p = p->rchild;
	}
}

void visit(BiTree t)
{
	printf("%d ", t->data);
}