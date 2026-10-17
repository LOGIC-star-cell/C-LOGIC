#include<stdio.h>

// typedef unsigned int unit;
// int main()
// {
//     unsigned int num1 = 0;
//     unit num2 = 0;
//     return 0;
// }


// typedef int* pint_t;
// int main()
// {
//     //int *p1,p2;
//     //p1：指针变量 p2：整型

//     // int *p1 = NULL,*p2 = NULL;
//     // p1,p2：指针变量
//     pint_t p1,p2;

//     return 0;
// }

// #define PINT_T int*
// int main()
// {
//     PINT_T p1,p2;
//     return 0;
// }

// 对数组指针重命名
// typedef int (*parr_t)[5];
// int main()
// {
//     int arr[5] = {0};
//     int (*pa)[5] = &arr;
//     //类型：int (*)[5]
//     parr_t pb = &arr;
//     return 0;
// }

//对函数指针重命名
int Add(int x,int y)
{
    return x + y;
}

typedef int(*pf_t)(int,int);
int main()
{
    int (*pf1)(int,int) = Add;
    pf_t pf2 = Add;
    printf("%p\n",pf2);
    return 0;
}
