#include <stdio.h>

// 포인터를 인자로 전달
void reverse(char *p, char *q) {
    // abcd 문자열의 개수
    int length = 4;

    for(int i=0; i<4; ++i) {
        // 역순의 주소값을 이용해 q에 원소 채워주기
        q[i] = *(p + length - i - 1);
    }
}

int main(void) {
    char s1[100], s2[100], *p, *q;
    int i;

    printf("문자열 입력: ");
    scanf("%s", s1);

    // 입력 문자열이 저장된 배열s1에 포인터 p 연결 : 배열은 &(주소연산자) 사용할 필요 없음
    p = s1;
    // 역순 문자열을 저장할 배열s2에 포인터 q 연결 : 배열은 &(주소연산자) 사용할 필요 없음
    q = s2;

    reverse(p, q);
    printf("역순 문자열 : %s\n", s2);

    return 0;
}