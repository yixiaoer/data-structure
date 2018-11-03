#include <stdio.h>
#include <stdlib.h>
#include "0stack.h"
/*===========================================================================
����ջ�ĸ��ֲ���_(:�١���)_
============================================================================*/
Status InitStack(SqStack *S)
{ //����һ����ջ
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));

	if (!(*S).base)
		exit(OVERFLOW); //ջ��Ԫ�ز��գ�˵�����ջ�Ѿ������ˣ��޷�initһ��stack
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestoryStack(SqStack *S)
{
	(*S).base = NULL;
	(*S).stacksize = 0;
	free(S); //free�����ָ��Ĵ洢�ռ�
	return OK;
}

Status ClearStack(SqStack *S)
{
	(*S).top = (*S).top;
	(*S).stacksize = 0;
	return OK;
}

Status StackEmpty(SqStack S)
{ //�ж�ջ�Ƿ�Ϊ��
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
{ //popԪ�س�ջ
	if ((*S).top == (*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

Status Pop1(SqStack *S, SElemType1 *e)
{ //popԪ�س�ջ
	if ((*S).top == (*S).base)
		return ERROR;
	*e = *--(*S).top;
	return OK;
}

Status Push(SqStack *S, SElemType e)
{ //pushԪ����ջ
	if ((*S).top - (*S).base >= (*S).stacksize)
	{ //ջ����׷�Ӵ���ռ�
		(*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!(*S).base)
			exit(OVERFLOW); //�洢����ʧ��

		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*(*S).top++ = e;
	return OK;
}

Status StackTraverse(SqStack S, Status (*visit)())
{ //��ջ�׵�ջ��һ�ζ�ջ��ÿ��Ԫ�ص��ú���visit()��һ��visit()ʧ�ܣ������ʧ��
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
		conversion(num, numN); //����ת��
		break;
	case 2:
		paren(); //����ƥ��ļ���
		break;
	case 3:
		LineEdit(); //�б༭����
		break;
	case 4:
		maze(); //�Թ����
		break;
	case 5:
		EvaluateExpression(); //���ʽ��ֵ
	case 6:
		Hanoi(); //Hanoi������
	default:
		break;
	}
}
