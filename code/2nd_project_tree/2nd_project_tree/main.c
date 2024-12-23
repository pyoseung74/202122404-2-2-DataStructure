#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "tree.h"

#define NUM_OP 20      // 총 연산 횟수
#define RAND_STR_LEN 2 // 무작위 문자열 길이 (예: 2글자)

// 무작위 문자열 생성 함수 (영소문자 RAND_STR_LEN개)
void getRandomString(char* buf, int length)
{
    for (int i = 0; i < length; i++)
    {
        buf[i] = 'a' + rand() % 26; // 'a' ~ 'z'
    }
    buf[length] = '\0'; // 문자열 종료
}

// 무작위 순회 타입 얻기 (0 ~ 3)
int getRandomTraverseType()
{
    return rand() % 4; // 0: Pre, 1: In, 2: Post, 3: Level
}

// 무작위 연산(Insert, Delete, Print) 중 하나 선택
// insert=0, delete=1, print=2 로 가정
int getRandomOperation()
{
    return rand() % 3; // 0 or 1 or 2
}

int main()
{
    // 로케일 설정 (Windows에서 한글 메시지가 깨지지 않도록)
    setlocale(LC_ALL, "");

    // 난수 시드 설정
    srand((unsigned)time(NULL));

    // 배열 기반, 연결 리스트 기반 트리 생성
    tree_A* tA = CreateArrayTree();
    tree_LL* tLL = CreateLListTree();

    printf("===== 랜덤 테스트 시작 =====\n");

    for (int i = 0; i < NUM_OP; i++)
    {
        int op = getRandomOperation();
        char tempStr[STRINGSIZE];

        switch (op)
        {
        case 0: // Insert
        {
            getRandomString(tempStr, RAND_STR_LEN);
            printf("[Insert] \"%s\"\n", tempStr);

            InsertNodeA(tA, tempStr);
            InsertNodeLL(tLL, tempStr);

            break;
        }
        case 1: // Delete
        {
            getRandomString(tempStr, RAND_STR_LEN);
            printf("[Delete] \"%s\"\n", tempStr);

            DeleteNodeA(tA, tempStr);
            DeleteNodeLL(tLL, tempStr);

            break;
        }
        case 2: // Print
        {
            int travType = getRandomTraverseType();
            printf("[Print] type=%d (0:Pre,1:In,2:Post,3:Level)\n", travType);

            printf("  배열 기반: ");
            PrintNodeA(tA, travType);

            printf("  연결 리스트 기반: ");
            PrintNodeLL(tLL, travType);

            break;
        }
        }
    }

    printf("===== 최종 트리 상태 =====\n");
    // 배열 기반 트리 최종 상태(Inorder)
    printf("배열 기반 트리(Inorder) : ");
    PrintNodeA(tA, 1);

    // 연결 리스트 기반 트리 최종 상태(Inorder)
    printf("연결 리스트 기반 트리(Inorder) : ");
    PrintNodeLL(tLL, 1);

    printf("트리 형태 체크\n");
    CheckBSTA(tA);
    CheckBSTLL(tLL);

    // 트리 메모리 해제
    DestroyArrayTree(tA);
    DestroyLListTree(tLL);

    return 0;
}
