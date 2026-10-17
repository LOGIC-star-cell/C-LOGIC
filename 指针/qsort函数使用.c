#include<stdio.h>

void qsort(void *base,//指针，指向了要排序的数组的第一个元素
    size_t num, //base指向的数组的元素个数
    size_t size, //base指向的数组中一个元素的字节数
    int (*compar)(const void*,const void*) //函数指针- 指向一个行数
    //指向的这个函数用来比较base指向的数组中任意两个数据的大小
    )

//qsort是一个库函数，是用来对数据进行排序的
//基于快速排序的思想对数据进行排序的
//qsort函数能排序任意类型的数据

int main()
{
    
    return 0;
}