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
	char stuCode[20];		// 학번
	char name[20];			// 이름
	unsigned char score[3]; // 0번지 국어 1번지 수학 2번지 영어
	int sum;				// 합계
	double ave;				// 평균
}score;

void Menu()
{
	printf("1. 자동 추가\n");
	printf("2. 선택 추가\n");
	printf("3. 선택 삭제\n");
	printf("4. 말단 삭제\n");
	printf("P. 출     력\n");
	printf("Q. 종     료\n");
}
void AutoAdd();									//1번 메뉴
char* AddSelectedPosition(int pos);				//2번 메뉴
char* DeleteSelectedPosition(int pos);			//3번 메뉴
char* DeleteLastPosition();						//4번 메뉴
void PrintInformation();						//p번 메뉴

score RandomGenerator();								//학생들의 정보를 랜덤으로 생성해주는 함수
score* Resize(int size);						//size 크기로 재할당 및 내용 복사

score* mgStu = NULL;	//학생들 정보를 저장할 공간
int numOfP = 0;			//현재까지 저장되어 있는 사람 수
int totalSize = 10;		// 배열의 최대사이즈

void main()
{
	mgStu = (score*)malloc(sizeof(score) * totalSize);		// 배열 동적할당 첫사이즈 10, 학생들 정보 관리 
	int flag = TRUE;										// 무한반복 flag
	srand(time(NULL));										// 시드값 변경 - 랜덤함수를 위한

	while (flag)											// 무한 반복 - 나중에 q가 입력되는 경우만 FALSE
	{
		Menu();												// 메뉴 출력
		DRAWSINGLELINE;
		printf("메  뉴  선  택 -> ");
		char choice;										// 메뉴 입력 변수
		char* deletedName;					// 선택 삭제의 경우 어떤 이름이 삭제되는지 받기 위해서
		char* insertedName;
		int inputNum;
		scanf(" %c", &choice);
		DRAWDOUBLELINE;
		switch (choice)
		{
		case '1':
			printf("몇 명의 사람을 입력할까요?\n(1~10 만 입력이 됩니다. \n그외에는 1명만 입력됩니다) -> ");
			scanf(" %d", &inputNum);
			inputNum = (inputNum > 0 && inputNum < 11) ? inputNum : 1;
			printf("%d 명의 학생의 정보를 자동생성합니다.\n", inputNum);
			DRAWSINGLELINE;							//1~10 사이만 들어가고, 그 이외의 숫자의 경우에는 강제로 1로 세팅

			for (int i = 0; i < inputNum; i++)
				AutoAdd();
			DRAWDOUBLELINE;
			break;
		case '2':
			printf("몇 번 인덱스의 사람을 추가할까요?\n(인덱스 바깥쪽이 입력되는 경우, 0번에 사람이 추가됩니다.) ->");
			scanf(" %d", &inputNum);
			inputNum = (inputNum >= 0 && inputNum < numOfP) ? inputNum : 0;
			//1~NumOfP 사이만 들어가고, 그 이외의 숫자의 경우에는 강제로 1로 세팅

			insertedName = AddSelectedPosition(inputNum);

			printf("%d 번, %s의 성적표를 추가하였습니다.\n", inputNum, insertedName);
			DRAWDOUBLELINE;
			break;
		case '3':
			printf("몇 번 인덱스의 사람을 삭제할까요?\n(인덱스 바깥쪽이 입력되는 경우, 0번이 삭제됩니다.) ->");
			scanf(" %d", &inputNum);
			inputNum = (inputNum >= 0 && inputNum < numOfP) ? inputNum : 0;
			//1~NumOfP 사이만 들어가고, 그 이외의 숫자의 경우에는 강제로 1로 세팅

			deletedName = DeleteSelectedPosition(inputNum);

			printf("%d 번, %s의 성적표를 삭제하였습니다.\n", inputNum, deletedName);
			DRAWDOUBLELINE;
			break;
		case '4':
			deletedName = DeleteLastPosition();	// 맨 마지막 사람의 이름을 받아옴
			printf("%d번, %s의 성적표를 삭제하였습니다.\n", numOfP, deletedName);
			free(deletedName);
			DRAWDOUBLELINE;
			break;

		case 'P': case 'p':
			printf("성적표를 출력합니다.\n");
			DRAWSINGLELINE;
			PrintInformation();
			DRAWDOUBLELINE;
			break;

		case 'Q': case 'q':
			flag = FALSE;
			printf("프로그램을 종료합니다.\n");
			break;

		default:
			printf("다시 입력하시오!!\n");
			DRAWDOUBLELINE;
		}
	}
}


void AutoAdd()
{
	if (numOfP == totalSize)
	{
		mgStu = Resize(totalSize + 10);
	}

	score temp = RandomGenerator();
	printf(" %s : %s 학생의 성적이 입력되었습니다.\n", temp.stuCode, temp.name);

	mgStu[numOfP++] = temp;
}


// 해당 포지션 삽입
char* AddSelectedPosition(int pos)
{
    if (numOfP == totalSize)
    {
        score* temp = mgStu;
        mgStu = Resize(totalSize+10);
        free(temp);
    }

    for (int i = numOfP ; i > pos ; i-- ) // 해당 위치에 삽입할 공간을 만들기 위해 뒤쪽 요소를 하나씩 뒤로 이동
    {
        mgStu[i] = mgStu[i-1];
    }

    mgStu[pos] = RandomGenerator();  // 해당 위치에 새로 생성한 데이터를 삽입
    numOfP++;

    return mgStu[pos].name;  // 새로 삽입한 학생의 이름을 반환
}

// 해당 포지션 삭제
char* DeleteSelectedPosition(int pos)
{
    char* deletedName = (char*)malloc(strlen(mgStu[pos].name) + 1);
    strcpy(deletedName, mgStu[pos].name);  // 삭제할 학생의 이름 저장

    for (int i = pos ; i < numOfP-1 ; i++  )  // 해당 위치부터 뒷 요소를 앞으로 이동
    {
        mgStu[i] = mgStu[i+1];
    }

    numOfP--;  // 학생 수 감소
    return deletedName;  // 삭제한 학생의 이름 반환
}

// 마지막 삭제
char* DeleteLastPosition()
{
    if (numOfP == 0)  // 저장된 학생이 없으면 NULL 반환
        return NULL;

    char* deletedName = (char*)malloc(strlen(mgStu[numOfP-1].name) + 1);
    strcpy(deletedName, mgStu[numOfP-1].name);  // 삭제할 학생의 이름 저장

    numOfP--;  // 학생 수 감소

    return deletedName;  // 삭제한 학생의 이름 반환
}


void PrintInformation()
{
	printf("%5s. %10s : %10s %7s %7s %7s %7s %7s\n"
		, "순서", "학번", "이름", "국어", "수학", "영어", "총점", "평균");
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


//Realloc 쓰지 않기
score* Resize(int size)
{
	totalSize = size;
	score* temp;		 // size만큼 늘어있어야 하고, mgStu에 있는 정보가 다 들어가 있어야함
	// malloc만 사용해야함
	// temp 라고 하는 공간에 size 만큼의 공간을 생성합니다, 동적할당

	// mgStu[0] >> temp[0]
	// mgStu[1] >> temp[1] ...
	// num0fP-1 까지 복사

	temp = (score*)malloc(sizeof(score) * size);
	for (int i = 0; i < numOfP; i++)
		temp[i] = mgStu[i];


	return temp;
}