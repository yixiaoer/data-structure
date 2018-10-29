/*=========================================
1.16 试写一算法，以大到小顺序依次输出读入的三个整
数X，Y，Z的值
==========================================*/

#include <stdio.h>

int main()
{
    int x, y, z, temp;
    printf("Input X，Y，Z:\n");
    scanf("%d%d%d", &x, &y, &z);
    if (x < y)
    {
        temp=x;
        x = y;
        y = temp;
    }
    if (x < z)
    {
        temp=x;
        x = z;
        z = temp;
    }
    if (y < z)
    {
        temp=y;
        y = z;
        z = temp;
    }
    printf("顺序是：%d\t%d\t%d\n", x, y, z);
    return 0;
}