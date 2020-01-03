#include <iostream>
using namespace std;
int visited[10000];
int x[10000][10000];
void f(int num, int t);
int main(void)
{
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
            cin >> x[i][j];
    int t = 0;
    for (int i = 0; i < num; i++)
    {
        if (visited[i] == 0)
        {
            printf("%d ", i);
            visited[i] = 1;
            t++;
            f(num, i);
        }
    }
    printf("\n%d",t);
}
void f(int num, int t)
{
    for (int i = 0; i < num; i++)
    {
        if (x[t][i] ==1)
            if (visited[i] == 0)
            {
                printf("%d ", i);
                visited[i] = 1;
                f(num, i);
            }
    }
}