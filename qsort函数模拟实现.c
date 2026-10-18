#include<stdio.h>

int cmp_int(const void *p1, const void *p2)
{
    return (*(int*)p1 - *(int*)p2);
}

void Swap(char *buf1, char *buf2, size_t width)
{
    for(size_t i = 0; i < width; i++)
    {
        char tmp = *buf1;
        *buf1 = *buf2;
        *buf2 = tmp;
        buf1++;
        buf2++;
    }
}

void bubble_sort2(void *base, size_t sz, size_t width, int (*cmp)(const void *p1, const void *p2))
{
    for(int i = 0; i < sz - 1; i++)
    {
        for(int j = 0; j < sz - 1 -i; j++)
        {
            //下标为j和下标为j+1这2个元素
            //升序
            if(cmp((char*)base + j * width, (char*)base + (j + 1) * width) > 0)
            {
                //交换
                Swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
            }
        }
    }
}

void test4()
{
    int arr[] = {8,7,6,5,4,1,3,2,0};
    int sz = sizeof(arr) / sizeof(arr[0]);
    bubble_sort2(arr, sz, sizeof(arr[0]), cmp_int);
    for (size_t i = 0; i < sz; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    
}

int main()
{
    test4();
    return 0;
}