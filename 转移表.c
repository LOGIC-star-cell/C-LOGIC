#include<stdio.h>

int Add(int x,int y)
{
    return x + y;
}

int Sub(int x, int y)
{
    return x - y;
}

int Mul(int x,int y)
{
    return x * y;
}

int Div(int x,int y)
{
    return x / y;
}

void menu()
{
    printf("--------------------------------\n");
    printf("---------1.add    2.sub---------\n");
    printf("---------3.mul    4.div---------\n");
    printf("------------0.exit--------------\n");
}

int main()
{
    int input = 0;
    int x = 0;
    int y = 0;
    int r = 0;
    int (*pf[5])(int,int) = {NULL,Add,Sub,Mul,Div};
    //                        0    1   2   3   4
    do
    {
        menu();
        printf("请选择：>");
        scanf("%d",&input);

        if(input >= 1 && input <= 4)
        {
            printf("请输入两个操作数：");
            scanf("%d %d",&x,&y);
            r = pf[input](x,y);
            printf("结果是%d\n",r);
        }

        else if(input == 0)
        {
            printf("退出计算器\n");
        }

        else
        {
            printf("请输入0-4的数\n");
        }

    } while (input);
    
    
    return 0;
}