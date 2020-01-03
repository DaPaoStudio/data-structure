#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5 /*叶子结点个数的最大值*/
#define M 2 * N - 1
#define MAXINT 32767

typedef char *HuffmanCode[N]; /*Huffman 编码*/

typedef struct
{
    int weight;
    int parent; /*双亲的下标*/
    int LChild; /*左孩子的下标*/
    int RChild; /*右孩子的下标*/
} HTNode, HuffmanTree[M];

void CrtHuffmanTree(HuffmanTree ht, int w[], int n);
void select(HuffmanTree ht, int pos, int *s1, int *s2);
void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n);

int main(void)
{
    HuffmanTree ht;
    int w[] = {5, 7, 3, 2, 8};
    CrtHuffmanTree(ht, w, 5);

    HuffmanCode x;

    CrtHuffmanCode(ht, x, N);
    for (int i = 0; i < N; i++)
        printf("%s\n", x[i]);
}

void CrtHuffmanTree(HuffmanTree ht, int w[], int n)
{
    int i, j, k, s1, s2;
    for (i = 0; i < n; i++) /*初始化*/
    {
        ht[i].weight = w[i];
        ht[i].parent = 0;
        ht[i].LChild = 0;
        ht[i].RChild = 0;
    }
    int m = 2 * n - 1;
    for (i = n + 1; i < m; i++) /*初始化*/
    {
        ht[i].weight = 0;
        ht[i].parent = 0;
        ht[i].LChild = 0;
        ht[i].RChild = 0;
    }
    /*选择   合并*/
    for (i = n; i < m; i++)
    {
        select(ht, i, &s1, &s2);
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].LChild = s1;
        ht[i].RChild = s2;
    }
}

void select(HuffmanTree ht, int pos, int *s1, int *s2)
{
    int j, m1, m2;    /*m1存放最小权值,s1是m1在数组的下标*/
    m1 = m2 = MAXINT; /*m2存放次小权值,s2是m2在数组的下标*/
    for (j = 0; j < pos; j++)
    {
        if (ht[j].weight < m1 && ht[j].parent == 0)
        {
            m2 = m1;
            *s2 = *s1;
            *s1 = j;
            m1 = ht[j].weight;
        }
        else if (ht[j].weight < m2 && ht[j].parent == 0)
        {
            m2 = ht[j].weight;
            *s2 = j;
        }
    }
}

void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n)
{
    char *cd;
    cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for (int i = 0; i < n; i++)
    {
        int start = n - 1;
        int c = i;
        int p = ht[i].parent;
        while (p != 0)
        {
            --start;
            if (ht[p].LChild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = p;
            p = ht[p].parent;
        }
        hc[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(hc[i], &cd[start]);
    }
    free(cd);
}