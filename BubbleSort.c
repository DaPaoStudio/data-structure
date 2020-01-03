#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int n,int x[n+1]);
void randint(int n, int max, int r[n+1]);
int Partition(int x[],int low,int high);
void QSort(int x[],int low,int high);
void QuickSort(int n,int x[n+1]);

int main(void)
{
    int x[101];
    randint(100,1000,x);
    QuickSort(100,x);
    for (int i = 1; i <= 100; i++)
    {
        printf("%4d ", x[i]);
        if (i % 10 == 0)
            printf("\n");
    }
}

void BubbleSort(int n,int x[n+1])
{
    for(int i = 1;i<n;i++)
    {
        for(int j = 1;j<=n-i;j++)
        {
            if(x[j]>x[j+1])
            {
                int tempt = x[j];
                x[j] = x[j+1];
                x[j+1] = tempt;
            }
        }
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
int Partition(int x[],int low,int high)
{
    x[0] = x[low];
    while(low<high)
    {
        while(low<high&&x[high]>=x[0])
            high--;
        x[low] = x[high];
        while(low<high&&x[low]<=x[0])
            low++;
        x[high] = x[low];
    }
    x[low] = x[0];
    return low;
}
void QSort(int x[],int low,int high)
{
    if(low<high)
    {
        int p = Partition(x,low,high);
        QSort(x,low,p-1);
        QSort(x,p+1,high);
    }
}
void QuickSort(int n,int x[n+1])
{
    QSort(x,1,n+1);
}