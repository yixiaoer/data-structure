/*======================================
用单链表来实现线性表(带头结点的单链表)
线性表的链式表示和实现
=======================================*/
#include <stdio.h>
#include <stdlib.h>
#include "1singlelinklinearlist.h"

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
    LinkList p;
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

Status ClearList_L(LinkList *L) //清空链表，仅保留头结点
{
    LinkList p0, p1;
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