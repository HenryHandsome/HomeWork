#include<iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define INFEASIBLE -1
typedef int Status;


/*  链表  */


typedef int QElemType;

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


/*               有向图邻接矩阵               */

#define MAX_VERTEX_NUM 20
typedef int VRType;
typedef int VertexType;

typedef struct ArcCell {
	VRType adj;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
}MGraph;

int Locate(MGraph &G, VRType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v)
			return i;
	}
	return -1;
 }

int FirstAdjVex(MGraph &G, int v)
{
	int i = v;
	for (int j = 0; j < G.vexnum; j++)
	{
		if (G.arcs[i][j].adj == 1)
			return i;
	}
	return -1;
}

int NextAdjVex(MGraph &G, int v, int w)
{
	int i = v;
	for (int j = w + 1; j < G.vexnum; j++)
	{
		if (G.arcs[i][j].adj == 1)
			return j;
	}
	return -1;
}

Status Create(MGraph &G)
{
	cout << "输入顶点数、边数：";
	cin >> G.vexnum >> G.arcnum;
	cout << "输入各个顶点信息：";
	for (int i = 0; i < G.vexnum; i++)
		cin >> G.vexs[i];
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j].adj = 0;
	for (int k = 0; k < G.arcnum; k++)
	{
		VRType v1, v2;
		cout << "输入<v1,v2>的信息：";
		cin >> v1 >> v2;
		int i = Locate(G, v1);
		int j = Locate(G, v2);
		G.arcs[i][j].adj = 1;
	}
	return OK;
}

Status BFS(MGraph G)
{
	bool visited[MAX_VERTEX_NUM];
	for (int i = 0; i < G.vexnum; i++)
		visited[i] = FALSE;
	LinkQueue Q;
	InitQueue(Q);
	for (int v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
		{
			visited[v] = TRUE;
			cout << G.vexs[v] << ",";
			EnQueue(Q, v);
			while (!QueueEmpty(Q))
			{
				int u;
				DeQueue(Q, u);
				for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
				{
					if (!visited[w])
					{
						visited[w] = TRUE;
						cout << G.vexs[w] << ",";
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}

int main()
{
	MGraph G;
	Create(G);
	cout << "广度优先搜索结果：";
	BFS(G);
	cout << endl;
	return 0;
}