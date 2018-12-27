#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef struct {
	int key;       // 关键字成员
	// ...  ...;   // 其余成员不关心
}Record; // 记录类型

typedef  struct {
	Record *elem;   // 记录数组
	int length;     // 记录个数
}SqList;


/***********  折半查找在顺序有序表中查找关键字k，返回位置 ***********/
int BinarySearch(SqList L, int k,int &sum) {
	int low = 1, high = L.length, mid; // 待查找区间的下界, 上界, 中间位置

	while (low <= high) {    // 区间大小为“正”
		sum++;
		mid = (low + high) / 2;
		if (k < L.elem[mid].key)
			high = mid - 1;  // 在左半区间继续查找
		else if (k > L.elem[mid].key)
			low = mid + 1;   // 在右半区间继续查找 
		else
			return mid; // 找到，返回位置
	}
	return 0; // 找不到
}

/***********  初始化长度为length顺序有序表 ***********/
void InitAscendList(SqList &L, int length) {
	L.elem = (Record *)malloc((length + 1) * sizeof(Record)); // 多分配一个（0下标不用）
	L.length = length;

	srand(time(0)); // 初始化随机数种子（保证后面每次产生的随机数不一样）
	L.elem[1].key = rand() % 10; // 首个值
	for (int i = 2; i <= L.length; i++) {
		L.elem[i].key = L.elem[i - 1].key + rand() % 10 + 1; // 后若干个值
	}
}

/***********  打印顺序表 ***********/
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

	printf("输入要查找的关键字: ");
	scanf("%d", &k);

	i = BinarySearch(L, k, sum);
	if (i == 0)
		printf("未找到\n");
	else
		printf("找到，位置为%d\n", i);
	printf("比较次数：%d\n", sum);
}