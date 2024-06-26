#include <stdio.h>
#include <stdlib.h>

// 함수 인자 : 포인터 선언 형식 : 포인터는 주소값을 지닌 변수
void increment(int *p) {
    // 간접 참조 연산자(*) : 포인터 변수가 가리키는 주소에 저장된 값 반환
    (*p)++;
}

void hello() {
    printf("Hello, World!\n");
}

int main() {
    int exampleA = 10;
    // 포인터와 배열 : 둘은 매우 밀접한 관계
    // 배열의 변수 이름은, <배열의 첫 번째 요소의 주소를 가리키는 포인터>로 해석

    // 배열을 사용할때, 크게 두 가지 방식이 존재합니다.
    // 1. {}를 이용한 선언
    int arr1[5] = { 1,2,3,4,5 }; // arr1 자체를 포인터 변수로 사용 가능 : arr1 === 배열 첫번째 원소의 주소값을 가리키는 포인터
    int *p = arr1; // 이렇게 다른 포인터 변수에 할당해줘도 됩니다. : p는 arr의 첫 번째 요소의 주소를 가리키는 포인터

    // 2. 동적 메모리 할당
    int *arr2 = (int *)malloc(sizeof(int) * 5);
    for(int i=1; i<6; i++) {
        arr2[i] = i*10;
    }

    // 포인터를 활용하여 함수 인자로 전달할 수 있음 : 함수는 원본 값을 직접 수정 가능(포인터를 안 쓰고 전달하면, 실제 원본값은 변경되지 않습니다)
    increment(&exampleA); // 인자가 포인터 -> 주소값을 전달해줘야함 -> 주소연산자(&)를 이용해서 변수의 주소값 전달

    // 포인터 배열은 일반 배열과 마찬가지로 숫자뿐 아니라 다른 데이터 타입들도 가리킬 수 있음
    const char *names[] = { "Alice", "Bob", "Ralo" };
    printf("%s\n", names[0]);

    // 함수 포인터 : 함수의 주소를 저장하는 포인터 : 함수 호출을 동적으로 가능
    void (*helloFnPtr)() = hello; // 함수 포인터 선언 및 초기화
    helloFnPtr(); // 함수 포인터를 통한 함수 호출


    // 동적 메모리 할당 해제
    free(arr2);
    return 0;
}