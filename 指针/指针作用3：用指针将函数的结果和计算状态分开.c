#include<stdio.h>

int getReminder(int a,int b,int *result);

int main()
{
    int a=10;
    int b=3;
    int result;
    int flag=getReminder(a,b,&result);
    if(flag)
    {
        printf("获得的余数为:%d\n",result);
    }
    else
    {
        printf("错误:除数不能为0!\n");
    }
    return 0;
}

int getReminder(int a,int b,int *result)
{
    if(b==0)
    {
        return 0;
    }
    else
    {
        *result=a%b;
        return 1;
    }
}