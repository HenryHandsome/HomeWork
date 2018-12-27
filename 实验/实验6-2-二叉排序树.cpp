#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef struct {
	int key;       // 关键字成员
	// ...  ...;   // 其余成员不关心
}Record; // 记录类型

typedef struct BSTreeNode {
	Record data;                         // 数结点信息
	struct BSTreeNode *lchild, *rchild;  // 结点左右孩子指针
}BSTreeNode, *BSTree; 


/********************   在二叉排序树T中查找结点关键字为k的结点p（找到返回true，否则false） ********************/
bool Search(BSTree &T, int k, BSTree &f, BSTree &p) {
	if(T == NULL) { // 空树
		p = f;
		return false;
	} else if(k == T->data.key) { // 找到
		p = T;
		return true;
	} else if(k < T->data.key) {
		return Search(T->lchild, k, T, p); // 递归找左子树
	} else {
		return Search(T->rchild, k, T, p); // 递归找右子树
	} 
}

/********************   在二叉排序树T中插入新结点（关键字为k） ********************/
void Insert(BSTree &T, int k) { 
	BSTreeNode *f=NULL, *p, *s;
	if(Search(T, k, f, p) == false) { // 未找到结点k
		s = (BSTree)malloc(sizeof(BSTreeNode)); // 创建新结点
		s->data.key = k;
		s->lchild = s->rchild = NULL;
		if(p == NULL) { // 首次插入
			T = s;
		} else if(k < p->data.key) { // 作为左孩子插入
			p->lchild = s;
		} else {
			p->rchild = s; // 作为右孩子插入
		}
	}else{ // 不允许插入重复结点
		printf("\nERROR：关键字 %d 已在树中存在，放弃插入！", k);
	}
}

/********************   中序遍历二叉排序树T ********************/
void InOrder(BSTree T)  {   
	if(T == NULL) 
		return; 
	InOrder(T->lchild);   
    printf ("%-4d", T->data.key); 
    InOrder(T->rchild);   
}

/********************   产生n个小于n的不重复的随机整数构成的数组a ********************/
void InitRandomNums(int* &a, int n) {
	int r;
	a = (int *)malloc(n * sizeof(int)); // 为数组分配空间

	srand(time(0)); // 初始化随机数种子（保证后面每次产生的随机数不一样）
	for(int i=0; i<n ;i++) {
 DO:	r = rand() % n; // 生成0至n-1的随机数
		for(int k=0; k<=i; k++) { // 扫描之前已生成的数
			if(r == a[k]) // 重复则继续生成
				goto DO;
		}
		a[i] = r;
		printf("%-4d", r);
	}
}


void main() {
	int *a, n=10;
	BSTree T=NULL;
	
	printf("%d 个不重复的随机数：", n);
	InitRandomNums(a, n);
	
	for(int i=0; i<n; i++) {
		Insert(T, a[i]);
	}

	printf("\n中序遍历二叉排序树T：");
	InOrder(T);
	printf("\n");
}
