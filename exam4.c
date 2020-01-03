#include <stdio.h>
#include <string.h>
int f(int num, int g[num][num], int t, int visited[]);
int main(void)
{
    int n, m;
    scanf("%d", &n);
    int t = 0;
    int r[1000] = {0};
    while (n != 0)
    {
        scanf("%d", &m);
        int g[m][m];
        memset(g, 0, m * m);
        for (int i = 0; i < m; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            g[x][y] = 1;
            g[y][x] = 1;
        }
        int visited[1000] = {0};
        f(m, g, 0, visited);
        int j = 0, flag = 0;
        while (j < m)
        {
            if (visited[j] == 0)
            {
                flag = 1;
                break;
            }
            j++;
        }
        if (flag == 1)
            r[t++] = 0;
        else
            r[t++] = 1;
        scanf("%d", &n);
    }
    for (int i = 0; i < t; i++)
    {
        if (r[i] == 0)
            printf("NO\n");
        else
            printf("YES\n");
    }
}
int f(int num, int g[num][num], int t, int visited[])
{
    for (int i = 0; i < num; i++)
    {
        if (visited[i] == 0 && g[t][i] == 1)
        {
            visited[i] = 1;
            f(num, g, i, visited);
        }
    }
}