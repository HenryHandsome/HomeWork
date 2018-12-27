#include<iostream>
#include<string>
using namespace std;

typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;

typedef string *HuffmanCode;

void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
	int w1 = 100, w2 = 100;
	s1 = 0;
	s2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent != 0)
			continue;
		if (HT[i].weight < w2)
		{
			if (HT[i].weight < w1)
			{
				w2 = w1;
				s2 = s1;
				w1 = HT[i].weight;
				s1 = i;
			}
			else
			{
				w2 = HT[i].weight;
				s2 = i;
			}
		}
	}
}


void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	if (n <= 1) return;
	int m = 2 * n - 1;
	int s1, s2;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HuffmanTree p = HT + 1;
	int i = 1;
	for (; i <= n; ++i, ++p, ++w)
		*p = { (unsigned int)*w,0,0,0 };
	for (; i <= m; ++i, ++p)
		*p = { 0,0,0,0 };
	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HuffmanCode cd = new string[n + 1];
	for (i = 1; i <= n; ++i)
	{
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
				cd[i] = "0" + cd[i];
			else
				cd[i] = "1" + cd[i];
		}
	}
	HC = cd;
}

void PrintHuffmanCode(HuffmanCode HC, int *w, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "权值为 " << w[i] << " 的Huffman编码为：" << HC[i+1] << endl;
	}
}


int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int n;
	int *w;
	cout << "结点数：";
	cin >> n;
	w = new int[n];
	cout << "输入各个结点的权值：";
	for (int i = 0; i < n; i++)
	{
		cin >> w[i];
	}
	HuffmanCoding(HT, HC, w, n);
	PrintHuffmanCode(HC, w, n);
}