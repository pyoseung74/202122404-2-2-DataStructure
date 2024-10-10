#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 각 달의 총 일수(윤년 제외)
int mondata[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char* monthNames[] = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };

// 윤년 확인용 함수
int Yoon(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 연도와 월을 입력받고 그 월 첫 번째 날의 요일을 불러오는 함수
int getFirstDay(int year, int month) {
    int allDays = 0;

    // 1970년 부터 입력된 연도까지의 총 일수 계산
    for (int i = 1970; i < year; i++) {
        allDays += 365;
        if (Yoon(i)) {
            allDays += 1; // 윤년은 하루 추가
        }
    }

    // 입력한 연도의 1월부터 입력한 월까지의 총 일수 계산
    for (int j = 0; j < month - 1; j++) {
        allDays += mondata[j];
        if (j == 1 && Yoon(year)) {
            allDays += 1; // 윤년이면 2월에 하루 추가
        }
    }

    // 1970년 1월 1일은 목요일(4) 이므로 전체를 7로 나눈 나머지로 요일 계산
    return (allDays + 4) % 7;
}

// 해당 월의 일수를 반환하는 함수
int getMonthDays(int year, int month) {
    if (month == 2 && Yoon(year)) {
        return 29; // 2월 29일
    }
    return mondata[month - 1];
}

// 달력 출력 함수
void Calendar(int year, int month) {
    int firstDay = getFirstDay(year, month);
    int monthDays = getMonthDays(year, month);

    printf("\n             %10s\n", monthNames[month - 1]);
    printf("-------------------------------------\n");
    printf(" SUN  MON  TUE  WED  THU  FRI  SAT\n");
    printf("-----------------------------------\n");

    // 시작 요일에 맞춰 공백 출력
    for (int i = 0; i < firstDay; i++) {
        printf("     "); // 5칸 공백
    }

    // 날짜 출력
    for (int day = 1; day <= monthDays; day++) {
        printf(" %2d  ", day);

        // 토요일이면 줄 바꿈
        if ((firstDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    int year, month;

    // 연도와 월 입력
    printf("몇 년도 달력을 출력할까요? (1970년 이후) -> ");
    scanf("%d", &year);
    if (year < 1970) {
        printf("1970년 이후의 연도를 입력하세요.\n");
        return 1;
    }

    printf("몇 월 달력을 출력할까요? (1월~12월) -> ");
    scanf("%d", &month);
    if (month < 1 || month > 12) {
        printf("1월에서 12월 사이의 월을 입력하세요.\n");
        return 1;
    }

    // 달력 출력
    Calendar(year, month);

    return 0;
}
