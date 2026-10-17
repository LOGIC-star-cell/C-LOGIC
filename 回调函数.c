#include<stdio.h>

//将四个函数抽象成一个函数 这一个函数就能做四种事情
void calc(int (*pf)(int,int))
{
    int x,y,r;
    printf("请输入两个操作数：");
    scanf("%d%d",&x,&y);
    r = pf(x,y);
    printf("结果是：%d\n",r);
}

int main()
{
    //calc(Add);
    return 0;
}