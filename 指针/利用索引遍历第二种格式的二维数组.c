#include<stdio.h>

int main()
{
    /*
        二维数组的定义格式二+索引遍历
            核心：实现把所有的一维数组定义完毕，再放入二维数组中
    */
    
    //1.定义三个一维数组
    int arr1[3]={1,2,3};
    int arr2[5]={1,2,3,4,5};
    int arr3[9]={1,2,3,4,5,6,7,8,9};

    //预先计算每一个数组真实的长度
    int len1=sizeof(arr1)/sizeof(int);
    int len2=sizeof(arr2)/sizeof(int);
    int len3=sizeof(arr3)/sizeof(int);

    //再去定义一个数组，装所有数组的长度
    int lenArr[3]={len1,len2,len3};

    //2.把三个一维数组放入到二维数组当中
    //数组的数据类型，跟内部存储的元素类型保持一致
    int* arr[3]={arr1,arr2,arr3}; //arr1,arr2,arr3都是地址，所以要用int*

    //3.利用索引遍历arr
    for(int i=0;i<3;i++)
    {
        //i表示二维数组的索引 0 1 2
        for(int j=0;j<lenArr[i];j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}