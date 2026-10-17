#include<stdio.h>

int main()
{
    //1.定义三个一维数组
    int arr1[5]={1,2,3,4,5};
    int arr2[5]={11,22,33,44,55};
    int arr3[5]={111,222,333,444,555};

    //2.把三个一维数组的内存地址，再放入到二维数组当中
    int *arr[3]={arr1,arr2,arr3};

    //3.获取指针
    int** p=arr;

    //4.遍历数组
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("%d ",*(*p+j));
        }
        printf("\n");

        //移动指针
        p++;
    }
    return 0;
}