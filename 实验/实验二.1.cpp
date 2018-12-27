#include<iostream>
#include<String>
using namespace std;

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define INFEASIBLE -1

typedef int Status;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}

Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}

int main()
{
	cout << "ÇëÊäÈëÒªÆ¥ÅäµÄ×Ö·û£º";
	string s;
	cin >> s;
	SqStack S;
	InitStack(S);
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '[' || s[i] == '{' || s[i] == '(')
			Push(S, s[i]);
		else
		{
			char c;
			GetTop(S, c);
			if ((c == '['&&s[i] == ']') || (c == '('&&s[i] == ')') || (c == '{'&&s[i] == '}'))
				Pop(S, c);
			else
			{
				cout << "Æ¥ÅäÊ§°Ü£¡" << endl;
				break;
			}
		}
		if (i == s.length() - 1 )
		{
			if (S.base != S.top)
				cout << "Æ¥ÅäÊ§°Ü£¡" << endl;
			else
				cout << "Æ¥Åä³É¹¦£¡" << endl;
		}
	}
}