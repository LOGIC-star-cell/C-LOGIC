#include<stdio.h>
#include<stdlib.h>

// void qsort(
//     void *base,//通用指针，指向了要排序的数组的第一个元素，可以接受任意类型的数组首地址
//     size_t num, //base指向的数组的元素个数
//     size_t size, //base指向的数组中一个元素的字节数
//     int (*compar)(const void*,const void*) //函数指针- 指向一个函数
//     //指向的这个函数用来比较base指向的数组中任意两个数据的大小
// )

//qsort是一个库函数，是用来对数据进行排序的
//基于快速排序的思想对数据进行排序
//qsort函数能排序任意类型的数据

int cmp_int(const void* p1,const void* p2)
{
    //比较两个整形数据的大小
    //要求函数的返回值能体现出p1,p2指向的数据大小
    //p1指向的数据>p2指向的数据，返回值>0
    //p1指向的数据<p2指向的数据，返回值<0
    //p1指向的数据=p2指向的数据，返回值=0

    // if (*(int*)p1 > *(int*)p2)
    // {
    //     return 1;
    // }

    // else if(*(int*)p1 < *(int*)p2)
    // {
    //     return -1;
    // }
    // else
    // {
    //     return 0;
    // }
    
    return (*(int*)p1 - *(int*)p2);

}

void print_arr(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void test1()
{
    int arr[] = {9,8,7,6,5,4,3,2,1,0};
    //对数组进行排序 - 升序
    int len = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, len, sizeof(arr[0]), cmp_int);
    print_arr(arr, len);
}

int main()
{
    test1(); //测试qsort排序整型数据
    return 0;
}