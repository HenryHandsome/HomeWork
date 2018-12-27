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
typedef int ElemType;

#define MAXSIZE 100
typedef struct {
	int i, j;
	ElemType e;
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;

Status PrintTSMatrix(TSMatrix &M)
{
	if (!M.tu) return ERROR;
	int k = 1;
	for (int i = 1; i <= M.mu; i++)
	{
		for (int j = 1; j <= M.nu; j++)
		{
			if (M.data[k].i == i && M.data[k].j == j)
			{
				cout << M.data[k].e;
				k++;
			}
			else
				cout << 0;
			cout << " ";
		}
		cout << endl;
	}
	return OK;
}

Status CreatTSMatrix(TSMatrix &M)
{
	cout << "矩阵期望规格行数不少于8，列数不少于12，非零元个数不多于100" << endl;
	cout << "行：";
	cin >> M.mu;
	cout << "列：";
	cin >> M.nu;
	cout << "非零元个数：";
	cin >> M.tu;
	srand(time(NULL));
	int m[110][110] = { 0 };
	for (int k = 1; k <= M.tu; k++)
	{
		int i = rand() % M.mu + 1;
		int j = rand() % M.nu + 1;
		if (m[i][j] == 0)
			m[i][j] = rand() % 9 + 1;
		else
			k--;
	}
	int k = 1;
	for(int i=1;i<=M.mu;i++)
		for(int j=1;j<=M.nu;j++)
			if (m[i][j] != 0)
			{
				M.data[k].i = i;
				M.data[k].j = j;
				M.data[k].e = m[i][j];
				k++;
			}
	PrintTSMatrix(M);
	return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	int num[110], cpot[110];
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if (!T.tu)
		return ERROR;
	for (int col = 1; col <= M.nu; col++)
		num[col] = 0;
	for (int t = 1; t <= M.tu; ++t)
		num[M.data[t].j]++;
	cpot[1] = 1;
	for (int col = 2; col <= M.nu; col++)
		cpot[col] = cpot[col - 1] + num[col - 1];
	for (int p = 1; p <= M.tu; p++)
	{
		int col = M.data[p].j;
		int q = cpot[col];
		T.data[q].i = M.data[p].j;
		T.data[q].j = M.data[p].i;
		T.data[q].e = M.data[p].e;
		cpot[col]++;
	}
	return OK;
}

int main()
{
	TSMatrix M, T;
	CreatTSMatrix(M);
	FastTransposeSMatrix(M, T);
	cout << "转置后的矩阵为：" << endl;
	PrintTSMatrix(T);
	return 0;
}