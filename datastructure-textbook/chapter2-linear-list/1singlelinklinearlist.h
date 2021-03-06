#ifndef singlelinkinearlist_H_
#define singlelinklinearlist_H_
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1 //预定义常量和类型
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status是函数的类型,其值是函数结构状态代码
typedef int Status;
//下面是有关链表的各种定义
typedef int ElemType;
typedef struct LNode
{
    ElemType data;      //数据域
    struct LNode *next; //指针域
} LNode, *LinkList;

Status InitList_L(LinkList *L);
Status ListEmpty_L(LinkList L);
Status DestoryList_L(LinkList *L);
Status ClearList_L(LinkList *L);
int ListLength_L(LinkList L);
Status ListInsert_L(LinkList *L, int i, ElemType e);
Status ListDelete_L(LinkList *L, int i, ElemType *e);
Status Getelem_L(LinkList L, int i, ElemType *e);
Status ListTraverse_L(LinkList L);
void CreatList_L(LinkList *L, int n);
void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc);
#endif