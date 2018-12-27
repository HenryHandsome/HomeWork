#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define INFEASIBLE -1

typedef int Status;
typedef int QElemType;

#define MAXQSIZE 100
typedef struct {
	QElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}

Status EnQueue(SqQueue &Q, QElemType e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue &Q, QElemType e)
{
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}

Status PrintQueue(SqQueue Q)
{
	if (Q.front == Q.rear)
	{
		cout << "队列空，请先入队！" << endl;
		return ERROR;
	}
	cout << "队列中的元素为：";
	for (int i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE)
	{
		cout << Q.base[i] << " ";
	}
	cout << endl;
	return OK;
}

int main()
{
	SqQueue Q;
	InitQueue(Q);
	int num = 0;
	while (TRUE)
	{
		cout << "输入1入队，输入2出队，输入0退出：";
		int choose;
		cin >> choose;
		if (choose == 0)
			break;
		else if (choose == 1)
		{
			EnQueue(Q, ++num);
			PrintQueue(Q);
		}
		else if (choose == 2)
		{
			DeQueue(Q, choose);
			PrintQueue(Q);
		}
		else
			cout << "输入错误请重新输入！" << endl;
	}
}