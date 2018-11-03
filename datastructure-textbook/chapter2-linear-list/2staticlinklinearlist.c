/*======================================
用静态单链表来实现线性表
借用一维数组来描述线性链表
线性表的链式表示和实现
=======================================*/
#include <stdio.h>
#include <stdlib.h>
#include "2staticlinklinearlist.h"

/*==========================================================
下面是对静态单链表的操作
前面三个是对于其备用空间的操作（就像是链表的空间来自内存一样）
==========================================================*/
Status InitSpace_SL(SLinkList *space) //将一维数组space中各分量链成一个备用链表，书本算法2.14
{                                     //即将整个数组空间初始化成一个链表
    int i = 0;
    for (; i < MAXSIZE; i++)
        (*space)[i].cur = i + 1;   //（ *space）[0].cur为头指针
    (*space)[MAXSIZE - 1].cur = 0; //0表示空指针
    return OK;
}

int Malloc_SL(SLinkList *space) //从备用空间取得一个结点，若备用空间链表非空，返回分配的下标结点，否则返回0，书本算法2.15
{                               //静态链表需要自己实现malloc和free
    int i;
    i = (*space)[0].cur;
    if ((*space)[0].cur)
        (*space)[0].cur = (*space)[i].cur; //space是备用链表，即没有用过的结点在这里存放，其第一个分配出去之后，第一个的值改变，就变成分配出去的那个值的cur的值
    return i;
}

void Free_SL(SLinkList *space, int k) //将下标为k的空闲结点回收到备用链表，书本算法2.16
{                                     //将空闲结点链结到备用链表上
    (*space)[k].cur = (*space)[0].cur;
    (*space)[0].cur = k;
}

int ListLength_SL(SLinkList S)
{
    int j = 0;
    int i = S[MAXSIZE - 1].cur;
    while (i)
    {
        i = S[i].cur;
        j++;
    }
    return j;
}

Status ListInsert_SL(SLinkList *S, int i, ElemType e) //在静态链表的第i个元素之前插入新的数据元素e
{
    int j, k, l;
    k = MAXSIZE - 1;
    if (i < 1 || i > ListLength_SL(*S) + 1)
        return ERROR;
    j = Malloc_SL(S);
    if (j)
    {
        (*S)[j].data = e; //将数据的值分配给分量的data
        for (l = 1; l <= i - 1; l++)

            k = (*S)[k].cur;
        (*S)[j].cur = (*S)[k].cur;
        (*S)[k].cur = j;
        return OK;
    }
    return ERROR;
}

Status ListDelete_SL(SLinkList *S, int i, ElemType *e)
{
    int j, k;
    if (i < 1 || i > ListLength_SL(*S))
        return ERROR;
    k = MAXSIZE - 1;
    for (j = 1; j <= i - 1; j++)
        k = (*S)[k].cur;
    j = (*S)[k].cur;
    (*S)[k].cur = (*S)[j].cur;
    Free_SL(S, j);
    return OK;
}
