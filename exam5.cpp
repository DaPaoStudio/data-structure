#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

void f(int root, int t, string s1, string s2);
int visited[1000];
int main(void)
{
    int num;
    cin >> num;
    string s1, s2;
    fflush(stdin);
    cin >> s1;
    cin >> s2;
    f(-1, 0, s1, s2);
    int max = 0;
    for(int i =0;i<num;i++)
    {
        max = max<visited[i]?visited[i]:max;
        //printf("%d ",visited[i]);
    }
    cout<<int(log(max)/log(2)+1);
    //cout<<max;
}

void f(int root, int t, string s1, string s2)
{
    char ch = s1[t];
    int i = 0;
    for (; s2[i] != ch; i++)
    {
    }
    int e = root;
    if(root==-1)
    {
        visited[i] = 1;
    }
    else if (i > root)
    {
        while (e <= i)
        {
            if (visited[e] != 0)
                root = visited[e];
            e++;
        }
        visited[i] = 2 * root+1;
    }
    else
    {
        while (e >= i)
        {
            if (visited[e] != 0)
                root = visited[e];
            e--;
        }
        visited[i] = 2 * root;
    }
    if (t + 1 < s1.length())
        f(i, t + 1, s1, s2);
}