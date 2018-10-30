/*======================================
用数组来实现线性表
线性表的顺序表示和实现
=======================================*/
#include <stdio.h>
#include <stdlib.h>
#include "0arraylinearlist.h"

int main()
{
    int choice, i, num;
    SqList La, Lb, Lc;
    ElemType e;
    ElemType Sqa[11] = {0, 3, 5, 6, 7, 11, 20, 27, 31, 39, 46}, Sqb[7] = {3, 4, 6, 8, 12, 39, 53};
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    printf("Input number:\n"); //根据输入数字选择例题
    scanf("%d", &choice);

    for (i = 0; i < 11; i++)               //特别注意，如果这里i是0开始，则在insert时是i+1
        ListInsert_Sq(&La, i + 1, Sqa[i]); //从第一个位置开始插入元素
    printf("La has those elements:\n");
    ListTraverse(La, visit);
    printf("\n\n");

    for (i = 0; i < 7; i++)
        ListInsert_Sq(&Lb, i + 1, Sqb[i]);
    printf("Lb has those elements:\n");
    ListTraverse(Lb, visit);
    printf("\n\n");

    switch (choice)
    {
    case 1:
        unionList(&La, Lb);
        printf("after union,La has those elements:\n");
        ListTraverse(La, visit);
        printf("\n\n");

        break;

    case 2: //例2-2
        InitList_Sq(&Lc);
        printf("after merge,Lc:\n");
        MergeList_Sq(La, Lb, &Lc);
        ListTraverse(Lc, visit);
        printf("\n\n");

        break;

    case 3: //测试一些函数
        printf("input the number of the element in La you want to delete(<=11):\n");
        scanf("%d", &num);
        ListDelete_Sq(&La, num, &e);
        printf("now La's elements:\n");
        ListTraverse(La, visit);
        printf("\n\n");

        ClearList_Sq(&La);
        printf("now clear the elements in La\nnow La's element:\n");
        ListTraverse(La, visit);
        printf("\nnothing");
    }
    getchar();
    return 0;
}

/*==========================================================
下面是对线性表的数组操作
==========================================================*/
Status InitList_Sq(SqList *L) //构造一个空的线性表,书本算法2.2
{
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!(*L).elem)
        exit(OVERFLOW);             //存储分配失败
    (*L).length = 0;                //初始化了空表,空表长度为0
    (*L).listsize = LIST_INIT_SIZE; //初始化存储容量
    return OK;
}

Status DestoryList_Sq(SqList *L) //销毁线性表
{
    if ((*L).elem != NULL) //先判断线性表存在
    {
        free((*L).elem); //释放顺序表L所占的空间
        (*L).elem = NULL;
        (*L).listsize = 0;
        (*L).length = 0;
        return OK;
    }
    else
        return ERROR;
}

Status ClearList_Sq(SqList *L) //清空线性表
{
    if ((*L).elem != NULL) //先判断线性表存在
    {
        (*L).length = 0; //将L置为空表
        return OK;
    }
    else
        return ERROR;
}

int ListLength_Sq(SqList L) //返回线性表中元素个数
{
    if (L.elem != NULL) //先判断线性表存在
    {
        return L.length; //返回个数
    }
    else
        return ERROR;
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

Status Getelem_Sq(SqList L, int i, ElemType *e) //用e返回L中第i个数据元素的值
{
    if ((i < 1) || (i > L.length)) //i的合法范围在1到表长之间
        return ERROR;
    (*e) = L.elem[i - 1];
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

Status compare(ElemType ea, ElemType eb) //LocateElem_Sq()中的数据元素判定函数
{
    if (ea == eb)
    {
        return TRUE;
    }
    else
        return FALSE; //这里可以用return e1==e2 ? TRUE : FALSE;这一句就够了哇owo...
}

Status ListTraverse(SqList L, void(visit)(ElemType))
{
    int i;
    for (i = 0; i < L.length; i++)
        visit(L.elem[i]);
    return OK;
}

void visit(ElemType e)
{
    printf("%d\t", e);
}
/*==========================================================
下面是题目的求解
==========================================================*/
/**********************************************
***例2-1 利用两个线性表LA和LB表示两个集合，扩大线性***
***表LA，将存在于LB但不存在于LA中的数据元素插入LA中***
**********************************************/
void unionList(SqList *La, SqList Lb)
{
    int i;
    int len_a;
    len_a = ListLength_Sq(*La);
    ElemType e;
    for (i = 1; i < Lb.length; i++)
    {
        Getelem_Sq(Lb, i, &e); //还是注意如果是从0开始取i！！！不过最好还是从1开始取叭，就有要get第i个位置element的对应
        if (!LocateElem_Sq((*La), e, compare))
            ListInsert_Sq(La, ++len_a, e); //注意这里对len_a不可直接用(*La).length
    }
}

/**********************************************
***例2-2 已知顺序线性表La和Lb的元素按值非递减排列，***
***归并表La和Lb得到新的顺序线性表Lc，Lc的元素也按值***
非递减排序.                      【书本算法2.6】***
**********************************************/
void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) //
{                                                   //
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
