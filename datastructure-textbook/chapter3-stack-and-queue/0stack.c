#include <stdio.h>
#include <stdlib.h>
#include "0stack.h"
/*===========================================================================
关于栈的各种操作_(:з」∠)_
============================================================================*/
Status InitStack(SqStack *S)
{ //构造一个空栈
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));

	if (!(*S).base)
		exit(OVERFLOW); //栈底元素不空，说明这个栈已经存在了，无法init一个stack
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestoryStack(SqStack *S)
{
	(*S).base = NULL;
	(*S).stacksize = 0;
	free(S); //free掉这个指针的存储空间
	return OK;
}

Status ClearStack(SqStack *S)
{
	(*S).top = (*S).top;
	(*S).stacksize = 0;
	return OK;
}

Status StackEmpty(SqStack S)
{ //判断栈是否为空
	if (S.top == S.base)
		return TRUE;
	else
		return (FALSE);
}

Status GetTop(SqStack S, SElemType *e)
{
	if (S.top == S.base)
		return ERROR;
	(*e) = *(S.top - 1);
	return OK;
}

int StackLength(SqStack S)
{
	int i = 0;
	while (S.top)
	{
		i++;
		S.top++;
	}
	return i;
}

Status Pop(SqStack *S, SElemType *e)
{ //pop元素出栈
	if ((*S).top == (*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

Status Pop1(SqStack *S, SElemType1 *e)
{ //pop元素出栈
	if ((*S).top == (*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

Status Push(SqStack *S, SElemType e)
{ //push元素入栈
	if ((*S).top - (*S).base >= (*S).stacksize)
	{ //栈满，追加储存空间
		(*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!(*S).base)
			exit(OVERFLOW); //存储分配失败

		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*(*S).top++ = e;
	return OK;
}

Status StackTraverse(SqStack S, Status (*visit)())
{ //从栈底到栈顶一次对栈中每个元素调用函数visit()。一旦visit()失败，则操作失败
	if (S.top == S.base)
		return ERROR;
	while (S.top)
	{
		visit();
		S.top++;
	}
}

void visit(SqStack S)
{
	printf("%d", *(S.top));
}

Status main()
{
	int choice;
	int num, numN;
	printf("input number:\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("Input number now\n");
		scanf("%d", &num);
		printf("transfer to what:\n");
		scanf("%d", &numN);
		printf("this is output\n");
		conversion(num, numN); //数制转换
		break;
	case 2:
		paren(); //括号匹配的检验
		break;
	case 3:
		LineEdit(); //行编辑程序
		break;
	case 4:
		maze(); //迷宫求解
		break;
	case 5:
		EvaluateExpression(); //表达式求值
	case 6:
		Hanoi(); //Hanoi塔过程
	default:
		break;
	}
}
