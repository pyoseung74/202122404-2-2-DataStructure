#include <stdio.h>
#include <string.h>

typedef struct
{
	char data[200];
	int front;
	int rear;
} queue;

queue CreateQ();
void EnQ(char a, queue* Q);
char DeQ(queue* Q);
char Peek(queue Q);
int IsEmpty(queue Q);

int main()
{
    queue NQ = CreateQ();
    char equation[100] = "5759+787-2124+575";

    for (int i = 0; i < strlen(equation); i++)
    {
        EnQ(equation[i], &NQ);
    }

    int num = 0;
    int sum = 0;
    char operation = '+';

    while (IsEmpty(NQ) == 0)
    {
        char temp = DeQ(&NQ);
        
        if (temp >= '0' && temp <= '9')
        {
            num = num * 10 + (temp - '0');
        }
        else
        {
            if (operation == '+')
                sum += num;
            else if (operation == '-')
                sum -= num;

            operation = temp;
            num = 0;
        }
    }
    
    if (operation == '+')
        sum += num;
    else if (operation == '-')
        sum -= num;

    printf("Result: %d\n", sum);
    return 0;
}

queue CreateQ()
{
	queue newQ;
	newQ.front = -1;
	newQ.rear = -1;
	return newQ;
}

void EnQ(char a, queue* Q)
{
	Q->data[++(Q->rear)] = a;
}

char DeQ(queue* Q)
{
	if (IsEmpty(*Q))
		return Q->data[++(Q->front)];
	else
		return -1;
}

char Peek(queue Q)
{
	if (IsEmpty(Q))
		return -1;
	else
		return Q.data[Q.front + 1];
}

int IsEmpty(queue Q)
{
	return Q.front == Q.rear;
}
