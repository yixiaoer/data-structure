#ifndef staticlinklist_H_
#define staticlinklist_H_
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1 //预定义常量和类型
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 1000 //链表的最大长度
//Status是函数的类型,其值是函数结构状态代码
typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType data;
    int cur; //cur是游标，用同指针
} component, SLinkList[MAXSIZE];

int InitSpace_SL(SLinkList *space);
#endif