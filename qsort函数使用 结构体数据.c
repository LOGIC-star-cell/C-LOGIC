#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Stu
{
    char name[100];
    int age;
};

int cmp_stu_by_age(const void *p1, const void *p2)
{
    //return ((*(struct Stu*)p1).age - (*(struct Stu*)p2).age);
    return (((struct Stu*)p1)->age - ((struct Stu*)p2)->age);
}

int cmp_stu_by_name(const void *p1, const void *p2)
{
    //return strcmp((*(struct Stu*)p1).name, (*(struct Stu*)p2).name);
    return strcmp(((struct Stu*)p1)->name, ((struct Stu*)p2)->name);
}

void test2()
{
    struct Stu arr[] = {{"zhangsan",18}, {"lisi",25}, {"wangwu",15}};
    int sz = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, sz, sizeof(arr[0]), cmp_stu_by_age);
    for(int i = 0; i < sz; i++)
    {
        printf("%s %d\n",arr[i].name, arr[i].age);
    }

    qsort(arr, sz, sizeof(arr[0]), cmp_stu_by_name);
    for(int j = 0; j < sz; j++)
    {
        printf("%s %d\n",arr[j].name,arr[j].age);
    }

}

void test3()
{
    struct Stu s = {"zhangsan", 28};
    printf("%s %d\n",s.name,s.age);

    //结构指针和结构体成员访问操作符 ->
    struct Stu *ps = &s;
    //printf("%s %d\n",(*ps).name, (*ps).age);
    printf("%s %d\n",ps->name,ps->age);
}
//结构体成员访问：
//1.结构体变量.成员名
//2.结构体指针->成员名

int main()
{
    test2();
    
    test3();
    
    return 0;
}