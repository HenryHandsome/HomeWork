#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef struct {
	int key;       // �ؼ��ֳ�Ա
	// ...  ...;   // �����Ա������
}Record; // ��¼����

typedef struct BSTreeNode {
	Record data;                         // �������Ϣ
	struct BSTreeNode *lchild, *rchild;  // ������Һ���ָ��
}BSTreeNode, *BSTree; 


/********************   �ڶ���������T�в��ҽ��ؼ���Ϊk�Ľ��p���ҵ�����true������false�� ********************/
bool Search(BSTree &T, int k, BSTree &f, BSTree &p) {
	if(T == NULL) { // ����
		p = f;
		return false;
	} else if(k == T->data.key) { // �ҵ�
		p = T;
		return true;
	} else if(k < T->data.key) {
		return Search(T->lchild, k, T, p); // �ݹ���������
	} else {
		return Search(T->rchild, k, T, p); // �ݹ���������
	} 
}

/********************   �ڶ���������T�в����½�㣨�ؼ���Ϊk�� ********************/
void Insert(BSTree &T, int k) { 
	BSTreeNode *f=NULL, *p, *s;
	if(Search(T, k, f, p) == false) { // δ�ҵ����k
		s = (BSTree)malloc(sizeof(BSTreeNode)); // �����½��
		s->data.key = k;
		s->lchild = s->rchild = NULL;
		if(p == NULL) { // �״β���
			T = s;
		} else if(k < p->data.key) { // ��Ϊ���Ӳ���
			p->lchild = s;
		} else {
			p->rchild = s; // ��Ϊ�Һ��Ӳ���
		}
	}else{ // ����������ظ����
		printf("\nERROR���ؼ��� %d �������д��ڣ��������룡", k);
	}
}

/********************   �����������������T ********************/
void InOrder(BSTree T)  {   
	if(T == NULL) 
		return; 
	InOrder(T->lchild);   
    printf ("%-4d", T->data.key); 
    InOrder(T->rchild);   
}

/********************   ����n��С��n�Ĳ��ظ�������������ɵ�����a ********************/
void InitRandomNums(int* &a, int n) {
	int r;
	a = (int *)malloc(n * sizeof(int)); // Ϊ�������ռ�

	srand(time(0)); // ��ʼ����������ӣ���֤����ÿ�β������������һ����
	for(int i=0; i<n ;i++) {
 DO:	r = rand() % n; // ����0��n-1�������
		for(int k=0; k<=i; k++) { // ɨ��֮ǰ�����ɵ���
			if(r == a[k]) // �ظ����������
				goto DO;
		}
		a[i] = r;
		printf("%-4d", r);
	}
}


void main() {
	int *a, n=10;
	BSTree T=NULL;
	
	printf("%d �����ظ����������", n);
	InitRandomNums(a, n);
	
	for(int i=0; i<n; i++) {
		Insert(T, a[i]);
	}

	printf("\n�����������������T��");
	InOrder(T);
	printf("\n");
}
