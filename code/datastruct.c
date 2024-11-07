#include <stdio.h>
#include <string.h>

typedef struct
{
	char data[200];
	int front;
	int rear;
}queue;

queue CreateQ();
void EnQ(char a, queue* Q);
char DeQ(queue* Q);
char Peek(queue* Q);
int IsEmpty(queue Q);

int main() 
{
	// 계산기 작성 과제 
	// 값 입력 받기로 바꾸기
	// 뺄셈기능 추가하기
	queue NQ = CreateQ();
	char equation[100] = "5759+787+2124+575";

	for (int i = 0; i < strlen(equation); i++)
	{
		EnQ(equation[i], &NQ);
	}

	int num = 0;
	int sum = 0;
	while (IsEmpty(NQ)==0)
	{
		char temp = DeQ(&NQ);
		if(temp >= '0' && temp <= '9')
			num = num * 10 + (temp - 32);
		else
		{
			sum += num;
			num = 0;
		}
		printf("%d\n", sum);
	}
	return 0;
}

queue CreateQ()
{
	queue newQ;
	newQ.front = -1;
	newQ.rear = -1;
	newQ.data[0] = 0;

}

void EnQ(char a, queue* Q)
{
	Q->data[++(Q->rear)] = a;
}

char DeQ(queue* Q)
{
	if (!IsEmpty(*Q))
		return -1;
	else
		return Q->data[++(Q->front)];
}

char Peek(queue Q)
{
	if (IsEmpty(Q))
		return -1;
	else
		return Q.data[++(Q.front + 1)];
}