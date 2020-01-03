#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 1000

void randint(int n, int max, int r[n + 1]);
void MSort(int x[], int y[], int s, int t);
void Merge(int x[],int y[],int i,int m,int n);
void MergeSort(int n,int x[n+1]);

int main(void)
{
    int x[101];
    randint(100, 1000, x);
    QuickSort(100, x);
    for (int i = 1; i <= 100; i++)
    {
        printf("%4d ", x[i]);
        if (i % 10 == 0)
            printf("\n");
    }
}
void randint(int n, int max, int r[n + 1])
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
void MSort(int x[], int y[], int s, int t)
{
    int z[MAXSIZE];
    if (s == t)
        y[s] = x[s];
    else 
    {
        int m = (s+t)/2;
        MSort(x,z,s,m);
        MSort(x,z,m+1,t);
        Merge(z,y,s,m,t);
    }
}
void Merge(int x[],int y[],int i,int m,int n)
{
    int j,k,l;
    for(j = m+1,k=i;i<=m&&j<=n;k++)
    {
        if(x[i]<x[j])
            y[k] = x[i++];
        else 
            y[k] = x[j++];
    }
    if(i<=m)
    {
        for(l = 0;l<=m-i;l++)
            y[k+l] = x[i+l];
    }
    if(j<=n)
    {
        for(l = 0;l<=n-j;l++)
            y[k+l] = x[j+l];
    }
}
void MergeSort(int n,int x[n+1])
{
    MSort();
}