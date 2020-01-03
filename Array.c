#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct 
{
    int *base;
    int dim;
    int *bounds;//存储各维数的大小
    int *constants;//帮助定位
} Array;

void InitArray(Array *a, int dim, ...);
int Locate(Array a,int *e);
int Value(Array a,int *e);
void Assign(Array a,int *e,int value);

int main()
{
    Array a;
    InitArray(&a,3,3,2,3);
    int t[] = {1,0,0};
    
    printf("%d",Locate(a,t));
}

void InitArray(Array *a, int dim, ...)
{
    va_list ap;
    int e=1;
    a->dim = dim;
    a->bounds = (int *)malloc(dim*sizeof(int));
    va_start(ap,dim);
    for(int i =0;i<dim;i++)
    {
        a->bounds[i] = va_arg(ap,int);
        e*=a->bounds[i];
    }
    va_end(ap);
    a->base = (int*)malloc(e*sizeof(int));
    a->constants = (int *)malloc(dim*sizeof(int));
    a->constants[dim-1] = 1;
    for(int i = dim-2;i>=0;i--)
        a->constants[i] = a->bounds[i+1] * a->constants[i+1];
}

int Locate(Array a,int *e)
{
    int off=0;
    for(int i = 0;i<a.dim;i++)
    {
        off+=a.constants[i]*e[i];
    }
    return off;
}

int Value(Array a,int *e)
{
    return a.base[Locate(a,e)];
}

void Assign(Array a,int *e,int value)
{
    a.base[Locate(a,e)] = value;
}