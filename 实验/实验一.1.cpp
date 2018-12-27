#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
typedef int Status;



#include<iostream>
using namespace std;


typedef struct Node{                //单链表
	int data;                       //结点自身信息
	struct Node *next;              //后继结点的指针
}LNode, *LinkList;                  //2个类型别名，分别代表链表中的结点，指向指针的结点


									/******** 创建表⻓长为n 的单链表L，n 个元素的值存于数组values 中 *********/
LinkList Creat_LinkList(int n)
{
	LinkList head, tail, p;
	int x;
	head = tail = (LinkList)malloc(sizeof(LNode));
	for (int i = 1; i <= n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));
		cin >> x;
		p->data = x;
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return head;
}


Status ListInsert_L(LinkList &L, int i, int e)
{
	LinkList p = L, s;
	int j = 0;
	while (p&&j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}


Status GetElem_L(LinkList L, int i,int &e)
{
	LinkList p;
	int j = 1;
	p = L->next;
	while (p&&j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}


Status ListDelete_L(LinkList L, int i, int &e)
{
	LinkList p = L;
	int j = 0;
	while (p->next&&j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i - 1)
		return ERROR;
	LinkList q;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}


int main()
{
	LinkList L;
	int n;
	cout << "要创建的链表长度：";
	cin >> n;
	L = Creat_LinkList(n);
	LinkList p;
	p = L;
	cout << "表L中的内容：";
	while (p->next != NULL)
	{
		p = p->next;
		cout << p->data << ",";
	}
	cout << endl;

	int e, i;
	cout << "输入插入的位置和数据：";
	cin >> i >> e;
	ListInsert_L(L, i, e);
	p = L;
	cout << "表L中的内容：";
	while (p->next != NULL)
	{
		p = p->next;
		cout << p->data << ",";
	}
	cout << endl;

	cout << "输入要查找的元素的位置：";
	cin >> i;
	GetElem_L(L, i, e);
	cout << "所查找的数据为：" << e << endl;

	cout << "输入要删除的数据的位置：";
	cin >> i;
	ListDelete_L(L, i, e);
	cout << "所删除的数据是：" << e << endl;
}