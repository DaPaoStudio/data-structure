#include <iostream>
#include <stack>
#define MAXSIZE 10000
using namespace std;

int main(void)
{
    int num;
    cin >> num;
    int d[num][num], path[num][num];

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            scanf("%d", &d[i][j]);
            path[i][j] = i;
        }
    }
    for (int i = 0; i < num; i++)
    {
        for (int x = 0; x < num; x++)
        {
            if (x != i)
            {
                for (int y = 0; y < num; y++)
                {
                    if (d[x][y] > d[x][i] + d[i][y])
                    {
                        d[x][y] = d[x][i] + d[i][y];
                        path[x][y] = path[i][y];
                    }
                }
            }
        }
    }
    /*
    for(int i = 0;i<num;i++)
    {
        for(int j = 0;j<num;j++)
            printf("%d ",d[i][j]);
        printf("\n");
    }*/
    int f[1000] = {0}, t[1000] = {0}, num1 = 0;
    scanf("%d %d", &f[num1], &t[num1]);
    while (f[num1] != -1)
    {
        num1++;
        scanf("%d %d", &f[num1], &t[num1]);
    }
    for (int i = 0; i < num1; i++)
    {
        if (d[f[i]][t[i]] != MAXSIZE)
        {
            printf("%d\n", d[f[i]][t[i]]);
            stack<int> s;
            int x = f[i], y = path[x][t[i]];
            while (y != x)
            {
                s.push(y);
                y = path[x][y];
            }
            printf("%d ", x);
            while (s.empty() == 0)
            {
                printf("%d ", s.top());
                s.pop();
            }
            printf("%d\n", t[i]);
        }
        else
        {
            printf("NO\n");
        }
    }
}