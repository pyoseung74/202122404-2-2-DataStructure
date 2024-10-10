#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int GCD(int x, int y)
{
//여기를 채워넣으면 됩니다.
    int gcd=1;
    int min; // 두 수중 작은값을 찾기위해
    
    if (x < y)
        min = x;
    else
        min = y;
    
    for(int i=1 ; i<=min ; i++ ){
        if(x%i==0 && y%i==0){
            gcd=i;
        }
    }
    return gcd;
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
