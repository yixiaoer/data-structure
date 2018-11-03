#include <stdio.h>
#include <stdlib.h>
#define TRUE 1 //Ԥ���峣��������
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACKINCREMENT 10   //�洢�ռ������
#define N 11				//��һ�����Ƕ��ڵ�ͼ��ɫ�����һЩ��������

typedef int Status; //״̬��������������ʾ
typedef int SElemType;
typedef char SElemType1;
typedef int PosType;

typedef struct
{
	SElemType *base; //ջ��Ԫ�ص�ָ�룬��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;  //ջ��Ԫ�ص�ָ��
	int stacksize;   //��ǰ�ѷ���Ĵ���ռ䣬��Ԫ��Ϊ��λ
} SqStack;

/*=========================================================
����Ҫ�ж�ջ�ĸ��ֲ���߹
���������洢ջ
==========================================================*/
Status InitStack(SqStack *S);			//����һ����ջ
Status DestoryStack(SqStack *S);		//ɾ��һ��ջ
Status ClearStack(SqStack *S);			//���һ��ջ
Status StackEmpty(SqStack S);			//��ջSΪ��ջ�򷵻�TRUE�����򷵻�FALSE
Status GetTop(SqStack S, SElemType *e); //�õ�ջ��Ԫ��
int StackLength(SqStack S);				//�õ�ջ�ĳ���
Status Pop(SqStack *S, SElemType *e);   //��ջ���գ�ɾ��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
Status Pop1(SqStack *S, SElemType1 *e);
Status Push(SqStack *S, SElemType e);				//����Ԫ��eΪ�µ�ջ��Ԫ��
Status StackTraverse(SqStack S, Status (*visit)()); //��ջ�׵�ջ��һ�ζ�ջ��ÿ��Ԫ�ص��ú���visit()��һ��visit()ʧ�ܣ������ʧ��
void visit(SqStack S);

void conversion(int num, int numN); //����ת��
void paren();						//����ƥ��ļ���
void LineEdit();					//�б༭����
void EvaluateExpression();			//���ʽ��ֵ
void Hanoi();						//Hanoi������