#ifndef arraylinearlist_H_
#define arraylinearlist_H_
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
//下面是有关线性表的各种定义
#define LIST_INIT_SIZE 100 //线性表储存空间的初始分配量
#define LISTINCREMENT 10   //线性表存储空间的分配增量
typedef int ElemType;
typedef struct
{
    ElemType *elem; //存储空间基址
    int length;     //当前长度
    int listsize;   //当前分配的存储容量(以sizeof(ElemType)为单位)
} SqList;

Status InitList_Sq(SqList *L);
Status DestoryList_Sq(SqList *L);
Status ClearList_Sq(SqList *L);
int ListLength_Sq(SqList L);
Status ListInsert_Sq(SqList *L, int i, ElemType e);
Status ListDelete_Sq(SqList *L, int i, ElemType *e);
Status Getelem_Sq(SqList L, int i, ElemType *e);
int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType));
Status compare(ElemType ea, ElemType eb);
Status ListTraverse(SqList L, void(visit)(ElemType));
void visit(ElemType e);
void unionList(SqList *La, SqList Lb);
void MergeList_Sq(SqList La, SqList Lb, SqList *Lc);
#endif
