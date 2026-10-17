#include<stdio.h>
 void swap(int *num1,int *num2)
 {
    int t=*num1;
    *num1=*num2;
    *num2=t;
 }
int main()
{
    int a=10;
    int b=20;
    swap(&a,&b);
    printf("%d %d",a,b);
    return 0;
}