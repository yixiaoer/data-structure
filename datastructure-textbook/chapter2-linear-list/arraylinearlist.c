/*======================================
用数组来实现线性表
=======================================*/
#include <stdio.h>
#include <stdlib.h>
#include "arraylinearlist.h"

Status InitList_Sq(SqList *L) //构造一个空的线性表,书本算法2.2
{
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!(*L).elem)
        exit(OVERFLOW);             //存储分配失败
    (*L).length = 0;                //初始化了空表,空表长度为0
    (*L).listsize = LIST_INIT_SIZE; //初始化存储容量
    return OK;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e) //在顺序线性表L中第i各位置之前插入新的元素e,书本算法2.3
{
    ElemType *newbase; //重新分配时用到
    ElemType *q;       //插入位置
    ElemType *p;       //原来的第i个位置及其之后的元素，通过这个来循环向后传值
    if (i <= 0 || i > (*L).length + 1)
        return ERROR;

    if (((*L).length) >= (*L).listsize) //如果当前存储空间已满,要重新分配
    {
        newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);  //储存分配失败
        (*L).elem = newbase; //新基址
        (*L).listsize += LISTINCREMENT;
    }

    q = &((*L).elem[i - 1]);                             //q为插入位置,这个位置是第i个元素的位置,e插于第i个元素之前,即插入之后e是第i个元素
    for (p = &((*L).elem[(*L).length - 1]); p >= q; --p) //先将插入位置之后的元素后移
        *(p + 1) = *p;                                   //先移后面的元素
    *q = e;
    ++(*L).length;
    return OK;
}

Status ListDelete_Sq(SqList *L, int i, ElemType *e) //在顺序线性表L中删除第i个元素,并用e返回其值,书本算法2.4
{
    ElemType *p;                      //被删除元素的位置,之后通过这个来循环向前传值
    ElemType *q;                      //表尾元素的位置
    if ((i < 1) || (i > (*L).length)) //i的合法范围在1到表长之间
        return ERROR;                 //i值不合法
    p = &((*L).elem[i - 1]);          //即被删除元素的位置
    *e = *p;                          //将被删除的元素的值赋给e
    q = &((*L).elem[(*L).length - 1]);
    for (++p; p <= q; ++p)
        *(p - 1) = *p; //删除元素的位置之后的元素左移
    --(*L).length;
    return OK;
}

int LocateElem_Sq(SqList L, ElemType e,
                  Status (*compare)(ElemType, ElemType)) //在顺序线性表L中查找第一个与e满足compare()的元素的位序
{                                                        //若找到返回其在L中的位序;否则返回0,书本算法2.5
    ElemType *p;
    int i = 1; //i的初值为第1个元素的位序
    p = L.elem;
    while (i <= L.length && !(*compare)(*p++, e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) //已知顺序线性表La和Lb的元素按值非递减排列
{                                                   //归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排序,书本算法2.6
    ElemType *pa, *pb, *pc;
    ElemType *pa_last, *pb_last;
    pa = La.elem;
    pb = Lb.elem;
    (*Lc).length = La.length + Lb.length;
    (*Lc).listsize = (*Lc).length;
    (*Lc).elem = (ElemType *)malloc((*Lc).listsize * sizeof(ElemType));
    if (!(*Lc).elem) //存储分配失败
        exit(OVERFLOW);
    pc = (*Lc).elem;
    pa_last = La.elem + La.length - 1; //指针形式，得到顺序线性表La的最后一个元素的位置
    pb_last = Lb.elem + Lb.length - 1;
    while (pa <= pa_last && pb <= pb_last) //归并
    {
        if (*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa <= pa_last) //插入La的剩余元素
        *pc++ = *pa++;
    while (pb <= pb_last) //插入Lb的剩余元素
        *pc++ = *pb++;
}