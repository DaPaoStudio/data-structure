#include <stdio.h>
#include <stdlib.h>
#define MAX 255
#define MAXSIZE 100
int x[6][6] =
    {{0, 6, 1, 5, MAX, MAX},
     {6, 0, 5, MAX, 3, MAX},
     {1, 5, 0, 5, 6, 4},
     {5, MAX, 5, 0, MAX, 2},
     {MAX, 3, 6, MAX, 0, 6},
     {MAX, MAX, 4, 2, 6, 0}};
int y[6][6] =
    {{0, 16, MAX, MAX, 21, 19},
     {16, 0, 5, 6, 11, MAX},
     {MAX, 5, 0, 6, MAX, MAX},
     {MAX, 6, 6, 0, 14, 18},
     {21, 11, MAX, 14, 0, 33},
     {19, MAX, MAX, 18, 33, 0}};

typedef struct side
{
    int from, to;
    int value;
} side, sides[MAXSIZE];

void Prim(int m, int x[m][m]);
void Kruskal(int m, int x[m][m]);
void sort(int m, sides s);

int main(void)
{
    Prim(6, y);
    Kruskal(6, y);
}
void Prim(int m, int x[m][m])
{
    int dot[m];
    int value[m];
    int u[m];
    for (int i = 0; i < m; i++)
    {
        dot[i] = -1;
        value[i] = MAX;
        u[i] = 0;
    }
    u[0] = 1;
    int i = 0, times = 0;
    while (times < 5)
    {
        for (int t = 0; t < m; t++)
            if (value[t] > x[i][t] && i != t && u[t] != 1)
            {
                dot[t] = i;
                value[t] = x[i][t];
            }
        int y = 0;
        for (int e = 0; e < m; e++)
        {
            if (value[e] < value[y] && u[e] != 1)
                y = e;
        }
        if (dot[y] > y)
            printf("%d->%d:value %d\n", y, dot[y], value[y]);
        else
            printf("%d->%d:value %d\n", dot[y], y, value[y]);
        u[y] = 1;
        i = y;
        times++;
    }
    printf("\n");
}

void Kruskal(int m, int x[m][m])
{
    sides s;
    int t = 0;
    for (int i = 0; i < m - 1; i++)
    {
        for (int n = i + 1; n < m; n++)
        {
            if (x[i][n] != 0 && x[i][n] != MAX)
            {
                s[t].from = i;
                s[t].to = n;
                s[t].value = x[i][n];
                t++;
            }
        }
    }
    sort(t, s);

    int e = 0, w[m];
    for (int i = 0; i < m; i++)
        w[i] = i;
    int o = 0, i = 0;
    while (o < m - 1)
    {
        if (w[s[i].from] != w[s[i].to])
        {
            printf("%d->%d:value %d\n", s[i].from, s[i].to, s[i].value);
            for (int q = 0; q < m; q++)
            {
                if (w[q] == w[s[i].to])
                    w[q] = w[s[i].from];
            }
            o++;
        }
        i++;
    }
    printf("\n");
}
void sort(int m, sides s)
{
    side temp;
    for (int i = 0; i < m - 1; i++)
    {
        for (int r = i + 1; r < m; r++)
        {
            if (s[i].value > s[r].value)
            {
                temp = s[i];
                s[i] = s[r];
                s[r] = temp;
            }
        }
    }
}