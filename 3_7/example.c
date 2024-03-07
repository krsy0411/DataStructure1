#include <stdio.h>
#include <stdlib.h> //srand, rand를 사용하기 위한 헤더파일
#include <time.h> // time을 사용하기 위한 헤더파일

int main() {
    // 100개짜리와 10개짜리 배열
    int array[100];
    int tenNumbers[10];
    
    srand(time(NULL)); // 난수 초기화

    for (int i = 0; i< 100; i++) {		
        // 0 ~ 100 사이의 숫자를 뽑아서 random 변수에 저장		
        array[i] = rand() % 101;
    }

    for(int i=0; i<10; i++) {
        // 0 ~ 99 인덱스 내에서의 랜덤값
        int randomIndex = rand() % 100;
        tenNumbers[i] = array[randomIndex]; // 랜덤인덱스값의 100개짜리 배열 내 해당 인덱스 원소를 10개짜리 원소에 담아줍니다.
    }

    // 우선 0번째 인덱스 원소로 초기화
    int max = tenNumbers[0];
    for (int i = 0; i < 10; i++) {
        // 순서대로 비교하며 max값 업데이트
        if (tenNumbers[i] > max) max = tenNumbers[i];
    }
    printf("%d\n", max); // 출력

    return 0;
}