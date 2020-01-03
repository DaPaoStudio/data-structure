#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int HashKey(char s[]);
void randint();
char s[45][20];
int r[100];

int main(void)
{
    int e = 0;
    randint();
    char t[20];
    int p;
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", r[i]);
        if (i % 9 == 0)
            printf("\n");
    }
    for (int i = 0; i < 30; i++)
    {
        gets(t);
        p = HashKey(t);
        //printf("%d ",p);
        if (s[p][0] == '\0')
        {
            strcpy(s[p], t);
        }
        else
        {
            int o = 0;
            while (s[p][0] != '\0')
            {
                p += r[o++];
                p %= 45;
                e++;
            }
            strcpy(s[p], t);
        }
    }
    for (int i = 0; i < 45; i++)
        printf("%s\n", s[i]);
    printf("%d\n", e);

    gets(t);
    double u = 0,w = 0;
    while (t[0] != 'e')
    { 
        int o = HashKey(t);
        w++;
        printf("HashKey:%d ",o);
        int y = 0;
        while (strcmp(t, s[o]))
        {
            u++;
            if (s[o][0] == '\0')
            {
                printf("error");
                break;
            }
            o += r[y++];
            o %= 45;
        }
        printf(" where:%d times:%d\n", o, y+1);
        gets(t);
    }
    printf("average:%lf",(w+u)/w);
}

int HashKey(char s[])
{
    int i;
    for (i = 0; s[i] != ' '; i++)
        ;
    int j = i + 1;
    for (; s[j] != '\0'; j++)
        ;
    int x = toascii(s[0]) * 11 + toascii(s[i + 1]) * 7 + toascii(s[j]);
    return x % 43;
}
void randint()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++)
    {
        r[i] = rand() % 45;
        while (r[i] == 0)
            r[i] = rand() % 45;
    }
}