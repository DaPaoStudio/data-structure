#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int HashKey(char s[]);
void randint(int r[]);

double hash(void)
{
    FILE *f;
    f = fopen("name.txt","r");
    if(f==NULL)
    {
        printf("error");
        return 0;
    }
    char s[45][20]={{'0'}};
    double e = 0;
    int r[100]={0};
    randint(r);
    char t[20];
    int p;
    for (int i = 0; i < 30; i++)
    {
        fgets(t,20,f);
        p = HashKey(t);
        e++;
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
    fclose(f);
    return e / (double)30;
}
int main(void)
{
    double times;
    scanf("%lf",&times);
    double x = 0;
    for (int i = 0; i < times; i++)
    {
        x += hash();
    }
    printf("%lf", x / times);
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
void randint(int r[])
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++)
    {
        r[i] = rand() % 45;
        while (r[i] == 0)
            r[i] = rand() % 45;
    }
}
