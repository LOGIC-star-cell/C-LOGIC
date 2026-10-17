#include<stdio.h>

void FindMinAndMax(int arr[],int len,int *min,int *max);

int main()
{
    int arr[]={2,6,9,5,4,8,1,7};
    int len=sizeof(arr)/sizeof(arr[0]);
    int max,min;
    FindMinAndMax(arr,len,&min,&max);    //调用函数时数组传参不能用arr[],要用数组名
    printf("数组的最大值是%d\n",max);
    printf("数组的最小值是%d\n",min);
    return 0;
}

void FindMinAndMax(int arr[],int len,int *min,int *max)    //用void类型函数 
{
    *min=arr[0];
    for(int i=1;i<len;i++) //不能<=，否则会越界
    {
        if(arr[i]<*min)
        {
            *min=arr[i];
        }
    }
    *max=arr[0];
    for(int i=0;i<len;i++)
    {
        if(arr[i]>*max)
        {
            *max=arr[i];
        }
    }
}