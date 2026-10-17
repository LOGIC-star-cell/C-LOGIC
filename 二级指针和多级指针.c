#include<stdio.h>

int main()
{
    /*
        二级指针
            格式：数据类型**指针名
    */
    //定义变量
    int a=10;
    int b=20;

    //定义一级指针
    int *p=&a;
    
    //定义二级指针
    int** pp=&p;
    
    //作用1：利用二级指针修改一级指针里面记录的内存地址
    *pp=&b;

    //作用2：利用二级指针获取到变量中的数据


    //输出打印
    printf("%p\n",&a);
    printf("%p\n",&b);
    printf("%p\n",p);
    printf("%d\n",**pp);
    return 0;
}