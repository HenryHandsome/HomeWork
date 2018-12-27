#include<iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define INFEASIBLE -1
typedef int Status;


/*                邻接表                */

#define MAX_VERTEX_NUM 20
typedef char VertexType;

typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode {
	VertexType data;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;


void PrintALGraph(ALGraph G)
{
	cout << "各顶点对应序号：" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << "元素：" << G.vertices[i].data << "   序号：" << i << endl;
	}
}


Status Create(ALGraph &G)
{
	cout << "请输入顶点数、边数：";
	cin >> G.vexnum >> G.arcnum;
	cout << "请输入各顶点元素：";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	PrintALGraph(G);
	for (int k = 0; k < G.arcnum; k++)
	{
		cout << "请输入（v1，v2）的顶点序号：";
		int i, j;
		cin >> i >> j;
		ArcNode *p1, *p2;
		p1 = (ArcNode *)malloc(sizeof(ArcNode));
		p2 = (ArcNode *)malloc(sizeof(ArcNode));
		p1->adjvex = j;
		p2->adjvex = i;
		p1->nextarc = G.vertices[i].firstarc;
		p2->nextarc = G.vertices[j].firstarc;
		G.vertices[i].firstarc = p1;
		G.vertices[j].firstarc = p2;
	}
	return OK;
}




/*           孩子兄弟链表         */

typedef char CSType;

typedef struct CSNode {
	CSType data;
	struct CSNode *lchild;
	struct CSNode *nextsibling;
}CSNode, *CSTree;

void PreOrder(CSTree T)
{
	if (T)
	{
		cout << T->data << "，";
		PreOrder(T->lchild);
		PreOrder(T->nextsibling);
	}
}

/*      深度优先生成树     */

bool visited[20];


int NextAdjVex(ALGraph G, int v, int w)
{
	ArcNode *p;
	p = G.vertices[v].firstarc;
	while (p)
	{
		if (p->adjvex == w)
		{
			if (p->nextarc)
				return p->nextarc->adjvex;
			else
				p = p->nextarc;
		}
		else
			p = p->nextarc;
	}
	return -1;
}


void DFSTree(ALGraph G, int v, CSTree &T)
{
	visited[v] = TRUE;
	bool first = TRUE;
	CSTree q = T;
	for (int w = G.vertices[v].firstarc->adjvex; w >= 0; w = NextAdjVex(G, v, w))
	{
		if (!visited[w])
		{
			CSTree p;
			p = (CSTree)malloc(sizeof(CSNode));
			p->data = G.vertices[w].data; 
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (first)
			{
				T->lchild = p;
				first = FALSE;
			}
			else
				q->nextsibling = p;
			q = p;
			DFSTree(G, w, q);
		}
	}
}

void DFSForest(ALGraph G, CSTree &T)
{
	T = NULL;
	CSTree q = T;
	for (int v = 0; v < G.vexnum; v++)
	{
		visited[v] = FALSE;
	}
	for (int v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
		{
			CSTree p;
			p = (CSTree)malloc(sizeof(CSNode));
			p->data = G.vertices[v].data;
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (!T)
				T = p;
			else
				q->nextsibling = p;
			q = p;
			DFSTree(G, v, p);
		}
	}
}

int main()
{
	ALGraph G;
	Create(G);
	CSTree T;
	DFSForest(G, T);
	cout << "先序遍历结果：";
	PreOrder(T);
	cout << endl;
	return 0;
}