#include<iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define INFEASIBLE -1
typedef int Status;


/*     二叉树定义    */

typedef char TElemType;
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


/***************                 顺序栈                       **********/

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef BiTree SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}

Status StackEmpty(SqStack &S)
{
	if (S.top == S.base)
		return OK;
	else
		return ERROR;
}


/******************                                    单链队列                      *******************/

typedef BiTree QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{
	Q.rear = Q.front = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue &Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}
Status DeQueue(LinkQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear) return ERROR;
	QueuePtr p;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}


Status QueueEmpty(LinkQueue &Q)
{
	if (Q.front == Q.rear)
		return OK;
	else
		return ERROR;
}


/***************                  二叉树                   ******************/

Status CreateBiTree(BiTree &T)
{
	char ch;
	cin >> ch;
	if (ch == '#')
		T = NULL;
	else
	{
		T = (BiTNode *)malloc(sizeof(BiTNode));
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}


Status InOrderTraverse(BiTree T)
{
	SqStack S;
	InitStack(S);
	BiTree p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			cout << p->data;
			p = p->rchild;
		}
	}
	return OK;
}

void PostOrder(BiTree T)
{
	if (T)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout << T->data;
	}
}


void LevelOrder(BiTree T)
{
	if (T)
	{
		LinkQueue Q;
		InitQueue(Q);
		EnQueue(Q, T);
		while (!QueueEmpty(Q))
		{
			BiTree p;
			DeQueue(Q, p);
			cout << p->data;
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
		}
		DestroyQueue(Q);
	}
}


int main()
{
	BiTree T;
	CreateBiTree(T);
	cout << "中序遍历：";
	InOrderTraverse(T);
	cout << endl << "后序遍历：";
	PostOrder(T);
	cout << endl << "层序遍历：";
	LevelOrder(T);
	cout << endl;
	return 0;
}