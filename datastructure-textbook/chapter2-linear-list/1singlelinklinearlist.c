/*======================================
用单链表来实现线性表(带头结点的单链表)
线性表的链式表示和实现
=======================================*/
#include <stdio.h>
#include <stdlib.h>
#include "1singlelinklinearlist.h"

int main()
{
    LinkList La, Lb, Lc;
    ElemType e;
    InitList_L(&La);
    InitList_L(&Lb);
    printf("elements in La and Lb are in non-decreasing sort\n");
    printf("there are 5 positive numbers in La\nInput them in reverse order:\n");
    CreatList_L(&La, 5);
    ListTraverse_L(La);
    printf("\n");
    printf("now input \"0\" at first place in La\n");
    ListInsert_L(&La, 1, 0);
    ListTraverse_L(La);
    printf("\n");
    printf("get the last element of La:\n");
    Getelem_L(La, 6, &e);
    printf("%d\n", e);
    printf("now delete the last element in La:\n");
    ListDelete_L(&La, 6, &e);
    ListTraverse_L(La);
    printf("\n");
    printf("there are 11 numbers in Lb\nInput them in reverse order:\n");
    CreatList_L(&Lb, 11);
    ListTraverse_L(Lb);
    printf("\n");
    printf("now merge La and Lb,there is Lc:\n");
    MergeList_L(&La, &Lb, &Lc);
    ListTraverse_L(Lc);
    printf("\n");
    printf("now clear La:\n");
    ClearList_L(&La);
    printf("show La now:\n");
    ListTraverse_L(La);
    printf("\n");
    printf("the length of La now is %d\n", ListLength_L(La));
}
/*==========================================================
下面是对单链表的操作
==========================================================*/
Status InitList_L(LinkList *L) //初始化一个单链表
{
    (*L) = (LinkList)malloc(sizeof(LNode)); //申请存放一个结点数据所要的空间
    if (!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL; //表的头结点的指针域置空
    return OK;
}

Status ListEmpty_L(LinkList L) //判断链表是否为空
{
    if (L->next == NULL && L != NULL) //链表存在且空
        return TRUE;
    else
        return FALSE;
}

Status DestoryList_L(LinkList *L) //销毁单链表,包括头结点
{
    LNode *p;
    if (ListEmpty_L(*L)) //先判断非空
    {
        while (*L) //只要不到NULL就持续循环，要逐一销毁每个结点
        {
            p = (*L)->next;
            //p将目前这个结点的下一个结点储存（下一个结点只有上一个结点知道在哪里，因为要销毁这个结点，所以要先把它的下一个结点信息储存）
            free(*L);
            *L = p; //再让L往后走
        }

        return OK;
    }
    else
        return ERROR;
}
/*****************
 **这个还有问题..***
 *****************/
Status ClearList_L(LinkList *L) //清空链表，仅保留头结点
{
    LNode *p0, *p1;
    p0 = (*L)->next;     //将p0置为头结点之后的首元结点，再将其及其之后按desory的方式依次删除
    if (ListEmpty_L(*L)) //先判断非空
    {
        while (p0) //只要不到NULL就持续循环，要逐一销毁每个结点
        {
            p1 = (p0)->next;
            //p将目前这个结点的下一个结点储存（下一个结点只有上一个结点知道在哪里，因为要销毁这个结点，所以要先把它的下一个结点信息储存）
            free(p0);
            p0 = p1; //再让L往后走
        }
        (*L)->next = NULL; //剩下的结点都清空了，将头结点的指针域指向NULL
        return OK;
    }
    else
        return ERROR;
}

int ListLength_L(LinkList L) //得到链表长度
{
    int length = 0;
    while (L)
    {
        L = L->next;
        length++;
    }
    return (length - 1); //因为先移动指针且length+1，在进行判断，在判断为NULL前已经加了一个1
}

Status ListInsert_L(LinkList *L, int i, ElemType e)
{ //在带头结点的单链线性表L中第i个位置之前插入元素e，书本算法2.9
    LNode *p = (*L), *s;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    } //持续向前，到达第i个位置之前那个元素
    if (!p || j > i - 1)
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode)); //生成新结点
    s->data = e;                         //为元素e安排一个结点
    s->next = p->next;                   //先将s的后面那个结点安排了，否则p后面那个结点会丢失
    p->next = s;
    return OK;
}

Status ListDelete_L(LinkList *L, int i, ElemType *e) //在带头结点的单链线性表L中，删除第i个元素，并由e返回其值，书本算法2.10
{
    LNode *p = (*L), *q;
    int j = 0;
    while (p && j < i - 1) //寻找第i个结点，并令p指向其前驱,j从0开始，则判断语句是到i-1
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = p->next->next;
    (*e) = q->data;
    free(q); //别忘了free！！
    return OK;
}

Status Getelem_L(LinkList L, int i, ElemType *e) //当第i个元素存在时，赋其值给e并返回OK，否则返回ERROR，书本算法2.8
{                                                //L是带头结点的单链表的
    int j = 1;                                   //计数
    LNode *p = L->next;                          //初始化，p指向首元结点，注意，p不是ElemType，而是LinkList，是结点的移动，ElemType是结点中的一个区域
    while (p && j < i)                           //不空且未到i处
    {
        p = p->next;
        j++;
    }
    if (!p || j > i) //空或长度不够i
        return ERROR;
    *e = p->data;
    return OK;
}

Status ListTraverse_L(LinkList L)
{
    while (L->next)
    {
        L = L->next; //主要要先移动结点，再printf，这样头结点才不会打出来，且后面也不会缺一项
        printf("%d\t", L->data);
    }
    return OK;
}
/*==========================================================
下面是题目的求解
==========================================================*/
/********************************************
***逆序输入n个元素的值，建立带表头结点的单链线性表***
***                         【书本算法2.11】***
**********************************************/
void CreatList_L(LinkList *L, int n)
{
    int i;
    LNode *p;
    (*L) = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL; //先建立一个带头结点的单链表
    for (i = n; i > 0; i--)
    {
        p = (LinkList)malloc(sizeof(LNode)); //生成新结点
        scanf("%d", &p->data);               //输入元素值
        p->next = (*L)->next;                //太妙了叭！
        (*L)->next = p;                      //插入到表头
    }
}
/*******************************************
***已知两个线性表LA和LB中的元素按值非递减排列，***
***其存储结构为单链表La和Lb，想要归并二者得到按***
***非递减排列的单链表Lc       【书本算法2.12】***
********************************************/
void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc)
{
    LinkList pa = (*La)->next, pb = (*Lb)->next, pc = (*La);
    (*Lc) = (*La); //用La的头结点作为Lc的头结点
    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }

    pc->next = pa ? pa : pb; //如果还有余下的元素，继续插入在后面

    free(*Lb);
    *Lb = NULL;
}