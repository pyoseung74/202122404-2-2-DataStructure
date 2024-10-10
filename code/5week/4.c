#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
     
void PrintWords(char** a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d : %s\n", i, a[i]);
	}
}

void main()
{
	char fullChar[1000];
	char** partChar;
	int count = 0;
	printf(" 전체 문장을 입력하세요. -> ");
	scanf(" %[^\n]s", fullChar);
	fflush(stdin);

//  여기서 partchar 를 제작하시오.
        
    // 단어 개수와 가장 긴 단어의 길이를 측정하기 위한 변수 선언
    int maxLen = 0;      // 가장 긴 단어의 길이를 저장할 변수
    int tempLen = 0;     // 현재 단어의 길이를 임시로 저장

    // 단어 개수와 최대 길이를 확인하는 루프
    for (int i = 0; fullChar[i] != '\0'; i++)
    {
        if (fullChar[i] == '/')
        {
            count++; // 단어 개수 증가
            if (tempLen > maxLen)
                maxLen = tempLen; // 최대 길이 갱신
            tempLen = 0; // 단어 길이 초기화
        }
        else
        {
            tempLen++; // 현재 단어 길이 증가
        }
    }
    count++; // 마지막 단어 포함
   
    if (tempLen > maxLen)
        maxLen = tempLen; // 마지막 단어가 가장 길 경우 갱신

    // partChar 배열 동적 할당 (단어 개수와 가장 긴 단어의 길이를 기반으로)
    partChar = (char**)malloc(sizeof(char*) * count);
    
    for (int i = 0; i < count; i++)
    {
        // 최대 길이에 맞게 할당
        partChar[i] = (char*)malloc(sizeof(char) * (maxLen + 1)); 
    }

    // 단어를 partChar 배열에 저장하는 루프
    int wordIndex = 0, charIndex = 0;
    
    for (int i = 0; fullChar[i] != '\0'; i++)
    {
        if (fullChar[i] == '/')
        {
            // 단어 끝에 null 추가
            partChar[wordIndex][charIndex] = '\0'; 
            
            wordIndex++; // 다음 단어로 이동
            charIndex = 0; // 글자 인덱스 초기화
        }
        else
        {
            partChar[wordIndex][charIndex++] = fullChar[i]; // 글자 복사
        }
    }
    
    // 마지막 단어 처리
    partChar[wordIndex][charIndex] = '\0';
    
//
	PrintWords(partChar, count);
}
