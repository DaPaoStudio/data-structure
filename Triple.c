#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
/*
	需按照顺序放入数组中
*/
typedef struct
{
	int i;
	int j;
	int e;
}Triple;
typedef struct
{
	Triple data[MAXSIZE];
	int mu;
	int nu;
	int tu;//行数 列数 非零元个数
}Matrix;

void TMatrix(Matrix p1, Matrix* p2);

int main(void)
{
	Matrix m, m2;
	m.mu = 3; m.nu = 2; m.tu = 4;
	Triple t1, t2, t3, t4;
	t1.e = 5; t2.e = 4; t3.e = 3; t4.e = 2;
	t1.i = 0; t1.j = 0;
	t2.i = 2; t2.j = 1;
	t3.i = 1; t3.j = 2;
	t4.i = 3; t4.j = 2;
	m.data[0] = t1;
	m.data[1] = t3;
	m.data[2] = t2;
	m.data[3] = t4;

	TMatrix(m, &m2);
	printf("%d", m2.data[2].e);
}

void TMatrix(Matrix p1, Matrix* p2)
{
	p2->nu = p1.mu;
	p2->mu = p1.nu;
	p2->tu = p1.tu;

	int a[10] = { 0 };
	int b[10] = { 0 };
	for (int i = 0; i < p1.tu; i++)
	{
		a[p1.data[i].j]++;
	}
	b[0] = 0;
	for (int i = 1; i < p1.tu; i++)
	{
		b[i] += b[i - 1] + a[i - 1];
	}
	for (int p = 0; p < p1.tu; p++)
	{
		int q = b[p1.data[p].j]++;
		p2->data[q] = p1.data[p];
	}
}