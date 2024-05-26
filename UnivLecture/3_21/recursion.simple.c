#include <stdio.h>
#include <time.h>

int recursion_simple(int base, int exp) {

    // 심플버전 순환 수행
    if(exp == 0) {
        return 1;
    } else {
        return base * recursion_simple(base, exp-1);
    }
}

int main(void) {
    int base;
    int exponential;

    printf("Input a Base : ");
    scanf("%d", &base);
    printf("Input an Exponential : ");
    scanf("%d", &exponential);

    clock_t start = clock();
    // 포인터 말고 그냥 복사값 넘기기
    int result = recursion_simple(base, exponential);
    clock_t end = clock();
    printf("순환 방법(심플버전) 결과값 : %d\n", result);
    printf("걸린 시간 : %ld 클록 틱\n", end-start);

    return 0;
}