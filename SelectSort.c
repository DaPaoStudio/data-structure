#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randint(int n, int max, int r[n+1]);
void SelectSort(int n,int x[n+1]);
void HeapSort(int n,int x[n+1]);
void HeapAdjust(int x[],int s,int m);

int main(void)
{
    int x[101];
    randint(100,1000,x);
    HeapSort(100,x);
    for (int i = 1; i <= 100; i++)
    {
        printf("%4d ", x[i]);
        if (i % 10 == 0)
            printf("\n");
    }
}

void randint(int n, int max, int r[n+1])
{
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; i++)
    {
        if (max == 0)
            r[i] = rand();
        else
            r[i] = rand() % max;
    }
}

void SelectSort(int n,int x[n+1])
{
    for(int i = 1;i<=n;i++)
    {
        int key = i;
        for(int j = i+1;j<=n;j++)
            if(x[j]<x[key])
                key = j;
        int tempt = x[i];
        x[i] = x[key];
        x[key] = tempt;
    }
}
void HeapSort(int n,int x[n+1])
{
    int i;
    for(i=n/2;i>0;i--)
        HeapAdjust(x,i,n);
    for(i=n;i>1;i--)
    {
        int tempt = x[1];
        x[1] = x[i];
        x[i] = tempt;
        HeapAdjust(x,1,i-1);
    }
}
void HeapAdjust(int x[],int s,int m)
{
    int tempt,j;
    tempt = x[s];
    for(j=2*s;j<=m;j*=2)//访问子树
    {
        if(j<m&&x[j]<x[j+1])
            j++;
        if(tempt>=x[j])
            break;
        x[s] = x[j];
        s = j;
    }
    x[s] = tempt;
}