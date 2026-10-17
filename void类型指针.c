#include<stdio.h>

void swap(void *p1,void *p2,int len);

int main()
{
    //1.定义两个变量
    int a=10;
    short b=20;

    //2.定义两个指针
    int *p1=&a;
    short *p2=&b;

    //3.输出打印
    printf("%d\n",*p1);
    printf("%d\n",*p2);
    
    //char *p3=(char)p1; //不同指针之间，是不能互相赋值的
    //void类型的指针打破上面的观念
    //void没有任何类型，好处是可以接受任意类型指针记录的内存地址
    // void *p3=p1;
    // void *p4=p2;
    //缺点：无法获取变量里面的数据，也不能进行加减的计算
    //printf("%p\n",p3+1);
    
    //调用函数交换数据
    int c=100;
    int d=200;
    swap(&c,&d,4);
    printf("c=%d,d=%d\n",c,d);

    return 0;
}

//函数：用来叫偶换两个变量记录的数据
//修改一下函数，更具有通用性

void swap(void *p1,void *p2,int len)
{
    //把void类型的指针，转成char类型的指针
    char *pc1=p1;
    char *pc2=p2;

    char temp=0;
    //以字节为单位，一个字节一个字节的进行交换
    for(int i=0;i<len;i++)
    {
        temp=*pc1;
        *pc1=*pc2;
        *pc2=temp;
        
        pc1++;
        pc2++;
    }
}