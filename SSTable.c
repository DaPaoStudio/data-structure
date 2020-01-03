#include <stdio.h>
#include <stdlib.h>

int Ssearch(int length,int x[length],int key);
int Bsearch(int length,int x[length],int key);

int main(void)
{
    int x[] = {0,1,2,3,4,5,6,7,8,9};
    printf("%d",Bsearch(10,x,0));
}

int Ssearch(int length,int x[length],int key)
{
    x[length+1] = key;
    int i = 0;
    while(x[i]!=key)
        i++;
    x[length+1]= 0;
    if(i==length+1)
        return -1;
    return i;
}

int Bsearch(int length,int x[length],int key)
{
    int low=0,mid,high = length-1;
    while(low<=high)
    {
        mid = (low + high)/2;
        if(x[mid]<key)
            low = mid+1;
        else if(x[mid]>key)
            high=mid-1;
        else
            return mid;
    }
    return -1;
}