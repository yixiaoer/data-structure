#include <stdio.h>
#include <stdlib.h>
#define TRUE 1 //预定义常量和类型
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10   //存储空间分配量
#define N 11				//这一部分是对于地图填色问题的一些常量定义

typedef int Status; //状态代码用数字来表示
typedef int SElemType;
typedef char SElemType1;
typedef int PosType;

typedef struct
{
	SElemType *base; //栈底元素的指针，在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;  //栈顶元素的指针
	int stacksize;   //当前已分配的储存空间，以元素为单位
} SqStack;

/*=========================================================
首先要有对栈的各种操作吖
用数组来存储栈
==========================================================*/
Status InitStack(SqStack *S);			//构造一个空栈
Status DestoryStack(SqStack *S);		//删除一个栈
Status ClearStack(SqStack *S);			//清空一个栈
Status StackEmpty(SqStack S);			//若栈S为空栈则返回TRUE，否则返回FALSE
Status GetTop(SqStack S, SElemType *e); //得到栈顶元素
int StackLength(SqStack S);				//得到栈的长度
Status Pop(SqStack *S, SElemType *e);   //若栈不空，删除栈顶元素，用e返回其值，并返回OK，否则返回ERROR
Status Pop1(SqStack *S, SElemType1 *e);
Status Push(SqStack *S, SElemType e);				//插入元素e为新的栈顶元素
Status StackTraverse(SqStack S, Status (*visit)()); //从栈底到栈顶一次对栈中每个元素调用函数visit()。一旦visit()失败，则操作失败
void visit(SqStack S);

void conversion(int num, int numN); //数制转换
void paren();						//括号匹配的检验
void LineEdit();					//行编辑程序
void EvaluateExpression();			//表达式求值
void Hanoi();						//Hanoi塔过程