#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include<iostream>
using namespace std;

#define MAXSIZE 100
typedef int KeyType;

typedef struct {
	KeyType key;
}RedType;

typedef struct {
	RedType r[MAXSIZE + 1];
	int length;
}SqList;


//����100�������

void InitRandList(SqList &L, int length) {
	L.length = length;
	srand(time(0)); // ��ʼ����������ӣ���֤����ÿ�β������������һ����
	for (int i = 1; i <= L.length; i++) 
	{
		L.r[i].key = (rand() % 110 + 1) % 110; 
	}
}




void PrintSqList(SqList L)
{
	for (int i = 1; i <= L.length; i++)
	{
		printf("%-4d", L.r[i].key);
		if (i % 10 == 0)
			cout << endl;
	}
	cout << endl;
}


//ֱ�Ӳ�������

int InsertSort(SqList &L)
{
	int sum = 0;
	for (int i = 2; i <= L.length; i++)
	{
		if (L.r[i].key < L.r[i - 1].key)
		{
			L.r[0] = L.r[i];
			L.r[i] = L.r[i - 1];
			int j;
			for (j = i - 2; L.r[0].key < L.r[j].key; j--)
			{
				L.r[j + 1] = L.r[j];
				sum++;
			}
			sum++;
			L.r[j + 1] = L.r[0];
		}
		sum++;
	}
	return sum;
 }

//ϣ������

int ShellInsert(SqList &L, int dk)
{
	int sum = 0;
	int i, j;
	for (i = dk + 1; i <= L.length; i++)
	{
		if (L.r[i].key < L.r[i - dk].key)
		{
			L.r[0] = L.r[i];
			for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)
			{
				L.r[j + dk] = L.r[j];
				sum++;
			}
 			sum++;
			L.r[j + dk] = L.r[0];
		}
		sum++;
	}
	return sum;
}

int ShellSort(SqList &L, int dita[], int t)
{
	int sum = 0;
	for (int k = 0; k < t; k++)
	{
		sum += ShellInsert(L, dita[k]);
	}
	return sum;
}



//��������

int Partition(SqList &L, int low, int high,int &sum)
{
	L.r[0] = L.r[low];
	KeyType pivotkey = L.r[low].key;
	while (low < high)
	{
		while (low < high&&L.r[high].key >= pivotkey)
		{
			high--;
			sum++;
		}
		if (low < high)
			L.r[low++] = L.r[high];
		while (low < high&&L.r[low].key <= pivotkey)
		{
			low++;
			sum++;
		}
		if (low < high)
			L.r[high--] = L.r[low];
	}
	L.r[low] = L.r[0];
	return low;
}

int QSort(SqList &L, int low, int high)
{
	int sum = 0;
	if (low < high)
	{
		int pivotloc = Partition(L, low, high, sum);
		sum += QSort(L, low, pivotloc - 1);
		sum += QSort(L, pivotloc + 1, high);
	}
	return sum;
}



//�鲢����

int Merge(RedType SR[], RedType TR[], int i, int m, int n)
//�������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i...m]
{
	int sum = 0;
	int j, k;
	for (j = m + 1, k = i; i <= m && j <= n; k++)
	{
		if (SR[i].key <= SR[j].key)
		{
			TR[k] = SR[i++];
		}
		else
		{
			TR[k] = SR[j++];
		}
		sum++;
	}
	while (i <= m)
		TR[k++] = SR[i++];
	while (j <= n)
		TR[k++] = SR[j++];
	return sum;
}

int MSort(RedType p1[], RedType p2[], int n, int l)
{
	int sum = 0;
	int i = 1, j;
	while (i + 2 * l - 1 <= n)
	{
		sum += Merge(p1, p2, i, i + l - 1, i + 2 * l - 1);
		i = i + 2 * l;
	}
	if (i + l <= n)
	{
		sum += Merge(p1, p2, i, i + l - 1, n);
	}
	else
	{
		for (j = i; j <= n; j++)
		{
			p2[j] = p1[j];
		}
	}
	return sum;
}

int MergeSort(SqList &L)
{
	int sum = 0;
	int l = 1;
	RedType s[110];
	while (l < L.length)
	{
		sum += MSort(L.r, s, L.length, l);
		l *= 2;
		sum += MSort(s, L.r, L.length, l);
		l *= 2;
	}
	return sum;
}


int main()
{
	SqList L;
	InitRandList(L, 100);
	cout << "������ɵ�˳�������ݣ�" << endl;
	PrintSqList(L);
	SqList L1, L2, L3, L4;
	L1 = L;
	L2 = L;
	L3 = L;
	L4 = L;
	int dita[10] = { 23,19,17,13,11,7,5,3,2,1 };
	cout << "ֱ�Ӳ�������ıȽϴ�����";
	cout << InsertSort(L1) << endl;
	cout << "�����˳����е����ݣ�" << endl;
	PrintSqList(L1);
	cout << "ϣ������ıȽϴ�����";
	cout << ShellSort(L2, dita, 10) << endl;
	cout << "�����˳����е����ݣ�" << endl;
	PrintSqList(L2);
	cout << "��������ıȽϴ�����";
	cout << QSort(L3, 1, L.length) << endl;
	cout << "�����˳����е����ݣ�" << endl;
	PrintSqList(L3);
	cout << "�鲢����ıȽϴ�����";
	cout << MergeSort(L4) << endl;
	cout << "�����˳����е����ݣ�" << endl;
	PrintSqList(L4);
}