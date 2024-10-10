#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int GCD(int x, int y)
{
//여기를 채워넣으면 됩니다.
   if (y == 0)
        return x;
    else
        return GCD(y, (x % y));
}

void main()
{
int a, b;
//입력
    printf("두 수를 입력하세요: ");
    
    scanf("%d %d", &a, &b);

//
printf("%d와 %d의 최대공약수는 %d입니다.\n",a,b,GCD(a,b));
}
