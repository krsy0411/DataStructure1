#include <stdio.h>
#include <time.h>

// 참조 연산자를 통해 넘겨받은 주소값으로부터 값을 참조합니다.
void iteration(int *base, int *exp) {
    int result = 1;
    // 반복적 연산 수행
    for(int i=0; i<*exp; i++) {
        result *= *base;
    }
    printf("Iteration 결과값 : %d\n", result);
}

int main(void) {
    int base;
    int exponential;

    printf("Input a Base : ");
    scanf("%d", &base);
    printf("Input an Exponential : ");
    scanf("%d", &exponential);
    
    // 입력받은 두 값에 대한 포인터 설정
    int *base_pointer = &base;
    int *exponential_pointer = &exponential;

    clock_t start = clock();
    // 포인터의 주소값을 넘겨줍니다
    iteration(base_pointer, exponential_pointer);
    clock_t end = clock();
    printf("반복 방법\n걸린 시간 : %ld 클록 틱\n", end-start);

    return 0;
}