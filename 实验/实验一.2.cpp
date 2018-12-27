#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#include<iostream>
using namespace std;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ElemType int

typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList &L)
{
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
	ElemType *newbase;
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length >= L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType *q, *p;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
	ElemType *pa, *pb, *pc;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
	if (!Lc.elem)
		exit(OVERFLOW);
	ElemType *pa_last, *pb_last;
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
		*pc++ = *pb++;
}

int main()
{
	SqList La, Lb, Lc;
	InitList_Sq(La);
	InitList_Sq(Lb);
	int n;
	cout << "La的长度：";
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		ListInsert_Sq(La, i, x);
	}
	cout << "La的内容：";
	for (int i = 1; i <= La.length; i++)
	{
		cout << La.elem[i - 1] << ",";
	}
	cout << endl;

	cout << "Lb的长度：";
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		ListInsert_Sq(Lb, i, x);
	}
	cout << "Lb的内容：";
	for (int i = 1; i <= Lb.length; i++)
	{
		cout << Lb.elem[i - 1] << ",";
	}
	cout << endl;

	MergeList_Sq(La, Lb, Lc);
	cout << "Lc的内容：";
	for (int i = 1; i <= Lc.length; i++)
	{
		cout << Lc.elem[i - 1] << ",";
	}
	cout << endl;
}