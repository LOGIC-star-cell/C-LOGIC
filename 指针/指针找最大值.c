#include<stdio.h>

int main()
{
    int a[5]={3,1,9,4,7};
    int *p=a;
    int max=*p;
    for(p=a;p<a+5;p++)
    {
        if(*p>max)
        {
            max=*p;
        }
    }
    printf("×î´óÖµ=%d\n",max);
    return 0;
}