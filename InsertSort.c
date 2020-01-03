#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void BInsertSort(int n, int x[n + 1]);
void InsertSort(int n, int x[n + 1]);
void randint(int n, int max, int r[n + 1]);
void ShellInsert(int n,int x[n+1],int dk);
void ShellSort(int n,int x[n+1],int t,int dlta[t]);

int main(void)
{
    int num = 100;
    int x[num] ;
    int dlta[5]={11,9,3,2,1};
    randint(num, 0, x);
    //InsertSort(num, x);
    //BInsertSort(num, x);
    ShellSort(100,x,5,dlta);
    for (int i = 1; i <= num; i++)
    {
        printf("%d ", x[i]);
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

void InsertSort(int n, int x[n + 1])
{
    int tempt;
    double begin = time(NULL);
    for (int i = 2; i <= n; i++)
    {
        x[0] = x[i];
        int j = i - 1;
        while (x[j] >= x[j + 1])
        {
            tempt = x[j + 1];
            x[j + 1] = x[j];
            x[j] = tempt;
            j--;
        }
    }
    double end = time(NULL);
    printf("time: %lf\n", end - begin);
}
void BInsertSort(int n, int x[n + 1])
{
    int tempt, low, high, m;
    double begin = time(NULL);
    for (int i = 2; i <= n; i++)
    {

        low = 1;
        high = i - 1;
        while (low <= high)
        {
            m = (low + high) / 2;
            if (x[i] < x[m])
                high = m - 1;
            else
                low = m + 1;
        }
        int j = i - 1;
        int key = x[i];
        while (j >= high + 1)
        {
            x[j + 1] = x[j];
            j--;
        }
        x[high + 1] = key;
    }
    double end = time(NULL);
    printf("time: %d\n", end - begin);
}

void ShellInsert(int n,int x[n+1],int dk)
{
    for(int i = dk+1;i<=n;i++)
    {
        if(x[i]<x[i-dk])
        {
            x[0] = x[i];
            int j;
            for(j = i-dk;j>0&&x[0]<x[j];j-=dk)
                x[j+dk] = x[j];
            x[j+dk] = x[0];
        }
    }
}
void ShellSort(int n,int x[n+1],int t,int dlta[t])
{
    for(int k = 0;k<t;k++)
    {
        ShellInsert(n,x,dlta[k]);
    }
}