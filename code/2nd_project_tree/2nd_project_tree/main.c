#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "tree.h"

#define NUM_OP 20      // �� ���� Ƚ��
#define RAND_STR_LEN 2 // ������ ���ڿ� ���� (��: 2����)

// ������ ���ڿ� ���� �Լ� (���ҹ��� RAND_STR_LEN��)
void getRandomString(char* buf, int length)
{
    for (int i = 0; i < length; i++)
    {
        buf[i] = 'a' + rand() % 26; // 'a' ~ 'z'
    }
    buf[length] = '\0'; // ���ڿ� ����
}

// ������ ��ȸ Ÿ�� ��� (0 ~ 3)
int getRandomTraverseType()
{
    return rand() % 4; // 0: Pre, 1: In, 2: Post, 3: Level
}

// ������ ����(Insert, Delete, Print) �� �ϳ� ����
// insert=0, delete=1, print=2 �� ����
int getRandomOperation()
{
    return rand() % 3; // 0 or 1 or 2
}

int main()
{
    // ������ ���� (Windows���� �ѱ� �޽����� ������ �ʵ���)
    setlocale(LC_ALL, "");

    // ���� �õ� ����
    srand((unsigned)time(NULL));

    // �迭 ���, ���� ����Ʈ ��� Ʈ�� ����
    tree_A* tA = CreateArrayTree();
    tree_LL* tLL = CreateLListTree();

    printf("===== ���� �׽�Ʈ ���� =====\n");

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

            printf("  �迭 ���: ");
            PrintNodeA(tA, travType);

            printf("  ���� ����Ʈ ���: ");
            PrintNodeLL(tLL, travType);

            break;
        }
        }
    }

    printf("===== ���� Ʈ�� ���� =====\n");
    // �迭 ��� Ʈ�� ���� ����(Inorder)
    printf("�迭 ��� Ʈ��(Inorder) : ");
    PrintNodeA(tA, 1);

    // ���� ����Ʈ ��� Ʈ�� ���� ����(Inorder)
    printf("���� ����Ʈ ��� Ʈ��(Inorder) : ");
    PrintNodeLL(tLL, 1);

    printf("Ʈ�� ���� üũ\n");
    CheckBSTA(tA);
    CheckBSTLL(tLL);

    // Ʈ�� �޸� ����
    DestroyArrayTree(tA);
    DestroyLListTree(tLL);

    return 0;
}
