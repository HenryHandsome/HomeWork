#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef struct {
	int key;       // �ؼ��ֳ�Ա
	// ...  ...;   // �����Ա������
}Record; // ��¼����

typedef  struct {
	Record *elem;   // ��¼����
	int length;     // ��¼����
}SqList;


/***********  �۰������˳��������в��ҹؼ���k������λ�� ***********/
int BinarySearch(SqList L, int k,int &sum) {
	int low = 1, high = L.length, mid; // ������������½�, �Ͻ�, �м�λ��

	while (low <= high) {    // �����СΪ������
		sum++;
		mid = (low + high) / 2;
		if (k < L.elem[mid].key)
			high = mid - 1;  // ����������������
		else if (k > L.elem[mid].key)
			low = mid + 1;   // ���Ұ������������ 
		else
			return mid; // �ҵ�������λ��
	}
	return 0; // �Ҳ���
}

/***********  ��ʼ������Ϊlength˳������� ***********/
void InitAscendList(SqList &L, int length) {
	L.elem = (Record *)malloc((length + 1) * sizeof(Record)); // �����һ����0�±겻�ã�
	L.length = length;

	srand(time(0)); // ��ʼ����������ӣ���֤����ÿ�β������������һ����
	L.elem[1].key = rand() % 10; // �׸�ֵ
	for (int i = 2; i <= L.length; i++) {
		L.elem[i].key = L.elem[i - 1].key + rand() % 10 + 1; // �����ɸ�ֵ
	}
}

/***********  ��ӡ˳��� ***********/
void PrintList(SqList L) {
	printf("\n");
	for (int i = 1; i <= L.length; i++) {
		printf("%-4d", L.elem[i].key);
	}
	printf("\n");
}

void main() {
	int sum = 0;
	SqList L;
	int k, i;
	InitAscendList(L, 80);
	PrintList(L);

	printf("����Ҫ���ҵĹؼ���: ");
	scanf("%d", &k);

	i = BinarySearch(L, k, sum);
	if (i == 0)
		printf("δ�ҵ�\n");
	else
		printf("�ҵ���λ��Ϊ%d\n", i);
	printf("�Ƚϴ�����%d\n", sum);
}