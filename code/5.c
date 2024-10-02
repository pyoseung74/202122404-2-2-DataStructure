#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DRAWSINGLELINE printf("-----------------------------------------------------------------------------------\n")
#define DRAWDOUBLELINE printf("===================================================================================\n")
#define RANGEN(a)  ((int)rand() % a)
#define TRUE 1
#define FALSE 0

typedef struct {
	char stuCode[20];		// �й�
	char name[20];			// �̸�
	unsigned char score[3]; // 0���� ���� 1���� ���� 2���� ����
	int sum;				// �հ�
	double ave;				// ���
}score;

void Menu()
{
	printf("1. �ڵ� �߰�\n");
	printf("2. ���� �߰�\n");
	printf("3. ���� ����\n");
	printf("4. ���� ����\n");
	printf("P. ��     ��\n");
	printf("Q. ��     ��\n");
}
void AutoAdd();									//1�� �޴�
char* AddSelectedPosition(int pos);				//2�� �޴�
char* DeleteSelectedPosition(int pos);			//3�� �޴�
char* DeleteLastPosition();						//4�� �޴�
void PrintInformation();						//p�� �޴�

score RandomGenerator();								//�л����� ������ �������� �������ִ� �Լ�
score* Resize(int size);						//size ũ��� ���Ҵ� �� ���� ����

score* mgStu = NULL;	//�л��� ������ ������ ����
int numOfP = 0;			//������� ����Ǿ� �ִ� ��� ��
int totalSize = 4;		// �迭�� �ִ������

void main()
{
	mgStu = (score*)malloc(sizeof(score) * 10);		// �迭 �����Ҵ� ù������ 10, �л��� ���� ���� 
	int flag = TRUE;								// ���ѹݺ� flag
	srand(time(NULL));								// �õ尪 ���� - �����Լ��� ����

	while (flag)									// ���� �ݺ� - ���߿� q�� �ԷµǴ� ��츸 FALSE
	{
		Menu();										// �޴� ���
		DRAWSINGLELINE;
		printf("��  ��  ��  �� -> ");
		char choice;								// �޴� �Է� ����
		char* deletedName, insertedName;							// ���� ������ ��� � �̸��� �����Ǵ��� �ޱ� ���ؼ�
		int inputNum;
		scanf(" %c", &choice);
		DRAWDOUBLELINE;
		switch (choice)
		{
		case '1':
			printf("�� ���� ����� �Է��ұ��?\n(1~10 �� �Է��� �˴ϴ�. \n�׿ܿ��� 1�� �Էµ˴ϴ�) -> ");
			scanf(" %d", &inputNum);
			inputNum = (inputNum > 0 && inputNum < 11) ? inputNum : 1;
			printf("%d ���� �л��� ������ �ڵ������մϴ�.\n", inputNum);
			DRAWSINGLELINE;							//1~10 ���̸� ����, �� �̿��� ������ ��쿡�� ������ 1�� ����

			for (int i = 0; i < inputNum; i++)
				AutoAdd();
			DRAWDOUBLELINE;
			break;
		case '2':
			printf("�� �� �ε����� ����� �߰��ұ��?\n(�ε��� �ٱ����� �ԷµǴ� ���, 0���� ����� �߰��˴ϴ�.) ->");
			scanf(" %d", &inputNum);
			inputNum = (inputNum >= 0 && inputNum < numOfP) ? inputNum : 0;
			//1~NumOfP ���̸� ����, �� �̿��� ������ ��쿡�� ������ 1�� ����

			deletedName = DeleteSelectedPosition(inputNum);

			printf("%d ��, %s�� ����ǥ�� �����Ͽ����ϴ�.\n", inputNum, deletedName);
			break;
		case '3':
			printf("�� �� �ε����� ����� �����ұ��?\n(�ε��� �ٱ����� �ԷµǴ� ���, 0���� �����˴ϴ�.) ->");
			scanf(" %d", &inputNum);
			inputNum = (inputNum >= 0 && inputNum < numOfP) ? inputNum : 0;
			//1~NumOfP ���̸� ����, �� �̿��� ������ ��쿡�� ������ 1�� ����

			insertedName = AddSelectedPosition(inputNum);

			printf("%d ��, %s�� ����ǥ�� �����Ͽ����ϴ�.\n", inputNum, insertedName);
			DRAWDOUBLELINE;
			break;
		case '4':
			deletedName = DeleteLastPosition();	// �� ������ ����� �̸��� �޾ƿ�
			printf("%d��, %s�� ����ǥ�� �����Ͽ����ϴ�.\n", numOfP, deletedName);
			free(deletedName);
			DRAWDOUBLELINE;
			break;

		case 'P': case 'p':
			printf("����ǥ�� ����մϴ�.\n");
			DRAWSINGLELINE;
			PrintInformation();
			DRAWDOUBLELINE;
			break;

		case 'Q': case 'q':
			flag = FALSE;
			printf("���α׷��� �����մϴ�.\n");
			break;

		default:
			printf("�ٽ� �Է��Ͻÿ�!!\n");
			DRAWDOUBLELINE;
		}
	}
}


void AutoAdd()
{
	if (numOfP == totalSize)
	{
		score* temp = mgStu;
		mgStu = Resize(totalSize + 10);
		free(mgStu);
	}

	score temp = RandomGenerator();
	printf(" %s : %s �л��� ������ �ԷµǾ����ϴ�.\n", temp.stuCode, temp.name);

	mgStu[numOfP++] = temp;
}


//�ش� ������ ����
char* AddSelectedPosition(int pos)
{

}

//�ش� ������ ����
char* DeleteSelectedPosition(int pos)
{


}

//������ ����
char* DeleteLastPosition()
{
	// ���� ����� num0fP�� ���ڸ� 1 ���� (5->4)
	// 5�� �������� 4������ ����Ǿ��ִ� ������ �α׸� 0���� �ٲٱ�


}


void PrintInformation()
{
	printf("%5s. %10s : %10s %7s %7s %7s %7s %7s\n"
		, "����", "�й�", "�̸�", "����", "����", "����", "����", "���");
	for (int i = 0; i < numOfP; i++)
	{
		DRAWSINGLELINE;
		printf("%5d. %10s : %10s %7d %7d %7d %7d %10.5lf\n"
			, i, mgStu[i].stuCode, mgStu[i].name, mgStu[i].score[0], mgStu[i].score[1], mgStu[i].score[2], mgStu[i].sum, mgStu[i].ave);
	}
}


score RandomGenerator()
{
	score temp;
	temp.sum = 0;

	strcpy(temp.stuCode, "2024");
	for (int i = 0; i < 5; i++)
		temp.stuCode[4 + i] = RANGEN(10) + '0';
	temp.stuCode[9] = 0;

	temp.name[0] = RANGEN(26) + 'A';
	for (int i = 1; i < 5; i++)
		temp.name[i] = RANGEN(26) + 'a';
	temp.name[5] = 0;

	for (int i = 0; i < 3; i++)
	{
		temp.score[i] = RANGEN(101);
		temp.sum += temp.score[i];
	}
	temp.ave = temp.sum / 3.0;

	return temp;
}


//Realloc ���� �ʱ�
score* Resize(int size)
{
	totalSize = size;
	score* temp;		 // size��Ű�� �þ��־�� �ϰ�, mgStu�� �ִ� ������ �� �� �־����
	// malloc�� ����ؾ���
	// temp ��� �ϴ� ������ size ��ŭ�� ������ �����մϴ�, �����Ҵ�
	
	// mgStu[0] >> temp[0]
	// mgStu[1] >> temp[1] ...
	// num0fP-1 ���� ����

	temp = (score*)malloc(sizeof(score) * size);	
	for (int i = 0; i <numOfP; i++)
		temp[i] = mgStu[i];

	
	return temp;
}