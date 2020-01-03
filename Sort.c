#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void InsertSort(int n, int x[n + 1]);                //直接插入
void randint(int n, int max, int t, int r[][n + 1]); //随机
void ShellInsert(int n, int x[n + 1], int dk);
void ShellSort(int n, int x[n + 1], int t, int dlta[t]); //希尔
int Partition(int x[], int low, int high);
void QSort(int x[], int low, int high);
void QuickSort(int n, int x[n + 1]);  //快速
void BubbleSort(int n, int x[n + 1]); //冒泡
void HeapSort(int n, int x[n + 1]);   //堆排
void HeapAdjust(int x[], int s, int e);
void SelectSort(int n, int x[n + 1]); //选择

int c = 0;
int m = 0;

int test(int mod)
{
    int num = 100;
    int x[6][num + 1];
    int dlta[4] = {41, 19, 5, 1};
    if (mod == 0)
    {
        randint(num, 1000, 6, x);
        printf("random:\n");
        for (int i = 1; i <= num; i++)
        {
            printf("%4d ", x[0][i]);
            if (i % 10 == 0)
                printf("\n");
        }
    }
    if (mod == 1)
    {
        printf("correct order:\n");
        for (int i = 1; i <= num; i++)
        {
            for (int p = 0; p <= 5; p++)
                x[p][i] = i;
            printf("%4d ", x[0][i]);
            if (i % 10 == 0)
                printf("\n");
        }
    }

    if (mod == 2)
    {
        printf("reverse order:\n");
        for (int i = 1; i <= num; i++)
        {
            for (int p = 0; p <= 5; p++)
                x[p][i] = num - i;
            printf("%4d ", x[0][i]);
            if (i % 10 == 0)
                printf("\n");
        }
    }

    BubbleSort(num, x[0]);
    printf("BubbleSort:\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%4d ", x[0][i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("comparison:%5d move:%5d sum:%5d\n", c, m, c + m);

    c = 0;
    m = 0;
    InsertSort(num, x[1]);
    printf("InsertSort:\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%4d ", x[1][i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("comparison:%5d move:%5d sum:%5d\n", c, m, c + m);

    c = 0;
    m = 0;
    SelectSort(num, x[2]);
    printf("SelectSort:\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%4d ", x[2][i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("comparison:%5d move:%5d sum:%5d\n", c, m, c + m);

    c = 0;
    m = 0;
    QuickSort(num, x[3]);
    printf("QuickSort:\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%4d ", x[3][i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("comparison:%5d move:%5d sum:%5d\n", c, m, c + m);

    c = 0;
    m = 0;
    ShellSort(num, x[4], 4, dlta);
    printf("ShellSort:\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%4d ", x[4][i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("comparison:%5d move:%5d sum:%5d\n", c, m, c + m);

    c = 0;
    m = 0;
    HeapSort(num, x[5]);
    printf("HeapSort:\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%4d ", x[5][i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("comparison:%5d move:%5d sum:%5d\n", c, m, c + m);
}

int main(void)
{
    test(0);
    test(1);
    test(2);
}

void randint(int n, int max, int t, int r[t][n + 1])
{
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; i++)
    {
        if (max == 0)
        {
            int w = rand();
            for (int e = 0; e < t; e++)
                r[e][i] = w;
        }
        else
        {
            int w = rand() % max;
            for (int e = 0; e < t; e++)
                r[e][i] = w;
        }
    }
}

void InsertSort(int n, int x[n + 1])
{
    for (int i = 2; i <= n; i++)
    {
        c++;
        if (x[i] < x[i - 1])
        {
            x[0] = x[i];
            x[i] = x[i - 1];
            m += 2;
            int j;
            for (j = i - 2; x[0] < x[j]; j--, m++)
                x[j + 1] = x[j];
            x[j + 1] = x[0];
            m++;
        }
    }
}

void ShellInsert(int n, int x[n + 1], int dk)
{
    for (int i = dk + 1; i <= n; i++)
    {
        if (c++ && x[i] < x[i - dk])
        {
            x[0] = x[i];
            m++;
            int j;
            for (j = i - dk; j > 0 && c++ && x[0] < x[j]; m++, j -= dk)
                x[j + dk] = x[j];
            x[j + dk] = x[0];
            m++;
        }
    }
}
void ShellSort(int n, int x[n + 1], int t, int dlta[t])
{
    for (int k = 0; k < t; k++)
    {
        ShellInsert(n, x, dlta[k]);
    }
}
int Partition(int x[], int low, int high)
{
    int p = x[low];
    m++;
    while (low < high)
    {
        while (low < high && c++ && x[high] >= p)
            high--;
        x[low] = x[high];
        m++;
        while (low < high && c++ && x[low] <= p)
            low++;
        x[high] = x[low];
        m++;
    }
    x[low] = p;
    m++;
    return low;
}
void QSort(int x[], int low, int high)
{
    if (low < high)
    {
        int p = Partition(x, low, high);
        QSort(x, low, p - 1);
        QSort(x, p + 1, high);
    }
}
void QuickSort(int n, int x[n + 1])
{
    QSort(x, 1, n);
}
void BubbleSort(int n, int x[n + 1])
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            c++;
            if (x[j] > x[j + 1])
            {
                int tempt = x[j];
                x[j] = x[j + 1];
                x[j + 1] = tempt;
                m += 3;
            }
        }
    }
}

void SelectSort(int n, int x[n + 1])
{
    for (int i = 1; i <= n; i++)
    {
        int key = i;
        m++;
        for (int j = i + 1; j <= n; j++)
            if (c++ && x[j] < x[key] && m++)
                key = j;
        int tempt = x[i];
        x[i] = x[key];
        x[key] = tempt;
        m += 3;
    }
}
void HeapSort(int n, int x[n + 1])
{
    int i;
    for (i = n / 2; i > 0; i--)
        HeapAdjust(x, i, n);
    for (i = n; i > 1; i--)
    {
        int tempt = x[1];
        x[1] = x[i];
        x[i] = tempt;
        m += 3;
        HeapAdjust(x, 1, i - 1);
    }
}
void HeapAdjust(int x[], int s, int e)
{
    int tempt, j;
    tempt = x[s];
    m++;
    for (j = 2 * s; j <= e; j *= 2) //访问子树
    {
        if (j < e && c++ && x[j] < x[j + 1])
            j++;
        if (c++ && tempt >= x[j])
            break;
        x[s] = x[j];
        s = j;
        m += 2;
    }
    x[s] = tempt;
    m++;
}