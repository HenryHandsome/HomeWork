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


//生成100个随机数

void InitRandList(SqList &L, int length) {
	L.length = length;
	srand(time(0)); // 初始化随机数种子（保证后面每次产生的随机数不一样）
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


//直接插入排序

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

//希尔排序

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



//快速排序

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



//归并排序

int Merge(RedType SR[], RedType TR[], int i, int m, int n)
//将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...m]
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
	cout << "随机生成的顺序表的数据：" << endl;
	PrintSqList(L);
	SqList L1, L2, L3, L4;
	L1 = L;
	L2 = L;
	L3 = L;
	L4 = L;
	int dita[10] = { 23,19,17,13,11,7,5,3,2,1 };
	cout << "直接插入排序的比较次数：";
	cout << InsertSort(L1) << endl;
	cout << "排序后顺序表中的数据：" << endl;
	PrintSqList(L1);
	cout << "希尔排序的比较次数：";
	cout << ShellSort(L2, dita, 10) << endl;
	cout << "排序后顺序表中的数据：" << endl;
	PrintSqList(L2);
	cout << "快速排序的比较次数：";
	cout << QSort(L3, 1, L.length) << endl;
	cout << "排序后顺序表中的数据：" << endl;
	PrintSqList(L3);
	cout << "归并排序的比较次数：";
	cout << MergeSort(L4) << endl;
	cout << "排序后顺序表中的数据：" << endl;
	PrintSqList(L4);
}