#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

int next[MAXSIZE];
int nextavl[MAXSIZE];

void getnext(char *t);
void getnextavl(char *t);
int kmp(char *s, char *t, int pos);
void StrAssign(char **s, char *s1);
void read(char *s);
int length(char *s);

int main(void)
{
    char *s1, *s2;
    StrAssign(&s1, "ababcabaababb");
    StrAssign(&s2, "abaa");

    getnext(s2);
    for (int i = 1; i < 14; i++)
        printf("%d ", next[i]);
    printf("\n%d", kmp(s1, s2, 1));
}

void getnext(char *t)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;

    while (i < t[0])
    {
        if (j == 0 || t[i] == t[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

int kmp(char *s, char *t, int pos)
{
    int i = pos;
    int j = 1;
    while (i <= length(s) && j <= length(t))
    {
        if (j == 0 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j > length(t))
        return i - length(t);
    return -1;
}

void getnextavl(char *t)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;

    while (i < t[0])
    {
        if (j == 0 || t[i] == t[j])
        {
            i++;
            j++;
            if (t[i] != t[j])
                nextavl[i] = j;
            //增加以下
            else
                nextavl[i] = nextavl[j];
        }
        else
            j = next[j];
    }
}

void StrAssign(char **s, char *s1)
{
    *s = (char *)malloc(MAXSIZE * sizeof(char));
    int i = 0;
    while (s1[i] != '\0')
    {
        (*s)[i + 1] = s1[i];
        i++;
    }
    (*s)[0] = i;
}

void read(char *s)
{
    for (int i = 1; i <= s[0]; i++)
        printf("%c", s[i]);
    printf("\n");
}

int length(char *s)
{
    return s[0];
}