#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
/*
	利用队列实现层次遍历
*/
typedef struct
{
	int front;
	int rear;
	BiTNode data[100];
} SqQueue;

void visit(BiTNode n);
void PreOrder(BiTree t);
void InOrder(BiTree t);
void PostOrder(BiTree t);
void InitTree(BiTree *t, int x, int r); //满二叉树 r为1 r用来赋值data
void ptp(int x, int pre[x], int in[x], BiTNode **f);
int Locate(int t, int x[]);
void prein_to_post(int x, int pre[x], int in[x], BiTNode *f); //实现前序 中序转为后序
void LevelOrder(BiTree t);									  //层次遍历

void InitQueue(SqQueue *q);
void EnQueue(SqQueue *q, BiTNode b);
int DeQueue(SqQueue *q, BiTNode *b);

int main(void)
{
	BiTree t;
	t = (BiTree)malloc(sizeof(BiTNode));
	t->data = 100;
	t->lchild = NULL;
	t->rchild = NULL;
	int x[] = {5, 2, 1, 4, 3, 6, 8, 7, 9, 10, 11};
	int y[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	prein_to_post(11, x, y, t);
	PreOrder(t->lchild);
	printf("\n");
	PostOrder(t->lchild);
	printf("\n");
	LevelOrder(t->lchild);

	printf("\n");

	BiTree b;
	b = (BiTNode *)malloc(sizeof(BiTNode));
	InitTree(&b, 3, 1);
	PreOrder(b);
	printf("\n");
	LevelOrder(b);
}

void visit(BiTNode n)
{
	printf("%d ", n.data);
}

void PreOrder(BiTree t)
{
	visit(*t);
	if (t->lchild != NULL)
		PreOrder(t->lchild);
	if (t->rchild != NULL)
		PreOrder(t->rchild);
}

void InOrder(BiTree t)
{
	if (t->lchild != NULL)
		InOrder(t->lchild);
	visit(*t);
	if (t->rchild != NULL)
		InOrder(t->rchild);
}

void PostOrder(BiTree t)
{
	if (t->lchild != NULL)
		PostOrder(t->lchild);
	if (t->rchild != NULL)
		PostOrder(t->rchild);
	visit(*t);
}

void InitTree(BiTree *t, int x, int r)
{
	(*t)->data = r;
	(*t)->lchild = NULL;
	(*t)->rchild = NULL;
	if (x == 1)
		return;
	(*t)->lchild = (BiTree)malloc(sizeof(BiTNode));
	(*t)->rchild = (BiTree)malloc(sizeof(BiTNode));
	InitTree(&((*t)->lchild), x - 1, 2 * r);
	InitTree(&((*t)->rchild), x - 1, 2 * r + 1);
}

void prein_to_post(int x, int pre[x], int in[x], BiTNode *f)
{
	f->lchild = (BiTNode *)malloc(sizeof(BiTNode));
	f->lchild->data = pre[0];
	f->lchild->lchild = NULL;
	f->lchild->rchild = NULL;
	int l = Locate(pre[0], in);
	if (l != 0)
	{
		int t[l];
		for (int i = 0; i < l; i++)
			t[i] = in[i];
		int z[l];
		for (int i = 0; i < l; i++)
			z[i] = pre[i + 1];
		ptp(l, z, t, &(f->lchild->lchild));
	}
	if (l != x - 1)
	{
		int t[x - l - 1];
		for (int i = 0; i < x - l - 1; i++)
			t[i] = in[i + l + 1];
		int z[x - l - 1];
		for (int i = 0; i < x - l - 1; i++)
			z[i] = pre[i + l + 1];
		ptp(x - l - 1, z, t, &(f->lchild->rchild));
	}
}

void ptp(int x, int pre[x], int in[x], BiTNode **f)
{
	int t = pre[0];
	*f = (BiTNode *)malloc(sizeof(BiTNode));
	(*f)->data = t;
	(*f)->lchild = NULL;
	(*f)->rchild = NULL;
	int l = Locate(pre[0], in);
	if (l != 0)
	{
		int t[l];
		for (int i = 0; i < l; i++)
			t[i] = in[i];
		int z[l];
		for (int t = 0; t < l; t++)
			z[t] = pre[t + 1];
		ptp(l, z, t, &((*f)->lchild));
	}
	if (l != x - 1)
	{
		int t[x - l - 1];
		for (int i = 0; i < x - l - 1; i++)
			t[i] = in[i + l + 1];
		int z[x - l - 1];
		for (int i = 0; i < x - l - 1; i++)
			z[i] = pre[i + l + 1];
		ptp(x - l - 1, z, t, &((*f)->rchild));
	}
}

int Locate(int t, int x[])
{
	int i = 0;
	while (x[i] != t)
		i++;
	return i;
}

void LevelOrder(BiTree t)
{
	SqQueue s;
	InitQueue(&s);
	EnQueue(&s, *t);
	BiTNode q;
	while (DeQueue(&s, &q))
	{
		visit(q);
		if (q.lchild != NULL)
			EnQueue(&s, *(q.lchild));
		if (q.rchild != NULL)
			EnQueue(&s, *(q.rchild));
		;
	}
}

void InitQueue(SqQueue *q)
{
	q->front = 0;
	q->rear = 1;
}

void EnQueue(SqQueue *q, BiTNode b)
{
	if (q->rear == q->front)
		printf("ERROR");
	else

	{
		q->data[q->rear++] = b;
		q->rear = q->rear % 100;
	}
}

int DeQueue(SqQueue *q, BiTNode *b)
{
	q->front = q->front % 100;
	if (q->front + 1 == q->rear)
		return 0;
	*b = q->data[++q->front];
	return 1;
}